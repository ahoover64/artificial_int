#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "Edge.h"
#include "Vertex.h"
#include <memory>
#include <set>
#include <iostream>

class Graph {
public:
  // Canonical Form
  Graph();
  Graph(const Graph &);
  Graph operator=(const Graph &);
  ~Graph();

  // Used for editting the Graph
  bool add_vertex(const Vertex &);
  bool add_edge(const Edge &);        // Adds verticies not already added
  bool add_edge(Vertex &, Vertex &);  // Same as above
  std::set<Edge> edges() const;
  std::set<Vertex> vertices() const;

  // Prints the vertices and Edges onseperate lines
  friend std::ostream& operator<<(std::ostream &os, const Graph &g);

private:
  class Impl;
  std::shared_ptr<Impl> mImpl;
};

#endif //__GRAPH_H__
