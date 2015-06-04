#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <string>

struct Vertex {
  std::string course = "";
  int session_num = 0;
  int time_slot = -1;
  int num_edges;

  // NEEDED FOR ITERATION
  bool operator==(const Vertex &other) const {
    return course == other.course && session_num == other.session_num;
  }

  bool operator!=(const Vertex &other) const {
    return course != other.course;
  }

  bool operator<(const Vertex &other) const {
    return course < other.course;
  }
};

#endif // __VERTEX_H__
