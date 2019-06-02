#include "HtmlDocumentWrapper.h"

namespace HellGateBot
{
    HtmlDocumentWrapper::HtmlDocumentWrapper(xmlDocPtr _document) :
        rootElement(xmlDocGetRootElement(_document)),
        document(_document)
    {
    }

    HtmlDocumentWrapper::HtmlDocumentWrapper(HtmlDocumentWrapper &&source) :
        rootElement(xmlDocGetRootElement(source.document))
    {
        document = source.document;
        source.document = nullptr;
    }

    HtmlDocumentWrapper::~HtmlDocumentWrapper()
    {
        if (document)
        {
            xmlFreeDoc(document);
        }
    }

    HtmlDocumentWrapper HtmlDocumentWrapper::operator =(HtmlDocumentWrapper &&source)
    {
        return std::move(source);
    }

    xmlpp::Element& HtmlDocumentWrapper::root()
    {
        return rootElement;
    }
}
