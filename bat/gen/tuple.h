// bat/gen/tuple.h                                                    -*-C++-*-
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

#ifndef INCLUDED_BAT_GEN_TUPLE
#define INCLUDED_BAT_GEN_TUPLE

#include <bslmf_issame.h>

// ----------------------------------------------------------------------------

namespace BloombergLP {
    namespace batgen {
        template <typename Type, typename Struct, Type Struct::*Member>
        struct tuple_member {
            typedef Type  type;
            static type&       get(Struct& s)       { return s.*Member; }
            static type const& get(Struct const& s) { return s.*Member; }
        };
        template <typename Type, typename Struct, Type Struct::*Member>
        struct tuple_const_member {
            typedef Type const type;
            static type const& get(Struct const& s) { return s.*Member; }
        };
        template <typename T0 = void, typename T1 = void,
                  typename T2 = void, typename T3 = void,
                  typename T4 = void, typename T5 = void,
                  typename T6 = void, typename T7 = void>
        struct tuple_members {
            enum { size = 0
                   + !bsl::is_same<void, T0>::value
                   + !bsl::is_same<void, T1>::value
                   + !bsl::is_same<void, T2>::value
                   + !bsl::is_same<void, T3>::value
                   + !bsl::is_same<void, T4>::value
                   + !bsl::is_same<void, T5>::value
                   + !bsl::is_same<void, T6>::value
                   + !bsl::is_same<void, T7>::value
            };
        };
        template <int Index, typename Members> struct tuple_element;
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<0, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T0 type;
        };
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<1, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T1 type;
        };
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<2, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T2 type;
        };
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<3, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T3 type;
        };
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<4, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T4 type;
        };
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<5, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T5 type;
        };
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<6, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T6 type;
        };
        template <typename T0, typename T1, typename T2, typename T3,
                  typename T4, typename T5, typename T6, typename T7>
        struct tuple_element<7, tuple_members<T0, T1, T2, T3, T4, T5, T6, T7> > {
            typedef T7 type;
        };

        template <typename T>
        struct tuple_size {
            enum Size { value = T::tuple::size };
        };

        template <int Index, typename Type>
        typename tuple_element<Index, typename Type::tuple>::type::type&
        get(Type& value) {
            return tuple_element<Index, typename Type::tuple>::type::get(value);
        }
        template <int Index, typename Type>
        typename tuple_element<Index, typename Type::tuple>::type::type const&
        get(Type const& value) {
            return tuple_element<Index, typename Type::tuple>::type::get(value);
        }
    }
}

// ----------------------------------------------------------------------------

#endif
