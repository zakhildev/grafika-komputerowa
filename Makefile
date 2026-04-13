CXX = clang++
CXXFLAGS = -std=c++23

INCLUDES = -I./dependencies/glm/ -L/opt/homebrew/lib/

LIBS = -lglfw -lGLEW -lassimp -framework OpenGL

HEADERS = $(wildcard ./src/include/*.h) $(wildcard ./src/include/*.hpp)
FILES = ./src/main.cpp $(wildcard ./src/lib/*.cpp)

AlcoholGallery: $(FILES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o AlcoholGallery $(FILES)  $(LIBS) -I./dependencies/glm/
