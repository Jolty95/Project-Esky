#ifndef MAIN_H
#define MAIN_H

// Metodo principal
int main();

// Vuelve a pintar en pantalla el menu
void actualiza(int opcion, PrintConsole topScreen, char *menu[], int n);

// Bloquea los bucles para mostrar un mensaje de error
void bloqueo(char *mensaje, int tipo);

#endif