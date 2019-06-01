#pragma once

#include "Irgbw.h"
#include "MestraTypes.h"


// _data
// Byte(s) From Class Type     Property           Meaning
// ------- ---------- -------- ------------------ ------------------------------------------------
//   0     Fixture    uint8_t  _fixtureNumber     Fixture number (always fixed)
//   1     Fixture    uint16_t _dmxOffsetChannel  DMX offset channel
//   3     Fixture    bool     _initialize        True until it has been processed for first time  
//   4     Fixture    uint8_t  _program           Program number
//   5- 7  Fixture    uint16_t _currentStep       Current step within program
//   7- 8  Fixture    uint16_t _nrOfSteps         Number of steps within program
//   9-12  Fixture    uint32_t _stepTime          Next time the current step changes
//  13-14  Fixture    uint32_t _stepDuration      Duration of one/the current step)
//  15-16  Fixture    int16_t  _parameter1        Parameter 1, depends on program
//  17-18  Fixture    int16_t  _parameter2		    Parameter 1, depends on program
//  19-20  Fixture    int16_t  _parameter3		    Parameter 1, depends on program
//  21-25  Par        Irgbw    _defaultcolor      Default color
//  26-30  Par        Irgbw    _alternateColor    Used for cross/multicolor programs
//  31     LedBar     uint8_t  _segmentNumber     Number of led bar segment
//
// Total 64 bytes, data is stored in LightSetup.
//
// Memory consumption
//
// SRAM Memory: Global variables:                                       1281 bytes
//              Dynamic memory:    17 fixtures * 2 ptrs * 2 bytes/ptr =   68 bytes
//              Stack size:         (rough estimate)                  =  200 bytes
//              Interrupt           (rough estimate)                  =   20 bytes
//                                                                      ---- 
//              Total used SRAM:                                        1569 bytes
// 
// SD Memory:    17 fixtures * 64 bytes                               = 1088 bytes
//
//                

#define DATA_START_FIXTURE_NUMBER     0
#define DATA_START_DMX_OFFSET_CHANNEL (DATA_START_FIXTURE_NUMBER     + 1)
#define DATA_START_INITIALIZE         (DATA_START_DMX_OFFSET_CHANNEL + 2)
#define DATA_START_PROGRAM            (DATA_START_INITIALIZE         + 1)
#define DATA_START_CURRENT_STEP       (DATA_START_PROGRAM            + 1)
#define DATA_START_NR_OF_STEPS        (DATA_START_CURRENT_STEP       + 2)
#define DATA_START_STEP_TIME          (DATA_START_NR_OF_STEPS        + 2)
#define DATA_START_STEP_DURATION      (DATA_START_STEP_TIME          + 4)
#define DATA_START_PARAMETER_1        (DATA_START_STEP_DURATION      + 2)
#define DATA_START_PARAMETER_2        (DATA_START_PARAMETER_1        + 2)
#define DATA_START_PARAMETER_3        (DATA_START_PARAMETER_2        + 2)
#define DATA_SIZE_FIXTURE             (DATA_START_PARAMETER_3        + 2)

#define DATA_SIZE_MAX                 64

#define SRAM_PAGE_SIZE                32

#define PRINT_DATA

class FixtureData
{
public:
	FixtureData();
	~FixtureData();

	void ClearAll();
	void Load(fixture_number_t fixtureNumber);
	void Save(fixture_number_t fixtureNumber);

	bool     ReadBool(uint8_t dataOffset);
	uint8_t  ReadUint8(uint8_t dataOffset);
	int16_t  ReadInt16(uint8_t dataOffset);
	int16_t  ReadUint16(uint8_t dataOffset);
	uint32_t ReadUint32(uint8_t dataOffset);
	void     ReadIrgbw(uint8_t dataOffset, Irgbw& irgbw);

	void WriteBool(uint8_t dataOffset, bool     value);
	void WriteUint8(uint8_t dataOffset, uint8_t  value);
	void WriteInt16(uint8_t dataOffset, int16_t  value);
	void WriteUint16(uint8_t dataOffset, uint16_t value);
	void WriteUint32(uint8_t dataOffset, uint32_t value);
	void WriteIrgbw(uint8_t dataOffset, Irgbw& value);
	
private:
	uint8_t _data[DATA_SIZE_MAX];
};

