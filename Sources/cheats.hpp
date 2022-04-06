#pragma once

#include "3ds.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include "maps.hpp"
#include "CTRPluginFramework.hpp"
#include "Zstd.hpp"

using namespace Zstd;

namespace CTRPluginFramework
{
	using StringVector = std::vector < std::string >;
	using namespace std;
	
	bool Boot();
	void TextToCheats();
	
	/*
    ** ゲーム全般
    ********************/
	void ChangePlayer(MenuEntry*);
	void ChangeArea(MenuEntry*);
	void ChangeName(MenuEntry*);
	void ChangeRegion(MenuEntry*);
	void ChangeDenger(MenuEntry*);
	void ChangeBadge(MenuEntry*);
	void TCP_ImageEditor(MenuEntry*);
	
	
	/*
    ** モーション
    ********************/
	void Motion1(MenuEntry*);
	void Motion2(MenuEntry*);
	void Motion3(MenuEntry*);
	void Motion4(MenuEntry*);
	void Motion5(MenuEntry*);
	void Motion6(MenuEntry*);
	void Motion7(MenuEntry*);
	
	
	/*
    ** 動き、動作
    ********************/
		/*--------------------------*/
		// ドロップ
		void DropStopper(MenuEntry*);
		void DD_Spam(MenuEntry*);
		void ChangeItemID(MenuEntry*);
		void ChangeDropID(MenuEntry*);
		void TouchDrop(MenuEntry*);
		void AutoDrop(MenuEntry*);
		/*--------------------------*/
	void WalkDelete(MenuEntry*);			// 歩き消し
	void PickupMode(MenuEntry*);			// ピックアップ変更
	void Tools_1(MenuEntry*);				// 道具機能変更
	void Tools_2(MenuEntry*);				// 道具持ち方変更
	void IslandPlayerHijack(MenuEntry*);	// 乗っ取り
	void CoordinateModifier(MenuEntry*);	// 座標移動
	void Coord_setting(MenuEntry*);			// 座標移動のスピード変更
	void WalkOver(MenuEntry*);				// 壁抜け
	void SpeedHack(MenuEntry*);				// スピードハック
	void Pose1(MenuEntry*);					// 逆さま
	void Pose2(MenuEntry*);					// Tポーズ
	void FastClothChange(MenuEntry*);		// はや着替え
	void TouchWarp(MenuEntry*);				// タッチワープ
	void GridMove(MenuEntry*);				// マス目移動
	void Moguru_black(MenuEntry*);			// 潜ると空黒くなる
	
	
	/*
    ** アクション
    ********************/
	void Action(MenuEntry*);				// アクション
	void Action_n(MenuEntry*);				// アクション(番号取得用)
	
	
	/*
    ** インベントリ
    ********************/
	void DisableItemLocks(MenuEntry*);		// 未使用アイテムを表示
	void InfinityItem(MenuEntry*);			// 置いても無くならない
	void DeleteInvItems(MenuEntry*);		// すべて削除
	void InvItemOption(MenuEntry*);			// 選択肢変更
	void Copy(MenuEntry*);					// コピー
	void TextToItem(MenuEntry*);			// アイテム取得
	void ViewSlotItems(MenuEntry*);			// アイテムID表示
	
	
	/*
    ** 環境、整備
    ********************/
	void DeleteAllItem(MenuEntry*);
	void GameReload(MenuEntry*);
	
	
	/*
    ** ショップ
    ********************/
		/*---------------- 商店街の店のレベル ----------------*/
			void change_uranai(MenuEntry*);			// 占いの館
			void change_yumemi(MenuEntry*);			// 夢見の館
			void change_kurabu(MenuEntry*);			// CLUB444
			void change_mametubu(MenuEntry*);		// まめつぶ
			void change_engei(MenuEntry*);			// 園芸店
			void change_biyouin(MenuEntry*);		// 美容院
			void change_kutuya(MenuEntry*);			// 靴屋
			void change_hakubutukan(MenuEntry*);	// 博物館
		/*----------------------------------------------------*/
		/*--------------------- アイテム変更 ---------------------*/
			void Change_Club444(MenuEntry*);						// CLUB444ハニワ
			void Change_Housing(MenuEntry*);						// たぬきハウジング
			void Change_Department_store(MenuEntry*);				// デパート1f
			void Change_Department_store_F2(MenuEntry*);			// デパート2f
			void Change_Department_store_F3(MenuEntry*);			// デパート3f
			void Change_Department_store_Engei(MenuEntry*);			// ホームセンター
			void Change_HomeCenter(MenuEntry*);						// スーパーマーケット
			void Change_SuperMarket(MenuEntry*);					// まめつぶ商店
			void Change_Syuten(MenuEntry*);							// デパート園芸コーナー
			void Change_HomeCenter_Engei(MenuEntry*);				// ホームセンター園芸コーナー
			void Change_ConvenienceStore(MenuEntry*);				// コンビニ
			void Change_SuperMarketandConvenienceStore(MenuEntry*);	// スーパー＆コンビニ園芸コーナー
			void Change_Cloth_shop(MenuEntry*);						// エイブルシスターズ
			void Change_Accessory_Shop(MenuEntry*);					// エイブルシスターズ（アクセ）
			void Change_Shoe_Shop(MenuEntry*);						// 靴屋
			void Change_Hakubutukan(MenuEntry*);					// 博物館2f
			void Change_Island(MenuEntry*);							// 島お土産変更
			void Change_Camp(MenuEntry*);							// オートキャンプ場
			void Change_Gallery(MenuEntry*);						// いなりギャラリー
			void Change_PoliceStation(MenuEntry*);					// 交番落とし物
			void Change_Recycle_Shop(MenuEntry*);					// リサイクルショップ
		/*----------------------------------------------------*/
	void Change_Recycle1(MenuEntry*);		// 高額買取品変更
	
	
	/*
    ** 無人島
    ********************/
	void mujintou_hosuuP1(MenuEntry*);		// 歩数変更P1
	void mujintou_hosuuP2(MenuEntry*);		// 歩数変更P2
	void mujintou_hosuuP3(MenuEntry*);		// 歩数変更P3
	void hosuukotei(MenuEntry*);			// 歩数固定
	void mujinntou_stage_open(MenuEntry*);	// 歩いた時のスコア変更
	void Walkscore_kotei(MenuEntry*);		// 歩いた時のスコア固定
	void mujintou_WalkScore(MenuEntry*);	// ステージ開放率変更
	void mujintou_Item1(MenuEntry*);		// 棒所持数変更
	void mujintou_Item2(MenuEntry*);		// 糸所持数変更
	void mujintou_Item3(MenuEntry*);		// 布きれ所持数変更
	void mujintou_Item4(MenuEntry*);		// 石ころ所持数変更
	void mujintou_Item5(MenuEntry*);		// ぎんこうせき所持数変更
	void mujintou_Item6(MenuEntry*);		// きんこうせき所持数変更
	void mujintou_Item7(MenuEntry*);		// おくすり所持数変更
	void mujintou_hoof1(MenuEntry*);		// 丸太の入手数変更
	void mujintou_hoof2(MenuEntry*);		// 船の旗の入手数変更
	void mujintou_hoof3(MenuEntry*);		// 丸太の残りの数変更
	void mujintou_hoof4(MenuEntry*);		// 船の旗の残りの数変更
	void mujintou_Tool1(MenuEntry*);		// 釣り竿所持変更
	void mujintou_Tool2(MenuEntry*);		// パチンコ所持変更
	void mujintou_Tool3(MenuEntry*);		// 網所持変更
	void mujintou_Tool4(MenuEntry*);		// スコップ所持変更
	void mujintou_STool1(MenuEntry*);		// 銀の釣り竿所持変更
	void mujintou_STool2(MenuEntry*);		// 銀のパチンコ所持変更
	void mujintou_STool3(MenuEntry*);		// 銀の網所持変更
	void mujintou_STool4(MenuEntry*);		// 銀のスコップ所持変更
	void mujintou_GTool1(MenuEntry*);		// 金の釣り竿所持変更
	void mujintou_GTool2(MenuEntry*);		// 金のパチンコ所持変更
	void mujintou_GTool3(MenuEntry*);		// 金の網所持変更
	void mujintou_GTool4(MenuEntry*);		// 金のスコップ所持変更
	void mujintou_hizuke1(MenuEntry*);		// 残り日数変更
	void mujintou_hizuke2(MenuEntry*);		// 経過日数変更
	void mujintou_syokuryou1(MenuEntry*);	// 食料落下数変更
	void mujintou_syokuryou2(MenuEntry*);	// リンゴゲージ変更
	void mujintou_syokuryou3(MenuEntry*);	// 食料所持数変更
	void mujintou_Otosiana(MenuEntry*);		// 落とし穴無効化
	void mujintou_TokugiP1(MenuEntry*);		// 特技変更P1
	void mujintou_TokugiP2(MenuEntry*);		// 特技変更P2
	void mujintou_TokugiP3(MenuEntry*);		// 特技変更P3
	void mujintou_FoodP1(MenuEntry*);		// 好きな食べ物変更P1
	void mujintou_FoodP2(MenuEntry*);		// 好きな食べ物変更P2
	void mujintou_FoodP3(MenuEntry*);		// 好きな食べ物変更P3
	
	
	/*
    ** その他
    ********************/
	void akarusa_change(MenuEntry*);		// 村の明るさ変更
	void FastGameSpeed(MenuEntry*);			// ゲーム速度上昇
	void ChangeIslandServer(MenuEntry*);	// サーバー変更
	void FarCamera(MenuEntry*);				// 遠距離カメラ
	void ChangeFlowerTreeSize(MenuEntry*);	// 花や木のサイズ変更
	void CrazyScreen(MenuEntry*);			// 画面崩壊
	void MoveFurniture(MenuEntry*);			// 室内の家具動かす
	void ChangeWeather(MenuEntry*);			// 天気変更
	void frag_change(MenuEntry*);			// 駅の旗大きさ変更
	void KeyboardExtender(MenuEntry*);		// キーボード改行
	void MoveCamera(MenuEntry*);			// カメラ操作
	void ChatCopyPaste(MenuEntry*);			// チャットコピぺ
	void KanjiHenkan(MenuEntry*);			// 漢字変換
	void ViewAddress(MenuEntry*);			// アドレス監視
	void HexEditor(MenuEntry*);				// HEXエディタ
	void Sleep(MenuEntry*);
	
	
}






