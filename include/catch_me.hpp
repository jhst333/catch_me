#ifndef CATCH_ME_HPP_
#define CATCH_ME_HPP_

#include <type_traits>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

namespace catch_me
{ template <typename error_object_t = uint32_t>
  class exception_t
  { private:
     //#:- Utils
     inline uint32_t safe_string_length(const char* _string) throw (std::runtime_error)
     { uint32_t index = 0;
       for (; _string[index]; index++)
       { if (_string[index] < 32 &&
             _string[index] != '\n') throw (std::runtime_error("[catch_me::exception_t]: Invalid string.")); }
       #ifdef DEBUG
        std::printf("[DEBUG] Length of '%s' is %d\n", _string, index);
       #endif
       return index; }
     inline uint32_t format_specifiers(const char* _string, uint32_t _length) throw (std::runtime_error)
     { uint32_t options = 0;
       for (uint32_t index = 0; index < _length; ++index)
       { if (_string[index] == '%')
         { ++index;
           if (index >= _length) throw (std::runtime_error("[catch_me::exception_t]: Invalid format specifier."));
           if (_string[index] != '%') ++options; } }
       #ifdef DEBUG
        std::printf("[DEBUG] Amount of format specifiers for '%s' is %d\n", _string, options);
       #endif
       return options; }
    public:
     //#:- Construction
     exception_t() = delete;
     template <typename argument_t, typename... arguments_t>
     exception_t(argument_t _argument, arguments_t... _arguments) throw (std::runtime_error)
                 :error_object_m()
     {  if (!(std::is_convertible<argument_t, const char*>::value))
        throw (std::runtime_error("[catch_me::exception_t]: Format string is not castable to const char*."));
       uint32_t format_string_length = safe_string_length(_argument);
       if (format_specifiers(_argument, format_string_length) != sizeof...(_arguments))
        throw (std::runtime_error("[catch_me::exception_t]: Different number of arguments and format specifiers."));
       uint32_t reason_string_length = std::snprintf(nullptr, 0, _argument, _arguments...) + 1;
       reason_m = new char [reason_string_length + 1];
       reason_m[reason_string_length] = '\0';
       std::snprintf(reason_m, reason_string_length + 1, _argument, _arguments...); }
     template <typename argument_t, typename... arguments_t>
     exception_t(error_object_t _error_object, argument_t _argument, arguments_t... _arguments) throw (std::runtime_error)
                 :error_object_m(_error_object)
     { if (!(std::is_convertible<argument_t, const char*>::value))
        throw (std::runtime_error("[catch_me::exception_t]: Format string is not castable to const char*."));
       uint32_t format_string_length = safe_string_length(_argument);
       if (format_specifiers(_argument, format_string_length) != sizeof...(_arguments))
        throw (std::runtime_error("[catch_me::exception_t]: Different number of arguments and format specifiers."));
       uint32_t reason_string_length = std::snprintf(nullptr, 0, _argument, _arguments...) + 1;
       reason_m = new char [reason_string_length + 1];
       reason_m[reason_string_length] = '\0';
       std::snprintf(reason_m, reason_string_length + 1, _argument, _arguments...); }
     template <typename argument_t>
     exception_t(argument_t _argument) throw (std::runtime_error)
                 :error_object_m()
     { if (!(std::is_convertible<argument_t, const char*>::value))
        throw (std::runtime_error("[catch_me::exception_t]: Format string is not castable to const char*."));
       uint32_t format_string_length = safe_string_length(_argument);
       if (format_specifiers(_argument, format_string_length))
        throw (std::runtime_error("[catch_me::exception_t]: No arguments for format specifiers."));
       reason_m = new char [format_string_length + 1];
       reason_m[format_string_length] = '\0';
       std::snprintf(reason_m, format_string_length + 1, _argument);}
     template <typename argument_t>
     exception_t(error_object_t _error_object, argument_t _argument) throw (std::runtime_error)
                 :error_object_m(_error_object)
     { if (!(std::is_convertible<argument_t, const char*>::value))
        throw (std::runtime_error("[catch_me::exception_t]: Format string is not castable to const char*."));
       uint32_t format_string_length = safe_string_length(_argument);
       if (format_specifiers(_argument, format_string_length))
        throw (std::runtime_error("[catch_me::exception_t]: No arguments for format specifiers."));
       reason_m = new char [format_string_length + 1];
       reason_m[format_string_length] = '\0';
       std::snprintf(reason_m, format_string_length + 1, _argument); }
     ~exception_t() { if (reason_m) delete [] reason_m; }
     //#:- Interface
     const char* reason() const throw ()
     { return reason_m; }
     operator const char*() const throw ()
     { return reason_m; }
     const error_object_t& error() const throw ()
     { return error_object_m; }
     operator const error_object_t& () const throw ()
     { return error_object_m; }
    private:
     char* reason_m;
     error_object_t error_object_m; }; }
#endif
