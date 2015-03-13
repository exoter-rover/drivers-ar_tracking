#include <boost/test/unit_test.hpp>
#include <ar_tracking/Dummy.hpp>

using namespace ar_tracking;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    ar_tracking::DummyClass dummy;
    dummy.welcome();
}
