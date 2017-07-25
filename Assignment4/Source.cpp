#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>

using namespace std;

const wstring CARD_NUM[] = { L"emp",L"A",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"10",L"J",L"Q",L"K" };

class Card {
	enum SUITE
	{
		emp, club, diamond, heart, spade
	};
public:
	Card() {
		this->cardNum = CARD_NUM[0];
		suit = emp;
		this->cardValue = 0;	
	}
	void display();
	void setCard(int suiteIndex, int cardNum);
	wstring getCardNum();
	int getCardValue();
	~Card() {};
private:
	wstring cardNum;
	SUITE suit;
	int cardValue;
};

wstring Card::getCardNum() {
	return this->cardNum;
}
int Card::getCardValue() {
	return this->cardValue;
}
void Card::display() {
	wcout << cardNum;

	if (suit == club) {
		wcout << L"♣";		
	}
	else if (suit == diamond) {
		wcout << L"♦";

	}
	else if (suit == heart) {
		wcout << L"♥";

	}
	else if (suit == spade) {
		wcout << L"♠";
	}
	else
	{
		wcout << L"";
	}
	//wcout << L"(" << cardValue << L")";
}
void Card::setCard(int suiteIndex, int cardNum) {

	if (suiteIndex == 1)
	{
		suit = club;
	}
	else if (suiteIndex == 2)
	{
		suit = diamond;
	}
	else if (suiteIndex == 3)
	{
		suit = heart;
	}
	else if (suiteIndex == 4)
	{
		suit = spade;
	}
	else if (suiteIndex == 0)
	{
		suit = emp;
	}
	this->cardNum = CARD_NUM[cardNum];

	this->cardValue = cardNum > 10 ? 10 : cardNum;
}

//class Board {
//	enum direction { east, south, west, north };
//public:
//	Board(vector<Player> players) {
//		this->players = players;
//	}
//	void displayBoard() {
//
//	}
//	vector<wstring> getCrib() {
//		return this->crib;
//	}
//	vector<wstring> getCut() {
//		return this->cut;
//	}
//	vector<wstring> getCut() {
//		return this->cut;
//	}
//	;
//private:
//	vector<wstring> cut;
//	vector<wstring> crib;
//	vector<wstring> playedCards;
//	vector<Player> players;
//	int totalScore;
//};
//
//class Game {
//public :
//	Game() {
//		
//	}
//	void postGameProcess() {
//
//	}
//	void pegging() {
//
//	}
//	;
//private :
//	int totalScore;
//
//};
class Player {
public:
	Player() {

	}
	Player(string playerName) {
		this->platerName = playerName;
	}
	vector<string> getHand() {
		return this->hand;
	}
	string getPlayerName() {
		return this->platerName;
	}
	void draw() {

	}
	;
private:
	string platerName;
	vector<string> hand;
	;

};
void createDeck(Card deck[52]);
void displayDeck(Card deck[52]);
void menu(Card deck[52]);
int getRand(int randMax);
Card cutDeck(Card deck[52]);
void shuflleDeck(Card deck[52]);


int getRand(int randMax) {
	int random_integer = rand() % randMax + 1;
	return random_integer;
}
void menu(Card deck[52]) {
	bool flag = true;
	while (flag) {
		int option;
		string name="";
		wcout << L"\n Welcome to Cribbage Game" << endl;
		//wcout << L"Declare how many players" << endl;
		//wcout << L"0. exit" << endl;
		//cin >> option;
		//for (int i = 0; i < option; i++)
		//{
		//	wcout << L"What's player" << i << L" Name";
		//}
		getline(cin, name);
			cout << name;
		
		/*
		if (option == 1)
		{
			createDeck(deck);
			displayDeck(deck);
		}	
		else if (option == 0)
		{
			flag = false;
		}*/

	}
}
Card cutDeck(Card deck[52]) {
	int rand = getRand(52);
	Card tempCard = deck[rand - 1];
	int num = 0;
	//**TBD 
	while (tempCard.getCardNum() == L"emp"&&num<52) {
		rand = getRand(52);
		tempCard = deck[rand - 1];
		num++;
	}
	if (num>52)
	{
		wcout << "Deck is empty";
	}
	else {
		deck[rand - 1].setCard(0, 0);
	}
	return tempCard;
}
void shuflleDeck(Card deck[52]) {

	int rand1, rand2;
	for (int i = 0; i < 52; i++)
	{
		rand1 = getRand(52);
		rand2 = getRand(52);
		do {
			rand2 = getRand(52);
		} while (rand1 == rand2);
		Card tempCard = deck[rand1 - 1];
		deck[rand1 - 1] = deck[rand2 - 1];
		deck[rand2 - 1] = tempCard;
	}
}
void displayDeck(Card deck[52]) {
	for (int k = 0; k < 52; k++)
	{
		if (k % 13 == 0 && k != 0)
		{
			wcout << endl;
		}
		wcout << " ";
		deck[k].display();
	}
}

void createDeck(Card deck[52]) {

	for (int i = 1; i <= 4; i++)
	{
		for (int k = 1; k <= 13; k++)
		{
			Card card;
			card.setCard(i, k);
			deck[(i - 1) * 13 + k - 1] = card;
		}
	}
}

 
int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	srand(time(NULL));
	Card deck[52];
	vector<Player> Players;
	// *** TBD add vector to store all the cuts
	menu(deck);
	return 0;
}