#ifndef STATIC_QUAD_TREE_INCLUDE
#define STATIC_QUAD_TREE_INCLUDE

#include "AreaShape.h"

#include <memory>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <fstream> 

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;
}

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

template <typename T, typename A>
struct QuadTreeItemLocation {
  typename std::list<std::pair<A, T>>* container;
  typename std::list<std::pair<A, T>>::iterator iterator;
};

template <typename OBJECT_TYPE, typename AREA_TYPE>
class QuadTree {
protected:
  size_t depth = 0;

  AreaRect rect_area;
  std::array<AreaRect, 4> child_areas{};
  std::array<std::shared_ptr<QuadTree<OBJECT_TYPE, AREA_TYPE>>, 4> child_trees{};
  std::list<std::pair<AREA_TYPE, OBJECT_TYPE>> tree_container;
  std::string id;

public:
  QuadTree(const AreaRect& size = {{0.0, 0.0}, {100.0, 100.0}}, const size_t depth = 0) {
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

  QuadTreeItemLocation<OBJECT_TYPE, AREA_TYPE> insert(const OBJECT_TYPE& item, const AREA_TYPE& item_size) {
    for (int i = 0; i < 4; i++) {
      if (this->child_areas[i].contains(item_size)) {
        if (this->depth <= MAX_QUAD_TREE_DEPTH) {
          if (!this->child_trees[i]) {
            this->child_trees[i] = std::make_shared<QuadTree<OBJECT_TYPE, AREA_TYPE>>(this->child_areas[i], this->depth + 1);
          }
          return this->child_trees[i]->insert(item, item_size);
        }
      }
    }

    this->tree_container.push_back({item_size, item});
    return { &this->tree_container, std::prev(this->tree_container.end()) };
  }

  std::list<OBJECT_TYPE> search(const AreaRect& search_area) const {
    std::list<OBJECT_TYPE> items_list;
    this->search(search_area, items_list);
    return items_list;
  }

  std::list<OBJECT_TYPE> search(const AreaCirc& search_area) const {
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

  void search(const AreaCirc& search_area, std::list<OBJECT_TYPE>& items_list) const {
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
    if (this->size() <= 200) {
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
  }

protected:
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

template <typename T, typename A>
struct QuadTreeItem {
  T item;
  QuadTreeItemLocation<typename std::list<QuadTreeItem<T, A>>::iterator, A> item_ptr;
};

template <typename OBJECT_TYPE, typename AREA_TYPE>
class QuadTreeContainer {
  using QuadTreeContainerList = std::list<QuadTreeItem<OBJECT_TYPE, AREA_TYPE>>;

protected:
  QuadTreeContainerList all_items;
  QuadTree<typename QuadTreeContainerList::iterator, AREA_TYPE> root;

public:
  QuadTreeContainer(const AreaRect& size = {{0.0, 0.0}, {100.0, 100.0}}, const size_t depth = 0) {}

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

  typename QuadTreeContainerList::iterator begin() { return this->all_items.begin(); }
  typename QuadTreeContainerList::iterator end() { return this->all_items.end(); }
  typename QuadTreeContainerList::iterator cbegin() { return this->all_items.cbegin(); }
  typename QuadTreeContainerList::iterator cend() { return this->all_items.cend(); }

  void insert(const OBJECT_TYPE& item, const AREA_TYPE& item_size) {
    QuadTreeItem<OBJECT_TYPE, AREA_TYPE> new_item;
    new_item.item = item;
    
    this->all_items.push_back(new_item);
    this->all_items.back().item_ptr = this->root.insert(std::prev(this->all_items.end()), item_size);
  }

  std::list<typename QuadTreeContainerList::iterator> search(const AreaRect& search_area) const {
    std::list<typename QuadTreeContainerList::iterator> item_ptrs_list;
    this->root.search(search_area, item_ptrs_list);
    return item_ptrs_list;
  }

  std::list<typename QuadTreeContainerList::iterator> search(const AreaCirc& search_area) const {
    std::list<typename QuadTreeContainerList::iterator> item_ptrs_list;
    this->root.search(search_area, item_ptrs_list);
    return item_ptrs_list;
  }

  void remove(typename QuadTreeContainerList::iterator& item) {
    // iterator points to a quadtree item
    item->item_ptr.container->erase(item->item_ptr.iterator);
    this->all_items.erase(item);
  }

  void relocate(typename QuadTreeContainerList::iterator& item, const AREA_TYPE& new_rect) {
    item->item_ptr.container->erase(item->item_ptr.iterator);
    item->item_ptr = this->root.insert(item, new_rect);
  }

  void visualizeTree(std::string file_name) {
    this->root.visualizeTree(file_name);
  }
};


#endif