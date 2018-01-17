using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;

namespace MestraApp.Parsers
{
    /// <summary>
    /// Format: [@"mc" <nr> 
    /// <nr> 1..16
    /// </summary>
    public class MidiMcParser
    {
        LineParser _lineParser;

        public MidiMcParser(LineParser lineParser)
        {
            _lineParser = lineParser;
        }

        public void Parse()
        {
            if (IsMc())
            {
                _lineParser.CurrentWordIndex++;
            }

            if (_lineParser.MoreWordsPresent)
            {
                byte mc;
                byte.TryParse(_lineParser.CurrentWord, out mc);

                if ((mc < 1) || (mc > 128))
                {
                    throw new ApplicationException("MIDI Channel out of range");
                }

                _lineParser.LineResult.MidiChannel = mc;
            }
            else
            {
                throw new ApplicationException("MIDI Channel missing");
            }

            _lineParser.CurrentWordIndex++;
        }

        private bool IsMc() => _lineParser.CurrentWord.ToLower().Equals("mc");
    }
}

