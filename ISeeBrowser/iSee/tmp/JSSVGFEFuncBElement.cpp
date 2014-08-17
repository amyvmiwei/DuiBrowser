/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"


#if ENABLE(SVG) && ENABLE(SVG_FILTERS)

#include "Document.h"
#include "Frame.h"
#include "SVGDocumentExtensions.h"
#include "SVGElement.h"
#include "SVGAnimatedTemplate.h"
#include "JSSVGFEFuncBElement.h"

#include <wtf/GetPtr.h>

#include "SVGFEFuncBElement.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFEFuncBElement)

/* Hash table for prototype */

static const HashTableValue JSSVGFEFuncBElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFEFuncBElementPrototypeTable = { 0, JSSVGFEFuncBElementPrototypeTableValues, 0 };

const ClassInfo JSSVGFEFuncBElementPrototype::s_info = { "SVGFEFuncBElementPrototype", 0, &JSSVGFEFuncBElementPrototypeTable, 0 };

JSObject* JSSVGFEFuncBElementPrototype::self(ExecState* exec)
{
    static const Identifier* prototypeIdentifier = new Identifier(exec, "[[JSSVGFEFuncBElement.prototype]]");
    return JSC::cacheGlobalObject<JSSVGFEFuncBElementPrototype>(exec, *prototypeIdentifier);
}

const ClassInfo JSSVGFEFuncBElement::s_info = { "SVGFEFuncBElement", &JSSVGComponentTransferFunctionElement::s_info, 0 , 0 };

JSSVGFEFuncBElement::JSSVGFEFuncBElement(JSObject* prototype, SVGFEFuncBElement* impl)
    : JSSVGComponentTransferFunctionElement(prototype, impl)
{
}


}

#endif // ENABLE(SVG) && ENABLE(SVG_FILTERS)