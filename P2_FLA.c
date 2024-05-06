#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Nodo{
    char Valores[50];
    struct Nodo* NodoInferior;
};

typedef struct{
    struct Nodo* Cabecera;
    struct Nodo* Ultimo;
    int cursor;
}Lista;

Lista* crearLista(int* error);
void enListarUltimo(Lista *p, int* error, struct Nodo dato);
void lenguaje_union(Lista *l1,Lista *l2,Lista *l3);
void lenguaje_intersencion(Lista *l1,Lista *l2,Lista *l3);
void lenguaje_resta(Lista *l1,Lista *l2,Lista *l3);
void lenguaje_concatenacion(Lista *l1,Lista *l2,Lista *l3);
void lenguaje_potencia(Lista *l1,Lista *l3);
void MostrarLista(Lista* p, int* error, struct Nodo Dato);
void vaciarLista(Lista *p, int* error);
bool isEmpty(Lista p, int* error);
void destruirLista(Lista* p, int* error);
int tamanocadena(char *cadena);
void invertirCadena(char *cadena);
void clonarLista(Lista *origen, Lista *destino, int *error);

int main() {
    int opcion, error, cantidadDatos, potencia;
    char Dato[50];
    Lista *l1=crearLista(&error);  
    Lista *l2=crearLista(&error);
    Lista *l3=crearLista(&error); 
    struct Nodo dato;

    do {
        printf("\nIngrese una opcion:\n");
        printf("1. Unir lenguajes\n");
        printf("2. Interseccion de Lenguajes\n");
        printf("3. Resta de Lenguajes\n");
        printf("4. Concatenacion de Lenguajes\n");
        printf("5. Potencia de Lenguaje\n");
        printf("6. Reflexion de Lenguaje\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        fflush(stdin);
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
            case 1:
                printf("Ingrese la cantidad de datos para el primer lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l1,&error,dato);
                }

                printf("Ingrese la cantidad de datos para el segundo lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l2,&error,dato);
                }

                puts("\n\nEl lenguaje union es:");
                lenguaje_union(l1,l2,l3);
                MostrarLista(l3,&error,dato);

                
                break;
            case 2:
                printf("Ingrese la cantidad de datos para el primer lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l1,&error,dato);
                }

                printf("Ingrese la cantidad de datos para el segundo lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l2,&error,dato);
                }

                puts("\n\nEl lenguaje intersencion es:");
                lenguaje_intersencion(l1,l2,l3);
                MostrarLista(l3,&error,dato);

                break;
            case 3:
                printf("Ingrese la cantidad de datos para el primer lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l1,&error,dato);
                }

                printf("Ingrese la cantidad de datos para el segundo lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l2,&error,dato);
                }

                puts("\n\nEl lenguaje resta es:");
                lenguaje_resta(l1,l2,l3);
                MostrarLista(l3,&error,dato);

                break;
            case 4:
                printf("Ingrese la cantidad de datos para el primer lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l1,&error,dato);
                }

                printf("Ingrese la cantidad de datos para el segundo lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l2,&error,dato);
                }

                puts("\n\nEl lenguaje concatenacion es:");
                lenguaje_concatenacion(l1,l2,l3);
                MostrarLista(l3,&error,dato);

                break;
            case 5:
                printf("Ingrese la potencia del lenguaje: ");
                fflush(stdin);
                scanf("%d",&potencia);
                if(potencia<0){
                    printf("Ingrese la cantidad de datos para el lenguaje: ");
                    fflush(stdin);
                    scanf("%d",&cantidadDatos);
                    for(int i=0; i<cantidadDatos; i++){
                        puts("Ingresa un valor:");
                        fflush(stdin);
                        scanf("%s", Dato);
                        invertirCadena(Dato);
                        strcpy(dato.Valores,Dato);
                        enListarUltimo(l1,&error,dato);
                    }
                    potencia=potencia*(-1);
                }else{
                    printf("Ingrese la cantidad de datos para el lenguaje: ");
                    fflush(stdin);
                    scanf("%d",&cantidadDatos);
                    for(int i=0; i<cantidadDatos; i++){
                        puts("Ingresa un valor:");
                        fflush(stdin);
                        scanf("%s", Dato);
                        strcpy(dato.Valores,Dato);
                        enListarUltimo(l1,&error,dato);
                    }
                }

                clonarLista(l1,l2, &error);

                for(int i = 1; i < potencia; i++) {
                    lenguaje_concatenacion(l2,l1, l3);
                    vaciarLista(l2, &error);
                    clonarLista(l3, l2, &error);
                    vaciarLista(l3, &error);
                }

                puts("\n\nEl lenguaje potencia es:");
                MostrarLista(l2,&error,dato);

                break;
            case 6:
                printf("Ingrese la cantidad de datos para el lenguaje: ");
                fflush(stdin);
                scanf("%d",&cantidadDatos);
                for(int i=0; i<cantidadDatos; i++){
                    puts("Ingresa un valor:");
                    fflush(stdin);
                    scanf("%s", Dato);
                    invertirCadena(Dato);
                    strcpy(dato.Valores,Dato);
                    enListarUltimo(l3,&error,dato);
                }

                puts("\n\nEl lenguaje reflexion es:");
                MostrarLista(l3,&error,dato);

                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no valida. Por favor, seleccione una opción valida.\n");
        }

        vaciarLista(l1,&error);
        vaciarLista(l2,&error);
        vaciarLista(l3,&error);

    } while (opcion != 7);

    // Liberar la memoria asignada a las listas
    destruirLista(l1, &error);
    destruirLista(l2, &error);
    destruirLista(l3, &error);
    
    return 0;
}

int tamanocadena(char *cadena) {
    if (cadena == NULL) {
        return 0;
    }
    if (*cadena == '\0') {
        return 0;
    }
    return 1 + tamanocadena(cadena + 1);
}

void invertirCadena(char cadena[]) {
    int tamano=tamanocadena(cadena);
    char invertida[tamano+1];
    for (int i = 0; i < tamano; i++) {
        invertida[i] = cadena[tamano - i - 1]; //Se copian los caracteres en orden inverso
    }
    invertida[tamano] = '\0'; // Agregar el terminador nulo
    strcpy(cadena, invertida);
}

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

bool BuscarElemento(Lista *p, int* error, struct Nodo *dato){
    struct Nodo* Aux= p->Cabecera;
    int encontrados = 0; 
    if(Aux==NULL){
        //perror("No hay Datos\n");
        //*error=-3;
    }else{
        while(Aux){
            if(strcmp(Aux->Valores, dato->Valores) == 0){
                encontrados++;
                break;
            }
            Aux=Aux->NodoInferior;
        }
    }
    if(encontrados==0){
        return false;
    } else {
        return true;
    }
}

void enListarUltimo(Lista *p, int* error, struct Nodo dato){
    // Verificar si el elemento ya existe en el lenguaje
    if (BuscarElemento(p, error, &dato)) {
        //printf("El elemento %s ya existe en la lista. No se agregará nuevamente.\n", dato.Valores);
        return;
    }

    struct Nodo* nodoUsuario=(struct Nodo*) malloc(sizeof(struct Nodo));
    if(nodoUsuario==NULL){
        perror("No hay memoria para almacenar tu información");
        *error=-1;
    } else {
        strcpy(nodoUsuario->Valores, dato.Valores);
        nodoUsuario->NodoInferior = NULL;

        if(isEmpty(*p,error)){
            p->Cabecera = nodoUsuario;
            p->Ultimo = nodoUsuario;
        } else {
            p->Ultimo->NodoInferior = nodoUsuario;
            p->Ultimo = nodoUsuario;
        }
        p->cursor++;
        *error=0;
    }
}

void DesenListarCabecera(Lista *p, int* error,struct Nodo *datoExtraido){
    if(!isEmpty(*p,error)){
        struct Nodo *aux = NULL; //Se trabaja con una copia de la Lista "Principal"
        if (p->cursor>1){
            aux=p->Cabecera;
            p->Cabecera=p->Cabecera->NodoInferior;
            aux->NodoInferior=NULL;    
        }else if(p->cursor==1){
            aux=p->Cabecera;
            p->Cabecera=NULL;
            p->Ultimo=NULL;
        }
        p->cursor--;
        strcpy(datoExtraido->Valores,aux->Valores);
    }else{
    *error=-3;
    }
}

void MostrarLista(Lista* p, int* error, struct Nodo Dato){
    struct Nodo *aux;
    aux = p->Cabecera;
    if (aux == NULL) {
        printf ("No hay Datos\n");
        *error=-3;
    }
    int cantidad = 1;
    while (aux) {
        printf ("%d. %s\n", cantidad, aux->Valores);
        aux = aux->NodoInferior;
        cantidad++;
    }
}

void vaciarLista(Lista *p, int* error){
    while(!isEmpty(*p, error)){
        struct Nodo datoExtraido;
        DesenListarCabecera(p,error,&datoExtraido);
        *error=0;
    }
}

void destruirLista(Lista* p, int* error){
    if(isEmpty(*p,error)){
        free(p);
    }
    else{
        puts("No se puede destruir la Lista debido a que contiene informacion");
    }
}

bool isEmpty(Lista p, int* error){
    if(p.Cabecera==NULL){
        *error=-3;
        return true;
    } else{
        *error=0;
        return false;   
    }
}

void lenguaje_union(Lista *l1, Lista *l2, Lista *l3) {
    int error;
    //struct Nodo datoExtraido;
    struct Nodo* Aux = l1->Cabecera;

    // Copiamos l1 a l3
    while (Aux != NULL) {
        enListarUltimo(l3, &error, *Aux);
        Aux = Aux->NodoInferior;
    }

    // Agregamos los elementos de l2 a l3 si no están en l1
    Aux = l2->Cabecera;
    while (Aux != NULL) {
        if (!BuscarElemento(l1, &error, Aux)) {
            enListarUltimo(l3, &error, *Aux);
        }
        Aux = Aux->NodoInferior;
    }
}

void lenguaje_intersencion(Lista *l1,Lista *l2,Lista *l3){
    int error;
    //struct Nodo datoExtraido;
    struct Nodo* Aux = l2->Cabecera;

    while (Aux != NULL) {
        if (BuscarElemento(l1, &error, Aux)) {
            enListarUltimo(l3, &error, *Aux);
        }
        Aux = Aux->NodoInferior;
    }
}
void lenguaje_resta(Lista *l1,Lista *l2,Lista *l3){
    int error;
    //struct Nodo datoExtraido;
    struct Nodo* Aux = l1->Cabecera;

    while (Aux != NULL) {
        if (!BuscarElemento(l2, &error, Aux)) {
            enListarUltimo(l3, &error, *Aux);
        }
        Aux = Aux->NodoInferior;
    }

}
void lenguaje_concatenacion(Lista *l1,Lista *l2,Lista *l3){
    int error;
    //struct Nodo datoExtraido;
    struct Nodo* Aux1 = l1->Cabecera;
    struct Nodo* Aux2 = l2->Cabecera;
    struct Nodo* cadena = (struct Nodo*) malloc(sizeof(struct Nodo));

    while (Aux1 != NULL) {
        while (Aux2 !=NULL){
            strcat(strcpy(cadena->Valores, Aux1->Valores), Aux2->Valores);
            enListarUltimo(l3, &error, *cadena);
            Aux2 = Aux2->NodoInferior;
        }
        Aux2 = l2->Cabecera;    
        Aux1 = Aux1->NodoInferior;
    }
}

void clonarLista(Lista *origen, Lista *destino, int *error) {
    vaciarLista(destino, error);

    struct Nodo *actual = origen->Cabecera;
    while (actual != NULL) {
        enListarUltimo(destino, error, *actual);
        actual = actual->NodoInferior;
    }
}