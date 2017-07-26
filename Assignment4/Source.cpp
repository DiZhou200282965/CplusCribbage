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
	int  getCardIndexValue() {
		return this->cardIndexValue;
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
	int cardIndexValue;
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
	cardIndexValue = cardNum;
	this->cardValue = cardNum > 10 ? 10 : cardNum;
}

class Player {
public:	
	Player(){}
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
	int getScore() {
		return this->score;
	}
	void setCut(Card c) {
		cut = c;
	}
	Card getCut() {
		return cut;
	}
	void draw() {

	}
	void printHand() {
		for (int i = 0; i < hand.size(); i++)
		{
			hand[i].display();
			if ((i+1)!=hand.size())
			{
				wcout << ",";
			}			
		}
	}
	;
private:
	wstring platerName;
	
	vector<Card> hand;
	int score;
	Card cut;
	;

};


class Board {	
public:	
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
	void setFirstHand(vector<vector<Card>> fh) {
		this->playerHands = fh;
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
	void setDealer(Player dealer) {
		this->dealer = dealer;
	}
	bool isDealer(Player p) {
		return p.getPlayerName() == dealer.getPlayerName();
	}
	;
private:
	vector<Card> deck;
	Card cut;
	vector<Card> roundPlay;
	vector<Card> crib;
	vector<vector<Card>> playerHands; //store original hands
	vector<Player> players;	
	Player dealer;
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
void displayDeck(vector<Card>deck) {

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

Player cutProcess(vector<Player>& tempPlayers, vector<Card>& tempDeck) {
	bool tie;
	vector<Card>  cutPool;
	Player p;
	int biggest = 0;
	do {
		//display players and its cut
		tie = false;
		for (int k = 0; k < tempPlayers.size(); k++)
		{
			tempPlayers[k].setCut(cutDeck(tempDeck));
			wcout << tempPlayers[k].getPlayerName() << ": ";
			tempPlayers[k].getCut().display();
			wcout << endl;
			if (tempPlayers[k].getCut().getCardIndexValue()>biggest)
			{
				biggest = tempPlayers[k].getCut().getCardIndexValue();
			}
		}
		int counter = 0;
		for (int k = 0; k < tempPlayers.size(); k++)
		{
			if (tempPlayers[k].getCut().getCardIndexValue() == biggest)
			{
				counter++;
				p = tempPlayers[k];
			}
		}

		if (counter>1)
		{
			tie = true;
			wcout << "There is a tie, recut";
		}
	} while (tie);

	return p;
}
int main() {
	vector<Card> createDeck();
	void displayDeck(vector<Card> deck);
	void menu(Game myGame);
	int getRand(int randMax);
	Card drawCard(vector<Card>&deck);
	Card cutDeck(vector<Card>&deck);
	void shuflleDeck(vector<Card> deck);
	Player cutProcess(vector<Player>& tempPlayers, vector<Card>& tempDeck);
	_setmode(_fileno(stdout), _O_U16TEXT);
	srand(time(NULL));
	vector<Card> deck = createDeck();
	vector<Player> Players;
	Board myBoard(Players, deck);
	Game myGame(myBoard);
	menu(myGame);
	system("pause");
	return 0;
}




void menu(Game myGame) {
	 int drawNum, toCrib, fromDeck;

	//bool flag = true;
	//while (flag) {
	int input1,input2;

	wcout << L"\n Welcome to Cribbage Game" << endl;
	wcout << L"Declare how many players" << endl;
	while (!(wcin >> input1)|| input1>4) {
		wcout << "you can only decare 2-4 players";
		wcin.clear();
		wcin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if (input1 ==2 )
	{
		drawNum = 6;
		toCrib = 2;
		fromDeck = 0;
	}
	else if (input1==3)
	{
		drawNum = 5;
		toCrib = 1;
		fromDeck = 0;
	}
	else if (input1==4)
	{
		drawNum = 5;
		toCrib = 1;
		fromDeck = 0;
	}
	wchar_t str[50];
	wstring wstr;
	for (int i = 0; i < input1; i++)
	{
		wcout<< "Player " <<i << ",please enter Name " << endl;
		ws(wcin); // get rid of space
		wcin.getline(str, 50);
		wstr = str;
		Player tempPlayer(str);
		myGame.getBoard()->addToPlayers(tempPlayer);
	}
	

	// temp variables declaration
	Board *tempBoard = myGame.getBoard();
	int playerNum = tempBoard->getPlayers().size();
	vector<Player> tempPlayers = tempBoard->getPlayers();
	vector<Card> tempDeck = tempBoard->getDeck();


	wcout << "Players please take your seats." << endl;
	//*************** Compare biggest cut   int biggestCutValue=0;

	wcout << L"Status: The match is ready to start."<<endl;
	wcout << "The deck has been cut with the following results. "<<endl;


	// cutting process 
	;

	wcout <<endl<< cutProcess(tempPlayers, tempDeck).getPlayerName()<< "  "<< "is the Dealer"<<endl;
	wcout << "Status: The dealer will now shuffle the deck and start the match." << endl;
	shuflleDeck(tempDeck);

	
	vector<vector<Card>> totalHands;
	for (int k = 0; k < playerNum; k++)
	{
		vector<Card> hand;
		for (int i = 0; i < 6; i++) //2 person 6 cards
		{
			hand.push_back(drawCard(tempDeck));		
			tempPlayers[k].setHand(hand);	 // save to player.hand		
		}
		totalHands.push_back(hand); // save to fist board.firsthand 
	}
	tempBoard->setFirstHand(totalHands);
	displayDeck(tempDeck);
	tempBoard->printScore();

	for (int k = 0; k < playerNum; k++)
	{
		wcout << tempPlayers[k].getPlayerName()<< ": ";
		tempPlayers[k].printHand();
		wcout << endl;
	}
}
