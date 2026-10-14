## Task 1 Discretizzazione del Dominio e Connettività

Il codice implementa la prima fase del progetto e ha lo scopo di generare un reticolo bidimensionale di dimensione $N \times N$ e di mapparne la topologia costruendo il relativo grafo di adiacenza.

* **Generazione Nodi (`coords_N.txt`):** Attraverso due cicli `for` annidati, assegna a ogni punto un identificatore numerico sequenziale (`n`), e ne scrive poi le sue coordinate discrete ($i, j$) e fisiche ($x, y$).
* **Generazione Archi (`connectivity_N.txt`):** All'interno dello stesso ciclo utilizzato per la scrittura delle coordinate del nodo, costruisce il grafo delle adiacenze. Per evitare duplicati, si tiene traccia esclusivamente dei collegamenti fra nodi in avanti (verso **destra** e verso l'**alto**), verificando di non trovarsi sui bordi estremi del dominio (rispettivamente `if (i < N)`, `if (j < N>)`). Ad ogni arco è assegnato un indice progressivo `e`.
* **Flusso di esecuzione (`main`):** Il `main` esegue automaticamente la discretizzazione per una serie di valori indicati nel codice ($N \in \{[32, 64, 128, 256, 512, 1024]\}$), salvando tutti i file nella directory di lavoro corrente.
