def sdvig(slovo):
    L_s = len(slovo)

    if L_s == 0:
        return slovo
    else:
        R = ''
        for t in slovo:
            if t in A_big:
                i = A_big.find(t)
                if i + L_s > 26:
                    i = i + L_s - 26
                R += A_big[i + L_s]
            else:
                i = A_small.find(t)
                if i + L_s > 26:
                    i = i + L_s - 26
                R += A_small[i + L_s]

    return R


f1 = open('file1.txt','r')
f2 = open('file2.txt', 'w')
A_big = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

A_small = A_big.lower()
Alf = A_big + A_small

T = f1.read()

R = ''
slovo = ''
for t in T:
    if t in Alf:
        slovo += t
    else:
        if slovo != '':
            R += sdvig(slovo) + t
            slovo = ''

        else:
            R += t

if slovo != '':
    R += sdvig(slovo)

f2.write(R)
print(R)