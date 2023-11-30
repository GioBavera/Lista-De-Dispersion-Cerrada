#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCasillas 25
#define VACIO NULL

static char* BORRADO = "**********"; // 10 asteriscos

typedef char **DICCIONARIO;


DICCIONARIO CREAR ();  
void DestruirTablaHash (DICCIONARIO); 
int h (char*); 
int localiza (char*, DICCIONARIO);
int localiza1 (char*, DICCIONARIO);
int MIEMBRO (char*, DICCIONARIO);
void INSERTA (char*, DICCIONARIO);
void SUPRIME (char*, DICCIONARIO);

//--------------------- MAIN
int main(){
    DICCIONARIO diccionario = CREAR();
    char entrada, palabra[25]; 

    printf("Desea Agregar algun miembro (Y/N): ");
    scanf(" %c", &entrada);
    while ((getchar()) != '\n'); // limpia el búfer de entrada
    while (entrada == 'Y'){
        printf("Ingrese una cadena: ");
        fgets(palabra, sizeof(palabra), stdin);
        palabra[strcspn(palabra, "\n")] = 0; // elimina el carácter de nueva línea
        INSERTA(palabra, diccionario);
        printf("Desea seguir agregando valores (Y/N)? ");
        scanf(" %c", &entrada);
        while ((getchar()) != '\n'); // limpia el búfer de entrada
    }
    printf("Que palabra desea saber si esta? ");
    fgets(palabra, sizeof(palabra), stdin);
    palabra[strcspn(palabra, "\n")] = 0; // elimina el carácter de nueva línea

    if(MIEMBRO(palabra, diccionario)){
        printf("Si esta.");
    }else{
        printf("No esta. ");
    }
    
    DestruirTablaHash(diccionario);
    return 0; 
}

//--------------------- FUNCIONES
// Crea un diccionario vacío con NCasillas contenedores
DICCIONARIO CREAR(){
    DICCIONARIO A = (char**) malloc(NCasillas*sizeof(char*));
    for (int i = 0; i < NCasillas; i++) {
        A[i] = VACIO;
    }
    return A;
}

// Libera la memoria del diccionario
void DestruirTablaHash(DICCIONARIO A) {
    for (int i = 0; i < NCasillas; i++) {
        if (A[i] != VACIO) {
            free(A[i]);
        }
    }
    free(A);
}


// Calcula el valor de dispersión de una cadena de caracteres
// Suma los valores numéricos de cada letra y luego toma el residuo de la división con NCasillas
int h(char *x) {
    int suma = 0;
    for (int i = 0; i < 10; i++) {
        suma += (int)x[i];
    }
    return suma % NCasillas;
}

// Busca el indice del contenedor (Primero x, despues vacio) y devuelve su direccion.
int localiza(char *x, DICCIONARIO A) {
    int inicial = h(x);
    int i = 0;

    if (A[inicial] == VACIO) {
        return inicial;
    }

    while (i < NCasillas && A[(inicial + i) % NCasillas] != VACIO) {
        i++;
    }

    return (inicial + i) % NCasillas;
}

// Busca el indice del contenedor (Primero x, despues vacio o borrado) y devuelve su direccion.
int localiza1(char *x, DICCIONARIO A) {
    int inicial = h(x); 
    int i = 0;          

    if (A[inicial] == VACIO || A[inicial] == BORRADO) {
        return inicial;
    }

    while (i < NCasillas && A[(inicial + i) % NCasillas] != VACIO && A[(inicial + i) % NCasillas] != BORRADO) {
        i++;
    }

    return (inicial + i) % NCasillas;
}

// Devuelve 1 si x es miembro del diccionario, 0 en caso contrario
int MIEMBRO(char *x, DICCIONARIO A) {
    int index = localiza(x, A);
    if (strcmp(A[index], x) == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Inserta x en el diccionario si no está ya
// Busca una localidad vacía o con BORRADO para insertar x
void INSERTA(char *x, DICCIONARIO A) {
    int index = localiza1(x, A); 

    if (A[index] == VACIO || A[index] == BORRADO) {
        A[index] = (char *)malloc((strlen(x) + 1) * sizeof(char)); 
        strcpy(A[index], x); // Copia x en el contenedor
    } else {
        printf("ERROR. Diccionario Lleno.\n");
    }
}

// Coloca BORRADO en el contenedor de X
void SUPRIME(char *x, DICCIONARIO A) {
    int index = localiza(x, A); 

    if (strcmp(A[index], x) == 0) {
        A[index] = BORRADO;   
    }
}

