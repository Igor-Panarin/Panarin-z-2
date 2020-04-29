import os


def read_file (file_name):
    arr = []
    sum = 0
    k = 0
    if not os.path.exists(file_name):
        return False
    with open(file_name, "r") as f:
        for line in f:
            line_arr = line.split()
            for el in line_arr:
                try:
                    k += 1
                    num = float(el)
                    sum += num
                    arr.append(num)
                except ValueError:
                    return False
    if k == 0:
        return False

    return True, arr, (sum/k)


def find_max_dist(numbers, average):
    max = 0
    for el in numbers:
        d = abs(average-el)
        if d > max:
            max = d
    return max


arr = read_file("a.txt")
if arr[0]:
    numbers = arr[1]
    average = arr[2]
    print("Answer = ", find_max_dist(numbers, average))
else:
    print("Wrong input data")
