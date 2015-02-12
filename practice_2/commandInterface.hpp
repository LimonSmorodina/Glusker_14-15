#ifndef H_COMMAND_INTERFACE
#define H_COMMAND_INTERFACE

#include "include.hpp"
#include "data.hpp"

class command {
public:
	command(const std::string &name, const std::function<void(const std::vector<std::string>&) > &f) {
		this->f = f;
		this->name = name;
	}

	inline void operator() (const std::vector<std::string>& args) {
		f(args);
	}

	inline bool operator== (std::string commandName) {
		return name == commandName;
	}

private:
	std::function<void(const std::vector<std::string>&) > f;
	std::string name;
};

std::vector<command> initCommandList(std::list<Star> &stars);

#endif