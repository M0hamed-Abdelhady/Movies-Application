//
// Created by Mohamed Abdelhady on 6/19/2023.
//
#include "Assistant.h"
#include "Model/Record.h"

std::string Assistant::usersDirectory = "database/Users.txt",
Assistant::adminsDirectory = "database/Admins.txt",
Assistant::moviesDirectory = "database/Movies.txt",
Assistant::recordsDirectory = "database/Records.txt",
Assistant::systemLogsDirectory = "database/SystemLogs.txt";

bool Assistant::comparator::operator()(const std::string& a, const std::string& b) const
{
	if (isInteger(a) && isInteger(b))
		return std::stoll(a) < std::stoll(b);
	else
		return a < b;
}

bool Assistant::comparator::operator()(const Model::Record& a,
	const Model::Record& b) const
{
	return a.getTime() < b.getTime();
}

std::vector<std::string>
Assistant::readLogs()
{
	std::string line;
	std::fstream log(systemLogsDirectory, std::ios::in);
	if (log.peek() == std::fstream::traits_type::eof() || log.peek() == '\n')
		return { "0", "0", "0", "0" };
	log.seekg(-1, std::ios_base::end);
	if (log.peek() == '\n') {
		log.seekg(-2, std::ios_base::cur);
	}
	while (true) {
		char ch;
		log.get(ch);
		if ((int)log.tellg() <= 1) {
			log.close();
			log.open(systemLogsDirectory, std::ios::in);
			break;
		}
		else if (ch == '\n') {
			break;
		}
		else {
			log.seekg(-3, std::ios_base::cur);
		}
	}
	getline(log, line);
	log.close();
	if (line.empty())
		return { "0", "0", "0", "0" };
	std::vector<std::string> logs = removingDelimiter(line, '|');
	if (findTimeDifference(logs[3]) / 2592000 >= 1) {
		std::fstream x(systemLogsDirectory, std::ios::out);
		x.close();
		return { "0", "0", "0", "0" };
	}
	return logs;
}

void Assistant::writeLogs(const bool& loggedIn,
	const bool& isAdmin,
	const std::string& id)
{
	std::fstream fout(systemLogsDirectory, std::ios::app);
	fout << loggedIn << '|' << isAdmin << '|' << id << '|'
		<< currentTimeToString() << '\n';
	fout.close();
}

std::vector<std::string>
Assistant::removingDelimiter(const std::string& entity, const char& delimiter)
{
	std::string word;
	std::vector<std::string> data;
	for (const auto& i : entity) {
		if (i != delimiter)
			word.push_back(i);
		else if (!word.empty())
			data.push_back(word), word.clear();
	}
	if (!word.empty())
		data.push_back(word);
	return data;
}

std::string
Assistant::addingDelimiter(std::vector<std::string>& data, char delimiter)
{
	std::string entity;
	for (const auto& datum : data) {
		entity += datum + delimiter;
	}
	entity.pop_back();
	return entity;
}

bool Assistant::emailValidation(const std::string& email)
{
	std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	return regex_match(email, pattern);
}

bool Assistant::isInteger(const std::string& s)
{
	std::istringstream iss(s);
	int value;
	iss >> value;
	return !iss.fail() && iss.eof();
}

bool Assistant::isDouble(const std::string& s)
{
	std::istringstream iss(s);
	double value;
	iss >> value;
	return !iss.fail() && iss.eof();
}

int Assistant::runMenu(std::vector<std::string>& menu)
{
	for (int i = 1; i <= menu.size(); ++i) {
		std::cout << i << ". " << menu[i - 1] << '\n';
	}
	std::cout << "Your Choice: ";
	std::string choice;
	while (true) {
		std::cin >> choice;
		if (std::cin.fail() || !isInteger(choice) || std::stoi(choice) > menu.size() || std::stoi(choice) < 0) {
			std::cout << "ERROR please input a number in range 1 to " << menu.size()
				<< ": ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cout << '\n';
			return stoi(choice);
		}
	}
}

std::string
Assistant::runMenu(std::set<std::string>& menu)
{
	std::cout << "Your Choice: ";
	std::string choice;
	while (true) {
		std::cin >> choice;
		if (std::cin.fail() || (!menu.count(choice) && choice != "0")) {
			std::cout << "ERROR please input a valid Id: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cout << '\n';
			return choice;
		}
	}
}

std::string
Assistant::currentTimeToString()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	time_t currentTime = std::chrono::system_clock::to_time_t(now);
	tm localTime;
	if (localtime_s(&localTime, &currentTime) != 0)
		throw std::runtime_error("Error getting local time");

	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y%m%d%H%M%S");
	std::string s = oss.str();
	return s;
}

std::string
Assistant::currentTimeToFormattedString()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	time_t currentTime = std::chrono::system_clock::to_time_t(now);
	tm localTime;
	if (localtime_s(&localTime, &currentTime) != 0)
		throw std::runtime_error("Error getting local time");
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y/%m/%d %H:%M:%S");
	std::string s = oss.str();
	return s;
}

std::string
Assistant::timeStingToFormattedString(const std::string& timeString)
{
	tm timeStruct = {};
	std::istringstream iss(timeString);
	iss >> std::get_time(&timeStruct, "%Y%m%d%H%M%S");
	--timeStruct.tm_hour;
	bool pm = false;

	if (timeStruct.tm_hour == 11)
		pm = true;
	else if (timeStruct.tm_hour > 11)
		timeStruct.tm_hour -= 12, pm = true;
	else if (timeStruct.tm_hour == -1)
		timeStruct.tm_hour = 11;
	time_t timeValue = mktime(&timeStruct);

	char buffer[22];
	struct tm timeInfo;
	if (localtime_s(&timeInfo, &timeValue) != 0) {
		throw std::runtime_error("Error getting local time");
	}

	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", &timeInfo);
	buffer[19] = ' ';
	if (pm)
		buffer[20] = 'P';
	else
		buffer[20] = 'A';

	buffer[21] = 'M';
	return std::string(buffer, sizeof(buffer));
}

int Assistant::findTimeDifference(const std::string& pastTime) {
	tm time1 = {};
	std::istringstream i(pastTime);
	i >> std::get_time(&time1, "%Y%m%d%H%M%S");
	time_t past = mktime(&time1);
	time_t now = std::time(nullptr);
	return difftime(now, past);
}
