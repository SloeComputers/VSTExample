//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/main/pluginfactory.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

// Undo some crazy namespace corruption by the VST3 build environment
#undef RELEASE

#include "SIG/SIG.h"

class Processor : public Steinberg::Vst::AudioEffect
{
public:
   Processor();

   static const Steinberg::FUID& uid()
   {
      const static Steinberg::FUID UID{0x644191FF, 0xCE364B5B, 0x87AADC4B, 0xFDD5EB7F};

      return UID;
   }

   static void registerClass(Steinberg::CPluginFactory* factory_)
   {
      static Steinberg::PClassInfo2 class_info(uid().toTUID(),
                                               Steinberg::PClassInfo::kManyInstances,
                                               kVstAudioEffectClass,
                                               "vstexample",
                                               Steinberg::Vst::kDistributable,
                                               Steinberg::Vst::PlugType::kInstrumentSynth,
                                               nullptr,
                                               "1.0.0.0",
                                               kVstVersionString);

      factory_->registerClass(&class_info, construct);
   }

private:
   Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) override;
   Steinberg::tresult PLUGIN_API canProcessSampleSize(int32_t sample_size) override;
   Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) override;
   Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) override;

   static Steinberg::FUnknown* construct(void*)
   {
      return static_cast<Steinberg::Vst::IAudioProcessor*>(new Processor());
   }

   template <typename SAMPLE>
   void render(Steinberg::Vst::ProcessData& data);

   void noteOn(int16_t pitch, float velocity);

   bool           active{false};
   int16_t        pitch{};
   SIG::osc::Ramp osc{};
};
