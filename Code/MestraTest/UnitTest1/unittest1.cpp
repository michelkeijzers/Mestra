#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../../Stm32/Stm32CubeProjects/MidiSerialTestDMA2Complete/Src/Mestra/Trigger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Mestra::Trigger trigger;
			Assert::AreEqual(52, trigger.F());
		}

	};
}