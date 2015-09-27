// bat/gen/tupleequalto.h                                             -*-C++-*-
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

#ifndef INCLUDED_BAT_GEN_TUPLEEQUALTO
#define INCLUDED_BAT_GEN_TUPLEEQUALTO

#include "bat/gen/tuple.h"
#include <bslmf_enableif.h>

// ----------------------------------------------------------------------------
// The class template `batgen::tuple_equalto<T>` is used to provide equality
// operators for `T` based on a tuple-like member declaration (see
// `batgen::tuple`): simply derive from `batgen::tuple_equalto<T>` and provide
// a member `typedef` named `tuple` listing the salient members of `T`. For
// example:
//
//    class Value
//        : private batgen::tuple_equalto<Value>
//    {
//        bool bv;
//        int  iv;
//        char cv;
//    public:
//        typedef batgen::tuple_members<
//            batgen::tuple_const_member<bool, Value, &Value::bv>,
//            batgen::tuple_const_member<int,  Value, &Value::iv>,
//            batgen::tuple_const_member<char, Value, &Value::cv>
//        > tuple;
//
//        Value(bool bv, int iv, char cv) : bv(bv), iv(iv), cv(cv) {}
//    };
//
// The base class `batgen::tuple_equalto<Value>` can [and probably should] be
// `private`! The provided operators are non-member operators found via ADL.

namespace BloombergLP {
    namespace batgen {
        template <typename> class tuple_equalto;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
class BloombergLP::batgen::tuple_equalto
{
    template <int Index, typename T>
    static
    typename bsl::enable_if<batgen::tuple_size<T>::value <= Index, bool>::type
    compare(T const&, T const&) {
        return true;
    }
    template <int Index, typename T>
    static
    typename bsl::enable_if<Index < batgen::tuple_size<T>::value, bool>::type
    compare(T const& value0, T const& value1) {
        return batgen::get<Index>(value0) == batgen::get<Index>(value1)
            && tuple_equalto<Type>::compare<Index + 1>(value0, value1);
    }
    friend bool operator== (Type const& value0, Type const& value1) {
        return tuple_equalto<Type>::compare<0>(value0, value1);
    }
    friend bool operator!= (Type const& value0, Type const& value1) {
        return !(value0 == value1);
    }
};

// ----------------------------------------------------------------------------

#endif
