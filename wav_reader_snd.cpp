#include <complex>
#include <cstdio>
#include <iostream>

#include "fft.hpp"
#include "pffft/pffft.hpp"
#include <fstream>
#include <iomanip>
#include <sndfile.hh>


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
    const char *fname = "/home/dkicinski/code/fft/out.wav";
    std::ofstream out{"/home/dkicinski/code/fft/output_file.txt"};

    Span read_buffer = read_file(fname);
    std::cout << read_buffer.length << std::endl;

    int fft_window = 512;
    int step_size = 256;

    auto spectrogram = stft(read_buffer, fft_window, step_size);
    int count = 0;
    for (int i = 0; i < spectrogram.dims[0]; ++i) {
        for (int j = 0; j < spectrogram.dims[1]; ++j) {
            out << std::fixed << std::setprecision(8) << *(spectrogram.buffer + i * spectrogram.dims[1] + j) << " ";
        }
        out << std::endl;
        ++count;
    }
    std::cout << count << std::endl;

    return 0;
}
