/*
Kate Perry
6/5/2017

Game of Hangman
HangmanGame.h
*/
#ifndef HANGMANGAME_H
#define HANGMANGAME_H
#include <string>
using namespace std;

class HangmanGame
{
private:
	string word;					// To hold the Hangman word or phrase
	string hiddenWord;				// To hold the copy of the Hangman word with letter's switched out with '?'
	int winner;						// Holds a 0 if the game isn't won - changes to a 1 when the game's won
	int numGuesses;					// To hold the number of guesses
	int points;						// To hold the points won
	int TotalPoints;				// To hold the accumlative points

public:
	HangmanGame();								// Constructor
	void setWord(string);
	void setHiddenWord(string);
	int HangmanGuess(char);
	int HangmanGuess(string);
	string HangmanDisplay();
	void CalculatePoints();
	void ResetTotalPoints();

	string getHiddenWord() const;
	string getWord() const;
	int getNumGuesses() const;
	int getPoints() const;
	int getTotalPoints() const;
	int getWinner() const;
	
};
#endif