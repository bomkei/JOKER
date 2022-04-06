#pragma once

namespace Zstd
{
	using namespace std;
	
	class StringUtil
	{
	public:
		static int lenUtf8(string &str);
		static int lenByte(unsigned char c);
	};
	
	class Chat
	{
	public:
		// チャットを開いているか(false = 開いてない, true = 開いている)
		bool IsOpened();
		
		// 書き込み
		void Write(string str);
		
		// 書き込み Utf16
		void Writeu(const u16 StrArray[], int index);
		
		// 読み取り
		string Read();
		
		// 読み取り Utf16
		void Readu(u16 output[], int index, int size = 0);
		
		// 選択中の文字列を得る
		string GetSelectedString();
		
		// 選択されていない部分の文字列を取得する
		string GetUnselectedString(int right = -1);
		
		// 文字コード変換
		void Change(int mode);
		
		// 送信
		void Send();
		
		// 全部消去する
		void Clear();
		
	private:
		u32 _get_text_buffer_addr();
		bool _isTown();
		void _write_length(u8);
		u8 _read_length();
		u32 len_addr();
		
	};
	
	
}


