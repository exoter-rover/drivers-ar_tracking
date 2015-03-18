#include <boost/test/unit_test.hpp>
#include <ar_tracking/ArtDriver.hpp>

#include <iostream>

using namespace artracking;

BOOST_AUTO_TEST_CASE(print_data)
{
    artracking::ARTDriver artDriver;
    std::string ip_host="127.0.0.1";
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

BOOST_AUTO_TEST_CASE(r_to_q)
{
    double r[9] = {0,-1,0,1,0,0,0,0,1};
     std::cout << " "   << r[0] << " " << r[3] << " " << r[6]<< std::endl
                 << " " << r[1] << " " << r[4] << " " << r[7]<< std::endl
                 << " " << r[2] << " " << r[5] << " " << r[8] << std::endl;
      
    artracking::ARTDriver artDriver;
    Eigen::Quaterniond q = artDriver.r_to_q(r);
    std::cout << q.toRotationMatrix()   << std::endl;

    double m[9] = {1,0,0,0,0,-1,0,1,0};
     std::cout << " "   << m[0] << " " << m[3] << " " << m[6]<< std::endl
                 << " " << m[1] << " " << m[4] << " " << m[7]<< std::endl
                 << " " << m[2] << " " << m[5] << " " << m[8] << std::endl;
      
    q = artDriver.r_to_q(m);
    std::cout << q.toRotationMatrix()   << std::endl;

}