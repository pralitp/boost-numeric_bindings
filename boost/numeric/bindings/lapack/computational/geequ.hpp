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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEEQU_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_GEEQU_HPP

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
    inline void geequ( integer_t const m, integer_t const n, float* a,
            integer_t const lda, float* r, float* c, float& rowcnd,
            float& colcnd, float& amax, integer_t& info ) {
        LAPACK_SGEEQU( &m, &n, a, &lda, r, c, &rowcnd, &colcnd, &amax, &info );
    }
    inline void geequ( integer_t const m, integer_t const n, double* a,
            integer_t const lda, double* r, double* c, double& rowcnd,
            double& colcnd, double& amax, integer_t& info ) {
        LAPACK_DGEEQU( &m, &n, a, &lda, r, c, &rowcnd, &colcnd, &amax, &info );
    }
    inline void geequ( integer_t const m, integer_t const n,
            traits::complex_f* a, integer_t const lda, float* r, float* c,
            float& rowcnd, float& colcnd, float& amax, integer_t& info ) {
        LAPACK_CGEEQU( &m, &n, traits::complex_ptr(a), &lda, r, c, &rowcnd,
                &colcnd, &amax, &info );
    }
    inline void geequ( integer_t const m, integer_t const n,
            traits::complex_d* a, integer_t const lda, double* r, double* c,
            double& rowcnd, double& colcnd, double& amax, integer_t& info ) {
        LAPACK_ZGEEQU( &m, &n, traits::complex_ptr(a), &lda, r, c, &rowcnd,
                &colcnd, &amax, &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct geequ_impl{};

// real specialization
template< typename ValueType >
struct geequ_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorR, typename VectorC >
    static void compute( MatrixA& a, VectorR& r, VectorC& c,
            real_type& rowcnd, real_type& colcnd, real_type& amax,
            integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorR >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::matrix_traits<
                MatrixA >::value_type, typename traits::vector_traits<
                VectorC >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        detail::geequ( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(r),
                traits::vector_storage(c), rowcnd, colcnd, amax, info );
    }
};

// complex specialization
template< typename ValueType >
struct geequ_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // templated specialization
    template< typename MatrixA, typename VectorR, typename VectorC >
    static void compute( MatrixA& a, VectorR& r, VectorC& c,
            real_type& rowcnd, real_type& colcnd, real_type& amax,
            integer_t& info ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorR >::value_type, typename traits::vector_traits<
                VectorC >::value_type >::value) );
        BOOST_ASSERT( traits::matrix_num_rows(a) >= 0 );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_rows(a)) );
        detail::geequ( traits::matrix_num_rows(a),
                traits::matrix_num_columns(a), traits::matrix_storage(a),
                traits::leading_dimension(a), traits::vector_storage(r),
                traits::vector_storage(c), rowcnd, colcnd, amax, info );
    }
};


// template function to call geequ
template< typename MatrixA, typename VectorR, typename VectorC >
inline integer_t geequ( MatrixA& a, VectorR& r, VectorC& c,
        typename traits::matrix_traits< MatrixA >::value_type& rowcnd,
        typename traits::matrix_traits< MatrixA >::value_type& colcnd,
        typename traits::matrix_traits< MatrixA >::value_type& amax ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    geequ_impl< value_type >::compute( a, r, c, rowcnd, colcnd, amax,
            info );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
