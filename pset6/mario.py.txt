from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0 and n < 9:
            break
for i in range(n):
    print("", end="")

    for s in range(n-1-i):
        print(" ", end="")

    for h in range(i+1):
        print("#", end="")


    print()

