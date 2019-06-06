#include <iostream>

#include "../Core/HellGateBot.h"
#include <QtWebEngine>

using namespace std;
using namespace HellGateBot;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtWebEngine::initialize();

    HellGateBot::HellGateBot hellGateBot;
    hellGateBot.setPatient(u8"НОЖКИН", u8"ИЛЬЯ", u8"ИГОРЕВИЧ", u8"10/10/1998");
    hellGateBot.setDoctorType(u8"ТЕРАПЕВТ");
    hellGateBot.setDoctor(u8"МЕДЯНОВА");
    hellGateBot.setDate(SimpleDate(07, 06, 2019));
    hellGateBot.setTime(SimpleTime(00, 00), SimpleTime(23, 00));
    hellGateBot.obtain("ticket.pdf");

    return 0;
}
