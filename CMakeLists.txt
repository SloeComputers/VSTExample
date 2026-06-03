#-------------------------------------------------------------------------------
# Copyright (c) 2026 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(VSTExample
        LANGUAGES CXX
        VERSION 0.0
        DESCRIPTION "Example VST3 plugin")

add_subdirectory(PDK)

set(VST3SDK_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/VST_SDK/vst3sdk" CACHE PATH "VST3 SDK path")

set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES 0)
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES  0)
set(SMTG_ENABLE_VSTGUI_SUPPORT        0)
set(SMTG_CREATE_PLUGIN_LINK           0)
set(SMTG_VSTGUI_ROOT                  "${VST3SDK_SOURCE_DIR}")

add_subdirectory(${VST3SDK_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)

smtg_enable_vst3_sdk()

add_subdirectory(Source)
