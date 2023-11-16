//
// Created by Mohamed Abdelhady on 10/1/2023.
//

#include "AdminController.h"
#include "../View/Interface.h"

namespace Controller {

	map<string, Model::Admin> AdminController::allAdminsUsername;
	map<string, Model::Admin> AdminController::allAdminsId;
	Model::Admin AdminController::currentAdmin{};
	long long AdminController::lastId = 0;

	bool AdminController::checkPassword(const string& username, const string& password) {
		return allAdminsUsername.count(username) && allAdminsUsername[username].getPassword() == password;
	}

	void AdminController::MainInterface(const string& username) {
		currentAdmin = allAdminsUsername[username];
		cout << "\n\t   <Admin Page>\n";
		vector<string> menu{ "All Movies", "All Users", "All Watch History", "Add Movie", "Delete Movie",
							"Designate User as Admin",
							"Delete Admin\t\tPlease Notice, To delete Admin you have to be older Admin.",
							"Delete User", "Account Information", "Exit", "Logout" };
		while (true) {
			int choice = Assistant::runMenu(menu);
			if (choice == 1)
				Controller::MovieController::showAll(true);
			else if (choice == 2)
				showAllUsers();
			else if (choice == 3)
				showAllHistory();
			else if (choice == 4)
				addMovie();
			else if (choice == 5)
				deleteMovie(inputMovieId());
			else if (choice == 6)
				designateAsAdmin(inputUserUsername(false));
			else if (choice == 7)
				deleteAdmin(inputAdminUsername());
			else if (choice == 8)
				deleteUser(inputUserUsername(false));
			else if (choice == 9)
				accountInformation();
			else if (choice == 11)
				View::Interface::logout(currentAdmin.getId(), true);
			else exit(0);
		}
	}

	void AdminController::accountInformation() {
		cout << "\tAdmin Account\n";
		cout << "Name: " << currentAdmin.getName() << '\n';
		cout << "username: " << currentAdmin.getUsername() << '\n';
		cout << "email: " << currentAdmin.getEmail() << '\n';
		cout << "Registration Time: " << Assistant::timeStingToFormattedString(currentAdmin.getCreationTime()) << '\n';
		cout << "Became Admin at " << Assistant::timeStingToFormattedString(currentAdmin.getBecameAdminTime()) << '\n';
		cout << '\n';
	}

	void AdminController::addMovie() {
		string name = inputMovieName();
		string year = inputMovieReleaseYear();
		string rate = inputMovieRate();
		string duration = inputMovieDuration();
		string story = inputMovieStory();
		Model::Movie movie(to_string(MovieController::generateId()), name, year, rate, duration, story,
			Assistant::currentTimeToString());
		MovieController::allMovies[movie.getId()] = movie;
		MovieController::moviesName.insert(movie.getName());
		MovieController::reloadMovies();
	}

	void AdminController::deleteMovie(const string& movieId) {
		string name = MovieController::allMovies[movieId].getName();
		MovieController::allMovies.erase(movieId);
		MovieController::moviesName.erase(name);
		MovieController::reloadMovies();
		UserController::reloadRecords(movieId, true);
		UserController::readRecords();
		cout << name << " DELETED successfully!\n\n";
	}

	void AdminController::showAllUsers() {
		while (true) {
			int name = max((int)Controller::UserController::maximumName - 8, 0),
				username = max((int)Controller::UserController::maximumUsername, 10);
			if (Controller::UserController::maximumUsername > 8)
				name += 4 + (Controller::UserController::maximumUsername - 8) / 2,
				username -= (Controller::UserController::maximumUsername - 8) / 2;
			cout << "    Name" + string(name, ' ') << "  username" + string(username, ' ') << "email\n";
			set<string> menu;
			for (auto element : Controller::UserController::allUsersId) {
				std::string id = element.first;
				Model::User user = element.second;
				menu.insert(user.getUsername());
				name = Controller::UserController::maximumName - user.getName().size(),
					username = Controller::UserController::maximumUsername - user.getUsername().size() + 8;
				cout << user.getName() << string(name, ' ') << "  " << string(username / 2, ' ') << user.getUsername()
					<< string(username / 2 + username % 2, ' ') << "  " << user.getEmail() << '\n';
			}
			cout << "\nChoose User (input his/her username) or 0 to Exit: ";
			string choice = Assistant::runMenu(menu);
			if (choice == "0")return;
			showUser(UserController::allUsersUsername[choice].getUsername());
		}
	}

	void AdminController::showUser(const string& username) {
		while (true) {
			vector<string> menu{ "User's Account", "Designate as Admin", "Delete User", "Back" };
			int choice = Assistant::runMenu(menu);
			if (choice == 1)
				Controller::UserController::accountInformation(UserController::allUsersUsername[username]);
			else if (choice == 2) designateAsAdmin(username);
			else if (choice == 3) deleteUser(username);
			else return;
		}
	}

	void AdminController::showAllHistory() {
		cout << "choose sort type According to Watching Time\n";
		vector<string> menu{ "Descending", "Ascending", "back" };
		int choice = Assistant::runMenu(menu), maxUsername = 0,
			maxMovieId = (int)to_string(MovieController::lastId).size();
		vector<Model::Record> history;

		for (const auto element : UserController::allRecords) {
			Model::Record record = element.second;
			if (record.getType() == 1) {
				history.push_back(record);
				maxUsername = max(maxUsername,
					(int)UserController::allUsersId[record.getUserId()].getUsername().size());
			}
		}
		sort(history.begin(), history.end(), [&](const Model::Record& a, const Model::Record& b) {
			return a.getTime() < b.getTime();
			});
		cout << "\t\t\t\tWatch History\n\t\t\t\t-------------\n";
		if (choice == 1) {
			for (auto i = history.rbegin(); i != history.rend(); ++i) {
				printHistoryRecord(*i, maxUsername, maxMovieId);
			}
		}
		else if (choice == 2) {
			for (const auto& record : history) {
				printHistoryRecord(record, maxUsername, maxMovieId);
			}
		}
		else return;
		cout << '\n';
	}

	void AdminController::printHistoryRecord(Model::Record record, const int& maxUsername, const int& maxMovieId) {
		Model::Movie movie = MovieController::allMovies[record.getMovieId()];

		int timeWatched = movie.getDuration() * record.getWatchedRatio();
		string username = UserController::allUsersId[record.getUserId()].getUsername(),
			movieId = movie.getId(), minutesWatched = to_string(timeWatched % 60),
			minutes = to_string(movie.getDuration() % 60);

		//----------------------------|Formatting output|-------------------------------
		for (int j = (int)username.size(); j < maxUsername; ++j)username.push_back(' ');
		for (int j = (int)movieId.size(); j < maxMovieId; ++j) movieId.push_back(' ');
		if (minutes.size() == 1)minutes.insert(minutes.begin(), '0');
		if (minutesWatched.size() == 1)minutesWatched.insert(minutesWatched.begin(), '0');
		//------------------------------------------------------------------------------

		cout << username << " Watched " << timeWatched / 60 << "h " << minutesWatched << "m / "
			<< movie.getDuration() / 60 << "h " << minutes << "m of <" << movieId << "> on "
			<< Assistant::timeStingToFormattedString(record.getTime()) << '\n';
	}

	void AdminController::designateAsAdmin(const string& username) {
		Model::User user = UserController::allUsersUsername[username];
		Controller::UserController::allUsersId.erase(user.getId());
		Controller::UserController::allUsersUsername.erase(username);
		Model::Admin admin((string&)user.getId(), user.getName(), user.getUsername(),
			user.getPassword(),
			user.getEmail(), user.getCreationTime(), true);
		admin.setBecameAdminTime(Assistant::currentTimeToString());
		allAdminsId[admin.getId()] = admin;
		allAdminsUsername[admin.getUsername()] = admin;
		reload();
		Controller::UserController::reloadUsers();
		Controller::UserController::reloadRecords(user.getId(), false);
		Controller::UserController::readRecords();
		cout << user.getUsername() << " Designated as Admin successfully!\n\n";
	}

	void AdminController::deleteAdmin(const string& username) {
		if (username == "0")return;
		allAdminsId.erase(allAdminsUsername[username].getId());
		allAdminsUsername.erase(username);
		reload();
		cout << username << " DELETED successfully!\n";
	}

	void AdminController::deleteUser(const string& username) {
		if (username == "0")return;
		string id = UserController::allUsersUsername[username].getId();
		Controller::UserController::allUsersId.erase(id);
		Controller::UserController::allUsersUsername.erase(username);
		Controller::UserController::reloadUsers();
		Controller::UserController::reloadRecords(id, false);
		Controller::UserController::readRecords();
		cout << username << " DELETED successfully!\n\n";
	}

	string AdminController::inputAdminUsername() {
		cout << "To DELETE an Admin you should be an older Admin!\n";
		cout << "input Admin username: ";
		string username;
		while (true) {
			cin >> username;
			if (username == "0")return username;
			if (!allAdminsUsername.count(username)) {
				cout << "No such username! input a valid username: " << std::flush;
				continue;
			}
			else if (currentAdmin.getBecameAdminTime() > allAdminsUsername[username].getBecameAdminTime()) {
				cout << "You are to new to DELETE this admin! input a valid username: " << std::flush;
				continue;
			}
			return username;
		}
	}

	string AdminController::inputUserUsername(const bool& New) {
		cout << "input User username: ";
		string username;
		while (true) {
			getline(cin, username);
			if (username == "0" && !New)return username;
			if (!UserController::allUsersUsername.count(username) && !New) {
				cout << "No such username! input a valid username: " << std::flush;
				cin.clear();
				continue;
			}
			else if (New) {
				if (UserController::allUsersUsername.count(username) || allAdminsUsername.count(username)) {
					cout << "Unavailable username! Try again: " << std::flush;
					cin.clear();
					continue;
				}
				auto it = username.find(' ');
				if (it != string::npos) {
					cout << "ERROR! invalid character -space-\nplease input valid username: ";
					cin.clear();
					continue;
				}
			}
			return username;
		}
	}

	string AdminController::inputMovieId() {
		cout << "input Movie Id: ";
		string movieId;
		while (true) {
			cin >> movieId;
			if (!MovieController::allMovies.count(movieId)) {
				cout << "No such Id! input a valid Id: " << std::flush;
				continue;
			}
			return movieId;
		}
	}

	string AdminController::inputMovieName() {
		string name;
		cout << "Input Movie Name: ";
		cin.ignore();
		getline(cin, name);
		return name;
	}

	string AdminController::inputMovieReleaseYear() {
		cout << "Input Movie Release Year: ";
		string year, currentYear = Assistant::currentTimeToString().string::substr(0, 4);
		while (true) {
			getline(cin, year);
			if (cin.fail() || !Assistant::isInteger(year) || year > currentYear) {
				cout << "Input a valid Year: ";
				cin.clear();
				continue;
			}
			return to_string(stoll(year));
		}
	}

	string AdminController::inputMovieRate() {
		cout << "Input Movie Rate: ";
		string rate;
		cin.ignore();
		while (true) {
			getline(cin, rate);
			if (cin.fail() || !Assistant::isDouble(rate)) {
				cout << "Input a valid Rate: ";
				cin.clear();
				continue;
			}
			return to_string(stod(rate));
		}
	}

	string AdminController::inputMovieDuration() {
		cout << "Input Movie Duration: ";
		string duration;
		cin.ignore();
		while (true) {
			getline(cin, duration);
			if (cin.fail() || !Assistant::isInteger(duration)) {
				cout << "Input a valid Duration: ";
				cin.clear();
				continue;
			}
			return to_string(stoll(duration));
		}
	}

	string AdminController::inputMovieStory() {
		string story;
		cout << "Input Movie story: ";
		cin.ignore();
		getline(cin, story);
		return story;
	}

	void AdminController::reload() {
		fstream fout(Assistant::adminsDirectory, ios::out);
		for (auto& [id, user] : allAdminsId)
			fout << user.toString() << '\n';
	}

	void AdminController::readAdmins() {
		allAdminsUsername.clear(), allAdminsId.clear();
		string entity;
		fstream fout(Assistant::adminsDirectory, ios::in);
		if (fout.fail()) {
			cout << "\n\tERROR occurred while opening Admins file\n";
			return;
		}
		while (getline(fout, entity)) {
			if (!entity.empty()) {
				Model::Admin admin(entity);
				allAdminsId[admin.getId()] = admin;
				allAdminsUsername[admin.getUsername()] = admin;
			}
		}
		fout.close();

	}

} // Controller
