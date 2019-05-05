#pragma once

#include "List.h"

template < typename Type >
class HashSet
{
private:
    static const int MAX_COUNT_HASH_SET = 16;
    List <Type> lists[MAX_COUNT_HASH_SET];

    int currentList = 0;

public:
    HashSet() = default;
    ~HashSet() = default;

    void Add( Type value )
    {
        int index = GetListIndexByHash( value );
        lists[index].Add( value );
    }

    bool Next()
    {
        bool isNext = lists[currentList].Next();

        while ( isNext == false )
        {
            currentList++;
            lists[currentList].ToStart();

            if ( currentList >= MAX_COUNT_HASH_SET )
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
        for ( int i = 0; i < MAX_COUNT_HASH_SET; i++ )
        {
            lists[i].ToStart();
        }
    }

    void Clear()
    {
        for ( int i = 0; i < MAX_COUNT_HASH_SET; i++ )
        {
            lists[i].Clear();
        }
    }

private:
    int GetListIndexByHash( Type value )
    {
        return value & 15;
    }
};
