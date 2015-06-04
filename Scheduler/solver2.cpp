#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <memory>
#include <vector>

void graph_solver(Graph &g) {
  int class_slots = 9;
  int lab_slots = 4;
}

// MAIN METHOD
int main(int argc, char* argv[]) {
  Graph stu_sched;
  std::vector<std::string> classes;
  std::string input_file;

  if(argc > 1) {
    input_file = argv[1];
  }
  else {
    input_file = "sampleClasses.txt";
  }

  std::ifstream infile(input_file);
  std::string line;
  std::vector<Vertex> stu_courses;
  while (std::getline(infile, line)) {
    std::istringstream ss(line);
    std::vector<std::string> vect;
    std::string i;
    stu_courses.clear();
    while (ss >> i) {
      if(std::find(classes.begin(), classes.end(), i) == classes.end()) {
        classes.push_back(i);
      }
      Vertex v;
      v.course = i;
      stu_courses.push_back(v);
    }
    for(std::vector<Vertex>::iterator it = stu_courses.begin(); it != stu_courses.end(); it++) {
      for(std::vector<Vertex>::iterator it2 = std::next(it); it2 != stu_courses.end(); it2++) {
        stu_sched.add_edge(*it, *it2);
        std::prev(it);
      }
    }
  }
  std::cout << stu_sched << std::endl;
  std::cout << stu_sched.edges().size() << std::endl;
  return 0;
}
