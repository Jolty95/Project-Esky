#include "pantalla.h"

#include <stdio.h>
#include <3ds.h>


u8* screenBottom = 0;
u8* screenTopLeft = 0;
u8* screenTopRight = 0;

void limpiar(u8* screen,gfxScreen_t screenPos)
{
	int width;
	int height=240;

	switch(screenPos){
	case GFX_BOTTOM:
		width=320;
		break;
	default:
		width=400;
		break;
	}

	int i, j;
	for(i=1;i<width;i++)
	{
		for(j=1;j<height;j++)
		{
			drawPixel(i,j,0x00,0x00,0x00,screen);			
		}
	}
}

void drawPixel(int x, int y, char r, char g, char b, u8* screen)
{
	int height=240;
	
	u32 v=(height-1-y+x*height)*3;
	screen[v]=b;
	screen[v+1]=g;
	screen[v+2]=r;
}

void borrarSuperior()
{
	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	limpiar(screenTopLeft, GFX_LEFT);
	limpiar(screenTopRight, GFX_LEFT);
}

void borrarInferior()
{
	screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL);
	limpiar(screenBottom, GFX_BOTTOM);
}
void borrarPantallas()
{
	borrarSuperior();
	borrarInferior();
}