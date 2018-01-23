using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MestraApp
{
    public class ConfigFileReader
    {
        private readonly string _fileName;
        
        public ConfigFileReader(string fileName)
        {
            _fileName = fileName;
        }

        public void Read(ConfigFileContent content)
        {
            try
            {
                content.Lines = File.ReadAllText(_fileName).Split('\n').ToList<string>();
            }
            catch (FileNotFoundException exception)
            {
                Console.WriteLine("File not found: {0}", exception.Message);
            }
        }
    }
}
