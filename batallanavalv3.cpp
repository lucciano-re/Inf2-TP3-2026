#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct record {
    char nombre[50];
    int disparos;
};

struct disparo {
    int fila;
    int columna;
};

struct EstadoJuego {
    char *tablero;               // Tablero dinámico
    int n;
    int barcoF;
    int barcoC;
    int opcion;
    int tiros;
    int gano;
    char nombreActual[50];
    struct disparo *historial;
    struct record ranking;
};

void inicializarTablero(struct EstadoJuego *juego);
void mostrarTablero(struct EstadoJuego *juego);
int realizarDisparo(struct EstadoJuego *juego, int f, int c);

int main() {
  struct EstadoJuego mega;

  strcpy(mega.ranking.nombre, "Lucho");
  mega.ranking.disparos = 9999999;

  srand(time(NULL));

  do {
    printf("\n=== TP3 INFORMATICA II ===\n");

    if (mega.ranking.disparos < 9999998) {
        printf("El cadete del mes: %s con %d tiros\n", mega.ranking.nombre, mega.ranking.disparos);
    }
  
    printf("1. Iniciar Combate\n2. Salir\nSeleccione: ");
    scanf("%d", &mega.opcion);
  
    if (mega.opcion == 1) {
      printf("Tamano del tablero: ");
      scanf("%d", &mega.n);

      inicializarTablero(&mega);
      
      printf("Cual es tu nombre muchacho: ");
      scanf("%s", mega.nombreActual);
      
      while (!mega.gano) {
        mostrarTablero(&mega);
        printf("Disparo actual: %d\n", mega.tiros + 1);
          
        int f_actual, c_actual;
        printf("Coordenadas:\nFila: ");
        scanf("%d", &f_actual);
        printf("Columna: ");
        scanf("%d", &c_actual);
        
        int res = realizarDisparo(&mega, f_actual, c_actual);
        
        if (res != -1) {
          mega.tiros++;
        
          mega.historial = (struct disparo *)realloc(mega.historial, mega.tiros * sizeof(struct disparo));
        
          if (mega.historial == NULL) {
            printf("Error fatal: No hay memoria suficiente.\n");
            return 1;
          }
          
          mega.historial[mega.tiros - 1].fila = f_actual;
          mega.historial[mega.tiros - 1].columna = c_actual;
          
          if (res == 1) mega.gano = 1; // Le dio al barco
        }
      }
      
      mostrarTablero(&mega);
      
      if (mega.gano) {
        printf("\nTreinta anos navegando he visto ese tiro exactamente... una vez. Y era yo. Asi que no te pongas muy comodo, entendiste %s?\nLe diste en %d canonazos.\n", mega.nombreActual, mega.tiros);
      
        if (mega.tiros < mega.ranking.disparos) {
          printf("\n¡NUEVO RECORD!\nComo quieres ser recordado muchacho?: ");
          scanf("%s", mega.ranking.nombre);
          mega.ranking.disparos = mega.tiros;
        }
      }
    
      printf("\n--- SECUENCIA DE DISPAROS ---\n");
      for (int i = 0; i < mega.tiros; i++) {
      printf("Tiro %d: Fila %d, Columna %d\n", i + 1, mega.historial[i].fila, mega.historial[i].columna);
      }
      
      free(mega.tablero);
      free(mega.historial);
    }
  }
  while (mega.opcion != 2);

  return 0;
}

void inicializarTablero(struct EstadoJuego *juego) {

    juego->tablero = (char *)malloc(juego->n * juego->n * sizeof(char));
    juego->tiros = 0;
    juego->gano = 0;
    juego->historial = NULL; // Vital para que el primer realloc funcione como malloc
    
    // Llenamos de '.' usando aritmética de punteros aplanada
    for (int i = 0; i < (juego->n * juego->n); i++) {
        juego->tablero[i] = '.';
    }
    
    // Posicionamos el barco
    juego->barcoF = rand() % juego->n;
    juego->barcoC = rand() % juego->n;
}

void mostrarTablero(struct EstadoJuego *juego) {
    printf("\n    ");
    for (int i = 0; i < juego->n; i++) printf("%2d ", i);
    printf("\n");
    
    for (int i = 0; i < juego->n; i++) {
        printf("%2d |", i);
        for (int j = 0; j < juego->n; j++) {
            // Aritmética para arreglo 1D: (fila * n) + columna
            printf(" %c ", juego->tablero[(i * juego->n) + j]);
        }
        printf("\n");
    }
}

int realizarDisparo(struct EstadoJuego *juego, int f, int c) {
    // Validar límites
    if (f < 0 || f >= juego->n || c < 0 || c >= juego->n) {
        printf("\nTecnicamente... no fallaste. Para fallar, la bala tiene que haber tenido alguna posibilidad de dar. Lo tuyo fue otra cosa. Lo tuyo fue... arte.\n!\n");
        return -1; // -1 indica disparo inválido
    }
    
    // Validar si ya disparó ahí
    if (juego->tablero[(f * juego->n) + c] != '.') {
        printf("\nYa has disparado ahi, y ya has fallado ahi! Te perdonare la bala por esta vez recluta.\n");
        return -1; 
    }
    
    // Comprobar si acertó
    if (f == juego->barcoF && c == juego->barcoC) {
        juego->tablero[(f * juego->n) + c] = 'B';
        return 1; // 1 indica que ganó
    } else {
        juego->tablero[(f * juego->n) + c] = 'A';
        printf("\nAGUA!\n");
        return 0; // 0 indica que falló, pero el disparo cuenta
    }
}
