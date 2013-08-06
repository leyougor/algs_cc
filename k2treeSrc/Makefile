CPP=gcc

OBJECTS=basic.o bitrankw32int.o directcodes.o kTree.o hash.o MemoryManager.o
BINS=build_tree  test_tree rebuild_tree invrebuild_tree revtest_tree use_tree rebuildCheck_tree checktest_tree
#CPPFLAGS=-Wall -g3 
CPPFLAGS=-Wall -O9 -g -DNDEBUG 
DEST=.

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: bin

bin: $(OBJECTS) $(BINS)

#build_wiki:
#	gcc $(CPPFLAGS) -o $(DEST)/build_wiki pruebaWikis.c $(OBJECTS) -lm

#build_youtube:
#	gcc $(CPPFLAGS) -o $(DEST)/build_youtube pruebayoutubelinks.c $(OBJECTS) -lm

#build_refs_titles:
#	gcc $(CPPFLAGS) -o $(DEST)/build_refs_titles pruebatitles.c $(OBJECTS) -lm

build_tree:
	gcc $(CPPFLAGS) -o $(DEST)/build_tree pruebaarbol.c $(OBJECTS) -lm

use_tree:
	gcc $(CPPFLAGS) -o $(DEST)/use_tree usararbol.c $(OBJECTS) -lm

test_tree:
	gcc $(CPPFLAGS) -o $(DEST)/test_tree tiemposarbol.c $(OBJECTS) -lm

revtest_tree:
	gcc $(CPPFLAGS) -o $(DEST)/revtest_tree tiemposinverso.c $(OBJECTS) -lm
	
rebuild_tree:
	gcc $(CPPFLAGS) -o $(DEST)/rebuild_tree recuperararbol.c $(OBJECTS) -lm

rebuildCheck_tree:
	gcc $(CPPFLAGS) -o $(DEST)/rebuildChek_tree recuperarCheckLink.c $(OBJECTS) -lm

checktest_tree:
	gcc $(CPPFLAGS) -o $(DEST)/checktest_tree tiemposcheck.c $(OBJECTS) -lm
	
invrebuild_tree:
	gcc $(CPPFLAGS) -o $(DEST)/invrebuild_tree recuperarinverso.c $(OBJECTS) -lm
				
clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)

