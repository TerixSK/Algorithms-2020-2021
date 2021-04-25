fin=open('smallsort.in','r')
fout=open("smallsort.out", "w")
n=int(fin.readline())
a=list(map(int, fin.readline().split()))
for i in range(n-1):
    for j in range(n-i-1):
        if a[j]>a[j+1]:
            a[j],a[j+1]=a[j+1],a[j]
for i  in range(n):
    print(a[i],end=" ", file=fout)
fout.close()
