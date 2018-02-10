#include "GIPI.h"
#include "arduino.h"
int BtNum = 0;
int BtPin[64];
int BtWork[64];
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

void GIPISetup(int revF, int revN, int revR) {

}

void GIPISetup(int revF, int revN, int revR, int baud) {

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
      a = (brake[1] - brake[0]) / 2;
      a = a + brake[0];
      if (brkal < a) {
        brcom(0);
        goto brout;
      }
    }
    else if (i < (brnum - 1)) {
      a = (brake[i + 1] - brake[i]) / 2;
      a = a + brake[i];
      b = (brake[i] - brake[i - 1]) / 2;
      b = b + brake[i - 1];
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
      a = (notch[0] - notch[1]) / 2;
      a = a + notch[1];
      if (masal > a) {
        nocom(0);
        goto out;
      }
    }
    else if (i < (nonum - 1)) {
      a = (notch[i - 1] - notch[i]) / 2;
      a = a + notch[i];
      b = (notch[i] - notch[i + 1]) / 2;
      b = b + notch[i + 1];
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

