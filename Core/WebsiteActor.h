#pragma once

#include <vector>

#include <libxml++/libxml++.h>

#include "HtmlDocumentWrapper.h"
#include "DataContracts.h"
#include "BrowserEmulator.h"

namespace HellGateBot
{
    enum class WebsiteActorState
    {
        NOT_CONNECTED,
        MAIN_PAGE,
        DOCTORS_TYPE_PAGE,
        DOCTORS_PAGE,
        DAYS_PAGE,
        TICKETS_PAGE,
        OBTAINING_PAGE
    };

    class WebsiteActor
    {
    public:
        //Requires: curlpp::initialize() is called
        //Ensures: state = NOT_CONNECTED
        WebsiteActor();
        ~WebsiteActor();

        //Requires: state = <ANY>
        //Ensures: state = MAIN_PAGE
        void openMainPage();

        //Requires: state = MAIN_PAGE
        //Ensures: state = DOCTORS_TYPE_PAGE
        void openDoctorTypesPage();

        //Requires: state = DOCTORS_TYPE_PAGE, 'id' given by getDoctorTypes()
        //Ensures: state = DOCTORS_PAGE
        void selectDoctorType(int id);

        //Requires: state = DOCTORS_PAGE, 'id' given by getDoctors()
        //Ensures: state = DAYS_PAGE
        void selectDoctor(int id);

        //Requires: state = DAYS_PAGE, 'id' given by getDays()
        //Ensures: state = TICKETS_PAGE
        void selectDay(int id);

        //Requires: state = TICKETS_PAGE, 'id' given by getTickets()
        //Ensures: state = OBTAINING_PAGE
        void selectTicket(int id);

        //Requires: state = OBTAINING_PAGE
        void fillObtainingForm(std::string surname, std::string name,
                               std::string patronymic, std::string dateOfBirth);

        //Requires: state = OBTAINING_PAGE, obtaining form filled
        void obtainTicket(std::string outputPdfPath);

        //Requires: state = DOCTORS_TYPE_PAGE
        std::vector<DoctorTypeInfo> getDoctorTypes();

        //Requires: state = DOCTORS_PAGE
        std::vector<DoctorInfo> getDoctors();

        //Requires: state = DAYS_PAGE
        std::vector<DayInfo> getDays();

        //Requires: state = TICKETS_PAGE
        std::vector<TicketInfo> getTickets();
    private:
        void updatePage(std::string html);
        void click(xmlpp::Node *node, bool update = false, bool submit = false);
        void clickById(std::string id);
        void fillInput(std::string id, std::string value);

        BrowserEmulator browser;
        WebsiteActorState state;
        std::unique_ptr<HtmlDocumentWrapper> page;
    };
}
