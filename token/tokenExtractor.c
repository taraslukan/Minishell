#include "token.h"

int test(void)
{
    char *input = "ls -l 'file with spaces' | grep \"pattern\" > output.txt";
    char delimiter = ' ';
    char **tokens;
    int i = 0;

    // Separiamo la stringa usando il delimitatore spazio
    tokens = token_master(input, delimiter);

    // Stampa dei token ottenuti
    while (tokens[i])
    {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]); // Libera ogni token
        i++;
    }
    free(tokens); // Libera l'array di token

    return 0;
}
