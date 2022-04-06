#include "cheats.hpp"
#include "Item.h"
#include "kanji.h"

void abort(void);

namespace CTRPluginFramework
{
	using StringVector = std::vector<std::string>;
	
	// カタカナをひらがなにする
	void k2h( std::string &str )
	{
		u16 Utf16_Str[200] = { 0 };
		
		Process::WriteString( (u32)Utf16_Str, str, StringFormat::Utf16 );
		
		for (u16 &moji : Utf16_Str)
			if ( moji >= 0x30a1 && moji <= 0x30f3 ) moji -= 0x60;
		
		Process::ReadString( (u32)Utf16_Str, str, 200, StringFormat::Utf16 );
	}
	
	
	// ---------------------------------------------------------------
	// アイテム検索
	// ～アイテム一覧の中から検索して、一致した場合はoutputに追加します。
	// ・str	: 探す文字列
	// ・output	: 追加されるベクター配列(ITEM_MAP)
	// ---------------------------------------------------------------
	void ItemSearch(const std::string &str, std::vector<ITEM_MAP> &output)
	{
		std::string tmp;
		for ( const ITEM_MAP &i: AllItems )
		{
			tmp = i.name2;
			k2h(tmp);
			
			if ( tmp.find(str) != std::string::npos )
				output.push_back(i);
		}
	}
	
	
	// ---------------------------------------------------------------
	// コマンドでチート実行
	// ---------------------------------------------------------------
	void OpenCatalog();
	void TextToCheats()
	{
		std::string com;
		Chat chat;
		
		if ( !chat.IsOpened() ) return;
		
		if ( Controller::IsKeyDown(B) && Controller::IsKeyPressed(R) )
		{
			com = chat.Read();
			
			if ( com == "drop on" )
			{
				chat.Write("ドロップを有効化しました");
				Process::Write32(0x5a0e50, 0xaffff84);
			}
			else if ( com == "drop off" )
			{
				chat.Write("ドロップを無効化しました");
				Process::Write32(0x5a0e50, 0xeaffff84);
			}
			else if ( com == "keyboard" )
			{
				/*
				static SwkbdState swkbd;
				static char mybuf[60];
				static SwkbdStatusData swkbdStatus;
				static SwkbdLearningData swkbdLearning;
				SwkbdButton button = SWKBD_BUTTON_NONE;
				bool didit = false;
				`
				swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 3, -1);
				swkbdSetInitialText(&swkbd, mybuf);
				swkbdSetHintText(&swkbd, "Please enter dank memes");
				swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Maybe Not", false);
				swkbdSetButton(&swkbd, SWKBD_BUTTON_MIDDLE, "~Middle~", true);
				swkbdSetButton(&swkbd, SWKBD_BUTTON_RIGHT, "Do It", true);
				swkbdSetFeatures(&swkbd, SWKBD_PREDICTIVE_INPUT);
				SwkbdDictWord words[2];
				swkbdSetDictWord(&words[0], "lenny", "( ͡° ͜ʖ ͡°)");
				swkbdSetDictWord(&words[1], "shrug", "¯\\_(ツ)_/¯");
				swkbdSetDictionary(&swkbd, words, sizeof(words)/sizeof(SwkbdDictWord));
				static bool reload = false;
				swkbdSetStatusData(&swkbd, &swkbdStatus, reload, true);
				swkbdSetLearningData(&swkbd, &swkbdLearning, reload, true);
				reload = true;
				button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
				*/
				
			}
			else if ( com.length() > 0 )// アイテム検索
			{
				std::vector<ITEM_MAP> Hits;
				ItemSearch(com, Hits);
				
				if ( !Hits.empty() )
				{
					if ( Hits.size() > 40 )
					{
						MessageBox("エラー", "一致するアイテム数が多すぎます。\nもう少し詳細に記述してください。")();
					}
					else
					{
						StringVector Names;
						Names.clear();
						
						for ( const ITEM_MAP &i: Hits )
							Names.push_back(i.name2);
						
						Keyboard key("", Names);
						int result = key.Open();
						
						if ( result >= 0 )
						{
							OSD::SwapBuffers();
							Sleep(Seconds(0.05));
							
							Player p;
							p.SetItem(Hits[result].code, 0);
							
							MessageBox("スロット1: " + Names[result])();
						}
					}
				}
			}
			
			
			
			
		}
	}
	
	
	void OpenCatalog()
	{
		
		
		
	}
	
	
}






