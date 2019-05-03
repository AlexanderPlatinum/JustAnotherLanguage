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

    struct Item
    {
        Type value;
        Item *next;

        Item ( Type value )
        {
            this->value = value;
            this->next = nullptr;
        }
    };

private:
    Item *root;
    Item *iter;
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
            root = new Item( value );
            return;
        }

        Item *current = root;
        while ( current != nullptr )
        {
            if ( current->next == nullptr )
            {
                current->next = new Item( value );
                return;
            }

            current = current->next;
        }
    }

    void ToStart()
    {
        iter = root;
        isStarted = true;
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
        Item *current = root;
        Item *toDelete = nullptr;

        while ( current != nullptr )
        {
            toDelete = current;
            current = current->next;

            delete toDelete;
        }
    }
};
