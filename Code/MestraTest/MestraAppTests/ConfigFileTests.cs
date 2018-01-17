using MestraApp;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MestraAppTests
{
    [TestClass()]
    public class ConfigFileContentTests
    {
        [TestMethod()]
        public void NumberOfLinesOfConfigFile()
        {
            var content = new ConfigFileContent();
            var reader = new ConfigFileReader(@"D:\mestra.txt");
            reader.Read(content);
            Assert.AreEqual(2, content.Lines.Count);
        }
    }
}
