#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <memory>
#include <vector>
#include <utility>

void graph_solver(Graph &g) {
  int class_slots = 9;
  int lab_slots = 4;
}

// MAIN METHOD
int main(int argc, char* argv[]) {
  Graph stu_sched;
  std::vector<std::pair<std::string,int>> classes;
  std::string class_file;
  std::string input_file;

  if(argc > 2) {
    class_file = argv[1];
    input_file = argv[2];
  }
  else {
    class_file = "classList.txt";
    input_file = "sampleClasses.txt";
  }

  std::ifstream cfile(class_file);
  std::string line;
  while (std::getline(cfile, line)) {
    std::istringstream ss(line);
    std::string i;
    std::string i2;

    ss >> i;
    ss >> i2;
    classes.push_back(std::make_pair(i,std::stoi(i2)));
  }

  std::ifstream infile(input_file);
  std::vector<Vertex> stu_courses;
  while(std::getline(infile, line)) {
    std::istringstream ss(line);
    std::string i;
    stu_courses.clear();
    while (ss >> i) {
      Vertex v;
      v.course = i;
      v.session_num = 0; // TEMPORARY
      stu_courses.push_back(v);
    }
    for(std::vector<Vertex>::iterator it = stu_courses.begin(); it != stu_courses.end(); it++) {
      std::prev(it);
      for(std::vector<Vertex>::iterator it2 = std::next(it); it2 != stu_courses.end(); it2++) {
        stu_sched.add_edge(*it, *it2);
      }
    }

  }

/*  for(std::vector<Vertex>::iterator it = stu_courses.begin(); it != stu_courses.end(); it++) {
    for(std::vector<Vertex>::iterator it2 = std::next(it); it2 != stu_courses.end(); it2++) {
      stu_sched.add_edge(*it, *it2);
      std::prev(it);
    }
  }*/

  std::cout << stu_sched << std::endl;
  std::cout << stu_sched.edges().size() << std::endl;
  return 0;
}
