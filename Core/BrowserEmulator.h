#pragma once

#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QtWidgets/QApplication>
#include <memory>

namespace HellGateBot
{
    class WebEngineInitializer
    {
    public:
        WebEngineInitializer();
    };

    class BrowserEmulator : public QObject
    {
    public:
        BrowserEmulator();
        ~BrowserEmulator();

        std::string loadUrl(std::string url);
        std::string executeJsAndLoadPage(std::string js);
        void executeJs(std::string js);
        bool printToPdf(std::string outputPath);
    private:
        static std::unique_ptr<QApplication> qtApplication;
        QWebEnginePage page;
    };
}
