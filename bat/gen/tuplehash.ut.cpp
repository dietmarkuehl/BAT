// bat/gen/tuplehash.ut.cpp                                           -*-C++-*-
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

#include "bat/gen/tuplehash.h"
#include "bat/gen/tupleoutput.h"
#include "bat/gen/tuple.h"
#include <bslh_hash.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace BloombergLP;

// ----------------------------------------------------------------------------

namespace {
    class Value
        : private batgen::TupleHash<Value>
        , private batgen::TupleOutput<Value>
    {
        bool bv;
        int  iv;
        char cv;
    public:
        typedef batgen::TupleMembers<
            batgen::TupleConstMember<bool, Value, &Value::bv>,
            batgen::TupleConstMember<int,  Value, &Value::iv>,
            batgen::TupleConstMember<char, Value, &Value::cv>
        > tuple;

        Value(bool bv, int iv, char cv) : bv(bv), iv(iv), cv(cv) {}
    };

    struct Sizer {
        bool bv;
        int  iv;
        char cv;
    };
}

// ----------------------------------------------------------------------------

TEST_CASE("breathing test", "[batgen::TupleHash]") {
    Value value(true,  17, 'a');

    REQUIRE(bslh::Hash<>()(value) == bslh::Hash<>()(value));
}

TEST_CASE("no size impact", "[batgen::TupleHash]") {
    REQUIRE(sizeof(Value) == sizeof(Sizer));
}

TEST_CASE("difference in first member", "[batgen::TupleHash]") {
    Value value0(true,  17, 'a');
    Value value1(false, 17, 'a');

    REQUIRE(bslh::Hash<>()(value0) != bslh::Hash<>()(value1));
}

TEST_CASE("difference in second member", "[batgen::TupleHash]") {
    Value value0(true, 17, 'a');
    Value value1(true, 18, 'a');

    REQUIRE(bslh::Hash<>()(value0) != bslh::Hash<>()(value1));
}

TEST_CASE("difference in third member", "[batgen::TupleHash]") {
    Value value0(true, 17, 'a');
    Value value1(true, 17, 'b');

    REQUIRE(bslh::Hash<>()(value0) != bslh::Hash<>()(value1));
}

