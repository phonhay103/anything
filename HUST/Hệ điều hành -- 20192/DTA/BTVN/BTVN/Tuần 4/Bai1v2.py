import turtle
import random
import winsound

# Sound
winsound.PlaySound("sound.wav", winsound.SND_ASYNC | winsound.SND_ALIAS)

# Screen
width = 800
height = 600
wn = turtle.Screen()
wn.title("Balls")
wn.bgcolor('black')
wn.setup(width=width, height=height)
wn.tracer(0)

def colorful(T):
    R = random.random()
    B = random.random()
    G = random.random()
    T.color(R, G, B)

def create_ball(shape='circle', color='white', dx = 1, dy = 1, size = (1,1)):
    ball = turtle.Turtle()
    ball.speed(0)
    ball.shape(shape)
    ball.color(color)
    ball.penup()
    ball.goto(0, 0)
    ball.dx = dx
    ball.dy = dy
    ball.shapesize(size[0], size[1])
    return ball

def move(balls):
    for ball in balls:
        ball.setx(ball.xcor() + ball.dx)
        ball.sety(ball.ycor() + ball.dy)

        # Reset
        if ball.xcor() > wn.window_width()/2 or ball.xcor() < -wn.window_width()/2 or ball.ycor() > wn.window_height()/2 or ball.ycor() < -wn.window_height()/2:
            ball.goto(0, 0)
        
        colorful(ball)

        # Border checking
        if ball.xcor() > wn.window_width()/2 - 12*ball.shapesize()[0]:
            ball.dx *= -1
        if ball.xcor() < -wn.window_width()/2 + 9*ball.shapesize()[0]:
            ball.dx *= -1
        if ball.ycor() > wn.window_height()/2 - 9*ball.shapesize()[1]:
            ball.dy *= -1
        if ball.ycor() < -wn.window_height()/2 + 12*ball.shapesize()[1]:
            ball.dy *= -1

def create(n):
    balls = []
    balls.append(create_ball(dx=0, dy=1))
    for i in range(1, n+1):
        dx = i*1/(n+1)
        dy = (1-dx**2)**0.5
        balls.append(create_ball(dx=dx, dy=dy))
    balls.append(create_ball(dx=1, dy=0))
    for i in range(1, n+1):
        dx = (n+1-i)*1/(n+1)
        dy = -(1-dx**2)**0.5
        balls.append(create_ball(dx=dx, dy=dy))
    balls.append(create_ball(dx=0, dy=-1))
    for i in range(1, n+1):
        dx = -i*1/(n+1)
        dy = -(1-dx**2)**0.5
        balls.append(create_ball(dx=dx, dy=dy))
    balls.append(create_ball(dx=-1, dy=0))
    for i in range(1, n+1):
        dx = -(n+1-i)*1/(n+1)
        dy = (1-dx**2)**0.5
        balls.append(create_ball(dx=dx, dy=dy))
    return balls

def set_speed(balls, s):
    for ball in balls:
        ball.dx *= s
        ball.dy *= s

def set_size(balls, s):
    for ball in balls:
        size = ball.shapesize()
        ball.shapesize(size[0]*s, size[1]*s)

n = 15
balls = create(n)
set_speed(balls, 5)
set_size(balls, 2)

while True:
    wn.update()
    move(balls)