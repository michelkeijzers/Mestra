#include "FixtureData.h"
#include "assert.h"
#include "LightSetup.h"

FixtureData::FixtureData()
: _data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
	for (int n = 0; n < DATA_SIZE_MAX; n++)
	{
		_data[n] = 0;
	}
}


FixtureData::~FixtureData()
{
}


void FixtureData::ClearAll()
{
	assert(DATA_SIZE_MAX % SRAM_PAGE_SIZE % 2 == 0);
	
	uint8_t clear[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	for (int page = 0; page < NR_OF_PARS * DATA_SIZE_MAX; page += SRAM_PAGE_SIZE)
	{
		LightSetup.GetSpiRam().write_page(page, (char*) clear);
	}
}


void FixtureData::Load(fixture_number_t fixtureNumber)
{
	assert(DATA_SIZE_MAX == 64);
	
	LightSetup.GetSpiRam().read_page(fixtureNumber * DATA_SIZE_MAX, (char*) & (_data[0]));
	LightSetup.GetSpiRam().read_page(fixtureNumber * DATA_SIZE_MAX + SRAM_PAGE_SIZE, (char*) & (_data[SRAM_PAGE_SIZE]));
}


void FixtureData::Save(fixture_number_t fixtureNumber)
{
	assert(DATA_SIZE_MAX == 64);

	LightSetup.GetSpiRam().write_page(fixtureNumber * DATA_SIZE_MAX, (char*) & (_data[0]));
	LightSetup.GetSpiRam().write_page(fixtureNumber * DATA_SIZE_MAX + SRAM_PAGE_SIZE, (char*) & (_data[SRAM_PAGE_SIZE]));
}


bool     FixtureData::ReadBool(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX);
	return _data[dataOffset];
}


uint8_t  FixtureData::ReadUint8(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX);
	return _data[dataOffset];
}


int16_t  FixtureData::ReadInt16(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX - 1);
	return ((_data[dataOffset]) << 8) +
		(_data[dataOffset + 1]);
}


int16_t  FixtureData::ReadUint16(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX - 1);
	return ((_data[dataOffset]) << 8) +
		(_data[dataOffset + 1]);
}


uint32_t FixtureData::ReadUint32(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX - 3);
	return (((_data[dataOffset]) << 24) +
		((_data[dataOffset + 1]) << 16) +
		((_data[dataOffset + 2]) << 8) +
		((_data[dataOffset + 3])));
}


void FixtureData::ReadIrgbw(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < DATA_SIZE_MAX - 4);
	irgbw.SetIntensity(ReadUint8(dataOffset));
	irgbw.SetRed(ReadUint8(dataOffset + 1));
	irgbw.SetGreen(ReadUint8(dataOffset + 2));
	irgbw.SetBlue(ReadUint8(dataOffset + 3));
	irgbw.SetWhite(ReadUint8(dataOffset + 4));
}


void FixtureData::WriteBool(uint8_t dataOffset, bool     value)
{
	assert(dataOffset < DATA_SIZE_MAX);
	_data[dataOffset] = value;
}


void FixtureData::WriteUint8(uint8_t dataOffset, uint8_t  value)
{
	assert(dataOffset < DATA_SIZE_MAX);
	_data[dataOffset] = value;
}


void FixtureData::WriteInt16(uint8_t dataOffset, int16_t  value)
{
	assert(dataOffset < DATA_SIZE_MAX - 1);
	_data[dataOffset] = (uint8_t) (value / 256);
	_data[dataOffset + 1] = value % 256;
}


void FixtureData::WriteUint16(uint8_t dataOffset, uint16_t value)
{
	assert(dataOffset < DATA_SIZE_MAX - 1);
	_data[dataOffset] = (uint8_t) (value / 256);
	_data[dataOffset + 1] = (uint8_t) (value % 256);
}


void FixtureData::WriteUint32(uint8_t dataOffset, uint32_t value)
{
	assert(dataOffset < DATA_SIZE_MAX - 3);
	_data[dataOffset] = (uint8_t)(value >> 24);
	_data[dataOffset + 1] = (uint8_t)((value >> 16) % 256);
	_data[dataOffset + 2] = (uint8_t)((value >> 8) % 256);
	_data[dataOffset + 3] = (uint8_t)(value % 256);
}


void FixtureData::WriteIrgbw(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < DATA_SIZE_MAX - 4);
	WriteUint8(dataOffset, irgbw.GetIntensity());
	WriteUint8(dataOffset + 1, irgbw.GetRed());
	WriteUint8(dataOffset + 2, irgbw.GetGreen());
	WriteUint8(dataOffset + 3, irgbw.GetBlue());
	WriteUint8(dataOffset + 4, irgbw.GetWhite());
}