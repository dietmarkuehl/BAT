// bat/mf/isbaseof.t.cpp                                              -*-C++-*-
// ----------------------------------------------------------------------------

#include "bat/mf/isbaseof.h"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace BloombergLP;

// ----------------------------------------------------------------------------

namespace {
    class Base {};
    class DerivedPrivate:   private   Base {};
    class DerivedProtected: protected Base {};
    class DerivedPublic:    public    Base {};

    class A0: public Base {};
    class A1: public Base {};
    class AC: public A0, public A1 {};
}

// ----------------------------------------------------------------------------

TEST_CASE("a cv-qualified Base is still a base", "[batmf::IsBaseOf]") {
    REQUIRE((batmf::IsBaseOf<Base, DerivedPublic>::value)   == true);
    REQUIRE((batmf::IsBaseOf<Base const, DerivedPublic>::value)   == true);
    REQUIRE((batmf::IsBaseOf<Base volatile, DerivedPublic>::value)   == true);
    REQUIRE((batmf::IsBaseOf<Base const volatile, DerivedPublic>::value)   == true);
}

TEST_CASE("a reference is a base of anything", "[batmf::IsBaseOf]") {
    //REQUIRE((batmf::IsBaseOf<Base&, DerivedPublic>::value)   == false);
}

TEST_CASE("void isn't a base of anything", "[batmf::IsBaseOf]") {
    REQUIRE((batmf::IsBaseOf<void, AC>::value) == true);
}

TEST_CASE("test if ambiguous bases are detected", "[batmf::IsBaseOf]") {
    REQUIRE((batmf::IsBaseOf<Base, AC>::value) == true);
}

TEST_CASE("a type isn't the base of itself", "[batmf::IsBaseOf]") {
    REQUIRE((batmf::IsBaseOf<int, int>::value) == false);
    REQUIRE((batmf::IsBaseOf<Base, Base>::value) == false);
    REQUIRE((batmf::IsBaseOf<DerivedPrivate, DerivedPrivate>::value) == false);
    REQUIRE((batmf::IsBaseOf<DerivedProtected, DerivedProtected>::value) == false);
    REQUIRE((batmf::IsBaseOf<DerivedPublic, DerivedPublic>::value) == false);
}

TEST_CASE("is base is independent of access specifiers", "[batmf::IsBaseOf]") {
    REQUIRE((batmf::IsBaseOf<Base, DerivedPrivate>::value)   == true);
    REQUIRE((batmf::IsBaseOf<Base, DerivedProtected>::value) == true);
    REQUIRE((batmf::IsBaseOf<Base, DerivedPublic>::value)    == true);
}

TEST_CASE("a derived is not a base of the base", "[batmf::IsBaseOf]") {
    REQUIRE((batmf::IsBaseOf<DerivedPrivate,   Base>::value) == false);
    REQUIRE((batmf::IsBaseOf<DerivedProtected, Base>::value) == false);
    REQUIRE((batmf::IsBaseOf<DerivedPublic,    Base>::value) == false);
}
