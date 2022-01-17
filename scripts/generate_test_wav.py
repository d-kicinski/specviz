from pathlib import Path
import librosa
import numpy as np
import soundfile
from numpy.typing import ArrayLike
import matplotlib.pyplot as plt

DEFAULT_WAV_PATH = Path("out.wav")


def generate_test_wav(output_path: Path = DEFAULT_WAV_PATH) -> ArrayLike:
    t = np.linspace(start=0, stop=1, num=8000)  # sampling with 16kH frequency

    # signal = sin(f * 2PIt), where f is signal frequency
    f = 7_500
    y = np.sin(f * 2 * np.pi * t)

    for i in range(1, 25):
        y += np.sin(1/i * f * 2 * np.pi * t)

    soundfile.write(str(output_path), y, samplerate=16_000)


if __name__ == '__main__':
    import fire

    fire.Fire(generate_test_wav)
