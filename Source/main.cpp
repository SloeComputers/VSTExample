//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Synth.h"
#include "PLT/PLGMidi.h"
#include "PLT/PLGAudio.h"

static Synth<8> synth{};
static Audio    audio{};
static Midi     midi{};

int plugin_main()
{
   midi.attachInstrument(synth);
   audio.attachInstrument(synth);

   return 0;
}
