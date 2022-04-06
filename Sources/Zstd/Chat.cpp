#include "3ds.h"
#include "CTRPluginFramework.hpp"
#include "Zstd/Chat.hpp"

namespace Zstd
{
	using namespace CTRPluginFramework;
	
	int StringUtil::lenUtf8(std::string &str)
	{
		auto _pstr = str.c_str();
		
		int i = 0;
		int len = 0;
		
		while (_pstr[i] != '\0')
		{
			len++;
			i += lenByte(_pstr[i]);
		}
		
		return len;
	}
	
	int StringUtil::lenByte(unsigned char c)
	{
		if ((c >= 0x00) && (c <= 0x7f))
			return 1;
		else if ((c >= 0xc2) && (c <= 0xdf))
			return 2;
		else if ((c >= 0xe0) && (c <= 0xef))
			return 3;
		else if ((c >= 0xe0) && (c <= 0xef))
			return 4;
		
		return 0;
	}
	
	// チャットを開いているか(false = 開いてない, true = 開いている)
	bool Chat::IsOpened()
	{
		if ( *(u32*)0x958114 == 0 ) return false;
		return true;
	}
	
	// 書き込み
	void Chat::Write(string str)
	{
		if ( !IsOpened() ) return;
		
		Clear();
		_write_length(StringUtil::lenUtf8(str));
		Process::WriteString( _get_text_buffer_addr(), str, StringFormat::Utf16 );
	}
	
	
	// 書き込み Utf16
	void Chat::Writeu(const u16 StrArray[], int index)
	{
		if ( !IsOpened() ) return;
		
		int i = 0;
		
		while(StrArray[i])
		{
			Process::Write16( _get_text_buffer_addr() + (index + i) * 0x4, StrArray[i] );
			i++;
		}
	}
	
	// 読み取り
	std::string Chat::Read()
	{
		if ( !IsOpened() ) return std::string("");
		
		std::string str;
		Process::ReadString(_get_text_buffer_addr(), str, 33, StringFormat::Utf16);
		
		return str;
	}
	
	// 読み取り Utf16
	void Chat::Readu(u16 output[], int index, int size)
	{
		for ( int i = 0; i < ( size==0 ? _read_length() : size ); i++ )
			Process::Read16( _get_text_buffer_addr() + (index + i) * 0x2, output[i] );
	}
	
	// 選択中の文字列を得る
	string Chat::GetSelectedString()
	{
		string r;
		u8 Length;
		u8 Pos1 = *(u8*)0x32e15634;// カーソル1
		u8 Pos2 = *(u8*)0x32e1562c;// カーソル2
		
		if ( Pos1 == Pos2 ) return "";
		
		// 右に選択
		if ( Pos1 < Pos2 )
		{
			Length = Pos2 - Pos1;
			r = Read().substr(Pos1, Length);
		}
		else // 左に選択
		{
			Length = Pos1 - Pos2;
			r = Read().substr(Pos2, Length);
		}
		
		return r;
	}
	
	// 選択されていない部分の文字列を取得する
	// right : 0 = 左側  1 = 右側
	// 省略時 : 両方を足したものを取得する
	string Chat::GetUnselectedString(int right)
	{
		string r;
		u8 Length;
		u8 Pos1 = *(u8*)0x32e15634;// カーソル1
		u8 Pos2 = *(u8*)0x32e1562c;// カーソル2
		
		if ( Pos1 == Pos2 ) return "";
		
		u8 b = (Pos1 < Pos2) ? Pos1 : Pos2;
		
		if ( right == 0 )
		{
			Process::ReadString(_get_text_buffer_addr(), r, b, StringFormat::Utf16);
		}
		else if ( right == 1 )
		{
			Process::ReadString(_get_text_buffer_addr() + b, r, 33 - b, StringFormat::Utf16);
		}
		else
		{
			
			string r2;
			Process::ReadString(_get_text_buffer_addr(), r, b, StringFormat::Utf16);
			Process::ReadString(_get_text_buffer_addr() + b, r2, 33 - b, StringFormat::Utf16);
			return (r + r2);
		}
		
		return r;
	}
	
	// 文字コード変換
	void Chat::Change(int mode)
	{
		u16 *c = (u16*)_get_text_buffer_addr();
		
		for ( int i = 0; i < _read_length(); i++ )
		{
			//Process::Read16( _get_text_buffer_addr() + i * 0x2, c );
			c++;
			
			// 英語をすべて大文字にする
			if ( mode == 0 )
			{
				if ( *c >= 0x61 && *c <= 0x7a ) *c -= 0x20;
			}
			// 英語をすべて小文字にする
			else if ( mode == 1 )
			{
				if ( *c >= 0x41 && *c <= 0x5a ) *c += 0x20;
			}
			// 英語の小文字と大文字をひっくり返す
			else if ( mode == 2 )
			{
				if ( *c >= 0x61 && *c <= 0x7a )
					*c -= 0x20; // 大文字にする
				else if ( *c >= 0x41 && *c <= 0x5a )
					*c += 0x20; // 小文字にする
			}
			// ひらがなをすべてカタカナにする
			else if ( mode == 3 )
			{
				if ( *c >= 0x3042 && *c <= 0x3093 ) *c -= 0x60;
			}
			// カタカナをすべてひらがなにする
			else if ( mode == 4 )
			{
				if ( *c >= 0x30a2 && *c <= 0x30f3 ) *c += 0x60;
			}
			// ひらがなとカタカナをひっくり返す
			else if ( mode == 5 )
			{
				if ( *c >= 0x3042 && *c <= 0x3093 )
					*c -= 0x60; // カタカナにする
				else if ( *c >= 0x30a2 && *c <= 0x30f3 )
					*c += 0x60;// ひらがなにする
			}
		}
		
	}
	
	// 送信
	void Chat::Send()
	{
		if ( IsOpened() ) Process::Write32(0x9580e1, 0x1000001);
	}
	
	// 全部消去する
	void Chat::Clear()
	{
		if ( !IsOpened() ) return;
		
		u32 *addr = (u32*)( _get_text_buffer_addr() );
		for (int i = 0; i < 16; i++)
			addr[i] = 0;
	}
	
	//////////////
	
	u32 Chat::_get_text_buffer_addr()
	{
		return *(u32*)(0x958108);
	}
	
	bool Chat::_isTown()	
	{
		if ( READU32(0x32E2A080) == 0xCBBCBABB )
			return false;
		
		return true;
	}
	
	void Chat::_write_length(u8 len)
	{
		*(u8*)((*(u32*)0x958114) + 0x8) = len;
	}
	
	u8 Chat::_read_length()
	{
		return *(u8*)((*(u32*)0x958114) + 0x8);
	}
	
	u32 Chat::len_addr()
	{
		return (*(u32*)0x958114) + 0x8;
	}
	
	
}


