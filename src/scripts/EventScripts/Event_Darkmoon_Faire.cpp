/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2016 AscEmu Team <http://www.ascemu.org>
 * Copyright (C) 2007-2008 Sun++ Team <http://www.sunplusplus.info/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Setup.h"
#include "Event_Darkmoon_Faire.h"

//////////////////////////////////////////////////////////////////////////////////////////
///\details <b>Darkmoon Faire (Elwynn Forest)</b>\n
// event_names entry: 4 \n
// event_names holiday: 374 \n
///\todo Check all Darkmoon Faire events


//////////////////////////////////////////////////////////////////////////////////////////
///\details <b>Darkmoon Faire (Mulgore)</b>\n
// event_names entry: 5 \n
// event_names holiday: 375 \n


//////////////////////////////////////////////////////////////////////////////////////////
///\details <b>Darkmoon Faire (Terokkar Forest)</b>\n
// event_names entry: 3 \n
// event_names holiday: 376 \n


//////////////////////////////////////////////////////////////////////////////////////////
///\details <b>Darkmoon Faire Gameobjects</b>\n

/// Blastenheimer 5000 Ultra Cannon
class Blastenheimer5000 : public GameObjectAIScript
{
    public:
    explicit Blastenheimer5000(GameObject* pGameObject) : GameObjectAIScript(pGameObject)
        {
            mPlayerGuid = 0;
        }

        static GameObjectAIScript* Create(GameObject* pGameObject)
        {
            return new Blastenheimer5000(pGameObject);
        }

        void OnActivate(Player* pPlayer) override
        {
            if (mPlayerGuid != 0)
                return;

            pPlayer->CastSpell(pPlayer, 24832, true);
            pPlayer->SetMovement(MOVE_ROOT, 1);
            _gameobject->PlaySoundToSet(8476);
            mPlayerGuid = static_cast<uint32>(pPlayer->GetGUID());
            RegisterAIUpdateEvent(2200);
        }

        void AIUpdate() override
        {
            Player* CurrentPlayer = objmgr.GetPlayer(mPlayerGuid);
            if (CurrentPlayer == nullptr)
            {
                RemoveAIUpdateEvent();
                mPlayerGuid = 0;
                return;
            }

            if (CurrentPlayer->GetMapId() == 530)           /// Shattrath
            {
                CurrentPlayer->SafeTeleport(530, 0, -1742.640869f, 5454.712402f, -7.928009f, 4.606363f);
            }
            else if (CurrentPlayer->GetMapId() == 0)        /// Elwynn Forest
            {
                CurrentPlayer->SafeTeleport(0, 0, -9569.150391f, -14.753426f, 68.051422f, 4.874008f);
            }
            else if (CurrentPlayer->GetMapId() == 1)        /// Mulgore
            {
                CurrentPlayer->SafeTeleport(1, 0, -1326.711914f, 86.301125f, 133.093918f, 3.510725f);
            }

            CurrentPlayer->SetMovement(MOVE_UNROOT, 1);
            CurrentPlayer->CastSpell(CurrentPlayer, 42867, true);   // 24742
            _gameobject->SetFlags(0);
            mPlayerGuid = 0;
            RemoveAIUpdateEvent();
        }

    protected:

        uint32 mPlayerGuid;
};

/*
Spells:
=====================
Cannon - 24933
Mortor - 25003
Drop Mine - 39685, 25024
Nitrous Boost - 27746



/// Tonk Control Consoles
class TonkControlConsole : public GameObjectAIScript
{
public:
TonkControlConsole(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
static GameObjectAIScript *Create(GameObject* GO) { return new TonkControlConsole(GO); }

// Click the Console
void OnActivate(Player* pPlayer)
{
// Pre-flight checks
GameObject* tonkConsole = NULL;
tonkConsole = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 180524);

// Open and disable the Tonk Console
tonkConsole->SetFlags(GO_FLAG_NONSELECTABLE);
tonkConsole->SetState(GO_STATE_OPEN);

// Spawn Steam Tonk
pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(19405, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), true, false, 0, 0)->Despawn(310000, 0);;

// Store the tonk just spawned
Creature* pTonk = NULL;
pTonk = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 19405);

// Cast the tonk control spell on the tonk
pPlayer->CastSpell(pTonk, 33849, false);

// Start checks to see if player still has aura
RegisterAIUpdateEvent(1000);

Plr = pPlayer;
Tonk = pTonk;
Console = tonkConsole;
}

void AIUpdate()
{
if (!Plr->HasAura(33849) || Tonk->isDead())
{
// Kill then Despawn Tonk after 10 seconds
Plr->CastSpell(Tonk, 5, false); // Kill spell
Plr->CastSpell(Plr, 2880, false); // Stun Player
Plr->RemoveAura(33849);
Tonk->Despawn(10000,0);

// Close the console so others can access it
Console->SetFlags(0);
Console->SetState(GO_STATE_CLOSED);
RemoveAIUpdateEvent();
}
}

protected:
Player* Plr;
Creature* Tonk;
GameObject* Console;
};
*/

// Setup Carnies
/// \todo Carnie use other text for gossip when Darkmoon Faire "is coming".
// move BARK_SETUP_CARNIES_1 - 4 from npc_script_text to npc_text (with prob) one entry.
class SetupCarnies_Gossip : public GossipScript
{
    public:
        void GossipHello(Object* pObject, Player* plr) override
        {
            GossipMenu* gossipMenu = nullptr;
            uint32 textId = 0;
            uint32 randomNumber = RandomUInt(3);

            switch (randomNumber)
            {
                case 0:
                    textId = BARK_SETUP_CARNIES_1;
                    break;
                case 1:
                    textId = BARK_SETUP_CARNIES_2;
                    break;
                case 2:
                    textId = BARK_SETUP_CARNIES_3;
                    break;
                case 3:
                    textId = BARK_SETUP_CARNIES_4;
                    break;
            }

            objmgr.CreateGossipMenuForPlayer(&gossipMenu, pObject->GetGUID(), textId, plr);
            gossipMenu->SendTo(plr);
        }

        void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code) override
        {
            if (!pObject->IsCreature())
                return;

            switch (IntId)
            {
                case 1:
                    GossipHello(pObject, plr);
                    break;
            }
        }
};


class Flik_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(Flik_Bark);
        Flik_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(180000);             // Start initial update after: 3mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(3))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_FLIK_1);
                    break;

                case 1:
                    _unit->SendScriptTextChatMessage(BARK_FLIK_2);
                    break;

                case 2:
                    _unit->SendScriptTextChatMessage(BARK_FLIK_3);
                    break;

                case 3:
                    _unit->SendScriptTextChatMessage(BARK_FLIK_4);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(120, 240);              // Generate a random value between: 2-4mins
            rndTimer = rndTimer * 1000;                 // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);              // Modify timer to new random value
        }
};


// Flik's Frog
class FliksFrog_Gossip : public GossipScript
{
    public:

        void GossipHello(Object* pObject, Player* plr) override
        {
            GossipMenu* gossipMenu = nullptr;
            uint32 textId = 0;
            uint32 randomNumber = RandomUInt(1);
            ARCEMU_ASSERT(randomNumber <= 1);

            switch (randomNumber)
            {
                case 0:
                    textId = 60011;
                    break;
                case 1:
                    textId = 60012;
                    break;
            }

            objmgr.CreateGossipMenuForPlayer(&gossipMenu, pObject->GetGUID(), textId, plr);
            gossipMenu->SendTo(plr);
        }

        void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code) override
        {
            if (!pObject->IsCreature())
                return;

            switch (IntId)
            {
                case 1:
                    GossipHello(pObject, plr);
                    break;
            }
        }
};


class GelvasGrimegate_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(GelvasGrimegate_Bark);
        GelvasGrimegate_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(60000);             // Start initial update after: 1mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(4))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_GEVAS_GRIMEGATE_1);
                    break;

                case 1:
                    _unit->SendScriptTextChatMessage(BARK_GEVAS_GRIMEGATE_2);
                    break;

                case 2:
                    _unit->SendScriptTextChatMessage(BARK_GEVAS_GRIMEGATE_3);
                    break;

                case 3:
                    _unit->SendScriptTextChatMessage(BARK_GEVAS_GRIMEGATE_4);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(180, 300);             // Generate a random value between: 3-5mins
            rndTimer = rndTimer * 1000;             // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);             // Modify timer to new random value
        }
};


class Lhara_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(Lhara_Bark);
        Lhara_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(90000);             // Start initial update after: 1.5mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(4))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_LHARA_1);
                    break;

                case 1:
                    _unit->SendScriptTextChatMessage(BARK_LHARA_2);
                    break;

                case 2:
                    _unit->SendScriptTextChatMessage(BARK_LHARA_3);
                    break;

                case 3:
                    _unit->SendScriptTextChatMessage(BARK_LHARA_4);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(240, 360);             // Generate a random value between: 4-6mins
            rndTimer = rndTimer * 1000;             // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);             // Modify timer to new random value
        }
};


class MaximaBlastenheimer_Gossip : public GossipScript
{
    public:

        void GossipHello(Object* pObject, Player* plr) override
        {
            GossipMenu* gossipMenu = nullptr;

            objmgr.CreateGossipMenuForPlayer(&gossipMenu, pObject->GetGUID(), BARK_MAXIMA_1, plr);
            gossipMenu->AddItem(0, "Tell me how to use the Blastenheimer 5000 Ultra Cannon.", 1);
            gossipMenu->SendTo(plr);
        }

        void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code) override
        {
            if (!pObject->IsCreature())
                return;

            GossipMenu* Menu;

            switch (IntId)
            {
                case 0:
                    GossipHello(pObject, plr);
                    break;

                case 1:
                    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), BARK_MAXIMA_2, plr);
                    if (Menu != nullptr)
                        Menu->SendTo(plr);
                    break;
            }
        }
};


class Morja_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(Morja_Bark);
        Morja_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(240000);              // Start initial update after: 4mins
        }

        void AIUpdate() override
        {
            _unit->SendScriptTextChatMessage(BARK_MORJA_1);

            uint32 rndTimer;
            rndTimer = RandomUInt(240, 360);              // Generate a random value between: 4-6mins
            rndTimer = rndTimer * 1000;                 // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);              // Modify timer to new random value
        }
};


class ProfessorThaddeusPaleo_Gossip : public GossipScript
{
    public:
    void GossipHello(Object* pObject, Player* plr) override
    {
        GossipMenu* gossipMenu;
        objmgr.CreateGossipMenuForPlayer(&gossipMenu, pObject->GetGUID(), 60016, plr);

        if (pObject->GetUInt32Value(UNIT_NPC_FLAGS) & UNIT_NPC_FLAG_VENDOR)
            gossipMenu->AddItem(1, "Let me browse your goods.", 1);
        
        gossipMenu->AddItem(0, "Tell me more about these Darkmoon Cards.", 2);
        gossipMenu->SendTo(plr);
    }

    void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code) override
    {
        if (!pObject->IsCreature())
            return;

        GossipMenu* Menu = nullptr;
        Creature* pCreature = (pObject->IsCreature()) ? (static_cast<Creature*>(pObject)) : NULL;

        switch (IntId)
        {
            case 1:
                plr->GetSession()->SendInventoryList(pCreature);
                return;
            case 2:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60017, plr);
                Menu->AddItem(0, "Tell me about the Beasts Deck.", 5);
                Menu->AddItem(0, "Tell me about the Portals Deck.", 6);
                Menu->AddItem(0, "Tell me about the Elementals Deck.", 7);
                Menu->AddItem(0, "Tell me about the Warlords Deck.", 8);
                Menu->AddItem(0, "Tell me about the Furies Deck.", 9);
                Menu->AddItem(0, "Tell me about the Lunacy Deck.", 10);
                Menu->AddItem(0, "Tell me about the Blessings Deck.", 11);
                Menu->AddItem(0, "Tell me about the Storms Deck.", 12);
                break;
            case 5:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60018, plr);
                break;
            case 6:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60019, plr);
                break;
            case 7:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60020, plr);
                break;
            case 8:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60021, plr);
                break;
            case 9:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60022, plr);
                break;
            case 10:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60023, plr);
                break;
            case 11:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60024, plr);
                break;
            case 12:
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60025, plr);
                break;
            default:
                return;
        }

        Menu->SendTo(plr);
    }
};


class ProfessorThaddeusPaleo_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(ProfessorThaddeusPaleo_Bark);
        ProfessorThaddeusPaleo_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(210000);             // Start initial update after: 3.5mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(3))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_PROFESSOR_THADDEUS_PALEO_1);
                    break;
                case 1:
                    _unit->SendScriptTextChatMessage(BARK_PROFESSOR_THADDEUS_PALEO_2);
                    break;
                case 2:
                    _unit->SendScriptTextChatMessage(BARK_PROFESSOR_THADDEUS_PALEO_3);
                    break;
                case 3:
                    _unit->SendScriptTextChatMessage(BARK_PROFESSOR_THADDEUS_PALEO_4);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(180, 360);             // Generate a random value between: 3-5mins
            rndTimer = rndTimer * 1000;             // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);             // Modify timer to new random value
        }
};


// Sayge
/// \todo find correct text in npc_text.
class Sayge_Gossip : public GossipScript
{
    public:

        void GossipHello(Object* pObject, Player* plr) override
        {
            GossipMenu* Menu;
            // Check to see if the player already has a buff from Sayge.
            if (plr->HasAura(23768) || plr->HasAura(23769) || plr->HasAura(23767) || plr->HasAura(23738) || plr->HasAura(23766) || plr->HasAura(23737) || plr->HasAura(23735) || plr->HasAura(23736))
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60034, plr);             // Player has buff, denied.
            }
            else
            {
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60026, plr);            // Player doesn't have any buff
                Menu->AddItem(0, "I am ready to discover where my fortune lies!", 1);
            }

            if (Menu != nullptr)
                Menu->SendTo(plr);
        }

        void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code) override
        {
            if (!pObject->IsCreature())
                return;

            GossipMenu* gossipMenu = nullptr;
            Creature* pCreature = static_cast<Creature*>(pObject);

            switch (IntId)
            {
                case 1:        // Question 1 (Initial question, always the same)
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60027, plr);
                    // plr->GetSession()->LocalizedGossipOption(GI_DF_ANSWER_1_1)
                    gossipMenu->AddItem(0, "I slay the man on the spot as my liege would expect me to do, as he is nothing more than a thief and a liar.", 10);
                    gossipMenu->AddItem(0, "I turn over the man to my liege for punishment, as he has broken the law of the land and it is my sworn duty to enforce it.", 11);
                    gossipMenu->AddItem(0, "I confiscate the corn he has stolen, warn him that stealing is a path towards doom and destruction, but I let him go to return to his family.", 12);
                    gossipMenu->AddItem(0, "I allow the man to take enough corn to feed his family for a couple of days, encouraging him to leave the land.", 13);
                    break;
                case 10:    // Question 2 (First Answer = 1)
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60028, plr);

                    gossipMenu->AddItem(0, "I execute him as per my liege's instructions, and do it in such a manner that he suffers painfully before he dies a retribution for his crimes against my people.", 14);
                    gossipMenu->AddItem(0, "I execute him as per my liege's instructions, but doing so in as painless of a way as possible. Justice must be served, but I can show some compassion.", 15);
                    gossipMenu->AddItem(0, "I risk my own life and free him so that he may prove his innocence. If I can, I'll help him in any way.", 16);
                    break;
                case 11:     // Question 2 (First Answer = 2)
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60029, plr);
                    gossipMenu->AddItem(0, "I confront the ruler on his malicious behavior, upholding my liege's honor at risk of any future diplomacy.", 17);
                    gossipMenu->AddItem(0, "I not-so-quietly ignore the insult, hoping to instill a fear in the ruler that he may have gaffed. I then inform my liege of the insult when I return.", 18);
                    gossipMenu->AddItem(0, "I quietly ignore the insult. I will not tell my liege, as I am to secure peace at all costs. It's only an insult - not a declaration of war.", 19);
                    break;
                case 12:     // Question 2 (First Answer = 3)
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60030, plr);
                    gossipMenu->AddItem(0, "I would speak against my brother joining the order, rushing a permanent breech in our relationship. He would be a danger to himself and those around him, and that is too great a risk hoping he would improve over time.", 20);
                    gossipMenu->AddItem(0, "I would speak for my brother joining the order, potentially risking the safety of the order. I could help him with the order's regimens, and I'd have faith in his ability to adapt and learn.", 21);
                    gossipMenu->AddItem(0, "I would create some surreptitious means to keep my brother out of the order. I can keep him out without him being any bit wiser, thereby saving our familial bonds.", 22);
                    break;
                case 13:     // Question 2 (First Answer = 4)
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60031, plr);
                    gossipMenu->AddItem(0, "I would show my liege the beast's ear and claim the beast's death as my own, taking the reward for my own use. It is wrong to claim a deed as your own that someone else in fact did.", 23);
                    gossipMenu->AddItem(0, "I would show my liege the beast's ear and claim the beast's death as my own - after all, I did slay it. I would then offer some of the reward to the destitute knight to help his family.", 24);
                    gossipMenu->AddItem(0, "I would remain silent about the kill and allow the knight to claim the reward to aid his family.", 25);
                    break;
                    // Answers 1-#
                case 14:     // Answers: 1-1
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23768, true);
                    break;
                case 15:     // Answers: 1-2
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23769, true);
                    break;
                case 16:     // Answers: 1-3
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23767, true);
                    break;
                    // Answers 2-#
                case 17:     // Answers: 2-1
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23738, true);
                    break;
                case 18:     // Answers: 2-2
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23766, true);
                    break;
                case 19:     // Answers: 2-3
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23769, true);
                    break;
                    // Answers 3-#
                case 20:     // Answers: 3-1
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23737, true);
                    break;
                case 21:     // Answers: 3-2
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23735, true);
                    break;
                case 22:     // Answers: 3-3
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23736, true);
                    break;
                    // Answers 4-#
                case 23:     // Answers: 4-1
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23766, true);
                    break;
                case 24:     // Answers: 4-2
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23738, true);
                    break;
                case 25:     // Answers: 4-3
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60032, plr);
                    gossipMenu->AddItem(0, "I'd love to get one of those written fortunes you mentioned! I've got the space in my inventory for it.", 30);
                    pCreature->CastSpell(plr, 23737, true);
                    break;
                case 30:
                {
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60033, plr);
                    // Cast the fortune into the player's inventory - Not working?
                    pCreature->CastSpell(plr, 23765, true);
                    // TEMP fix for spell not adding item to  player's inventory.
                    ItemPrototype*  proto = ItemPrototypeStorage.LookupEntry(19422);
                    if (proto == nullptr)
                        return;

                    SlotResult slotresult = plr->GetItemInterface()->FindFreeInventorySlot(proto);
                    if (!slotresult.Result)
                    {
                        plr->GetItemInterface()->BuildInventoryChangeError(nullptr, nullptr, INV_ERR_INVENTORY_FULL);
                        return;
                    }
                    else
                    {
                        Item* item = objmgr.CreateItem(19422, plr);
                        if (item == nullptr)
                            return;

                        AddItemResult result = plr->GetItemInterface()->SafeAddItem(item, slotresult.ContainerSlot, slotresult.Slot);
                        if (!result)
                        {
                            Log.Error("Event_Darkmoon_Faire", "Error while adding item %u to player %s", item->GetEntry(), plr->GetNameString());
                            item->DeleteMe();
                            return;
                        }
                    }
                    break;
                }
                default:
                    return;
            }

            gossipMenu->SendTo(plr);
        }
};

class Sayge_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(Sayge_Bark);
        Sayge_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(135000);             // Start initial update after: 2.25mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(3))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_SAYGE_1);
                    break;

                case 1:
                    _unit->SendScriptTextChatMessage(BARK_SAYGE_2);
                    break;

                case 2:
                    _unit->SendScriptTextChatMessage(BARK_SAYGE_3);
                    break;

                case 3:
                    _unit->SendScriptTextChatMessage(BARK_SAYGE_4);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(180, 360);             // Generate a random value between: 3-5mins
            rndTimer = rndTimer * 1000;             // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);             // Modify timer to new random value
        }
};


// Selina Dourman
/// \ todo find right gossip text in npc_text.
class SelinaDourman_Gossip : public GossipScript
{
    public:

        void GossipHello(Object* pObject, Player* plr) override
        {
            GossipMenu* gossipMenu = nullptr;

            objmgr.CreateGossipMenuForPlayer(&gossipMenu, pObject->GetGUID(), 60035, plr);
            gossipMenu->AddItem(0, "What can I purchase?", 1);
            gossipMenu->AddItem(0, "What are Darkmoon Faire Prize Tickets and how do I get them?", 2);
            gossipMenu->AddItem(0, "What are Darkmoon Cards?", 3);
            gossipMenu->AddItem(0, "What other things can I do at the faire?", 4);

            gossipMenu->SendTo(plr);
        }

        void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code) override
        {
            if (!pObject->IsCreature())
                return;

            GossipMenu* gossipMenu = nullptr;
            Creature* pCreature = static_cast<Creature*>(pObject);

            switch (IntId)
            {
                case 1:
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60036, plr);            // What can I purchase?
                    break;
                case 2:
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60037, plr);            // What are Darkmoon Faire Prize Tickets and how do I get them?
                    break;
                case 3:
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60038, plr);            // What are Darkmoon Cards?
                    gossipMenu->AddItem(0, "<more>", 10);
                    break;
                case 4:
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60040, plr);            // What other things can I do at the faire?
                    gossipMenu->AddItem(0, "What are these Tonk Control Consoles?", 20);
                    gossipMenu->AddItem(0, "Tell me about the cannon.", 21);
                    break;
                case 10:
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60039, plr);            // What are Darkmoon Cards? <more>
                    break;
                case 20:
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60041, plr);            // What are these Tonk Control Consoles?
                    break;
                case 21:
                    objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), 60042, plr);            // Tell me about the cannon.
                    break;
                default:
                    return;
            }
            
            gossipMenu->SendTo(plr);
        }
};


class SilasDarkmoon_Gossip : public GossipScript
{
    public:

        void GossipHello(Object* pObject, Player* plr) override
        {
            GossipMenu* Menu = nullptr;

            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60013, plr);                    /// \todo find right text
            Menu->AddItem(0, "Silas, why is most everything at the fair free? How do you make a profit?", 1);    // Silas, why is most everything at the fair free? How do you make a profit?

            if (Menu != nullptr)
                Menu->SendTo(plr);

        }

        void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code) override
        {
            if (!pObject->IsCreature())
                return;

            GossipMenu* gossipMenu = nullptr;
            Creature* pCreature = static_cast<Creature*>(pObject);
            uint32 textId = 0;

            switch (IntId)
            {
                case 1:
                    textId = 7336;
                    break;
            }

            objmgr.CreateGossipMenuForPlayer(&gossipMenu, pCreature->GetGUID(), textId, plr);
            gossipMenu->SendTo(plr);
        }
};


class SilasDarkmoon_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(SilasDarkmoon_Bark);
        SilasDarkmoon_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(180000);             // Start initial update after: 3mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(5))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_SILAS_DARKMOON_1);
                    break;

                case 1:
                    _unit->SendScriptTextChatMessage(BARK_SILAS_DARKMOON_2);
                    break;

                case 2:
                    _unit->SendScriptTextChatMessage(BARK_SILAS_DARKMOON_3);
                    break;

                case 3:
                    _unit->SendScriptTextChatMessage(BARK_SILAS_DARKMOON_4);
                    break;

                case 4:
                    _unit->SendScriptTextChatMessage(BARK_SILAS_DARKMOON_5);
                    break;

                case 5:
                    _unit->SendScriptTextChatMessage(BARK_SILAS_DARKMOON_6);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(240, 360);             // Generate a random value between: 3-5mins
            rndTimer = rndTimer * 1000;             // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);             // Modify timer to new random value
        }
};


class StampThunderhorn_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(StampThunderhorn_Bark);
        StampThunderhorn_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(180000);             // Start initial update after: 3mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(4))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_STAMP_THUNDERHORN_1);
                    break;

                case 1:
                    _unit->SendScriptTextChatMessage(BARK_STAMP_THUNDERHORN_2);
                    break;

                case 2:
                    _unit->SendScriptTextChatMessage(BARK_STAMP_THUNDERHORN_3);
                    break;

                case 3:
                    _unit->SendScriptTextChatMessage(BARK_STAMP_THUNDERHORN_4);
                    break;

                case 4:
                    _unit->SendScriptTextChatMessage(BARK_STAMP_THUNDERHORN_5);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(180, 360);             // Generate a random value between: 3-5mins
            rndTimer = rndTimer * 1000;             // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);             // Modify timer to new random value
        }
};


class Sylannia_Bark : public CreatureAIScript
{
    public:

        ADD_CREATURE_FACTORY_FUNCTION(Sylannia_Bark);
        Sylannia_Bark(Creature* pCreature) : CreatureAIScript(pCreature)
        {
            RegisterAIUpdateEvent(120000);             // Start initial update after: 2mins
        }

        void AIUpdate() override
        {
            switch (RandomUInt(3))
            {
                case 0:
                    _unit->SendScriptTextChatMessage(BARK_SYLANNIA_1);
                    break;

                case 1:
                    _unit->SendScriptTextChatMessage(BARK_SYLANNIA_2);
                    break;

                case 2:
                    _unit->SendScriptTextChatMessage(BARK_SYLANNIA_3);
                    break;

                case 3:
                    _unit->SendScriptTextChatMessage(BARK_SYLANNIA_4);
                    break;
            }

            uint32 rndTimer;
            rndTimer = RandomUInt(180, 360);             // Generate a random value between: 3-6mins
            rndTimer = rndTimer * 1000;             // Convert to milliseconds
            ModifyAIUpdateEvent(rndTimer);             // Modify timer to new random value
        }
};


void SetupDarkmoonFaire(ScriptMgr* mgr)
{
    //GossipScripts
    mgr->register_gossip_script(14866, new FliksFrog_Gossip);
    mgr->register_gossip_script(15303, new MaximaBlastenheimer_Gossip);
    mgr->register_gossip_script(14847, new ProfessorThaddeusPaleo_Gossip);
    mgr->register_gossip_script(14822, new Sayge_Gossip);
    mgr->register_gossip_script(10445, new SelinaDourman_Gossip);
    mgr->register_gossip_script(14823, new SilasDarkmoon_Gossip);

    // GameobjectScripts
    mgr->register_gameobject_script(180515, &Blastenheimer5000::Create);            // Blastenheimer 5000 Ultra Cannon
    // mgr->register_gameobject_script(180524, &TonkControlConsole::Create);        // Tonk Control Console

    //CreatureScripts
    mgr->register_creature_script(14860, &Flik_Bark::Create);
    mgr->register_creature_script(14828, &GelvasGrimegate_Bark::Create);
    mgr->register_creature_script(14846, &Lhara_Bark::Create);
    mgr->register_creature_script(14871, &Morja_Bark::Create);

    mgr->register_creature_script(14847, &ProfessorThaddeusPaleo_Bark::Create);
    mgr->register_creature_script(14822, &Sayge_Bark::Create);
    mgr->register_creature_script(14823, &SilasDarkmoon_Bark::Create);
    mgr->register_creature_script(14845, &StampThunderhorn_Bark::Create);
    mgr->register_creature_script(14844, &Sylannia_Bark::Create);
}
