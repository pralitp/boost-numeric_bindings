$TEMPLATE[blas.hpp]
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

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_$DIRNAME_$GROUPNAME_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_$DIRNAME_$GROUPNAME_HPP

$INCLUDES

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

$OVERLOADS
} // namespace detail

$LEVEL1

//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. Calls
// to these functions are passed to the $groupname_impl classes. In the 
// documentation, the const-overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

$LEVEL2
} // namespace blas
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
$TEMPLATE[backend_blas_overloads]
#if defined BOOST_NUMERIC_BINDINGS_BLAS_CBLAS
$CBLAS_OVERLOADS
#elif defined BOOST_NUMERIC_BINDINGS_BLAS_CUBLAS
$CUBLAS_OVERLOADS
#else
$BLAS_OVERLOADS
#endif
$TEMPLATE[blas_overloads]
//
// Overloaded function for dispatching to
// * netlib-compatible BLAS backend (the default), and
// * $SPECIALIZATION value-type.
//
template< $TYPES >
inline $RESULT_TYPE $groupname( $LEVEL0 ) {
    $STATIC_ASSERTS
    $RETURN_STATEMENTBLAS_$SUBROUTINE( $CALL_BLAS_HEADER );
}

$TEMPLATE[cblas_overloads]
//
// Overloaded function for dispatching to
// * CBLAS backend, and
// * $SPECIALIZATION value-type.
//
template< $TYPES >
inline $RESULT_TYPE $groupname( $LEVEL0 ) {
    $RETURN_STATEMENT$CBLAS_ROUTINE( $CALL_CBLAS_HEADER );
}

$TEMPLATE[cublas_overloads]
//
// Overloaded function for dispatching to
// * CUBLAS backend, and
// * $SPECIALIZATION value-type.
//
template< $TYPES >
inline $RESULT_TYPE $groupname( $LEVEL0 ) {
    $STATIC_ASSERTS
    $RETURN_STATEMENT$CUBLAS_ROUTINE( $CALL_CUBLAS_HEADER );
}

$TEMPLATE[blas_level1]
//
// Value-type based template class. Use this class if you need a type
// for dispatching to $groupname.
//
template< typename Value >
struct $groupname_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef $RESULT_TYPE result_type;

$INCLUDE_TEMPLATES
    //
    // Static member function that
    // * Deduces the required arguments for dispatching to BLAS, and
    // * Asserts that most arguments make sense.
    //
    template< $TYPES >
    static result_type invoke( $LEVEL1 ) {
        namespace bindings = ::boost::numeric::bindings;
        $TYPEDEFS
        $STATIC_ASSERTS
        $ASSERTS
        $RETURN_STATEMENTdetail::$groupname( $CALL_LEVEL0 );
    }
};
$TEMPLATE[blas_level2]
//
// Overloaded function for $groupname. Its overload differs for
$COMMENTS
//
template< $TYPES >
inline typename $groupname_impl< typename $NAMESPACEvalue_type< $FIRST_TYPENAME >::type >::result_type
$groupname( $LEVEL2 ) {
    $RETURN_STATEMENT$groupname_impl< typename $NAMESPACEvalue_type< $FIRST_TYPENAME >::type >::invoke( $CALL_LEVEL1 );
}
$TEMPLATE[end]
