#include "cheats.hpp"

namespace CTRPluginFramework
{
	// ---------------------------------------------------------------
	// サーバー変更
	// ---------------------------------------------------------------
	void ChangeIslandServer(MenuEntry* e) {
		Keyboard key("", { "日本", "イギリス", "韓国", "フランス", "アメリカ" });

		int r = key.Open();
		if (r == 0) Process::Write32(0x34f8f8, 0xe3a00001);
		if (r == 1) Process::Write32(0x34f8f8, 0xe3a0006e);
		if (r == 2) Process::Write32(0x34f8f8, 0xe3a00088);
		if (r == 3) Process::Write32(0x34f8f8, 0xe3a0004d);
		if (r == 4) Process::Write32(0x34f8f8, 0xe3a00031);
	}


	// ---------------------------------------------------------------
	// 乗っ取り
	// ---------------------------------------------------------------
	void IslandPlayerHijack(MenuEntry* e) {
		if (Controller::IsKeysPressed(L + DU)) Process::Write32(0x32018440, 0); // 1p
		if (Controller::IsKeysPressed(L + DR)) Process::Write32(0x32018440, 1); // 2p
		if (Controller::IsKeysPressed(L + DD)) Process::Write32(0x32018440, 2); // 3p
		if (Controller::IsKeysPressed(L + DL)) Process::Write32(0x32018440, 3); // 4p
	}


}

