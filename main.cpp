#include "graph.h"
#include <string>

int main() {

	Graph::graph<std::string> gr;

	gr.add_vertex(1, "first");
	gr.add_vertex(3, "second");
	gr.add_vertex(10, "third");

	gr.add_edge(1, 3);
	gr.add_edge(3, 2);

	gr.dump();

	gr.del_vertex(1);
	gr.del_edge(3, 2);
	
	gr.dump();
}