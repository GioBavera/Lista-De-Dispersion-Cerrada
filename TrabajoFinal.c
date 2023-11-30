#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCasillas 25
#define VACIO NULL

static char *BORRADO = "**********"; // 10 asteriscos

typedef char **DICCIONARIO;


DICCIONARIO CREAR ();  // aaa
void DestruirTablaHash (DICCIONARIO); // aaa
int h (char*); // aaa
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
  if (A == NULL) {
    printf("Error al reservar memoria\n");
  }
  for (int i = 0; i < NCasillas; i++) {
    A[i] = VACIO;
  }
  return A;
}

// Libera la memoria del diccionario
void DestruirTablaHash(DICCIONARIO A) {
  for (int i = 0; i < NCasillas; i++) {
    if (A[i] != VACIO && A[i] != BORRADO) {
      free(A[i]);
    }
  }
  free(A);
}

// Calcula el valor de dispersión de una cadena de caracteres
// Suma los valores numéricos de cada letra y luego toma el residuo de la división con NCasillas[^11^][11]
int h(char *x) {
  int suma = 0;
  for (int i = 0; i < 10; i++) {
    suma += (int)x[i];
  }
  return suma % NCasillas;
}

// Busca el índice del contenedor donde se encuentra x o un contenedor vacío
// Se detiene si encuentra x o un contenedor vacío, o si revisa toda la tabla[^14^][14]
int localiza(char *x, DICCIONARIO A) {
  int inicial = h(x); // guarda el valor de dispersión de x
  int i = 0;          // cuenta el número de contenedores examinados
  while (i < NCasillas && A[(inicial + i) % NCasillas] != x &&
         A[(inicial + i) % NCasillas] != VACIO) {
    i++;
  }
  return (inicial + i) % NCasillas;
}

// Como localiza, pero también se detiene en una entrada con BORRADO[^15^][15]
int localiza1(char *x, DICCIONARIO A) {
  int inicial = h(x);
  int i = 0;
  while (i < NCasillas && A[(inicial + i) % NCasillas] != x &&
         A[(inicial + i) % NCasillas] != VACIO &&
         A[(inicial + i) % NCasillas] != BORRADO) {
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
  if (A[localiza(x, A)] == x) {
    return; // x ya está en A
  }
  int contenedor = localiza1(x, A);
  if (A[contenedor] == VACIO || A[contenedor] == BORRADO) {
    A[contenedor] = (char *)malloc(11 * sizeof(char)); // reserva espacio para 10 caracteres y el '\0'
    if (A[contenedor] == NULL) {
      printf("Error al reservar memoria\n");
      exit(1);
    }
    strcpy(A[contenedor], x); // copia x en el contenedor
  } else {
    printf("INSERTA falló, la tabla está llena\n");
  }
}

// Suprime x del diccionario si está
// Coloca BORRADO en el contenedor que contiene x
void SUPRIME(char *x, DICCIONARIO A) {
  int contenedor = localiza(x, A);
  if (A[contenedor] == x) {
    free(A[contenedor]);       // libera el espacio de x
    A[contenedor] = BORRADO;   // marca el contenedor como borrado
  }
}