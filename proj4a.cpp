#include <iostream>
using namespace std ;

#include "card8.h"
#include "game8.h"
#include "player8.h"

int main() {

   Game8 G ;
   G.initialize(4) ;

   int n = G.getNumCards() ;
   Player *pptr1 = new Player8(&G,n) ;
   Player *pptr2 = new Player8(&G,n) ;
   Player *pptr3 = new Player8(&G,n) ;
   Player *pptr4 = new Player8(&G,n) ;

   G.addPlayer(pptr1) ;
   G.addPlayer(pptr2) ;
   G.addPlayer(pptr3) ;
   G.addPlayer(pptr4) ;

   G.startGame(3810743) ;
//   G.startGame(8132987) ;
//   G.startGame(7831035) ;
//   G.startGame(2310831) ;

   return 0 ;
}
