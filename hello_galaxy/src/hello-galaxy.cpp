#include "hellogalaxy/hello-galaxy.hpp"
#include <helloworld/hello-world.hpp>
#include <cmakepublic/cmake_public.hpp>

std::string say_a_lot() {
    return say_hello()
    + say_goodbye()
    + "Goodbye from CMakeSuperbuild2 :)";
}