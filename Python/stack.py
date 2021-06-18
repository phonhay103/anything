class Stack:
    def __init__(self):
        self.stack = []
    
    def pop(self):
        return self.stack.pop()
    
    def push(self, x):
        self.stack.append(x)

    def isEmpty(self):
        return len(self.stack) == 0

    def show(self):
        for i in self.stack[::-1]:
            print(i, end=' ')
        print()


stack = Stack()
stack.push(1)
stack.push(2)
stack.push(3)
stack.push(4)
stack.push(5)
print(stack.pop())
stack.show()