
/**********************************************
 * File:    Cruno8.h
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This header file includes the declaration of the Cruno8 and CrunoCard 
 * classes. CrunoCard is the only direct derivative of the Card Class, every 
 * other card class inherits from the CrunoCard Class. This is necessary for 
 * type comparison, granting each special (and normal) CrunoCard a protected
 * attribute m_special.
 *
 **********************************************/

#ifndef CRUNO8_H
#define CRUNO8_H

#include "card.h"
#include "CrunoGame.h"

//Minimally extended version of the basic Card class with m_special attribute
//So that card types can be compared in a sensible manner.
//NOTE: ALL OTHER CRUNO CARDS INHERIT DIRECTLY FROM THE CRUNOCARD CLASS
//class CrunoCard inherits from class Card
class CrunoCard : public Card {

public:
    
    //Convenient scoped constants to avoid assigning "magic numbers" as m_special type
    static const unsigned int WildCard = 15;
    static const unsigned int Skip = 16;
    static const unsigned int Reverse = 17;
    static const unsigned int DrawTwo = 18;
    static const unsigned int NonSpecial = 19;
    
    //CrunoCard constructor with the all-important special parameter to set m_special
    //upon construction
    CrunoCard(unsigned int s, unsigned int p, unsigned int special);
    
    //***Important*** Besides basic card functionality,
    //playCard sets m_special to zero with NonSpecial CrunoCards
    //so that special cards are not matched inappropriately after 'normal' 
    //base class cards have been played. Without this method, other special 
    //cards could be considered playable due to matching special type 
    //(because m_special never gets reset after the play of a base class Card)
    void playCard(Game *gptr, Player *pptr);
    
    //Basic getter for the card's current special type m_special
    unsigned int getSpecial();
    
protected:
    
    //Key addition of m_special attribute present in every derived CrunoCard
    unsigned int m_special;
    
};

//Wildcard class Cruno8 inherits from derived class CrunoCard
class Cruno8 : public CrunoCard {

public:
    
    //Wildcard constructor
    Cruno8();
    
    //Overloaded method to print card.
    //***NOTE*** Wildcards (in the fashion of Crazy Eights) do not require a suit
    //as they are playable at any time and the suit is set after the card is played
    string toString();
    
    //Overloaded method that simply returns true (Wildcards are playable at any time)
    bool playable(Game *gptr);
    
    //Dynamic casting must be performed to gain access to CrunoGame's setSpecial() 
    //method
    void playCard(Game *gptr, Player *pptr);

};

#endif /* CRUNO8_H */

