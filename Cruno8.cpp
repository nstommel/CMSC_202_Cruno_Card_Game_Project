
/**********************************************
 * File:    Cruno8.cpp
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This source file includes the implementation of
 * the Cruno8 and CrunoCard classes. 
 *
 **********************************************/

#include <iostream>
#include <sstream>

using namespace std;

#include "Cruno8.h"
#include "card.h"
#include "player.h"


Cruno8::Cruno8() : CrunoCard(Invalid, 8, WildCard)
{}

string Cruno8::toString() {
    
    ostringstream oss;
    //No need to print suit, Wildcards are suit-independent
    oss << "Wildcard 8";
    
    return oss.str() ;
}

bool Cruno8::playable(Game *gptr) {
    
    //Make playable at any time
    return true;
    
}

void Cruno8::playCard(Game *gptr, Player *pptr) {
    
    //Downcast Game pointer to CrunoGame pointer safely
    CrunoGame* cgptr = dynamic_cast<CrunoGame*>(gptr);
    
    //Have current player pick suit
    cgptr->setSuit(pptr->pickSuit());
    
    //Nice feedback message telling the user what suit was picked by the player
    cout << endl << "Player " << gptr->currentPlayer() << " picks suit ";
    switch (gptr->currentSuit()) {
        case CrunoCard::Clubs:
            cout << "Clubs" << endl;
            break;
        case CrunoCard::Diamonds:
            cout << "Diamonds" << endl;
            break;
        case CrunoCard::Hearts:
            cout << "Hearts" << endl;
            break;
        case CrunoCard::Spades:
            cout << "Spades" << endl;
            break;
        default:
            break;
    }
        
    //Reset m_points so erroneous matching doesn't occur
    cgptr->setPoints(m_points);
    //Reset m_special so erroneous matching doesn't occur
    cgptr->setSpecial(m_special);
        
}
    

CrunoCard::CrunoCard(unsigned int s, unsigned int p, unsigned int special) :
    Card(s, p), m_special(special)
{}

unsigned int CrunoCard::getSpecial() {
    return m_special;
}

void CrunoCard::playCard(Game *gptr, Player *pptr) {
    
    //Downcast Game pointer to CrunoGame pointer safely
    CrunoGame* cgptr = dynamic_cast<CrunoGame*>(gptr);
    
    cgptr->setSuit(m_suit);
    cgptr->setPoints(m_points);
    //Reset m_special so erroneous matching doesn't occur
    cgptr->setSpecial(m_special);
    
}