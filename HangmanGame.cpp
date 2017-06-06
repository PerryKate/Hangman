/*
Kate Perry
6/5/2017

Game of Hangman
HangmanGame.cpp
*/
#include "HangmanGame.h"

//****************************************************************************
// Constructor is the default constructor that accepts no arguments but sets
// the word and hiddenWord to empty strings and the winner, numGuesses,
// points, and TotalPoints to 0.
//****************************************************************************

HangmanGame::HangmanGame()
{
	word = string(200, ' ');
	hiddenWord = string(200, ' ');
	winner = 0;
	numGuesses = 0;
	points = 0;
	TotalPoints = 0;
}


//********************************************************************************
// setWord sets the string of the member variable word. Sets the winner, numGuesses,
// and points to 0. Calls setHiddenWord
//********************************************************************************

void HangmanGame::setWord(string w)
{
	word = w;
	winner = 0;
	numGuesses = 0;
	points = 0;
	setHiddenWord(w);
}

//********************************************************************************
// setHiddenWord sets the value of the member variable HiddenWord
//********************************************************************************

void HangmanGame::setHiddenWord(string w)
{
	hiddenWord = w;

	// Switch all letters A-Z in the hiddenWord with a "?"
	for (decltype(w.size()) x = 0; x < w.size(); x++)
	{
		if (w[x] <= 'Z' && w[x] >= 'A')
			hiddenWord[x] = '?';
	}
}


//********************************************************************************
// HangmanGuess accepts a char and searches for it in Word and replaces any "?" in
// the hiddenWord at the locations in Word where the char is found.  It compares 
// the new hiddenWord with the word and updates the winner varible which is returned.
//********************************************************************************

int HangmanGame::HangmanGuess(char guess) 
{
	// Increment number of guesses
	numGuesses++;

	// Change guess to uppercase
	guess = toupper(guess);

	//Loop through characters to search, compare, and replace guess in strings
	for (decltype(word.size()) x = 0; x < word.size(); x++)
	{
		if (word[x] == guess)
			hiddenWord[x] = guess;
	}

	// Update winner variable
	if (hiddenWord == word)
	{
		winner = 1;
	}

	return winner;
}

//********************************************************************************
// HangmanGuess accepts a string and compares it to the hiddenWord.  If they match,
// the winner variable is updated and returned.
//********************************************************************************

int HangmanGame::HangmanGuess(string guess)
{
	// Increment number of guesses
	numGuesses++;

	//Loop through characters to change guess to uppercase
	for (decltype(guess.size()) x = 0; x < guess.size(); x++)
	{
		guess[x] = toupper(guess[x]);
	}

	// Compare guess with word and then update winner and hiddenWord
	if (guess == word)
	{
		hiddenWord = word;
		winner = 1;

		// Assign bonus points
		if (numGuesses > 7)
			points += 150;
		else if (numGuesses > 4 && numGuesses < 8)
			points += 300;
		else
			points += 500;
	}
	return winner;
}

//********************************************************************************
// HangmanDisplay returns a string which prints the word Hangman over many lines
//********************************************************************************

string HangmanGame::HangmanDisplay()
{
	string message = "\n\t0    0    00000    0    0    000000    0      0    00000    0    0\n"
					   "\t0    0    0   0    00   0    0         00    00    0   0    00   0\n"
					   "\t0    0    0   0    000  0    0         000  000    0   0    000  0\n"
					   "\t000000    00000    000000    0  000    0 0000 0    00000    000000\n"
					   "\t0    0    0   0    0  000    0  0 0    0  00  0    0   0    0  000\n"
					   "\t0    0    0   0    0   00    0    0    0      0    0   0    0   00\n"
					   "\t0    0    0   0    0    0    000000    0      0    0   0    0    0\n\n\n";

;
	return message;
}

//********************************************************************************
// CalculatePoints calculates the points and TotalPoints.
//********************************************************************************

void HangmanGame::CalculatePoints()
{
	points += 1125 - (numGuesses * 75);
	TotalPoints += points;
	
}

//********************************************************************************
// ResetTotalPoints sets the TotalPoints to 0
//********************************************************************************

void HangmanGame::ResetTotalPoints()
{
	TotalPoints = 0;
}

//********************************************************************************
// getWord returns the string in the word member
//********************************************************************************

string HangmanGame::getWord() const
{
	return word;
}


//********************************************************************************
// getHiddenWord  returns the hiddenWord.
//********************************************************************************

string HangmanGame::getHiddenWord() const
{
	return hiddenWord;
}

//********************************************************************************
// getWinner  returns the winner.
//********************************************************************************

int HangmanGame::getWinner() const
{
	return winner;
}

//********************************************************************************
// getNumGuesses  returns the numGuesses.
//********************************************************************************

int HangmanGame::getNumGuesses() const
{
	return numGuesses;
}

//********************************************************************************
// getPoints returns the points 
//********************************************************************************

int HangmanGame::getPoints() const
{
	
	return points;
}

//********************************************************************************
// getTotalPoints returns the TotalPoints
//********************************************************************************

int HangmanGame::getTotalPoints() const
{
	return TotalPoints;
}