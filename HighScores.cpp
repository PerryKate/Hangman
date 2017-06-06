/*
Kate Perry
6/5/2017

Game of Hangman
HighScores.cpp
*/

#include "HighScores.h"

//****************************************************************************
// Constructor is the default constructor that accepts no arguments but sets
// all variables to empty strings
//****************************************************************************

HighScores::HighScores()
{
	name = string(30, ' ');
	points = string(10, ' ');
	game = string(15, ' ');
	date = string(10, ' ');
	
}


//********************************************************************************
// setName sets the string of the member variable name. 
//********************************************************************************

void HighScores::setName(string n)
{
	name = n;
}

//********************************************************************************
// setPoints sets the string of the member variable points. 
//********************************************************************************

void HighScores::setPoints(string p)
{
	points = p;
}
//********************************************************************************
// setGame sets the string of the member variable game. 
//********************************************************************************

void HighScores::setGame(string g)
{
	game = g;
}
//********************************************************************************
// setDate sets the string of the member variable date. 
//********************************************************************************

void HighScores::setDate(string d)
{
	date = d;
}

//********************************************************************************
// setAll sets the string of all the member variables. 
//********************************************************************************

void HighScores::setAll(string n, string p, string g, string d)
{
	name = n;
	points = p;
	game = g;
	date = d;
}

//********************************************************************************
// getName returns the string in the name member
//********************************************************************************

string HighScores::getName() const
{
	return name;
}

//********************************************************************************
// getPoints returns the string in the points member
//********************************************************************************

string HighScores::getPoints() const
{
	return points;
}

//********************************************************************************
// getPointsInt returns the the points string as an int
//********************************************************************************

int HighScores::getPointsInt() 
{
	// Convert points string into a cstring
	char num[15] = { ' ' };
	for (decltype(points.size()) x = 0; x < points.size(); x++)
	{
		num[x] = points[x];
		num[x + 1] = '\n';
	}
	// Convert points cstring into an int
	int number = atoi(num);
	return number;
}

//********************************************************************************
// getGame returns the string in the game member
//********************************************************************************

string HighScores::getGame() const
{
	return game;
}
//********************************************************************************
// getDate returns the string in the date member
//********************************************************************************

string HighScores::getDate() const
{
	return date;
}

