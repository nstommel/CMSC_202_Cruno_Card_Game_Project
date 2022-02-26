
/**********************************************
 * File:    CrunoGame.h
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This header file includes the critically important declaration of the 
 * derived CrunoGame class. Notice the added private attributes m_special 
 * (Keeps track of special of last played card), m_seed (Stores initial srand() 
 * seed in case stock runs out and needs to be reshuffled as discard), m_reversed 
 * (Tells the game whether to proceed in a reverse direction), m_skip (Tells the game 
 * whether to skip a player), m_showCount, (Keeps track of how many times card is shown),
 * and m_turns (Keep track of how many turns/plays have been made in the game.
 * 
 * Additional useful methods include getters and setters for these attributes, 
 * as well as helper methods like printStock() and printDiscard() to check contents of
 * the stock and discard piles
 *
 **********************************************/

#ifndef CRUNOGAME_H
#define CRUNOGAME_H

#include "game.h"

//class CrunoGame inherits from class Game
class CrunoGame : public Game {

public:
    
    //CrunoGame Constructor
    CrunoGame();
    
    //Destructor (doesn't require modification from original ~Game() destructor)
    ~CrunoGame();
    
    //Initialize CrunoGame with new Cruno cards
    void initialize(int numPlayers);
    
    //Override for sole purpose of setting seed value 
    void startGame(unsigned int seed);
    
    //***IMPORTANT*** 
    //Override of Game::dealOneCard() for reshuffling of cards when m_stock runs out!
    Card * dealOneCard();
    
    //***NOTE***
    //The following three function are used in the Cruno cards' 
    //playCard() method as setters
    
    //Used to toggle m_reversed mode true/false
    void changeDirection();
    
    //Used to toggle m_skip true/false
    void toggleSkip();
    
    //Used as setter to keep track of last card's special type in playCard() method
    void setSpecial(unsigned int special);
    
    //Used as getter in special cards' playable() method for the game's current
    //m_special state
    unsigned int currentSpecial();
    
    //Overrides virtual Game() method
    unsigned int nextPlayer();
    
    //Overrides virtual Game playerAfter() method
    unsigned int playerAfter(unsigned int thisPlayer);
    
    //Used as getter for m_showCount in CrunoPlayer::showCardToPlayer(...)
    unsigned int currentShowCount();
    
    //Used as setter for m_showCount in CrunoPlayer::showCardToPlayer(...) 
    void setShowCount(unsigned int count);
    
    //Used as getter for m_turns in CrunoPlayer::playOneCard(...)
    unsigned int getNumTurns();
    
    //Used as setter for m_turns in CrunoPlayer::playOneCard(...)
    void incrementNumTurns();
    
    //Helper method to check contents of stock
    void printStock();
    
    //Helper method to check contents of discard
    void printDiscard();
    
    
private:
    
    unsigned int m_special;   //Keeps track of special of last played card
    
    unsigned int m_seed;      //Keeps track of initial srand() seed in case stock runs out 
                              //and needs to be reshuffled as discard
    
    bool m_reversed;          //Tells the game whether to proceed in a reverse direction
    
    bool m_skip;              //Tells the game whether to skip a player
    
    unsigned int m_showCount; //Keeps track of how many times card is shown
    
    unsigned int m_turns;     //Neat addition to keep track of turns
    
};

#endif /* CRUNOGAME_H */

