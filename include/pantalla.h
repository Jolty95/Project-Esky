#ifndef PANTALLA_H
#define PANTALLA_H

#include <3ds.h>

void borrarPantallas(void);
void borrarInferior(void);
void borrarSuperior(void);
void clearScreen(u8* screen,gfxScreen_t screenPos);
void drawPixel(int x, int y, char r, char g, char b, u8* screen);
#endif