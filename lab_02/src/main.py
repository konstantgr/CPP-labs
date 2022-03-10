def f(x):
    return x**2 - x**2 + 4 * x - 5 * x + x + x


if __name__ == "__main__":
    n = input()

    try:
        n = int(n)
    except (TypeError, ValueError) as e:
        print("Error in input's type")
        exit(30)

    x = 1
    for _ in range(n):
        x += f(x)

    print(x)
