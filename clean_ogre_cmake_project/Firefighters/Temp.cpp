/*
 sample code from http://www.redblobgames.com/pathfinding/
 copyright 2014 red blob games <redblobgames@gmail.com>
 
 feel free to use this code in your own projects, including commercial projects
 license: apache v2.0 <http://www.apache.org/licenses/license-2.0.html>


#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>

using std::unordered_map;
using std::unordered_set;
using std::array;
using std::vector;
using std::queue;
using std::priority_queue;
using std::pair;
using std::tuple;
using std::tie;
using std::string;

template<typename l>
struct simplegraph {
  typedef l location;
  typedef typename vector<location>::iterator iterator;
  unordered_map<location, vector<location> > edges;

  inline const vector<location>  neighbors(location id) {
    return edges[id];
  }
};

simplegraph<char> example_graph {{
    {'a', {'b'}},
    {'b', {'a', 'c', 'd'}},
    {'c', {'a'}},
    {'d', {'e', 'a'}},
    {'e', {'b'}}
  }};

// helpers for squaregrid::location

// when using std::unordered_map<t>, we need to have std::hash<t> or
// provide a custom hash function in the constructor to unordered_map.
// since i'm using std::unordered_map<tuple<int,int>> i'm defining the
// hash function here. it would be nice if c++ automatically provided
// the hash function for tuple and pair, like python does. it would
// also be nice if c++ provided something like boost::hash_combine. in
// any case, here's a simple hash function that combines x and y:
namespace std {
  template <>
  struct hash<tuple<int,int> > {
    inline size_t operator()(const tuple<int,int>& location) const {
      int x, y;
      tie (x, y) = location;
      return x * 1812433253 + y;
    }
  };
}

// for debugging it's useful to have an ostream::operator << so that we can write cout << foo
std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, tuple<int,int> loc) {
  int x, y;
  tie (x, y) = loc;
  out << '(' << x << ',' << y << ')';
  return out;
}

// this outputs a grid. pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path.
template<class graph>
void draw_grid(const graph& graph, int field_width, 
               unordered_map<typename graph::location, double>* distances=nullptr,
               unordered_map<typename graph::location, typename graph::location>* point_to=nullptr,
               vector<typename graph::location>* path=nullptr) {
  for (int y = 0; y != graph.height; ++y) {
    for (int x = 0; x != graph.width; ++x) {
      typename graph::location id {x, y};
      std::cout << std::left << std::setw(field_width);
      if (graph.walls.count(id)) {
        std::cout << string(field_width, '#');
      } else if (point_to != nullptr && point_to->count(id)) {
        int x2, y2;
        tie (x2, y2) = (*point_to)[id];
        // todo: how do i get setw to work with utf8?
        if (x2 == x + 1) { std::cout << "\u2192 "; }
        else if (x2 == x - 1) { std::cout << "\u2190 "; }
        else if (y2 == y + 1) { std::cout << "\u2193 "; }
        else if (y2 == y - 1) { std::cout << "\u2191 "; }
        else { std::cout << "* "; }
      } else if (distances != nullptr && distances->count(id)) {
        std::cout << (*distances)[id];
      } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
        std::cout << '@';
      } else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
}

struct squaregrid {
  typedef tuple<int,int> location;
  static array<location, 4> dirs;

  int width, height;
  unordered_set<location> walls;

  squaregrid(int width_, int height_)
     : width(width_), height(height_) {}

  inline bool in_bounds(location id) const {
    int x, y;
    tie (x, y) = id;
    return 0 <= x && x < width && 0 <= y && y < height;
  }

  inline bool passable(location id) const {
    return !walls.count(id);
  }

  vector<location> neighbors(location id) const {
    int x, y, dx, dy;
    tie (x, y) = id;
    vector<location> results;

    for (auto dir : dirs) {
      tie (dx, dy) = dir;
      location next(x + dx, y + dy);
      if (in_bounds(next) && passable(next)) {
        results.push_back(next);
      }
    }

    if ((x + y) % 2 == 0) {
      // aesthetic improvement on square grids
      std::reverse(results.begin(), results.end());
    }

    return results;
  }
};

array<squaregrid::location, 4> squaregrid::dirs {location{1, 0}, location{0, -1}, location{-1, 0}, location{0, 1}};

void add_rect(squaregrid& grid, int x1, int y1, int x2, int y2) {
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.walls.insert(squaregrid::location { x, y });
    }
  }
}

squaregrid make_diagram1() {
  squaregrid grid(30, 15);
  add_rect(grid, 3, 3, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);
  return grid;
}

struct gridwithweights: squaregrid {
  unordered_set<location> forests;
  gridwithweights(int w, int h): squaregrid(w, h) {}
  double cost(location from_node, location to_node) const { 
    return forests.count(to_node) ? 5 : 1; 
  }
};

gridwithweights make_diagram4() {
  gridwithweights grid(10, 10);
  add_rect(grid, 1, 7, 4, 9);
  typedef squaregrid::location l;
  grid.forests = unordered_set<squaregrid::location> { 
    l{3, 4}, l{3, 5}, l{4, 1}, l{4, 2},
    l{4, 3}, l{4, 4}, l{4, 5}, l{4, 6},
    l{4, 7}, l{4, 8}, l{5, 1}, l{5, 2},
    l{5, 3}, l{5, 4}, l{5, 5}, l{5, 6},
    l{5, 7}, l{5, 8}, l{6, 2}, l{6, 3},
    l{6, 4}, l{6, 5}, l{6, 6}, l{6, 7},
    l{7, 3}, l{7, 4}, l{7, 5}
  };
  return grid;
}

template<typename t, typename priority_t>
struct priorityqueue {
  typedef pair<priority_t, t> pqelement;
  priority_queue<pqelement, vector<pqelement>, 
                 std::greater<pqelement>> elements;

  inline bool empty() const { return elements.empty(); }

  inline void put(t item, priority_t priority) {
    elements.emplace(priority, item);
  }

  inline t get() {
    t best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};

template<typename graph>
void dijkstra_search
  (const graph& graph,
   typename graph::location start,
   typename graph::location goal,
   unordered_map<typename graph::location, typename graph::location>& came_from,
   unordered_map<typename graph::location, double>& cost_so_far)
{
  typedef typename graph::location location;
  priorityqueue<location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;
  
  while (!frontier.empty()) {
    auto current = frontier.get();

    if (current == goal) {
      break;
    }

    for (auto next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        came_from[next] = current;
        frontier.put(next, new_cost);
      }
    }
  }
}

template<typename location>
vector<location> reconstruct_path(
   location start,
   location goal,
   unordered_map<location, location>& came_from
) {
  vector<location> path;
  location current = goal;
  path.push_back(current);
  while (current != start) {
    current = came_from[current];
    path.push_back(current);
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}

inline double heuristic(squaregrid::location a, squaregrid::location b) {
  int x1, y1, x2, y2;
  tie (x1, y1) = a;
  tie (x2, y2) = b;
  return abs(x1 - x2) + abs(y1 - y2);
}

template<typename graph>
void a_star_search
  (const graph& graph,
   typename graph::location start,
   typename graph::location goal,
   unordered_map<typename graph::location, typename graph::location>& came_from,
   unordered_map<typename graph::location, double>& cost_so_far)
{
  typedef typename graph::location location;
  priorityqueue<location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;
  
  while (!frontier.empty()) {
    auto current = frontier.get();

    if (current == goal) {
      break;
    }

    for (auto next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost + heuristic(next, goal);
        frontier.put(next, priority);
        came_from[next] = current;
      }
    }
  }
}
*/
