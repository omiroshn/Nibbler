#ifndef _START_SCREEN_
#define _START_SCREEN_

#include "GameEntity.hpp"
#include "Texture.hpp"

class InputManager;

class StartScreen : public GameEntity
{
public:
	StartScreen();
	virtual ~StartScreen()	= default;

	void	Render();
	void	Update();

	bool					PlayScreen(float amount);
	bool					ChoiceMade()	const { return choiceMade;	}
	int8_t					Choice()		const { return choice;		}

protected:
	bool						choiceMade;
	int8_t						choice;
	std::unique_ptr<Texture>	snakeGame;
	std::unique_ptr<Texture>	onePlayer;
	std::unique_ptr<Texture>	twoPlayer;
	std::unique_ptr<Texture>	quit;
	std::unique_ptr<Texture>	backGround;
	std::unique_ptr<Texture>	arrow;
	InputManager*				mInputManager;
};

#endif // START_SCREEN
