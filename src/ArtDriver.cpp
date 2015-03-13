#include <iostream>
#include <sstream>
#include <time.h>
#include <base/logging.h>
#include "DTrackSDK.hpp"
#include "ArtDriver.hpp"

using namespace std;
using namespace artracking;

static DTrackSDK* dt = NULL;

ARTDriver::ARTDriver()
{

}

bool ARTDriver::connect (const std::string& server_host, unsigned short server_port, unsigned short data_port)
{
	std::cout << "Connecting to ART..." 
                  << std::endl;
    dt = new DTrackSDK(server_host, server_port, 0, DTrackSDK::SYS_DTRACK_UNKNOWN);
    std::cout << "Connexion stablished" 
                  << std::endl;
	return false;
}
bool ARTDriver::isConnected()
{
	return false;
}
void ARTDriver::disconnect()
{

}
bool ARTDriver::getFrame( const base::Time& timeout)
{
	return false;
}
base::Time ARTDriver::getTimestamp(){
	return base::Time::now();
}