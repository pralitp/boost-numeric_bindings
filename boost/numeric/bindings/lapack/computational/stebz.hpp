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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEBZ_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_STEBZ_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for stebz is the netlib-compatible backend.
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
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const float vl, const float vu,
        const fortran_int_t il, const fortran_int_t iu, const float abstol,
        const float* d, const float* e, fortran_int_t& m,
        fortran_int_t& nsplit, float* w, fortran_int_t* iblock,
        fortran_int_t* isplit, float* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_SSTEBZ( &range, &order, &n, &vl, &vu, &il, &iu, &abstol, d, e, &m,
            &nsplit, w, iblock, isplit, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const double vl, const double vu,
        const fortran_int_t il, const fortran_int_t iu, const double abstol,
        const double* d, const double* e, fortran_int_t& m,
        fortran_int_t& nsplit, double* w, fortran_int_t* iblock,
        fortran_int_t* isplit, double* work, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DSTEBZ( &range, &order, &n, &vl, &vu, &il, &iu, &abstol, d, e, &m,
            &nsplit, w, iblock, isplit, work, iwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to stebz.
//
template< typename Value >
struct stebz_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT, typename WORK,
            typename IWORK >
    static std::ptrdiff_t invoke( const char range, const char order,
            const fortran_int_t n, const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            const real_type abstol, const VectorD& d, const VectorE& e,
            fortran_int_t& m, fortran_int_t& nsplit, VectorW& w,
            VectorIBLOCK& iblock, VectorISPLIT& isplit, detail::workspace2<
            WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorD >::type >::type,
                typename remove_const< typename value<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorD >::type >::type,
                typename remove_const< typename value<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorIBLOCK >::type >::type,
                typename remove_const< typename value<
                VectorISPLIT >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorIBLOCK >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorISPLIT >::value) );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( order == 'B' || order == 'E' );
        BOOST_ASSERT( range == 'A' || range == 'V' || range == 'I' );
        BOOST_ASSERT( size(d) >= n );
        BOOST_ASSERT( size(e) >= n-1 );
        BOOST_ASSERT( size(isplit) >= n );
        BOOST_ASSERT( size(w) >= n );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( n ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work( n ));
        return detail::stebz( range, order, n, vl, vu, il, iu, abstol,
                begin_value(d), begin_value(e), m, nsplit, begin_value(w),
                begin_value(iblock), begin_value(isplit),
                begin_value(work.select(real_type())),
                begin_value(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT >
    static std::ptrdiff_t invoke( const char range, const char order,
            const fortran_int_t n, const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            const real_type abstol, const VectorD& d, const VectorE& e,
            fortran_int_t& m, fortran_int_t& nsplit, VectorW& w,
            VectorIBLOCK& iblock, VectorISPLIT& isplit,
            minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n ) );
        return invoke( range, order, n, vl, vu, il, iu, abstol, d, e, m,
                nsplit, w, iblock, isplit, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename VectorW,
            typename VectorIBLOCK, typename VectorISPLIT >
    static std::ptrdiff_t invoke( const char range, const char order,
            const fortran_int_t n, const real_type vl, const real_type vu,
            const fortran_int_t il, const fortran_int_t iu,
            const real_type abstol, const VectorD& d, const VectorE& e,
            fortran_int_t& m, fortran_int_t& nsplit, VectorW& w,
            VectorIBLOCK& iblock, VectorISPLIT& isplit,
            optimal_workspace work ) {
        return invoke( range, order, n, vl, vu, il, iu, abstol, d, e, m,
                nsplit, w, iblock, isplit, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 4*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n ) {
        return 3*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the stebz_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * VectorIBLOCK&
// * VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, VectorIBLOCK& iblock, VectorISPLIT& isplit,
        Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * VectorIBLOCK&
// * VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, VectorIBLOCK& iblock, VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * VectorIBLOCK&
// * VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, VectorIBLOCK& iblock, VectorISPLIT& isplit,
        Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * VectorIBLOCK&
// * VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, VectorIBLOCK& iblock, VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * const VectorIBLOCK&
// * VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, const VectorIBLOCK& iblock, VectorISPLIT& isplit,
        Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * const VectorIBLOCK&
// * VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, const VectorIBLOCK& iblock, VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * const VectorIBLOCK&
// * VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, const VectorIBLOCK& iblock, VectorISPLIT& isplit,
        Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * const VectorIBLOCK&
// * VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, const VectorIBLOCK& iblock, VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * VectorIBLOCK&
// * const VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, VectorIBLOCK& iblock, const VectorISPLIT& isplit,
        Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * VectorIBLOCK&
// * const VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, VectorIBLOCK& iblock, const VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * VectorIBLOCK&
// * const VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, VectorIBLOCK& iblock, const VectorISPLIT& isplit,
        Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * VectorIBLOCK&
// * const VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, VectorIBLOCK& iblock, const VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * const VectorIBLOCK&
// * const VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, const VectorIBLOCK& iblock, const VectorISPLIT& isplit,
        Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * VectorW&
// * const VectorIBLOCK&
// * const VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        VectorW& w, const VectorIBLOCK& iblock, const VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * const VectorIBLOCK&
// * const VectorISPLIT&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT, typename Workspace >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, const VectorIBLOCK& iblock,
        const VectorISPLIT& isplit, Workspace work ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, work );
}

//
// Overloaded function for stebz. Its overload differs for
// * const VectorW&
// * const VectorIBLOCK&
// * const VectorISPLIT&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename VectorW,
        typename VectorIBLOCK, typename VectorISPLIT >
inline std::ptrdiff_t stebz( const char range, const char order,
        const fortran_int_t n, const typename remove_imaginary<
        typename value< VectorD >::type >::type vl,
        const typename remove_imaginary< typename value<
        VectorD >::type >::type vu, const fortran_int_t il,
        const fortran_int_t iu, const typename remove_imaginary<
        typename value< VectorD >::type >::type abstol, const VectorD& d,
        const VectorE& e, fortran_int_t& m, fortran_int_t& nsplit,
        const VectorW& w, const VectorIBLOCK& iblock,
        const VectorISPLIT& isplit ) {
    return stebz_impl< typename value< VectorD >::type >::invoke( range,
            order, n, vl, vu, il, iu, abstol, d, e, m, nsplit, w, iblock,
            isplit, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
