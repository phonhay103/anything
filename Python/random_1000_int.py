# Cho list data = [1, 2, 3, 4, 5, 6, 7, 8, 9].
# Chọn ngẫu nhiên 1000 phần tử từ list data, và phần tử có điểm số lớn hơn nên được chọn nhiều hơn.

import random

data = [i for i in range(1,10)]
count = 1000
l = [0]*9

while count > 0:
    x = random.randint(1,9)
    i = data.index(x)
    kt = True
    for j in range(i+1, 9):
        if l[i] >= l[j]-1:
            kt = False
            break
    if kt:
        l[i] += 1
        count -= 1

print("1 - %s\n2 - %s\n3 - %s\n4 - %s\n5 - %s\n6 - %s\n7 - %s\n8 - %s\n9 - %s"
    %(l[0], l[1], l[2], l[3], l[4], l[5], l[6], l[7], l[8]))