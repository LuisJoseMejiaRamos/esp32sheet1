#include "WiFi.h" // Libreria para conectarse al internet con el esp32 y esp8266
#include "HTTPClient.h" // Libreria para poner en cliente al esp32

int led = 12; //Led indicador
const char* ssid = "INFINITUM3658"; // Creamos una variable para el nombre de la red
const char* password = "Hi3kh33FCb"; // Creamos una variable para la contraseña de la red
HTTPClient http; // Creamos la variable de http para poder manejarlo sus metodos
int httpResponseCode; // Codigo de respuesta http
String respuesta; // Respuesta de las paginas
String Dato1 = "777", Dato2 = "444"; //Informacion para enviar
String URL_Implementacion = "https://script.google.com/macros/s/AKfycbwCeoMrBEjH25XXGH9aK7jpqph3GVV3ZipsJgShrYynPKAc3u9ALrpisTdgsNCLb0okkA/exec";
void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  WiFi.begin(ssid, password); //ponemos el nombre de la red y su contraseña 
  Serial.print("Red: ");
  Serial.println(ssid);
  Serial.print("Contraseña: ");
  Serial.println(password);
  Serial.println("Conectando al wifi");
  while (WiFi.status() != WL_CONNECTED) { //se rompera el ciclo hasta se conecte el esp32 al wifi
    digitalWrite(led, HIGH); //encendemos el led de wifi porque aun no se conecta el esp32 al intener 
    Serial.print(".");
    delay(200);
    digitalWrite(led, LOW); //encendemos el led de wifi porque aun no se conecta el esp32 al intener 
    delay(200);
  }
  digitalWrite(led, HIGH);
  Serial.println("\nConexion hecha"); 
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    http.begin(URL_Implementacion+"?value1="+Dato1+"&value2="+Dato2);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    httpResponseCode = http.GET();
    respuesta= "...";
  if(httpResponseCode > 0){
    Serial.print("Codigo de respuesta HTTP: ");
    Serial.println(httpResponseCode);
    respuesta = http.getString();
    Serial.println(respuesta);
    
  }
  else{
    Serial.print("Error: ");
    Serial.println(httpResponseCode);    
  }
  http.end();
}

