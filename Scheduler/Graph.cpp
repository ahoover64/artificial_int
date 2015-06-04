#include "Graph.h"
#include <iterator>

class Graph::Impl {
public:
  std::set<Vertex> v;
  std::set<Edge> e;
};

Graph::Graph() : mImpl(new Impl) {
  mImpl->v = std::set<Vertex>();
  mImpl->e = std::set<Edge>();
}

Graph::Graph(const Graph &other) : mImpl(new Impl) {
  mImpl->v = other.vertices();
  mImpl->e = other.edges();
}

Graph Graph::operator=(const Graph &other) {
  if (this != &other) {
    mImpl->v = other.vertices();
    mImpl->e = other.edges();
  }
  return *this;
}

bool Graph::add_vertex(const Vertex &ver) {
  return mImpl->v.insert(ver).second;
}

bool Graph::add_edge(const Edge &ed) {
  //mImpl->v.insert(&ed.v1); mImpl->v.insert(&ed.v2);
  return add_edge(*ed.v1, *ed.v2);
}

bool Graph::add_edge(Vertex &v1, Vertex &v2) {
  //std::cout << mImpl->v.insert(v1).second << mImpl->v.insert(v2).second <<std::endl;
  mImpl->v.insert(v1); mImpl->v.insert(v2);
  Edge ed;
  ed.v1 = &v1;
  ed.v2 = &v2;
  return mImpl->e.insert(ed).second;
}

std::set<Edge> Graph::edges() const {
  return mImpl->e;
}

std::set<Vertex> Graph::vertices() const {
  return mImpl->v;
}

std::ostream& operator<<(std::ostream &os, const Graph &g) {
  std::set<Vertex> v = g.vertices();
  std::set<Edge> e = g.edges();
  os << "Vertices: ";
  for(std::set<Vertex>::iterator i = v.begin(); i!=v.end(); i++){
    os << "(" << i->course << ", " << i->time_slot << "), ";
  }
  os << std::endl << std::endl << "Edges: ";
  for(std::set<Edge>::iterator i = e.begin(); i!=e.end(); i++){
    os << "(" << i->v1->course << ", " << i->v2->course << "), ";
  }
  os << std::endl;
  return os;
}

Graph::~Graph() {}
