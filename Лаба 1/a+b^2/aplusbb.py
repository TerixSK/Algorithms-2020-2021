fin = open("aplusbb.in")
fout = open("aplusbb.out", "w")
a,b=map(int, fin.readline().split())
print(a+b*b, file=fout)
fout.close()
