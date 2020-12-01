from threading import Thread
import time

def T1():
    global x, y
    while 1:
        x = y + 1
        print(x)
        time.sleep(0.1)

def T2():
    global y
    while 1:
        y = 2
        y = y * 2
    
x = 0
y = 1

t1 = Thread(target=T1)
t2 = Thread(target=T2)
t1.start()
t2.start()
t1.join()
t2.join()