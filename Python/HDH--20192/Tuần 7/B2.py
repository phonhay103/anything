from threading import Thread, Semaphore

a = 1
c1 = None
c2 = None
turn = 1
def func1():
    global a, c1, c2, turn
    while True:
        c1 = True
        while (c2 == True):
            if (turn == 2):
                c1 = False
                while(turn==2):
                    pass
                c1 = True
        
        a = a * 2

        turn = 2
        c1 = False
        print("func1:", a)

def func2():
    global a, c1, c2, turn
    while True:
        c2 = True
        while (c1 == True):
            if (turn == 1):
                C2 = False
                while(turn==1):
                    pass
                c1 = True

        a = a ** 2

        turn = 1
        c2 = False
        print("func2:", a)

Thread(target=func1).start()
Thread(target=func2).start()