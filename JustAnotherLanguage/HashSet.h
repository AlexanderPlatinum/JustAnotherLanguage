#pragma once

#include "List.h"

#include <exception>

class NotFoundHashSetException : public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "Element not found in hash set";
    }
};

template < typename TypeIndex, typename TypeValue >
class HashSet
{
private:
    struct HashSetItem
    {
        TypeIndex index;
        TypeValue value;

        HashSetItem() = default;

        HashSetItem( TypeIndex _index, TypeValue _value ) 
            : index( _index ), value( _value )
        {}

        HashSetItem( const HashSetItem &item ) 
            : index( item.index ), value( item.value )
        {}
    };

private:
    static const int COUNT_OF_HASH_SET = 16;
    List<HashSetItem> lists[COUNT_OF_HASH_SET];

public:
    HashSet() = default;
    ~HashSet() = default;

    void Add( TypeIndex index, TypeValue value )
    {
        int localIndex = calculateLocalIndex( index );
        lists[localIndex].Add( HashSetItem( index, value ) );
    }

    TypeValue Get( TypeIndex index )
    {
        int localIndex = calculateLocalIndex( index );
        lists[localIndex].ToStart();

        try
        {
            while ( lists[localIndex].Next() )
            {
                HashSetItem item = lists[localIndex].GetValue();

                if ( item.index == index )
                {
                    return item.value;
                }
            }
        }
        catch( ListNullreferenceException &e )
        {
            std::cout << e.what() << std::endl;

            throw NotFoundHashSetException();
        }
        catch( ListNotInitializedException &e )
        {
            std::cout << e.what() << std::endl;

            throw NotFoundHashSetException();
        }

        throw NotFoundHashSetException();
    }

    void Clear ()
    {
        for ( int i = 0; i < COUNT_OF_HASH_SET; i++ )
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
