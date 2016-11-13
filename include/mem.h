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
0x0D, 0x0A, 0x50, 0x6F, 0x72, 0x74, 0x3A, 0x20, 0x38, 0x38, 0x38, 0x39, 0x0D, 0x0A, 0x0D, 0x0A, 
0x43, 0x52, 0x43, 0x3A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xFF, 0xFF};
								|	  |	    |     |     |	  |		|	  |			****  **** ---> Suma HASH
							  ****  ****  ****  ****  ****  ****  ****  ****  --------------------> HASH CRC32													

 IP[2] = {0x0E, 0x0F}
 
*/

// CRC archivo valido TODO
#define CRC 0x7413AE37
#define TAM_CRC 37
#define TAM_OFF 48

/** Controlador */

#define BUF0 0x300
#define BUF1 0x20
#define TITLE 0x000400000F800100LL

#endif