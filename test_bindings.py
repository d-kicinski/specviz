import librosa
import librosa.display
import matplotlib
import numpy as np

matplotlib.use('TkAgg')

import pyfft
from matplotlib import pyplot as plt

WAV_SAMPLE = "samples/sin_composition.wav"
SR = 16_000


def test_bindings():
    wav, _ = librosa.load(WAV_SAMPLE, sr=SR)
    wav = wav.flatten()
    result = pyfft.stft(wav,  256, 128)
    spectrogram = np.array(result)
    print(f"python: {spectrogram.shape}")
    librosa.display.specshow(spectrogram.T)
    plt.show()


if __name__ == '__main__':
    test_bindings()
