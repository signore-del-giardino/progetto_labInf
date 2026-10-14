## Task 2 Nested Dissection

Il codice implementa la seconda fase del progetto effettuando l'algoritmo di ordinamento _Nested Dissection_ attraverso una funzione dedicata. Questa ricevendo in ingresso il numero di punti del dominio considerato, restituisce un file `ordering.txt` contenente in ciascuna riga il nuovo indice del nodo (_m_) dopo il riordinamento e il suo identificatore orginale (_n_).

* **Struttura Dati:** Utilizza il tipo di dato astratto `Nodo` per memorizzare l'identificativo originale, le coordinate sulla griglia discreta ($i, j$) e le coordinate spaziali ($x, y$) di ciascun nodo.

* **L'Algoritmo (`nested_dissection`)** 
  * Il passo base gestisce i casi con 0 o 1 elemento (aggiungendolo, in quest'ultimo caso, direttamente all'ordinamento finale).
  * La funzione determina l'elemento separatore iterando su tutti i nodi dell'insieme corrente (scansione lineare) per trovare il valore minimo e massimo lungo l'attuale asse di taglio. Il separatore è calcolato come la media di questi due estremi.
  * L'insieme viene poi diviso in tre sottoinsiemi: `v1` (prima del separatore), `v2` (dopo il separatore) e `vs` (i nodi sul separatore).
  * Viene invocata la ricorsione su `v1` e `v2` alternando ad ogni chiamata l'asse di taglio (`1 - asse`).
  * Al termine della ricorsione `v1` e `v2` contengono un unico elemento che viene aggiunto alla lista dell'ordinamento finale. Infine, viene aggiunto anche l'insieme separatore `vs`.
* **Flusso di Esecuzione (`main`):** Itera su una lista predefinita di dimensioni del reticolo ($N \in \{32, 64, 128, 256, 512, 1024\}$), leggendo per ognuno le coordinate dai file generati e scrivendo i risultati su file in blocco.
