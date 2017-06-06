/*
Kate Perry
6/5/2017

Game of Hangman
Main.cpp
*/

#include "HangmanGame.h"
#include "HighScores.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function prototype
int MenuDisplay();
string SoloPlayer_Display(vector<string> &, vector<string> &, vector<string> &, vector<string> &);
void TwoPlayer_Display(HangmanGame &, HangmanGame &);
void OpenFile(string, vector<string> &, fstream &);
void OpenHighScoresFile(string, HighScores *, fstream &);
void UpdateHighScores(string, HighScores *, fstream &, string, string, int);
string Word_Generator(vector<string> &);

int main()
{
	char MenuChoice = '1';
	char QuitChoice = 0;
	string Guess;				// Hangman guess for entire word/phrase
	char guessChar;				// Hangman guess to hold a character
	int Winner;
	fstream file;			// File stream object

	// Hangman objects and HighScores object 
	HangmanGame player1;
	HangmanGame player2;
	HighScores scores[10];
	

	// Vectors to hold Word Bank categories and High Scores from text files
	vector<string> Other, People, Places, Sayings;	

	// Constants for menu choices
	const char PLAY_SOLO = '1', TWO_PLAYER = '2', DISPLAY_HIGH_SCORES = '3', QUIT_GAME = '4';

	// Open word bank files and save contents to vectors & open High Scores file to save to HighScores object
	OpenFile("Other.txt", Other, file);
	OpenFile("People.txt", People, file);
	OpenFile("Places.txt", Places, file);
	OpenFile("Sayings.txt", Sayings, file);
	OpenHighScoresFile("High Scores.txt", scores, file);
	

	//Use While and Switch statement for menu options
	while (MenuChoice != '4')
	{
		// Display Menu and get user input
		cout << player1.HangmanDisplay();
		MenuChoice = MenuDisplay();

		switch (MenuChoice)
		{
		//********************************************SOLO PLAYER*************************************************************************
		case PLAY_SOLO:
			QuitChoice = 'Y';
			player1.ResetTotalPoints();
			while (QuitChoice != 'Q' && QuitChoice != 'q')
			{
				//Set player1.word with the SoloPlayer_Display function's result
				player1.setWord(SoloPlayer_Display(People, Places, Sayings, Other));

				// Display Hangman and Hidden Word
				cout << string(10, '\n') <<	player1.HangmanDisplay()
				 << endl << endl << string(30, ' ') << player1.getHiddenWord() << endl << endl;

				// While statement to allow user guesses
				Winner = 0;
				cin.ignore();
				while (Winner == 0)
				{
					cout << "Guess a letter(A-Z) or the entire word/phrase for bonus points: ";
					getline(cin, Guess);				// Store guess in a string
					guessChar = Guess[0];				// Make char version of guess

					// Call Hangman_Guess function according to whether the Guess is a letter or entire word
					if (Guess.size() > 1)
						Winner = player1.HangmanGuess(Guess);
					else
						Winner = player1.HangmanGuess(guessChar);

					// Display new hiddenWord
					cout << endl << endl << string(30, ' ') << player1.getHiddenWord() << endl << endl;
				}

				// Declare winner or loser
				player1.CalculatePoints();
				if (player1.getPoints() > 0)
				{
					cout << "\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! WINNER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
						<< string(30, ' ') << "SCORE: " << player1.getPoints() << endl
						<< string(30, ' ') <<"TOTAL POINTS: " << player1.getTotalPoints() << endl << endl;
				}
				else
				{
					cout << "\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SORRY - TOO MANY GUESSES !!!!!!!!!!!!!!!!!!!!!!!\n"
						<< string(30, ' ') << "SCORE: " << player1.getPoints() << endl
						<< string(30, ' ') << "TOTAL POINTS: " << player1.getTotalPoints() << endl << endl;
				}

				cout << "Press Y to choose a new category and play again or Q to quit to menu: ";
				cin >> QuitChoice;
			}
			UpdateHighScores("High Scores.txt", scores, file, "Solo Player", "Player 1",player1.getTotalPoints());
			system("Pause");
			break;
		//****************************************TWO PLAYER*****************************************************************************
		case TWO_PLAYER:
			QuitChoice = 'Y';
			player1.ResetTotalPoints();
			player2.ResetTotalPoints();

			while (QuitChoice != 'Q' && QuitChoice != 'q')
			{
				//Set player1.word and player2.word
				TwoPlayer_Display(player1, player2);
				cout << "Press Enter to begin playing\n";

				// While statement to allow players to guess
				Winner = 0;
				cin.ignore();
				while (Winner == 0)
				{
					// **********Player 1's Turn***************************
					cout << "PLAYER 1:\t" << player1.getHiddenWord() << endl
						<< "Guess: ";
					getline(cin, Guess);				// Store guess in a string
					guessChar = Guess[0];				// Make char version of guess

					// Call Hangman_Guess function according to whether the Guess is a letter or entire word
					if (Guess.size() > 1)
						Winner = player1.HangmanGuess(Guess);
					else
						Winner = player1.HangmanGuess(guessChar);

					// Display new hiddenWord
					cout << endl << endl << "PLAYER 1:\t" << player1.getHiddenWord() << endl << endl;

					if (Winner == 0)  // Skip if Player 1 wins
					{
						// **********Player 2's Turn***************************
						cout << "\t\t\t\t\tPLAYER 2:\t" << player2.getHiddenWord() << endl
							<< "\t\t\t\t\tGuess: ";
						getline(cin, Guess);				// Store guess in a string
						guessChar = Guess[0];				// Make char version of guess

						// Call Hangman_Guess function according to whether the Guess is a letter or entire word
						if (Guess.size() > 1)
							Winner = player2.HangmanGuess(Guess);
						else
							Winner = player2.HangmanGuess(guessChar);

						// Change Winner to 2 if Player 2 wins first
						if (Winner == 1)
							Winner = 2;

						// Display new hiddenWord
						cout << endl << endl << "\t\t\t\t\tPLAYER 2:\t" << player2.getHiddenWord() << endl << endl;
					}
				}	

				// Player 1 Wins
				if (Winner == 1)			
				{
					// Display Player 2's word
					cout << endl << "\t\t\t\t\tPLAYER 2:\t" << player2.getWord() << endl << endl;

					// Declare winner
					player1.CalculatePoints();
					cout << "\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PLAYER 1 WINS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
						<< string(30, ' ') << "SCORE: " << player1.getPoints() << endl
						<< string(30, ' ') << "TOTAL POINTS: " << player1.getTotalPoints() << endl << endl;
				}
				// Player 2 Wins
				else
				{
					// Display Player 1's word
					cout << endl  << "PLAYER 1:\t" << player1.getWord() << endl << endl;

					// Declare winner
					player2.CalculatePoints();
					cout << "\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PLAYER 2 WINS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
						<< string(30, ' ') << "SCORE: " << player2.getPoints() << endl
						<< string(30, ' ') << "TOTAL POINTS: " << player2.getTotalPoints() << endl << endl;
				}

				cout << "Press Y play again or Q to quit to menu: ";
				cin >> QuitChoice;
			}
			//Update High Scores for player 1 and player2
			cout << "\n\nPLAYER 1's Total Points: " << player1.getTotalPoints() << endl;
			cout << "\n\nPLAYER 2's Total Points: " << player2.getTotalPoints() << endl;

			// Check High Scores for the player with the most points
			if (player1.getTotalPoints() > player2.getTotalPoints())
				UpdateHighScores("High Scores.txt", scores, file, "Two Player", "Player 1", player1.getTotalPoints());
			else
				UpdateHighScores("High Scores.txt", scores, file, "Two Player", "Player 2", player2.getTotalPoints());
			
			system("Pause");
			break;
		//***********************************HIGH SCORES DISPLAY**********************************************************************************
		case DISPLAY_HIGH_SCORES:
			cout << "\n\n                                  High Scores\n"
				 << "-----------------------------------------------------------------------------\n"
				 << "           Name          Score             Game              Date         \n"
				 << "-----------------------------------------------------------------------------\n\n";
			//Loop through HighScores object to display scores
			for (int x = 0; x < 10; x++)
			{
				cout << left << setw(25) << scores[x].getName()
					<< left << setw(16) << scores[x].getPoints()
					<< left << setw(20) << scores[x].getGame()
					<< left << setw(20) << scores[x].getDate() << endl;
			}

			system("Pause");
			break;
		//************************************QUIT GAME*********************************************************************************
		case QUIT_GAME:

			cout << "\n\nPress Y to quit Hangman or N to return to menu and play again:  ";
			cin >> QuitChoice;
			if (QuitChoice == 'Y' || QuitChoice == 'y')
				MenuChoice = '4';
			else
				MenuChoice = '1';
			break;
		}
	}

	

	system("Pause");
	return 0;
}


//*******************************************************************************
// Definition of the function MenuDisplay:  Displays a menu of choices and asks 
// user for input
//*******************************************************************************

int MenuDisplay()
{
	char choice;				// To hold the user's selection

	// Display Menu
	cout << "1. Play Solo\n"
		<< "2. Two Player\n"
		<< "3. Display High Scores\n"
		<< "4. Quit Game\n\n"
		<< "Please Enter Your Choice(1-4):  ";

	// Get user's choice and check bounds
	cin >> choice;
	while (choice < '1' || choice > '4')
	{
		cout << "\n\nPlease Enter Your Choice(1-4):  ";
		cin >> choice;
	}

	return choice;
}

//*******************************************************************************
// Definition of the function SoloPlayer_Display:  Displays a menu of choices and asks 
// user for input.  Calls the Word_Generator function based on the user's input and
// returns the word generated.
//*******************************************************************************

string SoloPlayer_Display(vector<string> &V1, vector<string> &V2, vector<string> &V3, vector<string> &V4)
{
	char choice;			// To hold the user's selection
	string word;			// Random word to be returned

	// Display Menu
	cout << string(5, '\n')
		<< "PLAY SOLO\n---------\n\n"
		<< "Please choose a category\n"
		<< "\t1. People\n"
		<< "\t2. Places\n"
		<< "\t3. Sayings\n"
		<< "\t4. Other\n\n"
		<< "Enter Your Choice(1-4):  ";

	// Get user's choice and check bounds
	cin >> choice;
	while (choice < '1' || choice > '4')
	{
		cout << "\n\nPlease Enter Your Choice(1-4):  ";
		cin >> choice;
	}

	// A set of if/else statements to call the function Word_Generator using the correct vector input
	if (choice == '1')
		word = Word_Generator(V1);
	else if (choice == '2')
		word = Word_Generator(V2);
	else if (choice == '3')
		word = Word_Generator(V3);
	else 
		word = Word_Generator(V4);

	return word;
}

//*******************************************************************************
// Definition of the function TwoPlayer_Display:  Displays a menu of choices and asks 
// user for input.  Calls the Word_Generator function based on the user's input and
// returns the word generated.
//*******************************************************************************

void TwoPlayer_Display(HangmanGame &player1, HangmanGame &player2)
{
	string wordPhrase;					//To hold Hangman word or phrase

	cout << string(5, '\n')
		<< "TWO PLAYER\n----------\n\n"
		<< "In HANGMAN FOR TWO PLAYERS each player chooses their opponent's word\n"
		<< "Player 1 please secretly enter a word or phrase for Player 2 to guess\n\n"
		<< "PLAYER 1: ";
	cin.ignore();
	
	//Get Player1 word and transform it to uppercase
	getline(cin, wordPhrase);
	for (decltype(wordPhrase.size()) x = 0; x < wordPhrase.size(); x++)
	{
		wordPhrase[x] = toupper(wordPhrase[x]);
	}
	player1.setWord(wordPhrase);

	//Get Player2 word and transform it to uppercase 
	cout << string(30, '\n') << "Player 2 please secretly enter a word or phrase for Player 1 to guess\n\n"
		<< "PLAYER 2: ";
	getline(cin, wordPhrase);
	for (decltype(wordPhrase.size()) x = 0; x < wordPhrase.size(); x++)
	{
		wordPhrase[x] = toupper(wordPhrase[x]);
	}
	player2.setWord(wordPhrase);
	cout << string(30, '\n') << player1.HangmanDisplay() << endl << endl
		<< "Players may guess a letter(A - Z) or the entire word / phrase for bonus points\n\n";
}

//********************************************************************************
// Definition of function OpenFile: Opens files and stores them to vectors
//********************************************************************************

void OpenFile(string fileName, vector<string> &vect, fstream &file)
{
	string input;			// To hold file input

	// Open the file
	file.open(fileName, ios::in);

	// If the file was successfully opened, continue.
	if (file)
	{
		// Read an item from the file
		getline(file, input);
		
		// While the last read operation was successful, continue.
		while (file)
		{
			// Read the next item.
			vect.push_back(input);
			getline(file, input);
		}

		// Close the file.
		file.close();
	}

	else
		cout << "\n\n\t\tERROR: Cannot open file.\n\n\n";
}
//********************************************************************************
// Definition of function OpenHighScoresFile: Opens file and store to a HighScores object
//********************************************************************************

void OpenHighScoresFile(string fileName, HighScores *scores, fstream &file)
{
	string input;			// To hold file input
	int x = 0;					// counter

	// Open the file
	file.open(fileName, ios::in);

	// If the file was successfully opened, continue.
	if (file)
	{
		// Read an item from the file
		getline(file, input, '$');

		// While the last read operation was successful, continue.
		while (file)
		{
			scores[x].setName(input);			 
			getline(file, input, '$');
				
			scores[x].setPoints(input);
			getline(file, input, '$');
				
			scores[x].setGame(input);
			getline(file, input, '$');
				
			scores[x].setDate(input);
			getline(file, input, '$');
			x++;
						
		}

		// Close the file.
		file.close();
	}

	else
		cout << "\n\n\t\tERROR: Cannot open file.\n\n\n";
}


//********************************************************************************
// Definition of function UpdateHighScores: Determine if the newScore is higher than the lowest score in 
// HighScores array.  If it is high enough, the newScore replaces the lowest score
// in the array.  The HighScores array is then bubble sorted to move the newScore to 
// its proper place.  Lastly, the updated HighScores array is written to the file.
//********************************************************************************

void UpdateHighScores(string fileName, HighScores *scores, fstream &file, string game, string player, int newScore)
{
	//Check if the new score is higher than the lowest score in the HighScores Object
	if (newScore > scores[9].getPointsInt())
	{
		// Set points and game
		scores[9].setPoints(to_string(newScore));
		scores[9].setGame(game);

		// Set date 
		char date[9];
		_strdate_s(date);
		scores[9].setDate(date);

		// Get Name
		string name;
		cout << "\n\nCongratulations " << player <<"! You've made it into the High Scores Club!\n\n"
			<< "Please enter your name: ";
		cin.ignore();
		getline(cin, name);
		scores[9].setName(name);
	}

	//Sort HighScores array by score using bubble sort
	bool swap;
	string _name, _points, _game, _date;
	
	do
	{
		swap = false;
		for (int x = 9; x > 0; x--)
		{
			if (scores[x].getPointsInt() > scores[x - 1].getPointsInt())
			{
				_name = scores[x].getName();
				_points = scores[x].getPoints();
				_game = scores[x].getGame();
				_date = scores[x].getDate();
				scores[x].setAll(scores[x - 1].getName(), scores[x - 1].getPoints(), scores[x - 1].getGame(), scores[x - 1].getDate());
				scores[x - 1].setAll(_name, _points, _game, _date);
				swap = true;
			}
		}
	} while (swap);

	//Open file and save HighScores array
	file.open(fileName, ios::out);

	// If the file was successfully opened, continue.
	if (file)
	{
		for (int x = 0; x < 10; x++)
		{
			file << scores[x].getName() << '$'
				<< scores[x].getPoints() << '$'
				<< scores[x].getGame() << '$'
				<< scores[x].getDate() << endl;
			if (x < 9)
				file << '$';
		}

		// Close the file.
		file.close();
	}

	else
		cout << "\n\n\t\tERROR: Cannot open file.\n\n\n";
}

//*******************************************************************************
// Definition of the function Word_Generator:  Generates a random number using the
// system time and returns the string element of the random element.
//*******************************************************************************

string Word_Generator(vector<string> &vect)
{
	string randomWord;				//Hold the random word to be returned
	int max_value = vect.size();	//Holds the max value for the vector element
	int value;						//Holds the value of the random vector element

	unsigned seed = time(0);		//Get System time
	srand(seed);					//Seed random generator
	value = (rand() % max_value);	//Get random vector element number
	randomWord = vect[value];

	return randomWord;
}