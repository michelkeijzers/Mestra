using System;

namespace MestraGeneric
{
    public class Trigger : ICloneable
    {
        public byte[] Data  { get; set; }

        public enum EMidiTriggerType
        {
            NoteOn = 0x8,
            NoteOff = 0x9
        }

        public Trigger()
        {
            Data = new byte[3];
        }

        public bool IsEnabled
        {
            get { return (Data[0] & 0x80) == 0x80; } // MSB
            set { Data[0] = (byte)((Data[0] & 0x7F) + (value ? 0x80 : 0x00)); }
        }

        public EMidiTriggerType MidiTriggerType
        {
            get { return (EMidiTriggerType)(Data[0] & 0x0F); }
            set { Data[0] = (byte)((Data[0] & 0x80) + (byte)value); } // MIDI = 000 (bits 6~4
        }

        public int MidiChannel
        {
            get { return Data[1]; }
            set { Data[1] = (byte)value; }
        }

        public bool IsGroup
        {
            get { return (Data[2] & 0x80) == 0x80; }
            set { Data[2] = (byte)((Data[2] & 0x7F) + (value ? 0x80 : 0x00)); }
        }

        public bool All
        {
            get { return (Data[2] & 0x40) == 0x40; }
            set { Data[2] = (byte)((Data[2] & 0xBF) + (value ? 0x40 : 0x00)); }
        }

        public int Group
        {
            get { return (Data[2] & 0x3C) >> 2; }
            set { Data[2] = (byte)((Data[2] & 0xC3) + (value << 2)); }
        }


        public int Value
        {
            get { return Data[2] & 0x7F; }
            set { Data[2] = (byte)((Data[2] & 0x80) + value); }
        }

        /// <summary>
        /// Copy data.
        /// </summary>
        /// <returns></returns>
        public object Clone()
        {
            var trigger = (Trigger)MemberwiseClone();
            trigger.Data = new[] { Data[0], Data[1], Data[2] };
            return trigger;
        }
    }
}
