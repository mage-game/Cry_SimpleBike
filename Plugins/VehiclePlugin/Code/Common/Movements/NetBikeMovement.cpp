#include "stdafx.h"
#include "NetBikeMovement.h"

namespace SimpleVehicle
{
	void NetBikeMovement::Init(IEntity* pEntity)
	{
		BikeMovementBase::Init(pEntity);
	}

	void NetBikeMovement::Update(float frameTime)
	{
		if (m_Started) 
		{
			if (m_BikeEntity)
			{
				UpdateTransfrom(m_BikeTransfrom);
				UpdateAnimation(m_BikeAnimation);
			}
		}
	}

	void NetBikeMovement::UpdateTransfrom(const BikeTransfrom& bikeTransform)
	{
		Vec3 pos = Vec3(bikeTransform.posX, bikeTransform.posY, bikeTransform.posZ);
		Vec3 rot = Vec3(bikeTransform.rotX, bikeTransform.rotY, bikeTransform.rotZ);

		Matrix34 tm = m_BikeEntity->GetWorldTM();
		tm.SetTranslation(pos);
		m_BikeEntity->SetWorldTM(tm);

		Matrix33 mat;
		mat.SetRotationXYZ(rot);
		Quat qRotation = Quat(mat);
		m_BikeEntity->SetRotation(qRotation);
	}

	void NetBikeMovement::UpdateAnimation(const BikeAnimation& bikeAnimation)
	{
		SetAnimTime(Steer, bikeAnimation.steer);
		SetAnimTime(RearWheel, bikeAnimation.rearWheel);
		SetAnimTime(Pedal, bikeAnimation.pedal);
		SetAnimTime(FrontWheel, bikeAnimation.frontWheel);
		SetAnimTime(BodyRoll, bikeAnimation.bodyRoll);
	}
}
