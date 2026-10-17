## Task 3 Sistema Lineare

Il codice implemente la terza fase del progetto e si occupa della scrittura su file del sistema lineare $Ax = b$, con _A_ matrice sparsa e _b_ vettore dei termini noti. 

* **Struttura Dati:** Utilizza il tipo di dato astratto `Nodo` per memorizzare l'identificativo originale, le coordinate sulla griglia discreta ($i, j$) e le coordinate spaziali ($x, y$) di ciascun nodo.

*  **Flusso di esecuzione (`main`)**

   *  **Lettura Dati:** Attraverso le funzioni dedicate `leggiCoords`, `leggiConn`, `leggiOrd`, il codice carica in memoria rispettivamente la geometria, la topologia e la mappa di riordinamento dei nodi precedentemente generata. Soffermiamoci sulle ultime due $^1$:
      *  `leggiConn`: legge la topologia del reticolo e per ogni arco (cioè per ogni riga del file di connettività) aggiungiunge alla lista di adiacenza del nodo n1 il nodo n2 e viceversa;
      *  `leggiOrd`: legge `ordering.txt` e restituisce due vettori di interi definiti come `nuovo_a_vecchio[m] = n` e `vecchio_a_nuovo[n] = m`, che mappano i nuovi indici nei vecchi e viceversa.

   *  **Parametri Fisici:** Vengono calcolati il passo della griglia $h = \frac{1}{N+1}$ e la costante $C = \frac{k}{h^2}$ (dove $k=0.01$).

   *  **Il Sistema Lineare**: La scrittura del sistema avviene all'interno di un ciclo `for` che itera attraverso le $N^2$ righe `i` del sistema:
      *  **Scrittura termine noto RHS ($b$):** tramite la mappatura degli indici definita dalla funzione `leggiOrd`, si risale alle coordinate spaziale del nodo considerato. Il termine noto viene quindi calcolato tramite la funzione analitica `termineNoto(x, y)` (che valuta $e^{-10(x^2+y^2)}$) e scritto, cambiato di segno, nel file `rhs_N.txt`;
      *  **Scrittura matrice sparsa ($A$):** vengono scritti sul file `A_N.txt` gli elemententi sulla diagonale principale ($4C$). Identificati i nodi vicini, sfruttando le liste di adiacenza, per ciascuno di essi viene scritto un elemento fuori diagonale ($C$).

$^1$ Per maggiori informazioni su di `leggiCoords` vedi _task1.md_ e _task2.md_
