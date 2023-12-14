#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **matrix_new_line(char **matrix, char *str) {
    // Trova la lunghezza della matrice
    int len = 0;
    if (matrix != NULL) {
        while (matrix[len] != NULL) {
            len++;
        }
    }

    // Alloca memoria per una nuova matrice con spazio per len+2 puntatori (uno per la nuova stringa e uno per NULL)
    char **newMatrix = (char **)calloc((len + 2), sizeof(char *));
    if (newMatrix == NULL) {
        fprintf(stderr, "Errore di allocazione di memoria per la nuova matrice.\n");
        exit(EXIT_FAILURE);
    }

    // Copia i dati dalla vecchia matrice alla nuova
    for (int i = 0; i < len; i++) {
        int strLen = strlen(matrix[i]) + 1;
        newMatrix[i] = (char *)malloc(strLen);
        if (newMatrix[i] == NULL) {
            fprintf(stderr, "Errore di allocazione di memoria per la nuova stringa.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(newMatrix[i], matrix[i]);
    }

    // Alloca memoria per la nuova stringa e copia il contenuto
    int newStrLen = strlen(str) + 1;
    newMatrix[len] = (char *)malloc(newStrLen);
    if (newMatrix[len] == NULL) {
        fprintf(stderr, "Errore di allocazione di memoria per la nuova stringa.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newMatrix[len], str);

    // Imposta il nuovo puntatore a NULL
    newMatrix[len + 1] = NULL;

    // Dealloca la vecchia matrice e restituisci la nuova
    if (matrix != NULL) {
        for (int i = 0; i < len; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }

    return newMatrix;
}

int main() {
    char **myMatrix = NULL;

    // Aggiungi una nuova stringa alla matrice
    myMatrix = matrix_new_line(myMatrix, "Prima stringa");

    // Aggiungi un'altra stringa alla matrice
    myMatrix = matrix_new_line(myMatrix, "Seconda stringa");

    // Stampa la matrice
    for (int i = 0; myMatrix[i] != NULL; i++) {
        printf("%s\n", myMatrix[i]);
    }

    // Dealloca la memoria allocata
    for (int i = 0; myMatrix[i] != NULL; i++) {
        free(myMatrix[i]);
    }
    free(myMatrix);

    return 0;
}
