//
// Copyright (c) 2002--2010
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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_POTRS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_POTRS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for potrs is selected by defining a pre-processor
// variable, which can be one of
// * for ATLAS's CLAPACK, define BOOST_NUMERIC_BINDINGS_LAPACK_CLAPACK
// * netlib-compatible LAPACK is the default
//
#if defined BOOST_NUMERIC_BINDINGS_LAPACK_CLAPACK
#include <boost/numeric/bindings/lapack/detail/clapack.h>
#include <boost/numeric/bindings/lapack/detail/clapack_option.hpp>
#else
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#endif

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

#if defined BOOST_NUMERIC_BINDINGS_LAPACK_CLAPACK
//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * float value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const int n, const int nrhs,
        const float* a, const int lda, float* b, const int ldb ) {
    return clapack_spotrs( clapack_option< Order >::value, clapack_option<
            UpLo >::value, n, nrhs, a, lda, b, ldb );
}

//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * double value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const int n, const int nrhs,
        const double* a, const int lda, double* b, const int ldb ) {
    return clapack_dpotrs( clapack_option< Order >::value, clapack_option<
            UpLo >::value, n, nrhs, a, lda, b, ldb );
}

//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const int n, const int nrhs,
        const std::complex<float>* a, const int lda, std::complex<float>* b,
        const int ldb ) {
    return clapack_cpotrs( clapack_option< Order >::value, clapack_option<
            UpLo >::value, n, nrhs, a, lda, b, ldb );
}

//
// Overloaded function for dispatching to
// * ATLAS's CLAPACK backend, and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const int n, const int nrhs,
        const std::complex<double>* a, const int lda, std::complex<double>* b,
        const int ldb ) {
    return clapack_zpotrs( clapack_option< Order >::value, clapack_option<
            UpLo >::value, n, nrhs, a, lda, b, ldb );
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const float* a, const fortran_int_t lda,
        float* b, const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_SPOTRS( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, b, &ldb,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const double* a, const fortran_int_t lda,
        double* b, const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_DPOTRS( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, b, &ldb,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<float>* a,
        const fortran_int_t lda, std::complex<float>* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_CPOTRS( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, b, &ldb,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename UpLo >
inline std::ptrdiff_t potrs( Order, UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, const std::complex<double>* a,
        const fortran_int_t lda, std::complex<double>* b,
        const fortran_int_t ldb ) {
    BOOST_STATIC_ASSERT( (is_same<Order, tag::column_major>::value) );
    fortran_int_t info(0);
    LAPACK_ZPOTRS( &lapack_option< UpLo >::value, &n, &nrhs, a, &lda, b, &ldb,
            &info );
    return info;
}

#endif
} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to potrs.
//
template< typename Value >
struct potrs_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename MatrixB >
    static std::ptrdiff_t invoke( const MatrixA& a, MatrixB& b ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixB >::value) );
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_column(b) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(b) == 1 ||
                bindings::stride_minor(b) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        BOOST_ASSERT( bindings::stride_major(b) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        return detail::potrs( order(), uplo(), bindings::size_column(a),
                bindings::size_column(b), bindings::begin_value(a),
                bindings::stride_major(a), bindings::begin_value(b),
                bindings::stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the potrs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for potrs. Its overload differs for
// * MatrixB&
//
template< typename MatrixA, typename MatrixB >
inline std::ptrdiff_t potrs( const MatrixA& a, MatrixB& b ) {
    return potrs_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, b );
}

//
// Overloaded function for potrs. Its overload differs for
// * const MatrixB&
//
template< typename MatrixA, typename MatrixB >
inline std::ptrdiff_t potrs( const MatrixA& a, const MatrixB& b ) {
    return potrs_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
