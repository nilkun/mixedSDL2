engine=../engine/builds/
SOURCEFILES=main.o EventHandler.o Vector2D.o Vehicle.o Perlin.o Grid.o Pathfinder.o Viewport.o ViewportButton.o GameOfLife.o
GAMEENGINE=Factory.o ScreenManager.o
UPDATING=
TARGETFILE=beer
LFLAGS= -Wall
CFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
COMPILER=g++
all:
	$(COMPILER) $(LFLAGS) -o $(TARGETFILE) $(SOURCEFILES) $(GAMEENGINE) $(UPDATING) $(CFLAGS)
