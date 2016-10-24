#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <setjmp.h>
#include <3ds.h>

#include "main.h"
#include "util.h"
#include "pantalla.h"
#include "mem.h"

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

	consoleSelect(&topScreen);

	// Creamos un result para almacenar el estado del pulsador wifi

	Result ret = R_SUCCEEDED(ACU_GetWifiStatus(&wifi)) && wifi;

	// Comprobamos el pulsador. El programa no se pondra en marcha hasta que al menos una vez el pulsador wifi este encendido
	if(!ret){
		consoleSelect(&bottomScreen);

		bloqueo("El deslizador WIFI esta apagado", 0);
		
		borrarInferior();
	}


	// Selecionamos la pantalla superior
	consoleSelect(&topScreen);

	// Definimos un entero que almacene la opcion selecionada
	int opcion = 0;

	// Intenta abrir el archivo . Si no existe, lo crea.
	FILE *file;
	file = fopen(RUTA, "r");
	if (file == NULL){
		bloqueo("", 1);
	}
	fclose(file);	
	file = fopen(RUTA, "r");	
	unsigned char tmp[TAM_CRC] = {0};
	fread(tmp, sizeof(tmp), 1, file);

	// Hacemos una comprobacion CRC32. Si no pasa la comprobacion volvemos a crear el archivo
	if (CRC32(tmp) != CRC){
		bloqueo("", 1);
	}

	char ip[20] = {'\0'};
	getIP(ip);
	
	// A partir de aqui el archivo existe. Escribimos la IP de 3DSController.ini
	consoleSelect(&bottomScreen);	
	printf("\x1b[%d;%dHIP guardada: \x1b[31m %s \x1b[0m \x1b[0m", 2, 3, ip);

	// Definimos la lista del menu
	char* menu[lista] = {"Editar IP", "Editar y controlar PC", "Controlar PC", "Salir"};

	consoleSelect(&topScreen);
	// Dibujamos en la pantalla un mensaje en verde
	printf("\x1b[%d;%dH\x1b[31m---------\x1b[0m\x1b[32mProject: E S K Y \x1b[0m\x1b[31m---------\x1b[0m", 7, INDICE);

	// Refresca la pantalla
	actualiza(opcion, topScreen, menu, lista);

	// Volvemos a selecionar la pantalla superior
	consoleSelect(&topScreen);

	// Escribimos el mensaje
	printf("\x1b[%d;%dHPulsa A para elegir una opcion.", 12 + lista + INDICE, INDICE + 1);
	printf("\x1b[%d;%dHVersion de \x1b[31mpruebas.\x1b[0m", 12 + lista + INDICE + 2, INDICE + 1);


	// Inicializamos una variable para romper el bucle principal y parar la ejecucion	
	bool salir = false;

	// Bucle principal
	while(aptMainLoop()) {
		
		// Espera al refresco de pantalla
		gspWaitForVBlank();
		
		// Leemos las pulsaciones de entrada
		hidScanInput();
		
		// Comprobamos que siga el pulsador wifi activado
		
		ret = R_SUCCEEDED(ACU_GetWifiStatus(&wifi)) && wifi;
		
		if(!ret){
			consoleSelect(&bottomScreen);

			bloqueo("El deslizador WIFI esta apagado", 0);
			
			borrarInferior();
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
					printf("\x1b[%d;%dHMenu 1", 5, 5);
					break;
				}
			case 1 : {
					// Volvemos a selecionar la pantalla inferior					
					consoleSelect(&bottomScreen);
					printf("\x1b[%d;%dHMenu 2", 5, 5);
					break;
				}
			case 2 : {
					// Abrimos el controlador y cerramos esta aplicacion
					abrirControlador();
					break;
				}
			case 3 : {
					// Salimos
					salir = true;
					break;
				}
			}
		}
		
		// DEBUG SOLO
		
		if (hidKeysDown() & KEY_R){
			remove(RUTA);
			break;
		}
		
		// Si salir es true, salimos		
		if (salir == true) break;
		
		// Limpiamos los buffers graficos
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	// Volvemos a limpiar 
	gfxFlushBuffers();
	gfxSwapBuffers();

	// Cerramos la comunicacion AC
	acExit();

	// Cerramos la comunicacion con la SD
	sdmcExit();

	//Cerramos la comunicacion con la GPU
	gfxExit();

	return 0;
}