#include "3ds.h"
#include "CTRPluginFramework.hpp"
#include "Zstd/Player.hpp"

namespace Zstd
{
	int Player::GetNumber()
	{
		u32 value = *(u32*)0xaa914c;
		u32 value2 = (value - 0x31f49aa0) / 0xa480;
		return value2;
	}
	
	void Player::SetNumber(int n)
	{
		*(u32*)0xaa914c = 0x31f49aa0 + n * 0xa480;
	}
	
	u16 Player::GetItem(int slot)
	{
		return *(u32*)(get_inv_addr() + slot * 0x4);
	}
	
	void Player::SetItem(u16 item, int slot)
	{
		*(u16*)(get_inv_addr() + slot * 0x4) = item;
	}
	
	Coordinates* Player::Coord()
	{
		return reinterpret_cast<Coordinates*>( 0x33099e50 + get12c() );
	}
	
	u32 Player::get_inv_addr()
	{
		return *(u32*)(0xaa914c) + 0x6bd0;
	}
	
	
	
	
	
}

