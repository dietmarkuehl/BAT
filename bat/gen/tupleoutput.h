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

namespace BloombergLP {
    namespace batgen {
        template <typename> class tuple_output;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
class BloombergLP::batgen::tuple_output
{
    template <int Index, typename T>
    static
    typename bsl::enable_if<batgen::tuple_size<T>::value <= Index>::type
    print(bsl::ostream&, T const&) {
    }
    template <int Index, typename T>
    static
    typename bsl::enable_if<Index < batgen::tuple_size<T>::value>::type
    print(bsl::ostream& out, T const& value) {
        out << ' ' << batgen::get<Index>(value)
            << (Index + 1 < batgen::tuple_size<Type>::value? ",": " ");
        tuple_output<Type>::print<Index + 1>(out, value);
    }
    friend bsl::ostream& operator<< (bsl::ostream& out, Type const& value) {
        out << "{";
        tuple_output<Type>::print<0>(out, value);
        return out << "}";
    }
};

// ----------------------------------------------------------------------------

#endif
