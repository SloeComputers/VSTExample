//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Synth.h"

MIDI::Synth* MIDI::Synth::construct()
{
   return new ::Synth();
}
