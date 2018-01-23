using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace MestraApp.Parsers
{
    /// <summary>
    /// Format: [a..AZ..Z_] [a..AZ..Z0..9_]*
    /// </summary>
    public class ProgramNameParser
    {
        readonly LineParser _lineParser;

        public string Name { get; set; }


        public ProgramNameParser(LineParser lineParser)
        {
            _lineParser = lineParser;
            Name = "";
        }

        public void Parse()
        {
            if (_lineParser.CurrentWord.Length < 2)
            {
                throw new ApplicationException("Too short");
            }
            else if (_lineParser.CurrentWord[_lineParser.CurrentWord.Length - 1] != ':')
            {
                throw new ApplicationException("Colon at end missing");
            }

            if (char.IsLetter(_lineParser.CurrentWord[0]) || (_lineParser.CurrentWord[0] == '_'))
            {
                Name += _lineParser.CurrentWord[0];

                for (var n = 1; n < _lineParser.CurrentWord.Length - 1; n++)
                {
                    var character = _lineParser.CurrentWord[n];
                    if (char.IsLetterOrDigit(character) || (character == '_'))
                    {
                        Name += character;
                    }
                    else
                    {
                        throw new ApplicationException("Illegal charachter in name");
                    }
                }
            }
            else
            {
                throw new ApplicationException("Illegal charachter in name");
            }

            _lineParser.CurrentWordIndex++;
        }
    }
}

