//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_MULTICHANNEL_TO_MONO_CONVERTER_H
#define EDSP_MULTICHANNEL_TO_MONO_CONVERTER_H

#include "config.h"
#include "utility/vector.h"
#include <iterator>

EDSP_BEGIN_NAMESPACE
    namespace algorithm {
        class MultiChannelToMonoConverter {
        public:
            explicit MultiChannelToMonoConverter(size_t num_channels) : num_channels(num_channels) {}

            template <class InputIterator, class Outputiterator>
            void compute(InputIterator first, InputIterator last, Outputiterator out) {
                for (; first != last; first += num_channels, ++out) {
                    *out = utility::sum(first, first + num_channels) / num_channels;
                }
            }

        private:
            double num_channels;
        };




    }
EDSP_END_NAMESPACE

#endif //EDSP_MULTICHANNEL_TO_MONO_CONVERTER_H
