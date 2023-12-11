#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATHS 5

char *ft_strjoin(char const *s1, char const *s2) {
    if (!s1 || !s2)
        return NULL;

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t size = len1 + len2 + 1;

    char *str = malloc(sizeof(char) * size);
    if (!str) {
        perror("Errore nell'allocazione di memoria");
        exit(EXIT_FAILURE);
    }

    strcpy(str, s1);
    strcat(str, s2);

    return str;
}

char *pathfinder(char *command, char **path) {
    char *result = NULL;
    int i = 0;

    while (path[i] != NULL) {
        // Chiamiamo ft_strjoin due volte per aggiungere uno slash tra path[i] e command
        char *tempPath = ft_strjoin(path[i], "/");
        if (!tempPath) {
            perror("Errore nell'allocazione di memoria");
            exit(EXIT_FAILURE);
        }

        char *fullPath = ft_strjoin(tempPath, command);
        free(tempPath);  // Liberiamo la memoria temporanea

        if (!fullPath) {
            perror("Errore nell'allocazione di memoria");
            exit(EXIT_FAILURE);
        }

        if (access(fullPath, F_OK | X_OK) == 0) {
            result = fullPath;
            break;
        }

        free(fullPath);
        i++;
    }

    // Libera la memoria allocata per il percorso completo se non trovato
    if (result == NULL) {
        fprintf(stderr, "Il comando '%s' non è stato trovato nei percorsi specificati.\n", command);
    }

    return result;
}

int main() {
    char *command = "cat";
    char *paths[MAX_PATHS] = {"/bin", "/usr/bin", NULL};

    char *result = pathfinder(command, paths);

    if (result != NULL) {
        printf("Il percorso per il comando '%s' è: %s\n", command, result);
        free(result);
    }

    return 0;
}
