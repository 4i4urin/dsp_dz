from numpy import pi, sin, exp, abs, cos, savetxt, round, max, arange


fs = 24000
N = 1000
ts = arange(N) / fs

x = sin(2*pi*1000*ts) + 0.5 * sin(2*pi*2000*ts) + 0.3 * sin(2*pi*300*ts) + \
sin(2*pi*2500*ts)
x = round(x/max(abs(x)) * (2**7-2))
savetxt('input.txt',x,'%d')

for find in [3600, 8400, 15600, 20400]:
    print(f"\nFind freq: {find}")
    m = round(find / fs * N + 1)
    # Алгоритм герцеля
    u0 = 0
    u1 = 0
    u2 = 0
    w = 2*pi * (m - 1) / N
    print(f"cos = {round(cos(w) * (2**12-1))} sin = {round(sin(w) * (2**12-1))}")
    for i in range(N):
        u0 = 2 * cos(w)*u1 - u2 + x[i]
        u2 = u1
        u1 = u0
        # print(round(u0), round(u1), round(u2))

    y = u0 - exp(-1j*w) * u2
    res = 2 * abs(y) / N
    print(f"Result: {res}\nY: {y}")

