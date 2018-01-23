using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MestraApp.Parsers;

namespace MestraApp.Writers
{
    public class LineWriter
    {
        public void Write(LineResult result)
        {
            switch (result.ConfigType)
            {
                case LineResult.EConfigType.Trigger:
                    var triggerWriter = new TriggerStorage();
                    triggerWriter.Add(result);
                    break;

                case LineResult.EConfigType.Program:
                    break;

                case LineResult.EConfigType.Instruction:
                    break;

                default:
                    throw new ApplicationException("Unknown type");
            }
        }
    }
}
