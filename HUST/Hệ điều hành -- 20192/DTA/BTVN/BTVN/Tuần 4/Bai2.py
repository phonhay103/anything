import threading
from queue import Queue
import time

def producer(q):
    data = 0
    global q_size
    while True:
        if q.qsize() == q_size:
            continue
        q.put(data)
        data += 1

def consumer(q):
    while True:
        if q.empty():
            continue
        time.sleep(0.1)
        data = q.get()
        print(data)
        
    

q = Queue()
q_size = 100

threading.Thread(target=producer, args=(q,)).start()
threading.Thread(target=consumer, args=(q,)).start()