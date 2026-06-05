//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Synth.h"
#include "Midi.h"
#include "Audio.h"

static Synth<8> synth{};
static Audio    audio{};
static Midi     midi{};

int entry()
{
   midi.attachInstrument(synth);
   audio.attachInstrument(synth);

   return 0;
}
