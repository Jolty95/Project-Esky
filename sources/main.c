#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <setjmp.h>
#include <3ds.h>

//#include "drawing.h"
//#include "../u/util.h"

// Numero de items en el menu
#define lista 4

// Numero de columnas de la pantalla superior
#define COLUMNAS_SUP 50
// Numero de columnas de la pantalla inferior
#define COLUMNAS_INF 40
// Numero donde empieza el texto
#define INDICE 5

inline void clearScreen(void) {
	u8 *frame = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	memset(frame, 0, 320 * 240 * 3);
}

// Refresca la pantalla superior
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

	if (tipo == 0) {
		
		u32 wifi = 0;

		while (aptMainLoop()) {
			hidScanInput();

			clearScreen();
			
			if (R_SUCCEEDED(ACU_GetWifiStatus(&wifi)) && wifi){
				clearScreen();
				printf("\x1b[%d;%dH %s", 10, 1, "Reiniciando servicios...");
				break;
			}
			
			printf("\x1b[%d;%dH %s", 10, 1, mensaje);
			
			
			gfxFlushBuffers();
			gspWaitForVBlank();
			gfxSwapBuffers();
		}
	}
	else {
		while (aptMainLoop()) {
			hidScanInput();

			clearScreen();
			printf("\x1b[%d;%dH%s", 10, 1, mensaje);

			gfxFlushBuffers();
			gspWaitForVBlank();
			gfxSwapBuffers();
		}
	}
}

// MAIN SIEMPRE DEBAJO

int main() {
	
	// Iniciamos la grafica
	gfxInitDefault(); 
	
	// Iniciamos la SD
//	sdmcInit();
	
	// Iniciamos los servicios de Internet
	acInit();
	
	// Definimos las pantallas
	PrintConsole topScreen, bottomScreen;
		
	// Encendemos las pantallas
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	// Guardamos en una variable el estado del pulsador wifi
	u32 wifi = 0;
	
	// Comprobamos el pulsador. El programa NO se pondra en marcha hasta que al menos una vez el pulsador wifi este encendido
	consoleSelect(&topScreen);

	// Creamos un result para almacenar el estado del pulsador wifi
	
	Result ret = R_SUCCEEDED(ACU_GetWifiStatus(&wifi)) && wifi;
	
	if(!ret){
		printf("\x1b[%d;%dEstado wifi:%lx\x1b[0m", 10, 10, wifi);

		consoleSelect(&bottomScreen);

		bloqueo("El deslizador WIFI esta apagado", 0);
	}
	
	clearScreen();
	
	// Selecionamos la pantalla superior
	consoleSelect(&topScreen);
	
	// Definimos un entero que almacene la opcion selecionada
	int opcion = 0;
	
	// Definimos la lista del menu
	char* menu[lista] = {"Editar IP", "Editar y controlar PC", "Controlar PC", "Salir"};
	
	// Dibujamos en la pantalla un mensaje en verde
	printf("\x1b[%d;%dH\x1b[31m---------\x1b[0m\x1b[32mProject: E S K Y \x1b[0m\x1b[31m---------\x1b[0m", 8, INDICE);
	
	// Refresca la pantalla
	actualiza(opcion, topScreen, menu, lista);
	
	// Volvemos a selecionar la pantalla superior
	consoleSelect(&topScreen);
	
	// Escribimos la IP de la consola y la IP de 3DSController.initgraph
//	prinf("\xib[%d;%dHIP Consola: \x1b[30%d \x1b[0m   -  IP guardada: \x1b[34%d \x1b[0m", 12 + lista + 2, INDICE + 1, IP, "test")
	
	// Escribimos el mensaje
	printf("\x1b[%d;%dHPulsa A para elegir una opcion.", 12 + lista + INDICE, INDICE + 1);
	printf("\x1b[%d;%dHVersion de \x1b[31mpruebas.\x1b[0m", 12 + lista + INDICE + 2, INDICE + 1);

	
	
	// Bucle principal
	while(aptMainLoop()) {
		
		// Espera al refresco de pantalla
		gspWaitForVBlank();
		
		// Leemos las pulsaciones de entrada
		hidScanInput();
		
		// Comprobamos que siga el pulsador wifi activado
		
		ret = R_SUCCEEDED(ACU_GetWifiStatus(&wifi)) && wifi;
	
		if(!ret){
			printf("\x1b[%d;%dEstado wifi:%lx\x1b[0m", 1, 1, wifi);

			consoleSelect(&bottomScreen);

			bloqueo("El deslizador WIFI esta apagado", 0);
		}
		
		
		// Si pulsas arriba
		if (hidKeysDown() & KEY_UP) {
			if (opcion == 0) opcion = lista - 1;
			else if (opcion > 0) opcion--;		
			
			actualiza(opcion, topScreen, menu, lista);
		}
		
		// Si pulsas abajo
		if (hidKeysDown() & KEY_DOWN) {
			if (opcion == lista - 1) opcion = 0;
			else if (opcion < lista - 1) opcion++;
			
			actualiza(opcion, topScreen, menu, lista);
		}

		// Si pulsas A
		if (hidKeysDown() & KEY_A) {
			switch (opcion) {
				case 0 : {					
					// Volvemos a selecionar la pantalla inferior					
					consoleSelect(&bottomScreen);
					printf("\x1b[%d;%dHHola E S K Y!!!!", 5, 5);
					break;
				}
				case 1 : {
					// Volvemos a selecionar la pantalla inferior					
					consoleSelect(&bottomScreen);
					printf("\x1b[%d;%dHHola umb....umbumbumb", 5, 5);
					break;
				}
				case 3 : {
					// Volvemos a selecionar la pantalla inferior					
					consoleSelect(&bottomScreen);
					printf("\x1b[%d;%dHHola umb....umbumbumb", 5, 5);
					break;
				}
				case 4 : {
					// Volvemos a selecionar la pantalla inferior					
					consoleSelect(&bottomScreen);
					printf("\x1b[%d;%dHHola umb....umbumbumb", 5, 5);
					break;
				}
			}
		}
		
		// Limpiamos los buffers graficos
		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	
	// Cerramos la comunicacion con la SD
	sdmcExit();
	
	//Cerramos la comunicacion con la GPU
	gfxExit();
	
	return 0;
}
