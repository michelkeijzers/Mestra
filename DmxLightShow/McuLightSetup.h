#pragma once

#include "PlatformLightSetup.h"
#include "Par.h" 

class McuLightSetup :
	public PlatformLightSetup
{
public:
	McuLightSetup();
	virtual ~McuLightSetup();

	void SetProperties() override;

	void PrintHeader() const override;
	void PrintFixture(fixture_number_t fixtureNumber) const override;
	void PrintFooter() const override;

	bool ArePropertiesSet() const override;
};

