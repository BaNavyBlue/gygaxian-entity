#OBJS specifies which files to compile as part of the project
MAIN = main.cpp
UI = ui-test.cpp
SRC = entity.cpp dice_roll.cpp simdjson.cpp StatHelpers.cpp skills.cpp char_class.cpp items.cpp
SRC_UI = 

OBJS = $(MAIN) $(SRC)
UI_OBJ = $(UI) $(SRC_UI)
INCL =

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -std=c++17 -Wall
COMPUI_FLAGS = -g -O2 -Wall -Wextra
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = magic

#This is the target that compiles our executable
test : $(OBJS)
	$(CC) $(INCL) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

ui : $(UI_OBJ)
	$(CXX) $(INCL) $(UI_OBJ) $(COMPUI_FLAGS) $(LINKER_FLAGS) -o ui-test

.PHONY : clean
