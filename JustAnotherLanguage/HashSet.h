#pragma once

#include "List.h"

#include <map>

template < typename Type >
class HashSet
{
private:
    std::vector<List <Type>> lists;

    int currentList = 0;
    int size_of_trash = 16;
    int local_count = 0;
public:
    HashSet()
    {
        Resize();
    }

    ~HashSet() = default;

    void Resize ()
    {
        lists.reserve( size_of_trash );

        std::vector<List <Type>> temp = lists;
        lists.clear();

        for ( int i = 0; i < size_of_trash; i++ )
        {
            while( temp[i].Next() )
            {
                Type tmp_var = temp[i].GetValue();

                Add( tmp_var );
            }
        }
    }

    void Add( Type value )
    {
        int index = GetListIndexByHash( value );

        if ( local_count == size_of_trash )
        {
            size_of_trash += 16;
            Resize();
        }

        if ( !IsContaint( value ) )
        {
            lists[index].Add( value );
            local_count++;
        }
    }

    bool Next()
    {
        bool isNext = lists[currentList].Next();

        while ( isNext == false )
        {
            currentList++;
            lists[currentList].ToStart();

            if ( currentList >= size_of_trash )
            {
                return false;
            }

            isNext = lists[currentList].Next();
        }

        return isNext;
    }

    Type GetItem()
    {
        return lists[currentList].GetValue();
    }

    void ToStart()
    {
        for ( int i = 0; i < size_of_trash; i++ )
        {
            lists[i].ToStart();
        }
    }

    void Clear()
    {
        for ( int i = 0; i < size_of_trash; i++ )
        {
            lists[i].Clear();
        }
    }

    bool IsContaint( Type value )
    {
        int index = GetListIndexByHash( value );
        return lists[index].IsContaint( value );
    }

private:
    int GetListIndexByHash( Type value )
    {
        return value & ( size_of_trash - 1 );
    }
};
