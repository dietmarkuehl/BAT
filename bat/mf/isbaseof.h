// bat/mf/isbaseof.h                                                  -*-C++-*-
// ----------------------------------------------------------------------------

#ifndef INCLUDED_BAT_MF_ISBASEOF
#define INCLUDED_BAT_MF_ISBASEOF

#include <bslmf_integralconstant.h>

// ----------------------------------------------------------------------------

namespace BloombergLP {
namespace batmf {
namespace detail {
    template <typename, typename> struct IsBaseOf;
}

template <typename, typename> class IsBaseOf;

}
}

// ----------------------------------------------------------------------------

template <typename Base, typename Derived>
struct BloombergLP::batmf::detail::IsBaseOf {
    operator Base*() const;
    operator Derived*();

    template <typename Aux>
    static char (&test(Derived*, Aux))[1];
    static char (&test(Base*, int))[2];
};

// ----------------------------------------------------------------------------

template <typename Base, typename Derived>
class BloombergLP::batmf::IsBaseOf
    : public bsl::integral_constant<bool,
       1u == sizeof(detail::IsBaseOf<Base, Derived>::test(detail::IsBaseOf<Base, Derived>(), int()))>
{
};

// ----------------------------------------------------------------------------

#endif
