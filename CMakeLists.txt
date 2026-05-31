
cmake_minimum_required(VERSION 3.20)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

project(MinimalSawSynth
        VERSION 1.0.0.0
        DESCRIPTION "Minimal saw wave VST3 instrument")

set(vst3sdk_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/VST_SDK/vst3sdk" CACHE PATH "VST3 SDK path")

set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES 0)
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES 0)
set(SMTG_ENABLE_VSTGUI_SUPPORT 0)
set(SMTG_CREATE_PLUGIN_LINK 0)
set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(MinimalSawSynth
                    source/controller.cpp
                    source/entry.cpp
                    source/processor.cpp)

target_compile_features(MinimalSawSynth PUBLIC cxx_std_17)
target_link_libraries(MinimalSawSynth PRIVATE sdk)

smtg_target_configure_version_file(MinimalSawSynth)

if(SMTG_MAC)
    smtg_target_set_bundle(MinimalSawSynth
        BUNDLE_IDENTIFIER com.local.minimalsawsynth
        COMPANY_NAME "Local")
endif()
