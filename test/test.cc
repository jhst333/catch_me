#include "catch_me.hpp"
#define BOOST_TEST_DYN_LINK 1
#define BOOST_TEST_MODULE catch_me_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(CatchMe001)
{ BOOST_CHECK_THROW(catch_me::exception_t<>("-$=n+dw}i-X=v_<Ux=J+xc#]s%s4cf7;jE _`GlV9xDf2vYa_{=s"),
                    std::runtime_error); }

BOOST_AUTO_TEST_CASE(CatchMe002)
{ auto exception = catch_me::exception_t<>("-$=n+dw}i-X=v_<Ux=J+xc#]s%%4cf7;jE _`GlV9xDf2vYa_{=s");
  BOOST_CHECK(std::string(exception.reason()) == "-$=n+dw}i-X=v_<Ux=J+xc#]s%4cf7;jE _`GlV9xDf2vYa_{=s"); }

BOOST_AUTO_TEST_CASE(CatchMe003)
{ BOOST_CHECK_THROW(catch_me::exception_t<>("-$=n+dw}i-X=v_<Ux=J+xc#]s4cf7;jE _`GlV9xDf2vYa_{=s%", "a"),
                    std::runtime_error); }

BOOST_AUTO_TEST_CASE(CatchMe004)
{ auto exception = catch_me::exception_t<>("-$=n+dw}i-X=v_<Ux=J+xc#]s%%4cf7;jE _`GlV9xDf2vYa_{=s%s", "a");
  BOOST_CHECK(std::string(exception.reason()) == "-$=n+dw}i-X=v_<Ux=J+xc#]s%4cf7;jE _`GlV9xDf2vYa_{=sa"); }

BOOST_AUTO_TEST_CASE(CatchMe005)
{ auto exception = catch_me::exception_t<>("-$=n+dw}i-X=v_<Ux=J+xc#]s%%4cf7;jE _`GlV9xDf2vYa_{=s%%%s%%%%%d", "a", -157871);
  BOOST_CHECK(std::string(exception.reason()) == "-$=n+dw}i-X=v_<Ux=J+xc#]s%4cf7;jE _`GlV9xDf2vYa_{=s%a%%-157871"); }

BOOST_AUTO_TEST_CASE(CatchMe006)
{ std::string a("%%s");
  BOOST_CHECK_THROW(catch_me::exception_t<>(a.c_str(), "a"), std::runtime_error); }

BOOST_AUTO_TEST_CASE(CatchMe007)
{ BOOST_CHECK(catch_me::exception_t<>("a").error() == 0); }

BOOST_AUTO_TEST_CASE(CatchMe008)
{ enum class error_codes
  { success,
    error };
  BOOST_CHECK(catch_me::exception_t<error_codes>(error_codes::success, "a").error() ==
                                                 error_codes::success); }

BOOST_AUTO_TEST_CASE(CatchMe009)
{ enum class error_codes
  { success,
    error };
  BOOST_CHECK(catch_me::exception_t<error_codes>(error_codes::success, "%c", "a").error() ==
                                                 error_codes::success); }

BOOST_AUTO_TEST_CASE(CatchMe010)
{ class my_class
  { private:
     std::string foo_m;
    public:
     my_class(const std::string& _foo) { foo_m = _foo; }
     my_class(const my_class& _my_class) { foo_m = _my_class.foo_m; }
     const std::string& str() const { return foo_m; } };
  try { throw(catch_me::exception_t<my_class>(my_class("asd"), "%s", "a")); }
  catch (const catch_me::exception_t<my_class>& _exception)
  { BOOST_CHECK(_exception.error().str() == "asd"); } }

BOOST_AUTO_TEST_CASE(CatchMe011)
{ BOOST_CHECK_THROW(catch_me::exception_t<>("\x1F").error(), std::runtime_error); }

BOOST_AUTO_TEST_CASE(CatchMe012)
{ BOOST_CHECK_THROW(catch_me::exception_t<>("\x7F").error(), std::runtime_error); }
