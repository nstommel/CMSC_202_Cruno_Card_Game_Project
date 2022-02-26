
CFLAGS = -std=c++98 -Wall -ansi -gstabs -c
OBJS = card.o player.o game.o
NEWOBJS = Cruno8.o CrunoSkip.o CrunoReverse.o CrunoDraw2.o CrunoPlayer.o CrunoGame.o
SUBMITFILES = mytest.cpp Cruno8.h Cruno8.cpp CrunoSkip.h CrunoSkip.cpp CrunoReverse.h CrunoReverse.cpp CrunoDraw2.h CrunoDraw2.cpp CrunoPlayer.h CrunoPlayer.cpp CrunoGame.h CrunoGame.cpp

all: mytest.out

#DERIVED FILES
mytest.out: mytest.o $(OBJS) $(NEWOBJS)
	g++ mytest.o $(OBJS) $(NEWOBJS) -o mytest.out

mytest.o: mytest.cpp Cruno8.h
	g++ $(CFLAGS) mytest.cpp

Cruno8.o: Cruno8.cpp Cruno8.h CrunoGame.h CrunoPlayer.h
	g++ $(CFLAGS) Cruno8.cpp

CrunoSkip.o: CrunoSkip.cpp CrunoSkip.h CrunoGame.h CrunoPlayer.h
	g++ $(CFLAGS) CrunoSkip.cpp

CrunoReverse.o: CrunoReverse.cpp CrunoReverse.h CrunoGame.h CrunoPlayer.h
	g++ $(CFLAGS) CrunoReverse.cpp

CrunoDraw2.o: CrunoDraw2.cpp CrunoDraw2.h CrunoGame.h CrunoPlayer.h
	g++ $(CFLAGS) CrunoDraw2.cpp

CrunoPlayer.o: CrunoPlayer.cpp CrunoPlayer.h CrunoGame.h
	g++ $(CFLAGS) CrunoPlayer.cpp

CrunoGame.o: CrunoGame.cpp CrunoGame.h CrunoPlayer.h
	g++ $(CFLAGS) CrunoGame.cpp

#BASE SOURCE FILES
card.o: card.cpp card.h game.h player.h
	g++ $(CFLAGS) card.cpp

game.o: game.cpp card.h game.h player.h
	g++ $(CFLAGS) game.cpp

player.o: player.cpp card.h game.h player.h
	g++ $(CFLAGS) player.cpp

clean:
	rm -f *.o *~ *.out

submit:
	cp $(SUBMITFILES) ~/cs202proj/proj4

