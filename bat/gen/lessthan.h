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
// The class template `LessThan` is used to tag a type as providing an ordering
// relation. A class providing a less than operator (operator<()) could derive
// from it to get the other relational operations provided based on the less
// than operator. If the class `Type` deriving from `LessThan<Type>` doesn't
// provide a less than operator, it is assumed that there is a member operation
// `lessThan()` which can be used to implement the less than operation.


namespace BloombergLP {
    namespace batgen {
        template <typename T> struct LessThan;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
struct BloombergLP::batgen::LessThan {
    friend bool operator< (Type const& value0, Type const& value1) {
        return value0.lessThan(value1);
    }

    friend bool operator<= (Type const& value0, Type const& value1) {
        return !(value1 < value0);
    }

    friend bool operator> (Type const& value0, Type const& value1) {
        return value1 < value0;
    }

    friend bool operator>= (Type const& value0, Type const& value1) {
        return !(value0 < value1);
    }
};

// ----------------------------------------------------------------------------

#endif
