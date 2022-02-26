
/**********************************************
 * File:    CrunoPlayer.cpp
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This source file includes the implementation of
 * the derived CrunoPlayer class and its children.
 *
 **********************************************/

#include <iostream>
using namespace std;

#include "CrunoPlayer.h"
#include "CrunoGame.h"
#include "Cruno8.h"

// *** 'DUMB' CRUNO PLAYER ***

CrunoPlayer::CrunoPlayer(Game *gptr, unsigned int numCards) : Player(gptr, numCards), 
    m_cgame(dynamic_cast<CrunoGame*>(m_game))
{}

void CrunoPlayer::showCardToPlayer(const Card* cptr, unsigned int player, bool oneCardLeft) {
    
    //Keep track of how many times card is showed to players
    if(m_cgame->currentShowCount() < m_cgame->numPlayers() - 1) {
        m_cgame->setShowCount(m_cgame->currentShowCount() + 1);
    } else {
        m_cgame->setShowCount(1);
    }
    
}

CrunoGame* CrunoPlayer::getGameLink() {
    return m_cgame;
}

Card* CrunoPlayer::playOneCard(bool& lastCard, bool& oneCardLeft) {
   
    //BELOW CODE UNCHANGED FOR 'DUMB' CRUNOPLAYER
    
    unsigned int c ;
    Card *cptr;

    // find first card that is playable

    c = 0 ;        // index into array of Card pointers
    cptr = NULL ;  // haven't found a playable card yet

    while( 1 ) {
      if (c >= m_numCards) break ;   // hit end of array

      if (m_cards[c]->playable(m_game)) { // found playable card

         cptr = m_cards[c] ;  // remember the card

         // To remove the card we will play from the hand,
         // we replace it with the last card in the array.
         // This changes the order of the cards, but 
         // order doesn't matter here.

         m_numCards-- ;                       // one less card
         m_cards[c] = m_cards[m_numCards] ;   // replace with last card
         m_cards[m_numCards] = NULL ;         // just to be safe

         if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
         if (m_numCards == 0) lastCard = true ;     // did we win?
         break ;
      }

      c++ ;    // no pun intended
    }

    
    //ADDED TURNCOUNTER
    
    //If a card is played, the number of turns is
    //incremented and printed out.
    if(cptr != NULL) {
        m_cgame->incrementNumTurns();
        cout << endl << "TURN #" << m_cgame->getNumTurns() << endl << endl;
    }
    
    
    return cptr ; 
   
}



// *** SMART CRUNO PLAYER ***

SmartCrunoPlayer::SmartCrunoPlayer(Game *gptr, unsigned int numCards) : 
CrunoPlayer(gptr, numCards)
{}


Card* SmartCrunoPlayer::playOneCard(bool& lastCard, bool& oneCardLeft) {
    
    //Create basic structure playableCard to hold the pointer to the playable card 
    //as well as its original index in m_cards
    struct playableCard {
        CrunoCard* m_playableCard;
        unsigned int m_cardsIndex;
    };
    
    //Create an array of playableCards, allocating space for a maximum of all cards in the
    //player's hand, for which to store pointers to playable cards and their
    //indices in the player's m_cards hand
    playableCard playableCards[m_numCards];
    unsigned int playableCardsIndex = 0;

    for(unsigned int i = 0; i < m_numCards; ++i) {
        
        if (m_cards[i]->playable(m_game)) {
        //Place card in playable card array
            playableCards[playableCardsIndex].m_playableCard = dynamic_cast<CrunoCard*>(m_cards[i]);
            playableCards[playableCardsIndex].m_cardsIndex = i;
            ++playableCardsIndex;
        }
        
    }
    
    //If more than one card is playable, print out the player's possible playable cards
    //***NOTE*** block comment out if this message is undesirable in output
    //(Although it's great for diagnostic purposes)
    if(playableCardsIndex > 1) {
        //Print possible playable cards
        cout << "Player " << m_cgame->currentPlayer() << "'s Playable Cards" << endl;
        cout << "*************************" << endl;
        for(unsigned int i = 0; i < playableCardsIndex; ++i) {
            cout << playableCards[i].m_playableCard->toString() << endl;
        }
        cout << "*************************" << endl;
    }
    
    
    Card *cptr;
    // index into array of Card pointers
    unsigned int c ;
        
    //If there are no playable cards, return NULL
    if(playableCardsIndex == 0) {
        cptr = NULL;
    
    //If there are playable cards, execute the following
    } else if(playableCardsIndex > 0) {
        
        //By default, set the index of the first playable card as c
        c = playableCards[0].m_cardsIndex;
        //By default, set the pointer to the first playable card as cptr
        cptr = playableCards[0].m_playableCard;

        if(playableCardsIndex > 1) {
            
            //Select cards in order of precedence/usefulness in-game, starting with a card of 
            //matching point value but not matching suit that also matches the favored suit to 
            //"play a card that can switch the suit to one of the player's favored suits" (so as 
            //not to waste the value of a Wildcard), then if that doesn't exist,
            //a Wildcard (which allows the player to "play a card that can switch the suit to 
            //one of the player's favored suits", then a Draw2 card (to mercilessly punish other 
            //players), then a Skip card (to make the rightful next player annoyed), then a reverse 
            //card (to make the rightful next player disappointed, with the unfortunate side effect
            //of making the previous player delighted), then, if multiple playable cards of the
            //same suit exist, choose the one of the highest point value to minimize potential
            //penalty
            
            //NOTE: A HANDY WAY TO CHECK IF THIS IS WORKING CORRECTLY IS TO UNCOMMENT THE
            //cout << "FOUND... " statements!
            //AND THEN EXAMINE THE OUTPUT
            
            bool foundPickSuitCard = false;
            //Check if a card exists that matches point value but not suit, and also 
            //matches the player's favored suit from pickCard()
            for(unsigned int i = 0; i < playableCardsIndex; ++i) {
                if(playableCards[i].m_playableCard->getSpecial() == CrunoCard::NonSpecial
                    && playableCards[i].m_playableCard->getSuit() != m_cgame->currentSuit()
                    && playableCards[i].m_playableCard->getSuit() == pickSuit()) {
                    //cout << "FOUND PICKSUIT CARD!" << endl;
                    foundPickSuitCard = true;
                    cptr = playableCards[i].m_playableCard;
                    c = playableCards[i].m_cardsIndex;
                }
            }
            
            bool foundWildcard = false;
            if(!foundPickSuitCard) {
                //Check if wildcard is among playable cards, and play if found
                for(unsigned int i = 0; i < playableCardsIndex; ++i) {
                    if(playableCards[i].m_playableCard->getSpecial() == CrunoCard::WildCard) {
                        foundWildcard = true;
                        //cout << "FOUND WILDCARD!" << endl;
                        cptr = playableCards[i].m_playableCard;
                        c = playableCards[i].m_cardsIndex;
                    }
                }
            }
            
            bool foundDraw2 = false;
            //If Wildcard wasn't found, check if Draw2 is among playable cards and 
            //play if found
            if(!foundPickSuitCard && !foundWildcard) {
                for(unsigned int i = 0; i < playableCardsIndex; ++i) {
                    if(playableCards[i].m_playableCard->getSpecial() == CrunoCard::DrawTwo) {
                        foundDraw2 = true;
                        //cout << "FOUND DRAW2!" << endl;
                        cptr = playableCards[i].m_playableCard;
                        c = playableCards[i].m_cardsIndex;
                    }
                }
            }
            
            bool foundSkip = false;
            //If Wildcard and Draw2 weren't found, check if skip is among playable 
            //cards and play if found
            if(!foundPickSuitCard && !foundWildcard && !foundDraw2) {
                for(unsigned int i = 0; i < playableCardsIndex; ++i) {
                    if(playableCards[i].m_playableCard->getSpecial() == CrunoCard::Skip) {
                        foundSkip = true;
                        //cout << "FOUND SKIP!" << endl;
                        cptr = playableCards[i].m_playableCard;
                        c = playableCards[i].m_cardsIndex;
                    }
                }
            }
            
            bool foundReverse = false;
            //If Wildcard and Draw2 and Skip weren't found, check if reverse is among
            //playable and play if found
            if(!foundPickSuitCard && !foundWildcard && !foundDraw2 && !foundSkip) {
                for(unsigned int i = 0; i < playableCardsIndex; ++i) {
                    if(playableCards[i].m_playableCard->getSpecial() == CrunoCard::Reverse) {
                        foundReverse = true;
                        //cout << "FOUND REVERSE!" << endl;
                        cptr = playableCards[i].m_playableCard;
                        c = playableCards[i].m_cardsIndex;
                    }
                }
            }
            
            //If Wildcard and Draw2 and Skip and Reverse weren't found, play the highest
            //card of the matching suit
            if(!foundPickSuitCard && !foundWildcard && !foundDraw2 && !foundSkip && !foundReverse) {
                
                //Allocate space for an array of nonSpecial cards of matching suit 
                //according to the total number of playable cards
                playableCard nonSpecialMatchingSuit[playableCardsIndex];
                unsigned int nonSpecialMatchingSuitIndex = 0;
                
                for(unsigned int i = 0; i < playableCardsIndex; ++i) {
                    if(playableCards[i].m_playableCard->getSpecial() == CrunoCard::NonSpecial
                        && playableCards[i].m_playableCard->getSuit() == m_cgame->currentSuit()) {
                        
                        nonSpecialMatchingSuit[nonSpecialMatchingSuitIndex] = playableCards[i];
                        ++nonSpecialMatchingSuitIndex;
                    }
                }
                
                //If more than one nonSpecial card is found that matches the suit, 
                //choose to play the one of largest point value (to minimize penalty)
                if(nonSpecialMatchingSuitIndex > 1) {
                    
                    unsigned int maxPointVal = 0;
                    
                    unsigned int j;
                    for(unsigned int i = 0; i < nonSpecialMatchingSuitIndex; ++i) {
                        if(nonSpecialMatchingSuit[i].m_playableCard->getPoints() > maxPointVal) {
                            maxPointVal = nonSpecialMatchingSuit[i].m_playableCard->getPoints();
                            j = i;
                        }
                    }
                    
                    //cout << "PLAYING CARD OF MATCHING SUIT AND LARGEST POINT VALUE" << endl;
                    cptr = nonSpecialMatchingSuit[j].m_playableCard;
                    c = nonSpecialMatchingSuit[j].m_cardsIndex;
                }
                
            }
        
        }
               
        // To remove the card we will play from the hand,
        // we replace it with the last card in the array.
        // This changes the order of the cards, but 
        // order doesn't matter here.

        m_numCards-- ;                       // one less card
        m_cards[c] = m_cards[m_numCards] ;   // replace with last card
        m_cards[m_numCards] = NULL ;         // just to be safe

        if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
        if (m_numCards == 0) lastCard = true ;     // did we win?
        
    }
    
    
    //Nice added turn counter. If a card is played, the number of turns is
    //incremented and printed out.
    if(playableCardsIndex > 0) {
        m_cgame->incrementNumTurns();
        cout << endl << "TURN #" << m_cgame->getNumTurns() << endl << endl;
    }
    
    return cptr; 
    
}

unsigned int SmartCrunoPlayer::pickSuit() {
    
   unsigned int numClubs = 0; 
   unsigned int numDiamonds = 0; 
   unsigned int numHearts = 0; 
   unsigned int numSpades = 0; 
    
   //Loop through the player's hand to find the count of each suit
    for (unsigned int i = 0; i < m_numCards; ++i) {
        
        switch (m_cards[i]->getSuit()) {
            case CrunoCard::Clubs:
                ++numClubs;
                break;
            case CrunoCard::Diamonds:
                ++numDiamonds;
                break;
            case CrunoCard::Hearts:
                ++numHearts;
                break;
            case CrunoCard::Spades:
                ++numSpades;
                break;
            //Failsafe: If suit is invalid, do nothing
            default:
                break;
        }
    }
   
   //Put suit counts into an array to easily find the max 
   unsigned int suitCount[4] = {numClubs, numDiamonds, numHearts, numSpades};
   
   unsigned int maxCount = 0;
   
   //Find the maximum suit count among the four suits using a simple for loop.
   for (unsigned int i = 0; i < 4; ++i) {
       if(suitCount[i] > maxCount) {
           maxCount = suitCount[i];
       }
   }
   
   //If the maxCount matches that of the specific suit (or the first one that
   //may share a maximum suit count), pick that suit.
   if (maxCount == numClubs) {
       return CrunoCard::Clubs;
   } else if (maxCount == numDiamonds) {
       return CrunoCard::Diamonds;
   } else if (maxCount == numHearts) {
       return CrunoCard::Hearts;
   } else {
       return CrunoCard::Spades;
   }
    
}


// *** CHEATING CRUNO PLAYER ***

CheatingCrunoPlayer::CheatingCrunoPlayer(Game *gptr, unsigned int numCards) : 
SmartCrunoPlayer(gptr, numCards)
{}

Card* CheatingCrunoPlayer::playOneCard(bool& lastCard, bool& oneCardLeft) {
    
    unsigned int c ;
    Card *cptr;

    // find first card that is playable

    c = 0 ;        // index into array of Card pointers
    cptr = NULL ;  // haven't found a playable card yet

    while( 1 ) {
      if (c >= m_numCards) break ;   // hit end of array

      if (m_cards[c]->playable(m_game)) { // found playable card

         cptr = m_cards[c] ;  // remember the card

         // To remove the card we will play from the hand,
         // we replace it with the last card in the array.
         // This changes the order of the cards, but 
         // order doesn't matter here.

         m_numCards-- ;                       // one less card
         m_cards[c] = m_cards[m_numCards] ;   // replace with last card
         m_cards[m_numCards] = NULL ;         // just to be safe

         if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
         if (m_numCards == 0) lastCard = true ;     // did we win?
         break ;
      }

      c++ ;    // no pun intended
    }

    bool cheating = false;
    //Cheat if playable card doesn't exist!
    if(cptr == NULL) {
        
        //Reset c to first card in hand
        c = 0; 
        
        cptr = new Cruno8();  //Allocate memory for new card
        
        //Cheating!!!
        cheating = true;
        
        // To remove the card we will play from the hand,
        // we replace it with the last card in the array.
        // This changes the order of the cards, but 
        // order doesn't matter here.

        m_numCards-- ;                       // one less card
        m_cards[c] = m_cards[m_numCards] ;   // replace with last card
        m_cards[m_numCards] = NULL ;         // just to be safe

        if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
        if (m_numCards == 0) lastCard = true ;     // did we win?
    }
    
    //ADDED TURNCOUNTER
    
    //The number of turns is
    //incremented and printed out.
    m_cgame->incrementNumTurns();
    cout << endl << "TURN #" << m_cgame->getNumTurns() << endl << endl;
    
    if(cheating) {
        cout << "*** PLAYER " << m_cgame->currentPlayer() <<  " CHEATING ***" << endl;
    }
    
    return cptr;
    
}