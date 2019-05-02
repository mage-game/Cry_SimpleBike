//Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#include "StdAfx.h"
#include "LocalBikeMovement.h"

namespace SimpleVehicle
{
	void LocalBikeMovement::Turn(float angles)
	{
		angles = clamp_tpl(angles, MIN_TURN_ANGLES, MAX_TURN_ANGLES);
		m_BikeMovement.FrontWheelYaw = DEG2RAD(angles);
	}

	void LocalBikeMovement::Move(float speed)
	{
		speed = clamp_tpl(speed, MIN_MOVE_SPEED, MAX_MOVE_SPEED);
		m_BikeMovement.Speed = speed / 3.6f;
	}

	void LocalBikeMovement::Init(IEntity* pEntity)
	{
		BikeMovementBase::Init(pEntity);

		m_DeltaPos = ZERO;
		m_DeltaQ = Quat::CreateIdentity();

		ICharacterInstance* pCharInstance = pEntity->GetCharacter(0);
		IDefaultSkeleton& rIDefaultSkeleton = pCharInstance->GetIDefaultSkeleton();
		int bikeBodySlot = rIDefaultSkeleton.GetJointIDByName("Hull");
		int frontWheelSolt = rIDefaultSkeleton.GetJointIDByName("Wheel1");
		int rearWheelSolt = rIDefaultSkeleton.GetJointIDByName("Wheel2");

		ISkeletonPose* pSkeletonPose = pCharInstance->GetISkeletonPose();
		Matrix34 bikeBodyLocalTM = Matrix34(pSkeletonPose->GetAbsJointByID(bikeBodySlot));
		Vec3 bikeBodyLocalPos = bikeBodyLocalTM.GetTranslation();
		Matrix34 frontWheelLocalTM = Matrix34(pSkeletonPose->GetAbsJointByID(frontWheelSolt));
		Vec3 frontWheelLocalPos = frontWheelLocalTM.GetTranslation();
		Matrix34 rearWheelLocalTM = Matrix34(pSkeletonPose->GetAbsJointByID(rearWheelSolt));
		Vec3 rearWheelLocalPos = rearWheelLocalTM.GetTranslation();

		m_BikePropety.FrontWheelRadius = frontWheelLocalPos.z - bikeBodyLocalPos.z;
		m_BikePropety.RearWheelRadius = rearWheelLocalPos.z - bikeBodyLocalPos.z;
		m_BikePropety.BodyLength = (frontWheelLocalPos - rearWheelLocalPos).len();
		m_BikePropety.PedalRate = 0.5f;
	}

	void LocalBikeMovement::Update(float frameTime)
	{
		if (m_Started)
		{
			BikeAnimation bikeAnimation;

			float steeringTurnAnimTime = (90.0f + RAD2DEG(-m_BikeMovement.FrontWheelYaw)) / 180.0f;
			SetAnimTime(Steer, steeringTurnAnimTime);
			bikeAnimation.steer = steeringTurnAnimTime;
			if (fabs_tpl(m_BikeMovement.Speed) > 0.1f)
			{
				float rearWheelSpeedTemp = m_BikeMovement.Speed*frameTime;

				float rearWheelPitchTemp = rearWheelSpeedTemp / m_BikePropety.RearWheelRadius;
				AdjustAngles(m_BikeMovement.RearWheelPitch, rearWheelPitchTemp);
				float rearWheelPitchAnimTime = m_BikeMovement.RearWheelPitch / (2 * gf_PI);
				SetAnimTime(RearWheel, rearWheelPitchAnimTime);
				bikeAnimation.rearWheel = rearWheelPitchAnimTime;

				float pedalPitchTemp = rearWheelPitchTemp * m_BikePropety.PedalRate;
				AdjustAngles(m_BikeMovement.PedalPitch, pedalPitchTemp);
				float pedalPitchAnimTime = m_BikeMovement.PedalPitch / (2 * gf_PI);
				SetAnimTime(Pedal, pedalPitchAnimTime);
				bikeAnimation.pedal = pedalPitchAnimTime;

				float frontWheelPitchTemp = rearWheelPitchTemp / fabs_tpl(cos_tpl(m_BikeMovement.FrontWheelYaw));
				AdjustAngles(m_BikeMovement.FrontWheelPitch, frontWheelPitchTemp);
				float frontWheelPitchAnimTime = m_BikeMovement.FrontWheelPitch / (2 * gf_PI);
				SetAnimTime(FrontWheel, frontWheelPitchAnimTime);
				bikeAnimation.frontWheel = frontWheelPitchAnimTime;

				if (fabs_tpl(m_BikeMovement.FrontWheelYaw) > DEG2RAD(1.0f))
				{
					float frontWheelYawSgn = fsgnnz(m_BikeMovement.FrontWheelYaw);
					float frontWheelYawValue = fabs_tpl(m_BikeMovement.FrontWheelYaw);
					float rearWheelMovingRadius = frontWheelYawSgn * m_BikePropety.BodyLength / tan_tpl(frontWheelYawValue);
					float yawAngularVelocity = frontWheelYawSgn * (rearWheelSpeedTemp / m_BikePropety.BodyLength)*tan_tpl(frontWheelYawValue);
					Vec3 p0(0.f, 0.f, 0.f);
					Vec3 p1 = rearWheelMovingRadius * Vec3(-1, 0.f, 0.f);
					Vec3 p2 = rearWheelMovingRadius * Vec3(-cos_tpl(yawAngularVelocity), sin_tpl(yawAngularVelocity), 0.f);
					Matrix34 tm = m_BikeEntity->GetLocalTM();
					p0 = tm * p0;
					p1 = tm * p1;
					p2 = tm * p2;
					Vec3 v01 = p1 - p0;
					Vec3 v02 = p2 - p0;
					Vec3 v12 = v02 - v01;

					m_DeltaPos = v12;
					m_DeltaQ = Quat::CreateRotationZ(yawAngularVelocity);

					float bikeBodyRoll = -atan_tpl(pow_tpl(m_BikeMovement.Speed, 2) / (9.81f*rearWheelMovingRadius));
					bikeBodyRoll = clamp_tpl(RAD2DEG(bikeBodyRoll), MIN_BIKE_ROLL, MAX_BIKE_ROLL);
					float bikeBodyRollAnimTime = (15.0f + bikeBodyRoll) / 30.0f;

					SetAnimTime(BodyRoll, bikeBodyRollAnimTime);
					bikeAnimation.bodyRoll = bikeBodyRollAnimTime;
				}
				else
				{
					Vec3 dir = m_BikeEntity->GetForwardDir();
					m_DeltaPos = rearWheelSpeedTemp * dir;
				}
			}

			Vec3 bikeWorldPos = m_BikeEntity->GetWorldPos();
			Vec3 bikeRotate = Ang3::GetAnglesXYZ(m_BikeEntity->GetLocalTM());
			BikeTransfrom bikeTransfransform;
			bikeTransfransform.posX = bikeWorldPos.x;
			bikeTransfransform.posY = bikeWorldPos.y;
			bikeTransfransform.posZ = bikeWorldPos.z;
			bikeTransfransform.rotX = bikeRotate.x;
			bikeTransfransform.rotY = bikeRotate.y;
			bikeTransfransform.rotZ = bikeRotate.z;

			SetBikeTransfrom(bikeTransfransform);
			SetBikeAnimationTime(bikeAnimation);
		}
	}

	void LocalBikeMovement::Physicalize()
	{
		if (m_BikeEntity)
		{
			IPhysicalEntity* phy = m_BikeEntity->GetPhysicalEntity();

			pe_status_pos status_pos;
			if (phy->GetStatus(&status_pos))
			{
				pe_params_pos params_pos;
				params_pos.bRecalcBounds = 16 | 32 | 64;
				params_pos.pos = status_pos.pos + m_DeltaPos;
				params_pos.q = m_DeltaQ * status_pos.q;
				phy->SetParams(&params_pos, 1);
			}

			pe_action_awake action_awake;
			action_awake.bAwake = true;
			phy->Action(&action_awake, 1);

			m_DeltaPos = ZERO;
			m_DeltaQ = Quat::CreateIdentity();
		}
	}

	void LocalBikeMovement::AdjustAngles(float& angles, float temp)
	{
		angles += temp;
		if (angles > 2.0f*gf_PI)
		{
			angles -= 2.0f * gf_PI;
		}
		if (angles < 0.f)
		{
			angles += 2.0f * gf_PI;
		}
	}
}

