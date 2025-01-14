Funzionamento del codice

## FUNZIONAMENTO GENERALE
Il modulo Token è responsabile di elaborare la stringa di comandi letta dal modulo read.

- Divisione iniziale per pipe:
1)  Il primo passo consiste nel suddividere la stringa di comandi utilizzando la funzione ft_split, con la 
    pipe (|) come delimitatore. Questo processo consente di determinare il numero di pipe presenti e, di 
    conseguenza, quante volte sarà necessario reindirizzare le funzioni attraverso file descriptor temporanei 
    (FD) dichiarati nella struct generale (minishell.h).

- Suddivisione per token:
2)  Successivamente, ogni elemento della matrice risultante dalla suddivisione per pipe viene elaborato 
    individualmente. Ogni riga viene ulteriormente suddivisa nei suoi singoli token (es. comandi, argomenti, 
    redirezioni). I token estratti vengono quindi inviati al modulo di gestione delle funzioni (fun_create) 
    per l'esecuzione o la configurazione delle redirezioni.

- Creazione array comandi
3)  I dati estratti vengono salvati in un array di struct di tipo [t_comand]. La struct risiede nel parametro 
    functions della struct principale che viene chimata e creata nel main. I dati ora sono pronti per essere 
    passati alla funzione che esegue effettivamente le funzioni.

## • PIPE MANAGEMENT [((pipeManagement.c))]

Questo modulo contiene due funzioni che sono necessarie per la gestione e la suddivisione secondo le pipe.

>> count_pipe 

    Conta il numero di soddifisioni che sono state fatte per identificare il numero di pipe.
    Questo permette di avere una previsioni su quanti blocchi functions di tipo [t_comand] saranno necessari 
    per eseguire le operationi

>> pipe_splitter

    Questa funzione si occupa di eseguire uno split sulla stringa passata dal modulo read per il carattere pipe.
    Ritorna una matrice.

## • SPLIT BUILDER [((splitBuilder.c))]

Il codice implementa una funzione token_master che divide una stringa in token, 
trattando le parti tra virgolette (' o ") come un unico elemento. La suddivisione 
avviene rispettando un delimitatore specificato (es. spazio).

Analisi iniziale:
La funzione count_words analizza la stringa per calcolare il numero di token. 
Le virgolette vengono gestite per ignorare i delimitatori all'interno.

Tokenizzazione:
La funzione process_tokens percorre la stringa, identifica i token usando 
skip_token per gestire le virgolette e allocate_token per allocare memoria per ogni token.

Gestione delle virgolette:
La funzione skip_token tiene traccia dello stato delle virgolette (in_quotes) 
e si assicura che tutto il contenuto tra una coppia di virgolette venga considerato come un unico token.

Risultato finale:
ft_split restituisce un array di stringhe, dove ogni elemento è un token. 
La memoria per i token viene allocata dinamicamente e deve essere liberata successivamente.

Questo approccio è utile per simulare il comportamento delle shell, dove i comandi e i loro 
argomenti possono includere spazi o caratteri speciali racchiusi tra virgolette.

>> skip_token:

    Questa funzione avanza il puntatore str fino al termine del token corrente, ignorando eventuali caratteri 
    di delimitazione (c) se sono all'interno di virgolette.
    Gestisce le virgolette singole (') e doppie ("). Se il carattere attuale è una virgoletta e non siamo già 
    all'interno di virgolette (*in_quotes), la funzione imposta *in_quotes a true e salva il tipo di virgoletta 
    in *quote_char. Se il carattere attuale corrisponde al tipo di virgoletta memorizzato in *quote_char e siamo 
    all'interno di virgolette, imposta *in_quotes a false.

>> count_words:

    Questa funzione conta il numero di parole (token) nella stringa str separata dal delimitatore c.
    Usa la funzione skip_token per avanzare oltre ciascun token e tiene traccia di quante volte un token inizia.

>> allocate_token:

    Questa funzione alloca memoria per un token basato sulla sua lunghezza e copia il contenuto del token dalla 
    stringa start. Gestisce anche le virgolette, in modo simile alla funzione skip_token, ignorando i caratteri 
    di virgoletta all'interno del token.

>> process_tokens:

    Questa funzione crea effettivamente i token dalla stringa str utilizzando il delimitatore c e li salva 
    nell'array tokens. Usa skip_token per determinare i confini di ciascun token e allocate_token per allocare 
    memoria e copiare ciascun token.

>> token_master:

    Questa è la funzione principale che divide la stringa str in token.
    Conta il numero di parole nella stringa chiamando count_words.
    Alloca memoria per un array di puntatori a char (i token) e poi chiama process_tokens per riempire l'array con i token.

\\ esempio schematico

const char *str = "This 'is a' test \"string\".";
char delimiter = ' ';
char **tokens = token_master(str, delimiter);


## • CREAZIONE BLOCCO FUNZIONE [((tokenExtractor.c))]

Struttura e Funzionalità

    1. Funzione handle_file_redirections
    Questa funzione gestisce le redirezioni dei file e determina se l'output deve essere aggiunto 
    in modalità append.

Input:
    t_comand *ret: puntatore alla struttura comando da configurare.
    char **matrix: array di stringhe che rappresentano i token del comando.
    int i: indice di partenza per esaminare i token.
    bool pipe_in: indica se il comando riceve input da una pipe.
    bool pipe_out: indica se il comando invia output a una pipe.

Logica:
    Se è una pipe, assegna valori speciali (PIPE_STD_IN e PIPE_STD_OUT) per identificare i file di input/output.
    Scorre l'array matrix per identificare simboli di redirezione (<, >, >>) e imposta i file corrispondenti:
    [<]: specifica un file di input.
    [>]: specifica un file di output.
    [>>]: specifica un file di output in modalità append.



2. Funzione comand_write
    Questa funzione costruisce una struttura t_comand a partire dai token di un comando.

Input:
    char **matrix: array di stringhe contenente i token del comando.
    bool pipe_in e pipe_out: determinano se il comando è collegato a pipe.

Logica:
    Imposta il nome dell'eseguibile come il primo token (matrix[0]).
    Conta gli argomenti del comando ignorando le redirezioni [(<, >, >>)].
    Alloca memoria per gli argomenti e li copia.
    Chiama handle_file_redirections per configurare i file di input/output e la modalità append.



3. Funzione parse_pipeline
    Questa funzione costruisce una pipeline di comandi, rappresentata come un array di strutture t_comand.

Input:
    char ***pipeline_tokens: array di array di stringhe, ciascuno rappresentante i token di un comando nella pipeline.
    size_t num_pipes: numero di comandi nella pipeline.

Logica:
    Alloca memoria per l'array di t_comand.
    Per ogni comando, verifica se è connesso in una pipeline (usando pipe_in e pipe_out).
    Utilizza comand_write per costruire la struttura di ogni comando.



4. Funzione build_pipeline_tokens
    Questa funzione divide una pipeline in comandi distinti, creando token per ciascun comando.

Input:
    char **matrix_split: array di stringhe che rappresenta l'intera pipeline separata in comandi.
    size_t num_pipes: numero di comandi nella pipeline.

Logica:
    Alloca un array di array di stringhe (char ***).
    Per ogni comando, utilizza token_master per scomporre i token.
    L'ultimo elemento dell'array è NULL per segnalarne la fine.



5. Funzione tokenize
    Funzione principale per elaborare l'input di un comando con pipeline.

Input:
    char *input: stringa dell'intero comando.

Logica:
    Divide la pipeline in comandi usando pipe_splitter.
    Conta il numero di pipe nella pipeline con count_pipe.
    Crea i token dei comandi individuali con build_pipeline_tokens.
    Elabora ogni comando e costruisce le strutture t_comand con parse_pipeline.
    Stampa le informazioni con print_functions.
    Libera la memoria allocata per i token.



6. Funzione test
    Esegue un esempio di comando per verificare la funzionalità.

Input:
    Esempio: ls -l 'file with spaces' | grep "pattern" >> output.txt

Logica:
    Passa l'input a tokenize.
    La funzione tokenize esegue tutto il processo di tokenizzazione e parsing.
    Esempio di Flusso per il Comando
    Comando di input:

bash
    Copia codice
    ls -l 'file with spaces' | grep "pattern" >> output.txt

Pipeline:

    Primo comando: ls -l 'file with spaces'
    Secondo comando: grep "pattern"

Redirezioni:

    Il secondo comando ha un file di output (output.txt) in modalità append.
    Output della struttura t_comand:

Comando 1:
    exe: ls
    args: ["-l", "file with spaces", NULL]
    in_file: PIPE_STD_IN
    out_file: PIPE_STD_OUT

Comando 2:
    exe: grep
    args: ["pattern", NULL]
    in_file: PIPE_STD_IN
    out_file: "output.txt"
    append: true



Note
    La gestione delle redirezioni è stata separata in una funzione (handle_file_redirections) 
    per rendere il codice modulare e più leggibile. Ogni funzione è responsabile di una parte 
    specifica del processo di parsing e costruzione della pipeline.