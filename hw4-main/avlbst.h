#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
  
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    virtual void insertHelper(const std::pair<const Key, Value>& new_item, AVLNode<Key, Value>* current);
    virtual void rebalance(AVLNode<Key, Value>* node);
    virtual void rotateLeft(AVLNode<Key, Value>* node);
    virtual void rotateRight(AVLNode<Key, Value>* node);


};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item)
{
    if (this->root_ == nullptr) {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    } else {
        insertHelper(new_item, static_cast<AVLNode<Key, Value>*>(this->root_));
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertHelper(const std::pair<const Key, Value>& new_item, AVLNode<Key, Value>* current)
{
    if (current == nullptr) {
        // This should not happen, but if current is null, we cannot proceed
        return;
    }

    if (new_item.first < current->getKey()) {
        if (current->getLeft() == nullptr) {
            current->setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, current));
            current->updateBalance(-1); // Update balance factor (inserted to the left)
        } else {
            insertHelper(new_item, current->getLeft());
        }
    } else if (new_item.first > current->getKey()) {
        if (current->getRight() == nullptr) {
            current->setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, current));
            current->updateBalance(1); // Update balance factor (inserted to the right)
        } else {
            insertHelper(new_item, current->getRight());
        }
    } else {
        // Key already exists, update value
        current->setValue(new_item.second);
        return;
    }

    // Rebalance if necessary
    if(current != nullptr){
      rebalance(current);
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    AVLNode<Key, Value>* target = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    if (target == nullptr) {
        throw KeyError(); // Key not found
    }

    AVLNode<Key, Value>* parent = target->getParent();

    if (target->getLeft() == nullptr && target->getRight() == nullptr) {
        // Case 1: No children
        if (parent == nullptr) {
            // Removing the root node
            this->root_ = nullptr;
        } else if (parent->getLeft() == target) {
            parent->setLeft(nullptr);
            parent->updateBalance(1); // Update balance factor (removed from the left)
        } else {
            parent->setRight(nullptr);
            parent->updateBalance(-1); // Update balance factor (removed from the right)
        }
        delete target;
    } else if (target->getLeft() != nullptr && target->getRight() != nullptr) {
        // Case 2: Two children
        AVLNode<Key, Value>* predecessor = static_cast<AVLNode<Key, Value>*>(this->predecessor(target));
        if(predecessor != nullptr){
          nodeSwap(target, predecessor);
        }
        remove(predecessor->getKey());
    } else {
        // Case 3: One child
        AVLNode<Key, Value>* child = (target->getLeft() != nullptr) ? target->getLeft() : target->getRight();
        if (parent == nullptr) {
            // Removing the root node
            this->root_ = child;
        } else if (parent->getLeft() == target) {
            parent->setLeft(child);
        } else {
            parent->setRight(child);
        }
        child->setParent(parent);
        delete target;
    }

    // Rebalance if necessary
    if (parent != nullptr) {
        if (parent->getLeft() == nullptr) {
            parent->updateBalance(-1); // Update balance factor (removed from the left)
        } else {
            parent->updateBalance(1); // Update balance factor (removed from the right)
        }
        rebalance(parent);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rebalance(AVLNode<Key, Value>* node)
{
    if (node == nullptr) {
        return;
    }

    // Add a null check before accessing balance
    if (node->getBalance() == 0) {
        return; // No rebalancing needed
    }

    int8_t balance = node->getBalance();

    if (balance > 1) {
        // Left heavy
        if (node->getLeft() == nullptr ||(node->getLeft() != nullptr && node->getLeft()->getBalance() >= 0)) {
            // Left-left case
            rotateRight(node);
        } else {
            // Left-right case
            rotateLeft(node->getLeft());
            rotateRight(node);
        }
    } else if (balance < -1) {
        // Right heavy
        if (node->getRight() == nullptr || (node->getRight() != nullptr && node->getRight()->getBalance() <= 0)) {
            // Right-right case
            rotateLeft(node);
        } else {
            // Right-left case
            rotateRight(node->getRight());
            rotateLeft(node);
        }
    }

    // Update balance factors after rotation
    if (node->getLeft() != nullptr) {
        node->getLeft()->updateBalance(node->getLeft()->getBalance() - 1); // Pass difference
    }
    if (node->getRight() != nullptr) {
        node->getRight()->updateBalance(node->getRight()->getBalance() + 1); // Pass difference
    }
    node->updateBalance(0); // Update balance factor after rotation
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node)
{
  if(node != nullptr){
    AVLNode<Key, Value>* pivot = node->getRight();
    if(pivot != nullptr){
      node->setRight(pivot->getLeft());
      
      if(pivot->getLeft() != nullptr){
        pivot->getLeft()->setParent(node);
      }
      
      pivot->setParent(node->getParent());

      if(node->getParent() == nullptr){
        this->root_ = pivot;
      } 
      else if (node == (node->getParent())->getLeft()){
        (node->getParent())->setLeft(pivot);
      }
      else{
        (node->getParent())->setRight(pivot);
      }
      pivot->setLeft(node);
      node->setParent(pivot);
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
  if(node != nullptr){
    AVLNode<Key, Value>* pivot = node->getLeft();
    if (pivot != nullptr) {
        node->setLeft(pivot->getRight());
      
        if (pivot->getRight() != nullptr) {
            pivot->getRight()->setParent(node);
        }
      
        pivot->setParent(node->getParent());

        if (node->getParent() == nullptr) {
            this->root_ = pivot;
        } 
        else if (node == (node->getParent())->getRight()) {
            (node->getParent())->setRight(pivot);
        }
        else {
            (node->getParent())->setLeft(pivot);
        }
      
        pivot->setRight(node);
        node->setParent(pivot);
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
