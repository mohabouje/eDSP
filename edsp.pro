QT       -= core gui
CONFIG += c++14
TARGET = edsp
TEMPLATE = lib
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
    src/version.h \
    src/config.h

INCLUDEPATH += $$PWD/src/
DEPENDPATH += $$PWD/src/

unix {
    target.path = /usr/lib
    INSTALLS += target
}


macx {
    LIBS += -L$$PWD/../../../usr/local/Cellar/fftw/3.3.6-pl2/lib/ -lfftw3.3
    INCLUDEPATH += $$PWD/../../../usr/local/Cellar/fftw/3.3.6-pl2/include
    DEPENDPATH += $$PWD/../../../usr/local/Cellar/fftw/3.3.6-pl2/include
}

