/*****************************************************
* Author: Austin Alberd
* Date: 12/04/2024
* Filename: driver.cpp 
* Purpose: Driver file for the baccarat program
******************************************************/

#include "header.h"

int main(){
    //Vars
    int numPlayers= 0;
    char playerChoice;

    //Get the basics started
    cout << "_____   ____   ____  ____   ____  _____   ____  _____ " << endl;
    cout << "| () ) / () \\/ (__`/ (__` / () \\ | () ) / () \\|_   _|" << endl;
    cout << "|_()_)/__/\\__\\____)\\____)/__/\\__\\|_|\\_\\/__/\\__\\ |_|  " << endl << endl;
    cout << "How many players are at the table? ";
    cin >> numPlayers;

    while (numPlayers <= 0 || !cin){
        cin.clear();
        cin.ignore(10000000,'\n');
        cout << "Hey there enter a valid number of players: ";
        cin >> numPlayers;
    }

    //Make the game
    Game currGame(numPlayers);

    //Initialize the game 
    currGame.initGame();
    

    do
    {
        //get the bets
        currGame.getBets();
        if(currGame.firstRound()){
            currGame.processWinState();
        }else if(currGame.finalRound()){
            currGame.processWinState();
        }else{
            return 0;
        }
        currGame.cleanUpGame();

        cout << endl << endl;
        cout << "Do you want to play another round (y/n)? ";
        cin >> playerChoice;
        
        cout << endl << endl;
    } while (playerChoice != 'n');
    return 0;
}