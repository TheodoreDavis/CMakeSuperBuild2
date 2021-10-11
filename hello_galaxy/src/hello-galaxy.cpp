#include "hellogalaxy/hello-galaxy.hpp"
#include <helloworld/hello-world.hpp>
#include <cmakepublic/cmake_public.hpp>

std::string say_a_lot() {
    return say_hello() + std::endl
    + say_goodbye() + std::endl
    + "Goodbye from CMakeSuperbuild2 :)" + std::endl;
}