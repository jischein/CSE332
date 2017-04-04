#pragma once
#include <vector>
#include <string>

#ifndef FILEPARSE_H
#define FILEPARSE_H

using namespace std;

enum index { programName, gameName, numArgs };

enum result {
	success = 0, failToOpen = -1, wrongNumArgs = -2, failToReadLine = -3, failToGrabDimensions = -4, failToGrabPieces = -5, tooManyPieces = -6, quitEntered = -7, stalemateErr = -8, wrongGameName = -9, invalidGamePiece = -10, nonNumberInput = -11, invalidNum = -12
};

int fileParser(vector<string> &, char *);

int usageMessage(const string &, const string &, int);

void make_lowercase(string &);

#endif
