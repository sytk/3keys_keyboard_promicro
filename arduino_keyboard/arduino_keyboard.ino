#include <Keyboard.h> // キーボードライブラリの読み込み
#define N 6
#define OVERLAP_TIME 20

int SW[N]= {2,3,4};
char KEY_MAP[64] = {0, KEY_RETURN, KEY_F13, KEY_F5};

void setup() {
  Keyboard.begin();
  for(int i = 0; i < N; i++){
    pinMode(SW[i], INPUT_PULLUP);
  }
}

int pre_num = 0;
void loop() {
    int num = getSwitchState();
    if(num != 0 && pre_num == 0){
        if(KEY_MAP[num] < 128){
          Keyboard.print(KEY_MAP[num]);
        }
        else
          Keyboard.write(KEY_MAP[num]);
    }
    pre_num = num;
    delay(10);
}

int getSwitchState(){
  int num = 0;
  static bool first_flag = true;
  
  for(int i = 0; i < N; i++){
    if(digitalRead(SW[i]) == LOW){ 
       num += i+1; 
    }
  }
  
  if(num != 0 && first_flag){
    first_flag = false;
    unsigned long start_time = millis();
    while(true){
      num = getSwitchState();
      if(millis() - start_time > OVERLAP_TIME) break;
    }
    first_flag = true;
  }
  
  return num;
}
