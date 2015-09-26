// bat/gen/tupleequalto.t.cpp                                         -*-C++-*-
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

#include "bat/gen/tupleequalto.h"
#include "bat/gen/tuplelike.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace BloombergLP;

// ----------------------------------------------------------------------------

namespace {
    class Value
        : private batgen::tuple_equalto<Value> {
        bool bv;
        int  iv;
        char cv;
    public:
        typedef batgen::elements<
            batgen::const_element<bool, Value, &Value::bv>,
            batgen::const_element<int,  Value, &Value::iv>,
            batgen::const_element<char, Value, &Value::cv>
        > tuple;

        Value(bool bv, int iv, char cv) : bv(bv), iv(iv), cv(cv) {}
    };
}

// ----------------------------------------------------------------------------

TEST_CASE("breating test", "[batgen::tuple_like]") {
    Value value0(true,  17, 'a');
    Value value1(false, 17, 'a');
    Value value2(true,  18, 'a');
    Value value3(true,  17, 'b');

    REQUIRE(value0 == value0);
    REQUIRE(!(value0 != value0));

    REQUIRE(!(value0 == value1));
    REQUIRE(value0 != value1);
    REQUIRE(!(value0 == value2));
    REQUIRE(value0 != value2);
    REQUIRE(!(value0 == value3));
    REQUIRE(value0 != value3);
}
