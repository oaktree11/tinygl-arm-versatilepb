#include "lcd.h"

#include <GL/gl.h> 
#include <pl110.h>
#include <zbuffer.h>

#include "examples/ui.h"
int fb1[1*1024*1024];
int fb2[1*1024*1024];/*
*(volatile unsigned int *)(0x1000001c) = 0x2C77;        // LCDCLK SYS_OSCCLK
  *(volatile unsigned int *)(0x10120000) = 0x3F1F3F9C;    // time0
  *(volatile unsigned int *)(0x10120004) = 0x090B61DF;    // time1
  *(volatile unsigned int *)(0x10120008) = 0x067F1800;    // time2
  *(volatile unsigned int *)(0x10120010) = fb;//(1*1024*1024); // panelBaseAddress
  *(volatile unsigned int *)(0x10120018) = 0x82B|PL110_CR_EN|PL110_CR_PWR;   */

void init_lcd(void)
{
	PFN		fn;
	PL110MMIO	*plio;
	int		x, y;
	uint16		volatile *fb;
 
	*(volatile unsigned int *)(0x1000001c) = 0x2C77;
	plio = (PL110MMIO*)PL110_IOBASE;
 
	/* 640x480 pixels */
//	plio->tim0 = 0x3f1f3f9c;
	//plio->tim1 = 0x080b61df;
//	plio->upbase = fb1;//0x40000000;

	/* 16-bit color */
	//plio->control = 0b1100000101001;
	*(volatile unsigned int *)(0x1000001c) = 0x2C77;        // LCDCLK SYS_OSCCLK
	  *(volatile unsigned int *)(0x10120000) = 0x3F1F3F9C;    // time0
	  *(volatile unsigned int *)(0x10120004) = 0x090B61DF;    // time1
	  *(volatile unsigned int *)(0x10120008) = 0x067F1800;    // time2
	  *(volatile unsigned int *)(0x10120010) = fb1;//(1*1024*1024); // panelBaseAddress
	  *(volatile unsigned int *)(0x10120018) = 0x82B|PL110_CR_EN|PL110_CR_PWR;
	fb = (uint16*) fb1;//0x40000000;

	/* test screen */
	for (x = 0; x < (160 * 640); ++x)
		fb[x] = 0b0000000000111110; 
	for (x = (160 * 640); x < (320 * 640); ++x)
		fb[x] = 0b0000011111000000; 
	for (x = (320 * 640); x < (480 * 640); ++x)
		fb[x] = 0b1111100000000000; 
 }

void swapBuffers(void)
{
	// This performs the hardware double buffering and is called every frame
	PL110MMIO *plio;
	GLContext *gl_context;
    pl110_Context *ctx;

	gl_context = gl_get_context();
	ctx = (pl110_Context *) gl_context->opaque;

	plio = (PL110MMIO*) PL110_IOBASE;
	if(ctx->gl_context->zb->pbuf == (unsigned short*) fb1){//0x40000000) {
		plio->upbase = fb1;//0x40000000;
		ctx->gl_context->zb->pbuf = (unsigned short*) fb2;//0x40400000;
	}
	else {
		plio->upbase = fb2;//0x40400000;
		ctx->gl_context->zb->pbuf = (unsigned short*) fb1;////0x40000000;
	}
}

int ui_loop()
{
	pl110_Context *ctx = pl110_CreateContext();
	pl110_MakeCurrent(ctx);
	init();

	// This is for the hardware double buffering
	ctx->gl_context->zb->pbuf = (unsigned short*)fb2; //0x40400000;

	reshape(640,480);

	int done=0;
	while(!done)
	{
	  idle();
	}
	return 0;
}

