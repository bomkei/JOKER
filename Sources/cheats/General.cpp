#include "cheats.hpp"

namespace CTRPluginFramework
{
	using StringVector = std::vector<std::string>;

	// ---------------------------------------------------------------
	// プレイヤー変更
	// ---------------------------------------------------------------
	void ChangePlayer(MenuEntry* e) {
		Keyboard keyboard("指定したプレイヤーに変化。", {"村長", "サブ1", "サブ2", "サブ3"});
		int r = keyboard.Open();

		if (r >= 0)
			Process::Write32(0xAA914C, 0x31f49aa0 + r * 0xa480);
	}


	// ---------------------------------------------------------------
	// エリア移動
	// ---------------------------------------------------------------
	static const std::vector< NAME_VALUE_MAP > change_area = {
		{ "村",								 0x00 },
		{ "商店街",							 0x01 },
		{ "駅",								 0x02 },
		{ "P1 家 Main",						 0x03 },
		{ "P1 家 UP",							 0x04 },
		{ "P1 家 DOWN",						 0x05 },
		{ "P1 家 Right",						 0x06 },
		{ "P1 家 left",						 0x07 },
		{ "P1 家 Back",						 0x08 },
		{ "P2 家 Main",						 0x09 },
		{ "P2 家 UP",							 0x0A },
		{ "P2 家 DOWN",						 0x0B },
		{ "P2 家 Right",						 0x0C },
		{ "P2 家 left",						 0x0D },
		{ "P2 家 Back",						 0x0E },
		{ "P3 家 Main",						 0x0F },
		{ "P3 家 UP",							 0x10 },
		{ "P3 家 DOWN",						 0x11 },
		{ "P3 家 Right",						 0x12 },
		{ "P3 家 left",						 0x13 },
		{ "P3 家 Back",						 0x14 },
		{ "P4 家 Main",						 0x15 },
		{ "P4 家 UP",							 0x16 },
		{ "P4 家 DOWN",						 0x17 },
		{ "P4 家 Right",						 0x18 },
		{ "P4 家 left",						 0x19 },
		{ "P4 家 Back",						 0x1A },
		{ "A1 家",								 0x1B },
		{ "A2 家",								 0x1C },
		{ "A3 家",								 0x1D },
		{ "A4 家",								 0x1E },
		{ "A5 家",								 0x1F },
		{ "A6 家",								 0x20 },
		{ "A7 家",								 0x21 },
		{ "A8 家",								 0x22 },
		{ "A9 家",								 0x23 },
		{ "役場",								 0x23 },
		{ "return error",						 0x28 },
		{ "Come to the village",				 0x2A },
		{ "R-Parkers",						 0x2B },
		{ "モダンな交番",						 0x30 },
		{ "クラシックな交番",				 0x31 },
		{ "カフェ",							 0x32 },
		{ "カフェ バイトイベント",			 0x33 },
		{ "夢見の館",							 0x37 },
		{ "デパート1階",						 0x3C },
		{ "デパート2階",						 0x3D },
		{ "デパート3階",						 0x3E },
		{ "エイブルシスターズ 服屋",		 0x3F },
		{ "エイブルシスターズ アクセ屋",	 0x40 },
		{ "Shoe Shank 靴屋",					 0x40 },
		{ "不動産屋",							 0x41 },
		{ "Club444",							 0x47 },
		{ "ビューティーサロン スピーディ",	 0x48 },
		{ "博物館 中央",						 0x49 },
		{ "博物館 魚",						 0x4A },
		{ "博物館 虫",						 0x4D },
		{ "博物館 化石",						 0x50 },
		{ "博物館 絵画",						 0x53 },
		{ "博物館 2階",						 0x55 },
		{ "博物館 2階 左上",					 0x56 },
		{ "博物館 2階 左下",					 0x57 },
		{ "博物館 2階 右上",					 0x58 },
		{ "博物館 2階 右下",					 0x59 },
		{ "郵便局",							 0x5A },
		{ "夢見の館",							 0x5B },
		{ "証明写真機",						 0x5C },
		{ "Train",								 0x5D },
		{ "Dream Bed Error",					 0x64 },
		{ "島へ行くイベント",				 0x65 },
		{ "村へ戻るイベント",				 0x66 },
		{ "島 室内",							 0x67 },
		{ "島 屋外",							 0x68 },
		{ "ハッピーホームアカデミー 中央",	 0x8E },
		{ "オートキャンプ場",				 0xA0 },
		{ "オートキャンプ場 車の中",		 0xA1 },
		{ "しずえがいるエリア",				 0x63 },
		{ "タイトル",							 0x5E },
		{ "カメラ",							 0xa4 },
		{ "住民登録",							 0x5d },
		{ "オレンジテント",					 0x25 },
		{ "模様替えイベント",				 0xa3 },
		{ "釣り結果",							 0x2F },
	};
	void Action14(void);
	void ChangeArea(MenuEntry* e) {
		StringVector items;
		items.clear();
		for (const NAME_VALUE_MAP& i : change_area)
			items.push_back(i.name);

		Keyboard keyboard("指定した場所に移動", items);
		int choice = keyboard.Open();

		if (choice >= 0) {
			Process::Write8(0x0095133A, change_area[choice].value);
			Action14();
		}
	}

	// ---------------------------------------------------------------
	// 名前変更
	// ---------------------------------------------------------------
	void ChangeName(MenuEntry* e) {
		Keyboard key("プレイヤーを選ぶ", { "村名", "メイン", "サブ1", "サブ2", "サブ3" });
		int r = key.Open();

		std::string str;
		if (r == 0) {
			
		}
		else if (r > 0) {
			Keyboard name_input("");
			name_input.Open(str);

			for (int i = 0; i < 4; i++)
				Process::Write32((0x31f4f048 + ((r - 1) * 0xA480)) + (i * 4), 0);

			Process::WriteString((0x31f4f048 + ((r - 1) * 0xA480)), str, StringFormat::Utf16);
		}
	}

	// ---------------------------------------------------------------
	// 国籍変更
	// ---------------------------------------------------------------
	static const std::vector< NAME_VALUE_MAP > kuni = {
		{ "日本",									0x190c0001 },
		{ "アルバニア",							0x40 },
		{ "アメリカ",								0x31 },
		{ "アンギラ",								0x8	 },
		{ "アンティグア・バーブーダ",			0x9	 },
		{ "アルゼンチン",							0xa	 },
		{ "アルバ",								0xb	 },
		{ "ウルグアイ",							0x32 },
		{ "エクアドル",							0x19 },
		{ "エルサルバドル",						0x1a },
		{ "英領ヴァージン諸島",					0x11 },
		{ "オランダ領アンティル",				0x26 },
		{ "カナダ",								0x12 },
		{ "ガイアナ",								0x1f },
		{ "グレナダ",								0x1c },
		{ "グアドループ",							0x1d },
		{ "グアテマラ",							0x1e },
		{ "ケイマン諸島",							0x13 },
		{ "コスタリカ",							0x16 },
		{ "コロンビア",							0x15 },
		{ "ジャマイカ",							0x22 },
		{ "スリナム",								0x2e },
		{ "セントキッツ・ネイビス",				0x2b },
		{ "セントルシア",							0x2c },
		{ "セントビンセント・グレナディーン",	0x2d },
		{ "タークス・カイコス諸島",				0x30 },
		{ "チリ",									0x14 },
		{ "トリニダード・トバゴ",				0x2f },
		{ "ドミニカ国",							0x17 },
		{ "ドミニカ共和国",						0x18 },
		{ "ニカラグア",							0x27 },
		{ "ハイチ",								0x20 },
		{ "パナマ",								0x28 },
		{ "パラグアイ",							0x29 },
		{ "バハマ",								0xc	 },
		{ "バルバドス",							0xd	 },
		{ "フランス領ギアナ",					0x1b },
		{ "ブラジル",								0x10 },
		{ "ベリーズ",								0xe	 },
		{ "ペルー",								0x2a },
		{ "ベネズエラ",							0x34 },
		{ "ホンジュラス",							0x21 },
		{ "ボリビア",								0xf	 },
		{ "マルティニーク",						0x23 },
		{ "メキシコ",								0x24 },
		{ "モントセラト",							0x25 },
		{ "米領バージン諸島",					0x33 },
	};
	void ChangeRegion(MenuEntry* e) {
		StringVector regions;
		regions.clear();
		for (const NAME_VALUE_MAP& i : kuni)
			regions.push_back(i.name);

		Keyboard key("国籍変更", regions);
		int r = key.Open();

		if (r >= 0)
			Process::Write32(0x31f4f072, kuni[r].value);
	}

	// ---------------------------------------------------------------
	// 性別変更
	// ---------------------------------------------------------------
	void ChangeDenger(MenuEntry* e) {
		Keyboard key("プレイヤー", { "村長", "サブ1", "サブ2", "サブ3" });
		int r0 = key.Open();

		OSD::SwapBuffers();

		if (r0 >= 0)
		{
			Keyboard denger("性別", { "男", "女" });
			int r1 = denger.Open();

			if (r1 >= 0)
				Process::Write32(0x31F4F05A + r0 * 0xA480, r1);
		}

	}

	// ---------------------------------------------------------------
	// バッジ変更
	// ---------------------------------------------------------------
	static const std::vector< BADGE_MAP > badge = {
		{ 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, "なし" },
		{ 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, "銅"	 },
		{ 0x02020202, 0x02020202, 0x02020202, 0x02020202, 0x02020202, 0x02020202, "銀"	 },
		{ 0x03030303, 0x03030303, 0x03030303, 0x03030303, 0x03030303, 0x03030303, "金"	 },
		{ 0xe9c6d5cb, 0xc1b7ad03, 0x03261c12, 0x0821352b, 0x0f0c0c0e, 0x0e030403, "神"	 },
	};
	void ChangeBadge(MenuEntry* e) {
		StringVector items;
		items.clear();
		for (const BADGE_MAP& i : badge)
			items.push_back(i.name);

		Keyboard keyboard("", items);
		int choice = keyboard.Open();

		if (choice >= 0) {
			u32 offset = 0x31F4F13C + 0x569c;

			Process::Write32(offset, badge[choice].hex);
			Process::Write32(offset + 0x4, badge[choice].hex2);
			Process::Write32(offset + 0x8, badge[choice].hex3);
			Process::Write32(offset + 0xc, badge[choice].hex4);
			Process::Write32(offset + 0x10, badge[choice].hex5);
			Process::Write32(offset + 0x14, badge[choice].hex6);
		}
	}


}







