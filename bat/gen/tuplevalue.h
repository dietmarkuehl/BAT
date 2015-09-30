// bat/gen/tuplevalue.h                                               -*-C++-*-
// ----------------------------------------------------------------------------
//  Copyright (C) 2015 Dietmar Kuehl http://www.dietmar-kuehl.de         
//                                                                       
//  Permission is hereby granted, free of charge, to any person          
//  obtaining a copy of this software and associated documentation       
//  files (the "Software"), to deal in the Software without restriction, 
//  including without limitation the rights to use, copy, modify,        
//  merge, publish, distribute, sublicense, and/or sell copies of        
//  the Software, and to permit persons to whom the Software is          
//  furnished to do so, subject to the following conditions:             
//                                                                       
//  The above copyright notice and this permission notice shall be       
//  included in all copies or substantial portions of the Software.      
//                                                                       
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES      
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND             
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT          
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,         
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING         
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR        
//  OTHER DEALINGS IN THE SOFTWARE. 
// ----------------------------------------------------------------------------

#ifndef INCLUDED_BAT_GEN_TUPLEVALUE
#define INCLUDED_BAT_GEN_TUPLEVALUE

#include "bat/gen/tupleequalto.h"
#include "bat/gen/tuplehash.h"
#include "bat/gen/tuplelessthan.h"
#include "bat/gen/tupleoutput.h"

// ----------------------------------------------------------------------------
// The class template `batgen::TupleValue<T>` is used to provide several value
// operators for `T` based on a tuple-like member declaration (see
// `batgen::tuple`): simply derive from `batgen::TupleValue<T>` and provide a
// member `typedef` named `tuple` listing the salient members of `T`. The
// operations provided are
//  - output `operator<<()`
//  - equality operators `operator==()` and `operator!=()`
//  - relation operators `operator<()`, `operator>()`, `operator<=()`, and
//    `operator>=()`
//  - `hashAppend()` to compute a hash value
// For example:
//
//    class Value
//        : private batgen::TupleValue<Value>
//    {
//        bool bv;
//        int  iv;
//        char cv;
//    public:
//        typedef batgen::TupleMembers<
//            batgen::TupleConstMembers<bool, Value, &Value::bv>,
//            batgen::TupleConstMembers<int,  Value, &Value::iv>,
//            batgen::TupleConstMembers<char, Value, &Value::cv>
//        > tuple;
//
//        Value(bool bv, int iv, char cv) : bv(bv), iv(iv), cv(cv) {}
//    };
//
// The base class `batgen::TupleValue<Value>` can [and probably should] be
// `private`! The provided operators are non-member operators found via ADL.

namespace BloombergLP {
    namespace batgen {
        template <typename> class TupleValue;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
class BloombergLP::batgen::TupleValue
    : BloombergLP::batgen::TupleEqualTo<Type>
    , BloombergLP::batgen::TupleHash<Type>
    , BloombergLP::batgen::TupleLessThan<Type>
    , BloombergLP::batgen::TupleOutput<Type>
{
};

// ----------------------------------------------------------------------------

#endif
