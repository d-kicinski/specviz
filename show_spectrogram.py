from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np


def read_data(saved_file: Path):
    spectrogram = []
    with saved_file.open("r") as f:
        for line in f:
            spectrogram.append([float(v) for v in line.strip().split(" ")])
    return np.array(spectrogram)


def show_spectrogram(arr: np.array, fft_num=1024, sampling_rate=16_000):
    plt.imshow(arr)
    # plt.specgram(arr, NFFT=fft_num, Fs=sampling_rate)
    plt.show()


if __name__ == '__main__':
    data = read_data(Path("output_file.txt"))
    show_spectrogram(data)
