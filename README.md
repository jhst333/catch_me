*Catch_me*
==========

***Catch_me*** is a simple meta-header designed to ease generation of exception objects.

 - Uses *std::printf* format strings to create *fail reason* string.
 - Allows developer to use his/her own *error objects*.
Example
-------

    ```c++
    #include <catch_me.hpp>
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
```

Above example presents all essential capabilities of this meta-header.

    enum class error_codes { ... };

Defines user *error type*.

    catch_me::exception_t<error_codes>( ... );
   
*catch_me::exception_t* is a class template that takes *error type* as template argument. If template is left without user's *error type*, then default *uint32_t* is given. User's *error type* must be *copy-constructible* and must offer default, parameterless constructor in order to compile with more complex *error types*. 

    < ... >(error_codes::not_found, ... );
  
Here, We specify value for *error_codes* type that *catch_me::exception_t* will carry.

    < my_class >(my_class("abc"), ... );
  
Above code snippet shows how to assign value to more complex *error type*.

    ..., "[%s:%d <%s>]: Some kind of reason", __FILE__, (__LINE__ - 2), __FUNCTION__));
  
These arguments are *format strings*. They're an *argument pack*, so only limit for their amount is your stack space. 

    catch_me::exception_t<my_type_or_none>("Format string");

*catch_me::exception_t* object may be also created without explicit set *error value*. In that case the default constructor will jump into action.

    catch_me::exception_t::reason();
    catch_me::exception_t::error();

*::reason()*, will return *const char** string that contains a reason string.
*::error()*, will return user's *error object*/*value*.

Security considerations
----------------------

 - *catch_me::exception_t* doesn't check if *format specifiers* are right for given argument pack yet.
 - If amount of *format specifiers* is not equal to amount of arguments, it will throw *std::runtime_error*.
 - If first argument (omitting *error value*) is not convertible to *const char**, it will throw *std::runtime_error*.
 - If any of the format strings will contain *non-printable* symbols (except for *newline*) from *ASCII* set, it will throw *std::runtime_error*.
