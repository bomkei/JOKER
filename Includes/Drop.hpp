#ifndef DROP_HPP
#define DROP_HPP

#include "CTRPluginFramework.hpp"
#include "Helpers/Strings.hpp"

namespace CTRPluginFramework
{
	using OnInputChange = void(*)(Keyboard &keyboard, InputChangeEvent &event);
	
	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnInputChange cb = nullptr);
	
	class Player
	{
	public:
		static u8 GetLocation();
		static u32 GetInstance(u8 PlayerIndex, bool noChecks);
		static float *GetCoordinates(u8 PlayerIndex = 4);
		static bool GetWorldCoords(u32 *worldx, u32 *worldy, u8 PlayerIndex, bool noChecks);
		static bool Exists(u8 PlayerIndex);
		static u8 GetRoom(u8 PlayerIndex);
		static u32 GetAnimationInstance(u32 playerInstance, u8 someVal1, u8 someVal2, u32 encVal);
		static void SendAnimPacket(u8 senderIndex, u32 animObj, u8 animID, u8 roomID, u8 targetPlayerIndex);
		static bool ExecuteAnimation(u32 pPlayerObj, u8 animID, u32 pAnimObj, bool u0);
	};
	
	class GameHelper
	{
	public:
	static void TrampleAt(u8 wX, u8 wY);
	static u32 *GetItemAtWorldCoords(u32 MapPtr, u32 x, u32 y, bool u0);
	static u32 GetCurrentMap();
	static u8 GetOnlinePlayerIndex();
	static u8 GetActualPlayerIndex();
	static u32 GetLockedSpotIndex(u8 wX, u8 wY, u8 roomID);
	static u32 PlaceItem(u8 ID, u32 *ItemToReplace, u32 *ItemToPlace, u32 *ItemToShow, u8 worldx, u8 worldy, bool u0, bool u1, bool u2, bool u3, bool u4);
	static float *WorldCoordsToCoords(u8 wX, u8 wY, float res[3]);
	static void Particles(u32 particleID, float *floats, u32 u0, u32 u1);
	static bool PlaceItemWrapper(u8 ID, u32 ItemToReplace, u32 *ItemToPlace, u32 *ItemToShow, u8 worldx, u8 worldy, bool u0, bool u1, bool u2, bool u3, bool u4, u8 waitAnim, u8 roomID);
	static u8 GetOnlinePlayerCount();
	};
	
	class ItemSequence
	{
	public:
	static u32 *Next();
	static void init(u32 defaultPtr);
	static u32 PeekNext();
	static bool openKB();
	static void Switch(bool enable);
	static bool Enabled();
	};
	
	class Camera
	{
	public:
	static u32 GetInstance();
	static void AddToX(float val);
	static void AddToY(float val);
	static void AddToZ(float val);
	static void AddToYRotation(u16 val);
	};
	
	struct dropInfo
	{
		u32 itemToRemove;
		u32 itemToShow;
		u32 itemToPlace;
		u8 unknown0;
		u8 playerindex;
		u8 wX;
		u8 wY;
		u8 dropID;
		u8 unknown1;
		u8 unknown2;
		u8 unknown3;
		u8 unknown4;
		u8 roomID;
	};

	struct dropPkt
	{
		u32 replaceID;
		u32 placeID;
		u32 showID;
		u8 combinedDropIDPlayerIndex;
		u8 processFlags;
		u8 paramFlags;
		u8 flags;
		u8 u0;
		u8 u1;
		u8 roomID;
		u8 wX;
		u8 wY;
		u8 u2;
	};

	struct TramplePkt
	{
		u32 item;
		u8 roomID;
		u8 wX;
		u8 wY;
		u8 u0;
	};
}	
#endif