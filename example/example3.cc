#include "catch_me.hpp"
#include <tuple>
#include <iostream>

class error_class_t
{ private:
   uint32_t line_m;
   const char* file_m;
   const char* function_m;
  public:
   //#:- Construction
   error_class_t() throw () { line_m = 0; file_m = nullptr; function_m = nullptr; }
   error_class_t(const error_class_t& _error_class) throw ()
   { line_m = _error_class.line_m;
     file_m = _error_class.file_m;
     function_m = _error_class.function_m; }
   error_class_t(std::tuple<uint32_t, const char*, const char*> _info) throw ()
   { line_m = std::get<0>(_info);
     file_m = std::get<1>(_info);
     function_m = std::get<2>(_info); }
   //#:- Interface
   inline uint32_t line() const throw () { return line_m; }
   inline const char* file() const throw () { return file_m; }
   inline const char* function() const throw () { return function_m; } };

int main()
{ try
  { //#: Generic exception, template type argument is uint32_t, value is 1
    throw (catch_me::exception_t<>(1, "Reason")); }
  catch (const catch_me::exception_t<>& _e)
  { std::cout << "[!] Error code: " << _e.error() << "\n";
    std::cout << "[!] " << _e.reason() << std::endl; }
  try
  { //#: Generic exception, template type argument is uint32_t, value is 0
    throw (catch_me::exception_t<>("Reason")); }
    catch (const catch_me::exception_t<>& _e)
    { std::cout << "[!] Error code: " << _e.error() << "\n";
      std::cout << "[!] " << _e.reason() << std::endl; }
  try
  { //#: Construct error_class_t with tuple argument,
    //#: then copy it to exception_t internal member.
    throw (catch_me::exception_t<error_class_t>(error_class_t(std::make_tuple(__LINE__, __FILE__, __FUNCTION__)), "Reason: %s", "much complexity")); }
    catch (const catch_me::exception_t<error_class_t>& _e)
    { std::cout << "[!] Error object: " << _e.error().file() << ':'
                << _e.error().line() << " <" << _e.error().function() << ">\n";
      std::cout << "[!] " << _e.reason() << std::endl; } }
