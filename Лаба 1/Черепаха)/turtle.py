# Работаем!!!
fin=open('turtle.in','r')
fout=open("turtle.out", "w")
h=3
w=3
a = [[0, 1, 2, ], [3, 6, 4], [2, 5, 1]]
for i in range(len(a)):
    for j in range(len(a[i])):
        print(a[i][j], end=' ')
    print()
f=a[h-1][0]
p=a[h-1][0]
x=0
while f==a[0][w-1]:        # Программа не правильно рпботает от слова совсем,
    if a[h-2][x]>a[h-1][x+1]: # Поскульку приравных числах в диаогалях оно
        f=a[h-2][x]             #  Едит кукухой P.S. Она и так не работает)))
        p+=a[h-2][x]
        h-=1
        print(p)
    else:
        f=a[h-2][x+1]
        p+=a[h-1][x+1]
        p+=a[h-2][x+1]
        x+=1
        h-=1
        print(p)
print(p)
