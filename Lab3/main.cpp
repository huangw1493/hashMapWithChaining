#include "hashmap.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

//This program takes in a 2 value CSV file and adds it to a HashTable. The two vales are the name of a player and their score.
using namespace std;
int main() {
	HashTable<string, int> test(511,std::hash<string>());

	/*Import CSV file*/
	string line; string player;  string score; size_t com;
	ifstream myfile("players_homeruns.csv");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//Find location of comma. Put int string before comma and after comma in player and
			//score respectivly.
			com = line.find(',');
			player = line.substr(0, com);
			score = line.substr(com+1);
			//somehow its necessary to convert this in a seperate int first
			int tmp = stoi(score);
			test.insert(player, tmp);
		}
		//Make sure file is closed so we're not unhappy
		myfile.close();
	}
	
	/*Test Block. Manually tested*/
	/*
	cout << "Count : " << test.count() << endl;
	test.remove("Babe Ruth");
	cout << "Count : " << test.count() << endl;
	cout << "Input player name" << endl;
	*/
	string input;
	//User input time. 
	//While input isn't exit, continue looping. This block demos the find function.
	while (input != "exit") {
		getline(cin, input);
		try { cout << "Loop: " << test.find(input) << endl; }
		catch (const std::out_of_range& o) { cout << "Player not found" << endl; }
	}
}