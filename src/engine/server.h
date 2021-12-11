/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you miss that file, contact Pikotee, because he changed some stuff here ...			 */
/*	... and would like to be mentioned in credits in case of using his code					 */

#ifndef ENGINE_SERVER_H
#define ENGINE_SERVER_H
#include "kernel.h"
#include "message.h"
#include <game/generated/protocol.h>
#include <engine/shared/protocol.h>
#include <string>
#include <vector>

enum
{
	CHATCATEGORY_SYSTEM=0,
	CHATCATEGORY_FNG,
	CHATCATEGORY_JAIL,
	CHATCATEGORY_ACCOUNT,
	CHATCATEGORY_MAINCITY,
	CHATCATEGORY_INSTA,
};

class IServer : public IInterface
{
	MACRO_INTERFACE("server", 0)
protected:
	int m_CurrentGameTick;
	int m_TickSpeed;

public:
	class CLocalization* m_pLocalization;

public:
	enum
	{
		AUTHED_NO=0,
		AUTHED_MOD,
		AUTHED_ADMIN,
	};

public:
	/*
		Structure: CClientInfo
	*/
	struct CClientInfo
	{
		const char *m_pName;
		int m_Latency;
	};

	virtual ~IServer() { };

	int Tick() const { return m_CurrentGameTick; }
	int TickSpeed() const { return m_TickSpeed; }

	virtual const char *ClientName(int ClientID) = 0;
	virtual const char *ClientClan(int ClientID) = 0;
	virtual int ClientCountry(int ClientID) = 0;
	virtual bool ClientIngame(int ClientID) = 0;
	virtual int GetClientInfo(int ClientID, CClientInfo *pInfo) = 0;
	virtual void GetClientAddr(int ClientID, char *pAddrStr, int Size) = 0;

	virtual int SendMsg(CMsgPacker *pMsg, int Flags, int ClientID) = 0;

	template<class T>
	int SendPackMsg(T *pMsg, int Flags, int ClientID)
	{
		CMsgPacker Packer(pMsg->MsgID());
		if(pMsg->Pack(&Packer))
			return -1;
		return SendMsg(&Packer, Flags, ClientID);
	}
	virtual void SetClientName(int ClientID, char const *pName) = 0;
	virtual void SetClientClan(int ClientID, char const *pClan) = 0;
	virtual void SetClientCountry(int ClientID, int Country) = 0;
	virtual void SetClientScore(int ClientID, int Score) = 0;
	virtual void Logout(int ClientID) = 0;
	virtual void Police(int ClientID,int Switch) = 0;
	virtual void SetRconlvl(int ClientID,int Level) = 0;
	virtual void SetClientAccID(int ClientID, int AccID) = 0;

	virtual int SnapNewID() = 0;
	virtual void SnapFreeID(int ID) = 0;
	virtual void *SnapNewItem(int Type, int ID, int Size) = 0;

	virtual void SnapSetStaticsize(int ItemType, int Size) = 0;

	//KlickFoots stuff
	virtual bool IsAdmin(int ClientID) = 0;
	virtual bool IsMod(int ClientID) = 0;
	//Normales zeugs
	virtual bool IsAuthed(int ClientID) = 0;
	virtual int AuthLvl(int ClientID) = 0;
	virtual void Kick(int ClientID, const char *pReason) = 0;

	virtual void DemoRecorder_HandleAutoStart() = 0;

	// Dummy
	virtual void DummyJoin(int DummyID, const char *pDummyName, const char *pDummyClan, int Country) = 0;
	virtual void DummyLeave(int DummyID, const char *pDummyName = 0) = 0;

	virtual std::string GetClientIP(int ClientID) = 0;
	virtual void SetClientLanguage(int ClientID, const char* pLanguage) = 0;

	inline class CLocalization* Localization() { return m_pLocalization; }
};

class IGameServer : public IInterface
{
	MACRO_INTERFACE("gameserver", 0)
protected:
public:
	virtual void OnInit() = 0;
	virtual void OnConsoleInit() = 0;
	virtual void OnShutdown() = 0;

	virtual void OnTick() = 0;
	virtual void OnPreSnap() = 0;
	virtual void OnSnap(int ClientID) = 0;
	virtual void OnPostSnap() = 0;

	virtual void OnMessage(int MsgID, CUnpacker *pUnpacker, int ClientID) = 0;

	virtual void OnClientConnected(int ClientID) = 0;
	virtual void OnClientEnter(int ClientID) = 0;
	virtual void OnClientDrop(int ClientID/*, int Type*/, const char *pReason) = 0;
	virtual void OnClientDirectInput(int ClientID, void *pInput) = 0;
	virtual void OnClientPredictedInput(int ClientID, void *pInput) = 0;

	virtual bool IsClientReady(int ClientID) = 0;
	virtual bool IsClientPlayer(int ClientID) = 0;

	virtual const char *GameType() = 0;
	virtual const char *Version() = 0;
	virtual const char *NetVersion() = 0;
	
	virtual void ClearBroadcast(int To, int Priority) = 0;
	virtual void SendBroadcast_Localization(int To, int Priority, int LifeSpan, const char* pText, ...) = 0;
	virtual void SendBroadcast_Localization_P(int To, int Priority, int LifeSpan, int Number, const char* pText, ...) = 0;
	virtual void SendChatTarget(int To, const char* pText) = 0;
	virtual void SendChatTarget_Localization(int To, int Category, const char* pText, ...) = 0;
	virtual void SendChatTarget_Localization_P(int To, int Category, int Number, const char* pText, ...) = 0;
	virtual void SendMOTD(int To, const char* pText) = 0;
	virtual void SendMOTD_Localization(int To, const char* pText, ...) = 0;
};

extern IGameServer *CreateGameServer();

#endif
