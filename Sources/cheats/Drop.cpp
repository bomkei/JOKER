#include "cheats.hpp"
#include "Drop.hpp"

namespace CTRPluginFramework
{
	u16 ItemID = 0x2159;
	u16 DropID = 0x10a;

	// ---------------------------------------------------------------
	// ドロップ関数
	// 成功するとtrueを返し、失敗すればfalseを返します。
	// ---------------------------------------------------------------
	bool Drop(u16 item, u16 dcode, u8 x, u8 y, bool check)
	{
		if ( check && Game::GetWorldItem(x, y) != 0x7ffe ) return false;
		
		Process::Write32(0x9AE160, item);
		Process::Write32(0x9AE164, item);
		
		u16 location = y * 0x100 + x;
		u16 IsDropping;
		u32 DropAddress;
		u32 ItemAddress;
		
		for ( int i = 0; i < 32; i++ )
		{
			IsDropping = READU16(0x9ae254 + i * 0x16);
			DropAddress = 0x9ae252 + i * 0x16;
			if ( READU16(DropAddress) == location && IsDropping != 0 ) return false;
		}
		
		for ( int i = 0; i < 32; i++ )
		{
			IsDropping = READU16(0x9ae254 + i * 0x16);
			ItemAddress = 0x9ae248 + i * 0x16;
			DropAddress = 0x9ae252 + i * 0x16;
			if ( IsDropping == 0 )
			{
				Process::Write32(ItemAddress, item);
				Process::Write32(ItemAddress + 0x4, item);
				Process::Write32(DropAddress, dcode * 0x10000 + location);
				return true;
			}
		}
		
		return false;
	}

	// ドロップ無効化
	void DropStopper(MenuEntry* e) {
		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys()))
			Process::Write32(0x5a0e50, 0xeaffff84);

		if (Controller::IsKeysPressed(e->Hotkeys[1].GetKeys()))
			Process::Write32(0x5a0e50, 0xaffff84);
	}

	// 連続スライドドロップ
	void DD_Spam(MenuEntry* e) {
		static bool mode;

		u32* infItemAddr1 = (u32*)0x19C4D0;
		u32* infItemAddr2 = (u32*)0x19C42C;
		const u32 nop = 0xE1A00000;

		if (*infItemAddr1 != 0)
		{
			*infItemAddr1 = 0;
			*infItemAddr2 = 0;
		}

		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys()))
		{
			if (!mode)
			{
				mode = true;
				OSD::Notify("DragDropSpam: ON");
				Process::Write32(0x19c548, nop);
				Process::Write32(0x19dde4, nop);
				Process::Write32(0x26f000, nop);
			}
			else
			{
				mode = false;
				OSD::Notify("DragDropSpam: OFF");
				Process::Write32(0x19c548, 0xeb03fb85);
				Process::Write32(0x19dde4, 0xeb03f55e);
				Process::Write32(0x26f000, 0xeb00b0d7);
			}
		}
	}

	// アイテム変更
	void ChangeItemID(MenuEntry* e) {
		if (e->Hotkeys[0].IsDown())
		{
			Keyboard key("アイテムID");
			key.Open(ItemID);
		}
	}

	// ドロップ変更
	void ChangeDropID(MenuEntry* e) {
		if (e->Hotkeys[0].IsDown())
		{
			Keyboard key("", { "通常", "花を植える", "マイデザイン", "埋める" });
			u16 DropCodes[4] = { 0x10a, 0x10c, 0x10d, 0x10b };

			int r0 = key.Open();
			if (r0 >= 0) DropID = DropCodes[r0];
		}
	}

	// タッチドロップ
	void TouchDrop(MenuEntry* e) {
		touchPosition tp;
		hidTouchRead(&tp);
		Chat chat;

		int x = tp.px;
		int y = tp.py;

		if (x < 70 || y < 54) return;
		if (x > 249 || y > 206) return;
		if (chat.IsOpened()) return;

		x -= 70;
		x *= 13.7;
		x /= 32;

		y -= 54;
		y *= 14.8;
		y /= 32;

		if (Controller::IsKeysDown(Touchpad))
		{
			Drop(ItemID, DropID, x + 0x10, y + 0x10, true);
		}
	}

	// 自動ドロップ
	void AutoDrop(MenuEntry* e) {
		static bool mode;

		u8 sx = *(u8*)0x3309a2b8;
		u8 sy = *(u8*)0x3309a2bc;

		sx -= 1;
		sy -= 1;

		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys())) {
			if (!mode) {
				mode = true;
				OSD::Notify("AutoDrop: ON");
			}
			else {
				mode = false;
				OSD::Notify("AutoDrop: OFF");
			}
		}

		if (mode) {
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					u32 px = sx + x;
					u32 py = sy + y;
					if (px >= 0x10 && px <= 0x60 && py >= 0x10 && py <= 0x60)
						Drop(ItemID, DropID, px, py, true);
				}
			}
		}
	}

	//////////////////////////////////
	//////////MAP EDITOR HERE/////////
	//////////////////////////////////

	u32 selectedX, selectedY, selectedItem = 0x10; 
	bool selecting = false;
	bool turbo = false;
	u8 DropType = 0xA;
	u32 itemIDToReplace = 0x7FFE;
	u8 waitAnim = 0x56;
	static u32 particleID = 0x0214;
	
	bool editorID(const Screen &screen) { 
		if (screen.IsTop) screen.Draw("ID: " << Hex(selectedItem), 320, 220, Color::White); 
		return 0;
	}
	
	void tileSelector(MenuEntry *e) {
		if (Player::GetInstance(4, 1) == 0) return;
		static u32 keyPressedTicks = 0, DPadKeyPressedTicks = 0;
		static u8 size; 
		static u32 tileID;
		static bool removal = false;
		float Y = *(float *)((u32)Player::GetCoordinates(4) + 4);
		float particleCoords[3]{ 0, Y, 0 };
		u32 pItem;
		if (!selecting) Player::GetWorldCoords(&selectedX, &selectedY, 4, 1);
		pItem = (u32)GameHelper::GetItemAtWorldCoords(GameHelper::GetCurrentMap(), selectedX, selectedY, 0);
		u32 player = Player::GetInstance(4, 1);
        if (player != 0) {
		if (e->WasJustActivated()) { 
				Process::Patch(0x1A08C8, 0xE1A00000);
				Process::Patch(0x1A08CC, 0xE3A00000);
				Process::Patch(0x1A08D0, 0xEB0E011D);
		}
		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys())) {//Key::Start + Key::DPadUp
			if (selecting) {
				OSD::Stop(editorID);
				Process::Write32(0x1A5128, 0xE2805C01);
				OSD::Notify("Map Editor: OFF",  Color::Red);
				selecting = false;
			}
			else {
				OSD::Run(editorID);		
				Process::Write32(0x1A5128, 0xE8BD81F0);
				OSD::Notify("Map Editor: ON", Color::Green);
				selecting = true;

				*(float *)(Camera::GetInstance() + 4) = (float)(selectedX * 0x20 + 0x10);
				Camera::AddToY(90.0f);
				*(float *)(Camera::GetInstance() + 0xC) = (float)(selectedY * 0x20 + 0x70);
				Camera::AddToYRotation(0x700);
			}
		}
		if (selecting) {
			if (Controller::IsKeysDown(e->Hotkeys[1].GetKeys()) || Controller::IsKeysPressed(e->Hotkeys[1].GetKeys())) {//Key::DPadRight
				DPadKeyPressedTicks++;
				if ((DPadKeyPressedTicks < 50 ? (DPadKeyPressedTicks % 8) == 1 : (DPadKeyPressedTicks % 3) == 1) || DPadKeyPressedTicks > 100) {
					selectedX += 1;
					Camera::AddToX(32.0f);
				}
			}
			if (Controller::IsKeysDown(e->Hotkeys[2].GetKeys()) || Controller::IsKeysPressed(e->Hotkeys[2].GetKeys())) {//Key::DPadLeft
				DPadKeyPressedTicks++;
				if ((DPadKeyPressedTicks < 50 ? (DPadKeyPressedTicks % 8) == 1 : (DPadKeyPressedTicks % 3) == 1) || DPadKeyPressedTicks > 100) {
					selectedX -= 1;
					Camera::AddToX(-32.0f);
				}
			}
			if (Controller::IsKeysDown(e->Hotkeys[3].GetKeys()) || Controller::IsKeysPressed(e->Hotkeys[3].GetKeys())) {//Key::DPadDown
				DPadKeyPressedTicks++;
				if ((DPadKeyPressedTicks < 50 ? (DPadKeyPressedTicks % 8) == 1 : (DPadKeyPressedTicks % 3) == 1) || DPadKeyPressedTicks > 100) {
					selectedY += 1;
					Camera::AddToZ(32.0f);
				}
			}
			if (Controller::IsKeysDown(e->Hotkeys[4].GetKeys()) || Controller::IsKeysPressed(e->Hotkeys[4].GetKeys())) {//Key::DPadUp
				DPadKeyPressedTicks++;
				if ((DPadKeyPressedTicks < 50 ? (DPadKeyPressedTicks % 8) == 1 : (DPadKeyPressedTicks % 3) == 1) || DPadKeyPressedTicks > 100) {
					selectedY -= 1;
					Camera::AddToZ(-32.0f);
				}
			}
			if (Controller::IsKeysReleased(e->Hotkeys[5].GetKeys()) || Controller::IsKeysReleased(e->Hotkeys[6].GetKeys())) keyPressedTicks = 0; //Key::L + R
			if (Controller::IsKeysReleased(e->Hotkeys[1].GetKeys()) || Controller::IsKeysReleased(e->Hotkeys[2].GetKeys()) || Controller::IsKeysReleased(e->Hotkeys[3].GetKeys()) || Controller::IsKeysReleased(e->Hotkeys[4].GetKeys())) DPadKeyPressedTicks = 0; //DPadRight + DPadLeft + DPadDown + DPadUp
			if (Controller::IsKeysDown(e->Hotkeys[5].GetKeys())) {//Key::L
				keyPressedTicks++;
				if ((keyPressedTicks < 90 ? (keyPressedTicks % 10) == 1 : (keyPressedTicks % 3) == 1) || keyPressedTicks > 220) {
				selectedItem = (selectedItem - 1 == 0x1FFF ? 0xFD : selectedItem - 1) % 0x4000;
				}
			}
			if (Controller::IsKeysDown(e->Hotkeys[6].GetKeys())) {//Key::R
				keyPressedTicks++;
				if ((keyPressedTicks < 90 ? (keyPressedTicks % 10) == 1 : (keyPressedTicks % 3) == 1) || keyPressedTicks > 220) {
				selectedItem = (selectedItem + 1 == 0xFE ? 0x2000 : selectedItem + 1) % 0x4000;
				}
			}
			if (Controller::IsKeysPressed(e->Hotkeys[7].GetKeys())) {//Key::Start + Key::DPadDown
				size++;
				if (size >= 4) size = 0;
				OSD::Notify("Size " << std::to_string(size));
			}
			if (Controller::IsKeysPressed(e->Hotkeys[8].GetKeys())) {//Key::Start + Key::DPadLeft
				if (removal) { OSD::Notify("Removal Mode: OFF"); removal = false; }
				else { OSD::Notify("Removal Mode: ON"); removal = true; }
			}
			if (turbo ? Controller::IsKeysDown(e->Hotkeys[9].GetKeys()) : Controller::IsKeysPressed(e->Hotkeys[9].GetKeys())) {//Key::A
				if (pItem == 0) return;
				for (int8_t i = -size; i <= size; i++) {
					for (int8_t j = -size; j <= size; j++) {
						if (!removal) GameHelper::PlaceItemWrapper(DropType, itemIDToReplace, &selectedItem, &selectedItem, (selectedX + j), (selectedY + i), 0, 0, 0, 0, 0, waitAnim, 0xA5);
						else GameHelper::TrampleAt((selectedX + j), (selectedY + i)); 
					}
				}
			}
			if (Controller::IsKeysPressed(e->Hotkeys[10].GetKeys())) {//Key::Start + Key::DPadRight
			if(SetUpKB("Enter ID:", true, 8, tileID, tileID)) selectedItem = tileID;
			}
			for (int8_t i = -size; i <= size; i++) {
				for (int8_t j = -size; j <= size; j++) {
					particleCoords[0] = (selectedX + j) * 0x20 + 0x10;
					particleCoords[2] = (selectedY + i) * 0x20 + 0x10;
					GameHelper::Particles(particleID, particleCoords, 0x96FC06, 0xADF870);
				}
			}
		}
		}
		if (!e->IsActivated()) { 
			OSD::Stop(editorID);
			Process::Write32(0x1A5128, 0xE2805C01);
			Process::Patch(0x1A08C8, 0xE3A01040);
            Process::Patch(0x1A08CC, 0xE5900000);
            Process::Patch(0x1A08D0, 0xEB14CAC6);
		}
	}

	//////////////////////////////////
	///////CLASS FUNCTIONS HERE///////
	//////////////////////////////////
	bool SetUpKB(const std::string &msg, bool hex, const int length, u32 &output, u32 def, OnInputChange cb) {
		Sleep(Milliseconds(100));
		Keyboard kb("Enter ID: ");
		kb.GetMessage() = msg;
		kb.IsHexadecimal(hex);
		kb.SetMaxLength(length);
		kb.OnInputChange(cb);
		return kb.Open(output, def) == 0;
	}
	
	std::vector<u32> items;
	std::vector<std::string> keyBoardItems;
	u8 index;
	bool useDropChain = false;
	Keyboard *optDCKB;
	Keyboard *DCKB;
	u32 *defPtr;
	u32 defItem;
	
	volatile u32(*pfunction0)();
	volatile u32(*pfunction1)(u32 param1);
	volatile u32(*pfunction2)(u32 param1, u32 param2);
	volatile u32(*pfunction3)(u32 param1, u32 param2, u32 param3);
	volatile u32(*pfunction4)(u32 param1, u32 param2, u32 param3, u32 param4);
	volatile u32(*pfunction5)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
	volatile u32(*pfunction6)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
	volatile u32(*pfunction7)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
	volatile u32(*pfunction8)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
	volatile u32(*pfunction9)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9);
	volatile u32(*pfunction10)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10);
	volatile u32(*pfunction11)(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10, u32 param11);              

	void GameHelper::TrampleAt(u8 wX, u8 wY) {
		u32 pItem = (u32)GameHelper::GetItemAtWorldCoords(GameHelper::GetCurrentMap(), wX, wY, 0);
		if (pItem != 0) {
			u8 room = Player::GetRoom(GameHelper::GetActualPlayerIndex()); 
			if (GameHelper::GetOnlinePlayerCount() != 0) {	
				TramplePkt data { *(u32 *)pItem, room, wX, wY, 0 };
				Process::Write32((u32)&pfunction4, 0x623F80);
				pfunction4(0x47, 4, (u32)&data, 8);
			}
			Process::Write32((u32)&pfunction5, 0x168E08);
			pfunction5(wX, wY, 0, room, 0x955FF4);
			Process::Write32((u32)&pfunction3, 0x59DA7C);
			pfunction3(wX, wY, 1);
		}
	}

	u8 Player::GetLocation() {
		return *(u8 *)0x33099F7C;
	}
	
	u32 Player::GetInstance(u8 PlayerIndex, bool noChecks) {
		Process::Write32((u32)&pfunction2, 0x5C27D8);
		return pfunction2(PlayerIndex, noChecks);
	}
	
	u32 *GameHelper::GetItemAtWorldCoords(u32 MapPtr, u32 x, u32 y, bool u0) {
		Process::Write32((u32)&pfunction4, 0x2FEE38);
		return (u32 *)pfunction4(MapPtr, x, y, u0);
	}
	
	u32 GameHelper::GetCurrentMap() {
		Process::Write32((u32)&pfunction0, 0x6A53DC);
		return pfunction0();
	}
	
	u8 GameHelper::GetOnlinePlayerCount() {
		Process::Write32((u32)&pfunction1, 0x75D798);
		return pfunction1(*(u32 *)0x94D644);
	}
	
	bool Player::GetWorldCoords(u32 *worldx, u32 *worldy, u8 PlayerIndex, bool noChecks) {
		Process::Write32((u32)&pfunction4, 0x5BFCE4);
		return pfunction4((u32)worldx, (u32)worldy, PlayerIndex, noChecks);
	}
	
	float *Player::GetCoordinates(u8 PlayerIndex) {
		u32 i = GetInstance(PlayerIndex, 1);
		if (i != 0) i += 0x14;
		return (float *)i;
	}
	
	u32 *ItemSequence::Next() {
		if (items.size() - 1 > index) index++;
		else index = 0;
		if (index == 0) return defPtr;
		else return &items.at(index);
	}
	
	void ItemSequence::init(u32 defaultPtr) {
		optDCKB = new Keyboard("Choose:");
		DCKB = new Keyboard("Enter ID:");
		items.clear();
		items.push_back(defaultPtr);
		defPtr = (u32 *)defaultPtr;
		optDCKB->CanAbort(true);
		DCKB->CanAbort(true);
		DCKB->IsHexadecimal(true);
		DCKB->SetMaxLength(8);
		DCKB->DisplayTopScreen = true;
	}
	
	u32 ItemSequence::PeekNext() {
		if (index + 1 == items.size()) return *defPtr;
		else return items.at(index + 1);
	}
	
	bool ItemSequence::openKB() {
		int8_t val;
		u32 newItem;
		keyBoardItems.clear();
		keyBoardItems.push_back((items.size() == 1 || index + 1 == items.size() ? "Slot 1: " : "Slot 2: "));
		for (u8 i = 1; i < items.size(); i++) keyBoardItems.push_back((index + 1 == i  ? "->" : "") << Hex(items.at(i)));
		keyBoardItems.push_back("Add");
		optDCKB->Populate(keyBoardItems);
		val = optDCKB->Open();
		switch (val) {
		case -1:
			return false;
		case 0:
			Sleep(Milliseconds(100));
			newItem = *defPtr;
			if (DCKB->Open(newItem, newItem) == 0) *defPtr = newItem;
			break;
		default:
			Sleep(Milliseconds(100));
			if (val + 1 == keyBoardItems.size()) {
				if (DCKB->Open(newItem) == 0) items.push_back(newItem);
			}
			else {
				if (DCKB->Open(items.at(val), items.at(val)) == -1)	items.erase(items.begin() + val);
			}
			break;
		}
		Sleep(Milliseconds(100));
		openKB();
		return true;
	}
	
	void ItemSequence::Switch(bool enable) {
		useDropChain = enable;
	}
	
	bool ItemSequence::Enabled() {
		return useDropChain;
	}
	
	u8 GameHelper::GetOnlinePlayerIndex() {
		Process::Write32((u32)&pfunction0, 0x305F6C);
		return pfunction0();
	}
	
	u8 GameHelper::GetActualPlayerIndex() {
		u8 index = *(u8 *)((*(u32 *)0x94D644) + 0x13268);
		if (index >= 4) return 0;
		else return index;
	}
	
	u32 GameHelper::GetLockedSpotIndex(u8 wX, u8 wY, u8 roomID) {
		Process::Write32((u32)&pfunction3, 0x59FAF4);
		return pfunction3(wX, wY, roomID);
	}
	
	bool Player::Exists(u8 PlayerIndex) {
		if (GameHelper::GetOnlinePlayerCount() == 0 && PlayerIndex == GameHelper::GetOnlinePlayerIndex()) return true;
		if (*(u8 *)(0x32005398 + PlayerIndex) != 0xA5) return true;
		return false;
	}
	
	u8 Player::GetRoom(u8 PlayerIndex) {
		u32 animObjPtr;
		Process::Write32((u32)&pfunction1, 0x5C2714);
		animObjPtr = pfunction1(PlayerIndex);
		return animObjPtr == 0 ? 0xFF : *(u8 *)animObjPtr;
	}
	
	void pseudoType0x21(dropPkt *pkt) {
		dropPkt *drop = new dropPkt();
		u32 x, y;
		s8 diffX, diffY;
		u32 *item;
		drop->replaceID = 0x71;
		drop->placeID = pkt->placeID;
		drop->showID = 0x71;
		drop->paramFlags = 0;
		drop->processFlags = 0;
		drop->u0 = 0;
		drop->u1 = 0;
		drop->u2 = 0;
		drop->roomID = pkt->roomID;
		drop->wX = pkt->wX;
		drop->wY = pkt->wY;
		drop->combinedDropIDPlayerIndex = GameHelper::GetOnlinePlayerIndex() & 3 | 0x84;
		drop->processFlags = drop->processFlags & 0xC3 | (GameHelper::GetOnlinePlayerCount() > 1 ? 0x1C : 0xC);
		drop->flags = 0;
		Player::GetWorldCoords(&x, &y, 4, 1);
		pkt->wX = x;
		pkt->wY = y;
		pkt->replaceID = 0x71;
		item = GameHelper::GetItemAtWorldCoords(GameHelper::GetCurrentMap(), x, y, 0);
		if (item == nullptr) return;
		pkt->placeID = *item;
		pkt->showID = drop->placeID == 0x7FFE ? 0x2001 : drop->placeID;
		pkt->paramFlags = 0x8;
		diffX = drop->wX - x;
		diffY = drop->wY - y;
		pkt->flags = (((diffX + 4) & 0xF) | (((diffY + 4) & 0xF) << 4));
		pkt->u0 = 0;
		pkt->u1 = 0;
		pkt->u2 = 0;
		Process::Write32((u32)&pfunction1, 0x59E8F8);
		pfunction1((u32)drop);
		return;
	}
	
	u32 GameHelper::PlaceItem(u8 ID, u32 *ItemToReplace, u32 *ItemToPlace, u32 *ItemToShow, u8 worldx, u8 worldy, bool u0, bool u1, bool u2, bool u3, bool u4) {
		Process::Write32((u32)&pfunction11, 0x59E5B4);
		return pfunction11(ID, (u32)ItemToReplace, (u32)ItemToPlace, (u32)ItemToShow, worldx, worldy, u0, u1, u2, u3, u4);
	}
	
	u32 Player::GetAnimationInstance(u32 playerInstance, u8 someVal1, u8 someVal2, u32 encVal) {
		Process::Write32((u32)&pfunction4, 0x6561F0);
		return pfunction4(playerInstance, someVal1, someVal2, encVal);
	}
	
	float *GameHelper::WorldCoordsToCoords(u8 wX, u8 wY, float res[3]) {
		volatile float *coords = Player::GetCoordinates();
		if (coords != nullptr) res[1] = *(volatile float *)((u32)coords + 4);
		res[0] = (float)(wX * 0x20 + 0x10);
		res[2] = (float)(wY * 0x20 + 0x10);
		return &res[0];
	}
	
	void Player::SendAnimPacket(u8 senderIndex, u32 animObj, u8 animID, u8 roomID, u8 targetPlayerIndex) {
		Process::Write8(animObj, roomID);
		Process::Write8(animObj + 1, animID);
		Process::Write32(0x62764C, 0xE3A01000 + targetPlayerIndex); // in sendPkt Function GetOnlinePlayerIndex inline
		Process::Write8(0x5C25E4, targetPlayerIndex);
		Sleep(Milliseconds(5));
		Process::Write32((u32)&pfunction2, 0x5C25B4);
		pfunction2(targetPlayerIndex, animObj);
		Sleep(Milliseconds(5));
		Process::Write32(0x62764C, 0xE5D11268);
		Process::Write8(0x5C25E4, 4);
	}
	
	bool Player::ExecuteAnimation(u32 pPlayerObj, u8 animID, u32 pAnimObj, bool u0) {
		Process::Write32((u32)&pfunction4, 0x64C688);
		return pfunction4(pPlayerObj, animID, pAnimObj, u0);
	}
	
	u32 Camera::GetInstance() {
		return *(u32 *)0x94A880;
	}
	
	void Camera::AddToX(float val) {
		*(float *)(Camera::GetInstance() + 4) += val;
	}
	
	void Camera::AddToY(float val) {
		*(float *)(Camera::GetInstance() + 8) += val;
	}
	
	void Camera::AddToZ(float val) {
		*(float *)(Camera::GetInstance() + 0xC) += val;
	}
	
	void Camera::AddToYRotation(u16 val) {
		*(u16 *)(Camera::GetInstance() + 0x1C) += val;
	}
		
	void GameHelper::Particles(u32 particleID, float *floats, u32 u0, u32 u1) {
		if (floats == nullptr) return;
		Process::Write32((u32)&pfunction4, 0x207AD0);
		pfunction4(particleID, (u32)floats, u0, u1);
	}
	
	bool GameHelper::PlaceItemWrapper(u8 ID, u32 ItemToReplace, u32 *ItemToPlace, u32 *ItemToShow, u8 worldx, u8 worldy, bool u0, bool u1, bool u2, bool u3, bool u4, u8 waitAnim, u8 roomID) {
		Process::Write32((u32)&pfunction5, 0x5979E4);
		static Hook h;
		float coords[3];
		u32 crashPreventItem = Player::GetLocation() != 0xFF ? 0x2001 : 0x80007FFE;
		u8 autoWaitAnim = waitAnim;
		u32 player = Player::GetInstance(4, 1);
		u32 *pItemAtCoords = GameHelper::GetItemAtWorldCoords(GameHelper::GetCurrentMap(), worldx, worldy, 0);
		u32 *actualItemToPlace = useDropChain ? ItemSequence::Next() : ItemToPlace;
		u32 *actualItemToShow = useDropChain ? actualItemToPlace : ItemToShow;
		u32 animInstance;
		u8 currentIndex = GameHelper::GetOnlinePlayerIndex();
		bool forced = (currentIndex != GameHelper::GetActualPlayerIndex()) && (GameHelper::GetActualPlayerIndex() <= 3);
		if (GameHelper::GetLockedSpotIndex(worldx, worldy, roomID) != 0xFFFFFFFF) return 0;
		if (pItemAtCoords == nullptr) return 0;
		u32 *actualItemToReplace = ItemToReplace == 0xFFFFFFFF ? pItemAtCoords : &ItemToReplace;
		if (*actualItemToReplace != *pItemAtCoords && !(*actualItemToReplace == 0x7FFE && *pItemAtCoords == 0x80007FFE)) return 0;
		if (Player::GetLocation() == 0xFF && (*actualItemToPlace == 0x207A || *actualItemToPlace == 0x2079)) return 0;
		if (Player::GetLocation() != 0xFF && (*actualItemToPlace <= 0xFF || (*actualItemToPlace & 0x80000000) != 0 || ID == 8 || ID == 9 || ID == 0xE || ID == 0xF)) return 0;
		if (ID == 9 || ID == 0xF) *actualItemToReplace = 0x26;
		if (ID == 8 || ID == 0xE) *actualItemToReplace = 0x3E;
		if (ID == 3 || ID == 4 || ID == 5) *actualItemToReplace = 0x2001;
		if (roomID != 0xA5) {
			*(vu32 *)0x59EC90 = 0xE3A00000 + roomID;
			for (u8 i = 0; i < 4; i++) {
				if (Player::Exists(i) && Player::GetRoom(i) == roomID) {
					Process::Write32(0x59EBF8, 0xE3A00000 + i);
				}
			}
			Sleep(Milliseconds(5));
		}
		if (ID == 0x21) {
			if (player == 0) return 0;
			if (!h.flags.isEnabled) {
				Process::Write32(0x59EDD8, 0xE1A00000);
				Sleep(Milliseconds(5));
				h.Initialize(0x59EDD8, (u32)&pseudoType0x21);
				h.Enable();
			}
			Sleep(Milliseconds(5));
		}
		else {
			h.Disable();
			Process::Write32(0x59EDD8, 0xEB000019);
		}
		GameHelper::PlaceItem(ID == 0x21 ? 0xF : ID, *actualItemToReplace == 0x7FFE ? &crashPreventItem : actualItemToReplace, *actualItemToPlace == 0x7FFE && ID != 0x1C && !(ID >= 0x6 && ID <= 0x9) && ID != 0xE && ID != 0xF ? &crashPreventItem : actualItemToPlace, *actualItemToShow == 0x7FFE && ID != 0x1C && !(ID >= 0x6 && ID <= 0x9) && ID != 0xE && ID != 0xF ? &crashPreventItem : actualItemToShow, worldx, worldy, u0, u1, ID == 0x8 || ID == 0xE ? 1 : 0, u3, u4);
		if (roomID != 0xA5) {
			Sleep(Milliseconds(5));
			Process::Write32(0x59EC90, 0xEBF5624D);
			Process::Write32(0x59EBF8, 0xEBF59CDB);
		}
		if (!(ID >= 0xa && ID <= 0xd) && ID != 0x22) {
			bool noWait = false;
			if (player == 0) return 0;
			animInstance = Player::GetAnimationInstance(player, 0, 0, 0);
			*(u32 *)(player + 0x844) = 0;
			*(u8 *)(player + 0x8CC) = ID;
			if (waitAnim == 0x5D || waitAnim == 0x6B || waitAnim == 0x4F || waitAnim == 0x4C || waitAnim == 0x50 || waitAnim == 0x52 || waitAnim == 0x5A || waitAnim == 0x5F || waitAnim == 0x60 || waitAnim == 0x61 || waitAnim == 0x7E || waitAnim == 0x87 || waitAnim == 0xAC)
				noWait = true;
			if (waitAnim == 0x3D || waitAnim == 0x40 || waitAnim == 0x41) {
				noWait = true;
				goto noWaitPick;
			}
			if (ID >= 0x1 && ID <= 0x6 && !noWait) {
				if (forced) {
					switch (ID) {
					case 1:
					case 2:
						autoWaitAnim = 0x3D;
						break;
					case 3:
					case 4:
					case 5:
						autoWaitAnim = 0x41;
						break;
					case 6:
						autoWaitAnim = 0x40;
						break;
					}
				}
				else {
					autoWaitAnim = 0x3C;
				}
				noWaitPick:
				Process::Write32(animInstance + 0xE, *(u32 *)actualItemToReplace);
				Process::Write8(animInstance + 0x12, ID == 0x21 ? *(u8 *)(player + 0x47C) : worldx);
				Process::Write8(animInstance + 0x13, ID == 0x21 ? *(u8 *)(player + 0x480) : worldy);
				Process::Write8(animInstance + 0x15, ID);
				Process::Write32((u32)&pfunction2, 0x5D3504);
				pfunction2(animInstance + 0x17, (u32)Player::GetCoordinates(currentIndex));
			}
			else {
				*(u8 *)(animInstance + 0xE) = ID == 0x21 ? *(u8 *)(player + 0x47C) : worldx;
				*(u8 *)(animInstance + 0xF) = ID == 0x21 ? *(u8 *)(player + 0x480) : worldy;
				*(u16 *)(animInstance + 0x10) = *(u16 *)actualItemToReplace == 0x7FFE ? 0x2001 : *(u16 *)actualItemToReplace;
				if (waitAnim == 0x60 || waitAnim == 0x61) {
					volatile float *pCoords = Player::GetCoordinates();
					if (pCoords != nullptr) {
						*pCoords = worldx * 0x20 + 0x10;
						*((float *)((vu32)pCoords + 8)) = worldy * 0x20 + 0x10;
					}
				}
				if (ID == 0x7 && !noWait && waitAnim != 0x5C && waitAnim != 0x6A) autoWaitAnim = forced ? 0x5D : 0x5C;
				else if (ID >= 0x8 && ID <= 0xF && !noWait && waitAnim != 0x6A) autoWaitAnim = forced ? 0x6B : 0x6A;
				else if (forced && !noWait) autoWaitAnim = 0x4C;
				if (((ID >= 0x13 && ID <= 0x1C) || autoWaitAnim == 0x4A) && !noWait && !forced) {
					autoWaitAnim = 0x4A;
					*(u32 *)0x680F28 = 0xE3A00000;
					Process::Write16(animInstance + 0x10, ID);
					Sleep(Milliseconds(5));
				}
				else if (forced) autoWaitAnim = 0x4F;
			}
			if (waitAnim == 0x87) {
				Process::Write32((u32)&pfunction2, 0x5D3504);
				pfunction2(animInstance + 0xE, (u32)GameHelper::WorldCoordsToCoords(worldx, worldy + 1, coords));
				Process::Write8(animInstance + 0x12,0xC0);
				Process::Write8(animInstance + 0x13, 0);
				Process::Write8(animInstance + 0x14, 2);
			}
			else if (waitAnim == 0xAC) {
				Process::Write32((u32)&pfunction2, 0x5D3504);
				pfunction2(animInstance + 0xE, (u32)GameHelper::WorldCoordsToCoords(worldx, worldy + 1, coords));
				Process::Write8(animInstance + 0x12, 0);
				pfunction2(animInstance + 0x13, (u32)GameHelper::WorldCoordsToCoords(worldx, worldy + 1, coords));
				Process::Write8(animInstance + 0x17, 0);
				Process::Write8(animInstance + 0x18, 2);
			}
			else if (waitAnim == 0x7E) {
				Process::Write32((u32)&pfunction2, 0x5D3504);
				pfunction2(animInstance + 0xF, (u32)GameHelper::WorldCoordsToCoords(worldx, worldy - 1, coords));
				Process::Write8(animInstance + 0x13, 0);
				pfunction2(animInstance + 0x17, (u32)GameHelper::WorldCoordsToCoords(worldx, worldy - 1, coords));
				Process::Write8(animInstance + 0x16, 1);
				Process::Write16(animInstance + 0x14, 2);
			}
			if (currentIndex == GameHelper::GetActualPlayerIndex()) Player::ExecuteAnimation(player, autoWaitAnim, animInstance, 0);
			else Player::SendAnimPacket(GameHelper::GetActualPlayerIndex(), animInstance, autoWaitAnim, roomID == 0xA5 ? Player::GetRoom(currentIndex) : roomID, currentIndex);	
			if (!noWait) {
				Sleep(Milliseconds(40));
				*(u32 *)0x680F28 = 0xEBFC52D7;
			}
		}
		return true;
	}

}

