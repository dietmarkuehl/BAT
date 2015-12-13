// bat/gen/equalto.h                                                  -*-C++-*-
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

#ifndef INCLUDED_BATGEN_EQUALTO
#define INCLUDED_BATGEN_EQUALTO

// ----------------------------------------------------------------------------
// The class template `EqualTo` is used to tag a type as providing an equality
// operation. A class providing an equality operation could derive from it to
// get the inequality operation provided based on the equality. If the class
// `Type` deriving from `EqualTo<Type>` doesn't provide an equality operator,
// it is assumed that there is a member operation `equalTo()` which can be
// used to implement the equality operation.

namespace BloombergLP {
    namespace batgen {
        template <typename Type> struct EqualTo;
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
struct BloombergLP::batgen::EqualTo {
    friend bool
    operator== (Type const& value0, Type const& value1) {
        return value0.equalTo(value1);
    }

    friend bool
    operator!= (Type const& value0, Type const& value1) {
        return !(value0 == value1);
    }
};

// ----------------------------------------------------------------------------

#endif
