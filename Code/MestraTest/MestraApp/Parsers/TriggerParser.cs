using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;

namespace MestraApp.Parsers
{
    public class TriggerParser
    {
        readonly LineParser _lineParser;

        public TriggerParser(LineParser lineParser)
        {
            _lineParser = lineParser;
        }

        public void Parse()
        {
            var parser = new MidiTriggerParser(_lineParser);
            parser.Parse();

            //LATER add non MIDI triggers
        }
    }
}

