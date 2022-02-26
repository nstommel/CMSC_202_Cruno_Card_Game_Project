# CMSC_202_Cruno_Card_Game_Project
This project implements a card game called Cruno (Crazy 8s plus Uno). More details about the rules are given in the prompt below and are documented in the code. Several new classes of cards are added to Crazy 8's from Uno including Skip, Reverse, Wildcard, and Draw 2.

# Background

Crazy Eights and Uno are both "shedding-type" card games where the objective of the game is to get rid of your cards. The first person to get rid of all his/her cards wins. There is a pile of cards that you draw new cards from called "the stock". There is another pile of cards called the "discard". When you play a card from your hand, it goes into the discard pile. There are many variations on how Crazy Eights and Uno can be played (people follow their own "house rules"). Generally, the card that you play must somehow match the top card of the discard pile (with some exception). If you do not have a card that is playable you have to draw from the stock. Some rules have you draw just one card, others have you draw until you can play. There are also variations on whether you have to play a card if you have a playable card. Some rules allow you to 'pass'. There are also variations on what happens when the stock runs out. Some rules end the game when the stock runs out. In other games, you shuffle the discard pile (except for the last card played) to replenish the stock. Finally, "action cards" are added to the mix. In Crazy Eights, which is played with standard playing cards, an 8 card can be played at any time. Furthermore, the person who plays an 8 can name the suit that next card must follow. The wild card in Uno does the same thing. In Uno, there are additional action cards that skips the next player, reverses the direction of play, and makes another player draw extra cards. In this project, you will see that variations on these card games can be implemented in C++ using class derivation and polymorphism without rewriting too much of the code.

# Assignment Prompt

For this project, you are given the source code for a program that plays a basic shedding-type card game. This game is played with the standard 52 playing cards for 2 to 10 players. If more than 5 players are in the game, two decks of cards are used. Here are the rules:

    Each player is dealt 5 cards at the beginning of the game.
    Play proceeds clockwise from the dealer's left.
    After players have received their cards, one card from the stock pile is revealed to serve as the first card of the discard.
    Each player plays one card in his/her turn. The card played must match the top card of the discard pile either in suit or points. For example: if the top card is 5 of Clubs, then 5 of Hearts can be played and also 7 of Clubs.
    If the player does not have a matching card or does not want to play a matching card, he/she must draw from the stock until a card is played.
    The first player with an empty hand wins.
    If the stock runs out, the game ends immediately. The winner is determined by penalties for cards remaining in the players' hands when the game ended. Face cards are penalized 10 points. All other cards are penalized at their usual values. (I.e., an Ace incurs a penalty of 10 points, and a 7 incurs a penalty of 7 points.) The player with the lowest total penalty wins. Ties are possible. 

Here's the source code for the basic game.

    Card class: card.h and card.cpp.
    Player class: player.h and player.cpp.
    Game class: game.h and game.cpp.
    Sample main program: proj4.cpp.
    Sample output: sample1.txt. 

These classes are designed so that much of the game playing details are handled by the Card class. The Player class handles game playing strategy (or lack thereof). The Game class handles who plays next, but it is blissfully unaware of the strategy used by each player or what each card actually does. This design allows you to add new types of cards to the game without having to rewrite too much of the game.

Here is the general design of the program. In each turn a Game object ask a particular Player to play a card by calling playOneCard(). If the function returns NULL, then cards are drawn, one at a time, from the stock and given to that player until playOneCard() returns a non-NULL value or the stock runs out. If a card is played, then this card is "shown" to all of the other players. This gives the other players information that might be needed for their strategizing. Each player is also "shown" to the card. This allows action cards to "interact" with the player (for example, to make them draw additional cards). Finally, the card is given an opportunity to interact with the Game object and the Player that played the card. This allows the player to do things like choose a new suit. In this setup, Card objects must be able to determine whether they are playable in the current setting. This allows a very simple strategy for a naive Player: try every card in his/her hand and play the first card that is playable.

Your assignment is to add new features to the basic game:

    Make 8's wild cards as in Crazy Eights. The 8's can be played at any time. Player names a suit for the subsequent plays thru the pickSuit() virtual member function.
    Add the following cards from Uno: Skip, Reverse and Draw Two. Each of these cards have a suit, but do not replace any of the old cards. Add two of each card in each suit for a total of 24 additional cards. These action cards match cards with the same action or the same suit. So, a Diamond Skip can be played on top of any Diamond or another Skip of any suit. A Diamond Skip can also be played if the previous card was an 8 and the previous player chose Diamond. A Reverse changes direction of play from clockwise to counter-clockwise or vice versa. A Draw Two makes the next player (in the direction of play) draw two cards from the stock.
    Change the game so that when the stock runs out, you shuffle the discard pile to make a new stock. (Except the last card played remains in the discard pile.)
    Implement some simple strategies for the Player class. For example,
        After playing an 8, the player should pick the suit that appears the most in his/her hand. (See sample output: sample2.txt.
        Try to play a card that can switch the suit to one of the player's favored suits.
        Cheat: when nothing can be played. Convert a card to an 8. 

Let's call this new game "Cruno" for "Crazy Eights" + "Uno". (Sort of like "croissants" + "donuts" = "cronuts".) Your program should have at least 6 classes Cruno8, CrunoSkip, CrunoReverse, CrunoDraw2, CrunoPlayer and CrunoGame. If you implement more than one type of player, you will have a separate class for each type. You should write as little code as possible and take advantage of the base classes that have been given to you. 
