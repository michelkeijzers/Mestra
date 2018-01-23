using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using MestraGeneric;

namespace MestraApp.Parsers
{
    /// <summary>
    /// Format: [Note] | ( [Note]-[Note] <nr> 
    ///
    /// </summary>
    public class MidiNotesParser
    {
        readonly LineParser _lineParser;

        int _currentIndex;

        public MidiNotesParser(LineParser lineParser)
        {
            _lineParser = lineParser;
            _currentIndex = 0;
        }

        public void Parse()
        {
            if (IsAll)
            {
                _lineParser.LineResult.StartNote = MidiNotes.ENote.C0;
                _lineParser.LineResult.EndNote = MidiNotes.ENote.G10;
            }
            else
            {
                _currentIndex = 0;
                _lineParser.LineResult.StartNote = GetNote();
                _lineParser.LineResult.EndNote = _lineParser.LineResult.StartNote;

                if (_lineParser.CurrentWord.Length > _currentIndex)
                {
                    if (_lineParser.CurrentWord[_currentIndex] != '-')
                    {
                        throw new ApplicationException("Unexpected MIDI range symbol");
                    }

                    _currentIndex++;
                    _lineParser.LineResult.EndNote = GetNote();
                }
            }

            _lineParser.CurrentWordIndex++;
        }

        private bool IsAll => (_lineParser.CurrentWord.ToLower() == "all");

        private MidiNotes.ENote GetNote()
        {
            var offset = ParseBasicNote();
            offset = ParseSharpSign(offset);
            offset = ParseOctave(offset);

            if (offset > 127)
            {
                throw new ApplicationException("MIDI note number too high");
            }

            return (MidiNotes.ENote) offset;
        }

        private int ParseOctave(int offset)
        {
            var currentChar = _lineParser.CurrentWord[_currentIndex];
            if (currentChar == '0')
            {
                _currentIndex++;
            }
            else if (currentChar == '1')
            {
                offset += 12;
                _currentIndex++;

                if ((_lineParser.CurrentWord.Length > _currentIndex) && (_lineParser.CurrentWord[_currentIndex] == '0'))
                {
                    offset += 9*12; // Octave 10
                    _currentIndex++;
                }
            } else if ((currentChar >= '2') && (currentChar <= '9'))
            {
                offset += (currentChar - '0') * 12;
                _currentIndex++;
            }
            else
            {
                throw new ApplicationException("Octave illegal");
            }

            return offset;
        }

        private int ParseSharpSign(int offset)
        {
            if (_lineParser.CurrentWord[_currentIndex] == '#')
            {
                if ((offset == 3) || (offset == 10))
                {
                    throw new ApplicationException("No # allowed in E or B note");
                }

                _currentIndex++;
                offset++;
            }
            return offset;
        }

        private int ParseBasicNote()
        {
            int offset;
            switch (_lineParser.CurrentWord[_currentIndex])
            {
                case 'C':
                    offset = 0;
                    break;

                case 'D':
                    offset = 2;
                    break;

                case 'E':
                    offset = 4;
                    break;

                case 'F':
                    offset = 5;
                    break;

                case 'G':
                    offset = 7;
                    break;

                case 'A':
                    offset = 9;
                    break;

                case 'B':
                    offset = 11;
                    break;

                default:
                    throw new ApplicationException("Illegal note");
            }

            if (offset == -1)
            {
                throw new ApplicationException("Illegal base note");
            }
            _currentIndex++;
            return offset;
        }
    }
}

