#include "cheats.hpp"

namespace CTRPluginFramework
{
	using NVMvector = std::vector<NAME_VALUE_MAP>;
	std::vector<std::string> items(200);

	// 構造体配列の中から文字列だけを取り出して、StringVectorを作成する。
	void CreateStringVector(NVMvector map_items)
	{
		items.clear();

		for (const NAME_VALUE_MAP& i : map_items)
			items.push_back(i.name);
	}

	extern const std::vector< NAME_VALUE_MAP > Tool;

	// クラブ４４４のハニワ
	static const	std::vector< NAME_VALUE_MAP > Club444_Item =
	{
		{ "ハニワ左",			0x31FB4792 },
		{ "ハニワ左中央",		0x31FB4796 },
		{ "ハニワ右中央",		0x31FB479A },
		{ "ハニワ右",			0x31FB479E }
	};

	// たぬきハウジング商品
	static const	std::vector< NAME_VALUE_MAP > Housing_Item =
	{
		{ "石畳",					0x31FB46CE },
		{ "屋根",					0x31FB46D2 },
		{ "壁",					0x31FB46D6 },
		{ "柵",					0x31FB46DA },
		{ "ポスト",				0x31FB46DE },
		{ "ドア左",				0x31FB46E2 },
		{ "ドア右",				0x31FB46E6 },
		{ "建物",					0x31FB46EA },
	};

	// デパート1f
	static const	std::vector< NAME_VALUE_MAP > DepartmentStore_Item =
	{
		{ "フォーチュンクッキー上",	0x31FABCAC },
		{ "フォーチュンクッキー下",	0x31FABCB0 },
		{ "ツール上",					0x31FABC70 },
		{ "ツール真ん中",				0x31FABC78 },
		{ "ツール下",					0x31FABC7C },
		{ "音楽左",					0x31FABCA4 },
		{ "音楽右",					0x31FABCA8 },
		{ "お薬", 						0x31FABCA0 },
		{ "ラッピング", 				0x31FABC90 },
		{ "手紙上", 					0x31FABC94 },
		{ "手紙下",					0x31FABC98 },
		{ "メロディーカード",		0x31FABC9C },
	};

	// デパート2f
	static const	std::vector< NAME_VALUE_MAP > DepartmentStoreF2_Item =
	{
		{ "壁掛け左"	, 			0x31FABCB4 },
		{ "壁掛け右"	, 			0x31FABCB8 },
		{ "家具左上"	, 			0x31FABCBC },
		{ "家具左下"	, 			0x31FABCC4 },
		{ "家具中央"	, 			0x31FABCC8 },
		{ "家具右下"	, 			0x31FABCCC },
		{ "家具右上"	, 			0x31FABCC0 },
		{ "壁紙上"		, 			0x31FABC80 },
		{ "壁紙下"		, 			0x31FABC84 },
		{ "床上"		, 			0x31FABC88 },
		{ "床下"		, 			0x31FABC8C },
	};

	// デパート3f
	static const	std::vector< NAME_VALUE_MAP > DepartmentStoreF3_Item =
	{
		{ "床", 		0x31FB4710 },
		{ "壁紙", 		0x31FB470C },
		{ "家具左上",	0x31FB46F8 },
		{ "家具左下",	0x31FB4700 },
		{ "家具右下",	0x31FB4704 },
		{ "家具右上",	0x31FB46FC },
		{ "帽子左", 	0x31FB4714 },
		{ "帽子右", 	0x31FB4718 },
		{ "靴左", 		0x31FB471C },
		{ "靴右", 		0x31FB4720 },
		{ "ズボン左",	0x31FB4734 },
		{ "服左中央",	0x31FB4724 },
		{ "服左内側",	0x31FB4728 },
		{ "服右内側",	0x31FB472C },
		{ "服右中央",	0x31FB4730 },
		{ "ズボン右",	0x31FB4738 },
		{ "壁掛け", 	0x31FB4708 },
	};

	// ---------------------------------------------------------------
	// 園芸店変更
	// ---------------------------------------------------------------
	static const NVMvector engei_shop =
	{
		{ "未完成",			0x00 },
		{ "工事中",			0x01 },
		{ "完成",				0x02 },
		{ "ホームセンター",	0x03 },
		{ "デパート",			0x04 },
	};
	void change_engei(MenuEntry* e)
	{
		CreateStringVector(engei_shop);

		Keyboard keyboard("指定した園芸店に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FB00F4, engei_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// まめつぶ変更
	// ---------------------------------------------------------------
	static const NVMvector mametubu_shop =
	{
		{ "商店",					0x00 },
		{ "コンビニ",				0x01 },
		{ "スーパーマーケット",	0x02 },
		{ "ホームセンター",		0x03 },
		{ "デパート",				0x04 },
	};
	void change_mametubu(MenuEntry* e)
	{
		CreateStringVector(mametubu_shop);

		Keyboard keyboard("指定したまめつぶショップに変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FABC64, mametubu_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// 　占いの館
	// ---------------------------------------------------------------
	static const NVMvector uranai_shop =
	{
		{ "未完成", 0x00	},
		{ "完成", 0x01 },
	};
	void change_uranai(MenuEntry* e)
	{
		CreateStringVector(uranai_shop);

		Keyboard keyboard("指定した占いの館に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FB47A4, uranai_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// 夢見の館変更
	// ---------------------------------------------------------------
	static const NVMvector yumemi_shop =
	{
		{ "未完成", 0x00 },
		{ "完成", 0x01	 },
	};
	void change_yumemi(MenuEntry* e)
	{
		CreateStringVector(yumemi_shop);

		Keyboard keyboard("指定した夢見の館に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FB47A2, yumemi_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// CLUB444変更
	// ---------------------------------------------------------------
	static const NVMvector kurabu_shop =
	{
		{ "未完成", 0x00},
		{ "完成", 0x02 },
	};
	void change_kurabu(MenuEntry* e)
	{
		CreateStringVector(kurabu_shop);

		Keyboard keyboard("指定したCLUB444に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FB4782, kurabu_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// 美容院
	// ---------------------------------------------------------------
	static const NVMvector biyouin_shop =
	{
		{ "未完成", 0x00 },
		{ "工事中", 0x01 },
		{ "完成", 0x02 },
	};
	void change_biyouin(MenuEntry* e)
	{
		CreateStringVector(biyouin_shop);

		Keyboard keyboard("指定した美容院に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FB47B4, biyouin_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// 靴屋変更
	// ---------------------------------------------------------------
	static const NVMvector kutuya_shop =
	{
		{ "未完成", 0x00 },
		{ "工事中", 0x01 },
		{ "完成", 0x02 },
	};
	void change_kutuya(MenuEntry* e)
	{
		CreateStringVector(kutuya_shop);

		Keyboard keyboard("指定した靴屋に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FB022C, kutuya_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// 博物館変更
	// ---------------------------------------------------------------
	static const NVMvector hakubutukan_shop =
	{
		{ "F2未完成", 0x00 },
		{ "F2完成", 0x01 }
	};
	void change_hakubutukan(MenuEntry* e)
	{
		CreateStringVector(hakubutukan_shop);

		Keyboard keyboard("指定した博物館に変化。", items);
		int choice = keyboard.Open();
		if (choice >= 0) Process::Write8(0x31FB46BC, hakubutukan_shop[choice].value);
	}


	// ---------------------------------------------------------------
	// CLUB444ハニワ変更
	// ---------------------------------------------------------------
	void Change_Club444(MenuEntry* e)
	{
		u16 a; // <-- ここに移動
		CreateStringVector(Club444_Item);

		Keyboard keyboard("ハニワ変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) // <-- aiueo.Open( a );
				Process::Write16(Club444_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// 不動産屋
	// ---------------------------------------------------------------
	void Change_Housing(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(Housing_Item);

		Keyboard keyboard("エクステリア変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(Housing_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// デパートF1
	// ---------------------------------------------------------------
	void Change_Department_store(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(DepartmentStore_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(DepartmentStore_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// デパート2f
	// ---------------------------------------------------------------
	void Change_Department_store_F2(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(DepartmentStoreF2_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0)
				Process::Write16(DepartmentStoreF2_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// デパートF3
	// ---------------------------------------------------------------
	void Change_Department_store_F3(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(DepartmentStoreF3_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(DepartmentStoreF3_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// デパート園芸店
	// ---------------------------------------------------------------
	static const NVMvector DepartmentStoreEngei_Item =
	{
		{ "ツール左", 			0x31FB00FA },
		{ "ツール右",  			0x31FB00FE },
		{ "肥料",  				0x31FB011E },
		{ "果物",  				0x31FB010A },
		{ "苗",  					0x31FB0102 },
		{ "低木上",  				0x31FB0112 },
		{ "低木下",  				0x31FB010E },
		{ "種下",  				0x31FB011A },
		{ "種上",   				0x31FB0116 },
		{ "家具",  				0x31FB00F6 },
		{ "ラッピング",  			0x31FABC90 },
		{ "手紙左",   				0x31FABC98 },
		{ "手紙右",  				0x31FABC94 },
		{ "メロディーカード", 	0x31FABC9C },
		{ "ツール上", 			0x31FABC70 },
		{ "ツール真ん中", 		0x31FABC78 },
		{ "ツール下", 			0x31FABC7C },
	};
	void Change_Department_store_Engei(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(DepartmentStoreEngei_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(DepartmentStoreEngei_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// ホームセンター
	// ---------------------------------------------------------------
	static const NVMvector HomeCenter_Item =
	{
		{ "家具左外側", 				0x31FABCBC },
		{ "家具左内側", 				0x31FABCC0 },
		{ "壁掛け",  					0x31FABCB4 },
		{ "家具右内側",   			0x31FABCC4 },
		{ "家具右外側", 				0x31FABCC8 },
		{ "音楽左", 					0x31FABCA4 },
		{ "フォーチュンクッキー上",	0x31FABCAC },
		{ "フォーチュンクッキー下",	0x31FABCB0 },
		{ "壁紙左", 					0x31FABC80 },
		{ "壁紙右",  					0x31FABC84 },
		{ "床左",  					0x31FABC88 },
		{ "床右",  					0x31FABC8C },
		{ "お薬", 						0x31FABCA0 },
	};
	void Change_HomeCenter(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(HomeCenter_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(HomeCenter_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// ホームセンター園芸店
	// ---------------------------------------------------------------
	static const NVMvector HomeCenterEngei_Item =
	{
		{ "ツール",	0x31FB00FA },
		{ "苗",		0x31FB0102 },
		{ "低木左",	0x31FB0112 },
		{ "低木右",	0x31FB010E },
		{ "種左",		0x31FB011A },
		{ "種右",		0x31FB0116 },
		{ "家具",		0x31FB00F6 },
	};
	void Change_HomeCenter_Engei(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(HomeCenterEngei_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(HomeCenterEngei_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// スーパー商品変更
	// ---------------------------------------------------------------
	static const NVMvector SuperMarket_Item =
	{
		{ "家具上",					0x31FABCBC },
		{ "家具真ん中",				0x31FABCC0 },
		{ "家具下",					0x31FABCC4 },
		{ "壁掛け",					0x31FABCB4 },
		{ "壁紙左",					0x31FABC80 },
		{ "壁紙右",					0x31FABC84 },
		{ "床左",						0x31FABC88 },
		{ "床右",						0x31FABC8C },
		{ "フォーチュンクッキー上",	0x31FABCAC },
		{ "フォーチュンクッキー下",	0x31FABCB0 },
		{ "ツール左",					0x31FABC70 },
		{ "ツール真ん中",				0x31FABC78 },
		{ "ツール右",					0x31FABC7C },
		{ "お薬",						0x31FABCA0 },
		{ "ラッピング",				0x31FABC90 },
		{ "手紙左",					0x31FABC94 },
		{ "手紙右",					0x31FABC98 },
		{ "メロディーカード",		0x31FABC9C },
	};
	void Change_SuperMarket(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(SuperMarket_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(SuperMarket_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// スーパー&コンビニ園芸店
	// ---------------------------------------------------------------
	static const NVMvector SuperMarketandConvenienceStore_Item =
	{
		{ "種左",		0x31FB011A },
		{ "種右",		0x31FB0116 },
		{ "苗",		0x31FB0102  },
		{ "ツール",	0x31FB00FA},
	};
	void Change_SuperMarketandConvenienceStore(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(SuperMarketandConvenienceStore_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(SuperMarketandConvenienceStore_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// コンビニ商品変更
	// ---------------------------------------------------------------
	static const NVMvector ConvenienceStore_Item =
	{
		{ "家具上",					0x31FABCBC },
		{ "家具真ん中",				0x31FABCC0 },
		{ "家具下",					0x31FABCC4 },
		{ "壁紙",						0x31FABC80 },
		{ "床",						0x31FABC88 },
		{ "ラッピング",				0x31FABC90 },
		{ "手紙",						0x31FABC94 },
		{ "ツール左",					0x31FABC70 },
		{ "ツール右",					0x31FABC78 },
		{ "フォーチュンクッキー上",	0x31FABCAC },
		{ "フォーチュンクッキー下",	0x31FABCB0 },
		{ "お薬",						0x31FABCA0 },
	};
	void Change_ConvenienceStore(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(ConvenienceStore_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(ConvenienceStore_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// 商店商品変更
	// ---------------------------------------------------------------
	static const 	NVMvector Syuten_Item =
	{
		{  "家具左",  						0x31FABCBC },
		{  "家具右",  						0x31FABCC0 },
		{  "ラッピング", 					0x31FABC90 },
		{  "手紙",  						0x31FABC94 },
		{  "ツール", 						0x31FABC70 },
		{  "フォーチュンクッキー上",  	0x31FABCAC },
	};
	void Change_Syuten(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(Syuten_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(Syuten_Item[choice].value, a);
		}
	}


	// ---------------------------------------------------------------
	// 服屋商品変更
	// ---------------------------------------------------------------
	static const NVMvector Cloth_shop_Item =
	{
		{ "左内側", 	0x31FABCEC },
		{ "左中央",  	0x31FABCF0 },
		{  "中央", 	0x31FABCF4 },
		{  "右内側", 	0x31FABCF8 },
		{  "右外側", 	0x31FABCFC },
	};
	void Change_Cloth_shop(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(Cloth_shop_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(Cloth_shop_Item[choice].value, a);
		}
	}


	// ---------------------------------------------------------------
	// アクセサリー屋商品変更
	// ---------------------------------------------------------------
	static const NVMvector Accessory_Shop_Item =
	{
		{ "帽子左",  				0x31FB00B8 },
		{ "帽子中央",				0x31FB00BC },
		{ "帽子右", 				0x31FB00C0 },
		{ "アクセサリー上",		0x31FB00C4 },
		{ "アクセサリー中央",	0x31FB00C8 },
		{ "アクセサリー下",		0x31FB00CC },
		{ "傘", 					0x31FB00D0 },
	};
	void Change_Accessory_Shop(MenuEntry* e)
	{
		u16 a;
		CreateStringVector(Accessory_Shop_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			if (aiueo.Open(a) >= 0) Process::Write16(Accessory_Shop_Item[choice].value, a);
		}
	}


	// ---------------------------------------------------------------
	// 靴商品変更
	// ---------------------------------------------------------------
	static const NVMvector Shoe_Shop_Item =
	{
		{ "靴左外側", 	0x31FB022E },
		{ "靴左中央", 	0x31FB0232 },
		{ "靴右中央", 	0x31FB0236 },
		{ "靴右外側", 	0x31FB023A },
		{ "靴下右", 		0x31FB023E },
		{ "靴下左"	, 		0x31FB0242 },
	};
	void Change_Shoe_Shop(MenuEntry* e)
	{
		CreateStringVector(Shoe_Shop_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			u16 a;
			aiueo.Open(a);
			Process::Write16(Shoe_Shop_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// 交番商品変更
	// ---------------------------------------------------------------
	static const NVMvector PoliceStation_Item =
	{
		{ "左上", 		0x31FABBE2 },
		{ "左上外側",	0x31FABBE6 },
		{ "左上内側",	0x31FABBEA },
		{ "右上内側",	0x31FABBEE },
		{ "右上外側",	0x31FABBF2 },
		{ "右上", 		0x31FABBF6 },
		{ "左下", 		0x31FABBFA },
		{ "中央左", 	0x31FABBFE },
		{ "中央右", 	0x31FABC02 },
		{ "右下", 		0x31FABC06 },
	};
	void Change_PoliceStation(MenuEntry* e)
	{
		CreateStringVector(PoliceStation_Item);

		Keyboard keyboard("落とし物変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			u16 a;
			aiueo.Open(a);
			Process::Write16(PoliceStation_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// オートキャンプ場商品変更
	// ---------------------------------------------------------------
	static const NVMvector Camp_Item =
	{
		{  "左", 0x31FB4854 },
		{  "右", 0x31FB4858 },
	};
	void Change_Camp(MenuEntry* e)
	{
		CreateStringVector(Camp_Item);

		Keyboard keyboard("商品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			u16 a;
			aiueo.Open(a);
			Process::Write16(Camp_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// 博物館二階商品変更
	// ---------------------------------------------------------------
	static const NVMvector Hakubutukan_Item =
	{
		{  "上", 0x31FB46BE },
		{  "左", 0x31FB46C2 },
		{  "右", 0x31FB46C6 },
	};
	void Change_Hakubutukan(MenuEntry* e)
	{
		CreateStringVector(Hakubutukan_Item);

		Keyboard keyboard("記念販売品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			u16 a;
			aiueo.Open(a);
			Process::Write16(Hakubutukan_Item[choice].value, a);
		}
	}


	// ---------------------------------------------------------------
	// 島お土産変更
	// ---------------------------------------------------------------
	void Change_Island(MenuEntry* entry)
	{
		static u32 id;
		static int place;

		if (Controller::IsKeysPressed(X + DL))
		{
			Keyboard key("アイテムIDを入力してください");
			key.Open(id);
			OSD::SwapBuffers();
			Keyboard key2("アイテム場所変更",
				{
					"右上", "左", "真ん中", "右"
				});
			place = key2.Open();
			Process::Write32(0x3305b810 + (place * 0x4), id);
		}
	}

	// ---------------------------------------------------------------
	// いなりギャラリー商品変更
	// ---------------------------------------------------------------
	static const NVMvector Gallery_Item =
	{
		{ "左上", 0x31FB0130 },
		{ "右上", 0x31FB0134 },
		{ "左下", 0x31FB0138 },
		{ "右下", 0x31FB013C },
	};
	void Change_Gallery(MenuEntry* e)
	{
		CreateStringVector(Gallery_Item);

		Keyboard keyboard("美術品変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			u16 a;
			aiueo.Open(a);
			Process::Write16(Gallery_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// リサイクルショップ商品変更
	// ---------------------------------------------------------------
	static const NVMvector Recycle_Shop_Item =
	{
		{  "前左",  0x31FB02CC   },
		{  "前右", 0x31FB02D0   },
		{  "真ん中左", 0x31FB02C4   },
		{  "真ん中右",  0x31FB02C8  },
		{  "後ろ左外側",  0x31FB02B4  },
		{  "後ろ左内側",  0x31FB02B8  },
		{  "後ろ右内側",  0x31FB02BC  },
		{  "後ろ右外側",  0x31FB02C0  },
		{  "リメイク前P1",  0x31FB024C  },
		{  "リメイク後P1", 0x31FB025C   },
	};
	void Change_Recycle_Shop(MenuEntry* e)
	{
		CreateStringVector(Recycle_Shop_Item);

		Keyboard keyboard("出品物変更先を指定してください。", items);
		int choice = keyboard.Open();
		if (choice >= 0)
		{
			Keyboard aiueo("指定したアイテムに変化。");
			u16 a;
			aiueo.Open(a);
			Process::Write16(Recycle_Shop_Item[choice].value, a);
		}
	}

	// ---------------------------------------------------------------
	// 駅の旗大きさ変更
	// ---------------------------------------------------------------
	void frag_change(MenuEntry* e) {
		float fxx;

		Keyboard keyboard(Utils::Format("指定した旗のサイズに変化。/nデフォルト14.1421/nmin1.8750/nmax536870912"));
		int choice = keyboard.Open(fxx);
		if (choice >= 0)
			if (fxx >= 1.8750 && fxx <= 536870912) Process::WriteFloat(0x001C8CAC, fxx);
	}

	// ---------------------------------------------------------------
	// 高額買取品変更
	// ---------------------------------------------------------------
	void Change_Recycle1(MenuEntry* e) {
		u16 fxx;

		Keyboard keyboard("指定したアイテムに変化。");
		int choice = keyboard.Open(fxx);
		if (choice >= 0) Process::Write16(0x31FB02A0, fxx);
	}


}

