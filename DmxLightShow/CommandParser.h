// CommandParser.h 

// List of commands:
//
// Command   First       Second     Description
//         Parameter    Parameter
// ------- --------- -------------- -----------------------------------------
//    a     parbits  0/color/IRGBW  Set alternate color, 0 = off
//    d     parbits  0/Color/IRGBW  Set default color, 0 = off
//    p     parbits  preset 0-65535 Set preset
//    s     parbits  speed          Set strobe
//    t     parbits  value 0-65535  Set (delay) time
//
// <Color>: All combinations with i, r, g, b, w possible
//          Combinations with w switches off Strobo
// <IRGBW>: (<Intensity>), <Red>, <Green>, <Blue> (, <White>)
//           0<=Intensity<=255, 0 (%) <=Red, Green, Blue, White<=100 (%)
//
// Max length:
//
// 12345678901234567890123456789012
// c FL1 255,100,100,100,100,100

// List of presets
//
// Preset              Preset Program Description
// Group               number
// ------------------- ------ ------- ------------------------------------------
// Switch colors           10    n.a. Default color    -> Alternate color
//                         11    n.a. Alternate color  -> Default color
//                         12    n.a. Default color   <-> Alternate color
//                         13    n.a. Default color    -> Actual color
//                         14    n.a. Actual color     -> Default color
//                         15    n.a. Default color   <-> Actual color
//                         16    n.a. Alternate color  -> Actual color
//                         17    n.a. Actual color     -> Alternate color
//                         18    n.a. Alternate color <-> Actual color
// Solid color             20      0  Solod (Default) color
// Dual colors             30     10  Switch between default and alternate color
//                         31     10  Switch between alternate and default color
// Chase                   40     10  Chase left -> right
//                         41     10  Chase right -> left
//                         42     10  Chase left -> right -> left
//                         43     10  Chase right -> left -> right
// Fade in/out             50     20  Fade default color->alternate color
//                         51     21  Fade alternate color->default color
//                         52     20  Fade def->alt->def
//                         53     20  Fade alt->def->alt
// Fade + Chase            60     30  Fade + Chase, left -> right
//                         61     30  Fade + Chase, right -> left
//                         62     30  Fade + Chase, left -> right -> left
//                         63     30  Fade + Chase, right -> left -> right
// Rainbow colors          70     40  No fade, left -> right, 
//                         71     40  No fade, right -> left
//                         72     40  Fade, left -> right
//                         73     40  Fade, right -> left
//
// Program List
// 
// Prg Name       Par1 Par2 Par3 Description
// --- ---------- ---- ---- ---- ------------------------------------------------------------------------
//   0 SolidColor	 -    -    - 
//  10 DualColor  Yes  Yes   -   Use default color if step = par1 or par2, else alternate color
//  20 FadeInOut  Yes  Yes   -   Fade in using default color for fade in, alt color for fade out
//  21 FadeOut    Yes  Yes   -   Like FadeInOut, but only FadeOut
//  30 FaceChase  Yes  Yes  Yes  Fade + chase combined (par 3 = Nr of pars in group)
//  40 Rainbow    Yes   -    -   Step increase

#pragma once

#include <string.h>
#include "ClassNames.h"
#include "Par.h"

class CommandParser
{
public:
	CommandParser();
	~CommandParser();

	void Parse(char* command);

private:
	// Current index within string
	char* _command;

	uint8_t _currentIndex;

	par_bits_t _parBits;

	bool _parseError;

	void ParseColorCommand(Par::EActiveColor color);

	void ParseIrgbwAsNumbers(Irgbw& irgwb);
	void ParseIrgbwAsCharacters(Irgbw& irgbw);

	void SetIrgbw(Par::EActiveColor color, Irgbw& irgbw);

	void ParsePresetCommand();

	void ParseStrobeCommand();

	void ParseDelayTimeCommand();

	void ParseParBits();

	void ParseWhitespace();
	void SkipWhitespace();

	void SkipUntilComma();

	void SetDelay(step_time_t delay);
};
