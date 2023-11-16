//
// Created by Mohamed Abdelhady on 10/1/2023.
//

#include "MovieController.h"
#include "UserController.h"
#include "AdminController.h"
#include "../View/Interface.h"

namespace Controller {
	map<string, Model::Movie, Assistant::comparator> MovieController::allMovies;
	set<string>MovieController::moviesName;
	long long MovieController::lastId = 0, MovieController::maximumName = 0;

	int MovieController::watch(Model::Movie& movie) {
		chrono::high_resolution_clock::time_point START_, END_;
		START_ = chrono::high_resolution_clock::now();
		cout << "\n\n\tWatching\n\nMovie Duration:" << movie.getDuration();
		cout << "\nInput any to Exit: ";
		string s;
		cin >> s;
		END_ = chrono::high_resolution_clock::now();
		chrono::duration<double> duration = END_ - START_;
		return (int)duration.count() / 60;
	}

	void MovieController::showAll(const bool& admin) {
		while (true) {
			set<string> menu;
			for (auto& [id, movie] : MovieController::allMovies)
				menu.insert(id), printMovie(movie);
			cout << "\nChoose Movie (input its ID) or 0 to Exit: ";
			string choice = Assistant::runMenu(menu);
			if (choice == "0")return;
			if (admin)
				showDetails(MovieController::allMovies[choice]);
			else UserController::openMovie(MovieController::allMovies[choice]);
		}
	}

	void MovieController::showDetails(Model::Movie& movie) {
		cout << "Movie Name: " << movie.getName();
		cout << "\nID: " << movie.getId();
		cout << "\nYear of Release: " << movie.getYear();
		cout << "\nAdded on " << Assistant::timeStingToFormattedString(movie.getCreationTime());
		cout << "\nRate: " << movie.getRate();
		cout << "\nDuration: " << movie.getDuration() / 60 << "h " << movie.getDuration() % 60 << 'm';
		cout << "\nStory: ";
		string story = movie.getStory();
		int count = 1;
		bool f = false;
		for (const auto& i : story) {
			cout << i;
			++count;
			if (count >= 65)f = true;
			if (f && i == ' ')cout << "\n    ", count = 0, f = false;
		}
		cout << "\n\n";
	}

	void MovieController::showRecentlyAddedMovies() {
		set<string> menu;
		int MonthToSecond = 2592000;
		for (auto& [id, movie] : MovieController::allMovies)
			if (Assistant::findTimeDifference(movie.getCreationTime()) / MonthToSecond <= 3)
				menu.insert(id), printMovie(movie);
		if (menu.empty())return void(cout << "There is no recent movies!\n\n");
		cout << "\nChoose Movie (input its ID) or 0 to Exit: ";
		string choice = Assistant::runMenu(menu);
		if (choice == "0")return;
		if (UserController::currentUser.getState())
			showDetails(MovieController::allMovies[choice]);
		else UserController::openMovie(MovieController::allMovies[choice]);

	}

	void MovieController::printMovie(Model::Movie movie) {
		cout << "\t<" << movie.getId() << "> ";
		for (int j = movie.getId().size(); j < to_string(MovieController::lastId).size(); ++j) cout << ' ';
		cout << movie.getName();
		for (int j = movie.getName().size(); j < MovieController::maximumName; ++j) cout << ' ';
		cout << '\n';
	}

	void MovieController::reloadMovies() {
		fstream fout(Assistant::moviesDirectory, ios::out);
		for (auto& [id, movie] : allMovies)
			fout << movie.toString() << '\n';

	}

	long long MovieController::generateId() {
		return ++lastId;
	}

	void MovieController::readMovies() {
		allMovies.clear();
		moviesName.clear();
		string entity;
		fstream fout(Assistant::moviesDirectory, ios::in);
		if (fout.fail()) {
			cout << "\n\tERROR occurred while opening Movies file\n";
			return;
		}
		while (getline(fout, entity)) {
			if (!entity.empty()) {
				Model::Movie movie(entity);
				allMovies[movie.getId()] = movie;
				moviesName.insert(movie.getName());
				lastId = max(lastId, stoll(movie.getId()));
				maximumName = max(maximumName, (long long)movie.getName().size());
			}
		}
		fout.close();

	}
} // Controller