#include "StdAfx.h"
#include "LocalBikeComponent.h"
#include "SimpleVehiclePluginEnv.h"

namespace SimpleVehicle
{
	void LocalBikeComponent::Initialize()
	{
		m_BikeMovementPtr = std::make_shared<LocalBikeMovement>();
	}

	uint64 LocalBikeComponent::GetEventMask() const
	{
		return ENTITY_EVENT_BIT(ENTITY_EVENT_START_GAME)
			| ENTITY_EVENT_BIT(ENTITY_EVENT_UPDATE) 
			| ENTITY_EVENT_BIT(ENTITY_EVENT_DEACTIVATED)
			| ENTITY_EVENT_BIT(ENTITY_EVENT_PREPHYSICSUPDATE);
	}

	void LocalBikeComponent::ProcessEvent(const SEntityEvent& event)
	{
		switch (event.event)
		{
		case ENTITY_EVENT_START_GAME:
		{
			m_BikeMovementPtr->Init(m_pEntity);
		}
		break;
		case ENTITY_EVENT_PREPHYSICSUPDATE:
		{
			m_BikeMovementPtr->Physicalize();
		}
		break;
		case ENTITY_EVENT_UPDATE:
		{
			SEntityUpdateContext* pCtx = (SEntityUpdateContext*)event.nParam[0];
			float frameTime = pCtx->fFrameTime;

			m_BikeMovementPtr->Update(frameTime);
		}
		break;
		case ENTITY_EVENT_DEACTIVATED:
		{
			StopDrive();
		}
		break;
		default: break;
		}
	}

	void LocalBikeComponent::OnShutDown()
	{
		//StopDrive();
	}

	void LocalBikeComponent::StartDrive()
	{
		m_BikeMovementPtr->Start();
	}

	void LocalBikeComponent::StopDrive()
	{
		m_BikeMovementPtr->Stop();
	}

	void LocalBikeComponent::Turn(float angles)
	{
		m_BikeMovementPtr->Turn(angles);
	}

	void LocalBikeComponent::Move(float speed)
	{
		m_BikeMovementPtr->Move(speed);
	}

	const BikeTransfrom& LocalBikeComponent::GetBikeTransfrom() const
	{
		return m_BikeMovementPtr->GetBikeTransfrom();
	}

	const BikeAnimation& LocalBikeComponent::GetBikeAnimation() const
	{
		return m_BikeMovementPtr->GetBikeAnimation();
	}

	AUTO_REGISTER_COMPONENT(LocalBikeComponent)
}

