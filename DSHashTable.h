//
// Created by txsiddharth on 3/31/2022.
//

/*  The DSHashTable class is a custom Hash Table class.
 *
 *  DSHashTable.h is used for the definitions and implementations of the class.
 *  Source: https://medium.com/@raunit_x/lets-implement-a-hashmap-in-c-48d49266125f
 *  The DSHashNode class is also included in this file and is used aid in the construction of the DSHashTable
 */


#ifndef SEARCHENGINESANDBOX_DSHASHTABLE_H
#define SEARCHENGINESANDBOX_DSHASHTABLE_H
#include <string>
#include <iostream>
#pragma once
using namespace std;



template<typename V>
class DSHashNode {
    template<typename T> friend class DSHashTable;
private:
    string key;
    V value;
    DSHashNode * next;
public:
    /**
     * Constructor for DSHashNode
     * @param key node key
     * @param value node value
     */
    DSHashNode(string key, V value) : key(key), value(value), next(nullptr) {}

    /**
     * Recursive destructor for DSHashNode
     */
    ~DSHashNode()
    {
        delete next;
    }
};

template<typename V>
class DSHashTable
{
private:
    DSHashNode<V> ** table;
    int size;
    int capacity;
    int hashFunc(string key);
    void resize();
public:
    DSHashTable();
    ~DSHashTable();
    int getSize();
    int getCapacity();
    V* search(string& key);
    void insert(string key, V value);
    V remove(string key);
    void clear();
};

/**
 * Hash function for the HashTable
 * @param key key to hash
 * @return hashing index for the given key
 */
template<typename V>
int DSHashTable<V>::hashFunc(string key)
{
    int hashcode = 0;
    int currCoeff = 1;
    for (int i = int(key.size()) - 1; i >= 0; i--)
    {
        hashcode += ((key[i]) * (currCoeff)) % capacity;
        currCoeff *= 29;
        currCoeff = currCoeff % capacity;
    }
    return hashcode % capacity;
}

/**
 * Method to double the hashtable capacity if load factor is above 0.75
 */
template<typename V>
void DSHashTable<V>::resize()
{
    DSHashNode<V> ** temp = table;
    int newCapacity = capacity * 2;
    table = new DSHashNode<V>*[newCapacity];
    for (int i = 0; i < newCapacity ; i++)
    {
        table[i] = nullptr;
    }
    int oldCapacity = capacity;
    capacity = newCapacity;
    size = 0;

    for(int i = 0; i < oldCapacity; i++)
    {
        DSHashNode<V> * head = temp[i];
        while (head) {
            string key = head -> key;
            V value = head -> value;
            insert(key, value);
            head = head -> next;
        }
    }
    for (int i = 0; i < oldCapacity; i++)
    {
        delete temp[i];
    }
    delete []temp;
}

/**
 * Default constructor
 */
template<typename V>
DSHashTable<V>::DSHashTable()
{
    size = 0;
    capacity = 50000;
    table = new DSHashNode<V>*[capacity];
    for (int i = 0; i < capacity; i++)
        table[i] = nullptr;
}

/**
 * Destructor
 */
template<typename V>
DSHashTable<V>::~DSHashTable()
{
    for (int i = 0; i < capacity; i++)
    {
        delete table[i];
    }
    delete []table;
}

/**
 * Method to check the current size of the hashtable
 * @return size of hashtable
 */
template<typename V>
int DSHashTable<V>::getSize()
{
    return size;
}

/**
 * Method to check the current "carrying capacity" of the hashtable
 * @return capacity of the hashtable
 */
template<typename V>
int DSHashTable<V>::getCapacity()
{
    return capacity;
}

/**
 * Search for a given key within the hashtable
 * @param key key to search for
 * @return associated value of the key (if it exists)
 */
template<typename V>
V* DSHashTable<V>::search(string& key)
{
    int hashIndex = hashFunc(key);
    DSHashNode<V> * head = table[hashIndex];
    while (head != nullptr)
    {
        if (head -> key == key)
        {
            return &head -> value;
        }
        head = head -> next;
    }
    return nullptr;
}

/**
 * Insert a key, value pair into the hashtable
 * @param key key to insert
 * @param value value to insert
 */
template<typename V>
void DSHashTable<V>::insert(string key, V value)
{
    int hashIndex = hashFunc(key);
    DSHashNode<V> * head = table[hashIndex];

    while (head != nullptr)
    {
        if (head -> key == key)
        {
            head -> value = value;
            return;
        }
        head = head -> next;
    }

    head = table[hashIndex];
    DSHashNode<V> * newNode = new DSHashNode<V>(key, value);
    newNode -> next = head;
    table[hashIndex] = newNode;
    size++;

    double loadFactor = ((double)size) / ((double)capacity);;
    if (loadFactor > 0.75)
    {
        resize();
    }
}

/**
 * Delete a key, value pair from the hashtable
 * @param key the key to delete
 * @return the value of the deleted pair
 */
template<typename V>
V DSHashTable<V>::remove(string key)
{
    int hashIndex = hashFunc(key);
    DSHashNode<V> * head = table[hashIndex];
    if (head -> key == key)
    {
        V value = head -> value;
        table[hashIndex] = head -> next;
        head -> next = nullptr;
        delete head;
        size--;
        return value;
    }

    DSHashNode<V> * prev = nullptr;
    while (head != nullptr)
    {
        if (head -> key == key)
        {
            V value = head -> value;
            prev -> next = head -> next;
            head -> next = nullptr;
            delete head;
            size--;
            return value;
        }
        prev = head;
        head = head -> next;
    }

    return 0;
}

/**
 * Clears the entire table, but does not deallocate it
 */
template<typename V>
void DSHashTable<V>::clear() {
    for (int i = 0; i < capacity; i++)
    {
        table[i] = nullptr;
    }
}


#endif //SEARCHENGINESANDBOX_DSHASHTABLE_H
