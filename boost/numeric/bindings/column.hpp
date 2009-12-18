//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_COLUMN_HPP
#define BOOST_NUMERIC_BINDINGS_COLUMN_HPP

#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/adaptable_type.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/ref.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace detail {

template< typename T >
struct column_wrapper:
        adaptable_type< column_wrapper<T> >,
        reference_wrapper<T> {

    column_wrapper( T& t, std::size_t index ):
        reference_wrapper<T>(t),
        m_index( index ) {}

    std::size_t m_index;
};

template< typename T, typename Id, typename Enable >
struct adaptor< column_wrapper<T>, Id, Enable > {

    typedef typename value<T>::type value_type;
    typedef mpl::map<
        mpl::pair< tag::value_type, value_type >,
        mpl::pair< tag::entity, tag::vector >,
        mpl::pair< tag::size_type<1>, typename result_of::size1<T>::type >,
        mpl::pair< tag::data_structure, tag::linear_array >,
        mpl::pair< tag::stride_type<1>, typename result_of::stride1<T>::type >
    > property_map;

    static typename result_of::size1<T>::type size1( const Id& id ) {
        return bindings::size1( id.get() );
    }

    static typename result_of::begin_value< T >::type begin_value( Id& id ) {
        return bindings::begin_value( id.get() ) +
            id.m_index * bindings::stride2( id.get() );
    }

    static typename result_of::end_value< T >::type end_value( Id& id ) {
        // TODO subtract some stuff from the true end
        return bindings::end_value( id.get() );
    }

    static typename result_of::stride1<T>::type stride1( const Id& id ) {
        return bindings::stride1( id.get() );
    }

};


} // namespace detail

namespace result_of {

template< typename T >
struct column {
    typedef detail::column_wrapper<T> type;
};

}

template< typename T >
detail::column_wrapper<T> column( T& underlying, std::size_t index ) {
    return detail::column_wrapper<T>( underlying, index );
}

template< typename T >
detail::column_wrapper<const T> column( const T& underlying, std::size_t index ) {
    return detail::column_wrapper<const T>( underlying, index );
}

} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
