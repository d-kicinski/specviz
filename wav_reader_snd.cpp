#include <complex>
#include <cstdio>
#include <iostream>

#include "pffft/pffft.hpp"
#include <fstream>
#include <iomanip>
#include <sndfile.hh>


typedef struct span {
    float *buffer;
    long length;
} Span;

auto read_file(const char *fname) -> Span
{
    SndfileHandle file;

    file = SndfileHandle(fname);
    printf("Opened file '%s'\n", fname);
    printf("    Sample rate : %d\n", file.samplerate());
    printf("    Channels    : %d\n", file.channels());
    printf("    Frames    : %ld\n", file.frames());

    auto buffer = new float[file.frames()];

    long frames_read = file.read(buffer, file.frames());
    auto span = Span{.buffer = buffer, .length = frames_read};
    return span;
}


int main()
{
    const char *fname = "/home/dkicinski/code/fft/follow.wav";

    Span read_buffer = read_file(fname);
    std::cout << read_buffer.length << std::endl;

    int fft_window = 1024;
    int step_size = 128;

    pffft::Fft<float> fft{fft_window};
    auto X = fft.valueVector();
    auto Y = fft.spectrumVector();

    std::ofstream out{"output_file.txt"};

    int count = 0;
    for (int i = 0; i < read_buffer.length - fft_window; i += step_size) {
        std::copy(read_buffer.buffer + i, read_buffer.buffer + i + fft_window, X.begin());
        fft.forward(X, Y);
        for (const auto &item : Y) {
            out << std::fixed << std::setprecision(8) << std::abs(item) << " ";
        }
        out << std::endl;
        ++count;
    }
    std::cout << count << std::endl;

    return 0;
}
