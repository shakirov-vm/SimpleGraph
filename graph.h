
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
struct vertex_data final {

	T attr; // must be copied?
	std::list<int> adjacency_list;

	vertex_data(const T& attr_) : attr(attr_) {
		std::cout << "ctor vertex_data" << std::endl;
	}
};

template<typename T>
class graph final {

	using list_it = typename std::list<vertex_data<T>>::iterator;

	std::list<vertex_data<T>> vertex_list;
	std::map<int, list_it> vertex_map;

public:

	graph() {}
							
	void add_vertex(int num, const T& attr) {

		vertex_list.push_back(vertex_data<T>(attr));
		auto ret = vertex_map.emplace(num, --vertex_list.end());
		if (ret.second == false) throw just_exist_vertex();
	}

	void add_edge(int start, int end) {
												
		auto place = vertex_map.find(start);
		if (place == vertex_map.end()) throw no_vertex();

		place = vertex_map.find(end);
		if (place == vertex_map.end()) throw no_vertex();

		place->second->adjacency_list.push_back(end);
	}

	void del_vertex(int num) {

		auto place = vertex_map.find(num);
		if (place == vertex_map.end()) throw no_vertex();

		vertex_list.erase(place->second);
		vertex_map.erase(num);

		for (auto vertex : vertex_list) {

			vertex.adjacency_list.remove(num);
		}
	}

	void del_edge(int start, int end) {

		auto place = vertex_map.find(start);
		if (place == vertex_map.end()) throw no_vertex();

		place->second->adjacency_list.remove(end); // no exception if end don't end in list?
		// And what if end not in a graph?
	}

	void dump() noexcept {
// no auto&& because there is value not ref
		for (auto vertex : vertex_map) {

			std::cout << vertex.first << " [" << vertex.second->attr << "] : ";

			for (auto it : vertex.second->adjacency_list) {

				std::cout << it << " "; 
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
};

}