 # Makefile
 # created by GET_A team for CPE111 project
 # Kodchaphon Treesak 62070503401
 # Kulchaya Songkwan 62070503405
 # Chotiya Pertpring 62070503413
 # Prakasit Issanapong 62070503431

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= interface$(EXECEXT) 

all : $(EXECUTABLES)

interface.o : interface.c addData.h searchData.h
	gcc -c interface.c

searchData.o :	searchData.c searchData.h structure.h validation.h abstractHashTable.h
	gcc -c searchData.c

chainedHashTable.o :	chainedHashTable.c abstractHashTable.h
	gcc -c chainedHashTable.c

validation.o : validation.c validation.h structure.h
	gcc -c validation.c

addData.o : addData.c addData.h structure.h validation.h
	gcc -c addData.c


interface$(EXECEXT) : interface.o searchData.o chainedHashTable.o validation.o addData.o
	gcc -o interface$(EXECEXT) interface.o searchData.o chainedHashTable.o validation.o addData.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
