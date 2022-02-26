
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
 * This source file includes the implementation of
 * the CrunoDraw2 class. 
 *
 **********************************************/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CrunoDraw2.h"
#include "CrunoGame.h"
#include "CrunoPlayer.h"

CrunoDraw2::CrunoDraw2(unsigned int suit) : CrunoCard(suit, 0, DrawTwo)
{}

string CrunoDraw2::toString() {
    
    ostringstream oss;
    
    oss << "Draw Two";
    
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

void CrunoDraw2::playCard(Game *gptr, Player *pptr) {
    
    //Downcast Game pointer to CrunoGame pointer safely
    CrunoGame* cgptr = dynamic_cast<CrunoGame*>(gptr);
    
    cgptr->setSuit(m_suit);
    
    //Reset m_points so erroneous matching doesn't occur
    cgptr->setPoints(m_points);
    cgptr->setSpecial(m_special);
    
   return ;
}

bool CrunoDraw2::playable(Game *gptr) {
    
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

void CrunoDraw2::showPlayerToCard(Player *pptr) {
    
    //Safely downcast Player pointer to CrunoPlayer pointer to 
    //gain access to getGameLink()
    CrunoPlayer* cpptr = dynamic_cast<CrunoPlayer*>(pptr);
    
    //The CrunoPlayer's getGameLink() function is used to get the player's link to the
    //game and actually deal cards to the player from the stock when a Draw2 is played
    
    //If the showCount is one (meaning only the first player shown the Draw2 card 
    //will actually draw2)...
    if(cpptr->getGameLink()->currentShowCount() == 1) {
        
        //Nice output messages included to show which cards are drawn an when such an
        //event takes place
        cout << endl << "*** PLAYER " << cpptr->getGameLink()->playerAfter(
            cpptr->getGameLink()->currentPlayer()) << " DRAWS 2 ***" << endl << endl;
            
        Card* dcptr1 = cpptr->getGameLink()->dealOneCard();
        cpptr->takeCard(dcptr1);
        
        cout << "Player " << cpptr->getGameLink()->playerAfter(
            cpptr->getGameLink()->currentPlayer()) << " draws a card: " << dcptr1->toString() << endl;
        
        Card* dcptr2 = cpptr->getGameLink()->dealOneCard();
        cpptr->takeCard(dcptr2);
        
        cout << "Player " << cpptr->getGameLink()->playerAfter(
            cpptr->getGameLink()->currentPlayer()) << " draws a card: " << dcptr2->toString() << endl << endl;
        
    }
    
}


