
/**********************************************
 * File:    CrunoPlayer.h
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This header file includes the declaration of the derived CrunoPlayer class, 
 * its child class SmartCrunoPlayer,and its child class (for inclusion of pickSuit()) 
 * CheatingCrunoPlayer.
 * 
 * Notice the inclusion of attribute m_cgame, which is basically a downcast version 
 * of m_game as a CrunoGame pointer. This dynamic casting allows access through the 
 * CrunoGame link to the added methods in the CrunoGame class. (dynamic_cast is used
 * in the constructor). This attribute exists for ease of use and so that the m_game
 * pointer does not have to be downcast repeatedly to access CrunoGame methods. The added
 * function getGameLink() also allows access to this protected link in 
 * CrunoDraw2::showPlayerToCard() so that the game's methods can be called on the player
 * and actions can be performed directly.
 *
 **********************************************/

#ifndef CRUNOPLAYER_H
#define CRUNOPLAYER_H

#include "player.h"
#include "CrunoGame.h"

//Basic CrunoPlayer
//Note: this is the 'dumb' CrunoPlayer who uses the same strategy (or lack of strategy)
//as a normal base Player. However, 'dumb' CrunoPlayers still know to draw two cards
//upon previous play of a Draw2 card and to pick a new suit after play of a WildCard
class CrunoPlayer : public Player {
    
public:
    
    //CrunoPlayer constructor
    CrunoPlayer(Game *gptr, unsigned int numCards);
    
    //Important overloaded function that keeps track of how many times the card has
    //been shown to players (so that the first player shown the card can perform an
    //action like drawing two cards after being shown the Draw2 card)
    void showCardToPlayer(const Card* cptr, unsigned int player, bool oneCardLeft);
    
    //Unchanged from Player class for 'dumb' CrunoPlayer, but includes additional
    //turn/play counter for diagnostic purposes
    Card* playOneCard(bool& lastCard, bool& oneCardLeft);
    
    //Critical getter for the Player's link to the game
    CrunoGame* getGameLink();
    
protected:
    
    //Link into CrunoGame, downcast version of regular m_game attribute
    //so m_game doesn't need to be repeatedly downcast to access CrunoGame methods
    CrunoGame *m_cgame;
        
};

//Smart CrunoPlayer
//A smart Cruno Player chooses cards to play according to the playable cards in 
//their hand (not simply the first playable one), and picks the most common suit 
//in their hand after playing a Wildcard
//***NOTE*** inherits from CrunoPlayer so that m_cgame attribute and additional CrunoPlayer
//methods are available
class SmartCrunoPlayer : public CrunoPlayer {

public:
    
    //SmartCrunoPlayer constructor
    SmartCrunoPlayer(Game *gptr, unsigned int numCards);
    
    //Overrides 'dumb' CrunoPlayer's playOneCard(...) function so that strategy is
    //used when selecting cards
    Card* playOneCard(bool& lastCard, bool& oneCardLeft);
    
    //Overrides base class Player's pickSuit() method intelligently
    unsigned int pickSuit();
    
};

//Cheating CrunoPlayer
//A terrible, awful, no-good cheating Cruno Player converts a card to a Wildcard 8 when 
//they don't have any cards to play and picks their favored suit 
//(inheriting smartCrunoPlayer's) pickSuit() method and overriding
//its playOneCard() method
//***NOTE*** further inherits from SmartCrunoPlayer so that intelligent pickSuit() 
//method can be used without repeating code and CrunoPlayer 
//functions/attributes are also accessible
class CheatingCrunoPlayer : public SmartCrunoPlayer {
    
public:
    
    //CheatingCrunoPlayer constructor
    CheatingCrunoPlayer(Game *gptr, unsigned int numCards);
    
    //Overrides 'smart' CrunoPlayer's playOneCard(...) function to enable cheating
    //when a playable card is not found in hand
    Card* playOneCard(bool& lastCard, bool& oneCardLeft);
    
};

#endif /* CRUNOPLAYER_H */

