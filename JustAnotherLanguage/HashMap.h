#pragma once

#include "List.h"

#include <exception>

class NotFoundHashMapException : public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "Element not found in hash map";
    }
};

template < typename TypeIndex, typename TypeValue >
class HashMap
{
private:
    struct HashMapItem
    {
        TypeIndex index;
        TypeValue value;

        HashMapItem() = default;

        HashMapItem( TypeIndex _index, TypeValue _value ) 
            : index( _index ), value( _value )
        {}

        HashMapItem( const HashMapItem &item ) 
            : index( item.index ), value( item.value )
        {}
    };

private:
    static const int COUNT_OF_HASH_MAP = 16;
    List<HashMapItem> lists[COUNT_OF_HASH_MAP];

public:
    HashMap() = default;
    ~HashMap() = default;

    void Add( TypeIndex index, TypeValue value )
    {
        int localIndex = calculateLocalIndex( index );
        lists[localIndex].Add( HashMapItem( index, value ) );
    }

    TypeValue Get( TypeIndex index )
    {
        int localIndex = calculateLocalIndex( index );
        lists[localIndex].ToStart();

        try
        {
            while ( lists[localIndex].Next() )
            {
                HashMapItem item = lists[localIndex].GetValue();

                if ( item.index == index )
                {
                    return item.value;
                }
            }
        }
        catch( ListNullreferenceException &e )
        {
            std::cout << e.what() << std::endl;

            throw NotFoundHashMapException();
        }
        catch( ListNotInitializedException &e )
        {
            std::cout << e.what() << std::endl;

            throw NotFoundHashMapException();
        }

        throw NotFoundHashMapException();
    }

    void Clear ()
    {
        for ( int i = 0; i < COUNT_OF_HASH_MAP; i++ )
        {
            lists[i].Clear();
        }
    }

private:
    int calculateLocalIndex( TypeIndex index )
    {
        return index & 15; 
    }
};
