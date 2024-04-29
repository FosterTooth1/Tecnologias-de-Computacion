#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
                Tabla de errores
        Variable        Estado      Descripción
        error           -1          Nodo nulo
        error           -2          Lista nula
        error           -3          Lista vacia
        error           0           Sin errores
*/

struct Nodo{
    int valor;  //--> Puede ser otro TDA
    //char Valores[50];
    struct Nodo* NodoInferior;
};

//Nivel 3
typedef struct{
    struct Nodo* Cabecera;
    struct Nodo* Ultimo;
    int cursor;
}Lista;

Lista* crearLista(int* error);
void consultarCabecera(Lista p, int* error);
void consultarUltimo(Lista p, int* error);
void consultarPosicion(Lista p, int* error, int n);
void enListarUltimo(Lista *p, int* error, struct Nodo dato);//push
void enListarCabecera(Lista *p, int* error, struct Nodo dato);
void enListarPosicion(Lista *p, int* error, struct Nodo dato, int n);
void DesenListarCabecera(Lista *p, int* error,struct Nodo *datoExtraido);
void DesenListarUltimo(Lista *p, int* error,struct Nodo *datoExtraido);
void DesenListarPosicion(Lista *p, int* error,struct Nodo *datoExtraido, int n);
bool isEmpty(Lista p, int* error);
void vaciarLista(Lista *p, int* error);
void vaciarMudo(Lista *p, int* error);
void destruirLista(Lista* p, int* error);
void MostrarLista(Lista *p, int* error, struct Nodo dato);
void selection_sort(Lista* p, int* error, int* datos);
void insertion_sort(Lista* p, int* error, int* datos);
void sort(int *arreglo, int tam);
void mezcla(int *arrIzq, int tamIzq, int *arrDer, int tamDer, int* arreglo);
void GuardarEnArreglo(Lista* p, int* error, int* datos);
void Burble_sort_Ascendente(Lista *p, int* error);
void Burble_sort_Descendente(Lista *p, int* error);
void BuscarElemento(Lista *p, int* error, struct Nodo *dato);

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

void consultarCabecera(Lista p, int* error){
    if(!isEmpty(p,error) && *error==0){
        printf("Valor en la Cabecera: %d\n", p.Cabecera->valor);
    }
    *error=0;
}

void consultarUltimo(Lista p, int* error){
    if(!isEmpty(p,error) && *error==0){
        printf("Valor en la ultima posicion de la Lista: %d\n", p.Ultimo->valor);
    }
    *error=0;
}

void consultarPosicion(Lista p, int* error, int n){
    if(isEmpty(p,error)){
        printf("La Lista esta Vacia\n");
    }else{
    struct Nodo* Puntero= p.Cabecera;
    int posicion=1;
    while(posicion<n && Puntero->NodoInferior){
        Puntero=Puntero->NodoInferior;
        posicion++;
    }
    if(posicion!=n){
        printf("No existe esa posicion porque no hay suficientes datos en la lista");
    }else{
        printf("Valor en la %d posicion de la Lista: %d\n", n, Puntero->valor);
    }
    }    
    *error=0;
}

//@param p Lista donde se alamcenaran los datos
//@param error variable que gestiona errores
//@param dato Nodo con la información del usuario
void enListarUltimo(Lista *p, int* error, struct Nodo dato){
    struct Nodo* nodoUsuario=(struct Nodo*) malloc(sizeof(struct Nodo));
    if(nodoUsuario==NULL){
        perror("No hay memoria para almacenar tu información");
        *error=-1;
    }else{
        nodoUsuario->valor=dato.valor;
        nodoUsuario->NodoInferior=NULL;
    }
    if(isEmpty(*p,error)){
        p->Cabecera=nodoUsuario;
        p->Ultimo=nodoUsuario;
    }else{
        p->Ultimo->NodoInferior=nodoUsuario;
        p->Ultimo=nodoUsuario;
    }
    p->cursor++;
    *error=0;
}

void enListarCabecera(Lista *p, int* error, struct Nodo dato){
    struct Nodo* nodoUsuario=(struct Nodo*) malloc(sizeof(struct Nodo));
    if(nodoUsuario==NULL){
        perror("No hay memoria para almacenar tu información");
        *error=-1;
    }
    if(isEmpty(*p,error)){
        nodoUsuario->valor=dato.valor;
        //strcpy(nodoUsuario->Valores,dato.Valores);
        nodoUsuario->NodoInferior=NULL;
        p->Cabecera=nodoUsuario;
        p->Ultimo=nodoUsuario;
    }else{
    nodoUsuario->valor=dato.valor;
    //strcpy(nodoUsuario->Valores,dato.Valores);
    nodoUsuario->NodoInferior=p->Cabecera;
    p->Cabecera=nodoUsuario;
    }
    p->cursor++;
    *error=0;
}

void enListarPosicion(Lista *p, int* error, struct Nodo dato, int n){
    struct Nodo* nodoUsuario=(struct Nodo*) malloc(sizeof(struct Nodo));
    if(nodoUsuario==NULL){
        perror("No hay memoria para almacenar tu información");
        *error=-1;
    }
    nodoUsuario->valor=dato.valor;
    nodoUsuario->NodoInferior=NULL;
    if(isEmpty(*p,error)){
        puts("La lista esta vacia por lo tanto el dato se anadio al principio de la Lista");
        p->Cabecera=nodoUsuario;
        p->Ultimo=nodoUsuario;
    }else{
    struct Nodo* Puntero= p->Cabecera;
    int posicion=1;
    while(posicion<n && Puntero->NodoInferior){
        Puntero=Puntero->NodoInferior;
        posicion++;
    }
    nodoUsuario->NodoInferior=Puntero->NodoInferior;
    Puntero->NodoInferior=nodoUsuario;
    }
    p->cursor++;
    *error=0;
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
        datoExtraido->valor=aux->valor;
    }else{
    *error=-3;
    }
}

void DesenListarUltimo(Lista *p, int* error,struct Nodo *datoExtraido){
    if(!isEmpty(*p,error)){
        struct Nodo *aux = NULL; //Se trabaja con una copia de la Lista "Principal"
        if (p->cursor>1){
            aux=p->Cabecera;
            while (aux->NodoInferior!=p->Ultimo){
                aux=aux->NodoInferior;
            }
            datoExtraido->valor=p->Ultimo->valor;
            p->Ultimo=aux;
            p->Ultimo->NodoInferior=NULL;
            aux->NodoInferior=NULL;    
        }else if(p->cursor==1){
            aux=p->Cabecera;
            p->Cabecera=NULL;
            p->Ultimo=NULL;
            datoExtraido->valor=aux->valor;
        }
        p->cursor--;
    }else{
    *error=-3;
    }
}

void DesenListarPosicion(Lista *p, int* error,struct Nodo *datoExtraido, int n){
    if(!isEmpty(*p,error)){
        struct Nodo *aux = NULL; //Se trabaja con una copia de la Lista "Principal"
        struct Nodo *aux2 = NULL;
        if (p->cursor>1){
            aux = p->Cabecera;
            for (int i=1; i<(n-1); ++i){ //Si no funciona correctamente cambiar (n-1) a solo n
                aux = aux->NodoInferior;
            }
            aux2 = aux->NodoInferior;
            datoExtraido->valor=aux2->valor;
            aux->NodoInferior = aux->NodoInferior->NodoInferior;
            if(aux->NodoInferior == NULL){
                p->Ultimo = aux;
            }
            free(aux2);
        }else if(p->cursor==1){
            aux=p->Cabecera;
            datoExtraido->valor=aux->valor;
            p->Cabecera=NULL;
            p->Ultimo=NULL;
        }
        p->cursor--;
    }else{
    *error=-3;
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

void vaciarLista(Lista *p, int* error){
    puts("Vaciando la Lista...");
    while(!isEmpty(*p, error)){
        struct Nodo datoExtraido;
        DesenListarCabecera(p,error,&datoExtraido);
        printf("Valor extraido: %d\n",datoExtraido.valor);
        *error=0;
    }
}

void vaciarMudo(Lista *p, int* error){
    while(!isEmpty(*p, error)){
        struct Nodo datoExtraido;
        DesenListarCabecera(p,error,&datoExtraido);
        *error=0;
    }
}

void destruirLista(Lista* p, int* error){
    if(isEmpty(*p,error)){
        puts("Destruyendo Lista...");
        free(p);
        puts("Lista Destruida!");
    }
    else{
        puts("No se puede destruir la Lista debido a que contiene informacion");
    }
}

void MostrarLista(Lista* p, int* error, struct Nodo Dato){
    printf ("\nDatos en la Lista:\n\n");
    struct Nodo *aux;
    aux = p->Cabecera; //Se trabaja con una copia de la Lista "Principal"
    if (aux == NULL) {
        printf ("No hay Datos\n");
        *error=-3;
    }
    int cantidad = 1;
    while (aux) {
        //printf ("%d. %s\n", cantidad, aux->Valores);
        printf ("%d. %d\n", cantidad, aux->valor);
        aux = aux->NodoInferior;
        cantidad++;
    }
}

void Burble_sort_Ascendente(Lista *p, int* error){
    struct Nodo *aux;
    aux = p->Cabecera; //Se trabaja con una copia de la Lista "Principal"
    if (aux == NULL) {
        printf ("No hay Datos\n");
        *error=-3;
    }else{
        while(aux!=NULL){
            struct Nodo *aux2 = aux->NodoInferior;
            while(aux2!=NULL){
                if(aux->valor>aux2->valor){
                    int aux3 = aux2->valor;
                    aux2->valor = aux->valor;
                    aux->valor=aux3;
                }
                aux2=aux2->NodoInferior;
            }
            aux=aux->NodoInferior;
        }
    }
}

void Burble_sort_Descendente(Lista *p, int* error){
    struct Nodo *aux;
    aux = p->Cabecera; //Se trabaja con una copia de la Lista "Principal"
    if (aux == NULL) {
        printf ("No hay Datos\n");
        *error=-3;
    }else{
        while(aux!=NULL){
            struct Nodo *aux2 = aux->NodoInferior;
            while(aux2!=NULL){
                if(aux->valor<aux2->valor){
                    int aux3 = aux2->valor;
                    aux2->valor = aux->valor;
                    aux->valor=aux3;
                }
                aux2=aux2->NodoInferior;
            }
            aux=aux->NodoInferior;
        }
    }
}


void GuardarEnArreglo(Lista* p, int* error, int* datos){
    struct Nodo *aux;
    aux = p->Cabecera; //Se trabaja con una copia de la Lista "Principal"
    if (aux == NULL) {
        printf ("No hay Datos\n");
        *error=-3;
    }else{
        int cantidad = 0;
        while (aux) {
            datos[cantidad]= aux->valor;       
            aux = aux->NodoInferior;
            cantidad++;
        }
    }
}

void selection_sort(Lista* p, int* error, int* datos){
    struct Nodo *aux;
    aux = p->Cabecera; //Se trabaja con una copia de la Lista "Principal"
    if (aux == NULL) {
        printf ("No hay Datos\n");
        *error=-3;
    }else{
        int cantidad = 0;
        while (aux) {
            datos[cantidad]= aux->valor;       
            aux = aux->NodoInferior;
            cantidad++;
        }
        int temp;
        for (int i=0; i<(p->cursor-1); i++){
            for (int j =(i+1); j<p->cursor; j++){
                if (datos[i] > datos[j]){
                    temp = datos[i];
                    datos[i] = datos[j];
                    datos[j] = temp;
                }
            }
        }
        *error=0;
    }
}

void insertion_sort(Lista* p, int* error, int* datos){
    struct Nodo *aux;
    aux = p->Cabecera; //Se trabaja con una copia de la Lista "Principal"
    if (aux == NULL) {
        perror("No hay Datos\n");
        *error=-3;
    }else{
        int cantidad = 0;
        while (aux) {
            datos[cantidad]= aux->valor;       
            aux = aux->NodoInferior;
            cantidad++;
        }
        int temp, j;
        for (int i = 1; i<p->cursor; i++){	   
		    temp = datos[i];
		    j = i-1;
		    //Comparar el valor selecionado con todos los valores anteriores
		    while (j >= 0 && datos[j] > temp){
			    //Insertar el valor donde corresponda
			    datos[j+1] = datos[j];
			    j--;
		    }
		    datos[j+1] = temp;
	    } 
        *error=0;
    }
}

void sort(int *arreglo, int tam){
    if(tam>1){
        int i,j,k;
        int mitad=tam/2;
        int arrIzq[mitad];
        int arrDer[tam-mitad];
        for(i=0, k=0; i<mitad; i++, k++){
            arrIzq[i]=arreglo[k];
        }
        for(j=0; j< (tam-mitad); j++, k++){
            arrDer[j]=arreglo[k];
        }
        sort(arrIzq,mitad);
        sort(arrDer,tam-mitad);
        mezcla(arrIzq,mitad, arrDer,tam-mitad,arreglo);
    }
}

void mezcla(int *arrIzq, int tamIzq, int *arrDer, int tamDer, int* arreglo){
    int i=0,j=0,k=0;
    while(i<tamIzq && j<tamDer){
        if(arrIzq[i]<arrDer[j]){
            arreglo[k]=arrIzq[i];
            i++;   
        } else{
            arreglo[k]=arrDer[j];
            j++;  
        }
        k++;
    }
    while(j<tamDer){
        arreglo[k]=arrDer[j];
        j++;
        k++;
    }
    while(i<tamIzq){
        arreglo[k]=arrIzq[i];
        i++;
        k++;
    }
}

void BuscarElemento(Lista *p, int* error, struct Nodo *dato){
    struct Nodo* Aux= p->Cabecera;
    int Posicion=1;
    int encontrados=0; 
    if(Aux==NULL){
        perror("No hay Datos\n");
        *error=-3;
    }else{
        while(Aux){
            if(Aux->valor==dato->valor){
                printf("\nDato %d encontrado en la posicion %d", dato->valor, Posicion);
                encontrados++;
            }
            Posicion++;
            Aux=Aux->NodoInferior;
        }
        if(encontrados==0){
            puts("El dato no se encuentra en la lista");
        }

    }
    *error=0;
}

int main(int argc, char** argv){
    int error;
    int cantidadDatos;
    int n;
    char Dato[50];
    int* datos= (int*)malloc(sizeof(int));
    Lista *p=crearLista(&error);
    struct Nodo dato;
    srand(time(NULL));
    int opc;
    do{
        printf("\n------------CONTROL DE LISTA---------\n");
        printf("\n1. Mostrar Datos\n");
        printf("2. Mostrar el valor en la primera posicion de la Lista\n");
        printf("3. Mostrar el valor en la ultima posicion de la Lista\n");
        printf("4. Mostrar el valor en la posicion 'n' de la lista\n");
        printf("5. Agregar Datos al principio de la lista\n");
        printf("6. Agregar Datos al final de la lista\n");
        printf("7. Agregar Datos en la posicion 'n'\n");
        printf("8. Remover Datos del principio de la Lista\n");
        printf("9. Remover Datos del final de la Lista\n");
        printf("10. Remover Datos de la posicion 'n' de la Lista\n");
        printf("11. Ordenar Lista ascendente o descendente haciendo una nueva lista\n");
        printf("12. Ordenar Lista de forma ascendente o descendente modificando la lista actual\n");
        printf("13. Buscar un dato en la lista\n");
        printf("14. Vaciar toda la Lista\n");
        printf("15. Salir");
        printf("\n\nInserte su opcion: ");
        scanf("%d", &opc);
    switch (opc){
    case 1:
        MostrarLista(p, &error,dato);
        break;

    case 2:
        consultarCabecera(*p, &error);
        break;

    case 3:
        consultarUltimo(*p,&error);
        break;

    case 4:
        puts("Digite la posicion de donde desea obtener el dato de la Lista:");
        fflush(stdin);
        scanf("%d", &n);
        consultarPosicion(*p,&error,n);
        break;

    case 5:
        /*
        puts("Cuantos valores quieres agregar a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        for(int i=0; i<cantidadDatos; i++){
            dato.valor= 1 + rand() % (10-1+1);
            enListarCabecera(p,&error,dato);
        }
        */
        //Si el usuario tiene que ingresar los datos cambiar el case nada mas
        puts("Cuantos valores quieres agregar a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        for(int i=0; i<cantidadDatos; i++){
            puts("Ingresa un valor:");
            fflush(stdin);
            //gets(Dato);
            //strcpy(dato.Valores,Dato);
            scanf("%d",&dato.valor);
            enListarCabecera(p,&error,dato);
        }
        puts("Datos agregados correctamente!");
        break;

    case 6:
        /*
        puts("Cuantos valores quieres agregar a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        for(int i=0; i<cantidadDatos; i++){
            dato.valor= 1 + rand() % (10-1+1);
            enListarUltimo(p,&error,dato);
        }
        */
        //Si el usuario tiene que ingresar los datos cambiar el case nada mas
        puts("Cuantos valores quieres agregar a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        for(int i=0; i<cantidadDatos; i++){
            puts("Ingresa un valor:");
            fflush(stdin);
            scanf("%d",&dato.valor);
            enListarUltimo(p,&error,dato);
        }
        puts("Datos agregados correctamente!");
        break;
    case 7:
        /*
        puts("Cuantos valores quieres agregar en esta posicion a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        puts("A partir de que posicion quieres agregar los datos:");
        fflush(stdin);
        scanf("%d", &n);
        for(int i=0; i<cantidadDatos; i++){
            dato.valor= 1 + rand() % (10-1+1);
            enListarPosicion(p,&error,dato, n);
        }
        */
        //Si el usuario tiene que ingresar los datos cambiar el case nada mas
        puts("Cuantos valores quieres agregar en esta posicion a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        puts("A partir de que posicion quieres agregar los datos:");
        fflush(stdin);
        scanf("%d", &n);
        for(int i=0; i<cantidadDatos; i++){
            puts("Ingresa un valor:");
            fflush(stdin);
            scanf("%d",&dato.valor);
            enListarPosicion(p,&error,dato, n);
        }
        puts("Datos agregados correctamente!");
        break;

    case 8:
        puts("Cuantos valores quieres quitar a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        for(int i=0; i<cantidadDatos; i++){
            DesenListarCabecera(p,&error,&dato);
            printf("Valor extraido: %d\n",dato.valor);
        }
        break;

    case 9:
        puts("Cuantos valores quieres quitar a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        for(int i=0; i<cantidadDatos; i++){
            DesenListarUltimo(p,&error,&dato);
            printf("Valor extraido: %d\n",dato.valor);
        }
        break;
        
    case 10:
        puts("Cuantos valores quieres quitar a la Lista?");
        fflush(stdin);
        scanf("%d",&cantidadDatos);
        puts("A partir de que posicion quieres eliminar los datos:");
        fflush(stdin);
        scanf("%d", &n);
        for(int i=0; i<cantidadDatos; i++){
            if(n<p->cursor){
                if(n==1){
                    DesenListarCabecera(p,&error,&dato);
                }else{
                    DesenListarPosicion(p,&error,&dato, n);
                }
            }else{
                DesenListarUltimo(p,&error,&dato);
            }
            printf("Valor extraido: %d\n",dato.valor);
        }
        break;       

    case 11:
        puts("De que manera quiere ordenar sus datos, ascendente o descendente?");
        puts("1.Ascendente");
        puts("2.Descendente");
        fflush(stdin);
        scanf("%d",&n);
        int y=p->cursor;
        /*
        En caso de utilizar cualquiera de las otras dos, solo quitar GuardarEnArreglo y sort
        // selection_sort(p,&error, datos);
        //insertion_sort(p,&error, datos);
        */
        GuardarEnArreglo(p,&error,datos);
        sort(datos, y);
        if(n==1){
            vaciarMudo(p, &error);
            for(int i=0; i<y; i++){
                dato.valor=datos[i];
                enListarUltimo(p,&error, dato);
            }
            puts("Lista reorganizada Correctamente!");
        }else if(n==2){
            vaciarMudo(p, &error);
            for(int i=0; i<y; i++){
                dato.valor=datos[i];
                enListarCabecera(p,&error, dato);
            }
            puts("Lista reorganizada Correctamente!");
        }
        break;

    case 12:
    puts("De que manera quiere ordenar sus datos, ascendente o descendente?");
        puts("1.Ascendente");
        puts("2.Descendente");
        fflush(stdin);
        scanf("%d",&n);
        if (n==1)
        {
        Burble_sort_Ascendente(p,&error);            
        }else if(n==2){
        Burble_sort_Descendente(p,&error);
        }
        puts("La lista se ordeno correctamente");
        break;

    case 13:
        puts("Ingresa un valor:");
        fflush(stdin);
        scanf("%d",&dato.valor);
        BuscarElemento(p,&error, &dato);
        break;
    
    case 14:
        vaciarLista(p,&error);
        puts("Lista Vaciada correctamente!");
        break;

    default:
        break;
    }

    }while (opc!=15);
    vaciarLista(p,&error);
    destruirLista(p, &error);
    return error;
}