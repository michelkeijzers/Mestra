#pragma once


#include "MestraTypes.h"



class ParGroups
{
public:
	static uint8_t GetNrOfGroups();

	static uint8_t GetNrOfPars(par_group_t parGroup);

	static par_bits_t GetParBits(par_group_t parGroup);

	static par_group_t GetParGroup(char abbreviationChar1, char abbreviationChar2, bool* ok);

	static uint8_t GetParIndexInGroup(par_group_t parGroup, fixture_number_t fixtureNumber);

private:
	ParGroups();
	~ParGroups();
};

