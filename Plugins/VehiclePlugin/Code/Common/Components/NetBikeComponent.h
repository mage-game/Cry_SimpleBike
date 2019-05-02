#pragma once
#include <CryEntitySystem/IEntityComponent.h>
#include "../Movements/NetBikeMovement.h"

namespace SimpleVehicle
{
	class NetBikeComponent : public IEntityComponent
	{
	public:
		NetBikeComponent() {}
		virtual ~NetBikeComponent() {}

		// Reflect type to set a unique identifier for this component
		static void ReflectType(Schematyc::CTypeDesc<NetBikeComponent>& desc)
		{
			desc.SetGUID("{249D4964-F95B-42da-95A1-FF37EAE9036A}"_cry_guid);
			desc.SetEditorCategory("Vehicles");
			desc.SetLabel("SimpleNetBike");
			desc.SetDescription("Bike net component.");
			desc.SetIcon("icons:ObjectTypes/object.ico");
		}

		virtual uint64 GetEventMask() const override;
		
	public:
		void StartDrive();
		void StopDrive();

		void SetBikeTransfrom(const BikeTransfrom& transfrom);

		void SetBikeAnimationTime(const BikeAnimation& bikeAnimation);
	protected:
		// IEntityComponent
		virtual void Initialize() override;
		virtual void ProcessEvent(const SEntityEvent& event) override;
		virtual void OnShutDown() override;
		// ~IEntityComponent
	protected:
		std::shared_ptr<NetBikeMovement> m_NetBikeMovementPtr;
	};
}