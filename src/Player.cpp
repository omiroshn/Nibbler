#include "Player.hpp"

//=================================================================================================
//	Player
//	Tail and Head need separate rendering to avoid separate rotation function for them
//-------------------------------------------------------------------------------------------------
Player::Player(const std::string& _filePath)
: eInherited(16, PLAYER), filePath(_filePath)
{
	isAlive			= true;
	speed			= 5.0f;
	score			= 0;
	mPos			= Vector2(128.0f, 128.0f);

	snakeTextures.reserve(100);

	snakeTextures.push_back(std::make_unique<Texture>(_filePath, 96, 0, 32, 32));
	snakeTextures.back()->Direction(UP_DIR);
	snakeTextures.back()->Pos(mPos);

	snakeTextures.push_back(std::make_unique<Texture>(_filePath, 64, 32, 32, 32));
	snakeTextures.back()->Pos(Vector2(128.0f, 160.0f));

	snakeTextures.push_back(std::make_unique<Texture>(_filePath, 64, 32, 32, 32));
	snakeTextures.back()->Pos(Vector2(128.0f, 192.0f)); 

	tailTexture		= std::make_unique<Texture>(_filePath, 96, 64, 32, 32);
	tailTexture->Pos(Vector2(128.0f, 224.0f));
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
	Translate(snakeTextures.front()->Direction());
}
//=================================================================================================
// Render
//-------------------------------------------------------------------------------------------------
void Player::Render()
{
	for(auto &body : snakeTextures)
	{
		body->Render();
	}
	tailTexture->Render();
}
//=================================================================================================
// HandleInput
//-------------------------------------------------------------------------------------------------
void Player::HandleInput(float deltaTime)
{
	mInputManager->Update();
	if (mInputManager->KeyDown(SDL_SCANCODE_W) && snakeTextures.front()->Direction() != DOWN_DIR)
	{
		snakeTextures.front()->setStartX(96);
		snakeTextures.front()->setStartY(0);
		snakeTextures.front()->Direction(UP_DIR);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_S) && snakeTextures.front()->Direction() != UP_DIR)
	{
		snakeTextures.front()->setStartX(128);
		snakeTextures.front()->setStartY(32);
		snakeTextures.front()->Direction(DOWN_DIR);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_D) && snakeTextures.front()->Direction() != LEFT_DIR)
	{
		snakeTextures.front()->setStartX(128);
		snakeTextures.front()->setStartY(0);
		snakeTextures.front()->Direction(RIGHT_DIR);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_A) && snakeTextures.front()->Direction() != RIGHT_DIR)
	{
		snakeTextures.front()->setStartX(96);
		snakeTextures.front()->setStartY(32);
		snakeTextures.front()->Direction(LEFT_DIR);
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
	isAlive = false;
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
	mPos += _amount;

	Vector2 prevHeadPos				= snakeTextures.front()->Pos();
	Vector2 currentHeadDirection	= snakeTextures.front()->Direction(); // current
	Vector2 prevBodyPos;
	Vector2 prevBodyDir;

	snakeTextures.front()->Pos(mPos);
	// 1 because 0 is head
	for(size_t i = 1; i < snakeTextures.size(); ++i)
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
