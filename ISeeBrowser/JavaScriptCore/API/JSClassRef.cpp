/*
 * Copyright (C) 2006, 2007 Apple Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "JSClassRef.h"

#include "APICast.h"
#include "JSCallbackObject.h"
#include "JSObjectRef.h"
#include <kjs/InitializeThreading.h>
#include <kjs/JSGlobalObject.h>
#include <kjs/ObjectPrototype.h>
#include <kjs/identifier.h>

using namespace JSC;

const JSClassDefinition kJSClassDefinitionEmpty = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

OpaqueJSClass::OpaqueJSClass(const JSClassDefinition* definition, OpaqueJSClass* protoClass) 
    : parentClass(definition->parentClass)
    , prototypeClass(0)
    , initialize(definition->initialize)
    , finalize(definition->finalize)
    , hasProperty(definition->hasProperty)
    , getProperty(definition->getProperty)
    , setProperty(definition->setProperty)
    , deleteProperty(definition->deleteProperty)
    , getPropertyNames(definition->getPropertyNames)
    , callAsFunction(definition->callAsFunction)
    , callAsConstructor(definition->callAsConstructor)
    , hasInstance(definition->hasInstance)
    , convertToType(definition->convertToType)
    , m_className(UString::Rep::createFromUTF8(definition->className))
    , m_staticValues(0)
    , m_staticFunctions(0)
{
    initializeThreading();

    if (const JSStaticValue* staticValue = definition->staticValues) {
        m_staticValues = new OpaqueJSClassStaticValuesTable();
        while (staticValue->name) {
            m_staticValues->add(UString::Rep::createFromUTF8(staticValue->name),
                              new StaticValueEntry(staticValue->getProperty, staticValue->setProperty, staticValue->attributes));
            ++staticValue;
        }
    }

    if (const JSStaticFunction* staticFunction = definition->staticFunctions) {
        m_staticFunctions = new OpaqueJSClassStaticFunctionsTable();
        while (staticFunction->name) {
            m_staticFunctions->add(UString::Rep::createFromUTF8(staticFunction->name),
                                 new StaticFunctionEntry(staticFunction->callAsFunction, staticFunction->attributes));
            ++staticFunction;
        }
    }
        
    if (protoClass)
        prototypeClass = JSClassRetain(protoClass);
}

OpaqueJSClass::~OpaqueJSClass()
{
    ASSERT(!m_className.rep()->identifierTable());

    if (m_staticValues) {
        OpaqueJSClassStaticValuesTable::const_iterator end = m_staticValues->end();
        for (OpaqueJSClassStaticValuesTable::const_iterator it = m_staticValues->begin(); it != end; ++it) {
            ASSERT(!it->first->identifierTable());
            delete it->second;
        }
        delete m_staticValues;
    }

    if (m_staticFunctions) {
        OpaqueJSClassStaticFunctionsTable::const_iterator end = m_staticFunctions->end();
        for (OpaqueJSClassStaticFunctionsTable::const_iterator it = m_staticFunctions->begin(); it != end; ++it) {
            ASSERT(!it->first->identifierTable());
            delete it->second;
        }
        delete m_staticFunctions;
    }
    
    if (prototypeClass)
        JSClassRelease(prototypeClass);
}

PassRefPtr<OpaqueJSClass> OpaqueJSClass::createNoAutomaticPrototype(const JSClassDefinition* definition)
{
    return adoptRef(new OpaqueJSClass(definition, 0));
}

void clearReferenceToPrototype(JSObjectRef prototype)
{
    OpaqueJSClassContextData* jsClassData = static_cast<OpaqueJSClassContextData*>(JSObjectGetPrivate(prototype));
    ASSERT(jsClassData);
    jsClassData->cachedPrototype = 0;
}

PassRefPtr<OpaqueJSClass> OpaqueJSClass::create(const JSClassDefinition* definition)
{
    if (const JSStaticFunction* staticFunctions = definition->staticFunctions) {
        // copy functions into a prototype class
        JSClassDefinition protoDefinition = kJSClassDefinitionEmpty;
        protoDefinition.staticFunctions = staticFunctions;
        protoDefinition.finalize = clearReferenceToPrototype;
        
        // We are supposed to use JSClassRetain/Release but since we know that we currently have
        // the only reference to this class object we cheat and use a RefPtr instead.
        RefPtr<OpaqueJSClass> protoClass = adoptRef(new OpaqueJSClass(&protoDefinition, 0));

        // remove functions from the original class
        JSClassDefinition objectDefinition = *definition;
        objectDefinition.staticFunctions = 0;

        return adoptRef(new OpaqueJSClass(&objectDefinition, protoClass.get()));
    }

    return adoptRef(new OpaqueJSClass(definition, 0));
}

OpaqueJSClassContextData::OpaqueJSClassContextData(OpaqueJSClass* jsClass)
    : m_class(jsClass)
    , cachedPrototype(0)
{
    if (jsClass->m_staticValues) {
        staticValues = new OpaqueJSClassStaticValuesTable;
        OpaqueJSClassStaticValuesTable::const_iterator end = jsClass->m_staticValues->end();
        for (OpaqueJSClassStaticValuesTable::const_iterator it = jsClass->m_staticValues->begin(); it != end; ++it) {
            ASSERT(!it->first->identifierTable());
            staticValues->add(UString::Rep::createCopying(it->first->data(), it->first->size()),
                              new StaticValueEntry(it->second->getProperty, it->second->setProperty, it->second->attributes));
        }
            
    } else
        staticValues = 0;
        

    if (jsClass->m_staticFunctions) {
        staticFunctions = new OpaqueJSClassStaticFunctionsTable;
        OpaqueJSClassStaticFunctionsTable::const_iterator end = jsClass->m_staticFunctions->end();
        for (OpaqueJSClassStaticFunctionsTable::const_iterator it = jsClass->m_staticFunctions->begin(); it != end; ++it) {
            ASSERT(!it->first->identifierTable());
            staticFunctions->add(UString::Rep::createCopying(it->first->data(), it->first->size()),
                              new StaticFunctionEntry(it->second->callAsFunction, it->second->attributes));
        }
            
    } else
        staticFunctions = 0;
}

OpaqueJSClassContextData::~OpaqueJSClassContextData()
{
    if (staticValues) {
        deleteAllValues(*staticValues);
        delete staticValues;
    }

    if (staticFunctions) {
        deleteAllValues(*staticFunctions);
        delete staticFunctions;
    }
}

OpaqueJSClassContextData& OpaqueJSClass::contextData(ExecState* exec)
{
    HashMap<OpaqueJSClass*, OpaqueJSClassContextData*>* contextDataMap = exec->globalData().opaqueJSClassData;
    HashMap<OpaqueJSClass*, OpaqueJSClassContextData*>::iterator iter = contextDataMap->find(this);
    if (iter != contextDataMap->end())
        return *iter->second;
    return *contextDataMap->add(this, new OpaqueJSClassContextData(this)).first->second;
}

UString OpaqueJSClass::className()
{
    // Make a deep copy, so that the caller has no chance to put the original into IdentifierTable.
    return UString(m_className.data(), m_className.size());
}

OpaqueJSClassStaticValuesTable* OpaqueJSClass::staticValues(JSC::ExecState* exec)
{
    OpaqueJSClassContextData& jsClassData = contextData(exec);
    return jsClassData.staticValues;
}

OpaqueJSClassStaticFunctionsTable* OpaqueJSClass::staticFunctions(JSC::ExecState* exec)
{
    OpaqueJSClassContextData& jsClassData = contextData(exec);
    return jsClassData.staticFunctions;
}

/*!
// Doc here in case we make this public. (Hopefully we won't.)
@function
 @abstract Returns the prototype that will be used when constructing an object with a given class.
 @param ctx The execution context to use.
 @param jsClass A JSClass whose prototype you want to get.
 @result The JSObject prototype that was automatically generated for jsClass, or NULL if no prototype was automatically generated. This is the prototype that will be used when constructing an object using jsClass.
*/
JSObject* OpaqueJSClass::prototype(ExecState* exec)
{
    /* Class (C++) and prototype (JS) inheritance are parallel, so:
     *     (C++)      |        (JS)
     *   ParentClass  |   ParentClassPrototype
     *       ^        |          ^
     *       |        |          |
     *  DerivedClass  |  DerivedClassPrototype
     */
    
    if (!prototypeClass)
        return 0;

    OpaqueJSClassContextData& jsClassData = contextData(exec);

    if (!jsClassData.cachedPrototype) {
        // Recursive, but should be good enough for our purposes
        JSObject* parentPrototype = 0;
        if (parentClass)
            parentPrototype = parentClass->prototype(exec); // can be null
        if (!parentPrototype)
            parentPrototype = exec->dynamicGlobalObject()->objectPrototype();
        jsClassData.cachedPrototype = new (exec) JSCallbackObject<JSObject>(exec, prototypeClass, parentPrototype, &jsClassData); // set jsClassData as the object's private data, so it can clear our reference on destruction
    }
    return jsClassData.cachedPrototype;
}
