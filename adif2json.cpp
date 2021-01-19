#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


enum ADIFState {
	ADIF_NONE,
	ADIF_TAG,
	ADIF_VALUE
};


int main()
{
	json records = json::array();
	json record = json::object();

	//std::ifstream adif_stream("logbook.adif", std::ios::in);

	ADIFState adif_state = ADIF_NONE;
	bool in_records = false;

	std::string tag;
	int length = 0;
	std::string value;

	char ch;
	while (std::cin) {
		std::cin.read(&ch, 1);
		ADIFState adif_next_state = adif_state;

		switch(adif_state) {
		case ADIF_NONE:
			if (ch == '<') {
				tag = "";
				value = "";
				length = 0;
				adif_next_state = ADIF_TAG;
			}
			break;
		case ADIF_TAG:
			if (ch == '>') {
				auto col = tag.rfind(":");

				if (col != std::string::npos) {
					std::string length_st = tag.substr(col+1);
					length = std::stoi(length_st);
				}
				if (length < 0 || length > 1024)
					length == 0;

				tag = tag.substr(0,col);

				if (length > 0) {
					adif_next_state = ADIF_VALUE;
				} else {
					adif_next_state = ADIF_NONE;
				}
			} else {
				tag += ch;
			}
			break;
		case ADIF_VALUE:
			value += ch;
			length--;
			if (length == 0) {
				adif_next_state = ADIF_NONE;
			}
			break;
		};

		if (adif_state != ADIF_NONE && adif_next_state == ADIF_NONE) {
			if (tag.compare("EOH") == 0) {
				//std::cout << tag << std::endl << std::endl;
				in_records = true;
				record = json::object();
			} else if (in_records && tag.compare("EOR") == 0) {
				//std::cout << tag << std::endl << std::endl;
				records.push_back(record);
				record = json::object();
			} else {
				//std::cout << tag << " = " << value << std::endl;
				record[tag] = value;
			}
		}
		adif_state = adif_next_state;
	}

	std::cout << records.dump(4) << std::endl;
}
