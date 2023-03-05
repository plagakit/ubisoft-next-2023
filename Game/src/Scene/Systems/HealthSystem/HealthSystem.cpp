#include <stdafx.h>

#include "HealthSystem.h"
#include "Scene/Scene.h"
#include "Scene/Components/DamageField/DamageField.h"
#include "Scene/Components/PrimitiveComponents.h"


void HealthSystem::ExecuteDamage(Scene& scene, Entity attacker, Entity target)
{
	DamageField df = scene.GetComponent<DamageField>(attacker);
	Health hp = scene.GetComponent<Health>(target);

	Signature sig = scene.GetSignature(target);
	if (df.TryHit(target, sig))
	{
		hp -= df.damage;
		s_DamagedBy.Emit(scene, target, attacker);
		if (hp <= 0)
			s_Died.Emit(scene, target);
	}

	scene.SetComponent<DamageField>(target, df);
	scene.SetComponent<Health>(target, hp);
}


void HealthSystem::OnCollision(Scene& scene, Entity id1, Entity id2, Vector2 _unused)
{
	if (scene.HasComponent<DamageField>(id1) && scene.HasComponent<Health>(id2))
		ExecuteDamage(scene, id1, id2);
}

void HealthSystem::OnTrigger(Scene& scene, Entity id1, Entity id2, Vector2 _unused)
{
	if (scene.HasComponent<DamageField>(id1) && scene.HasComponent<Health>(id2))
		ExecuteDamage(scene, id1, id2);
}