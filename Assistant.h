//
// Created by Mohamed Abdelhady on 6/19/2023.
//


#ifndef MOVIESAPP_ASSISTANT_H
#define MOVIESAPP_ASSISTANT_H


#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <random>
#include <chrono>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>

namespace Model { class Record; };


class Assistant {
public:
	static std::string usersDirectory, adminsDirectory, moviesDirectory, recordsDirectory, systemLogsDirectory;

	class comparator {
	public:
		bool operator()(const std::string& a, const std::string& b) const;

		bool operator()(const Model::Record& a, const Model::Record& b) const;
	};

	static std::vector<std::string> readLogs();

	static void writeLogs(const bool& loggedIn, const bool& isAdmin, const std::string& id);

	static std::vector<std::string> removingDelimiter(const std::string& entity, const char& delimiter);

	static std::string addingDelimiter(std::vector<std::string>& data, char delimiter);

	static bool emailValidation(const std::string& email);

	static bool isInteger(const std::string& s);

	static bool isDouble(const std::string& s);

	static int runMenu(std::vector<std::string>& menu);

	static std::string runMenu(std::set<std::string>& menu);

	static std::string currentTimeToString();

	static std::string currentTimeToFormattedString();

	static std::string timeStingToFormattedString(const std::string& timeString);

	static int findTimeDifference(const std::string& pastTime);

};

#endif //MOVIESAPP_ASSISTANT_H
