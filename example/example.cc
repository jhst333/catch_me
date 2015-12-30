#include "catch_me.hpp"
#include <iostream>

enum class error_codes
{ success,
  not_found,
  unknown };

int main()
{ try
  { throw (catch_me::exception_t<error_codes>(error_codes::not_found,
                                              "[%s:%d <%s>]: Some kind of reason",
                                              __FILE__, (__LINE__ - 2), __FUNCTION__)); }
  catch (const catch_me::exception_t<error_codes>& _e)
  { std::cout << "[!] Error code: ";
    switch (_e.error())
    { case error_codes::success: std::cout << "Success!\n"; break;
      default: std::cout << "Error!\n"; }
    std::cout << "[!] " << _e.reason() << std::endl; } }
