Funzionamento del codice

## • SPLIT BUILDER

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