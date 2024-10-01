#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * Construct a new Heap object
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * Push an item to the heap
   */
  void push(const T& item);

  /**
   * Returns the top (priority) item
   */
  T const & top() const;

  /**
   * Remove the top priority item
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * Returns size of the heap
   * 
   */
  size_t size() const;

private:
    // Data members
    std::vector<T> elements;
    PComparator comp;
    int m;

    // Helper functions
    void heapifyUp(int index);
    void heapifyDown(int index);

};

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
    : elements(), comp(c), m(m) {}

// Destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

// Push an item to the heap
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
    // add new item to end of vector and restore the heap property
    elements.push_back(item);
    heapifyUp(elements.size() - 1);
}

// Returns the top (priority) item
template <typename T, typename PComparator>
T const & Heap<T, PComparator>::top() const {
    // Check if the heap is empty before accessing the top element
    if (empty()) {
        throw std::underflow_error("Heap underflow");
    }
    return elements.front();
}

// Remove the top priority item
template <typename T, typename PComparator>
void Heap<T, PComparator>::pop() {
    // Check if the heap is empty before attempting to pop
    if (empty()) {
        throw std::underflow_error("Heap underflow");
    }

    // Swap the top and last elements, then remove the last element and restore heap property
    std::swap(elements.front(), elements.back());
    elements.pop_back();
    heapifyDown(0);
}

// Returns true if the heap is empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
    return elements.empty();
}

// Returns size of the heap
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
    return elements.size();
}

// heapify up to maintain heap property
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyUp(int index) {
    // Calculate the parent index in a m-ary heap
    int parent = (index - 1) / m;

    // Move up the heap until the heap property is restored
    while (index > 0 && comp(elements[index], elements[parent])) {
        // swap current element with parent and update indices
        std::swap(elements[index], elements[parent]);
        index = parent;
        parent = (index - 1) / m;
    }
}

// heapify down to maintain heap property
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyDown(int index) {
    // Calculate the index of the first child in a m-ary heap    
    int child = m * index + 1;

    // Move down the heap until the heap property is restored
    while (child < elements.size()) {
        int minChild = child;

        // Find the minimum child among all children
        for (size_t i = 1; i < m && i + child < elements.size(); ++i) {
            if (comp(elements[child + i], elements[minChild])) {
                minChild = child + i;
            }
        }
        // Swap with the minimum child if it violates the heap property, and update indices
        if (comp(elements[minChild], elements[index])) {
            std::swap(elements[index], elements[minChild]);
            index = minChild;
            child = m * index + 1;
        } else {
            // Break the loop if the heap property is not violated
            break;
        }
    }
}




#endif

