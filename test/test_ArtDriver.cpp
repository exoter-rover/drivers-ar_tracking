#include <boost/test/unit_test.hpp>
#include <ar_tracking/ArtDriver.hpp>

using namespace artracking;

BOOST_AUTO_TEST_CASE(print_data)
{
    artracking::ARTDriver artDriver;
    std::string ip_host="131.176.25.107";
    unsigned short server_port=5000;
    unsigned short data_port=0;
    artDriver.connect(ip_host,server_port,data_port);

    int loop_count = 0;
	while(loop_count++ < 5){

		if(artDriver.getFrame()){
			artDriver.output_to_console();
			artDriver.getSegmentTransform(0);
		} else {
			artDriver.error_to_console();
			artDriver.getSegmentTransform(0);
		}

	}
	artDriver.disconnect();
    
}

BOOST_AUTO_TEST_CASE(reconnection)
{
    artracking::ARTDriver artDriver;
    std::string ip_host="131.176.25.107";
    unsigned short server_port=5000;
    unsigned short data_port=0;
    artDriver.connect(ip_host,server_port,data_port);

    artDriver.disconnect();
    artDriver.connect(ip_host,server_port,data_port);
}