# 目次

- [目次](#目次)
- [開発環境](#開発環境)
- [ツール](#ツール)
- [言語](#言語)
- [各プロジェクト](#各プロジェクト)
    - [ConsoleOthello](#consoleothello)
    - [VisualOthello](#visualothello)
	- [Replay](#Replay)
- [新しいAIクラスを作る](#新しいaiクラスを作る)
- [ConsoleOthelloプロジェクトで実行するには](#consoleothelloプロジェクトで実行するには)
- [ConsoleOthelloプロジェクトで AI VS 人をする方法](#consoleothelloプロジェクトで-ai-vs-人をする方法)
- [保存したリプレイを再生する方法](#保存したリプレイを再生する方法)
- [リプレイ保存先ファイルの変更](#リプレイ保存先ファイルの変更)
- [プログラム内で使える列挙体、構造体](#プログラム内で使える列挙体構造体)
     - [BoardStatus列挙体](#boardstatus列挙体)
     - [GameStatus列挙体](#gamestatus列挙体)
	 - [Coordinate構造体](#coordinate構造体)
- [Playerクラスの関数](#playerクラスの関数)
- [各クラスの関係](#各クラスの関係)

# 開発環境
## ツール
- Visual Studio 2019
- [Siv3D(4.3.0)](https://siv3d.github.io/ja-jp/tutorial/basic/)

## 言語
- C++

# 各プロジェクト
各プロジェクトは「スタートアッププロジェクトに設定する」をしてから実行する
## ConsoleOthello
- 開発者 VS AI が出来るデバッグ用プロジェクト
- 開発者 VS 開発者も出来る
- AI VS AI も出来る
- これらはプロジェクト内の`Main.cpp`を変更する事で変更できる
## VisualOthello
- AI VS AI 用プロジェクト
## Replay
- ConsoleOthelloプロジェクトとVisualOthelloプロジェクトで行われた試合のリプレイを再生するためのプロジェクト
- リプレイを保存する機能はConsoleOthelloプロジェクトとVisualOthelloプロジェクトにすでに存在している

# 新しいAIクラスを作る
1. ソリューションエクスプローラーのVisualOthello上で右クリック
1. 追加 > 新しい項目 でC++クラスを選択し、名前を自分のAI名にして追加を押す
1. 次の画面で基底クラスにPlayerと書き、OKを押す

1. ヘッダーファイルをこのような状態にする(MaxAIクラスの例、MaxAI.h)
	```cpp
	#pragma once
	#include "Player.h"
	class MaxAI : public Player
	{
	public:
		MaxAI();
		Coordinate calc(std::vector<std::vector<BoardStatus>> board);
	};
	```

1. C++ファイルをこのような状態にする(MaxAIクラスの例、MaxAI.cpp)

	- 返り値がCoordinate構造体のcalc関数内にプログラムを書き込むことでAIの脳を作ります
	```cpp
	#include "MaxAI.h"

	MaxAI::MaxAI(std::string name) : Player::Player(name)
	{
	}

	Coordinate MaxAI::calc(std::vector<std::vector<BoardStatus>> board)
	{
	}
	```

1. 最も沢山裏返すことが出来るマスにコマを置くAIを作ってみる
	- MaxAIクラスのcalc関数をこういう風にするだけ。簡単ですね
	```cpp
	Coordinate MaxAI::calc(std::vector<std::vector<BoardStatus>> board)
	{
		int max = 0;
		Coordinate max_coordinate;

		for (int y = 1; y <= 8; y++)
		{
			for (int x = 1; x <= 8; x++)
			{
				// 置けるなら
				if (Player::can_put(Coordinate{ x, y }, player_num, board))
				{
					// 座標(x, y)に置いたときに裏返せるコマの数
					int now = Player::can_get_num(Coordinate{ x, y }, this->player_num, board);
					// 現在のmaxよりも多ければ
					if (now > max)
					{
						// maxを更新する
						max = now;
						// maxの座標を更新する
						max_coordinate = Coordinate{ x, y };
					}
				}
			}
		}

		return max_coordinate;
	}
	```

1. main関数(Main.cpp)を書き換える
	
	VisualOthello内のmain関数を書き換える。
	- 18または19行目の宣言を以下のようにする
	```cpp
	MaxAI player2(std::string("Max AI"));
	```
	これは
	```cpp
	クラス名 player2(std::string("AIの名前"));
	```
	の形式で書く。

	- クラスのヘッダーをインクルードする
	```cpp
	#include "Max.h"
	```

1. 実行してみる
	1. VisualOthelloプロジェクトをスタートアッププロジェクトに設定する
	1. 実行する(Ctrl + F5)


# ConsoleOthelloプロジェクトで実行するには
1. main関数を変更する
	- ConsoleOthelloプロジェクト内のmain関数をVisualOthelloのmain関数と同様に変更する

1. ConsoleOthelloプロジェクトにクラスを追加する
	1. ConsoleOthelloのソースファイル上で右クリックする
	1. 追加 > 既存の項目 をクリックする
	1. VisualOthelloプロジェクトにあるMax.cppを選択し、追加を押す

	1. ConsoleOthelloのヘッダーファイル上で右クリックする
	1. 追加 > 既存の項目 をクリックする
	1. VisualOthelloプロジェクトにあるMax.hを選択し、追加を押す

1. 実行する
	1. ConsoleOthelloをスタートアッププロジェクトに設定する
	1. 実行する(Ctrl + F5)

# ConsoleOthelloプロジェクトで AI VS 人をする方法
1. main関数を変更する
	- main関数内のplayer1またはplayer2の宣言、初期化を以下のように書き換える。(player2を書き換える例)
	```cpp
	PersonPlayer player2(std::string("Name"));
	```

1. 実行する
	1. ConsoleOthelloをスタートアッププロジェクトに設定する
	1. 実行する(Ctrl + F5)

# 保存したリプレイを再生する方法
1. MainReplay.cpp(Replayプロジェクト)を書き換える
	MainRepaly.cppの14行目を変更する
	```cpp
	Replay replay("D:/replay.txt");
	```
	上のコードは
	```cpp
	Replay replay("リプレイが保存されているファイル名");
	```
	の形式で書かれている

	ここで書くリプレイが保存されているファイル名は実行より前に保存されている必要がある
1. 実行する
	1. Replayプロジェクトをスタートアッププロジェクトに設定する
	1. 実行する(Ctrl + F5)

# リプレイ保存先ファイルの変更
- MainVisual.cpp(VisualOthelloプロジェクト)またはMainConsole.cpp(ConsoleOthelloプロジェクト)を書き換えることでリプレイ保存ファイルを変更できる
- 保存先はテキストファイルがよい(拡張子：.txt)

- MainVisual.cppの25行目を変更する
```cpp
Replay replay("D:/replay.txt");
```
上のコードは
```cpp
Replay replay("リプレイ保存先ファイル名");
```
の形式で書かれている

ここで書くリプレイ保存先ファイル名は存在するファイルである必要はない(試合開始と同時にファイルが生成される)

# プログラム内で使える列挙体、構造体
- 宣言はType.hにある。
## BoardStatus列挙体
- calc関数に引数として渡されるboardは10x10のstd::vectorで出来ている
- boardの外側1行と1列は`WALL`で埋められている
``` cpp
enum BoardStatus
{
	Player1,
	Player2,
	NONE,
	WALL
};
```
|名前|意味|
|:-:|:-:|
|Player1|白いコマが有るマスを表す。Console OthelloではOで表示される。|
|Player2|黒いコマが有るマスを表す。Console OthelloではXで表示される。|
|NONE|何も置いていないマスを表す。|
|WALL|board外側を囲む|

## GameStatus列挙体
- Console Othelloでのみ使われている。
```cpp
enum GameStatus
{
	SET,
	CANNOT_SET,
	PASS
};
```

## Coordinate構造体
- 座標を表す構造体。
```cpp
struct Coordinate
{
	int x;
	int y;
};
```

# Playerクラスの関数
- 上記のように作れるAIのクラスはPlayerクラス(抽象クラス)を継承している。
- そのため、AIのクラスの関数内ではPlayerクラスの持つ関数を使用することが出来る。以下に示す。
- 実装はVisualOthello内のPlayer.cppでいることが出来る

|プロトタイプ宣言|説明|
|:-:|:-:|
|`Player(std::string name);`|Playerクラスのコンストラクタ。使わない|
|`Coordinate calc(std::vector<std::vector<BoardStatus>> board);`|AIのクラスでのcalc関数でオーバーライドされる。使わない。|
|`void set_player_num(BoardStatus player_num);`|使用禁止|
|`bool is_inside(Coordinate coordinate);`|coordinateのさす座標が盤面内ならtrue、盤面外ならfalseを返す|
|`bool can_put(Coordinate coordinate, BoardStatus player, std::vector<std::vector<BoardStatus>> board);`|board内の座標coordinateにplayerが置けるならtrue、置けないならfalseを返す|
|`BoardStatus get_enemy(BoardStatus player);`|playerの敵AIのBoardStatusを返す|
|`std::string get_name();`|AIの名前を返す。使わない|
|`int can_get_num(Coordinate coordinate, BoardStatus player, std::vector<std::vector<BoardStatus>> board);`|board内の座標coordinateにplayerのコマを置いたときに裏返すことのできるコマの数を返す|

# 各クラスの関係
|クラス|Visual Othello|Console Othello|内容|親クラス|
|:-:|:-:|:-:|:-:|:-:|
|Gameクラス|GameVisual.h / GameVisual.cpp|GameConsole.h / GameConsole.cpp|オセロの試合を制御する|なし|
|Playerクラス|Player.h / Player.cpp|Player.h / Player.cpp|AIのクラス。各AIのクラスはPlayerクラスを継承して作られる|なし|
|PersonPlayerクラス|PersonPlayer.h / PersonPlayer.cpp|PersonPlayer.h / PersonPlayer.cpp|人がプレーするためのクラス|Playerクラス|
|RandomAIクラス|RandomAI.h / RandomAI.cpp|RandomAI.h / RandomAI.cpp|左上から走査して置ける場所を見つけたら置けるAI|Playerクラス|
|MaxAIクラス|MaxAI.h / Max.cpp|MaxAI.h / Max.cpp|置けるマスの中で一番沢山裏返せるマスに置くAI|Playerクラス|
||Type.h|Type.h|列挙体、構造体が定義されている|なし|