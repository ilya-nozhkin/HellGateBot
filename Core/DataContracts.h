#pragma once

#include <string>
#include <chrono>

#include "Utils.h"

namespace HellGateBot
{
    struct DoctorTypeInfo
    {
        int id;
        std::string typeName;
        int availableTickets;

        DoctorTypeInfo() = default;
        DoctorTypeInfo(int _id, std::string _typeName, int _availableTickets)
        {
            id = _id;
            typeName = _typeName;
            availableTickets = _availableTickets;
        }
    };

    struct DoctorInfo
    {
        int id;
        std::string name;
        int availableTickets;

        DoctorInfo() = default;
        DoctorInfo(int _id, std::string _name, int _availableTickets)
        {
            id = _id;
            name = _name;
            availableTickets = _availableTickets;
        }
    };

    struct DayInfo
    {
        int id;
        SimpleDate date;

        SimpleTime begin;
        SimpleTime end;

        int availableTickets;

        DayInfo() = default;
        DayInfo(int _id, SimpleDate _date, SimpleTime _begin, SimpleTime _end, int _availableTickets)
        {
            id = _id;
            date = _date;
            begin = _begin;
            end = _end;
            availableTickets = _availableTickets;
        }
    };

    struct TicketInfo
    {
        int id;
        SimpleTime time;

        TicketInfo() = default;
        TicketInfo(int _id, SimpleTime _time)
        {
            id = _id;
            time = _time;
        }
    };
}
