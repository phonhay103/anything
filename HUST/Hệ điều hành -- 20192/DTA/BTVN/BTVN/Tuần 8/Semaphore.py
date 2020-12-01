import threading

S1 = threading.Semaphore(1000)
S2 = threading.Semaphore()
a=0
b=0

def T1():
    global a, b
    while True:
        S1.acquire()
        a+=1
        S2.release()

        if not (b <= a and a <= b+1000):
            print("a={} b={}".format(a, b))

def T2():
    global a,b
    while True:
        S2.acquire()
        b+=1
        S1.release()

if __name__ == "__main__":
    h1 = threading.Thread(target=T1)
    h2 = threading.Thread(target=T2)
    h1.start()
    h2.start()
    h1.join()
    h2.join()