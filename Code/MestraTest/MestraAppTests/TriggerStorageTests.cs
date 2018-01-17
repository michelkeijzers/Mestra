using MestraApp;
using MestraApp.Parsers;
using MestraApp.Writers;
using MestraGeneric;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MestraAppTests
{
    [TestClass()]
    public class TriggerStorageTests
    {
        [TestMethod()]
        public void SingleNote()
        {
            var result = new LineResult
            {
                MidiIsEnabled = true,
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOn,
                MidiChannel = 2,
                StartNote = MidiNotes.ENote.A1,
                EndNote = MidiNotes.ENote.A1
            };

            var triggerWriter = new TriggerStorage();
            triggerWriter.Add(result);

            Assert.AreEqual(1, triggerWriter.TriggersToSave.Count);
            var trigger = triggerWriter.TriggersToSave[0];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(2, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(false, trigger.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.A1, (MidiNotes.ENote) triggerWriter.TriggersToSave[0].Value);
        }

        [TestMethod()]
        public void TwoNotes()
        {
            var result = new LineResult
            {
                MidiIsEnabled = true,
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOn,
                MidiChannel = 34,
                StartNote = MidiNotes.ENote.A1,
                EndNote = MidiNotes.ENote.Ais1
            };

            var triggerWriter = new TriggerStorage();
            triggerWriter.Add(result);

            Assert.AreEqual(2, triggerWriter.TriggersToSave.Count);

            var trigger = triggerWriter.TriggersToSave[0];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(false, trigger.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.A1, (MidiNotes.ENote)trigger.Value);

            trigger = triggerWriter.TriggersToSave[1];
            Assert.AreEqual(true, triggerWriter.TriggersToSave[1].IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(false, trigger.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.Ais1, (MidiNotes.ENote)trigger.Value);
        }

        [TestMethod()]
        public void All()
        {
            var result = new LineResult
            {
                MidiIsEnabled = true,
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOn,
                MidiChannel = 34,
                StartNote = MidiNotes.ENote.C0,
                EndNote = MidiNotes.ENote.G10
            };

            var triggerWriter = new TriggerStorage();
            triggerWriter.Add(result);

            Assert.AreEqual(1, triggerWriter.TriggersToSave.Count);

            var trigger = triggerWriter.TriggersToSave[0];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(true, trigger.All);
        }

        [TestMethod()]
        public void TwoGroups()
        {
            var result = new LineResult
            {
                MidiIsEnabled = true,
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOn,
                MidiChannel = 34,
                StartNote = MidiNotes.ENote.C0,
                EndNote = MidiNotes.ENote.Dis1
            };

            var triggerWriter = new TriggerStorage();
            triggerWriter.Add(result);

            Assert.AreEqual(2, triggerWriter.TriggersToSave.Count);

            var trigger = triggerWriter.TriggersToSave[0];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(true, trigger.IsGroup);
            Assert.AreEqual(0, trigger.Group);

            trigger = triggerWriter.TriggersToSave[1];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(true, trigger.IsGroup);
            Assert.AreEqual(1, trigger.Group);
        }


        [TestMethod()]
        public void OneNoteTwoGroupsThreeNotes()
        {
            var result = new LineResult
            {
                MidiIsEnabled = true,
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOn,
                MidiChannel = 34,
                StartNote = MidiNotes.ENote.G0, // Note 7
                EndNote = MidiNotes.ENote.D2 // Note 26
            };

            var triggerWriter = new TriggerStorage();
            triggerWriter.Add(result);

            Assert.AreEqual(6, triggerWriter.TriggersToSave.Count);

            var trigger = triggerWriter.TriggersToSave[0];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(false, trigger.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.G0, (MidiNotes.ENote) trigger.Value);

            trigger = triggerWriter.TriggersToSave[1];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(true, trigger.IsGroup);
            Assert.AreEqual(1, trigger.Group);

            trigger = triggerWriter.TriggersToSave[2];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(true, trigger.IsGroup);
            Assert.AreEqual(2, trigger.Group);

            trigger = triggerWriter.TriggersToSave[3];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(false, trigger.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.C2, (MidiNotes.ENote) trigger.Value);

            trigger = triggerWriter.TriggersToSave[4];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(false, trigger.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.Cis2, (MidiNotes.ENote) trigger.Value);

            trigger = triggerWriter.TriggersToSave[5];
            Assert.AreEqual(true, trigger.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger.MidiTriggerType);
            Assert.AreEqual(34, trigger.MidiChannel);
            Assert.AreEqual(false, trigger.All);
            Assert.AreEqual(false, trigger.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.D2, (MidiNotes.ENote) trigger.Value);
        }




        [TestMethod()]
        public void TwoDifferentTriggers()
        {
            var result1 = new LineResult
            {
                MidiIsEnabled = true,
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOn,
                MidiChannel = 34,
                StartNote = MidiNotes.ENote.A1, // Note 7
                EndNote = MidiNotes.ENote.A1 // Note 26
            };

            var result2 = new LineResult
            {
                MidiIsEnabled = true,
                ConfigType = LineResult.EConfigType.Trigger,
                MidiTriggerType = MestraGeneric.Trigger.EMidiTriggerType.NoteOff,
                MidiChannel = 35,
                StartNote = MidiNotes.ENote.B1, // Note 7
                EndNote = MidiNotes.ENote.B1 // Note 26
            };

            var triggerWriter = new TriggerStorage();
            triggerWriter.Add(result1);
            triggerWriter.Add(result2);

            Assert.AreEqual(2, triggerWriter.TriggersToSave.Count);

            var trigger1 = triggerWriter.TriggersToSave[0];
            Assert.AreEqual(true, trigger1.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOn, trigger1.MidiTriggerType);
            Assert.AreEqual(34, trigger1.MidiChannel);
            Assert.AreEqual(false, trigger1.All);
            Assert.AreEqual(false, trigger1.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.A1, (MidiNotes.ENote) trigger1.Value);

            var trigger2 = triggerWriter.TriggersToSave[1];
            Assert.AreEqual(true, trigger2.IsEnabled);
            Assert.AreEqual(MestraGeneric.Trigger.EMidiTriggerType.NoteOff, trigger2.MidiTriggerType);
            Assert.AreEqual(35, trigger2.MidiChannel);
            Assert.AreEqual(false, trigger2.All);
            Assert.AreEqual(false, trigger2.IsGroup);
            Assert.AreEqual(MidiNotes.ENote.B1, (MidiNotes.ENote) trigger2.Value);

        }
    }
}
