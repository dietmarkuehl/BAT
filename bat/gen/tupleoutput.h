// bat/gen/tupleoutput.h                                              -*-C++-*-
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

#ifndef INCLUDED_BAT_GEN_TUPLEOUTPUT
#define INCLUDED_BAT_GEN_TUPLEOUTPUT

#include "bat/gen/tuple.h"
#include <bsl_ostream.h>
#include <bslmf_enableif.h>

// ----------------------------------------------------------------------------
// The class template `batgen::tuple_output<T>` is used to provide an output
// operator for `T` based on a tuple-like member declaration (see
// `batgen::tuple`): simply derive from `batgen::tuple_output<T>` and provide
// a member `typedef` named `tuple` listing the salient members of `T`. For
// example:
//
//    class Value
//        : private batgen::tuple_output<Value>
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
// The base class `batgen::tuple_output<Value>` can [and probably should] be
// `private`! The provided operators are non-member operators found via ADL.


namespace BloombergLP {
    namespace batgen {
        template <typename> class tuple_output;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
class BloombergLP::batgen::tuple_output
{
    template <int Index, typename cT, typename Traits, typename T>
    static
    typename bsl::enable_if<batgen::tuple_size<T>::value <= Index>::type
    print(bsl::basic_ostream<cT, Traits>&, T const&) {
    }
    template <int Index, typename cT, typename Traits, typename T>
    static
    typename bsl::enable_if<Index < batgen::tuple_size<T>::value>::type
    print(bsl::basic_ostream<cT, Traits>& out, T const& value) {
        out << out.widen(' ') << batgen::get<Index>(value)
            << out.widen(Index + 1 < batgen::tuple_size<Type>::value? ',': ' ');
        tuple_output<Type>::print<Index + 1>(out, value);
    }
    template <typename cT, typename Traits>
    friend bsl::basic_ostream<cT, Traits>&
    operator<< (bsl::basic_ostream<cT, Traits>& out, Type const& value) {
        out << out.widen('{');
        tuple_output<Type>::print<0>(out, value);
        return out << out.widen('}');
    }
};

// ----------------------------------------------------------------------------

#endif
