#pragma once
class Actor;

class Component
{
public:
	Component();
	Component(Actor* actor, const char* name);
	~Component() ;

	const char* getName();
	Actor* getOwner();

	virtual void start();
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void end();
	virtual void onCollision(Actor* actor);

private:
	Actor* m_owner;
	const char* m_name;
};

