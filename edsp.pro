QT       -= core gui
CONFIG += c++14
TARGET = eDSP
TEMPLATE = lib

DEFINES += EDSP_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    src/base/constants.h \
    src/filters/biquad.h \
    src/filters/biquaddesigner.h \
    src/frequency/autocorrelation.h \
    src/frequency/cepstrum.h \
    src/frequency/linearpredictivecoding.h \
    src/frequency/spectrogram.h \
    src/generators/brownnoisegenerator.h \
    src/generators/generator.h \
    src/generators/impulsegenerator.h \
    src/generators/singenerator.h \
    src/generators/squaregenerator.h \
    src/generators/whitenoisegenerator.h \
    src/math/complex.h \
    src/math/math.h \
    src/math/stats.h \
    src/math/trig.h \
    src/properties/properties.h \
    src/transforms/dct.h \
    src/transforms/dht.h \
    src/transforms/fft.h \
    src/transforms/idct.h \
    src/transforms/ifft.h \
    src/utility/map_util.h \
    src/utility/template_util.h \
    src/utility/vector_util.h \
    src/window/window.h \
    src/config.h \
    src/version.h

INCLUDEPATH += $$PWD/src/
DEPENDPATH += $$PWD/src/

# Using FFTW library
INCLUDEPATH += /usr/local/include/
LIBS += -lfftw3
