## Task 1 Discretizzazione del Dominio e Connettività

Il codice implementa la prima fase del progetto e ha lo scopo di generare un reticolo bidimensionale di dimensione $N \times N$ e di mapparne la topologia costruendo il relativo grafo di adiacenza.

* **Generazione Nodi (`coords_N.txt`):** Attraverso due cicli `for` annidati, assegna a ogni punto un identificatore numerico sequenziale (`n`), e ne scrive poi le sue coordinate discrete ($i, j$) e fisiche ($x, y$).
* **Generazione Archi (`connectivity_N.txt`):** All'interno dello stesso ciclo utilizzato per la scrittura delle coordinate del nodo, costruisce il grafo delle adiacenze. Per evitare duplicati, si tiene traccia esclusivamente dei collegamenti fra nodi in avanti (verso **destra** e verso l'**alto**), verificando di non trovarsi sui bordi estremi del dominio (rispettivamente `if (i < N)`, `if (j < N>)`). Ad ogni arco è assegnato un indice progressivo `e`.
* **Flusso di esecuzione (`main`):** Il `main` esegue automaticamente la discretizzazione per una serie di valori indicati nel codice ($N \in \{[32, 64, 128, 256, 512, 1024]\}$), salvando tutti i file nella directory di lavoro corrente.

---

## Patch 1

Questa versione del codice si concentra sul miglioramento della **user experience** e sull'**organizzazione dei file**.

**Modifiche apportate:**

* **Gestione autonoma delle directory (`<filesystem>`):** Il miglioramento più importante è l'inclusione della libreria standard `filesystem`. Il programma ora richiama `fs::create_directory("output")` per assicurarsi che esista una cartella dedicata. Tutti i file generati vengono instradati automaticamente in questo percorso ordinato (`"output/coords_N.txt"`, ecc.).

* **Esecuzione interattiva:** Il ciclo automatizzato per i valori multipli di $N$ è stato rimosso. Ora il programma chiede direttamente all'utente (tramite `cin`) quale dimensione $N$ si desidera discretizzare durante la specifica esecuzione.
