#-------------------------------------------------------------------------------
# Copyright (c) 2026 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(VSTExample
        LANGUAGES CXX
        VERSION 0.0
        DESCRIPTION "Example VST3-PDK plugin"
        HOMEPAGE_URL "https://github.com/SloeComputers")

set(PDK_PROJ_OWNER "Sloe Computers")
set(PDK_PROJ_EMAIL "sloecomputer@gmail.com")

add_subdirectory(PDK)

add_subdirectory(Source)
