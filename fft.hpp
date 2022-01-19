#pragma once

#include <algorithm>
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


class Matrix {
public:
    Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {
        _data = new float[rows*cols];
    }
    ~Matrix() {
        std::cout << "Deleting Matrix{" << _rows << ", " << _cols << "}" << std::endl;
        delete[] _data;
    }

    auto rows() const -> size_t { return _rows; }
    auto cols() const -> size_t { return _cols; }
    auto data() -> float * { return _data; }

private:
    size_t _rows;
    size_t _cols;
    float *_data;
};


auto stft(Span audio_buffer, int fft_window, int step_size) -> Matrix *
{
    pffft::Fft<float> fft{fft_window};
    auto X = fft.valueVector();
    auto Y = fft.spectrumVector();
    int D = static_cast<int>(fft_window / 2);
    int num_frames = 1 + std::floor((audio_buffer.length - fft_window) / step_size);
    auto spectrogram = new Matrix(num_frames, D);
    std::cout << "num_frames = " << num_frames << "    " << "D = " << D  << std::endl;

    int frame_counter = 0;
    for (int i = 0; i < audio_buffer.length - fft_window; i += step_size) {
        std::cout << i << "    ";
        std::copy(audio_buffer.buffer + i, audio_buffer.buffer + i + fft_window, X.begin());
        fft.forward(X, Y);
        auto offset = frame_counter * D;
        std::cout << "frame: " << frame_counter << "    " << offset << "/" << audio_buffer.length
                  << "    " << "Y.size() = " << std::distance(Y.begin(), Y.end()) << std::endl;

        std::transform(Y.begin(), Y.end(), spectrogram->data() + offset,
                       [](std::complex<float> v){ return std::abs(v); });
        frame_counter ++;
    }
    return spectrogram;
}
