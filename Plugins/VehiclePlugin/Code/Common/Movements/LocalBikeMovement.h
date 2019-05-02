#pragma once
#include "BikeMovementBase.h"

namespace SimpleVehicle
{
	class LocalBikeMovement :public BikeMovementBase
	{
	public:
		LocalBikeMovement() = default;
		~LocalBikeMovement() = default;

		void Turn(float angles);
		void Move(float speed);

		void Init(IEntity* pEntity) override;
		void Update(float frameTime) override;

		void Physicalize();

	private:
		void AdjustAngles(float& angles, float temp);

	private:
		const float MAX_TURN_ANGLES = 60.0f;
		const float MIN_TURN_ANGLES = -60.0f;
		const float MAX_MOVE_SPEED = 30.0f;
		const float MIN_MOVE_SPEED = -30.0f;
		const float MAX_BIKE_ROLL = 15.0f;
		const float MIN_BIKE_ROLL = -15.0f;

		struct BikePropety
		{
			float BodyLength = 1.8f;
			float FrontWheelRadius = 0.3f;
			float RearWheelRadius = 0.3f;
			float PedalRate = 0.5f;
		};
		struct BikeMovement
		{
			float FrontWheelPitch = 0.f;
			float FrontWheelYaw = 0.f;

			float RearWheelPitch = 0.f;
			float PedalPitch = 0.f;

			float Speed = 0.f;
		};

		BikePropety m_BikePropety;
		BikeMovement m_BikeMovement;

		Vec3 m_DeltaPos;
		Quat m_DeltaQ;
	};
}
