#ifndef UTIL_H
#define UTIL_H

// Vuelve a pintar en pantalla el menu
void actualiza(int opcion, PrintConsole topScreen, char *menu[], int n);

// Bloquea los bucles para mostrar un mensaje de error
void bloqueo(char *mensaje, int tipo);

// Crea el archivo de configuracion
void creaArchivo(void);
#endif