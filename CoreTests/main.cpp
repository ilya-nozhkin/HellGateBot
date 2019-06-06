#include "../Core/HellGateBot.h"

#include <QtWebEngine>

#include <iostream>

#ifndef read
int read(int fd, void *buf, int nbyte)
{
	return 0;
}

int write(int fd, const void *buf, int nbyte)
{
	return 0;
}

int close(int fd)
{
	return 0;
}

int _isatty(int a)
{
	return 0;
}
#endif

#include <gtest/gtest.h>
#include <httpmockserver/mock_server.h>
#include <httpmockserver/test_environment.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

static const std::string MOCK_ADDRESS = "http://127.0.0.1:8080";

std::string readMockPage(std::string pageFileName)
{
    static const std::string mockPagesPath = MOCK_PAGES_PATH;

    ifstream file;
    stringstream content;

    file.open(mockPagesPath + "/" + pageFileName);
    content << file.rdbuf();

    std::string result = content.str();

    file.close();

    return result;
}

std::vector<std::string> splitString(std::string source, char delimiter)
{
    std::stringstream test(source);
    std::string segment;
    std::vector<std::string> segments;

    while(std::getline(test, segment, delimiter))
    {
       segments.push_back(segment);
    }

    return segments;
}

std::map<std::string, std::string> parseData(std::string data)
{
    std::map<std::string, std::string> parsed;

    auto actualOptions = splitString(data, '&');
    for (auto actualOption : actualOptions)
    {
        auto keyAndValue = splitString(actualOption, '=');

        if (keyAndValue.size() == 1)
        {
            keyAndValue.push_back("");
        }

        if (keyAndValue.size() == 2)
        {
            parsed[keyAndValue[0]] = keyAndValue[1];
        }
    }

    return std::move(parsed);
}

bool checkData(std::string data, std::vector<std::pair<std::string, std::string>> expected, bool exact = true)
{
    std::map<std::string, std::string> expectedMap;

    for (auto const &expectedOption : expected)
    {
        expectedMap[expectedOption.first] = expectedOption.second;
    }

    auto actualMap = parseData(data);

    for (auto const &actualOption : actualMap)
    {
        if (expectedMap.count(actualOption.first) != 1)
        {
            if (exact)
            {
                return false;
            }
            continue;
        }

        if (expectedMap[actualOption.first] != actualOption.second)
        {
            return false;
        }
    }

    return !exact || expectedMap.size() == actualMap.size();
}

class HTTPMock : public httpmock::MockServer
{
public:
    HTTPMock(int port = 8080) : MockServer(port)
    {
    }

    void resetSession()
    {
        mainPageRequested = false;
        doctorTypesPageRequested = false;
        doctorsPageRequested = false;
        selectedDoctorType = "";
    }

    bool isMainPageRequested() const
    {
        return mainPageRequested;
    }

    bool isDoctorTypesPageRequested() const
    {
        return doctorTypesPageRequested;
    }

    std::pair<bool, std::string> isDoctorsPageRequested() const
    {
        return std::make_pair(doctorsPageRequested, selectedDoctorType);
    }
private:
    Response responseHandler(
            const std::string &url,
            const std::string &method,
            const std::string &data,
            const std::vector<UrlArg> &urlArguments,
            const std::vector<Header> &headers)
    {
        if (url == "/index.html")
        {
            std::string content = readMockPage("MainPage.html");
            mainPageRequested = true;
            return Response(200, content);
        }
        if (url == "/cgi-bin/tcgi1.exe" && checkData(data, {{"COMMAND", "2"}, {"TITLE", "1"}}))
        {
            std::string content = readMockPage("DoctorTypesPage.html");
            doctorTypesPageRequested = true;
            return Response(200, content);
        }
        if (url == "/cgi-bin/tcgi1.exe" && checkData(data, {{"COMMAND", "10"}}, false))
        {
            std::string content = readMockPage("DoctorsPage.html");
            auto options = parseData(data);
            doctorsPageRequested = true;
            selectedDoctorType = options["CODESPEC"];
            return Response(200, content);
        }

        return Response(404, "Not found");
    }

    bool mainPageRequested;
    bool doctorTypesPageRequested;
    bool doctorsPageRequested;
    std::string selectedDoctorType;
};

static httpmock::TestEnvironment<HTTPMock> *environment;

void openMainPage(HellGateBot::WebsiteActor &websiteActor)
{
    websiteActor.openMainPage();
}

void openDoctorTypesPage(HellGateBot::WebsiteActor &websiteActor)
{
    openMainPage(websiteActor);
    websiteActor.openDoctorTypesPage();
}

void openDoctorsPage(HellGateBot::WebsiteActor &websiteActor)
{
    openDoctorTypesPage(websiteActor);
    auto types = websiteActor.getDoctorTypes();
    websiteActor.selectDoctorType(types[1].id);
}

TEST(Navigation, OpenMainPage)
{
    HellGateBot::WebsiteActor websiteActor(MOCK_ADDRESS);
    openMainPage(websiteActor);

    ASSERT_TRUE(environment->getMock().isMainPageRequested());
}

TEST(Navigation, OpenDoctorTypesPage)
{
    HellGateBot::WebsiteActor websiteActor(MOCK_ADDRESS);
    openDoctorTypesPage(websiteActor);

    ASSERT_TRUE(environment->getMock().isDoctorTypesPageRequested());
}

TEST(Navigation, OpenDoctorsPage)
{
    HellGateBot::WebsiteActor websiteActor(MOCK_ADDRESS);
    openDoctorsPage(websiteActor);

    auto info = environment->getMock().isDoctorsPageRequested();
    ASSERT_TRUE(info.first);
    ASSERT_EQ("4", info.second);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtWebEngine::initialize();

    testing::InitGoogleTest(&argc, argv);
    environment = new httpmock::TestEnvironment<HTTPMock>();
    testing::AddGlobalTestEnvironment(environment);

    int code = RUN_ALL_TESTS();
    return code;
}
