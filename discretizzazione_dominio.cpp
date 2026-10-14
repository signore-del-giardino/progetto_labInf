#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void discretizzazione_dominio(int N) {
    double h = 1.0 / (N + 1);   // passo reticolare
    int n = 0;  // identificativo numerico del punto
    int e = 0;  // indice di numerazione degli archi

    // Definizione nomi dei file
    string nome_coords = "coords_" + to_string(N) + ".txt";
    string nome_conn = "connectivity_" + to_string(N) + ".txt";

    ofstream fileCoords(nome_coords);
    ofstream fileConn(nome_conn);

    if (!fileCoords || !fileConn) {
        cerr << "Errore nell'apertura dei file." << endl; 
        return;
    } 
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // Scrittura sul file coords.txt (discretizzazione del dominio)
            double x = i * h;
            double y = j * h;
            fileCoords << n++ << " " << i << " " << j << " " << x << " " << y << "\n";

            // Calcolo degli archi del grafo e scrittura sul file connectivity.txt
            int current_node = (i - 1) * N + (j - 1);

            // Connessione verso DESTRA (se non siamo sull'ultima colonna)
            if (i < N) {
                int right_node = i * N + (j - 1);
                fileConn << e++ << " " << current_node << " " << right_node << "\n";
            }
            
            // Connessione verso l'ALTO (se non siamo sull'ultima riga)
            if (j < N) {
                int top_node = (i - 1) * N + j;
                fileConn << e++ << " " << current_node << " " << top_node << "\n";
            }
        }
    }

    fileCoords.close();
    fileConn.close();
}

int main() {
    vector<int> punti = {32, 64, 128, 256, 512, 1024};

    // Ad ogni iterazione genero una coppia di file: coords_32.txt, connectivity_32.txt ecc.
    for (int N : punti) {
        cout << "Elaborazione N = " << N << " in corso..." << endl;
        discretizzazione_dominio(N); 
    }
    
    return 0;
}
