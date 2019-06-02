#pragma once

#include "Irgbw.h"
#include "MestraTypes.h"


#define DATA_START_FIXTURE_NUMBER       0
#define DATA_START_DMX_OFFSET_CHANNEL   (DATA_START_FIXTURE_NUMBER     + 1)
#define DATA_START_INITIALIZE           (DATA_START_DMX_OFFSET_CHANNEL + 2)
#define DATA_START_INITIALIZE_BIT       0
#define DATA_START_ONE_SHOT_PROGRAM     (DATA_START_DMX_OFFSET_CHANNEL + 2)
#define DATA_START_ONE_SHOT_PROGRAM_BIT 1
#define DATA_START_PROGRAM              (DATA_START_INITIALIZE         + 1)
#define DATA_START_CURRENT_STEP			    (DATA_START_PROGRAM            + 1)
#define DATA_START_NR_OF_STEPS          (DATA_START_CURRENT_STEP       + 2)
#define DATA_START_STEP_TIME            (DATA_START_NR_OF_STEPS        + 2)
#define DATA_START_STEP_DURATION        (DATA_START_STEP_TIME          + 4)
#define DATA_START_PARAMETER_1          (DATA_START_STEP_DURATION      + 2)
#define DATA_START_PARAMETER_2          (DATA_START_PARAMETER_1        + 2)
#define DATA_START_PARAMETER_3          (DATA_START_PARAMETER_2        + 2)
#define DATA_SIZE_FIXTURE               (DATA_START_PARAMETER_3        + 2)

#define DATA_SIZE_MAX                   64

#define SRAM_PAGE_SIZE                  32

#define PRINT_DATA


class FixtureData
{
public:
	FixtureData();
	~FixtureData();

	void ClearAll();
	void Load(fixture_number_t fixtureNumber);
	void Save(fixture_number_t fixtureNumber);

	bool     ReadBool(uint8_t dataOffset, uint8_t bitNumber);
	uint8_t  ReadUint8(uint8_t dataOffset);
	int16_t  ReadInt16(uint8_t dataOffset);
	int16_t  ReadUint16(uint8_t dataOffset);
	uint32_t ReadUint32(uint8_t dataOffset);
	void     ReadIrgbw(uint8_t dataOffset, Irgbw& irgbw);

	void WriteBool(uint8_t dataOffset, uint8_t bitNumber, bool value);
	void WriteUint8(uint8_t dataOffset, uint8_t value);
	void WriteInt16(uint8_t dataOffset, int16_t value);
	void WriteUint16(uint8_t dataOffset, uint16_t value);
	void WriteUint32(uint8_t dataOffset, uint32_t value);
	void WriteIrgb(uint8_t dataOffset, Irgbw& value);
	void WriteIrgbw(uint8_t dataOffset, Irgbw& value);
	
private:
	uint8_t _data[DATA_SIZE_MAX];
};

