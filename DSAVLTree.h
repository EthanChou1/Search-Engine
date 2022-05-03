//
// Created by ethan on 3/31/2022.
//

/*  The DSAVLTree class is a custom AVL Tree class.
 *
 *  DSAVLTree.h is used for the definitions and implementations of the class.
 *  The DSAVLNode class is also included in this file and is used aid in the construction of the DSAVLTree
 */

#ifndef SEARCHENGINESANDBOX_DSAVLTREE_H
#define SEARCHENGINESANDBOX_DSAVLTREE_H
#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <iomanip>
using namespace std;

template<class Key, class Value>
class DSAVLNode {
    template<class K, class V> friend class DSAVLTree;
private:
    Key key;
    Value value;
    DSAVLNode<Key, Value>* left;
    DSAVLNode<Key, Value>* right;
    int height;
public:
    DSAVLNode(const Key &key, const Value &value, DSAVLNode* left = nullptr, DSAVLNode* right = nullptr);
    Key& getKey();
    Value& getValue();
};

/**
 * Default constructor for DSAVLNode class
 * @param key key of the node
 * @param value value of the node
 * @param left pointer to the left of the node
 * @param right pointer to the right of the node
 */
template<class Key, class Value>
DSAVLNode<Key, Value>::DSAVLNode(const Key &key, const Value &value, DSAVLNode* left, DSAVLNode* right) {
    this->key = key;
    this->right = right;
    this->left = left;
    this->value = value;
    height = 0;
}

template<class Key, class Value>
Key &DSAVLNode<Key, Value>::getKey() {
    return key;
}

template<class Key, class Value>
Value &DSAVLNode<Key, Value>::getValue() {
    return value;
}
template<class Key, class Value>
class DSAVLTree {
private:
    DSAVLNode<Key, Value>* rootNode;
    DSAVLNode<Key, Value>* copy(DSAVLNode<Key, Value>*& node);
    inline void insert(const Key& key, const Value& value, DSAVLNode<Key, Value>*& node);
    inline void rotateLeftChild(DSAVLNode<Key, Value>*& node);
    inline void doubleLeftChild(DSAVLNode<Key, Value>*& node);
    inline void rotateRightChild(DSAVLNode<Key, Value>*& node);
    inline void doubleRightChild(DSAVLNode<Key, Value>*& node);
    inline void autoBalance(DSAVLNode<Key, Value>*& node);
    inline Value* get(const Key& key, DSAVLNode<Key, Value>*& node);
    int getHeight(DSAVLNode<Key, Value>* node);
    void printInOrder(DSAVLNode<Key, Value>* node);
    void printPreOrder(DSAVLNode<Key, Value>* node);
    void printPostOrder(DSAVLNode<Key, Value>* node);
    void getMostPopularWordsHelp(const DSAVLNode<Key,Value>* node, vector<DSAVLNode<Key, Value>>& vector);

public:
    DSAVLTree(DSAVLNode<Key, Value>* rootNode = nullptr);
    DSAVLTree(DSAVLTree& secondTree);
    ~DSAVLTree();
    void deleteTree(DSAVLNode<Key, Value>*& node);
    bool contains(Key dataType);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    inline void insert(const Key& key, const Value& value);
    inline void insert(const DSAVLNode<Key, Value>*& node);
    Value* get(const Key& dataType);
    void clear();
    vector<DSAVLNode<Key,Value>> getMostPopularWords();

};




/**
 * Default constructor for DSAVL tree class
 * @param node check if node is null--if so, make rootNode nullpointer--if not, call copy method
 */
template<class Key, class Value>
DSAVLTree<Key, Value>::DSAVLTree(DSAVLNode<Key, Value> *node) {
    if(node == nullptr)
    {
        rootNode = nullptr;
        return;
    }
    this->rootNode = copy(node);
}

/**
 * Copy constructor--Generates deep copy of tree in parameter
 * @param secondTree the tree which to make a copy of
 */
template<class Key, class Value>
DSAVLTree<Key, Value>::DSAVLTree(DSAVLTree & secondTree) {
    if(secondTree.rootNode == nullptr)
    {
        rootNode = nullptr;
        return;
    }
    this->rootNode = copy(secondTree.rootNode);
}

//https://interview.hackingnote.com/en/problems/clone-binary-tree
/**
 * Helper method for copy constructor, recursively goes through all nodes of the tree and copies them
 * @param node the node from where to go next
 * @return the next node to copy from
 */
template<class Key, class Value>
DSAVLNode<Key, Value> *DSAVLTree<Key, Value>::copy(DSAVLNode<Key, Value> *&node) {
    if(node == nullptr)
    {
        return nullptr;
    }
    DSAVLNode<Key, Value>*right = copy(node->right);
    DSAVLNode<Key, Value>*left = copy(node->left);
    return new DSAVLNode<Key, Value>(node->key, node->value, left, right);

}

/**
 * Recursively inserts a node into the tree
 * @param key the key of the node to insert
 * @param value the value of the node to insert
 * @param node the actual node to insert
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::insert(const Key &key, const Value &value, DSAVLNode<Key, Value> *&node) {
    if(node == nullptr)
    {
        node = new DSAVLNode<Key, Value>(key, value);
    }
    else if(key > node->key)
    {
        insert(key, value, node->right);
    }
    else if(key < node->key)
    {
        insert(key, value, node->left);
    }
    else;
    autoBalance(node);
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

/**
 * Helper method to insert a node at the root
 * @param key the key of the node to insert
 * @param value the value of the node to insert
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::insert(const Key &key, const Value &value) {
    insert(key, value, rootNode);
}

/**
 * Inserts just a node into the tree
 * @param node the node to insert
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::insert(const DSAVLNode<Key, Value> *&node) {
    insert(node->key, node->value, rootNode);
}

/**
 * Gets the height of a certain node
 * @param node the node of which to check the height
 * @return the height of the node
 */
template<class Key, class Value>
int DSAVLTree<Key, Value>::getHeight(DSAVLNode<Key, Value> *node) {
    if(node == nullptr)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}

/**
 * Covers Case 1 imbalance scenario by rotating the left branch of a node
 * @param node the root of the subtree which needs to be rotated
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::rotateLeftChild(DSAVLNode<Key, Value> *&node) {
    DSAVLNode<Key, Value>* left = node->left;
    node->left = left->right;
    left->right = node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    left->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node = left;
}

/**
 * Covers Case 3 imbalance scenario by rotating the right branch of a node
 * @param node the root of the subtree which needs to be rotated
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::doubleLeftChild(DSAVLNode<Key, Value> *&node) {
    rotateRightChild(node->left);
    rotateLeftChild(node);
}

/**
 * Resolves th Case 2 imbalance scenario by doing Case 1 and then rotating left
 * @param node the root of the subtree which needs to be rotated
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::rotateRightChild(DSAVLNode<Key, Value> *&node) {
    DSAVLNode<Key, Value>* right = node->right;
    node->right = right->left;
    right->left = node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    right->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node = right;
}

/**
 * Resolves the Case 4 imbalance by doing Case 3 and then rotating right
 * @param node
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::doubleRightChild(DSAVLNode<Key, Value> *&node) {
    rotateLeftChild(node->right);
    rotateRightChild(node);
}

//https://stackoverflow.com/questions/24361198/how-to-find-out-if-binary-search-tree-contains-a-node-given-by-user
/**
 * Checks to see if a certain key is within the DSAVLTree
 * @param dataType the key to search for
 * @return whether or not the key exists within the tree
 */
template<class Key, class Value>
bool DSAVLTree<Key, Value>::contains(Key dataType) {
    DSAVLNode<Key, Value>* tempNode = rootNode;
    while(tempNode != nullptr)
    {
        if(tempNode->key < dataType)
        {
            tempNode = tempNode->right;
        }
        else if(tempNode->key > dataType)
        {
            tempNode = tempNode->left;
        }
        else if(tempNode->key == dataType)
        {
            return true;
        }
    }
    return false;
}

/**
 * Recursively searches for and gets a value given a certain key and root node
 * @param key the desired key of the value to search for
 * @param node the root node
 * @return
 */
template<class Key, class Value>
inline Value *DSAVLTree<Key, Value>::get(const Key &key, DSAVLNode<Key, Value>*& node) {
    if(node == nullptr){
        return nullptr;
    }
    if(node->key == key){
        return &node->value;
    }
    if(node->key < key){
        return get(key, node->right);
    }
    else{
        return get(key, node->left);
    }
}

//https://stackoverflow.com/questions/24361198/how-to-find-out-if-binary-search-tree-contains-a-node-given-by-user
/**
 * Recursively searches for a value given a certain key
 * @param dataType the associated key to look for the value of
 * @return the value of the associated key
 */
template<class Key, class Value>
Value* DSAVLTree<Key, Value>::get(const Key& dataType) {
    DSAVLNode<Key, Value> *node = rootNode;
    return get(dataType, node);
}

/**
 * Changes the tree structure to ensure that it remains balanced and is still an AVL Tree
 * @param node the root node of the AVL Tree
 */
template<class Key, class Value>
inline void DSAVLTree<Key, Value>::autoBalance(DSAVLNode<Key, Value>*& node) {
    if(getHeight(node->right) - getHeight(node->left) > 1)
    {
        if(getHeight(node->right->right) >= getHeight(node->right->left))
        {
            rotateRightChild(node);
        }
        else
        {
            doubleRightChild(node);
        }
    }
    else if(getHeight(node->left) - getHeight(node->right) > 1)
    {
        if(getHeight(node->left->left) >= getHeight(node->left->right))
        {
            rotateLeftChild(node);
        }
        else
        {
            doubleLeftChild(node);
        }
    }
}

/**
 * Destructor for DSAVLTree
 */
template<class Key, class Value>
DSAVLTree<Key, Value>::~DSAVLTree() {
    deleteTree(rootNode);
}

/**
 * Deallocates all nodes in the AVL tree with the given root node
 * @param node node from which to start deallocation
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::deleteTree(DSAVLNode<Key, Value> *&node) {
    if(node != nullptr){
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

/**
 * Recursively prints tree in order
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::printInOrder() {
    printInOrder(rootNode);
}

/**
 * Recursively prints tree in order with root node
 * @param node the root node of the tree/subtree being printed
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::printInOrder(DSAVLNode<Key, Value> *node) {
    if(node == nullptr){
        return;
    }
    printInOrder(node->left);
    cout << node->key << endl;
    printInOrder(node->right);
}

/**
 * Recursively prints tree in pre-order format
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::printPreOrder() {
    printPreOrder(rootNode);
}

/**
 * Recursively prints tree in preorder order with root node
 * @param node the root node of the tree/subtree being printed
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::printPreOrder(DSAVLNode<Key, Value> *node) {
    if(node == nullptr){
        return;
    }
    cout << node->key << endl;
    printPreOrder(node->left);
    printPreOrder(node->right);
}

/**
 * Recursively prints tree in post-order format
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::printPostOrder() {
    printPostOrder(rootNode);
}

/**
 * Recursively prints tree in postorder order with root node
 * @param node the root node of the tree/subtree being printed
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::printPostOrder(DSAVLNode<Key, Value> *node) {
    if(node == nullptr){
        return;
    }
    printPostOrder(node->left);
    printPostOrder(node->right);
    cout << node->key << endl;
}

/**
 * Recursively clears all of the node from the AVL Tree
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::clear() {
    deleteTree(rootNode);
    rootNode = nullptr;
}

/**
 * Recursive method for adding nodes to a vector
 * @param node recursive starting point
 * @param vector vector to add words to
 */
template<class Key, class Value>
void DSAVLTree<Key, Value>::getMostPopularWordsHelp(const DSAVLNode<Key, Value> *node, vector<DSAVLNode<Key, Value>>& vector) {
    if(node == nullptr){
        return;
    }
    getMostPopularWordsHelp(node->left, vector);
    vector.push_back(*node);
    getMostPopularWordsHelp(node->right, vector);
}

/**
 * Gets each unique node from the AVL tree
 * @return vector of most popular words
 */
template<class Key, class Value>
vector<DSAVLNode<Key, Value>> DSAVLTree<Key, Value>::getMostPopularWords() {
    vector<DSAVLNode<Key, Value>> vector;
    getMostPopularWordsHelp(rootNode, vector);
    return vector;
}


#endif //SEARCHENGINESANDBOX_DSAVLTREE_H
