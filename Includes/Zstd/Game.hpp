#pragma once

namespace Zstd
{
	class Game
	{
	public:
		
		static void SetCameraPos(Coordinates);	// カメラ座標設定
		static Coordinates GetCameraPos();		// カメラ座標取得
		
		static u32 CameraAddrPtr();				// カメラ回転度を管理するアドレスのポインタ
		static u16 *CameraRotX();				// カメラ回転X
		static u16 *CameraRotY();				// カメラ回転Y
		
		static u16 GetWorldItem(int, int);
		static void SetWorldItem(u16, int, int);
		
		
		
	private:
		static u32 _get_world_item_pos(int, int);
		static void _write_player(u32, u32);
		
	};


}

