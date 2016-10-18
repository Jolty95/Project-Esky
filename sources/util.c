#include <stdio.h>
#include <malloc.h>
#include <3ds.h>

#include "util.h"
#include "mem.h"
#include "pantalla.h"
#include <string.h>

/** 3DSController.ini */
unsigned char OFFSET[28] = {0x49, 0x50, 0x3A, 0x20, 0x31, 0x39, 0x32, 0x2E, 0x31, 0x36, 0x38, 0x2E, 0x31, 0x2E, 0x39, 0x39,
							0x0D, 0x0A, 0x50, 0x6F, 0x72, 0x74, 0x3A, 0x20, 0x38, 0x38, 0x38, 0x39};

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
	
	FILE *archivo = fopen(RUTA, "wb");
	fwrite(OFFSET,sizeof(OFFSET),1,archivo);
	fclose(archivo);	

}

char getIP()
{
	FILE *archivo = fopen(RUTA, "rb");
	fread()
}