#pragma once

#include <string>

namespace HellGateBot
{
    enum class WebsiteInfoXPath
    {
        MAIN_PAGE_DOCTORS_BUTTON,
        DOCTOR_TYPES_PAGE_ALL_DOCTOR_TYPES,
        INNER_SPAN,
        DOCTOR_TYPES_PAGE_SELECT_DOCTOR_TYPE,
        DOCTORS_PAGE_ALL_DOCTORS,
        DOCTORS_PAGE_SELECT_DOCTOR,
        DAYS_PAGE_ALL_DAYS,
        DAYS_PAGE_SELECT_DAY,
        TICKETS_PAGE_ALL_TICKETS,
        TICKETS_PAGE_SELECT_TICKET,
        OBTAINING_PAGE_OBTAIN
    };

    enum class WebsiteInfoPatterns
    {
        TICKETS_NUMBER
    };

    enum class WebsiteInfoIds
    {
        SURNAME,
        NAME,
        PATRONYMIC,
        DATE_OF_BIRTH,
        AGREEMENT
    };

    //TODO: Read from file
    class WebsiteInfo
    {
    public:
        static std::string getBaseAddress();
        static std::string findMainPage();
        static std::string xPath(WebsiteInfoXPath type);
        static std::string pattern(WebsiteInfoPatterns type);
        static std::string id(WebsiteInfoIds id);
    private:
        WebsiteInfo();

        inline static const std::string ADDRESS = "http://nikmed.spb.ru";
        inline static const std::string MAIN_PAGE = "/index.html";

        // Main page
        inline static const std::string XPATH_DOCTORS_BUTTON =
                "/html/body/div/*/*/input[@name='COMMAND' and @value='2']/../input[@type='submit']";

        // Doctor types page
        inline static const std::string XPATH_SELECT_DOCTOR_TYPES =
                "//*[@id='f1']//button[@type='submit' or @type='button']";

        inline static const std::string XPATH_SELECT_DOCTOR_TYPE =
                "//*[@id='f1']//button[@type='submit' and @id='$arg1$']";

        // Doctors page
        inline static const std::string XPATH_SELECT_DOCTORS =
                "//*[@id='f1']//button[@type='submit' or @type='button']";

        inline static const std::string XPATH_SELECT_DOCTOR =
                "//*[@id='f1']//button[@type='submit' and @id='$arg1$']";

        // Days page
        inline static const std::string XPATH_SELECT_DAYS =
                "//*[@id='f1']/table//button[@type='submit' or @type='button']";

        inline static const std::string XPATH_SELECT_DAY =
                "//*[@id='f1']/table//button[@type='submit' and @id='$arg1$']";

        // Tickets page
        inline static const std::string XPATH_SELECT_TICKETS =
                "//*[@id='f1']/table//button[@type='submit']";

        inline static const std::string XPATH_SELECT_TICKET =
                "//*[@id='f1']/table//button[@type='submit' and @id='$arg1$']";

        // Obtaining page
        inline static const std::string ID_SURNAME = "SURNAME";
        inline static const std::string ID_NAME = "NAME1";
        inline static const std::string ID_PATRONYMIC = "NAME2";
        inline static const std::string ID_DATE_OF_BIRTH = "DR";
        inline static const std::string ID_AGREEMENT = "csd";

        inline static const std::string XPATH_OBTAIN = "//*[@id='form1']//*[@type='submit' and @id='1']";

        // Common
        inline static const std::string INNER_SPAN =
                ".//span";

        inline static const std::string PATTERN_TICKETS_NUMBER =
                u8"НОМЕРКОВ";
    };
}
