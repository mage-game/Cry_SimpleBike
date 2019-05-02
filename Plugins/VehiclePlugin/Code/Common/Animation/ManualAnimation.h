#pragma once
#include "CryAnimation\ICryAnimation.h"
#include "CryEntitySystem\IEntityComponent.h"

namespace SimpleVehicle
{
	class ManualAnimation
	{
	public:
		void Init(IEntity* pEntity);

		bool StartAnimation(int layerId, const string& name);
		bool StopAnimation(int layerId);
		void SetAnimTime(int layerId, float time);
	private:
		ISkeletonAnim * m_SkeletonAnim = nullptr;
	};
}
