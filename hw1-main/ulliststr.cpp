#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// Helper function to get the value at a specific location
std::string* ULListStr::getValAtLoc(size_t loc) const {
    // Check if the location is valid
    if (loc >= size_) {
        return nullptr;
    }

    // Iterate through the Items to find the correct location
    Item* currentItem = head_;
    size_t currentIndex = 0;

    while (currentItem != nullptr) {
        size_t currentSize = currentItem->last - currentItem->first;

        // Check if the location is within the current Item's range
        if (loc < currentIndex + currentSize) {
            // Calculate the index within the current Item's array
            size_t indexWithinItem = loc - currentIndex + currentItem->first;
            return &(currentItem->val[indexWithinItem]);
        }
        
        // go to search next index
        currentIndex += currentSize;
        currentItem = currentItem->next;
    }

    return nullptr; // Should not reach here

}

   /**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::push_back(const std::string& val) {
    if (tail_ == nullptr || tail_->last == 10) {
        // Allocate a new Item
        Item* newItem = new Item();
        // set the prev pointer for the new item to old tail
        newItem->prev = tail_;
        // change tail_ according to if the list was empty or not
        if (tail_ == nullptr) {
            head_ = newItem;
        } else {
            tail_->next = newItem;
        }
        tail_ = newItem;
    }

    // Add the value to the back of the list
    tail_->val[tail_->last++] = val;
    size_++;


}

  /**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */

void ULListStr::push_front(const std::string& val) {
    // Create a new node
    if(head_ == nullptr || head_->first == 0){
      Item* newHead = new Item();
      
      // Update values
      newHead->val[newHead->first] = val;
      newHead->last = newHead->first + 1;
      
      // Set new node as the head
      newHead->next = head_;
      if(head_ != nullptr){
        head_->prev = newHead;
      }
      head_ = newHead;
      
      // set tail if the list was empty
      if(tail_ == nullptr){
        tail_ = newHead;
      }
    }
    else{ // if a new node is not needed, simply add in val
      head_->val[head_->first-1] = val;
      head_->first--;
    }
    size_++;
    

}

  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_back() {
    if (size_ == 0) {
        return; // Empty list, nothing to remove
    }

    // Remove the value from the back of the list
    tail_->last--;
    size_--;

    if (tail_->first == tail_->last) {
        // Deallocate the empty Item
        Item* prevItem = tail_->prev;
        delete tail_;
        // set tail according to list size
        tail_ = prevItem;
        if (prevItem != nullptr) {
            prevItem->next = nullptr;
        } else {
            head_ = nullptr;
        }
    }

}

  /**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_front() {
    if (size_ == 0) {
        return; // Empty list, nothing to remove
    }

    // Remove the value from the front of the list
    head_->first++;
    size_--;

    if (head_->first == head_->last) {
        // Deallocate the empty Item
        Item* nextItem = head_->next;
        delete head_;
        head_ = nextItem;
        // set nextItem or tail according to list size
        if (nextItem != nullptr) {
            nextItem->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
    }

}

  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
const std::string& ULListStr::back() const {
    return tail_->val[tail_->last - 1]; // gets location of back element

}

  /**
   * Returns a const reference to the front element
   *   - MUST RUN in O(1)
   */
const std::string& ULListStr::front() const {
    return head_->val[head_->first]; // gets location of front element

}



void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
