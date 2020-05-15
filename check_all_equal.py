import os


def task(file_name):
    k = 0
    first = 0
    second = 0
    sec = False
    if not os.path.exists(file_name):
        print("There is no file")
        return False, False
    with open(file_name, "r") as f:
        for line in f:
            for el in line.split():
                try:
                    num = float(el)
                    if k == 0:
                        first = num
                    else:
                        if num != first:
                            if not sec:
                                second = num
                                sec = True
                            else:
                                if num != second:
                                    return True, False
                    k += 1

                except ValueError:
                    print("ValueError")
                    return False, False
    if k == 0:
        print("File is empty")
        return False, False

    return True, True


filename = input("Print filename: ")

res = task(filename)
if res[0]:
    if res[1]:
        print("All are equal or two are not equal")
    else:
        print("All are not equal")

