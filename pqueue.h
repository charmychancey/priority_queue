#ifndef PQUEUE_H_
#define PQUEUE_H_

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
#include <utility>

template <typename T, typename C = std::less<T>>
class PQueue {
 public:
  PQueue() {}
  // ret num items in pqueue
  size_t Size();
  // ret top of pqueue
  T& Top();
  // Remove top of pqueue
  void Pop();
  // Insert <item> and sort pqueue
  void Push(const T &item);

 private:
  std::vector<T> items;
  size_t cur_size = 0;
  C cmp;

  // Helper methods for indices
  size_t Root() {
    return 0;
  }
  size_t Parent(size_t n) {
    return (n - 1) / 2;
  }
  size_t LeftChild(size_t n) {
    return 2 * n + 1;
  }
  size_t RightChild(size_t n) {
    return 2 * n + 2;
  }

  // Helper methods for node testing
  bool HasParent(size_t n) {
    return n != Root();
  }
  bool IsNode(size_t n) {
    return n < cur_size;
  }

  // Helper methods for restructuring
  void PercolateUp(size_t n);
  void PercolateDown(size_t n);

  // Node comparison
  bool CompareNodes(size_t i, size_t j);
};

template<typename T, typename C>
bool PQueue<T, C>::CompareNodes(size_t i, size_t j) {
  return cmp(items[i], items[j]);
}

template<typename T, typename C>
void PQueue<T, C>::PercolateUp(size_t n) {
  // like: items[Parent(n)] > items[n]
  while (HasParent(n) && CompareNodes(n, Parent(n))) {
    std::swap(items[Parent(n)], items[n]);
    n = Parent(n);
  }
}
template<typename T, typename C>
void PQueue<T, C>::PercolateDown(size_t n) {
  // While node has at least one child (if one, necessarily on the left)
  while (IsNode(LeftChild(n))) {
    // Consider l_child by default
    size_t child = LeftChild(n);
    // If r_child exists and <C> than l_child, consider r_child
    // like: items[RightChild(n)] < items[LeftChild(n)]
    if (IsNode(RightChild(n)) && CompareNodes(RightChild(n), LeftChild(n)))
      child = RightChild(n);

    // Exchange <C> child w/ node to restore heap-order if needed
    // like: items[child] < items[n]
    if (CompareNodes(child, n))
      std::swap(items[child], items[n]);
    else
      break;
    // Do it again, one level down
    n = child;
  }
}

template<typename T, typename C>
size_t PQueue<T, C>::Size() {
  return cur_size;
}

template<typename T, typename C>
T& PQueue<T, C>::Top() {
  if (!Size())
    throw std::underflow_error("Empty priority queue!");
  return items[Root()];
}

template<typename T, typename C>
void PQueue<T, C>::Pop() {
  if (!Size())
    throw std::underflow_error("Empty priority queue!");
  // Move last item back to root and reduce heap's size
  // like: items[Root()] = std::move(items[cur_size--]);
  items[Root()] = std::move(items[cur_size-1]);
  items.pop_back();
  PercolateDown(Root());
  cur_size--;  // tracks num_elements
}

template<typename T, typename C>
void PQueue<T, C>::Push(const T &item) {
  if (cur_size == items.size() - 1)
    throw std::overflow_error("Priority queue full!");
  // Insert at the end
  // like: items[++cur_size] = std::move(item);
  items.push_back(item);
  // Percolate up
  PercolateUp(cur_size);
  cur_size++;  // tracks num_elements
}

#endif  // PQUEUE_H_
