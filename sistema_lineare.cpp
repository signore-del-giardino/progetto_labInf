#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>

using namespace std;

struct Nodo {
    int id;         // identificativo numerico del nodo
    int i, j;       // coordinate discrete del nodo (colonna, riga)
    double x, y;    // coordinate spaziali del nodo
};

vector<Nodo> leggiCoords(int N) {
    vector<Nodo> nodi(N * N);
    
    string nome_coords = "coords_" + to_string(N) + ".txt";
    int id, i, j;
    double x, y;

    ifstream fileCoords(nome_coords);
    if (!fileCoords) {
        cerr << "Errore: impossibile aprire " << nome_coords << endl;
        return {};
    } while (fileCoords >> id >> i >> j >> x >> y) {
        // Posizioniamo il nodo esattamente nell'indice corrispondente al suo ID originale
        nodi[id] = {id, i, j, x, y}; 
    }
    fileCoords.close();

    return nodi;
}

vector<vector<int>> leggiConn(int N) {
    vector<vector<int>> adiacenza(N * N);

    string nome_conn = "connectivity_" + to_string(N) + ".txt";
    int e, n1, n2;

    ifstream fileConn(nome_conn);
    if (!fileConn) {
        cerr << "Errore: impossibile aprire " << nome_conn << endl;
        return {}; 
    } while (fileConn >> e >> n1 >> n2) {
        // Ad ogni iterazione aggiungiungo alla lista di adiacenza del nodo n1 il nodo n2 e viceversa
        adiacenza[n1].push_back(n2);
        adiacenza[n2].push_back(n1);
    }
    fileConn.close();

    return adiacenza;
}

pair<vector<int>, vector<int>> leggiOrd(int N) {
    vector<int> nuovo_a_vecchio(N * N);
    vector<int> vecchio_a_nuovo(N * N);

    string nome_ord = "ordering_" + to_string(N) + ".txt";
    int m, n;

    ifstream fileOrd(nome_ord);
    if (!fileOrd) { cerr << "Errore: impossibile aprire " << nome_ord << endl;
        return {};
    } while (fileOrd >> m >> n) {
            nuovo_a_vecchio[m] = n;  // inserendo il nuovo ID (m) mi restituisce il vecchio (n)
            vecchio_a_nuovo[n] = m;  // inserendo il vecchio ID (n) mi restituisce il nuovo (m)
    }
    fileOrd.close();

    return {nuovo_a_vecchio, vecchio_a_nuovo};
}

double termineNoto(double x, double y) {
    return exp(- 10 * (x * x + y * y));
};

int main() {
    vector<int> punti = {32, 64, 128, 256, 512, 1024};

    for (int N : punti) {
        // --- Lettura dal file coords.txt; id, i, j, x, y ---
        vector<Nodo> nodi = leggiCoords(N);
        
        // --- Lettura dal file connectivity.txt; e, n1, n2 ---
        vector<vector<int>> adiacenza = leggiConn(N);

        // --- Lettura dal file ordering.txt; m, n ---
        auto [nuovo_a_vecchio, vecchio_a_nuovo] = leggiOrd(N);
        
        double k = 0.01;
        double h = 1.0 / (N + 1);
        double C = k / (h * h);

        string nome_A = "A_" + to_string(N) + ".txt";
        string nome_rhs = "rhs_" + to_string(N) + ".txt";

        ofstream fileA(nome_A);
        ofstream fileRHS(nome_rhs);

        if (!fileA || !fileRHS) {
            cerr << "Errore nell'apertura dei file A o rhs" << "\n";
            return 1;
        } for (int i = 0; i < N * N; i++) {
            // Accedo alle coordinate spaziali del nodo
            double x = nodi[nuovo_a_vecchio[i]].x;
            double y = nodi[nuovo_a_vecchio[i]].y;
            
            // Scrivo su rhs_N.txt il valore del termine noto (cambiato di segno!) corrispondente alle coordinate trovate
            fileRHS << - termineNoto(x, y) << "\n";

            // Scrivo su A_N.txt il valore dell'elemento diagonale
            fileA << i << " " << i << " " << - 4 * C << "\n";

            // Iterando all'interno della lista di adiacenza scrivo su A_N gli elementi fuori diagonale
            for (const auto& vicino : adiacenza[nuovo_a_vecchio[i]]) {
                int nuova_colonna = vecchio_a_nuovo[vicino];
                fileA << i << " " << nuova_colonna << " " << C << "\n";
            }  
        }

        fileA.close();
        fileRHS.close();
    }
    
    return 0;
}
