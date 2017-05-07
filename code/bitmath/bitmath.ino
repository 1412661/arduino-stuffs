//Khai báo sử dụng các chân từ 2-9 để điều khiển led
int led[] = {
  2,3,4,5,6,7,8,9}; 

//Khai báo số lượng led sử dụng
int nbit = 8;

//Khai báo biến A (sẽ được dùng cho các ví dụ phía dưới)
int A;

void setup() {

  for(int i = 0; i<=nbit-1; i++) {
    //Khai báo việc sử dụng các chân từ 2-9 (led[0] - led[7]) trên Arduino
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  //Hiệu ứng 1
  Serial.println("Hieu ung 1");
  turn(0);      //viết trong hệ nhị phân là turn(0B00000000);
  delay(500);
  turn(255);    //viết trong hệ nhị phân là turn(0B11111111);
  delay(500);
  turn(0);     
  delay(500);
  turn(255);    
  delay(500);
  ///////////////////////////////////////////////////////////

  //Mỗi hiệu ứng cách nhau 3 giây
  turn(0);    //tắt hết đèn led trong lúc chờ chuyển sang hiệu ứng khác
  delay(3000);

  //Hiệu ứng 2
  Serial.println("Hieu ung 2");
  A = 0B10101010; //Khởi tạo trạng thái ban đầu của các đèn led
  //Bật đèn và đảo trạng thái bật - tắt cho chúng
  turn(A);
  delay(1000);
  turn(~A);
  delay(1000);
  turn(A);
  delay(1000);
  turn(~A);
  delay(1000);


  turn(0);
  delay(2000);

  A = 0B11000101;  //Khởi tại trạng khác của các led
  //Bật đèn và đảo trạng thái bật - tắt cho chúng
  turn(A);
  delay(1000);
  turn(~A);
  delay(1000);
  turn(A);
  delay(1000);
  turn(~A);
  delay(1000);
  ///////////////////////////////////////////////////////

  turn(0);
  delay(3000);

  //Hiệu ứng 3
  Serial.println("Hieu ung 3");
  for (int i = 0; i<=7; i++) {
    turn(1 << i); //dịch bit 1 lần lượt đi từ vị trí đầu tiên (vị trí i=0) đến vị trí cuối cùng (vị trí i=7) trong chuỗi 8 bit
    delay(300); 
  }
  ///////////////////////////////////////////////////////

  turn(0);
  delay(3000);

  //Hiệu ứng 4
  A = 0;
  Serial.println("Hieu ung 4");
  for (int i = 0; i<= 7;i++) {
    A = A | (1 << i); //Vận dụng (1 << i) từ hiệu ứng 3
    /*
   Trạng thái của A khi duyệt từ bit 0 đến bit 7 là
     0B00000001;
     0B00000011;
     0B00000111;
     0B00001111;
     0B00011111;
     0B00111111;
     0B01111111;
     0B11111111;
     */
    turn(A);
    delay(300);
  }
  /////////////////////////////////////////////

  turn(0);
  delay(3000);

  //Hiệu ứng 5
  //blah blah blah
  
}

void turn(int bits) {
  for (int i=0; i<=7;i++) {
    digitalWrite(led[i], bitRead(bits,i));
    //Hàm bitRead(bits,i) trả về trạng thái của bit thứ i trong bits
    //Hàm digitalWrite(led,state) sẽ cho điện áp ở chân led là 5V nếu state = 1 và ngược lại
  }
}






