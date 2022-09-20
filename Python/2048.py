from tkinter import *
from tkinter import messagebox
import random

class Board:
    bg_color={
        '2':    '#eee4da',
        '4':    '#ede0c8',
        '8':    '#edc850',
        '16':   '#edc53f',
        '32':   '#f67c5f',
        '64':   '#f65e3b',
        '128':  '#edcf72',
        '256':  '#edcc61',
        '512':  '#f2b179',
        '1024': '#f59563',
        '2048': '#edc22e',
        '4096': '#00FF00'
    }
    color={
        '2':    '#776e65',
        '4':    '#f9f6f2',
        '8':    '#f9f6f2',
        '16':   '#f9f6f2',
        '32':   '#f9f6f2',
        '64':   '#f9f6f2',
        '128':  '#f9f6f2',
        '256':  '#f9f6f2',
        '512':  '#776e65',
        '1024': '#f9f6f2',
        '2048': '#f9f6f2',
        '4096': '#f9f6f2'
    }

    def __init__(self, size=4, num=2048):
        self.size = size
        self.num = num
        self.window = Tk()
        self.window.title('2048 Game')
        self.gameArea = Frame(self.window, bg='azure3')
        self.board = []
        self.gridCell = [[0]*size for _ in range(size)]
        self.compressed = False
        self.merged = False
        self.moved = False

        for i in range(size):
            row = []
            for j in range(size):
                cell = Label(self.gameArea, text='', bg='azure4', font=('arial', 22, 'bold'), width=4, height=2)
                cell.grid(row=i, column=j, padx=7, pady=7)
                row.append(cell);
            self.board.append(row)
        self.gameArea.grid()

    def reverse(self):
        self.gridCell = [row[::-1] for row in self.gridCell]

    def transpose(self):
        self.gridCell = [list(t) for t in zip(*self.gridCell)]

    def compressGrid(self):
        compressed = False
        temp = [[0]*self.size for _ in range(self.size)]
        for i in range(self.size):
            cnt = 0
            for j in range(self.size):
                if self.gridCell[i][j] != 0:
                    temp[i][cnt] = self.gridCell[i][j]
                    if cnt != j:
                        compressed = True
                    cnt += 1
        self.gridCell = temp
        self.compressed = compressed

    def mergeGrid(self):
        merged = False
        for i in range(self.size):
            for j in range(self.size-1):
                if self.gridCell[i][j] == self.gridCell[i][j + 1] and self.gridCell[i][j] != 0:
                    self.gridCell[i][j] *= 2
                    self.gridCell[i][j+1] = 0
                    merged = True
        self.merged = merged

    def random_cell(self):
        cells = []
        for i in range(self.size):
            for j in range(self.size):
                if self.gridCell[i][j] == 0:
                    cells.append((i, j))
        curr = random.choice(cells)
        i = curr[0]
        j = curr[1]
        self.gridCell[i][j] = 2
    
    def lose(self):
        # Check can move
        for i in range(self.size):
            for j in range(self.size):
                if self.gridCell[i][j] == 0:
                    return False
        # Check can merge
        for i in range(self.size):
            for j in range(self.size-1):
                if self.gridCell[i][j] == self.gridCell[i][j+1]:
                    return False
        for i in range(self.size-1):
            for j in range(self.size):
                if self.gridCell[i+1][j] == self.gridCell[i][j]:
                    return False
        return True
    
    def win(self):
        for i in range(self.size):
            for j in range(self.size):
                if(self.gridCell[i][j] == self.num):
                    return True
        return False

    def paintGrid(self):
        for i in range(self.size):
            for j in range(self.size):
                if self.gridCell[i][j] == 0:
                    self.board[i][j].config(text='', bg='azure4')
                else:
                    self.board[i][j].config(
                        text = str(self.gridCell[i][j]),
                        bg = self.bg_color.get(str(self.gridCell[i][j])),
                        fg = self.color.get(str(self.gridCell[i][j]))
                    )

class Game:
    def __init__(self, gamepanel):
        self.gamepanel = gamepanel

    def start(self):
        self.gamepanel.random_cell()
        self.gamepanel.random_cell()
        self.gamepanel.paintGrid()
        self.gamepanel.window.bind('<Key>', self.link_keys)
        self.gamepanel.window.mainloop()
    
    def link_keys(self, event):
        presed_key = event.keysym
        if presed_key == 'Up':
            self.gamepanel.transpose()
            self.gamepanel.compressGrid()
            self.gamepanel.mergeGrid()
            self.gamepanel.moved = self.gamepanel.compressed or self.gamepanel.merged
            self.gamepanel.compressGrid()
            self.gamepanel.transpose()
        elif presed_key == 'Down':
            self.gamepanel.transpose()
            self.gamepanel.reverse()
            self.gamepanel.compressGrid()
            self.gamepanel.mergeGrid()
            self.gamepanel.moved = self.gamepanel.compressed or self.gamepanel.merged
            self.gamepanel.compressGrid()
            self.gamepanel.reverse()
            self.gamepanel.transpose()
        elif presed_key == 'Left':
            self.gamepanel.compressGrid()
            self.gamepanel.mergeGrid()
            self.gamepanel.moved = self.gamepanel.compressed or self.gamepanel.merged
            self.gamepanel.compressGrid()
        elif presed_key == 'Right':
            self.gamepanel.reverse()
            self.gamepanel.compressGrid()
            self.gamepanel.mergeGrid()
            self.gamepanel.moved = self.gamepanel.compressed or self.gamepanel.merged
            self.gamepanel.compressGrid()
            self.gamepanel.reverse()
        self.gamepanel.paintGrid()

        if self.gamepanel.win():
            messagebox.showinfo('2048', 'Congratulation!')
            exit(0)

        if self.gamepanel.lose():
            messagebox.showinfo('2048','Game Over')
            exit(0)

        if self.gamepanel.moved:
            self.gamepanel.random_cell()
            self.gamepanel.paintGrid()

game2048 = Game(Board(5, 4096))
game2048.start()