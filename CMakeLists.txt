cmake_minimum_required(VERSION 3.16)

# Wir entfernen die Zeile mit EXTRA_COMPONENT_DIRS, 
# da der Manager alles automatisch regelt.

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(fast_scan)