#ifndef FIRST_ORDER_LOGIC_SENTENCE_CONVERTER_HPP
#define FIRST_ORDER_LOGIC_SENTENCE_CONVERTER_HPP
#include "sentence_helper.hpp"
#include "forward/first_order_logic.hpp"
#include "../cpp_common/expansion.hpp"
namespace first_order_logic
{
    struct variable;
    template< typename TO >
    struct all_converter
    {
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_all(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >
        >
        sentence< TO > operator ( )( const variable & v, const ARG & t ) const
        { return make_all( v, t ); }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_all(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_all(
                                std::declval< variable >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >
        >
        sentence< TO > operator ( )( const variable & v, const ARG & t ) const
        { return make_all( v, sentence< TO >( t ) ); }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_all(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_all(
                                std::declval< variable >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        sentence< TO > operator ( )( const variable & v, const ARG & a )
        {
            return make_pass< sentence< TO > >(
                        typename next_sentence_type< sentence< TO > >::type(
                            make_all( v, a ) ) );
        }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_all(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_all(
                                std::declval< variable >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename = std::enable_if_t
                <
                    ! std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        void operator ( )( const variable &, const ARG & ) const { throw; }
        sentence< TO > operator ( )( const variable &, const no_such_sentence & ) const
        { throw; }
    };

    template< typename TO >
    struct some_converter
    {
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_some(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >
        >
        sentence< TO > operator ( )( const variable & v, const ARG & t ) const
        { return make_some( v, t ); }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ( ! std::is_same
                    <
                        decltype(
                            make_some(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value )
                >,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_some(
                                std::declval< variable >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >
        >
        sentence< TO > operator ( )( const variable & v, const ARG & t ) const
        { return make_some( v, sentence< TO >( t ) ); }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_some(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_some(
                                std::declval< variable >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        sentence< TO > operator ( )( const variable & v, const ARG & a )
        {
            return make_pass< sentence< TO > >(
                        typename next_sentence_type< sentence< TO > >::type(
                            make_some( v, a ) ) );
        }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_some(
                                std::declval< variable >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_some(
                                std::declval< variable >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        void operator ( )( const variable &, const ARG & ) const { throw; }
        sentence< TO > operator ( )( const variable &, const no_such_sentence & ) const { throw; }
    };

    template< typename TO >
    struct and_converter
    {
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_and(
                                std::declval< ARG >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l, const ARG & r ) const
        { return make_and( l, r ); }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_and(
                                std::declval< ARG >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_and(
                                std::declval< sentence< TO > >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l, const ARG & r ) const
        { return make_and( sentence< TO >( l ), sentence< TO >( r ) ); }

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_and(
                                std::declval< ARG >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_and(
                                std::declval< sentence< TO > >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l, const ARG & r )
        {
            return make_pass< sentence< TO > >(
                        typename next_sentence_type< sentence< TO > >::type(
                            make_and( l, r ) ) );
        }

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype( make_and( std::declval< ARG >( ), std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_and(
                                std::declval< sentence< TO > >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        void operator ( )( const ARG &, const ARG & ) const { throw; }
        sentence< TO > operator ( )( const no_such_sentence &, const no_such_sentence & ) const
        { throw; }
    };
    template< typename TO >
    struct or_converter
    {

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_or(
                                std::declval< ARG >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l, const ARG & r ) const { return make_or( l, r ); }
        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_or(
                                std::declval< ARG >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype(
                            make_or(
                                std::declval< sentence< TO > >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l, const ARG & r ) const
        { return make_or( sentence< TO >( l ), sentence< TO >( r ) ); }

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_or(
                                std::declval< ARG >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_or(
                                std::declval< sentence< TO > >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l, const ARG & r )
        {
            return make_pass< sentence< TO > >(
                        typename next_sentence_type< sentence< TO > >::type(
                            make_or( l, r ) ) );
        }

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_or(
                                std::declval< ARG >( ),
                                std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype(
                            make_or(
                                std::declval< sentence< TO > >( ),
                                std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        void operator ( )( const ARG &, const ARG & ) const { throw; }
        sentence< TO > operator ( )( const no_such_sentence &, const no_such_sentence & ) const
        { throw; }
    };
    template< typename TO >
    struct not_converter
    {

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype( make_not( std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l ) const { return make_not( l ); }

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype( make_not( std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    std::is_same
                    <
                        decltype( make_not( std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >
        >
        sentence< TO > operator ( )( const ARG & l ) const
        { return make_not( sentence< TO >( l ) ); }

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype( make_not( std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype( make_not( std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
            typename = std::enable_if_t
            <
                std::is_convertible
                <
                    ARG,
                    typename next_sentence_type< sentence< TO > >::type
                >::value
            >
        >
        sentence< TO > operator ( )( const ARG & l )
        {
            return make_pass< sentence< TO > >(
                        typename next_sentence_type< sentence< TO > >::type( make_not( l ) ) );
        }

        template
        <
            typename ARG,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype( make_not( std::declval< ARG >( ) ) ),
                        sentence< TO >
                    >::value
                >,
            typename =
                std::enable_if_t
                <
                    ! std::is_same
                    <
                        decltype( make_not( std::declval< sentence< TO > >( ) ) ),
                        sentence< TO >
                    >::value && std::is_same< ARG, ARG >::value
                >,
                typename = std::enable_if_t
                <
                    ! std::is_convertible
                    <
                        ARG,
                        typename next_sentence_type< sentence< TO > >::type
                    >::value
                >
        >
        void operator ( )( const ARG & ) const { throw; }
        sentence< TO > operator ( )( const no_such_sentence & ) const { throw; }
    };
}
#endif //FIRST_ORDER_LOGIC_SENTENCE_CONVERTER_HPP
