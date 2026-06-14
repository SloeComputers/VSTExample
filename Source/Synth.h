//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "MIDI/Synth.h"
#include "SIG/ReSample.h"

class Synth : public MIDI::Synth
{
public:
   Synth()
      : MIDI::Synth(NUM_VOICE)
   {
   }

private:
   void setSampleRate(unsigned sample_rate_) override
   {
      re_sample.setOutRate(sample_rate_);
   }

   SIG::Signal sample() override
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

   static constexpr unsigned NUM_VOICE = 8;

   SIG::osc::Ramp                  osc[NUM_VOICE] = {};
   SIG::ReSample<Synth,/* N */ 16> re_sample{*this, SIG::SAMPLE_RATE};
};
