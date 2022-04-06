#include "cheats.hpp"

namespace CTRPluginFramework
{
	float CoordSpeed = 8.0;
	
	// 道具
	const struct NAME_VALUE_MAP Tool[] =
	{
		{ "レンタルスコップ"				, 0x3358 },
		{ "スコップ"						, 0x3359 },
		{ "銀のスコップ"					, 0x335A },
		{ "金のスコップ"					, 0x335B },
		{ "レンタル釣り竿"				, 0x3354 },
		{ "釣り竿"							, 0x3355 },
		{ "銀の釣り竿"					, 0x3356 },
		{ "金の釣り竿"					, 0x3357 },
		{ "レンタル網"					, 0x3350 },
		{ "網"								, 0x3351 },
		{ "銀の網"							, 0x3352 },
		{ "金の網"							, 0x3353 },
		{ "レンタル斧"					, 0x334C },
		{ "斧"								, 0x334D },
		{ "銀の斧"							, 0x334E },
		{ "金の斧"							, 0x334F },
		{ "レンタルジョウロ"				, 0x335C },
		{ "ジョウロ"						, 0x335D },
		{ "銀のジョウロ"					, 0x335E },
		{ "金のジョウロ"					, 0x335F },
		{ "レンタルパチンコ"				, 0x3360 },
		{ "パチンコ"						, 0x3361 },
		{ "銀のパチンコ"					, 0x3362 },
		{ "金のパチンコ"					, 0x3363 },
		{ "レンタルピコピコハンマー"	, 0x3364 },
		{ "ピコピコハンマー"				, 0x3365 },
		{ "コーヒー"						, 0x338C },
		{ "恵方巻"							, 0x338F },
		{ "豆"								, 0x338E },
		{ "クラッカー"					, 0x336A },
		{ "緑のスティックライト"		, 0x3399 },
		{ "黄色いスティックライト"		, 0x339B },
		{ "ピンクのスティックライト"	, 0x339A },
		{ "青いスティックライト"		, 0x3398 },
		{ "スパークリングサイダー"		, 0x338D },
		{ "青い風船"						, 0x3379 },
		{ "赤い風船"						, 0x3374 },
		{ "オレンジの風船"				, 0x3375 },
		{ "黄色い風船"					, 0x3376 },
		{ "ピンクの風船"					, 0x337B },
		{ "水色の風船"					, 0x3378 },
		{ "緑の風船"						, 0x3377 },
		{ "紫の風船"						, 0x337A },
		{ "青いウサギ風船"				, 0x3371 },
		{ "赤いウサギ風船"				, 0x336C },
		{ "オレンジウサギ風船"			, 0x336D },
		{ "黄色いウサギ風船" 			, 0x336E },
		{ "ピンクウサギ風船"				, 0x3373 },
		{ "水色ウサギ風船"				, 0x3370 },
		{ "緑のウサギ風船"				, 0x336F },
		{ "紫ウサギ風船"					, 0x3372 },
		{ "青いハート風船"				, 0x3379 },
		{ "赤いハート風船"				, 0x3381 },
		{ "オレンジハート風船"			, 0x337D },
		{ "黄色いハート風船"				, 0x337E },
		{ "ピンクのハート風船"			, 0x3383 },
		{ "水色ハート風船"				, 0x3380 },
		{ "緑のハート風船"				, 0x337F },
		{ "紫ハート風船"					, 0x3382 },
		{ "青い風車"						, 0x3389 },
		{ "赤い風車"						, 0x3384 },
		{ "オレンジの風車"				, 0x3385 },
		{ "黄色い風車"					, 0x3386 },
		{ "ピンクの風車"					, 0x338B },
		{ "水色の風車"					, 0x3388 },
		{ "緑の風車"						, 0x3387 },
		{ "紫の風車"						, 0x338A },
		{ "シャボン玉"					, 0x336B },
		{ "吹き戻し"						, 0x339E },
		{ "チョコソフトクリーム"		, 0x3391 },
		{ "バニラソフトクリーム"		, 0x3390 },
		{ "抹茶のソフトクリーム"		, 0x3392 },
		{ "ミックスソフトクリーム"		, 0x3393 },
		{ "イチゴアイスクリーム"		, 0x3395 },
		{ "バニラアイスクリーム"		, 0x3394 },
		{ "ミントダブルアイス"			, 0x3397 },
		{ "レモンダブルアイス"			, 0x3396 },
	};


	// ---------------------------------------------------------------
	// 歩き消し
	// ---------------------------------------------------------------
	void WalkDelete(MenuEntry* e)
	{
		Keyboard key("", { "オン", "オフ" });
		int a = key.Open();
		if (a == 0) WRITEU32(0x596890, 0xea00001d);
		if (a == 1) WRITEU32(0x596890, 0xea000000);
	}


	// ---------------------------------------------------------------
	// ピックアップ変更
	// ---------------------------------------------------------------
	void PickupMode(MenuEntry* e)	{
		Keyboard key("", { "通常動作", "なんでも拾う", "雑草として抜く"/*, "四つ葉のクローバー"*/ });
		int a = key.Open();
		if (a == 0) Process::Write32(0x5989fc, 0xea000044);
		if (a == 1) Process::Write32(0x5989fc, 0xea000030);
		if (a == 2) Process::Write32(0x5989fc, 0xea000019);
	}


	// ---------------------------------------------------------------
	// 道具機能変更
	// ---------------------------------------------------------------
	void Tools_1(MenuEntry* e) {
		std::vector<std::string> items;
		items.clear();

		for (const NAME_VALUE_MAP& i : Tool)
			items.push_back(i.name);

		Keyboard keyboard("指定したツールの機能に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write16(0x33096734, Tool[choice].value);
	}


	// ---------------------------------------------------------------
	// 道具持ち方変更
	// ---------------------------------------------------------------
	void Tools_2(MenuEntry* e)
	{
		std::vector<std::string> items;
		items.clear();

		for (const NAME_VALUE_MAP& i : Tool)
			items.push_back(i.name);

		Keyboard keyboard("指定したツールの持ち方に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write16(0x3309A20C, Tool[choice].value);
	}


	// ---------------------------------------------------------------
	// 座標移動
	// ---------------------------------------------------------------
	void CoordinateModifier(MenuEntry* e)
	{
		Player p;
		
		if (Controller::IsKeyDown(A))
		{
			if (Controller::IsKeyDown(DU)) p.Coord()->z -= CoordSpeed;
			if (Controller::IsKeyDown(DD)) p.Coord()->z += CoordSpeed;
			if (Controller::IsKeyDown(DL)) p.Coord()->x -= CoordSpeed;
			if (Controller::IsKeyDown(DR)) p.Coord()->x += CoordSpeed;
		}
	}


	// ---------------------------------------------------------------
	// 座標移動のスピード変更
	// ---------------------------------------------------------------
	void Coord_setting(MenuEntry* e)
	{
		Keyboard key("移動する速度");
		key.Open(CoordSpeed, CoordSpeed);
	}


	// ---------------------------------------------------------------
	// 壁抜け
	// ---------------------------------------------------------------
	void WalkOver(MenuEntry* e)	{
		static bool mode;

		if (Controller::IsKeysPressed(e->Hotkeys[0].GetKeys())) {
			if (mode) {
				mode = false;
				OSD::Notify("Walk Over Objects: OFF");
				Process::Write32(0x0064EEF4, 0x0A000094);
				Process::Write32(0x0064EF0C, 0x0A000052);
				Process::Write32(0x0064F070, 0x0A000001);
				Process::Write32(0x0064F0E8, 0xDA000014);
				Process::Write32(0x0064F19C, 0xED841A05);
				Process::Write32(0x0064F1B4, 0xED840A07);
				Process::Write32(0x0064F1B8, 0x0A000026);
				Process::Write32(0x0064F1E4, 0x0A000065);
			}
			else {
				mode = true;
				OSD::Notify("Walk Over Objects: ON");
				Process::Write32(0x0064EEF4, 0xEA000094);
				Process::Write32(0x0064EF0C, 0xEA000052);
				Process::Write32(0x0064F070, 0xEA000001);
				Process::Write32(0x0064F0E8, 0xEA000014);
				Process::Write32(0x0064F19C, 0xE1A00000);
				Process::Write32(0x0064F1B4, 0xE1A00000);
				Process::Write32(0x0064F1B8, 0xEA000026);
				Process::Write32(0x0064F1E4, 0xEA000065);
			}
		}
	}


	// ---------------------------------------------------------------
	// スピードハック
	// ---------------------------------------------------------------
	void SpeedHack(MenuEntry* e)
	{
		u32		velocity;
		float* Flo = (float*)0x33099E7C;
		const float max = 100;

		if (e->Hotkeys[0].IsDown())
		{
			if (*Flo > max)
			{
				*Flo = max;
			}
			else if (*Flo > 0)
			{
				*Flo += 2.0;
			}
		}
	}


	// ---------------------------------------------------------------
	// 逆さま
	// ---------------------------------------------------------------
	void Pose1(MenuEntry* entry)
	{
		static bool key_status = false;

		if (entry->Hotkeys[0].IsDown() && key_status == false)
		{
			key_status = true;
			Process::Write32(0x3309A080, 0x00008000);
			Process::Write32(0x3309A1AC, 0x00008000);
			OSD::Notify("Hand stand " << Color::Green << "ON!");
		}

		if (entry->Hotkeys[1].IsDown() && key_status == false)
		{
			key_status = true;
			Process::Write32(0x3309A080, 0x00000000);
			Process::Write32(0x3309A1AC, 0x00000000);
			OSD::Notify("Hand stand " << Color::Red << "OFF!");
		}
		if (entry->Hotkeys[0].IsDown() == 0 && entry->Hotkeys[1].IsDown() == 0) key_status = false;
	}


	// ---------------------------------------------------------------
	// Tポーズ
	// ---------------------------------------------------------------
	void Pose2(MenuEntry* entry)
	{
		static bool key_status = false;

		if (entry->Hotkeys[0].IsDown() && key_status == false)
		{
			key_status = true;
			Process::Write32(0x0073AA30, 0xE1A00000);
			OSD::Notify("T pose " << Color::Green << "ON!");
		}

		if (entry->Hotkeys[1].IsDown() && key_status == false)
		{
			key_status = true;
			Process::Write32(0x0073AA30, 0x0A000011);
			OSD::Notify("T pose " << Color::Red << "OFF!");
		}
		if (entry->Hotkeys[0].IsDown() == 0 && entry->Hotkeys[1].IsDown() == 0) key_status = false;
	}



	// ---------------------------------------------------------------
	// はや着替え
	// ---------------------------------------------------------------
	void FastClothChange(MenuEntry* entry)
	{
		Process::Write32(0x3309A714, 0x00000000);
	}

	// ---------------------------------------------------------------
	// タッチワープ
	// ---------------------------------------------------------------
	void TouchWarp(MenuEntry* e) {
		u16 baseValueCheck = *(u16*)0x95133a;

		static Coordinates* const PlayerCoordinates = reinterpret_cast<Coordinates* const>(0x33099E50);

		touchPosition tp;
		hidTouchRead(&tp);

		if (!Controller::IsKeyDown(Touchpad)) return;

		int TouchX = tp.px - 70;
		int TouchY = tp.py - 54;

		// タッチ範囲制限
		if (TouchX < 0) TouchX = 0;
		if (TouchY < 0) TouchY = 0;
		if (TouchX > 180) TouchX = 180;
		if (TouchY > 152) TouchX = 152;

		// 島と村での座標ずれを対処する
		float basePoint = 528;

		PlayerCoordinates->x = basePoint + (TouchX * 13.7);
		PlayerCoordinates->z = basePoint + (TouchY * 14.8);
	}


	// ---------------------------------------------------------------
	// マス目移動
	// ---------------------------------------------------------------
	void GridMove(MenuEntry* e) {
		if (get12c() != 0) return;

		static int start_c;
		static int down_c;

		const int s_time = 20;
		const int d_time = 2;

		if (!Controller::IsKeyDown(DPad)) {
			start_c = -1;
			down_c = 0;
			return;
		}

		start_c++;
		if (start_c > s_time) {
			start_c = s_time;
			down_c++;
			if (down_c > d_time) down_c = 0;
		}

		if ((start_c > 0 && start_c < s_time) || (down_c != 0)) return;

		static Coordinates* const PlayerCoordinates = reinterpret_cast<Coordinates* const>(0x33099E50);

		if (Controller::IsKeyPressed(DPad)) {
			PlayerCoordinates->x = 528 + ((READU8(0x3309a2b8) - 0x10) * 32);
			PlayerCoordinates->z = 528 + ((READU8(0x3309a2bc) - 0x10) * 32);
		}

		if (Controller::IsKeyDown(DU)) PlayerCoordinates->z -= 32.0;
		if (Controller::IsKeyDown(DD)) PlayerCoordinates->z += 32.0;
		if (Controller::IsKeyDown(DL)) PlayerCoordinates->x -= 32.0;
		if (Controller::IsKeyDown(DR)) PlayerCoordinates->x += 32.0;
	}


	// ---------------------------------------------------------------
	// 潜ると空黒くなる
	// ---------------------------------------------------------------
	void Moguru_black(MenuEntry* e) {
		Process::Write32(0x3309a70c, 0xbff);
	}


}

