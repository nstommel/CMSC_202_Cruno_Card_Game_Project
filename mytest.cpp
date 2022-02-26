
/**********************************************
 * File:    mytest.cpp
 * Project: CMSC 202 Project 4, Spring 2016
 * Author:  Nick Stommel
 * Date:    04/16/16
 * Section: 07
 * E-mail:  stommel1@gl.umbc.edu
 *
 * Description:
 * 
 * This source file includes all the derived header files and necessary derived 
 * classes for a proper CrunoGame test file. It also illustrates helper functions 
 * like printStock() and printDiscard(). There are also some tips included. 
 * The current configuration of this file is particularly interesting, as the game 
 * lasts for 491 Turns (and the stock runs out 12 times)! This makes the output 
 * file exceptionally lengthy and fun to pick through - over 28,400 lines!
 * 
 **********************************************/

#include <iostream>
using namespace std ;

//Card header files, including cards of type NonSpecial,
//Wildcard, Draw2, Reverse, and Skip 
#include "Cruno8.h"
#include "CrunoDraw2.h"
#include "CrunoReverse.h"
#include "CrunoSkip.h"

#include "CrunoGame.h"
#include "CrunoPlayer.h"

int main() {

   CrunoGame G;

   G.initialize(5);

   // Make the players and add them
   // We could add any object derived from Player.
   // So, we can have a mix of smart, dumb or cheating
   // players in the same game.
   //
   int n = G.getNumCards();
   Player *pptr1 = new SmartCrunoPlayer(&G,n);
   Player *pptr2 = new SmartCrunoPlayer(&G,n);
   Player *pptr3 = new SmartCrunoPlayer(&G,n);
   Player *pptr4 = new SmartCrunoPlayer(&G,n);
   Player *pptr5 = new SmartCrunoPlayer(&G,n);
   //Player *pptr6 = new CheatingCrunoPlayer(&G,n);
   //Player *pptr7 = new CheatingCrunoPlayer(&G,n);
   //Player *pptr8 = new CrunoPlayer(&G,n);
   //Player *pptr9 = new CrunoPlayer(&G,n);

   G.addPlayer(pptr1);
   G.addPlayer(pptr2);
   G.addPlayer(pptr3);
   G.addPlayer(pptr4);
   G.addPlayer(pptr5);
   //G.addPlayer(pptr6);
   //G.addPlayer(pptr7);
   //G.addPlayer(pptr8);
   //G.addPlayer(pptr9);

   G.printStock();
   
   // Play game with different random seeds.
   // The random seeds control the initial shuffle.

   //G.startGame(3810743);
   //G.startGame(8132987);
   //G.startGame(7831035);
   //G.startGame(2310831);
   
   //Now this is quite the interesting seed.
   G.startGame(1234567);
   
   G.printDiscard();
   
   //NOTE: TO ACTUALLY EXAMINE OUTPUT, IT IS MUCH HANDIER TO OUPUT TO A FILE!
   //Type './mytest > output.txt' into the command line and then use Ctrl-F to 
   //search for particular plays of a card
   
   return 0 ;
}
