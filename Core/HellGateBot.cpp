#include "HellGateBot.h"
#include <iostream>
#include <optional>

namespace HellGateBot
{
    HellGateBot::HellGateBot() : actor()
    {
    }

    void HellGateBot::setPatient(std::string _surname, std::string _name,
                                 std::string _patronymic, std::string _dateOfBirth)
    {
        surname = _surname;
        name = _name;
        patronymic = _patronymic;
        dateOfBirth = _dateOfBirth;
    }

    void HellGateBot::setDoctorType(std::string _doctorType)
    {
        doctorType = _doctorType;
    }

    void HellGateBot::setDoctor(std::string _doctor)
    {
        doctor = _doctor;
    }

    void HellGateBot::setDate(SimpleDate _date)
    {
        date = _date;
    }

    void HellGateBot::setTime(SimpleTime _since, SimpleTime _until)
    {
        since = _since;
        until = _until;
    }

    std::optional<DoctorTypeInfo> findDoctorType(WebsiteActor &actor, std::string &doctorType)
    {
        auto types = actor.getDoctorTypes();
        for (auto type : types)
        {
            if (type.availableTickets > 0 &&
                type.typeName.find(doctorType.c_str()) != type.typeName.npos)
            {
                return std::make_optional(type);
            }
        }

        return std::nullopt;
    }

    std::optional<DoctorInfo> findDoctor(WebsiteActor &actor, std::string &doctorName)
    {
        auto doctors = actor.getDoctors();
        for (auto doctor : doctors)
        {
            if (doctor.availableTickets > 0 &&
                doctor.name.find(doctorName.c_str()) != doctor.name.npos)
            {
                return std::make_optional(doctor);
            }
        }

        return std::nullopt;
    }

    std::optional<DayInfo> findDay(WebsiteActor &actor, SimpleDate &date)
    {
        auto days = actor.getDays();
        for (auto day : days)
        {
            if (day.availableTickets > 0 &&
                day.date == date)
            {
                return std::make_optional(day);
            }
        }

        return std::nullopt;
    }

    std::optional<TicketInfo> findTicket(WebsiteActor &actor, SimpleTime &since, SimpleTime &until)
    {
        auto tickets = actor.getTickets();
        for (auto ticket : tickets)
        {
            if ((since <= ticket.time) && (ticket.time <= until))
            {
                return std::make_optional(ticket);
            }
        }

        return std::nullopt;
    }

    void HellGateBot::obtain(std::string outputPdfPath)
    {
        actor.openMainPage();
        log("Main page opened");

        actor.openDoctorTypesPage();
        log("Doctor types page opened");

        auto selectedType = findDoctorType(actor, doctorType);
        if (!selectedType.has_value()) return;
        actor.selectDoctorType(selectedType.value().id);
        log("Doctor type selected");

        auto selectedDoctor = findDoctor(actor, doctor);
        if (!selectedDoctor.has_value()) return;
        actor.selectDoctor(selectedDoctor.value().id);
        log("Doctor selected");

        auto selectedDay = findDay(actor, date);
        if (!selectedDay.has_value()) return;
        actor.selectDay(selectedDay.value().id);
        log("Day selected");

        auto selectedTicket = findTicket(actor, since, until);
        if (!selectedTicket.has_value()) return;
        actor.selectTicket(selectedTicket.value().id);
        log("Ticket selected");

        actor.fillObtainingForm(surname, name, patronymic, dateOfBirth);
        log("Form filled");

        actor.obtainTicket(outputPdfPath);
        log("Ticket obtained");
    }
}
