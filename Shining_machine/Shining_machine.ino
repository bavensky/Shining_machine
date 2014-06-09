  /*******************************************************************************
   * Project  : Shining machine                                                  *
   * Compiler : Arduino 1.5.5-r2                                                 *
   * Board    : Arduino UNO                                                      *
   * Shield   : -                                                                *
   * Module   : -                                                                *
   * Material : LCD 16x2                                                         *
   *          : 2 button and 2 l                                                 *
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
   * Date     : 07/06/2014 [dd/mm/yyyy]                                          *
   *******************************************************************************/
  /*
  Tharit : มีโปรเจ็ค ให้เขียน กำลัง จะขอเงิน เป็นเครื่อง ฉายแสงใส่ สารอุดฟัน

  มีจอ LCD 1 อัน มี ปุ่มกด 2 ปุ่ม ปุ่มเลื่ิอนเมนู ปุ่ม โอเค
  แสงที่ว่า คือ แสง  LED สีฟ้า ครูมีโมดูล พร้อมชุดไดรฟ์
  
  เมนูที่ 1 คือ ให้ LED ยิงแสงออกมา ครั้งละ 5 วินาที 15 ครั้ง
  เมนูที่ 2 คือ LED ยิงแสงออกมาตลอด แต่ค่อย ๆ สว่างขึ้นจนเต็มที่ ใช้เวลาประมาณ 18 วินาที
  เมนูที่ 3 คือ กด โอเคกำ ยิงกำ
   */
   
   #include <LiquidCrystal.h>

   #define RS  12
   #define EN  11
   #define D4  10
   #define D5  8
   #define D6  9
   #define D7  7
   
   #define BUTTON1  4
   #define BUTTON2  2
   
   #define LED1  6
   #define LED2  3
   
   #define DEBOUNCE 200
   #define DELAY 2000
   
   LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
   
   String message[] = { "Shining Machine ",
                        "   Start Menu   ",
                        "     Menu1      ",
                        "     Menu2      ",
                        "     Menu3      ",
                        "   Exit Menu    "};
                       
   int button1=0, button2=0; 
   int a=0, b=0, c=0, d=0;
   
   void setup()
   {
     pinMode(LED1, OUTPUT);
     pinMode(LED2, OUTPUT);
     
     Serial.begin(9600);
     lcd.begin(16, 2);
     
     lcd.home();
     lcd.print(message[0]);     
   }
   
   void loop()
   {
     lcd.setCursor(0, 1);
     lcd.print(message[1]);
     
     button1 = digitalRead(BUTTON1);
     if(button1==0)
     {
       delay(DEBOUNCE);
       a=1;
     }
     
     while(a==1)
     {
       lcd.setCursor(0, 1);
       lcd.print(message[2]);
       
       button1 = digitalRead(BUTTON1);
       button2 = digitalRead(BUTTON2);
       if(button1 == 0)
       {
         delay(DEBOUNCE);
         a=2;
       }
       if(button2 == 0)
       {
         delay(DEBOUNCE);
         for(int lo=0; lo<15; lo++)
         {
           digitalWrite(LED1, HIGH);
           delay(1000);  //  ติด 5 วินาที
           digitalWrite(LED1, LOW);
           delay(200);
         }
       } 
     }
     
     while(a==2)
     {
       lcd.setCursor(0,1);
       lcd.print(message[3]);
       
       button1 = digitalRead(BUTTON1);
       button2 = digitalRead(BUTTON2);
       if(button1 == 0)
       {
         delay(DEBOUNCE);
         analogWrite(LED1, LOW);
         a=3;
       }
       if(button2 == 0)
       {
         delay(DEBOUNCE);
         for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5)
         { 
           analogWrite(LED1, fadeValue);        
           delay(300);  
         }  
       }
     }
     
     while(a==3)
     {
       lcd.setCursor(0,1);
       lcd.print(message[4]);
       button1 = digitalRead(BUTTON1);
       button2 = digitalRead(BUTTON2);
       if(button1 == 0)
       {
         delay(DEBOUNCE);
         lcd.setCursor(0, 1);
         lcd.print(message[5]);
         delay(1000);
         a=0;
       }
       if(button2 == 0)
       {
         digitalWrite(LED2, HIGH);
       }
       if(button2 == 1)
       {
         digitalWrite(LED2, LOW);
       }
     } 
   }
