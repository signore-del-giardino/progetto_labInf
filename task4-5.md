## Task 4-5 Soluzione Sistema Lineare

Il codice implementa la quarta fase del progetto destinata alla risoluzione in ambiente Python del sistema lineare sparso $Ax = b$, derivante dalla discretizzazione dell'equazione del calore. Il codice è strutturato in quattro celle principali:

* **Prima Cella (librerie e parametri):** Viene effettuato il setup dell'ambiente. Si importano `numpy` per la gestione degli array, i moduli `coo_matrix` e `csc_matrix` da `scipy.sparse` per la creazione e manipolazione di matrici sparse, `spsolve_triangular` per la risoluzione di sistemi triangolari. Viene importato `cholesky` da `sksparse.cholmod` per l'ommonima fattorizzazione e `matplotlib.pyplot` per la visualizzazione dei risultati e l'analisi sperimentale.

* **Seconda Cella (funzioni):** Contiene le funzioni fondamentali:
  * `sistema_lineare(N, ord)`: Legge i file di testo (`A` e `rhs`) generati in C++. I dati della matrice $A$ vengono letti, forzati a interi (SciPy per costruire una matrice sparsa pretende che gli indici siano numeri interi!) per gli indici di riga e colonna, e caricati in formato COO (Coordinate list). Infine, la matrice viene convertita nel formato CSC (Compressed Sparse Column).

  * `my_Cholesky(a)`: calcola il fattore di Cholesky (`factor[0]`) in formato CSC.

  * `soluzione_sistemaLineare(l, b)`: Risolve il sistema $LL^T x = b$ in due passi sequenziali, sostituzione in avanti $Ly = b$ e all'indietro $L^T x = y$.

* **Terza Cella (soluzione):** Un ciclo `for` itera sui valori di $N$ e la soluzione viene salvata in un dizionario `x`.

* **Quarta Cella (visualizzazione):** Il vettore soluzione $1D$ di $N^2$ elementi viene ridimensionato (reshaped) in una griglia $2D$ di dimensioni $N \times N$. Tramite `matplotlib.contourf` viene tracciata una mappa di calore (heatmap) della temperatura.
