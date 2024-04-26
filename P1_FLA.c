#include <stdio.h>
#include <stdlib.h>

int tamanocadena(char *cadena);
char *leerCadena(char *cadena);
char *sufijo(char *cadena, int n);
char *prefijo(char *cadena, int n);
char *subcadena(char *cadena, int s, int p);
char *invertirCadena(char *cadena);
char *concatenar(char *cadena1, char *cadena2);
char *subsecuencia(char *cadena1, int indices[], int can_ind);
char *copiarCadena(char *cadena);

int main() {
    char *cadena = (char *)malloc(1000 * sizeof(char));
    char *cadena2 = (char *)malloc(1000 * sizeof(char));

    // Leer la cadena desde la entrada estándar
    printf("Ingrese una cadena: ");
    int i = 0;
    char caracter;
    while ((caracter = getchar()) != '\n') {
        // Almacenar el caracter en el cadena
        cadena[i] = caracter;
        i++;
    }
    cadena[i] = '\0'; // Agregar el terminador nulo al final de la cadena    
    int opcion, tamano, n, s, p, can_ind, aux;
    int indices[100];

    

    do {
        char *copia_cadena = copiarCadena(cadena);
        printf("\nIngrese una opcion:\n");
        printf("1. Leer cadena\n");
        printf("2. Sufijo\n");
        printf("3. Prefijo\n");
        printf("4. Subcadena\n");
        printf("5. Invertir cadena\n");
        printf("6. Concatenar\n");
        printf("7. Mostrar datos de la cadena\n");
        printf("8. Subsecuencia\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese la nueva cadena: ");
                fflush(stdin);
                cadena = leerCadena(cadena);
                printf("Cadena leida: %s\n", cadena);
                break;
            case 2:
                tamano = tamanocadena(copia_cadena);
                printf("El tamano de la cadena es: %d\n", tamano);
                printf("Ingrese el indice para obtener el sufijo: ");
                scanf("%d", &n);
                copia_cadena = sufijo(copia_cadena, n);
                printf("Cadena sin el sufijo: %s\n", copia_cadena);
                //free(copia_cadena);
                break;
            case 3:
                tamano = tamanocadena(copia_cadena);
                printf("El tamano de la cadena es: %d\n", tamano);
                printf("Ingrese el indice para obtener el prefijo: ");
                scanf("%d", &n);
                copia_cadena = prefijo(copia_cadena, n);
                printf("Cadena sin el prefijo: %s\n", copia_cadena);
                //free(copia_cadena);
                break;
            case 4:
                tamano = tamanocadena(copia_cadena);
                printf("El tamano de la cadena es: %d\n", tamano);
                printf("Ingrese la posición inicial para obtener la subcadena: ");
                scanf("%d", &s);
                printf("Ingrese el tamaño de la subcadena: ");
                scanf("%d", &p);
                copia_cadena = subcadena(copia_cadena, s, p);
                printf("Subcadena: %s\n", copia_cadena);
                //free(copia_cadena);
                break;
            case 5:
                copia_cadena = invertirCadena(copia_cadena);
                printf("Cadena invertida: %s\n", copia_cadena);
                //free(copia_cadena);
                break;
            case 6:
                printf("Ingrese una cadena: ");
                int i = 0;
                char caracter;
                while ((caracter = getchar()) != '\n') {
                    // Almacenar el caracter en el cadena
                    cadena2[i] = caracter;
                    i++;
                }
                cadena2[i] = '\0'; // Agregar el terminador nulo al final de la cadena  
                puts(cadena2);
                copia_cadena = concatenar(copia_cadena, cadena2);
                printf("Cadenas concatenadas: %s\n", copia_cadena);
                //free(cadena);
                break;
            case 7:
                printf("La cadena ingresada es: %s\n", cadena);
                tamano = tamanocadena(cadena);
                printf("El tamano de la cadena es: %d\n", tamano);
                break;
            case 8:
                printf("Ingrese la cantidad de indices a eliminar:\n");
                scanf("%d", &can_ind);
                for(int i = 0; i < can_ind; i++) {
                    printf("Ingrese el indice: ");
                    scanf("%d", &indices[i]); 
                }
                copia_cadena = subsecuencia(copia_cadena, indices, can_ind);
                printf("Cadena resultante: %s\n", copia_cadena);
                //free(copia_cadena);
                break;
            case 9:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor, seleccione una opción válida.\n");
        }
    } while (opcion != 9);

    // Liberar la memoria asignada a las cadenas
    free(cadena);
    free(cadena2);
    
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

char *leerCadena(char *cadena) {
    printf("Ingrese una cadena: ");
    int i = 0;
    char caracter;
    fflush(stdin);
    while ((caracter = getchar()) != '\n') {
        // Almacenar el caracter en el cadena
        cadena[i] = caracter;
        i++;
    }
    cadena[i] = '\0'; //Agregamos el salto de linea para marcar fin en la cadena
    return cadena;
}

char *sufijo(char *cadena, int n) {
    int tamano = tamanocadena(cadena);
    if (n >= tamano) {
        printf("\nLambda");
        return cadena;
    }
    printf("Sufijo: %s\n", cadena + n); // Imprimimos el sufijo
    cadena[n] = '\0'; // Eliminamos el sufijo de la cadena agregando el salto de linea para marcar fin en la cadena
    return cadena;
}

char *prefijo(char *cadena, int n) {
    if (n <= 0) {
        printf("\nLambda");
        return cadena;
    }
    printf("Prefijo: ");
    for (int i = 0; i < n; i++) {
        printf("%c", cadena[i]); // Imprime el prefijo
    }
    printf("\n");
    return cadena + n; // Devolvemos la cadena sin el prefijo
}

char *subcadena(char *cadena, int s, int f) {
    int tamano = f - s + 1; // Calculamos el tamaño de la subcadena
    char *sub = (char *)malloc(sizeof(char) * ((f - s + 1)+ 1)); 
    for (int i = 0; i < tamano; i++) {
        sub[i] = cadena[s + i]; // Se copian los caracteres desde la posición s hasta f
    }
    sub[tamano] = '\0'; //Agregamos el salto de linea para marcar fin en la cadena
    return sub;
}

// Función para invertir una cadena
char *invertirCadena(char *cadena) {
    int tamano=tamanocadena(cadena);
    char *invertida = (char *)malloc(sizeof(char) * (tamano + 1));
    for (int i = 0; i < tamano; i++) {
        invertida[i] = cadena[tamano - i - 1]; //Se copian los caracteres en orden inverso
    }
    invertida[tamano] = '\0'; // Agregar el terminador nulo
    return invertida;
}

// Función para concatenar dos cadenas
char *concatenar(char *cadena1, char *cadena2) {
    int tamano1 = tamanocadena(cadena1);
    int tamano2 = tamanocadena(cadena1);
    char *concat = (char *)malloc(sizeof(char) * (tamano1 + tamano2 + 2)); // Se asigna memoria para la cadena concatenada (+1 por el operador fin de cadena) 
    for (int i = 0; i < tamano1; i++) {
        concat[i] = cadena1[i]; // Copiar los caracteres de la primera cadena
    }
    for (int i = 0; i < tamano2; i++) {
        concat[tamano1 + i] = cadena2[i]; // Copiar los caracteres de la segunda cadena
    }
    concat[tamano1 + tamano2] = '\0'; // Agregar el terminador nulo
    return concat;
}

char *subsecuencia(char *cadena, int indices[], int cantidad_indices) {
    int tamano = tamanocadena(cadena);
    char *resultado = (char *)malloc(tamano * sizeof(char) + 1); // Reservar memoria suficiente
    int j = 0;
    int es_indice_para_eliminar;

    for (int i = 0; i < tamano; i++) {
        es_indice_para_eliminar = 0;
        for (int k = 0; k < cantidad_indices; k++) {
            if (indices[k] == i) {
                es_indice_para_eliminar = 1;
                break;
            }
        }
        if (!es_indice_para_eliminar) {
            resultado[j++] = cadena[i];
        }
    }
    resultado[j] = '\0'; // Colocar el terminador nulo en la cadena resultante
    return resultado;
}

char *copiarCadena(char *cadena) {
    int tamano = tamanocadena(cadena);
    char *copia = (char *)malloc((tamano + 1) * sizeof(char)); // +1 para el caracter nulo
    for (int i = 0; i <= tamano; i++) { // Incluye el caracter nulo en la copia
        copia[i] = cadena[i];
    }
    return copia;
}
