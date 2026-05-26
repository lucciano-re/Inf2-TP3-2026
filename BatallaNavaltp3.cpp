#include <stdio.h>
#include <string.h> // para memset
#include <stdlib.h> // para system("command"); en este caso --> cls = borrar la pantalla
#include <unistd.h> // para sleep(seconds);
#include <time.h> // para inicializar el generador de numeros aleatorios

#pragma pack (1) // para que haga la alineacion de memoria de a 1 byte
struct fecha {
int anio;
int mes;
int dia;
unsigned char nombre_mes[15];
unsigned char dia_semana[10];
};

/*************** funciones de "soporte" *********************/
void borrar_pantalla(void) {
#ifdef Linux // si puse un #define Linux al principio, se va a ejecutar esta instruccion
system("clear");
#else // si no esta la sentencia #define Linux, se va a ejecutar esta instruccion
system("cls"); // esto solo es valido para windows
#endif
return;
}

void borrar_teclado(void) {
fseek(stdin, 0, SEEK_END); // hago que el buffer (memoria) del teclado "avance" hasta el final
return;
}

void mostrar (struct fecha *local) {
  printf("Fecha: %s %d de %s de %d\n",
  local->dia_semana,
  local->dia,
  local->nombre_mes,
  local->anio);
  printf("\n");
}

int main(void) {
struct fecha Fecha_Final_Copa_Libertadores;

struct fecha Copia_Fecha_Final_Copa_Libertadores;

printf("Tamaño = %ld bytes.\n", sizeof(Fecha_Final_Copa_Libertadores));
printf("Ingrese año: ");
scanf("%d", &Fecha_Final_Copa_Libertadores.anio);
printf("Ingrese mes: ");
scanf("%d", &Fecha_Final_Copa_Libertadores.mes);
printf("Ingrese mes (en letras): ");
scanf("%s", Fecha_Final_Copa_Libertadores.nombre_mes);
borrar_teclado();  
printf("Ingrese dia: ");
scanf("%d", &Fecha_Final_Copa_Libertadores.dia);
borrar_teclado();
printf("Ingrese dia de la semana (en letras): ");
scanf("%s", Fecha_Final_Copa_Libertadores.dia_semana);
borrar_teclado();
printf("\n");
printf("\n");
printf("Datos de Fecha Final Copa Libertadores:\n");
printf("---------------------------------------\n");
mostrar (&Fecha_Final_Copa_Libertadores);
memcpy(&Copia_Fecha_Final_Copa_Libertadores, &Fecha_Final_Copa_Libertadores,
sizeof(Copia_Fecha_Final_Copa_Libertadores));
printf("Datos de Copia Fecha Final Copa Libertadores:\n");
printf("---------------------------------------------\n");
mostrar(&Copia_Fecha_Final_Copa_Libertadores)
return 0;
}
