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
Description: Controls Flash UI,calls ActionScript

-------------------------------------------------------------------------
History:
- 14.12.2015 - Created

*************************************************************************/

#include "StdAfx.h"
#include "ArkenUIController.h"

ArkenUIController* gArkenUIInstance = NULL;

ArkenUIController::ArkenUIController()
	: m_pArkenUI(NULL),
	m_pSkillbar(NULL),
	obj2(true)
{
	gArkenUIInstance = this;

	if ( gEnv->pFlashUI )
	{
		m_pArkenUI = gEnv->pFlashUI->GetUIElement( "ArkenUI" );
		m_pSkillbar = gEnv->pFlashUI->GetUIElement( "ArkenSkillbar" );
		if ( m_pArkenUI )
		{
			m_pArkenUI->AddEventListener( this, "ArkenUI" );
			m_pSkillbar->AddEventListener( this, "ArkenSkillbar" );

		}
	}
}

ArkenUIController::~ArkenUIController()
{

	if(m_pArkenUI)m_pArkenUI->RemoveEventListener(this);
	if(m_pSkillbar)m_pSkillbar->RemoveEventListener(this);
}

ArkenUIController* ArkenUIController::Get()
{
	return gArkenUIInstance;
}

void ArkenUIController::SetBushText(const string& text)
{
	SUIArguments args;
	args.AddArgument( text );

	TUIData res;

	m_pArkenUI->CallFunction( "SetBushText",args,&res );
	m_pArkenUI->CallFunction( "BushHighlight",args,&res );
}

void ArkenUIController::SetFlintText(const string& text)
{
	SUIArguments args;
	args.AddArgument( text );

	TUIData res;

	m_pArkenUI->CallFunction( "SetFlintText",args,&res );
	m_pArkenUI->CallFunction( "FlintHighlight",args,&res );
}

void ArkenUIController::SetHealthOrb(int percent)
{
	SUIArguments args;
	args.AddArgument( percent );

	TUIData res;

	m_pSkillbar->CallFunction( "SetHunger",args,&res );
}

void ArkenUIController::SetManaOrb(int percent)
{
	SUIArguments args;
	args.AddArgument( percent );

	TUIData res;

	m_pSkillbar->CallFunction( "SetSanity",args,&res );
}

void ArkenUIController::EnableSkillOne(bool status)
{
	SUIArguments args;
	args.AddArgument( status );

	TUIData res;

	m_pSkillbar->CallFunction( "SetSkillOne",args,&res );
}

void ArkenUIController::EnableHungerWarning(bool status)
{
	SUIArguments args;
	args.AddArgument( status );

	TUIData res;

	m_pArkenUI->CallFunction( "EnableHungerWarning",args,&res );
}

void ArkenUIController::ShowNotEnough(bool status)
{
	SUIArguments args;
	args.AddArgument( status );

	TUIData res;

	m_pArkenUI->CallFunction( "ShowNotEnough",args,&res );
}

void ArkenUIController::SetObjectiveOne(int p11,int p21,bool p3,bool p4)
{

	SUIArguments args;
	args.AddArgument( p11 );
	args.AddArgument( 3 );
	args.AddArgument( p21 );
	args.AddArgument( 1 );
	args.AddArgument( p3 );
	args.AddArgument( p4 );


	TUIData res;

	m_pArkenUI->CallFunction( "SetObjectiveOne",args,&res );



}

void ArkenUIController::SetObjectiveTwo(bool p1,bool p4)
{

	SUIArguments args;
	args.AddArgument( p1 );
	args.AddArgument( p4 );



	TUIData res;
	
	m_pArkenUI->CallFunction( "SetObjectiveTwo",args,&res );

	SetObjectiveOne(0,0,false,false);


}
void ArkenUIController::OnUIEvent( IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args )
{

}
