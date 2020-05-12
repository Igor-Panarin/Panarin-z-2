import os


def task(file_name, X):
    k = 0
    if not os.path.exists(file_name):
        print("There is no file")
        return False, False
    with open(file_name, "r") as f:
        for line in f:
            for el in line.split():
                try:
                    k += 1
                    num = float(el)
                    if num == float(X):
                        return True, True
                except ValueError:
                    print("ValueError")
                    return False, False
    if k == 0:
        print("File is empty")
        return False, False

    return True, False


filename = input("Print filename: ")
x = input("Print X: ")
try:
    x = float(x)
except ValueError:
    print("Wrong X")
    quit()

res = task(filename, x)
if res[0]:
    if res[1]:
        print("X is in list")
    else:
        print("X is not in list")
