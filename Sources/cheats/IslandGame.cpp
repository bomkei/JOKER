#include "cheats.hpp"

namespace CTRPluginFramework
{
	using NVMvector = std::vector<NAME_VALUE_MAP>;
	extern std::vector<std::string> items;

	// 構造体配列の中から文字列だけを取り出して、StringVectorを作成する。
	void CreateStringVector(NVMvector);

	u8	motion_ekiin;						// 駅員モーション変更
	u8	motion_kappei;						// かっぺいモーション変更
	u8	motion_sizue_indoor;				// しずえ(室内)モーション変更
	u8	motion_sizue_outdoor;				// しずえ(室外)モーション変更
	u8	motion_risa;						// リサモーション変更
	u8	motion_keito;						// ケイトモーション変更
	u8	motion_tanukiti;					// タヌキチモーション変更
	u16 outdoor_Frag;						// 室外アイテム判定変更　Freg
	u16 outdoor_item;						// 室外アイテム判定変更
	u32 change_pickup;						// 拾い方変更
	u32 hosuuP1;							// 無人島P1歩数変更
	u32 hosuuP2;							// 無人島P2歩数変更
	u32 hosuuP3;							// 無人島P3歩数変更
	u32 change_WalkScore;					// 無人島歩いた時のスコア変更
	int* room_ID = (int*)0x0095133A;		// room_deta指定


	extern int* g_location;
	
	// ---------------------------------------------------------------
	// 無人島歩数変更P1
	// ---------------------------------------------------------------
	void mujintou_hosuuP1(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("指定した歩数に変化。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			hosuuP1 = fxx;
			Process::Write32(0x330C5324, fxx);
			Process::Write32(hosuuP1, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島歩数変更P2
	// ---------------------------------------------------------------
	void mujintou_hosuuP2(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("指定した歩数に変化。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			hosuuP2 = fxx;
			Process::Write32(0x330C577C, fxx);
			Process::Write32(hosuuP2, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島歩数変更P3
	// ---------------------------------------------------------------
	void mujintou_hosuuP3(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("歩数を指定してください。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			hosuuP3 = fxx;
			Process::Write32(0x330C5BD4, fxx);
			Process::Write32(hosuuP3, fxx);
		}
	}

	// ------------------------------------------------------------------
	// 歩数固定
	// ------------------------------------------------------------------
	void hosuukotei(MenuEntry* e)
	{
		if (hosuuP1) *(u32*)0x330C5324 = hosuuP1;
		if (hosuuP2) *(u32*)0x330C577C = hosuuP2;
		if (hosuuP3) *(u32*)0x330C5BD4 = hosuuP3;
	}

	// ---------------------------------------------------------------
	// ステージ開放
	// ---------------------------------------------------------------
	static const	std::vector< NAME_VALUE_MAP > mujinntou_stage =
	{
		{ "無開放", 			0x00000000 },
		{ "初級1まで解放", 	0x00000002 },
		{ "初級2まで解放", 	0x00000022 },
		{ "初級3まで解放", 	0x00000222 },
		{ "初級4まで解放", 	0x00000262 },
		{ "初級5まで解放", 	0x00000362 },
		{ "初級6まで解放", 	0x00000372 },
		{ "初級8まで解放", 	0x000003FA },
		{ "初級9まで解放", 	0x000003FB },
		{ "初級全開放", 		0x000003FF },
		{ "全開放", 			0xFFFFFFFF },
	};
	void mujinntou_stage_open(MenuEntry* e)
	{
		CreateStringVector(mujinntou_stage);

		Keyboard keyboard("ステージ開放率を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write32(0x330B110C, mujinntou_stage[choice].value);
	}

	// ---------------------------------------------------------------
	// 無人島歩く時のスコア変更
	// ---------------------------------------------------------------
	void mujintou_WalkScore(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("スコアを指定してください。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			change_WalkScore = fxx;
			Process::Write32(0x330BB078, fxx);
			Process::Write32(change_WalkScore, fxx);
		}
	}

	// ------------------------------------------------------------------
	// 無人島歩く時のスコア固定
	// ------------------------------------------------------------------
	void Walkscore_kotei(MenuEntry* e)
	{
		if (change_WalkScore) *(u16*)0x330BB078 = change_WalkScore; // 無人島歩いた時のスコア変更
	}

	// ---------------------------------------------------------------
	// 無人島棒所持数変更
	// ---------------------------------------------------------------
	void mujintou_Item1(MenuEntry* e)
	{
		u8 fxx;

		Keyboard keyboard("所持数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write8(0x330BE3C8, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島糸所持数変更
	// ---------------------------------------------------------------
	void mujintou_Item2(MenuEntry* e)
	{
		u8 fxx;

		Keyboard keyboard("所持数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write8(0x330BE3CC, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島布きれ所持数変更
	// ---------------------------------------------------------------
	void mujintou_Item3(MenuEntry* e)
	{
		u8 fxx;

		Keyboard keyboard("所持数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write8(0x330BE3D0, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島石ころ所持数変更
	// ---------------------------------------------------------------
	void mujintou_Item4(MenuEntry* e)
	{
		u8 fxx;

		Keyboard keyboard("所持数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write8(0x330BE3D8, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島ぎんこうせき所持数変更
	// ---------------------------------------------------------------
	void mujintou_Item5(MenuEntry* e)
	{
		u8 fxx;

		Keyboard keyboard("所持数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write8(0x330BE3DC, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島きんこうせき所持数変更
	// ---------------------------------------------------------------
	void mujintou_Item6(MenuEntry* e)
	{
		u8 fxx;

		Keyboard keyboard("所持数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write8(0x330BE3E0, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 無人島おくすり所持数変更
	// ---------------------------------------------------------------
	void mujintou_Item7(MenuEntry* e)
	{
		u8 fxx;

		Keyboard keyboard("所持数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write8(0x330BE3D4, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 丸太入手数変更
	// ---------------------------------------------------------------
	void mujintou_hoof1(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("入手数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330BE3E4, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 船の旗入手数変更
	// ---------------------------------------------------------------
	void mujintou_hoof2(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("入手数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330BE3E8, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 丸太残りの数変更
	// ---------------------------------------------------------------
	void mujintou_hoof3(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("残りの数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330E0FF0, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 船の旗残りの数変更
	// ---------------------------------------------------------------
	void mujintou_hoof4(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("残りの数を指定してください");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330E0FF8, fxx);
		}
	}

	// ---------------------------------------------------------------
	//  無人島ツール
	// ---------------------------------------------------------------
	void mujintou_Tool1(MenuEntry* e)//釣り竿
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2DC, 1 - choice);
	}

	void mujintou_Tool2(MenuEntry* e)//パチンコ
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2E0, 1 - choice);
	}

	void mujintou_Tool3(MenuEntry* e)//網
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2E4, 1 - choice);
	}

	void mujintou_Tool4(MenuEntry* e)//スコップ
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2E8, 1 - choice);
	}

	void mujintou_STool1(MenuEntry* e)//銀の釣り竿
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2EC, 1 - choice);
	}

	void mujintou_STool2(MenuEntry* e)//銀のパチンコ
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2F0, 1 - choice);
	}

	void mujintou_STool3(MenuEntry* e)//銀の網
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2F4, 1 - choice);
	}

	void mujintou_STool4(MenuEntry* e)//銀のスコップ
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2F8, 1 - choice);
	}

	void mujintou_GTool1(MenuEntry* e)//金の釣り竿
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC2FC, 1 - choice);
	}

	void mujintou_GTool2(MenuEntry* e)//金のパチンコ
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC300, 1 - choice);
	}

	void mujintou_GTool3(MenuEntry* e)//金の網
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC304, 1 - choice);
	}

	void mujintou_GTool4(MenuEntry* e)//金のスコップ
	{
		Keyboard keyboard("このアイテムを入手しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330BC308, 1 - choice);
	}

	// ---------------------------------------------------------------
	// 残り日数変更
	// ---------------------------------------------------------------
	void mujintou_hizuke1(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("残り日数を指定してください。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330B1798, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 経過日数変更
	// ---------------------------------------------------------------
	void mujintou_hizuke2(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("経過日数を指定してください。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330B1794, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 食料落下数変更
	// ---------------------------------------------------------------
	void mujintou_syokuryou1(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("食料落下数を指定してください。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330F9080, fxx);
		}
	}

	// ---------------------------------------------------------------
	// リンゴゲージ変更
	// ---------------------------------------------------------------
	void mujintou_syokuryou2(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("リンゴゲージを指定してください。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330E0FDC, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 食料所持数変更
	// ---------------------------------------------------------------
	void mujintou_syokuryou3(MenuEntry* e)
	{
		u32 fxx;

		Keyboard keyboard("食料所持数を指定してください。");
		keyboard.IsHexadecimal(false);
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
		{ // 入力あり
			Process::Write32(0x330E0FD8, fxx);
		}
	}

	// ---------------------------------------------------------------
	// 落とし穴無効化
	// ---------------------------------------------------------------
	static const	std::vector< NAME_VALUE_MAP > Mujiontou_otosiana =
	{
		{ "無効化", 0x01 },
		{ "有効化", 0x00 },
	};
	void mujintou_Otosiana(MenuEntry* e)//釣り竿
	{
		CreateStringVector(Mujiontou_otosiana);

		Keyboard keyboard("落とし穴から抜け出しますか？", { "入手", "未入手" });
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x330F9078, 1 - choice);
	}

	// ---------------------------------------------------------------
	// 住民特技変更
	// ---------------------------------------------------------------
	static const std::vector< NAME_VALUE_MAP > Mujiontou_tokugi =
	{
		{ "ランナー", 		0x00 },
		{ "探偵", 				0x01 },
		{ "ハニーモンター", 	0x02 },
		{ "釣り名人", 		0x04 },
		{ "料理人", 			0x08 },
		{ "食いしん坊", 		0x10 },
		{ "気まぐれ", 		0x20 },
		{ "寝だめ", 			0x40 },
		{ "怪力", 				0x80 },
		{ "水泳", 				0x100 },
		{ "ハンター", 		0x200 },
		{ "飛行", 				0x400 },
		{ "トンネル", 		0x800 },
		{ "忍び足", 			0x1000 },
		{ "応急処置", 		0x2000 },
		{ "衝突猛進", 		0x4000 },
		{ "器用", 				0x8000 },
		{ "一匹狼",			0x10000 },

	};
	void mujintou_TokugiP1(MenuEntry* e)//P
	{
		CreateStringVector(Mujiontou_tokugi);

		Keyboard keyboard("特技を選択してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write32(0x330C5240, Mujiontou_tokugi[choice].value);
	}
	void mujintou_TokugiP2(MenuEntry* e)//P2
	{
		CreateStringVector(Mujiontou_tokugi);

		Keyboard keyboard("特技を選択してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write32(0x330C5698, Mujiontou_tokugi[choice].value);
	}
	void mujintou_TokugiP3(MenuEntry* e)//P3
	{
		CreateStringVector(Mujiontou_tokugi);

		Keyboard keyboard("特技を選択してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write32(0x330C5AF0, Mujiontou_tokugi[choice].value);
	}

	// ---------------------------------------------------------------
	// 住民好きな食べ物変更
	// ---------------------------------------------------------------
	static const	std::vector< NAME_VALUE_MAP > Mujiontou_Food =
	{
		{ "桃", 					0x0E0300 },
		{ "ヤシの実", 			0x020B00 },
		{ "レモン", 				0x010600 },
		{ "ドリアン", 			0x040500 },
		{ "リンゴ", 				0x030000 },
		{ "オレンジ", 			0x080100 },
		{ "梨", 					0x050200 },
		{ "バナナ", 				0x100A00 },
		{ "ライチ", 				0x090700 },
		{ "柿", 					0x0A0900 },
		{ "マンゴー", 			0x0C0800 },
		{ "好きな食べ物ない", 	0x0F0000 },

	};
	void mujintou_FoodP1(MenuEntry* e)//P1
	{
		CreateStringVector(Mujiontou_Food);

		Keyboard keyboard("好きな食べ物を選択してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write32(0x330C5244, Mujiontou_Food[choice].value);
	}
	void mujintou_FoodP2(MenuEntry* e)//P2
	{
		CreateStringVector(Mujiontou_Food);

		Keyboard keyboard("好きな食べ物を選択してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write32(0x330C569C, Mujiontou_Food[choice].value);
	}
	void mujintou_FoodP3(MenuEntry* e)//P3
	{
		CreateStringVector(Mujiontou_Food);

		Keyboard keyboard("好きな食べ物を選択してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write32(0x330C5AF4, Mujiontou_Food[choice].value);
	}


}

