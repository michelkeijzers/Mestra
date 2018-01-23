using MestraApp;
using MestraApp.Parsers;
using MestraApp.Writers;
using MestraGeneric;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MestraAppTests
{
    [TestClass()]
    public class LineWriterTests
    {
        [TestMethod()]
        public void Trigger()
        {
            var result = new LineResult
            {
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOn,
                MidiChannel = 2,
                StartNote = MidiNotes.ENote.A1,
                EndNote = MidiNotes.ENote.A1
            };

            var lineWriter = new LineWriter();
            lineWriter.Write(result);

            //FUTURE not yet tests possible
            
        }
        
    }
}
