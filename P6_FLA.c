#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura del nodo
struct Nodo {
    char* Nombre;
    char*** Caminos; // Array de arrays de nombres de nodos destino
    int esFinal;
    int esInicio; // Nuevo campo para indicar si es un nodo inicial
    int* CantidadDeCaminos; // Array que almacena la cantidad de caminos para cada entrada
    int numEntradas; // Número de posibles caminos (entradas)
};

// Estructura de la lista
typedef struct {
    struct Nodo* Cabecera;
    int NumNodos;
} Lista;

// Función para crear un nuevo nodo
struct Nodo* crearNodo(char* nombre, int numEntradas) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->Nombre = strdup(nombre);
    nuevoNodo->Caminos = (char***)malloc(numEntradas * sizeof(char**));
    nuevoNodo->CantidadDeCaminos = (int*)calloc(numEntradas, sizeof(int));
    nuevoNodo->esFinal = 0;
    nuevoNodo->esInicio = 0;
    nuevoNodo->numEntradas = numEntradas;
    for (int i = 0; i < numEntradas; i++) {
        nuevoNodo->Caminos[i] = NULL;
    }
    return nuevoNodo;
}

// Función para agregar un camino a un nodo, evitando duplicados
void agregarCamino(struct Nodo* nodo, int entradaIdx, char* destino) {
    // Verificar si el destino ya está en el camino
    for (int i = 0; i < nodo->CantidadDeCaminos[entradaIdx]; i++) {
        if (strcmp(nodo->Caminos[entradaIdx][i], destino) == 0) {
            return; // El destino ya está en el camino, no agregar
        }
    }
    nodo->Caminos[entradaIdx] = (char**)realloc(nodo->Caminos[entradaIdx], (nodo->CantidadDeCaminos[entradaIdx] + 1) * sizeof(char*));
    nodo->Caminos[entradaIdx][nodo->CantidadDeCaminos[entradaIdx]] = strdup(destino);
    nodo->CantidadDeCaminos[entradaIdx]++;
}

// Función para imprimir la lista
void imprimirLista(Lista* lista) {
    printf("Cantidad de nodos en la lista: %d\n", lista->NumNodos);
    for (int i = 0; i < lista->NumNodos; i++) {
        struct Nodo* nodo = &lista->Cabecera[i];
        printf("Nodo %s (esFinal: %d, esInicio: %d):\n", nodo->Nombre, nodo->esFinal, nodo->esInicio);
        for (int j = 0; j < nodo->numEntradas; j++) {
            if (nodo->CantidadDeCaminos[j] > 0) {
                printf("  Camino %d:", j);
                for (int k = 0; k < nodo->CantidadDeCaminos[j]; k++) {
                    printf(" %s", nodo->Caminos[j][k]);
                }
                printf("\n\n");
            }
        }
    }
}

// Función para contar el número de elementos separados por comas en una línea
int contarElementos(char* linea) {
    int count = 0;
    char* token = strtok(linea, ",");
    while (token) {
        count++;
        token = strtok(NULL, ",");
    }
    return count;
}

// Función para verificar si un nodo combinado ya existe en la lista
int nodoExiste(Lista* lista, char* nombre) {
    for (int i = 0; i < lista->NumNodos; i++) {
        if (strcmp(lista->Cabecera[i].Nombre, nombre) == 0) {
            return 1;
        }
    }
    return 0;
}

// Función para generar combinaciones de nodos
void generarCombinaciones(Lista* lista, char** elementos, int numElementos, int inicio, char* combinacion, int profundidad, int numEntradas) {
    if (profundidad > 0 && !nodoExiste(lista, combinacion)) {
        struct Nodo* nuevoNodo = crearNodo(combinacion, numEntradas);
        for (int i = 0; i < lista->NumNodos; i++) {
            if (strstr(combinacion, lista->Cabecera[i].Nombre) != NULL) {
                for (int entrada = 0; entrada < lista->Cabecera[i].numEntradas; entrada++) {
                    for (int k = 0; k < lista->Cabecera[i].CantidadDeCaminos[entrada]; k++) {
                        agregarCamino(nuevoNodo, entrada, lista->Cabecera[i].Caminos[entrada][k]);
                    }
                }
                if (lista->Cabecera[i].esFinal) {
                    nuevoNodo->esFinal = 1;
                }
            }
        }
        lista->Cabecera = (struct Nodo*)realloc(lista->Cabecera, (lista->NumNodos + 1) * sizeof(struct Nodo));
        lista->Cabecera[lista->NumNodos] = *nuevoNodo;
        lista->NumNodos++;
    }
    for (int i = inicio; i < numElementos; i++) {
        if (strcmp(elementos[i], "Vacio\n") != 0) { // Ignorar "Vacio"
            int newLen = strlen(combinacion) + strlen(elementos[i]) + 1;
            char* nuevaCombinacion = (char*)malloc(newLen * sizeof(char));
            snprintf(nuevaCombinacion, newLen, "%s%s",
            combinacion, elementos[i]);
            generarCombinaciones(lista, elementos, numElementos, i + 1, nuevaCombinacion, profundidad + 1, numEntradas);
            free(nuevaCombinacion);
        }
    }
}

// Función para verificar si una cadena pertenece al autómata
int verificarCadena(Lista* lista, char* cadena) {
    struct Nodo* nodoActual = NULL;
    for (int i = 0; i < lista->NumNodos; i++) {
        if (lista->Cabecera[i].esInicio) {
            nodoActual = &lista->Cabecera[i];
            break;
        }
    }
    
    if (nodoActual == NULL) {
        printf("No se encontró el nodo inicial.\n");
        return 0;
    }
    
    for (int i = 0; i < strlen(cadena); i++) {
        int entradaIdx = cadena[i] - '0';
        if (entradaIdx < 0 || entradaIdx >= nodoActual->numEntradas || nodoActual->CantidadDeCaminos[entradaIdx] == 0) {
            printf("Cadena no válida.\n");
            return 0;
        }
        nodoActual = NULL;
        for (int j = 0; j < lista->NumNodos; j++) {
            if (strcmp(lista->Cabecera[j].Nombre, nodoActual->Caminos[entradaIdx][0]) == 0) {
                nodoActual = &lista->Cabecera[j];
                break;
            }
        }
    }
    
    return nodoActual != NULL && nodoActual->esFinal;
}

// Función principal para leer el archivo y crear el autómata
void leerArchivoYCrearAutomata(char* nombreArchivo, Lista* lista) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char linea[100];
    char* token;
    
    // Leer la primera línea (nodos)
    fgets(linea, 100, archivo);
    int numNodos = contarElementos(strdup(linea));
    lista->Cabecera = (struct Nodo*)malloc(numNodos * sizeof(struct Nodo));
    lista->NumNodos = numNodos;
    
    // Leer nodos y crear nodos en la lista
    fseek(archivo, 0, SEEK_SET);
    fgets(linea, 100, archivo);
    token = strtok(linea, ",");
    int idx = 0;
    char** nombresNodos = (char**)malloc(numNodos * sizeof(char*));
    while (token) {
        nombresNodos[idx] = strdup(token);
        lista->Cabecera[idx] = *crearNodo(token, 1); // Inicialmente con un camino
        idx++;
        token = strtok(NULL, ",");
    }
    
    // Leer la segunda línea (caminos)
    fgets(linea, 100, archivo);
    int numEntradas = contarElementos(strdup(linea));
    for (int i = 0; i < lista->NumNodos; i++) {
        struct Nodo* nodo = &lista->Cabecera[i];
        nodo->numEntradas = numEntradas;
        nodo->Caminos = (char***)realloc(nodo->Caminos, numEntradas * sizeof(char**));
        nodo->CantidadDeCaminos = (int*)realloc(nodo->CantidadDeCaminos, numEntradas * sizeof(int));
        for (int j = 0; j < numEntradas; j++) {
            nodo->Caminos[j] = NULL;
            nodo->CantidadDeCaminos[j] = 0;
        }
    }
    
    // Leer la tercera línea (estado inicial)
    fgets(linea, 100, archivo);
    token = strtok(linea, ",");
    while (token) {
        for (int i = 0; i < lista->NumNodos; i++) {
            if (strcmp(lista->Cabecera[i].Nombre, token) == 0) {
                lista->Cabecera[i].esInicio = 1;
                break;
            }
        }
        token = strtok(NULL, ",");
    }

    // Leer la cuarta línea (nodos finales)
    fgets(linea, 100, archivo);
    token = strtok(linea, ",");
    while (token) {
        for (int i = 0; i < lista->NumNodos; i++) {
            if (strcmp(lista->Cabecera[i].Nombre, token) == 0) {
                lista->Cabecera[i].esFinal = 1;
                break;
            }
        }
        token = strtok(NULL, ",");
    }

    // Leer los caminos
    while (fgets(linea, 100, archivo)) {
        char* origen = strtok(linea, ",");
        char* entrada = strtok(NULL, ",");
        char* destino = strtok(NULL, ",\n"); // Asegurarse de eliminar nueva línea
        for (int i = 0; i < lista->NumNodos; i++) {
            if (strcmp(lista->Cabecera[i].Nombre, origen) == 0) {
                int entradaIdx = atoi(entrada);
                agregarCamino(&lista->Cabecera[i], entradaIdx, destino);
                break;
            }
        }
    }

    fclose(archivo);

    // Generar combinaciones de nodos
    char combinacion[100] = "";
    generarCombinaciones(lista, nombresNodos, numNodos, 0, combinacion, 0, numEntradas);

    // Liberar memoria
    for (int i = 0; i < numNodos; i++) {
        free(nombresNodos[i]);
    }
    free(nombresNodos);
}

int main() {
    Lista lista;
    leerArchivoYCrearAutomata("ejemplo.txt", &lista);
    imprimirLista(&lista);

    char cadena[100];
    printf("Ingrese una cadena para verificar: ");
    scanf("%s", cadena);

    if (verificarCadena(&lista, cadena)) {
        printf("La cadena pertenece al autómata.\n");
    } else {
        printf("La cadena no pertenece al autómata.\n");
    }

    return 0;
}
