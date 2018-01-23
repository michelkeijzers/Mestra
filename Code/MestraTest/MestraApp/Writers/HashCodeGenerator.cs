using System.Collections.Generic;
using System.Linq;

namespace MestraApp.Writers
{
    public class HashCodeGenerator
    {
        private readonly List<byte> _data;

        public HashCodeGenerator()
        {
            _data = new List<byte>(); 
        }

        public void Add(byte value)
        {
            _data.Add(value);
        }

        public byte Calculate(byte maxSets)
        {
            var hash = _data.Aggregate<byte, byte>(0, (current, data) => (byte) (current ^ data));
            return (byte) (hash % maxSets);
        }
    }
}
