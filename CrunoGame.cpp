
/**********************************************
 * File:    CrunoGame.cpp
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This source file includes the critically important
 * implementation of the derived CrunoGame class. 
 *
 **********************************************/

#include <stdlib.h>
#include <iostream>
using namespace std ;

#include "card.h"
#include "player.h"
#include "game.h"

#include "Cruno8.h"
#include "CrunoSkip.h"
#include "CrunoReverse.h"
#include "CrunoDraw2.h"

CrunoGame::CrunoGame() : Game(), m_special(0), m_seed(0),
    m_reversed(false), m_skip(false), m_showCount(0), m_turns(0)
{}

CrunoGame::~CrunoGame()
{
  //Destructor Body Empty, there are no additional
  //dynamically allocated members to delete
}

// ifNullCrash(void *ptr) must be redefined in this file in order 
// to override the initialize function safely.
//
static void ifNullCrash(void *ptr) {
   if (ptr == NULL) {
      cerr << "Could not allocate memory\n" ;
      exit(1) ;
   }
   return ;
}

void CrunoGame::initialize(int numPlayers) {
   m_suit = 0 ;
   m_points = 0 ;
   m_currentPlayer = 0 ;

   // can't play by yourself
   //
   if (numPlayers < 2) {
      cerr << "Insufficient players\n" ;
      exit(1) ;
   }

   // not enough cards to make it fun for >10.
   //
   if (numPlayers > 10) {
      cerr << "Too many players\n" ;
      exit(1) ;
   }

   m_numPlayers = 0 ;  // no players added yet.

   // allocate space for max requested
   //
   m_maxPlayers = numPlayers ;
   m_players = new Player*[numPlayers] ;
   ifNullCrash(m_players) ;

   m_winner = m_maxPlayers + 1 ;  // not a real player

   // usually use just one deck
   int decks = 1 ;
   m_maxCards = 52 + 24;   // 52 (+24 uno cards) in one deck

   if (numPlayers > 5) {
      // use two decks
      decks = 2 ;
      m_maxCards = 104 + 48;   // 104 (+48 uno cards) in two decks
   }


   // allocate space for the discard pile
   m_discard = new Card*[m_maxCards] ;
   ifNullCrash(m_discard) ;
   m_numDiscard = 0 ;  // nothing discarded yet

   // allocate space for the stock pile
   m_stock = new Card*[m_maxCards] ;
   ifNullCrash(m_stock) ;

   //Fill with standard cards
   
   int i = 0 ;  // next available slot in m_stock[]

    for (int d = 0 ; d < decks ; ++d) {  // # of decks

        // iterate over suits
        for (unsigned int s = Card::Clubs ; s <= Card::Spades ; ++s) {

            // iterate over point values 
            for (unsigned int p = 2 ; p <= Card::Ace ; ++p) {

                //If card is an eight, add a Wildcard
                if(p == 8) {
                    m_stock[i] = new Cruno8();
                } else { 
                    m_stock[i] = new CrunoCard(s,p,CrunoCard::NonSpecial);
                }

                ifNullCrash(m_stock[i]) ;
                ++i ;

            }

            //Add Uno cards (Skip, Reverse, and DrawTwo)
            for (unsigned int special = 16; special <= CrunoDraw2::DrawTwo; ++special) {
                
                if(special == CrunoSkip::Skip) {
                    m_stock[i] = new CrunoSkip(s);
                    ifNullCrash(m_stock[i]);
                    ++i;
                    m_stock[i] = new CrunoSkip(s);
                    
                } else if(special == CrunoReverse::Reverse) {
                    m_stock[i] = new CrunoReverse(s);
                    ifNullCrash(m_stock[i]);
                    ++i;
                    m_stock[i] = new CrunoReverse(s);
                    
                } else if(special == CrunoDraw2::DrawTwo) {
                    m_stock[i] = new CrunoDraw2(s);
                    ifNullCrash(m_stock[i]);
                    ++i;
                    m_stock[i] = new CrunoDraw2(s);
                }
                
                ifNullCrash(m_stock[i]);
                ++i;
                
            }

        }
    }

   // remember how many cards we added
   m_numStock = m_maxCards ;

   // Still haven't started (need to have players added)
   m_started = false ;
   m_over = false ;
}

void CrunoGame::startGame(unsigned int seed) {
    
    //Make sure to save seed value in game
    m_seed = seed;
    
    //FOLLOWING CODE BELOW IS EXACTLY THE SAME AS THAT OF THE
    //startGame() METHOD OF BASE GAME CLASS
    
    int j ;

   // shuffle cards
   //
   cout << "Random seed = " << seed << endl ;
   srand(seed) ;
   for(unsigned int i = 0 ; i < m_numStock ; i++) {
      Card *temp ;

      j = rand() % m_numStock ;
      temp = m_stock[i] ;
      m_stock[i] = m_stock[j] ;
      m_stock[j] = temp ;
   }
   
   // give players cards
   //
   dealCards() ;


   // Sanity check. Did we run out?
   //
   if (m_numStock < 1) {
      cerr << "Missing cards!\n" ;
      exit(1) ;
   }


   // turn over one card in the stock pile
   // and make it the top of the discard pile
   //
   m_numStock-- ;
   m_discard[0] = m_stock[m_numStock] ;
   m_stock[m_numStock] = NULL ;
   m_numDiscard = 1 ;
   setSuit( m_discard[0]->getSuit() ) ;
   setPoints( m_discard[0]->getPoints() ) ;

   cout << "First card: " << m_discard[0]->toString() << endl ;

   m_started = true ;
   playGame() ;  // main game loop

   gameOver() ;  // who won?

}

void CrunoGame::setSpecial(unsigned int special) {
    m_special = special;
}

unsigned int CrunoGame::currentSpecial() {
    return m_special;
}

void CrunoGame::changeDirection() {
    m_reversed = !m_reversed;
}

void CrunoGame::toggleSkip() {
    m_skip = !m_skip;
}

unsigned int CrunoGame::nextPlayer() {
    
    //Change m_currentPlayer to be that of next player
    
    if(m_reversed) {
        
        cout << endl << "*** REVERSE MODE ***" << endl;
        
        if(m_skip) {
            
            //Account for rollover when skipping and reversed
            if(m_currentPlayer == 0) {
                m_currentPlayer = m_numPlayers - 2;
            } else if(m_currentPlayer == 1) {
                m_currentPlayer = m_numPlayers - 1;
            
            } else {
                m_currentPlayer -= 2;
            }
         
        } else {
            
            //Account for rollover when reversed but not skipping
            if(m_currentPlayer == 0) {
                m_currentPlayer = m_numPlayers - 1;
            } else {
                m_currentPlayer -= 1;

            }
        }
        
    } else {
    
        if(m_skip) {
            m_currentPlayer = (m_currentPlayer + 2) % m_numPlayers ;
        } else {
            m_currentPlayer = (m_currentPlayer + 1) % m_numPlayers ;
        }
    }
    
    //Make sure to toggle skip mode off if skip is used
    if(m_skip) {
        toggleSkip();
    }
    
    return m_currentPlayer ;
}


unsigned int CrunoGame::playerAfter(unsigned int thisPlayer) {
    
    //Look familiar? Works exactly like nextPlayer but just returns the playerAfter's index
    
    if(m_reversed) {
        
        if(m_skip) {
            
            if(thisPlayer == 0) {
                thisPlayer = m_numPlayers - 2;
            
            } else if(thisPlayer == 1) {
                thisPlayer = m_numPlayers - 1;
            
            } else {
                thisPlayer -= 2;
            }
            
        } else {
            
            if(thisPlayer == 0) {
                thisPlayer = m_numPlayers - 1;
            } else {
                thisPlayer -= 1;
            }
        }
        
    } else {
    
        if(m_skip) {
            thisPlayer = (thisPlayer + 2) % m_numPlayers ;
        } else {
            thisPlayer = (thisPlayer + 1) % m_numPlayers ;
        }
    }
    
    return thisPlayer;
    
}

Card * CrunoGame::dealOneCard() {
    
    Card *cptr ;
    
    //If m_stock is empty and there are cards in the discard pile, 
    //reshuffle cards in discard pile to make new stock 
    if (m_numStock == 0 && m_numDiscard > 0) {
        
        cout << endl << "***   STOCK RAN OUT    ***" << endl;
        cout << "SHUFFLING DISCARD AS STOCK" << endl << endl;

        //Save last card in m_discard separately before shuffling
        Card* lastDiscard = m_discard[m_numDiscard - 1];
        m_discard[m_numDiscard - 1] = NULL;
        m_numDiscard -= 1;

        //Seed the random number generator with original m_seed
        srand(m_seed);
        int j;
        //Shuffle discard pile
        for(unsigned int i = 0 ; i < m_numDiscard ; i++) {
            Card *temp ;

            j = rand() % m_numDiscard ;
            temp = m_discard[i] ;
            m_discard[i] = m_discard[j] ;
            m_discard[j] = temp ;
        }

        //Copy m_discard to m_stock and flush Discard contents
        for(unsigned int i = 0; i < m_numDiscard; i++) {
            m_stock[i] = m_discard[i];
            m_discard[i] = NULL;
        }   

        //Readjust m_numStock
        m_numStock = m_numDiscard;

        m_numDiscard = 1;
        //Add back in last played card as first card in discard pile
        m_discard[0] = lastDiscard;
        
    //Sanity Check
    //Else, if there are no longer cards in the stock or discard pile,
    //end the game and return NULL
    } else if (m_numStock == 0 && m_numDiscard == 0) {
        m_over = true ;
        return NULL ;
    }

    //Draw card from end of stock array
    m_numStock-- ;
    cptr = m_stock[m_numStock] ;
    m_stock[m_numStock] = NULL ;

    return cptr ;

}

void CrunoGame::setShowCount(unsigned int count) {
    m_showCount = count;
}
    
unsigned int CrunoGame::currentShowCount() {
    return m_showCount;
}

unsigned int CrunoGame::getNumTurns() {
    return m_turns;
}

void CrunoGame::incrementNumTurns() {
    ++m_turns;
}

void CrunoGame::printStock() {
    
    cout << endl << "*** PRINTING STOCK ***" << endl << endl;
    for(unsigned int i = 0; i < m_numStock; ++i) {
        
        //Prevent segmentation fault if m_stock is not full
        //(there is no card at the memory location)
        if(m_stock[i] == NULL) {
            break;
            
        } else {
            //Print card count and cards
            cout << "#" << i + 1 << "  " << m_stock[i]->toString() << endl;
        }
    }
    cout << endl;
}

void CrunoGame::printDiscard() {
    
    cout << endl << "*** PRINTING DISCARD ***" << endl << endl;
    for(unsigned int i = 0; i < m_numDiscard; ++i) {
        
        //Prevent segmentation fault if m_discard is not full
        //(there is no card at the memory location)
        if(m_discard[i] == NULL) {
            break;
            
        } else {
            //Print card count and cards
            cout << "#" << i + 1 << "  " << m_discard[i]->toString() << endl;
        }
    }
    cout << endl;
}

