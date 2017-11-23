#include <user_config.h>
#include <SmingCore/SmingCore.h>

#include <Adafruit_NeoPixel/Adafruit_NeoPixel.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
	#define WIFI_SSID "ssiddd" // Put you SSID and Password here
	#define WIFI_PWD "insert?here "
#endif

void onReceive(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort); // Declaration


// UDP server
const uint16_t EchoPort = 6454;
UdpConnection udp(onReceive);


// Which pin on the Esp8266 is connected to the NeoPixels?
#define PIN           5 

// How many NeoPixels are attached to the Esp8266?
#define NUMPIXELS     8 

//Circular buffer
//frame:[led1, led2, led3], [led1, led2, led3]
const int ledbuffer_size = 20;
uint8_t r_buf [NUMPIXELS * ledbuffer_size] = {0};
uint8_t g_buf [NUMPIXELS * ledbuffer_size];
uint8_t b_buf [NUMPIXELS * ledbuffer_size];

uint8_t buffer_read_pos = 0;
uint8_t buffer_write_pos = 1;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//ARTNET########################
char ar_header[] = "Art-Net\0";
uint16_t OpCode;
uint8_t highByte;
uint8_t lowByte;
bool is_opcode_artpoll;
bool is_opcode_dmx;
uint8_t ar_data_start = 18;

//##############################

void onReceive(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort)
{
	debugf("UDP Sever callback from %s:%d, %d bytes", remoteIP.toString().c_str(), remotePort, size);

	// We implement string mode server for example
	Serial.print(">\t");

	if (size <= 18){
        debugf ("Invalid header received. Less than 18 bytes\n");
        return;
    }
        
	bool headerOK = true;
    is_opcode_dmx = false;
    is_opcode_artpoll = false;
    int num_of_channels = 24;
    //HEADER 0-7 bytes
    for (int i = 0; i <= 8; i++){
        if (data[i] != ar_header[i]){
            headerOK = false;
        }
    }
    //OpCode 8 and 9 bytes
    highByte = data[9];
    lowByte = data[8];
    OpCode = (highByte << 8) | lowByte;
	if (OpCode==0x5000) {
        is_opcode_dmx = true;
	}
	if (OpCode==0x2000) {
        is_opcode_artpoll = true;
        //Write IP address as an reply.
	}
    //DATA
    if (is_opcode_dmx){
        Serial.println("DMX");
        for (int i = 0; i < NUMPIXELS; i++){
            int data_pos = ar_data_start + (i * 3);
            r_buf[i + buffer_write_pos*NUMPIXELS] = data[data_pos];
            g_buf[i + buffer_write_pos*NUMPIXELS] = data[data_pos+1];
            b_buf[i + buffer_write_pos*NUMPIXELS] = data[data_pos+2];
        }
    }

    for (int ledi=0; ledi < NUMPIXELS; ledi++){
        int c_led = buffer_write_pos*NUMPIXELS+ledi;
        strip.setPixelColor(ledi, r_buf[c_led], g_buf[c_led], b_buf[c_led]);
    }
    strip.show();
    buffer_write_pos += 1;
    if (buffer_write_pos >= ledbuffer_size){
        buffer_write_pos = 0;
    }

    // Send echo to remote sender
	String text = String("echo: success");// + data;
	udp.sendStringTo(remoteIP, EchoPort, text);
}

void gotIP(IPAddress ip, IPAddress gateway, IPAddress netmask)
{
	//udp.listen(EchoPort);

	Serial.print("\r\n=== UDP SERVER STARTED ===");
	Serial.print(WifiStation.getIP().toString()); Serial.print(":"); Serial.println(EchoPort);
	Serial.print("=============================\r\n");

	//udp.connect(IPAddress(192, 168, 10, 38), 1234);
	//udp.sendString("Hello!");
}


// Will be called when WiFi station loses connection
void connect_Fail(String SSID, uint8_t ssid_len, uint8_t bssid[6], uint8_t reason)
{
	Serial.println("I'm NOT CONNECTED!");
}

void init()
{
    //Initialize buffers
    r_buf[0] = 100;
    g_buf[0] = 100;
    b_buf[0] = 100;

	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true);

	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiEvents.onStationDisconnect(connect_Fail);
	WifiEvents.onStationGotIP(gotIP);
	udp.listen(EchoPort);

	strip.begin();  //init port
}
