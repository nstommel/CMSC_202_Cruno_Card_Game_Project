
/**********************************************
 * File:    CrunoSkip.cpp
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This source file includes the implementation of the 
 * derived CrunoSkip card class.  
 *
 **********************************************/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "card.h"
#include "CrunoSkip.h"
#include "CrunoGame.h"

CrunoSkip::CrunoSkip(unsigned int suit) : CrunoCard(suit, 0, Skip)
{}

string CrunoSkip::toString() {
    
    ostringstream oss;
    
    oss << "Skip";
    
    switch ( m_suit ) {
      case Clubs :
         oss << " of Clubs" ;
         break ;
      case Diamonds :
         oss << " of Diamonds" ;
         break ;
      case Hearts :
         oss << " of Hearts" ;
         break ;
      case Spades :
         oss << " of Spades" ;
         break ;
      default :
         oss << "of INVALID SUIT\n" ;
   }

   return oss.str() ;

}

void CrunoSkip::playCard(Game *gptr, Player *pptr) {
    
    //Downcast Game pointer to CrunoGame pointer safely
    CrunoGame* cgptr = dynamic_cast<CrunoGame*>(gptr);
    
    cgptr->setSuit(m_suit);
    
    //Reset m_points so erroneous matching doesn't occur
    cgptr->setPoints(m_points);
    cgptr->setSpecial(m_special);
    cgptr->toggleSkip();

   return ;
}

bool CrunoSkip::playable(Game *gptr) {
    
    //Downcast Game pointer to CrunoGame pointer safely
    CrunoGame* cgptr = dynamic_cast<CrunoGame*>(gptr);
    
    if (m_suit == cgptr->currentSuit()) { // matches suit?
        return true;
    } else if (m_special == cgptr->currentSpecial()) { //matches special?
        return true;
    } else {
        return false ;
    }

}