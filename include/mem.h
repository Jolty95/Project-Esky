#ifndef MEMORY_H
#define MEMORY_H

/**Variables*/

// Numero donde empieza el texto
#define INDICE 6
// Numero de items en el menu
#define lista 4
// Numero de columnas de la pantalla superior
#define COLUMNAS_SUP 50
// Numero de columnas de la pantalla inferior
#define COLUMNAS_INF 40
// Ruta del archivo
#define RUTA "/3DSController.ini"

/** Offset del archivo 
																					 ****  ****  <--- IP 192.168.1.XX
{0x49, 0x50, 0x3A, 0x20, 0x31, 0x39, 0x32, 0x2E, 0x31, 0x36, 0x38, 0x2E, 0x31, 0x2E, 0x39, 0x39,
 0x0D, 0x0A, 0x50, 0x6F, 0x72, 0x74, 0x3A, 0x20, 0x38, 0x38, 0x38, 0x39};

 IP[2] = {0x0E, 0x0F}
 
*/

// CRC archivo valido
#define CRC 0xec951452l

/** Controlador */

#define BUF1 0x300
#define BUF2 0x20
#define TITLE 0x00040000000F0FC200

#endif