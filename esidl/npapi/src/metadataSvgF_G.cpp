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

#include <org/w3c/dom.h>

using namespace org::w3c::dom;

void initializeSvgMetaDataF_G()
{
    ProxyControl::registerMetaData(svg::SVGFEBlendElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEBlendElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEColorMatrixElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEColorMatrixElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEComponentTransferElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEComponentTransferElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFECompositeElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFECompositeElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEConvolveMatrixElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEConvolveMatrixElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEDiffuseLightingElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEDiffuseLightingElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEDisplacementMapElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEDisplacementMapElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEDistantLightElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEDistantLightElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEFloodElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEFloodElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEFuncAElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEFuncAElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEFuncBElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEFuncBElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEFuncGElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEFuncGElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEFuncRElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEFuncRElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEGaussianBlurElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEGaussianBlurElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEImageElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEImageElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEMergeElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEMergeElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEMergeNodeElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEMergeNodeElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEMorphologyElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEMorphologyElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEOffsetElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEOffsetElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFEPointLightElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFEPointLightElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFESpecularLightingElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFESpecularLightingElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFESpotLightElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFESpotLightElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFETileElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFETileElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFETurbulenceElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFETurbulenceElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFilterElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFilterElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFilterPrimitiveStandardAttributes::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFilterPrimitiveStandardAttributes_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFitToViewBox::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFitToViewBox_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFontElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFontElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFontFaceElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFontFaceElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFontFaceFormatElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFontFaceFormatElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFontFaceNameElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFontFaceNameElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFontFaceSrcElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFontFaceSrcElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGFontFaceUriElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGFontFaceUriElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGForeignObjectElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGForeignObjectElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGGElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGGElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGGlyphElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGGlyphElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGGlyphRefElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGGlyphRefElement_Bridge<Any, invoke> >::createInstance);
    ProxyControl::registerMetaData(svg::SVGGradientElement::getMetaData(), Proxy_Impl<ProxyObject, svg::SVGGradientElement_Bridge<Any, invoke> >::createInstance);
}