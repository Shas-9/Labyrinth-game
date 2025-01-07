#ifndef STATIC_QUAD_TREE_INCLUDE
#define STATIC_QUAD_TREE_INCLUDE

#include "Vector.h"
#include <vector>
#include <list>
#include <array>
#include <string>

#include <iostream>
#include <fstream> 

struct AreaRect {
  AreaRect() {
    this->pos = Vector(0, 0);
    this->size = Vector(1, 1);
  }
  AreaRect(double x, double y, double w, double h) {
    this->pos = Vector(x, y);
    this->size = Vector(w, h);
  }
  AreaRect(Vector pos, Vector size) {
    this->pos = pos;
    this->size = size;
  }
  bool contains(const AreaRect& rect) const {
    // bool x_axis = this->pos.x < rect.pos.x && this->pos.x + this->size.x > rect.pos.x + rect.size.x;
    // bool y_axis = this->pos.y < rect.pos.y && this->pos.y + this->size.y > rect.pos.y + rect.size.y;
    // return x_axis && y_axis;
    return (rect.pos.x >= pos.x) && (rect.pos.x + rect.size.x < pos.x + size.x) &&
				(rect.pos.y >= pos.y) && (rect.pos.y + rect.size.y < pos.y + size.y);
  }
  bool overlap(const AreaRect& rect) const {
    // bool A_above_B = rect.pos.y >= this->pos.y + this->size.y;
    // bool A_below_B = rect.pos.y + rect.size.y <= this->pos.y;
    // bool A_right_of_B = rect.pos.x + rect.size.x <= this->pos.x;
    // bool A_left_of_B = rect.pos.x >= this->pos.x + this->size.x;

    // bool notColliding = A_above_B || A_below_B || A_right_of_B || A_left_of_B;
    
    // return !notColliding;

    return pos.x < rect.pos.x + rect.size.x && pos.x + size.x >= rect.pos.x && pos.y < rect.pos.y + rect.size.y && pos.y + size.y >= rect.pos.y;
  }
  // top left coords
  Vector pos;
  // Width and height
  Vector size;
};

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

#define MAX_QUAD_TREE_DEPTH 10

template <typename OBJECT_TYPE>
class StaticQuadTree {
protected:
  size_t depth = 0;

  AreaRect rect_area;
  std::array<AreaRect, 4> child_areas{};
  std::array<std::shared_ptr<StaticQuadTree<OBJECT_TYPE>>, 4> child_trees{};
  std::vector<std::pair<AreaRect, OBJECT_TYPE>> tree_container;
  std::string id;

public:
  StaticQuadTree(const AreaRect& size = {{0.0, 0.0}, {100.0, 100.0}}, const size_t depth = 0) {
    this->depth = depth;
    this->resize(size);
    this->id = gen_random(5);
  }

  void resize(const AreaRect& resize_area) {
    this->clear();
    this->rect_area = resize_area;
    Vector child_size = Vector(this->rect_area.size.x/2, this->rect_area.size.y/2);

    this->child_areas = {
      // top left
      AreaRect(this->rect_area.pos, child_size),
      // top right
      AreaRect(Vector(this->rect_area.pos.x + child_size.x, this->rect_area.pos.y), child_size),
      // bottom left
      AreaRect(Vector(this->rect_area.pos.x, this->rect_area.pos.y + child_size.y), child_size),
      // bottom right
      AreaRect(Vector(this->rect_area.pos.x + child_size.x, this->rect_area.pos.y + child_size.y), child_size),
    };
  }
  
  void clear() {
    this->tree_container.clear();
    for (int i = 0; i < 4; i++) {
      if (this->child_trees[i]) this->child_trees[i]->clear();
      this->child_trees[i] = 0;
    }
  }

  size_t size() const {
    size_t count = this->tree_container.size();
    for (int i = 0; i < 4; i++) {
      if (this->child_trees[i]) count += this->child_trees[i]->size();
    }
    return count;
  }

  void insert(const OBJECT_TYPE& item, const AreaRect& item_size) {
    for (int i = 0; i < 4; i++) {
      if (this->child_areas[i].contains(item_size)) {
        if (this->depth + 1 < MAX_QUAD_TREE_DEPTH) {
          if (!this->child_trees[i]) {
            this->child_trees[i] = std::make_shared<StaticQuadTree<OBJECT_TYPE>>(this->child_areas[i], this->depth + 1);
          }
          this->child_trees[i]->insert(item, item_size);
          return;
        }
      }
    }

    this->tree_container.push_back({ item_size, item });
  }

  std::list<OBJECT_TYPE> search(const AreaRect& search_area) const {
    std::list<OBJECT_TYPE> items_list;
    this->search(search_area, items_list);
    return items_list;
  }

  void search(const AreaRect& search_area, std::list<OBJECT_TYPE>& items_list) const {
    for (const auto& p : this->tree_container) {
      if (search_area.overlap(p.first)) {
        items_list.push_back(p.second);
      }
    }
    
    for (int i = 0; i < 4; i++) {
      if (this->child_trees[i]) {
        if (search_area.contains(this->child_areas[i])) this->child_trees[i]->items(items_list);
        else if (search_area.overlap(this->child_areas[i])) this->child_trees[i]->search(search_area, items_list);
      }
    }
  }

  void items(std::list<OBJECT_TYPE>& items_list) const {
    for (const auto& p : this->tree_container) items_list.push_back(p.second);
    for (int i = 0; i < 4; i++) if (this->child_trees[i]) this->child_trees[i]->items(items_list);
  }

  const AreaRect& area() { return this->rect_area; }

  void visualizeTree(std::string file_location) {
    // Create and open a text file
    std::ofstream MyFile(file_location);

    MyFile << "digraph test123 {" << std::endl;
    
    MyFile << "  \"" << this->id << "\" [shape=box,label=\" Root \n" << this->tree_container.size() << " elements\"];" << std::endl;

    // Write to the file
    this->printChildren(MyFile);

    MyFile << "}" << std::endl;

    // Close the file
    MyFile.close();

    std::string cmd = "dot -Tsvg " + file_location + " > " + file_location + ".svg";
    exec(cmd.c_str());
  }

  void printChildren(std::ofstream& idk) {
    for (int i = 0; i < 4; i++) {
      if (this->child_trees[i]) {
        std::string blah[] = { "Top Left", "Top Right", "Bottom Left", "Bottom Right" };
        idk << "  \"" << this->child_trees[i]->id << "\" [shape=box,label=\"" << blah[i] << "\n" << this->child_trees[i]->tree_container.size() << " elements\"];" << std::endl;
        
        idk << "  \"" << this->id << "\" -> \"" << this->child_trees[i]->id << "\";" << std::endl;
        this->child_trees[i]->printChildren(idk);
      }
    }
  }
};

template <typename OBJECT_TYPE>
class StaticQuadTreeContainer {
  using QuadTreeContainer = std::list<OBJECT_TYPE>;

protected:
  QuadTreeContainer all_items;
  StaticQuadTree<typename QuadTreeContainer::iterator> root;

public:
  StaticQuadTreeContainer(const AreaRect& size = {{0.0, 0.0}, {100.0, 100.0}}, const size_t depth = 0) {}

  void resize(const AreaRect& resize_area) {
    this->root.resize(resize_area);
  }

  size_t size() const {
    return this->all_items.size();
  }

  void clear() {
    this->root.clear();
    this->all_items.clear();
  }

  typename QuadTreeContainer::iterator begin() { return this->all_items.begin(); }
  typename QuadTreeContainer::iterator end() { return this->all_items.end(); }
  typename QuadTreeContainer::iterator cbegin() { return this->all_items.cbegin(); }
  typename QuadTreeContainer::iterator cend() { return this->all_items.cend(); }

  void insert(const OBJECT_TYPE& item, const AreaRect& item_size) {
    this->all_items.push_back(item);
    this->root.insert(std::prev(this->all_items.end()), item_size);
  }

  std::list<typename QuadTreeContainer::iterator> search(const AreaRect& search_area) const {
    std::list<typename QuadTreeContainer::iterator> item_ptrs_list;
    this->root.search(search_area, item_ptrs_list);
    return item_ptrs_list;
  }
};

template <typename T>
struct QuadTreeItemLocation {
  typename std::list<std::pair<AreaRect, T>>* container;
  typename std::list<std::pair<AreaRect, T>>::iterator iterator;
};

template <typename OBJECT_TYPE>
class DynamicQuadTree {
protected:
  size_t depth = 0;

  AreaRect rect_area;
  std::array<AreaRect, 4> child_areas{};
  std::array<std::shared_ptr<DynamicQuadTree<OBJECT_TYPE>>, 4> child_trees{};
  std::vector<std::pair<AreaRect, OBJECT_TYPE>> tree_container;

public:
  DynamicQuadTree(const AreaRect& size = {{0.0, 0.0}, {100.0, 100.0}}, const size_t depth = 0) {
    this->depth = depth;
    this->resize(size);
  }

  void resize(const AreaRect& resize_area) {
    this->clear();
    this->rect_area = resize_area;
    Vector child_size = Vector(this->rect_area.size.x/2, this->rect_area.size.y/2);

    this->child_areas = {
      // top left
      AreaRect(this->rect_area.pos, child_size),
      // top right
      AreaRect(Vector(this->rect_area.pos.x + child_size.x, this->rect_area.pos.y), child_size),
      // bottom left
      AreaRect(Vector(this->rect_area.pos.x, this->rect_area.pos.y + child_size.y), child_size),
      // bottom right
      AreaRect(Vector(this->rect_area.pos.x + child_size.x, this->rect_area.pos.y + child_size.y), child_size),
    };
  }
  
  void clear() {
    this->tree_container.clear();
    for (int i = 0; i < 4; i++) {
      if (this->child_trees[i]) this->child_trees[i]->clear();
      this->child_trees[i] = 0;
    }
  }

  size_t size() const {
    size_t count = this->tree_container.size();
    for (int i = 0; i < 4; i++) {
      if (this->child_trees[i]) count += this->child_trees[i]->size();
    }
    return count;
  }

  QuadTreeItemLocation<OBJECT_TYPE> insert(const OBJECT_TYPE& item, const AreaRect& item_size) {
    for (int i = 0; i < 4; i++) {
      if (this->child_areas[i].contains(item_size)) {
        if (this->depth <= MAX_QUAD_TREE_DEPTH) {
          if (!this->child_trees[i]) {
            this->child_trees[i] = std::make_shared<DynamicQuadTree<OBJECT_TYPE>>(this->child_areas[i], this->depth + 1);

          }
          return this->child_trees[i]->insert(item, item_size);
        }
      }
    }

    this->tree_container.push_back({item_size, item});
  }

  std::list<OBJECT_TYPE> search(const AreaRect& search_area) const {
    std::list<OBJECT_TYPE> items_list;
    this->search(search_area, items_list);
    return items_list;
  }

  void search(const AreaRect& search_area, std::list<OBJECT_TYPE>& items_list) const {
    for (const auto& p : this->tree_container) {
      if (search_area.overlap(p.first)) {
        items_list.push_back(p.second);
      }
    }
    
    for (int i = 0; i < 4; i++) {
      if (this->child_trees[i]) {
        if (search_area.contains(this->child_areas[i])) this->child_trees[i]->items(items_list);
        else if (search_area.overlap(this->child_areas[i])) this->child_trees[i]->search(search_area, items_list);
      }
    }
  }

  void items(std::list<OBJECT_TYPE> items_list) const {
    for (const auto& p : this->tree_container) items_list.push_back(p.second);
    for (int i = 0; i < 4; i++) if (this->child_trees[i]) this->child_trees[i]->items(items_list);
  }

  const AreaRect& area() { return this->rect_area; }
};

template <typename OBJECT_TYPE>
class DynamicQuadTreeContainer {
  using QuadTreeContainer = std::list<OBJECT_TYPE>;

protected:
  QuadTreeContainer all_items;
  DynamicQuadTree<typename QuadTreeContainer::iterator> root;

public:
  DynamicQuadTreeContainer(const AreaRect& size = {{0.0, 0.0}, {100.0, 100.0}}, const size_t depth = 0) {}

  void resize(const AreaRect& resize_area) {
    this->root.resize(resize_area);
  }

  size_t size() const {
    return this->all_items.size();
  }

  void clear() {
    this->root.clear();
    this->all_items.clear();
  }

  typename QuadTreeContainer::iterator begin() { return this->all_items.begin(); }
  typename QuadTreeContainer::iterator end() { return this->all_items.end(); }
  typename QuadTreeContainer::iterator cbegin() { return this->all_items.cbegin(); }
  typename QuadTreeContainer::iterator cend() { return this->all_items.cend(); }

  void insert(const OBJECT_TYPE& item, const AreaRect& item_size) {
    this->all_items.push_back(item);
    this->root.insert(std::prev(this->all_items.end()), item_size);
  }

  std::list<typename QuadTreeContainer::iterator> search(const AreaRect& search_area) const {
    std::list<typename QuadTreeContainer::iterator> item_ptrs_list;
    this->root.search(search_area, item_ptrs_list);
    return item_ptrs_list;
  }
};


#endif