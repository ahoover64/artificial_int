#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

int main() {
  Graph g;
  Vertex v;
  v.time_slot = 10;
  v.course = "CS201";
  //g.add_vertex(v);
  Vertex v2;
  v2.time_slot = 5;
  v2.course = "ENG101";
  //g.add_vertex(v2);
  Edge e;
  e.v1 = &v;
  e.v2 = &v2;
  g.add_edge(e);
  std::cout << g << std::endl;
  return 0;
}
