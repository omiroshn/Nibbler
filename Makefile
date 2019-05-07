NAME = nibbler

CPP =	main				\
		AnimatedTexture		\
		AssetManager		\
		AudioManager		\
		Collider			\
		Food				\
		GameEntity			\
		gManager			\
		Graphics			\
		InputManager		\
		Level				\
		Player				\
		Texture				\
		Timer				\
		Wall				\
		
HPP =	AnimatedTexture.hpp	\
		AssetManager.hpp	\
		AudioManager.hpp	\
		Collider.hpp		\
		Food.hpp			\
		GameEntity.hpp		\
		gManager.hpp		\
		Graphics.hpp		\
		InputManager.hpp	\
		Level.hpp			\
		MathHelper.hpp		\
		Player.hpp			\
		Texture.hpp			\
		Timer.hpp			\
		Wall.hpp			\

SRC = $(addprefix src/, $(addsuffix .cpp, $(CPP)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(CPP)))
HDR = $(addprefix includes/, $(HPP))
SDL_LIBS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
SDL_Headers = `sdl2-config --cflags`
FLAGS = -Wall -Wextra -std=c++11
#-Werror
HEADERS = -I./includes

all: $(NAME)

$(NAME): $(OBJ) $(HDR)
	clang++ $(FLAGS) $(OBJ) -lm $(SDL_LIBS) $(HEADERS) -o $(NAME)


$(OBJ): obj/%.o : src/%.cpp $(HDR)
	clang++ -o $@ $ -c $(FLAGS) $(HEADERS) $(SDL_Headers) $<

clean:
	rm -f $(OBJ)

fclean :
	rm -f $(NAME)
	rm -rf $(OBJ)
	
re: fclean all

