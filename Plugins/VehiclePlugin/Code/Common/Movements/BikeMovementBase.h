#pragma once
#include "../SimpleVehiclePluginAPI/CommonData.h"
#include "../Animation/ManualAnimation.h"

namespace SimpleVehicle
{
	enum BikeAnimationType
	{
		FrontWheel = 0,
		RearWheel,
		Steer,
		Pedal,
		BodyRoll,
	};
	
	class BikeMovementBase
	{
	public:
		BikeMovementBase()
		{
			m_ManualAnimation= std::make_shared<ManualAnimation>();
		}
		virtual ~BikeMovementBase()
		{
			Stop();
		}

		virtual void Init(IEntity* pEntity)
		{
			m_BikeEntity = pEntity;

			m_ManualAnimation->Init(pEntity);
		}

		void Start()
		{
			if (!m_Started)
			{
				m_ManualAnimation->StartAnimation(FrontWheel, "bar_wheel1");
				m_ManualAnimation->StartAnimation(RearWheel, "bar_wheel2");
				m_ManualAnimation->StartAnimation(Steer, "bar_steer");
				m_ManualAnimation->StartAnimation(Pedal, "Default");
				m_ManualAnimation->StartAnimation(BodyRoll, "bar_hull");

				Reset();   

				m_Started = true;
			}
		}				  		

		void Stop()
		{
			if (m_Started)
			{
				m_Started = false;

				Reset();

				m_ManualAnimation->StopAnimation(FrontWheel);
				m_ManualAnimation->StopAnimation(FrontWheel);
				m_ManualAnimation->StopAnimation(FrontWheel);
				m_ManualAnimation->StopAnimation(FrontWheel);
				m_ManualAnimation->StopAnimation(FrontWheel);
			}
		}

		void SetAnimTime(int layerId, float time)
		{
			m_ManualAnimation->SetAnimTime(layerId, time);
		}

		virtual void Update(float frameTime) = 0;

		void SetBikeTransfrom(const BikeTransfrom& transfrom)
		{
			m_BikeTransfrom = transfrom;
		}

		const BikeTransfrom& GetBikeTransfrom() const
		{
			return m_BikeTransfrom;
		}

		void SetBikeAnimationTime(const BikeAnimation& bikeAnimation)
		{
			m_BikeAnimation = bikeAnimation;
		}

		const BikeAnimation& GetBikeAnimation() const
		{
			return m_BikeAnimation;
		}
	protected:
		void Reset()
		{
			m_ManualAnimation->SetAnimTime(FrontWheel, 0.0f);
			m_ManualAnimation->SetAnimTime(RearWheel, 0.0f);
			m_ManualAnimation->SetAnimTime(Steer, 0.5f);
			m_ManualAnimation->SetAnimTime(Pedal, 0.0f);
			m_ManualAnimation->SetAnimTime(BodyRoll, 0.5f);
		}
	protected:
		BikeTransfrom m_BikeTransfrom;
		BikeAnimation m_BikeAnimation;

		std::shared_ptr<ManualAnimation> m_ManualAnimation;
		IEntity* m_BikeEntity = nullptr;
		bool m_Started = false;
	};
}