#ifndef __ART_DRIVER_HPP__
#define __ART_DRIVER_HPP__

#include <base/time.h>
#include <base/eigen.h>
#include <boost/shared_ptr.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>

namespace artracking
{

	class ARTDriver
	{
	public:
		ARTDriver();

		bool connect (const std::string& server_host, unsigned short server_port, unsigned short data_port);
		bool isConnected();
		void disconnect();
		bool getFrame( const base::Time& timeout = base::Time::fromSeconds(1.0) );
		base::Time getTimestamp();
	};

}
#endif