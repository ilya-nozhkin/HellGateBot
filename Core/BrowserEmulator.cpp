#include "BrowserEmulator.h"
#include "Utils.h"

#include <QtWebEngine/QtWebEngine>
#include <QtPrintSupport>
#include <iostream>

namespace HellGateBot
{
    BrowserEmulator::BrowserEmulator() : page()
    {
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

    void BrowserEmulator::executeJs(std::string js)
    {
        page.runJavaScript(QString(js.c_str()));
    }

    bool BrowserEmulator::printToPdf(std::string outputPath)
    {
        QPrinter printer;
        printer.setOrientation(QPrinter::Portrait);
        printer.setPaperSize(QPrinter::A4);
        printer.setFullPage(true);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(QString(outputPath.c_str()));
        printer.setFromTo(1, 1);

        QEventLoop loop;
        bool finished = false;
        bool printed = false;

        page.print(&printer, [&](bool status) {
                printed = status;
                finished = true;
                loop.quit(); });

        if (!finished)
        {
            loop.exec();
        }

        return printed;
    }

    WebEngineInitializer::WebEngineInitializer()
    {
        QtWebEngine::initialize();
    }
}
