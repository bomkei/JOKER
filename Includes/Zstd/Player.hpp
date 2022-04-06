#pragma once

namespace Zstd
{
	class Player
	{
	public:
		// プレイヤ番号
		/*
		 * 0 村長
		 * 1 サブ1
		 * 2 サブ2
		 * 3 サブ3
		 */
		int  GetNumber();
		void SetNumber(int);
		
		// インベントリ
		u16  GetItem(int);		// アイテム取得
		void SetItem(u16, int);	// アイテム設定
		
		u16 *Hat();				// 帽子
		u16 *Accessories();		// アクセサリ
		u16 *Clothes();			// 服
		u16 *Pants();			// パンツ(ズボン)
		u16 *Socks();			// 靴下
		u16 *Shoes();			// 靴
		
		Coordinates *Coord();	// 座標
		
		// 座標(ブロック単位)
		u8 *Block_X();
		u8 *Block_Y();
		
		
		
	private:
		u32 get_inv_addr();
		
		
	};
	
	
	
}


