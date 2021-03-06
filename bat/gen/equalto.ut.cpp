// bat/gen/equalto.t.cpp                                              -*-C++-*-
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

#include "bat/gen/equalto.h"
#include <bsl_iostream.h>
#include <bsl_stdexcept.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace BloombergLP;

// ----------------------------------------------------------------------------

namespace {
    class Value
        : private batgen::EqualTo<Value> {
    private:
        int d_value;

    public:
        explicit Value(int value): d_value(value) {}
        bool equalTo(Value const& other) const {
            return this->d_value == other.d_value;
        }
        int value() const { return this->d_value; }
    };
    
    bsl::ostream& operator<< (bsl::ostream& out, Value const& value) {
        return out << value.value();
    }
}

// ----------------------------------------------------------------------------

TEST_CASE("breathing test", "[batgen::EqualTo]") {
    Value v1(1), v2(2);

    REQUIRE(v1 == v1);
    REQUIRE(v1 != v2);
}

// ----------------------------------------------------------------------------

TEST_CASE("no size contribution", "[batgen::EqualTo]") {
    REQUIRE(sizeof(Value) == sizeof(int));
}
