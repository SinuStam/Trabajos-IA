#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int N = 10;

int n; // número de pancakes
vector<int> p(N+1);
vector<int> ans;

// Función para voltear los pancakes desde la posición i hasta la posición j
void voltear(int i, int j) {
    while (i < j) {
        swap(p[i], p[j]);
        i++; j--;
    }
}

// Función para verificar si los pancakes están ordenados
bool ordenados() {
    for (int i = 1; i < n; i++) {
        if (p[i] > p[i+1]) {
            return false;
        }
    }
    return true;
}

// Función que realiza la búsqueda DFS
void dfs() {
    stack<vector<int>> st;
    st.push(p);

    while (!st.empty()) {
        vector<int> curr = st.top();
        st.pop();

        if (ordenados()) {
            ans = curr;
            return;
        }

        for (int i = 1; i < n; i++) {
            for (int j = i+1; j <= n; j++) {
                vector<int> next = curr;
                voltear(i, j-1);
                next = curr;
                st.push(next);
                voltear(i, j-1);
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    dfs();

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}