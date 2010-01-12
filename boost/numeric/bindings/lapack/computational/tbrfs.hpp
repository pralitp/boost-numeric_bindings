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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TBRFS_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TBRFS_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/data_side.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/diag_tag.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/trans_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for tbrfs is the netlib-compatible backend.
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
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbrfs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const float* ab, const fortran_int_t ldab,
        const float* b, const fortran_int_t ldb, const float* x,
        const fortran_int_t ldx, float* ferr, float* berr, float* work,
        fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_STBRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, x, &ldx, ferr,
            berr, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbrfs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const double* ab, const fortran_int_t ldab,
        const double* b, const fortran_int_t ldb, const double* x,
        const fortran_int_t ldx, double* ferr, double* berr, double* work,
        fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DTBRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, x, &ldx, ferr,
            berr, work, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbrfs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const std::complex<float>* ab,
        const fortran_int_t ldab, const std::complex<float>* b,
        const fortran_int_t ldb, const std::complex<float>* x,
        const fortran_int_t ldx, float* ferr, float* berr,
        std::complex<float>* work, float* rwork ) {
    fortran_int_t info(0);
    LAPACK_CTBRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, x, &ldx, ferr,
            berr, work, rwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename Trans, typename Diag >
inline std::ptrdiff_t tbrfs( const char uplo, Trans, Diag,
        const fortran_int_t n, const fortran_int_t kd,
        const fortran_int_t nrhs, const std::complex<double>* ab,
        const fortran_int_t ldab, const std::complex<double>* b,
        const fortran_int_t ldb, const std::complex<double>* x,
        const fortran_int_t ldx, double* ferr, double* berr,
        std::complex<double>* work, double* rwork ) {
    fortran_int_t info(0);
    LAPACK_ZTBRFS( &uplo, &lapack_option< Trans >::value, &lapack_option<
            Diag >::value, &n, &kd, &nrhs, ab, &ldab, b, &ldb, x, &ldx, ferr,
            berr, work, rwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to tbrfs.
//
template< typename Value, typename Enable = void >
struct tbrfs_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct tbrfs_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR, typename WORK,
            typename IWORK >
    static std::ptrdiff_t invoke( const char uplo, const fortran_int_t n,
            const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            detail::workspace2< WORK, IWORK > work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                VectorFERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(berr) >= size_column(x) );
        BOOST_ASSERT( size(work.select(fortran_int_t())) >=
                min_size_iwork( n ));
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_work( n ));
        BOOST_ASSERT( size_column(x) >= 0 );
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(x) == 1 || stride_minor(x) == 1 );
        BOOST_ASSERT( stride_major(ab) >= kd+1 );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( stride_major(x) >= std::max< std::ptrdiff_t >(1,n) );
        return detail::tbrfs( uplo, trans(), diag(), n, kd, size_column(x),
                begin_value(ab), stride_major(ab), begin_value(b),
                stride_major(b), begin_value(x), stride_major(x),
                begin_value(ferr), begin_value(berr),
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
    template< typename MatrixAB, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const char uplo, const fortran_int_t n,
            const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            minimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        bindings::detail::array< real_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( n ) );
        return invoke( uplo, n, kd, ab, b, x, ferr, berr, workspace( tmp_work,
                tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const char uplo, const fortran_int_t n,
            const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            optimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        return invoke( uplo, n, kd, ab, b, x, ferr, berr,
                minimal_workspace() );
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
struct tbrfs_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR, typename WORK,
            typename RWORK >
    static std::ptrdiff_t invoke( const char uplo, const fortran_int_t n,
            const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            detail::workspace2< WORK, RWORK > work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< VectorFERR >::type >::type,
                typename remove_const< typename value<
                VectorBERR >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixX >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorFERR >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorBERR >::value) );
        BOOST_ASSERT( kd >= 0 );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( size(berr) >= size_column(x) );
        BOOST_ASSERT( size(work.select(real_type())) >= min_size_rwork( n ));
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work( n ));
        BOOST_ASSERT( size_column(x) >= 0 );
        BOOST_ASSERT( size_minor(ab) == 1 || stride_minor(ab) == 1 );
        BOOST_ASSERT( size_minor(b) == 1 || stride_minor(b) == 1 );
        BOOST_ASSERT( size_minor(x) == 1 || stride_minor(x) == 1 );
        BOOST_ASSERT( stride_major(ab) >= kd+1 );
        BOOST_ASSERT( stride_major(b) >= std::max< std::ptrdiff_t >(1,n) );
        BOOST_ASSERT( stride_major(x) >= std::max< std::ptrdiff_t >(1,n) );
        return detail::tbrfs( uplo, trans(), diag(), n, kd, size_column(x),
                begin_value(ab), stride_major(ab), begin_value(b),
                stride_major(b), begin_value(x), stride_major(x),
                begin_value(ferr), begin_value(berr),
                begin_value(work.select(value_type())),
                begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const char uplo, const fortran_int_t n,
            const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            minimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        bindings::detail::array< value_type > tmp_work( min_size_work( n ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork( n ) );
        return invoke( uplo, n, kd, ab, b, x, ferr, berr, workspace( tmp_work,
                tmp_rwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB, typename MatrixB, typename MatrixX,
            typename VectorFERR, typename VectorBERR >
    static std::ptrdiff_t invoke( const char uplo, const fortran_int_t n,
            const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
            const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
            optimal_workspace work ) {
        typedef typename result_of::diag_tag< MatrixAB >::type diag;
        return invoke( uplo, n, kd, ab, b, x, ferr, berr,
                minimal_workspace() );
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
// Calls to these functions are passed to the tbrfs_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for tbrfs. Its overload differs for
// * VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, VectorFERR& ferr, VectorBERR& berr,
        Workspace work ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, work );
}

//
// Overloaded function for tbrfs. Its overload differs for
// * VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, VectorFERR& ferr, VectorBERR& berr ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for tbrfs. Its overload differs for
// * const VectorFERR&
// * VectorBERR&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, const VectorFERR& ferr, VectorBERR& berr,
        Workspace work ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, work );
}

//
// Overloaded function for tbrfs. Its overload differs for
// * const VectorFERR&
// * VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, const VectorFERR& ferr, VectorBERR& berr ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for tbrfs. Its overload differs for
// * VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, VectorFERR& ferr, const VectorBERR& berr,
        Workspace work ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, work );
}

//
// Overloaded function for tbrfs. Its overload differs for
// * VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, VectorFERR& ferr, const VectorBERR& berr ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, optimal_workspace() );
}

//
// Overloaded function for tbrfs. Its overload differs for
// * const VectorFERR&
// * const VectorBERR&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR, typename Workspace >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, const VectorFERR& ferr, const VectorBERR& berr,
        Workspace work ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, work );
}

//
// Overloaded function for tbrfs. Its overload differs for
// * const VectorFERR&
// * const VectorBERR&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixB, typename MatrixX,
        typename VectorFERR, typename VectorBERR >
inline std::ptrdiff_t tbrfs( const char uplo, const fortran_int_t n,
        const fortran_int_t kd, const MatrixAB& ab, const MatrixB& b,
        const MatrixX& x, const VectorFERR& ferr, const VectorBERR& berr ) {
    return tbrfs_impl< typename value< MatrixAB >::type >::invoke( uplo,
            n, kd, ab, b, x, ferr, berr, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
