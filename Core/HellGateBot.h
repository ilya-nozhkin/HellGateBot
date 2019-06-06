#pragma once

#include "WebsiteActor.h"

namespace HellGateBot
{
    class HellGateBot
    {
    public:
        HellGateBot();

        void setPatient(std::string _surname, std::string _name,
                            std::string _patronymic, std::string _dateOfBirth);
        void setDoctorType(std::string _doctorType);
        void setDoctor(std::string _doctor);
        void setDate(SimpleDate _date);
        void setTime(SimpleTime _since, SimpleTime _until);

        void obtain(std::string outputPdfPath);
    private:
        WebsiteActor actor;

        std::string surname;
        std::string name;
        std::string patronymic;
        std::string dateOfBirth;
        std::string doctorType;
        std::string doctor;
        SimpleDate date;
        SimpleTime since;
        SimpleTime until;
    };
}
