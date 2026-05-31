
#include "ids.h"

#include "pluginterfaces/base/fplatform.h"
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "projectversion.h"
#include "public.sdk/source/main/pluginfactory.h"

#define stringOriginalFilename "MinimalSawSynth.vst3"
#if SMTG_PLATFORM_64
#define stringFileDescription  "MinimalSawSynth VST3 (64Bit)"
#else
#define stringFileDescription  "MinimalSawSynth VST3"
#endif
#define stringCompanyName      "Local\0"
#define stringLegalCopyright   "Copyright(c) 2026."
#define stringLegalTrademarks  "VST is a trademark of Steinberg Media Technologies GmbH"


namespace MinimalSawSynth {
Steinberg::FUnknown* createProcessorInstance(void*);
Steinberg::FUnknown* createControllerInstance(void*);
}

BEGIN_FACTORY_DEF ("Local", "", "")

   DEF_CLASS2 (INLINE_UID_FROM_FUID(MinimalSawSynth::ProcessorUID),
               Steinberg::PClassInfo::kManyInstances,
               kVstAudioEffectClass,
               "MinimalSawSynth",
               Steinberg::Vst::kDistributable,
               Steinberg::Vst::PlugType::kInstrumentSynth,
               FULL_VERSION_STR,
               kVstVersionString,
               MinimalSawSynth::createProcessorInstance)

   DEF_CLASS2 (INLINE_UID_FROM_FUID(MinimalSawSynth::ControllerUID),
               Steinberg::PClassInfo::kManyInstances,
               kVstComponentControllerClass,
               "MinimalSawSynthController",
               0,
               "",
               FULL_VERSION_STR,
               kVstVersionString,
               MinimalSawSynth::createControllerInstance)

END_FACTORY
