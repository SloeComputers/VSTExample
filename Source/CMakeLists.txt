#-------------------------------------------------------------------------------
# Copyright (c) 2026 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

smtg_add_vst3plugin(vstexample
                    Processor.cpp
                    plugin.cpp)

target_compile_features(vstexample PUBLIC cxx_std_17)

target_link_libraries(vstexample PRIVATE sdk)

smtg_target_configure_version_file(vstexample)

if(SMTG_MAC)
    smtg_target_set_bundle(vstexample
        BUNDLE_IDENTIFIER com.local.vstexample
        COMPANY_NAME "Sloe Computers")

   set_target_properties(vstexample PROPERTIES
      MACOSX_BUNDLE_INFO_PLIST           "${CMAKE_CURRENT_LIST_DIR}/../cmake/MacVST3Info.plist.in"
      MACOSX_BUNDLE_BUNDLE_NAME          "vstexample"
      MACOSX_BUNDLE_GUI_IDENTIFIER       "com.local.vstexample"
      MACOSX_BUNDLE_BUNDLE_VERSION       "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
      MACOSX_BUNDLE_LONG_VERSION_STRING  "${PROJECT_VERSION}"
      MACOSX_BUNDLE_INFO_STRING          "${PROJECT_DESCRIPTION}"
      MACOSX_BUNDLE_COPYRIGHT            "Copyright (C) 2026 Sloe Computers.")

   add_custom_command(TARGET vstexample POST_BUILD
      COMMAND /usr/bin/codesign --force --sign - --deep "$<TARGET_BUNDLE_DIR:vstexample>"
      COMMENT "Ad-hoc signing vstexample VST3 bundle")
endif()
