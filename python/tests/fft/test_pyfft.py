import os.path

import librosa
import librosa.display
import matplotlib
import numpy as np

matplotlib.use('TkAgg')

from fft import pyfft
from matplotlib import pyplot as plt


WAV_SAMPLE = "sin_composition.wav"
SR = 16_000


def test_bindings(resources_directory):
    input_path = os.path.join(resources_directory, WAV_SAMPLE)
    wav, _ = librosa.load(input_path, sr=SR)
    wav = wav.flatten()
    result = pyfft.stft(wav,  256, 128)
    spectrogram = np.array(result)
    print(f"python: {spectrogram.shape}")
    librosa.display.specshow(spectrogram.T)
    plt.show()


if __name__ == '__main__':
    test_bindings()
