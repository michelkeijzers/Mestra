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
    public class MidiTriggerParser
    {
        readonly LineParser _lineParser;


        public MidiTriggerParser(LineParser lineParser)
        {
            _lineParser = lineParser;
        }


        public void Parse()
        {
            if ((_lineParser.MoreWordsPresent) && IsMidi())
            {
                _lineParser.CurrentWordIndex++;
            }

            // MIDI keyword is optional, so check here for all MIDI triggers.
            if (_lineParser.MoreWordsPresent)
            {
                if (IsNoteOn())
                {
                    ParseNoteOn();
                }
                else if (IsNoteOff())
                {
                    ParseNoteOff();
                }

                var triggerNameParser = new NameParser(_lineParser);
                triggerNameParser.Parse();
                _lineParser.LineResult.MidiTriggerName = triggerNameParser.Name;

                _lineParser.LineResult.MidiIsEnabled = IsEnabled();

                if (_lineParser.MoreWordsPresent)
                {
                    throw new ApplicationException("Unexpected words at end");
                }
            }
        }


        private void ParseNoteOff()
        {
            _lineParser.LineResult.MidiTriggerType = Trigger.EMidiTriggerType.NoteOff;
            _lineParser.CurrentWordIndex++;

            var mcParser = new MidiMcParser(_lineParser);
            mcParser.Parse();

            var noteParser = new MidiNotesParser(_lineParser);
            noteParser.Parse();
        }


        private void ParseNoteOn()
        {
            _lineParser.LineResult.MidiTriggerType = Trigger.EMidiTriggerType.NoteOn;
            _lineParser.CurrentWordIndex++;

            var mcParser = new MidiMcParser(_lineParser);
            mcParser.Parse();

            var noteParser = new MidiNotesParser(_lineParser);
            noteParser.Parse();
        }


        private bool IsMidi() => _lineParser.CurrentWord.ToLower().Equals("midi");


        private bool IsNoteOn()
        {
            var word = _lineParser.CurrentWord.ToLower().Replace(" ", "");
            return word.Equals("noteon") || word.Equals("on");
        }


        private bool IsNoteOff()
        {
            var word = _lineParser.CurrentWord.ToLower().Replace(" ", "");
            return word.Equals("noteoff") || word.Equals("off");
        }

        private bool IsEnabled()
        {
            var isEnabled = true;

            if (_lineParser.MoreWordsPresent)
            {
                if (_lineParser.CurrentWord.ToLower() == "enabled")
                {
                    isEnabled = true;
                }
                else if (_lineParser.CurrentWord.ToLower() == "disabled")
                {
                    isEnabled = false;
                }
                else
                {
                    throw new ApplicationException("Enabled or Disabled expected");
                }
            }
            // else: Enabled if not present

            return isEnabled;
        }
    }
}

