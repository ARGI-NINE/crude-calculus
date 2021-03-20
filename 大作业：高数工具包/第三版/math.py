import sympy as sp# exp*cos(x)的积分

w = sp.symbols('x')

formula = sp.Integral(sp.cos(w)*sp.exp(w), w)

print (formula)

sp.init_printing()

formula

# 求积分
print(formula.doit())

for i in range(3):
    print()
##求二阶导：

# method 1
b = 5 * w ** 3

print(b)

b1 = sp.diff(b, w)
print()

print(sp.diff(b1, w))

print(sp.diff(b, w, 2))



