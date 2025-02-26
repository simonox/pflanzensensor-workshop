#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "DHTesp.h"
#include "credentials.h" // put your WIFI credentials in here

#define AOUT_PIN A0 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor

DHTesp dht;
WiFiServer server(80);

// Replace with your network credentials
const char* ssid = secrect_ssid;
const char* password = secret_password;

// Set web server port number to 80

// Variable to store the HTTP request
String header;



// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);
  dht.setup(D0, DHTesp::DHT11); // Connect DHT sensor to D0


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){

    // read humidity
  float humi  = dht.getHumidity();
  // read temperature in Celsius
  float tempC = dht.getTemperature();


  // read soil
  int soil = analogRead(AOUT_PIN); // read the analog value from sensor

  WiFiClient client = server.available();     // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println("</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Pflanzensensor</h1>");
            client.println("<img src='https://curious.bio/wp-content/uploads/2021/04/cropped-cropped-Curious_Community_Labs_Logo_fit.png' width=200><br />");
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p><b>Temperature:</b> ");
            client.println(tempC);
            client.println("&deg;C</p>");
            client.println("<p><b>Humidity:</b> ");
            client.println(humi);
            client.println(" %</p>");
            client.println("<p><b>Soil moisture value:</b> ");
            client.println(soil);
            client.println("</p>");
            client.println("<script>window.setTimeout(() => {window.location.href = window.location.href}, 10000)</script>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}