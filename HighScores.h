/*
Kate Perry
6/5/2017

Game of Hangman
HighScores.h
*/
#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <string>
using namespace std;

class HighScores
{
private:
	string name;								// To hold the player's name
	string points;								// To hold the score
	string game;								// To hold the type of game
	string date;								// To hold the date

public:
	HighScores();								// Constructor
	void setName(string);
	void setPoints(string);
	void setGame(string);
	void setDate(string);
	void setAll(string, string, string, string);

	string getName() const;
	string getPoints() const;
	int getPointsInt();
	string getGame() const;
	string getDate() const;

};
#endif