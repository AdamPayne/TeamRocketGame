#include "Ship.h"

Ship::Ship() : speed(0), acceleration(100), maxSpeed(400)
{
}

void Ship::createShip(CIndieLib * const mI, const char * path, const float posX, const float posY, const float scaleX, const float scaleY)
{
	setMI(mI);

	// Load Animations

	mAnimationShip = IND_Animation::newAnimation();
	getMI()->_animationManager->addToSurface(mAnimationShip, path, IND_ALPHA, IND_32);

	mAnimationLeft = IND_Animation::newAnimation();
	getMI()->_animationManager->addToSurface(mAnimationLeft, "../SpaceGame/resources/Spaceship rotation smoke/LEFT/Rotate_left.xml", IND_ALPHA, IND_32);

	mAnimationRight = IND_Animation::newAnimation();
	getMI()->_animationManager->addToSurface(mAnimationRight, "../SpaceGame/resources/Spaceship rotation smoke/RIGHT/Rotate_right.xml", IND_ALPHA, IND_32);

	// Manage 2D entity

	setEntity2d(IND_Entity2d::newEntity2d());
	getMI()->_entity2dManager->add(getEntity2d());

	getEntity2d()->setAnimation(mAnimationShip);
	getEntity2d()->setHotSpot(0.5f, 0.5f);
	getEntity2d()->setPosition(posX, posY, 0);
	getEntity2d()->setScale(scaleX, scaleY);

	saveProperties();
}

void Ship::checkCoords()
{
	// Check for negative coordinates

	if (getEntity2d()->getPosX() < 0)
	{
		getEntity2d()->setPosition(0, getEntity2d()->getPosY(), 0);
	}

	if (getEntity2d()->getPosY() < 0)
	{
		getEntity2d()->setPosition(getEntity2d()->getPosX(), 0, 0);
	}

	// Check for too big coordinates

	if (getEntity2d()->getPosX() > getMI()->_window->getWidth())
	{
		getEntity2d()->setPosition(getMI()->_window->getWidth(), getEntity2d()->getPosY(), 0);
	}

	if (getEntity2d()->getPosY() > getMI()->_window->getHeight())
	{
		getEntity2d()->setPosition(getEntity2d()->getPosX(), getMI()->_window->getHeight(), 0);
	}
}

void Ship::moveShip()
{
	float mDelta = getMI()->_render->getFrameTime() / 1000.0f;

	// Set Rotated Animation and Restart the Sequence
	// IMPORTANT: everytime the animation is reset, the properties of the 2d entity are reset
	// Solution: load them from the Object class 

	if (getMI()->_input->onKeyPress(IND_KEYLEFT) || getMI()->_input->onKeyPress(IND_KEYRIGHT))
	{
		getEntity2d()->setAnimation(getMI()->_input->isKeyPressed(IND_KEYLEFT) ? mAnimationLeft : mAnimationRight);
		getEntity2d()->setSequence(0); // Otherwise will continue from where it stopped

		this->loadProperties();
	}

	// Move 

	if (getMI()->_input->isKeyPressed(IND_KEYUP))
	{
		getEntity2d()->setAnimation(mAnimationShip);
		this->loadProperties();

		getEntity2d()->setPosition(getEntity2d()->getPosX() + speed * cos((-getEntity2d()->getAngleZ() + 90) / 180 * M_PI) * mDelta, getEntity2d()->getPosY() - speed * sin((-getEntity2d()->getAngleZ() + 90) / 180 * M_PI) * mDelta, 0);
		this->checkCoords();

		speed += ((speed + acceleration*mDelta) < maxSpeed ? acceleration*mDelta : 0);

		this->saveProperties();
	}

	// In case Both the Up and either Left or Right keys are pressed, the later should overwrite the standard animation
	// Also perform the actual rotation on the ship

	if (getMI()->_input->isKeyPressed(IND_KEYLEFT) || getMI()->_input->isKeyPressed(IND_KEYRIGHT))
	{
		// Set Animation

		getEntity2d()->setAnimation(getMI()->_input->isKeyPressed(IND_KEYLEFT) ? mAnimationLeft : mAnimationRight);
		this->loadProperties();

		// Rotate

		getEntity2d()->setAngleXYZ(0, 0, getEntity2d()->getAngleZ() + (getMI()->_input->isKeyPressed(IND_KEYLEFT) ? -1 : 1)*180*mDelta);
		this->saveProperties();
	}

	// Change to standard animation on the release of the Left/Right keys

	if (getMI()->_input->onKeyRelease(IND_KEYLEFT) || getMI()->_input->onKeyRelease(IND_KEYRIGHT))
	{
		getEntity2d()->setAnimation(mAnimationShip);
		this->loadProperties();
	}

	// Reset the speed on release of the up key

	if (getMI()->_input->onKeyRelease(IND_KEYUP))
	{
		speed = 0;
	}
}

Ship::~Ship()
{
	mAnimationShip->destroy();
	mAnimationLeft->destroy();
	mAnimationRight->destroy();
}
