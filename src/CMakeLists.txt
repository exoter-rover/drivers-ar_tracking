include_directories("${PROJECT_SOURCE_DIR}/Lib")
add_subdirectory (Lib) 
rock_library(ar_tracking
    SOURCES ArtDriver.cpp DTrackSDK.cpp Lib/DTrackNet.cpp Lib/DTrackParse.cpp Lib/DTrackParser.cpp
    HEADERS ArtDriver.hpp DTrackSDK.hpp Lib/DTrackDataTypes.h Lib/DTrackNet.h Lib/DTrackParse.hpp Lib/DTrackParser.hpp
    DEPS_PKGCONFIG base-types)



