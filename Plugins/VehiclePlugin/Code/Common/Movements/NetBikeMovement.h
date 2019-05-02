#pragma once
#include "BikeMovementBase.h"

namespace SimpleVehicle
{
	class NetBikeMovement :public BikeMovementBase
	{
	public:
		NetBikeMovement() = default;
		~NetBikeMovement() = default;

		void Init(IEntity* pEntity) override;
		void Update(float frameTime) override;

	private:
		void UpdateTransfrom(const BikeTransfrom& bikeTransform);
		void UpdateAnimation(const BikeAnimation& bikeAnimation);
	};
}

