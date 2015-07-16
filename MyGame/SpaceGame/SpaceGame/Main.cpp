#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include "CIndieLib.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "IND_Animation.h"
#include "IND_Font.h"
#include "Planet.h"
#include "Ship.h"

/*
==================
Main
==================
*/
int IndieLib()
{
	// ----- IndieLib intialization -----

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;
	
	// ----- Get Window Dimensions

	int winWidth = mI->_window->getWidth();
	int winHeight = mI->_window->getHeight();

	// ----- Surface loading -----

	IND_Surface *mSurfaceBack = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceBack, "../SpaceGame/resources/Backgrounds/18.jpg", IND_OPAQUE, IND_32)) return 0;

	IND_Font* mFont = IND_Font::newFont();
	if (!mI->_fontManager->add(mFont, "../SpaceGame/resources/font_big.png", "../SpaceGame/resources/font_big.xml", IND_ALPHA, IND_32)) return 0;

	// Loding 2D Entities

	IND_Entity2d* mBack = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mBack);
	mBack->setSurface(mSurfaceBack);
	mBack->setScale((float)winWidth / mSurfaceBack->getWidth(), (float)winHeight / mSurfaceBack->getHeight());

	IND_Entity2d* mText = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mText);
	mText->setFont(mFont);
	mText->setPosition(1366, 200, 0);
	//mText->setText("");

	Planet* mPlanet = new Planet();
	mPlanet->createPlanet(mI, "../SpaceGame/resources/planets/1.png", 100, 100, 0.5f, 0.5f);

	Ship* mShip = new Ship();
	mShip->createShip(mI, "../SpaceGame/resources/Spaceship with motor new/Ship_advance.xml", winWidth/2, winHeight/2, 0.1f, 0.1f);

	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
	{
		mShip->moveShip();
		//mI->_render->showFpsInWindowTitle();
		mI->_input->update();
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();
	}

	// ----- Free -----

	mI->end();

	return 0;
}