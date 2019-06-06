#include "WebsiteActor.h"
#include "Configuration.h"
#include "Utils.h"

#include <libxml/tree.h>
#include <libxml/HTMLparser.h>

#include <sstream>
#include <fstream>

#include <stdio.h>

namespace HellGateBot
{
    std::string getJsToFindElementByXPath(std::string xpath)
    {
        return "document.evaluate(\"" + xpath + "\", "
               "document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue";
    }

    std::string getJsToFindElementById(std::string id)
    {
        return "document.getElementById(\"" + id + "\")";
    }

    WebsiteActor::WebsiteActor(std::string _address) : browser()
    {
        state = WebsiteActorState::NOT_CONNECTED;
        address = _address;
    }

    WebsiteActor::~WebsiteActor()
    {
    }

    void WebsiteActor::openMainPage()
    {
        auto url = WebsiteInfo::findMainPage(address);
        auto html = browser.loadUrl(url);
        updatePage(html);

        state = WebsiteActorState::MAIN_PAGE;
    }

    void WebsiteActor::openDoctorTypesPage()
    {
        auto xPath = WebsiteInfo::xPath(WebsiteInfoXPath::MAIN_PAGE_DOCTORS_BUTTON);
        auto nodes = page->root().find(xPath);

        if (nodes.size() != 1)
            throw HellGateException("There are no any or more than one possible button that leads to the doctor page");

        click(nodes[0], true);

        state = WebsiteActorState::DOCTORS_TYPE_PAGE;
    }

    void WebsiteActor::selectDoctorType(int id)
    {
        auto xPath = WebsiteInfo::xPath(WebsiteInfoXPath::DOCTOR_TYPES_PAGE_SELECT_DOCTOR_TYPE);
        xPath = replace(xPath, "$arg1$", std::to_string(id));
        auto nodes = page->root().find(xPath);

        if (nodes.size() != 1)
            throw HellGateException("There are no any or more than one possible button that leads to the doctors page");

        click(nodes[0], true);

        state = WebsiteActorState::DOCTORS_PAGE;
    }

    void WebsiteActor::selectDoctor(int id)
    {
        auto xPath = WebsiteInfo::xPath(WebsiteInfoXPath::DOCTORS_PAGE_SELECT_DOCTOR);
        xPath = replace(xPath, "$arg1$", std::to_string(id));
        auto nodes = page->root().find(xPath);

        if (nodes.size() != 1)
            throw HellGateException("There are no any or more than one possible button that leads to the days page");

        click(nodes[0], true);

        state = WebsiteActorState::DAYS_PAGE;
    }

    void WebsiteActor::selectDay(int id)
    {
        auto xPath = WebsiteInfo::xPath(WebsiteInfoXPath::DAYS_PAGE_SELECT_DAY);
        xPath = replace(xPath, "$arg1$", std::to_string(id));
        auto nodes = page->root().find(xPath);

        if (nodes.size() != 1)
            throw HellGateException("There are no any or more than one possible button that leads to the tickets page");

        click(nodes[0], true);

        state = WebsiteActorState::TICKETS_PAGE;
    }

    void WebsiteActor::selectTicket(int id)
    {
        auto xPath = WebsiteInfo::xPath(WebsiteInfoXPath::TICKETS_PAGE_SELECT_TICKET);
        xPath = replace(xPath, "$arg1$", std::to_string(id));
        auto nodes = page->root().find(xPath);

        if (nodes.size() != 1)
            throw HellGateException("There are no any or more than one possible button that "
                                    "leads to the obtaining page");

        click(nodes[0], true);

        state = WebsiteActorState::OBTAINING_PAGE;
    }

    void WebsiteActor::fillObtainingForm(std::string surname, std::string name,
                                         std::string patronymic, std::string dateOfBirth)
    {
        auto surnameId     = WebsiteInfo::id(WebsiteInfoIds::SURNAME);
        auto nameId        = WebsiteInfo::id(WebsiteInfoIds::NAME);
        auto patronymicId  = WebsiteInfo::id(WebsiteInfoIds::PATRONYMIC);
        auto dateOfBirthId = WebsiteInfo::id(WebsiteInfoIds::DATE_OF_BIRTH);
        auto agreementId   = WebsiteInfo::id(WebsiteInfoIds::AGREEMENT);

        fillInput(surnameId, surname);
        fillInput(nameId, name);
        fillInput(patronymicId, patronymic);
        fillInput(dateOfBirthId, dateOfBirth);

        clickById(agreementId);
    }

    void WebsiteActor::obtainTicket(std::string outputPdfPath)
    {
        auto xPath = WebsiteInfo::xPath(WebsiteInfoXPath::OBTAINING_PAGE_OBTAIN);
        auto nodes = page->root().find(xPath);

        if (nodes.size() != 1)
            throw HellGateException("There are no obtaining button");

        click(nodes[0], true);

        browser.printToPdf(outputPdfPath);
    }

    std::optional<std::string> extractSpanData(xmlpp::Node *base);
    std::optional<std::string> extractId(xmlpp::Node *node);

    DoctorTypeInfo parseDoctorTypeData(std::string data, int id);

    std::vector<std::pair<std::string, int>> findSpansAndIds(xmlpp::Node *root, std::string xPath);

    std::vector<DoctorTypeInfo> WebsiteActor::getDoctorTypes()
    {
        auto selectingXPath = WebsiteInfo::xPath(WebsiteInfoXPath::DOCTOR_TYPES_PAGE_ALL_DOCTOR_TYPES);
        auto records = findSpansAndIds(&page->root(), selectingXPath);

        std::vector<DoctorTypeInfo> types;
        for (auto &record : records)
        {
            types.push_back(parseDoctorTypeData(record.first, record.second));
        }

        return types;
    }

    DoctorInfo parseDoctorData(std::string data, int id);

    std::vector<DoctorInfo> WebsiteActor::getDoctors()
    {
        auto selectingXPath = WebsiteInfo::xPath(WebsiteInfoXPath::DOCTORS_PAGE_ALL_DOCTORS);
        auto records = findSpansAndIds(&page->root(), selectingXPath);

        std::vector<DoctorInfo> doctors;
        for (auto &record : records)
        {
            doctors.push_back(parseDoctorData(record.first, record.second));
        }

        return doctors;
    }

    DayInfo parseDayData(std::string data, int id);

    std::vector<DayInfo> WebsiteActor::getDays()
    {
        auto selectingXPath = WebsiteInfo::xPath(WebsiteInfoXPath::DAYS_PAGE_ALL_DAYS);
        auto records = findSpansAndIds(&page->root(), selectingXPath);

        std::vector<DayInfo> days;
        for (auto &record : records)
        {
            days.push_back(parseDayData(record.first, record.second));
        }

        return days;
    }

    TicketInfo parseTicketData(std::string data, int id);

    std::vector<TicketInfo> WebsiteActor::getTickets()
    {
        auto selectingXPath = WebsiteInfo::xPath(WebsiteInfoXPath::TICKETS_PAGE_ALL_TICKETS);
        auto records = findSpansAndIds(&page->root(), selectingXPath);

        std::vector<TicketInfo> tickets;
        for (auto &record : records)
        {
            tickets.push_back(parseTicketData(record.first, record.second));
        }

        return tickets;
    }

    // private
    std::optional<std::string> extractSpanData(xmlpp::Node *base)
    {
        auto spanXPath = WebsiteInfo::xPath(WebsiteInfoXPath::INNER_SPAN);
        auto spans = base->find(spanXPath);

        if (spans.size() != 1)
        {
            return std::nullopt;
        }

        auto span = spans[0];

        std::optional<std::string> data = std::nullopt;
        for (xmlpp::Node *child : span->get_children())
        {
            auto text = dynamic_cast<xmlpp::TextNode*>(child);

            if (text)
            {
                data = std::make_optional(text->get_content());
                break;
            }
        }

        return data;
    }

    std::optional<std::string> extractId(xmlpp::Node *node)
    {
        auto element = dynamic_cast<xmlpp::Element*>(node);
        if (!element)
        {
            return std::nullopt;
        }

        auto attributes = element->get_attributes();
        for (xmlpp::Attribute *attribute : attributes)
        {
            if (attribute->get_name() == "id")
            {
                return std::make_optional(attribute->get_value());
            }
        }

        return std::nullopt;
    }

    std::vector<std::pair<std::string, int>> findSpansAndIds(xmlpp::Node *root, std::string xPath)
    {
        std::vector<std::pair<std::string, int>> pairs;

        auto nodes = root->find(xPath);

        for (xmlpp::Node *node : nodes)
        {
            auto optionalData = extractSpanData(node);
            if (!optionalData.has_value())
                throw HellGateException("Couldn't extract span data");

            auto optionalId = extractId(node);
            if (!optionalId.has_value())
                throw HellGateException("Couldn't extract id");

            int id = std::atoi(optionalId.value().c_str());
            pairs.push_back(std::make_pair(optionalData.value(), id));
        }

        return pairs;
    }

    DoctorTypeInfo parseDoctorTypeData(std::string data, int id)
    {
        static const std::string ticketsKeyword = WebsiteInfo::pattern(WebsiteInfoPatterns::TICKETS_NUMBER);
        auto ticketsPosition = data.find(ticketsKeyword);

        auto tickets = std::atoi(data.substr(ticketsPosition + ticketsKeyword.size() + 1).c_str());
        auto doctorType = data.substr(0, ticketsPosition);

        return DoctorTypeInfo(id, doctorType, tickets);
    }

    DoctorInfo parseDoctorData(std::string data, int id)
    {
        static const std::string ticketsKeyword = WebsiteInfo::pattern(WebsiteInfoPatterns::TICKETS_NUMBER);
        auto ticketsPosition = data.find(ticketsKeyword);

        auto tickets = std::atoi(data.substr(ticketsPosition + ticketsKeyword.size() + 1).c_str());
        auto doctor = data.substr(0, ticketsPosition);

        return DoctorInfo(id, doctor, tickets);
    }

    DayInfo parseDayData(std::string data, int id)
    {
        std::stringstream source(data);

        std::string date, weekDay, timeSpan, ticketsKeyword, tickets;
        source >> date >> weekDay >> timeSpan >> ticketsKeyword >> tickets;

        int day, month, year;
        sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);

        int leftHour, leftMinutes, rightHour, rightMinutes;
        sscanf(timeSpan.c_str(), "%d:%d-%d:%d", &leftHour, &leftMinutes, &rightHour, &rightMinutes);

        int availableTickets = 0;
        sscanf(tickets.c_str(), "%d", &availableTickets);

        return DayInfo(id,
                       SimpleDate(day, month, year),
                       SimpleTime(leftHour, leftMinutes),
                       SimpleTime(rightHour, rightMinutes),
                       availableTickets);
    }

    TicketInfo parseTicketData(std::string data, int id)
    {
        std::stringstream source(data);

        std::string time;
        source >> time;

        int hours, minutes;
        sscanf(time.c_str(), "%d:%d", &hours, &minutes);

        return TicketInfo(id, SimpleTime(hours, minutes));
    }

    HtmlDocumentWrapper parseString(std::string &data)
    {
        auto documentPtr = htmlReadDoc((const xmlChar*) data.c_str(), nullptr, "UTF-8",
                                  HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);

        if (!documentPtr)
        {
            throw HellGateException("Error occured during parsing of source:\n" + data);
        }

        auto wrapper = HtmlDocumentWrapper(documentPtr);
        //nameToLower(&wrapper.root());

        return std::move(wrapper);
    }

    void WebsiteActor::updatePage(std::string html)
    {
        auto data = html;
        auto &&document = parseString(data);

        //std::cout << data << endl;

        page = std::make_unique<HtmlDocumentWrapper>(std::move(document));
    }

    void WebsiteActor::click(xmlpp::Node *node, bool update, bool submit)
    {
        std::string xpath = node->get_path().c_str();
        auto locating = getJsToFindElementByXPath(xpath);
        auto method = submit ? ".submit()" : ".click()";
        auto fullJs = locating + method;

        if (update)
        {
            auto html = browser.executeJsAndLoadPage(fullJs);
            updatePage(html);
        }
        else
        {
            browser.executeJs(fullJs);
        }
    }

    void WebsiteActor::clickById(std::string id)
    {
        auto jsFindElement = getJsToFindElementById(id);
        auto fullJs = jsFindElement + ".click()";

        browser.executeJs(fullJs);
    }

    void WebsiteActor::fillInput(std::string id, std::string value)
    {
        auto jsFindElement = getJsToFindElementById(id);
        auto fullJs = jsFindElement + ".value = \"" + value + "\"";

        browser.executeJs(fullJs);
    }
}
