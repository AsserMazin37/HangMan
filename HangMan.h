#pragma once
#include <vector>
#include<string>
#include<stack>
#include <map>
using namespace std;

class Node
{
public:
	string newName;
	string newDesc;
	Node* next;
	Node(string, string);
};

class linkedList
{
public:
	int counter;
	Node* head;
	Node* tail;
	linkedList();
	void push(string, string);
};

class hashTable
{
	int tableSize;
public:
	linkedList* hash;
	hashTable();
	int hashFunc(string);
	void put(string, map<string, string>);
};

class HangMan :public hashTable, linkedList
{
	struct player
	{
		string nameOfPlayer;
		int score;
	}s;
	string randomWord;
	string randomMeaning;
	int length(int);
	stack<string>currentCategory; // to continue the game if he won
	int playerScore;              // total score
	int penality;                  // for penalities
	int levels;
	string playerName;
	stack<int>totalScore;
	vector<char> guessedChars;
public:
	string temp;
	string word;
	string meaning;
	HangMan();
	void Menu();
	void onePlayer();
	void twoPlayers();
	void setColour(int);
	void read(string, map<string, string>&);
	void clearScreen();
	void gotoXY(int, int);
	void Exit();
	void loadingMessage();
	void loadingDots();
	int fail(int);
	void generateRandom(string);
	void showGuessedChars(char);
	void print_Message(string, bool, bool);
	void draw_hangman(int, string);
	void play(string, string);
	void scoring();
	~HangMan();
};
