#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Nodo {
    int id;         // identificativo numerico (originale) del nodo
    int i, j;       // coordinate discrete del nodo (colonna, riga)
    double x, y;    // coordinate spaziali del nodo
};

// Implementazione (ricorsiva) dell'algoritmo di Nested Dissection
void nestedDissection(vector<Nodo>& nodi, int asse, vector<int>& ordinamento_finale) {

    if (nodi.empty()) return;       // insieme vuoto

    if (nodi.size() == 1) {         // insieme con un singolo elemento
        ordinamento_finale.push_back(nodi[0].id);
        return;
    }

    // Determinazione del separatore
    int min_val = 1e9, max_val = -1;
    for (const auto& nodo : nodi) {
        int val = (asse == 0) ? nodo.i : nodo.j;
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }
    
    int separatore = (min_val + max_val) / 2;

    vector<Nodo> v1, v2, vs;

    // Partizionamento nei tre insiemi V1, V2 e VS
    for (const auto& nodo : nodi) {
        int val = (asse == 0) ? nodo.i : nodo.j;

        if (val < separatore) {
            v1.push_back(nodo);
        } else if (val > separatore) {
            v2.push_back(nodo);
        } else {
            vs.push_back(nodo);
        }
    }

    // Alla fine della ricorsione v1 e v2 contano un singolo elemento che verrà quindi aggiunto all'ordinamento_finale
    nestedDissection(v1, 1 - asse, ordinamento_finale);
    nestedDissection(v2, 1 - asse, ordinamento_finale);

    // Inserimento dell'insieme separatore VS in coda all'ordinamento
    for (const auto& nodo : vs) {
        ordinamento_finale.push_back(nodo.id);
    }
}

int main() {
    vector<int> punti = {32, 64, 128, 256, 512, 1024};

    for (int N : punti) {
        vector<Nodo> nodi;
        vector<int> ordinamento_finale;
        
        string nome_coords = "coords_" + to_string(N) + ".txt";
        string nome_ordering = "ordering_" + to_string(N) + ".txt";

        // Lettura dal file coords.txt e
        ifstream fileCoords(nome_coords);
        if (!fileCoords) { cerr << "Errore: impossibile aprire " << nome_coords << "\n"; return 1; }

        int id, i, j;
        double x, y;
        // Il formato previsto dal file è: n i j x y
        while (fileCoords >> id >> i >> j >> x >> y) {
            nodi.push_back({id, i, j, x, y});
        }
        fileCoords.close();

        // Esecuzione dell'ordinamento
        nestedDissection(nodi, 0, ordinamento_finale);

        // Trascrizione del risultato su ordering_N.txt
        ofstream fileOrd(nome_ordering);
        if (!fileOrd) { cerr << "Errore: impossibile creare " << nome_ordering << "\n"; return; }

        for (int m = 0; m < ordinamento_finale.size(); m++) {
            fileOrd << m << " " << ordinamento_finale[m] << "\n";
        }
        fileOrd.close();
        }

    return 0;
}
