#include <boost/test/unit_test.hpp>
#include <ar_tracking/ArtDriver.hpp>

using namespace artracking;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    artracking::ARTDriver artDriver;
    std::string ip_host="127.0.0.1";
    artDriver.connect(ip_host,5000,0);
}
