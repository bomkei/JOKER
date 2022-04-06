#include "cheats.hpp"

#define SPADE	"\uE015"
#define DIAMOND	"\uE016"
#define HEART	"\uE017"
#define CLOVER	"\uE018"

namespace CTRPluginFramework
{
	/*
		フォルダーの装飾文字順番

		♦あいうえお
			*かきくけこ
				さしすせそ
	*/
	
	const std::vector<std::string> Entry_ActionNames =
	{
		"気絶",
		"前転",
		"尻もち",
		"泳ぐ",
		"受け取る",
		"よろける",
		"空気椅子",
		"斧を壊す",
		"唾を吐く",
		"叩かれる",
		"ウィンドウ",
		"綿毛を吹く",
		"クラゲ回避",
		"赤バラ表示",
		"頭がピッカーん",
		"釣り竿を引き戻す",
		"地中深くまで沈む",
		"アイテムを捕まえた",
		"リアクション四連発",
		"止まると動きがフリーズ",
		"黒くなって地面から出る",
		"かっぺいのボートに立って乗る",
	};
	
	static MenuEntry* EntryWithHotkey(MenuEntry* entry, const Hotkey& hotkey)
	{
		if (entry != nullptr)
		{
			entry->Hotkeys += hotkey;
			entry->SetArg(new std::string(entry->Name()));
			entry->Name() += " " + hotkey.ToString();
			entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry* entry, int index)
				{
					std::string* name = reinterpret_cast<std::string*>(entry->GetArg());

					entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
				});
		}
		return (entry);
	}

	static MenuEntry* EntryWithHotkey(MenuEntry* entry, const std::vector<Hotkey>& hotkeys)
	{
		if (entry != nullptr)
		{
			for (const Hotkey& hotkey : hotkeys)
				entry->Hotkeys += hotkey;
		}
		return (entry);
	}

	void InitEntrys(PluginMenu &menu)
	{
		menu += new MenuFolder(Color::DodgerBlue << "ゲーム全般",
			{
				new MenuEntry(Color::DodgerBlue << "プレイヤー変更", nullptr, ChangePlayer),
				new MenuEntry(Color::DodgerBlue << "エリア移動", nullptr, ChangeArea),
				new MenuEntry(Color::DodgerBlue << "名前変更", nullptr, ChangeName),
				new MenuEntry(Color::DodgerBlue << "国籍変更", nullptr, ChangeRegion),
				new MenuEntry(Color::DodgerBlue << "性別変更", nullptr, ChangeDenger),
				new MenuEntry(Color::DodgerBlue << "バッジ変更", nullptr, ChangeBadge),
				EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "ソパカ写真編集", TCP_ImageEditor, "写真機の中で、キーを押す"), Hotkey(Key::R + DU, "")),

			});


		menu += new MenuFolder(Color::Orange << "モーション",
			{
				new MenuEntry(Color::Orange << "駅員モーション変更"				, nullptr, Motion1),
				new MenuEntry(Color::Orange << "かっぺいモーション変更"		, nullptr, Motion2),
				new MenuEntry(Color::Orange << "しずえ(室内)モーション変更"	, nullptr, Motion3),
				new MenuEntry(Color::Orange << "しずえ(室外)モーション変更"	, nullptr, Motion4),
				new MenuEntry(Color::Orange << "リサモーション変更"				, nullptr, Motion5),
				new MenuEntry(Color::Orange << "ケイトモーション変更"			, nullptr, Motion6),
				new MenuEntry(Color::Orange << "たぬきちモーション変更"		, nullptr, Motion7),
			});
		
		
		MenuFolder *drop = new MenuFolder(Color::DodgerBlue << "ドロップ",
			{
				EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "ドロップ無効化", DropStopper),
				{
					Hotkey(Key::L, "オン"),
					Hotkey(Key::R, "オフ"),
				}),
				EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "連続スライドドロップ", DD_Spam), Hotkey(Key::R + DL, "オン/オフ")),
				/*
				EntryWithHotkey(new MenuEntry("アイテムランダマイザ", ItemRandomizer),
				{
					Hotkey(Key::R, "ランダムに変更"),
					Hotkey(Key::R + X, "設定変更"),
				}),
				*/
				EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "アイテム変更", ChangeItemID), Hotkey(Key::Y + DR, "")),
				EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "ドロップ変更", ChangeDropID), Hotkey(Key::Y + DL, "")),
								new MenuEntry(Color::DodgerBlue << "タッチドロップ", TouchDrop),
				EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "自動ドロップ", AutoDrop), Hotkey(Key::B + DL, "")),
				/*
				EntryWithHotkey(new MenuEntry("マップエディタ \ue001 + \ue07b", MapEditor),
				{
					Hotkey(Key::A, "置く / 消す"),
					Hotkey(Key::B + DL, "モード切替"),
				}),
				*/
				/*
				EntryWithHotkey(new MenuEntry("塗りつぶし", FillDrop),
				{
					Hotkey(Key::L + B, "Change size & location"),
					Hotkey(Key::B + DD, "Drop!"),
				}),
				EntryWithHotkey(new MenuEntry("四角形", BoxDrop),
				{
					Hotkey(Key::L + B, "Change size & location"),
					Hotkey(Key::B + DD, "Drop!"),
				}),
				*/
			});
		
		
		MenuFolder *movement = new MenuFolder(Color::DodgerBlue << "動き、操作");
		{
			*movement += drop;
			*movement += new MenuEntry(Color::DodgerBlue << "歩き消し", nullptr, WalkDelete);
			*movement += new MenuEntry(Color::DodgerBlue << "ピックアップ変更", nullptr, PickupMode);
			*movement += new MenuEntry(Color::DodgerBlue << "道具機能変更", nullptr, Tools_1, "道具の機能を変更できる。網、釣り竿、スコップ以外を持っているとクラッシュする危険性がある");
			*movement += new MenuEntry(Color::DodgerBlue << "道具持ち方変更", nullptr, Tools_2, "道具の持ち方を変更できる。");
			*movement += new MenuEntry(Color::DodgerBlue << "乗っ取り", IslandPlayerHijack);
			*movement += new MenuEntry(Color::DodgerBlue << "座標移動", CoordinateModifier, Coord_setting);
			*movement += EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "壁抜け", WalkOver), Hotkey(Key::L + DL, ""));
			*movement += EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "スピードハック", SpeedHack), Hotkey(B, ""));
			*movement += EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "逆さま", Pose1, Color::SkyBlue << "キーを押すと自分が逆さになる。"),
			{
				Hotkey(Key::L | DPadUp, "逆さま"),
				Hotkey(Key::L | DPadDown, "通常")
			});
			*movement += EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "Tポーズ", Pose2, Color::SkyBlue << "キーを押すとみんながTポーズをする。"),
			{
				Hotkey(Key::L | DPadUp, "Tポーズ"),
				Hotkey(Key::L | DPadDown, "通常")
			});
			*movement += new MenuEntry(Color::DodgerBlue << "はや着替え", FastClothChange, "オンにすると着替えが早くなる。");
			//new MenuEntry("ひらひら歩き", Pose3, Color::SkyBlue << "オンにするとひらひら歩きをする。" ),
			//new MenuEntry("顔を初期設定にする", Pose4, Color::SkyBlue << "オンにすると顔が初期設定(目が黒くなり坊主に)なる。\nオフにしてリロードすると元に戻る。" ),
			*movement += new MenuEntry(Color::DodgerBlue << "タッチワープ", TouchWarp);
			*movement += new MenuEntry(Color::DodgerBlue << "マス目移動", GridMove);
			*movement += new MenuEntry(Color::DodgerBlue << "潜ると空黒くなる", Moguru_black);

		}
		menu += movement;



		menu += new MenuFolder(Color::Orange << "インベントリ",
		{
			new MenuEntry(Color::Orange << "未使用アイテムを表示", nullptr, DisableItemLocks),
			new MenuEntry(Color::Orange << "置いても無くならない", nullptr, InfinityItem),
			new MenuEntry(Color::Orange << "すべて削除", nullptr, DeleteInvItems),
			new MenuEntry(Color::Orange << "選択肢変更", nullptr, InvItemOption),
			EntryWithHotkey(new MenuEntry(Color::Orange << "コピー", Copy), Hotkey(Key::R, "")),
			EntryWithHotkey(new MenuEntry(Color::Orange << "アイテム取得", TextToItem), Hotkey(Key::X + DR, "")),
			new MenuEntry(Color::Orange << "アイテムID表示", ViewSlotItems),
		});


		MenuFolder *act = new MenuFolder(Color::DodgerBlue << "アクション");
		{
			*act += EntryWithHotkey( new MenuEntry(Color::DodgerBlue << "アクション", Action), { Hotkey(Key::L+DU, "実行"), Hotkey(Key::L+DD, "停止") } );
			
			int i = 0;
			for ( const std::string &a: Entry_ActionNames )
			{
				MenuEntry *a_entry = new MenuEntry(2, Color::DodgerBlue << a, Action_n);
				a_entry->SetArg(&i);
				*act += a_entry;
				i++;
			}
		}
		menu += act;
		

		menu += new MenuFolder(Color::Orange << "環境、整備", "",
			{
				EntryWithHotkey(new MenuEntry(Color::Orange << "村のアイテムを全部消す", DeleteAllItem), Hotkey(Key::L + Y, "")),
				EntryWithHotkey(new MenuEntry(Color::Orange << "リロード", GameReload), Hotkey(Key::L + A, "")),
				
			});


		MenuFolder* omise = new MenuFolder(Color::DodgerBlue << "ショップ");
		{
			*omise += new MenuFolder(Color::DodgerBlue << "商店街の店のレベル",
				{
					new MenuEntry(Color::DodgerBlue << "占いの館", nullptr, change_uranai),
					new MenuEntry(Color::DodgerBlue << "夢見の館", nullptr, change_yumemi),
					new MenuEntry(Color::DodgerBlue << "CLUB444", nullptr, change_kurabu),
					new MenuEntry(Color::DodgerBlue << "まめつぶ", nullptr, change_mametubu),
					new MenuEntry(Color::DodgerBlue << "園芸店", nullptr, change_engei),
					new MenuEntry(Color::DodgerBlue << "美容院", nullptr, change_biyouin),
					new MenuEntry(Color::DodgerBlue << "靴屋", nullptr, change_kutuya),
					new MenuEntry(Color::DodgerBlue << "博物館", nullptr, change_hakubutukan),
				});

			*omise += new MenuFolder(Color::DodgerBlue << "アイテム変更",
				{
					new MenuEntry(Color::DodgerBlue << "CLUB444ハニワ", nullptr, Change_Club444),
					new MenuEntry(Color::DodgerBlue << "たぬきハウジング", nullptr, Change_Housing),
					new MenuEntry(Color::DodgerBlue << "デパート1f", nullptr, Change_Department_store),
					new MenuEntry(Color::DodgerBlue << "デパート2f", nullptr, Change_Department_store_F2),
					new MenuEntry(Color::DodgerBlue << "デパート3f", nullptr, Change_Department_store_F3),
					new MenuEntry(Color::DodgerBlue << "ホームセンター", nullptr, Change_HomeCenter),
					new MenuEntry(Color::DodgerBlue << "スーパーマーケット", nullptr, Change_SuperMarket),
					new MenuEntry(Color::DodgerBlue << "まめつぶ商店", nullptr, Change_Syuten),
					new MenuEntry(Color::DodgerBlue << "デパート園芸コーナー", nullptr, Change_Department_store_Engei),
					new MenuEntry(Color::DodgerBlue << "ホームセンター園芸コーナー", nullptr, Change_HomeCenter_Engei),
					new MenuEntry(Color::DodgerBlue << "コンビニ", nullptr, Change_ConvenienceStore),
					new MenuEntry(Color::DodgerBlue << "スーパー＆コンビニ園芸コーナー", nullptr, Change_SuperMarketandConvenienceStore),
					new MenuEntry(Color::DodgerBlue << "エイブルシスターズ", nullptr, Change_Cloth_shop),
					new MenuEntry(Color::DodgerBlue << "エイブルシスターズ（アクセ）", nullptr, Change_Accessory_Shop),
					new MenuEntry(Color::DodgerBlue << "靴屋", nullptr, Change_Shoe_Shop),
					new MenuEntry(Color::DodgerBlue << "博物館2f", nullptr, Change_Hakubutukan),
					new MenuEntry(Color::DodgerBlue << "島お土産変更", nullptr, Change_Island),
					new MenuEntry(Color::DodgerBlue << "オートキャンプ場", nullptr, Change_Camp),
					new MenuEntry(Color::DodgerBlue << "いなりギャラリー", nullptr, Change_Gallery),
					new MenuEntry(Color::DodgerBlue << "交番落とし物", nullptr, Change_PoliceStation),
					new MenuEntry(Color::DodgerBlue << "リサイクルショップ", nullptr, Change_Recycle_Shop),
				});

			*omise += new MenuEntry(Color::DodgerBlue << "高額買取品変更", nullptr, Change_Recycle1);
		}
		menu += omise;


		menu += new MenuFolder(Color::Orange << "無人島",
			{
				new MenuEntry(Color::Orange << "歩数変更P1", nullptr, mujintou_hosuuP1),
				new MenuEntry(Color::Orange << "歩数変更P2", nullptr, mujintou_hosuuP2),
				new MenuEntry(Color::Orange << "歩数変更P3", nullptr, mujintou_hosuuP3),
				new MenuEntry(Color::Orange << "歩数固定", hosuukotei),
				new MenuEntry(Color::Orange << "歩いた時のスコア変更", nullptr, mujintou_WalkScore),
				new MenuEntry(Color::Orange << "歩いた時のスコア固定", Walkscore_kotei),
				new MenuEntry(Color::Orange << "ステージ開放率変更", nullptr, mujinntou_stage_open),
				new MenuEntry(Color::Orange << "棒所持数変更", nullptr, mujintou_Item1),
				new MenuEntry(Color::Orange << "糸所持数変更", nullptr, mujintou_Item2),
				new MenuEntry(Color::Orange << "布きれ所持数変更", nullptr, mujintou_Item3),
				new MenuEntry(Color::Orange << "石ころ所持数変更", nullptr, mujintou_Item4),
				new MenuEntry(Color::Orange << "ぎんこうせき所持数変更", nullptr, mujintou_Item5),
				new MenuEntry(Color::Orange << "きんこうせき所持数変更", nullptr, mujintou_Item6),
				new MenuEntry(Color::Orange << "おくすり所持数変更", nullptr, mujintou_Item7),
				new MenuEntry(Color::Orange << "丸太の入手数変更", nullptr, mujintou_hoof1),
				new MenuEntry(Color::Orange << "船の旗の入手数変更", nullptr, mujintou_hoof2),
				new MenuEntry(Color::Orange << "丸太の残りの数変更", nullptr, mujintou_hoof3),
				new MenuEntry(Color::Orange << "船の旗の残りの数変更", nullptr, mujintou_hoof4),
				new MenuEntry(Color::Orange << "釣り竿所持変更", nullptr, mujintou_Tool1),
				new MenuEntry(Color::Orange << "パチンコ所持変更", nullptr, mujintou_Tool2),
				new MenuEntry(Color::Orange << "網所持変更", nullptr, mujintou_Tool3),
				new MenuEntry(Color::Orange << "スコップ所持変更", nullptr, mujintou_Tool4),
				new MenuEntry(Color::Orange << "銀の釣り竿所持変更", nullptr, mujintou_STool1),
				new MenuEntry(Color::Orange << "銀のパチンコ所持変更", nullptr, mujintou_STool2),
				new MenuEntry(Color::Orange << "銀の網所持変更", nullptr, mujintou_STool3),
				new MenuEntry(Color::Orange << "銀のスコップ所持変更", nullptr, mujintou_STool4),
				new MenuEntry(Color::Orange << "金の釣り竿所持変更", nullptr, mujintou_GTool1),
				new MenuEntry(Color::Orange << "金のパチンコ所持変更", nullptr, mujintou_GTool2),
				new MenuEntry(Color::Orange << "金の網所持変更", nullptr, mujintou_GTool3),
				new MenuEntry(Color::Orange << "金のスコップ所持変更", nullptr, mujintou_GTool4),
				new MenuEntry(Color::Orange << "残り日数変更", nullptr, mujintou_hizuke1),
				new MenuEntry(Color::Orange << "経過日数変更", nullptr, mujintou_hizuke2),
				new MenuEntry(Color::Orange << "食料落下数変更", nullptr, mujintou_syokuryou1),
				new MenuEntry(Color::Orange << "リンゴゲージ変更", nullptr, mujintou_syokuryou2),
				new MenuEntry(Color::Orange << "食料所持数変更", nullptr, mujintou_syokuryou3),
				new MenuEntry(Color::Orange << "落とし穴無効化", nullptr, mujintou_Otosiana),
				new MenuEntry(Color::Orange << "特技変更P1", nullptr, mujintou_TokugiP1),
				new MenuEntry(Color::Orange << "特技変更P2", nullptr, mujintou_TokugiP2),
				new MenuEntry(Color::Orange << "特技変更P3", nullptr, mujintou_TokugiP3),
				new MenuEntry(Color::Orange << "好きな食べ物変更P1", nullptr, mujintou_FoodP1),
				new MenuEntry(Color::Orange << "好きな食べ物変更P2", nullptr, mujintou_FoodP2),
				new MenuEntry(Color::Orange << "好きな食べ物変更P3", nullptr, mujintou_FoodP3),
			});


		MenuFolder *misc = new MenuFolder(Color::DodgerBlue << "その他");
		{
			*misc += new MenuEntry(Color::DodgerBlue << "村の明るさ変更", nullptr, akarusa_change);
			*misc += new MenuEntry(Color::DodgerBlue << "ゲーム速度上昇", nullptr, FastGameSpeed);
			*misc += new MenuEntry(Color::DodgerBlue << "サーバー変更", nullptr, ChangeIslandServer);
			*misc += new MenuEntry(Color::DodgerBlue << "遠距離カメラ", nullptr, FarCamera);
			*misc += new MenuEntry(Color::DodgerBlue << "花や木のサイズ変更", nullptr, ChangeFlowerTreeSize);
			*misc += new MenuEntry(Color::DodgerBlue << "画面崩壊", nullptr, CrazyScreen);
			*misc += new MenuEntry(Color::DodgerBlue << "室内の家具動かす", nullptr, MoveFurniture);
			*misc += new MenuEntry(Color::DodgerBlue << "天気変更", nullptr, ChangeWeather);
			*misc += new MenuEntry(Color::DodgerBlue << "駅の旗大きさ変更", nullptr, frag_change, Color::SkyBlue << "駅の旗の大きさを変更できる。");
			*misc += new MenuEntry(Color::DodgerBlue << "キーボード改行", KeyboardExtender);
			*misc += EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "カメラ操作", MoveCamera),
			{
				Hotkey(Key::Y + L, "固定"),
				Hotkey(Key::R, "回転"),
				Hotkey(Key::B, "移動"),
			});
			*misc += EntryWithHotkey(new MenuEntry(Color::DodgerBlue << "チャットコピぺ", ChatCopyPaste),
			{
				Hotkey(Key::R + DU, "コピー"),
				Hotkey(Key::R + DD, "ペースト"),
			});
			*misc += new MenuEntry("漢字変換", KanjiHenkan);
			*misc += new MenuFolder("デバッガ / サーチ補助",
			{
				EntryWithHotkey(new MenuEntry("アドレス監視", ViewAddress),
				{
					Hotkey(Key::R + A, "アドレス変更"),
					Hotkey(Key::R + B, "リストに追加"),
					Hotkey(Key::R + X, "リスト変更"),
				}),
				new MenuEntry("1Fずつ実行(レジスタ表示)", Sleep, "L: ゲーム停止\nDR: ゲーム再生( 1フレーム )\nR: ゲーム再開"),
				new MenuEntry("HEXエディタ", HexEditor),
			});
			
		}
		menu += misc;
		
		
		menu += TextToCheats;
		
	}
}


