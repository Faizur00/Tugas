import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq

# =============================
# Parameter dasar
# =============================
f0 = 23e6      # frekuensi sinyal = 23 MHz
fs = 50e6     # frekuensi sampling = 50 MHz
T = 1e-5      # durasi sinyal (detik)

# =============================
# Waktu & sinyal
# =============================
t = np.linspace(0, T, int(fs*T), endpoint=False)   # vektor waktu
x = np.sin(2 * np.pi * f0 * t)                     # sinyal sinus 6 MHz

# =============================
# FFT untuk melihat spektrum
# =============================
N = len(x)
X = fft(x)
freqs = fftfreq(N, 1/fs)

# Ambil bagian frekuensi positif saja
X_mag = 2.0/N * np.abs(X[:N//2])
freqs_pos = freqs[:N//2]

# =============================
# Plot hasil
# =============================
plt.figure(figsize=(8,4))
plt.plot(freqs_pos/1e6, X_mag)
plt.title("Spektrum Sinyal 23 MHz")
plt.xlabel("Frekuensi (MHz)")
plt.ylabel("Magnitudo")
plt.grid(True)
plt.show()