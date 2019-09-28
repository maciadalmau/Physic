#pragma once
#include "Module.h"
#include "Globals.h"

#define METERS_TO_PIXELS(a) a * 10
#define PIXELS_TO_METERS(a) a * 0.1

class b2World;


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:
	
	b2World* myWorld = nullptr;
	bool debug;
};