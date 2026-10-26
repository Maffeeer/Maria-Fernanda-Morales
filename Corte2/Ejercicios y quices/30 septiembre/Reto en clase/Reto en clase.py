class Nodo:
	def __init__(self, valor, siguiente=None):
		self.valor = valor
		self.siguiente = siguiente


class Pila:
	def __init__(self):
		self.tope = None

	def apilar(self, valor):
		self.tope = Nodo(valor, self.tope)

	def desapilar(self):
		if self.vacia():
			return None
		valor = self.tope.valor
		self.tope = self.tope.siguiente
		return valor

	def cima(self):
		return None if self.vacia() else self.tope.valor

	def vacia(self):
		return self.tope is None


def balanceados(cadena):
	pila = Pila()
	pares = {')': '(', ']': '[', '}': '{'}

	for caracter in cadena:
		if caracter in '([{':
			pila.apilar(caracter)
		elif caracter in ')]}':
			if pila.desapilar() != pares[caracter]:
				return False

	return pila.vacia()


if __name__ == '__main__':
	print(balanceados('([]{})'))
	print(balanceados('([)]'))
	print(balanceados('((()'))
	print(balanceados('{}[]()'))
