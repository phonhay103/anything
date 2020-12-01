# Sinh hoán vị kế tiếp
# Hoán vị cuối cùng: (6, 5, 4, 3, 2, 1)
def next(A):
    A_next = list(A)

    # j là số lớn nhất thỏa mãn A[j] < A[j+1] (Tìm từ phải qua trái và lấy chỉ số j đầu tiên thỏa mãn A[j] < A[j+1])
    for i in range(len(A)-2, -1, -1):
        if A[i] < A[i+1]:
            j = i
            break
    else:
        exit(0) # LAST

    # Tìm A[k] là số nhỏ nhất còn lớn hơn A[j] trong các số ở bên phải A[j] (Tìm từ phải đến A[j+1] và lấy chỉ số k đầu tiên A[k] lớn hơn A[j])
    k = j+1
    for i in range(len(A)-1, j, -1):
        if A[i] > A[j]:
            k = i
            break

    # Đổi chỗ A[j] với A[k]
    A_next[j], A_next[k] = A_next[k], A_next[j]

    # Lật ngược đoạn từ A[j+1] đến A[n]
    A_next[j+1:len(A_next)] = A_next[len(A_next):j:-1]

    A_next = tuple(A_next)
    return A_next

A = (1, 2, 3, 4, 5)
print("A =", A)

def pre(A):
    c = 0
    T = (1, 2, 3, 4, 5)
    while True:
        if next(T) == A:
            break
        c+=1
        T = next(T)
    if c != 0:
        return T

print(pre(A))