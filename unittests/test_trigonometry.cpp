#include "catch.hpp"
#include "trigonometry.hpp"

TEST_CASE("trigonometry","tri")
{
	SECTION("minutes/seconds to radians")
	{
		using namespace trigonometry;
		REQUIRE( minutesToRadians(15) == 0.0 );
		REQUIRE( minutesToRadians(30) == float(0.5 * M_PI) );
		REQUIRE( minutesToRadians(45) == float(1.0 * M_PI) );
		REQUIRE( minutesToRadians(00) == float(1.5 * M_PI) );
	}
	SECTION("hours to radians")
	{
		using namespace trigonometry;
		REQUIRE( hoursToRadians(3) == 0.0 );
		REQUIRE( hoursToRadians(6) == float(0.5 * M_PI) );
		REQUIRE( hoursToRadians(9) == float(1.0 * M_PI) );
		REQUIRE( hoursToRadians(12) == float(1.5 * M_PI) );
		REQUIRE( hoursToRadians(15) == 0.0 );
		REQUIRE( hoursToRadians(18) == float(0.5 * M_PI) );
		REQUIRE( hoursToRadians(21) == float(1.0 * M_PI) );
		REQUIRE( hoursToRadians(0) == float(1.5 * M_PI) );
	}
}
