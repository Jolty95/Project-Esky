#include <stdio.h>
#include <malloc.h>
#include <3ds.h>

#include "util.h"
#include "mem.h"
#include "pantalla.h"
#include <string.h>

void actualiza(int opcion, PrintConsole topScreen, char *menu[], int n) {
	consoleSelect(&topScreen);
	for (int i = 0; i < n; i++) {
		if (i == opcion) 
		printf("\x1b[%d;%dH> %s", 12 + i, INDICE + 2, menu[i]);
		else 
		printf("\x1b[%d;%dH  %s", 12 + i, INDICE + 2, menu[i]);
	}
}

void bloqueo(char *mensaje, int tipo) {

	/**
	Case 0:
		-Deslizador wifi apagado
	Case 1:
		-Archivo 3DSController.ini no encontrado
	Case -1:
		-Excepcion no controlada
*/

	switch(tipo){
	case 0:{
			u32 wifi = 0;

			while (aptMainLoop()) {
				hidScanInput();

				borrarInferior();
				
				if (R_SUCCEEDED(ACU_GetWifiStatus(&wifi)) && wifi){
					borrarInferior();
					break;
				}
				
				printf("\x1b[%d;%dH %s", 10, 1, mensaje);			
				
				gfxFlushBuffers();
				gspWaitForVBlank();
				gfxSwapBuffers();
			}
			break;
		}
	case 1:{
			
			borrarInferior();
			
			creaArchivo();
			
			gfxFlushBuffers();
			gspWaitForVBlank();
			gfxSwapBuffers();
			break;
		}
	case -1:{
			while (aptMainLoop()) {
				hidScanInput();

				borrarInferior();
				
				
				printf("\x1b[%d;%dH %s", 10, 1, mensaje);			
				
				gfxFlushBuffers();
				gspWaitForVBlank();
				gfxSwapBuffers();
			}
			break;
		
		}
	}
	
}

void creaArchivo(void)
{
	static char buf[100];		
	static char string[100];
	
	
	for (int i = 0; i < 100; i++) string[i] = 0;
	char x[100] = "IP: 192.168.1.1\nPort: 8889";
	
	for (int i = 0; i < 100; i++) string[i] = x[i];

	
	memcpy(buf, string, 100);
	string[99] = '\0';
	
	FILE *set = fopen(RUTA, "wb");
	fwrite(buf, 1, 19, set);
	fclose(set);	
}