#ifndef __STM8L15x_IT_H
#define __STM8L15x_IT_H

#include "stm8l15x.h"

// Display resolution
#define EPD_WIDTH 122
#define EPD_HEIGHT 250
#define BUFFER_SIZE 4000

#define EPD_FULL 0
#define EPD_PART 1

void Epd_Init(const uint8_t full_refresh);
void Epd_Clear(void);
void Epd_Display(const uint8_t* frame_buffer);
void Epd_DisplayPartBaseImage(const uint8_t* frame_buffer);
void Epd_DisplayPart(const uint8_t* frame_buffer);
void Epd_ClearPart(void);
void Epd_Sleep(void);

void Epd_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
void Epd_SetCursor(uint16_t Xstart, uint16_t Ystart);

#endif