using MestraApp;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MestraAppTests
{
    [TestClass()]
    public class CommentRemoverTests
    {
        [TestMethod()]
        public void RemoveFullComments()
        {
            var content = new ConfigFileContent();
            content.Lines.Add("// Comment");
            var remover = new CommentRemover(content);
            remover.Run();
            Assert.AreEqual(0, content.Lines.Count);
        }

        [TestMethod()]
        public void RemoveHalfLineComment()
        {
            var content = new ConfigFileContent();
            content.Lines.Add("Test// Comment");
            var remover = new CommentRemover(content);
            remover.Run();
            Assert.AreEqual(1, content.Lines.Count);
            Assert.AreEqual("Test", content.Lines[0]);
        }


        [TestMethod()]
        public void RemoveEmptyLine()
        {
            var content = new ConfigFileContent();
            content.Lines.Add("");
            var remover = new CommentRemover(content);
            remover.Run();
            Assert.AreEqual(0, content.Lines.Count);
        }

        [TestMethod()]
        public void RemoveWhiteSpaceLine()
        {
            var content = new ConfigFileContent();
            content.Lines.Add("  \t \t");
            var remover = new CommentRemover(content);
            remover.Run();
            Assert.AreEqual(0, content.Lines.Count);
        }

        [TestMethod()]
        public void TrimLine()
        {
            var content = new ConfigFileContent();
            content.Lines.Add(" Test ");
            var remover = new CommentRemover(content);
            remover.Run();
            Assert.AreEqual(1, content.Lines.Count);
            Assert.AreEqual("Test", content.Lines[0]);
        }
    }
}
