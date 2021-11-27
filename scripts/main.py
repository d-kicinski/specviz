import matplotlib.pyplot as plt
import numpy as np
import scipy.fft


def plot_signals(s1, s2, signal, t):
    plt.ylabel("Amplitude")
    plt.xlabel("Time [s]")

    ax: plt.Axes = plt.subplot(3, 1, 1)
    ax.plot(t, s1)
    ax.set_title(r"$s_1 = \sin(33Hz * 2\pi t)$")

    ax: plt.Axes = plt.subplot(3, 1, 2)
    ax.plot(t, s2)
    ax.set_title(r"$s_2 = \sin(70Hz * 2\pi t)$")

    ax: plt.Axes = plt.subplot(3, 1, 3)
    ax.plot(t, signal)
    ax.set_title(r"$s = s_1 + s_2$")

    figure: plt.Figure = ax.get_figure()
    # figure.set_size_inches((10, 10))
    figure.tight_layout(h_pad=2)
    figure.show()


def plot_spectrum(amplitudes: np.array, t: np.array, N: int):
    K = len(amplitudes)
    T = t[1] - t[0]  # sampling interval
    # The frequency resolution is determined by: df = sampling frequency / number of samples
    f = np.linspace(0, 1 / T, N)  # (0, 1000), 500 samples

    # we don't care about negative frequencies
    amplitudes = amplitudes[:K // 2]
    f = f[:K // 2]

    figure, ax = plt.subplots()
    ax.bar(f, amplitudes, width=1.5)
    ax.set_ylabel("Amplitude")
    ax.set_xlabel("Frequency [Hz]")
    figure.show()


def main():
    t = np.linspace(start=0, stop=1, num=8000)  # sampling with 16kH frequency

    # signal = sin(f * 2PIt), where f is signal frequency
    s1_f = 1000
    s1 = np.sin(s1_f * 2 * np.pi * t)
    s2_f = 3000
    s2 = 0.5 * np.sin(s2_f * 2 * np.pi * t)

    signal = s1 + s2
    plot_signals(s1, s2, signal, t)

    N = len(signal)
    K = 200

    y = scipy.fft.fft(signal)
    amplitudes = np.abs(y) * 1 / N

    plot_spectrum(amplitudes, t, N)


if __name__ == '__main__':
    main()
