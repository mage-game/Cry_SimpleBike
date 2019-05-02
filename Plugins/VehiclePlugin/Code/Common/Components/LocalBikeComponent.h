#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include "../Movements/LocalBikeMovement.h"
#include "../SimpleVehiclePluginAPI/CommonData.h"

namespace SimpleVehicle
{
	class LocalBikeComponent : public IEntityComponent
	{
	public:
		LocalBikeComponent() {}
		virtual ~LocalBikeComponent() {}

		// Reflect type to set a unique identifier for this component
		static void ReflectType(Schematyc::CTypeDesc<LocalBikeComponent>& desc)
		{
			desc.SetGUID("{63F4C0C6-32AF-4ACB-8FB0-57D45DD14725}"_cry_guid);
			desc.SetEditorCategory("Vehicles");
			desc.SetLabel("SimpleBike");
			desc.SetDescription("Bike component.");
			desc.SetIcon("icons:ObjectTypes/object.ico");
		}

		virtual uint64 GetEventMask() const override;

	public:
		void StartDrive();
		void StopDrive();

		void Turn(float angles);
		void Move(float speed);
	public:
		const BikeTransfrom& GetBikeTransfrom() const;

		const BikeAnimation& GetBikeAnimation() const;
	protected:
		// IEntityComponent
		virtual void Initialize() override;
		virtual void ProcessEvent(const SEntityEvent& event) override;
		virtual void OnShutDown() override;
		// ~IEntityComponent
	protected:
		std::shared_ptr<LocalBikeMovement> m_BikeMovementPtr;
	};
}
     