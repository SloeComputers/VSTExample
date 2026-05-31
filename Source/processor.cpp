
#include "ids.h"

#include "pluginterfaces/vst/ivstevents.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

#include <cmath>
#include <cstdint>

namespace MinimalSawSynth {

class Processor : public Steinberg::Vst::AudioEffect
{
public:
   Processor()
   {
      setControllerClass(ControllerUID);
   }

private:
   Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) override
   {
      Steinberg::tresult result = Steinberg::Vst::AudioEffect::initialize(context);
      if (result != Steinberg::kResultOk)
         return result;

      addEventInput(STR16("MIDI In"), 1);
      addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

      return Steinberg::kResultOk;
   }

   Steinberg::tresult PLUGIN_API canProcessSampleSize(int32_t sample_size) override
   {
      return (sample_size == Steinberg::Vst::kSample32 ||
              sample_size == Steinberg::Vst::kSample64) ?
                   Steinberg::kResultTrue :
                   Steinberg::kResultFalse;
   }

   Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state_) override
   {
      if (state_)
      {
         active = false;
      }

      return Steinberg::Vst::AudioEffect::setActive(state_);
   }

   Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) override
   {
      if (data.numOutputs == 0 || data.outputs[0].numChannels == 0)
         return Steinberg::kResultOk;

      if (processSetup.symbolicSampleSize == Steinberg::Vst::kSample64)
         render<Steinberg::Vst::Sample64>(data);
      else
         render<Steinberg::Vst::Sample32>(data);

      return Steinberg::kResultOk;
   }

   template <typename Sample>
   void render(Steinberg::Vst::ProcessData& data)
   {
      unsigned event_idx = 0;
      unsigned event_num = data.inputEvents ? data.inputEvents->getEventCount() : 0;
      Sample** out = reinterpret_cast<Sample**>(data.outputs[0].channelBuffers32);

      for(unsigned sample = 0; sample < unsigned(data.numSamples); ++sample)
      {
         while(event_idx < event_num)
         {
            Steinberg::Vst::Event event{};

            if (data.inputEvents->getEvent(event_idx, event) != Steinberg::kResultOk ||
                    event.sampleOffset > sample)
            {
               break;
            }

            switch(event.type)
            {
            case Steinberg::Vst::Event::kNoteOnEvent:
               if (event.noteOn.velocity > 0.0)
                  noteOn(event.noteOn.pitch, event.noteOn.velocity);
               break;

            case Steinberg::Vst::Event::kNoteOffEvent:
               if (event.noteOff.pitch == pitch)
                  active = false;
               break;

            default:
               break;
            }

            ++event_idx;
         }

         float value = 0.0f;
         if (active)
         {
            value = float((phase * 2) - 1) * gain;
            phase += frequency / processSetup.sampleRate;
            if (phase >= 1.)
               phase -= std::floor(phase);
         }

         const int16_t quantized = int16_t(value * 32767.f);
         value = float(quantized) / 32768.f;

         for(unsigned channel = 0; channel < data.outputs[0].numChannels; ++channel)
         {
            out[channel][sample] = Sample(value);
         }
      }
   }

   void noteOn(int16_t pitch_, float velocity_)
   {
      pitch     = pitch_;
      frequency = 440. * pow(2.0, (pitch - 69) / 12.0);
      gain      = velocity_ * 0.2f;
      phase     = 0.0;
      active    = true;
   }

   bool    active{false};
   int16_t pitch{};
   double  frequency{};
   double  phase{};
   float   gain{};
};

Steinberg::FUnknown* createProcessorInstance(void*)
{
   return static_cast<Steinberg::Vst::IAudioProcessor*>(new Processor());
}

} // namespace MinimalSawSynth
