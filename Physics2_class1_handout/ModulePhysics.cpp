#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

// TODO 1: Include Box 2 header and library

#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG

#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib")
#else
#pragma comment(lib, "Box2D/libx86/Release/Box2D.lib")
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
	
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	
	
	b2Vec2 gravity(0.0f, 10.0f);
	myWorld = new b2World(gravity);

	// TODO 4: Create a a big static circle as "ground"
	
	//BIGCIRCLE
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(PIXELS_TO_METERS(500), PIXELS_TO_METERS(300));
	b2Body* groundBody = myWorld->CreateBody(&groundBodyDef);
	b2CircleShape circle;
	circle.m_radius = PIXELS_TO_METERS(250);
	b2FixtureDef fixture;
	fixture.shape = &circle;
	groundBody->CreateFixture(&fixture);

	//GROUND
	b2BodyDef groundBodyDef2;
	groundBodyDef2.type = b2_staticBody;
	groundBodyDef2.position.Set(PIXELS_TO_METERS(512), PIXELS_TO_METERS(800));
	b2Body* groundBody3 = myWorld->CreateBody(&groundBodyDef2);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(PIXELS_TO_METERS(100), PIXELS_TO_METERS(100));
	groundBody3->CreateFixture(&groundBox, 0.0f);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	
	myWorld->Step(1.0f / 60.0f, 8, 3);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()));
		b2Body* groundBody2 = myWorld->CreateBody(&bodyDef);
		b2CircleShape miniCircle;
		float randomradius = 0;
		randomradius = (rand() % 100) + 1;
		miniCircle.m_radius = PIXELS_TO_METERS(randomradius);
		b2FixtureDef fixture2;
		fixture2.shape = &miniCircle;
		groundBody2->CreateFixture(&fixture2);
	}
		

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = myWorld->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;
				case b2Shape::e_polygon:
				{
					b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
					int32 count = shape->GetVertexCount();
					b2Vec2 prev = b->GetWorldPoint(shape->GetVertex(0)); 
					b2Vec2 v;


					for (int32 i = 0; i < count; i++)
					{
						v = b->GetWorldPoint(shape->GetVertex(i));

						if(i > 0)
						{
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 255, 255);
							prev = v;
						}
					}

					v = b->GetWorldPoint(shape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 255, 255);

					/*SDL_Rect rect;
					rect.x = 412;
					rect.y = 800;
					rect.w = 200;
					rect.h = -100;*/
					//App->renderer->DrawQuad(rect, 255, 255, 255, 255, false);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete myWorld;
	return true;
}
