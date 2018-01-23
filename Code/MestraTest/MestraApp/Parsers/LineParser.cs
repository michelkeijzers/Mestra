using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;

namespace MestraApp.Parsers
{
    public class LineParser
    {
        public LineResult LineResult { get; set; }

        readonly string _line;

        public string[] Words { get; private set; }

        public int CurrentWordIndex { get; set; }

        public string CurrentWord => Words[CurrentWordIndex];

        public bool MoreWordsPresent => CurrentWordIndex < Words.Length;

        public int NumberOfWords => Words.Length;

        public LineParser(string line)
        {
            LineResult = new LineResult();
            _line = line;
            CurrentWordIndex = 0;
        }

        public void Parse()
        {
            Words = _line.Split(' ');

            if (IsTrigger())
            {
                LineResult.ConfigType = LineResult.EConfigType.Trigger;
                CurrentWordIndex++;
                var parser = new TriggerParser(this);
                parser.Parse();
            }
            else if (IsProgram())
            {
                LineResult.ConfigType = LineResult.EConfigType.Program;
                CurrentWordIndex++;
                var parser = new ProgramNameParser(this);
                parser.Parse();
                LineResult.ProgramName = parser.Name;
            }
            else if (IsInstruction())
            {
                LineResult.ConfigType = LineResult.EConfigType.Instruction;
                //TODO
            }
        }
        
        private bool IsTrigger()
        {
            var word = Words[CurrentWordIndex].ToLower();
            return word.Equals("trigger");
        }

        private bool IsProgram()
        {
            var word = Words[CurrentWordIndex].ToLower();
            return word.Equals("program");
        }


        private bool IsInstruction()
        {
            var word = Words[CurrentWordIndex].ToLower();
            return true;
        }
    }
}
