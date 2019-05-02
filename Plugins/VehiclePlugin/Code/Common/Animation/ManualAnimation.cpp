#include "StdAfx.h"
#include "ManualAnimation.h"

namespace SimpleVehicle
{		
	void ManualAnimation::Init(IEntity* pEntity)
	{
		ICharacterInstance* pCharacterInstance = pEntity->GetCharacter(0);
		if (pCharacterInstance)
		{
			m_SkeletonAnim = pCharacterInstance->GetISkeletonAnim();
		}
	}

	bool ManualAnimation::StartAnimation(int layerId, const string& name)
	{		 		
		if (m_SkeletonAnim)
		{
			CryCharAnimationParams animParams;
			animParams.m_nFlags = CA_FORCE_SKELETON_UPDATE | CA_MANUAL_UPDATE;
			animParams.m_nLayerID = layerId;
			animParams.m_fTransTime = 0.2f;

			if (m_SkeletonAnim->StartAnimation(name, animParams))
			{
				m_SkeletonAnim->SetLayerBlendWeight(layerId, 1.0f);
				return true;
			}
		}
		return false;
	}

	bool ManualAnimation::StopAnimation(int layerId)
	{
		if (m_SkeletonAnim)
		{
			if (m_SkeletonAnim->StopAnimationInLayer(layerId, 0.5f))
			{
				return true;
			}
		}
		return false;
	}

	void ManualAnimation::SetAnimTime(int layerId, float time)
	{
		if (m_SkeletonAnim)
		{
			int numAnimsLayer0 = m_SkeletonAnim->GetNumAnimsInFIFO(layerId);
			if (numAnimsLayer0 > 0)
			{
				CAnimation& animation = m_SkeletonAnim->GetAnimFromFIFO(layerId, numAnimsLayer0 - 1);
				m_SkeletonAnim->SetAnimationNormalizedTime(&animation, time);
				//m_SkeletonAnim->SetLayerNormalizedTime(m_LayerId,time);			
			}
		}
	}
}
