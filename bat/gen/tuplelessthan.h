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

namespace BloombergLP {
    namespace batgen {
        template <typename> class tuple_lessthan;

        template <int Index, typename Type>
        typename bsl::enable_if<batgen::tuple_size<Type>::value <= Index, bool>::type
        tuple_lessthan_element(Type const&, Type const&) {
            return false;
        }
        template <int Index, typename Type>
        typename bsl::enable_if<Index < batgen::tuple_size<Type>::value, bool>::type
        tuple_lessthan_element(Type const& value0, Type const& value1) {
            return batgen::get<Index>(value0) < batgen::get<Index>(value1)
                || (!(batgen::get<Index>(value1) < batgen::get<Index>(value0))
                    && tuple_lessthan_element<Index + 1>(value0, value1));
        }
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
class BloombergLP::batgen::tuple_lessthan
{
    friend bool operator< (Type const& value0, Type const& value1) {
        return batgen::tuple_lessthan_element<0>(value0, value1);
    }
};

// ----------------------------------------------------------------------------

#endif
