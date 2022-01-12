#include "languages.h"

int CLanguage::SetLanguage(int ClientID, int Language)
{;
    GameServer()->m_apPlayers[ClientID]->m_AccData.m_Language = (int)Language;
    GameServer()->m_apPlayers[ClientID]->Language = (int)Language;
}

int CLanguage::GetLanguage(int ClientID)
{
    return GameServer()->m_apPlayers[ClientID]->Language;
}