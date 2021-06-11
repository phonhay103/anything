from tkinter import *
import time

num_binary = {0:'1111110', 1:'0110000', 2:'1101101', 3:'1111001', 4:'0110011',
       5:'1011011', 6:'1011111', 7:'1110000', 8:'1111111', 9:'1111011'}
traffic_color = [('Red', 15), ('Orange', 2), ('Green', 10)] # Thời gian chạy của từng đèn
leds = ['a1', 'b1', 'c1', 'd1', 'e1', 'f1', 'g1', 'a2', 'b2', 'c2', 'd2', 'e2', 'f2', 'g2']

def get_next_light():
    color, counters = traffic_color.pop(0)
    traffic_color.append((color,counters))
    return color, counters

def split_number(num):
    return (0, num) if num < 10 else (num // 10, num % 10)

def show_light(color):
    canvas.itemconfig("Red", fill="black")
    canvas.itemconfig("Orange", fill="black")
    canvas.itemconfig("Green", fill="black")
    canvas.itemconfig(color, fill=color)

def show_number(first, second, color):
    # Get number
    first = num_binary[first]
    second = num_binary[second]

    # Clear number
    for led in leds:
        canvas.delete(led)
    canvas.create_rectangle(220, 270, 370, 290, outline='white', tags=('a1'))
    canvas.create_rectangle(350, 270, 370, 420, outline='white', tags=('b1'))
    canvas.create_rectangle(350, 420, 370, 550, outline='white', tags=('c1'))
    canvas.create_rectangle(220, 530, 370, 550, outline='white', tags=('d1'))
    canvas.create_rectangle(220, 420, 240, 550, outline='white', tags=('e1'))
    canvas.create_rectangle(220, 270, 240, 420, outline='white', tags=('f1'))
    canvas.create_rectangle(220, 400, 370, 420, outline='white', tags=('g1'))
    canvas.create_rectangle(450, 270, 600, 290, outline='white', tags=('a2'))
    canvas.create_rectangle(580, 270, 600, 420, outline='white', tags=('b2'))
    canvas.create_rectangle(580, 420, 600, 550, outline='white', tags=('c2'))
    canvas.create_rectangle(450, 530, 600, 550, outline='white', tags=('d2'))
    canvas.create_rectangle(450, 420, 470, 550, outline='white', tags=('e2'))
    canvas.create_rectangle(450, 270, 470, 420, outline='white', tags=('f2'))
    canvas.create_rectangle(450, 400, 600, 420, outline='white', tags=('g2'))

    # Show number
    for turn, led in zip(first+second, leds):
        if turn == '1':
            canvas.itemconfigure(led, fill=color)

def main():
    color, counters = get_next_light()
    show_light(color)
    for num in range(counters, -1, -1):
        first, second = split_number(num)
        show_number(first, second, color)
        window.update()
        time.sleep(1)
    window.after(0, main)

window = Tk()
canvas = Canvas()
canvas.pack(fill=BOTH, expand=1)
window.title("Welcome to Traffic Lights Simulator App")
window.geometry("800x600+600+200")
window.resizable(False, False)

canvas.create_rectangle(200, 80, 630, 220, fill='black')
canvas.create_oval(203, 83, 340, 217, fill='Red', outline='white', tags=('Red'))
canvas.create_oval(345, 83, 485, 217, fill='Orange', outline='white', tags=('Orange'))
canvas.create_oval(490, 83, 627, 217, fill='Green', outline='white', tags=('Green'))

window.after(1000, main)
window.mainloop()