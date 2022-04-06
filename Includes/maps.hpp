#pragma once

namespace CTRPluginFramework
{
	struct NAME_VALUE_MAP
	{
		const char	*name;
		const u32	value;
	};
	
	struct BADGE_MAP
	{
		const u32	hex;
		const u32	hex2;
		const u32	hex3;
		const u32	hex4;
		const u32	hex5;
		const u32	hex6;
		const char	*name;
	};
	
	struct ITEM_MAP
	{
		const u16	code;	// アイテムID
		const char	*name1; // 表示用
		const char	*name2; // 検索用
	};
	
	
	
}


