#include "FixtureData.h"
#include "AssertUtils.h"
#include "LightSetup.h"
#include "BitsUtils.h"


FixtureData::FixtureData()
: _data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
	for (uint8_t n = 0U; n < FIXTURE_DATA_SIZE_MAX; n++)
	{
		_data[n] = 0U;
	}
}


FixtureData::~FixtureData()
{
}


void FixtureData::ClearAll()
{
	//assert(DATA_SIZE_MAX % SRAM_PAGE_SIZE == 2U);

	uint8_t clear[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	for (uint16_t page = 0U; page < NR_OF_PARS * FIXTURE_DATA_SIZE_MAX; page += FIXTURE_DATA_SRAM_PAGE_SIZE)
	{
		LightSetup.GetSpiRam().write_page(page, (char*)clear);
	}
}


void FixtureData::Load(fixture_number_t fixtureNumber)
{
	//assert(DATA_SIZE_MAX == 64U);
	
	LightSetup.GetSpiRam().read_page(fixtureNumber * FIXTURE_DATA_SIZE_MAX, (char*) & (_data[0]));
	LightSetup.GetSpiRam().read_page(fixtureNumber * FIXTURE_DATA_SIZE_MAX + FIXTURE_DATA_SRAM_PAGE_SIZE, (char*) & (_data[FIXTURE_DATA_SRAM_PAGE_SIZE]));
}


void FixtureData::Save(fixture_number_t fixtureNumber)
{
	//assert(DATA_SIZE_MAX == 64U);

	LightSetup.GetSpiRam().write_page(fixtureNumber * FIXTURE_DATA_SIZE_MAX, (char*) & (_data[0]));
	LightSetup.GetSpiRam().write_page(fixtureNumber * FIXTURE_DATA_SIZE_MAX + FIXTURE_DATA_SRAM_PAGE_SIZE, (char*) & (_data[FIXTURE_DATA_SRAM_PAGE_SIZE]));
}


bool FixtureData::ReadBool(uint8_t dataOffset, uint8_t bitNumber)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX);
	assert(bitNumber <= 7U);

	return ((dataOffset < FIXTURE_DATA_SIZE_MAX) ? ((_data[dataOffset] & (1U << bitNumber)) > 0U) : false);
}


uint8_t FixtureData::ReadUint8(uint8_t dataOffset)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX);

	return ((dataOffset < FIXTURE_DATA_SIZE_MAX) ? _data[dataOffset] : UINT8_MAX);
}


int16_t FixtureData::ReadInt16(uint8_t dataOffset)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 1U);

	return ((dataOffset < FIXTURE_DATA_SIZE_MAX - 1U) ? *((int16_t*) (&_data[dataOffset])) : INT16_MAX);
}


int16_t FixtureData::ReadUint16(uint8_t dataOffset)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 1U);

	return ((dataOffset < FIXTURE_DATA_SIZE_MAX - 1U) ? ((_data[dataOffset]) << 8U) + (_data[dataOffset + 1U]) : INT16_MAX);
}


uint32_t FixtureData::ReadUint32(uint8_t dataOffset)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 3U);

	return ((dataOffset < FIXTURE_DATA_SIZE_MAX - 3U) 
		? (((uint32_t)(_data[dataOffset]) << 24U) +
		   ((uint32_t)(_data[dataOffset + 1U]) << 16U) +
		   ((uint32_t)(_data[dataOffset + 2U]) << 8U) +
		   ((uint32_t)(_data[dataOffset + 3U])))
		: UINT32_MAX);
}


void FixtureData::ReadIrgbw(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 4U);

	if (dataOffset < FIXTURE_DATA_SIZE_MAX - 4U)
	{
		irgbw.SetIntensity(ReadUint8(dataOffset));
		irgbw.SetRed(ReadUint8(dataOffset + 1U));
		irgbw.SetGreen(ReadUint8(dataOffset + 2U));
		irgbw.SetBlue(ReadUint8(dataOffset + 3U));
		irgbw.SetWhite(ReadUint8(dataOffset + 4U));
	}
}


void FixtureData::WriteBool(uint8_t dataOffset, uint8_t bitNumber, bool value)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX);
	assert(bitNumber <= 7U);

	if ((dataOffset < FIXTURE_DATA_SIZE_MAX) && (bitNumber <= 7U))
	{
		_data[dataOffset] = (uint8_t)BitsUtils::ChangeBit(_data[dataOffset], bitNumber, value);
	}
}


void FixtureData::WriteUint8(uint8_t dataOffset, uint8_t  value)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX);

	if (dataOffset < FIXTURE_DATA_SIZE_MAX)
	{
		_data[dataOffset] = value;
	}
}


void FixtureData::WriteInt16(uint8_t dataOffset, int16_t  value)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 1U);

	if (dataOffset < FIXTURE_DATA_SIZE_MAX - 1U)
	{
		*((parameter_t*)(&_data[dataOffset])) = value;
		//_data[dataOffset] = (uint8_t)(value / 256);
		//_data[dataOffset + 1U] = value % 256U;
	}
}


void FixtureData::WriteUint16(uint8_t dataOffset, uint16_t value)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 1U);

	if (dataOffset < FIXTURE_DATA_SIZE_MAX - 1U)
	{
		_data[dataOffset] = (uint8_t)(value / 256U);
		_data[dataOffset + 1U] = (uint8_t)(value % 256U);
	}
}


void FixtureData::WriteUint32(uint8_t dataOffset, uint32_t value)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 3U);

	if (dataOffset < FIXTURE_DATA_SIZE_MAX - 3U)
	{
		_data[dataOffset] = (uint8_t)(value >> 24U);
		_data[dataOffset + 1U] = (uint8_t)((value >> 16U) % 256U);
		_data[dataOffset + 2U] = (uint8_t)((value >> 8U) % 256U);
		_data[dataOffset + 3U] = (uint8_t)(value % 256U);
	}
}


void FixtureData::WriteIrgb(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 4U);

	if (dataOffset < FIXTURE_DATA_SIZE_MAX - 4U)
	{
		WriteUint8(dataOffset, irgbw.GetIntensity());
		WriteUint8(dataOffset + 1U, irgbw.GetRed());
		WriteUint8(dataOffset + 2U, irgbw.GetGreen());
		WriteUint8(dataOffset + 3U, irgbw.GetBlue());
	}
}


void FixtureData::WriteIrgbw(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < FIXTURE_DATA_SIZE_MAX - 4U);

	if (dataOffset < FIXTURE_DATA_SIZE_MAX - 4U)
	{
		WriteUint8(dataOffset, irgbw.GetIntensity());
		WriteUint8(dataOffset + 1U, irgbw.GetRed());
		WriteUint8(dataOffset + 2U, irgbw.GetGreen());
		WriteUint8(dataOffset + 3U, irgbw.GetBlue());
		WriteUint8(dataOffset + 4U, irgbw.GetWhite());
	}
}