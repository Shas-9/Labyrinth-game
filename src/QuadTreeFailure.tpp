// #ifndef STATIC_QUAD_TREE_INCLUDE
// #define STATIC_QUAD_TREE_INCLUDE

// #include "AreaShape.h"
// #include "misc.h"

// #include <memory>
// #include <vector>
// #include <list>
// #include <array>
// #include <string>
// #include <fstream> 

// #define MAX_QUAD_TREE_DEPTH 10

// template <typename EL_TYPE>
// struct Element {
//   EL_TYPE element_data;
//   int next_element_index;
//   int prev_element_index;
// };

// template <typename EL_TYPE>
// class FreeList {
// private:
//   std::vector<Element<EL_TYPE>> data;
//   int free_head = -1;
// public:
//   int insert(Element<EL_TYPE> element) {
//     if (this->free_head == -1) {
//       this->data.push_back(element);
//       return this->data.size() - 1;
//     }
//   }
//   void remove(int element_index) {
    
//   }
//   auto operator[](size_t index) const { return this->data[index]; }
//   auto operator[](size_t index) { return this->data[index]; }
// };

// template <typename OBJECT_TYPE, typename AREA_TYPE>
// class QuadTree {
// protected:
//   size_t depth = 0;

//   AreaRect rect_area;
//   std::array<AreaRect, 4> child_areas{};
//   std::array<std::shared_ptr<QuadTree<OBJECT_TYPE, AREA_TYPE>>, 4> child_trees{};
//   // std::list<std::pair<AREA_TYPE, OBJECT_TYPE>> tree_container;
//   int first_element_index;


// public:
//   FreeList<std::pair<AREA_TYPE, OBJECT_TYPE>>* free_list_ptr;

//   QuadTree(const AreaRect& size = { {0.0, 0.0}, {100.0, 100.0} }, const size_t depth = 0, const FreeList<std::pair<AREA_TYPE, OBJECT_TYPE>>* free_list_ptr = nullptr) {
//     this->depth = depth;
//     this->resize(size);
//     first_element_index = -1;
//   }

//   void resize(const AreaRect& resize_area) {
//     this->clear();
//     this->rect_area = resize_area;
//     Vector child_size = Vector(this->rect_area.size.x / 2, this->rect_area.size.y / 2);

//     this->child_areas = {
//       // top left
//       AreaRect(this->rect_area.pos, child_size),
//       // top right
//       AreaRect(Vector(this->rect_area.pos.x + child_size.x, this->rect_area.pos.y), child_size),
//       // bottom left
//       AreaRect(Vector(this->rect_area.pos.x, this->rect_area.pos.y + child_size.y), child_size),
//       // bottom right
//       AreaRect(Vector(this->rect_area.pos.x + child_size.x, this->rect_area.pos.y + child_size.y), child_size),
//     };
//   }

//   // void clear() {
//   //   this->tree_container.clear();
//   //   for (int i = 0; i < 4; i++) {
//   //     if (this->child_trees[i]) this->child_trees[i]->clear();
//   //     this->child_trees[i] = 0;
//   //   }
//   // }

//   // size_t size() const {
//   //   size_t count = this->tree_container.size();
//   //   for (int i = 0; i < 4; i++) {
//   //     if (this->child_trees[i]) count += this->child_trees[i]->size();
//   //   }
//   //   return count;
//   // }

//   // returns the element index
//   int insert(const OBJECT_TYPE& item, const AREA_TYPE& item_size) {
//     for (int i = 0; i < 4; i++) {
//       if (this->child_areas[i].contains(item_size)) {
//         if (this->depth <= MAX_QUAD_TREE_DEPTH) {
//           if (!this->child_trees[i]) {
//             this->child_trees[i] = std::make_shared<QuadTree<OBJECT_TYPE, AREA_TYPE>>(this->child_areas[i], this->depth + 1, this->free_list_ptr);
//           }
//           return this->child_trees[i]->insert(item, item_size);
//         }
//       }
//     }

//     // create the new element to be inserted
//     Element<std::pair<AREA_TYPE, OBJECT_TYPE>> el = { {item_size, item}, first_element_index, -1 };
//     // insert the element into the free list, pointing towards the previous first_element_index
//     int element_index = this->free_list_ptr->insert(el);
//     // update the prev_element_index  of the old first_element to point to the one we just inserted
//     (*this->free_list_ptr)[this->first_element_index].prev_element_index = element_index;
//     // update the first_element_index to the element we just inserted index
//     this->first_element_index = element_index;

//     return element_index;
//   }

//   std::list<OBJECT_TYPE> search(const AreaRect& search_area) const {
//     std::list<OBJECT_TYPE> items_list;
//     this->search(search_area, items_list);
//     return items_list;
//   }

//   std::list<OBJECT_TYPE> search(const AreaCirc& search_area) const {
//     std::list<OBJECT_TYPE> items_list;
//     this->search(search_area, items_list);
//     return items_list;
//   }

//   void search(const AreaRect& search_area, std::list<OBJECT_TYPE>& items_list) const {
//     for (int el_index = this->first_element_index; el_index != -1; el_index = (*this->free_list_ptr)[el_index].next_element_index) {
//       Element<std::pair<AREA_TYPE, OBJECT_TYPE>> el = (*this->free_list_ptr)[el_index];
//       if (search_area.overlap(el.element_data.first)) items_list.push_back(el.element_data.second);
//     }
//     // for (const auto& p : this->tree_container) {
//     //   if (search_area.overlap(p.first)) {
//     //     items_list.push_back(p.second);
//     //   }
//     // }

//     for (int i = 0; i < 4; i++) {
//       if (this->child_trees[i]) {
//         if (search_area.contains(this->child_areas[i])) this->child_trees[i]->items(items_list);
//         else if (search_area.overlap(this->child_areas[i])) this->child_trees[i]->search(search_area, items_list);
//       }
//     }
//   }

//   void search(const AreaCirc& search_area, std::list<OBJECT_TYPE>& items_list) const {
//     for (int el_index = this->first_element_index; el_index != -1; el_index = (*this->free_list_ptr)[el_index].next_element_index) {
//       Element<std::pair<AREA_TYPE, OBJECT_TYPE>> el = (*this->free_list_ptr)[el_index];
//       if (search_area.overlap(el.element_data.first)) items_list.push_back(el.element_data.second);
//     }
//     for (const auto& p : this->tree_container) {
//       if (search_area.overlap(p.first)) {
//         items_list.push_back(p.second);
//       }
//     }

//     for (int i = 0; i < 4; i++) {
//       if (this->child_trees[i]) {
//         if (search_area.contains(this->child_areas[i])) this->child_trees[i]->items(items_list);
//         else if (search_area.overlap(this->child_areas[i])) this->child_trees[i]->search(search_area, items_list);
//       }
//     }
//   }

//   void items(std::list<OBJECT_TYPE>& items_list) const {
//     for (const auto& p : this->tree_container) items_list.push_back(p.second);
//     for (int i = 0; i < 4; i++) if (this->child_trees[i]) this->child_trees[i]->items(items_list);
//   }

//   const AreaRect& area() { return this->rect_area; }
// };

// template <typename T, typename A>
// struct QuadTreeItem {
//   T item;
//   int item_index;
// };

// template <typename OBJECT_TYPE, typename AREA_TYPE>
// class QuadTreeContainer {
//   using QuadTreeContainerList = std::list<QuadTreeItem<OBJECT_TYPE, AREA_TYPE>>;

// protected:
//   QuadTreeContainerList all_items;
//   QuadTree<typename QuadTreeContainerList::iterator, AREA_TYPE> root;

// public:
//   FreeList<std::pair<AREA_TYPE, typename QuadTreeContainerList::iterator>>* free_list_ptr;

//   QuadTreeContainer(const AreaRect& size = { {0.0, 0.0}, {100.0, 100.0} }, const size_t depth = 0) {
//     this->free_list_ptr = std::make_shared<FreeList<std::pair<AREA_TYPE, typename QuadTreeContainerList::iterator>>>();
//     this->root.free_list_ptr = this->free_list_ptr;
//   }

//   void resize(const AreaRect& resize_area) {
//     this->root.resize(resize_area);
//   }

//   size_t size() const {
//     return this->all_items.size();
//   }

//   void clear() {
//     this->root.clear();
//     this->all_items.clear();
//   }

//   typename QuadTreeContainerList::iterator begin() { return this->all_items.begin(); }
//   typename QuadTreeContainerList::iterator end() { return this->all_items.end(); }
//   typename QuadTreeContainerList::iterator cbegin() { return this->all_items.cbegin(); }
//   typename QuadTreeContainerList::iterator cend() { return this->all_items.cend(); }

//   void insert(const OBJECT_TYPE& item, const AREA_TYPE& item_size) {
//     QuadTreeItem<OBJECT_TYPE, AREA_TYPE> new_item;
//     new_item.item = item;

//     this->all_items.push_back(new_item);
//     this->all_items.back().item_index = this->root.insert(std::prev(this->all_items.end()), item_size);
//   }

//   std::list<int> search(const AreaRect& search_area) const {
//     std::list<int> item_indices_list;
//     this->root.search(search_area, item_indices_list);
//     return item_indices_list;
//   }

//   std::list<int> search(const AreaCirc& search_area) const {
//     std::list<int> item_indices_list;
//     this->root.search(search_area, item_indices_list);
//     return item_indices_list;
//   }

//   void remove(int item_index) {
//     // iterator points to a quadtree item
//     // item->item_ptr.container->erase(item->item_ptr.iterator);
//     this->free_list_ptr->remove(item_index);
//     // this->all_items.erase(item);
//   }

//   void relocate(typename QuadTreeContainerList::iterator& item, const AREA_TYPE& new_rect) {
//     item->item_ptr.container->erase(item->item_ptr.iterator);
//     item->item_ptr = this->root.insert(item, new_rect);
//   }
// };


// #endif