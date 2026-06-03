//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include <algorithm>

#include "pluginterfaces/vst/ivstevents.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

#include "Processor.h"
#include "Controller.h"

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
     synth.noteOffAll();
  }

  return Vst::AudioEffect::setActive(state_);
}

tresult PLUGIN_API Processor::process(Vst::ProcessData& data)
{
   if (data.numOutputs == 0 || data.outputs[0].numChannels == 0)
      return kResultOk;

   int32_t    num_samples = data.numSamples;
   int32_t    event_idx   = 0;
   int32_t    num_events  = data.inputEvents != nullptr ? data.inputEvents->getEventCount() : 0;
   int32_t    event_sample;
   Vst::Event event{};

   if ((event_idx < num_events) &&
       (data.inputEvents->getEvent(event_idx, event) == kResultOk))
      event_sample = std::min(event.sampleOffset, num_samples);
   else
      event_sample = num_samples;

   for(int32_t sample = 0; sample < num_samples;)
   {
      if (sample >= event_sample)
      {
         switch(event.type)
         {
         case Vst::Event::kNoteOnEvent:
            synth.noteOn(event.noteOn.pitch, event.noteOn.velocity);
            break;

         case Vst::Event::kNoteOffEvent:
            synth.noteOff(event.noteOff.pitch);
            break;

         default:
            break;
         }

         ++event_idx;

         if ((event_idx < num_events) &&
             (data.inputEvents->getEvent(event_idx, event) == kResultOk))
            event_sample = std::min(event.sampleOffset, num_samples);
         else
            event_sample = num_samples;
      }
      else
      {
         if (processSetup.symbolicSampleSize == Vst::kSample64)
            render<Vst::Sample64>(data, sample, event_sample);
         else
            render<Vst::Sample32>(data, sample, event_sample);

         sample = event_sample;
      }
   }

   return kResultOk;
}

template <typename SAMPLE>
void Processor::render(Vst::ProcessData& data, int32_t start, int32_t end)
{
   SAMPLE** buffer = reinterpret_cast<SAMPLE**>(data.outputs[0].channelBuffers32);

   for(int32_t i = start; i < end; ++i)
   {
      SIG::Float value = synth.getSample();

      for(int32_t channel = 0; channel < data.outputs[0].numChannels; ++channel)
      {
         buffer[channel][i] = SAMPLE(value);
      }
   }
}
