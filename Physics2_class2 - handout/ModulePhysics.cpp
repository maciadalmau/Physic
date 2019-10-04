#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// On space bar press, create a circle on mouse position
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{

		CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 50, 1);

		/*
		b2BodyDef body;
		body.type = b2_dynamicBody;
		float radius = PIXEL_TO_METERS(25);
		body.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		b2Body* b = world->CreateBody(&body);

		b2CircleShape shape;
		shape.m_radius = radius;
		b2FixtureDef fixture;
		fixture.shape = &shape;

		b->CreateFixture(&fixture);
		*/
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		// TODO 1: When pressing 2, create a box on the mouse position
		b2BodyDef body2;
		body2.type = b2_dynamicBody;
		body2.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		b2Body* b2 = world->CreateBody(&body2);

		b2PolygonShape shape2;
		shape2.SetAsBox(PIXEL_TO_METERS(25), PIXEL_TO_METERS(25));
		b2FixtureDef fixture2;
		fixture2.shape = &shape2;
		fixture2.density = 1.0f;
		b2->CreateFixture(&fixture2);
		// TODO 2: To have the box behave normally, set fixture's density to 1.0f
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// TODO 3: Create a chain shape using those vertices
		// remember to convert them from pixels to meters!
		
		/*
		int points[24]
		{
			-38, 80,
			-44, -54,
			-16, -60,
			-16, -17,
			19, -19,
			19, -79,
			61, -77,
			57, 73,
			17, 78,
			20, 16,
			-25, 13,
			-9, 72
		};

		b2Vec2 a[24];
		*/
		
		b2BodyDef chain;
		chain.type = b2_dynamicBody;
		chain.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));
		b2Body* groundBody = world->CreateBody(&chain);
		b2Vec2 points[60];

		points[0].Set(PIXEL_TO_METERS(46), PIXEL_TO_METERS(131));
		points[1].Set(PIXEL_TO_METERS(34), PIXEL_TO_METERS(137));
		points[2].Set(PIXEL_TO_METERS(39), PIXEL_TO_METERS(125));
		points[3].Set(PIXEL_TO_METERS(22), PIXEL_TO_METERS(124));		points[4].Set(PIXEL_TO_METERS(30), PIXEL_TO_METERS(115));
		points[5].Set(PIXEL_TO_METERS(10), PIXEL_TO_METERS(103));
		points[6].Set(PIXEL_TO_METERS(28), PIXEL_TO_METERS(91));
		points[7].Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(76));		points[8].Set(PIXEL_TO_METERS(29), PIXEL_TO_METERS(62));		points[9].Set(PIXEL_TO_METERS(13), PIXEL_TO_METERS(35));		points[10].Set(PIXEL_TO_METERS(42), PIXEL_TO_METERS(39));		points[11].Set(PIXEL_TO_METERS(40), PIXEL_TO_METERS(0));		points[12].Set(PIXEL_TO_METERS(74), PIXEL_TO_METERS(32));
		points[13].Set(PIXEL_TO_METERS(87), PIXEL_TO_METERS(4));
		points[14].Set(PIXEL_TO_METERS(94), PIXEL_TO_METERS(40));
		points[15].Set(PIXEL_TO_METERS(111), PIXEL_TO_METERS(34));		points[16].Set(PIXEL_TO_METERS(104), PIXEL_TO_METERS(57));
		points[17].Set(PIXEL_TO_METERS(115), PIXEL_TO_METERS(66));
		points[18].Set(PIXEL_TO_METERS(109), PIXEL_TO_METERS(73));
		points[19].Set(PIXEL_TO_METERS(104), PIXEL_TO_METERS(93));		points[20].Set(PIXEL_TO_METERS(109), PIXEL_TO_METERS(99));		points[21].Set(PIXEL_TO_METERS(103), PIXEL_TO_METERS(105));		points[22].Set(PIXEL_TO_METERS(100), PIXEL_TO_METERS(114));		points[23].Set(PIXEL_TO_METERS(98), PIXEL_TO_METERS(126));		points[24].Set(PIXEL_TO_METERS(96), PIXEL_TO_METERS(135));		points[25].Set(PIXEL_TO_METERS(91), PIXEL_TO_METERS(140));		points[26].Set(PIXEL_TO_METERS(83), PIXEL_TO_METERS(148));		points[27].Set(PIXEL_TO_METERS(73), PIXEL_TO_METERS(149));		points[28].Set(PIXEL_TO_METERS(54), PIXEL_TO_METERS(140));		
		
		
		b2ChainShape chains;
		chains.CreateLoop(points, 29);		b2FixtureDef fixture;		fixture.shape = &chains;		groundBody->CreateFixture(&fixture);

	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
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
	delete world;

	return true;
}

void ModulePhysics::CreateCircle(int x, int y, int radium, int type)
{

	b2BodyDef body;
	if(type == 1)
	{
		body.type = b2_dynamicBody;
	}
	if(type == 2)
	{
		body.type = b2_staticBody;
	}

	float radius = PIXEL_TO_METERS(radium);
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

}