#!/usr/bin/env python3

from pathlib import Path

import librosa.display
import matplotlib.pyplot as plt
import numpy as np


def read_data(saved_file: Path):
    spectrogram = []
    with saved_file.open("r") as f:
        for line in f:
            spectrogram.append([float(v) for v in line.strip().split(" ")])
    return np.array(spectrogram)


def show_spectrogram(arr: np.array, fft_num=512, sampling_rate=16_000):
    # plt.imshow(np.log(arr + 1e-7))
    # plt.specgram(arr, NFFT=fft_num, Fs=sampling_rate)
    librosa.display.specshow(arr)
    plt.show()


if __name__ == '__main__':
    data = read_data(Path("output_file.txt"))
    # data = np.log(data + 1e-7).T
    data = data.T
    print(f"spectrogram.shape = {data.shape}")
    show_spectrogram(data)
