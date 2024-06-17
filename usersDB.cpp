#include "usersDB.h"
#include <fstream>

const std::string mydb = "db.txt";

std::vector<userData> getObservers() {
	std::ifstream db{ mydb, std::ios::in };
	std::vector<userData> observers;
	int id = 0;
	std::string event;
	while (db.peek(), db.good()) {
		db >> id >> event;
		observers.push_back({ id, event });
	}
	return observers;
};

bool saveObserver(int64_t id, std::string event) {
	std::vector<userData> observers = getObservers();
	observers.push_back({ id, event });
	std::ofstream db(mydb, std::ios::out | std::ios::trunc);
	while (db.good()) {
		for each (userData user in observers)
		{
			db << user.id << " " << user.event << "\n";
		}
	}
	return true;
};
bool deleteObserver(int64_t id) {
	std::vector<userData> observers = getObservers();
	auto it = observers.begin();
	while (!(it->id = id)) { it++; };
	observers.erase(it);
	std::ofstream db(mydb, std::ios::out | std::ios::trunc);
	while (db.good()) {
		for each (userData user in observers)
		{
			db << user.id << " " << user.event << "\n";
		}
	}
	return true;
};