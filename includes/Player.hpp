#ifndef _PLAYER_HPP_
#define	_PLAYER_HPP_

#include "InputManager.hpp"
#include "Collider.hpp"
#include "Texture.hpp"
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
	void			HandleInput();

	bool			IsAlive() const;
	int32_t			Score() const;
	virtual void	Translate(Vector2 amount) override;
	void			Collide(Collider&);

protected:
	void			CollideWithSelf();
	void			CollideWithWall();
	void			CollideWithFood();

	void			ChangeDirectionBody(Texture&, const Vector2& previousDirection);
	void			ChangeDirectionTail(Texture&);
	void			BodyGrow();

	bool									isAlive;
	int32_t									score;
	std::string								filePath;
	std::unique_ptr<Texture>				headTexture;
	std::unique_ptr<Texture>				tailTexture;
	std::vector<std::unique_ptr<Texture>>	snakeTextures;
	InputManager*							mInputManager;
};

#endif 