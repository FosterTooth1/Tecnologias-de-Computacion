#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo
struct Nodo{
    struct Nodo* Nodo_0;
    struct Nodo* Nodo_1;
};

// Definición de la estructura de la lista
typedef struct{
    struct Nodo* Cabecera;
    struct Nodo* Ultimo;
}Lista;

// Prototipos de funciones
Lista* crearLista(int* error);
void tabla_funcion(Lista *p);
int verificar_pos(int* array, int tam, Lista *p);

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
    *error=0;
    return ListaAsignacion;
}

// Tabla de Transicion
void tabla_funcion(Lista *p) {
    // Creación de los nodos
    struct Nodo* q0 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q1 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q2 = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* q3 = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    // Descripcion tabla de transicion
    q0->Nodo_0 = q2;
    q0->Nodo_1 = q1;
    
    q1->Nodo_0 = q3;
    q1->Nodo_1 = q0;
    
    q2->Nodo_0 = q0;
    q2->Nodo_1 = q3;
    
    q3->Nodo_0 = q1;
    q3->Nodo_1 = q2;
    
    // Definir inicio y final
    p->Cabecera = q0;
    p->Ultimo = q0;
}

// Veriricar posicion
int verificar_pos(int* array, int tam, Lista *p) {
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
                return 0;
            }
        } else {
            return 0; // Si el número no es ni 0 ni 1, devuelve falso
        }
    }
    
    // Devuelve verdadero si el nodo actual es el final
    return (nodoActual == p->Ultimo);
}

int main() {
    int error;
    int* array = (int*)malloc(sizeof(int));
    int numero;
    int contador = 0;
    
    printf("Ingrese numeros binarios (0 o 1). Ingrese -1 para terminar.\n");
    while (1) {
        printf("Ingrese un numero: ");
        scanf("%d", &numero);
        if (numero == -1) {
            break;
        }
        array = (int*)realloc(array, (contador + 1) * sizeof(int));
        array[contador] = numero;
        contador++;
    }

    // Añadimos un elemento más para el -1
    array = (int*)realloc(array, (contador + 1) * sizeof(int)); 
    array[contador] = -1;
    
    Lista *p=crearLista(&error);
    
    // Creamos la tabla de nodos
    tabla_funcion(p);

    if(contador==0 && p->Cabecera==p->Ultimo){
        puts("Epsilon si pertenece al lenguaje");
    }else{

        //Verifica si el array pertenece al lenguaje
        if (verificar_pos(array, contador, p)) {
            printf("El arreglo pertenece al lenguaje.\n");
        } else {
            printf("El arreglo no pertenece al lenguaje.\n");
        }
    }
    
    free(array);
    
    return 0;
}
