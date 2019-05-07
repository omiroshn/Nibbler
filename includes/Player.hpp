#ifndef _PLAYER_HPP_
#define	_PLAYER_HPP_

#include "Texture.hpp"
#include "InputManager.hpp"
#include "Collider.hpp"
#include <vector>

//**************************************************************************************************
//	Player
//--------------------------------------------------------------------------------------------------
class Player : public Collider
{
	using eInherited = Collider;
public:
	Player(const std::string& filePath);
	virtual			~Player();

	void			Update();
	void			Render();
	void			HandleInput(float deltaTime);

	int32_t			Score() const;
	virtual void	Translate(Vector2 amount) override;
	void			Collide(Collider&);

protected:
	void			CollideWithWall();
	void			CollideWithFood();
	void			CollideWithSelf();

	void			ChangeDirectionBody(Texture&, const Vector2& previousDirection);
	void			ChangeDirectionTail(Texture&);
	void			BodyGrow();

	bool					isAlive;
	float					speed;
	int32_t					score;
	std::string				filePath;
	Texture*				tailTexture; 
	std::vector<Texture*>	snakeTextures;
	InputManager*			mInputManager;
};

#endif 