#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <cmath>
#include <stdlib.h>
#include <unordered_map>

class Node {
public:
  int data;
  int parent;
  int rank;
  Node() {
    data = -1;
    parent = -1;
    rank = -1;
  }

  Node(int data_input, int parent_input) {
    data = data_input;
    parent = parent_input;
    rank = 0;
  }
};
int merges = 0;
int find_parent(std::vector<Node>&, int);
bool union_method(std::vector<Node>&, int, int);
// void initialize(const std::vector<int>, std::vector<int>&, std::vector<int>&);
int karger(std::vector<Node> [], const int, std::vector<Node>, int);
int karger_core(std::vector<Node> [], const int, std::vector<Node>, int);

int main() {
  int SIZE = 200;
  std::ifstream file("_kargerMinCut.txt");
  std::vector<Node> nodes;
  std::vector<Node> num_array[SIZE + 1];
  int num_edges = 0;

  nodes.push_back(Node(1, 1));
  for (int i = 1; i <= SIZE; ++i) {
    nodes.push_back(Node(i, i));
  }

  while (file) {
    std::string line;
    getline(file, line);
    std::stringstream lineNew(line);
    int element = 0;
    lineNew >> element;
    while(lineNew) {
      int edge_node = 0;
      lineNew >> edge_node;
      if (edge_node != 0) {
        num_edges++;
        num_array[element].push_back(nodes[edge_node]);
      }
    }
  }
  file.close();
  int ans = karger(num_array, SIZE, nodes, num_edges);
  std::cout <<  "The Minimum Cut is: " << ans << std::endl;
}

int karger(std::vector<Node> graph[], const int size, std::vector<Node> nodes, int num_edges) {

  int RUNNING_CONSTANT = 5;
  srand((unsigned int)time(NULL));
  int running_time = 200;//500*size*(size-1)/2 * log(size);
  int min_ans = INT_MAX;
  while (running_time) {
    // initialize(graph, superNodes, superEdges);
    int ans = karger_core(graph, size, nodes, num_edges);

    if (min_ans > ans && ans != 0) {
      min_ans = ans;
    }
    running_time--;
  }
  return min_ans;
}

int karger_core(std::vector<Node> graph[], const int size, std::vector<Node> nodes, int num_edges) {

  int times = 0;
  std::vector<int> nodesTouchedUpon(size + 1, 0);
  int num_nodes = size;
  // num_edges = 400;

  int num_parents = size;

  while (num_parents > 2) {

    std::unordered_map<int, bool> map;
    int random_edge_opening_one_index = rand() % size + 1;
    int random_edge_opening_two_index = rand() %
                                      graph[random_edge_opening_one_index].size();
    // nodesTouchedUpon[random_edge_opening_one_index] = 1;
    // nodesTouchedUpon[graph[random_edge_opening_one_index][random_edge_opening_two_index].data] = 1;
    num_parents = 0;
    int not_counted = 0;
    for (int i = 1; i <= size; ++i) {
        map[nodes[i].parent] = false;
    }

    for (int i = 1; i <= size; ++i) {
      if (map[nodes[i].parent] != true) {
         num_parents++;
         map[nodes[i].parent] = true;
         //map.insert({nodes[i].parent, true});
      } else {
          not_counted++;
      }
    }
    /*if (times == 200) {
      std::cout << num_parents << ' ' << not_counted << std::endl;
      break;
    } */

    /*if (graph[random_edge_opening_one_index][random_edge_opening_two_index].data == -1) {
      continue;
    }*/

    // std::cout << num_edges << ' ';
    // std::cout << random_edge_opening_one_index << ": " << nodes[random_edge_opening_one_index].parent << ", " << graph[random_edge_opening_one_index][random_edge_opening_two_index].data << ": " << nodes[graph[random_edge_opening_one_index][random_edge_opening_two_index].data].parent <<"\n";
    // num_edges--;

    bool union_check = union_method(nodes, random_edge_opening_one_index,
       graph[random_edge_opening_one_index][random_edge_opening_two_index].data);

    //times++;
     // std::cout << random_edge_opening_one_index << ": " << nodes[random_edge_opening_one_index].parent << ", " << graph[random_edge_opening_one_index][random_edge_opening_two_index].data << ": " << nodes[graph[random_edge_opening_one_index][random_edge_opening_two_index].data].parent <<"\n";
    // if (union_check) {
      //num_nodes--;

       /*
      Node new_node = Node();
      if (num_edges <146) {parent_two
        std::cout << random_edge_opening_one_index << ' ' << random_edge_opening_two_index << '\n';
      }
       graph[random_edge_opening_one_index][random_edge_opening_two_index] = new_node;
      for (int i = 0; i < graph[graph[random_edge_opening_one_index][random_edge_opening_two_index].data].size(); ++i) {
         if (graph[graph[random_edge_opening_one_index][random_edge_opening_two_index].data][i].data == nodes[random_edge_opening_one_index].data) {
           graph[graph[random_edge_opening_one_index][random_edge_opening_two_index].data][i] = Node();
         }
       }*/
      // std::cout << num_nodes << ' ';
    //}
  }
  // std::cout << num_parents;

  int cross_connections = 0;
  for (int i = 1; i <= size; ++i) {
    int parent_one = find_parent(nodes, i);
    for (int j = 0; j < graph[i].size(); ++j) {
      int parent_two = find_parent(nodes, graph[nodes[i].data][j].data);
      // std::cout << "StartNew: " << "\n";
      // std::cout << parent_one << ' ' << parent_two  << "\n";
      // std::cout << i << ' ' << graph[nodes[i].data][j].data  << "\n";
      if (parent_one != parent_two) {
        cross_connections++;
      }
    }
  }
  int not_scanned = 0;
  for (int i = 1; i <= size; ++i) {
    if (nodesTouchedUpon[i] == 0) {
      // std::cout << i << ' ';
      not_scanned++;
    }
  }
  // std::cout << edges_ignored;
  return cross_connections/2;
}

int find_parent(std::vector<Node> &nodes, int node_index) {
  if (nodes[node_index].parent != node_index) {
     nodes[node_index].parent = find_parent(nodes, nodes[node_index].parent);
  }
  return nodes[node_index].parent;
}

bool union_method(std::vector<Node> &nodes, int node_one_index, int node_two_index) {
  int node_one_parent_index = find_parent(nodes, node_one_index);
  int node_two_parent_index = find_parent(nodes, node_two_index);
  if (node_one_parent_index == node_two_parent_index) {
    // edges_ignored++;
    return false;
  }
  if(nodes[node_one_parent_index].rank < nodes[node_two_parent_index].rank) {
    nodes[node_one_index].parent = node_two_parent_index;
    } else if(nodes[node_one_parent_index].rank > nodes[node_two_parent_index].rank){
    nodes[node_two_index].parent = node_one_parent_index;
  } else {
    nodes[node_two_index].parent = node_one_parent_index;
    nodes[node_one_parent_index].rank++;
  }
  return true;
}
