#ifdef _WINDOWS

#include "LiquidCrystalStub.h"


LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	(void) rs;
	(void) en;
	(void) d4;
	(void) d5;
	(void) d6;
	(void) d7;
}


LiquidCrystal::~LiquidCrystal()
{

}


void LiquidCrystal::begin(int nrOfColumns, int nrOfRows)
{
	(void) nrOfColumns;
	(void) nrOfRows;
}


void LiquidCrystal::print(char ch)
{
	(void) ch;
}


void LiquidCrystal::setCursor(int x, int y)
{
	(void) x;
	(void) y;
}


void LiquidCrystal::autoscroll()
{

}


void LiquidCrystal::noAutoscroll()
{

}


void LiquidCrystal::clear()
{

}



#endif // _WINDOWS