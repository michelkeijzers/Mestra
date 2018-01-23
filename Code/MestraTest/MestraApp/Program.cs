using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MestraApp.Parsers;

namespace MestraApp
{
    // ReSharper disable once ClassNeverInstantiated.Global
    public class Program
    {
        static void Main(string[] args)
        {
            var content = new ConfigFileContent();
            var reader = new ConfigFileReader(args[1]);
            reader.Read(content);

            var remover = new CommentRemover(content);
            remover.Run();

            var parser = new Parser(content);
            parser.Parse();
        }
    }
}
