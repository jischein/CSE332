#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FileParser.h"

using namespace std;


int usageMessage(const string &programName, const string &error_info, int error_type) {
	cout << "usage: " << programName;

	cout << error_info << endl;

	cerr << error_type << endl;

	return error_type;
}

void make_lowercase(string &input) {

	for (std::string::iterator letter = input.begin(); letter != input.end(); ++letter) {
		if (*letter >= 65 && *letter <= 90) {
			*letter += 32;
		}
	}

}
