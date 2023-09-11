from math import fabs


def sumV(v1, v2):
    return [v1[i] + v2[i] for i in range(len(v1))]


def diffV(v1, v2):
    return [v1[i] - v2[i] for i in range(len(v1))]


def v_multiply_k(v1, k):
    return [i * k for i in v1]


def dF(x, rk):
    h = 0.1**6
    mas = []
    for i in range(len(x)):
        x1 = [x[j] if j!=i else x[j]+h for j in range(len(x))]
        mas.append((F1(x1, rk)-F1(x, rk))/h)
    return mas


def norma(mas):
    return max([fabs(i) for i in mas])


def mns(x0, rk, eps1, eps2, N):
    def pd(x0):
        a, b, eps = -100, 100, 0.1**6
        delta = eps/2    # 0.1**2
        df = dF(x0, rk)
        while True:
            x1 = (a+b-delta)/2
            newargX = [x0[i]-x1*df[i] for i in range(len(x0))]
            y1 = (a+b+delta)/2
            newargY = [x0[i]-y1*df[i] for i in range(len(x0))]
            if F1(newargX,rk) < F1(newargY,rk):
                b = y1
            else:
                a = x1
            if fabs(b-a) <= 2*eps:
                x1 = (a+b)/2
                return x1

    if norma(dF(x0, rk)) < eps1:
        x_result = x0
    else:
        it = 0
        count = 0
        while True:
            s = v_multiply_k(dF(x0, rk), -1)
            alpha = pd(x0)
            x = sumV(x0, v_multiply_k(s, alpha))
            if norma(diffV(x, x0)) < eps2 and fabs(F1(x,rk) - F1(x0,rk)) < eps2:
                count += 1
                x_result = x
                if count == 2: break
            x0 = x
            if it >= N:
                x_result = x
                break
            it += 1
    return x_result


def F(x):
    #return 3*x[0]**2 + 4*x[1]**2 - 2*x[0]*x[1] + x[0]
    return  x[0] ** 2 + 6*x[1] ** 2+x[0]*x[1]+x[0]
def g(x):
    #return x[0] + x[1] - 1
    return x[0] + 3*x[1] - 1
def g1(x):
    return 0

def P1(x_0,rk):
    return rk/2*(g(x_0)**2+g1(x_0)**2)

def F1(x,rk):
    return F(x)+rk/2*(g(x)**2+g1(x)**2)
rk=1
c=2
N = 1000
xk = [1.5, 1.1]
eps1, eps2 = 0.1**3, 0.1**3

while True:
    f1=F1(xk,rk)
    x_0=mns(xk,rk, eps1, eps2, N)
    p1= P1(x_0,rk)
    if p1 <eps1:
        x_res = x_0
        f_res= F(x_0)
        break
    else:
        rk=c*rk
        xk=x_0
    print(f'x={x_0 }')
    print(f'p={p1 }')

print('метод Штрафных функций')
print(f'x={x_res } \n f(x)={F(x_res)}')