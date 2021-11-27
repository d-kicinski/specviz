from pathlib import Path
import librosa
import numpy as np
from numpy.typing import ArrayLike
import matplotlib.pyplot as plt

DEFAULT_WAV_PATH = Path("out.wav")


def generate_test_wav(output_path: Path = DEFAULT_WAV_PATH) -> ArrayLike:
    x = np.linspace(0, 2 * np.pi)
    y = np.sin(x)
    plt.plot(x, y)
    plt.show()


if __name__ == '__main__':
    import fire

    fire.Fire(generate_test_wav)
