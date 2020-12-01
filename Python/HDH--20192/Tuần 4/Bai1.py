import turtle
import random

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

def create_ball(shape='circle', color='white', dx = 0.1, dy = -0.1, width=wn.window_width(), height=wn.window_height(), size = (1,1)):
    ball = turtle.Turtle()
    ball.speed(0)
    ball.shape(shape)
    ball.color(color)
    ball.penup()
    ball.goto(random.randint(-width/2 + 30*size[0], width/2 - 30*size[0]), random.randint(-height/2 + 30*size[1], height/2 - 30*size[1]))
    ball.dx = dx * random.randint(-1, 1)
    ball.dy = dy * random.randint(-1, 1)
    ball.shapesize(size[0], size[1])
    return ball

def ball_active(ball):
    # Move the ball
    ball.setx(ball.xcor() + ball.dx)
    ball.sety(ball.ycor() + ball.dy)

    if ball.dx == 0 and ball.dy == 0:
        ball.dx = random.random() * random.randint(-1,1)
        ball.dy = random.random() * random.randint(-1,1)

    # Reset
    if ball.xcor() > wn.window_width()/2 or ball.xcor() < -wn.window_width()/2 or ball.ycor() > wn.window_height()/2 or ball.ycor() < -wn.window_height()/2:
        ball.goto(0, 0)

    # Border checking
    if ball.xcor() > wn.window_width()/2 - 12*ball.shapesize()[0]:
        ball.dx *= -1
    if ball.xcor() < -wn.window_width()/2 + 9*ball.shapesize()[0]:
        ball.dx *= -1
    if ball.ycor() > wn.window_height()/2 - 9*ball.shapesize()[1]:
        ball.dy *= -1
    if ball.ycor() < -wn.window_height()/2 + 12*ball.shapesize()[1]:
        ball.dy *= -1

    # Ball color
    colorful(ball)

n = 50
balls = [create_ball(size=(2,2), dx=0.3*n, dy=-0.2*n) for i in range(n)]

while True:
    wn.update()
    for ball in balls:
        ball_active(ball)