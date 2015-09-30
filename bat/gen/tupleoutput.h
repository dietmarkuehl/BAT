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
// The class template `batgen::TupleOutput<T>` is used to provide an output
// operator for `T` based on a tuple-like member declaration (see
// `batgen::tuple`): simply derive from `batgen::TupleOutput<T>` and provide
// a member `typedef` named `tuple` listing the salient members of `T`. For
// example:
//
//    class Value
//        : private batgen::TupleOutput<Value>
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
// The base class `batgen::TupleOutput<Value>` can [and probably should] be
// `private`! The provided operators are non-member operators found via ADL.


namespace BloombergLP {
    namespace batgen {
        template <typename> class TupleOutput;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
class BloombergLP::batgen::TupleOutput
{
    template <int Index, typename cT, typename Traits, typename T>
    static
    typename bsl::enable_if<batgen::TupleSize<T>::value <= Index>::type
    print(bsl::basic_ostream<cT, Traits>&, T const&) {
    }
    template <int Index, typename cT, typename Traits, typename T>
    static
    typename bsl::enable_if<Index < batgen::TupleSize<T>::value>::type
    print(bsl::basic_ostream<cT, Traits>& out, T const& value) {
        out << out.widen(' ') << batgen::get<Index>(value)
            << out.widen(Index + 1 < batgen::TupleSize<Type>::value? ',': ' ');
        TupleOutput<Type>::print<Index + 1>(out, value);
    }
    template <typename cT, typename Traits>
    friend bsl::basic_ostream<cT, Traits>&
    operator<< (bsl::basic_ostream<cT, Traits>& out, Type const& value) {
        out << out.widen('{');
        TupleOutput<Type>::print<0>(out, value);
        return out << out.widen('}');
    }
};

// ----------------------------------------------------------------------------

#endif
