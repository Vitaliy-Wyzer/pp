import matplotlib.pyplot as plt


def aproksymacja_f1zmKwadrat(x, y):
    n = len(x)
    sum_x = sum(x)
    sum_x2 = sum(x**2)
    sum_x3 = sum(x**3)
    sum_x4 = sum(x**4)
    sum_y = sum(y)
    sum_xy = sum(x*y)
    sum_x2y = sum((x**2)*y)

    p2 = (n*sum_x2y - sum_x2*sum_y) / (n*sum_x4 - sum_x2**2)
    p1 = (sum_y - p2*sum_x2) / n
    p0 = (sum_xy - p1*sum_x - p2*sum_x3) / n

    return p0, p1, p2

# Dane punktów
x = [1.88, 2.29, 1.45, 4.03, 9.11, 6.97, 8.85, 2.6, 5.13]
y = [3.86, 6.7, 3.29, 5.34, 9.01, 2.08, 5.41, 1.79, 0.31]

# Obliczenie współczynników funkcji kwadratowej
p0, p1, p2 = aproksymacja_f1zmKwadrat(x, y)
print("p0 =", p0)
print("p1 =", p1)
print("p2 =", p2)

# Wygenerowanie punktów do wykresu funkcji kwadratowej
x_aprox = [min(x) + i*(max(x)-min(x))/100 for i in range(100)]
y_aprox = [p0 + p1*x + p2*x**2 for x in x_aprox]

# Wykres danych
plt.scatter(x, y, label='Dane punkty')

# Wykres funkcji aproksymującej
plt.plot(x_aprox, y_aprox, color='red', label='Aproksymacja')

plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.show()
