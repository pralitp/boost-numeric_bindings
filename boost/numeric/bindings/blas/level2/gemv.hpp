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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GEMV_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL2_GEMV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/blas/detail/default_order.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The BLAS-backend is selected by defining a pre-processor variable,
//  which can be one of
// * for CBLAS, define BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
// * for CUBLAS, define BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
// * netlib-compatible BLAS is the default
//
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
#include <boost/numeric/bindings/blas/detail/cblas.h>
#include <boost/numeric/bindings/blas/detail/cblas_option.hpp>
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
#include <boost/numeric/bindings/blas/detail/cublas.h>
#include <boost/numeric/bindings/blas/detail/blas_option.hpp>
#else
#include <boost/numeric/bindings/blas/detail/blas.h>
#include <boost/numeric/bindings/blas/detail/blas_option.hpp>
#endif

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end BLAS-routine.
//
namespace detail {

#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * float value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const float alpha, const float* a,
        const std::ptrdiff_t lda, const float* x, const std::ptrdiff_t incx,
        const float beta, float* y, const std::ptrdiff_t incy ) {
    cblas_sgemv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, alpha, a, lda, x, incx, beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * double value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const double alpha, const double* a,
        const std::ptrdiff_t lda, const double* x, const std::ptrdiff_t incx,
        const double beta, double* y, const std::ptrdiff_t incy ) {
    cblas_dgemv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, alpha, a, lda, x, incx, beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const std::complex<float> alpha,
        const std::complex<float>* a, const std::ptrdiff_t lda,
        const std::complex<float>* x, const std::ptrdiff_t incx,
        const std::complex<float> beta, std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    cblas_cgemv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, &alpha, a, lda, x, incx, &beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const std::complex<double> alpha,
        const std::complex<double>* a, const std::ptrdiff_t lda,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double> beta, std::complex<double>* y,
        const std::ptrdiff_t incy ) {
    cblas_zgemv( cblas_option< Order >::value, cblas_option< Trans >::value,
            m, n, &alpha, a, lda, x, incx, &beta, y, incy );
}

#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * float value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const float alpha, const float* a,
        const std::ptrdiff_t lda, const float* x, const std::ptrdiff_t incx,
        const float beta, float* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasSgemv( blas_option< Trans >::value, m, n, alpha, a, lda, x, incx,
            beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * double value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const double alpha, const double* a,
        const std::ptrdiff_t lda, const double* x, const std::ptrdiff_t incx,
        const double beta, double* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasDgemv( blas_option< Trans >::value, m, n, alpha, a, lda, x, incx,
            beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<float> value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const std::complex<float> alpha,
        const std::complex<float>* a, const std::ptrdiff_t lda,
        const std::complex<float>* x, const std::ptrdiff_t incx,
        const std::complex<float> beta, std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasCgemv( blas_option< Trans >::value, m, n, alpha, a, lda, x, incx,
            beta, y, incy );
}

//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * complex<double> value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const std::complex<double> alpha,
        const std::complex<double>* a, const std::ptrdiff_t lda,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double> beta, std::complex<double>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    cublasZgemv( blas_option< Trans >::value, m, n, alpha, a, lda, x, incx,
            beta, y, incy );
}

#else
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * float value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const float alpha, const float* a,
        const std::ptrdiff_t lda, const float* x, const std::ptrdiff_t incx,
        const float beta, float* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_SGEMV( &blas_option< Trans >::value, &m, &n, &alpha, a, &lda, x,
            &incx, &beta, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * double value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const double alpha, const double* a,
        const std::ptrdiff_t lda, const double* x, const std::ptrdiff_t incx,
        const double beta, double* y, const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_DGEMV( &blas_option< Trans >::value, &m, &n, &alpha, a, &lda, x,
            &incx, &beta, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<float> value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const std::complex<float> alpha,
        const std::complex<float>* a, const std::ptrdiff_t lda,
        const std::complex<float>* x, const std::ptrdiff_t incx,
        const std::complex<float> beta, std::complex<float>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_CGEMV( &blas_option< Trans >::value, &m, &n, &alpha, a, &lda, x,
            &incx, &beta, y, &incy );
}

//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * complex<double> value-type.
//
template< typename Order, typename Trans >
inline void gemv( Order, Trans, const std::ptrdiff_t m,
        const std::ptrdiff_t n, const std::complex<double> alpha,
        const std::complex<double>* a, const std::ptrdiff_t lda,
        const std::complex<double>* x, const std::ptrdiff_t incx,
        const std::complex<double> beta, std::complex<double>* y,
        const std::ptrdiff_t incy ) {
    BOOST_STATIC_ASSERT( (is_column_major<Order>::value) );
    BLAS_ZGEMV( &blas_option< Trans >::value, &m, &n, &alpha, a, &lda, x,
            &incx, &beta, y, &incy );
}

#endif

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gemv.
//
template< typename Value >
struct gemv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef void return_type;

    // high-level transform typedefs and functions
    template< typename MatrixA, typename VectorX, typename VectorY >
    static return_type transform( MatrixA& A, VectorX& x, VectorY& y,
            const value_type alpha, const value_type beta ) {
        invoke();
    }

    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorX, typename VectorY >
    static return_type invoke( const value_type alpha, const MatrixA& a,
            const VectorX& x, const value_type beta, VectorY& y ) {
        typedef typename detail::default_order< MatrixA >::type order;
        typedef typename result_of::trans_tag< MatrixA, order >::type trans;
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixA >::type >::type, typename remove_const<
                typename value< VectorX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_same< typename remove_const< typename value<
                MatrixA >::type >::type, typename remove_const<
                typename value< VectorY >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorY >::value ) );
        detail::gemv( order(), trans(), size_row_op(a, trans()),
                size_column_op(a, trans()), alpha, begin_value(a),
                stride_major(a), begin_value(x), stride(x), beta,
                begin_value(y), stride(y) );
    }
};

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the gemv_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gemv. Its overload differs for
// * VectorY&
//
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename gemv_impl< typename value< MatrixA >::type >::return_type
gemv( const typename value< MatrixA >::type alpha, const MatrixA& a,
        const VectorX& x, const typename value< MatrixA >::type beta,
        VectorY& y ) {
    gemv_impl< typename value< MatrixA >::type >::invoke( alpha, a, x,
            beta, y );
}

//
// Overloaded function for gemv. Its overload differs for
// * const VectorY&
//
template< typename MatrixA, typename VectorX, typename VectorY >
inline typename gemv_impl< typename value< MatrixA >::type >::return_type
gemv( const typename value< MatrixA >::type alpha, const MatrixA& a,
        const VectorX& x, const typename value< MatrixA >::type beta,
        const VectorY& y ) {
    gemv_impl< typename value< MatrixA >::type >::invoke( alpha, a, x,
            beta, y );
}

} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
