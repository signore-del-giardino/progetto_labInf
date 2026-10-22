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

---

## Patch 1

Il codice ha subìto interventi di **refactoring e ottimizzazione algoritmica**, specialmente nella gestione del partizionamento logico della griglia.

**Modifiche apportate**

* **Modularizzazione della Lettura:** E' stata implementata una funzione `leggiCoords` dedicata alla lettura dei file delle coordinate, all'inteno della quale il vettore dei nodi viene preallocato con dimensione $N \times N$ e il nodo letto posizionato esattamente all'indice corrispondente al suo ID originale. Restituisce un vettore di Nodi contenente le informazioni spaziali di ciascun punto del dominio.

* **Ottimizzazione del Separatore:** Ora la funzione accetta come parametri il limiti discreti $min_i, max_i, min_j, max_j$ di ciascun dominio. Come conseguenza
  * viene eliminato il ciclo `for` (con costo computazionale $O(N^2)$ pari al numero di punti del dominio) per il calcolo di minino e massimo, migliorando drasticamente le performance del codice, $O(1)$;
  * il separatore viene calcolato analiticamente usando gli indici geometrici espliciti;
  * Le chiamate ricorsive ora aggiornano i confini passati ai figli (es. da $min_i$ a $separatore - 1$).

* **Gestione dei Casi Limite:** È stato introdotto un controllo `if (min == max)` per continuare la ricorsione semplicemente invertendo l'asse qualora un lato del dominio non sia più sezionabile.

---

## Patch 2

Quest'ultimo aggiornamento si concentra sull'**usabilità, sull'organizzazione dei file e sulla gestione degli errori**.

**Modifiche apportate**

* **Gestione delle Directory (`<filesystem>`):** Viene introdotta la libreria `filesystem` standard del C++. Il codice si aspetta (e verifica) che i file si trovino all'interno di una sottocartella dedicata `"output/"`, mantenendo ordinata la working directory dell'utente.

* **Interazione con l'Utente:** Il ciclo predefinito sulle diverse dimensioni $N$ nel `main` è stato eliminato. Il programma ora chiede esplicitamente all'utente (tramite `cin`) per quale valore di $N$ intende effettuare il calcolo.

* **Miglioramento dei Log d'Errore:** Nel caso non si riesca ad aprire il file di coordinate o se la cartella `"output/"` è mancante, i messaggi di `cerr` suggeriscono all'utente le azioni da intraprendere (es. "*Esegui 'discretizzazione_dominio'!*").

* **Documentazione Interna:** È stato aggiunto un blocco commento all'inizio della funzione ricorsiva `nested_dissection` per spiegare chiaramente lo scopo di tutti i parametri inseriti nella versione 2.

* **Feedback Visivo:** È stato inserito un log di successo alla fine dell'esecuzione che conferma dove e con quale nome è stato salvato il risultato.
