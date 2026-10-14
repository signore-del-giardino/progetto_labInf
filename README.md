# Soluzione Equazione del Calore 2D

**Progetto di Informatica con Laboratorio**
*ottobre 2026*

---

## 1 Architettura Generale del Software

L'obiettivo del progetto è risolvere l'equazione del calore 2D con una sorgente interna $f(x,y)$ su una piastra quadrata tramite il metodo delle differenze finite. Il software è logicamente suddiviso in due macro-moduli indipendenti che comunicano tramite file di testo:

*   **Modulo C++:** Si occupa della generazione della griglia spaziale, della costruzione del grafo di adiacenza, del riordinamento dei nodi (Nested Dissection) e della generazione del sistema lineare.
*   **Modulo Python:** Prende in carico la lettura del sistema lineare, la fattorizzazione di Cholesky, la risoluzione numerica e l'analisi sperimentale delle performance.

---

## 2 Parte 1 (C++)

Questo modulo conta 3 codici distinti che comunicano attraverso file di testo, in particolare:
1.  Il primo codice, `discretizzazione_dominio.cpp`, genera la griglia spaziale e il grafo di adiacenza.
2.  Il secondo codice, `nested_dissection.cpp`, riordina il dominio attraverso l'algoritmo di nested dissection.
3.  Il terzo codice, `sistema_lineare.cpp`, genera la matrice e il vettore dei termini noti associati al sistema lineare da risolvere.

### 2.1 Task 1: Dominio e Grafo di Adiacenza

*   **Input:** Intero $N$ che determina la discretizzazione uniforme del dominio quadrato $[0,1]^{2}$.
*   **Output:**
    *   File `coords.txt` contenente indice progressivo e coordinate $(x_{i},y_{j})$ dei punti interni.
    *   File `connectivity.txt` contenente la lista degli archi del grafo non orientato.
*   **Specifiche funzionali:**
    *   Generazione dei punti interni della griglia.
    *   Assegnazione di identificatori numerici progressivi ai nodi.
    *   Costruzione delle relazioni di adiacenza orizzontali e verticali.


### 2.2 Task 2: Riordinamento Nested Dissection

*   **Input:** Coordinate spaziali (`coords.txt`) e grafo di adiacenza (`connectivity.txt`) generati al punto precedente.
*   **Output:** File `ordering.txt` contenente il nuovo identificatore e l'identificatore originale del nodo.
*   **Specifiche funzionali:**
    *   Partizione dei nodi in tre insiemi disgiunti $V_{1}$, $V_{2}$, $V_{S}$ dove $V_{1}$ e $V_{2}$ hanno dimensione comparabile e il separatore $V_{S}$ ha cardinalità bassa.
    *   Applicazione ricorsiva della separazione geometrica, alternando i tagli lungo gli assi $\hat{x}$ e $\hat{y}$.
    *   Riordinamento finale che lista prima $V_{1}$, poi $V_{2}$ e infine $V_{S}$.


### 2.3 Task 3: Generazione del Sistema Lineare

*   **Input:** Coordinate (`coords.txt`), grafo di adiacenza (`connectivity.txt`) e ordinamento (`ordering.txt`), naturale o ottenuto attraverso nested dissection.
*   **Output:**
    *   File `A.txt` con le entrate non nulle della matrice A (indici di riga, colonna e valore).
    *   File `rhs.txt` con il vettore dei termini noti corrispondente.
*   **Specifiche funzionali:**
    *   Costruzione dell'approssimazione alle differenze finite per ogni punto interno usando la formula:
        $\frac{\kappa}{h^{2}}(u_{i-1,j}+u_{i+1,j}+u_{i,j-1}+u_{i,j+1}-4u_{i,j})+f(x_{i},y_{j})=0$
    *   Incorporazione delle condizioni al contorno $u_{0}(x,y)$ all'interno del termine noto (right hand side) per i nodi adiacenti al bordo.

---

## 3 Parte 2 (Python)

Questo modulo si occupa della risoluzione numerica del sistema lineare e della visualizzazione grafica della soluzione.

### 3.1 Task 4: Fattorizzazione Cholesky e Soluzione del Sistema

*   **Input:** File `A.txt` e `rhs.txt`.
*   **Output:** Vettore soluzione $u$.
*   **Specifiche funzionali:**
    *   Lettura dei file testuali e conversione della matrice in formato sparso CSC tramite le librerie SciPy.
    *   Calcolo della fattorizzazione di Cholesky $-A=LL^{T}$ utilizzando il pacchetto scikit-sparse.
    *   Risoluzione del sistema lineare triangolare tramite le funzioni `spsolve_triangular` di `scipy.sparse.linalg`.

### 3.2 Task 5: Benchmarking e Analisi Sperimentale

*   **Input:** Dati generati per risoluzioni crescenti della griglia ($N=32,64,\dots,1024$).
*   **Output:** Grafici comparativi, visualizzazione della matrice L e della soluzione
*   **Specifiche funzionali:**
    *   Misurazione e confronto dei tempi di esecuzione e del numero di entrate non-zero (fill-in) tra l'ordinamento naturale e l'ordinamento ottenuto tramite nested dissection.
    *   Plot della soluzione $u(x_{i},y_{i})$ del sistema sul dominio 2D.
    *   Visualizzazione della struttura della matrice A e del fattore di Cholesky L attraverso `matplotlib.pyplot.spy`.

