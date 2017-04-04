#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FileParser.h"

using namespace std;


int fileParser(vector<string> &v, char * inputFile) {
	ifstream ifs(inputFile);

	if (ifs.is_open()) {
		string file_line, file_word;
		while (getline(ifs, file_line)) {

			istringstream iss(file_line);

			while (iss >> file_word) {
				v.push_back(file_word);
			}
		}

	}

	else {
		cout << "unable to open file" << endl;
		cerr << wrongNumArgs << endl;
	}

	return success;
}

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