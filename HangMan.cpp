#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>       // for rand() func
#include <conio.h>        // for_getch() func
#include <Windows.h>
#include <time.h>
#include <vector>
#include <map>
using namespace std;
#include "HangMan.h"

HangMan::HangMan()
{
	penality = 0;
	playerScore = 0;
	levels = 1;

	map<string, string> country;
	map<string, string> verbs;
	map<string, string> fruits;
	map<string, string> sports;
	map<string, string> animals;

	read("countries.txt", country);
	read("verbs.txt", verbs);
	read("fruits.txt", fruits);
	read("sports.txt", sports);
	read("animals.txt", animals);

	put("country", country);
	put("verbs", verbs);
	put("fruits", fruits);
	put("sports", sports);
	put("animals", animals);

	SetConsoleTitle("Hang Man Game");

	string line;
	ifstream myfile("hangmanWelcome.txt");
	cout << "WELCOME TO..." << endl;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			setColour(4);
			cout << line << endl;
		}
		myfile.close();
		setColour(7);
		cout << "Press Any Key To Continue" << endl;
		_getch();          // wait for some time until a key is hit
		clearScreen();     // clear screen
	}
	else
		cout << "Unable to open file" << endl;
}

void HangMan::loadingMessage()
{
	for (int i = 0; i < 4; i++)
		Sleep(150);
}

void HangMan::loadingDots()
{
	for (int i = 0; i < 3; i++)
	{
		cout << ".";
		Sleep(1500);
	}
}

void HangMan::clearScreen()
{
	system("cls");
}

void HangMan::setColour(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void HangMan::Menu()
{
	int mode;
	cout << "Choose your Mode: " << endl;
	cout << "1- One Player" << endl;
	cout << "2- Two Players" << endl;
	cout << "3- Help/Info" << endl;
	cout << "4- Exit" << endl;
	
	cin >> mode;
	mode = fail(mode);
	clearScreen();
	if (mode == 1)
		onePlayer();
	else if (mode == 2)
		twoPlayers();
	else if (mode == 3)
	{
		ifstream myfile("instructions.txt");
		string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				cout << line << endl;
			}
			myfile.close();
			cout << "Press Any Key To Continue" << endl;
			_getch();          // wait for some time until a key is hit
			clearScreen();    // clear screen
			Menu();
		}
		else
			cout << "Unable to open file" << endl;
	}
	else if (mode == 4)
	{
		clearScreen();
		for (int i = 0; i < 7; i++)
		{
			setColour(i);
			Exit();
			loadingMessage();
		}
	}
}

void HangMan::onePlayer()
{
	cout << "Enter Your Name" << endl;
	cin.ignore();
	getline(cin, playerName);
	int category;
	cout << "Choose a Category" << endl;
	cout << "1- Country" << endl;
	cout << "2- Verbs" << endl;
	cout << "3- Fruits" << endl;
	cout << "4- Sports" << endl;
	cout << "5- Animals" << endl;
	cin >> category;
	category = fail(category);
	clearScreen();
	if (category == 1)
	{
		temp = "country";
		currentCategory.push("country");
		generateRandom(temp);
	}
	else if (category == 2)
	{
		temp = "verbs";
		currentCategory.push("verbs");
		generateRandom(temp);
	}
	else if (category == 3)
	{
		temp = "fruits";
		currentCategory.push("fruits");
		generateRandom(temp);
	}
	else if (category == 4)
	{
		temp = "sports";
		currentCategory.push("sports");
		generateRandom(temp);
	}
	else if (category == 5)
	{
		temp = "animals";
		currentCategory.push("animals");
		generateRandom(temp);
	}
}

int HangMan::fail(int x)
{
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state 
		cin.ignore(INT_MAX, '\n'); // ignore last input 
		cout << "You can only enter numbers !" << endl;
		cout << "Enter a number please" << endl;
		cin >> x;
	}
	return x;
}

void HangMan::read(string temp, map<string, string>& m)
{
	ifstream myfile(temp);
	string line;
	int i = 1;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (i % 2 != 0)
				meaning = line;
			else
			{
				word = line;
				//m.insert(pair<string, string>(word, meaning));
				m[word] = meaning;
			}
			i++;
		}
		myfile.close();
	}
	else
		cout << "Unable to open file" << endl;
}

void HangMan::twoPlayers()
{
	vector <player> v;
	string test;
	cout << "Enter name of player ONE: ";
	cin >> s.nameOfPlayer;
	v.push_back(s);
	cout << "Enter name of player TWO: ";
	cin >> s.nameOfPlayer;
	v.push_back(s);

	for (int i = 0; i < 2; i++)
	{
		string wordTobeGuessed, wordMeaning, categ, wordGuess;
		if (i == 0)
			cout << "\t" << v[0].nameOfPlayer << ", Enter the word \n";
		else
			cout << "\t" << v[1].nameOfPlayer << ", Enter the word \n";
		cin >> wordTobeGuessed;
		cout << "Enter category \n";
		cin >> categ;
		cout << "Enter description \n";
		cin.ignore();
		getline(cin, wordMeaning);
		clearScreen();
		if (i == 0)
			cout << "\t For " << v[1].nameOfPlayer << " \n";
		else
			cout << "\t For " << v[0].nameOfPlayer << " \n";
		cout << "The word category is : " << categ << endl << "and its meaning is : " << wordMeaning;
		int c = 0;

		while (c <= 6)
		{
			cout << "\nwhat is the word ? \n";
			cin >> wordGuess;
			if (wordGuess == wordTobeGuessed)
			{
				cout << "Right answer !\n";
				break;
			}

			else
			{
				c++;
				clearScreen();
				draw_hangman(c, wordTobeGuessed);
			}

			if (c == 6)
				break;
		}

		if (i == 0)
			v[1].score = c;
		else
			v[0].score = c;
	}

	for (int i = 0; i < 2; i++)
	{
		cout << "name \t wrongAnswers \n";
		cout << v[i].nameOfPlayer << "\t" << v[i].score << endl;
	}

	if (v[0].score < v[1].score)
	{
		cout << "And the winner is " << v[0].nameOfPlayer << endl;
		cout << "Sorry " << v[1].nameOfPlayer << ", Better luck next time" << endl;
	}
	else if (v[0].score > v[1].score)
	{
		cout << "And the winner is " << v[1].nameOfPlayer << endl;
		cout << "Sorry " << v[0].nameOfPlayer << ", Better luck next time" << endl;
	}
	else
	{
		cout << "Draw" << endl;
	}
}

void HangMan::generateRandom(string categ)
{

	int index = hashFunc(categ); 

	int count = length(index);
	srand(time(NULL));                    // Use a different seed value so that we don't get
	int chooseRand = rand() % count + 1;  // same result each time we run the program
	Node* temp = hash[index].head;
	int i = 1;
	while (i != chooseRand)
	{
		temp = temp->next;
		i++;
	}
	randomWord = temp->newName;
	randomMeaning = temp->newDesc;
	play(randomWord, randomMeaning);
}

void HangMan::showGuessedChars(char input)
{
	bool found = false;
	for (int i = 0; i < guessedChars.size(); i++)
		if (guessedChars[i] == input)
		{
			found = true;
			break;
		}

	if (found)
		cout << "You Already entered This Charachter !!" << endl;
	else
		guessedChars.push_back(input);

	gotoXY(75, 5);
	cout << "Entered Charchters";
	gotoXY(75, 6);
	for (int i = 0; i < guessedChars.size(); i++)
		cout << guessedChars[i] << " ";
}

void HangMan::gotoXY(int newX, int newY)
{
	COORD myCoord;
	myCoord.X = newX;
	myCoord.Y = newY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), myCoord);
}

void HangMan::Exit()
{
	int i = 0;
	string line;
	ifstream myfile("hangmanWelcome.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << endl;
		}
		myfile.close();
	}
	else
		cout << "Unable to open file" << endl;
	setColour(7);
}

Node::Node(string word, string meaning)
{
	newName = word;
	newDesc = meaning;
	next = nullptr;
}

linkedList::linkedList()
{
	counter = 0;
	tail = head = NULL;
}

void linkedList::push(string first, string second)
{
	Node* newNode = new Node(first, second);

	if (counter == 0)
		head = tail = newNode;
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	counter++;
}

int HangMan::length(int index)  // return length of each category
{
	int count = 0;
	Node* temp = hash[index].head;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

hashTable::hashTable()
{
	tableSize = 37;             // least prime number with no collisions
	hash = new linkedList[tableSize];
}

int hashTable::hashFunc(string key)
{
	int ascii = 0;
	for (int i = 0; i < key.size(); i++)
		ascii += int(key[i]);
	ascii %= tableSize;
	return ascii;
}

void hashTable::put(string s, map<string, string> m)
{
	int index = hashFunc(s);
	map<string, string>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
		hash[index].push(it->first, it->second); // first is name , second is description.
	counter = 0;
}

void HangMan::print_Message(string msg, bool top = true, bool botton = true)
{
	if (top)
	{
		cout << "+--------------------------+" << endl << "|";
	}
	else cout << "|";
	bool front = true;
	for (int i = msg.length(); i < 26; i++)
	{
		if (front)
		{
			msg = " " + msg;
		}
		else msg = msg + " ";
		front = !front;
	}
	cout << msg;
	if (botton)
		cout << "|" << endl << "+--------------------------+" << endl;
	else {
		cout << "|";
		cout << endl;
	}
}

void HangMan::draw_hangman(int guesscount, string finalWord)
{
	setColour(3);
	print_Message("HANGMAN");
	if (guesscount >= 1)
		print_Message("O", false, false);
	if (guesscount == 2)
		print_Message("/ ", false, false);
	if (guesscount == 3)
		print_Message("/|", false, false);
	if (guesscount >= 4)
		print_Message("/|\\", false, false);
	if (guesscount == 5)
		print_Message("/ ", false, false);
	if (guesscount >= 6)
	{
		print_Message("/ \\", false, true);
		print_Message("You Lost", false, true);
		setColour(7);
		cout << "The word was " << finalWord << endl;
	}
	setColour(7);
}

void HangMan::scoring()
{
	gotoXY(50, 5);
	cout << "POINTS" << endl;
	gotoXY(60, 5);
	cout << "PENALITIES" << endl;
	gotoXY(50, 6);
	cout << playerScore << endl;
	gotoXY(60, 6);
	cout << penality << endl;
}

void HangMan::play(string name, string meaning)
{
	guessedChars.clear();      // clear vector with every level
	int trialsCount = 0;
	string guess;
	gotoXY(20, 0);
	cout << "Here is your description" << endl;
	cout << meaning << endl;
	gotoXY(20, 2);
	cout << "Try to guess the word" << endl;
	scoring();

	for (int i = 0; i < 3; i++)
	{
		gotoXY(0, 20);
		cin >> guess;
		if (name != guess)
		{
			trialsCount++;
			if (levels > 1)
				penality += 5;
			clearScreen();
			gotoXY(20, 0);
			cout << "Wrong answer, please try again" << endl;
			gotoXY(22, 2);
			cout << "Here is your description" << endl;
			cout << meaning << endl;
			draw_hangman(trialsCount, name);
			scoring();
		}

		else
		{
			if (i == 0)
				playerScore += 30 - penality;   // penality is 0 in first level
			else if (i == 1)
				playerScore += 25 - penality;
			else if (i == 2)
				playerScore += 20 - penality;
			penality = 0;
			scoring();
			gotoXY(0, 19);
			cout << "CONGRATULATIONS, " << playerName << " YOU WON AND YOUR SCORE IS "
				<< playerScore << "!!" << endl;
			levels++;
			gotoXY(0, 20);
			cout << "Off to the next level";
			loadingDots();
			clearScreen();
			generateRandom(currentCategory.top());  // if he won , move to next word of same category
		}
	}

		string dashes = string(name.size(), '-');
		bool giveHint = true;
		
		while (trialsCount != 6)
		{
			if (trialsCount == 3 && giveHint)
			{
				scoring();
				gotoXY(0, 18);
				cout << "Here is a hint for you" << endl;
				srand(time(NULL));
				int hint = rand() % name.length();
				for (int i = 0; i < name.length(); i++)
				{
					if (name[i] == name[hint])
						dashes[i] = name[i];
				}
				gotoXY(0, 19);
				cout << dashes;
				giveHint = false;
				cout << endl;
			}
			int repeat = 0;
			bool valid = false;
			bool proceed = false;
			gotoXY(0, 21);
			cin >> guess;
			for (int i = 0; i < name.size(); i++)
			{
				if (guess[0] == name[i])
				{
					repeat++;
					valid = true;
					dashes[i] = name[i];
					clearScreen();
					gotoXY(22, 2);
					cout << "Here is your description" << endl;
					cout << meaning << endl;
					draw_hangman(trialsCount, name);
					gotoXY(0, 19);
					cout << dashes << endl;
					if (repeat == 1)
					{
						showGuessedChars(guess[0]);
					}
					scoring();
				}
			}
			repeat = 0;

			if (!valid)
			{
				trialsCount++;
				if (levels > 1)
					penality += 5;
				clearScreen();
				gotoXY(20, 0);
				cout << "Wrong answer, please try again" << endl;
				gotoXY(22, 2);
				cout << "Here is your description" << endl;
				cout << meaning << endl;
				draw_hangman(trialsCount, name);
				gotoXY(0, 19);
				cout << dashes << endl;
				showGuessedChars(guess[0]);
				scoring();
			}

			if (dashes == name)
			{
				playerScore = (playerScore + 10) - penality;
				penality = 0;
				if (playerScore < 0)         // it means that penalities were greater than total score
					playerScore = 0;         // No score with negative
				
				scoring();
				gotoXY(0, 19);
				cout << "CONGRATULATIONS, " << playerName << " YOU WON AND YOUR SCORE IS "
					<< playerScore << "!!" << endl;
				levels++;
				proceed = true;
				gotoXY(0, 20);
				cout << "Off to the next level";
				loadingDots();
				clearScreen();
				generateRandom(currentCategory.top());  // if he won , move to next word of same category
			}

			if (!proceed && trialsCount == 6)
			{
				playerScore -= penality;
				if (playerScore < 0)          // it means that penalities were greater than total score
					playerScore = 0;          // No score with negative
				penality = 0;

				scoring();
				loadingMessage();
				clearScreen();
				draw_hangman(trialsCount, name);
				gotoXY(22, 10);
				cout << "SORRY, " << playerName << " YOU LOST WITH SCORE " << playerScore << "!" << endl;
				cout << "Better luck next time" << endl;
				gotoXY(22, 12);
				cout << "Enter Any Key To Continue" << endl;
				_getch();                     // wait for some time until a key is hit
				clearScreen();
				for (int i = 1; i < 7; i++)
				{
					setColour(i);
					Exit();
					loadingMessage();
				}
			}
		}
}

HangMan::~HangMan()
{
	cout << "Thanks for Playing !" << endl;
}
