#include "StdAfx.h"
#include "NetBikeComponent.h"

namespace SimpleVehicle
{
	uint64 NetBikeComponent::GetEventMask() const
	{
		return ENTITY_EVENT_BIT(ENTITY_EVENT_UPDATE) | ENTITY_EVENT_BIT(ENTITY_EVENT_DEACTIVATED);
	}

	void NetBikeComponent::Initialize()
	{
		m_NetBikeMovementPtr = std::make_shared<NetBikeMovement>();
	}

	void NetBikeComponent::ProcessEvent(const SEntityEvent& event)
	{
		switch (event.event)
		{
		case ENTITY_EVENT_UPDATE:
		{
			SEntityUpdateContext* pCtx = (SEntityUpdateContext*)event.nParam[0];
			float frameTime = pCtx->fFrameTime;

			m_NetBikeMovementPtr->Update(frameTime);
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

	void NetBikeComponent::OnShutDown()
	{
		StopDrive();
	}

	void NetBikeComponent::StartDrive()
	{
		m_NetBikeMovementPtr->Init(m_pEntity);
		m_NetBikeMovementPtr->Start();
	}

	void NetBikeComponent::StopDrive()
	{
		m_NetBikeMovementPtr->Stop();
	}

	void NetBikeComponent::SetBikeTransfrom(const BikeTransfrom& transfrom)
	{
		m_NetBikeMovementPtr->SetBikeTransfrom(transfrom);
	}

	void NetBikeComponent::SetBikeAnimationTime(const BikeAnimation& bikeAnimation)
	{
		m_NetBikeMovementPtr->SetBikeAnimationTime(bikeAnimation);
	}

	AUTO_REGISTER_COMPONENT(NetBikeComponent)
}

