//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBEQU_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBEQU_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void pbequ( char const uplo, integer_t const n, integer_t const kd,
            float* ab, integer_t const ldab, float* s, float& scond,
            float& amax, integer_t& info ) {
        LAPACK_SPBEQU( &uplo, &n, &kd, ab, &ldab, s, &scond, &amax, &info );
    }
    inline void pbequ( char const uplo, integer_t const n, integer_t const kd,
            double* ab, integer_t const ldab, double* s, double& scond,
            double& amax, integer_t& info ) {
        LAPACK_DPBEQU( &uplo, &n, &kd, ab, &ldab, s, &scond, &amax, &info );
    }
    inline void pbequ( char const uplo, integer_t const n, integer_t const kd,
            traits::complex_f* ab, integer_t const ldab, float* s,
            float& scond, float& amax, integer_t& info ) {
        LAPACK_CPBEQU( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, s,
                &scond, &amax, &info );
    }
    inline void pbequ( char const uplo, integer_t const n, integer_t const kd,
            traits::complex_d* ab, integer_t const ldab, double* s,
            double& scond, double& amax, integer_t& info ) {
        LAPACK_ZPBEQU( &uplo, &n, &kd, traits::complex_ptr(ab), &ldab, s,
                &scond, &amax, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct pbequ_impl{};

// real specialization
template< typename ValueType >
struct pbequ_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAB, typename VectorS >
    static void compute( integer_t const n, integer_t const kd, MatrixAB& ab,
            VectorS& s, real_type& scond, real_type& amax, integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixAB >::value_type, typename traits::vector_traits<
                VectorS >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd+1 );
        detail::pbequ( traits::matrix_uplo_tag(a), n, kd,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::vector_storage(s), scond, amax, info );
    }
};

// complex specialization
template< typename ValueType >
struct pbequ_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixAB, typename VectorS >
    static void compute( integer_t const n, integer_t const kd, MatrixAB& ab,
            VectorS& s, real_type& scond, real_type& amax, integer_t& info ) {
        BOOST_ASSERT( traits::matrix_uplo_tag(a) == 'U' ||
                traits::matrix_uplo_tag(a) == 'L' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( traits::leading_dimension(ab) >= kd+1 );
        detail::pbequ( traits::matrix_uplo_tag(a), n, kd,
                traits::matrix_storage(ab), traits::leading_dimension(ab),
                traits::vector_storage(s), scond, amax, info );
    }
};


// template function to call pbequ
template< typename MatrixAB, typename VectorS >
inline integer_t pbequ( integer_t const n, integer_t const kd,
        MatrixAB& ab, VectorS& s, typename traits::matrix_traits<
        MatrixAB >::value_type& scond, typename traits::matrix_traits<
        MatrixAB >::value_type& amax ) {
    typedef typename traits::matrix_traits< MatrixAB >::value_type value_type;
    integer_t info(0);
    pbequ_impl< value_type >::compute( n, kd, ab, s, scond, amax, info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
