/*
 * Copyright (C) 2003, 2008 Apple Inc. All rights reserved.
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

/*
* This file was modified by Electronic Arts Inc Copyright � 2009-2010
*/

#ifndef RegularExpression_h
#define RegularExpression_h

#include <wtf/FastAllocBase.h>
#include <wtf/RefPtr.h>

namespace OWBAL {

class String;

class RegularExpression/*: public WTF::FastAllocBase*/ {
public:
    RegularExpression();
    RegularExpression(const String&, bool caseSensitive = false);
    RegularExpression(const char*);
    ~RegularExpression();

    RegularExpression(const RegularExpression&);
    RegularExpression& operator=(const RegularExpression&);

    String pattern() const;
    int match(const String&, int startFrom = 0, int* matchLength = 0) const;

    int search(const String&, int startFrom = 0) const;
    int searchRev(const String&) const;

    int pos(int n = 0);
    int matchedLength() const;

private:
    class Private;    
    RefPtr<Private> d;
};

void replace(String&, const RegularExpression&, const String&);

} // namespace WebCore

#endif // RegularExpression_h
