#//: General
 cmake_minimum_required (VERSION 2.6)
 project                (catch_me)
 set                    (catch_me_VERSION_MAJOR 1)
 set                    (catch_me_VERSION_MINOR 0)

#//: Package
 find_package(Boost COMPONENTS unit_test_framework)

#//: Example
 add_executable             (catch_me_example1 example/example1.cc)
 target_include_directories (catch_me_example1 PUBLIC include/)
 target_compile_options     (catch_me_example1 PUBLIC -Wall -Wextra -pedantic -std=c++11 -fPIC -Ofast)

 add_executable             (catch_me_example2 example/example2.cc)
 target_include_directories (catch_me_example2 PUBLIC include/)
 target_compile_options     (catch_me_example2 PUBLIC -Wall -Wextra -pedantic -std=c++11 -fPIC -Ofast)

 add_executable             (catch_me_example3 example/example3.cc)
 target_include_directories (catch_me_example3 PUBLIC include/)
 target_compile_options     (catch_me_example3 PUBLIC -Wall -Wextra -pedantic -std=c++11 -fPIC -Ofast)

#//: Test
 if (Boost_UNIT_TEST_FRAMEWORK_LIBRARY)
  add_executable             (catch_me_test test/test.cc)
  target_include_directories (catch_me_test PUBLIC include/)
  target_compile_options     (catch_me_test PUBLIC -Wall -Wextra -pedantic -std=c++11 -g -DDEBUG)
  target_link_libraries      (catch_me_test LINK_PUBLIC ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
 endif()

#//: Installation
 INSTALL (FILES include/catch_me.hpp DESTINATION include)
