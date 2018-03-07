#include "GIPI.h"
#include "arduino.h"
int BtNum = 0;
int BtPin[16];
int BtWork[16];

float sikiFN = 0;
float sikiNR = 0;

float where = 0;
float rev = 0;
int wh = 0;
int wh2 = 0;

float reval = 0;
float masal = 0;
float brkal = 0;
float btnari = 0;

int brnum = 0;//制動段数
int nonum = 0;//力行段数
int yonum = 0; //抑速段数

int rever = 0; //Pin Num
int mascon = 0; //Pin Num
int brakevr = 0; //Pin Num
int yokusp = 0; //Pin Num

int brakes[32];//制動VR値
int notchs[32];//力行VR値
int yokus[32];//抑速VR値


void GIPISetup(int levF, int levN, int levR) {
  //revX = Xsiki
  //
  //BaudRate Default 9600
  Serial.begin(9600);
  while (!Serial);
  sikiFN = levN + (levF - levN) / 2;//levN>levFでも対応。
  sikiNR = levN - (levN - levR) / 2;
}

void GIPISetup(int levF, int levN, int levR, int baud) {
  //levX::レバーサーXの可変抵抗値。
  Serial.begin(baud);
  while (!Serial);
  sikiFN = levN + (levF - levN) / 2;
  sikiNR = levN - (levN - levR) / 2;
}
void RevPinSet(int Rev, int Rik, int Sei) {
  //レバーサー、力行ハンドル、制動ハンドル  のピン番号
  rever = Rev; //Pin Num
  mascon = Rik; //Pin Num
  brakevr = Sei; //Pin Num
}
void RevPinSet(int Rev, int Rik, int Sei, int Yok) {
  //レバーサー、力行ハンドル、制動ハンドル、抑速ハンドル
  rever = Rev; //Pin Num
  mascon = Rik; //Pin Num
  brakevr = Sei; //Pin Num
  yokusp = Yok; //Pin Num

}
void RevPinValue(int Rik[], int Sei[]) {
  //各段AnalogRead値(力行, 制動)
  if (brnum > 0) {
    for (int i = 0; i < brnum; i++) {
      brakes[i] = Sei[i]; //制動VR値
    }
  } else if (brnum == 0) {
    Serial.println("Error! You must put 'RevHowMany()' before 'RevPinValue()'!");
  } else {
    Serial.println("Error! You must put natual number in 'RevHowMany()'!");
  }
  if (nonum > 0) {
    for (int i = 0; i < nonum; i++) {
      notchs[i] = Rik[i]; //力行VR値
    }
  } else if (nonum == 0) {
    Serial.println("Error! You must put 'RevHowMany()' before 'RevPinValue()'!");
  } else {
    Serial.println("Error! You must put natual number in 'RevHowMany()'!");
  }
}
void RevPinValue(int Rik[], int Sei[], int Yok[]) {
  if (brnum > 0) {
    for (int i = 0; i < brnum; i++) {
      brakes[i] = Sei[i]; //制動VR値
    }
  } else if (brnum == 0) {
    Serial.println("Error! You must put 'RevHowMany()' before 'RevPinValue()'!");
  } else {
    Serial.println("Error! You must put natual number in 'RevHowMany()'!");
  }

  if (nonum > 0) {
    for (int i = 0; i < nonum; i++) {
      notchs[i] = Rik[i]; //力行VR値
    }
  } else if (nonum == 0) {
    Serial.println("Error! You must put 'RevHowMany()' before 'RevPinValue()'!");
  } else {
    Serial.println("Error! You must put natual number in 'RevHowMany()'!");
  }
  if (yonum > 0) {
    for (int i = 0; i < yonum; i++) {
      yokus[i] = Yok[i]; //抑速VR値
    }
  } else if (yonum == 0) {
    Serial.println("Error! You must put 'RevHowMany()' before 'RevPinValue()'!");
  } else {
    Serial.println("Error! You must put natual number in 'RevHowMany()'!");
  }

}

void RevHowMany(int Mas, int Bre) {
  //各段数
  if (Mas > 0 && Bre > 0) {
    brnum = Bre;
    nonum = Mas;
  } else {
    Serial.println("Error! You must put natual number in 'RevHowMany()'!");
  }
}

void RevHowMany(int Mas, int Bre, int Yok) {
  if (Mas > 0 && Bre > 0 && Yok > 0) {
    brnum = Bre;
    nonum = Mas;
    yonum = Yok;
  } else {
    Serial.println("Error! You must put natual number in 'RevHowMany()'!");
  }

}

void ButtonSet(int HowMany, int PinNum[], int BtnWork[])
{
  //個数、ピン番号、役割
  BtNum = HowMany;
  for (int i = 0; i < HowMany; i++) {
    BtPin[i] = PinNum[i];
    BtWork[i] = BtnWork[i];
    pinMode(BtPin[i], INPUT_PULLUP);
  }
}

bool bthis[64] = {1};

void ButtonRead()
{
  //全部Readする。仕事が0以下の場合はスルー
  for (int i = 0; i < BtNum; i++) {
    int dr = digitalRead(BtPin[i]);
    if (dr != bthis[i] && BtWork[i] > 0) {
      if (dr == LOW) {
        bthis[i] = dr;
        Serial.print("TOK");
        Serial.print(BtWork[i]);
        Serial.print("D\r");
      } else {
        bthis[i] = dr;
        Serial.print("TOK");
        Serial.print(BtWork[i]);
        Serial.print("U\r");
      }
    }
  }
}
void ButtonRead(int i) {
  //指定された番号だけReadする
  int dr = digitalRead(BtPin[i]);
  if (dr != bthis[i] && BtWork[i] > 0) {
    if (dr == LOW) {
      bthis[i] = dr;
      Serial.print("TOK");
      Serial.print(BtWork[i]);
      Serial.print("D\r");
    } else {
      bthis[i] = dr;
      Serial.print("TOK");
      Serial.print(BtWork[i]);
      Serial.print("U\r");
    }
  }
}

void ButtonRead(int i, int ThisBtWork) {
  //ピン番号、役割
  //Historyにかかわらず送信するため利用時はino側での対策推奨
  if (digitalRead(i) == LOW) {
    Serial.print("TOK");
    Serial.print(ThisBtWork);
    Serial.print("D\r");
  } else {
    Serial.print("TOK");
    Serial.print(ThisBtWork);
    Serial.print("U\r");
  }
}

void masconhand() {
  //masal
  float a = 0;
  float b = 0;

  //brakecommand
  for (int i = 0; i <= brnum; i++) {
    if (i == 0) {
      a = (brakes[1] - brakes[0]) / 2;
      a = a + brakes[0];
      if (brkal < a) {
        brcom(0);
        goto brout;
      }
    }
    else if (i < (brnum - 1)) {
      a = (brakes[i + 1] - brakes[i]) / 2;
      a = a + brakes[i];
      b = (brakes[i] - brakes[i - 1]) / 2;
      b = b + brakes[i - 1];
      if (brkal > b && brkal < a) {
        //int s = 50 + i;
        //mascom(s);
        brcom(i);
        goto brout;
      }
    }
    else {
      int s = brnum - 1;
      brcom(s);
      goto brout;
    }
  }
brout:

  //notchcommand
  for (int i = 0; i <= nonum; i++) {
    if (i == 0) {
      a = (notchs[0] - notchs[1]) / 2;
      a = a + notchs[1];
      if (masal > a) {
        nocom(0);
        goto out;
      }
    }
    else if (i < (nonum - 1)) {
      a = (notchs[i - 1] - notchs[i]) / 2;
      a = a + notchs[i];
      b = (notchs[i] - notchs[i + 1]) / 2;
      b = b + notchs[i + 1];
      if (masal > b && masal < a) {
        nocom(i);
        goto out;
      }
    }
    else {
      int s = nonum - 1;
      nocom(s);
      goto out;
    }
  }
out:
  delay(5);
}
void brcom(int command) {
  if (wh != command) {
    Serial.print("TOB");
    Serial.print(command);
    Serial.print("\r");
    wh = command;
  }
}
void nocom(int command) {
  if (wh2 != command) {
    Serial.print("TOP");
    Serial.print(command);
    Serial.print("\r");
    wh2 = command;
  }

}
void reverser() {
  if (reval > sikiFN && rev != 2) {
    Serial.print("TORF\r");
    rev = 2;
  } else if (reval < sikiNR && rev != 1) {
    Serial.print("TORB\r");
    rev = 1;
  } else if (reval > sikiNR && reval < sikiFN && rev != 0) {
    Serial.print("TORN\r");
    rev = 0;
  }
}
void ave() {
  reval = 0;
  masal = 0;
  brkal = 0;
  for (int i = 0; i < 100; i++) {
    reval = reval + analogRead(rever);
    masal = masal + analogRead(mascon);
    brkal = brkal + analogRead(brakevr);
  }
  reval = reval / 100;
  masal = masal / 100;
  brkal = brkal / 100;
}

