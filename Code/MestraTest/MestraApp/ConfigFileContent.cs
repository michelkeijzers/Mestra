using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MestraApp
{
    public class ConfigFileContent
    {
        public List<string> Lines { get; set; }
        
        public ConfigFileContent()
        {
            Lines = new List<string>();
        }
    }
}
