#include <iostream>

#include "../Core/HellGateBot.h"
#include <QtWebEngine>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtWebEngine::initialize();

    HellGateBot::HellGateBot hellGateBot;

    return 0;
}
