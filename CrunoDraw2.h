
/**********************************************
 * File:    CrunoDraw2.cpp
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This header file includes the declaration of
 * the CrunoDraw2 class.
 *
 **********************************************/

#ifndef CRUNODRAW2_H
#define CRUNODRAW2_H

#include <string>
using namespace std;

//Contains CrunoCard class
#include "Cruno8.h"

//DrawTwo class CrunoDraw2 inherits from derived class CrunoCard
class CrunoDraw2 : public CrunoCard {

public:
    
    CrunoDraw2(unsigned int suit);
    
    string toString();
    
    //Dynamic casting must be performed to gain access to CrunoGame's setSpecial() 
    //method
    void playCard(Game *gptr, Player *pptr);
    
    bool playable(Game *gptr);
    
    //Used to make the first player shown the card draw two cards from the stock
    void showPlayerToCard(Player *pptr);
    
};


#endif /* CRUNODRAW2_H */

