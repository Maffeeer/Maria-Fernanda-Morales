#include <iostream>
#include <string>
#include <unordered_map>

struct Nodo {
    char valor;
    Nodo* siguiente;

    Nodo(char valor, Nodo* siguiente = nullptr)
        : valor(valor), siguiente(siguiente) {}
};

class Pila {
private:
    Nodo* tope;

public:
    Pila() : tope(nullptr) {}

    ~Pila() {
        while (!vacia()) {
            desapilar();
        }
    }

    void apilar(char valor) {
        tope = new Nodo(valor, tope);
    }

    char desapilar() {
        if (vacia()) {
            return '\0';
        }

        Nodo* nodo = tope;
        char valor = nodo->valor;
        tope = nodo->siguiente;
        delete nodo;
        return valor;
    }

    char cima() const {
        return vacia() ? '\0' : tope->valor;
    }

    bool vacia() const {
        return tope == nullptr;
    }
};

bool balanceados(const std::string& cadena) {
    Pila pila;
    const std::unordered_map<char, char> pares = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char caracter : cadena) {
        if (caracter == '(' || caracter == '[' || caracter == '{') {
            pila.apilar(caracter);
        } else if (caracter == ')' || caracter == ']' || caracter == '}') {
            if (pila.desapilar() != pares.at(caracter)) {
                return false;
            }
        }
    }

    return pila.vacia();
}

int main() {
    std::cout << std::boolalpha;
    std::cout << balanceados("([]{})") << '\n';
    std::cout << balanceados("([)]") << '\n';
    std::cout << balanceados("((()") << '\n';
    std::cout << balanceados("{}[]()") << '\n';
    return 0;
}
