
// DmxLightShow.ino
//
//           
//             M E G A        
//            Flash SRAM   SRAMnew
// Maximum:  253952 8192
// Current:   11880 1045       663
//       %:       4   12         8
//
// Stack:
//
// Class          ::Method					   Parameters     Local Variables
// ProgramExecuter::Run							    0                  0
// ProgramExecuter::RunPars						    2                  2
// ProgramExecuter::FadeOutProgram				    2                  3
// ProgramExecuter::SetFadeColor				    3                  9
// ProgramExecuter::WriteIrgb				        2                  2
// ChinesePar     ::GetBlue2Dmx					    1                  0
// McuPar         ::GetBlue2GammaCorrectedDmx       1                  0
// Or alternative: DmxSimple.write()
// Total                                           11                 16      + 2 per level (7) = 11+16+14=41


#pragma once
class ArduinoDmxLightShow
{
public:
	ArduinoDmxLightShow();
	~ArduinoDmxLightShow();

	void Setup();
	void Loop();

	static void PrintFixtures();
};
