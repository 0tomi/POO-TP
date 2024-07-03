# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TP2UI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TP2UI_autogen.dir\\ParseCache.txt"
  "TP2UI_autogen"
  )
endif()
