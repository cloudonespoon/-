import turtle as t
import random

t = t.Turtle()
t.shape("turtle")

A = int(input("횟수를 말해봐라: "))

for i in range(A):
    gag = random.randint(30,180)
    ganda = random.randint(50,100)
    t.forward(ganda)
    t.left(gag)