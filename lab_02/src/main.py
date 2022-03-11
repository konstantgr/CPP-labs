import time


def f(x):
    return x**2 - x**2 + 4 * x - 5 * x + x + x


if __name__ == "__main__":
    while True:
        n = input()

        try:
            n = int(n)
        except (TypeError, ValueError) as e:
            print("Error in input's type")
            exit(30)

        x = 1
        start_time = time.time()

        for _ in range(n):
            x += f(x)

        print(x)
        print("--- %s seconds ---" % (time.time() - start_time))
