//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

// XXX undo some crazy namespace corruption by the VST3 build environment
#undef RELEASE

#include "SIG/SIG.h"

class Synth
{
public:
   Synth() = default;

   void noteOn(int16_t midi_note_, float velocity_)
   {
      if (velocity_ <= 0.0)
         return;

      osc.setNote(midi_note_);
      osc.gain = velocity_ * 0.2f;
      osc.sync();

      note   = midi_note_;
      active = true;
   }

   void noteOff(int16_t midi_note_)
   {
      if (midi_note_ == note)
         active = false;
   }

   void noteOffAll()
   {
      active = false;
   }

   SIG::Signal getSample()
   {
      return active ? osc() : SIG::Float(0.0);
   }

private:
   bool           active{false};
   int16_t        note{};
   SIG::osc::Ramp osc{};
};
