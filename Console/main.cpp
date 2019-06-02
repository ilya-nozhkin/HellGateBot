#include <iostream>

#include "../Core/HellGateBot.h"
#include <curlpp/cURLpp.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    curlpp::initialize();

    HellGateBot::HellGateBot hellGateBot;

    curlpp::terminate();

    return 0;
}
