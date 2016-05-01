// bat/gen/totalorder.ut.cpp                                          -*-C++-*-
// ----------------------------------------------------------------------------
//  Copyright (C) 2016 Dietmar Kuehl http://www.dietmar-kuehl.de         
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

#include "bat/gen/totalorder.h"
#include <bsl_ostream.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace BloombergLP;

// ----------------------------------------------------------------------------

namespace {
    class Value
        : private batgen::TotalOrdered<Value> {
    private:
        int d_value;
    public:
        explicit Value(int value): d_value(value) {}
        int value() const { return this->d_value; }

        friend batgen::TotalOrderingType
        totalOrder(Value const& v1, Value const& v2) {
            return v1.d_value == v2.d_value
                ? batgen::TotalOrdering::equal
                : (v1.d_value < v2.d_value
                   ? batgen::TotalOrdering::less
                   : batgen::TotalOrdering::greater);
        }
    };
    
    bsl::ostream& operator<< (bsl::ostream& out, Value const& value) {
        return out << value.value();
    }
}

// ----------------------------------------------------------------------------

TEST_CASE("TotalOrdering test", "[batgen::TotalOrdering]") {
    batgen::TotalOrderingType l = batgen::TotalOrdering::less;
    batgen::TotalOrderingType e = batgen::TotalOrdering::equal;
    batgen::TotalOrderingType g = batgen::TotalOrdering::greater;

    REQUIRE(l != e);
    REQUIRE(l != g);
    REQUIRE(e != g);
}

// ----------------------------------------------------------------------------

TEST_CASE("TotalOrdered test", "[batgen::TotalOrdered]") {
    Value v1(1), v2(2);

    REQUIRE(batgen::TotalOrdering::less    == totalOrder(v1, v2));
    REQUIRE(batgen::TotalOrdering::equal   == totalOrder(v1, v1));
    REQUIRE(batgen::TotalOrdering::greater == totalOrder(v2, v1));

    REQUIRE(v1 <  v2);
    REQUIRE(v1 <= v2); REQUIRE(v1 <= v1);
    REQUIRE(v2 >  v1);
    REQUIRE(v2 >= v1); REQUIRE(v2 >= v2);
    REQUIRE(v1 == v1);
    REQUIRE(v1 != v2);
}

// ----------------------------------------------------------------------------

TEST_CASE("TotalOrderEqualTo test", "[batgen::TotalOrderEqualTo]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderEqualTo(v1, v2));
    REQUIRE(true  == batgen::totalOrderEqualTo(v1, v3));
}

TEST_CASE("TotalOrderNotEqualTo test", "[batgen::TotalOrderNotEqualTo]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderNotEqualTo(v1, v3));
    REQUIRE(true  == batgen::totalOrderNotEqualTo(v1, v2));
}

TEST_CASE("TotalOrderGreater test", "[batgen::TotalOrderGreater]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderGreater(v1, v3));
    REQUIRE(false == batgen::totalOrderGreater(v1, v2));
    REQUIRE(true  == batgen::totalOrderGreater(v2, v1));
}

TEST_CASE("TotalOrderLess test", "[batgen::TotalOrderLess]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderLess(v1, v3));
    REQUIRE(false == batgen::totalOrderLess(v2, v1));
    REQUIRE(true  == batgen::totalOrderLess(v1, v2));
}

TEST_CASE("TotalOrderGreaterEqual test", "[batgen::TotalOrderGreaterEqual]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderGreaterEqual(v1, v2));
    REQUIRE(true  == batgen::totalOrderGreaterEqual(v2, v1));
    REQUIRE(true  == batgen::totalOrderGreaterEqual(v1, v3));
}

TEST_CASE("TotalOrderLessEqual test", "[batgen::TotalOrderLessEqual]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderLessEqual(v2, v1));
    REQUIRE(true  == batgen::totalOrderLessEqual(v1, v2));
    REQUIRE(true  == batgen::totalOrderLessEqual(v1, v3));
}
