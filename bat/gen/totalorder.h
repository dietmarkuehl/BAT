// bat/gen/totalorder.h                                               -*-C++-*-
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

#ifndef INCLUDED_BAT_GEN_TOTALORDER
#define INCLUDED_BAT_GEN_TOTALORDER

#include <bslmf_enableif.h>
#include <bslmf_isenum.h>
#include <bslmf_isintegral.h>

// ----------------------------------------------------------------------------

namespace BloombergLP {
    namespace batgen {
#if __cplusplus < 201103L
        struct TotalOrdering {
            enum type { less, equal, greater };
        };
        typedef TotalOrdering::type TotalOrderingType;
#else
        enum class TotalOrdering { less, equal, greater };
        using TotalOrderingType = TotalOrdering;
#endif

        template <typename Type> struct TotalOrdered;

        extern struct TotalOrderEqualTo      const totalOrderEqualTo;
        extern struct TotalOrderNotEqualTo   const totalOrderNotEqualTo;
        extern struct TotalOrderGreater      const totalOrderGreater;
        extern struct TotalOrderLess         const totalOrderLess;
        extern struct TotalOrderGreaterEqual const totalOrderGreaterEqual;
        extern struct TotalOrderLessEqual    const totalOrderLessEqual;

        template <typename Type>
        typename bsl::enable_if<
            bsl::is_integral<Type>::value || bsl::is_enum<Type>::value
            , TotalOrderingType>::type 
        totalOrder(Type v0, Type v1) {
            return v0 == v1
                ? TotalOrdering::equal
                : (v0 < v1
                   ? TotalOrdering::less
                   : TotalOrdering::greater)
                ;
        }
    }
}

// ----------------------------------------------------------------------------

template <typename Type>
struct BloombergLP::batgen::TotalOrdered {
    friend bool
    operator== (Type const& value0, Type const& value1) {
        return totalOrder(value0, value1) == TotalOrdering::equal;
    }
    friend bool
    operator!= (Type const& value0, Type const& value1) {
        return !(value0 == value1);
    }
    friend bool
    operator<  (Type const& value0, Type const& value1) {
        return totalOrder(value0, value1) == TotalOrdering::less;
    }
    friend bool
    operator>  (Type const& value0, Type const& value1) {
        return totalOrder(value0, value1) == TotalOrdering::greater;
    }
    friend bool
    operator<= (Type const& value0, Type const& value1) {
        return totalOrder(value0, value1) != TotalOrdering::greater;
    }
    friend bool
    operator>= (Type const& value0, Type const& value1) {
        return totalOrder(value0, value1) != TotalOrdering::less;
    }
};

// ----------------------------------------------------------------------------

struct BloombergLP::batgen::TotalOrderEqualTo {
    template <typename Type>
    inline bool operator()(Type const& value0, Type const& value1) const {
        return totalOrder(value0, value1) == TotalOrdering::equal;
    }
};

struct BloombergLP::batgen::TotalOrderNotEqualTo {
    template <typename Type>
    inline bool operator()(Type const& value0, Type const& value1) const {
        return totalOrder(value0, value1) != TotalOrdering::equal;
    }
};

struct BloombergLP::batgen::TotalOrderGreater {
    template <typename Type>
    inline bool operator()(Type const& value0, Type const& value1) const {
        return totalOrder(value0, value1) == TotalOrdering::greater;
    }
};

struct BloombergLP::batgen::TotalOrderLess {
    template <typename Type>
    inline bool operator()(Type const& value0, Type const& value1) const {
        return totalOrder(value0, value1) == TotalOrdering::less;
    }
};

struct BloombergLP::batgen::TotalOrderGreaterEqual {
    template <typename Type>
    inline bool operator()(Type const& value0, Type const& value1) const {
        return totalOrder(value0, value1) != TotalOrdering::less;
    }
};

struct BloombergLP::batgen::TotalOrderLessEqual {
    template <typename Type>
    inline bool operator()(Type const& value0, Type const& value1) const {
        return totalOrder(value0, value1) != TotalOrdering::greater;
    }
};

// ----------------------------------------------------------------------------

#endif
