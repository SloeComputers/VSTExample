//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/main/pluginfactory.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

class Controller : public Steinberg::Vst::EditController
{
public:
   Controller() = default;

   static const Steinberg::FUID& uid()
   {
      const static Steinberg::FUID UID{0x7AA56082, 0xEBC84042, 0xB02A7627, 0xDFC099A4};

      return UID;
   }

   static void registerClass(Steinberg::CPluginFactory* factory_)
   {
      static Steinberg::PClassInfo2 class_info(uid().toTUID(),
                                               Steinberg::PClassInfo::kManyInstances,
                                               kVstComponentControllerClass,
                                               "vstexample_Controller",
                                               0,
                                               "",
                                               nullptr,
                                               "1.0.0.0",
                                               kVstVersionString);

      factory_->registerClass(&class_info, construct);
   }

private:
   static Steinberg::FUnknown* construct(void*)
   {
      return static_cast<Steinberg::Vst::IEditController*>(new Controller());
   }
};
