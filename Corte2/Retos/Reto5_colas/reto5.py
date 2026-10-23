def siguienteMayor(a):
    n = len(a)
    res = [-1] * n
    pila = []

    for i in range(n):
        while pila and a[pila[-1]] < a[i]:
            res[pila.pop()] = a[i]
        pila.append(i)

    return res

print(siguienteMayor([2, 1, 2, 4, 3]))
