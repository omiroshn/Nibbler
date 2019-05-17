#include "Player.hpp"

//=================================================================================================
//	Player
//	Tail and Head need separate rendering to avoid separate rotation function for them
//-------------------------------------------------------------------------------------------------
Player::Player(const std::string& _filePath)
: eInherited(RADIUS16, PLAYER), filePath(_filePath)
{
	isAlive			= true;
	score			= 0;
	mPos			= Vector2(128.0f, 128.0f);

	snakeTextures.reserve(100);

	headTexture = std::make_unique<Texture>(_filePath, 96, 0, SQUARE_32x32, SQUARE_32x32);
	headTexture->Direction(UP_DIR);
	headTexture->Pos(mPos);

	snakeTextures.push_back(std::make_unique<Texture>(_filePath, 64, 32, SQUARE_32x32, SQUARE_32x32));
	snakeTextures.back()->Pos(Vector2(128.0f, 160.0f));

	tailTexture		= std::make_unique<Texture>(_filePath, 96, 64, SQUARE_32x32, SQUARE_32x32);
	tailTexture->Pos(Vector2(128.0f, 192.0f));
	mInputManager	= InputManager::Instance();
}
//=================================================================================================
//	~Player
//-------------------------------------------------------------------------------------------------
Player::~Player()
{}
//=================================================================================================
// Update
//-------------------------------------------------------------------------------------------------
void Player::Update()
{
	Translate(headTexture->Direction());
	CollideWithSelf();
}
//=================================================================================================
// Render
//-------------------------------------------------------------------------------------------------
void Player::Render()
{
	headTexture->Render();
	for(auto &body : snakeTextures)
	{
		body->Render();
	}
	tailTexture->Render();
}
//=================================================================================================
// HandleInput
//-------------------------------------------------------------------------------------------------
void Player::HandleInput()
{
	//mInputManager->Update();
	if (mInputManager->KeyDown(SDL_SCANCODE_W) && headTexture->Direction() != DOWN_DIR)
	{
		headTexture->setStartX(96);
		headTexture->setStartY(0);
		headTexture->Direction(UP_DIR);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_S) && headTexture->Direction() != UP_DIR)
	{
		headTexture->setStartX(128);
		headTexture->setStartY(32);
		headTexture->Direction(DOWN_DIR);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_D) && headTexture->Direction() != LEFT_DIR)
	{
		headTexture->setStartX(128);
		headTexture->setStartY(0);
		headTexture->Direction(RIGHT_DIR);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_A) && headTexture->Direction() != RIGHT_DIR)
	{
		headTexture->setStartX(96);
		headTexture->setStartY(32);
		headTexture->Direction(LEFT_DIR);
	}
}
//=================================================================================================
// Collide
//-------------------------------------------------------------------------------------------------
void Player::Collide(Collider& _toCollideWith)
{
	switch(_toCollideWith.GetCollideType())
	{
	case WALL:		CollideWithWall();	break;
	case FOOD:		CollideWithFood();	break;
	case PLAYER:	CollideWithSelf();	break;
	default:		break;
	}
}
//=================================================================================================
// CollideWithWall
//-------------------------------------------------------------------------------------------------
void Player::CollideWithWall()
{
	isAlive = false;
}
//=================================================================================================
// CollideWithFood
//-------------------------------------------------------------------------------------------------
void Player::CollideWithFood()
{
	// score += Food->ValueScore() // like this, in gManager set Player Score

	score += 10;
	BodyGrow();
}
//=================================================================================================
// CollideWithSelf
//-------------------------------------------------------------------------------------------------
void Player::CollideWithSelf()
{
	// not working
	/*for (auto& snake : snakeTextures)
	{
		if (CheckCircleCollision(headTexture->Pos(), snake->Pos(), SQUARE_16x16, SQUARE_16x16))
		{
			std::cout << "Killed\n";
			isAlive = false;
		}
	}*/
}
//=================================================================================================
// Score
//-------------------------------------------------------------------------------------------------
bool Player::IsAlive() const
{
	return isAlive;
}
//=================================================================================================
// Score
//-------------------------------------------------------------------------------------------------
int32_t Player::Score() const
{
	return score;
}
//=================================================================================================
// Score
//-------------------------------------------------------------------------------------------------
void Player::BodyGrow()
{
	// $todo find a proper way to render the tail

	Vector2 prevBodyPartPos = snakeTextures.back()->Pos();
	Vector2 prevBodyPartDir = snakeTextures.back()->Direction();
	snakeTextures.push_back(std::make_unique<Texture>(filePath, 96, 0, 32, 32));
	snakeTextures.back()->Pos(prevBodyPartPos);
	snakeTextures.back()->Direction(prevBodyPartDir);
	tailTexture->Pos(snakeTextures.back()->Pos());
	tailTexture->Direction(snakeTextures.back()->Direction());
	//Update();
}
//=================================================================================================
// Translate
//-------------------------------------------------------------------------------------------------
void Player::Translate(Vector2 _amount)
{
	Vector2 prevHeadPos				= headTexture->Pos();
	Vector2 currentHeadDirection	= headTexture->Direction(); // current
	Vector2 prevBodyPos;
	Vector2 prevBodyDir;

	mPos += _amount;
	headTexture->Translate(_amount);
	for(size_t i = 0; i < snakeTextures.size(); ++i)
	{
		prevBodyPos		= snakeTextures[i]->Pos();
		prevBodyDir		= snakeTextures[i]->Direction();
		snakeTextures[i]->Pos(prevHeadPos);
		snakeTextures[i]->Direction(currentHeadDirection);
		ChangeDirectionBody(*snakeTextures[i], prevBodyDir);
		prevHeadPos				= prevBodyPos;
		currentHeadDirection	= prevBodyDir;
	}
	tailTexture->Pos(prevHeadPos);
	tailTexture->Direction(currentHeadDirection);
	ChangeDirectionTail(*tailTexture);
}
//=================================================================================================
// ChangeDirectionBody
//-------------------------------------------------------------------------------------------------
void Player::ChangeDirectionBody(Texture& _body, const Vector2& _previousDirection)
{
	if (_body.Direction() == _previousDirection)
	{
		// if direction isn't changed next frame, set texture due to direction
		if (_body.Direction() == RIGHT_DIR || _body.Direction() == LEFT_DIR)
		{
			_body.setStartX(32);
			_body.setStartY(0);
		}
		else
		{
			_body.setStartX(64);
			_body.setStartY(32);
		}
	}
	else
	{
		// direction changed
		if (_previousDirection == UP_DIR)
		{
			if (_body.Direction() == RIGHT_DIR)
			{
				_body.setStartX(0);
				_body.setStartY(0);
			}
			else
			{
				_body.setStartX(64);
				_body.setStartY(0);
			}
		}
		else if (_previousDirection == DOWN_DIR)
		{
			if (_body.Direction() == RIGHT_DIR)
			{
				_body.setStartX(0);
				_body.setStartY(32);
			}
			else
			{
				_body.setStartX(64);
				_body.setStartY(64);
			}
		}
		else if (_previousDirection == RIGHT_DIR)
		{
			if (_body.Direction() == UP_DIR)
			{
				_body.setStartX(64);
				_body.setStartY(64);
			}
			else
			{
				_body.setStartX(64);
				_body.setStartY(0);
			}
		}
		else if (_previousDirection == LEFT_DIR)
		{
			if (_body.Direction() == UP_DIR)
			{
				_body.setStartX(0);
				_body.setStartY(32);
			}
			else
			{
				_body.setStartX(0);
				_body.setStartY(0);
			}
		}
	}
}
//==================================================================================================
//	Player::ChangeDirectionTail
//--------------------------------------------------------------------------------------------------
void Player::ChangeDirectionTail(Texture& _tail)
{
	if(_tail.Direction() == RIGHT_DIR)
	{
		_tail.setStartX(128);
		_tail.setStartY(64);
	}
	else if(_tail.Direction() == LEFT_DIR)
	{
		_tail.setStartX(96);
		_tail.setStartY(96);
	}
	else if(_tail.Direction() == UP_DIR)
	{
		_tail.setStartX(96);
		_tail.setStartY(64);
	}
	else if(_tail.Direction() == DOWN_DIR)
	{
		_tail.setStartX(128);
		_tail.setStartY(96);
	}
}
