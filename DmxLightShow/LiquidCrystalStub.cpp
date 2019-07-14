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


#endif // _WINDOWS