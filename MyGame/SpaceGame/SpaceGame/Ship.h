#ifndef SHIP_H
#define SHIP_H

#include "irrKlang.h"
#include "Object.h"
#include "Bullet.h"
#include "Controls.h"
#include "IND_Animation.h"

class Ship : public Object {
private:
	int health;
	int numFiredBullets;
	int score;
	float speed;
	float acceleration;
	float jolt;
	float maxSpeed;

	IND_Animation* mAnimationStill;
	IND_Animation* mAnimationShip;
	IND_Animation* mAnimationLeft;
	IND_Animation* mAnimationRight;
	IND_Entity2d* mAnim2dShip;

	irrklang::ISoundEngine* soundEngine;
	irrklang::ISound* rocketSound;
	irrklang::ISoundSource* blasterSoundSource;
	irrklang::ISound* blasterSound;

	vector<Bullet*> mBullets;
public:
	Ship(int health = 100, int numFiredBullets = 0, int score = 0, float acceleration = 0.0f, float jolt = 50.0f, float maxSpeed = 800.0f);

	// @overwrite
	virtual float getAngleZRadian() const;

	int getHealth() const;
	void setHealth(int);
	int getNumFiredBullets() const;
	void setNumFiredBullets(int);
	int getScore()const;
	void setScore(int);

	float getSpeed() const;
	void setSpeed(float);
	float getAcceleration() const;
	void setAcceleration(float);
	float getJolt() const;
	void setJolt(float);
	float getMaxSpeed() const;
	void setMaxSpeed(float);

	IND_Animation* getAnimationStill() const;
	void setAnimationStill(IND_Animation*);
	IND_Animation* getAnimationShip() const;
	void setAnimationShip(IND_Animation*);
	IND_Animation* getAnimationLeft() const;
	void setAnimationLeft(IND_Animation*);
	IND_Animation* getAnimationRight() const;
	void setAnimationRight(IND_Animation*);
	IND_Entity2d* getAnim2dShip() const;
	void setAnim2dShip(IND_Entity2d*);

	irrklang::ISoundEngine* getSoundEngine() const;
	void setSoundEngine(irrklang::ISoundEngine*);
	irrklang::ISound* getRocketSound() const;
	void setRocketSound(irrklang::ISound*);
	irrklang::ISoundSource* getBlasterSoundSource() const;
	void setBlasterSoundSource(irrklang::ISoundSource*);
	irrklang::ISound* getBlasterSound() const;
	void setBlasterSound(irrklang::ISound*);

	vector<Bullet*>& getBullets();
	void setBullets(vector<Bullet*>);

	// Reseting the animation, also resets the properties of Anim2d
	// Use this function to load them from the object entity that holds the surface which never changes
	void loadPropsAnim2d();

	void createShip(CIndieLib* const, const char*, const float, const float);
	void updateShip(Controls*, float);

	~Ship();
};
#endif
