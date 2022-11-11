#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  //bool empty() const;

  bool empty() const {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  //int size() const;

  int size() const {
    return s;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  //T & front();

  T & front() {
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  //T & back();

  T & back() {
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  //void push_front(const T &datum);

  void push_front(const T &datum) {
    Node *plus = new Node;
    plus->datum = datum;
    if (empty()) {
      plus->prev = nullptr;
      plus->next = nullptr;
      first = plus;
      last = plus;
      s++;
    }
    else if (s == 1) {
      plus->next = first;
      first->prev = plus;
      last = first;
      first = plus;
      plus->prev = nullptr;
      s++;
    }
    else {
      plus->next = first;
      first->prev = plus;
      first = plus;
      plus->prev = nullptr;
      s++;
    } 
  }

  //EFFECTS:  inserts datum into the back of the list
  //void push_back(const T &datum);

  void push_back(const T &datum) {
    Node *backPlus = new Node;
    backPlus->datum = datum;
    if (empty()) {
      backPlus->prev = nullptr;
      backPlus->next = nullptr;
      first = backPlus;
      last = backPlus;
      s++;
    }
    else if (s == 1) {
      backPlus->next = nullptr;
      backPlus->prev = last;
      last->next = backPlus;
      first = last;
      last = backPlus;
      s++;
    }
    else {
      backPlus->next = nullptr;
      backPlus->prev = last;
      last->next = backPlus;
      last = backPlus;
      s++;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  //void pop_front();

  void pop_front() {
    assert(!empty());
    if (s == 1) {
      Node *fir = first;
      delete fir;
      first = nullptr;
      last = nullptr;
      s--;
    }
    else if (s == 2) {
      Node *fir = first;
      first = first->next;
      first->prev = nullptr;
      last = first;
      delete fir;
      s--;
    }
    else {
      Node *fir = first;
      first = first->next;
      first->prev = nullptr;
      delete fir;
      s--;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  //void pop_back();

  void pop_back() {
    if (s == 1) {
      Node *fin = last;
      first = nullptr;
      last = nullptr;
      delete fin;
      s--;
    }
    else if (s == 2) {
      Node *fin = last;
      last = last->prev;
      last->next = nullptr;
      first = last;
      delete fin;
      s--;
    }
    else {
      Node *fin = last;
      last = last->prev;
      last->next = nullptr;
      delete fin;
      s--;
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  //void clear();

  void clear() {
    while(s != 0) {
      pop_front();
    }
    first = nullptr;
    last = nullptr;
  }

  List(): first(nullptr), last(nullptr), s(0) {}

  List(const List &separate): first(nullptr), last(nullptr), s(0) {
    copy_all(separate);
  }

  List &operator=(const List &separate) {
    if (this == &separate) {
      return *this;
    }
    clear();
    copy_all(separate);
    return *this;
  }

  ~List() {
    clear();
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  //void copy_all(const List<T> &other);

  void copy_all(const List<T> &other) {
      for(Node *i = other.first; i != nullptr; i = i->next){
          this->push_back(i->datum);
      }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int s;

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T& operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    Iterator(): node_ptr(nullptr){}

    bool operator==(Iterator check) const {
      return node_ptr == check.node_ptr;
    }

    bool operator!=(Iterator check) const {
      return node_ptr != check.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p): node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  //Iterator end() const;

  Iterator end() const {
    return Iterator();
  }

   //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  //void erase(Iterator i);

  void erase(Iterator i) {
    if(!i.node.ptr->next && !i.node.ptr->prev){ //next and prev node is there
      (i.node_ptr->next)->prev = i.node_ptr->prev; //repoint next node's previous arrow
      (i.node_ptr->prev)->next = i.node_ptr->next; //repoint prev node's next arrow
    }
    else if(!i.node.ptr->next){ //no prev node but next is there
      (i.node_ptr->next)->prev = nullptr;
    }
    else if(!i.node.ptr->prev){ //no next node but prev is there
      (i.node_ptr->prev)->next = nullptr;
    }
    delete i.node_ptr;
    s--;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  //void insert(Iterator i, const T &datum);

  void insert(Iterator i, const T &datum) { //use pop front/back push front/back for edge cases (size check)
    Node *newNode = new Node;
    newNode->next = i.node_ptr->next;
    newNode->prev = i.node_ptr->prev;
    newNode->datum = datum;
    (i.node_ptr->next)->prev = i.node_ptr->prev;
    (i.node_ptr->prev)->next = i.node_ptr->next;
    s++;
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.




#endif // Do not remove this. Write all your code above this line.
