PROJECT_NAME = boxes

CXX = g++
CXXFLAGS = -std=c++17

SRC = src
INCLUDE = -Iinclude

STATIC = -static libgcc -static libsdl2-image-dev -static libsdl2-dev -static libsdl2-ttf-dev

## SDL Stuff ##
SDL_INCLUDE = -ISDL/include/SDL2
#  Left out, because they don't seem to be necessary (also they point to the
#  wrong place. There is new mingw_dev_lib on here)
#SDL_INCLUDE = -IC:\mingw_dev_lib\include\SDL2
#SDL_SEARCHDIR = -LC:\mingw_dev_lib\lib

#  I'm not sure what this does, but it behaves oddly. Leave it alone or,
#  comment out if not using SDL (it interferes with command line output)
#SDL_FLAGS = -w -Wl,-subsystem,windows

#  This is absolutely necessary!
# Fixed So I can Compile too you asshole - Liam
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	SDL_ARCHIVE = -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2
else 
	SDL_ARCHIVE = -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2
endif

#SDL_ARCHIVE = -lmingw32 -Wl,-rpath,SDL/lib/SDL2main -Wl,-rpath,SDL/include/SDL2
SDL = $(SDL_INCLUDE) $(SDL_FLAGS) $(SDL_ARCHIVE)
## End SDL Stuff ##

.DEFUALT_GOAL := $(PROJ)

$(PROJECT_NAME): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC)/*.cpp -o $@ $(INCLUDE) $(SDL)



clean:
	rm -f *.exe *.o src/*.o $(PROJECT_NAME)
