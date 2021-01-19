#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	json records;
	std::cin >> records;

	std::cout << "<ADIF_VER:5>2.2.7" << std::endl;
	std::cout << "<PROGRAMID:9>json2adif" << std::endl;
	std::cout << "<PROGRAMVERSION:5>1.0.0" << std::endl;
	std::cout << "<EOH>" << std::endl;

	for (auto& [na, record] : records.items()) {
		for (auto& [key, value] : record.items()) {
			if (value.empty()) {
				std::cout << "<" << key << ">";
			} else {
				std::string v = value;
				std::cout << "<" << key << ":" << v.length() << ">" << v;
			}
		}
		std::cout << "<EOR>" << std::endl;
	}
}
