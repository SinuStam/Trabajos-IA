#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15; // Tamaño máximo del stack de pancakes

int n; // Número de pancakes
int v[MAXN]; // Stack de pancakes

// Función para revertir un substack de pancakes
void revertir(int i, int j) {
    while (i < j) {
        swap(v[i], v[j]);
        i++, j--;
    }
}

// Función para verificar si el stack de pancakes está ordenado
bool es_solucion() {
    for (int i = 1; i < n; i++) {
        if (v[i] < v[i - 1]) {
            return false;
        }
    }
    return true;
}

bool dfs_iterativo(int limite) {
    stack<pair<int, int>> pila;
    pila.push(make_pair(0, -1));
    int profundidad = 0;
    while (!pila.empty()) {
        int actual = pila.top().first;
        int padre = pila.top().second;
        pila.pop();
        if (es_solucion()) {
            return true;
        }
        if (profundidad >= limite) {
            continue;
        }
        for (int i = 2; i <= n; i++) {
            if (padre == -1 || i != padre) {
                revertir(0, i - 1);
                pila.push(make_pair(0, i));
                revertir(0, i - 1);
            }
        }
        profundidad++;
    }
    return false;
}

// Función principal
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int limite = 0;
    while (!dfs_iterativo(limite)) {
        limite++;
    }
    cout << "Se encontró una solución en profundidad " << limite << "\n";
    return 0;
}