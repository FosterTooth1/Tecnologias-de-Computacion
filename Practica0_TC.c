#include <stdio.h>
#include <stdlib.h>

void Burble_sort_Ascendente(int* valor, int cantidadDatos);
void Burble_sort_Descendente(int* valor, int cantidadDatos);

int main() {
    int cantidadDatos, n;

    puts("Cuantos valores quiere agregar a el arreglo?");
    scanf("%d", &cantidadDatos);

    int* valor = (int*)malloc(sizeof(int) * cantidadDatos);
    
    for (int i = 0; i < cantidadDatos; i++) {
        printf("Ingresa un valor:");
        scanf("%d", &valor[i]);
    }
    puts("Datos agregados correctamente!");

    for(int i=0; i<cantidadDatos; i++){
        printf("\nEl dato numero %d es: %d ", i, valor[i]);
    }

    puts("\nDe que manera quiere ordenar sus datos, ascendente o descendente?");
    puts("1.Ascendente");
    puts("2.Descendente");
    scanf("%d", &n);

    if (n == 1) {
        Burble_sort_Ascendente(valor, cantidadDatos);            
    } else if(n == 2) {
        Burble_sort_Descendente(valor, cantidadDatos);
    }

    puts("El arreglo se ordeno correctamente");

    for(int i=0; i<cantidadDatos; i++){
        printf("\nEl dato numero %d es: %d ", i, valor[i]);
    }

    free(valor); // Liberar memoria asignada dinámicamente
    return 0;


}

void Burble_sort_Ascendente(int* valor, int cantidadDatos) {
    int aux;
    for (int i = 0; i < cantidadDatos - 1; i++) {
        for (int j = 0; j < cantidadDatos - 1 - i; j++) {
            if (valor[j] > valor[j + 1]) {
                aux = valor[j];
                valor[j] = valor[j + 1];
                valor[j + 1] = aux;
            }
        }
    }
}

void Burble_sort_Descendente(int* valor, int cantidadDatos) {
    int aux;
    for (int i = 0; i < cantidadDatos - 1; i++) {
        for (int j = 0; j < cantidadDatos - 1 - i; j++) {
            if (valor[j] < valor[j + 1]) {
                aux = valor[j];
                valor[j] = valor[j + 1];
                valor[j + 1] = aux;
            }
        }
    }
}
