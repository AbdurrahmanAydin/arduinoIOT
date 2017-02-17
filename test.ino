#include <SPI.h>
#include <Ethernet.h>

// Ethernet shield için mac adresi veriyoruz eğer ethernet kartınızın üzerinde böyle bir adres yoksa kafanıza göre bi mac yazın
byte mac[] = {  
   0x90, 0xA2, 0xDA, 0x00, 0x6C, 0xFA 
};

// bilgisayarınızın ip adresi
IPAddress ip(192,168,1,29);

// Node.js ip adresi
IPAddress server(192,168,1,29);

int pin = 13;
int pinVal = 0;

// internet için istemci oluşturuyoruz.
EthernetClient client;

void setup() {
 
  Ethernet.begin(mac, ip);
  
  Serial.begin(9600);
  
  delay(1000);
  
  Serial.println("bağlanıyor...");
  
  if (client.connect(server, 3000)) {
    Serial.println("bağlandı");
  } 
  else {
    Serial.println("Bağlantı başarısız");
  }

  pinMode(pin, OUTPUT);
}

void loop()
{
  
  //serverimize bağlanabildikmi diye kontrol ediyoruz
  if (client.available()) {
    int c = client.read();
    Serial.print(c);

        if (c == 1) {
      pinVal = HIGH;
      client.print('1');
    } 
    else if (c == 0) {
      pinVal = LOW;
      client.print('0'); 
    }
    
    //ledimize değeri yazıyoruz
    digitalWrite(pin, pinVal);

  }

}

