#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Nodo {
    int id;         // identificativo numerico del nodo
    int i, j;       // coordinate discrete del nodo
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

// Implementazione (ricorsiva) dell'algoritmo di Nested Dissection
void nested_dissection(vector<Nodo>& nodi, int asse, int min_i, int max_i, int min_j, int max_j, vector<int>& ordinamento_finale) {

    if (nodi.empty()) return;       // insieme vuoto

    if (nodi.size() == 1) {         // insieme con un singolo elemento
        ordinamento_finale.push_back(nodi[0].id);
        return;
    }

    // Determinazione del separatore
    int min = (asse == 0) ? min_i : min_j;
    int max = (asse == 0) ? max_i : max_j;

    if (min == max) {
        nested_dissection(nodi, 1 - asse, min_i, max_i, min_j, max_j, ordinamento_finale);
        return;
    }

    int separatore = (max + min) / 2;

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

    // Alla fine della ricorsione v1 e v2 contano un singolo elemento che verrà quindi aggiunto all'ordinamento_finale: [V1, V2, VS]
    if (asse == 0) {    // se sto tagliando lungo X (asse == 0)
        nested_dissection(v1, 1 - asse, min_i, separatore - 1, min_j, max_j, ordinamento_finale);
        nested_dissection(v2, 1 - asse, separatore + 1, max_i, min_j, max_j, ordinamento_finale);
    } else {            // altrimenti, se sto tagliando lungo Y (asse == 1)
        nested_dissection(v1, 1 - asse, min_i, max_i, min_j, separatore - 1, ordinamento_finale);
        nested_dissection(v2, 1 - asse, min_i, max_i, separatore + 1, max_j, ordinamento_finale);
    }

    // Inserimento dell'insieme separatore VS in coda all'ordinamento
    for (const auto& nodo : vs) {
        ordinamento_finale.push_back(nodo.id);
    }
}

int main() {
    vector<int> punti = {32, 64, 128, 256, 512, 1024};

    for (int N : punti) {
        // Lettura dal file coords.txt
        vector<Nodo> nodi = leggiCoords(N);
	if (nodi.empty()) return 1;

        vector<int> ordinamento_finale;
        // Esecuzione dell'ordinamento
        nested_dissection(nodi, 0, 1, N, 1, N, ordinamento_finale);

        string nome_ordering = "ordering_" + to_string(N) + ".txt";
        // Trascrizione del risultato su ordering_N.txt
        ofstream fileOrd(nome_ordering);
        if (!fileOrd) {
            cerr << "Errore: impossibile creare " << nome_ordering << "\n";
            return 1;
        } for (int m = 0; m < ordinamento_finale.size(); m++) {
            fileOrd << m << " " << ordinamento_finale[m] << "\n";
        }
        fileOrd.close();
    }
        
    return 0;
}
