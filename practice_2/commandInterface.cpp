#include "commandInterface.hpp"

bool is_number(const std::string &s) {
	std::regex reg("^\\+?\\d+$");
	return std::regex_match(s, reg);
}

std::vector<command> initCommandList(std::list<Star> &stars) {
	std::vector<command> commandList;

	commandList.push_back(command("add", [&stars](const std::vector<std::string>& args){
		if (!args.empty()) {
			std::cout << "Excepted 0 parametr... " << args.size() << " is given." << std::endl;
			return;
		}
		std::string inputTemp;
		bool inputIncorrect;
		std::string starName;
		u_int starAzimuth, starZenith, starMagnitude;

		std::cout << "Enter a star name:" << std::endl;
		do {
			std::getline(std::cin, starName);
            boost::algorithm::trim(starName);
			if (starName.length() < 1) {
				std::cout << "Name can't be empty, enter again..." << std::endl;
				inputIncorrect = true;
			}
			else inputIncorrect = false;
		} while (inputIncorrect);

		std::cout << "Enter a star azimuth" << std::endl;
		do {
			std::getline(std::cin, inputTemp);
            boost::algorithm::trim(inputTemp);
			if (is_number(inputTemp)) {
				starAzimuth = std::stoi(inputTemp);
				inputIncorrect = false;
				if (starAzimuth < CelestialCoord::MIN_AZIMUTH) {
					std::cout << "Azimuth must be more or equal " << CelestialCoord::MIN_AZIMUTH << ", enter again..." << std::endl;
					inputIncorrect = true;
				}
				else if (starAzimuth > CelestialCoord::MAX_AZIMUTH) {
					std::cout << "Azimuth must be less or equal " << CelestialCoord::MAX_AZIMUTH << ", enter again..." << std::endl;
					inputIncorrect = true;
				}
			}
			else {
				std::cout << "Azimuth must be a positive number, enter again..." << std::endl;
				inputIncorrect = true;
			}
		} while (inputIncorrect);

		std::cout << "Enter a star zenith" << std::endl;
		do {
			std::getline(std::cin, inputTemp);
            boost::algorithm::trim(inputTemp);
			if (is_number(inputTemp)) {
				starZenith = std::stoi(inputTemp);
				inputIncorrect = false;
				if (starZenith < CelestialCoord::MIN_ZENITH) {
					std::cout << "Zenith must be more or equal " << CelestialCoord::MIN_ZENITH << ", enter again..." << std::endl;
					inputIncorrect = true;
				}
				else if (starZenith > CelestialCoord::MAX_ZENITH) {
					std::cout << "Zenith must be less or equal " << CelestialCoord::MAX_ZENITH << ", enter again..." << std::endl;
					inputIncorrect = true;
				}
			}
			else {
				std::cout << "Zenith must be a positive number, enter again..." << std::endl;
				inputIncorrect = true;
			}
		} while (inputIncorrect);

		std::cout << "Enter a star magnitude" << std::endl;
		do {
			std::getline(std::cin, inputTemp);
            boost::algorithm::trim(inputTemp);
			if (is_number(inputTemp)) {
				starMagnitude = std::stoi(inputTemp);
				inputIncorrect = false;
				if (starMagnitude < Star::MIN_MAGNITUDE) {
					std::cout << "Magnitude must be more or equal " << Star::MIN_MAGNITUDE << ", enter again..." << std::endl;
					inputIncorrect = true;
				}
				else if (starMagnitude > Star::MAX_MAGNITUDE) {
					std::cout << "Magnitude must be less or equal " << Star::MAX_MAGNITUDE << ", enter again..." << std::endl;
					inputIncorrect = true;
				}
			}
			else {
				std::cout << "Magnitude must be a positive number, enter again..." << std::endl;
				inputIncorrect = true;
			}
		} while (inputIncorrect);

		stars.push_back(Star(starName, CelestialCoord(starAzimuth, starZenith), starMagnitude));
		std::cout << "...done." << std::endl;
	}));

	commandList.push_back(command("delete", [&stars](const std::vector<std::string>& args){
		if (args.size() != 1) {
			std::cout << "Excepted 1 parametr... " << args.size() << " is given." << std::endl;
			return;
		}
		if (is_number(args[0])) {
			u_int index = std::stoi(args[0]);
			if ((index == 0) || (index > stars.size())) {
				std::cout << "There is no star with such index" << std::endl;
			}
			else {
				std::list<Star>::iterator star = stars.begin();
				for (u_int i = 0; i < index - 1; i++) {
					star++;
				}
				stars.remove(*star);
				std::cout << "...done." << std::endl;
			}
		}
		else {
			std::cout << "Star number must be a positive integer" << std::endl;
		}
	}));

	commandList.push_back(command("edit", [&stars](const std::vector<std::string>& args) {
		if (args.size() != 1) {
			std::cout << "Excepted 1 parametr... " << args.size() << " is given." << std::endl;
			return;
		}
		if (is_number(args[0])) {
			u_int index = std::stoi(args[0]);
			std::string inputTemp;
			bool inputIncorrect;
			std::string starName;
			u_int starAzimuth, starZenith, starMagnitude;

			if ((index == 0) || (index > stars.size())) {
				std::cout << "There is no star with such index" << std::endl;
			}
			else {
				std::list<Star>::iterator star = stars.begin();
				for (u_int i = 0; i < index - 1; i++) {
					star++;
				}

				std::cout << "Enter a new star name (nothing for - " << (*star).getName() << "):" << std::endl;

				std::getline(std::cin, starName);
                boost::algorithm::trim(starName);
				if (starName.length() > 1) {
					(*star).setName(starName);
				}

				std::cout << "Enter a new star azimuth (nothing for - " << (*star).getLocation().getAzimuth() << "):" << std::endl;
				do {
					std::getline(std::cin, inputTemp);
                    boost::algorithm::trim(inputTemp);
					inputIncorrect = false;
					if (inputTemp.length() == 0) {
						starAzimuth = (*star).getLocation().getAzimuth();
					}
					else if (is_number(inputTemp)) {
						starAzimuth = std::stoi(inputTemp);
						if (starAzimuth < CelestialCoord::MIN_AZIMUTH) {
							std::cout << "Azimuth must be more or equal " << CelestialCoord::MIN_AZIMUTH << ", enter again..." << std::endl;
							inputIncorrect = true;
						}
						else if (starAzimuth > CelestialCoord::MAX_AZIMUTH) {
							std::cout << "Azimuth must be less or equal " << CelestialCoord::MAX_AZIMUTH << ", enter again..." << std::endl;
							inputIncorrect = true;
						}
					}
					else {
						std::cout << "Azimuth must be a positive number, enter again..." << std::endl;
						inputIncorrect = true;
					}
				} while (inputIncorrect);

				std::cout << "Enter a new star zenith (nothing for - " << (*star).getLocation().getZenith() << "):" << std::endl;
				do {
					std::getline(std::cin, inputTemp);
                    boost::algorithm::trim(inputTemp);
					inputIncorrect = false;
					if (inputTemp.length() == 0) {
						starZenith = (*star).getLocation().getZenith();
					}
					else if (is_number(inputTemp)) {
						starZenith = std::stoi(inputTemp);
						if (starZenith < CelestialCoord::MIN_ZENITH) {
							std::cout << "Zenith must be more or equal " << CelestialCoord::MIN_ZENITH << ", enter again..." << std::endl;
							inputIncorrect = true;
						}
						else if (starZenith > CelestialCoord::MAX_ZENITH) {
							std::cout << "Zenith must be less or equal " << CelestialCoord::MAX_ZENITH << ", enter again..." << std::endl;
							inputIncorrect = true;
						}
					}
					else {
						std::cout << "Zenith must be a positive number, enter again..." << std::endl;
						inputIncorrect = true;
					}
				} while (inputIncorrect);

				(*star).setLocation(CelestialCoord(starAzimuth, starZenith));

				std::cout << "Enter a new star magnitude (nothing for - " << (*star).getMagnitude() << "):" << std::endl;
				do {
					std::getline(std::cin, inputTemp);
                    boost::algorithm::trim(inputTemp);
					inputIncorrect = false;
					if (inputTemp.length() == 0) {
						starMagnitude = (*star).getMagnitude();
					}
					else if (is_number(inputTemp)) {
						starMagnitude = std::stoi(inputTemp);
						if (starMagnitude < Star::MIN_MAGNITUDE) {
							std::cout << "Magnitude must be more or equal " << Star::MIN_MAGNITUDE << ", enter again..." << std::endl;
							inputIncorrect = true;
						}
						else if (starMagnitude > Star::MAX_MAGNITUDE) {
							std::cout << "Magnitude must be less or equal " << Star::MAX_MAGNITUDE << ", enter again..." << std::endl;
							inputIncorrect = true;
						}
					}
					else {
						std::cout << "Magnitude must be a positive number, enter again..." << std::endl;
						inputIncorrect = true;
					}
				} while (inputIncorrect);

				(*star).setMagnitude(starMagnitude);

				std::cout << "...done." << std::endl;
			}
		}
		else {
			std::cout << "Star number must be a positive integer" << std::endl;
		}
	}));

	commandList.push_back(command("save", [&stars](const std::vector<std::string>& args) {
		if (args.size() != 1) {
			std::cout << "Excepted 1 parametr... " << args.size() << " is given." << std::endl;
			return;
		}
		try {
			std::ofstream ofs(args[0]);
			boost::archive::binary_oarchive oa(ofs);
			oa << const_cast<const std::list<Star>&>(stars);
			ofs.close();
			std::cout << "...done." << std::endl;
		}
		catch (std::ofstream::failure e) {
			std::cerr << e.what() << std::endl;
		}
		catch (boost::archive::archive_exception) {
			std::cerr << "Error: can't serialize data..." << std::endl;
		}
	}));

	commandList.push_back(command("load", [&stars](const std::vector<std::string>& args){
		if (args.size() != 1) {
			std::cout << "Excepted 1 parametr... " << args.size() << " is given." << std::endl;
			return;
		}
		try {
			std::ifstream ofs(args[0]);
			boost::archive::binary_iarchive oa(ofs);
			oa >> stars;
			ofs.close();
			std::cout << "...done." << std::endl;
		}
		catch (std::ifstream::failure e) {
			std::cerr << e.what() << std::endl;
		}
		catch (boost::archive::archive_exception e) {
			std::cerr << e.what() << std::endl;
		}
	}));

	commandList.push_back(command("help", [](const std::vector<std::string>& args){
		if (!args.empty()) {
			std::cout << "Excepted 0 parametr... " << args.size() << " is given." << std::endl;
			return;
		}
		std::cout
			<< "'add' - add a star\n"
			<< "'delete <star number>' - remove specific star\n"
			<< "'edit <star number>' - edit specific star\n"
			<< "'list' - show all stars and there numbers\n"
			<< "'save <filename>' - save DB in file <filename>\n"
			<< "'load <filename>' - load DB from file <filename>\n"
			<< "'exit' - terminate programm\n" << std::endl;
	}));

	commandList.push_back(command("list", [&stars](const std::vector<std::string>& args){
		if (!args.empty()) {
			std::cout << "Excepted 0 parametr... " << args.size() << " is given." << std::endl;
			return;
		}
		int i = 1;
		for (auto it = stars.cbegin(); it != stars.cend(); it++, i++) {
			std::cout << "\nStar number - " << i << ":\n";
			std::cout << "\tName: " << (*it).getName() << ".\n";
			std::cout << "\tLocation:\n";
			std::cout << "\t\tAzimuth: " << (*it).getLocation().getAzimuth() << ".\n";
			std::cout << "\t\tZenith: " << (*it).getLocation().getZenith() << ".\n";
			std::cout << "\tMagnitude: " << (*it).getMagnitude() << ".\n";
		}
		std::cout << "\n...done." << std::endl;
	}));

	return commandList;
}
