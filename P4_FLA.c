#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo
struct Nodo {
    struct Nodo** Nodo_b;
    struct Nodo** Nodo_a;
    int caminos_b;
    int caminos_a;
    int esFinal;
};

// Definición de la estructura de la lista
typedef struct {
    struct Nodo* Cabecera;
    struct Nodo* Ultimo;
} Lista;

// Prototipos de funciones
Lista* crearLista(int* error);
void tabla_funcion(Lista *p);
int verificar_pos(struct Nodo* nodoActual, char* array, int tam, int index);

// Función para crear una lista
Lista* crearLista(int* error) {
    Lista* ListaAsignacion = (Lista*) malloc(sizeof(Lista));
    if (ListaAsignacion == NULL) {
        perror("No hay memoria para la Lista");
        *error = -2;
        return NULL;
    }
    ListaAsignacion->Cabecera = NULL;
    ListaAsignacion->Ultimo = NULL;
    *error = 0;
    return ListaAsignacion;
}

// Tabla de Transicion
void tabla_funcion(Lista *p) {
    // Creación de los nodos
    struct Nodo* q0 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q1 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q2 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q3 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q4 = (struct Nodo*)malloc(sizeof(struct Nodo));

    // Inicialización de los nodos
    q0->Nodo_b = NULL;
    q0->Nodo_a = NULL;
    q0->caminos_b = 0;
    q0->caminos_a = 0;
    q0->esFinal = 0;

    q1->Nodo_b = NULL;
    q1->Nodo_a = NULL;
    q1->caminos_b = 0;
    q1->caminos_a = 0;
    q1->esFinal = 0;

    q2->Nodo_b = NULL;
    q2->Nodo_a = NULL;
    q2->caminos_b = 0;
    q2->caminos_a = 0;
    q2->esFinal = 1;

    q3->Nodo_b = NULL;
    q3->Nodo_a = NULL;
    q3->caminos_b = 0;
    q3->caminos_a = 0;
    q3->esFinal = 1;

    q4->Nodo_b = NULL;
    q4->Nodo_a = NULL;
    q4->caminos_b = 0;
    q4->caminos_a = 0;
    q4->esFinal = 1;

    // Descripcion tabla de transicion
    q0->Nodo_b = (struct Nodo**) malloc(sizeof(struct Nodo*));
    q0->Nodo_b[0] = q3;
    q0->caminos_b = 1;

    q0->Nodo_a = (struct Nodo**) malloc(2 * sizeof(struct Nodo*));
    q0->Nodo_a[0] = q1;
    q0->Nodo_a[1] = q4;
    q0->caminos_a = 2;

    q1->Nodo_a = (struct Nodo**) malloc(sizeof(struct Nodo*));
    q1->Nodo_a[0] = q1;
    q1->caminos_a = 1;

    q1->Nodo_b = (struct Nodo**) malloc(sizeof(struct Nodo*));
    q1->Nodo_b[0] = q2;
    q1->caminos_b = 1;

    q4->Nodo_b = (struct Nodo**) malloc(sizeof(struct Nodo*));
    q4->Nodo_b[0] = q4;
    q4->caminos_b = 1;

    // Definir inicio y final
    p->Cabecera = q0;
    p->Ultimo = q4; //En este caso puede ser cualquiera excepto el inicial
}

// Función recursiva para verificar si la secuencia es aceptada por el NFA
int verificar_pos(struct Nodo* nodoActual, char* array, int tam, int index) {
    if (index == tam) {
        return nodoActual->esFinal;
    }

    if (array[index] == 'a') {
        for (int i = 0; i < nodoActual->caminos_a; i++) {
            if (verificar_pos(nodoActual->Nodo_a[i], array, tam, index + 1)) {
                return 1;
            }
        }
    } else if (array[index] == 'b') {
        for (int i = 0; i < nodoActual->caminos_b; i++) {
            if (verificar_pos(nodoActual->Nodo_b[i], array, tam, index + 1)) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    int error;
    char* array = (char*)malloc(sizeof(char));
    char letra;
    int contador = 0;

    printf("Ingrese 'a' o 'b'. Ingrese 'c' para terminar.\n");
    while (1) {
        printf("Ingrese un letra: ");
        fflush(stdin);
        scanf("%c", &letra);
        if (letra == 'c') {
            break;
        }
        array = (char*)realloc(array, (contador + 1) * sizeof(char));
        array[contador] = letra;
        contador++;
    }

    // Añadimos un elemento más para el -1
    array = (char*)realloc(array, (contador + 1) * sizeof(char)); 
    array[contador] = 'c';

    Lista *p = crearLista(&error);

    // Creamos la tabla de nodos
    tabla_funcion(p);

    if (contador == 0 && p->Cabecera == p->Ultimo) {
        puts("Epsilon si pertenece al lenguaje");
    } else {
        // Verifica si el array pertenece al lenguaje
        if (verificar_pos(p->Cabecera, array, contador, 0)) {
            printf("El arreglo pertenece al lenguaje.\n");
        } else {
            printf("El arreglo no pertenece al lenguaje.\n");
        }
    }

    free(array);

    return 0;
}
