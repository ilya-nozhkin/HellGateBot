#include "BrowserEmulator.h"

#include <QtWebEngine/QtWebEngine>
#include <iostream>

namespace HellGateBot
{
    static int __argc = 0;

    BrowserEmulator::BrowserEmulator() : qtApplication(__argc, nullptr), page()
    {
        QtWebEngine::initialize();
    }

    BrowserEmulator::~BrowserEmulator()
    {
    }

    std::string BrowserEmulator::loadUrl(std::string url)
    {
        QEventLoop loop;
        QObject::connect(&page, &QWebEnginePage::loadFinished,
                         &loop, &QEventLoop::quit);
        page.load(QUrl(url.c_str()));
        loop.exec();

        QObject::disconnect(&page, &QWebEnginePage::loadFinished,
                            &loop, &QEventLoop::quit);

        QString html;

        page.toHtml([&html, &loop](const QString& data){
            html = data;
            loop.quit();
        });

        loop.exec();

        return html.toUtf8().toStdString();
    }

    std::string BrowserEmulator::executeJsAndLoadPage(std::string js)
    {
        QEventLoop loop;

        QObject::connect(&page, &QWebEnginePage::loadFinished,
                         &loop, &QEventLoop::quit);

        page.runJavaScript(QString(js.c_str()));
        loop.exec();

        QObject::disconnect(&page, &QWebEnginePage::loadFinished,
                            &loop, &QEventLoop::quit);


        QString html;

        page.toHtml([&html, &loop](const QString& data){
            html = data;
            loop.quit();
        });

        loop.exec();

        return html.toUtf8().toStdString();
    }

    std::string BrowserEmulator::executeJs(std::string js)
    {
        page.runJavaScript(QString(js.c_str()));
    }

    void BrowserEmulator::printToPdf(std::string outputPath)
    {
        page.printToPdf(QString(outputPath.c_str()));
    }
}
