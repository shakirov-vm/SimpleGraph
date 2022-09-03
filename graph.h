
#include <map>
#include <list>
#include <iostream>
#include <algorithm>

namespace Graph {

template <typename T>
struct vertex_data {

	T attr; // must be copied?
	std::list<int> adjacency_list;

	vertex_data(const T& attr_) : attr(attr_) {}
};

template<typename T>
class graph final {

	std::map<int, vertex_data<T>> vertex_arr;

public:

	graph() {}
							// ?
	void add_vertex(int num, const T& attr) {

		vertex_arr.emplace(num, vertex_data<T>(attr));
	}

	void add_edge(int start, int end) {
												// pattern?
		auto place = vertex_arr.find(start);
		place->second.adjacency_list.push_back(end);
	}

	void del_vertex(int num) {

		auto place = vertex_arr.erase(num);

		for (auto vertex : vertex_arr) {

			vertex.second.adjacency_list.remove(num);
		}
	}

	void del_edge(int start, int end) {

		auto place = vertex_arr.find(start);
		place->second.adjacency_list.remove(end); // ?
	}

	void dump() {

		for (auto vertex : vertex_arr) {

			std::cout << vertex.first << " [" << vertex.second.attr << "] : ";

			for (auto it : vertex.second.adjacency_list) {

				std::cout << it << " "; 
			}

			std::cout << std::endl;
		}
	}
};

}