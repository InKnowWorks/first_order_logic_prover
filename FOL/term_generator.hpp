#ifndef FIRST_ORDER_LOGIC_TERM_GENERATOR_HPP
#define FIRST_ORDER_LOGIC_TERM_GENERATOR_HPP
#include "../sentence/function.hpp"
#include <set>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
namespace first_order_logic
{
    template< class variable_maker >
    struct term_generator
    {
        variable_maker vm;
        size_t arity;
        std::map< term, std::set< free_sentence > > & cv;
        std::set< term > term_map;
        std::map< function, std::pair< std::unique_ptr< term_generator >, std::unique_ptr<term_generator> > > functions;
        const std::set< function > & original_functions;
        term_generator( const term_generator & tg ) :
            vm( tg.vm ),
            arity( tg.arity ),
            cv( tg.cv ),
            term_map( tg.term_map ),
            original_functions( tg.original_functions ),
            i( this->functions.begin( ) ) { }
        term_generator(
                variable_maker vm,
                size_t arity,
                decltype( cv ) & cv,
                const std::set< function > & functions )
            : vm( vm ),
              arity( arity ),
              cv( cv ),
              original_functions( functions ),
              i( this->functions.begin( ) ) { }
        decltype(functions.begin()) i;
        std::vector< term > generate( decltype( functions.begin( ) ) it )
        {
            auto f = it->second.first->generate( );
            auto s = it->second.second->generate( );
            f.reserve( f.size( ) + s.size( ) );
            std::copy( s.begin( ), s.end( ), std::back_inserter( f ) );
            if ( arity == 1 ) { return { make_function( it->first.name,  f ) }; }
            else
            {
                assert( f.size( ) == arity );
                return f;
            }
        }
        term_generator generate_term_generator( size_t a ) const
        { return term_generator( vm, a, cv, original_functions ); }
        std::vector< term > generate( )
        {
            if ( arity == 0 ) { return { }; }
            else
            {
                for ( auto it : cv )
                {
                    if ( term_map.count( it.first ) == 0 )
                    {
                        term_map.insert( it.first );
                        return { it.first };
                    }
                }
                if ( functions.size( ) != original_functions.size( ) )
                {
                    std::transform(
                                original_functions.begin( ),
                                original_functions.end( ),
                                std::inserter( functions, functions.end( ) ),
                                [this]( const function & f )
                    {
                        assert( f.arity != 0 );
                        return std::make_pair(
                                    f,
                                    std::make_pair(
                                        std::make_unique< term_generator >( generate_term_generator( f.arity - 1 ) ),
                                        std::make_unique< term_generator >( generate_term_generator( 1 ) ) ) );
                    } );
                }
                if ( i == functions.end( ) ) { i = functions.begin( ); }
                if ( i == functions.end( ) ) { return { vm( ) }; }
                auto ret = generate( i );
                if ( i != functions.end( ) ) { ++i; }
                assert( ret.size( ) == arity );
                return ret;
            }
        }
    };
}
#endif //FIRST_ORDER_LOGIC_TERM_GENERATOR_HPP
