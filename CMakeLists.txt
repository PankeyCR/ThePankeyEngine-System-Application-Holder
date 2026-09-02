cmake_minimum_required(VERSION 3.15)

project(ThePankeyEngine_System_Application_Holder)

if(NOT TARGET ThePankeyEngine_System_Application_Holder)

    add_library(ThePankeyEngine_System_Application_Holder INTERFACE)

    target_include_directories(
        ThePankeyEngine_System_Application_Holder
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

endif()
