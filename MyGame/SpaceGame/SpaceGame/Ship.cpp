#include "Ship.h"

Ship::Ship(float acceleration, float maxSpeed) : health(100), speed(0.0f), acceleration(acceleration), maxSpeed(maxSpeed), mAnimationShip(IND_Animation::newAnimation()), mAnimationStill(IND_Animation::newAnimation()), mAnimationLeft(IND_Animation::newAnimation()), mAnimationRight(IND_Animation::newAnimation()), mAnim2dShip(IND_Entity2d::newEntity2d())
{
}

int Ship::getHealth() const
{
	return health;;
}

void Ship::setHealth(int health)
{
	this->health = health;
}

float Ship::getSpeed() const
{
	return speed;
}

void Ship::setSpeed(float speed)
{
	this->speed = speed;
}

float Ship::getAcceleration() const
{
	return acceleration;
}

float Ship::getMaxSpeed() const
{
	return maxSpeed;
}

IND_Animation * Ship::getAnimationShip() const
{
	return mAnimationShip;
}

void Ship::setAnimationShip(IND_Animation * mAnimationShip)
{
	this->mAnimationShip = mAnimationShip;
}

IND_Animation * Ship::getAnimationStill() const
{
	return mAnimationStill;
}

void Ship::setAnimationStill(IND_Animation * mAnimationStill)
{
	this->mAnimationStill = mAnimationStill;
}

IND_Animation * Ship::getAnimationLeft() const
{
	return mAnimationLeft;
}

void Ship::setAnimationLeft(IND_Animation * mAnimationLeft)
{
	this->mAnimationLeft = mAnimationLeft;
}

IND_Animation * Ship::getAnimationRight() const
{
	return mAnimationRight;
}

void Ship::setAnimationRight(IND_Animation * mAnimationRight)
{
	this->mAnimationRight = mAnimationRight;
}

IND_Entity2d * Ship::getAnim2dShip() const
{
	return mAnim2dShip;
}

void Ship::setAnim2dShip(IND_Entity2d * mAnim2dShip)
{
	this->mAnim2dShip = mAnim2dShip;
}

void Ship::loadProperties()
{
	getAnim2dShip()->setHotSpot(0.5f, 0.5f);
	getAnim2dShip()->setPosition(getPosX(), getPosY(), 0);
	getAnim2dShip()->setScale(getScaleX(), getScaleY());
	getAnim2dShip()->setAngleXYZ(0, 0, getAngleZ());
}

void Ship::saveProperties()
{
	setPosX(getAnim2dShip()->getPosX());
	setPosY(getAnim2dShip()->getPosY());
	setScaleX(getAnim2dShip()->getScaleX());
	setScaleY(getAnim2dShip()->getScaleY());
	setAngleZ(getAnim2dShip()->getAngleZ());
}

void Ship::createShip(CIndieLib * const mI, const char * path, const float posX, const float posY)
{
	setMI(mI);
	initialize(mI);

	// Load Animations
	getMI()->_surfaceManager->add(getSurface(), "resources/Spaceship with motor new/1.png", IND_ALPHA, IND_32);

	getMI()->_animationManager->addToSurface(getAnimationShip(), path, IND_ALPHA, IND_32);

	getMI()->_animationManager->addToSurface(getAnimationStill(), "resources/Spaceship with motor new/Ship_still.xml", IND_ALPHA, IND_32);

	getMI()->_animationManager->addToSurface(getAnimationLeft(), "resources/Spaceship rotation smoke/LEFT/Rotate_left.xml", IND_ALPHA, IND_32);

	getMI()->_animationManager->addToSurface(getAnimationRight(), "resources/Spaceship rotation smoke/RIGHT/Rotate_right.xml", IND_ALPHA, IND_32);

	// Manage 2D entity

	getMI()->_entity2dManager->add(getEntity2d());
	getMI()->_entity2dManager->add(getAnim2dShip());

	getEntity2d()->setSurface(getSurface());
	getEntity2d()->setHotSpot(0.5f, 0.5f);
	getEntity2d()->setPosition(posX, posY, 0);

	getAnim2dShip()->setAnimation(getAnimationStill());
	getAnim2dShip()->setHotSpot(0.5f, 0.5f);
	getAnim2dShip()->setPosition(posX, posY, 0);

	int winWidth = getMI()->_window->getWidth();
	int winHeight = getMI()->_window->getHeight();
	float entWidth = getAnimationStill()->getHighWidth(0);
	float entHeight = getAnimationStill()->getHighHeight(0);
	float scale = ((0.05*(winWidth/entWidth)) < (0.15*(winHeight/entHeight)) ? (0.05*(winWidth / entWidth)) : (0.15*(winHeight / entHeight)));

	getEntity2d()->setScale(scale, scale);
	getAnim2dShip()->setScale(scale, scale);

	this->saveProperties();
}

void Ship::moveShip(Controls* controls)
{
	float mDelta = getMI()->_render->getFrameTime() / 1000.0f;

	// Set Rotated Animation and Restart the Sequence
	// IMPORTANT: everytime the animation is reset, the properties of the 2d entity are reset
	// Solution: load them from the Object class
	if (getMI()->_input->onKeyPress(controls->getRotateLeft()) || getMI()->_input->onKeyPress(controls->getRotateRight()))
	{
		getAnim2dShip()->setAnimation(getMI()->_input->isKeyPressed(controls->getRotateLeft()) ? getAnimationLeft() : getAnimationRight());
		getAnim2dShip()->setSequence(0); // Otherwise will continue from where it stopped

		this->loadProperties();
	}

	// Move or slow down

	if (getMI()->_input->isKeyPressed(controls->getAdvance()))
	{
		getAnim2dShip()->setAnimation(getAnimationShip());
		this->loadProperties();

		getAnim2dShip()->setPosition(getAnim2dShip()->getPosX() + getSpeed() * cos((-getAnim2dShip()->getAngleZ() + 90) / 180 * M_PI) * mDelta, getAnim2dShip()->getPosY() - getSpeed() * sin((-getAnim2dShip()->getAngleZ() + 90) / 180 * M_PI) * mDelta, 0);
		this->checkCoords();

		setSpeed(getSpeed() + ((getSpeed() + getAcceleration()*mDelta) < getMaxSpeed() ? getAcceleration()*mDelta : 0));

		this->saveProperties();
	}
	else
	{
		getAnim2dShip()->setAnimation(getAnimationStill());
		this->loadProperties();

		// Slow Down

		setSpeed(getSpeed() - ((getSpeed() - getAcceleration()*mDelta) > 0 ? getAcceleration()*mDelta : 0));
	}

	// In case Both the Up and either Left or Right keys are pressed, the later should overwrite the standard animation
	// Also perform the actual rotation on the ship

	if (getMI()->_input->isKeyPressed(controls->getRotateLeft()) || getMI()->_input->isKeyPressed(controls->getRotateRight()))
	{
		// Set Animation

		getAnim2dShip()->setAnimation(getMI()->_input->isKeyPressed(controls->getRotateLeft()) ? getAnimationLeft() : getAnimationRight());
		this->loadProperties();

		// Rotate

		getAnim2dShip()->setAngleXYZ(0, 0, getAnim2dShip()->getAngleZ() + (getMI()->_input->isKeyPressed(controls->getRotateLeft()) ? -1 : 1)*180*mDelta);
		this->saveProperties();
	}
	// Change to standard animation on the release of the Left/Right keys

	if (getMI()->_input->onKeyRelease(controls->getRotateLeft()) || getMI()->_input->onKeyRelease(controls->getRotateRight()))
	{
		getAnim2dShip()->setAnimation(getAnimationShip());
		this->loadProperties();
	}
}

Ship::~Ship()
{
	getAnimationShip()->destroy();
	getAnimationStill()->destroy();
	getAnimationLeft()->destroy();
	getAnimationRight()->destroy();
	getAnim2dShip()->destroy();
}