using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using MestraApp.Writers;
using MestraGeneric;

namespace MestraApp.Parsers
{
    public class LineResult
    {
        public enum EConfigType
        {
            Trigger,
            Program,
            Instruction
        };

        public EConfigType ConfigType { get; set; }

        public Trigger.EMidiTriggerType MidiTriggerType { get; set; }

        public string MidiTriggerName { get; set; }

        public byte MidiChannel { get; set; }
        
        public MidiNotes.ENote StartNote { get; set; }

        public MidiNotes.ENote EndNote { get; set; }

        public string ProgramName { get; set; }

        public bool MidiIsEnabled { get; set; }

        public LineResult()
        {
        }
    }
}
