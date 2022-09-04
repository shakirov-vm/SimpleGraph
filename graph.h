
#include <map>
#include <list>
#include <iostream>
#include <algorithm>
#include <exception>
#include <stdexcept>

namespace Graph {

// maybe from std::domain_error?
struct no_vertex : std::exception {
	const char* what() const noexcept override {
		return "requested node does not exist";
	}
};

struct just_exist_vertex : std::exception {
	just_exist_vertex() {}
	const char* what() const noexcept override {
		return "requested node just exist";
	}
};

template <typename T>
struct vertex_data {

	T attr; // must be copied?
	std::list<int> adjacency_list;

	vertex_data(const T& attr_) : attr(attr_) {
		std::cout << "ctor vertex_data" << std::endl;
	}
};

template<typename T>
class graph final {

	std::map<int, vertex_data<T>> vertex_arr;

public:

	graph() {}
							// ?
	void add_vertex(int num, const T& attr) {

		auto ret = vertex_arr.emplace(num, vertex_data<T>(attr));
		if (ret.second == false) throw just_exist_vertex();
	}

	void add_edge(int start, int end) {
												
		auto place = vertex_arr.find(start);
		if (place == vertex_arr.end()) throw no_vertex();

		place = vertex_arr.find(end);
		if (place == vertex_arr.end()) throw no_vertex();

		place->second.adjacency_list.push_back(end);
	}

	void del_vertex(int num) {

		size_t deleted = vertex_arr.erase(num);
		if (deleted < 1) throw no_vertex();

		for (auto vertex : vertex_arr) {

			vertex.second.adjacency_list.remove(num);
		}
	}

	void del_edge(int start, int end) {

		auto place = vertex_arr.find(start);
		if (place == vertex_arr.end()) throw no_vertex();

		place->second.adjacency_list.remove(end); // no exception if end don't end in list?
		// And what if end not in a graph?
	}

	void dump() noexcept {
// no auto&& because there is value not ref
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