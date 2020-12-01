from threading import Thread, Semaphore
import time

m = 0
n = 5
def func():
    n = 0
    global m

    while True:
        n += 1
        m += 1
        print ('m= {}, n= {}'.format(m, n))
        # time.sleep(0.2)

for i in range(n):
    Thread(target=func).start()