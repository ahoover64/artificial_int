#ifndef __EDGE_H__
#define __EDGE_H__
#include "Vertex.h"

struct Edge {
  Vertex *v1;
  Vertex *v2;

  // NEEDED FOR ITERATION
  bool operator==(const Edge &other) const {
    if(v1 == (other.v1) &&  v2 == (other.v2))
      return true;
    if(v1 == (other.v2) &&  v2 == (other.v1))
      return true;
    return false;
  }

  bool operator<(const Edge &other) const {
    return !(this == &other);
  }
};

#endif //__EDGE_H__
