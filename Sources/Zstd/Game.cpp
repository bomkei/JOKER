#include "3ds.h"
#include "CTRPluginFramework.hpp"
#include "Zstd/Game.hpp"

using namespace CTRPluginFramework;

namespace Zstd
{
	void Game::SetCameraPos(Coordinates c)
	{
		Coordinates *cr = reinterpret_cast<Coordinates*>(0x97f6f4);
		cr->x = c.x;
		cr->y = c.y;
		cr->z = c.z;
		delete cr;
	}
	
	Coordinates Game::GetCameraPos()
	{
		Coordinates c;
		c.x = *(float*)(0x97f6f4);
		c.y = *(float*)(0x97f6f8);
		c.z = *(float*)(0x97f6fc);
		return c;
	}
	
	u32 Game::CameraAddrPtr()
	{
		return (*(u32*)0x94a880) + 0x12c;
	}
	
	u16 *Game::CameraRotX()
	{
		return (u16*)(CameraAddrPtr());
	}
	
	u16 *Game::CameraRotY()
	{
		return (u16*)(CameraAddrPtr() + 2);
	}
	
	u16 Game::GetWorldItem(int x, int y)
	{
		u16 item;
		Process::Read16(_get_world_item_pos(x, y), item);
		return item;
	}
	
	void Game::SetWorldItem(u16 item, int x, int y)
	{
		Process::Write16(_get_world_item_pos(x, y), item);
	}
	
	
	u32 Game::_get_world_item_pos(int x, int y)
	{
		u32 wx = x - 0x10;
		u32 wy = y - 0x10;
		u32 reg0, reg1;
		
		reg0 = wx % 0x10;
		wx /= 0x10;
		reg0 *= 0x4;
		wx *= 0x400;
		
		reg1 = wy % 0x10;
		wy /= 0x10;
		reg1 *= 0x40;
		wy *= 0x1400;
		
		return 0x31f9ced8 + (reg0 + reg1 + wx + wy);
	}
	
	
	
	
}

