// bat/ma/allocator.t.cpp                                             -*-C++-*-
// ----------------------------------------------------------------------------

#include "bat/ma/allocator.h"
#include <bslma_testallocator.h>
#include <bsl_stdexcept.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace BloombergLP;

// ----------------------------------------------------------------------------

TEST_CASE("breathing test", "[batma::Allocator]") {
    bslma::TestAllocator testAllocator;
    batma::Allocator allocator0;
    batma::Allocator allocator1(allocator0);
    batma::Allocator allocator2(&testAllocator);
    batma::Allocator allocator3(bslmf::MovableRefUtil::move(allocator1));

    REQUIRE(allocator0.get());
    REQUIRE(static_cast<bslma::Allocator*>(allocator0) != 0);
    int* ip = new(allocator0) int(17);
    allocator0->deallocate(ip);
}

// ----------------------------------------------------------------------------

TEST_CASE("the default ctor stores the default allocator",
          "[batma::Allocator]") {
    batma::Allocator  allocator;
    bslma::Allocator *defAllocator = bslma::Default::allocator();

    REQUIRE(allocator.get() == defAllocator);
    REQUIRE(allocator.operator->() == defAllocator);
    REQUIRE(&*allocator == defAllocator);
    REQUIRE(static_cast<bslma::Allocator*>(allocator) == defAllocator);
}

// ----------------------------------------------------------------------------

TEST_CASE("the ctor using null stores the default allocator",
          "[batma::Allocator]") {
    batma::Allocator  allocator(static_cast<bslma::Allocator*>(0));
    bslma::Allocator *defAllocator = bslma::Default::allocator();

    REQUIRE(allocator.get() == defAllocator);
    REQUIRE(allocator.operator->() == defAllocator);
    REQUIRE(&*allocator == defAllocator);
    REQUIRE(static_cast<bslma::Allocator*>(allocator) == defAllocator);
}

// ----------------------------------------------------------------------------

TEST_CASE("the ctor using an allocator stores the specified allocator",
          "[batma::Allocator]") {
    bslma::TestAllocator testAllocator;
    batma::Allocator     allocator(&testAllocator);

    REQUIRE(allocator.get() == &testAllocator);
    REQUIRE(allocator.operator->() == &testAllocator);
    REQUIRE(&*allocator == &testAllocator);
    REQUIRE(static_cast<bslma::Allocator*>(allocator) == &testAllocator);
}

// ----------------------------------------------------------------------------

TEST_CASE("the move ctor stores the stored allocator of the argument",
          "[batma::Allocator]") {
    bslma::TestAllocator  testAllocator;
    batma::Allocator      allocator0(&testAllocator);
    batma::Allocator      allocator1(bslmf::MovableRefUtil::move(allocator0));
    bslma::Allocator     *defAllocator = bslma::Default::allocator();

    REQUIRE(allocator0.get() == &testAllocator);
    REQUIRE(allocator1.get() == &testAllocator);
}

// ----------------------------------------------------------------------------

TEST_CASE("the operator new() uses the stored allocator",
          "[batma::Allocator]") {
    bslma::TestAllocator testAllocator;
    batma::Allocator     allocator(&testAllocator);

    REQUIRE(0 == testAllocator.numBytesInUse());
    int* pointer = new(allocator) int(17);
    REQUIRE(int(sizeof(int)) <= testAllocator.numBytesInUse());
    allocator->deallocate(pointer);
    REQUIRE(0 == testAllocator.numBytesInUse());
}

// ----------------------------------------------------------------------------

namespace {
    struct ThrowingCtor {
        int dummy;
        ThrowingCtor() { throw bsl::runtime_error("bail out"); }
    };
}

TEST_CASE("the operator delete() release memory with the stored allocator",
          "[batma::Allocator]") {
    bslma::TestAllocator testAllocator;
    batma::Allocator     allocator(&testAllocator);

    REQUIRE(0 == testAllocator.numBytesInUse());
    REQUIRE(0 == testAllocator.numBytesTotal());
    try {  new(allocator) ThrowingCtor(); }
    catch (bsl::runtime_error const&) { /* eating the expected exception */ }
    REQUIRE(0 == testAllocator.numBytesInUse());
    REQUIRE(int(sizeof(ThrowingCtor)) <= testAllocator.numBytesTotal());
}
