#ifndef UTIL_H
#define UTIL_H

// Vuelve a pintar en pantalla el menu
void actualiza(int opcion, PrintConsole topScreen, char *menu[], int n);

// Bloquea los bucles para mostrar un mensaje de error
void bloqueo(char *mensaje, int tipo);

// Crea el archivo de configuracion
void creaArchivo(void);

// Lee la ip del archivo de configuracion
void getIP(char* ip);

// Hace un check CRC32
unsigned long CRC32(unsigned char *mensaje) {

#endif