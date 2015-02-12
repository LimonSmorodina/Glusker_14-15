#include "include.hpp"

#include "data.hpp"
#include "commandInterface.hpp"

int main() {
	std::list<Star> stars;
	std::vector<command> commandList = initCommandList (stars);
	std::vector<command>::iterator command;
	bool exit = false;
	
	std::cout
		<< "Hello, this is the \"Star data base\" programm.\n"
		<< "For list commands enter 'help'." << std::endl;

	do {
		std::string userInput;
		std::getline(std::cin, userInput);

		std::vector<std::string> words;
		boost::split(words, userInput, boost::is_any_of(" "), boost::token_compress_on);

		if (words.size() > 0) {
			if (words[0] == "exit") {
				exit = true;
				continue;
			}
			command = std::find(commandList.begin(), commandList.end(), *words.begin());
			if (command != commandList.cend()) {
				words.erase(words.cbegin());
				(*command)(words);
			}
			else {
				std::cout << "Unknown command '" << words[0] << "', enter 'help' to list commands.\n";
			}
		}
		else {
			std::cout << "Enter a command\n";
		}
	} while (!exit);

	return 0;
}