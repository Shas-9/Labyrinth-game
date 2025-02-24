#include <stdint.h>

#include <vector>

// Represents a node in the quadtree.
struct QuadNode {
  // Points to the first child if this node is a branch or the first
  // element if this node is a leaf.
  int32_t first_child;

  // Stores the number of elements in the leaf or -1 if it this node is
  // not a leaf.
  int32_t count;
};

// Represents an element in the quadtree.
struct QuadElt {
    // Stores the ID for the element (can be used to
    // refer to external data).
    int id;

    // Stores the rectangle for the element.
    int x1, y1, x2, y2;
};

// Represents an element node in the quadtree.
struct QuadEltNode {
    // Points to the next element in the leaf node. A value of -1 
    // indicates the end of the list.
    int next;

    // Stores the element index.
    int element;
};

template <typename EL_TYPE>
struct Element {
  EL_TYPE element_data;
  int next_element_index;
  int prev_element_index;
};

template <typename EL_TYPE>
class FreeList {
private:
  std::vector<Element<EL_TYPE>> data;
  int free_head = -1;
public:
  int insert(Element<EL_TYPE> element) {
    if (this->free_head == -1) {
      this->data.push_back(element);
      return this->data.size() - 1;
    }
  }
  void remove(int element_index) {
    
  }
  auto operator[](size_t index) const { return this->data[index]; }
  auto operator[](size_t index) { return this->data[index]; }
};

class Quadtree {
private:
  FreeList<QuadElt> elts;
  FreeList<QuadEltNode> elts_nodes;
  std::vector<QuadNode> nodes;
  int free_node;
  
public:
  int insert() {

  };
  void cleanup();
  void remove();
};