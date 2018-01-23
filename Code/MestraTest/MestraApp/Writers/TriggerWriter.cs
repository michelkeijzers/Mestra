using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MestraGeneric;

namespace MestraApp.Writers
{
    public class TriggerWriter
    {
        private readonly byte _nrOfHashSets;

        private readonly TriggerStorage _storage;

        public List<byte> Memory { get; private set; }

        readonly List<List<Trigger>> _triggerHashSets; 

        public TriggerWriter(TriggerStorage storage, byte nrOfHashSets)
        {
            _storage = storage;
            _nrOfHashSets = nrOfHashSets;
            _triggerHashSets = new List<List<Trigger>>();

            for (var index = 0; index < _nrOfHashSets; index++)
            {
                _triggerHashSets.Add(new List<Trigger>());
            }

            Memory = new List<byte>();
        }


        // Split in hash sets.
        public void Write()
        {
            foreach (var trigger in _storage.TriggersToSave)
            {
                var generator = new HashCodeGenerator();
                generator.Add(trigger.Data[0]);
                generator.Add(trigger.Data[1]);
                generator.Add(trigger.Data[2]);
                _triggerHashSets[generator.Calculate(_nrOfHashSets)].Add(trigger);
            }

            WriteMemory();
        }

        private void WriteMemory()
        {
            WriteTableStarts();
            WriteTableContents();
        }

        /// <summary>
        /// 1 bytes: _nrOfHasSets;
        /// Each start index has 2 bytes, amount: _nrOfHashSets;
        /// </summary>
        private void WriteTableStarts()
        {
            Memory.Add(_nrOfHashSets);

            var index = 0;
            foreach (var hashSet in _triggerHashSets)
            {
                Memory.Add((byte) (index / 256));
                Memory.Add((byte) (index % 256));
                index += hashSet.Count * 3; // 3 bytes per trigger
            }
        }

        private void WriteTableContents()
        {
            foreach (var value in from hashSet in _triggerHashSets
                                  from trigger in hashSet
                                  from value in trigger.Data select value)
            {
                Memory.Add(value);
            }
        }
    }
}
