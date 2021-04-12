#include "midi.h"

using namespace avrlib;
using namespace grids;

struct LowPriorityBufferSpecs
{
    enum
    {
        buffer_size = 128,
        data_size = 8,
    };
    typedef avrlib::DataTypeForSize<data_size>::Type Value;
};

struct HighPriorityBufferSpecs
{
    enum
    {
        buffer_size = 16,
        data_size = 8,
    };
    typedef avrlib::DataTypeForSize<data_size>::Type Value;
};

class MidiDispatcher : public midi::MidiDevice
{
public:
    typedef avrlib::RingBuffer<LowPriorityBufferSpecs> OutputBufferLowPriority;
    typedef avrlib::RingBuffer<HighPriorityBufferSpecs> OutputBufferHighPriority;

    static uint8_t readable_high_priority()
    {
        return OutputBufferHighPriority::readable();
    }

    static uint8_t readable_low_priority()
    {
        return OutputBufferLowPriority::readable();
    }

    static uint8_t ImmediateReadHighPriority()
    {
        return OutputBufferHighPriority::ImmediateRead();
    }

    static uint8_t ImmediateReadLowPriority()
    {
        return OutputBufferLowPriority::ImmediateRead();
    }

    MidiDispatcher() {}

    static void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
    static void NoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
    //static void ControlChange(uint8_t channel, uint8_t controller, uint8_t value);
};

uint8_t midi_state = 0;
uint8_t midi_shuffle = 0;
uint8_t state_mask = 0b11111111;

void MidiDispatcher::NoteOn(uint8_t channel, uint8_t note, uint8_t velocity){

  state_mask = 0b00111111;
  const uint8_t GM_RESET = 12;  //C0

  uint8_t& state = midi_state;

  if(note == GM_RESET) {
    pattern_generator.Reset();
    pattern_generator.TickClock(1);
    return;
  }

  if(velocity > 0 && velocity <= 127)
  {
    bool won = (Random::GetByte() / 2) < velocity;
    if (note == (GM_RESET + 2))
      won ? state |= 1 : state |= 8;
    else if (note == (GM_RESET + 4))
      won ? state |= 2 : state |= 16;
    else if (note == (GM_RESET + 5))
      won ? state |= 4 : state |= 32;
    else if (note == (GM_RESET + 7))
      won ? state |= 64 : state |= 128;
  }
  else
  {
    if (note == (GM_RESET + 2))
      state &= ~(1|8);
    else if ( note == (GM_RESET + 4))
       state &= ~(2|16);
    else if (note == (GM_RESET + 5))
      state &= ~(4|32);
    else if (note == (GM_RESET + 7))
      state &= ~(64|128);
  }
}
void MidiDispatcher::NoteOff(uint8_t channel, uint8_t note, uint8_t velocity){
  MidiDispatcher::NoteOn(channel, note, 0);
}

midi::MidiStreamParser<MidiDispatcher> midi_dispatcher;
RingBuffer<SerialInput<SerialPort0> > midi_buffer;