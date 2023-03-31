#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int v[MAXN];

struct Estado {
    int h;
    int g;
    int f;
    int padre;
    int accion;
    int pancakes[MAXN];
};

void revertir(int i, int j, Estado& e) {
    while (i < j) {
        swap(e.pancakes[i], e.pancakes[j]);
        i++, j--;
    }
}

// Función para verificar si el stack de pancakes está ordenado
bool es_solucion(const Estado& e) {
    for (int i = 1; i < n; i++) {
        if (e.pancakes[i] < e.pancakes[i - 1]) {
            return false;
        }
    }
    return true;
}

// Función para calcular la heurística de un estado
int calcular_heuristica(const Estado& e) {
    int desordenados = 0;
    for (int i = 1; i < n; i++) {
        if (e.pancakes[i] < e.pancakes[i - 1]) {
            desordenados++;
        }
    }
    return desordenados;
}

// Función que implementa A*
bool a_star() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cola;
    vector<Estado> estados;
    estados.push_back({calcular_heuristica({0, 0, 0, -1, -1, v}), 0, calcular_heuristica({0, 0, 0, -1, -1, v}), -1, -1, {v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12], v[13], v[14]}}); // Agregamos el estado inicial
    cola.push(make_pair(estados[0].f, 0));
    while (!cola.empty()) {
        int actual = cola.top().second;
        cola.pop();
        if (es_solucion(estados[actual])) {
            return true;
        }
        for (int i = 2; i <= n; i++) {
            if (estados[actual].accion == -1 || i != estados[actual].accion) {
                Estado hijo = estados[actual];
                revertir(0, i - 1, hijo);
                hijo.padre = actual;