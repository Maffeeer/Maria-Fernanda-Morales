#include <bits/stdc++.h>
using namespace std;

vector<int> siguienteMayor(const vector<int>& a) {
    int n = a.size();
    vector<int> result(n, -1);
    stack<int> pila;

    for (int i = 0; i < n; ++i) {
        while (!pila.empty() && a[i] > a[pila.top()]) {
            result[pila.top()] = a[i];
            pila.pop();
        }
        pila.push(i);
    }

    return result;
}

int main() {
    vector<int> a = {2, 1, 2, 4, 3};
    for (int x : siguienteMayor(a)) cout << x << " ";
    return 0;
}
