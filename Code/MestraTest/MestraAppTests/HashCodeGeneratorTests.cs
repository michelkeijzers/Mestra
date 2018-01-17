using MestraApp;
using MestraApp.Parsers;
using MestraApp.Writers;
using MestraGeneric;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MestraAppTests
{
    [TestClass()]
    public class HashCodeGeneratorTests
    {
        [TestMethod()]
        public void NoValueCode()
        {
            var generator = new HashCodeGenerator();
            Assert.AreEqual(0, generator.Calculate(251));
        }

        [TestMethod()]
        public void SimpleValueCode()
        {
            var generator = new HashCodeGenerator();
            generator.Add(10);
            Assert.AreEqual(10, generator.Calculate(251));
        }

        [TestMethod()]
        public void TwoValuesCode()
        {
            var generator = new HashCodeGenerator();
            generator.Add(10);
            generator.Add(23);
            Assert.AreEqual(29, generator.Calculate(251));
        }

        [TestMethod()]
        public void ExceedingHashSets()
        {
            var generator = new HashCodeGenerator();
            generator.Add(10);
            generator.Add(23);
            Assert.AreEqual(5, generator.Calculate(8));
        }
    }
}