n = 100
count = 0
# 14! = 87178291200 => 2
# Chia hết cho mười: chứa cặp 2 * 5
# Số chữ số 2 > Số chữ số 5 
# => Tìm số chữ số 5
# count_0 = n / 5 + n / 5**2 + ... n / 5**k

while (n >= 5):
    n //= 5
    count += n

print(n)