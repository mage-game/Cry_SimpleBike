#include "StdAfx.h"
#include <CryFlowGraph/IFlowBaseNode.h>
#include "Common/Components/LocalBikeComponent.h"

namespace SimpleVehicle
{
	class BikeNode :public CFlowBaseNode<eNCT_Instanced>
	{
		enum INPUTS
		{
			EIP_Start = 0,
			EIP_Stop,
			EIP_Turn,
			EIP_Speed,
		};
		enum OUTPUTS
		{
			EOP_Start = 0,
			EOP_Stop,
		};

	public:
		BikeNode(SActivationInfo* pActInfo)
		{			   
		}
		~BikeNode()
		{
		}

		IFlowNodePtr Clone(SActivationInfo* pActInfo)
		{
			return new BikeNode(pActInfo);
		}
		virtual void GetMemoryUsage(ICrySizer* s) const
		{
			s->Add(*this);
		}

		virtual void GetConfiguration(SFlowNodeConfig& config)
		{
			static const SInputPortConfig in_config[] = {
				InputPortConfig<bool>("Start", false),
				InputPortConfig<bool>("Stop", false),
				InputPortConfig<float>("Turn", 0.f),
				InputPortConfig<float>("Speed", 0.f),
				{ 0 }
			};
			static const SOutputPortConfig out_config[] = {
				OutputPortConfig_Void("Started"),
				OutputPortConfig_Void("Stoped"),
				{ 0 }
			};
			config.sDescription = _HELP("This node provides information about the VIRZoom Bike");
			config.pInputPorts = in_config;
			config.pOutputPorts = out_config;
			config.nFlags |= EFLN_TARGET_ENTITY;
			config.SetCategory(EFLN_APPROVED);
		}

		virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
		{
			if (pActInfo->pEntity == nullptr)
			{
				return;
			}
			if (event == eFE_Initialize)
			{
				m_BikeComponent = pActInfo->pEntity->GetOrCreateComponent<LocalBikeComponent>();
			}
			else if (event == eFE_Activate)
			{
				if (IsPortActive(pActInfo, EIP_Start))
				{
					m_BikeComponent->StartDrive();

					pActInfo->pGraph->SetRegularlyUpdated(pActInfo->myID, true);

					ActivateOutput(pActInfo, EOP_Start, SFlowSystemVoid());
				}
				if (IsPortActive(pActInfo, EIP_Stop))
				{
					pActInfo->pGraph->SetRegularlyUpdated(pActInfo->myID, false);
					m_BikeComponent->StopDrive();

					ActivateOutput(pActInfo, EOP_Stop, SFlowSystemVoid());
				}
				if (IsPortActive(pActInfo, EIP_Speed))
				{
					float speed = GetPortFloat(pActInfo, EIP_Speed);
					m_BikeComponent->Move(speed);
				}
				if (IsPortActive(pActInfo, EIP_Turn))
				{
					float angles = GetPortFloat(pActInfo, EIP_Turn);
					m_BikeComponent->Turn(angles);
				}
			}
		}
	private:
		LocalBikeComponent * m_BikeComponent;
	};
												  
	REGISTER_FLOW_NODE("VIRZoomBike:Bike", BikeNode);
}