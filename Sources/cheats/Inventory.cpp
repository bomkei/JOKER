#include "Helpers/OSDManager.hpp"
#include "cheats.hpp"

namespace CTRPluginFramework
{

	// ---------------------------------------------------------------
	// 未使用アイテムを表示
	// ---------------------------------------------------------------
	void DisableItemLocks(MenuEntry* e)
	{
		Keyboard key("", { "オン", "オフ" });
		int r = key.Open();

		if (r == 0) {
			Process::Write32(0x7238c0, 0xe1a00000);
			Process::Write32(0xad0250, 0x01000000);
		}
		else if (r == 1) {
			Process::Write32(0x7238c0, 0x0a000001);
			Process::Write32(0xad0250, 0x00000000);
		}
	}


	// ---------------------------------------------------------------
	// 置いても無くならない
	// ---------------------------------------------------------------
	void InfinityItem(MenuEntry* e)
	{
		Keyboard key("", { "オン", "オフ" });
		int r = key.Open();

		if (r == 0)
		{
			Process::Write32(0x0019C4D0, 0x00000000);
			Process::Write32(0x0019C42C, 0x00000000);
		}
		else if (r == 1)
		{
			Process::Write32(0x0019C4D0, 0xEB057D0A);
			Process::Write32(0x0019C42C, 0xEB057D33);
		}
	}


	// ---------------------------------------------------------------
	// 全て削除
	// ---------------------------------------------------------------
	void DeleteInvItems(MenuEntry* e)
	{
	
	}


	// ---------------------------------------------------------------
	// 選択変更
	// ---------------------------------------------------------------
	void InvItemOption(MenuEntry* e)
	{
		u32 addresses[4 * 3] =
		{
			0x19b9d8, 0xe1a00000, 0x1a000012,
			0x19bfc8, 0xe1a00000, 0x0a00001a,
			0x19c150, 0xe1a00000, 0x0a000009,
			0x19ba38, 0xe1a00000, 0x1a000012
		};

		std::vector<std::string> option =
		{
			"見せびらかす",
			"壁掛け & 床に飾る",
			"食べる",
			"手紙を書く"
		};

		Keyboard addr_input(option);
		Keyboard value_input("", { "追加", "削除" });

		int r = addr_input.Open();
		if (r >= 0)
		{
			int r2 = value_input.Open();
			if (r2 >= 0)
			{
				Process::Write32(addresses[r * 3], addresses[r * 3 + (r2 + 1)]);
			}
		}
	}


	// ---------------------------------------------------------------
	// コピー
	// ---------------------------------------------------------------
	void Copy(MenuEntry* e)
	{
		
	}


	// ---------------------------------------------------------------
	// アイテム取得
	// ---------------------------------------------------------------
	void TextToItem(MenuEntry* e)
	{
		u16 item;
		Keyboard key("アイテムID");
		
		if ( e->Hotkeys[0].IsDown() && key.Open(item) != -1 )
		{
			Player p;
			p.SetItem(item, 0);
		}
	}


	// ---------------------------------------------------------------
	// アイテムID表示
	// ---------------------------------------------------------------
	void ViewSlotItems(MenuEntry* e)
	{
		/*		
		u32 CheckBottomScreen, items[16];
		std::vector<std::string> items_str;

		Process::Read32(0x946be8, CheckBottomScreen);
		if (CheckBottomScreen < 0x8f90 || CheckBottomScreen > 0x11000) return;

		items_str.clear();
		for (int i = 0; i < 16; i++)
		{
			items[i] = Inventory::ReadItem(i);
			items_str.push_back(Utils::Format("%04X", items[i]));
		}

		_OSDManager& manager = OSDManager;
		manager.Lock();
		Screen* scr = new Screen();
		scr->IsTop = false;

		scr->Draw(items_str[0], 5, 120);// slot 0
		scr->Draw(items_str[1], 5 + 50, 120);// slot 1
		scr->Draw(items_str[2], 5 + 50 * 4, 120);// slot 2
		scr->Draw(items_str[3], 5 + 50 * 5, 120);// slot 3

		// 4<
		for (int x = 0; x < 6; x++)
			for (int y = 0; y < 2; y++)
				scr->Draw(items_str[4 + (x + y * 6)], 5 + x * 50, 161 + y * 41);

		scr->IsTop = true;
		delete scr;
		manager.Unlock();
		*/
	}

	
}

