#include "cheats.hpp"
#include "adrs.h"
#include "csvc.h"

void abort(void);

namespace CTRPluginFramework
{
	void patches(void)
	{
		const u32 nop = 0xE1A00000;
		const u32 dropReplaceSwitchAddr = USA0x005A1120;
		int		choice, code, n;
		u8		*house_base;
		char	buf[300];
		
		// 「ここにはもう置けないヨ」を非表示にする
		Process::Write32(0x19df08, 0xe1a00000);
		
		// inventory base
		Process::Write32( USA0x0019B694, nop );
		Process::Write32( USA0x0019BF2C, nop );
		Process::Write32( USA0x0019BA78, nop );
		Process::Write32( USA0x0019B988, nop );
		Process::Write32( USA0x0019C050, nop );
		Process::Write32( USA0x00725124, nop );
		
		// items2money
		Process::Write32( USA0x0019B5BC, 0xE3A06001 );
		
		// drop
		Process::Write32( USA0x0059FCA4, 0xEA000004 );
		
		// drop replace
		for( int i = 0; i <= 0x21; i++ )
			Process::Write32( USA0x005A0F54 + i * 4, dropReplaceSwitchAddr );
		
		// drop everywhere
		Process::Write32( USA0x001655EC, 0xE3A00001 );
		Process::Write32( USA0x001655F8, 0xEA000006 );
		Process::Write32( USA0x001654EC, 0xEA000005 );
		Process::Write32( USA0x00165580, 0xEA000010 );	// on other players
		
		// host drop
		Process::Write32( USA0x005A1454, nop );			// create locked spot pkt send
		Process::Write32( USA0x005A12F4, nop );			// clear locked spot pkt send
		Process::Write32( USA0x0059FF5C, 0xEA000010 );	// pkt is from host
		Process::Write32( USA0x0059FD98, 0xEA000003 );	// bypass check in USA0x59FC7C
		Process::Write32( USA0x005983F4, nop );			// unnecessary?
		Process::Write32( USA0x005984DC, nop );			// unnecessary?
		Process::Write32( USA0x0059F8A0, nop );
		Process::Write32( USA0x005A09B0, 0xEA000022 );	// item tree drop
		Process::Write32( USA0x005A0DF4, 0xEA00002D );	// fruit tree drop
	}
	
	bool Boot()
	{
		if ( Process::GetTitleID() != 0x4000000086200 )
		{
			(MessageBox("THIS GAME IS NOT SUPPORTED!!!!!"))();
			return false;
		}
		
		patches();
		
		return true;
	}
}




