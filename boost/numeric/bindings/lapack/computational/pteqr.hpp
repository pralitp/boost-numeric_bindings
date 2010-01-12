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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PTEQR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PTEQR_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for pteqr is the netlib-compatible backend.
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
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n, float* d,
        float* e, float* z, const fortran_int_t ldz, float* work ) {
    fortran_int_t info(0);
    LAPACK_SPTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        double* d, double* e, double* z, const fortran_int_t ldz,
        double* work ) {
    fortran_int_t info(0);
    LAPACK_DPTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n, float* d,
        float* e, std::complex<float>* z, const fortran_int_t ldz,
        float* work ) {
    fortran_int_t info(0);
    LAPACK_CPTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        double* d, double* e, std::complex<double>* z,
        const fortran_int_t ldz, double* work ) {
    fortran_int_t info(0);
    LAPACK_ZPTEQR( &compz, &n, d, e, z, &ldz, work, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to pteqr.
//
template< typename Value, typename Enable = void >
struct pteqr_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct pteqr_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK >
    static std::ptrdiff_t invoke( const char compz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, detail::workspace1<
            WORK > work ) {
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
        BOOST_ASSERT( compz == 'N' || compz == 'V' || compz == 'I' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(d) >= n );
        BOOST_ASSERT( size(e) >= n-1 );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work( n ));
        BOOST_ASSERT( size_minor(z) == 1 || stride_minor(z) == 1 );
        return detail::pteqr( compz, n, begin_value(d), begin_value(e),
                begin_value(z), stride_major(z),
                begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        return invoke( compz, n, d, e, z, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, optimal_workspace work ) {
        return invoke( compz, n, d, e, z, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 4*n;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct pteqr_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK >
    static std::ptrdiff_t invoke( const char compz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, detail::workspace1<
            WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorD >::type >::type,
                typename remove_const< typename value<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( compz == 'N' || compz == 'V' || compz == 'I' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(d) >= n );
        BOOST_ASSERT( size(e) >= n-1 );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work( n ));
        BOOST_ASSERT( size_minor(z) == 1 || stride_minor(z) == 1 );
        return detail::pteqr( compz, n, begin_value(d), begin_value(e),
                begin_value(z), stride_major(z),
                begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, minimal_workspace work ) {
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        return invoke( compz, n, d, e, z, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static std::ptrdiff_t invoke( const char compz, const fortran_int_t n,
            VectorD& d, VectorE& e, MatrixZ& z, optimal_workspace work ) {
        return invoke( compz, n, d, e, z, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return 4*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the pteqr_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixZ& z, Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, VectorE& e, MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, VectorE& e, MatrixZ& z, Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, VectorE& e, MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, const VectorE& e, MatrixZ& z, Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, const VectorE& e, MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, MatrixZ& z, Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixZ& z, Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, VectorE& e, const MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, VectorE& e, const MatrixZ& z, Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, VectorE& e, const MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, const VectorE& e, const MatrixZ& z, Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * VectorD&
// * const VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        VectorD& d, const VectorE& e, const MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * const MatrixZ&
// * User-defined workspace
//
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, const MatrixZ& z,
        Workspace work ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, work );
}

//
// Overloaded function for pteqr. Its overload differs for
// * const VectorD&
// * const VectorE&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename VectorD, typename VectorE, typename MatrixZ >
inline std::ptrdiff_t pteqr( const char compz, const fortran_int_t n,
        const VectorD& d, const VectorE& e, const MatrixZ& z ) {
    return pteqr_impl< typename value< MatrixZ >::type >::invoke( compz,
            n, d, e, z, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
