
/**********************************************
 * File:    CrunoSkip.h
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This header file includes the declaration of the 
 * derived CrunoSkip card class.  
 *
 **********************************************/

#ifndef CRUNOSKIP_H
#define CRUNOSKIP_H

#include <string>
using namespace std;

//Contains CrunoCard class
#include "Cruno8.h"

//Skip class CrunoSkip inherits from derived class CrunoCard
class CrunoSkip : public CrunoCard {

public:
    
    CrunoSkip(unsigned int suit);
    
    string toString();
    
    //Dynamic casting must be performed to gain access to CrunoGame's setSpecial() 
    //method
    void playCard(Game *gptr, Player *pptr);
    
    bool playable(Game *gptr);
      
};


#endif /* CRUNOSKIP_H */

