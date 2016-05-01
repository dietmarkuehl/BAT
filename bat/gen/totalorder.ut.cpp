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

TEST_CASE("TotalOrdering test", "[batgen::TotalOrder]") {
    batgen::TotalOrderingType l = batgen::TotalOrdering::less;
    batgen::TotalOrderingType e = batgen::TotalOrdering::equal;
    batgen::TotalOrderingType g = batgen::TotalOrdering::greater;

    REQUIRE(l != e);
    REQUIRE(l != g);
    REQUIRE(e != g);
}

// ----------------------------------------------------------------------------

TEST_CASE("TotalOrdered test", "[batgen::TotalOrder]") {
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

TEST_CASE("TotalOrderEqualTo test", "[batgen::TotalOrder]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderEqualTo(v1, v2));
    REQUIRE(true  == batgen::totalOrderEqualTo(v1, v3));
}

TEST_CASE("TotalOrderNotEqualTo test", "[batgen::TotalOrder]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderNotEqualTo(v1, v3));
    REQUIRE(true  == batgen::totalOrderNotEqualTo(v1, v2));
}

TEST_CASE("TotalOrderGreater test", "[batgen::TotalOrder]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderGreater(v1, v3));
    REQUIRE(false == batgen::totalOrderGreater(v1, v2));
    REQUIRE(true  == batgen::totalOrderGreater(v2, v1));
}

TEST_CASE("TotalOrderLess test", "[batgen::TotalOrder]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderLess(v1, v3));
    REQUIRE(false == batgen::totalOrderLess(v2, v1));
    REQUIRE(true  == batgen::totalOrderLess(v1, v2));
}

TEST_CASE("TotalOrderGreaterEqual test", "[batgen::TotalOrder]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderGreaterEqual(v1, v2));
    REQUIRE(true  == batgen::totalOrderGreaterEqual(v2, v1));
    REQUIRE(true  == batgen::totalOrderGreaterEqual(v1, v3));
}

TEST_CASE("TotalOrderLessEqual test", "[batgen::TotalOrder]") {
    Value v1(1), v2(2), v3(1);

    REQUIRE(false == batgen::totalOrderLessEqual(v2, v1));
    REQUIRE(true  == batgen::totalOrderLessEqual(v1, v2));
    REQUIRE(true  == batgen::totalOrderLessEqual(v1, v3));
}

// ----------------------------------------------------------------------------

template <typename T>
static bool testTotalOrder(T v1, T v2) {
    using batgen::totalOrder;
    return totalOrder(v1, v2) == batgen::TotalOrdering::less
        && totalOrder(v1, v1) == batgen::TotalOrdering::equal
        && totalOrder(v2, v1) == batgen::TotalOrdering::greater
        ;
}

namespace {
    enum Enum { enum1, enum2 };
}

TEST_CASE("totalOrder() for built-in types", "[batgen::TotalOrder]") {
    REQUIRE(testTotalOrder<Value>(Value(1), Value(2)));

    REQUIRE(testTotalOrder<wchar_t>(1, 2));
    REQUIRE(testTotalOrder<char>(1, 2));
    REQUIRE(testTotalOrder<signed char>(1, 2));
    REQUIRE(testTotalOrder<unsigned char>(1, 2));
    REQUIRE(testTotalOrder<signed short>(1, 2));
    REQUIRE(testTotalOrder<unsigned short>(1, 2));
    REQUIRE(testTotalOrder<signed int>(1, 2));
    REQUIRE(testTotalOrder<unsigned int>(1, 2));
    REQUIRE(testTotalOrder<signed long>(1, 2));
    REQUIRE(testTotalOrder<unsigned long>(1, 2));
#if 201103L <= __cplusplus
    REQUIRE(testTotalOrder<char16_t>(1, 2));
    REQUIRE(testTotalOrder<char32_t>(1, 2));
    REQUIRE(testTotalOrder<signed long long>(1, 2));
    REQUIRE(testTotalOrder<unsigned long long>(1, 2));
#endif

    REQUIRE(testTotalOrder<Enum>(enum1, enum2));
}
