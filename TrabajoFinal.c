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
void MOSTRAR (DICCIONARIO);
void menu (DICCIONARIO);

//--------------------- MAIN
int main(){
    DICCIONARIO diccionario = CREAR();
    menu(diccionario);
    DestruirTablaHash(diccionario);
    return 0; 
}

//--------------------- FUNCIONES
// MENU
void menu (DICCIONARIO diccionario){
    int value;
    char palabra[12];
    printf("-----------------------\n");
    printf("(1) Agregar Elemento\n(2) Saber si esta Elemento\n(3) Eliminar Elemento\n(4) Mostrar Tabla\n(5) Terminar\nOpcion: ");
    scanf("%d", &value);
    switch (value){
    case 1:
        printf("Ingrese una cadena (10 MAX): ");
        scanf(" %s", palabra);
        INSERTA(palabra, diccionario);
        menu(diccionario);
        break;
    case 2:
        printf("Cual es su palabra? ");
        scanf(" %s", palabra);
        if(MIEMBRO(palabra, diccionario)){
            printf("Su palabra SI esta.\n");
        }else{
            printf("Su palabra NO esta.\n ");
        }
        menu(diccionario);
        break;
    case 3:
        printf("Cual es su palabra? ");
        scanf(" %s", palabra);
        SUPRIME(palabra, diccionario);
        menu(diccionario);
        break;
    case 4:
        MOSTRAR(diccionario);
        menu(diccionario);
        break;
    case 5:
        printf("Programa Terminado.");
        break;
    default:
        menu(diccionario);
        break;
    }
}
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

// Suma los valores numéricos de cada letra y luego toma el residuo de la división con NCasillas
int h(char *x) {
    int suma = 0;
    for (int i = 0; x[i]; i++) {
        suma += (int)x[i];
    }
    return suma % NCasillas;
}

// Busca el indice del contenedor (Primero x, despues vacio) y devuelve su direccion.
int localiza(char *x, DICCIONARIO A) {
    int inicial = h(x);
    int i = 0;

    while (i < NCasillas && A[(inicial + i) % NCasillas] != VACIO) {
        i++;
    }

    return (inicial + i) % NCasillas;
}

// Busca el indice del contenedor (Primero x, despues vacio o borrado) y devuelve su direccion.
int localiza1(char *x, DICCIONARIO A) {
    int inicial = h(x); 
    int i = 0;          

    while (i < NCasillas && A[(inicial + i) % NCasillas] != VACIO && A[(inicial + i) % NCasillas] != BORRADO) {
        i++;
    }

    return (inicial + i) % NCasillas;
}

// Devuelve 1 si x es miembro del diccionario, 0 en caso contrario
int MIEMBRO(char *x, DICCIONARIO A) {
    int inicial = h(x), i=0;
    while (i < NCasillas){
        if (A[(inicial + i) % NCasillas] == VACIO){
            return 0;
        }
        if (A[(inicial + i) % NCasillas] != NULL && strcmp(A[(inicial + i) % NCasillas], x) == 0){
            return 1;
        }
        
        i++;
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
void SUPRIME(char* x, DICCIONARIO A) {
    int siono = MIEMBRO(x, A);
    if(siono == 0){ 
        printf("La palabra no esta. \n");
    }
    int inicial = h(x), i=0;
    for(int i=0; i<NCasillas; i++){
        if (A[(inicial + i) % NCasillas] != NULL && strcmp(A[(inicial + i) % NCasillas], x) == 0){
            A[(inicial + i) % NCasillas] = BORRADO;
        }
        i++;
    }
}

void MOSTRAR(DICCIONARIO A){
    for(int i=0; i<25; i++){
        printf("%s \n", A[i]);
    }
}
