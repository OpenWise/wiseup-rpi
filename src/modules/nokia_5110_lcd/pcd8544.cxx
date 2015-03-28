/*
 * Author: Yevgeniy Kiveisha <yevgeniy.kiveisha@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 */
 
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "pcd8544.h"
#include "gfx.h"

uint8_t pcd8544_buffer[LCDWIDTH * LCDHEIGHT / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFF, 0xFC, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x87, 0x8F, 0x9F, 0x9F, 0xFF, 0xFF, 0xFF,
0xC1, 0xC0, 0xE0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE,
0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0xC0, 0xE0, 0xF1, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x0F, 0x87,
0xE7, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0x3F, 0xF9, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFD, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x7E, 0x3F, 0x3F, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFC, 0xF0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x7F, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

PCD8544::PCD8544 (spi_context& spi, uint8_t cs, uint8_t dc, uint8_t rst) : GFX (LCDWIDTH, LCDHEIGHT, pcd8544_buffer, font) {
	result_t error = SUCCESS;

	m_spi = spi;
	
	m_csCtx = gpio_init (cs);
    if (m_csCtx == NULL) {
        fprintf (stderr, "Are you sure that pin%d you requested is valid on your platform?", cs);
        exit (1);
    }
	
	m_dcCtx = gpio_init (dc);
    if (m_dcCtx == NULL) {
        fprintf (stderr, "Are you sure that pin%d you requested is valid on your platform?", dc);
        exit (1);
    }
	
	m_rstCtx = gpio_init (rst);
    if (m_rstCtx == NULL) {
        fprintf (stderr, "Are you sure that pin%d you requested is valid on your platform?", rst);
        exit (1);
    }
	
	error = gpio_dir (m_csCtx, GPIO_OUT);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
	
	error = gpio_dir (m_dcCtx, GPIO_OUT);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
	
	error = gpio_dir (m_rstCtx, GPIO_OUT);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
	
	init ();
}

PCD8544::PCD8544 (uint8_t cs, uint8_t dc, uint8_t rst) : GFX (LCDWIDTH, LCDHEIGHT, pcd8544_buffer, font) {
	result_t error = SUCCESS;
	
	m_spi = spi_init (0, 0);
	// spi_mode (m_spi, 0);
	// spi_lsbmode (m_spi, 0);
	
	m_csCtx = gpio_init (cs);
    if (m_csCtx == NULL) {
        fprintf (stderr, "Are you sure that pin%d you requested is valid on your platform?", cs);
        exit (1);
    }
	
	m_dcCtx = gpio_init (dc);
    if (m_dcCtx == NULL) {
        fprintf (stderr, "Are you sure that pin%d you requested is valid on your platform?", dc);
        exit (1);
    }
	
	m_rstCtx = gpio_init (rst);
    if (m_rstCtx == NULL) {
        fprintf (stderr, "Are you sure that pin%d you requested is valid on your platform?", rst);
        exit (1);
    }
	
	error = gpio_dir (m_csCtx, GPIO_OUT);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
	
	error = gpio_dir (m_dcCtx, GPIO_OUT);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
	
	error = gpio_dir (m_rstCtx, GPIO_OUT);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
	
	init ();
}

PCD8544::~PCD8544 () {
	result_t error = SUCCESS;
	
    error = spi_stop(m_spi);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
    error = gpio_close (m_csCtx);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
    error = gpio_close (m_dcCtx);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
	error = gpio_close (m_rstCtx);
    if (error != SUCCESS) {
        fprintf (stderr, "Error #%d", error);
    }
}

void
PCD8544::init () {
	gpio_write(m_rstCtx, LOW);
    usleep (500000);
    gpio_write(m_rstCtx, HIGH);
	
	m_contrast 	= 40;
	m_bias 		= 0x04;
	m_rotation	= 0;
	
	setTextColor(WHITE, BLACK);
	
	powerUp ();

	// Push out pcd8544_buffer to the Display (will show the AFI logo)
	refresh();
}

void
PCD8544::powerUp () {
	// get into the EXTENDED mode!
	cmd (PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION );

	// LCD bias select (4 is optimal?)
	cmd (PCD8544_SETBIAS | m_bias);

	// set contrast
	cmd (PCD8544_SETVOP | m_contrast); // Experimentally determined

	// normal mode
	cmd (PCD8544_FUNCTIONSET);

	// Set display to Normal
	cmd (PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

void
PCD8544::powerDown () {
	cmd (PCD8544_POWERDOWN | PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
}

void
PCD8544::setContrast (uint8_t contrast) {
	if (m_contrast > 0x7f) {
		m_contrast = 0x7f;
	} else {
		m_contrast = contrast;
	}
	
	cmd (PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION );
	cmd (PCD8544_SETVOP | contrast); 
	cmd (PCD8544_FUNCTIONSET);
}

void
PCD8544::drawPixel (int16_t x, int16_t y, uint16_t color) {
	if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT)) {
		return;
	}

	int16_t temp;
	switch(m_rotation){
	case 1:
		temp = x;
		x = y;
		y =  LCDHEIGHT - 1 - temp;
		break;
	case 2:
		x = LCDWIDTH - 1 - x;
		y = LCDHEIGHT - 1 - y;
		break;
	case 3:
		temp = x;
		x = LCDWIDTH - 1 - y;
		y = temp;
		break;
	}

	// x is which column
	if (color) {
		pcd8544_buffer[x+ (y/8)*LCDWIDTH] |= (1 << (y%8)); 
	} else {
		pcd8544_buffer[x+ (y/8)*LCDWIDTH] &= ~(1 << (y%8));
	}
}

void
PCD8544::setAddrWindow (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {

}

void
PCD8544::refresh () {
	uint8_t col, maxCol;

	for (int i = 0; i < 6; i++) {
		cmd (PCD8544_SETYADDR | i);
		
		col 	= 0;
		maxCol 	= LCDWIDTH-1;
		
		cmd (PCD8544_SETXADDR | col);
		
		gpio_write(m_dcCtx, HIGH);
		gpio_write(m_csCtx, LOW);
		
		for(; col <= maxCol; col++) {
			spi_write (m_spi, pcd8544_buffer[(LCDWIDTH*i)+col]);
		}
		
		gpio_write(m_csCtx, HIGH);
	}
	
	cmd (PCD8544_SETYADDR);
}

void
PCD8544::clearscr () {
	memset (pcd8544_buffer, 0, LCDWIDTH*LCDHEIGHT/8);
	refresh ();
}

void
PCD8544::drawFromBuffer (uint8_t * rawData) {
	memcpy (pcd8544_buffer, rawData, LCDWIDTH * LCDHEIGHT / 8);
	refresh ();
}

void
PCD8544::cmd (uint8_t data) {
	gpio_write (m_dcCtx, LOW);
	gpio_write (m_csCtx, LOW);
	spi_write (m_spi, data);
	gpio_write (m_csCtx, HIGH);	
}

void
PCD8544::data (uint8_t data) {
	gpio_write (m_dcCtx, HIGH);
	gpio_write (m_csCtx, LOW);
	spi_write (m_spi, data);
	gpio_write (m_csCtx, HIGH);
}
