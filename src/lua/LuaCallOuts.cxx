
#include "common.h"

// interface header
#include "LuaCallOuts.h"

// system headers
#include <sstream> // for ReadImage
#include <string.h>
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

// common headers
#include "AnsiCodes.h"
#include "Bundle.h"
#include "BundleMgr.h"
#include "BzVFS.h"
#include "BzfDisplay.h"
#include "BzfWindow.h"
#include "CacheManager.h"
#include "CollisionManager.h"
#include "CommandManager.h"
#include "GameTime.h"
#include "GfxBlock.h"
#include "KeyManager.h"
#include "MapInfo.h"
#include "MediaFile.h"
#include "OpenGLLight.h"
#include "SceneRenderer.h"
#include "Team.h"
#include "TextUtils.h"
#include "TimeKeeper.h"
#include "bzfio.h"
#include "bz_md5.h"
#include "version.h"

// bzflag headers
#include "../bzflag/ClientFlag.h"
#include "../bzflag/ControlPanel.h"
#include "../bzflag/LocalCommand.h"
#include "../bzflag/LocalPlayer.h"
#include "../bzflag/MainWindow.h"
#include "../bzflag/RadarRenderer.h"
#include "../bzflag/Roaming.h"
#include "../bzflag/Roster.h"
#include "../bzflag/ScoreboardRenderer.h"
#include "../bzflag/ServerLink.h"
#include "../bzflag/World.h"
#include "../bzflag/playing.h"
#include "../bzflag/sound.h"

// mediafile headers
#include "../mediafile/PNGImageFile.h"

// local headers
#include "LuaDouble.h"
#include "LuaInclude.h"
#include "LuaHandle.h"
#include "LuaHashString.h"
#include "LuaFontTexture.h"
#include "LuaZip.h"

// LuaHandle headers
#include "LuaUser.h"


//============================================================================//
//============================================================================//

bool LuaCallOuts::PushEntries(lua_State* L)
{
	const bool fullRead = L2H(L)->HasFullRead();

	PUSH_LUA_CFUNC(L, GetBzLuaVersion);
	PUSH_LUA_CFUNC(L, GetClientVersion);
	PUSH_LUA_CFUNC(L, GetProtocolVersion);

	PUSH_LUA_CFUNC(L, Print);
	PUSH_LUA_CFUNC(L, Debug);
	PUSH_LUA_CFUNC(L, GetDebugLevel);

	PUSH_LUA_CFUNC(L, CalcMD5);
	PUSH_LUA_CFUNC(L, StripAnsiCodes);
	PUSH_LUA_CFUNC(L, ExpandColorString);
	PUSH_LUA_CFUNC(L, LocalizeString);
	PUSH_LUA_CFUNC(L, GetCacheFilePath);

	PUSH_LUA_CFUNC(L, GetConsoleMessages);
	PUSH_LUA_CFUNC(L, GetConsoleMessageCount);

	PUSH_LUA_CFUNC(L, GetGameInfo);
	PUSH_LUA_CFUNC(L, GetWorldInfo);

	PUSH_LUA_CFUNC(L, GetServerAddress);
	PUSH_LUA_CFUNC(L, GetServerIP);
	PUSH_LUA_CFUNC(L, GetServerPort);
	PUSH_LUA_CFUNC(L, GetServerDescription);

	PUSH_LUA_CFUNC(L, GetWind);
	PUSH_LUA_CFUNC(L, GetLights);

	PUSH_LUA_CFUNC(L, GetWorldHash);

	PUSH_LUA_CFUNC(L, SendLuaData);

	PUSH_LUA_CFUNC(L, SendCommand);

	PUSH_LUA_CFUNC(L, BlockControls);

	PUSH_LUA_CFUNC(L, PlaySound);

	PUSH_LUA_CFUNC(L, ReadImageData);
	PUSH_LUA_CFUNC(L, ReadImageFile);

	PUSH_LUA_CFUNC(L, GetViewType);

	PUSH_LUA_CFUNC(L, GetKeyToCmds);
	PUSH_LUA_CFUNC(L, GetCmdToKeys);

	PUSH_LUA_CFUNC(L, GetRoamInfo);
	PUSH_LUA_CFUNC(L, SetRoamInfo);

	PUSH_LUA_CFUNC(L, GetScreenGeometry);
	PUSH_LUA_CFUNC(L, GetWindowGeometry);
	PUSH_LUA_CFUNC(L, GetViewGeometry);
	PUSH_LUA_CFUNC(L, GetRadarGeometry);
	PUSH_LUA_CFUNC(L, GetRadarRange);

	PUSH_LUA_CFUNC(L, GetVisualExtents);
	PUSH_LUA_CFUNC(L, GetLengthPerPixel);

	PUSH_LUA_CFUNC(L, SetCameraView);
	PUSH_LUA_CFUNC(L, SetCameraProjection);
	PUSH_LUA_CFUNC(L, GetCameraPosition);
	PUSH_LUA_CFUNC(L, GetCameraDirection);
	PUSH_LUA_CFUNC(L, GetCameraUp);
	PUSH_LUA_CFUNC(L, GetCameraRight);
	PUSH_LUA_CFUNC(L, GetCameraMatrix);
	PUSH_LUA_CFUNC(L, GetFrustumPlane);

	PUSH_LUA_CFUNC(L, NotifyStyleChange);

	PUSH_LUA_CFUNC(L, GetSun);

	PUSH_LUA_CFUNC(L, GetTime);
	PUSH_LUA_CFUNC(L, GetGameTime);
	PUSH_LUA_CFUNC(L, GetTimer);
	PUSH_LUA_CFUNC(L, DiffTimers);

	PUSH_LUA_CFUNC(L, GetTeamList);
	PUSH_LUA_CFUNC(L, GetTeamPlayers);
	PUSH_LUA_CFUNC(L, GetTeamName);
	PUSH_LUA_CFUNC(L, GetTeamLongName);
	PUSH_LUA_CFUNC(L, GetTeamCount);
	PUSH_LUA_CFUNC(L, GetTeamScore);
	PUSH_LUA_CFUNC(L, GetTeamColor);
	PUSH_LUA_CFUNC(L, GetTeamRadarColor);
	PUSH_LUA_CFUNC(L, GetTeamsAreEnemies);
	PUSH_LUA_CFUNC(L, GetPlayersAreEnemies);

	PUSH_LUA_CFUNC(L, GetMousePosition);
	PUSH_LUA_CFUNC(L, GetJoyPosition);
	PUSH_LUA_CFUNC(L, GetKeyModifiers);

	PUSH_LUA_CFUNC(L, WarpMouse);

	PUSH_LUA_CFUNC(L, MakeFont);

	PUSH_LUA_CFUNC(L, GetLocalPlayer);
	PUSH_LUA_CFUNC(L, GetLocalPlayerTarget);
	PUSH_LUA_CFUNC(L, GetLocalTeam);
	PUSH_LUA_CFUNC(L, GetRabbitPlayer);
	PUSH_LUA_CFUNC(L, GetAntidotePosition);

	PUSH_LUA_CFUNC(L, GetGfxBlock);
	PUSH_LUA_CFUNC(L, SetGfxBlock);
	PUSH_LUA_CFUNC(L, GetPlayerGfxBlock);
	PUSH_LUA_CFUNC(L, SetPlayerGfxBlock);
	PUSH_LUA_CFUNC(L, GetFlagGfxBlock);
	PUSH_LUA_CFUNC(L, SetFlagGfxBlock);
	PUSH_LUA_CFUNC(L, GetShotGfxBlock);
	PUSH_LUA_CFUNC(L, SetShotGfxBlock);

	PUSH_LUA_CFUNC(L, GetPlayerList);
	PUSH_LUA_CFUNC(L, GetPlayerName);
	PUSH_LUA_CFUNC(L, GetPlayerType);
	PUSH_LUA_CFUNC(L, GetPlayerTeam);
	PUSH_LUA_CFUNC(L, GetPlayerFlagType);
	PUSH_LUA_CFUNC(L, GetPlayerScore);
	PUSH_LUA_CFUNC(L, GetPlayerMotto);
	PUSH_LUA_CFUNC(L, GetPlayerAutoPilot);
	if (fullRead) {
		PUSH_LUA_CFUNC(L, GetPlayerCustomData);
		PUSH_LUA_CFUNC(L, GetPlayerFlag);
		PUSH_LUA_CFUNC(L, GetPlayerShots);
		PUSH_LUA_CFUNC(L, GetPlayerState);
		PUSH_LUA_CFUNC(L, GetPlayerStateBits);
		PUSH_LUA_CFUNC(L, GetPlayerPosition);
		PUSH_LUA_CFUNC(L, GetPlayerRotation);
		PUSH_LUA_CFUNC(L, GetPlayerDirection);
		PUSH_LUA_CFUNC(L, GetPlayerVelocity);
		PUSH_LUA_CFUNC(L, GetPlayerAngVel);
		PUSH_LUA_CFUNC(L, GetPlayerDimensions);
		PUSH_LUA_CFUNC(L, GetPlayerPhysicsDriver);
		PUSH_LUA_CFUNC(L, GetPlayerDesiredSpeed);
		PUSH_LUA_CFUNC(L, GetPlayerDesiredAngVel);
		PUSH_LUA_CFUNC(L, GetPlayerExplodeTime);
	}
	PUSH_LUA_CFUNC(L, IsPlayerAdmin);
	PUSH_LUA_CFUNC(L, IsPlayerVerified);
	PUSH_LUA_CFUNC(L, IsPlayerRegistered);
	PUSH_LUA_CFUNC(L, IsPlayerHunted);

	if (fullRead) {
		PUSH_LUA_CFUNC(L, GetFlagList);
		PUSH_LUA_CFUNC(L, GetFlagName);
		PUSH_LUA_CFUNC(L, GetFlagType);
		PUSH_LUA_CFUNC(L, GetFlagShotType);
		PUSH_LUA_CFUNC(L, GetFlagQuality);
		PUSH_LUA_CFUNC(L, GetFlagEndurance);
		PUSH_LUA_CFUNC(L, GetFlagTeam);
		PUSH_LUA_CFUNC(L, GetFlagOwner);
		PUSH_LUA_CFUNC(L, GetFlagState);
		PUSH_LUA_CFUNC(L, GetFlagPosition);
	}

	if (fullRead) {
		PUSH_LUA_CFUNC(L, GetShotList);
		PUSH_LUA_CFUNC(L, GetShotType);
		PUSH_LUA_CFUNC(L, GetShotFlagType);
		PUSH_LUA_CFUNC(L, GetShotPlayer);
		PUSH_LUA_CFUNC(L, GetShotTeam);
		PUSH_LUA_CFUNC(L, GetShotPosition);
		PUSH_LUA_CFUNC(L, GetShotVelocity);
		PUSH_LUA_CFUNC(L, GetShotLeftTime);
		PUSH_LUA_CFUNC(L, GetShotLifeTime);
		PUSH_LUA_CFUNC(L, GetShotReloadTime);
	}

	LuaZip::PushEntries(L);

#ifdef HAVE_UNISTD_H
	PUSH_LUA_CFUNC(L, ReadStdin);
#endif

	return true;
}


//============================================================================//
//============================================================================//

static inline const Player* ParsePlayer(lua_State* L, int index)
{
	const int playerID = luaL_checkint(L, index);
	return lookupPlayer((PlayerId)playerID);
}


static inline const ClientFlag* ParseFlag(lua_State* L, int index)
{
	World* world = World::getWorld();
	if (world == NULL) {
		return NULL;
	}
	const int flagID = luaL_checkint(L, index);
	if ((flagID < 0) || (flagID >= world->getMaxFlags())) {
		return NULL;
	}
	return (const ClientFlag*)&(world->getFlag(flagID));
}


static inline const ShotPath* ParseShot(lua_State* L, int index)
{
	const uint32_t fullID   = luaL_checkint(L, index);
	const PlayerId playerID = (fullID >> 16);
	const uint16_t shotID   = fullID & 0xffff;

	const Player* player = lookupPlayer(playerID);
	if (player == NULL) {
		return NULL;
	}

	const ShotPath* shot = player->getShot(shotID);
	if ((shot == NULL) || shot->isExpired()) {
		return NULL;
	}

	return shot;
}


static const map<string, TeamColor>& GetTeamNameMap()
{
	static map<string, TeamColor> teamNames;
	if (teamNames.empty()) {
		teamNames["automatic"] = AutomaticTeam;
		teamNames["rogue"]     = RogueTeam;
		teamNames["red"]       = RedTeam;
		teamNames["green"]     = GreenTeam;
		teamNames["blue"]      = BlueTeam;
		teamNames["purple"]    = PurpleTeam;
		teamNames["observer"]  = ObserverTeam;
		teamNames["rabbit"]    = RabbitTeam;
		teamNames["hunter"]    = HunterTeam;
	}
	return teamNames;
}


static inline TeamColor ParseTeam(lua_State* L, int index)
{
	if (lua_israwstring(L, index)) {
		const string teamName = lua_tostring(L, index);
		const map<string, TeamColor>& teamNames = GetTeamNameMap();
		map<string, TeamColor>::const_iterator it = teamNames.find(teamName);
		if (it == teamNames.end()) {
			return NoTeam;
		}
		return it->second;
	}

	TeamColor teamNum = (TeamColor)luaL_checkint(L, index);
	if ((teamNum < AutomaticTeam) || (teamNum >= NumTeams)) {
		return NoTeam;
	}

	return teamNum;
}


//============================================================================//
//============================================================================//

static inline int PushShot(lua_State* L, const ShotPath* shot, int count)
{
	count++;
	lua_pushinteger(L, count);
	const uint32_t shotID = (shot->getPlayer() << 16) | shot->getShotId();
	lua_pushinteger(L, shotID);
	lua_rawset(L, -3);
	return count;
}


//============================================================================//
//============================================================================//

int LuaCallOuts::GetBzLuaVersion(lua_State* L)
{
	lua_pushliteral(L, "0.1");
	return 1;
}


int LuaCallOuts::GetClientVersion(lua_State* L)
{
	lua_pushstring(L, getAppVersion());
	return 1;
}


int LuaCallOuts::GetProtocolVersion(lua_State* L)
{
	lua_pushstring(L, getProtocolVersion());
	return 1;
}


//============================================================================//

int LuaCallOuts::Print(lua_State* L)
{
	if (controlPanel == NULL) {
		return 0;
	}
	ControlPanel::MessageModes mode = ControlPanel::MessageMisc;
	int msgArg = 1;
	if (lua_israwnumber(L, msgArg)) {
		mode = (ControlPanel::MessageModes)lua_toint(L, msgArg);
		msgArg++;
	}
	const char* msg = luaL_checkstring(L, msgArg);
	controlPanel->addMessage(msg, mode);
	return 0;
}


int LuaCallOuts::Debug(lua_State* L)
{
	int level = 0;
	int msgArg = 1;
	if (lua_israwnumber(L, msgArg)) {
		level = lua_toint(L, msgArg);
		msgArg++;
	}
	const char* msg = luaL_checkstring(L, msgArg);
	logDebugMessage(level, msg);
	return 0;
}


int LuaCallOuts::GetDebugLevel(lua_State* L)
{
	lua_pushinteger(L, debugLevel);
	return 1;
}


int LuaCallOuts::LocalizeString(lua_State* L)
{
	const char* text = luaL_checkstring(L, 1);
	Bundle* bundle = BundleMgr::getCurrentBundle();
	if (bundle == NULL) {
		lua_settop(L, 1);
		lua_pushboolean(L, false);
		return 2;
	}
	lua_pushstdstring(L, bundle->getLocalString(text));
	lua_pushboolean(L, true);
	return 2;
}


//============================================================================//

int LuaCallOuts::CalcMD5(lua_State* L)
{
	MD5 md5;
	for (int arg = 1; lua_israwstring(L, arg); arg++) {
		size_t len;
		const char* text = luaL_checklstring(L, arg, &len);
		md5.update((const unsigned char*)text, len);
	}
	md5.finalize();
	lua_pushstdstring(L, md5.hexdigest());
	return 1;
}


int LuaCallOuts::StripAnsiCodes(lua_State* L)
{
	size_t len;
	const char* text = luaL_checklstring(L, 1, &len);
	lua_pushstring(L, stripAnsiCodes(text));
	return 1;
}


int LuaCallOuts::ExpandColorString(lua_State* L)
{
	size_t len;
	const char* text = luaL_checklstring(L, 1, &len);
	lua_pushstdstring(L, TextUtils::unescape_colors(text));
	return 1;
}


int LuaCallOuts::GetCacheFilePath(lua_State* L)
{
	const char* text = luaL_checkstring(L, 1);
	lua_pushstdstring(L, CACHEMGR.getLocalName(text));
	return 1;
}


//============================================================================//

int LuaCallOuts::GetConsoleMessages(lua_State* L)
{
	if (controlPanel == NULL) {
		return 0;
	}

	const ControlPanel::MessageModes mode =
		(ControlPanel::MessageModes)luaL_checkint(L, 1);

	const std::deque<ControlPanelMessage>* messages =
		controlPanel->getModeMessages(mode);
	if (messages == NULL) {
		return 0;
	}

	const size_t msgSize = messages->size();
	size_t count = (size_t)luaL_optint(L, 2, (int)msgSize);
	if (count > msgSize) {
		count = msgSize;
	}

	const size_t start = msgSize - count;

	lua_createtable(L, count, 0);
	int index = 0;
	for (size_t m = start; m < msgSize; m++) {
		index++;
		const ControlPanelMessage& msg = (*messages)[m];
		lua_pushlstring(L, msg.string.data(), msg.string.size());
		lua_rawseti(L, -2, index);
	}

	return 1;
}


int LuaCallOuts::GetConsoleMessageCount(lua_State* L)
{
	if (controlPanel == NULL) {
		return 0;
	}

	const ControlPanel::MessageModes mode =
		(ControlPanel::MessageModes)luaL_checkint(L, 1);

	const std::deque<ControlPanelMessage>* messages =
		controlPanel->getModeMessages(mode);
	if (messages == NULL) {
		return 0;
	}

	lua_pushinteger(L, controlPanel->getModeMessageCount(mode));
	return 1;
}


//============================================================================//

int LuaCallOuts::GetGameInfo(lua_State* L)
{
	lua_newtable(L);

	World* world = World::getWorld();
	if (world == NULL) {
		return 1;
	}

	HSTR_PUSH_INT(L,  "type",          world->getGameType());
	HSTR_PUSH_BOOL(L, "teams",         world->allowTeams());
	HSTR_PUSH_BOOL(L, "teamKills",     world->allowTeamKills());
	HSTR_PUSH_BOOL(L, "teamFlags",     world->allowTeamFlags());
	HSTR_PUSH_BOOL(L, "superFlags",    world->allowSuperFlags());
	HSTR_PUSH_BOOL(L, "ricochet",      world->allShotsRicochet());
	HSTR_PUSH_BOOL(L, "rabbit",        world->allowRabbit());
	HSTR_PUSH_BOOL(L, "handicap",      world->allowHandicap());
	HSTR_PUSH_BOOL(L, "antidote",      world->allowAntidote());
	if (world->allowShakeWins()) {
		HSTR_PUSH_INT(L, "shakeWins",    world->getFlagShakeWins());
	}
	if (world->allowShakeTimeout()) {
		HSTR_PUSH_NUMBER(L, "shakeTime", world->getFlagShakeTimeout());
	}
	HSTR_PUSH_INT(L, "maxFlags",       world->getMaxFlags());
	HSTR_PUSH_INT(L, "maxShots",       world->getMaxShots());
	HSTR_PUSH_INT(L, "maxPlayers",     world->getMaxPlayers());
	return 1;
}


int LuaCallOuts::GetWorldInfo(lua_State* L)
{
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	const vector<string>* entries = NULL;

	if (!lua_israwstring(L, 1)) {
		entries = &world->getMapInfo().getVec();
	}
	else {
		const char* key = lua_tostring(L, 1);
		const MapInfo::InfoMap& infoMap = world->getMapInfo().getMap();
		MapInfo::InfoMap::const_iterator it = infoMap.find(key);
		if (it != infoMap.end()) {
			entries = &it->second;
		}
	}

	if (entries == NULL) {
		lua_pushboolean(L, false);
		return 1;
	}

	lua_createtable(L, entries->size(), 0);
	for (size_t i = 0; i < entries->size(); i++) {
		lua_pushstdstring(L, (*entries)[i]);
		lua_rawseti(L, -2, i + 1);
	}
	return 1;
}


int LuaCallOuts::GetServerAddress(lua_State* /*L*/) // FIXME
{
	return 0;
}


int LuaCallOuts::GetServerIP(lua_State* /*L*/) // FIXME
{
	return 0;
}


int LuaCallOuts::GetServerPort(lua_State* /*L*/) // FIXME
{
	return 0;
}


int LuaCallOuts::GetServerDescription(lua_State* /*L*/) // FIXME
{
	return 0;
}


//============================================================================//

int LuaCallOuts::GetWind(lua_State* L)
{
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}

	float pos[3];
	pos[0] = luaL_optfloat(L, 1, 0.0f);
	pos[1] = luaL_optfloat(L, 1, 0.0f);
	pos[2] = luaL_optfloat(L, 1, 0.0f);
	float wind[3];
	world->getWind(wind, pos);

	lua_pushnumber(L, wind[0]);
	lua_pushnumber(L, wind[1]);
	lua_pushnumber(L, wind[2]);

	return 3;
}


int LuaCallOuts::GetLights(lua_State* L)
{
	lua_newtable(L);

	const int numAllLights = RENDERER.getNumAllLights();
	for (int li = 0; li < numAllLights; li++) {
		const OpenGLLight& light = RENDERER.getLight(li);
		lua_newtable(L);

		if (light.getOnlyReal())   { HSTR_PUSH_BOOL(L, "onlyReal", true);   }
		if (light.getOnlyGround()) { HSTR_PUSH_BOOL(L, "onlyGround", true); }

		HSTR_PUSH_NUMBER(L, "maxDist",    light.getMaxDist());
		HSTR_PUSH_NUMBER(L, "importance", light.getImportance());

		const float* pos = light.getPosition();
		lua_pushliteral(L, "pos");
		lua_createtable(L, 4, 0);
		lua_pushnumber(L, pos[0]); lua_rawseti(L, -2, 1);
		lua_pushnumber(L, pos[1]); lua_rawseti(L, -2, 2);
		lua_pushnumber(L, pos[2]); lua_rawseti(L, -2, 3);
		lua_pushnumber(L, pos[3]); lua_rawseti(L, -2, 4);
		lua_rawset(L, -3);

		const float* color = light.getColor();
		lua_pushliteral(L, "color");
		lua_createtable(L, 4, 0);
		lua_pushnumber(L, color[0]); lua_rawseti(L, -2, 1);
		lua_pushnumber(L, color[1]); lua_rawseti(L, -2, 2);
		lua_pushnumber(L, color[2]); lua_rawseti(L, -2, 3);
		lua_pushnumber(L, color[3]); lua_rawseti(L, -2, 4);
		lua_rawset(L, -3);

		const float* atten = light.getColor();
		lua_pushliteral(L, "atten");
		lua_createtable(L, 3, 0);
		lua_pushnumber(L, atten[0]); lua_rawseti(L, -2, 1);
		lua_pushnumber(L, atten[1]); lua_rawseti(L, -2, 2);
		lua_pushnumber(L, atten[2]); lua_rawseti(L, -2, 3);
		lua_rawset(L, -3);

		lua_rawseti(L, -2, li + 1);
	}

	return 1;
}


int LuaCallOuts::GetWorldHash(lua_State* L)
{
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	lua_pushstdstring(L, world->getMapHash());
	return 1;
}


//============================================================================//

int LuaCallOuts::SendLuaData(lua_State* L)
{
	const int myOrder = L2H(L)->GetOrder();
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank == NULL) {
		return 0;
	}
	if (serverLink == NULL) {
		return 0;
	}

	size_t len;
	const char* ptr = luaL_checklstring(L, 1, &len);
	const string data(ptr, len);

	const PlayerId dstPlayerID = (PlayerId)luaL_optint(L, 2, AllPlayers);
	const int16_t  dstScriptID =  (int16_t)luaL_optint(L, 3, 0);
	const uint8_t  statusBits  =  (uint8_t)luaL_optint(L, 4, 0);

	lua_pushboolean(L, serverLink->sendLuaData(myTank->getId(), myOrder,
	                                           dstPlayerID, dstScriptID,
	                                           statusBits, data));
	return 1;
}


int LuaCallOuts::SendCommand(lua_State* L) // FIXME -- removed for safety
{
	L = L;
/*
	const char* command = luaL_checkstring(L, 1);
	const bool local = lua_tobool(L, 2);
	if (local) {
		lua_pushboolean(L, LocalCommand::execute(command));
	} else {
		lua_pushstdstring(L, CMDMGR.run(command));
	}
	return 1;
*/
	return 0;
}


//============================================================================//

int LuaCallOuts::BlockControls(lua_State* L)
{
	if (!L2H(L)->HasInputCtrl()) {
		luaL_error(L, "this script can not block controls");
	}
	forceControls(true, 0.0f, 0.0f);
	return 0;
}


//============================================================================//

int LuaCallOuts::PlaySound(lua_State* L)
{
	int soundID = -1;
	if (lua_israwnumber(L, 1)) {
		soundID = lua_toint(L, 1);
	}
	else if (lua_israwstring(L, 1)) {
		soundID = SOUNDSYSTEM.getID(lua_tostring(L, 1));
	}
	if (soundID < 0) {
		lua_pushboolean(L, false);
		return 1;
	}

	bool local = true;
	bool repeated = false;
	bool important = false;
	float volume = 1.0f; // currently unused
	float pos[3] = { 0.0f, 0.0f, 0.0f };

	if (lua_istable(L, 2)) {
		lua_getfield(L, 2, "volume"); // NOTE -- not used
		if (lua_israwnumber(L, -1)) {
			volume = lua_tonumber(L, -1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 2, "important");
		important = lua_isboolean(L, -1) && lua_tobool(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, 2, "repeated");
		repeated = lua_isboolean(L, -1) && lua_tobool(L, -1);
		lua_pop(L, 1);

		const char* posNames[3] = { "px", "py", "pz" };
		for (int a = 0; a < 3; a++) {
			lua_getfield(L, 2, posNames[a]);
			if (lua_israwnumber(L, -1)) {
				pos[a] = lua_tonumber(L, -1);
				local = false;
			}
			lua_pop(L, 1);
		}
	}

	SOUNDSYSTEM.play(soundID, local ? NULL : pos, important, local, repeated);

	return 0;
}


//============================================================================//

static int PushImageInfo(lua_State* L, PNGImageFile& image)
{
	if (!image.isOpen()) {
		return 0;
	}

	lua_pushinteger(L, image.getWidth());
	lua_pushinteger(L, image.getHeight());
	lua_pushinteger(L, image.getNumChannels());

	return 3;
}


static int PushImageData(lua_State* L, PNGImageFile& image)
{
	if (!image.isOpen()) {
		return 0;
	}

	const int width = image.getWidth();
	const int height = image.getHeight();
	const int channels = image.getNumChannels();

	const int bufSize = width * height * channels;
	char* buf = new char[bufSize];
	if (!image.read(buf)) {
		delete[] buf;
		return 0;
	}

	lua_pushinteger(L, width);
	lua_pushinteger(L, height);
	lua_pushinteger(L, channels);
	lua_pushlstring(L, buf, bufSize);

	delete[] buf;

	return 4;
}


int LuaCallOuts::ReadImageData(lua_State* L)
{
	size_t inLen;
	const char* inData = luaL_checklstring(L, 1, &inLen);
	const bool infoOnly = lua_isboolean(L, 2) && lua_tobool(L, 2);

	std::istringstream iss(string(inData, inLen));
	PNGImageFile image(&iss);

	if (infoOnly) {
		return PushImageInfo(L, image);
	}
	return PushImageData(L, image);
}


int LuaCallOuts::ReadImageFile(lua_State* L)
{
	const char* path = luaL_checkstring(L, 1);

	const LuaHandle* lh = L2H(L);
	string modes = lh->GetFSRead();
	bool infoOnly = false;
	if (!lua_israwstring(L, 2)) {
		infoOnly = lua_isboolean(L, 2) && lua_tobool(L, 2);
	}
	else {
		modes = lua_tostring(L, 2); // wanted
		modes = BzVFS::allowModes(modes, lh->GetFSReadAll().c_str());
		infoOnly = lua_isboolean(L, 3) && lua_tobool(L, 3);
	}

	string data;
	if (!bzVFS.readFile(path, modes, data)) {
		return 0;
	}

	std::istringstream iss(data);
	PNGImageFile image(&iss);

	if (infoOnly) {
		return PushImageInfo(L, image);
	}
	return PushImageData(L, image);
}


//============================================================================//

int LuaCallOuts::GetViewType(lua_State* L)
{
	switch (RENDERER.getViewType()) {
		case SceneRenderer::Normal:       { HSTR_PUSH(L, "normal");       break; }
		case SceneRenderer::Stereo:       { HSTR_PUSH(L, "stereo");       break; }
		case SceneRenderer::Stacked:      { HSTR_PUSH(L, "stacked");      break; }
		case SceneRenderer::ThreeChannel: { HSTR_PUSH(L, "threeChannel"); break; }
		case SceneRenderer::Anaglyph:     { HSTR_PUSH(L, "anaglyph");     break; }
		case SceneRenderer::Interlaced:   { HSTR_PUSH(L, "interlaced");   break; }
		default: {
			HSTR_PUSH(L, "unknown");
		}
	}
	return 1;
}


int LuaCallOuts::GetKeyToCmds(lua_State* L)
{
	const string keyString = luaL_checkstring(L, 1);
	BzfKeyEvent keyEvent;
	if (!KEYMGR.stringToKeyEvent(keyString, keyEvent)) {
		return 0;
	}
	const bool press = !lua_isboolean(L, 2) || lua_tobool(L, 2);
	const string command = KEYMGR.get(keyEvent, press);
	lua_pushstdstring(L, command);
	return 1;
}


int LuaCallOuts::GetCmdToKeys(lua_State* L)
{
	const string command = luaL_checkstring(L, 1);
	const bool press = !lua_isboolean(L, 2) || lua_tobool(L, 2);
	const vector<string> keys = KEYMGR.getKeysFromCommand(command, press);
	lua_createtable(L, keys.size(), 0);
	for (size_t i = 0; i < keys.size(); i++) {
		lua_pushstdstring(L, keys[i]);
		lua_rawseti(L, -2, i + 1);
	}
	return 1;
}


int LuaCallOuts::GetRoamInfo(lua_State* L)
{
	if (!ROAM.isRoaming()) {
		return 0;
	}

	lua_pushinteger(L, ROAM.getMode());
	const Roaming::RoamingCamera* cam = ROAM.getCamera();
	lua_pushnumber(L, cam->pos[0]);
	lua_pushnumber(L, cam->pos[1]);
	lua_pushnumber(L, cam->pos[2]);
	lua_pushnumber(L, cam->theta);
	lua_pushnumber(L, cam->phi);
	lua_pushnumber(L, cam->zoom);

	// push the target
	switch (ROAM.getMode()) {
		case Roaming::roamViewTrack:
		case Roaming::roamViewFollow:
		case Roaming::roamViewFP: {
			const Player* player = ROAM.getTargetTank();
			if (player != NULL) {
				lua_pushinteger(L, player->getId());
			}
			break;
		}
		case Roaming::roamViewFlag: {
			const ClientFlag* flag = (const ClientFlag*)ROAM.getTargetFlag();
			if (flag != NULL) {
				lua_pushinteger(L, flag->id);
			}
			break;
		}
		default: {
			break;
		}
	}

	lua_settop(L, 8);
	return 8;
}


int LuaCallOuts::SetRoamInfo(lua_State* L)
{
	if (!ROAM.isRoaming()) {
		return 0;
	}

	const Roaming::RoamingView mode = (Roaming::RoamingView)luaL_checkint(L, 1);
	if ((mode <= Roaming::roamViewDisabled) || (mode >= Roaming::roamViewCount)) {
		return 0;
	}

	ROAM.setMode(mode);

	switch (mode) {
		case Roaming::roamViewTrack:
		case Roaming::roamViewFollow:
		case Roaming::roamViewFP: {
			const int type = lua_type(L, 2);
			if ((type == LUA_TNUMBER) || (type == LUA_TBOOLEAN)) {
				const Player* player = ParsePlayer(L, 2);
				if (player == NULL) {
					lua_pushboolean(L, false);
					return 1;
				}

				if (type == LUA_TNUMBER) {
					ROAM.changeTarget(Roaming::explicitSet, player->getId());
				}
				else {
					const Roaming::RoamingTarget target =
						lua_tobool(L, 2) ? Roaming::next : Roaming::previous;
					ROAM.changeTarget(target, 0);
				}
			}
			lua_pushboolean(L, true);
			return 1;
		}
		case Roaming::roamViewFlag: {
			const int type = lua_type(L, 2);
			if ((type == LUA_TNUMBER) || (type == LUA_TBOOLEAN)) {
				const ClientFlag* flag = ParseFlag(L, 2);
				if (flag == NULL) {
					lua_pushboolean(L, false);
					return 1;
				}

				if (type == LUA_TNUMBER) {
					ROAM.changeTarget(Roaming::explicitSet, flag->id);
				}
				else {
					const Roaming::RoamingTarget target =
						lua_tobool(L, 2) ? Roaming::next : Roaming::previous;
					ROAM.changeTarget(target, 0);
				}
			}
			lua_pushboolean(L, true);
			return 1;
		}
		case Roaming::roamViewFree: {
			Roaming::RoamingCamera cam;
			memcpy(&cam, ROAM.getCamera(), sizeof(Roaming::RoamingCamera));
			cam.pos[0] = luaL_optfloat(L, 2, cam.pos[0]);
			cam.pos[1] = luaL_optfloat(L, 3, cam.pos[1]);
			cam.pos[2] = luaL_optfloat(L, 4, cam.pos[2]);
			cam.theta  = luaL_optfloat(L, 5, cam.theta);
			cam.phi    = luaL_optfloat(L, 6, cam.phi);
			cam.zoom   = luaL_optfloat(L, 7, cam.zoom);
			ROAM.setCamera(&cam);
			lua_pushboolean(L, true);
			return 1;
		}
		case Roaming::roamViewDisabled:
		case Roaming::roamViewCount: {
			return 0;
		}
	}

	return 0;
}


//============================================================================//

int LuaCallOuts::GetScreenGeometry(lua_State* L)
{
	BzfDisplay* dpy = getDisplay();
	if (dpy == NULL) {
		return 0;
	}
	lua_pushinteger(L, dpy->getWidth());
	lua_pushinteger(L, dpy->getHeight());
	lua_pushinteger(L, 0);
	lua_pushinteger(L, 0);
	return 4;
}


int LuaCallOuts::GetWindowGeometry(lua_State* L)
{
	MainWindow* window = getMainWindow();
	if (window == NULL) {
		return 0;
	}
	BzfDisplay* dpy = getDisplay();
	if (dpy == NULL) {
		return 0;
	}

	const int wsx = window->getWidth();
	const int wsy = window->getHeight();

	int wpx, wpy;
	BzfWindow* bzWindow = window->getWindow();
	bzWindow->getPosition(wpx, wpy);
	wpy = (dpy->getHeight() - (wpy + wsy));

	lua_pushinteger(L, wsx);
	lua_pushinteger(L, wsy);
	lua_pushinteger(L, wpx);
	lua_pushinteger(L, wpy);
	return 4;
}


int LuaCallOuts::GetViewGeometry(lua_State* L)
{
	MainWindow* window = getMainWindow();
	if (window == NULL) {
		return 0;
	}
	const int wh = window->getHeight();
	const int vh = window->getViewHeight();
	const int yOffset = (wh - vh);

	lua_pushinteger(L, window->getWidth());
	lua_pushinteger(L, window->getViewHeight());
	lua_pushinteger(L, window->getOriginX());
	lua_pushinteger(L, window->getOriginY() + yOffset);
	return 4;
}


int LuaCallOuts::GetRadarGeometry(lua_State* L)
{
	const RadarRenderer* radar = getRadarRenderer();
	if (radar == NULL) {
		return 0;
	}
	lua_pushinteger(L, radar->getWidth());
	lua_pushinteger(L, radar->getHeight());
	lua_pushinteger(L, radar->getX());
	lua_pushinteger(L, radar->getY());
	return 4;
}


int LuaCallOuts::GetRadarRange(lua_State* L)
{
	World* world = World::getWorld();
	const RadarRenderer* radar = getRadarRenderer();
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if ((world == NULL) || (radar == NULL) || (myTank == NULL)) {
		return 0;
	}
	lua_pushnumber(L, radar->getRange());
	return 1;
}


//============================================================================//

int LuaCallOuts::GetWorldExtents(lua_State* L)
{
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	const Extents& exts = COLLISIONMGR.getWorldExtents();
	lua_pushnumber(L, exts.mins[0]);
	lua_pushnumber(L, exts.mins[1]);
	lua_pushnumber(L, exts.mins[2]);
	lua_pushnumber(L, exts.maxs[0]);
	lua_pushnumber(L, exts.maxs[1]);
	lua_pushnumber(L, exts.maxs[2]);
	return 6;
}


int LuaCallOuts::GetVisualExtents(lua_State* L)
{
	const Extents* exts = RENDERER.getVisualExtents();
	if (exts == NULL) {
		return 0;
	}
	lua_pushnumber(L, exts->mins[0]);
	lua_pushnumber(L, exts->mins[1]);
	lua_pushnumber(L, exts->mins[2]);
	lua_pushnumber(L, exts->maxs[0]);
	lua_pushnumber(L, exts->maxs[1]);
	lua_pushnumber(L, exts->maxs[2]);
	return 6;
}


int LuaCallOuts::GetLengthPerPixel(lua_State* L)
{
	lua_pushnumber(L, RENDERER.getLengthPerPixel());
	return 1;
}


//============================================================================//

int LuaCallOuts::SetCameraView(lua_State* L)
{
	if (!L2H(L)->HasFullRead()) {
		return 0;
	}

	// get the defaults
	ViewFrustum& vf = RENDERER.getViewFrustum();
	const float* currPos = vf.getEye();
	const float* currDir = vf.getDirection();
	float pos[3] = { currPos[0], currPos[1], currPos[2] };
	float dir[3] = { currDir[0], currDir[1], currDir[2] };

	const int table = 1;
	if (!lua_istable(L, table)) {
		pos[0] = luaL_optfloat(L, 1, pos[0]);
		pos[1] = luaL_optfloat(L, 2, pos[1]);
		pos[2] = luaL_optfloat(L, 3, pos[2]);
		dir[0] = luaL_optfloat(L, 4, dir[0]);
		dir[1] = luaL_optfloat(L, 5, dir[1]);
		dir[2] = luaL_optfloat(L, 6, dir[2]);
	}
	else {
		for (lua_pushnil(L); lua_next(L, table) != 0; lua_pop(L, 1)) {
			if (lua_israwstring(L, -2) && // key
			    lua_israwnumber(L, -1)) { // value
				const string key = lua_tostring(L, -2);
				     if (key == "px") { pos[0] = lua_tofloat(L, -1); }
				else if (key == "py") { pos[1] = lua_tofloat(L, -1); }
				else if (key == "pz") { pos[2] = lua_tofloat(L, -1); }
				else if (key == "dx") { pos[0] = lua_tofloat(L, -1); }
				else if (key == "dy") { pos[1] = lua_tofloat(L, -1); }
				else if (key == "dz") { pos[2] = lua_tofloat(L, -1); }
			}
		}
	}

	float target[3];
	target[0] = pos[0] + dir[0];
	target[1] = pos[1] + dir[1];
	target[2] = pos[2] + dir[2];

	vf.setView(pos, target);

	return 0;
}


int LuaCallOuts::SetCameraProjection(lua_State* L)
{
	if (!L2H(L)->HasFullRead()) {
		return 0;
	}

	MainWindow* window = getMainWindow();
	if (window == NULL) {
		return 0;
	}

	// get the defaults
	ViewFrustum& vf = RENDERER.getViewFrustum();
	float fov      = vf.getFOVy();
	float nearZ    = vf.getNear();
	float farZ     = vf.getFar();
	float deepFarZ = vf.getDeepFar();
	int ww  = window->getWidth();
	int wh  = window->getHeight();
	int wvh = window->getViewHeight();

	const int table = 1;
	if (!lua_istable(L, table)) {
		fov      = luaL_optfloat(L, 1,  fov);
		nearZ    = luaL_optfloat(L, 2,  nearZ);
		farZ     = luaL_optfloat(L, 3,  farZ);
		deepFarZ = luaL_optfloat(L, 4, deepFarZ);
		ww       = luaL_optint(L, 5, ww);
		wh       = luaL_optint(L, 6, wh);
		wvh      = luaL_optint(L, 7, wvh);
	}
	else {
		for (lua_pushnil(L); lua_next(L, table) != 0; lua_pop(L, 1)) {
			if (lua_israwstring(L, -2) && // key
			    lua_israwnumber(L, -1)) { // value
				const string key = lua_tostring(L, -2);
				     if (key == "fov")        { fov      = lua_tofloat(L, -1); }
				else if (key == "nearZ")      { nearZ    = lua_tofloat(L, -1); }
				else if (key == "farZ")       { farZ     = lua_tofloat(L, -1); }
				else if (key == "deepFarZ")   { deepFarZ = lua_tofloat(L, -1); }
				else if (key == "width")      { ww  = lua_toint(L, -1); }
				else if (key == "height")     { wh  = lua_toint(L, -1); }
				else if (key == "viewHeight") { wvh = lua_toint(L, -1); }
			}
		}
	}

	vf.setProjection(fov, nearZ, farZ, deepFarZ, ww, wh, wvh);

	return 0;
}


int LuaCallOuts::GetCameraPosition(lua_State* L)
{
	const ViewFrustum& vf = RENDERER.getViewFrustum();
	const float* pos = vf.getEye();
	lua_pushnumber(L, pos[0]);
	lua_pushnumber(L, pos[1]);
	lua_pushnumber(L, pos[2]);
	return 3;
}


int LuaCallOuts::GetCameraDirection(lua_State* L)
{
	const ViewFrustum& vf = RENDERER.getViewFrustum();
	const float* dir = vf.getDirection();
	lua_pushnumber(L, dir[0]);
	lua_pushnumber(L, dir[1]);
	lua_pushnumber(L, dir[2]);
	return 3;
}


int LuaCallOuts::GetCameraUp(lua_State* L)
{
	const ViewFrustum& vf = RENDERER.getViewFrustum();
	const float* up = vf.getUp();
	lua_pushnumber(L, up[0]);
	lua_pushnumber(L, up[1]);
	lua_pushnumber(L, up[2]);
	return 3;
}


int LuaCallOuts::GetCameraRight(lua_State* L)
{
	const ViewFrustum& vf = RENDERER.getViewFrustum();
	const float* right = vf.getRight();
	lua_pushnumber(L, right[0]);
	lua_pushnumber(L, right[1]);
	lua_pushnumber(L, right[2]);
	return 3;
}


int LuaCallOuts::GetCameraMatrix(lua_State* L)
{
	const ViewFrustum& vf = RENDERER.getViewFrustum();
	const float* m;
	if (!lua_tobool(L, 1)) {
		 m = vf.getViewMatrix();
	} else {
		 m = vf.getProjectionMatrix();
	}
	for (int i = 0; i < 16; i++) {
		lua_pushnumber(L, m[i]);
	}
	return 16;
}


int LuaCallOuts::GetFrustumPlane(lua_State* L)
{
	const ViewFrustum& vf = RENDERER.getViewFrustum();
	int plane = -1;
	if (lua_israwnumber(L, 1)) {
		plane = lua_toint(L, 1);
	}
	else if (lua_israwstring(L, 1)) {
		const string key = lua_tostring(L, 1);
		if (key == "near")   { plane = 0; }
		if (key == "left")   { plane = 1; }
		if (key == "right")  { plane = 2; }
		if (key == "bottom") { plane = 3; }
		if (key == "top")    { plane = 4; }
		if (key == "far")    { plane = 5; }
	}
	else {
		return 0;
	}

	if ((plane < 0) || (plane >= 6)) {
		return 0;
	}

	const float* p = vf.getSide(plane);
	lua_pushnumber(L, p[0]);
	lua_pushnumber(L, p[1]);
	lua_pushnumber(L, p[2]);
	lua_pushnumber(L, p[3]);

	return 4;
}


//============================================================================//

int LuaCallOuts::NotifyStyleChange(lua_State* /*L*/)
{
	RENDERER.notifyStyleChange();
	return 0;
}


//============================================================================//
int LuaCallOuts::GetSun(lua_State* L)
{
	const string param = luaL_checkstring(L, 1);

	const float* data = NULL;

	if (param == "brightness") {
		lua_pushnumber(L, RENDERER.getSunBrightness());
		return 1;
	}
	else if (param == "dir") {
		data = RENDERER.getSunDirection();
	}
	else if (param == "ambient") {
		data = RENDERER.getAmbientColor();
	}
	else if (param == "diffuse") {
		data = RENDERER.getSunColor();
	}
	else if (param == "specular") {
		data = RENDERER.getSunColor();
	}

	if (data != NULL) {
		lua_pushnumber(L, data[0]);
		lua_pushnumber(L, data[1]);
		lua_pushnumber(L, data[2]);
		return 3;
	}

	return 0;
}


//============================================================================//

int LuaCallOuts::GetTime(lua_State* L)
{
	const double nowTime = TimeKeeper::getCurrent().getSeconds();
	LuaDouble::PushDouble(L, nowTime);
	return 1;
}


int LuaCallOuts::GetGameTime(lua_State* L)
{
	const double gameTime = GameTime::getStepTime();
	LuaDouble::PushDouble(L, gameTime);
	return 1;
}


int LuaCallOuts::GetTimer(lua_State* L)
{
	const double nowTime = TimeKeeper::getCurrent().getSeconds();
	const uint32_t millisecs = (uint32_t)(nowTime * 1000.0);
	lua_pushlightuserdata(L, (void*)millisecs);
	return 1;
}


int LuaCallOuts::DiffTimers(lua_State* L)
{
	const int args = lua_gettop(L); // number of arguments
	if ((args != 2) || !lua_isuserdata(L, 1) || !lua_isuserdata(L, 2)) {
		luaL_error(L, "Incorrect arguments to DiffTimers()");
	}
	const void* p1 = lua_touserdata(L, 1);
	const void* p2 = lua_touserdata(L, 2);
	const uint32_t t1 = *((const uint32_t*)(const void*)&p1);
	const uint32_t t2 = *((const uint32_t*)(const void*)&p2);
	const uint32_t diffTime = (t1 - t2);
	lua_pushnumber(L, (lua_Number)diffTime * 0.001f); // return seconds
	return 1;
}

//============================================================================//
//============================================================================//

int LuaCallOuts::GetTeamList(lua_State* L) // FIXME
{
	lua_newtable(L);

	World* world = World::getWorld();
	if (world == NULL) {
		return 1;
	}

	return 1;
}


int LuaCallOuts::GetTeamPlayers(lua_State* L) // FIXME
{
	lua_newtable(L);

	World* world = World::getWorld();
	if (world == NULL) {
		return 1;
	}

	return 1;
}


int LuaCallOuts::GetTeamName(lua_State* L)
{
	const TeamColor teamID = ParseTeam(L, 1);
	if (teamID == NoTeam) {
		return 0;
	}
	const char* name = Team::getShortName(teamID);
	if (name == NULL) {
		return 0;
	}
	lua_pushstring(L, name);
	return 1;
}


int LuaCallOuts::GetTeamLongName(lua_State* L)
{
	const TeamColor teamID = ParseTeam(L, 1);
	if (teamID == NoTeam) {
		return 0;
	}
	const char* name = Team::getName(teamID);
	if (name == NULL) {
		return 0;
	}
	lua_pushstring(L, name);
	return 1;
}


int LuaCallOuts::GetTeamCount(lua_State* L)
{
	const TeamColor teamID = ParseTeam(L, 1);
	if (teamID == NoTeam) {
		return 0;
	}
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	if ((teamID < 0) || (teamID >= NumTeams)) {
		return 0; // not safe for world->getTeam()
	}
	const Team& team = world->getTeam(teamID);
	lua_pushinteger(L, team.size);
	return 1;
}


int LuaCallOuts::GetTeamScore(lua_State* L)
{
	const TeamColor teamID = ParseTeam(L, 1);
	if (teamID == NoTeam) {
		return 0;
	}
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	if ((teamID < 0) || (teamID > NumTeams)) {
		return 0; // not safe for world->getTeam()
	}
	const Team& team = world->getTeam(teamID);
	lua_pushinteger(L, team.won);
	lua_pushinteger(L, team.lost);
	return 2;
}


int LuaCallOuts::GetTeamColor(lua_State* L)
{
	const TeamColor teamID = ParseTeam(L, 1);
	if (teamID == NoTeam) {
		return 0;
	}
	const float* color = Team::getTankColor(teamID);
	if (color == NULL) {
		return 0;
	}
	lua_pushnumber(L, color[0]);
	lua_pushnumber(L, color[1]);
	lua_pushnumber(L, color[2]);
	return 3;
}


int LuaCallOuts::GetTeamRadarColor(lua_State* L)
{
	const TeamColor teamID = ParseTeam(L, 1);
	if (teamID == NoTeam) {
		return 0;
	}
	const float* color = Team::getRadarColor(teamID);
	if (color == NULL) {
		return 0;
	}
	lua_pushnumber(L, color[0]);
	lua_pushnumber(L, color[1]);
	lua_pushnumber(L, color[2]);
	return 3;
}


int LuaCallOuts::GetTeamsAreEnemies(lua_State* L)
{
	const TeamColor t1 = ParseTeam(L, 1);
	const TeamColor t2 = ParseTeam(L, 2);
	if ((t1 == NoTeam) || (t2 == NoTeam)) {
		return 0;
	}
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	lua_pushboolean(L, Team::areFoes(t1, t2, world->getGameType()));
	return 1;
}


int LuaCallOuts::GetPlayersAreEnemies(lua_State* L)
{
	const Player* p1 = ParsePlayer(L, 1);
	if (p1 == NULL) {
		return 0;
	}
	const Player* p2 = ParsePlayer(L, 2);
	if (p2 == NULL) {
		return 0;
	}
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	lua_pushboolean(L, Team::areFoes(p1->getTeam(), p2->getTeam(),
	                                 world->getGameType()));
	return 1;
}


//============================================================================//
//============================================================================//

int LuaCallOuts::GetMousePosition(lua_State* L)
{
	MainWindow* wnd = getMainWindow();
	if (wnd == NULL) {
		return 0;
	}

	int mx, my;
	wnd->getWindow()->getMouse(mx, my);
	lua_pushinteger(L, mx);
	lua_pushinteger(L, wnd->getHeight() - my - 1);
	return 2;
}


int LuaCallOuts::GetJoyPosition(lua_State* L)
{
	MainWindow* wnd = getMainWindow();
	if (wnd == NULL) {
		return 0;
	}
	int jx, jy;
	wnd->getJoyPosition(jx, jy);
	lua_pushinteger(L, jx);
	lua_pushinteger(L, jy);
	return 2;
}


int LuaCallOuts::GetKeyModifiers(lua_State* L)
{
	BzfDisplay* dpy = getDisplay();
	if (dpy == NULL) {
		return 0;
	}
	bool alt, ctrl, shift;
	dpy->getModState(shift, ctrl, alt);
	lua_pushboolean(L, alt);
	lua_pushboolean(L, ctrl);
	lua_pushboolean(L, shift);
	return 3;
}


//============================================================================//
//============================================================================//

int LuaCallOuts::WarpMouse(lua_State* L)
{
	if (!L2H(L)->HasInputCtrl()) {
		return 0;
	}
	const int mx = luaL_checkint(L, 1);
	const int my = luaL_checkint(L, 2);

	MainWindow* wnd = getMainWindow();
	if (wnd == NULL) {
		return 0;
	}

	BzfWindow* bzWnd = wnd->getWindow();
	bzWnd->warpMouse(mx, wnd->getHeight() - my - 1);

	return 0;
}


//============================================================================//
//============================================================================//

int LuaCallOuts::GetLocalPlayer(lua_State* L)
{
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank == NULL) {
		return 0;
	}
	lua_pushinteger(L, myTank->getId());
	return 1;
}


int LuaCallOuts::GetLocalPlayerTarget(lua_State* L)
{
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank == NULL) {
		return 0;
	}
	const Player* target = myTank->getTarget();
	if (target == NULL) {
		return 0;
	}
	lua_pushinteger(L, target->getId());
	return 1;
}


int LuaCallOuts::GetLocalTeam(lua_State* L)
{
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank == NULL) {
		return 0;
	}
	lua_pushinteger(L, myTank->getTeam());
	return 1;
}


int LuaCallOuts::GetRabbitPlayer(lua_State* L)
{
	// FIXME -- is this valid?
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank != NULL) {
		if (myTank->getTeam() == RabbitTeam) {
			lua_pushinteger(L, myTank->getId());
			return 1;
		}
	}

	World* world = World::getWorld();
	if (world != NULL) {
		const RemotePlayer* rabbit = world->getCurrentRabbit();
		if (rabbit != NULL) {
			lua_pushinteger(L, rabbit->getId());
			return 1;
		}
	}

	return 0;
}


int LuaCallOuts::GetAntidotePosition(lua_State* L)
{
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank == NULL) {
		return 0;
	}
	const float* pos = myTank->getAntidoteLocation();
	if (pos == NULL) {
		return 0;
	}
	lua_pushnumber(L, pos[0]);
	lua_pushnumber(L, pos[1]);
	lua_pushnumber(L, pos[2]);
	return 3;
}


//============================================================================//
//============================================================================//

static GfxBlock* ParseGfxBlock(lua_State* L, int index)
{
	int id = -1;

	if (lua_israwnumber(L, index)) {
		id = luaL_checkint(L, index);
	} else {
		id = GfxBlockMgr::getStringID(luaL_checkstring(L, index));
	}

	if ((id < 0) || (id >= GfxBlockMgr::BlockIDCount)) {
		luaL_error(L, "invalid GfxBlock id");
	}

	GfxBlock* gfxBlock = GfxBlockMgr::get(id);
	if (gfxBlock == NULL) {
		return NULL;
	}

	return gfxBlock;
}


int LuaCallOuts::SetGfxBlock(lua_State* L)
{
	GfxBlock* gfxBlock = ParseGfxBlock(L, 1);
	if (gfxBlock == NULL) {
		return 0;
	}
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	const bool block = lua_tobool(L, 2);

	EventClient* ec = L2H(L);
	// block LuaUser from setting world graphics blocks
	if ((ec == luaUser) && gfxBlock->worldBlock()) {
		return 0;
	}

	if (!block) {
		gfxBlock->remove(ec);
		return 0;
	}

	const bool queue = lua_isboolean(L, 2) && lua_tobool(L, 2);
	lua_pushboolean(L, gfxBlock->set(ec, queue));
	return 1;
}


int LuaCallOuts::GetGfxBlock(lua_State* L)
{
	const GfxBlock* gfxBlock = ParseGfxBlock(L, 1);
	if (gfxBlock == NULL) {
		return 0;
	}
	EventClient* ec = L2H(L);
	lua_pushboolean(L, gfxBlock->blocked());
	lua_pushboolean(L, gfxBlock->test(ec));
	return 2;
}


int LuaCallOuts::SetPlayerGfxBlock(lua_State* L)
{
	// FIXME - remove these 3 const_cast<>s for now const Parse routines ?
	Player* player = const_cast<Player*>(ParsePlayer(L, 1));
	if (player == NULL) {
		return 0;
	}
	EventClient* ec = L2H(L);
	GfxBlock& gfxBlock = player->getGfxBlock();

	luaL_checktype(L, 2, LUA_TBOOLEAN);
	const bool block = lua_tobool(L, 2);
	if (!block) {
		gfxBlock.remove(ec);
		return 0;
	}
	const bool queue = lua_isboolean(L, 3) && lua_tobool(L, 3);
	lua_pushboolean(L, gfxBlock.set(ec, queue));
	return 1;
}


int LuaCallOuts::GetPlayerGfxBlock(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	EventClient* ec = L2H(L);
	const GfxBlock& gfxBlock = player->getGfxBlock();
	lua_pushboolean(L, gfxBlock.blocked());
	lua_pushboolean(L, gfxBlock.test(ec));
	return 2;
}


int LuaCallOuts::SetFlagGfxBlock(lua_State* L)
{
	ClientFlag* flag = const_cast<ClientFlag*>(ParseFlag(L, 1));
	if (flag == NULL) {
		return 0;
	}
	EventClient* ec = L2H(L);
	GfxBlock& gfxBlock = flag->gfxBlock;

	luaL_checktype(L, 2, LUA_TBOOLEAN);
	const bool block = lua_tobool(L, 2);
	if (!block) {
		gfxBlock.remove(ec);
		return 0;
	}
	const bool queue = lua_isboolean(L, 3) && lua_tobool(L, 3);
	lua_pushboolean(L, gfxBlock.set(ec, queue));
	return 1;
}


int LuaCallOuts::GetFlagGfxBlock(lua_State* L)
{
	const ClientFlag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	EventClient* ec = L2H(L);
	const GfxBlock& gfxBlock = flag->gfxBlock;
	lua_pushboolean(L, gfxBlock.blocked());
	lua_pushboolean(L, gfxBlock.test(ec));
	return 2;
}


int LuaCallOuts::SetShotGfxBlock(lua_State* L)
{
	ShotPath* shot = const_cast<ShotPath*>(ParseShot(L, 1));
	if (shot == NULL) {
		return 0;
	}
	EventClient* ec = L2H(L);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	const bool block = lua_tobool(L, 2);
	if (!block) {
		shot->getGfxBlock().remove(ec);
		return 0;
	}
	const bool queue = lua_isboolean(L, 3) && lua_tobool(L, 3);
	lua_pushboolean(L, shot->getGfxBlock().set(ec, queue));
	return 1;
}


int LuaCallOuts::GetShotGfxBlock(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	EventClient* ec = L2H(L);
	const GfxBlock& gfxBlock = shot->getGfxBlock();
	lua_pushboolean(L, gfxBlock.blocked());
	lua_pushboolean(L, gfxBlock.test(ec));
	return 2;
}


//============================================================================//

int LuaCallOuts::GetPlayerList(lua_State* L)
{
	lua_newtable(L);
	int count = 0;

	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank != NULL) {
		count++;
		lua_pushinteger(L, myTank->getId());
		lua_rawseti(L, -2, count);
	}

#ifdef ROBOT
	for (int i = 0; i < numRobots; i++) {
		if (robots[i] != NULL) {
			count++;
			lua_pushinteger(L, robots[i]->getId());
			lua_rawseti(L, -2, count);
		}
	}
#endif

	for (int i = 0; i < curMaxPlayers; i++) {
		if (remotePlayers[i] != NULL) {
			count++;
			lua_pushinteger(L, remotePlayers[i]->getId());
			lua_rawseti(L, -2, count);
		}
	}

	return 1;
}


int LuaCallOuts::GetPlayerName(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushstring(L, player->getCallSign());
	return 1;
}


int LuaCallOuts::GetPlayerType(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushinteger(L, player->getPlayerType());
	return 1;
}


int LuaCallOuts::GetPlayerTeam(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushinteger(L, player->getTeam());
	return 1;
}


int LuaCallOuts::GetPlayerFlag(lua_State* L) // FIXME -- linear search, ew
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	if (player->getFlag() == Flags::Null) {
		return 0;
	}
	World* world = World::getWorld();
	if (world == NULL) {
		return 0;
	}
	const PlayerId playerID = player->getId();
	const int maxFlags = world->getMaxFlags();
	for (int flagID = 0; flagID < maxFlags; flagID++) {
		const Flag& flag = world->getFlag(flagID);
		if ((flag.status == FlagOnTank) && (flag.owner == playerID)) {
			lua_pushinteger(L, flag.id);
			return 1;
		}
	}
	return 0;
}


int LuaCallOuts::GetPlayerFlagType(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	const FlagType* ft = player->getFlag();
	if (ft == NULL) {
		return 0;
	}
	lua_pushstring(L, ft->flagAbbv.c_str());
	return 1;
}


int LuaCallOuts::GetPlayerScore(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushinteger(L, player->getWins());
	lua_pushinteger(L, player->getLosses());
	lua_pushinteger(L, player->getTeamKills());
	return 3;
}


int LuaCallOuts::GetPlayerMotto(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	map<string, string>::const_iterator it = player->customData.find("motto");
	if (it == player->customData.end()) {
		return 0;
	}
	lua_pushstdstring(L, it->second);
	return 1;
}


int LuaCallOuts::GetPlayerAutoPilot(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushboolean(L, player->isAutoPilot());
	return 1;
}


int LuaCallOuts::GetPlayerCustomData(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	const string key = luaL_checkstring(L, 2);
	map<string, string>::const_iterator it = player->customData.find(key);
	if (it == player->customData.end()) {
		return 0;
	}
	lua_pushstdstring(L, it->second);
	return 1;
}


int LuaCallOuts::GetPlayerShots(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}

	lua_newtable(L);

	World* world = World::getWorld();
	if (world == NULL) {
		return 1;
	}

	int maxShots = 0;
	const WorldPlayer* worldWeapons = world->getWorldWeapons();
	if (player != (const Player*)worldWeapons) {
		maxShots = world->getMaxShots();
	} else {
		maxShots = worldWeapons->getMaxShots();
	}

	int count = 0;
	for (int i = 0; i < maxShots; i++) {
		const ShotPath* shot = player->getShot(i);
		if ((shot != NULL) && !shot->isExpired()) {
			count = PushShot(L, shot, count);
		}
	}

	return 1;
}


int LuaCallOuts::GetPlayerState(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	// FIXME -- break these into separate calls?
	lua_newtable(L);
	if (player->isAlive())        { HSTR_PUSH_BOOL(L, "alive",        true); }
	if (player->isPaused())       { HSTR_PUSH_BOOL(L, "paused",       true); }
	if (player->isFalling())      { HSTR_PUSH_BOOL(L, "falling",      true); }
	if (player->isPhantomZoned()) { HSTR_PUSH_BOOL(L, "zoned",        true); }
	if (player->isTeleporting())  { HSTR_PUSH_BOOL(L, "teleporting",  true); }
	if (player->isCrossingWall()) { HSTR_PUSH_BOOL(L, "crossingWall", true); }
	if (player->isExploding())    { HSTR_PUSH_BOOL(L, "exploding",    true); }

	return 1;
}


int LuaCallOuts::GetPlayerStateBits(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushinteger(L, player->getStatus());
	return 1;
}


int LuaCallOuts::GetPlayerPosition(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	const float* pos = player->getPosition();
	lua_pushnumber(L, pos[0]);
	lua_pushnumber(L, pos[1]);
	lua_pushnumber(L, pos[2]);
	return 3;
}


int LuaCallOuts::GetPlayerRotation(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushnumber(L, player->getAngle());
	return 1;
}


int LuaCallOuts::GetPlayerDirection(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	const float* dir = player->getForward();
	lua_pushnumber(L, dir[0]);
	lua_pushnumber(L, dir[1]);
	lua_pushnumber(L, dir[2]);
	return 3;
}


int LuaCallOuts::GetPlayerVelocity(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	const float* vel = player->getVelocity();
	lua_pushnumber(L, vel[0]);
	lua_pushnumber(L, vel[1]);
	lua_pushnumber(L, vel[2]);
	return 3;
}


int LuaCallOuts::GetPlayerAngVel(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushnumber(L, player->getAngularVelocity());
	return 1;
}


int LuaCallOuts::GetPlayerDimensions(lua_State* L)
{

	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	const float* dims = player->getDimensions();
	lua_pushnumber(L, dims[0]);
	lua_pushnumber(L, dims[1]);
	lua_pushnumber(L, dims[2]);
	return 3;
}


int LuaCallOuts::GetPlayerPhysicsDriver(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushinteger(L, player->getPhysicsDriver());
	return 1;
}


int LuaCallOuts::GetPlayerDesiredSpeed(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushnumber(L, player->getUserSpeed());
	return 1;
}


int LuaCallOuts::GetPlayerDesiredAngVel(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushnumber(L, player->getUserAngVel());
	return 1;
}


int LuaCallOuts::GetPlayerExplodeTime(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	if (!player->isExploding()) {
		return 0;
	}
	const TimeKeeper current = TimeKeeper::getTick();
	const TimeKeeper explode = player->getExplodeTime();
	const float explodeTime = (float)(current - explode);
	if (explodeTime < 0.0f) {
		return 0; // should not happen
	}
	lua_pushnumber(L, explodeTime);
	return 1;
}


int LuaCallOuts::IsPlayerAdmin(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushboolean(L, player->isAdmin());
	return 1;
}


int LuaCallOuts::IsPlayerVerified(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushboolean(L, player->isVerified());
	return 1;
}


int LuaCallOuts::IsPlayerRegistered(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushboolean(L, player->isRegistered());
	return 1;
}


int LuaCallOuts::IsPlayerHunted(lua_State* L)
{
	const Player* player = ParsePlayer(L, 1);
	if (player == NULL) {
		return 0;
	}
	lua_pushboolean(L, player->isHunted());
	return 1;
}


//============================================================================//

int LuaCallOuts::GetFlagList(lua_State* L)
{
	lua_newtable(L);

	World* world = World::getWorld();
	if (world == NULL) {
		return 1;
	}

	for (int i = 0; i < world->getMaxFlags(); i++) {
		lua_pushinteger(L, i);
		lua_rawseti(L, -2, i + 1);
	}
	return 1;
}


int LuaCallOuts::GetFlagName(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	lua_pushstring(L, flag->type->flagName.c_str());
	return 1;
}


int LuaCallOuts::GetFlagType(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	lua_pushstring(L, flag->type->flagAbbv.c_str());
	return 1;
}


int LuaCallOuts::GetFlagShotType(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	lua_pushinteger(L, flag->type->flagShot);
	return 1;
}


int LuaCallOuts::GetFlagQuality(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	lua_pushinteger(L, flag->type->flagQuality);
	return 1;
}


int LuaCallOuts::GetFlagEndurance(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	lua_pushinteger(L, flag->endurance);
	return 1;
}


int LuaCallOuts::GetFlagTeam(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	lua_pushinteger(L, flag->type->flagTeam);
	return 1;
}


int LuaCallOuts::GetFlagOwner(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	if (flag->owner == (PlayerId) -1) {
		return 0;
	}
	lua_pushinteger(L, flag->owner);
	return 1;
}


int LuaCallOuts::GetFlagState(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	lua_pushinteger(L, flag->status);
	return 1;
}


int LuaCallOuts::GetFlagPosition(lua_State* L)
{
	const Flag* flag = ParseFlag(L, 1);
	if (flag == NULL) {
		return 0;
	}
	const float* pos = flag->position;
	lua_pushnumber(L, pos[0]);
	lua_pushnumber(L, pos[1]);
	lua_pushnumber(L, pos[2]);
	return 3;
}


//============================================================================//

int LuaCallOuts::GetShotList(lua_State* L)
{
	lua_newtable(L);
	int count = 0;

	World* world = World::getWorld();
	if (world == NULL) {
		return 1;
	}

	const int maxShots = world->getMaxShots();

	// my shots
	const LocalPlayer* myTank = LocalPlayer::getMyTank();
	if (myTank != NULL) {
		for (int i = 0; i < maxShots; i++) {
			const ShotPath* shot = myTank->getShot(i);
			if ((shot != NULL) && !shot->isExpired()) {
				count = PushShot(L, shot, count);
			}
		}
	}

	// robot player shots
#ifdef ROBOT
	for (int i = 0; i < numRobots; i++) {
		const RobotPlayer* player = robots[i];
		if (player != NULL) {
			for (int j = 0; j < maxShots; j++) {
				const ShotPath* shot = player->getShot(i);
				if ((shot != NULL) && !shot->isExpired()) {
					count = PushShot(L, shot, count);
				}
			}
		}
	}
#endif

	// remote player shots
	for (int i = 0; i < curMaxPlayers; i++) {
		const RemotePlayer* player = world->getPlayer(i);
		if (player != NULL) {
			for (int j = 0; j < maxShots; j++) {
				const ShotPath* shot = player->getShot(i);
				if ((shot != NULL) && !shot->isExpired()) {
					count = PushShot(L, shot, count);
				}
			}
		}
	}

	// world weapon shots
	const WorldPlayer* worldWeapons = world->getWorldWeapons();
	if (worldWeapons != NULL) {
		const int wwMaxShots = worldWeapons->getMaxShots();
		for (int i = 0; i < wwMaxShots; i++) {
			const ShotPath* shot = worldWeapons->getShot(i);
			if ((shot != NULL) && !shot->isExpired()) {
				count = PushShot(L, shot, count);
			}
		}
	}

	return 1;
}


int LuaCallOuts::GetShotType(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	lua_pushinteger(L, shot->getShotType());
	return 1;
}


int LuaCallOuts::GetShotFlagType(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	lua_pushstring(L, shot->getFlag()->flagAbbv.c_str());
	return 1;
}


int LuaCallOuts::GetShotPlayer(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	lua_pushinteger(L, shot->getPlayer());
	return 1;
}


int LuaCallOuts::GetShotTeam(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	lua_pushinteger(L, shot->getTeam());
	return 1;
}


int LuaCallOuts::GetShotPosition(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	const float* pos = shot->getPosition();
	lua_pushnumber(L, pos[0]);
	lua_pushnumber(L, pos[1]);
	lua_pushnumber(L, pos[2]);
	return 3;
}


int LuaCallOuts::GetShotVelocity(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	const float* vel = shot->getVelocity();
	lua_pushnumber(L, vel[0]);
	lua_pushnumber(L, vel[1]);
	lua_pushnumber(L, vel[2]);
	return 3;
}


int LuaCallOuts::GetShotLifeTime(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	lua_pushnumber(L, shot->getLifetime());
	return 1;
}


int LuaCallOuts::GetShotLeftTime(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	const double timeLeft = shot->getCurrentTime() - shot->getStartTime();
	lua_pushnumber(L, (lua_Number)timeLeft);
	return 1;
}


int LuaCallOuts::GetShotReloadTime(lua_State* L)
{
	const ShotPath* shot = ParseShot(L, 1);
	if (shot == NULL) {
		return 0;
	}
	lua_pushnumber(L, shot->getReloadTime());
	return 1;
}


//============================================================================//
//============================================================================//

int LuaCallOuts::MakeFont(lua_State* L)
{
	LuaFontTexture::Reset();

	int tableIndex = 1;
	if (lua_israwstring(L, 1)) {
		LuaFontTexture::SetInFileName(lua_tostring(L, 1));
		tableIndex++;
	}

	LuaHandle* lh = L2H(L);
	LuaFontTexture::SetInVFSModes(lh->GetFSReadAll());
	LuaFontTexture::SetOutVFSModes(lh->GetFSWriteAll());

	if (lua_istable(L, tableIndex)) {
		for (lua_pushnil(L); lua_next(L, tableIndex) != 0; lua_pop(L, 1)) {
			if (lua_israwstring(L, -2)) {
				const string key = lua_tostring(L, -2);
				if (lua_israwstring(L, -1)) {
					if (key == "outName") {
						LuaFontTexture::SetOutBaseName(lua_tostring(L, -1));
					}
					else if (key == "inData") {
						size_t len = 0;
						const char* ptr = lua_tolstring(L, -1, &len);
						string inputData(ptr, len);
						LuaFontTexture::SetInData(inputData);
					}
				}
				else if (lua_israwnumber(L, -1)) {
					const unsigned int value = (unsigned int)lua_tointeger(L, -1);
					if (key == "height") {
						LuaFontTexture::SetFontHeight(value);
					} else if (key == "texWidth") {
						LuaFontTexture::SetTextureWidth(value);
					} else if (key == "minChar") {
						LuaFontTexture::SetMinChar(value);
					} else if (key == "maxChar") {
						LuaFontTexture::SetMaxChar(value);
					} else if (key == "outlineMode") {
						LuaFontTexture::SetOutlineMode(value);
					} else if (key == "outlineRadius") {
						LuaFontTexture::SetOutlineRadius(value);
					} else if (key == "outlineWeight") {
						LuaFontTexture::SetOutlineWeight(value);
					} else if (key == "padding") {
						LuaFontTexture::SetPadding(value);
					} else if (key == "stuffing") {
						LuaFontTexture::SetStuffing(value);
					} else if (key == "debug") {
						LuaFontTexture::SetDebugLevel(value);
					}
				}
			}
		}
	}

	lua_pushboolean(L, LuaFontTexture::Execute());

	return 1;
}


//============================================================================//
//============================================================================//

// whacky bit of dev'ing fun
#if defined(HAVE_UNISTD_H) && defined(HAVE_FCNTL_H)
	#include <unistd.h>
	#include <fcntl.h>
	int LuaCallOuts::ReadStdin(lua_State* L)
	{
		fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
		char buf[4096];
		const int r = read(STDIN_FILENO, buf, sizeof(buf));
		if (r <= 0) {
			return 0;
		}
		lua_pushlstring(L, buf, r);
		fcntl(STDIN_FILENO, F_SETFL, 0);
		return 1;
	}
#endif


//============================================================================//
//============================================================================//
