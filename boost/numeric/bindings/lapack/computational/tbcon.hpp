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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TBCON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TBCON_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

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
// Overloaded function for dispatching to float value-type.
//
template< typename Diag >
inline void tbcon( char norm, char uplo, Diag, fortran_int_t n,
        fortran_int_t kd, const float* ab, fortran_int_t ldab, float& rcond,
        float* work, fortran_int_t* iwork, fortran_int_t& info ) {
    LAPACK_STBCON( &norm, &uplo, &lapack_option< Diag >::value, &n, &kd, ab,
            &ldab, &rcond, work, iwork, &info );
}

//
// Overloaded function for dispatching to double value-type.
//
template< typename Diag >
inline void tbcon( char norm, char uplo, Diag, fortran_int_t n,
        fortran_int_t kd, const double* ab, fortran_int_t ldab, double& rcond,
        double* work, fortran_int_t* iwork, fortran_int_t& info ) {
    LAPACK_DTBCON( &norm, &uplo, &lapack_option< Diag >::value, &n, &kd, ab,
            &ldab, &rcond, work, iwork, &info );
}

//
// Overloaded function for dispatching to complex<float> value-type.
//
template< typename Diag >
inline void tbcon( char norm, char uplo, Diag, fortran_int_t n,
        fortran_int_t kd, const std::complex<float>* ab, fortran_int_t ldab,
        float& rcond, std::complex<float>* work, float* rwork,
        fortran_int_t& info ) {
    LAPACK_CTBCON( &norm, &uplo, &lapack_option< Diag >::value, &n, &kd, ab,
            &ldab, &rcond, work, rwork, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
template< typename Diag >
inline void tbcon( char norm, char uplo, Diag, fortran_int_t n,
        fortran_int_t kd, const std::complex<double>* ab, fortran_int_t ldab,
        double& rcond, std::complex<double>* work, double* rwork,
        fortran_int_t& info ) {
    LAPACK_ZTBCON( &norm, &uplo, &lapack_option< Diag >::value, &n, &kd, ab,
            &ldab, &rcond, work, rwork, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to tbcon.
//
template< typename Value, typename Enable = void >
struct tbcon_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct tbcon_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename WORK, typename IWORK >
    static void invoke( const char norm, const char uplo,
            const fortran_int_t n, const fortran_int_t kd,
            const MatrixAB& ab, real_type& rcond, fortran_int_t& info,
            detail::workspace2< WORK, IWORK > work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( n ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work( n ));
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( stride_major(ab) >= kd+1 );
        detail::tbcon( norm, uplo, diag(), n, kd, begin_value(ab),
                stride_major(ab), rcond,
                begin_value(work.select(real_type())),
                begin_value(work.select(fortran_int_t())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB >
    static void invoke( const char norm, const char uplo,
            const fortran_int_t n, const fortran_int_t kd,
            const MatrixAB& ab, real_type& rcond, fortran_int_t& info,
            minimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n ) );
        invoke( norm, uplo, n, kd, ab, rcond, info, workspace( tmp_work,
                tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB >
    static void invoke( const char norm, const char uplo,
            const fortran_int_t n, const fortran_int_t kd,
            const MatrixAB& ab, real_type& rcond, fortran_int_t& info,
            optimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        invoke( norm, uplo, n, kd, ab, rcond, info, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 3*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t n ) {
        return n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct tbcon_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename WORK, typename RWORK >
    static void invoke( const char norm, const char uplo,
            const fortran_int_t n, const fortran_int_t kd,
            const MatrixAB& ab, real_type& rcond, fortran_int_t& info,
            detail::workspace2< WORK, RWORK > work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( norm == '1' || norm == 'O' || norm == 'I' );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_rwork( n ));
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work( n ));
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( stride_major(ab) >= kd+1 );
        detail::tbcon( norm, uplo, diag(), n, kd, begin_value(ab),
                stride_major(ab), rcond,
                begin_value(work.select(value_type())),
                begin_value(work.select(real_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB >
    static void invoke( const char norm, const char uplo,
            const fortran_int_t n, const fortran_int_t kd,
            const MatrixAB& ab, real_type& rcond, fortran_int_t& info,
            minimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        bindings::detail::array< value_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        invoke( norm, uplo, n, kd, ab, rcond, info, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB >
    static void invoke( const char norm, const char uplo,
            const fortran_int_t n, const fortran_int_t kd,
            const MatrixAB& ab, real_type& rcond, fortran_int_t& info,
            optimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        invoke( norm, uplo, n, kd, ab, rcond, info, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 2*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const std::ptrdiff_t n ) {
        return n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the tbcon_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for tbcon. Its overload differs for
// * User-defined workspace
//
template< typename MatrixAB, typename Workspace >
inline std::ptrdiff_t tbcon( const char norm, const char uplo,
        const fortran_int_t n, const fortran_int_t kd,
        const MatrixAB& ab, typename remove_imaginary< typename value<
        MatrixAB >::type >::type& rcond, Workspace work ) {
    fortran_int_t info(0);
    tbcon_impl< typename value< MatrixAB >::type >::invoke( norm, uplo,
            n, kd, ab, rcond, info, work );
    return info;
}

//
// Overloaded function for tbcon. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixAB >
inline std::ptrdiff_t tbcon( const char norm, const char uplo,
        const fortran_int_t n, const fortran_int_t kd,
        const MatrixAB& ab, typename remove_imaginary< typename value<
        MatrixAB >::type >::type& rcond ) {
    fortran_int_t info(0);
    tbcon_impl< typename value< MatrixAB >::type >::invoke( norm, uplo,
            n, kd, ab, rcond, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
