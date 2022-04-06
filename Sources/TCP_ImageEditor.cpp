// ---------------------------------------------------------------
// ソパカ写真編集   Mr.zkR
// 2020-3-16  v0.00
// 2020-3-26  v1.02 大幅な機能改善
// ---------------------------------------------------------------

#include "Helpers.hpp"
#include "cheats.hpp"

#define IMAGE_WIDTH		64
#define IMAGE_HEIGHT	104

namespace CTRPluginFramework
{
	Color Image[IMAGE_WIDTH][IMAGE_HEIGHT];
	
	void Update();
	void DrawEditor(const Screen &, const Screen &);
	
	bool Draw(const Screen &);
	void Line(int, int, int, int, Color);
	Point TchXY[2];
	
	bool Loop = false;
	
	void TCP_ImageEditor(MenuEntry *e)
	{
		if ( !e->Hotkeys[0].IsDown() ) return;
		
		if ( *(u16*)(0x95133a) == 0xa55c )
		{
			bool BottomUI  = *(u32*)(0x949d1f) == 0x6 || *(u32*)(0x949d1f) == 0x8a;
			bool ScreenTWQ = *(u16*)(0x946be8) == 0x6d30;
			if ( !BottomUI || !ScreenTWQ )
			{
				(MessageBox("カウント中のみ使えます。"))();
				return;
			}
		}
		else
		{
			if ( (MessageBox("ここは写真機ではありません。\nワープしますか？"))() )
			{
				volatile u32(*pfunction04)(u32 param1, u32 param2, u32 param3, u32 param4);
				Process::Write32( (u32)&pfunction04, 0x304A94 );
				pfunction04(0x5C, 1, 1, 0);
			}
			return;
		}
		
		// 描画する色
		Color PutPixel = Color::White;
		
		Process::Pause();
		
		const Screen &top = OSD::GetTopScreen();
		const Screen &bottom = OSD::GetBottomScreen();
		
		// 上画面の写真部分をImage配列に保存
		for ( int sy = 0; sy < IMAGE_HEIGHT; sy++ )
			for ( int sx = 0; sx < IMAGE_WIDTH; sx++ )
			{
				top.ReadPixel(168 + sx, 63 + sy, Image[sx][sy]);
			}
		
		// メインループ
		Loop = true;
		while ( Loop )
		{
			Controller::Update();
			Update();
			DrawEditor(top, bottom);
			OSD::SwapBuffers();
		}
		
		Process::Play();
		
		OSD::Run(Draw);
		while ( *(u16*)(0x946be8) != 0x9cc0 )
		{
			Sleep( Milliseconds(10) );
		}
		OSD::Stop(Draw);
		
		
		
		
	}

	
	void Update()
	{
		
		
	}
	

	void DrawEditor(const Screen &top, const Screen &bottom)
	{
		// 
		
		
	}


	// 写真描画
	bool Draw(const Screen &scr)
	{
		if ( !scr.IsTop ) return false;
		
		for ( int sy = 0; sy < IMAGE_HEIGHT; sy++ )
			for ( int sx = 0; sx < IMAGE_WIDTH; sx++ )
				scr.DrawPixel(160 + sx, 56 + sy, Image[sx][sy]);
		
		scr.Draw("Please wait...", 398 - OSD::GetTextWidth(false, "DOODLE DoooOOO"), 220);
		
		return true;
	}
	
	
	// 線を描画
	void Line(int sx, int sy, int dx, int dy, Color c)
	{
		int x = sx, y = sy;
		int wx = (sx >= dx ? sx - dx : dx - sx);
		int wy = (sy >= dy ? sy - dy : dy - sy);
		bool xmode = (wx >= wy);
		int gosa = 0;
		
		while ( x != dx || y != dy )
		{
			Image[x][y] = c;
			if ( xmode )
			{
				if ( sx < dx )
					x++;
				else
					x--;
				
				gosa += ((dy - sy) << 1);
				if ( gosa > wx )
				{
					y++;
					gosa -= (wx << 1);
				}
				else if ( gosa < -wx )
				{
					y--;
					gosa += (wx << 1);
				}
			}
			else
			{
				if ( sy < dy )
					y++;
				else
					y--;
				
				gosa += ((dx - sx) << 1);
				if ( gosa > wy )
				{
					x++;
					gosa -= (wy << 1);
				}
				else if ( gosa < -wy )
				{
					x--;
					gosa += (wy << 1);
				}
			}
		}
		
		
		
	}
	
	
	
	
}



