#pragma once

#include <libxml/tree.h>
#include <libxml++/libxml++.h>

namespace HellGateBot
{
    class HtmlDocumentWrapper
    {
    public:
        HtmlDocumentWrapper(xmlDocPtr _document);
        HtmlDocumentWrapper(HtmlDocumentWrapper &&source);
        ~HtmlDocumentWrapper();

        HtmlDocumentWrapper operator =(HtmlDocumentWrapper &&source);

        xmlpp::Element& root();
    private:
        HtmlDocumentWrapper(const HtmlDocumentWrapper &source) = delete;

        xmlDocPtr document;
        xmlpp::Element rootElement;
    };
}
