//
// Created by Mohamed Abdelhady on 10/1/2023.
//

#include "UserController.h"
#include "AdminController.h"
#include "../View/Interface.h"


namespace Controller {

	map<string, Model::User, Assistant::comparator> UserController::allUsersId;
	map<string, Model::User> UserController::allUsersUsername;
	map<vector<string>, Model::Record> UserController::allRecords;
	Model::User UserController::currentUser{};
	long long UserController::lastId = 0, UserController::maximumName = 0, UserController::maximumUsername = 0;

	bool UserController::checkPassword(const string& username, const string& password)
	{
		return allUsersUsername.count(username) && allUsersUsername[username].getPassword() == password;
	}

	void UserController::MainInterface(const string& username) {
		currentUser = allUsersUsername[username];
		cout << "\n\t   <User Page>\n";
		vector<string> menu{ "Recently Added Movies", "Not Watched Movies", "All Movies", "Watch History",
							"Favourite List", "Account Information", "Delete Account", "Exit", "Logout" };
		while (true) {
			int choice = Assistant::runMenu(menu);
			if (choice == 1)
				MovieController::showRecentlyAddedMovies();
			else if (choice == 2)
				showUnwatchedMovies();
			else if (choice == 3)
				MovieController::showAll(false);
			else if (choice == 4)
				showHistory();
			else if (choice == 5)
				showFavourite();
			else if (choice == 6)
				accountInformation();
			else if (choice == 7)
				deleteAccount();
			else if (choice == 9)
				View::Interface::logout(currentUser.getId(), false);
			else exit(0);
		}
	}

	void UserController::accountInformation(Model::User& user) {
		cout << "\tUser Account\n";
		cout << "Name: " << user.getName() << '\n';
		cout << "username: " << user.getUsername() << '\n';
		cout << "email: " << user.getEmail() << '\n';
		cout << "Registration Time: " << Assistant::timeStingToFormattedString(user.getCreationTime()) << "\n\n";
	}

	void UserController::watch(Model::Movie& movie) {
		if (allRecords.count({ currentUser.getId(), movie.getId(), "1" }))
			allRecords.erase({ currentUser.getId(), movie.getId(), "1" });
		double watchedRatio = 1.0 * MovieController::watch(movie) / movie.getDuration();
		addToHistory(movie, watchedRatio);
	}

	void UserController::showUnwatchedMovies() {
		set<string> menu;
		for (auto& [id, movie] : MovieController::allMovies)
			if (!currentUser.watched.count(movie.getId()))menu.insert(id), printMovie(movie);
		string choice = Assistant::runMenu(menu);
		openMovie(MovieController::allMovies[choice]);
	}

	void UserController::openMovie(Model::Movie& movie) {
		vector<string> menu = { "Watch" };
		bool inFavourite = currentUser.isInFavourite.count(movie.getId()),
			inHistory = currentUser.watched.count(movie.getId());
		//------------------------|Formatted Printing|------------------------
		int l = movie.getName().size() + movie.getId().size() + 3, r = 0;
		cout << "\n\t";
		if (l < 30) {
			r = ceil(1.0 * (30 - l) / 2);
			for (int i = 0; i < r; ++i) cout << ' ';
		}
		cout << movie.getName() << " <" << movie.getId() << ">";
		for (int i = 0; i < r; ++i) cout << ' ';
		cout << "\n\t";
		for (int i = 0; i < 30; ++i)cout << '-';
		cout << "\n\t";

		if (inFavourite) {
			if (inHistory) {
				cout << "   Favourite | ";
				int y = movie.getDuration(), x = currentUser.getRecord(movie.getId(), 1).getWatchedRatio() * y;
				cout << x / 60 << "h " << x % 60 << "m / " << y / 60 << "h " << y % 60 << '\n';
			}
			else {
				cout << "       Favourite | ";
				cout << "New!\n";
			}
			menu.emplace_back("Remove from Favourite");
		}
		else {
			if (inHistory) {
				for (int i = 0; i < 8; ++i) cout << ' ';
				int y = movie.getDuration(), x = currentUser.getRecord(movie.getId(), 1).getWatchedRatio() * y;
				cout << x / 60 << "h " << x % 60 << "m / " << y / 60 << "h " << y % 60 << '\n';
			}
			else cout << "             New!\n";
			menu.emplace_back("Add to Favourite");
		}

		menu.emplace_back("Details");
		menu.emplace_back("Back");
		int choice = Assistant::runMenu(menu);
		if (choice == 1) {
			watch(movie);
		}
		else if ((choice == 2 && inFavourite)) {
			removeFromFavourite(movie.getId());
		}
		else if (choice == 2) {
			addToFavourite(movie);
		}
		else if (choice == 3)
			MovieController::showDetails(movie);
	}

	void UserController::printMovie(Model::Movie& movie) {
		cout << "\t<" << movie.getId() << "> ";
		for (int j = movie.getId().size(); j < to_string(MovieController::lastId).size(); ++j) cout << ' ';
		cout << movie.getName();
		for (int j = movie.getName().size(); j < MovieController::maximumName; ++j) cout << ' ';
		if (currentUser.isInFavourite.count(movie.getId())) cout << "   { Favourite } ";
		else cout << "                 ";
		if (currentUser.watched.count(movie.getId())) {
			int y = movie.getDuration(), x = currentUser.getRecord(movie.getId(), 1).getWatchedRatio() * y;
			cout << "   " << x / 60 << "h " << x % 60 << "m / " << y / 60 << "h " << y % 60 << "m\n";
		}
		else cout << "   New!\n";
	}

	void UserController::showHistory() {
		map<string, Model::Record, Assistant::comparator>
			history = (const map<string, Model::Record, Assistant::comparator> &) currentUser.getHistory();
		if (history.empty())return void(cout << "There is no Watch History!\n\n");
		cout << "choose sort type According to Watching Time\n";
		vector<string> menu{ "Descending", "Ascending", "back" };
		int choice = Assistant::runMenu(menu), maxName = 0, maxId = 0;

		for (const auto& [id, record] : history) {
			maxName = max(maxName, (int)MovieController::allMovies[record.getMovieId()].getName().size());
			maxId = max(maxId, (int)MovieController::allMovies[record.getMovieId()].getId().size());
		}
		cout << "\t\t\t\tWatch History\n\t\t\t\t-------------\n";
		set<string> menu_;
		if (choice == 1)
			for (auto i = history.rbegin(); i != history.rend(); ++i)
				printHistoryRecord(i->second, maxName, maxId), menu_.insert(i->second.getMovieId());
		else if (choice == 2)
			for (const auto& [id, record] : history)
				printHistoryRecord(record, maxName, maxId), menu_.insert(record.getMovieId());
		else return;
		cout << "\nChoose Movie (input its ID) to Remove from your Watch history (or 0 to Exit the List): ";
		string choice_ = Assistant::runMenu(menu_);
		if (choice_ == "0")return;
		removeFromHistory(choice_);
	}

	void UserController::printHistoryRecord(Model::Record record, const int& maxName, const int& maxId) {
		Model::Movie movie = MovieController::allMovies[record.getMovieId()];
		int timeWatched = movie.getDuration() * record.getWatchedRatio();
		string movieName = movie.getName(), movieId = movie.getId(), minutesWatched = to_string(timeWatched % 60),
			minutes = to_string(movie.getDuration() % 60);

		//----------------------------|Formatting output|-------------------------------
		for (int j = movieName.size(); j < maxName; ++j)movieName.push_back(' ');
		for (int j = movieId.size(); j < maxId; ++j) movieId.push_back(' ');
		if (minutes.size() == 1)minutes.insert(minutes.begin(), '0');
		if (minutesWatched.size() == 1)minutesWatched.insert(minutesWatched.begin(), '0');
		//------------------------------------------------------------------------------

		cout << "You Watched  " << timeWatched / 60 << "h " << minutesWatched << "m / "
			<< movie.getDuration() / 60 << "h " << minutes << " of " << movieName
			<< " (ID: " << movieId << ")  on " << Assistant::timeStingToFormattedString(record.getTime()) << '\n';
	}

	void UserController::addToHistory(Model::Movie& movie, double& watchedRatio) {
		Model::Record record(currentUser.getId(), movie.getId(), 1, Assistant::currentTimeToString(), watchedRatio);
		currentUser.setRecord(record);
		allUsersId[currentUser.getId()].setRecord(record);
		allUsersUsername[currentUser.getUsername()].setRecord(record);
		allRecords[{currentUser.getId(), movie.getId(), "1"}] = record;
		reloadRecords();
	}

	void UserController::removeFromHistory(const string& movieId) {
		currentUser.removeFromRecords(movieId, 1);
		allUsersId[currentUser.getId()].removeFromRecords(movieId, 1);
		allUsersUsername[currentUser.getUsername()].removeFromRecords(movieId, 1);
		allRecords.erase({ currentUser.getId(), movieId, "1" });
		reloadRecords();
		cout << "Removed from your Watch History successfully!\n\n";
	}

	void UserController::showFavourite() {
		map<string, Model::Record, Assistant::comparator>
			favouriteList = (const map<string, Model::Record, Assistant::comparator> &) currentUser.getFavourite();
		if (favouriteList.empty())return void(cout << "Your Favourite list is empty!\n\n");
		cout << "choose sort type According to Time of adding to Favourite list\n";
		vector<string> menu{ "Descending", "Ascending", "back" };
		int choice = Assistant::runMenu(menu), maxName = 0, maxId = 0;

		for (const auto& [id, record] : favouriteList) {
			maxName = max(maxName, (int)MovieController::allMovies[record.getMovieId()].getName().size());
			maxId = max(maxId, (int)MovieController::allMovies[record.getMovieId()].getId().size());
		}
		cout << "\t\t\t\tFavourite List\n\t\t\t\t-------------\n";
		set<string> menu_;
		if (choice == 1) {
			for (const auto& [id, record] : favouriteList) {
				printFavouriteRecord(record, maxName, maxId), menu_.insert(record.getMovieId());
			}
		}
		else if (choice == 2) {
			for (auto i = favouriteList.rbegin(); i != favouriteList.rend(); ++i) {
				printFavouriteRecord(i->second, maxName, maxId), menu_.insert(i->second.getMovieId());
			}
		}
		else return;
		cout << "\nChoose Movie (input its ID) or 0 to Exit the list: ";
		string choice_ = Assistant::runMenu(menu_);
		if (choice_ == "0")return;
		openMovie(MovieController::allMovies[choice_]);
	}

	void UserController::printFavouriteRecord(Model::Record record, const int& maxName, const int& maxId) {
		Model::Movie movie = MovieController::allMovies[record.getMovieId()];
		int durationWatched;
		string movieName = movie.getName(), movieId = movie.getId(), minutesWatched, minutes;
		bool watched = false;
		if (currentUser.watched[record.getMovieId()])
			watched = true,
			durationWatched =
			movie.getDuration() * allRecords[{currentUser.getId(), movie.getId(), "1"}].getWatchedRatio(),
			minutesWatched = to_string(durationWatched % 60),
			minutes = to_string(movie.getDuration() % 60);


		//----------------------------|Formatting output|-------------------------------
		for (int j = movieName.size(); j < maxName; ++j)movieName.push_back(' ');
		for (int j = movieId.size(); j < maxId; ++j) movieId.push_back(' ');
		if (watched && minutes.size() == 1)minutes.insert(minutes.begin(), '0');
		if (watched && minutesWatched.size() == 1)minutesWatched.insert(minutesWatched.begin(), '0');
		//------------------------------------------------------------------------------

		cout << '<' << movieId << "> " << movieName;
		if (watched) {
			cout << "  ( " << durationWatched / 60 << "h " << durationWatched % 60 << "m / " << movie.getDuration() / 60
				<< "h " << movie.getDuration() % 60 << "m )";
		}
		else cout << "  (New!)";
		cout << "   Added on " << Assistant::timeStingToFormattedString(record.getTime()) << '\n';

	}

	void UserController::addToFavourite(Model::Movie& movie) {
		Model::Record record(currentUser.getId(), movie.getId(), 2, Assistant::currentTimeToString());
		currentUser.setRecord(record);
		allUsersId[currentUser.getId()].setRecord(record);
		allUsersUsername[currentUser.getUsername()].setRecord(record);
		allRecords[{currentUser.getId(), movie.getId(), "2"}] = record;
		reloadRecords();
		cout << "Added to your Favourite list successfully!\n\n";
	}

	void UserController::removeFromFavourite(const string& movieId) {
		currentUser.removeFromRecords(movieId, 2);
		allUsersId[currentUser.getId()].removeFromRecords(movieId, 2);
		allUsersUsername[currentUser.getUsername()].removeFromRecords(movieId, 2);
		allRecords.erase({ currentUser.getId(), movieId, "2" });
		reloadRecords();
		cout << "Removed from your Favourite list successfully!\n\n";
	}

	void UserController::deleteAccount() {
		cout << "Once you DELETE your account you CAN't RECOVER it again.\n";
		vector<string> menu{ "Confirm", "Cancel" };
		int choice = Assistant::runMenu(menu);
		if (choice == 1) {
			AdminController::deleteUser(currentUser.getUsername());
			View::Interface::defaultInterface();
		}
	}

	void UserController::reloadUsers() {
		fstream fout(Assistant::usersDirectory, ios::out);
		for (auto& [id, user] : allUsersId)
			fout << user.toString() << '\n';
	}

	void UserController::reloadRecords(const string& id, const bool& movie) {
		fstream fout(Assistant::recordsDirectory, ios::out);
		for (const auto& [IDs, record] : allRecords)
			if ((IDs[0] != id && !movie) || (IDs[1] != id && movie))
				fout << record.toString() << '\n';
	}

	long long UserController::generateId() {
		return ++lastId;
	}

	void UserController::readUsers() {
		allUsersUsername.clear(), allUsersId.clear();
		string entity;
		fstream fout(Assistant::usersDirectory, ios::in);
		if (fout.fail()) {
			cout << "\n\tERROR occurred while opening Users file\n";
			return;
		}
		while (getline(fout, entity)) {
			if (!entity.empty()) {
				Model::User user(entity);
				allUsersUsername[user.getUsername()] = user;
				allUsersId[user.getId()] = user;
				lastId = max(lastId, stoll(user.getId()));
				maximumName = max(maximumName, (long long)user.getName().size());
				maximumUsername = max(maximumUsername, (long long)user.getUsername().size());
			}
		}
		fout.close();
	}

	void UserController::readRecords() {
		allRecords.clear();
		for (auto& [id, user] : allUsersId) {
			user.clearHistory(), user.clearFavourite();
			allUsersUsername[user.getUsername()].clearHistory(), allUsersUsername[user.getUsername()].clearFavourite();
		}
		string entity;
		fstream fout(Assistant::recordsDirectory, ios::in);
		if (fout.fail()) {
			cout << "\n\tERROR occurred while opening Records file\n";
			return;
		}
		while (getline(fout, entity)) {
			if (!entity.empty()) {
				Model::Record record(entity);
				allRecords[{record.getUserId(), record.getMovieId(), to_string(record.getType())}] = record;
				allUsersId[record.getUserId()].setRecord(record);
				allUsersUsername[allUsersId[record.getUserId()].getUsername()].setRecord(record);
			}
		}
		if (!currentUser.getUsername().empty())currentUser = allUsersUsername[currentUser.getUsername()];
		fout.close();
	}

} // Controller