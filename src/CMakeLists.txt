rock_library(ar_tracking
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(ar_tracking_bin Main.cpp
    DEPS ar_tracking)

