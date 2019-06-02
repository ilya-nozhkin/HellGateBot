#pragma once

#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QtWidgets/QApplication>

namespace HellGateBot
{
    class BrowserEmulator : public QObject
    {
    public:
        BrowserEmulator();
        ~BrowserEmulator();

        std::string loadUrl(std::string url);
        std::string executeJsAndLoadPage(std::string js);
        std::string executeJs(std::string js);
        void printToPdf(std::string outputPath);
    private:
        QApplication qtApplication;
        QWebEnginePage page;
    };
}
