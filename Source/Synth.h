//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

// XXX undo some crazy namespace corruption by the VST3 build environment
#undef RELEASE

#include "SIG/SIG.h"
#include "MIDI/Instrument.h"
#include "PLT/PLGAudio.h"

template <unsigned NUM_VOICE>
class Synth
   : public MIDI::Instrument
   , public Audio::Instrument
{
public:
   Synth()
      : MIDI::Instrument(NUM_VOICE)
   {
   }

private:
   SIG::Signal getSample() override
   {
      SIG::Signal signal{};

      for(unsigned i = 0; i < NUM_VOICE; ++i)
         signal += osc[i]();

      return signal;
   }

   void voiceOn(unsigned voice_, uint8_t note_, uint8_t velocity_) override
   {
      osc[voice_].setNote(note_);
      osc[voice_].gain = SIG::Signal(velocity_) / (127 * NUM_VOICE);
      osc[voice_].sync();
   }

   void voiceOff(unsigned voice_, uint8_t velocity_) override
   {
      osc[voice_].gain = 0.0;
   }

   void voiceMute(unsigned voice_) override
   {
      osc[voice_].gain = 0.0;
   }

   SIG::osc::Ramp osc[NUM_VOICE] = {};
};
