fin=open('sortland.in','r')
fout=open("sortland.out", "w")
n=int(fin.readline())
M=list(map(float, fin.readline().split()))
a=[0]*n
for i in range(n):
    a[i]=M[i]
z1=1
z2=1
z3=1
x=0
y=0
w=0
for i in range(n-1):
    for j in range(n-i-1):
        if a[j]>a[j+1]:
            a[j],a[j+1]=a[j+1],a[j]

z1=a[0]
z2=a[n//2]
z3=a[n-1]
for i in range(n):
    if M[i]==z1:
        x=i
    if M[i]==z2:
        y=i
    if M[i]==z3:
        w=i
print(x+1,y+1,w+1, file=fout)
fout.close()
