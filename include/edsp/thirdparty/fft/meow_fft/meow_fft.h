/*
    meow_fft. My Easy Oresome Wonderful Fast Fourier Transform.
    Copyright (C) 2017 Richard Maxwell <jodi.the.tigger@gmail.com>

    Permission to use, copy, modify, and/or distribute this software for any
    purpose with or without fee is hereby granted.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
    OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
    CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef MEOW_FFT
#define MEOW_FFT

#include <stdlib.h>
// for size_t

#ifdef __cplusplus
extern "C" {
#endif

// C-API -----------------------------------------------------------------------

typedef struct Meow_FFT_Complex
{
    float r;
    float j;
}
Meow_FFT_Complex;

struct Meow_FFT_Workset;
struct Meow_FFT_Workset_Real;

size_t meow_fft_generate_workset
(
      int                      N
    , struct Meow_FFT_Workset* workset
);
// returns the size of the workset if null is passed.

size_t meow_fft_generate_workset_real
(
      int                           N
    , struct Meow_FFT_Workset_Real* workset
);
// returns the size of the workset if null is passed.

unsigned meow_fft_is_slow     (const struct Meow_FFT_Workset*      workset);
unsigned meow_fft_is_slow_real(const struct Meow_FFT_Workset_Real* workset);
// returns non-zero if the fft has a slow dft in any one of its stages.

// C-API (ffts) ----------------------------------------------------------------

// NOTES:
// countof(out) == countof(in).
// In order to do that I have mixed out[0] with out[N/2]. That is:
// out[0].r == out[0].r, out[0].j = out[N/2].r


void meow_fft_real
(
      const struct Meow_FFT_Workset_Real* workset
    , const float*                        in
    , Meow_FFT_Complex*                   out
);

void meow_fft_real_i
(
      const struct Meow_FFT_Workset_Real* workset
    , const Meow_FFT_Complex*             in
    , Meow_FFT_Complex*                   temp
    , float*                              out
);

void meow_fft
(
      const struct Meow_FFT_Workset* data
    , const Meow_FFT_Complex*        in
    , Meow_FFT_Complex*              out
);

void meow_fft_i
(
      const struct Meow_FFT_Workset* data
    , const Meow_FFT_Complex*        in
    , Meow_FFT_Complex*              out
);

// -----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // MEOW_FFT

#ifdef MEOW_FFT_IMPLEMENTAION

// Reading List ----------------------------------------------------------------
//
// It's a circle! -> How FFTs _actually_ work
// http://betterexplained.com/articles/an-interactive-guide-to-the-fourier-transform/
//
// How to get radix-2, 3, 4, and 5 formulas:
// http://www.briangough.com/fftalgorithms.pdf pages 18 and 19
//
// How do make a faster fft when only dealing with real (non-complex) inputs.
// (Warning, the maths is confusing due to inconsisten formulas and assumptions)
// http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM
//
// Finally, know that ffts are pretty much as fast as you can get, you need
// to start making them cache friendly to get any extra speed.
// https://math.mit.edu/~stevenj/18.335/FFTW-Alan-2008.pdf
//
// -----------------------------------------------------------------------------

#include <math.h>
#include <stdint.h>

typedef const Meow_FFT_Complex Complex;

#define MEOW_TAU 6.283185307179586476925286766559005768394338798750211641949889

// Plumbing --------------------------------------------------------------------

typedef struct Meow_Fft_Stages
{
    unsigned  count;
    unsigned* radix;
    unsigned* remainder;
    unsigned* offsets;
}
Meow_Fft_Stages;

typedef struct Meow_FFT_Workset
{
    int               N;

    Meow_FFT_Complex* wn;
    // Non-null only defined if there is a slow-dft as one of the radix stages.

    Meow_FFT_Complex* wn_ordered;
    // Sequentially ordered per stage, will be duplicates between stages.

    Meow_Fft_Stages   stages;
}
Meow_FFT_Workset;

typedef struct Meow_FFT_Workset_Real
{
    Meow_FFT_Complex* w_2n;
    Meow_FFT_Workset  half;
}
Meow_FFT_Workset_Real;

typedef struct Meow_Stage_Info
{
    unsigned is_slow;
    unsigned stage_count;
    unsigned w_count;
}
Meow_Stage_Info;

// -----------------------------------------------------------------------------

unsigned meow_is_codelet(unsigned radix)
{
    return ((radix <= 5) || (radix == 8));
}

void meow_make_twiddles
(
      unsigned          n
    , unsigned          count
    , Meow_FFT_Complex* w
)
{
    const double ni = 1.0f / n;
    for (unsigned i = 0; i < count; ++i)
    {
        w[i].r = (float) cos(MEOW_TAU * i * ni);
        w[i].j = (float) sin(MEOW_TAU * i * ni);
    }
};

unsigned meow_make_twiddles_sequential
(
      unsigned          n
    , Meow_FFT_Complex* w
    , Meow_Fft_Stages*  stages
)
// Returns number of W constants needed.
{
    // Figure out the tiddle offsets.
    unsigned w_count = 0;
    {
        unsigned offset = 0;

        for (unsigned s = 0; s < stages->count; s++)
        {
            unsigned r     = stages->radix[s];
            unsigned count = stages->remainder[s];

            unsigned amount = meow_is_codelet(r) ? (r - 1) * (count - 1) : 0u;

            stages->offsets[s]  = amount;
            offset             += amount;
        }

        w_count = offset;

        for (unsigned s = 0; s < stages->count; s++)
        {
            unsigned count = stages->offsets[s];
            offset -= count;
            stages->offsets[s] = offset;
        }
    }

    // Fill in the twiddles so that they are accessed sequentially in the radix
    // code for best cacheline use.
    if (w)
    {
        unsigned w_mul = 1;
        double   ni    = 1.0 / n;

        for (unsigned s = 0; s < stages->count; s++)
        {
            const unsigned radix  = stages->radix[s];
            const unsigned count  = stages->remainder[s];
                  unsigned offset = stages->offsets[s];

            if (meow_is_codelet(radix))
            {
                for (unsigned i = 1 ; i < count; i++)
                {
                    for (unsigned j = 1; j < radix; j++)
                    {
                        const unsigned w_x = i * j * w_mul;

                        w[offset].r = (float) cos(MEOW_TAU * w_x * ni);
                        w[offset].j = (float) sin(MEOW_TAU * w_x * ni);

                        offset++;
                    }
                }
            }

            w_mul  *= radix;
        }
    }

    return w_count;
};

Meow_Stage_Info meow_calculate_stages(unsigned n, Meow_FFT_Workset* workset)
{
    unsigned is_slow = 0u;
    unsigned stage   = 0u;
    unsigned w_count = 0u;

    while (n > 1)
    {
        // premade codelets 2, 3, 4, 5, 8
        unsigned i = 8;
        for (; i > 1; i--)
        {
            if ((i == 7) || (i == 6))
            {
                // don't have radix-7 or radix-6.
                continue;
            }

            if (!(n % i))
            {
                w_count += ((i - 1) * (n - 1));
                break;
            }
        }

        // bah, plain slow dft instead
        if (i == 1)
        {
            is_slow = 1;
            i       = 7;
            for (; i <= n; i++)
            {
                if (!(n % i))
                {
                    break;
                }
            }
        }

        n /= i;

        if (workset)
        {
            workset->stages.radix[stage]     = i;
            workset->stages.remainder[stage] = n;
        }

        stage++;
    }

    Meow_Stage_Info result =
    {
          is_slow
        , stage
        , w_count
    };

    return result;
}

size_t meow_fft_generate_workset(int N, Meow_FFT_Workset* workset)
{
    if (N < 2)
    {
        // Too small.
        return 0;
    }

    Meow_Stage_Info info = meow_calculate_stages(N, NULL);

    const size_t size_workset   = sizeof(Meow_FFT_Workset);
    const size_t size_radix     = info.stage_count * sizeof(int);
    const size_t size_remainder = info.stage_count * sizeof(int);
    const size_t size_offsets   = info.stage_count * sizeof(int);

    const size_t size_twiddles_ordered =
        info.w_count * sizeof(Meow_FFT_Complex);

    const size_t size_twiddles =
        N * sizeof(Meow_FFT_Complex) * info.is_slow;

    const size_t size_total =
          size_workset
        + size_twiddles
        + size_radix
        + size_remainder
        + size_offsets
        + size_twiddles_ordered;

    if (workset)
    {
        uint8_t* data            = (uint8_t*)(workset);

        uint8_t* data_wn         = data           + size_workset;
        uint8_t* data_radix      = data_wn        + size_twiddles;
        uint8_t* data_remainder  = data_radix     + size_radix;
        uint8_t* data_offsets    = data_remainder + size_offsets;
        uint8_t* data_wn_ordered = data_offsets   + size_remainder;

        workset->wn =
            (info.is_slow)
            ? (Meow_FFT_Complex*)(data_wn)
            : NULL;

        workset->stages.radix     = (unsigned*)(data_radix);
        workset->stages.remainder = (unsigned*)(data_remainder);
        workset->stages.offsets   = (unsigned*)(data_offsets);
        workset->stages.count     = info.stage_count;
        workset->wn_ordered       = (Meow_FFT_Complex*)(data_wn_ordered);
        workset->N                = N;

        if (workset->wn)
        {
            meow_make_twiddles(N, N, workset->wn);
        }

        meow_calculate_stages(N, workset);

        meow_make_twiddles_sequential
        (
              N
            , workset->wn_ordered
            , &workset->stages
        );
    }

    return size_total;
}

size_t meow_fft_generate_workset_real
(
      const int              N
    , Meow_FFT_Workset_Real* workset
)
{
    if ((N < 4) || (N % 2))
    {
        // Too small or not divisible by two.
        return -1;
    }

    const unsigned N_2 = N / 2;
    const unsigned N_4 = N / 4;

    const size_t size_workset = sizeof(Meow_FFT_Workset_Real);
    const size_t size_w_2n    = (N_4 + 1) * sizeof(Meow_FFT_Complex);
    const size_t size_half    = meow_fft_generate_workset(N_2, NULL);

    if (workset)
    {
        meow_fft_generate_workset(N_2, &workset->half);

        uint8_t* data      = (uint8_t*)(&workset->half);
        uint8_t* data_w_2n = data + size_half;

        workset->w_2n = (Meow_FFT_Complex*)(data_w_2n);

        meow_make_twiddles(N, N_4 + 1, workset->w_2n);
    }

    return size_workset + size_w_2n + size_half;
}

// -----------------------------------------------------------------------------

unsigned meow_fft_is_slow(const Meow_FFT_Workset* workset)
{
    return !!(workset->wn);
}

unsigned meow_fft_is_slow_real(const Meow_FFT_Workset_Real* workset)
{
    return meow_fft_is_slow(&workset->half);
}

// -----------------------------------------------------------------------------

Meow_FFT_Complex inline meow_add
(
      const Meow_FFT_Complex lhs
    , const Meow_FFT_Complex rhs
)
{
    Meow_FFT_Complex result =
    {
          lhs.r + rhs.r
        , lhs.j + rhs.j
    };

    return result;
}

Meow_FFT_Complex inline meow_sub
(
      const Meow_FFT_Complex lhs
    , const Meow_FFT_Complex rhs
)
{
    Meow_FFT_Complex result =
    {
          lhs.r - rhs.r
        , lhs.j - rhs.j
    };

    return result;
}

Meow_FFT_Complex inline meow_negate(const Meow_FFT_Complex lhs)
{
    Meow_FFT_Complex result =
    {
          -lhs.r
        , -lhs.j
    };

    return result;
}

Meow_FFT_Complex inline meow_conjugate(const Meow_FFT_Complex lhs)
{
    Meow_FFT_Complex result =
    {
           lhs.r
        , -lhs.j
    };

    return result;
}

Meow_FFT_Complex inline meow_mul
(
      const Meow_FFT_Complex lhs
    , const Meow_FFT_Complex rhs
)
{
    Meow_FFT_Complex result =
    {
          (lhs.r * rhs.r) - (lhs.j * rhs.j)
        , (lhs.r * rhs.j) + (lhs.j * rhs.r)
    };

    return result;
}

Meow_FFT_Complex inline meow_mul_by_conjugate
(
      const Meow_FFT_Complex lhs
    , const Meow_FFT_Complex rhs
)
{
    Meow_FFT_Complex result =
    {
          (lhs.r * rhs.r) + (lhs.j * rhs.j)
        , (lhs.j * rhs.r) - (lhs.r * rhs.j)
    };

    return result;
}

Meow_FFT_Complex inline meow_mul_by_j(const Meow_FFT_Complex lhs)
{
    Meow_FFT_Complex result =
    {
          -lhs.j
        ,  lhs.r
    };

    return result;
}

Meow_FFT_Complex inline meow_mulf
(
      const Meow_FFT_Complex lhs
    ,       float            rhs
)
{
    Meow_FFT_Complex result =
    {
          lhs.r * rhs
        , lhs.j * rhs
    };

    return result;
}

// -----------------------------------------------------------------------------

void meow_dft_n_dit
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
    , unsigned                w_multiplier
    , unsigned                radix
    , unsigned                N
    , unsigned                reverse
)
{
    // Can I do something with the knowledge that n is always odd?

    Meow_FFT_Complex scratch[radix];

    for (unsigned butterfly = 0; butterfly < count; ++butterfly)
    {
        for (unsigned i = 0; i < radix; i++)
        {
            scratch[i] = out[i * count + butterfly];
        }

        for (unsigned i = 0 ; i < radix ; ++i)
        {
            const unsigned  index_out = i * count + butterfly;

            // W0 is always 1
            Meow_FFT_Complex sum = scratch[0];

            for (unsigned j = 1; j < radix; ++j )
            {
                const unsigned wi = (j * w_multiplier * index_out) % N;
                Complex        w  = w_n[wi];
                Complex        in = scratch[j];

                float rr;
                float jj;

                if (reverse)
                {
                    rr = (in.r * w.r) - (in.j * w.j);
                    jj = (in.r * w.j) + (in.j * w.r);
                }
                else
                {
                    rr = (in.r * w.r) + (in.j * w.j);
                    jj = (in.j * w.r) - (in.r * w.j);
                }

                sum.r += rr;
                sum.j += jj;
            }

            out[index_out] = sum;
        }
    }
}

// -----------------------------------------------------------------------------

// Algorithms taken from
// http://www.briangough.com/fftalgorithms.pdf
// (equations 135 to 146)
// in, out and twiddle indicies taken from kiss_fft
// All twiddles are assumed to be ifft calculated. Conjugation is done in the
// maths.
// All twiddle input arrays are assumed to be sequentiall accessed. Twiddle
// indicies are pre-calculated.

// -----------------------------------------------------------------------------
// Forward
// -----------------------------------------------------------------------------

void meow_radix_2_dit
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    // butteryfly 0 always has the twiddle factor == 1.0f
    // so special case that one.
    {
        Complex z0  = out[0];
        Complex z1  = out[count];

        out[0]     = meow_add(z0, z1);
        out[count] = meow_sub(z0, z1);
    }

    for (unsigned butterfly = 1; butterfly < count; ++butterfly)
    {
        Complex  w   = w_n[butterfly - 1];

        const unsigned i0  = butterfly;
        const unsigned i1  = butterfly + count;

        Complex z0  = out[i0];
        Complex z1  = meow_mul_by_conjugate(out[i1], w);

        out[i0] = meow_add(z0, z1);
        out[i1] = meow_sub(z0, z1);
        // Equation 135
    }
}

#define MEOW_SIN_PI_3 -0.866025403784438646763723170752936183471402626905190314f

void meow_radix_3_dit
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    // W[0] is always 1.0f;
    {
        const unsigned i0  = 0 * count;
        const unsigned i1  = 1 * count;
        const unsigned i2  = 2 * count;

        Complex z0  = out[i0];
        Complex z1  = out[i1];
        Complex z2  = out[i2];

        Complex t1  = meow_add(z1, z2);
        Complex t2  = meow_sub(z0, meow_mulf(t1, 0.5));
        Complex t3j = meow_mul_by_j(meow_mulf(meow_sub(z1, z2), MEOW_SIN_PI_3));

        out[i0] = meow_add(z0, t1);
        out[i1] = meow_add(t2, t3j);
        out[i2] = meow_sub(t2, t3j);
    }

    unsigned wi = 0;
    for (unsigned butterfly = 1; butterfly < count; butterfly++, wi+=2)
    {
        Complex w1  = w_n[wi + 0];
        Complex w2  = w_n[wi + 1];

        const unsigned i0  = butterfly;
        const unsigned i1  = butterfly + count;
        const unsigned i2  = butterfly + 2 * count;

        Complex z0  = out[i0];
        Complex z1  = meow_mul_by_conjugate(out[i1], w1);
        Complex z2  = meow_mul_by_conjugate(out[i2], w2);

        Complex t1  = meow_add(z1, z2);
        Complex t2  = meow_sub(z0, meow_mulf(t1, 0.5));
        Complex t3j = meow_mul_by_j(meow_mulf(meow_sub(z1, z2), MEOW_SIN_PI_3));
        // Equation 136

        out[i0] = meow_add(z0, t1);
        out[i1] = meow_add(t2, t3j);
        out[i2] = meow_sub(t2, t3j);
        // Equation 137
    }
}

void meow_radix_4_dit
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    // W[0] is always 1.0f;
    {
        const unsigned i0  = 0 * count;
        const unsigned i1  = 1 * count;
        const unsigned i2  = 2 * count;
        const unsigned i3  = 3 * count;

        Complex z0  = out[i0];
        Complex z1  = out[i1];
        Complex z2  = out[i2];
        Complex z3  = out[i3];

        Complex t1  = meow_add(z0, z2);
        Complex t2  = meow_add(z1, z3);
        Complex t3  = meow_sub(z0, z2);
        Complex t4j = meow_negate(meow_mul_by_j(meow_sub(z1, z3)));

        out[i0] = meow_add(t1, t2);
        out[i1] = meow_add(t3, t4j);
        out[i2] = meow_sub(t1, t2);
        out[i3] = meow_sub(t3, t4j);
    }

    unsigned wi = 0u;
    for (unsigned butterfly = 1; butterfly < count; ++butterfly, wi+=3)
    {
        Complex w1  = w_n[wi + 0];
        Complex w2  = w_n[wi + 1];
        Complex w3  = w_n[wi + 2];

        const unsigned i0  = butterfly + 0 * count;
        const unsigned i1  = butterfly + 1 * count;
        const unsigned i2  = butterfly + 2 * count;
        const unsigned i3  = butterfly + 3 * count;

        Complex z0  = out[i0];
        Complex z1  = meow_mul_by_conjugate(out[i1], w1);
        Complex z2  = meow_mul_by_conjugate(out[i2], w2);
        Complex z3  = meow_mul_by_conjugate(out[i3], w3);

        Complex t1  = meow_add(z0, z2);
        Complex t2  = meow_add(z1, z3);
        Complex t3  = meow_sub(z0, z2);
        Complex t4j = meow_negate(meow_mul_by_j(meow_sub(z1, z3)));
        // Equations 138
        // Also instead of conjugating the input and multplying with the
        // twiddles for the ifft, we invert the twiddles instead. This works
        // fine except here, the mul_by_j is assuming that it's the forward
        // fft twiddle we are multiplying with, not the conjugated one we
        // actually have. So we have to conjugate it _back_ if we are doing the
        // ifft.
        // Also, had to multiply by -j, not j for reasons I am yet to grasp.

        out[i0] = meow_add(t1, t2);
        out[i1] = meow_add(t3, t4j);
        out[i2] = meow_sub(t1, t2);
        out[i3] = meow_sub(t3, t4j);
        // Equations 139
    }
}

#define MEOW_SQR_5_DIV_4 0.5590169943749474241022934171828190588601545899028814f
#define MEOW_SIN_2PI_5  -0.9510565162951535721164393333793821434056986341257502f
#define MEOW_SIN_2PI_10 -0.5877852522924731291687059546390727685976524376431459f

void meow_radix_5_dit
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned              count
)
{
    // W[0] is always 1.0f;
    {
        const unsigned i0   = 0 * count;
        const unsigned i1   = 1 * count;
        const unsigned i2   = 2 * count;
        const unsigned i3   = 3 * count;
        const unsigned i4   = 4 * count;

        Complex z0   = out[i0];
        Complex z1   = out[i1];
        Complex z2   = out[i2];
        Complex z3   = out[i3];
        Complex z4   = out[i4];

        Complex t1   = meow_add(z1, z4);
        Complex t2   = meow_add(z2, z3);
        Complex t3   = meow_sub(z1, z4);
        Complex t4   = meow_sub(z2, z3);
        // Equations 140

        Complex t5   = meow_add(t1, t2);
        Complex t6   = meow_mulf(meow_sub(t1, t2), MEOW_SQR_5_DIV_4);
        Complex t7   = meow_sub(z0, meow_mulf(t5, 0.25f));
        // Equation 141

        Complex t8   = meow_add(t7, t6);
        Complex t9   = meow_sub(t7, t6);
        // Equation 142

        Complex t10j = meow_mul_by_j
        (
            meow_add
            (
                  meow_mulf(t3, MEOW_SIN_2PI_5)
                , meow_mulf(t4, MEOW_SIN_2PI_10)
            )
        );

        Complex t11j = meow_mul_by_j
        (
            meow_sub
            (
                  meow_mulf(t3, MEOW_SIN_2PI_10)
                , meow_mulf(t4, MEOW_SIN_2PI_5)
            )
        );
        // Equation 143

        out[i0] = meow_add(z0, t5);
        // Equation 144

        out[i1] = meow_add(t8, t10j);
        out[i2] = meow_add(t9, t11j);
        // Equation 145

        out[i3] = meow_sub(t9, t11j);
        out[i4] = meow_sub(t8, t10j);
        // Equation 146
    }

    unsigned wi = 0u;
    for (unsigned butterfly = 1; butterfly < count; ++butterfly, wi+=4)
    {
        Complex w1  = w_n[wi + 0];
        Complex w2  = w_n[wi + 1];
        Complex w3  = w_n[wi + 2];
        Complex w4  = w_n[wi + 3];

        unsigned i0   = butterfly + 0 * count;
        unsigned i1   = butterfly + 1 * count;
        unsigned i2   = butterfly + 2 * count;
        unsigned i3   = butterfly + 3 * count;
        unsigned i4   = butterfly + 4 * count;

        Complex z0   = out[i0];
        Complex z1   = meow_mul_by_conjugate(out[i1], w1);
        Complex z2   = meow_mul_by_conjugate(out[i2], w2);
        Complex z3   = meow_mul_by_conjugate(out[i3], w3);
        Complex z4   = meow_mul_by_conjugate(out[i4], w4);

        Complex t1   = meow_add(z1, z4);
        Complex t2   = meow_add(z2, z3);
        Complex t3   = meow_sub(z1, z4);
        Complex t4   = meow_sub(z2, z3);
        // Equations 140

        Complex t5   = meow_add(t1, t2);
        Complex t6   = meow_mulf(meow_sub(t1, t2), MEOW_SQR_5_DIV_4);
        Complex t7   = meow_sub(z0, meow_mulf(t5, 0.25f));
        // Equation 141

        Complex t8   = meow_add(t7, t6);
        Complex t9   = meow_sub(t7, t6);
        // Equation 142

        Complex t10j = meow_mul_by_j
        (
            meow_add
            (
                  meow_mulf(t3, MEOW_SIN_2PI_5)
                , meow_mulf(t4, MEOW_SIN_2PI_10)
            )
        );

        Complex t11j = meow_mul_by_j
        (
            meow_sub
            (
                  meow_mulf(t3, MEOW_SIN_2PI_10)
                , meow_mulf(t4, MEOW_SIN_2PI_5)
            )
        );
        // Equation 143

        out[i0] = meow_add(z0, t5);
        // Equation 144

        out[i1] = meow_add(t8, t10j);
        out[i2] = meow_add(t9, t11j);
        // Equation 145

        out[i3] = meow_sub(t9, t11j);
        out[i4] = meow_sub(t8, t10j);
        // Equation 146
    }
}

#define MEOW_1_DIV_SQR_2 0.707106781186547524400844362104849039284835938f

static void meow_radix_8_dit
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    const float* W = &w_n[0].r;

    {
        float T3;
        float T23;
        float T18;
        float T38;
        float T6;
        float T37;
        float T21;
        float T24;
        float T13;
        float T49;
        float T35;
        float T43;
        float T10;
        float T48;
        float T30;
        float T42;
        {
            float T1;
            float T2;
            float T19;
            float T20;
            T1 = out[0].r;
            T2 = out[count * 4].r;
            T3 = T1 + T2;
            T23 = T1 - T2;
            {
                float T16;
                float T17;
                float T4;
                float T5;
                T16 = out[0].j;
                T17 = out[count * 4].j;
                T18 = T16 + T17;
                T38 = T16 - T17;
                T4 = out[count * 2].r;
                T5 = out[count * 6].r;
                T6 = T4 + T5;
                T37 = T4 - T5;
            }
            T19 = out[count * 2].j;
            T20 = out[count * 6].j;
            T21 = T19 + T20;
            T24 = T19 - T20;
            {
                float T11;
                float T12;
                float T31;
                float T32;
                float T33;
                float T34;
                T11 = out[count * 7].r;
                T12 = out[count * 3].r;
                T31 = T11 - T12;
                T32 = out[count * 7].j;
                T33 = out[count * 3].j;
                T34 = T32 - T33;
                T13 = T11 + T12;
                T49 = T32 + T33;
                T35 = T31 - T34;
                T43 = T31 + T34;
            }
            {
                float T8;
                float T9;
                float T26;
                float T27;
                float T28;
                float T29;
                T8 = out[count * 1].r;
                T9 = out[count * 5].r;
                T26 = T8 - T9;
                T27 = out[count * 1].j;
                T28 = out[count * 5].j;
                T29 = T27 - T28;
                T10 = T8 + T9;
                T48 = T27 + T28;
                T30 = T26 + T29;
                T42 = T29 - T26;
            }
        }
        {
            float T7;
            float T14;
            float T51;
            float T52;
            T7 = T3 + T6;
            T14 = T10 + T13;
            out[count * 4].r = T7 - T14;
            out[0].r = T7 + T14;
            T51 = T18 + T21;
            T52 = T48 + T49;
            out[count * 4].j = T51 - T52;
            out[0].j = T51 + T52;
        }
        {
            float T15;
            float T22;
            float T47;
            float T50;
            T15 = T13 - T10;
            T22 = T18 - T21;
            out[count * 2].j = T15 + T22;
            out[count * 6].j = T22 - T15;
            T47 = T3 - T6;
            T50 = T48 - T49;
            out[count * 6].r = T47 - T50;
            out[count * 2].r = T47 + T50;
        }
        {
            float T25;
            float T36;
            float T45;
            float T46;
            T25 = T23 + T24;
            T36 = MEOW_1_DIV_SQR_2 * (T30 + T35);
            out[count * 5].r = T25 - T36;
            out[count * 1].r = T25 + T36;
            T45 = T38 - T37;
            T46 = MEOW_1_DIV_SQR_2 * (T42 + T43);
            out[count * 5].j = T45 - T46;
            out[count * 1].j = T45 + T46;
        }
        {
            float T39;
            float T40;
            float T41;
            float T44;
            T39 = T37 + T38;
            T40 = MEOW_1_DIV_SQR_2 * (T35 - T30);
            out[count * 7].j = T39 - T40;
            out[count * 3].j = T39 + T40;
            T41 = T23 - T24;
            T44 = MEOW_1_DIV_SQR_2 * (T42 - T43);
            out[count * 7].r = T41 - T44;
            out[count * 3].r = T41 + T44;
        }
    }

    out = out + 1;

    {
        unsigned m;
        for (m = 1; m < count; m = m + 1, out = out + 1, W = W + 14)
        {
            float T7;
            float T76;
            float T43;
            float T71;
            float T41;
            float T65;
            float T53;
            float T56;
            float T18;
            float T77;
            float T46;
            float T68;
            float T30;
            float T64;
            float T48;
            float T51;
            {
                float T1;
                float T70;
                float T6;
                float T69;
                T1 = out[0].r;
                T70 = out[0].j;
                {
                    float T3;
                    float T5;
                    float T2;
                    float T4;
                    T3 = out[count * 4].r;
                    T5 = out[count * 4].j;
                    T2 = W[6];
                    T4 = W[7];
                    T6 = (T2 * T3) + (T4 * T5);
                    T69 = (T2 * T5) - (T4 * T3);
                }
                T7 = T1 + T6;
                T76 = T70 - T69;
                T43 = T1 - T6;
                T71 = T69 + T70;
            }
            {
                float T35;
                float T54;
                float T40;
                float T55;
                {
                    float T32;
                    float T34;
                    float T31;
                    float T33;
                    T32 = out[count * 7].r;
                    T34 = out[count * 7].j;
                    T31 = W[12];
                    T33 = W[13];
                    T35 = (T31 * T32) + (T33 * T34);
                    T54 = (T31 * T34) - (T33 * T32);
                }
                {
                    float T37;
                    float T39;
                    float T36;
                    float T38;
                    T37 = out[count * 3].r;
                    T39 = out[count * 3].j;
                    T36 = W[4];
                    T38 = W[5];
                    T40 = (T36 * T37) + (T38 * T39);
                    T55 = (T36 * T39) - (T38 * T37);
                }
                T41 = T35 + T40;
                T65 = T54 + T55;
                T53 = T35 - T40;
                T56 = T54 - T55;
            }
            {
                float T12;
                float T44;
                float T17;
                float T45;
                {
                    float T9;
                    float T11;
                    float T8;
                    float T10;
                    T9 = out[count * 2].r;
                    T11 = out[count * 2].j;
                    T8 = W[2];
                    T10 = W[3];
                    T12 = (T8 * T9) + (T10 * T11);
                    T44 = (T8 * T11) - (T10 * T9);
                }
                {
                    float T14;
                    float T16;
                    float T13;
                    float T15;
                    T14 = out[count * 6].r;
                    T16 = out[count * 6].j;
                    T13 = W[10];
                    T15 = W[11];
                    T17 = (T13 * T14) + (T15 * T16);
                    T45 = (T13 * T16) - (T15 * T14);
                }
                T18 = T12 + T17;
                T77 = T12 - T17;
                T46 = T44 - T45;
                T68 = T44 + T45;
            }
            {
                float T24;
                float T49;
                float T29;
                float T50;
                {
                    float T21;
                    float T23;
                    float T20;
                    float T22;
                    T21 = out[count * 1].r;
                    T23 = out[count * 1].j;
                    T20 = W[0];
                    T22 = W[1];
                    T24 = (T20 * T21) + (T22 * T23);
                    T49 = (T20 * T23) - (T22 * T21);
                }
                {
                    float T26;
                    float T28;
                    float T25;
                    float T27;
                    T26 = out[count * 5].r;
                    T28 = out[count * 5].j;
                    T25 = W[8];
                    T27 = W[9];
                    T29 = (T25 * T26) + (T27 * T28);
                    T50 = (T25 * T28) - (T27 * T26);
                }
                T30 = T24 + T29;
                T64 = T49 + T50;
                T48 = T24 - T29;
                T51 = T49 - T50;
            }
            {
                float T19;
                float T42;
                float T73;
                float T74;
                T19 = T7 + T18;
                T42 = T30 + T41;
                out[count * 4].r = T19 - T42;
                out[0].r = T19 + T42;
                {
                    float T67;
                    float T72;
                    float T63;
                    float T66;
                    T67 = T64 + T65;
                    T72 = T68 + T71;
                    out[0].j = T67 + T72;
                    out[count * 4].j = T72 - T67;
                    T63 = T7 - T18;
                    T66 = T64 - T65;
                    out[count * 6].r = T63 - T66;
                    out[count * 2].r = T63 + T66;
                }
                T73 = T41 - T30;
                T74 = T71 - T68;
                out[count * 2].j = T73 + T74;
                out[count * 6].j = T74 - T73;
                {
                    float T59;
                    float T78;
                    float T62;
                    float T75;
                    float T60;
                    float T61;
                    T59 = T43 - T46;
                    T78 = T76 - T77;
                    T60 = T51 - T48;
                    T61 = T53 + T56;
                    T62 = MEOW_1_DIV_SQR_2 * (T60 - T61);
                    T75 = MEOW_1_DIV_SQR_2 * (T60 + T61);
                    out[count * 7].r = T59 - T62;
                    out[count * 5].j = T78 - T75;
                    out[count * 3].r = T59 + T62;
                    out[count * 1].j = T75 + T78;
                }
                {
                    float T47;
                    float T80;
                    float T58;
                    float T79;
                    float T52;
                    float T57;
                    T47 = T43 + T46;
                    T80 = T77 + T76;
                    T52 = T48 + T51;
                    T57 = T53 - T56;
                    T58 = MEOW_1_DIV_SQR_2 * (T52 + T57);
                    T79 = MEOW_1_DIV_SQR_2 * (T57 - T52);
                    out[count * 5].r = T47 - T58;
                    out[count * 7].j = T80 - T79;
                    out[count * 1].r = T47 + T58;
                    out[count * 3].j = T79 + T80;
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------
// Inverse
// -----------------------------------------------------------------------------

void meow_radix_2_dit_i
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    // butteryfly 0 always has the twiddle factor == 1.0f
    // so special case that one.
    {
        Complex z0  = out[0];
        Complex z1  = out[count];

        out[0]     = meow_add(z0, z1);
        out[count] = meow_sub(z0, z1);
    }

    for (unsigned butterfly = 1; butterfly < count; ++butterfly)
    {
        Complex  w   = w_n[butterfly - 1];

        const unsigned i0  = butterfly;
        const unsigned i1  = butterfly + count;

        Complex z0  = out[i0];
        Complex z1  = meow_mul(out[i1], w);

        out[i0] = meow_add(z0, z1);
        out[i1] = meow_sub(z0, z1);
        // Equation 135
    }
}

void meow_radix_3_dit_i
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    // W[0] is always 1.0f;
    {
        const unsigned i0  = 0 * count;
        const unsigned i1  = 1 * count;
        const unsigned i2  = 2 * count;

        Complex z0  = out[i0];
        Complex z1  = out[i1];
        Complex z2  = out[i2];

        Complex t1  = meow_add(z1, z2);
        Complex t2  = meow_sub(z0, meow_mulf(t1, 0.5));
        Complex t3j = meow_mul_by_j
        (
            meow_mulf(meow_sub(z1, z2), -MEOW_SIN_PI_3)
        );

        out[i0] = meow_add(z0, t1);
        out[i1] = meow_add(t2, t3j);
        out[i2] = meow_sub(t2, t3j);
    }

    unsigned wi = 0u;
    for (unsigned butterfly = 1; butterfly < count; butterfly++, wi+=2)
    {
        Complex w1  = w_n[wi + 0];
        Complex w2  = w_n[wi + 1];

        const unsigned i0  = butterfly;
        const unsigned i1  = butterfly + count;
        const unsigned i2  = butterfly + 2 * count;

        Complex z0  =         out[i0];
        Complex z1  = meow_mul(w1, out[i1]);
        Complex z2  = meow_mul(w2, out[i2]);

        Complex t1  = meow_add(z1, z2);
        Complex t2  = meow_sub(z0, meow_mulf(t1, 0.5));
        Complex t3j = meow_mul_by_j
        (
            meow_mulf(meow_sub(z1, z2), -MEOW_SIN_PI_3)
        );
        // Equation 136

        out[i0] = meow_add(z0, t1);
        out[i1] = meow_add(t2, t3j);
        out[i2] = meow_sub(t2, t3j);
        // Equation 137
    }
}

void meow_radix_4_dit_i
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    // W[0] is always 1.0f;
    {
        const unsigned i0  = 0 * count;
        const unsigned i1  = 1 * count;
        const unsigned i2  = 2 * count;
        const unsigned i3  = 3 * count;

        Complex z0  = out[i0];
        Complex z1  = out[i1];
        Complex z2  = out[i2];
        Complex z3  = out[i3];

        Complex t1  = meow_add(z0, z2);
        Complex t2  = meow_add(z1, z3);
        Complex t3  = meow_sub(z0, z2);
        Complex t4j = meow_mul_by_j(meow_sub(z1, z3));

        out[i0] = meow_add(t1, t2);
        out[i1] = meow_add(t3, t4j);
        out[i2] = meow_sub(t1, t2);
        out[i3] = meow_sub(t3, t4j);
    }

    unsigned wi = 0u;
    for (unsigned butterfly = 1; butterfly < count; ++butterfly, wi+=3)
    {
        Complex w1  = w_n[wi + 0];
        Complex w2  = w_n[wi + 1];
        Complex w3  = w_n[wi + 2];

        const unsigned i0  = butterfly + 0 * count;
        const unsigned i1  = butterfly + 1 * count;
        const unsigned i2  = butterfly + 2 * count;
        const unsigned i3  = butterfly + 3 * count;

        Complex z0  =         out[i0];
        Complex z1  = meow_mul(w1, out[i1]);
        Complex z2  = meow_mul(w2, out[i2]);
        Complex z3  = meow_mul(w3, out[i3]);

        Complex t1  = meow_add(z0, z2);
        Complex t2  = meow_add(z1, z3);
        Complex t3  = meow_sub(z0, z2);

        Complex t4j = meow_mul_by_j(meow_sub(z1, z3));
        // Equations 138
        // Also instead of conjugating the input and multplying with the
        // twiddles for the ifft, we invert the twiddles instead. This works
        // fine except here, the mul_by_j is assuming that it's the forward
        // fft twiddle we are multiplying with, not the conjugated one we
        // actually have. So we have to conjugate it _back_ if we are doing the
        // ifft.
        // Also, had to multiply by -j, not j for reasons I am yet to grasp.

        out[i0] = meow_add(t1, t2);
        out[i1] = meow_add(t3, t4j);
        out[i2] = meow_sub(t1, t2);
        out[i3] = meow_sub(t3, t4j);
        // Equations 139
    }
}

void meow_radix_5_dit_i
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    // W[0] is always 1.0f;
    {
        const unsigned i0   = 0 * count;
        const unsigned i1   = 1 * count;
        const unsigned i2   = 2 * count;
        const unsigned i3   = 3 * count;
        const unsigned i4   = 4 * count;

        Complex z0   = out[i0];
        Complex z1   = out[i1];
        Complex z2   = out[i2];
        Complex z3   = out[i3];
        Complex z4   = out[i4];

        Complex t1   = meow_add(z1, z4);
        Complex t2   = meow_add(z2, z3);
        Complex t3   = meow_sub(z1, z4);
        Complex t4   = meow_sub(z2, z3);
        // Equations 140

        Complex t5   = meow_add(t1, t2);
        Complex t6   = meow_mulf(meow_sub(t1, t2), MEOW_SQR_5_DIV_4);
        Complex t7   = meow_sub(z0, meow_mulf(t5, 0.25f));
        // Equation 141

        Complex t8   = meow_add(t7, t6);
        Complex t9   = meow_sub(t7, t6);
        // Equation 142

        Complex t10j = meow_mul_by_j
        (
            meow_add
            (
                  meow_mulf(t3, -MEOW_SIN_2PI_5)
                , meow_mulf(t4, -MEOW_SIN_2PI_10)
            )
        );

        Complex t11j = meow_mul_by_j
        (
            meow_sub
            (
                  meow_mulf(t3, -MEOW_SIN_2PI_10)
                , meow_mulf(t4, -MEOW_SIN_2PI_5)
            )
        );
        // Equation 143

        out[i0] = meow_add(z0, t5);
        // Equation 144

        out[i1] = meow_add(t8, t10j);
        out[i2] = meow_add(t9, t11j);
        // Equation 145

        out[i3] = meow_sub(t9, t11j);
        out[i4] = meow_sub(t8, t10j);
        // Equation 146
    }

    unsigned wi = 0u;
    for (unsigned butterfly = 1; butterfly < count; ++butterfly, wi+=4)
    {
        Complex w1  = w_n[wi + 0];
        Complex w2  = w_n[wi + 1];
        Complex w3  = w_n[wi + 2];
        Complex w4  = w_n[wi + 3];

        const unsigned i0   = butterfly + 0 * count;
        const unsigned i1   = butterfly + 1 * count;
        const unsigned i2   = butterfly + 2 * count;
        const unsigned i3   = butterfly + 3 * count;
        const unsigned i4   = butterfly + 4 * count;

        Complex z0   =         out[i0];
        Complex z1   = meow_mul(w1, out[i1]);
        Complex z2   = meow_mul(w2, out[i2]);
        Complex z3   = meow_mul(w3, out[i3]);
        Complex z4   = meow_mul(w4, out[i4]);

        Complex t1   = meow_add(z1, z4);
        Complex t2   = meow_add(z2, z3);
        Complex t3   = meow_sub(z1, z4);
        Complex t4   = meow_sub(z2, z3);
        // Equations 140

        Complex t5   = meow_add(t1, t2);
        Complex t6   = meow_mulf(meow_sub(t1, t2), MEOW_SQR_5_DIV_4);
        Complex t7   = meow_sub(z0, meow_mulf(t5, 0.25f));
        // Equation 141

        Complex t8   = meow_add(t7, t6);
        Complex t9   = meow_sub(t7, t6);
        // Equation 142

        Complex t10j = meow_mul_by_j
        (
            meow_add
            (
                  meow_mulf(t3, -MEOW_SIN_2PI_5)
                , meow_mulf(t4, -MEOW_SIN_2PI_10)
            )
        );

        Complex t11j = meow_mul_by_j
        (
            meow_sub
            (
                  meow_mulf(t3, -MEOW_SIN_2PI_10)
                , meow_mulf(t4, -MEOW_SIN_2PI_5)
            )
        );
        // Equation 143

        out[i0] = meow_add(z0, t5);
        // Equation 144

        out[i1] = meow_add(t8, t10j);
        out[i2] = meow_add(t9, t11j);
        // Equation 145

        out[i3] = meow_sub(t9, t11j);
        out[i4] = meow_sub(t8, t10j);
        // Equation 146
    }
}

static void meow_radix_8_dit_i
(
      const Meow_FFT_Complex* w_n
    , Meow_FFT_Complex*       out
    , unsigned                count
)
{
    const float* W = &w_n[0].r;
    {
        float T3;
        float T37;
        float T18;
        float T23;
        float T6;
        float T24;
        float T21;
        float T38;
        float T13;
        float T49;
        float T35;
        float T43;
        float T10;
        float T48;
        float T30;
        float T42;
        {
            float T1;
            float T2;
            float T19;
            float T20;
            T1 = out[0].r;
            T2 = out[count * 4].r;
            T3 = T1 + T2;
            T37 = T1 - T2;
            {
                float T16;
                float T17;
                float T4;
                float T5;
                T16 = out[0].j;
                T17 = out[count * 4].j;
                T18 = T16 + T17;
                T23 = T16 - T17;
                T4 = out[count * 2].r;
                T5 = out[count * 6].r;
                T6 = T4 + T5;
                T24 = T4 - T5;
            }
            T19 = out[count * 2].j;
            T20 = out[count * 6].j;
            T21 = T19 + T20;
            T38 = T19 - T20;
            {
                float T11;
                float T12;
                float T31;
                float T32;
                float T33;
                float T34;
                T11 = out[count * 7].r;
                T12 = out[count * 3].r;
                T31 = T11 - T12;
                T32 = out[count * 7].j;
                T33 = out[count * 3].j;
                T34 = T32 - T33;
                T13 = T11 + T12;
                T49 = T32 + T33;
                T35 = T31 + T34;
                T43 = T34 - T31;
            }
            {
                float T8;
                float T9;
                float T26;
                float T27;
                float T28;
                float T29;
                T8 = out[count * 1].r;
                T9 = out[count * 5].r;
                T26 = T8 - T9;
                T27 = out[count * 1].j;
                T28 = out[count * 5].j;
                T29 = T27 - T28;
                T10 = T8 + T9;
                T48 = T27 + T28;
                T30 = T26 - T29;
                T42 = T26 + T29;
            }
        }
        {
            float T7;
            float T14;
            float T47;
            float T50;
            T7 = T3 + T6;
            T14 = T10 + T13;
            out[count * 4].r = T7 - T14;
            out[0].r = T7 + T14;
            T47 = T18 + T21;
            T50 = T48 + T49;
            out[count * 4].j = T47 - T50;
            out[0].j = T47 + T50;
        }
        {
            float T15;
            float T22;
            float T51;
            float T52;
            T15 = T10 - T13;
            T22 = T18 - T21;
            out[count * 2].j = T15 + T22;
            out[count * 6].j = T22 - T15;
            T51 = T3 - T6;
            T52 = T49 - T48;
            out[count * 6].r = T51 - T52;
            out[count * 2].r = T51 + T52;
        }
        {
            float T25;
            float T36;
            float T45;
            float T46;
            T25 = T23 - T24;
            T36 = MEOW_1_DIV_SQR_2 * (T30 - T35);
            out[count * 7].j = T25 - T36;
            out[count * 3].j = T25 + T36;
            T45 = T37 + T38;
            T46 = MEOW_1_DIV_SQR_2 * (T43 - T42);
            out[count * 7].r = T45 - T46;
            out[count * 3].r = T45 + T46;
        }
        {
            float T39;
            float T40;
            float T41;
            float T44;
            T39 = T37 - T38;
            T40 = MEOW_1_DIV_SQR_2 * (T30 + T35);
            out[count * 5].r = T39 - T40;
            out[count * 1].r = T39 + T40;
            T41 = T24 + T23;
            T44 = MEOW_1_DIV_SQR_2 * (T42 + T43);
            out[count * 5].j = T41 - T44;
            out[count * 1].j = T41 + T44;
        }
    }

    out = out + 1;

    {
        unsigned m;
        for (m = 1; m < count; m = m + 1, out = out + 1, W = W + 14)
        {
            float T7;
            float T77;
            float T43;
            float T71;
            float T41;
            float T64;
            float T53;
            float T56;
            float T18;
            float T76;
            float T46;
            float T68;
            float T30;
            float T65;
            float T48;
            float T51;
            {
                float T1;
                float T70;
                float T6;
                float T69;
                T1 = out[0].r;
                T70 = out[0].j;
                {
                    float T3;
                    float T5;
                    float T2;
                    float T4;
                    T3 = out[count * 4].r;
                    T5 = out[count * 4].j;
                    T2 = W[6];
                    T4 = W[7];
                    T6 = (T2 * T3) - (T4 * T5);
                    T69 = (T4 * T3) + (T2 * T5);
                }
                T7 = T1 + T6;
                T77 = T70 - T69;
                T43 = T1 - T6;
                T71 = T69 + T70;
            }
            {
                float T35;
                float T54;
                float T40;
                float T55;
                {
                    float T32;
                    float T34;
                    float T31;
                    float T33;
                    T32 = out[count * 7].r;
                    T34 = out[count * 7].j;
                    T31 = W[12];
                    T33 = W[13];
                    T35 = (T31 * T32) - (T33 * T34);
                    T54 = (T33 * T32) + (T31 * T34);
                }
                {
                    float T37;
                    float T39;
                    float T36;
                    float T38;
                    T37 = out[count * 3].r;
                    T39 = out[count * 3].j;
                    T36 = W[4];
                    T38 = W[5];
                    T40 = (T36 * T37) - (T38 * T39);
                    T55 = (T38 * T37) + (T36 * T39);
                }
                T41 = T35 + T40;
                T64 = T54 + T55;
                T53 = T35 - T40;
                T56 = T54 - T55;
            }
            {
                float T12;
                float T44;
                float T17;
                float T45;
                {
                    float T9;
                    float T11;
                    float T8;
                    float T10;
                    T9 = out[count * 2].r;
                    T11 = out[count * 2].j;
                    T8 = W[2];
                    T10 = W[3];
                    T12 = (T8 * T9) - (T10 * T11);
                    T44 = (T10 * T9) + (T8 * T11);
                }
                {
                    float T14;
                    float T16;
                    float T13;
                    float T15;
                    T14 = out[count * 6].r;
                    T16 = out[count * 6].j;
                    T13 = W[10];
                    T15 = W[11];
                    T17 = (T13 * T14) - (T15 * T16);
                    T45 = (T15 * T14) + (T13 * T16);
                }
                T18 = T12 + T17;
                T76 = T12 - T17;
                T46 = T44 - T45;
                T68 = T44 + T45;
            }
            {
                float T24;
                float T49;
                float T29;
                float T50;
                {
                    float T21;
                    float T23;
                    float T20;
                    float T22;
                    T21 = out[count * 1].r;
                    T23 = out[count * 1].j;
                    T20 = W[0];
                    T22 = W[1];
                    T24 = (T20 * T21) - (T22 * T23);
                    T49 = (T22 * T21) + (T20 * T23);
                }
                {
                    float T26;
                    float T28;
                    float T25;
                    float T27;
                    T26 = out[count * 5].r;
                    T28 = out[count * 5].j;
                    T25 = W[8];
                    T27 = W[9];
                    T29 = (T25 * T26) - (T27 * T28);
                    T50 = (T27 * T26) + (T25 * T28);
                }
                T30 = T24 + T29;
                T65 = T49 + T50;
                T48 = T24 - T29;
                T51 = T49 - T50;
            }
            {
                float T19;
                float T42;
                float T73;
                float T74;
                T19 = T7 + T18;
                T42 = T30 + T41;
                out[count * 4].r = T19 - T42;
                out[0].r = T19 + T42;
                {
                    float T67;
                    float T72;
                    float T63;
                    float T66;
                    T67 = T65 + T64;
                    T72 = T68 + T71;
                    out[0].j = T67 + T72;
                    out[count * 4].j = T72 - T67;
                    T63 = T7 - T18;
                    T66 = T64 - T65;
                    out[count * 6].r = T63 - T66;
                    out[count * 2].r = T63 + T66;
                }
                T73 = T30 - T41;
                T74 = T71 - T68;
                out[count * 2].j = T73 + T74;
                out[count * 6].j = T74 - T73;
                {
                    float T59;
                    float T78;
                    float T62;
                    float T75;
                    float T60;
                    float T61;
                    T59 = T43 + T46;
                    T78 = T76 + T77;
                    T60 = T56 - T53;
                    T61 = T48 + T51;
                    T62 = MEOW_1_DIV_SQR_2 * (T60 - T61);
                    T75 = MEOW_1_DIV_SQR_2 * (T61 + T60);
                    out[count * 7].r = T59 - T62;
                    out[count * 5].j = T78 - T75;
                    out[count * 3].r = T59 + T62;
                    out[count * 1].j = T75 + T78;
                }
                {
                    float T47;
                    float T80;
                    float T58;
                    float T79;
                    float T52;
                    float T57;
                    T47 = T43 - T46;
                    T80 = T77 - T76;
                    T52 = T48 - T51;
                    T57 = T53 + T56;
                    T58 = MEOW_1_DIV_SQR_2 * (T52 + T57);
                    T79 = MEOW_1_DIV_SQR_2 * (T52 - T57);
                    out[count * 5].r = T47 - T58;
                    out[count * 7].j = T80 - T79;
                    out[count * 1].r = T47 + T58;
                    out[count * 3].j = T79 + T80;
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------

// Paraphrased from kiss-fft
void meow_recursive_fft_mixed_meow_radix_dit
(
      const Meow_FFT_Workset* fft
    , unsigned                stage
    , Complex* in
    , Meow_FFT_Complex*       out
    , unsigned                w_mul
)
{
    const unsigned radix = fft->stages.radix[stage];
    const unsigned count = fft->stages.remainder[stage];

    Complex* w              = fft->wn;
    const unsigned w_offset = fft->stages.offsets[stage];
    Complex* w_sequential   = &fft->wn_ordered[w_offset];

    if (count == 1)
    {
        for (unsigned i = 0; i < radix; i++)
        {
            out[i] = in[i * w_mul];
        }
    }
    else
    {
        const unsigned new_w_multiplier = w_mul * radix;

        for (unsigned i = 0; i < radix; ++i)
        {
            meow_recursive_fft_mixed_meow_radix_dit
            (
                  fft
                , stage + 1
                , &in[w_mul * i]
                , &out[count * i]
                , new_w_multiplier
            );
        }
    }

    switch (radix)
    {
        case  2: meow_radix_2_dit(w_sequential, out, count); break;
        case  3: meow_radix_3_dit(w_sequential, out, count); break;
        case  4: meow_radix_4_dit(w_sequential, out, count); break;
        case  5: meow_radix_5_dit(w_sequential, out, count); break;
        case  8: meow_radix_8_dit(w_sequential, out, count); break;

        default: meow_dft_n_dit(w, out, count, w_mul, radix, fft->N, 0); break;
    }
}

void meow_recursive_fft_mixed_meow_radix_dit_i
(
      const Meow_FFT_Workset* fft
    , unsigned                stage
    , Complex* in
    , Meow_FFT_Complex*       out
    , unsigned                w_mul
)
{
    const unsigned radix = fft->stages.radix[stage];
    const unsigned count = fft->stages.remainder[stage];

    Complex* w              = fft->wn;
    const unsigned w_offset = fft->stages.offsets[stage];
    Complex* w_sequential   = &fft->wn_ordered[w_offset];

    if (count == 1)
    {
        for (unsigned i = 0; i < radix; i++)
        {
            out[i] = in[i * w_mul];
        }
    }
    else
    {
        const unsigned new_w_multiplier = w_mul * radix;

        for (unsigned i = 0; i < radix; ++i)
        {
            meow_recursive_fft_mixed_meow_radix_dit_i
            (
                  fft
                , stage + 1
                , &in[w_mul * i]
                , &out[count * i]
                , new_w_multiplier
            );
        }
    }

    switch (radix)
    {
        case  2: meow_radix_2_dit_i(w_sequential, out, count); break;
        case  3: meow_radix_3_dit_i(w_sequential, out, count); break;
        case  4: meow_radix_4_dit_i(w_sequential, out, count); break;
        case  5: meow_radix_5_dit_i(w_sequential, out, count); break;
        case  8: meow_radix_8_dit_i(w_sequential, out, count); break;

        default: meow_dft_n_dit(w, out, count, w_mul, radix, fft->N, 1); break;
    }
}

// -----------------------------------------------------------------------------
//
// http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM
// I finally figured out why this page confused me so much. It wasn't
// _consistent_ with formular chunks. Sometimes with would include j, othertimes
// it wouldn't. Sometimes it would include Wk, othertimes not. Ugh. No wonder
// my maths was wrong by the wrong twiddle or incorrect sign.
//
// So the magic forumlar is:
//
// Z()   == two-for-one-fft result waiting for final tiwddle
// F()   == result fft, what we want
// Wn()  == twiddle factor for N
// Wn2() == twiddle factor for N/2
//
// Note for fft  Wn() == e^(-j*2*pi*k/N)
// Note for ifft Wn() == e^( j*2*pi*k/N)  // <--- NOTICE MISSING '-'!

// For FFT
// k = 0

// F(0)   = Z(0).real + Z(0).imag
// F(N/2) = Z(0).real - Z(0).imag

// k > 0
// Feven_a(k) = Z(k) + Z(N/2 - k)*
// Fodd_a(k)  = Z(k) - Z(N/2 - k)*
//
// Feven = Feven_a(k)
// Fodd  = -j * Fodd_a(k)
//
// F(k) = 0.5 * (Feven + (Wn(k) * Fodd))

// -----------------------------------------------------------------------------

// For IFFT (think the twiddle is DIF hence not * 0.5)
// k = 0

// Z(0).real = F(0).real + F(N/2).real
// Z(0).imag = F(0).real - F(N/2).real

// k > 0
// Zeven_a(k) = F(k) + F(N/2 - k)*
// Zodd_a(k)  = F(k) - F(N/2 - k)*
//
// Feven = Feven_a(k)
// Fodd  =  j * Fodd_a(k)    // <---- NOTICE missing '-'!
//
// F(k) = Feven + (Wn(k) * Fodd) // <---- Remember ifft twiddles!, no * 0.5.

void inline meow_mixer
(
      unsigned                N_2
    , Complex* w_2n
    , Complex* in
    , Meow_FFT_Complex*       out
)
{
    // looking at kiss_fft they use double symmetery, so we only need to
    // actaully do N/4 twiddles. engineeringproductivitytools mentions something
    // similar as well.

    const unsigned N_4 = N_2 / 2u;

    for (unsigned k = 1; k <= N_4; k++)
    {
        Complex x_k           = in[k];
        Complex x_n_2_minus_k = meow_conjugate(in[N_2 - k]);
        Complex wk            = meow_conjugate(w_2n[k]);

        Complex za = meow_add(x_k, x_n_2_minus_k);
        Complex zb = meow_sub(x_k, x_n_2_minus_k);

        Complex x_even = za;

        Complex x_odd = meow_negate(meow_mul_by_j(zb));

        Complex wk_x_odd          = meow_mul(x_odd, wk);
        Complex x_k_sum           = meow_add(x_even, wk_x_odd);
        Complex x_n_2_minus_k_sum = meow_conjugate(meow_sub(x_even, wk_x_odd));

        Complex x_k_out           = meow_mulf(x_k_sum          , 0.5f);
        Complex x_n_2_minus_k_out = meow_mulf(x_n_2_minus_k_sum, 0.5f);

        out[k]       = x_k_out;
        out[N_2 - k] = x_n_2_minus_k_out;
    }
}

void inline meow_mixer_i
(
      unsigned          N_2
    , Complex*          w_2n
    , Complex*          in
    , Meow_FFT_Complex* out
)
{
    const unsigned N_4 = N_2 / 2u;

    for (unsigned k = 1; k <= N_4; k++)
    {
        Complex x_k           = in[k];
        Complex x_n_2_minus_k = meow_conjugate(in[N_2 - k]);
        Complex wk            = w_2n[k];

        Complex za = meow_add(x_k, x_n_2_minus_k);
        Complex zb = meow_sub(x_k, x_n_2_minus_k);

        Complex x_even = za;

        Complex x_odd = meow_mul_by_j(zb);

        Complex wk_x_odd          = meow_mul(x_odd, wk);
        Complex x_k_sum           = meow_add(x_even, wk_x_odd);
        Complex x_n_2_minus_k_sum = meow_conjugate(meow_sub(x_even, wk_x_odd));

        Complex x_k_out           = x_k_sum;
        Complex x_n_2_minus_k_out = x_n_2_minus_k_sum;

        out[k]       = x_k_out;
        out[N_2 - k] = x_n_2_minus_k_out;
    }
}

// -----------------------------------------------------------------------------

void meow_fft_real
(
      const Meow_FFT_Workset_Real* fft
    , const float*                 in
    , Meow_FFT_Complex*            out
)
{
    // Need two sets of twiddles. One set for N/2, and one set for N.
    // However for the N set, we only need N/4 twiddles due to symmetry * 2.

    const unsigned N_2   = fft->half.N;
    Complex*       magic = fft->w_2n;

    meow_recursive_fft_mixed_meow_radix_dit
    (
          &fft->half
        , 0
        , (Complex*)(in)
        , out
        , 1
    );

    Complex z0 = out[0];

    out[0].r = z0.r + z0.j;
    out[0].j = z0.r - z0.j;
    // combine 0, and N_2 into the same number in order
    // to keep the array size N/2

    meow_mixer(N_2, magic, out, out);
}

void meow_fft_real_i
(
      const Meow_FFT_Workset_Real* ifft
    , const Meow_FFT_Complex*      in
    , Meow_FFT_Complex*            temp
    , float*                       out
)
{
    const unsigned N_2   = ifft->half.N;
    Complex*       magic = ifft->w_2n;

    temp[0].r = in[0].r + in[0].j;
    temp[0].j = in[0].r - in[0].j;

    meow_mixer_i(N_2, magic, in, temp);

    meow_recursive_fft_mixed_meow_radix_dit_i
    (
          &ifft->half
        , 0
        , temp
        , (Meow_FFT_Complex*)(out)
        , 1
    );
}

void meow_fft
(
      const Meow_FFT_Workset* data
    , const Meow_FFT_Complex* in
    , Meow_FFT_Complex* out
)
{
    meow_recursive_fft_mixed_meow_radix_dit
    (
          data
        , 0
        , in
        , out
        , 1
    );
}

void meow_fft_i
(
      const Meow_FFT_Workset* data
    , const Meow_FFT_Complex* in
    , Meow_FFT_Complex* out
)
{
    meow_recursive_fft_mixed_meow_radix_dit_i
    (
          data
        , 0
        , in
        , out
        , 1
    );
}

#endif

// bash script used to generate radix N codelets from fftw that suit this code.
// since my tests run slower with > 8 radix, I hand modified the radix 8
// generated (function signature) instead of updating this code.
#if 0
#!/bin/sh
# <command> N [-1|1] [|_i]

cat << EOF

static void meow_radix_${1}_dit${3}
(
      meow_fft_complex* out
    , const float*  W
    , unsigned      count
)
{
EOF

#// First loop doesn't use twiddles
./gen_notw.native -n ${1} -standalone -sign ${2}                               \
    | sed  's/E /float /g'                                                     \
    | sed '/INT.*/d'                                                           \
    | sed -r 's/r[io]\[(.+)]/out\[\1\].r/g'                                    \
    | sed -r 's/i[io]\[(.+)]/out\[\1\].j/g'                                    \
    | sed '/for (.*).*/d'                                                      \
    | sed -r 's/WS\(.., (.*)\)/count * \1/g'                                   \
    | sed -r 's/FMA\((.+), (.+), (.+)\)/\(\1 * \2\) + \(\3\)/g'                \
    | sed -r 's/FMS\((.+), (.+), (.+)\)/\(\1 * \2\) - \(\3\)/g'                \
    | sed -r 's/FNMA\((.+), (.+), (.+)\)/-\(\1 * \2\) + \(\3\)/g'              \
    | sed -r 's/FNMS\((.+), (.+), (.+)\)/\(\3\) - \(\1 * \2\)/g'               \
    | sed -r 's/DK\((.+), (.+)\);/static const float \1  = \2;/g'              \
    | head -n -3                                                               \
    | tail -n +9

echo ""
echo "out = out + 1;"
echo ""

./gen_twiddle.native -n ${1} -standalone -sign ${2} -dit -with-ms 1            \
    | sed  's/E /float /g'                                                     \
    | sed 's/INT /unsigned /g'                                                 \
    | sed -r 's/r[io]\[(.+)]/out\[\1\].r/g'                                    \
    | sed -r 's/i[io]\[(.+)]/out\[\1\].j/g'                                    \
    | sed 's/, MAKE_VOLATILE_STRIDE(.*))/)/g'                                  \
    | sed 's/, MAKE_VOLATILE_STRIDE(.*)//g'                                    \
    | sed -r 's/WS\(.., (.*)\)/count * \1/g'                                   \
    | sed -r 's/FMA\((.+), (.+), (.+)\)/\(\1 * \2\) + \(\3\)/g'                \
    | sed -r 's/FMS\((.+), (.+), (.+)\)/\(\1 * \2\) - \(\3\)/g'                \
    | sed -r 's/FNMA\((.+), (.+), (.+)\)/-\(\1 * \2\) + \(\3\)/g'              \
    | sed -r 's/FNMS\((.+), (.+), (.+)\)/\(\3\) - \(\1 * \2\)/g'               \
    | sed '/DK(.*);/d'                                                         \
    | sed 's/ri = ri + 1, ii = ii + 1,/out = out + 1,/g'                       \
    | sed 's/m = mb, W = W + (mb * .*);/m = 1;/g'                              \
    | sed -r 's/(for \(.*\)).*/\1\n{/g'                                        \
    | sed 's/me/count/g'                                                       \
    | head -n -2                                                               \
    | tail -n +10


echo "}"
#endif
