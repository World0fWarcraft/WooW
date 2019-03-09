/*
 * ArcScripts for ArcEmu MMORPG Server
 * Copyright (C) 2009- 2014 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (C) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define MAP_ICECROWNCITADEL 631

enum IceCrownCitadelGOs{
	//GO_Tele
	GO_TELE_1 = 202242,
	GO_TELE_2 = 202243,
	GO_TELE_3 = 202244,
	GO_TELE_4 = 202245,
	GO_TELE_5 = 202246,

	//GO_Interactive
	GO_MARROWGAR_ICEWALL_1 = 201911,
	GO_MARROWGAR_ICEWALL_2 = 201910,
	GO_MARROWGAR_DOOR = 201563
};

enum IceCrownCitadelCNentry{

   CN_HIGHLORD_TIRION_FORDRING_LH = 37119,
   CN_THE_LICH_KING_LH = 37181,
   CN_HIGHLORD_BOLVAR_FORDRAGON_LH = 37183,
   CN_KOR_KRON_GENERAL = 37189,
   CN_ALLIANCE_COMMANDER = 37190,
   CN_TORTUNOK = 37992,
   CN_ALANA_MOONSTRIKE = 37999,
   CN_GERARDO_THE_SUAVE = 37993,
   CN_TALAN_MOONSTRIKE = 37998,
   CN_UVLUS_BANEFIRE = 38284,
   CN_MALFUS_GRIMFROST = 38283,
   CN_IKFIRUS_THE_VILE = 37991,
   CN_YILI = 37997,
   CN_VOL_GUK = 38841,
   CN_JEDEBIA = 38840,
   CN_HARAGG_THE_UNSEEN = 38181,
   CN_NIBY_THE_ALMIGHTY = 38182,
   CN_GARROSH_HELLSCREAM = 39372,
   CN_KING_VARIAN_WRYNN = 39371,
   CN_DEATHBOUND_WARD = 37007,
   CN_LADY_JAINA_PROUDMOORE_QUEST = 38606,
   CN_MURADIN_BRONZEBEARD_QUEST = 38607,
   CN_UTHER_THE_LIGHTBRINGER_QUEST = 38608,
   CN_LADY_SYLVANAS_WINDRUNNER_QUEST = 38609,

   CN_INFILTRATOR_MINCHAR = 38471,
   CN_KOR_KRON_LIEUTENANT = 38491,
   CN_SKYBREAKER_LIEUTENANT = 38492,
   CN_ROTTING_FROST_GIANT_10 = 38490,
   CN_ROTTING_FROST_GIANT_25 = 38494,
   CN_ALCHEMIST_ADRIANNA = 38501,
   CN_ALRIN_THE_AGILE = 38551,
   CN_INFILTRATOR_MINCHAR_BQ = 38558,
   CN_MINCHAR_BEAM_STALKER = 38557,
   CN_VALITHRIA_DREAMWALKER_QUEST = 38589,

   CN_LORD_MARROWGAR = 36612,
   CN_COLDFLAME = 36672,
   CN_BONE_SPIKE = 36619,

   CN_LADY_DEATHWHISPER = 36855,
   CN_CULT_FANATIC = 37890,
   CN_DEFORMED_FANATIC = 38135,
   CN_REANIMATED_FANATIC = 38009,
   CN_CULT_ADHERENT = 37949,
   CN_EMPOWERED_ADHERENT = 38136,
   CN_REANIMATED_ADHERENT = 38010,
   CN_VENGEFUL_SHADE = 38222,

   CN_MARTYR_STALKER_IGB_SAURFANG = 38569,
   CN_ALLIANCE_GUNSHIP_CANNON = 36838,
   CN_HORDE_GUNSHIP_CANNON = 36839,
   CN_SKYBREAKER_DECKHAND = 36970,
   CN_ORGRIMS_HAMMER_CREW = 36971,
   CN_IGB_HIGH_OVERLORD_SAURFANG = 36939,
   CN_IGB_MURADIN_BRONZEBEARD = 36948,
   CN_THE_SKYBREAKER = 37540,
   CN_ORGRIMS_HAMMER = 37215,
   CN_GUNSHIP_HULL = 37547,
   CN_TELEPORT_PORTAL = 37227,
   CN_TELEPORT_EXIT = 37488,
   CN_SKYBREAKER_SORCERER = 37116,
   CN_SKYBREAKER_RIFLEMAN = 36969,
   CN_SKYBREAKER_MORTAR_SOLDIER = 36978,
   CN_SKYBREAKER_MARINE = 36950,
   CN_SKYBREAKER_SERGEANT = 36961,
   CN_KOR_KRON_BATTLE_MAGE = 37117,
   CN_KOR_KRON_AXETHROWER = 36968,
   CN_KOR_KRON_ROCKETEER = 36982,
   CN_KOR_KRON_REAVER = 36957,
   CN_KOR_KRON_SERGEANT = 36960,
   CN_ZAFOD_BOOMBOX = 37184,
   CN_HIGH_CAPTAIN_JUSTIN_BARTLETT = 37182,
   CN_SKY_REAVER_KORM_BLACKSCAR = 37833,

   CN_DEATHBRINGER_SAURFANG = 37813,
   CN_BLOOD_BEAST = 38508,
   CN_SE_JAINA_PROUDMOORE = 37188,
   CN_SE_MURADIN_BRONZEBEARD = 37200,
   CN_SE_KING_VARIAN_WRYNN = 37879,
   CN_SE_HIGH_OVERLORD_SAURFANG = 37187,
   CN_SE_KOR_KRON_REAVER = 37920,
   CN_SE_SKYBREAKER_MARINE = 37830,
   CN_FROST_FREEZE_TRAP = 37744,

   CN_FESTERGUT = 36626,
   CN_GAS_DUMMY = 36659,
   CN_MALLEABLE_OOZE_STALKER = 38556,

   CN_ROTFACE = 36627,
   CN_OOZE_SPRAY_STALKER = 37986,
   CN_PUDDLE_STALKER = 37013,
   CN_UNSTABLE_EXPLOSION_STALKER = 38107,
   CN_VILE_GAS_STALKER = 38548,

   CN_PROFESSOR_PUTRICIDE = 36678,
   CN_ABOMINATION_WING_MAD_SCIENTIST_STALKER = 37824,
   CN_GROWING_OOZE_PUDDLE = 37690,
   CN_GAS_CLOUD = 37562,
   CN_VOLATILE_OOZE = 37697,
   CN_CHOKING_GAS_BOMB = 38159,
   CN_TEAR_GAS_TARGET_STALKER = 38317,
   CN_MUTATED_ABOMINATION_10 = 37672,
   CN_MUTATED_ABOMINATION_25 = 38285,

   CN_PRINCE_KELESETH = 37972,
   CN_PRINCE_TALDARAM = 37973,
   CN_PRINCE_VALANAR = 37970,
   CN_BLOOD_ORB_CONTROLLER = 38008,
   CN_FLOATING_TRIGGER = 30298,
   CN_DARK_NUCLEUS = 38369,
   CN_BALL_OF_FLAME = 38332,
   CN_BALL_OF_INFERNO_FLAME = 38451,
   CN_KINETIC_BOMB_TARGET = 38458,
   CN_KINETIC_BOMB = 38454,
   CN_SHOCK_VORTEX = 38422,

   CN_BLOOD_QUEEN_LANA_THEL = 37955,

   CN_CROK_SCOURGEBANE = 37129,
   CN_CAPTAIN_ARNATH = 37122,
   CN_CAPTAIN_BRANDON = 37123,
   CN_CAPTAIN_GRONDEL = 37124,
   CN_CAPTAIN_RUPERT = 37125,
   CN_CAPTAIN_ARNATH_UNDEAD = 37491,
   CN_CAPTAIN_BRANDON_UNDEAD = 37493,
   CN_CAPTAIN_GRONDEL_UNDEAD = 37494,
   CN_CAPTAIN_RUPERT_UNDEAD = 37495,
   CN_YMIRJAR_BATTLE_MAIDEN = 37132,
   CN_YMIRJAR_DEATHBRINGER = 38125,
   CN_YMIRJAR_FROSTBINDER = 37127,
   CN_YMIRJAR_HUNTRESS = 37134,
   CN_YMIRJAR_WARLORD = 37133,
   CN_SISTER_SVALNA = 37126,
   CN_IMPALING_SPEAR = 38248,

   CN_VALITHRIA_DREAMWALKER = 36789,
   CN_GREEN_DRAGON_COMBAT_TRIGGER = 38752,
   CN_RISEN_ARCHMAGE = 37868,
   CN_BLAZING_SKELETON = 36791,
   CN_SUPPRESSER = 37863,
   CN_BLISTERING_ZOMBIE = 37934,
   CN_GLUTTONOUS_ABOMINATION = 37886,
   CN_MANA_VOID = 38068,
   CN_COLUMN_OF_FROST = 37918,
   CN_ROT_WORM = 37907,
   CN_THE_LICH_KING_VALITHRIA = 16980,
   CN_DREAM_PORTAL_PRE_EFFECT = 38186,
   CN_NIGHTMARE_PORTAL_PRE_EFFECT = 38429,
   CN_DREAM_PORTAL = 37945,
   CN_NIGHTMARE_PORTAL = 38430,

   CN_SINDRAGOSA = 36853,
   CN_SPINESTALKER = 37534,
   CN_RIMEFANG = 37533,
   CN_FROSTWARDEN_HANDLER = 37531,
   CN_FROSTWING_WHELP = 37532,
   CN_ICY_BLAST = 38223,
   CN_FROST_BOMB = 37186,
   CN_ICE_TOMB = 36980,

   CN_THE_LICH_KING = 36597,
   CN_HIGHLORD_TIRION_FORDRING_LK = 38995,
   CN_TERENAS_MENETHIL_FROSTMOURNE = 36823,
   CN_SPIRIT_WARDEN = 36824,
   CN_TERENAS_MENETHIL_FROSTMOURNE_H = 39217,
   CN_SHAMBLING_HORROR = 37698,
   CN_DRUDGE_GHOUL = 37695,
   CN_ICE_SPHERE = 36633,
   CN_RAGING_SPIRIT = 36701,
   CN_DEFILE = 38757,
   CN_VALKYR_SHADOWGUARD = 36609,
   CN_VILE_SPIRIT = 37799,
   CN_WICKED_SPIRIT = 39190,
   CN_STRANGULATE_VEHICLE = 36598,
   CN_WORLD_TRIGGER = 22515,
   CN_WORLD_TRIGGER_INFINITE_AOI = 36171,
   CN_SPIRIT_BOMB = 39189,
   CN_FROSTMOURNE_TRIGGER = 38584
};

// CN ids for Encounter State ?!?
enum IceCrownCitadelCNid{
   CNID_LORD_MARROWGAR         = 0,
   CNID_COLDFLAME              = 1,
   CNID_LADY_DEATHWHISPER      = 2,
   CNID_VALITHRIA_DREAMWALKER  = 3,
   CNID_END
};

static Location Doors[] =
{
	{ -407.35f, 2147.88f, 42.85f, 0 },	     //IceWall1
	{ -412.97f, 2285.24f, 42.01f, 0 },       //IceWall2
	{ -520.44f, 2211.47f, 63.14f, 0 },       //Door behinde ice
};

// Teleport coords for Gossip
static float ICCTeleCoords[6][5] =
{	// Maybe moving this to a clean mysql table with all teleports in it... maybe as spell or event?
	{ MAP_ICECROWNCITADEL, -17.856115f, 2211.640137f, 30.115812f, 0.0f },     //1   Teleport to Light's Hammer 
	{ MAP_ICECROWNCITADEL, -503.632599f, 2211.219971f, 62.823246f, 0.0f },    //2   Teleport to Oratory of The Damned
	{ MAP_ICECROWNCITADEL, -615.098267f, 2211.509766f, 199.973083f, 0.0f },   //3   Teleport to Rampart of Skulls 
	{ MAP_ICECROWNCITADEL, -549.151001f, 2211.463967f, 539.290222f, 0.0f },   //4   Teleport to Deathbringer's Rise 
	{ MAP_ICECROWNCITADEL, 4356.780273f, 2863.636230f, 349.337982f, 0.0f },   //5   Teleport to the Upper Spire.
	{ MAP_ICECROWNCITADEL, 4453.248535f, 2769.325684f, 349.347473f, 0.0f }    //6   Teleport to Sindragosa's Lair
};

void SetupICC(ScriptMgr* mgr);