// bat/ma/allocator.h                                                  -*-C++-*-
// ----------------------------------------------------------------------------

#ifndef INCLUDED_BATMA_ALLOCATOR
#define INCLUDED_BATMA_ALLOCATOR

#include <bslma_allocator.h>
#include <bslma_default.h>
#include <bslmf_movableref.h>
#include <bsl_cstddef.h>

// ----------------------------------------------------------------------------

namespace BloombergLP {
    namespace batma {
        class Allocator;
    }
}

// Allocate `size` bytes of memory using the specified `allocator`.
void* operator new(bsl::size_t size, BloombergLP::batma::Allocator& allocator);
// Release the memory pointed to by `pointer` using the specified `allocator`.
void  operator delete(void* pointer, BloombergLP::batma::Allocator& allocator);

// ----------------------------------------------------------------------------
// The class `batma::Allocator` provides a thin wrapper around
// `bslma::Allocator` intended to be used as class member holding the allocator
// pointer. It main objectives are preventing some default generated functions
// which wouldn't work with classes handling allocators and to obtain the
// default allocator when the allocator the object is constructed with is null.
//
// Note that `batma::Allocator` objects are immutable! The only data member is
// a pointer to an allocator which is declared to be `const`. The entire
// functionality of this class consists of an easy way to get hold of the
// default allocator, provision of an assignment operator which does nothing,
// a number of access functions to the stored allocator.
//
// Most functions are provided to have `batma::Allocator` be a simple
// replacement for storing a `bslma::Allocator*`.

class BloombergLP::batma::Allocator
{
    bslma::Allocator *const d_allocator;

    // The assignment operator is made inaccessible to enforce implementation
    // of a suitable assignment operator.
    Allocator& operator= (Allocator const&); // = delete
public:
    // The default constructor initializes the `Allocator` object with the
    // currently installed default allocator using
    // `bslma::Default::defaultAllocator()`. The main difference to the
    // constructor taking a `bslma::Allocator*` is that default constructor
    // doesn't need to check the argument.
    Allocator();
    // Initialize the object with the passed `allocator` or with the default
    // allocator if null is passed.
    explicit Allocator(bslma::Allocator *allocator);
    // The copy constructor just copies the argument. Since `batma::Allocator`
    // may be used as value parameter to constructors, it can't be made
    // inaccessible.
    Allocator(Allocator const&);
    // The move constructor does propagate the stored allocator.
    Allocator(bslmf::MovableRef<Allocator> other);

    // The dereference operator returns a reference to the stored allocator.
    bslma::Allocator& operator*() const;

    // The member access operator returns the stored allocator which is
    // guaranteed to be non-null.
    bslma::Allocator *operator->() const;

    // The function `get()` returns the stored allocator which is guaranteed
    // to be non-null.
    bslma::Allocator *get() const;

    // The conversion operator returns the stored allocator which is guaranteed
    // to be non-null.
    operator bslma::Allocator *() const;

    // Provide access to the allocator using a function call operator. The
    // function call operator enables the use of `batma::Allocator` as a
    // public member to provide access to the stored allocator without the
    // need to explicitly create a forwarding function.
    bslma::Allocator* operator()() const;
};

// ----------------------------------------------------------------------------

inline
BloombergLP::batma::Allocator::Allocator()
    : d_allocator(bslma::Default::defaultAllocator()) {
}

inline
BloombergLP::batma::Allocator::Allocator(bslma::Allocator *allocator)
    : d_allocator(bslma::Default::allocator(allocator)) {
}

inline
BloombergLP::batma::Allocator::Allocator(batma::Allocator const& other)
    : d_allocator(other.d_allocator) {
}

inline
BloombergLP::batma::Allocator::Allocator(bslmf::MovableRef<batma::Allocator> other)
    : d_allocator(bslmf::MovableRefUtil::access(other).d_allocator) {
}

BloombergLP::bslma::Allocator&
BloombergLP::batma::Allocator::operator*() const {
    return *this->d_allocator;
}

inline
BloombergLP::bslma::Allocator*
BloombergLP::batma::Allocator::operator->() const {
    return this->d_allocator;
}

inline
BloombergLP::bslma::Allocator*
BloombergLP::batma::Allocator::get() const {
    return this->d_allocator;
}

inline
BloombergLP::batma::Allocator::operator BloombergLP::bslma::Allocator*() const{
    return this->d_allocator;
}

inline
BloombergLP::bslma::Allocator*
BloombergLP::batma::Allocator::operator()() const {
    return this->d_allocator;
}

// ----------------------------------------------------------------------------

inline
void* operator new(bsl::size_t size, BloombergLP::batma::Allocator& allocator)
{
    return allocator->allocate(size);
}

inline
void  operator delete(void* pointer, BloombergLP::batma::Allocator& allocator)
{
    return allocator->deallocate(pointer);
}

// ----------------------------------------------------------------------------

#endif
