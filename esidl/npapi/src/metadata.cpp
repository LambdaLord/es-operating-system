/*
 * Copyright 2008-2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "esnpapi.h"
#include "proxyImpl.h"

#include <any.h>
#include <reflect.h>
#include <org/w3c/dom.h>

using namespace org::w3c::dom;

void initializeMetaData()
{
    registerMetaData(Attr::getMetaData(), Proxy_Impl<ProxyObject, Attr_Bridge<Any, invoke> >::createInstance);
    registerMetaData(CaretPosition::getMetaData(), Proxy_Impl<ProxyObject, CaretPosition_Bridge<Any, invoke> >::createInstance);
    registerMetaData(CDATASection::getMetaData(), Proxy_Impl<ProxyObject, CDATASection_Bridge<Any, invoke> >::createInstance);
    registerMetaData(CharacterData::getMetaData(), Proxy_Impl<ProxyObject, CharacterData_Bridge<Any, invoke> >::createInstance);
    registerMetaData(Comment::getMetaData(), Proxy_Impl<ProxyObject, Comment_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DocumentFragment::getMetaData(), Proxy_Impl<ProxyObject, DocumentFragment_Bridge<Any, invoke> >::createInstance);
    registerMetaData(Document::getMetaData(), Proxy_Impl<ProxyObject, Document_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DocumentType::getMetaData(), Proxy_Impl<ProxyObject, DocumentType_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMConfiguration::getMetaData(), Proxy_Impl<ProxyObject, DOMConfiguration_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMError::getMetaData(), Proxy_Impl<ProxyObject, DOMError_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMErrorHandler::getMetaData(), Proxy_Impl<ProxyObject, DOMErrorHandler_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMImplementation::getMetaData(), Proxy_Impl<ProxyObject, DOMImplementation_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMImplementationList::getMetaData(), Proxy_Impl<ProxyObject, DOMImplementationList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMImplementationSource::getMetaData(), Proxy_Impl<ProxyObject, DOMImplementationSource_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMLocator::getMetaData(), Proxy_Impl<ProxyObject, DOMLocator_Bridge<Any, invoke> >::createInstance);
    registerMetaData(DOMStringList::getMetaData(), Proxy_Impl<ProxyObject, DOMStringList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(Element::getMetaData(), Proxy_Impl<ProxyObject, Element_Bridge<Any, invoke> >::createInstance);
    registerMetaData(Entity::getMetaData(), Proxy_Impl<ProxyObject, Entity_Bridge<Any, invoke> >::createInstance);
    registerMetaData(EntityReference::getMetaData(), Proxy_Impl<ProxyObject, EntityReference_Bridge<Any, invoke> >::createInstance);
    registerMetaData(NamedNodeMap::getMetaData(), Proxy_Impl<ProxyObject, NamedNodeMap_Bridge<Any, invoke> >::createInstance);
    registerMetaData(NameList::getMetaData(), Proxy_Impl<ProxyObject, NameList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(Node::getMetaData(), Proxy_Impl<ProxyObject, Node_Bridge<Any, invoke> >::createInstance);
    registerMetaData(NodeList::getMetaData(), Proxy_Impl<ProxyObject, NodeList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(Notation::getMetaData(), Proxy_Impl<ProxyObject, Notation_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ProcessingInstruction::getMetaData(), Proxy_Impl<ProxyObject, ProcessingInstruction_Bridge<Any, invoke> >::createInstance);
    registerMetaData(Text::getMetaData(), Proxy_Impl<ProxyObject, Text_Bridge<Any, invoke> >::createInstance);
    registerMetaData(TypeInfo::getMetaData(), Proxy_Impl<ProxyObject, TypeInfo_Bridge<Any, invoke> >::createInstance);
    registerMetaData(UserDataHandler::getMetaData(), Proxy_Impl<ProxyObject, UserDataHandler_Bridge<Any, invoke> >::createInstance);
    registerMetaData(XMLHttpRequestEventTarget::getMetaData(), Proxy_Impl<ProxyObject, XMLHttpRequestEventTarget_Bridge<Any, invoke> >::createInstance);
    registerMetaData(XMLHttpRequest::getMetaData(), Proxy_Impl<ProxyObject, XMLHttpRequest_Bridge<Any, invoke> >::createInstance);
    registerMetaData(XMLHttpRequestUpload::getMetaData(), Proxy_Impl<ProxyObject, XMLHttpRequestUpload_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::Counter::getMetaData(), Proxy_Impl<ProxyObject, css::Counter_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSS2Properties::getMetaData(), Proxy_Impl<ProxyObject, css::CSS2Properties_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSCharsetRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSCharsetRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSFontFaceRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSFontFaceRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSImportRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSImportRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSMediaRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSMediaRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSPageRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSPageRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSPrimitiveValue::getMetaData(), Proxy_Impl<ProxyObject, css::CSSPrimitiveValue_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSRuleList::getMetaData(), Proxy_Impl<ProxyObject, css::CSSRuleList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSStyleDeclaration::getMetaData(), Proxy_Impl<ProxyObject, css::CSSStyleDeclaration_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSStyleRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSStyleRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSStyleSheet::getMetaData(), Proxy_Impl<ProxyObject, css::CSSStyleSheet_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSUnknownRule::getMetaData(), Proxy_Impl<ProxyObject, css::CSSUnknownRule_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSValue::getMetaData(), Proxy_Impl<ProxyObject, css::CSSValue_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::CSSValueList::getMetaData(), Proxy_Impl<ProxyObject, css::CSSValueList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::DocumentCSS::getMetaData(), Proxy_Impl<ProxyObject, css::DocumentCSS_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::DOMImplementationCSS::getMetaData(), Proxy_Impl<ProxyObject, css::DOMImplementationCSS_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::ElementCSSInlineStyle::getMetaData(), Proxy_Impl<ProxyObject, css::ElementCSSInlineStyle_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::Rect::getMetaData(), Proxy_Impl<ProxyObject, css::Rect_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::RGBColor::getMetaData(), Proxy_Impl<ProxyObject, css::RGBColor_Bridge<Any, invoke> >::createInstance);
    registerMetaData(css::ViewCSS::getMetaData(), Proxy_Impl<ProxyObject, css::ViewCSS_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::DocumentEvent::getMetaData(), Proxy_Impl<ProxyObject, events::DocumentEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::Event::getMetaData(), Proxy_Impl<ProxyObject, events::Event_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::EventListener::getMetaData(), Proxy_Impl<ProxyObject, events::EventListener_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::EventTarget::getMetaData(), Proxy_Impl<ProxyObject, events::EventTarget_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::MouseEvent::getMetaData(), Proxy_Impl<ProxyObject, events::MouseEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::MutationEvent::getMetaData(), Proxy_Impl<ProxyObject, events::MutationEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(eventsource::EventSource::getMetaData(), Proxy_Impl<ProxyObject, eventsource::EventSource_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::ProgressEvent::getMetaData(), Proxy_Impl<ProxyObject, events::ProgressEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(events::UIEvent::getMetaData(), Proxy_Impl<ProxyObject, events::UIEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::DOMImplementationLS::getMetaData(), Proxy_Impl<ProxyObject, ls::DOMImplementationLS_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSInput::getMetaData(), Proxy_Impl<ProxyObject, ls::LSInput_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSLoadEvent::getMetaData(), Proxy_Impl<ProxyObject, ls::LSLoadEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSOutput::getMetaData(), Proxy_Impl<ProxyObject, ls::LSOutput_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSParserFilter::getMetaData(), Proxy_Impl<ProxyObject, ls::LSParserFilter_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSParser::getMetaData(), Proxy_Impl<ProxyObject, ls::LSParser_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSProgressEvent::getMetaData(), Proxy_Impl<ProxyObject, ls::LSProgressEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSResourceResolver::getMetaData(), Proxy_Impl<ProxyObject, ls::LSResourceResolver_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSSerializerFilter::getMetaData(), Proxy_Impl<ProxyObject, ls::LSSerializerFilter_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ls::LSSerializer::getMetaData(), Proxy_Impl<ProxyObject, ls::LSSerializer_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ranges::DocumentRange::getMetaData(), Proxy_Impl<ProxyObject, ranges::DocumentRange_Bridge<Any, invoke> >::createInstance);
    registerMetaData(ranges::Range::getMetaData(), Proxy_Impl<ProxyObject, ranges::Range_Bridge<Any, invoke> >::createInstance);
    registerMetaData(stylesheets::DocumentStyle::getMetaData(), Proxy_Impl<ProxyObject, stylesheets::DocumentStyle_Bridge<Any, invoke> >::createInstance);
    registerMetaData(stylesheets::LinkStyle::getMetaData(), Proxy_Impl<ProxyObject, stylesheets::LinkStyle_Bridge<Any, invoke> >::createInstance);
    registerMetaData(stylesheets::MediaList::getMetaData(), Proxy_Impl<ProxyObject, stylesheets::MediaList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(stylesheets::StyleSheet::getMetaData(), Proxy_Impl<ProxyObject, stylesheets::StyleSheet_Bridge<Any, invoke> >::createInstance);
    registerMetaData(stylesheets::StyleSheetList::getMetaData(), Proxy_Impl<ProxyObject, stylesheets::StyleSheetList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(traversal::DocumentTraversal::getMetaData(), Proxy_Impl<ProxyObject, traversal::DocumentTraversal_Bridge<Any, invoke> >::createInstance);
    registerMetaData(traversal::NodeFilter::getMetaData(), Proxy_Impl<ProxyObject, traversal::NodeFilter_Bridge<Any, invoke> >::createInstance);
    registerMetaData(traversal::NodeIterator::getMetaData(), Proxy_Impl<ProxyObject, traversal::NodeIterator_Bridge<Any, invoke> >::createInstance);
    registerMetaData(traversal::TreeWalker::getMetaData(), Proxy_Impl<ProxyObject, traversal::TreeWalker_Bridge<Any, invoke> >::createInstance);
    registerMetaData(validation::CharacterDataEditVAL::getMetaData(), Proxy_Impl<ProxyObject, validation::CharacterDataEditVAL_Bridge<Any, invoke> >::createInstance);
    registerMetaData(validation::DocumentEditVAL::getMetaData(), Proxy_Impl<ProxyObject, validation::DocumentEditVAL_Bridge<Any, invoke> >::createInstance);
    registerMetaData(validation::ElementEditVAL::getMetaData(), Proxy_Impl<ProxyObject, validation::ElementEditVAL_Bridge<Any, invoke> >::createInstance);
    registerMetaData(validation::NodeEditVAL::getMetaData(), Proxy_Impl<ProxyObject, validation::NodeEditVAL_Bridge<Any, invoke> >::createInstance);
    registerMetaData(views::AbstractView::getMetaData(), Proxy_Impl<ProxyObject, views::AbstractView_Bridge<Any, invoke> >::createInstance);
    registerMetaData(views::ClientRect::getMetaData(), Proxy_Impl<ProxyObject, views::ClientRect_Bridge<Any, invoke> >::createInstance);
    registerMetaData(views::ClientRectList::getMetaData(), Proxy_Impl<ProxyObject, views::ClientRectList_Bridge<Any, invoke> >::createInstance);
    registerMetaData(views::DocumentView::getMetaData(), Proxy_Impl<ProxyObject, views::DocumentView_Bridge<Any, invoke> >::createInstance);
    registerMetaData(webnotifications::NotificationCenter::getMetaData(), Proxy_Impl<ProxyObject, webnotifications::NotificationCenter_Bridge<Any, invoke> >::createInstance);
    registerMetaData(webnotifications::Notification::getMetaData(), Proxy_Impl<ProxyObject, webnotifications::Notification_Bridge<Any, invoke> >::createInstance);
    registerMetaData(websocket::WebSocket::getMetaData(), Proxy_Impl<ProxyObject, websocket::WebSocket_Bridge<Any, invoke> >::createInstance);
    registerMetaData(webstorage::StorageEvent::getMetaData(), Proxy_Impl<ProxyObject, webstorage::StorageEvent_Bridge<Any, invoke> >::createInstance);
    registerMetaData(webstorage::Storage::getMetaData(), Proxy_Impl<ProxyObject, webstorage::Storage_Bridge<Any, invoke> >::createInstance);
    registerMetaData(xpath::XPathEvaluator::getMetaData(), Proxy_Impl<ProxyObject, xpath::XPathEvaluator_Bridge<Any, invoke> >::createInstance);
    registerMetaData(xpath::XPathExpression::getMetaData(), Proxy_Impl<ProxyObject, xpath::XPathExpression_Bridge<Any, invoke> >::createInstance);
    registerMetaData(xpath::XPathNamespace::getMetaData(), Proxy_Impl<ProxyObject, xpath::XPathNamespace_Bridge<Any, invoke> >::createInstance);
    registerMetaData(xpath::XPathNSResolver::getMetaData(), Proxy_Impl<ProxyObject, xpath::XPathNSResolver_Bridge<Any, invoke> >::createInstance);
    registerMetaData(xpath::XPathResult::getMetaData(), Proxy_Impl<ProxyObject, xpath::XPathResult_Bridge<Any, invoke> >::createInstance);
}