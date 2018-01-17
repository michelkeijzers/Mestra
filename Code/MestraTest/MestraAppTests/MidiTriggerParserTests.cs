using System.Runtime.InteropServices;
using MestraApp;
using MestraApp.Parsers;
using MestraApp.Writers;
using MestraGeneric;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MestraAppTests
{
    [TestClass()]
    public class MidiTriggerParserTests
    {
        [TestMethod()]
        public void TriggerNoteOn()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 PlayC2");
            lineParser.Parse();

            var parser = new MidiTriggerParser(lineParser);
            parser.Parse();

            Assert.AreEqual(Trigger.EMidiTriggerType.NoteOn, lineParser.LineResult.MidiTriggerType);
            Assert.AreEqual(1, lineParser.LineResult.MidiChannel);
            Assert.AreEqual(MidiNotes.ENote.C1, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.C1, lineParser.LineResult.EndNote);
        }


        [TestMethod()]
        public void TriggerNoteOff()
        {
            var lineParser = new LineParser("trigger noteoff 1 C1 PlayC2");
            lineParser.Parse();

            var parser = new MidiTriggerParser(lineParser);
            parser.Parse();

            Assert.AreEqual(Trigger.EMidiTriggerType.NoteOff, lineParser.LineResult.MidiTriggerType);
            Assert.AreEqual(1, lineParser.LineResult.MidiChannel);
        }

        [TestMethod()]
        public void TriggerMidiChannel1()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(1, lineParser.LineResult.MidiChannel);
        }

        [TestMethod()]
        public void TriggerMidiChannel16()
        {
            var lineParser = new LineParser("trigger noteon 16 C1 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(16, lineParser.LineResult.MidiChannel);
        }

        [TestMethod()]
        public void TriggerMidiNoteA0()
        {
            var lineParser = new LineParser("trigger noteon 1 C0 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.C0, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.C0, lineParser.LineResult.EndNote);
        }
        [TestMethod()]
        public void TriggerMidiNoteC1()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.C1, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.C1, lineParser.LineResult.EndNote);
        }

        [TestMethod()]
        public void TriggerMidiNoteCis1()
        {
            var lineParser = new LineParser("trigger noteon 1 C#1 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.Cis1, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.Cis1, lineParser.LineResult.EndNote);
        }

        [TestMethod()]
        public void TriggerMidiNoteG10()
        {
            var lineParser = new LineParser("trigger noteon 1 G10 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.G10, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.G10, lineParser.LineResult.EndNote);
        }

        [TestMethod()]
        public void TriggerMidiNoteAll()
        {
            var lineParser = new LineParser("trigger noteon 1 All PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.C0, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.G10, lineParser.LineResult.EndNote);
        }

        [TestMethod()]
        public void TriggerMidiNoteD1ToE3()
        {
            var lineParser = new LineParser("trigger noteon 1 D1-E3 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.D1, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.E3, lineParser.LineResult.EndNote);
        }

        [TestMethod()]
        public void TriggerMidiNoteDis1ToE3()
        {
            var lineParser = new LineParser("trigger noteon 1 D#1-E3 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.Dis1, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.E3, lineParser.LineResult.EndNote);
        }

        [TestMethod()]
        public void TriggerMidiNoteD1ToGis3()
        {
            var lineParser = new LineParser("trigger noteon 1 D1-G#3 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(MidiNotes.ENote.D1, lineParser.LineResult.StartNote);
            Assert.AreEqual(MidiNotes.ENote.Gis3, lineParser.LineResult.EndNote);
        }
    }
}
