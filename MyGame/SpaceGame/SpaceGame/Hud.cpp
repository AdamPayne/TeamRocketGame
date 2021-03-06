#include "Hud.h"

Hud::Hud() : mFont(IND_Font::newFont()), bulletsText(IND_Entity2d::newEntity2d()), healthText(IND_Entity2d::newEntity2d()), scoreText(IND_Entity2d::newEntity2d()), loadingText(IND_Entity2d::newEntity2d()), gameOverText(IND_Entity2d::newEntity2d())
{
}

CIndieLib * Hud::getMI() const
{
	return mI;
}

void Hud::setMI(CIndieLib* const mI)
{
	this->mI = mI;
}

IND_Font * Hud::getFont() const
{
	return mFont;
}

void Hud::setFont(IND_Font* mFont)
{
	this->mFont = mFont;
}

IND_Entity2d* Hud::getBulletsText() const
{
	return bulletsText;
}

void Hud::setBulletsText(IND_Entity2d* bulletsText)
{
	this->bulletsText = bulletsText;
}

IND_Entity2d * Hud::getHealthText() const
{
	return healthText;
}

void Hud::setHealthText(IND_Entity2d* healthText)
{
	this->healthText = healthText;
}

IND_Entity2d * Hud::getScoreText() const
{
	return scoreText;
}

void Hud::setScoreText(IND_Entity2d* scoreText)
{
	this->scoreText = scoreText;
}

IND_Entity2d * Hud::getLoadingText() const
{
	return loadingText;
}

void Hud::setLoadingText(IND_Entity2d* loadingText)
{
	this->loadingText = loadingText;
}

IND_Entity2d * Hud::getGameOverText() const
{
	return gameOverText;
}

void Hud::setGameOverText(IND_Entity2d* gameOverText)
{
	this->gameOverText = gameOverText;
}

void Hud::createHud(CIndieLib* const mI)
{
	setMI(mI);

	float scale = getMI()->_window->getWidth() / 1350.0f ;
	getMI()->_fontManager->add(getFont(), "../SpaceGame/resources/font_big.png", "../SpaceGame/resources/font_big.xml", IND_ALPHA, IND_32);

	getMI()->_entity2dManager->add(getBulletsText());
	getMI()->_entity2dManager->add(getHealthText());
	getMI()->_entity2dManager->add(getScoreText());
	getMI()->_entity2dManager->add(getLoadingText());
	getMI()->_entity2dManager->add(getGameOverText());

	getBulletsText()->setFont(getFont());
	getHealthText()->setFont(getFont());
	getScoreText()->setFont(getFont());
	getLoadingText()->setFont(getFont());
	getGameOverText()->setFont(getFont());

	getBulletsText()->setAlign(IND_LEFT);
	getHealthText()->setAlign(IND_LEFT);
	getScoreText()->setAlign(IND_LEFT);
	getLoadingText()->setAlign(IND_CENTER);
	getGameOverText()->setAlign(IND_LEFT);

	getBulletsText()->setScale(scale, scale);
	getHealthText()->setScale(scale, scale);
	getScoreText()->setScale(scale, scale);
	getLoadingText()->setScale(scale, scale);
	getGameOverText()->setScale(scale, scale);
	getGameOverText()->setLineSpacing(32);

	int winWidth = getMI()->_window->getWidth();
	int winHeight = getMI()->_window->getHeight();

	getBulletsText()->setPosition(0, 0, 2);
	getHealthText()->setPosition(winWidth * (1.2f / 3.0f), 0, 2);
	getScoreText()->setPosition(winWidth * (2.0f / 3.0f), 0, 2);
	getLoadingText()->setPosition(winWidth / 2.0f, winHeight / 2.0f, 2);
	getGameOverText()->setPosition(0, winHeight / 2.0f, 2);

	getLoadingText()->setText("Loading...");
	getLoadingText()->setShow(false);
}

void Hud::updateHud(Ship* mShip)
{
	getBulletsText()->setText(("Fired Bullets: " + to_string(mShip->getNumFiredBullets())).c_str());
	getHealthText()->setText(("Health: " + to_string(mShip->getHealth())).c_str());
	getScoreText()->setText(("Score: " + to_string(mShip->getScore())).c_str());
}

void Hud::updateGameOverText(int score)
{
	getGameOverText()->setText(("Game Over!\nYou scored: " + to_string(score)).c_str());
}

void Hud::hideHud()
{
	getBulletsText()->setShow(false);
	getHealthText()->setShow(false);
	getScoreText()->setShow(false);
	getGameOverText()->setShow(false);
}

void Hud::showHud()
{
	getBulletsText()->setShow(true);
	getHealthText()->setShow(true);
	getScoreText()->setShow(true);
}

Hud::~Hud()
{
	getMI()->_fontManager->remove(getFont());
	getMI()->_entity2dManager->remove(getBulletsText());
	getMI()->_entity2dManager->remove(getHealthText());
	getMI()->_entity2dManager->remove(getScoreText());
}