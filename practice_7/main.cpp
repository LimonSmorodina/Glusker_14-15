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

	void count5end(std::ostream &output = std::cout) {
		node *t = head;
		int count = 0;
		while (t) {
			if (t->value % 10 == 5) count++;
			t = t->next;
		}
		output << count << std::endl;
	}

	void delete_onXX() {
		node *t, *tmp;

		while (head && head->value % 10 == head->value % 100 / 10) {
			tmp = head->next;
			delete head;
			head = tmp;
		}
		t = head;
		while (t && t->next) {
			if (t->next->value % 10 == t->next->value % 100 / 10) {
				tmp = t->next->next;
				delete t->next;
				t->next = tmp;
			}
			else {
				t = t->next;
			}
		}
	}

	void add_1_after_positive() {
		node *t = head;
		while (t) {
			if (t->value > 0) {
				t->next = new node({ t->next, 1 });
				t = t->next->next;
			}
			else {
				t = t->next;
			}
		}
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

	std::cout
		<< "1 - insert\n"
		<< "2 - listElems\n"
		<< "3 - count5end\n"
		<< "4 - delete_onXX\n"
		<< "5 - add_1_after_positive\n"
		<< "6 - exit\n";

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
			list->listElems();
			break;
		case 3:
			list->count5end();
			break;
		case 4:
			list->delete_onXX();
			break;
		case 5:
			list->add_1_after_positive();
			break;
		case 6:
            delete list;
			return 0;
			break;
		default:
			std::cout << "I DONT KNOW" << std::endl;
		}
	}
}
