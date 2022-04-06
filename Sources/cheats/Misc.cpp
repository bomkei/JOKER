#include "Helpers.hpp"
#include "cheats.hpp"
#include "kanji.h"

extern "C" void LoadBottomUI(void);

u32 g_bottomUI;
u32 g_bottomReturn;

namespace CTRPluginFramework
{
	// ---------------------------------------------------------------
	// 村の明るさ変更
	// ---------------------------------------------------------------
	void akarusa_change(MenuEntry* e) {
		float level;
		
		Keyboard keyboard("指定した明るさに変化。");
		if (keyboard.Open(level) >= 0) Process::WriteFloat(0x1E6CB4, level);
	}


	// ---------------------------------------------------------------
	// ゲーム速度上昇
	// ---------------------------------------------------------------
	void FastGameSpeed(MenuEntry* e) {
		Keyboard key("", { "オン", "オフ" });

		int r = key.Open();

		if (r == 0) Process::Write32(0x54c6e8, 0xe3e004ff);
		if (r == 1) Process::Write32(0x54c6e8, 0xe59400a0);
	}


	// ---------------------------------------------------------------
	// カメラ操作
	// ---------------------------------------------------------------
	void MoveCamera(MenuEntry* e) {
		static bool locked;

		// カメラ座標のXYZを構造体に取得する
		static Coordinates* const cameraCoord = reinterpret_cast<Coordinates* const>(0x97f6f4);

		// カメラポインタ( 0x12Cを加算して使う )
		// 外: 0x3309c164
		// 中: 0x3309c290
		const u32 CameraPtr = (*(u32*)0x94a880) + 0x12c;

		// X回転度のアドレス
		const u32 rot_x = CameraPtr;

		// Y回転度のアドレス
		const u32 rot_y = rot_x + 2;

		// 回転速度
		const u32 rot_speed = 0x60;

		// 十字キーで移動するときのスピード
		const float move_spd = 8;

		// カメラ回転を強制的に可能にする
		const u32 nop = 0xE1A00000;
		Process::Patch(0x1a3190, (u8*)&nop, 4);
		Process::Patch(0x1a319c, (u8*)&nop, 4);

		// カメラ固定
		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys())) {
			if (!locked) {
				locked = true;
				Process::Write32(0x762ca4, 0xea000020);
				Process::Write32(0x47d170, 0x3fd00000);
				OSD::Notify("Camera Lock");
			}
			else {
				locked = false;
				Process::Write32(0x762ca4, 0x2a000020);
				Process::Write32(0x47d170, 0x40000000);
				OSD::Notify("Camera Unlock");
			}
		}

		// R
		if (e->Hotkeys[1].IsDown()) {
			// X軸の回転
			if (Controller::IsKeyDown(CU)) ADD16(rot_x, rot_speed);
			if (Controller::IsKeyDown(CD)) SUB16(rot_x, rot_speed);

			// Y軸の回転
			if (Controller::IsKeyDown(CL)) ADD16(rot_y, rot_speed);
			if (Controller::IsKeyDown(CR)) SUB16(rot_y, rot_speed);

			// 範囲制限
			if (*Game::CameraRotX() < 0) *Game::CameraRotX() = 0xffff;
			if (*Game::CameraRotY() < 0) *Game::CameraRotY() = 0xffff;
			if (*Game::CameraRotX() > 0xffff) *Game::CameraRotX() = 0;
			if (*Game::CameraRotY() > 0xffff) *Game::CameraRotY() = 0;
		}

		// B
		if (e->Hotkeys[2].IsDown() && locked) {
			if (Controller::IsKeyDown(DU)) cameraCoord->z -= move_spd;
			if (Controller::IsKeyDown(DD)) cameraCoord->z += move_spd;
			if (Controller::IsKeyDown(DL)) cameraCoord->x -= move_spd;
			if (Controller::IsKeyDown(DR)) cameraCoord->x += move_spd;
			if (Controller::IsKeyDown(R)) cameraCoord->y -= move_spd;
			if (Controller::IsKeyDown(L)) cameraCoord->y += move_spd;
		}
	}


	// ---------------------------------------------------------------
	// 遠距離カメラ
	// ---------------------------------------------------------------
	void FarCamera(MenuEntry* e) {
		Keyboard key("", { "オン", "オフ" });
		int r = key.Open();
		if (r == 0) Process::Write32(0x47d170, 0x3fd00000);
		if (r == 1) Process::Write32(0x47d170, 0x40000000);
	}


	// ---------------------------------------------------------------
	// 花や木のサイズ変更
	// ---------------------------------------------------------------
	void ChangeFlowerTreeSize(MenuEntry* e) {
		Keyboard key("default = 1.0");
		float size;
		if (key.Open(size) == 0) Process::WriteFloat(0x5901a4, size);
	}


	// ---------------------------------------------------------------
	// 画面崩壊
	// ---------------------------------------------------------------
	void CrazyScreen(MenuEntry* e) {
		Keyboard key("", { "オン", "オフ" });
		int r = key.Open();
		if (r == 0) Process::Write32(0x569530, 0x40130020);
		if (r == 1) Process::Write32(0x569530, 0x40000000);
	}


	// ---------------------------------------------------------------
	// 室内の家具動かす
	// ---------------------------------------------------------------
	void MoveFurniture(MenuEntry* e) {
		if (READU32(0x33099f84) == -1) {
			(MessageBox("屋外では実行できません"))();
			return;
		}

		static u16 area;

		Keyboard key("", { "ON", "OFF" });
		int r = key.Open();

		if (r == 0) {
			area = READU16(0x95133a);
			Process::Write32(0x95133a, 0xa503);
		}

		if (r == 0)
			Process::Write32(0x95133a, area);
	}


	// ---------------------------------------------------------------
	// 天気変更
	// ---------------------------------------------------------------
	void ChangeWeather(MenuEntry* e) {
		Keyboard key("",
			{
				"晴れ(雲なし)",
				"晴れ(雲あり)",
				"くもり空",
				"雨(小)",
				"雨",
				"雪(小)",
				"雪",
			});

		int r = key.Open();

		if (r >= 0) {
			Process::Write32(0x0062e728, 0xe3a00000 + r);
			Process::Write32(0x00949530, 0x1000000 * r);
		}
	}


	// ---------------------------------------------------------------
	// キーボード改行
	// ---------------------------------------------------------------
	void KeyboardExtender(MenuEntry* e) {
		Process::Write32(0x00AD0250, 0x1000000);
	}


	// ---------------------------------------------------------------
	// チャットコピペ
	// ---------------------------------------------------------------
	void ChatCopyPaste(MenuEntry* e) {
		static std::string data;
		Chat chat;
		
		if ( !chat.IsOpened() ) return;
		
		if ( e->Hotkeys[0].IsDown() )
			data = chat.Read();
		else if ( e->Hotkeys[1].IsDown() )
		{
			chat.Write(data);
			chat.Send();
		}
	}
	
	
	// ---------------------------------------------------------------
	// 漢字変換
	// ---------------------------------------------------------------
	void KanjiHenkan(MenuEntry *e)
	{
		Chat chat;
		
		if ( !chat.IsOpened() || !Controller::IsKeyPressed(X) )
			return;
		else if ( chat.Read() == "" )
		{
			(MessageBox("文字がありません"))();
			return;
		}
		
		int pos, result;
		u16 Kanji16[10], Hiragana16[10];
		
		string SelectedStr = chat.GetSelectedString();
		string Left = chat.GetUnselectedString(0);
		string Right = chat.GetUnselectedString(1);
		
		chat.Change(4);
		vector<string> henkan_moji;
		henkan_moji.clear();
		
		for ( const KANJI_MAP& k : s_kanji )
			if ( k.kana == SelectedStr ) henkan_moji.push_back( k.kanji );
		
		Keyboard key("", henkan_moji);
		result = key.Open();
		
		if ( result >= 0 )
			chat.Write(Left + henkan_moji[result] + Right);
	}

	
	// ---------------------------------------------------------------
	// アドレス監視
	// ---------------------------------------------------------------
	void ViewAddress(MenuEntry* e) {
		int r0, r1;

		// アドレス
		static u32 addr = 0x33099e50;

		// アドレスリスト
		static std::vector<u32> addrs = { 0x33099e50, 0x33099e58 };

		// アドレス変更
		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys())) {
			Keyboard key("アドレス変更");
			key.Open(addr);
		}

		// リストに追加
		if (Controller::IsKeysPressed(e->Hotkeys[1].GetKeys())) {
			if (addrs.size() >= 10) {
				(MessageBox("10個まで。"))();
				return;
			}
			addrs.push_back(addr);
		}

		// リスト変更
		if (e->Hotkeys[2].IsDown()) {
			std::vector<std::string> addrsStr = {};

			for (int i = 0; i < addrs.size(); i++)
				addrsStr.push_back(Utils::ToHex(addrs[i]));

			addrsStr.push_back("すべて削除");

			Keyboard key("リスト変更", addrsStr);
			r0 = key.Open();
			OSD::SwapBuffers();

			// すべて削除
			if (r0 == addrs.size())
				addrs.clear();

			// 変更、または削除
			else if (r0 >= 0) {
				int number = r0;

				Keyboard key("", { "変更", "削除" });
				r0 = key.Open();

				OSD::SwapBuffers();

				if (r0 == 0) {
					Keyboard change("");
					change.Open(addrs[number], addrs[number]);
				}
				else if (r0 == 1) {
					addrs.erase(addrs.begin() + (number - 1));
				}
			}
		}

		_OSDManager& manager = OSDManager;
		manager.Lock();
		const Screen &scr = OSD::GetTopScreen();

		u32 value;
		Process::Read32(addr, value);
		scr.Draw(Utils::ToHex(addr) + ": " + Utils::ToHex(value), 4, 0);
		if (addrs.size() > 0) {
			for (int i = 0; i < addrs.size(); i++) {
				Process::Read32(addrs[i], value);
				scr.Draw(Utils::Format("(%d)%08X: %08X", i, addrs[i], value), 0, 14 + i * 10);
			}
		}

		manager.Unlock();
	}


	// ---------------------------------------------------------------
	// HEXエディタ
	// ---------------------------------------------------------------
	void HexEditor(MenuEntry *entry)
	{
		static u32 address = 0x33099e50;
		u32 edit_value, jump_addr;
		const int view_length = 10;
		static int sx, sy;
		u32 tmp;
		
		u32 now_addr = address + sy * 0x10 + sx * 0x4;
		
		// Xをおしながら十字キーで編集の場所変更
		if ( Controller::IsKeyDown(X) )
		{
			if ( Controller::IsKeyPressed(DU) ) sy--;
			if ( Controller::IsKeyPressed(DD) ) sy++;
			if ( Controller::IsKeyPressed(DL) ) sx--;
			if ( Controller::IsKeyPressed(DR) ) sx++;
			
			if ( sx < 0 ) sx = 0;
			if ( sx > 3 ) sx = 3;
			
			if ( sy < 0 ) sy = 0;
			if ( sy > 9 ) sy = 9;
		}
		
		// Yを押しながら十字キーの上/下でスクロール
		if ( Controller::IsKeyDown(Y) )
		{
			if ( Controller::IsKeyPressed(DU) ) address -= 0x10;
			if ( Controller::IsKeyPressed(DD) ) address += 0x10;
		}
		
		// ジャンプ
		if ( Controller::IsKeysDown(X + Y) )
		{
			Keyboard key("ジャンプ");
			if ( key.Open( jump_addr, address ) == 0 )
			{
				address = jump_addr;
			}
		}
		
		// 編集
		if ( Controller::IsKeyPressed(A) )
		{
			Keyboard key("値を編集");
			if ( key.Open( edit_value, *(u32 *)(now_addr) ) == 0 )
			{
				Process::Write32(now_addr, edit_value);
			}
		}
		
		_OSDManager& manager = OSDManager;
		manager.Lock();
		
		const Screen &scr = OSD::GetTopScreen();
		
		for ( int i = 0; i < view_length; i++ )
		{
			scr.Draw(Utils::Format("%08X:", address + i * 0x10), 0, i * 10);
			for ( int x = 0; x < 4; x++ )
			{
				Color c = Color::Black;
				if ( x == sx && i == sy ) c = Color::Blue;
				
				if ( Process::Read32((address + i * 0x10 + x * 0x4), tmp) )
					scr.Draw(Utils::Format("%08X", tmp), (6 * 10 + 1) + x * ((6 * 9) + 1), i * 10, Color::White, c);
				else
					scr.Draw("????????", (6 * 10 + 1) + x * ((6 * 9) + 1), i * 10, Color::White, c);
			}
		}
		
		manager.Unlock();
	}

	void DrawRegisters(const Screen &scr)
	{
		CpuRegisters c;
		
		std::vector<std::string> str;
		str.clear();
		
		for ( int i = 0; i < 13; i++ )
			str.push_back( Utils::Format("r%-4d: %08X", i, c.r[i]) );

		str.push_back( Utils::Format("sp   : %08X", c.sp) );
		str.push_back( Utils::Format("lr   : %08X", c.lr) );
		str.push_back( Utils::Format("pc   : %08X", c.pc) );
		str.push_back( Utils::Format("cpsr : %08X", c.sp) );
		
		int i = 0;
		for ( const std::string &s: str )
		{
			scr.Draw( s, 4, 2 + i * 10 );
			i++;
		}
	}
		
	void Sleep(MenuEntry *e)
	{
		if ( !Controller::IsKeyPressed(L) ) return;
		
		Process::Pause();
		
		const Screen &scr = OSD::GetTopScreen();
		
		while ( true )
		{
			Controller::Update();
			
			if ( Controller::IsKeyPressed(R) ) break;
			
			if ( Controller::IsKeyPressed(DR) )
				Process::Play(1);
			
			DrawRegisters(scr);
			
			OSD::SwapBuffers();
		}
		
		Process::Play();
		
	}
		
	

}

