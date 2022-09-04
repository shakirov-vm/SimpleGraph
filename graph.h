
#include <map>
#include <list>
#include <iostream>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <tuple>

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

template <typename ...types>
struct vertex_data final {

	std::tuple<types...> attrs;
	std::list<int> adjacency_list;
				// But best forwarding???
	vertex_data(const types&... attrs_) : attrs(make_tuple(attrs_...)) {}
};

template<typename ...types>
class graph final {

	using list_it = typename std::list<vertex_data<types...>>::iterator;

	std::list<vertex_data<types...>> vertex_list;
	std::map<int, list_it> vertex_map;

public:

	graph() {}
							
	void add_vertex(int num, types&&... attrs) {
							// copy?
		vertex_list.emplace_back(vertex_data<types...>(attrs...));
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

	void print_tuple(const std::tuple<types...>& tpl) {

	    std::cout << "(";
	    std::apply([](const auto&... tpl_args) {

	                size_t index = 0;
	                auto print_elem = [&index](const auto& part) {
	                    if (index > 0) std::cout << ", ";
	                    index++;
	                    std::cout << part;
	                };

	                (print_elem(tpl_args), ...);

	            }, tpl);
	    std::cout << ")";
	}

	void dump() noexcept {
// no auto&& because there is value not ref
		for (auto vertex : vertex_map) {

			std::cout << vertex.first << " ["; 
			print_tuple(vertex.second->attrs);
			std::cout << "] : ";

			for (auto it : vertex.second->adjacency_list) {

				std::cout << it << " "; 
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
};

}