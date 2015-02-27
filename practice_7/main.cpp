#include <iostream>
#include <string>
#include <regex>
#include <boost/algorithm/string.hpp>

bool is_number(const std::string &s) {
	std::regex reg("^\[+-]?\\d+$");
	return std::regex_match(s, reg);
}

struct IntList {
public:
	IntList() : head(nullptr){}

	~IntList() {
		while (head) {
			node *t = head->next;
			delete head;
			head = t;
		}
	}

	void insert(int value) {
		head = head ? new node({ head, value }) : new node({ 0, value });
	}

	void listElems(std::ostream &output = std::cout) {
		node *t = head;
		while (t) {
			output << t->value << '\n';
			t = t->next;
		}
	}

	void allInOne() {
		node *t = head, *prev = nullptr, *next = nullptr, *tmp;
 		int count = 0, primePrevVal, curVal;

		while (t) {
			curVal = t->value;
			next = t->next;

			if (t->value % 5 == 0) count++;

			if (prev && primePrevVal - 1 == curVal) {
				prev->next = next;
				delete t;
				t = prev;
			}

			if (curVal > 0) {
				t->next = new node({ t->next, 1 });
				next = (prev = t->next)->next;
			}
			else {
				prev = t;
			}
			
			primePrevVal = curVal;
			t = next;
		}

		std::cout << "Number of elemnts ends on 5 - " << count << std::endl;
	}

private:
	struct node {
		node *next;
		int value;
	} *head;
};

int main() {
	std::string input;
	IntList *list = new IntList;

	list->insert(-5);
	list->insert(4);
	list->insert(5);
	list->insert(6);
	list->insert(-10);
	list->insert(-9);
	list->insert(3);

	std::cout
		<< "1 - insert\n"
		<< "2 - calculate\n"
		<< "3 - listElems\n"
		<< "4 - exit\n";

	while (true) {
		do {
			std::cout << "Command: ";
			std::getline(std::cin, input);
			boost::trim(input);
		} while (!is_number(input));
		switch (std::stoi(input))
		{
		case 1:
			std::cout << "Enter a integral number: ";
			std::getline(std::cin, input);
			//boost::trim(input);
			try {
				list->insert(std::stoi(input));
			}
			catch (std::invalid_argument) {
				std::cerr << "Not an integral number!" << std::endl;
			}
			catch (std::out_of_range) {
				std::cerr << "Your number out of range!" << std::endl;
			}
			break;
		case 2:
			list->allInOne();
			break;
		case 3:
			list->listElems();
			break;
		case 4:
            delete list;
			return 0;
			break;
		default:
			std::cout << "I DONT KNOW" << std::endl;
		}
	}
}
