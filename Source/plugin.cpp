//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "public.sdk/source/main/pluginfactory.h"

#include "Config.h"
#include "Processor.h"
#include "Controller.h"

using namespace Steinberg;

SMTG_EXPORT_SYMBOL IPluginFactory* PLUGIN_API GetPluginFactory()
{
   if (gPluginFactory == nullptr)
   {
      static PFactoryInfo factory_info(PROJECT_OWNER,
                                       PROJECT_URL,
                                       PROJECT_EMAIL,
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
