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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_PPSV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_PPSV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for ppsv is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
template< typename UpLo >
inline std::ptrdiff_t ppsv( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, float* ap, float* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_SPPSV( &lapack_option< UpLo >::value, &n, &nrhs, ap, b, &ldb,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t ppsv( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, double* ap, double* b,
        const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_DPPSV( &lapack_option< UpLo >::value, &n, &nrhs, ap, b, &ldb,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t ppsv( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, std::complex<float>* ap,
        std::complex<float>* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_CPPSV( &lapack_option< UpLo >::value, &n, &nrhs, ap, b, &ldb,
            &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t ppsv( UpLo, const fortran_int_t n,
        const fortran_int_t nrhs, std::complex<double>* ap,
        std::complex<double>* b, const fortran_int_t ldb ) {
    fortran_int_t info(0);
    LAPACK_ZPPSV( &lapack_option< UpLo >::value, &n, &nrhs, ap, b, &ldb,
            &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to ppsv.
//
template< typename Value >
struct ppsv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAP, typename MatrixB >
    static std::ptrdiff_t invoke( MatrixAP& ap, MatrixB& b ) {
        typedef typename result_of::data_side< MatrixAP >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAP >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixAP >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixB >::value) );
        BOOST_ASSERT( size_column(ap) >= 0 );
        BOOST_ASSERT( size_column(b) >= 0 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,
                size_column(ap)) );
        return detail::ppsv( uplo(), size_column(ap), size_column(b),
                begin_value(ap), begin_value(b), stride_major(b) );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the ppsv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for ppsv. Its overload differs for
// * MatrixAP&
// * MatrixB&
//
template< typename MatrixAP, typename MatrixB >
inline std::ptrdiff_t ppsv( MatrixAP& ap, MatrixB& b ) {
    return ppsv_impl< typename value< MatrixAP >::type >::invoke( ap,
            b );
}

//
// Overloaded function for ppsv. Its overload differs for
// * const MatrixAP&
// * MatrixB&
//
template< typename MatrixAP, typename MatrixB >
inline std::ptrdiff_t ppsv( const MatrixAP& ap, MatrixB& b ) {
    return ppsv_impl< typename value< MatrixAP >::type >::invoke( ap,
            b );
}

//
// Overloaded function for ppsv. Its overload differs for
// * MatrixAP&
// * const MatrixB&
//
template< typename MatrixAP, typename MatrixB >
inline std::ptrdiff_t ppsv( MatrixAP& ap, const MatrixB& b ) {
    return ppsv_impl< typename value< MatrixAP >::type >::invoke( ap,
            b );
}

//
// Overloaded function for ppsv. Its overload differs for
// * const MatrixAP&
// * const MatrixB&
//
template< typename MatrixAP, typename MatrixB >
inline std::ptrdiff_t ppsv( const MatrixAP& ap, const MatrixB& b ) {
    return ppsv_impl< typename value< MatrixAP >::type >::invoke( ap,
            b );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
