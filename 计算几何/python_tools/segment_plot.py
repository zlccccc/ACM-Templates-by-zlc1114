import matplotlib.pyplot as plt
def doit():
    n = int(input())
    for i in range(n):
        x1, y1, x2, y2 = map(int,input().split())
        plt.plot([x1, x2], [y1, y2])
    plt.show()

while True:
    doit()