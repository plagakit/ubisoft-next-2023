#include <stdafx.h>

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Wireframe/Wireframe.h"
#include "Scene/Components/Timer/Timer.h"

class ECSTest {

public:
	static void RunTests()
	{
		// Create randomness using <random>
		std::random_device rd;
		std::mt19937 r(rd());
		std::uniform_int_distribution<> randBool(0, 1);
		std::uniform_int_distribution<> randEntity(0, 1000);
		
		Scene scene;

		// Test adding of entity & component
		Entity test = scene.CreateEntity();
		Transform testComponent = Transform();
		scene.AddComponent<Transform>(test, testComponent);

		assert(scene.DoesEntityExist(test));
		assert(scene.GetCount() == (Entity)1);
		assert(scene.GetComponentArray<Transform>() != nullptr);
		scene.GetComponent<Transform>(test); // can't compare addresses b/c components are copied, just run it to see if it works
		
		auto a = scene.GetComponentType<Transform>();
		assert(a == (ComponentID)0);


		// Test creating entities with random components
		for (int i = 0; i < 999; i++)
		{
			Entity ent = scene.CreateEntity();

			if (randBool(r))
				scene.AddComponent<Transform>(ent, Transform());

			if (randBool(r))
				scene.AddComponent<Wireframe>(ent, Wireframe());

			if (randBool(r))
				scene.AddComponent<Timer>(ent, Timer(5));

		}

		// Test deleting at random

		Entity prevCount = scene.GetCount();
		while (scene.GetCount() > 0)
		{
			Entity id; 
			do
			{
				id = randEntity(r);
			} while (!scene.DoesEntityExist(id));
			scene.QueueDelete(id);
			scene.DeleteQueuedEntities();
			assert(prevCount > scene.GetCount());
			prevCount++;
		}
		
	}

};