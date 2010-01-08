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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_STEVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_STEVD_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

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
inline void stevd( char jobz, fortran_int_t n, float* d, float* e, float* z,
        fortran_int_t ldz, float* work, fortran_int_t lwork,
        fortran_int_t* iwork, fortran_int_t liwork, fortran_int_t& info ) {
    LAPACK_SSTEVD( &jobz, &n, d, e, z, &ldz, work, &lwork, iwork, &liwork,
            &info );
}

//
// Overloaded function for dispatching to double value-type.
//
inline void stevd( char jobz, fortran_int_t n, double* d, double* e,
        double* z, fortran_int_t ldz, double* work, fortran_int_t lwork,
        fortran_int_t* iwork, fortran_int_t liwork, fortran_int_t& info ) {
    LAPACK_DSTEVD( &jobz, &n, d, e, z, &ldz, work, &lwork, iwork, &liwork,
            &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to stevd.
//
template< typename Value >
struct stevd_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK, typename IWORK >
    static void invoke( const char jobz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, fortran_int_t& info,
            detail::workspace2< WORK, IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorD >::type >::type,
                typename remove_const< typename value<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorD >::type >::type,
                typename remove_const< typename value<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(e) >= n-1 );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( jobz, n ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work( jobz,
                n ));
        BOOST_ASSERT( size_minor(z) == 1 || stride_minor(z) == 1 );
        detail::stevd( jobz, n, begin_value(d), begin_value(e),
                begin_value(z), stride_major(z),
                begin_value(work.select(real_type())),
                size(work.select(real_type())),
                begin_value(work.select(fortran_int_t())),
                size(work.select(fortran_int_t())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( const char jobz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, fortran_int_t& info,
            minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work( jobz,
                n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( jobz, n ) );
        invoke( jobz, n, d, e, z, info, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( const char jobz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, fortran_int_t& info,
            optimal_workspace work ) {
        real_type opt_size_work;
        fortran_int_t opt_size_iwork;
        detail::stevd( jobz, n, begin_value(d), begin_value(e),
                begin_value(z), stride_major(z), &opt_size_work, -1,
                &opt_size_iwork, -1, info );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                opt_size_iwork );
        invoke( jobz, n, d, e, z, info, workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char jobz,
            const std::ptrdiff_t n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 1 + 4*n + n*n;
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const char jobz,
            const std::ptrdiff_t n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 3 + 5*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the stevd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixZ& z, Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, VectorE& e, MatrixZ& z, Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, VectorE& e, MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * const VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, const VectorE& e, MatrixZ& z, Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * const VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, const VectorE& e, MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * const VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, MatrixZ& z, Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * const VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixZ& z, Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, VectorE& e, const MatrixZ& z, Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, VectorE& e, const MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * const VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, const VectorE& e, const MatrixZ& z, Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * VectorD&
// * const VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        VectorD& d, const VectorE& e, const MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * const VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, const MatrixZ& z,
        Workspace work ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, work );
    return info;
}

//
// Overloaded function for stevd. Its overload differs for
// * const VectorD&
// * const VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t stevd( const char jobz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, const MatrixZ& z ) {
    fortran_int_t info(0);
    stevd_impl< typename value< VectorD >::type >::invoke( jobz, n, d, e,
            z, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
