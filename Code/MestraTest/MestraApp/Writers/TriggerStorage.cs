using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MestraApp.Parsers;
using MestraGeneric;

namespace MestraApp.Writers
{
    public class TriggerStorage
    {
        private const int GroupSize = 8;

        private LineResult _result;

        /// <summary>
        /// Trigger used to fill in values from LineResult.
        /// </summary>
        private Trigger _trigger;

        /// <summary>
        /// _trigger, split in all/groups/single.
        /// </summary>
        public List<Trigger> TriggersToSave { get; private set; }

        public TriggerStorage()
        {
            TriggersToSave = new List<Trigger>();
        }

        public void Add(LineResult result)
        {
            _result = result;

            _trigger = new Trigger
            {
                IsEnabled = _result.MidiIsEnabled,
                MidiTriggerType = _result.MidiTriggerType
            };

            switch (_result.MidiTriggerType)
            {
                case Trigger.EMidiTriggerType.NoteOn: // Fall through
                    _trigger.MidiTriggerType = Trigger.EMidiTriggerType.NoteOn;
                    _trigger.MidiChannel = _result.MidiChannel;
                    ParseNotes();
                    break;

                case Trigger.EMidiTriggerType.NoteOff:
                    _trigger.MidiTriggerType = Trigger.EMidiTriggerType.NoteOff;
                    _trigger.MidiChannel = _result.MidiChannel;
                    ParseNotes();
                    break;

                // FUTURE: Other types
                default:
                    throw new ApplicationException("Unknown type");
            }
        }

        private void ParseNotes()
        {
            if ((_result.StartNote == 0) && (_result.EndNote == (MidiNotes.ENote) 127))
            {
                WriteAllNotes();
            }
            else
            {
                WriteGroupsAndSingleNotes();
            }
        }

        private void WriteAllNotes()
        {
            _trigger.IsGroup = true;
            _trigger.All = true;
            TriggersToSave.Add(_trigger);
        }

        private bool IsAtLeastOneFullGroupSpanned => 
            ((int)_result.EndNote - (int)_result.StartNote >= GroupSize) &&
            ((int)_result.StartNote / GroupSize != (int)_result.EndNote / GroupSize);

        private void WriteGroupsAndSingleNotes()
        {
            var note = (int) _result.StartNote;
            var endNote = (int) _result.EndNote;
            var endGroup = (int) _result.EndNote/GroupSize;

            do
            {
                var group = note / GroupSize;
                if ((note % GroupSize == 0) && // Start of group
                    ((endGroup > group) || // End note in next group or
                     ((endGroup == group) && (endNote % GroupSize == GroupSize - 1)))) // End note last of current group
                {
                    WriteGroup(group);
                    note += GroupSize;
                }
                else
                {
                    WriteSingleNote(note);
                    note++;
                }
            } while (note <= endNote);
        }

        private void WriteGroup(int group)
        {

            _trigger.IsGroup = true;
            _trigger.All = false;
            _trigger.Group = group;
            TriggersToSave.Add((Trigger) _trigger.Clone());
        }

        private void WriteSingleNote(int note)
        {
            _trigger.IsGroup = false;
            _trigger.All = false;
            _trigger.Value = note;
            TriggersToSave.Add((Trigger) _trigger.Clone());
        }
    }
}
