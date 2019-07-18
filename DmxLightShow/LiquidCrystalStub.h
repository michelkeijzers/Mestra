#pragma once


#include "MestraTypes.h"


class LiquidCrystal
{
public:
	LiquidCrystal(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	~LiquidCrystal();

	void begin(int nrOfColumns, int nrOfRows);
	void print(char ch);
	void setCursor(int x, int y);
	void autoscroll();
	void noAutoscroll();
	void clear();
};
