#pragma once

#include <stdint.h>

//============================================================================
// Native types. All native functions take extended handle types when
// possible to help prevent passing bad values to native functions
//============================================================================
typedef int32_t			handle;
typedef handle			agent;				// all reference counted objects
typedef agent			event;				// a reference to an event registration
typedef agent			player;				// a single player reference
typedef agent			widget;				// an interactive game object with life
typedef widget			unit;				// a single unit reference
typedef widget			destructable;
typedef widget			item;
typedef agent			ability;
typedef ability			buff;
typedef agent			force;
typedef agent			group;
typedef agent			trigger;
typedef agent			triggercondition;
typedef handle			triggeraction;
typedef agent			timer;
typedef agent			location;
typedef agent			region;
typedef agent			rect;
typedef agent			boolexpr;
typedef agent			sound;
typedef boolexpr		conditionfunc;
typedef boolexpr		filterfunc;
typedef handle			unitpool;
typedef handle			itempool;
typedef handle			race;
typedef handle			alliancetypedef;
typedef handle			racepreference;
typedef handle			gamestate;
typedef gamestate		igamestate;
typedef gamestate		fgamestate;
typedef handle			playerstate;
typedef handle			playerscore;
typedef handle			playergameresult;
typedef handle			unitstate;
typedef handle			aidifficulty;

typedef handle			eventid;
typedef eventid			gameevent;
typedef eventid			playerevent;
typedef eventid			playerunitevent;
typedef eventid			unitevent;
typedef eventid			limitop;
typedef eventid			widgetevent;
typedef eventid			dialogevent;
typedef handle			unittypedef;

typedef handle			gamespeed;
typedef handle			gamedifficulty;
typedef handle			gametypedef;
typedef handle			mapflag;
typedef handle			mapvisibility;
typedef handle			mapsetting;
typedef handle			mapdensity;
typedef handle			mapcontrol;
typedef handle			playerslotstate;
typedef handle			volumegroup;
typedef handle			camerafield;
typedef handle			camerasetup;
typedef handle			playercolor;
typedef handle			placement;
typedef handle			startlocprio;
typedef handle			raritycontrol;
typedef handle			blendmode;
typedef handle			texmapflags;
typedef agent			effect;
typedef handle			effecttypedef;
typedef handle			weathereffect;
typedef handle			terraindeformation;
typedef handle			fogstate;
typedef agent			fogmodifier;
typedef agent			dialog;
typedef agent			button;
typedef agent			quest;
typedef agent			questitem;
typedef agent			defeatcondition;
typedef agent			timerdialog;
typedef agent			leaderboard;
typedef agent			multiboard;
typedef agent			multiboarditem;
typedef agent			trackable;
typedef agent			gamecache;
typedef handle			version;
typedef handle			itemtypedef;
typedef handle			texttag;
typedef handle			attacktypedef;
typedef handle			damagetypedef;
typedef handle			weapontypedef;
typedef handle			soundtypedef;
typedef handle			lightning;
typedef handle			pathingtypedef;
typedef handle			image;
typedef handle			ubersplat;
typedef agent			hashtable;

typedef int32_t			jboolean;
typedef bool			jbooleanret;
typedef int32_t			integer;
typedef handle			string;
typedef float*			real;
typedef void			nothing;

//=========================================
// Custom Data Types
//=========================================
typedef handle			code;
typedef float			realret;
typedef LPCSTR			stringret;
union DWFP
{
	DWORD dw;
	float fl;
};
//=========================================
// Game Constants    
//=========================================
const integer			JASS_MAX_ARRAY_SIZE = 8192;
const integer			PLAYER_NEUTRAL_PASSIVE = 15;
const integer			PLAYER_NEUTRAL_AGGRESSIVE = 12;


#define PLAYER_COLOR_RED						ConvertPlayerColor(0)
#define PLAYER_COLOR_BLUE						ConvertPlayerColor(1)
#define PLAYER_COLOR_CYAN						ConvertPlayerColor(2)
#define PLAYER_COLOR_PURPLE						ConvertPlayerColor(3)
#define PLAYER_COLOR_YELLOW						ConvertPlayerColor(4)
#define PLAYER_COLOR_ORANGE						ConvertPlayerColor(5)
#define PLAYER_COLOR_GREEN						ConvertPlayerColor(6)
#define PLAYER_COLOR_PINK						ConvertPlayerColor(7)
#define PLAYER_COLOR_LIGHT_GRAY					ConvertPlayerColor(8)
#define PLAYER_COLOR_LIGHT_BLUE					ConvertPlayerColor(9)
#define PLAYER_COLOR_AQUA						ConvertPlayerColor(10)
#define	PLAYER_COLOR_BROWN						ConvertPlayerColor(11)

#define	_HUMAN									ConvertRace(1)
#define	_ORC									ConvertRace(2)
#define	_UNDEAD									ConvertRace(3)
#define	_NIGHTELF								ConvertRace(4)
#define	_DEMON									ConvertRace(5)
#define	_OTHER									ConvertRace(7)

#define	PLAYER_GAME_RESULT_VICTORY				ConvertPlayerGameResult(0)
#define	PLAYER_GAME_RESULT_DEFEAT				ConvertPlayerGameResult(1)
#define	PLAYER_GAME_RESULT_TIE					ConvertPlayerGameResult(2)
#define	PLAYER_GAME_RESULT_NEUTRAL				ConvertPlayerGameResult(3)

#define	ALLIANCE_PASSIVE						ConvertAllianceType(0)
#define	ALLIANCE_HELP_REQUEST					ConvertAllianceType(1)
#define	ALLIANCE_HELP_RESPONSE					ConvertAllianceType(2)
#define	ALLIANCE_SHARED_XP						ConvertAllianceType(3)
#define	ALLIANCE_SHARED_SPELLS					ConvertAllianceType(4)
#define	ALLIANCE_SHARED_VISION					ConvertAllianceType(5)
#define	ALLIANCE_SHARED_CONTROL					ConvertAllianceType(6)
#define	ALLIANCE_SHARED_ADVANCED_CONTROL		ConvertAllianceType(7)
#define	ALLIANCE_RESCUABLE						ConvertAllianceType(8)
#define	ALLIANCE_SHARED_VISION_FORCED			ConvertAllianceType(9)

#define VERSION_REIGN_OF_CHAOS					ConvertVersion(0)
#define	VERSION_FROZEN_THRONE					ConvertVersion(1)

#define	ATTACK_TYPE_NORMAL						ConvertAttackType(0)
#define	ATTACK_TYPE_MELEE						ConvertAttackType(1)
#define	ATTACK_TYPE_PIERCE						ConvertAttackType(2)
#define	ATTACK_TYPE_SIEGE						ConvertAttackType(3)
#define	ATTACK_TYPE_MAGIC						ConvertAttackType(4)
#define	ATTACK_TYPE_CHAOS						ConvertAttackType(5)
#define	ATTACK_TYPE_HERO						ConvertAttackType(6)

#define	DAMAGE_TYPE_UNKNOWN						ConvertDamageType(0)
#define DAMAGE_TYPE_NORMAL						ConvertDamageType(4)
#define DAMAGE_TYPE_ENHANCED					ConvertDamageType(5)
#define DAMAGE_TYPE_FIRE						ConvertDamageType(8)
#define DAMAGE_TYPE_COLD						ConvertDamageType(9)
#define DAMAGE_TYPE_LIGHTNING					ConvertDamageType(10)
#define DAMAGE_TYPE_POISON						ConvertDamageType(11)
#define DAMAGE_TYPE_DISEASE						ConvertDamageType(12)
#define DAMAGE_TYPE_DIVINE						ConvertDamageType(13)
#define DAMAGE_TYPE_MAGIC						ConvertDamageType(14)
#define DAMAGE_TYPE_SONIC						ConvertDamageType(15)
#define DAMAGE_TYPE_ACID						ConvertDamageType(16)
#define DAMAGE_TYPE_FORCE						ConvertDamageType(17)
#define DAMAGE_TYPE_DEATH						ConvertDamageType(18)
#define DAMAGE_TYPE_MIND						ConvertDamageType(19)
#define DAMAGE_TYPE_PLANT						ConvertDamageType(20)
#define DAMAGE_TYPE_DEFENSIVE					ConvertDamageType(21)
#define DAMAGE_TYPE_DEMOLITION					ConvertDamageType(22)
#define DAMAGE_TYPE_SLOW_POISON					ConvertDamageType(23)
#define DAMAGE_TYPE_SPIRIT_LINK					ConvertDamageType(24)
#define DAMAGE_TYPE_SHADOW_STRIKE				ConvertDamageType(25)
#define	DAMAGE_TYPE_UNIVERSAL					ConvertDamageType(26)

#define WEAPON_TYPE_WHOKNOWS					ConvertWeaponType(0)
#define WEAPON_TYPE_METAL_LIGHT_CHOP			ConvertWeaponType(1)
#define WEAPON_TYPE_METAL_MEDIUM_CHOP			ConvertWeaponType(2)
#define WEAPON_TYPE_METAL_HEAVY_CHOP			ConvertWeaponType(3)
#define WEAPON_TYPE_METAL_LIGHT_SLICE			ConvertWeaponType(4)
#define WEAPON_TYPE_METAL_MEDIUM_SLICE			ConvertWeaponType(5)
#define WEAPON_TYPE_METAL_HEAVY_SLICE			ConvertWeaponType(6)
#define WEAPON_TYPE_METAL_MEDIUM_BASH			ConvertWeaponType(7)
#define WEAPON_TYPE_METAL_HEAVY_BASH			ConvertWeaponType(8)
#define WEAPON_TYPE_METAL_MEDIUM_STAB			ConvertWeaponType(9)
#define WEAPON_TYPE_METAL_HEAVY_STAB			ConvertWeaponType(10)
#define WEAPON_TYPE_WOOD_LIGHT_SLICE			ConvertWeaponType(11)
#define WEAPON_TYPE_WOOD_MEDIUM_SLICE			ConvertWeaponType(12)
#define WEAPON_TYPE_WOOD_HEAVY_SLICE			ConvertWeaponType(13)
#define WEAPON_TYPE_WOOD_LIGHT_BASH				ConvertWeaponType(14)
#define WEAPON_TYPE_WOOD_MEDIUM_BASH			ConvertWeaponType(15)
#define WEAPON_TYPE_WOOD_HEAVY_BASH				ConvertWeaponType(16)
#define WEAPON_TYPE_WOOD_LIGHT_STAB				ConvertWeaponType(17)
#define WEAPON_TYPE_WOOD_MEDIUM_STAB			ConvertWeaponType(18)
#define WEAPON_TYPE_CLAW_LIGHT_SLICE			ConvertWeaponType(19)
#define WEAPON_TYPE_CLAW_MEDIUM_SLICE			ConvertWeaponType(20)
#define WEAPON_TYPE_CLAW_HEAVY_SLICE			ConvertWeaponType(21)
#define WEAPON_TYPE_AXE_MEDIUM_CHOP				ConvertWeaponType(22)
#define WEAPON_TYPE_ROCK_HEAVY_BASH				ConvertWeaponType(23)

#define PATHING_TYPE_ANY						ConvertPathingType(0)
#define PATHING_TYPE_WALKABILITY				ConvertPathingType(1)
#define PATHING_TYPE_FLYABILITY					ConvertPathingType(2)
#define PATHING_TYPE_BUILDABILITY				ConvertPathingType(3)
#define PATHING_TYPE_PEONHARVESTPATHING			ConvertPathingType(4)
#define PATHING_TYPE_BLIGHTPATHING				ConvertPathingType(5)
#define PATHING_TYPE_FLOATABILITY				ConvertPathingType(6)
#define PATHING_TYPE_AMPHIBIOUSPATHING			ConvertPathingType(7)

//=========================================
// Map Setup Constants    
//=========================================
#define	RACE_PREF_HUMAN							ConvertRacePref(1)
#define	RACE_PREF_ORC							ConvertRacePref(2)
#define	RACE_PREF_NIGHTELF						ConvertRacePref(4)
#define	RACE_PREF_UNDEAD						ConvertRacePref(8)
#define	RACE_PREF_DEMON							ConvertRacePref(16)
#define	RACE_PREF_RANDOM						ConvertRacePref(32)
#define	RACE_PREF_USER_SELECTABLE				ConvertRacePref(64)

#define	MAP_CONTROL_USER						ConvertMapControl(0)
#define	MAP_CONTROL_COMPUTER					ConvertMapControl(1)
#define	MAP_CONTROL_RESCUABLE					ConvertMapControl(2)
#define	MAP_CONTROL_NEUTRAL						ConvertMapControl(3)
#define	MAP_CONTROL_CREEP						ConvertMapControl(4)
#define	MAP_CONTROL_NONE						ConvertMapControl(5)

#define	GAME_TYPE_MELEE							ConvertGameType(1)
#define	GAME_TYPE_FFA							ConvertGameType(2)
#define	GAME_TYPE_USE_MAP_SETTINGS				ConvertGameType(4)
#define	GAME_TYPE_BLIZ							ConvertGameType(8)
#define	GAME_TYPE_ONE_ON_ONE					ConvertGameType(16)
#define	GAME_TYPE_TWO_TEAM_PLAY					ConvertGameType(32)
#define	GAME_TYPE_THREE_TEAM_PLAY				ConvertGameType(64)
#define	GAME_TYPE_FOUR_TEAM_PLAY				ConvertGameType(128)

#define	MAP_FOG_HIDE_TERRAIN					ConvertMapFlag(1)
#define	MAP_FOG_MAP_EXPLORED					ConvertMapFlag(2)
#define	MAP_FOG_ALWAYS_VISIBLE					ConvertMapFlag(4)

#define	MAP_USE_HANDICAPS						ConvertMapFlag(8)
#define	MAP_OBSERVERS							ConvertMapFlag(16)
#define	MAP_OBSERVERS_ON_DEATH					ConvertMapFlag(32)

#define	MAP_FIXED_COLORS						ConvertMapFlag(128)

#define	MAP_LOCK_RESOURCE_TRADING				ConvertMapFlag(256)
#define	MAP_RESOURCE_TRADING_ALLIES_ONLY		ConvertMapFlag(512)

#define	MAP_LOCK_ALLIANCE_CHANGES				ConvertMapFlag(1024)
#define	MAP_ALLIANCE_CHANGES_HIDDEN				ConvertMapFlag(2048)

#define	MAP_CHEATS								ConvertMapFlag(4096)
#define	MAP_CHEATS_HIDDEN						ConvertMapFlag(8192)

#define	MAP_LOCK_SPEED							ConvertMapFlag(8192*2)
#define	MAP_LOCK_RANDOM_SEED					ConvertMapFlag(8192*4)
#define	MAP_SHARED_ADVANCED_CONTROL				ConvertMapFlag(8192*8)
#define	MAP_RANDOM_HERO							ConvertMapFlag(8192*16)
#define	MAP_RANDOM_RACES						ConvertMapFlag(8192*32)
#define	MAP_RELOADED							ConvertMapFlag(8192*64)

#define  MAP_PLACEMENT_RANDOM					ConvertPlacement(0)   // random among all slots
#define  MAP_PLACEMENT_FIXED					ConvertPlacement(1)   // player 0 in start loc 0...
#define  MAP_PLACEMENT_USE_MAP_SETTINGS			ConvertPlacement(2)   // whatever was specified by the script
#define  MAP_PLACEMENT_TEAMS_TOGETHER			ConvertPlacement(3)   // random with allies next to each other    

#define	MAP_LOC_PRIO_LOW						ConvertStartLocPrio(0)
#define	MAP_LOC_PRIO_HIGH						ConvertStartLocPrio(1)
#define	MAP_LOC_PRIO_NOT						ConvertStartLocPrio(2)

#define	MAP_DENSITY_NONE						ConvertMapDensity(0)
#define	MAP_DENSITY_LIGHT						ConvertMapDensity(1)
#define	MAP_DENSITY_MEDIUM						ConvertMapDensity(2)
#define	MAP_DENSITY_HEAVY						ConvertMapDensity(3)

#define	MAP_DIFFICULTY_EASY						ConvertGameDifficulty(0)
#define	MAP_DIFFICULTY_NORMAL					ConvertGameDifficulty(1)
#define	MAP_DIFFICULTY_HARD						ConvertGameDifficulty(2)
#define	MAP_DIFFICULTY_INSANE					ConvertGameDifficulty(3)

#define	MAP_SPEED_SLOWEST						ConvertGameSpeed(0)
#define	MAP_SPEED_SLOW							ConvertGameSpeed(1)
#define	MAP_SPEED_NORMAL						ConvertGameSpeed(2)
#define	MAP_SPEED_FAST							ConvertGameSpeed(3)
#define	MAP_SPEED_FASTEST						ConvertGameSpeed(4)

#define	PLAYER_SLOT_STATE_EMPTY					ConvertPlayerSlotState(0)
#define	PLAYER_SLOT_STATE_PLAYING				ConvertPlayerSlotState(1)
#define	PLAYER_SLOT_STATE_LEFT					ConvertPlayerSlotState(2)

//=========================================
// Sound Constants
//=========================================
#define SOUND_VOLUMEGROUP_UNITMOVEMENT			ConvertVolumeGroup(0)
#define SOUND_VOLUMEGROUP_UNITSOUNDS			ConvertVolumeGroup(1)
#define SOUND_VOLUMEGROUP_COMBAT				ConvertVolumeGroup(2)
#define SOUND_VOLUMEGROUP_SPELLS				ConvertVolumeGroup(3)
#define SOUND_VOLUMEGROUP_UI					ConvertVolumeGroup(4)
#define SOUND_VOLUMEGROUP_MUSIC					ConvertVolumeGroup(5)
#define SOUND_VOLUMEGROUP_AMBIENTSOUNDS			ConvertVolumeGroup(6)
#define SOUND_VOLUMEGROUP_FIRE					ConvertVolumeGroup(7)

//===============================================
// Game, Player, and Unit States
// For use with TriggerRegister<X>StateEvent
//===============================================
#define GAME_STATE_DIVINE_INTERVENTION			ConvertIGameState(0)
#define GAME_STATE_DISCONNECTED					ConvertIGameState(1)
#define GAME_STATE_TIME_OF_DAY					ConvertFGameState(2)

#define PLAYER_STATE_GAME_RESULT				ConvertPlayerState(0)

// Current resource levels
#define PLAYER_STATE_RESOURCE_GOLD				ConvertPlayerState(1)
#define PLAYER_STATE_RESOURCE_LUMBER			ConvertPlayerState(2)
#define PLAYER_STATE_RESOURCE_HERO_TOKENS		ConvertPlayerState(3)
#define PLAYER_STATE_RESOURCE_FOOD_CAP			ConvertPlayerState(4)
#define PLAYER_STATE_RESOURCE_FOOD_USED			ConvertPlayerState(5)
#define PLAYER_STATE_FOOD_CAP_CEILING			ConvertPlayerState(6)

#define PLAYER_STATE_GIVES_BOUNTY				ConvertPlayerState(7)
#define PLAYER_STATE_ALLIED_VICTORY				ConvertPlayerState(8)
#define PLAYER_STATE_PLACED						ConvertPlayerState(9)
#define PLAYER_STATE_OBSERVER_ON_DEATH			ConvertPlayerState(10)
#define PLAYER_STATE_OBSERVER					ConvertPlayerState(11)
#define PLAYER_STATE_UNFOLLOWABLE				ConvertPlayerState(12)

// Taxation rate for each resource
#define PLAYER_STATE_GOLD_UPKEEP_RATE			ConvertPlayerState(13)
#define PLAYER_STATE_LUMBER_UPKEEP_RATE			ConvertPlayerState(14)

// Cumulative resources collected by the player during the mission
#define PLAYER_STATE_GOLD_GATHERED				ConvertPlayerState(15)
#define PLAYER_STATE_LUMBER_GATHERED			ConvertPlayerState(16)

#define PLAYER_STATE_NO_CREEP_SLEEP				ConvertPlayerState(25)

#define UNIT_STATE_LIFE							ConvertUnitState(0)
#define UNIT_STATE_MAX_LIFE						ConvertUnitState(1)
#define UNIT_STATE_MANA							ConvertUnitState(2)
#define UNIT_STATE_MAX_MANA						ConvertUnitState(3)

#define AI_DIFFICULTY_NEWBIE					ConvertAIDifficulty(0)
#define AI_DIFFICULTY_NORMAL					ConvertAIDifficulty(1)
#define AI_DIFFICULTY_INSANE					ConvertAIDifficulty(2)

// Player score values
#define PLAYER_SCORE_UNITS_TRAINED				ConvertPlayerScore(0)
#define PLAYER_SCORE_UNITS_KILLED				ConvertPlayerScore(1)
#define PLAYER_SCORE_STRUCT_BUILT				ConvertPlayerScore(2)
#define PLAYER_SCORE_STRUCT_RAZED				ConvertPlayerScore(3)
#define PLAYER_SCORE_TECH_PERCENT				ConvertPlayerScore(4)
#define PLAYER_SCORE_FOOD_MAXPROD				ConvertPlayerScore(5)
#define PLAYER_SCORE_FOOD_MAXUSED				ConvertPlayerScore(6)
#define PLAYER_SCORE_HEROES_KILLED				ConvertPlayerScore(7)
#define PLAYER_SCORE_ITEMS_GAINED				ConvertPlayerScore(8)
#define PLAYER_SCORE_MERCS_HIRED				ConvertPlayerScore(9)
#define PLAYER_SCORE_GOLD_MINED_TOTAL			ConvertPlayerScore(10)
#define PLAYER_SCORE_GOLD_MINED_UPKEEP			ConvertPlayerScore(11)
#define PLAYER_SCORE_GOLD_LOST_UPKEEP			ConvertPlayerScore(12)
#define PLAYER_SCORE_GOLD_LOST_TAX				ConvertPlayerScore(13)
#define PLAYER_SCORE_GOLD_GIVEN					ConvertPlayerScore(14)
#define PLAYER_SCORE_GOLD_RECEIVED				ConvertPlayerScore(15)
#define PLAYER_SCORE_LUMBER_TOTAL				ConvertPlayerScore(16)
#define PLAYER_SCORE_LUMBER_LOST_UPKEEP			ConvertPlayerScore(17)
#define PLAYER_SCORE_LUMBER_LOST_TAX			ConvertPlayerScore(18)
#define PLAYER_SCORE_LUMBER_GIVEN				ConvertPlayerScore(19)
#define PLAYER_SCORE_LUMBER_RECEIVED			ConvertPlayerScore(20)
#define PLAYER_SCORE_UNIT_TOTAL					ConvertPlayerScore(21)
#define PLAYER_SCORE_HERO_TOTAL					ConvertPlayerScore(22)
#define PLAYER_SCORE_RESOURCE_TOTAL				ConvertPlayerScore(23)
#define PLAYER_SCORE_TOTAL						ConvertPlayerScore(24)

//===================================================
// Game, Player and Unit Events
//  When an event causes a trigger to fire these
//  values allow the action code to determine which
//  event was dispatched and therefore which set of
//  native functions should be used to get information
//  about the event.
//===================================================

//============================================
// For use with TriggerRegisterGameEvent    
//============================================

#define EVENT_GAME_VICTORY						ConvertGameEvent(0)
#define EVENT_GAME_END_LEVEL					ConvertGameEvent(1)

#define EVENT_GAME_VARIABLE_LIMIT				ConvertGameEvent(2)
#define EVENT_GAME_STATE_LIMIT					ConvertGameEvent(3)

#define EVENT_GAME_TIMER_EXPIRED				ConvertGameEvent(4)

#define EVENT_GAME_ENTER_REGION					ConvertGameEvent(5)
#define EVENT_GAME_LEAVE_REGION					ConvertGameEvent(6)

#define EVENT_GAME_TRACKABLE_HIT				ConvertGameEvent(7)
#define EVENT_GAME_TRACKABLE_TRACK				ConvertGameEvent(8)

#define EVENT_GAME_SHOW_SKILL					ConvertGameEvent(9)    
#define EVENT_GAME_BUILD_SUBMENU				ConvertGameEvent(10)

//===============================================
// For use with TriggerRegisterPlayerEvent
//===============================================
#define EVENT_PLAYER_STATE_LIMIT				ConvertPlayerEvent(11)
#define EVENT_PLAYER_ALLIANCE_CHANGED			ConvertPlayerEvent(12)

#define EVENT_PLAYER_DEFEAT						ConvertPlayerEvent(13)
#define EVENT_PLAYER_VICTORY					ConvertPlayerEvent(14)
#define EVENT_PLAYER_LEAVE						ConvertPlayerEvent(15)
#define EVENT_PLAYER_CHAT						ConvertPlayerEvent(16)
#define EVENT_PLAYER_END_CINEMATIC				ConvertPlayerEvent(17)

//===============================================
// For use with TriggerRegisterPlayerUnitEvent
//===============================================
#define EVENT_PLAYER_UNIT_ATTACKED				ConvertPlayerUnitEvent(18)
#define EVENT_PLAYER_UNIT_RESCUED				ConvertPlayerUnitEvent(19)

#define EVENT_PLAYER_UNIT_DEATH					ConvertPlayerUnitEvent(20)
#define EVENT_PLAYER_UNIT_DECAY					ConvertPlayerUnitEvent(21)

#define EVENT_PLAYER_UNIT_DETECTED				ConvertPlayerUnitEvent(22)
#define EVENT_PLAYER_UNIT_HIDDEN				ConvertPlayerUnitEvent(23)

#define EVENT_PLAYER_UNIT_SELECTED				ConvertPlayerUnitEvent(24)
#define EVENT_PLAYER_UNIT_DESELECTED			ConvertPlayerUnitEvent(25)

#define EVENT_PLAYER_UNIT_CONSTRUCT_START		ConvertPlayerUnitEvent(26)
#define EVENT_PLAYER_UNIT_CONSTRUCT_CANCEL		ConvertPlayerUnitEvent(27)
#define EVENT_PLAYER_UNIT_CONSTRUCT_FINISH		ConvertPlayerUnitEvent(28)

#define EVENT_PLAYER_UNIT_UPGRADE_START			ConvertPlayerUnitEvent(29)
#define EVENT_PLAYER_UNIT_UPGRADE_CANCEL		ConvertPlayerUnitEvent(30)
#define EVENT_PLAYER_UNIT_UPGRADE_FINISH		ConvertPlayerUnitEvent(31)

#define EVENT_PLAYER_UNIT_TRAIN_START			ConvertPlayerUnitEvent(32)
#define EVENT_PLAYER_UNIT_TRAIN_CANCEL			ConvertPlayerUnitEvent(33)
#define EVENT_PLAYER_UNIT_TRAIN_FINISH			ConvertPlayerUnitEvent(34)

#define EVENT_PLAYER_UNIT_RESEARCH_START		ConvertPlayerUnitEvent(35)
#define EVENT_PLAYER_UNIT_RESEARCH_CANCEL		ConvertPlayerUnitEvent(36)
#define EVENT_PLAYER_UNIT_RESEARCH_FINISH		ConvertPlayerUnitEvent(37)
#define EVENT_PLAYER_UNIT_ISSUED_ORDER			ConvertPlayerUnitEvent(38)
#define EVENT_PLAYER_UNIT_ISSUED_POINT_ORDER	ConvertPlayerUnitEvent(39)
#define EVENT_PLAYER_UNIT_ISSUED_TARGET_ORDER	ConvertPlayerUnitEvent(40)
#define EVENT_PLAYER_UNIT_ISSUED_UNIT_ORDER		ConvertPlayerUnitEvent(40)    // For compat

#define EVENT_PLAYER_HERO_LEVEL					ConvertPlayerUnitEvent(41)
#define EVENT_PLAYER_HERO_SKILL					ConvertPlayerUnitEvent(42)

#define EVENT_PLAYER_HERO_REVIVABLE				ConvertPlayerUnitEvent(43)

#define EVENT_PLAYER_HERO_REVIVE_START			ConvertPlayerUnitEvent(44)
#define EVENT_PLAYER_HERO_REVIVE_CANCEL			ConvertPlayerUnitEvent(45)
#define EVENT_PLAYER_HERO_REVIVE_FINISH			ConvertPlayerUnitEvent(46)
#define EVENT_PLAYER_UNIT_SUMMON				ConvertPlayerUnitEvent(47)
#define EVENT_PLAYER_UNIT_DROP_ITEM				ConvertPlayerUnitEvent(48)
#define EVENT_PLAYER_UNIT_PICKUP_ITEM			ConvertPlayerUnitEvent(49)
#define EVENT_PLAYER_UNIT_USE_ITEM				ConvertPlayerUnitEvent(50)

#define EVENT_PLAYER_UNIT_LOADED				ConvertPlayerUnitEvent(51)

//===================================================
// For use with TriggerRegisterUnitEvent
//===================================================
#define EVENT_UNIT_DAMAGED						ConvertUnitEvent(52)
#define EVENT_UNIT_DEATH						ConvertUnitEvent(53)
#define EVENT_UNIT_DECAY						ConvertUnitEvent(54)
#define EVENT_UNIT_DETECTED						ConvertUnitEvent(55)
#define EVENT_UNIT_HIDDEN						ConvertUnitEvent(56)
#define EVENT_UNIT_SELECTED						ConvertUnitEvent(57)
#define EVENT_UNIT_DESELECTED					ConvertUnitEvent(58)

#define EVENT_UNIT_STATE_LIMIT					ConvertUnitEvent(59)

//========================================================
// Events which may have a filter for the "other unit"
//========================================================
#define EVENT_UNIT_ACQUIRED_TARGET				ConvertUnitEvent(60)
#define EVENT_UNIT_TARGET_IN_RANGE				ConvertUnitEvent(61)
#define EVENT_UNIT_ATTACKED						ConvertUnitEvent(62)
#define EVENT_UNIT_RESCUED						ConvertUnitEvent(63)

#define EVENT_UNIT_CONSTRUCT_CANCEL				ConvertUnitEvent(64)
#define EVENT_UNIT_CONSTRUCT_FINISH				ConvertUnitEvent(65)

#define EVENT_UNIT_UPGRADE_START				ConvertUnitEvent(66)
#define EVENT_UNIT_UPGRADE_CANCEL				ConvertUnitEvent(67)
#define EVENT_UNIT_UPGRADE_FINISH				ConvertUnitEvent(68)

//========================================================
// Events which involve the specified unit performing
// training of other units  
//========================================================
#define EVENT_UNIT_TRAIN_START					ConvertUnitEvent(69)
#define EVENT_UNIT_TRAIN_CANCEL					ConvertUnitEvent(70)
#define EVENT_UNIT_TRAIN_FINISH					ConvertUnitEvent(71)

#define EVENT_UNIT_RESEARCH_START				ConvertUnitEvent(72)
#define EVENT_UNIT_RESEARCH_CANCEL				ConvertUnitEvent(73)
#define EVENT_UNIT_RESEARCH_FINISH				ConvertUnitEvent(74)

#define EVENT_UNIT_ISSUED_ORDER					ConvertUnitEvent(75)
#define EVENT_UNIT_ISSUED_POINT_ORDER			ConvertUnitEvent(76)
#define EVENT_UNIT_ISSUED_TARGET_ORDER			ConvertUnitEvent(77)

#define EVENT_UNIT_HERO_LEVEL					ConvertUnitEvent(78)
#define EVENT_UNIT_HERO_SKILL					ConvertUnitEvent(79)

#define EVENT_UNIT_HERO_REVIVABLE				ConvertUnitEvent(80)
#define EVENT_UNIT_HERO_REVIVE_START			ConvertUnitEvent(81)
#define EVENT_UNIT_HERO_REVIVE_CANCEL			ConvertUnitEvent(82)
#define EVENT_UNIT_HERO_REVIVE_FINISH			ConvertUnitEvent(83)

#define EVENT_UNIT_SUMMON						ConvertUnitEvent(84)

#define EVENT_UNIT_DROP_ITEM					ConvertUnitEvent(85)
#define EVENT_UNIT_PICKUP_ITEM					ConvertUnitEvent(86)
#define EVENT_UNIT_USE_ITEM						ConvertUnitEvent(87)

#define EVENT_UNIT_LOADED						ConvertUnitEvent(88)

#define EVENT_WIDGET_DEATH						ConvertWidgetEvent(89)

#define EVENT_DIALOG_BUTTON_CLICK				ConvertDialogEvent(90)
#define EVENT_DIALOG_CLICK						ConvertDialogEvent(91)

//===================================================
// Frozen Throne Expansion Events
// Need to be added here to preserve compat
//===================================================

//===================================================
// For use with TriggerRegisterGameEvent    
//===================================================
#define	EVENT_GAME_LOADED						ConvertGameEvent(256)
#define	EVENT_GAME_TOURNAMENT_FINISH_SOON		ConvertGameEvent(257)
#define	EVENT_GAME_TOURNAMENT_FINISH_NOW		ConvertGameEvent(258)
#define	EVENT_GAME_SAVE							ConvertGameEvent(259)

//===================================================
// For use with TriggerRegisterPlayerEvent
//===================================================
#define EVENT_PLAYER_ARROW_LEFT_DOWN			ConvertPlayerEvent(261)
#define EVENT_PLAYER_ARROW_LEFT_UP				ConvertPlayerEvent(262)
#define EVENT_PLAYER_ARROW_RIGHT_DOWN			ConvertPlayerEvent(263)
#define EVENT_PLAYER_ARROW_RIGHT_UP				ConvertPlayerEvent(264)
#define EVENT_PLAYER_ARROW_DOWN_DOWN			ConvertPlayerEvent(265)
#define EVENT_PLAYER_ARROW_DOWN_UP				ConvertPlayerEvent(266)
#define EVENT_PLAYER_ARROW_UP_DOWN				ConvertPlayerEvent(267)
#define EVENT_PLAYER_ARROW_UP_UP				ConvertPlayerEvent(268)

//===================================================
// For use with TriggerRegisterPlayerUnitEvent
//===================================================
#define EVENT_PLAYER_UNIT_SELL					ConvertPlayerUnitEvent(269)
#define EVENT_PLAYER_UNIT_CHANGE_OWNER			ConvertPlayerUnitEvent(270)
#define EVENT_PLAYER_UNIT_SELL_ITEM				ConvertPlayerUnitEvent(271)
#define EVENT_PLAYER_UNIT_SPELL_CHANNEL			ConvertPlayerUnitEvent(272)
#define EVENT_PLAYER_UNIT_SPELL_CAST			ConvertPlayerUnitEvent(273)
#define EVENT_PLAYER_UNIT_SPELL_EFFECT			ConvertPlayerUnitEvent(274)
#define EVENT_PLAYER_UNIT_SPELL_FINISH			ConvertPlayerUnitEvent(275)
#define EVENT_PLAYER_UNIT_SPELL_ENDCAST			ConvertPlayerUnitEvent(276)
#define EVENT_PLAYER_UNIT_PAWN_ITEM				ConvertPlayerUnitEvent(277)

//===================================================
// For use with TriggerRegisterUnitEvent
//===================================================
#define EVENT_UNIT_SELL							ConvertUnitEvent(286)
#define EVENT_UNIT_CHANGE_OWNER					ConvertUnitEvent(287)
#define EVENT_UNIT_SELL_ITEM					ConvertUnitEvent(288)
#define EVENT_UNIT_SPELL_CHANNEL				ConvertUnitEvent(289)
#define EVENT_UNIT_SPELL_CAST					ConvertUnitEvent(290)
#define EVENT_UNIT_SPELL_EFFECT					ConvertUnitEvent(291)
#define EVENT_UNIT_SPELL_FINISH					ConvertUnitEvent(292)
#define EVENT_UNIT_SPELL_ENDCAST				ConvertUnitEvent(293)
#define EVENT_UNIT_PAWN_ITEM					ConvertUnitEvent(294)

//===================================================
// Limit Event API constants    
// variable, player state, game state, and unit
// state events
//===================================================
#define LESS_THAN								ConvertLimitOp(0)
#define LESS_THAN_OR_EQUAL						ConvertLimitOp(1)
#define EQUAL									ConvertLimitOp(2)
#define GREATER_THAN_OR_EQUAL					ConvertLimitOp(3)
#define GREATER_THAN							ConvertLimitOp(4)
#define NOT_EQUAL								ConvertLimitOp(5)

//===================================================
// Unit Type Constants for use with IsUnitType()
//===================================================
#define UNIT_TYPE_HERO							ConvertUnitType(0)
#define UNIT_TYPE_DEAD							ConvertUnitType(1)
#define UNIT_TYPE_STRUCTURE						ConvertUnitType(2)

#define UNIT_TYPE_FLYING						ConvertUnitType(3)
#define UNIT_TYPE_GROUND						ConvertUnitType(4)

#define UNIT_TYPE_ATTACKS_FLYING				ConvertUnitType(5)
#define UNIT_TYPE_ATTACKS_GROUND				ConvertUnitType(6)

#define UNIT_TYPE_MELEE_ATTACKER				ConvertUnitType(7)
#define UNIT_TYPE_RANGED_ATTACKER				ConvertUnitType(8)

#define UNIT_TYPE_GIANT							ConvertUnitType(9)
#define UNIT_TYPE_SUMMONED						ConvertUnitType(10)
#define UNIT_TYPE_STUNNED						ConvertUnitType(11)
#define UNIT_TYPE_PLAGUED						ConvertUnitType(12)
#define UNIT_TYPE_SNARED						ConvertUnitType(13)

#define UNIT_TYPE_UNDEAD						ConvertUnitType(14)
#define UNIT_TYPE_MECHANICAL					ConvertUnitType(15)
#define UNIT_TYPE_PEON							ConvertUnitType(16)
#define UNIT_TYPE_SAPPER						ConvertUnitType(17)
#define UNIT_TYPE_TOWNHALL						ConvertUnitType(18)
#define UNIT_TYPE_ANCIENT						ConvertUnitType(19)

#define UNIT_TYPE_TAUREN						ConvertUnitType(20)
#define UNIT_TYPE_POISONED						ConvertUnitType(21)
#define UNIT_TYPE_POLYMORPHED					ConvertUnitType(22)
#define UNIT_TYPE_SLEEPING						ConvertUnitType(23)
#define UNIT_TYPE_RESISTANT						ConvertUnitType(24)
#define UNIT_TYPE_ETHEREAL						ConvertUnitType(25)
#define UNIT_TYPE_MAGIC_IMMUNE					ConvertUnitType(26)

//=========================================
// Unit Type Constants for use with
// ChooseRandomItemEx()
//=========================================
#define ITEM_TYPE_PERMANENT						ConvertItemType(0)
#define ITEM_TYPE_CHARGED						ConvertItemType(1)
#define ITEM_TYPE_POWERUP						ConvertItemType(2)
#define ITEM_TYPE_ARTIFACT						ConvertItemType(3)
#define ITEM_TYPE_PURCHASABLE					ConvertItemType(4)
#define ITEM_TYPE_CAMPAIGN						ConvertItemType(5)
#define ITEM_TYPE_MISCELLANEOUS					ConvertItemType(6)
#define ITEM_TYPE_UNKNOWN						ConvertItemType(7)
#define ITEM_TYPE_ANY							ConvertItemType(8)

// Deprecated, should use ITEM_TYPE_POWERUP
#define ITEM_TYPE_TOME							ConvertItemType(2)

//=========================================
// Animatable Camera Fields
//=========================================
#define CAMERA_FIELD_TARGET_DISTANCE			ConvertCameraField(0)
#define CAMERA_FIELD_FARZ						ConvertCameraField(1)
#define CAMERA_FIELD_ANGLE_OF_ATTACK			ConvertCameraField(2)
#define CAMERA_FIELD_FIELD_OF_VIEW				ConvertCameraField(3)
#define CAMERA_FIELD_ROLL						ConvertCameraField(4)
#define CAMERA_FIELD_ROTATION					ConvertCameraField(5)
#define CAMERA_FIELD_ZOFFSET					ConvertCameraField(6)

#define BLEND_MODE_NONE							ConvertBlendMode(0)
#define BLEND_MODE_DONT_CARE					ConvertBlendMode(0)
#define BLEND_MODE_KEYALPHA						ConvertBlendMode(1)
#define BLEND_MODE_BLEND						ConvertBlendMode(2)
#define BLEND_MODE_ADDITIVE						ConvertBlendMode(3)
#define BLEND_MODE_MODULATE						ConvertBlendMode(4)
#define BLEND_MODE_MODULATE_2X					ConvertBlendMode(5)

#define RARITY_FREQUENT							ConvertRarityControl(0)
#define RARITY_RARE								ConvertRarityControl(1)

#define TEXMAP_FLAG_NONE						ConvertTexMapFlags(0)
#define TEXMAP_FLAG_WRAP_U						ConvertTexMapFlags(1)
#define TEXMAP_FLAG_WRAP_V						ConvertTexMapFlags(2)
#define TEXMAP_FLAG_WRAP_UV						ConvertTexMapFlags(3)

#define FOG_OF_WAR_MASKED						ConvertFogState(1)
#define FOG_OF_WAR_FOGGED						ConvertFogState(2)
#define FOG_OF_WAR_VISIBLE						ConvertFogState(4)

//=========================================
// Camera Margin constants for use with
// GetCameraMargin
//=========================================
const integer			CAMERA_MARGIN_LEFT = 0;
const integer			CAMERA_MARGIN_RIGHT = 1;
const integer			CAMERA_MARGIN_TOP = 2;
const integer			CAMERA_MARGIN_BOTTOM = 3;

//=========================================
// Effect API constants
//=========================================
#define EFFECT_TYPE_EFFECT						ConvertEffectType(0)
#define EFFECT_TYPE_TARGET						ConvertEffectType(1)
#define EFFECT_TYPE_CASTER						ConvertEffectType(2)
#define EFFECT_TYPE_SPECIAL						ConvertEffectType(3)
#define EFFECT_TYPE_AREA_EFFECT					ConvertEffectType(4)
#define EFFECT_TYPE_MISSILE						ConvertEffectType(5)
#define EFFECT_TYPE_LIGHTNING					ConvertEffectType(6)

#define SOUND_TYPE_EFFECT						ConvertSoundType(0)
#define SOUND_TYPE_EFFECT_LOOPED				ConvertSoundType(1)
