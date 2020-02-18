/*For more information about esp now :-
 https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/network/esp_now.html

*/
#include <ESP8266WiFi.h>

extern "C" {
    #include <espnow.h>
}
// this is the MAC Address of the slave which receives the data
uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
#define WIFI_CHANNEL 4



// must match the slave struct
// struct that will be send to the peered device
struct __attribute__((packed)) 
DataStruct {
char text[32];
};
DataStruct Forward;

struct __attribute__((packed)) 
DataStruct2 {
char text[32];
};
DataStruct2 Backward;

struct __attribute__((packed)) 
DataStruct3 {
char text[32];
};
DataStruct3 Left;

struct __attribute__((packed)) 
DataStruct4 {
char text[32];
};
DataStruct4 Right;

struct __attribute__((packed)) // to keep bot stationary in idle condition
DataStruct5 {
char text[32];
};
DataStruct5 Hault;
//=======================================================================================

void setup() {
  pinMode(D1,INPUT);
  pinMode(D2,INPUT);
  pinMode(D5,INPUT);
  pinMode(D6,INPUT);
 
    Serial.begin(115200); Serial.println();
  
    WiFi.mode(WIFI_STA); // Station mode for esp-now controller
    WiFi.disconnect();
    Serial.printf("This mac: %s, ", WiFi.macAddress().c_str());
    Serial.printf("slave mac: %02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf(", channel: %i\n", WIFI_CHANNEL);
    if (esp_now_init() != 0) //Call esp_now_init() to initialize ESP-NOW
    {
    Serial.println("*** ESP_Now initialization failed");
    }
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_add_peer(mac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0); //Call esp_now_add_peer() to add the device to the paired device list 
    strcpy(Forward.text,"Forward");
    strcpy(Backward.text,"Backward");
    strcpy(Left.text,"Left");
    strcpy(Right.text,"Right");
    strcpy(Hault.text,"Hault");
    Serial.println("Setup finished");

}

//=======================================================================================

void loop() {
    sendData();

}

//============================================================================================

void sendData() {                                          
   uint8_t bs[sizeof(Hault)];
        memcpy(bs, &Hault, sizeof(Hault));
        esp_now_send(NULL, bs, sizeof(Hault)); //Call esp_now_send() to send ESP-NOW data
        Serial.println(Hault.text);
 
 
    if(digitalRead(D1) == HIGH){
       uint8_t bs[sizeof(Forward)];
        memcpy(bs, &Forward, sizeof(Forward));
        esp_now_send(NULL, bs, sizeof(Forward));
        Serial.println(Forward.text);

    }

       if(digitalRead(D2) == HIGH){
       uint8_t bs[sizeof(Backward)];
        memcpy(bs, &Backward, sizeof(Backward));
        esp_now_send(NULL, bs, sizeof(Backward));
        Serial.println(Backward.text);

    }

       if(digitalRead(D5) == HIGH){
       uint8_t bs[sizeof(Right)];
        memcpy(bs, &Right, sizeof(Right));
        esp_now_send(NULL, bs, sizeof(Right));
        Serial.println(Right.text);
      

    }

       if(digitalRead(D6) == HIGH){
       uint8_t bs[sizeof(Left)];
        memcpy(bs, &Left, sizeof(Left));
        esp_now_send(NULL, bs, sizeof(Left));
        Serial.println(Left.text);

    }

 
  
  delay(100);

}
