/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "dm.h"
#include <game/server/gamecontext.h>


CGameControllerDM::CGameControllerDM(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "u|City";
}

void CGameControllerDM::Tick()
{
	IGameController::Tick();


	/*if(Tipy == 0)
	{
		m_pGameType = "y  uTown-Cit";
	}
	else if(Tipy == 1)
	{
		m_pGameType = "ty  uTown-Ci";
	}
	else if(Tipy == 2)
	{
		m_pGameType = "ity  uTown-C";
	}
	else if(Tipy == 3)
	{
		m_pGameType = "City  uTown-";
	}
	else if(Tipy == 4)
	{
		m_pGameType = "-City  uTown";
	}
	else if(Tipy == 5)
	{
		m_pGameType = "n-City  uTow";
	}
	else if(Tipy == 6)
	{
		m_pGameType = "wn-City  uTo";
	}
	else if(Tipy == 7)
	{
		m_pGameType = "own-City  uT";
	}
	else if(Tipy == 8)
	{
		m_pGameType = "Town-City  u";
	}
	else if(Tipy == 9)
	{
		m_pGameType = "uTown-City";
		Tipy++;
	}*/
}
