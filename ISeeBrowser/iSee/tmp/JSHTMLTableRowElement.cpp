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

#include "JSHTMLTableRowElement.h"

#include <wtf/GetPtr.h>

#include "HTMLCollection.h"
#include "HTMLElement.h"
#include "HTMLTableRowElement.h"
#include "JSHTMLCollection.h"
#include "JSHTMLElement.h"
#include "KURL.h"

#include <kjs/Error.h>
#include <kjs/JSNumberCell.h>
#include <kjs/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLTableRowElement)

/* Hash table */

static const HashTableValue JSHTMLTableRowElementTableValues[10] =
{
    { "rowIndex", (intptr_t)JSHTMLTableRowElement::RowIndexAttrNum, DontDelete|ReadOnly, 0 },
    { "sectionRowIndex", (intptr_t)JSHTMLTableRowElement::SectionRowIndexAttrNum, DontDelete|ReadOnly, 0 },
    { "cells", (intptr_t)JSHTMLTableRowElement::CellsAttrNum, DontDelete|ReadOnly, 0 },
    { "align", (intptr_t)JSHTMLTableRowElement::AlignAttrNum, DontDelete, 0 },
    { "bgColor", (intptr_t)JSHTMLTableRowElement::BgColorAttrNum, DontDelete, 0 },
    { "ch", (intptr_t)JSHTMLTableRowElement::ChAttrNum, DontDelete, 0 },
    { "chOff", (intptr_t)JSHTMLTableRowElement::ChOffAttrNum, DontDelete, 0 },
    { "vAlign", (intptr_t)JSHTMLTableRowElement::VAlignAttrNum, DontDelete, 0 },
    { "constructor", (intptr_t)JSHTMLTableRowElement::ConstructorAttrNum, DontEnum, 0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTableRowElementTable = { 63, JSHTMLTableRowElementTableValues, 0 };

/* Hash table for constructor */

static const HashTableValue JSHTMLTableRowElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTableRowElementConstructorTable = { 0, JSHTMLTableRowElementConstructorTableValues, 0 };

class JSHTMLTableRowElementConstructor : public DOMObject {
public:
    JSHTMLTableRowElementConstructor(ExecState* exec)
        : DOMObject(exec->lexicalGlobalObject()->objectPrototype())
    {
        putDirect(exec->propertyNames().prototype, JSHTMLTableRowElementPrototype::self(exec), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    JSValue* getValueProperty(ExecState*, int token) const;
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    virtual bool implementsHasInstance() const { return true; }
};

const ClassInfo JSHTMLTableRowElementConstructor::s_info = { "HTMLTableRowElementConstructor", 0, &JSHTMLTableRowElementConstructorTable, 0 };

bool JSHTMLTableRowElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTableRowElementConstructor, DOMObject>(exec, &JSHTMLTableRowElementConstructorTable, this, propertyName, slot);
}

JSValue* JSHTMLTableRowElementConstructor::getValueProperty(ExecState* exec, int token) const
{
    // The token is the numeric value of its associated constant
    return jsNumber(exec, token);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLTableRowElementPrototypeTableValues[3] =
{
    { "insertCell", (intptr_t)jsHTMLTableRowElementPrototypeFunctionInsertCell, DontDelete|Function, 1 },
    { "deleteCell", (intptr_t)jsHTMLTableRowElementPrototypeFunctionDeleteCell, DontDelete|Function, 1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTableRowElementPrototypeTable = { 1, JSHTMLTableRowElementPrototypeTableValues, 0 };

const ClassInfo JSHTMLTableRowElementPrototype::s_info = { "HTMLTableRowElementPrototype", 0, &JSHTMLTableRowElementPrototypeTable, 0 };

JSObject* JSHTMLTableRowElementPrototype::self(ExecState* exec)
{
    static const Identifier* prototypeIdentifier = new Identifier(exec, "[[JSHTMLTableRowElement.prototype]]");
    return JSC::cacheGlobalObject<JSHTMLTableRowElementPrototype>(exec, *prototypeIdentifier);
}

bool JSHTMLTableRowElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSHTMLTableRowElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSHTMLTableRowElement::s_info = { "HTMLTableRowElement", &JSHTMLElement::s_info, &JSHTMLTableRowElementTable , 0 };

JSHTMLTableRowElement::JSHTMLTableRowElement(JSObject* prototype, HTMLTableRowElement* impl)
    : JSHTMLElement(prototype, impl)
{
}

bool JSHTMLTableRowElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTableRowElement, Base>(exec, &JSHTMLTableRowElementTable, this, propertyName, slot);
}

JSValue* JSHTMLTableRowElement::getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case RowIndexAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return jsNumber(exec, imp->rowIndex());
    }
    case SectionRowIndexAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return jsNumber(exec, imp->sectionRowIndex());
    }
    case CellsAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return toJS(exec, WTF::getPtr(imp->cells()));
    }
    case AlignAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return jsString(exec, imp->align());
    }
    case BgColorAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return jsString(exec, imp->bgColor());
    }
    case ChAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return jsString(exec, imp->ch());
    }
    case ChOffAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return jsString(exec, imp->chOff());
    }
    case VAlignAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        return jsString(exec, imp->vAlign());
    }
    case ConstructorAttrNum:
        return getConstructor(exec);
    }
    return 0;
}

void JSHTMLTableRowElement::put(ExecState* exec, const Identifier& propertyName, JSValue* value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLTableRowElement, Base>(exec, propertyName, value, &JSHTMLTableRowElementTable, this, slot);
}

void JSHTMLTableRowElement::putValueProperty(ExecState* exec, int token, JSValue* value)
{
    switch (token) {
    case AlignAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        imp->setAlign(valueToStringWithNullCheck(exec, value));
        break;
    }
    case BgColorAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        imp->setBgColor(valueToStringWithNullCheck(exec, value));
        break;
    }
    case ChAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        imp->setCh(valueToStringWithNullCheck(exec, value));
        break;
    }
    case ChOffAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        imp->setChOff(valueToStringWithNullCheck(exec, value));
        break;
    }
    case VAlignAttrNum: {
        HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(impl());
        imp->setVAlign(valueToStringWithNullCheck(exec, value));
        break;
    }
    }
}

JSValue* JSHTMLTableRowElement::getConstructor(ExecState* exec)
{
    static const Identifier* constructorIdentifier = new Identifier(exec, "[[HTMLTableRowElement.constructor]]");
    return JSC::cacheGlobalObject<JSHTMLTableRowElementConstructor>(exec, *constructorIdentifier);
}

JSValue* jsHTMLTableRowElementPrototypeFunctionInsertCell(ExecState* exec, JSObject*, JSValue* thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSHTMLTableRowElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLTableRowElement* castedThisObj = static_cast<JSHTMLTableRowElement*>(thisValue);
    HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    int index = args.at(exec, 0)->toInt32(exec);


    JSC::JSValue* result = toJS(exec, WTF::getPtr(imp->insertCell(index, ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue* jsHTMLTableRowElementPrototypeFunctionDeleteCell(ExecState* exec, JSObject*, JSValue* thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSHTMLTableRowElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLTableRowElement* castedThisObj = static_cast<JSHTMLTableRowElement*>(thisValue);
    HTMLTableRowElement* imp = static_cast<HTMLTableRowElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    int index = args.at(exec, 0)->toInt32(exec);

    imp->deleteCell(index, ec);
    setDOMException(exec, ec);
    return jsUndefined();
}


}
