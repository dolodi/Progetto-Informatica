COMPILER=g++
SOURCES=main.cpp classifica.cpp my_list.cpp
EXECUTABLE=gioca
FLAGS=-lncurses -w
RUN = ./script/run_game.sh 

all: $(EXECUTABLE)

$(EXECUTABLE) : $(SOURCES)
	$(COMPILER) -o $(EXECUTABLE) $(SOURCES) $(FLAGS)

clean:
	rm gioca

run:
	chmod +x $(RUN)
	$(RUN) 
