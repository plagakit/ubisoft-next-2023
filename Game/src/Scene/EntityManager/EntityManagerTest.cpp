#include <stdafx.h>

#include <Scene/Components/Transform/Transform.h>
#include <Scene/Components/Sprite/Sprite.h>
#include <Scene/Components/Timer/Timer.h>
#include <Scene/EntityManager/EntityManager.h>

class EntityManagerTest {

public:
	static void RunTests()
	{
		// Create randomness using <random>
		std::random_device rd;
		std::mt19937 r(rd());
		std::uniform_int_distribution<> randBool(0, 1);
		std::uniform_int_distribution<> randEntity(0, 1000);
		
		EntityManager em (1000);
		em.Init();

		// Test adding of entity & component
		Entity test = em.CreateEntity();
		em.AddComponent<Transform>(test, Transform());

		assert(em.HasEntity(test));
		assert(em.GetCount() == (Entity)1);
		em.GetComponentArray<Transform>();
		em.GetComponent<Transform>(test);
		em.GetComponentType<Transform>();


		// Test creating entities with random components
		for (int i = 0; i < 999; i++)
		{
			Entity ent = em.CreateEntity();

			if (randBool(r))
				em.AddComponent<Transform>(ent, Transform());

			if (randBool(r))
				em.AddComponent<Sprite>(ent, Sprite());

			if (randBool(r))
				em.AddComponent<Timer>(ent, Timer(5));

		}

		// Test deleting at random
		while (em.GetCount() > 0)
		{
			Entity id; 
			do
			{
				id = randEntity(r);
			} while (!em.HasEntity(id));
			em.QueueDelete(id);
			em.DeleteQueuedEntities();
		}
		
	}

};