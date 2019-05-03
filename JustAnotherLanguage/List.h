#pragma once

#include <exception>

class ListNotInitializedException : public std::exception 
{
public:
    virtual const char* what() const noexcept
    {
        return "Not initialized iterator for list";
    }
};

class ListNullreferenceException : public std::exception
{
    public:
    virtual const char* what() const noexcept
    {
        return "Null reference pointer in iterator for list";
    }
};

template<typename Type>
class List
{
private:

    struct ListItem
    {
        Type value;
        ListItem *next;

        ListItem() = default;

        ListItem ( Type _value )
            : value( _value ), next( nullptr )
        {}

        ListItem ( const ListItem &item )
            : value( item.value ), next( item.next )
        {}
    };

private:
    ListItem *root;
    ListItem *iter;
    bool isStarted;

public:
    List()
    {
        root = nullptr;
        iter = nullptr;

        isStarted = false;
    }

    ~List ()
    {
        Clear();
    }

    void Add( Type value )
    {
        if ( root == nullptr )
        {
            root = new ListItem( value );
            return;
        }

        ListItem *current = root;
        while ( current != nullptr )
        {
            if ( current->next == nullptr )
            {
                current->next = new ListItem( value );
                return;
            }

            current = current->next;
        }
    }

    void ToStart()
    {
        this->iter = root;
        this->isStarted = true;
    }

    bool Next()
    {
        if ( root == nullptr )
        {
            return false;
        }

        if ( isStarted == false )
        {
            ToStart();
            return true;
        }

        if ( iter == nullptr )
        {
            return false;
        }

        iter = iter->next;
        return true;
    }

    Type GetValue ()
    {
        if ( isStarted == false )
        {
            throw ListNotInitializedException();
        }

        if ( iter == nullptr )
        {
            throw ListNullreferenceException();
        }

        return iter->value;
    }

    void Clear()
    {
        ListItem *current = root;
        ListItem *toDelete = nullptr;

        while ( current != nullptr )
        {
            toDelete = current;
            current = current->next;

            delete toDelete;
        }
    }
};
