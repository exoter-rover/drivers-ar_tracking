all: \
	example_without_remote_control \
	example_with_dtrack2_remote_control \
	example_with_simple_remote_control \
	example_listen_to_multicast
%: %.cpp
	g++ -o $* -I . -I Lib/ $< DTrackSDK.cpp Lib/*.cpp
