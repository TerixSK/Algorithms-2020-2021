fin=open('sortland.in','r')
fout=open("sortland.out", "w")
n=int(fin.readline())
M=list(map(float, fin.readline().split()))
bog=-1
bed=10000000
sre=0
a=-1
b=-1
c=-1
for i in range(n):
    if M[i]<bed:
        bed=M[i]
        b=i+1
    if M[i]>bog:
        bog=M[i]
        a=i+1
    sre=sum(M)//n
    for i in range(n):
        if M[i]==sre:
            c=i+1
print(b,c,a, file=fout)
fout.close()
