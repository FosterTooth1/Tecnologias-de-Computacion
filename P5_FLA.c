#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para contar el número de caracteres en una cadena hasta un delimitador o el final
int contarCaracteresHasta(const char *str, char delimitador) {
    int count = 0;
    while (str[count] != delimitador && str[count] != '\0' && str[count] != '\n') {
        count++;
    }
    return count;
}

// Función para procesar una línea y dividirla en tokens
char **procesarLinea(char *buffer, int *token_count) {
    char **tokens = NULL;
    *token_count = 0;
    char *ptr = buffer;

    while (*ptr != '\0' && *ptr != '\n') {
        int len = contarCaracteresHasta(ptr, ',');

        // Asignar memoria para el nuevo token
        tokens = (char **)realloc(tokens, sizeof(char *) * (*token_count + 1));
        tokens[*token_count] = (char *)malloc(sizeof(char) * (len + 1));

        // Copiar el token al array
        for (int i = 0; i < len; i++) {
            tokens[*token_count][i] = ptr[i];
        }
        tokens[*token_count][len] = '\0'; // Añadir el carácter nulo al final del token

        (*token_count)++;
        ptr += len;
        if (*ptr == ',') {
            ptr++; // Saltar la coma
        }
    }
    return tokens;
}

void generarCombinaciones(char **array, int n, char ***combinaciones, int *comb_count) {
    int total_combinations = (1 << n) - 1; // 2^n - 1 combinaciones
    *combinaciones = (char **)malloc(sizeof(char *) * total_combinations);
    if (!(*combinaciones)) {
        perror("Error en la asignación de memoria");
        exit(EXIT_FAILURE);
    }
    *comb_count = 0;

    for (int i = 1; i <= total_combinations; i++) {
        int len = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                len += contarCaracteresHasta(array[j], '\0') + 1; // +1 para la coma
            }
        }

        (*combinaciones)[*comb_count] = (char *)malloc(len);
        if (!(*combinaciones)[*comb_count]) {
            perror("Error en la asignación de memoria");
            exit(EXIT_FAILURE);
        }
        (*combinaciones)[*comb_count][0] = '\0';

        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                strcat((*combinaciones)[*comb_count], array[j]);
                strcat((*combinaciones)[*comb_count], ",");
            }
        }

        // Remover la última coma
        (*combinaciones)[*comb_count][len - 1] = '\0';
        (*comb_count)++;
    }
}

// Función para encontrar el índice de una combinación en el array de combinaciones
int encontrarIndiceCombinacion(char **combinaciones, int comb_count, char *combinacion) {
    for (int i = 0; i < comb_count; i++) {
        if (strcmp(combinaciones[i], combinacion) == 0) {
            return i;
        }
    }
    return -1; // No encontrado
}

// Función para encontrar el índice de una columna dada en la cabecera
int encontrarIndiceColumna(char **cabecera, int col_count, char *columna) {
    for (int i = 0; i < col_count; i++) {
        if (strcmp(cabecera[i], columna) == 0) {
            return i;
        }
    }
    return -1; // No encontrado
}

char *concatenarUnicos(char *destino, const char *fuente) {
    if (strlen(destino) == 0) {
        return strdup(fuente);
    }

    char *resultado = (char *)malloc(strlen(destino) + strlen(fuente) + 2); // +2 para la coma y el terminador nulo
    if (!resultado) {
        perror("Error en la asignación de memoria");
        exit(EXIT_FAILURE);
    }
    strcpy(resultado, destino);

    char *token_fuente = strdup(fuente);
    if (!token_fuente) {
        perror("Error en la asignación de memoria");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(token_fuente, ",");
    while (token != NULL) {
        if (strstr(destino, token) == NULL) {
            if (resultado[0] != '\0') {
                strcat(resultado, ",");
            }
            strcat(resultado, token);
        }
        token = strtok(NULL, ",");
    }
    free(token_fuente);

    return resultado;
}

// Función para contar los tokens en una cadena separada por comas
int contarTokens(const char *str) {
    int count = 0;
    const char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == ',') {
            count++;
        }
        ptr++;
    }
    return count + 1; // El número de tokens es el número de comas + 1
}

// Función para verificar si un token está en un array de tokens
int tokenEnArray(char *token, char **array, int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (strcmp(token, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Función para imprimir la matriz con los marcadores especificados
void imprimirMatriz(FILE *output, char ***matriz, int filas, int columnas, char *token_unico, char **array_tokens, int array_size) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] != NULL) {
                fprintf(output, "%-15s", matriz[i][j]);
            } else {
                fprintf(output, "%-15s", "");
            }
        }

        // Añadir marcadores
        if (i > 0 && strcmp(matriz[i][0], token_unico) == 0) {
            fprintf(output, "  *");
        } else if (i > 0) {
            char *comb = strdup(matriz[i][0]);
            char *token = strtok(comb, ",");
            int found = 0;
            while (token != NULL) {
                if (tokenEnArray(token, array_tokens, array_size)) {
                    fprintf(output, "  <-");
                    found = 1;
                    break;
                }
                token = strtok(NULL, ",");
            }
            free(comb);
        }

        fprintf(output, "\n");
    }
}

// Función para imprimir una matriz con marcadores
void imprimirMatrizConMarcadores(FILE *output, char ***matriz, int inicio, int fin, int columnas, char *token_unico, char **array_tokens, int array_size) {
    for (int i = inicio; i < fin; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] != NULL) {
                fprintf(output, "%-15s", matriz[i][j]);
            } else {
                fprintf(output, "%-15s", "");
            }
        }

        // Añadir marcadores
        if (strcmp(matriz[i][0], token_unico) == 0) {
            fprintf(output, "  *");
        } else {
            char *comb = strdup(matriz[i][0]);
            char *token = strtok(comb, ",");
            while (token != NULL) {
                if (tokenEnArray(token, array_tokens, array_size)) {
                    fprintf(output, "  <-");
                    break;
                }
                token = strtok(NULL, ",");
            }
            free(comb);
        }

        fprintf(output, "\n");
    }
}

int main() {
    FILE *file;
    char *filename = "ejemplo.txt";
    char buffer[1024];
    char ***lineas = (char ***)malloc(sizeof(char **) * 4);
    int token_counts[4] = {0};

    // Abrir el archivo para lectura
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Leer y procesar las primeras 4 líneas del archivo
    for (int i = 0; i < 4; i++) {
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            lineas[i] = procesarLinea(buffer, &token_counts[i]);
        } else {
            lineas[i] = NULL; // Manejar el caso donde hay menos de 4 líneas
        }
    }

    // Generar combinaciones de la primera línea (lineas[0])
    char **combinaciones;
    int comb_count;
    generarCombinaciones(lineas[0], token_counts[0], &combinaciones, &comb_count);

    // Crear y llenar la matriz
    int filas = comb_count + 1; // +1 para la cabecera
    int columnas = token_counts[1] + 1; // +1 para la columna de combinaciones

    char ***matriz = (char ***)malloc(filas * sizeof(char **));
    for (int i = 0; i < filas; i++) {
        matriz[i] = (char **)malloc(columnas * sizeof(char *));
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = NULL;
        }
    }

    // Llenar la cabecera
    matriz[0][0] = strdup("Q");
    for (int j = 0; j < token_counts[1]; j++) {
        matriz[0][j + 1] = strdup(lineas[1][j]);
    }

    // Llenar las combinaciones en la primera columna
    for (int i = 0; i < comb_count; i++) {
        matriz[i + 1][0] = strdup(combinaciones[i]);
    }

    // Leer las líneas restantes y llenar la matriz
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int token_count;
        char **tokens = procesarLinea(buffer, &token_count);
        if (token_count == 3) {
            int fila = encontrarIndiceCombinacion(combinaciones, comb_count, tokens[0]);
            int columna = encontrarIndiceColumna(lineas[1], token_counts[1], tokens[1]);
            if (fila != -1 && columna != -1) {
                fila++; // Ajustar para la cabecera
                columna++; // Ajustar para la cabecera
                if (matriz[fila][columna] == NULL) {
                    matriz[fila][columna] = strdup(tokens[2]);
                } else {
                    char *nuevo_valor = concatenarUnicos(matriz[fila][columna], tokens[2]);
                    free(matriz[fila][columna]);
                    matriz[fila][columna] = nuevo_valor;
                }
            }
        }
        for (int i = 0; i < token_count; i++) {
            free(tokens[i]);
        }
        free(tokens);
    }

    // Rellenar los espacios de las combinaciones con la lógica especificada
for (int i = 1; i < filas; i++) {
    for (int j = 1; j < columnas; j++) {
        if (matriz[i][j] == NULL) {
            matriz[i][j] = strdup("");
        }
        char *comb = strdup(matriz[i][0]);
        char *token = strtok(comb, ",");
        while (token != NULL) {
            int fila_token = encontrarIndiceCombinacion(combinaciones, comb_count, token);
            fila_token++; // Ajustar para la cabecera
            if (fila_token != i && matriz[fila_token][j] != NULL && strlen(matriz[fila_token][j]) > 0) {
                char *nuevo_valor = concatenarUnicos(matriz[i][j], matriz[fila_token][j]);
                free(matriz[i][j]);
                matriz[i][j] = nuevo_valor;
            }
            token = strtok(NULL, ",");
        }
        free(comb);
    }
}



    fclose(file);

    // Abrir el archivo de salida para escritura
    FILE *output = fopen("dfa.txt", "w");
    if (output == NULL) {
        perror("Error al abrir el archivo de salida");
        return 1;
    }

    // Imprimir la matriz completa
    fprintf(output, "Funcion de Estados completa:\n");
    imprimirMatriz(output, matriz, filas, columnas, lineas[2][0], lineas[3], token_counts[3]);

    // Imprimir la matriz inicial
    fprintf(output, "\nFuncion de Estados Inicial:\n");
    for (int i = 1; i < filas; i++) { // Empieza desde 1 para omitir la cabecera
        if (contarTokens(matriz[i][0]) == 1) {
            imprimirMatrizConMarcadores(output, matriz, i, i + 1, columnas, lineas[2][0], lineas[3], token_counts[3]);
        }
    }

    // Imprimir la matriz con combinaciones
    fprintf(output, "\nFuncion de Estados añadidos:\n");
    for (int i = 1; i < filas; i++) { // Empieza desde 1 para omitir la cabecera
        if (contarTokens(matriz[i][0]) > 1) {
            imprimirMatrizConMarcadores(output, matriz, i, i + 1, columnas, lineas[2][0], lineas[3], token_counts[3]);
        }
    }

    // Cerrar el archivo de salida
    fclose(output);

    // Liberar memoria
    for (int i = 0; i < 4; i++) {
        if (lineas[i] != NULL) {
            for (int j = 0; j < token_counts[i]; j++) {
                free(lineas[i][j]);
            }
            free(lineas[i]);
        }
    }
    free(lineas);

    for (int i = 0; i < comb_count; i++) {
        free(combinaciones[i]);
    }
    free(combinaciones);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] != NULL) {
                free(matriz[i][j]);
            }
        }
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
