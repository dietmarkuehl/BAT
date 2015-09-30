// bat/gen/tuplelessthan.h                                            -*-C++-*-
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

#ifndef INCLUDED_BAT_GEN_TUPLELESSTHAN
#define INCLUDED_BAT_GEN_TUPLELESSTHAN

#include "bat/gen/tuple.h"
#include <bslmf_enableif.h>

// ----------------------------------------------------------------------------
// The class template `batgen::TupleLessThan<T>` is used to provide relational
// operators for `T` based on a tuple-like member declaration (see
// `batgen::tuple`): simply derive from `batgen::TupleLessThan<T>` and provide
// a member `typedef` named `tuple` listing the salient members of `T`. For
// example:
//
//    class Value
//        : private batgen::TupleLessThan<Value>
//    {
//        bool bv;
//        int  iv;
//        char cv;
//    public:
//        typedef batgen::TupleMembers<
//            batgen::TupleConstMember<bool, Value, &Value::bv>,
//            batgen::TupleConstMember<int,  Value, &Value::iv>,
//            batgen::TupleConstMember<char, Value, &Value::cv>
//        > tuple;
//
//        Value(bool bv, int iv, char cv) : bv(bv), iv(iv), cv(cv) {}
//    };
//
// The base class `batgen::TupleLessThan<Value>` can [and probably should] be
// `private`! The provided operators are non-member operators found via ADL.

namespace BloombergLP {
    namespace batgen {
        template <typename> class TupleLessThan;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
class BloombergLP::batgen::TupleLessThan
{
    template <int Index, typename T>
    static
    typename bsl::enable_if<batgen::TupleSize<T>::value <= Index, bool>::type
    compare(T const&, T const&) {
        return false;
    }
    template <int Index, typename T>
    static
    typename bsl::enable_if<Index < batgen::TupleSize<T>::value, bool>::type
    compare(T const& value0, T const& value1) {
        return batgen::get<Index>(value0) < batgen::get<Index>(value1)
            || (!(batgen::get<Index>(value1) < batgen::get<Index>(value0))
                && TupleLessThan<Type>::compare<Index + 1>(value0, value1));
    }
    friend bool operator<  (Type const& value0, Type const& value1) {
        return TupleLessThan<Type>::compare<0>(value0, value1);
    }
    friend bool operator<= (Type const& value0, Type const& value1) {
        return !(value1 < value0);
    }
    friend bool operator>  (Type const& value0, Type const& value1) {
        return value1 < value0;
    }
    friend bool operator>= (Type const& value0, Type const& value1) {
        return !(value0 < value1);
    }
};

// ----------------------------------------------------------------------------

#endif
