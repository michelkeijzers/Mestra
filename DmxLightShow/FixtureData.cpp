#include "FixtureData.h"
#include "assert.h"
#include "LightSetup.h"
#include "BitsUtils.h"


FixtureData::FixtureData()
: _data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
	for (uint8_t n = 0U; n < DATA_SIZE_MAX; n++)
	{
		_data[n] = 0U;
	}
}


FixtureData::~FixtureData()
{
}


void FixtureData::ClearAll()
{
	assert(DATA_SIZE_MAX % SRAM_PAGE_SIZE % 2U == 0U);
	
	uint8_t clear[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	for (uint16_t page = 0U; page < NR_OF_PARS * DATA_SIZE_MAX; page += SRAM_PAGE_SIZE)
	{
		LightSetup.GetSpiRam().write_page(page, (char*) clear);
	}
}


void FixtureData::Load(fixture_number_t fixtureNumber)
{
	assert(DATA_SIZE_MAX == 64U);
	
	LightSetup.GetSpiRam().read_page(fixtureNumber * DATA_SIZE_MAX, (char*) & (_data[0]));
	LightSetup.GetSpiRam().read_page(fixtureNumber * DATA_SIZE_MAX + SRAM_PAGE_SIZE, (char*) & (_data[SRAM_PAGE_SIZE]));
}


void FixtureData::Save(fixture_number_t fixtureNumber)
{
	assert(DATA_SIZE_MAX == 64U);

	LightSetup.GetSpiRam().write_page(fixtureNumber * DATA_SIZE_MAX, (char*) & (_data[0]));
	LightSetup.GetSpiRam().write_page(fixtureNumber * DATA_SIZE_MAX + SRAM_PAGE_SIZE, (char*) & (_data[SRAM_PAGE_SIZE]));
}


bool FixtureData::ReadBool(uint8_t dataOffset, uint8_t bitNumber)
{
	assert(dataOffset < DATA_SIZE_MAX);
	assert(bitNumber <= 7U);

	return ((_data[dataOffset] & (1U << bitNumber)) > 0U);
}


uint8_t FixtureData::ReadUint8(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX);
	return _data[dataOffset];
}


int16_t FixtureData::ReadInt16(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX - 1U);
	return ((_data[dataOffset]) << 8U) +
		(_data[dataOffset + 1U]);
}


int16_t FixtureData::ReadUint16(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX - 1U);
	return ((_data[dataOffset]) << 8U) +
		(_data[dataOffset + 1U]);
}


uint32_t FixtureData::ReadUint32(uint8_t dataOffset)
{
	assert(dataOffset < DATA_SIZE_MAX - 3U);
	return (uint32_t)(
		((uint32_t)(_data[dataOffset]) << 24U) +
		((uint32_t)(_data[dataOffset + 1U]) << 16U) +
		((uint32_t)(_data[dataOffset + 2U]) << 8U) +
		((uint32_t)(_data[dataOffset + 3U])));
}


void FixtureData::ReadIrgbw(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < DATA_SIZE_MAX - 4U);
	irgbw.SetIntensity(ReadUint8(dataOffset));
	irgbw.SetRed(ReadUint8(dataOffset + 1U));
	irgbw.SetGreen(ReadUint8(dataOffset + 2U));
	irgbw.SetBlue(ReadUint8(dataOffset + 3U));
	irgbw.SetWhite(ReadUint8(dataOffset + 4U));
}


void FixtureData::WriteBool(uint8_t dataOffset, uint8_t bitNumber, bool value)
{
	assert(dataOffset < DATA_SIZE_MAX);
	assert(bitNumber <= 7U);

	_data[dataOffset] = (uint8_t) BitsUtils::ChangeBit(_data[dataOffset], bitNumber, value);
}


void FixtureData::WriteUint8(uint8_t dataOffset, uint8_t  value)
{
	assert(dataOffset < DATA_SIZE_MAX);
	_data[dataOffset] = value;
}


void FixtureData::WriteInt16(uint8_t dataOffset, int16_t  value)
{
	assert(dataOffset < DATA_SIZE_MAX - 1U);
	_data[dataOffset] = (uint8_t) (value / 256);
	_data[dataOffset + 1U] = value % 256U;
}


void FixtureData::WriteUint16(uint8_t dataOffset, uint16_t value)
{
	assert(dataOffset < DATA_SIZE_MAX - 1U);
	_data[dataOffset] = (uint8_t) (value / 256U);
	_data[dataOffset + 1U] = (uint8_t) (value % 256U);
}


void FixtureData::WriteUint32(uint8_t dataOffset, uint32_t value)
{
	assert(dataOffset < DATA_SIZE_MAX - 3U);
	_data[dataOffset] = (uint8_t)(value >> 24U);
	_data[dataOffset + 1U] = (uint8_t)((value >> 16U) % 256U);
	_data[dataOffset + 2U] = (uint8_t)((value >> 8U) % 256U);
	_data[dataOffset + 3U] = (uint8_t)(value % 256U);
}


void FixtureData::WriteIrgb(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < DATA_SIZE_MAX - 4U);
	WriteUint8(dataOffset, irgbw.GetIntensity());
	WriteUint8(dataOffset + 1U, irgbw.GetRed());
	WriteUint8(dataOffset + 2U, irgbw.GetGreen());
	WriteUint8(dataOffset + 3U, irgbw.GetBlue());
}


void FixtureData::WriteIrgbw(uint8_t dataOffset, Irgbw& irgbw)
{
	assert(dataOffset < DATA_SIZE_MAX - 4U);
	WriteUint8(dataOffset, irgbw.GetIntensity());
	WriteUint8(dataOffset + 1U, irgbw.GetRed());
	WriteUint8(dataOffset + 2U, irgbw.GetGreen());
	WriteUint8(dataOffset + 3U, irgbw.GetBlue());
	WriteUint8(dataOffset + 4U, irgbw.GetWhite());
}