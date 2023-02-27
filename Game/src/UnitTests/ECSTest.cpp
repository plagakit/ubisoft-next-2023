#include <stdafx.h>

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Sprite/Sprite.h"
#include "Scene/Components/Timer/Timer.h"

class EntityManagerTest {

public:
	static void RunTests()
	{
		// Create randomness using <random>
		std::random_device rd;
		std::mt19937 r(rd());
		std::uniform_int_distribution<> randBool(0, 1);
		std::uniform_int_distribution<> randEntity(0, 1000);
		
		Scene scene;
		scene.Init();

		// Test adding of entity & component
		Entity test = scene.CreateEntity();
		Transform testComponent = Transform();
		scene.AddComponent<Transform>(test, testComponent);

		assert(scene.DoesEntityExist(test));
		assert(scene.GetCount() == (Entity)1);
		assert(scene.GetComponentArray<Transform>() != nullptr);
		scene.GetComponent<Transform>(test); // can't compare addresses b/c components are copied, just run it to see if it works
		assert(scene.GetComponentType<Transform>() == (ComponentID)0);


		// Test creating entities with random components
		for (int i = 0; i < 999; i++)
		{
			Entity ent = scene.CreateEntity();

			if (randBool(r))
				scene.AddComponent<Transform>(ent, Transform());

			if (randBool(r))
				scene.AddComponent<Sprite>(ent, Sprite());

			if (randBool(r))
				scene.AddComponent<Timer>(ent, Timer(5));

		}

		// Test deleting at random
		while (scene.GetCount() > 0)
		{
			Entity id; 
			do
			{
				id = randEntity(r);
			} while (!scene.DoesEntityExist(id));
			scene.QueueDelete(id);
			scene.DeleteQueuedEntities();
		}
		
	}

};