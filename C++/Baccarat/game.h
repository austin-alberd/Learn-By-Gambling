#ifndef GAME_H
#define GAME_H

/*****************************************************
* Author: Austin Alberd
* Date: 12/06/2024
* Filename: game.h 
* Purpose: Class definition for the game class.
******************************************************/
#include <iomanip>
#include <iostream>
#include <string>
#include <ctime>
#include <random>
using namespace std;

class Game{ 
    private:
        //Structs
        struct Player{
            bool bet;     //1 for banker 0 for player
            double money; //how much money the player has.
            double betAmnt;
            //Constructor so stuff does not break
            Player(){
                bet = 0;
                betAmnt = 0;
                money = -1;
            }
        };

        struct Table{
            //Trackers for the number of cards in hand
            int numCardsPlayerHand = 0;
            int numCardsDealerHand = 0;
            //Totals of cards in hands
            int playerTotal = 0;
            int dealerTotal = 0;
            int playerHand[3] = {0,0,0}; //Integer array for player hand
            int dealerHand[3] = {0,0,0}; //Integer array for dealer hand
            bool whoWin = 0;//1 for banker 0 for player
        };

        //Vars
        int numPlayers;


        //Arrays
        Player *players;

        //Game Table Struct
        Table gameTable;

        //Helper functions
        void printDecks();
        int totalCards(int * deck, int numElements);

    public:
        //Constructors
        Game(){
            numPlayers = 0;
        }
        Game(int _numPlayers){
            numPlayers = _numPlayers;
        };

        //Destructors
        ~Game(){
            delete [] players;
        }

        //Function Prototypes
        void initGame();
        void getBets();
        bool firstRound();
        bool finalRound();
        void processWinState();
        void cleanUpGame();
};

#endif
