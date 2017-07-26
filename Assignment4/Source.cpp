#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
const wstring CARD_NUM[] = { L"emp",L"A",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"10",L"J",L"Q",L"K" };

class Card {
	
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
	enum SUITE
	{
		emp, club, diamond, heart, spade
	};
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
	wcout << L"(" << cardValue << L")";
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

class Player {
public:	
	Player(wstring playerName) {
		this->platerName = playerName;
		score = 0;
	}
	vector<Card> getHand() {
		return this->hand;
	}
	void setHand(vector<Card> hand) {
		this->hand = hand;
	}
	wstring getPlayerName() {
		return this->platerName;
	}
	void setpositionIndex(int i) {
		this->positionIndex = i;
	}
	int getScore() {
		return this->score;
	}
	void draw() {

	}
	;
private:
	wstring platerName;
	int positionIndex;
	vector<Card> hand;
	int score;
	;

};


class Board {	
public:
	enum direction { east, south, west, north };
	Board(vector<Player> players, vector<Card> deck) {
		this->deck = deck;
		this->players = players;
		roundScore = 0;
	}
	void displayBoard() {

	}
	void printScore() {
		wcout << "##################################################" << endl;
		wcout<< "Score: " << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			wcout << this->players[i].getPlayerName() << " :                 " << this->players[i].getScore()<<endl;
		}
		
	}
	vector<Card> getCrib() {
		return this->crib;
	}
	void setCrib(vector<Card> crib) {
		this->crib= crib;
	}
	Card getCut() {
		return this->cut;
	}
	void setCut(Card c) {
		this->cut = c;
	}
	vector<Card> getDeck() {
		return this->deck;
	}


	vector<Player> getPlayers() {
		return this->players;
	}
	void addToPlayers(Player p) {
		this->players.push_back(p);
	}

	int getRoundScore() {
		return roundScore;
	}
	;
private:
	vector<Card> deck;
	Card cut;
	vector<Card> roundPlay;
	vector<Card> crib;
	vector<vector<Card>> playerHand; //store original hands
	vector<Player> players;	
	int roundScore;
};

class Game {
public :	
	Game(Board& myboard)  {
		this->myboard = &myboard;
	}
	void postGameProcess() {

	}
	void pegging() {

	}
	Board* getBoard() {
		return myboard;
	}
	;
private :
	int totalScore;
	Board *myboard;
};


int main() {
	vector<Card> createDeck();
	void displayDeck(vector<Card> deck);
	void menu(Game myGame);
	int getRand(int randMax);
	Card drawCard(vector<Card>&deck);
	Card cutDeck(vector<Card>&deck);
	void shuflleDeck(vector<Card> deck);

	_setmode(_fileno(stdout), _O_U16TEXT);
	srand(time(NULL));
	vector<Card> deck = createDeck();
	vector<Player> Players;
	Board myBoard(Players, deck);
	Game myGame(myBoard);
	menu(myGame);
	return 0;
}



int getRand(int randMax) {
	int random_integer = rand() % randMax + 1;
	return random_integer;
}

Card drawCard(vector<Card>&deck) {
	int rand = getRand(52);
	Card tempCard = deck[rand - 1];
	int num = 0;
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
		deck[rand - 1].display();
	}
	return tempCard;
}
Card cutDeck(vector<Card>&deck) {
	int rand = getRand(52);
	Card tempCard = deck[rand - 1];
	int num = 0;
	while (tempCard.getCardNum() == L"emp"&&num<52) {
		rand = getRand(52);
		tempCard = deck[rand - 1];
		num++;
	}
	if (num>52)
	{
		wcout << "Deck is empty";
	}
	return tempCard;
}

void shuflleDeck(vector<Card>&deck) {

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
void displayDeck(vector<Card>&deck) {
	
	for (int k = 0; k < 52; k++)
	{
		if (k % 13 == 0 && k != 0)
		{
			wcout << endl;
		}
		wcout << " ";
		deck[k].display();
	}
	wcout << endl;
}

vector<Card> createDeck() {
	vector<Card> deck;
	for (int i = 1; i <= 4; i++)
	{
		for (int k = 1; k <= 13; k++)
		{
			Card card;
			card.setCard(i, k);
			deck.push_back(card);
		}
	}
	return deck;
}
void menu(Game myGame) {
	//bool flag = true;
	//while (flag) {
	int option;
	wcout << L"\n Welcome to Cribbage Game" << endl;
	wcout << L"Declare how many players" << endl;
	wcout << L"Please enter Name" << endl;
	//********* TBD add name
	wstring names[2] = { L"Di",L"Mike"};
	for (int i = 0; i < 2; i++)
	{
		Player tempPlayer(names[i]);
		myGame.getBoard()->addToPlayers(tempPlayer);
	}
	int playerNum = myGame.getBoard()->getPlayers().size();
	vector<Player> tempPlayers = myGame.getBoard()->getPlayers();
	vector<Card> tempDeck = myGame.getBoard()->getDeck();
	//*********  TBD design seat
	wcout << "Players please pick your seat"<<endl; 
	for (int i = 0; i < playerNum; i++)
	{
		tempPlayers[i].setpositionIndex(i);
	}
	//*************** Compare biggest cut   int biggestCutValue=0;
	wcout << L"game commence"<<endl;
	wcout << "The deck has been cut with the following results. "<<endl;
	for (int i = 0; i < playerNum; i++)
	{
		wcout << L"Player " << i << ": " << tempPlayers[i].getPlayerName() << "Cut";
		cutDeck(tempDeck).display();
		wcout << endl;
	}
	wcout << "Di is the Dealer"<<endl;
	wcout << "Status: The dealer will now shuffle the deck and start the match." << endl;
	shuflleDeck(tempDeck);

	wcout << "##########################################################################" << endl;
	for (int i = 0; i < playerNum; i++)
	{
		for (int i = 0; i < 6; i++) //2 person 6 cards
		{
			drawCard(tempDeck);

		}
	}
	myGame.getBoard()->printScore();





	//}
}