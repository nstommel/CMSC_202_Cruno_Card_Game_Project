
/**********************************************
 * File:    CrunoReverse.h
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This header file includes the declaration of the 
 * derived CrunoReverse card class.  
 *
 **********************************************/

#ifndef CRUNOREVERSE_H
#define CRUNOREVERSE_H

#include <string>
using namespace std;

//Contains CrunoCard class
#include "Cruno8.h"

//Reverse class CrunoReverse inherits from derived class CrunoCard
class CrunoReverse : public CrunoCard {

public:
    
    CrunoReverse(unsigned int suit);
    
    string toString();
    
    //Dynamic casting must be performed to gain access to CrunoGame's setSpecial() 
    //method
    void playCard(Game *gptr, Player *pptr);
    
    bool playable(Game *gptr);
      
};


#endif /* CRUNOREVERSE_H */

