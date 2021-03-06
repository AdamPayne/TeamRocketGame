#include "ErrorHandler.h"

ErrorHandler::ErrorHandler() : initialized (false), mFont(IND_Font::newFont()), mText2d(IND_Entity2d::newEntity2d())
{
}

bool ErrorHandler::isInitialized() const
{
	return initialized;
}

void ErrorHandler::setInitialized(bool initialized)
{
	this->initialized = initialized;
}

IND_Font * ErrorHandler::getFont() const
{
	return mFont;
}

void ErrorHandler::setFont(IND_Font * mFont)
{
	this->mFont = mFont;
}

IND_Entity2d * ErrorHandler::getText2d() const
{
	return mText2d;
}

void ErrorHandler::setText2d(IND_Entity2d * mText2d)
{
	this->mText2d = mText2d;
}

void ErrorHandler::initialize(CIndieLib * mI)
{
	// prevent unintentional double initialization
	if (!isInitialized())
	{
		mi = mI;

		mI->_fontManager->add(getFont(), "../SpaceGame/resources/font_small.png", "../SpaceGame/resources/font_small.xml", IND_ALPHA, IND_32);

		mI->_entity2dManager->add(getText2d());

		getText2d()->setFont(getFont());

		getText2d()->setAlign(IND_CENTER);

		setInitialized(true);
	}
}

void ErrorHandler::writeError(float posX, float posY,string label, string value)
{
	getText2d()->setPosition(posX, posY, 1);
	getText2d()->setText((label+":" + value).c_str());
}

void ErrorHandler::writeError(float posX, float posY, string label, float value)
{
	char* text = new char[100];
	sprintf(text, "%f", value);
	writeError(posX, posY, label, text);
	delete[] text;
}

void ErrorHandler::clear()
{
	getText2d()->setText("");
}

ErrorHandler::~ErrorHandler()
{
	if (mi)
	{
		mi->_fontManager->remove(getFont());
		mi->_entity2dManager->remove(getText2d());
	}
}
