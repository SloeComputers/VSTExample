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

add_subdirectory(Source)
