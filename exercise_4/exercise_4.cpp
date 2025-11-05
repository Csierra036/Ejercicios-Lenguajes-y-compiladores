// Para un programa escrito en lenguaje C, cargado en una memoria de forma dinámica verifique si
// existen palabras reservadas en C y tradúzcalas a su equivalente en español.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *keyword;
    const char *translation;
} Keyword;

int main() {
    Keyword keywords[] = {
        {"int", "entero"},
        {"float", "flotante"},
        {"double", "doble"},
        {"char", "caracter"},
        {"if", "si"},
        {"else", "sino"},
        {"for", "para"},
        {"while", "mientras"},
        {"do", "hacer"},
        {"return", "retornar"},
        {"void", "vacio"},
        {"break", "romper"},
        {"continue", "continuar"},
        {"switch", "seleccionar"},
        {"case", "caso"},
        {"default", "predeterminado"},
        {"struct", "estructura"},
        {"typedef", "definición de tipo"},
        {"const", "constante"}
    };

    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    char *text = NULL;
    size_t size = 0;

    printf("Ingrese el codigo en C (finalice con una linea vacia):\n");

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strcmp(buffer, "\n") == 0) break;
        size_t len = strlen(buffer);
        char *newText = (char*) realloc(text, size + len + 1);
        if (!newText) {
            fprintf(stderr, "Error: no se pudo asignar memoria.\n");
            free(text);
            return 1;
        }
        text = newText;
        memcpy(text + size, buffer, len + 1);
        size += len;
    }

    if (!text) {
        printf("No se ingreso texto.\n");
        return 0;
    }

    printf("\nPalabras reservadas encontradas\n");

    char *token = strtok(text, " \n\t;(){}[]<>=+-*/&,");
    while (token) {
        for (int i = 0; i < numKeywords; i++) {
            if (strcmp(token, keywords[i].keyword) == 0) {
                printf("%s -> %s\n", keywords[i].keyword, keywords[i].translation);
            }
        }
        token = strtok(NULL, " \n\t;(){}[]<>=+-*/&,");
    }

    free(text);
    return 0;
}
