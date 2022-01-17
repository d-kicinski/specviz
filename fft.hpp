#pragma once

#include <complex>
#include <cstdio>
#include <iostream>

#include <fstream>
#include <iomanip>

#include "pffft/pffft.hpp"


typedef struct span {
    float *buffer;
    long length;
} Span;

typedef struct matrix {
    float *buffer;
    int dims[2];
} Matrix;


auto stft(Span audio_buffer, int fft_window, int step_size) -> Matrix
{
    pffft::Fft<float> fft{fft_window};
    auto X = fft.valueVector();
    auto Y = fft.spectrumVector();
    int D = 1 + static_cast<int>(fft_window / 2);
    int num_frames = std::floor((audio_buffer.length - fft_window) / step_size);
    Matrix spectrogram{.buffer = new float[num_frames * D], .dims = {num_frames, D}};

    int frame_counter = 0;
    for (int i = 0; i < audio_buffer.length - fft_window; i += step_size) {
        std::copy(audio_buffer.buffer + i, audio_buffer.buffer + i + fft_window, X.begin());
        fft.forward(X, Y);
        std::transform(Y.begin(), Y.end(), spectrogram.buffer + frame_counter * D,
                       [](std::complex<float> v){ return std::abs(v); });
        frame_counter ++;
    }
    return spectrogram;
}
