#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo
struct Nodo{
    int valor0; // Por completar con el tipo de datos adecuado
    struct Nodo* Nodo_0;
    struct Nodo* Nodo_1;
};

// Definición de la estructura de la lista
typedef struct{
    struct Nodo* Cabecera;
    struct Nodo* Ultimo;
    int cursor;
}Lista;

// Prototipos de funciones
Lista* crearLista(int* error);
void crear_nodos(Lista *p);
int procesarArray(int* array, int tam, Lista *p);
int obtenerTamanoArray(int* array);

// Función para crear una lista
Lista* crearLista(int* error){
    Lista* ListaAsignacion=(Lista*) malloc(sizeof(Lista));
    if(ListaAsignacion==NULL){
        perror("No hay memoria para la Lista");
        *error=-2;
        return NULL;
    }
    ListaAsignacion->Cabecera=NULL;
    ListaAsignacion->Ultimo=NULL;
    ListaAsignacion->cursor=0;
    *error=0;
    return ListaAsignacion;
}

// Función para crear los nodos según la descripción dada
void crear_nodos(Lista *p) {
    // Creación de los nodos
    struct Nodo* q0 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q1 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q2 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q3 = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    // Asignación de valores, por ejemplo, valor0 puede ser un entero
    q0->valor0 = 0; // Por completar con el valor adecuado
    q1->valor0 = 1; // Por completar con el valor adecuado
    q2->valor0 = 2; // Por completar con el valor adecuado
    q3->valor0 = 3; // Por completar con el valor adecuado
    
    // Establecimiento de las conexiones entre los nodos según la descripción dada
    q0->Nodo_0 = q2;
    q0->Nodo_1 = q1;
    
    q1->Nodo_0 = q3;
    q1->Nodo_1 = q0;
    
    q2->Nodo_0 = q0;
    q2->Nodo_1 = q3;
    
    q3->Nodo_0 = q1;
    q3->Nodo_1 = q2;
    
    // Asignación de los nodos a la lista
    p->Cabecera = q0;
    p->Ultimo = q3;
}

// Función para procesar el array de números binarios
int procesarArray(int* array, int tam, Lista *p) {
    struct Nodo* nodoActual = p->Cabecera; // Comenzamos en el nodo q0
    
    for (int i = 0; i < tam; i++) {
        if (array[i] == 1) {
            if (nodoActual->Nodo_1 != NULL) {
                nodoActual = nodoActual->Nodo_1;
            } else {
                return 0; // Si el nodo siguiente no existe, devuelve falso
            }
        } else if (array[i] == 0) {
            if (nodoActual->Nodo_0 != NULL) {
                nodoActual = nodoActual->Nodo_0;
            } else {
                return 0; // Si el nodo siguiente no existe, devuelve falso
            }
        } else {
            return 0; // Si el número no es ni 0 ni 1, devuelve falso
        }
    }
    
    // Devuelve verdadero si el nodo actual es q0, falso en caso contrario
    return (nodoActual == p->Cabecera);
}

// Función para obtener el tamaño de un array dinámico
int obtenerTamanoArray(int* array) {
    int tamano = 0;
    while (array[tamano] != -1) {
        tamano++;
    }
    return tamano;
}

int main() {
    int error;
    int* array = (int*)malloc(sizeof(int)); // Inicializamos el array dinámico con un tamaño inicial
    int numero;
    int contador = 0;
    
    // Solicitamos al usuario ingresar números binarios hasta que ingrese -1
    printf("Ingrese numeros binarios (0 o 1). Ingrese -1 para terminar.\n");
    while (1) {
        printf("Ingrese un numero: ");
        scanf("%d", &numero);
        if (numero == -1) {
            break;
        }
        array = (int*)realloc(array, (contador + 1) * sizeof(int)); // Ajustamos el tamaño del array
        array[contador] = numero;
        contador++;
    }
    array = (int*)realloc(array, (contador + 1) * sizeof(int)); // Añadimos un elemento más para el -1
    array[contador] = -1; // Agregamos -1 al final del array para marcar el final
    
    Lista *p=crearLista(&error);
    
    crear_nodos(p); // Creamos los nodos según las reglas dadas
    
    // Obtenemos el tamaño del array dinámico
    int tamanoArray = obtenerTamanoArray(array);
    
    // Procesamos el array y mostramos el resultado
    if (procesarArray(array, tamanoArray, p)) {
        printf("La función devuelve verdadero.\n");
    } else {
        printf("La función devuelve falso.\n");
    }
    
    free(array); // Liberamos la memoria asignada para el array
    
    return 0;
}
