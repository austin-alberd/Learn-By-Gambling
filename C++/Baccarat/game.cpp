/*****************************************************
* Author: Austin Alberd
* Date: 12/04/2024
* Filename: game.cpp
* Purpose: The game class for the baccarat program.
******************************************************/

#include "game.h"

//Helper Functions
/*****************************************************
* Function Name: printDecks()
* Purpose: Print the decks in a pretty manner
******************************************************/
void Game::printDecks(){
    cout << endl;
    cout << "--- Player Hand ---" << endl;
    for (int i = 0; i < gameTable.numCardsPlayerHand; i++){
        cout << "Card " << i+1 << ": "<< gameTable.playerHand[i] << endl;
    }
    cout << "Total: " << gameTable.playerTotal<< endl;
    cout << endl;

    cout << "--- Dealer Hand ---" << endl;
    for (int i = 0; i < gameTable.numCardsDealerHand; i++){
        cout << "Card " << i+1 << ": "<< gameTable.dealerHand[i] << endl;
    }
    cout << "Total: " << gameTable.dealerTotal<< endl;
}

/*****************************************************
* Function Name: totalCards()
* Purpose: Total the cards
******************************************************/
int Game::totalCards(int * deck, int numElements){
    int cumSum = 0;
    for(int i = 0; i < numElements; i++){
        cumSum += *(deck+i);
    }
    if (cumSum > 9){
        return cumSum - 10;
    }else{
        return cumSum;
    }
}
 
//Public Functions
/*****************************************************
* Function Name: initGame()
* Purpose: Setsup the game. Gets the money and sets the bets
******************************************************/ 
void Game::initGame(){
    srand(time(0));
    //Dynamically Allocate the arrays
    players = new Player[numPlayers];

    //Get the money
    for(int i = 0; i < numPlayers; i++){
        cout << "Howdy player " << i+1 << " how much money do you want to put in: $ ";
        cin >> players[i].money;
    }
    cout << endl << endl;
}

/*****************************************************
* Function Name: getBets()
* Purpose: Get the bets from the players
******************************************************/
void Game::getBets(){
    for (int i = 0; i < numPlayers; i++){
        cout << "Howdy player " << i+1 << " how much money do you want to bet: $";
        cin >> players[i].betAmnt;

        cout <<"Howdy player " << i+1 << " who do you want to bet on banker (1) or player (0): ";
        cin >> players[i].bet;

        cout << endl;
    }
}

/*****************************************************
* Function Name: firstRound()
* Purpose: Does the first round of the game. Returns false if there is no win. Returns true if there is a win
******************************************************/
bool Game::firstRound(){
    cout << endl << "--- First Round ---" << endl;
    //Deal the initial cards
    for (int i = 0; i < 2; i++){
        gameTable.dealerHand[i] = rand()%10;
        gameTable.playerHand[i] = rand()%10;
        gameTable.numCardsDealerHand += 1;
        gameTable.numCardsPlayerHand += 1;
    }

    // Total the cards
    gameTable.dealerTotal = totalCards(gameTable.dealerHand,gameTable.numCardsDealerHand);
    gameTable.playerTotal = totalCards(gameTable.playerHand, gameTable.numCardsPlayerHand);

    //print it out
    printDecks();
    
    //Check for a natural win
    if (gameTable.dealerTotal == 8 || gameTable.dealerTotal == 9){
        gameTable.whoWin = 1;
        return true;
    }else if (gameTable.playerTotal == 8 || gameTable.playerTotal == 9){
        gameTable.whoWin = 0;
        return true;
    }


    return false;
}

/*****************************************************
* Function Name: finalRound()
* Purpose: Runs the final round of the game
******************************************************/
bool Game::finalRound(){
    cout << endl << "--- Final Round ---" << endl;
    //Handle the special cards for the player
    if (gameTable.playerTotal <= 5 && gameTable.playerTotal >= 0){
       gameTable.playerHand[2] = rand()%10;
       gameTable.numCardsPlayerHand += 1;
       gameTable.playerTotal = totalCards(gameTable.playerHand,gameTable.numCardsPlayerHand);
    }

    //Handle the special cards for the dealer
    if (gameTable.dealerTotal <= 2 && gameTable.dealerTotal >=0){
        gameTable.dealerHand[2] = rand()%10;
        gameTable.numCardsDealerHand += 1;
        gameTable.dealerTotal = totalCards(gameTable.dealerHand,gameTable.numCardsDealerHand);
    }

    //Print out the decks and make it look all pretty
    printDecks();
    cout << endl << endl;

    //Check if there is a win or not
    if (gameTable.dealerTotal > gameTable.playerTotal){
        gameTable.whoWin = 1;
        return true;
    } else if (gameTable.playerTotal > gameTable.dealerTotal){
        gameTable.whoWin = 0;
        return true;
    }else{
        return false;
    }
}

/*****************************************************
* Function Name: processWinState()
* Purpose: Run when a winner has been determined.
******************************************************/
void Game::processWinState(){
    bool winState = gameTable.whoWin;

    //Print out the winners and losers and update the money.
    cout << endl << "--- WINNERS HAVE BEEN DETERMINED ---" << endl;
    for (int i = 0; i < numPlayers; i++){
        if (players[i].bet == winState){
            cout << "Player " << i + 1 << " won" << endl;
            players[i].money += players[i].betAmnt;
        }else{
            cout << "Player " << i + 1 << " lost" << endl;
            players[i].money -= players[i].betAmnt;
        }
    }
}

/*****************************************************
* Function Name: cleanUpGame()
* Purpose: Gets ready for the next game.
******************************************************/
void Game::cleanUpGame(){
    //Clean up the players list
    for (int i = 0; i < numPlayers; i++){
        players[i].bet = 0;
        players[i].betAmnt = 0;
    }

    //Clean up the table
    gameTable.numCardsDealerHand=0;
    gameTable.numCardsPlayerHand=0;
    gameTable.dealerTotal = 0;
    gameTable.playerTotal = 0;

    //Print out player stats
    cout << endl << endl;
    for (int i = 0; i < numPlayers; i++){
        cout << "--- Player " << i + 1 << " ---" << endl;
        cout << "Money: $" << players[i].money << endl;
        cout << "----------------" << endl;
    }
}