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

    ifstream fileCoords(nome_coords);
    if (!fileCoords) {
        cerr << "[ERRORE] Impossibile aprire " << nome_coords << endl;
        return {};
    } 
    
    int id, i, j;
    double x, y;
    while (fileCoords >> id >> i >> j >> x >> y) {
        // Posizioniamo il nodo esattamente nell'indice corrispondente al suo ID originale
        nodi[id] = {id, i, j, x, y}; 
    }
    fileCoords.close();

    return nodi;
}

vector<vector<int>> leggiConn(int N) {
    vector<vector<int>> adiacenza(N * N);
    string nome_conn = "connectivity_" + to_string(N) + ".txt";

    ifstream fileConn(nome_conn);
    if (!fileConn) {
        cerr << "[ERRORE] Impossibile aprire " << nome_conn << endl;
        return {}; 
    } 
    
    int e, n1, n2;
    while (fileConn >> e >> n1 >> n2) {
        // Ad ogni iterazione aggiungo alla lista di adiacenza del nodo n1 il nodo n2 e viceversa
        adiacenza[n1].push_back(n2);
        adiacenza[n2].push_back(n1);
    }
    fileConn.close();

    return adiacenza;
}

pair<vector<int>, vector<int>> leggiOrd(int N, const string& tipo_ordinamento) {
    int num_nodi = N * N;
    vector<int> nuovo_a_vecchio(num_nodi);
    vector<int> vecchio_a_nuovo(num_nodi);

    if (tipo_ordinamento == "old") {
        // Ordinamento naturale: nuovo indice e vecchio coincidono
        for (int k = 0; k < num_nodi; k++) {
            nuovo_a_vecchio[k] = k;
            vecchio_a_nuovo[k] = k;
        }
    } else if (tipo_ordinamento == "new") {
        // Ordinamento Nested Dissection
        string nome_ord = "ordering_" + to_string(N) + ".txt";
        ifstream fileOrd(nome_ord);
        
        if (!fileOrd) { 
            cerr << "[ERRORE] Impossibile aprire " << nome_ord << endl;
            return {};
        } 
        
        int m, n;
        while (fileOrd >> m >> n) {
            nuovo_a_vecchio[m] = n;  // inserendo il nuovo ID (m) mi restituisce il vecchio (n)
            vecchio_a_nuovo[n] = m;  // inserendo il vecchio ID (n) mi restituisce il nuovo (m)
        }
        fileOrd.close();
    }

    return {nuovo_a_vecchio, vecchio_a_nuovo};
}

double termineNoto(double x, double y) {
    return exp(- 10 * (x * x + y * y));
}

int main() {
    vector<int> punti = {32, 64, 128, 256, 512, 1024};

    for (int N : punti) {
        // --- Lettura file di input ---
        vector<Nodo> nodi = leggiCoords(N);
        if (nodi.empty()) return 1;

        vector<vector<int>> adiacenza = leggiConn(N);
        if (adiacenza.empty()) return 1;
        
        vector<string> ordinamenti_da_eseguire = {"old", "new"};
        for (string ord : ordinamenti_da_eseguire) {
            cout << "\nGenerazione del sistema lineare per l'ordinamento '" << ord << "' in corso..." << endl;

            auto [nuovo_a_vecchio, vecchio_a_nuovo] = leggiOrd(N, ord);
            if (nuovo_a_vecchio.empty()) return 1; 

            // Costanti del sistema
            double kappa = 0.01;
            double h = 1.0 / (N + 1);
            double C = kappa / (h * h);

            // Definizione dei nomi di output
            string nome_A = "A_" + to_string(N) + "_" + ord + ".txt";
            string nome_rhs = "rhs_" + to_string(N) + "_" + ord + ".txt";

            ofstream fileA(nome_A);
            ofstream fileRHS(nome_rhs);

            if (!fileA || !fileRHS) {
                cerr << "[ERRORE] Impossibile creare i file A o rhs";
                return 1;
            } 

            // --- Generazione di matrice A e vettore rhs ---
            for (int i = 0; i < N * N; i++) {
                
                // Risalgo al nodo fisico (identificatore originale) partendo dalla nuova riga 'i'
                int id_originale = nuovo_a_vecchio[i];
                
                // Accedo alle coordinate spaziali
                double x = nodi[id_originale].x;
                double y = nodi[id_originale].y;
                
                // Scrivo su rhs_N.txt il valore del termine noto (cambiato di segno)
                fileRHS << - termineNoto(x, y) << "\n";

                // Scrivo su A_N.txt il valore dell'elemento diagonale
                fileA << i << " " << i << " " << - 4 * C << "\n";

                // Itero all'interno della lista di adiacenza del nodo
                for (const auto& vicino : adiacenza[id_originale]) {
                    int nuova_colonna = vecchio_a_nuovo[vicino];
                    fileA << i << " " << nuova_colonna << " " << C << "\n";
                }  
            }

            fileA.close();
            fileRHS.close();

            cout << "File A_" << N << "_" << ord << ".txt e rhs_" << N << "_" << ord << ".txt generati con successo!" << endl;
        }
    }

    return 0;
}
