#include "Menu.h"

Menu::Menu() : hidden(false), scale(0), selectedID(0),  mI(NULL), mousePointerSurface(IND_Surface::newSurface()), mousePointer(IND_Entity2d::newEntity2d())
{
}

bool Menu::isHidden() const
{
	return hidden;
}

void Menu::setHidden(float hidden)
{
	this->hidden = hidden;
}

bool Menu::isExit() const
{
	return exit;
}

void Menu::setExit(float exit)
{
	this->exit = exit;;
}

short Menu::getSelectedID() const
{
	return selectedID;
}

void Menu::setSelectedID(short selectedID)
{
	this->selectedID = selectedID;
}

float Menu::getScale() const
{
	return scale;
}

void Menu::setScale(float scale)
{
	this->scale = scale;
}

CIndieLib * Menu::getMI() const
{
	return mI;
}

void Menu::setMI(CIndieLib* const mI)
{
	this->mI = mI;
}

IND_Surface * Menu::getMousePointerSurface() const
{
	return mousePointerSurface;
}

void Menu::setMousePointerSurface(IND_Surface* mousePointerSurface)
{
	this->mousePointerSurface = mousePointerSurface;
}

IND_Entity2d * Menu::getMousePointer() const
{
	return mousePointer;
}

void Menu::setMousePointer(IND_Entity2d* mousePointer)
{
	this->mousePointer = mousePointer;
}

vector<IND_Surface*>& Menu::getIdleBtnSurfaces()
{
	return idleBtnSurfaces;
}

void Menu::setIdleBtnSurfaces(vector<IND_Surface*> idleBtnSurfaces)
{
	this->idleBtnSurfaces = idleBtnSurfaces;
}

vector<IND_Surface*>& Menu::getActiveBtnSurfaces()
{
	return activeBtnSurfaces;
}

void Menu::setActiveBtnSurfaces(vector<IND_Surface*> activeBtnSurfaces)
{
	this->activeBtnSurfaces = activeBtnSurfaces;
}

vector<IND_Entity2d*>& Menu::getMenuOptions()
{
	return menuOptions;
}

void Menu::setMenuOptions(vector<IND_Entity2d*> menuOptions)
{
	this->menuOptions = menuOptions;
}

void Menu::createMenu(CIndieLib* const mI)
{
	setMI(mI);
	initialize(mI);

	int winWidth = getMI()->_window->getWidth();
	int winHeight = getMI()->_window->getHeight();

	// Manage the mouse pointer
	getMI()->_surfaceManager->add(getMousePointerSurface(), "../SpaceGame/resources/cursor.png", IND_ALPHA, IND_32);
	getMI()->_entity2dManager->add(getMousePointer());
	getMousePointer()->setSurface(getMousePointerSurface());
	getMousePointer()->setBoundingAreas("../SpaceGame/resources/cursor_collisions.xml");

	// Manage Button Surfaces
	for (int i = 0; i < 5; i++)
	{
		getIdleBtnSurfaces().push_back(IND_Surface::newSurface());
		getActiveBtnSurfaces().push_back(IND_Surface::newSurface());
		switch (i)
		{
			//-----Resume-----
			case 0:
				getMI()->_surfaceManager->add(getIdleBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnResume_idle.png", IND_ALPHA, IND_32);
				getMI()->_surfaceManager->add(getActiveBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnResume_active.png", IND_ALPHA, IND_32);
				break;
			//-----New Game-----
			case 1:
				getMI()->_surfaceManager->add(getIdleBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnNG_idle.png", IND_ALPHA, IND_32);
				getMI()->_surfaceManager->add(getActiveBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnNG_active.png", IND_ALPHA, IND_32);
				break;
			//-----Load Game-----
			case 2:
				getMI()->_surfaceManager->add(getIdleBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnLG_idle.png", IND_ALPHA, IND_32);
				getMI()->_surfaceManager->add(getActiveBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnLG_active.png", IND_ALPHA, IND_32);
				break;
			//-----Save Game-----
			case 3:
				getMI()->_surfaceManager->add(getIdleBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnSG_idle.png", IND_ALPHA, IND_32);
				getMI()->_surfaceManager->add(getActiveBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnSG_active.png", IND_ALPHA, IND_32);
				break;
			//-----Exit-----
			case 4:
				getMI()->_surfaceManager->add(getIdleBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnExit_idle.png", IND_ALPHA, IND_32);
				getMI()->_surfaceManager->add(getActiveBtnSurfaces().back(), "../SpaceGame/resources/Buttons/btnExit_active.png", IND_ALPHA, IND_32);
				break;
		}
	}

	// set the scale to 6.5% of the window height
	setScale(0.065 * winHeight / getIdleBtnSurfaces().back()->getHeight());

	for (int i = 0; i < 5; i++)
	{
		getMenuOptions().push_back(IND_Entity2d::newEntity2d());
		getMI()->_entity2dManager->add(getMenuOptions().back());

		getMenuOptions().back()->setSurface(getIdleBtnSurfaces().at(i));
		getMenuOptions().back()->setHotSpot(0.5f, 0.5f);

		getMenuOptions().back()->setScale(getScale(), getScale());

		float yOffset = (0.3f + i * 0.1f) * winHeight; // also chage the initial offset (0.35f) in restoreProperties
		getMenuOptions().back()->setPosition(winWidth / 2.0f, yOffset, 2);
		getMenuOptions().back()->setBoundingRectangle(("option" + to_string(i)).c_str(), 0, 0, getIdleBtnSurfaces().at(i)->getWidth(), getIdleBtnSurfaces().at(i)->getHeight());
		//getMenuOptions().back()->setShow(false);
	}
}

void Menu::updateMenu(Hud* mHud, Save* quickSave, vector<Planet*>& mPlanets, Ship*& mShip)
{
	// check for collisions
	short int i = 0, oldID = getSelectedID();
	setSelectedID(-1);
	for (vector<IND_Entity2d*>::iterator it = getMenuOptions().begin(); it != getMenuOptions().end(); ++it)
	{
		if (getMI()->_entity2dManager->isCollision(getMousePointer(), "cursor_point", *it, ("option" + to_string(i)).c_str()))
		{
			(*it)->setSurface(getActiveBtnSurfaces().at(i));
			setSelectedID(i);
			restoreProperties(*it, getSelectedID());

			// check if left mouse button was pressed
			if (getMI()->_input->isMouseButtonPressed(IND_MBUTTON_LEFT))
			{
				switch (i)
				{
					//-----Resume-----
					case 0:
						this->hide();
					break;
					//-----New Game-----
					case 1:
						this->hide();
						startNewGame(getMI(), mHud, mPlanets, mShip);
					break;
					//-----Load Game-----
					case 2:
						this->hide();
						deleteObjects(mHud, mShip, mPlanets);
						break;
					//-----Save Game-----
					case 3:
						quickSave->makeSave(mI, mShip, mPlanets);
						break;
					//-----Exit-----
					case 4:
						this->hide();
						setExit(true);
						break;
				}
			}
		}
		i++;
	}

	// if the oldID is different from the selected id then the user is longer hovering over the button
	if (oldID != -1 && oldID != getSelectedID())
	{
		getMenuOptions().at(oldID)->setSurface(getIdleBtnSurfaces().at(oldID));
		restoreProperties(getMenuOptions().at(oldID), oldID);
	}

	// update the mouse pointer
	getMousePointer()->setPosition(getMI()->_input->getMouseX(), getMI()->_input->getMouseY(), 3);
}

void Menu::hide()
{
	setHidden(true);
	getMousePointer()->setShow(false);
	for (vector<IND_Entity2d*>::iterator it = getMenuOptions().begin(); it != getMenuOptions().end(); ++it)
	{
		(*it)->setShow(false);
	}
}

void Menu::show()
{
	setHidden(false);
	getMousePointer()->setShow(true);
	for (vector<IND_Entity2d*>::iterator it = getMenuOptions().begin(); it != getMenuOptions().end(); ++it)
	{
		(*it)->setShow(true);
	}
}

void Menu::restoreProperties(IND_Entity2d* option, short int id)
{
	option->setHotSpot(0.5f, 0.5f);
	option->setScale(getScale(), getScale());
	option->setPosition(getMI()->_window->getWidth() / 2.0f, (0.3f + 0.1 * id) * getMI()->_window->getHeight(), 2);
	option->setBoundingRectangle(("option" + to_string(id)).c_str(), 0, 0, getIdleBtnSurfaces().at(id)->getWidth(), getIdleBtnSurfaces().at(id)->getHeight());
}

Menu::~Menu()
{
	//getMI()->_fontManager->remove(getFont());
	getMI()->_surfaceManager->remove(getMousePointerSurface());

	getMI()->_entity2dManager->remove(getMousePointer());
	for (vector<IND_Surface*>::iterator it = getIdleBtnSurfaces().begin(); it != getIdleBtnSurfaces().end(); ++it)
	{
		getMI()->_surfaceManager->remove(*it);
	}
	for (vector<IND_Surface*>::iterator it = getActiveBtnSurfaces().begin(); it != getActiveBtnSurfaces().end(); ++it)
	{
		getMI()->_surfaceManager->remove(*it);
	}
	for (vector<IND_Entity2d*>::iterator it = getMenuOptions().begin(); it != getMenuOptions().end(); ++it)
	{
		getMI()->_entity2dManager->remove(*it);
	}
	getMenuOptions().clear();
}

void startNewGame(CIndieLib* const mI, Hud* mHud, vector<Planet*>& mPlanets, Ship*& mShip)
{
	deleteObjects(mHud, mShip, mPlanets);
	mI->_render->beginScene();
	mI->_entity2dManager->renderEntities2d();
	mI->_render->endScene();

	int winWidth = mI->_window->getWidth();
	int winHeight = mI->_window->getHeight();

	// add 8 planets
	for (int i = 0; i < 8; i++)
	{
		mPlanets.push_back(new Planet());

		// Random Percent 
		float randPercent = (0.05f + (rand() % 5 + 1) / 100.0f);
		float randDegree = (i*M_PI / 4.0f); //+ (rand() % 60 + 1) / 100.0f;

		float radius = (1 - randPercent)*winHeight / 2.0f;
		float posX = winWidth / 2.0 + radius*cos(randDegree);
		float posY = winHeight / 2.0 + radius*sin(randDegree);

		// there are 3 orbits: 50%, 65%, and 80% of half of the window's height
		float orbitRadius = (winHeight / 2.0f) * ((60 + 15 * (i % 3)) / 100.0f);

		mPlanets.back()->createPlanet(mI, ("../SpaceGame/resources/Planets/" + to_string(i + 1) + ".png").c_str(), posX, posY, -randDegree, randPercent, rand() % 2, orbitRadius);
		//while (mPlanets.back()->addSatellite());
	}

	mShip = new Ship(100, 0, 0, 0, winWidth / 20.0f, winWidth / 1.5f);
	mShip->createShip(mI, "../SpaceGame/resources/Spaceship with motor new/1.png", winWidth / 2.0f, winHeight / 2.0f);

	mHud->showHud();
	mHud->getLoadingText()->setShow(false);
}

void  deleteObjects(Hud* mHud, Ship*& mShip, vector<Planet*>& mPlanets)
{
	// Adjust the hud
	mHud->hideHud();
	mHud->getLoadingText()->setShow(true);
	// check if mShip actually points to an object
	if (mShip)
	{
		delete mShip;
		mShip = NULL;
		for (vector<Planet*>::iterator it = mPlanets.begin(); it != mPlanets.end(); ++it)
		{
			delete (*it);
		}
		mPlanets.clear();
	}
}