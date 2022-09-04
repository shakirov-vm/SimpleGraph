#include <string>
#include <iostream>

#include "graph.h"

int main() {

	Graph::graph<std::string, int> gr;

	std::string forth("forth_and_two");

	gr.add_vertex(1, "first", 1);
	gr.add_vertex(3, "second", 2);
	gr.add_vertex(10, "third", 3);
	gr.add_vertex(12, forth.substr(5), 4);

	gr.add_edge(1, 3);
	gr.add_edge(3, 10);

	gr.dump();

	gr.del_vertex(1);
	gr.del_edge(3, 10);

	gr.dump();

	try {
		gr.del_vertex(42);
	} catch (struct Graph::no_vertex const &exc) {
		std::cout << exc.what() << std::endl;
	} catch (...) {
		std::cout << "Oops" << std::endl;
	}

	std::cout << "end of programm" << std::endl;
}