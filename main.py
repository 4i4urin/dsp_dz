from numpy import pi, sin, exp, abs, cos, savetxt, round, max, arange


fs = 8000
N = 1000
ts = arange(N) / fs

x = sin(2*pi*1000*ts) + 0.5 * sin(2*pi*2000*ts)
x = round(x/max(abs(x)) * (2**7-2))
savetxt('input.txt',x,'%d')
m = round(1000 / fs * N + 1)

# Алгоритм герцеля
u0 = 0
u1 = 0
u2 = 0
w = 2*pi * (m - 1) / N
for i in range(N):
    u0 = 2 * cos(w)*u1 - u2 + x[i]
    u2 = u1
    u1 = u0

y = u0 - exp(-1j*w) * u2
res = 2 * abs(y) / N
print(f"Result: {res}\nY: {y}")

