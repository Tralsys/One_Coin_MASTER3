//One Coin M@STER version 3.0.0
//Tech Otter(https://technotter.com)
//Tetsu Otter(https://twitter.com/tetsu_otter)
#include "GIPI.h"
const int rever = A0; //"A1"にレバーサー可変抵抗を接続したピンを入力してください。
const int mascon = A2; //"A2"にノッチ可変抵抗を接続したピンを入力してください。1ハンドルの場合は下と同じピンを指定してください。
const int brakevr = A2;//"A2"にブレーキ可変抵抗を接続したピンを入力してください。1ハンドルの場合は上と同じピンを指定してください。
const float levN = 530; //"500"のところに中立位置の時のレバーサー可変抵抗の出力値を入力してください。
const float levF = 880; //"750"のところに前進位置の時のレバーサー可変抵抗の出力値を入力してください。
const float levR = 180; //"250"のところに後退位置の時のレバーサー可変抵抗の出力値を入力してください。
const int brnum = 10; //制動段の数(非常ブレーキ含む)に1を足した数を入力してください。
const int nonum = 6; //力行段の数に1を足した数を入力してください。
const int btnum = 1; //ボタンの数を入力してください。最低でも1は必要です。0を入力するとエラーになります。
const int KeyNum = 2; //キーボードエミュレーションを行うボタンの数を入力してください。最低でも1は必要です。
const int brake[brnum] = {485, 545, 605, 665, 725, 785, 845, 905, 965, 1023}; //{}内に各段における出力値を "N(B0)の位置から順に" 整数で入力してください。
const int notch[nonum] = {485, 400, 300, 200, 100, 0}; //{}内に各段における出力値を "N(P0)の位置から順に" 整数で入力してください。
const int button[btnum] = {12}; //{}内にボタンを接続したピンの番号を入力してください。使用しない場合も適当でいいので、必ずなにかピン番号を入力してください。
const int btncord[btnum] = {0}; //{}内に、上で設定した各ボタンの果たす機能を入力してください。名称での指定も可能です。詳しくは本スケッチに同梱の説明書をご覧ください。
const int KeyPin[KeyNum]={12,12};//{}内に各キーボタンを接続したピン番号を入力してください。使用しない場合も適当でいいので、必ずなにかピン番号を入力してください。
const int KeyWorks[KeyNum] = {16,116}; //{}内に、上で設定した各キーボタンの果たす機能を入力してください。詳しくは本スケッチに同梱の説明書をご覧ください。


//ここから下は手を触れないでください。

//float btnhis[btnum];
void setup() {
  //for (int i = 0; i < btnum; i++) {
  //  btnhis[i] = 0;
  //}
  Serial.begin(9600);
  while (!Serial);
  
  Serial.print("TORN\r");
  nocom(1);
  nocom(0);
  brcom(6);
  ButtonSet(btnum, button, btncord);
}

void loop() {
  ave();
  reverser();
  //buttoncom();
  ButtonRead();
  masconhand();
}

