// bat/gen/lessthan.h                                                 -*-C++-*-
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

#ifndef INCLUDED_BATGEN_LESSTHAN
#define INCLUDED_BATGEN_LESSTHAN

#include <bat/mf/isbaseof.h>
#include <bslmf_enableif.h>

// ----------------------------------------------------------------------------

namespace BloombergLP {
    namespace batgen {
        namespace less_than {
            struct tag {};

            template <typename Type>
            typename bsl::enable_if<batmf::IsBaseOf<tag, Type>::value, bool>::type
            operator< (Type const& value0, Type const& value1) {
                return value0.less_than(value1);
            }

            template <typename Type>
            typename bsl::enable_if<batmf::IsBaseOf<tag, Type>::value, bool>::type
            operator<= (Type const& value0, Type const& value1) {
                return !value1.less_than(value0);
            }

            template <typename Type>
            typename bsl::enable_if<batmf::IsBaseOf<tag, Type>::value, bool>::type
            operator> (Type const& value0, Type const& value1) {
                return value1.less_than(value0);
            }

            template <typename Type>
            typename bsl::enable_if<batmf::IsBaseOf<tag, Type>::value, bool>::type
            operator>= (Type const& value0, Type const& value1) {
                return !value0.less_than(value1);
            }
        }
    }
}

// ----------------------------------------------------------------------------

#endif
