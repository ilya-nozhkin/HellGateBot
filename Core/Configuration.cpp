#include "Configuration.h"

namespace HellGateBot
{
    std::string WebsiteInfo::findMainPage(std::string base)
    {
        return base + MAIN_PAGE;
    }

    std::string WebsiteInfo::xPath(WebsiteInfoXPath type)
    {
        //TODO: Map
        switch(type)
        {
        case WebsiteInfoXPath::MAIN_PAGE_DOCTORS_BUTTON:
            return XPATH_DOCTORS_BUTTON;
        case WebsiteInfoXPath::DOCTOR_TYPES_PAGE_ALL_DOCTOR_TYPES:
            return XPATH_SELECT_DOCTOR_TYPES;
        case WebsiteInfoXPath::INNER_SPAN:
            return INNER_SPAN;
        case WebsiteInfoXPath::DOCTOR_TYPES_PAGE_SELECT_DOCTOR_TYPE:
            return XPATH_SELECT_DOCTOR_TYPE;
        case WebsiteInfoXPath::DOCTORS_PAGE_ALL_DOCTORS:
            return XPATH_SELECT_DOCTORS;
        case WebsiteInfoXPath::DOCTORS_PAGE_SELECT_DOCTOR:
            return XPATH_SELECT_DOCTOR;
        case WebsiteInfoXPath::DAYS_PAGE_ALL_DAYS:
            return XPATH_SELECT_DAYS;
        case WebsiteInfoXPath::DAYS_PAGE_SELECT_DAY:
            return XPATH_SELECT_DAY;
        case WebsiteInfoXPath::TICKETS_PAGE_ALL_TICKETS:
            return XPATH_SELECT_TICKETS;
        case WebsiteInfoXPath::TICKETS_PAGE_SELECT_TICKET:
            return XPATH_SELECT_TICKET;
        case WebsiteInfoXPath::OBTAINING_PAGE_OBTAIN:
            return XPATH_OBTAIN;
        }
    }

    std::string WebsiteInfo::pattern(WebsiteInfoPatterns type)
    {
        switch(type)
        {
        case WebsiteInfoPatterns::TICKETS_NUMBER:
            return PATTERN_TICKETS_NUMBER;
        }
    }

    std::string WebsiteInfo::id(WebsiteInfoIds id)
    {
        switch (id)
        {
        case WebsiteInfoIds::SURNAME:
            return ID_SURNAME;
        case WebsiteInfoIds::NAME:
            return ID_NAME;
        case WebsiteInfoIds::PATRONYMIC:
            return ID_PATRONYMIC;
        case WebsiteInfoIds::DATE_OF_BIRTH:
            return ID_DATE_OF_BIRTH;
        case WebsiteInfoIds::AGREEMENT:
            return ID_AGREEMENT;
        }
    }
}
