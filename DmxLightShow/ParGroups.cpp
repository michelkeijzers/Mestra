#include "AssertUtils.h"
#include "BitsUtils.h"

#include "ParGroups.h"
#include "Fixture.h"
#include "LightSetup.h"


const par_bits_t PAR_L4 = 1UL << 0;
const par_bits_t PAR_L3 = 1UL << 1;
const par_bits_t PAR_L2 = 1UL << 2;
const par_bits_t PAR_L1 = 1UL << 3;
const par_bits_t PAR_R1 = 1UL << 4;
const par_bits_t PAR_R2 = 1UL << 5;
const par_bits_t PAR_R3 = 1UL << 6;
const par_bits_t PAR_R4 = 1UL << 7;
const par_bits_t PAR_DL = 1UL << 8;
const par_bits_t PAR_DR = 1UL << 9;
const par_bits_t PAR_NL = 1UL << 10;
const par_bits_t PAR_NR = 1UL << 11;
const par_bits_t PAR_EL = 1UL << 12;
const par_bits_t PAR_ER = 1UL << 13;
const par_bits_t PAR_BL = 1UL << 14;
const par_bits_t PAR_BC = 1UL << 15;
const par_bits_t PAR_BR = 1UL << 16;

const par_bits_t PAR_BA = PAR_BL + PAR_BC + PAR_BR;

const par_bits_t PAR_DA = PAR_DL + PAR_DR;

const par_bits_t PAR_EA = PAR_EL + PAR_ER;

const par_bits_t PAR_LI = PAR_L2 + PAR_L3;
const par_bits_t PAR_LO = PAR_L4 + PAR_L1;
const par_bits_t PAR_LA = PAR_LI + PAR_LO;

const par_bits_t PAR_NA = PAR_NL + PAR_NR;

const par_bits_t PAR_RI = PAR_R2 + PAR_R3;
const par_bits_t PAR_RO = PAR_R4 + PAR_R1;
const par_bits_t PAR_RA = PAR_RI + PAR_RO;

const par_bits_t PAR_FA = PAR_LA + PAR_RA;
const par_bits_t PAR_FC = PAR_LO + PAR_RO;
const par_bits_t PAR_FM = PAR_LI + PAR_RI;
const par_bits_t PAR_FI = PAR_FM + PAR_L1 + PAR_R1;
const par_bits_t PAR_FO = PAR_L4 + PAR_R4;

const par_bits_t PAR_AA = PAR_FA + PAR_DA + PAR_NA + PAR_EA + PAR_BA;
const par_bits_t PAR_AC = PAR_FM + PAR_BC;
const par_bits_t PAR_AE = PAR_FA + PAR_DA + PAR_NA + PAR_BA;
const par_bits_t PAR_AL = PAR_LA + PAR_DL + PAR_NL + PAR_BL;
const par_bits_t PAR_AR = PAR_RA + PAR_DR + PAR_NR + PAR_BR;


struct ParGroupsStruct
{
	char       abbreviationChar1;
	char       abbreviationChar2;
	par_bits_t parBits;
};


#define NR_OF_PAR_GROUPS 37

ParGroupsStruct parGroups[NR_OF_PAR_GROUPS] =
{
	{ 'A', 'A', PAR_AA },
	{ 'A', 'C', PAR_AC },
	{ 'A', 'E', PAR_AE },
	{ 'A', 'L', PAR_AL },
	{ 'A', 'R', PAR_AR },
	{ 'B', 'A', PAR_BA },
	{ 'B', 'C', PAR_BC },
	{ 'B', 'L', PAR_BL },
	{ 'B', 'R', PAR_BR },
	{ 'D', 'A', PAR_DA },
	{ 'D', 'L', PAR_DL },
	{ 'D', 'R', PAR_DR },
	{ 'E', 'A', PAR_EA },
	{ 'E', 'L', PAR_EL },
	{ 'E', 'R', PAR_ER },
	{ 'F', 'A', PAR_FA },
	{ 'F', 'C', PAR_FC },
	{ 'F', 'M', PAR_FM },
	{ 'F', 'I', PAR_FI },
	{ 'F', 'O', PAR_FO },
	{ 'L', '1', PAR_L1 },
	{ 'L', '2', PAR_L2 },
	{ 'L', '3', PAR_L3 },
	{ 'L', '4', PAR_L4 },
	{ 'L', 'A', PAR_LA },
	{ 'L', 'I', PAR_LI },
	{ 'L', 'O', PAR_LO },
	{ 'N', 'A', PAR_NA },
	{ 'N', 'L', PAR_NL },
	{ 'N', 'R', PAR_NR },
	{ 'R', '1', PAR_R1 },
	{ 'R', '2', PAR_R2 },
	{ 'R', '3', PAR_R3 },
	{ 'R', '4', PAR_R4 },
	{ 'R', 'A', PAR_RA },
	{ 'R', 'I', PAR_RI },
	{ 'R', 'O', PAR_RO }
};


ParGroups::ParGroups()
{
}


ParGroups::~ParGroups()
{
}


/* static */ uint8_t ParGroups::GetNrOfGroups()
{
	return NR_OF_PAR_GROUPS;
}


/* static */ uint8_t ParGroups::GetNrOfPars(par_group_t parGroup)
{
	return BitsUtils::GetNrOfHighBits(parGroups[parGroup].parBits);
}


/* static */ par_bits_t ParGroups::GetParBits(par_group_t parGroup)
{
	return parGroups[parGroup].parBits;
}


/* static */ par_group_t ParGroups::GetParGroup(char abbreviationChar1, char abbreviationChar2, bool* ok)
{
	*ok = true;

	for (par_group_t par_group = 0; par_group < sizeof(parGroups) / sizeof(ParGroupsStruct); par_group++)
	{
		if (parGroups[par_group].abbreviationChar1 == abbreviationChar1 &&
			parGroups[par_group].abbreviationChar2 == abbreviationChar2)
		{
			return par_group;
		}
	}

	AssertUtils::MyAssert(false);
	*ok = false;

	return 0;
}


// Returns index of fixtureNumber within a par group.
/* static */ uint8_t ParGroups::GetParIndexInGroup(par_group_t parGroup, fixture_number_t fixtureNumberToFind)
{
	par_bits_t parBits = GetParBits(parGroup);
	bool found = false;
	fixture_number_t fixtureToFindInGroup = 0;
	fixture_number_t nrOfFixturesInGroup = 0;

	for (fixture_number_t fixtureNumber = 0; fixtureNumber < NR_OF_PARS; fixtureNumber++)
	{
		if (parBits & 1 << fixtureNumber)
		{
			nrOfFixturesInGroup++;
			fixtureToFindInGroup = nrOfFixturesInGroup - 1;
			if (fixtureNumber == fixtureNumberToFind)
			{
				found = true;
				break;
			}
		}
	}

	AssertUtils::MyAssert(found);
	return fixtureToFindInGroup;
}