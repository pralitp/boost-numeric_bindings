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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRSEN_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_TRSEN_HPP

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
// Overloaded function for dispatching to complex<float> value-type.
//
inline void trsen( char job, char compq, const logical_t* select,
        fortran_int_t n, std::complex<float>* t, fortran_int_t ldt,
        std::complex<float>* q, fortran_int_t ldq, std::complex<float>* w,
        fortran_int_t& m, float& s, float& sep, std::complex<float>* work,
        fortran_int_t lwork, fortran_int_t& info ) {
    LAPACK_CTRSEN( &job, &compq, select, &n, t, &ldt, q, &ldq, w, &m, &s,
            &sep, work, &lwork, &info );
}

//
// Overloaded function for dispatching to complex<double> value-type.
//
inline void trsen( char job, char compq, const logical_t* select,
        fortran_int_t n, std::complex<double>* t, fortran_int_t ldt,
        std::complex<double>* q, fortran_int_t ldq, std::complex<double>* w,
        fortran_int_t& m, double& s, double& sep, std::complex<double>* work,
        fortran_int_t lwork, fortran_int_t& info ) {
    LAPACK_ZTRSEN( &job, &compq, select, &n, t, &ldt, q, &ldq, w, &m, &s,
            &sep, work, &lwork, &info );
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to trsen.
//
template< typename Value >
struct trsen_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
            typename VectorW, typename WORK >
    static void invoke( const char job, const char compq,
            const VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
            fortran_int_t& m, real_type& s, real_type& sep,
            fortran_int_t& info, detail::workspace1< WORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixT >::type >::type,
                typename remove_const< typename value<
                MatrixQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixT >::type >::type,
                typename remove_const< typename value<
                VectorW >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixT >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< MatrixQ >::value) );
        BOOST_STATIC_ASSERT( (is_mutable< VectorW >::value) );
        BOOST_ASSERT( compq == 'V' || compq == 'N' );
        BOOST_ASSERT( job == 'N' || job == 'E' || job == 'V' || job == 'B' );
        BOOST_ASSERT( size(select) >= size_column(t) );
        BOOST_ASSERT( size(w) >= size_column(t) );
        BOOST_ASSERT( size(work.select(value_type())) >= min_size_work(
                $CALL_MIN_SIZE ));
        BOOST_ASSERT( size_column(t) >= 0 );
        BOOST_ASSERT( size_minor(q) == 1 || stride_minor(q) == 1 );
        BOOST_ASSERT( size_minor(t) == 1 || stride_minor(t) == 1 );
        BOOST_ASSERT( stride_major(t) >= std::max< std::ptrdiff_t >(1,
                size_column(t)) );
        detail::trsen( job, compq, begin_value(select), size_column(t),
                begin_value(t), stride_major(t), begin_value(q),
                stride_major(q), begin_value(w), m, s, sep,
                begin_value(work.select(value_type())),
                size(work.select(value_type())), info );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
            typename VectorW >
    static void invoke( const char job, const char compq,
            const VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
            fortran_int_t& m, real_type& s, real_type& sep,
            fortran_int_t& info, minimal_workspace work ) {
        bindings::detail::array< value_type > tmp_work( min_size_work(
                $CALL_MIN_SIZE ) );
        invoke( job, compq, select, t, q, w, m, s, sep, info,
                workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
            typename VectorW >
    static void invoke( const char job, const char compq,
            const VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
            fortran_int_t& m, real_type& s, real_type& sep,
            fortran_int_t& info, optimal_workspace work ) {
        value_type opt_size_work;
        detail::trsen( job, compq, begin_value(select), size_column(t),
                begin_value(t), stride_major(t), begin_value(q),
                stride_major(q), begin_value(w), m, s, sep, &opt_size_work,
                -1, info );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        invoke( job, compq, select, t, q, w, m, s, sep, info,
                workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( $ARGUMENTS ) {
        $MIN_SIZE
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the trsen_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q, VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q, VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q, VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q, VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, const VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, const VectorW& w,
        fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q,
        const VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q,
        const VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q,
        const VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q,
        const VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        const VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * const VectorW&
// * fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        const VectorW& w, fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q, VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q, VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q, VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q, VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        VectorW& w, const fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        VectorW& w, const fortran_int_t& m, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& s,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, const VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, MatrixQ& q, const VectorW& w,
        const fortran_int_t& m, typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q,
        const VectorW& w, const fortran_int_t& m,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, MatrixQ& q,
        const VectorW& w, const fortran_int_t& m,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q,
        const VectorW& w, const fortran_int_t& m,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * MatrixT&
// * const MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, MatrixT& t, const MatrixQ& q,
        const VectorW& w, const fortran_int_t& m,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * User-defined workspace
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW, typename Workspace >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        const VectorW& w, const fortran_int_t& m,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep, Workspace work ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, work );
    return info;
}

//
// Overloaded function for trsen. Its overload differs for
// * const MatrixT&
// * const MatrixQ&
// * const VectorW&
// * const fortran_int_t&
// * Default workspace-type (optimal)
//
template< typename VectorSELECT, typename MatrixT, typename MatrixQ,
        typename VectorW >
inline std::ptrdiff_t trsen( const char job, const char compq,
        const VectorSELECT& select, const MatrixT& t, const MatrixQ& q,
        const VectorW& w, const fortran_int_t& m,
        typename remove_imaginary< typename value<
        VectorSELECT >::type >::type& s, typename remove_imaginary<
        typename value< VectorSELECT >::type >::type& sep ) {
    fortran_int_t info(0);
    trsen_impl< typename value< VectorSELECT >::type >::invoke( job,
            compq, select, t, q, w, m, s, sep, info, optimal_workspace() );
    return info;
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
