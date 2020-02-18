#include <ESP8266WiFi.h>

extern "C" {
    #include <espnow.h>
     #include <user_interface.h>
}
uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};

//==============

void initVariant() {
  WiFi.mode(WIFI_AP);
  wifi_set_macaddr(SOFTAP_IF, &mac[0]);
}

//==============
#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
#define WIFI_CHANNEL 4
int speedCar = 800; // value can be 0-1023

// must match the controller struct
struct __attribute__((packed)) 
DataStruct {
    char text[32];
   
};

DataStruct myData;

//==================================================================================

void setup() {
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 
//==================================================================================
    Serial.begin(115200); Serial.println();
    
    Serial.print("This node AP mac: "); Serial.println(WiFi.softAPmacAddress());
    Serial.print("This node STA mac: "); Serial.println(WiFi.macAddress());

    if (esp_now_init()!=0) {
        Serial.println("*** ESP_Now init failed");
        while(true) {};
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(receiveCallBackFunction);  //Call esp_now_register_recv_cb to register receiving callback function
   Serial.println("End of setup - waiting for messages");
}

//=======================================================================================

void loop() {
 

}

//=======================================================================================

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
  void Hault(){
     digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, 0);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, 0);
    
  }


void receiveCallBackFunction(uint8_t *senderMac, uint8_t *incomingData, uint8_t len) {
    memcpy(&myData, incomingData, sizeof(myData));
    String DataCompare = String(myData.text);
    Serial.print(DataCompare);
    
   
   
    if(DataCompare == "Forward"){
    goAhead();
    }    
     if(DataCompare == "Backward"){
    goBack();
    }
    if(DataCompare == "Right"){
    goRight();
    }

    if(DataCompare == "Left"){
    goLeft();
    }
    if(DataCompare == "Hault"){
    Hault();
    }
    
    

    
    delay(10);


    
}
