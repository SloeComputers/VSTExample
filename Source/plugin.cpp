//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "public.sdk/source/main/pluginfactory.h"

#include "Processor.h"
#include "Controller.h"

using namespace Steinberg;

SMTG_EXPORT_SYMBOL IPluginFactory* PLUGIN_API GetPluginFactory()
{
   if (gPluginFactory == nullptr)
   {
      static PFactoryInfo factory_info("Sloe Computers",
                                       "https://github.com/SloeComputers",
                                       "sloecomputer@gmail.com",
                                       PFactoryInfo::kNoFlags);

      gPluginFactory = new CPluginFactory(factory_info);

      Processor::registerClass(gPluginFactory);
      Controller::registerClass(gPluginFactory);
   }
   else
   {
      gPluginFactory->addRef();
   }

   return gPluginFactory;
}
