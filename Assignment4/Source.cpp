#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>


using namespace std;
const wstring CARD_NUM[] = { L"emp",L"A",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"10",L"J",L"Q",L"K" };

class Card {

public:
	Card() {
		this->cardNum = CARD_NUM[0];
		suit = emp;
		this->cardValue = 0;
		suiteIndex = 0;
	}
	int  getCardIndexValue() {
		return this->cardIndexValue;
	}
	void display() {
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
	void setCard(int suiteIndex, int cardNum) {
		this->suiteIndex = suiteIndex;
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
	int getsuiteIndex() {
		return this->suiteIndex;
	}
	wstring getCardNum() {
		return this->cardNum;
	}
	int getCardValue() {
		return this->cardValue;
	}
	~Card() {};
private:
	enum SUITE
	{
		emp, club, diamond, heart, spade
	};
	int suiteIndex;
	wstring cardNum;
	SUITE suit;
	int cardValue;
	int cardIndexValue;
};

class Player {
public:
	Player() {}
	Player(wstring playerName) {
		statusGo = false;
		this->platerName = playerName;
		score = 0;
	}
	void setGoStatus() {
		this->statusGo = true;
	}
	bool getGoStatus() {
		return statusGo;
	}
	vector<Card> getHand() {
		return this->hand;
	}
	void emptyHandByIndex(int i) {
		this->hand[i].setCard(0, 0);
	}
	void removeFromHand(int i) {
		this->hand.erase(hand.begin() + i);
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
	void addToScore(int add) {
		this->score += add;
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
			if ((i + 1) != hand.size())
			{
				wcout << ",";
			}
		}
	}
	;
private:
	int suiteIndex;
	wstring platerName;
	bool statusGo;
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
	
	void setFirstHand(vector<vector<Card>> fh) {
		this->playerHands = fh;
	}
	vector<vector<Card>> getFirstHand() {
		return this->playerHands;
	}
	vector<Card> getCrib() {
		return this->crib;
	}
	void pushToCrib(Card c) {
		this->crib.push_back(c);
	}
	void pushToRoundPlay(Card c) {
		this->roundPlay.push_back(c);
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

	vector<Card> getRoundPlay() {
		return this->roundPlay;
	}
	void clearRoundPlay() {
		this->roundPlay.clear();
	}
	void clearCrib() {
		this->crib.clear();
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

	void setRoundScore(int i) {
		this->roundScore = i;
	}
	bool setRoundScore(Card c) {

		if (c.getCardValue() + getRoundScore() > 31) {
			wcout << endl << c.getCardValue() << " + " << getRoundScore() << " >31, Please choose another card.\n";
			return false;
		}
		else
		{
			this->roundScore += c.getCardValue();
			return true;
		}
	}

	void setDealer(Player dealer) {
		this->dealer = dealer;
		wcout << endl << dealer.getPlayerName() << " " << "is the Dealer" << endl;
	}
	wstring getDealerName() {
		return this->dealer.getPlayerName();
	}
	Player getDealer() {
		return this->dealer;
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
			wcout << "There is a tie, recut" << endl;
		}
	} while (tie);

	return p;
}


class Game {
public:
	bool gameFlag = true;
	Game(Board& myboard) {
		this->myboard = &myboard;
	}
	void postGameProcess() {

	}

	Board* getBoard() {
		return myboard;
	}
	bool canPlay(vector<Card> hand) {
		int  intFlag = 0,
			roundScore = myboard->getRoundScore();
		for (int i = 0; i < hand.size(); i++)
		{
			if (roundScore + hand[i].getCardValue() > 31) 	intFlag++;
		}
		if (intFlag == hand.size()) return false;
		else return true;
	}

	void setlastTurnPI(Player p, vector<Player> ps) {
		// figure next player
		for (int i = 0; i < ps.size(); i++)
		{

			if (ps[i].getPlayerName() == p.getPlayerName())
			{
				lastTurnPI = i;
			}
		}
	}
	int getnextTurnPI(int lastTurnPI, vector<Player> ps) {
		int nextTurnPI;
		if ((lastTurnPI + 1) == ps.size()) nextTurnPI = 0;
		else nextTurnPI = lastTurnPI + 1;
		return nextTurnPI;
	}
	int getlastTurnPI() {
		return lastTurnPI;
	}
	int getLastPlayCarPI() {
		return this->lastPlayCardPI;
	}
	void setLastPlayCarPI(Player p, vector<Player> ps) {
		for (int i = 0; i < ps.size(); i++)
		{
			if (ps[i].getPlayerName() == p.getPlayerName())
			{
				this->lastPlayCardPI = i;
			}
		}
	}
	void menu() {



		game_greeting(); //greeting and create players

						 // temp variables declaration		
		int playerNum = myboard->getPlayers().size();
		vector<Player> tempPlayers = myboard->getPlayers();
		vector<Card> tempDeck = myboard->getDeck();

		wcout << "Players please take your seats." << endl;
		wcout << L"Status: The match is ready to start." << endl;
		wcout << "The deck has been cut with the following results. " << endl;
		Player dealer = cutProcess(tempPlayers, tempDeck);
		myboard->setDealer(dealer);
	
		
		wcout << "Status: The dealer will now shuffle the deck and start the match." << endl;
	
	
	do{
		wcout << "Shuffling deck ......" << endl;
		shuflleDeck(tempDeck);
		wcout << "Draw cards ......" << endl;	
		for (int k = 0; k < playerNum; k++)
		{
			vector<Card> hand;
			for (int i = 0; i < drawNum; i++) // use draw num
			{
				hand.push_back(drawCard(tempDeck));
				tempPlayers[k].setHand(hand);	 // save to player.hand		
			}			
		}	
		
		displayBoard(tempDeck, myboard, tempPlayers);

		wcout << "Status: Creating the crib for the round." << endl;	
		int pHandsize, intIn;
		for (int k = 0; k < playerNum; k++) // loop players
		{
			displayBoard(tempDeck, myboard, tempPlayers);
			pHandsize = tempPlayers[k].getHand().size(); // get hand size			
			for (int i = 0; i < toCribNum; i++)  // loop toCribNum
			{
				displayBoard(tempDeck, myboard, tempPlayers);
				wcout << tempPlayers[k].getPlayerName() << ", what card would you like to discard to the Crib? (input by order, between 1~" << pHandsize << ")" << endl;
				while (!(wcin >> intIn) || intIn>pHandsize || intIn<1) {
					if (intIn>pHandsize || intIn<1)
					{
						wcout << "you must choose between 1~" << pHandsize << ", no alphabet character allowed";
					}
					wcin.clear();
					wcin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				myboard->pushToCrib(tempPlayers[k].getHand()[intIn - 1]); // push to crib vector
				wcout << tempPlayers[k].getPlayerName() << " played ";
				tempPlayers[k].getHand()[intIn - 1].display(); wcout << endl;
				tempPlayers[k].removeFromHand(intIn - 1);
			}
		}
		displayBoard(tempDeck, myboard, tempPlayers);

		if (fromDeckNum == 1)
		{
			Card c = drawCard(tempDeck);
			c = drawCard(tempDeck);
			c.display();
			wcout << "was cut from deck to Crib (3 players)" << endl;
			myboard->pushToCrib(c);
		}

		//cc.~Card;
		Card tc = drawCard(tempDeck);
		myboard->setCut(tc);


		// dealer cut
		wcout << "Status: " << dealer.getPlayerName() << " cut the deck revealing the ";
		tc.display();
		setlastTurnPI(dealer, tempPlayers);
		wcout << "\nStatus : The round pegging can now commence." << endl;


		// save to fist hands
		vector<vector<Card>> totalHands;
		for (int i = 0; i < tempPlayers.size(); i++)
		{
			totalHands.push_back(tempPlayers[i].getHand()); // save to fist board.firsthand 	
		}		
		myboard->setFirstHand(totalHands);

		


		// Pegging
		int k = getnextTurnPI(getlastTurnPI(), tempPlayers);
		while (canPegging(tempPlayers)) {
			displayBoard(tempDeck, myboard, tempPlayers);
			pHandsize = tempPlayers[k].getHand().size(); // get hand size				

			if (canPlay(tempPlayers[k].getHand()) && pHandsize != 0)
			{
				wcout << endl << tempPlayers[k].getPlayerName() << ", what card would you like to play? (input by order, between 1~" << pHandsize << ")" << endl;
				while (!(wcin >> intIn) || intIn>pHandsize || intIn <1 || !(myboard->setRoundScore(tempPlayers[k].getHand()[intIn - 1]))) {
					if (intIn>pHandsize || intIn <1)
					{
						wcout << "you must choose between 1~" << pHandsize << ", no alphabet character allowed";
					}
					wcin.clear();
					wcin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				myboard->pushToRoundPlay(tempPlayers[k].getHand()[intIn - 1]); // push to roundplay vector			
				wcout << tempPlayers[k].getPlayerName() << " played ";
				tempPlayers[k].getHand()[intIn - 1].display(); wcout << endl;
				tempPlayers[k].removeFromHand(intIn - 1);
			
				setLastPlayCarPI(tempPlayers[k], tempPlayers);			
			}
			else {
				tempPlayers[k].setGoStatus();
				// player can't play card ,go
				if (pHandsize == 0)
				{
					wcout << endl << tempPlayers[k].getPlayerName() << "has an empty hand, " << " GO ";
				}
				else {
					wcout << endl << tempPlayers[k].getPlayerName() << " can't play a card (sum more than 31), " << " GO " << endl;
				}
			}


			//game check
			int counter = 0;
			bool allGO;
			for (int i = 0; i < tempPlayers.size(); i++)
			{
				if (tempPlayers[i].getGoStatus())
				{
					counter++;
				}
			}
			if (counter == tempPlayers.size()) allGO = true;
			else   allGO = false;
			// check pairs, runs 15,31
			pegging_sumUp(myboard->getRoundPlay(), tempPlayers);
			pegging_pair(myboard->getRoundPlay(), tempPlayers);
			pegging_run(myboard->getRoundPlay(), tempPlayers);

		//	if (gameCheck(tempPlayers)) { break; }
			
		
			if (myboard->getRoundScore() == 31 || allGO)
			{
				if (allGO)
				{
					wcout << "no one can play," << tempPlayers[getLastPlayCarPI()].getPlayerName() << " played last card" << endl;
					tempPlayers[getLastPlayCarPI()].addToScore(1);
					wcout << tempPlayers[getLastPlayCarPI()].getPlayerName() << " got 1 point for playing the last card" << endl;
				}
				else  wcout << "round score reached 31, clearing round play" << endl;
				myboard->setRoundScore(0);
				myboard->clearRoundPlay();
				/*wcout << tempPlayers[getLastPlayCarPI()].getPlayerName() << " is the person who last played card " << endl;*/
			}

			if (++k >= tempPlayers.size())
			{
				k = 0;
			}
		}

	  // post game process
		wcout << "Status: All cards held by the players have been played.  Post-game counting to commence. " << endl;
		for (int i = 0; i < playerNum; i++)
		{
			postGameDisplay(tempDeck, myboard, tempPlayers);
			calPoints(myboard,tempPlayers);
		}

		myboard->clearRoundPlay();
		myboard->setRoundScore(0);
		myboard->clearCrib();	
			int num;
		for (int i = 0; i < tempPlayers.size(); i++)
		{
			if (tempPlayers[i].getPlayerName() == myboard->getDealer().getPlayerName())
			{
					num = i;
					if (i= tempPlayers.size()-1)
					{
						num = 0;
					}
			}
		}
		//set dealer to next person
		myboard->setDealer(tempPlayers[num + 1]);
	
}while(gameFlag);
} 

	;
private:
	int drawNum, toCribNum, fromDeckNum;
	int lastTurnPI; // last turns player index
	int lastPlayCardPI;
	int totalScore;
	Board *myboard;
	void calPoints(Board *myboard, vector<Player> tempPlayers){
		vector<int> nums;
		for (int i = 0; i < tempPlayers.size(); i++)
		{
			
			//tempBoard->getCut();
			//myboard->getCrib();
			vector<Card> pHand = myboard->getFirstHand()[i];//  players hand
			
			nums.push_back(myboard->getCut().getCardValue());
			for (int i = 0; i < pHand.size(); i++)
			{
				nums.push_back(pHand[i].getCardValue());
			}	
		};
		wcout << "Post game calculation is in construction!" << endl;
	/*	check15();
		checkPair();
		checkFlush();
		addd point to player
		*/

		//for crib 
		nums.clear();
		nums.push_back(myboard->getCut().getCardValue());
		for (int i = 0; i < myboard->getCrib().size(); i++)
		{
			nums.push_back(myboard->getCrib()[i].getCardValue());
		}
		/*	check15();
		checkPair();
		checkFlush();
		addd point to dealer
		*/
		
		
	}
	
	void pegging_run(vector<Card> roundPlay, vector<Player> &tempPlayers) {
		wcout <<  " peggin run checking still in construction !" << endl;
	}
	void pegging_pair(vector<Card> roundPlay, vector<Player> &tempPlayers) {
		int lastCardIndex = roundPlay[roundPlay.size() - 1].getCardIndexValue();
		//check if pair 
		if (roundPlay.size()>=2 && lastCardIndex == roundPlay[roundPlay.size() - 2].getCardIndexValue())
		{
			tempPlayers[getLastPlayCarPI()].addToScore(2);
			wcout << tempPlayers[getLastPlayCarPI()].getPlayerName() << " got 2 points for a pair" << endl;
		}		
		if (roundPlay.size() >= 3 && lastCardIndex == roundPlay[roundPlay.size() - 2].getCardIndexValue() && roundPlay[roundPlay.size() - 2].getCardIndexValue() == roundPlay[roundPlay.size() - 3].getCardIndexValue())
		{
			tempPlayers[getLastPlayCarPI()].addToScore(6);
			wcout << tempPlayers[getLastPlayCarPI()].getPlayerName() << " got 6 points for a royal pair!" << endl;
		}
		if (roundPlay.size()>=4 && lastCardIndex == roundPlay[roundPlay.size() - 2].getCardIndexValue() && roundPlay[roundPlay.size() - 2].getCardIndexValue() == roundPlay[roundPlay.size() - 3].getCardIndexValue())
		{
			tempPlayers[getLastPlayCarPI()].addToScore(12);
			wcout << tempPlayers[getLastPlayCarPI()].getPlayerName() << " got 12 points for a double pair royal !!!" << endl;
		}
	}
	void pegging_sumUp(vector<Card> roundPlay,vector<Player> &tempPlayers) {
		int sum=0;
		for (int i = 0; i < roundPlay.size(); i++)
		{
			sum += roundPlay[i].getCardValue();
		}	
		if (sum == 15 || sum == 31) {
			tempPlayers[getLastPlayCarPI()].addToScore(2);
			wcout << tempPlayers[getLastPlayCarPI()].getPlayerName() << " got 2 points for 15 or 31" << endl;
		}
		
	}
	bool canPegging(vector<Player> tempPlayers) {

		int counter = 0;
		for (int i = 0; i < tempPlayers.size(); i++)
		{
			if (tempPlayers[i].getHand().size() == 0)
			{
				counter++;
			}
		}
		if (counter == tempPlayers.size()) {	
			return false;

		}
		else  return true;	
	}
	bool gameCheck(vector<Player>tempPlayers) {
		bool myBool = true;
		for (int i = 0; i < tempPlayers.size(); i++)
		{
			if (tempPlayers[i].getScore() >= 121)
				myBool = false;
		}
		return myBool;

	}
	void postGameDisplay(vector<Card>tempDeck, Board *tempBoard, vector<Player>tempPlayers) {
		system("pause");
		system("cls");
		vector<vector<Card>> hands = myboard->getFirstHand();
		wcout << "  --------------------  Post-game counting --------------------------------  \n" << endl;
		wcout << " Cut : ";
		myboard->getCut().display();
		wcout << "\n\n Crib : ";
		for (int i = 0; i < myboard->getCrib().size(); i++)
		{
			myboard->getCrib()[i].display();
		}
		wcout << endl << endl;
		for (int i = 0; i < hands.size(); i++)
		{
			wcout << "Player  " << tempPlayers[i].getPlayerName() << "'s hand: ";
			for (int k = 0; k < hands[i].size(); k++)
			{
				hands[i][k].display();
			}
			wcout << endl << endl;
		}
		wcout << endl << "  -------------------- Score section  ------------------------------- \n" << endl;
		for (int i = 0; i < tempPlayers.size(); i++)
			wcout <<tempPlayers[i].getPlayerName() << " :                 " << tempPlayers[i].getScore() << endl;
	}
	void displayBoard(vector<Card>tempDeck, Board *tempBoard, vector<Player>tempPlayers) {
		system("pause");
		wcout << wstring(2, '\n');
		system("cls");
		wcout << "  -------------------- Deck section  --------------------------------  \n" << endl;
		wcout << " Cut : ";
		tempBoard->getCut().display();
		wcout << "\n Crib : ";
		if (tempBoard->getCrib().empty())
		{
			wcout << "none";
		}
		else {
			for (int i = 0; i < tempBoard->getCrib().size(); i++)
			{
				tempBoard->getCrib()[i].display();
			}
		}
		wcout << endl;
		//displayDeck(tempDeck);
		wcout << endl << "  -------------------- Score section  ------------------------------- \n" << endl;
		for (int i = 0; i < tempPlayers.size(); i++)
			wcout << tempPlayers[i].getPlayerName() << " :                 " << tempPlayers[i].getScore() << endl;


		if (!tempBoard->getRoundPlay().empty())
		{
			wcout << endl << "  -------------------- Round Played  ------------------------------ \n" << endl;
			wcout << "Round score : " << tempBoard->getRoundScore() << endl;
			wcout << "Round Play: " << endl;
			for (int i = 0; i < tempBoard->getRoundPlay().size(); i++)
			{
				tempBoard->getRoundPlay()[i].display();
			}
		}


		wcout << endl << "  -------------------- Player's hand   ------------------------------ \n" << endl;
		for (int k = 0; k < tempPlayers.size(); k++)
		{
			wcout << tempPlayers[k].getPlayerName();
			if (myboard->isDealer(tempPlayers[k].getPlayerName())) wcout << " <D> ";
			wcout << ": ";
			tempPlayers[k].printHand();
			wcout << endl << endl;
		}




	}

	void game_greeting() {
		int intIn;
		wcout << L"Welcome to Cribbage in C++.  Press Q at any time to quit." << endl;
		wcout << L"How many players are there (2, 3, or 4)? " << endl;
		while (!(wcin >> intIn) || intIn>4) {
			wcout << "you can only decare 2-4 players";
			wcin.clear();
			wcin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (intIn == 2)
		{
			drawNum = 6;
			toCribNum = 2;
			fromDeckNum = 0;
		}
		else if (intIn == 3)
		{
			drawNum = 5;
			toCribNum = 1;
			fromDeckNum = 1;
		}
		else if (intIn == 4)
		{
			drawNum = 5;
			toCribNum = 1;
			fromDeckNum = 0;
		}
		wchar_t str[50];
		wstring wstr;
		for (int i = 0; i < intIn; i++)
		{
			wcout << "Player " << i + 1 << ", please enter your name" << endl;
			ws(wcin); // get rid of space
			wcin.getline(str, 50);
			wstr = str;
			Player tempPlayer(str);
			getBoard()->addToPlayers(tempPlayer);
		}
	}
};


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
	myGame.menu();

	system("pause");
	return 0;
}
