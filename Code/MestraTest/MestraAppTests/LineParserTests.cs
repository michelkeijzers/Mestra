using MestraApp;
using MestraApp.Parsers;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MestraAppTests
{
    [TestClass()]
    public class LineParserTests
    {
        [TestMethod()]
        public void TriggerKeyword()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(LineResult.EConfigType.Trigger, lineParser.LineResult.ConfigType);
        }
        

        [TestMethod()]
        public void InstructionName()
        {
            var lineParser = new LineParser("Send");
            lineParser.Parse();
            Assert.AreEqual(LineResult.EConfigType.Instruction, lineParser.LineResult.ConfigType);
        }


        [TestMethod()]
        public void ProgramMidiChannel1()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 PlayC2");
            lineParser.Parse();
            Assert.AreEqual(1, lineParser.LineResult.MidiChannel);
        }


        [TestMethod()]
        public void TrigggerNameSimple()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 Play");
            lineParser.Parse();
            Assert.AreEqual("Play", lineParser.LineResult.MidiTriggerName);
        }

        [TestMethod()]
        public void TrigggerNameStartingWithUnderscore()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 _Play");
            lineParser.Parse();
            Assert.AreEqual("_Play", lineParser.LineResult.MidiTriggerName);
        }

        [TestMethod()]
        public void TrigggerNameUnderscoreWithin()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 Play_C1");
            lineParser.Parse();
            Assert.AreEqual("Play_C1", lineParser.LineResult.MidiTriggerName);
        }

        [TestMethod()]
        public void TrigggerNameDigitWithin()
        {
            var lineParser = new LineParser("trigger noteon 1 C1 Play1");
            lineParser.Parse();
            Assert.AreEqual("Play1", lineParser.LineResult.MidiTriggerName);
        }


        [TestMethod()]
        public void ProgramName()
        {
            var lineParser = new LineParser("program Name");
            lineParser.Parse();
            Assert.AreEqual(LineResult.EConfigType.Program, lineParser.LineResult.ConfigType);
        }

        [TestMethod()]
        public void ProgramName()
        {
            var lineParser = new LineParser("program Name:");
            lineParser.Parse();
            Assert.AreEqual(LineResult.EConfigType.Program, lineParser.LineResult.ConfigType);
        }

        [TestMethod()]
        public void ProgramNameSimple()
        {
            var lineParser = new LineParser("program Name:");
            lineParser.Parse();
            Assert.AreEqual("Name", lineParser.LineResult.ProgramName);
        }

        [TestMethod()]
        public void ProgramMixedKeyword()
        {
            var lineParser = new LineParser("ProGram Name:");
            lineParser.Parse();
            Assert.AreEqual("Name", lineParser.LineResult.ProgramName);
        }
    }
}

