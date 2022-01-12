#ifndef GAME_SERVER_LANGUAGE_H
#define GAME_SERVER_LANGUAGE_H

#include "gamecontext.h"

// Language list
enum
{
    LANG_EN = 1,
    LANG_CN,
};

class CLanguage
{
    CGameContext *m_pGameServer;

	CGameContext *GameServer() const { return m_pGameServer; }
    public:
        int SetLanguage(int ClientID, int Language);
        int GetLanguage(int ClientID);
};
#endif