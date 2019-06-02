#include "HellGateBot.h"
#include <iostream>

namespace HellGateBot
{
    HellGateBot::HellGateBot() : actor()
    {
        bool success = false;
        while (!success)
        {
            try
            {
                actor.openMainPage();
                actor.openDoctorTypesPage();
                auto types = actor.getDoctorTypes();
                actor.selectDoctorType(types[1].id);
                auto doctors = actor.getDoctors();
                actor.selectDoctor(doctors[0].id);
                auto days = actor.getDays();

                DayInfo selectedDay;
                for (auto day : days)
                {
                    if (day.availableTickets > 0)
                    {
                        selectedDay = day;
                        break;
                    }
                }

                actor.selectDay(selectedDay.id);
                auto tickets = actor.getTickets();
                actor.selectTicket(tickets[0].id);
                actor.fillObtainingForm(u8"НОЖКИН", u8"ИЛЬЯ", u8"ИГОРЕВИЧ", u8"10/10/1998");
                //actor.obtainTicket("./ticket.pdf");
                success = true;
            }
            catch(HellGateException e)
            {
                std::cout << e.what() << endl;
            }
            catch(...)
            {
            }
        }

        //actor.obtainTicket("./ticket.pdf");
    }
}
