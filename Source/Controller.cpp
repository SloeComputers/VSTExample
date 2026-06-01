
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace MinimalSawSynth {

class Controller : public Steinberg::Vst::EditController{};

Steinberg::FUnknown* createControllerInstance(void*)
{
   return static_cast<Steinberg::Vst::IEditController*> (new Controller);
}

} // namespace MinimalSawSynth
