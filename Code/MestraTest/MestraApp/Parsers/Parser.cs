using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using MestraApp.Writers;

namespace MestraApp.Parsers
{
    public class Parser
    {
        public ConfigFileContent Content { get; private set; }

        public Parser(ConfigFileContent content)
        {
            Content = content;
        }

        public void Parse()
        {
            var writer = new LineWriter();
            foreach (var lineParser in Content.Lines.Select(line => new LineParser(line)))
            {
                lineParser.Parse();
                writer.Write(lineParser.LineResult);
            }
        }
    }
}

