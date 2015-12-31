#include "catch_me.hpp"
#include <iostream>

int main()
{ try
  { throw (catch_me::exception_t<>(1, "Reason")); }
  catch (const catch_me::exception_t<>& _e)
  { std::cout << "[!] Error code: " << _e.error() << "\n";
    std::cout << "[!] " << _e.reason() << std::endl; } }
