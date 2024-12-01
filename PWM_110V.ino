// Arduino light brightness control (light dimmer) code
 
 
#define triac_gate   8    //Chân điều khiển
#define pot         A0    //Chân analog
#define sen         A1
#define Mode        A2
bool ZC = 0;   //Giá trị ban đầu của điều kiện bật đèn hay không
uint16_t alpha;   //
 
void setup(void) {
  Serial.begin(9600);
  pinMode(Mode, INPUT_PULLUP);
  pinMode(triac_gate, OUTPUT);    //thiết lập ngõ ra
  digitalWrite(triac_gate, LOW);    //Tắt đèn
  attachInterrupt(0, ZC_detect, CHANGE);       // Tạo ngắt ở chân D2(2), nếu chân D2(2) thay đổi thì tiếp tục xuất xung
}
 
void ZC_detect() {
  ZC = 1;  //Giá trị = 1 thì cho phép bắt đầu bật đèn
}
 
void loop() {
 
  if( ZC){
    if(alpha < 9500) {  //Nếu giá trị thấp hơn 9500 thfi chạy hàm trong
      delayMicroseconds(alpha);  //Delay từ 0->9500 micro giây
      digitalWrite(triac_gate, HIGH);  //Kích triac  
      delayMicroseconds(200);            //Delay 200 micro giây
      digitalWrite(triac_gate, LOW);     //Ngắt triac
    }
    ZC = 0;                             //Thoát chương trình
    if(digitalRead(Mode) == 1){
     //Điều khiển góc mở triac min = 0. Max = 9500
    alpha = ( 1023 - analogRead(pot) ) * 10;  //Ghi giá trị alpha = giá trị đọc được từ chân A0 * 10
    }
    if(digitalRead(Mode) == 0){
     //Điều khiển góc mở triac min = 0. Max = 9500
     Serial.println(analogRead(sen));
    alpha = map(analogRead(sen),10,975,0,9500);  //Độ sáng từ 200-1000 thì giá trị mởtriac từ 0-9500
    }
    if(alpha > 9500)   //Nếu alpha lớn hone 9500 
      alpha = 9500;    //Thfi alpha = 9500 
  }
}
