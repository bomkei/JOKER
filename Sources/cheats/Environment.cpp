#include "cheats.hpp"

namespace CTRPluginFramework
{
	// ---------------------------------------------------------------
	// 村のアイテムを全部消す
	// ---------------------------------------------------------------
	void DeleteAllItem(MenuEntry* e)
	{
		if ( !e->Hotkeys[0].IsDown() && !READU16(0x95133a) == 0xa500 ) return;
		
		for ( int x = 0x10; x < 0x60; x++ )
			for ( int y = 0x10; y < 0x60; y++ )
				Game::SetWorldItem(0x7ffe, x, y);
		
		Process::Write32(0x94844c, 0x100);
		Process::Write32(0x948450, 0x100);
		Process::Write32(0x94a3d0, 0x10001);
		Process::Write32(0x951338, 0x10100);
	}


	// ---------------------------------------------------------------
	// リロード
	// ---------------------------------------------------------------
	void GameReload(MenuEntry* e)
	{
		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys()) && READU16(0x95133a) == 0xa500)
		{
			Process::Write32(0x94844c, 0x100);
			Process::Write32(0x948450, 0x100);
			Process::Write32(0x94a3d0, 0x10001);
			Process::Write32(0x951338, 0x10100);
		}
	}


	
}

