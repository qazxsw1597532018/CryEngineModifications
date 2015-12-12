/*************************************************************************

Copyright (C) 2015 Alperen Gezer

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
-------------------------------------------------------------------------
Description: Procedural Collectible Generation

-------------------------------------------------------------------------
History:
- 12.12.2015 - Created

*************************************************************************/

#include "StdAfx.h"
#include "Game.h"
#include "Nodes/G2FlowBaseNode.h"
#include "Player.h"
#include "CraftSystem.h"

//--------------------------------------------------------------------

class CFlowNode_CraftSystemInventory : public CFlowBaseNode<eNCT_Instanced>
{
	enum EInputPorts
	{
		eINP_Enable = 0,
	};

	enum EOutputPorts
	{
		eOUT_Bushes = 0,
		eOUT_Flintstones
	};

public:
	CFlowNode_CraftSystemInventory( SActivationInfo * pActInfo )
		: m_BushCount(0),
		m_FlintstoneCount(0)
	{

	}
	CFlowNode_CraftSystemInventory::~CFlowNode_CraftSystemInventory() {}

	void Serialize( SActivationInfo * pActInfo, TSerialize ser )
	{
		ser.Value("TotalBushes", m_BushCount);
		ser.Value("TotalFlintstones", m_FlintstoneCount);
	}

	virtual void GetConfiguration( SFlowNodeConfig &config )
	{
		static const SInputPortConfig inp_config[] = {
			InputPortConfig_Void ("Enable", _HELP("Enables the craft system inventory")),
			{0}
		};
		static const SOutputPortConfig out_config[] = {
			OutputPortConfig<int>("TotalBushes"),
			OutputPortConfig<int>("TotalFlintstones"),
			{0}
		};

		config.sDescription = _HELP( "Returns the inventory" );
		config.pInputPorts = inp_config;
		config.pOutputPorts = out_config;
		config.SetCategory(EFLN_APPROVED);
	}


	virtual IFlowNodePtr Clone(SActivationInfo* pActInfo) { return new CFlowNode_CraftSystemInventory(pActInfo); }


	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		switch (event)
		{
		case eFE_Initialize:
			{
				m_actInfo = *pActInfo;
				m_BushCount = 0;
				m_FlintstoneCount = 0;
				break;
			}
		case eFE_Activate:
			{
				if (IsPortActive( pActInfo, eINP_Enable ))
				{
					CPlayer* pPlayer = static_cast<CPlayer*>(gEnv->pGame->GetIGameFramework()->GetClientActor());

					if(!pPlayer)
						return;

					CraftSystem* crafting = pPlayer->GetCraftSystem();

					if(!crafting)
						return;

					m_BushCount = crafting->GetCraftableCount(ECraftableItems::Bush);
					m_FlintstoneCount = crafting->GetCraftableCount(ECraftableItems::Flintstone);

					ActivateOutput( &m_actInfo, eOUT_Bushes, m_BushCount );
					ActivateOutput( &m_actInfo, eOUT_Flintstones, m_FlintstoneCount );
				}

				break;
			}
		}
	}

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->Add(*this);
	}


	SActivationInfo m_actInfo;
	int m_BushCount;
	int m_FlintstoneCount;
};

REGISTER_FLOW_NODE( "Crafting:Inventory", CFlowNode_CraftSystemInventory );
//--------------------------------------------------------------------