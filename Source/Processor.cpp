//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Processor.h"
#include "Controller.h"

#include "pluginterfaces/vst/ivstevents.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

#include <cmath>
#include <cstdint>

using namespace Steinberg;

Processor::Processor()
{
   setControllerClass(Controller::uid());
}

tresult PLUGIN_API Processor::initialize(FUnknown* context)
{
   tresult result = Vst::AudioEffect::initialize(context);
   if (result != kResultOk)
      return result;

   addEventInput(STR16("MIDI In"), 1);
   addAudioOutput(STR16("Stereo Out"), Vst::SpeakerArr::kStereo);

   return kResultOk;
}

tresult PLUGIN_API Processor::canProcessSampleSize(int32_t sample_size)
{
   return (sample_size == Vst::kSample32 || sample_size == Vst::kSample64) ? kResultTrue
                                                                           : kResultFalse;
}

tresult PLUGIN_API Processor::setActive(TBool state_)
{
  if (state_)
  {
     active = false;
  }

  return Vst::AudioEffect::setActive(state_);
}

tresult PLUGIN_API Processor::process(Vst::ProcessData& data)
{
   if (data.numOutputs == 0 || data.outputs[0].numChannels == 0)
      return kResultOk;

   if (processSetup.symbolicSampleSize == Vst::kSample64)
      render<Vst::Sample64>(data);
   else
      render<Vst::Sample32>(data);

   return kResultOk;
}

template <typename SAMPLE>
void Processor::render(Vst::ProcessData& data)
{
   unsigned event_idx = 0;
   unsigned event_num = data.inputEvents ? data.inputEvents->getEventCount() : 0;
   SAMPLE** out = reinterpret_cast<SAMPLE**>(data.outputs[0].channelBuffers32);

   for(unsigned sample = 0; sample < unsigned(data.numSamples); ++sample)
   {
      while(event_idx < event_num)
      {
         Vst::Event event{};

         if ((data.inputEvents->getEvent(event_idx, event) != kResultOk) ||
             (event.sampleOffset > sample))
         {
            break;
         }

         switch(event.type)
         {
         case Vst::Event::kNoteOnEvent:
            if (event.noteOn.velocity > 0.0)
               noteOn(event.noteOn.pitch, event.noteOn.velocity);
            break;

         case Vst::Event::kNoteOffEvent:
            if (event.noteOff.pitch == pitch)
               active = false;
            break;

         default:
            break;
         }

         ++event_idx;
      }

      SIG::Float value{};

      if (active)
      {
         value = osc();
      }

      for(unsigned channel = 0; channel < data.outputs[0].numChannels; ++channel)
      {
         out[channel][sample] = SAMPLE(value);
      }
   }
}

void Processor::noteOn(int16_t midi_note_, float velocity_)
{
   pitch  = midi_note_;
   active = true;

   osc.sync();
   osc.setNote(midi_note_);
   osc.gain = velocity_ * 0.2f;
}
