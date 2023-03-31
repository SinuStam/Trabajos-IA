#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

using Estado = vector<int>;

// Función para verificar si un estado es el estado objetivo
bool es_objetivo(const Estado& estado) {
    for (int i = 0; i < estado.size() - 1; i++) {
        if (estado[i] > estado[i+1]) {
            return false;
        }
    }
    return true;
}

// Función para generar todos los posibles estados a partir del estado actual
vector<Estado> generar_siguientes(const Estado& estado_actual) {
    vector<Estado> siguientes;
    int n = estado_actual.size();
    for (int i = 2; i <= n; i++) {
        Estado siguiente(estado_actual.begin(), estado_actual.begin() + i);
        reverse(siguiente.begin(), siguiente.end());
        siguiente.insert(siguiente.end(), estado_actual.begin() + i, estado_actual.end());
        siguientes.push_back(siguiente);
    }
    return siguientes;
}

// Función para imprimir el camino que lleva al estado objetivo
void imprimir_camino(const Estado& estado_actual, const unordered_map<Estado, Estado>& padres) {
    Estado estado_actual_padre = estado_actual;
    while (padres.count(estado_actual_padre)) {
        cout << estado_actual_padre << " <- ";
        estado_actual_padre = padres.at(estado_actual_padre);
    }
    cout << estado_actual_padre << endl;
}

// Función que implementa BFS para resolver el juego de pancakes
void bfs(const Estado& estado_inicial) {
    queue<Estado> cola;
    unordered_set<Estado> visitados;
    unordered_map<Estado, Estado> padres;

    cola.push(estado_inicial);
    visitados.insert(estado_inicial);

    while (!cola.empty()) {
        Estado estado_actual = cola.front();
        cola.pop();

        if (es_objetivo(estado_actual)) {
            cout << "Se ha encontrado la solución: ";
            imprimir_camino(estado_actual, padres);
            return;
        }

        vector<Estado> siguientes = generar_siguientes(estado_actual);
        for (const auto& siguiente : siguientes) {
            if (!visitados.count(siguiente)) {
                cola.push(siguiente);
                visitados.insert(siguiente);
                padres[siguiente] = estado_actual;
            }
        }
    }

    cout << "No se ha encontrado solución" << endl;
}