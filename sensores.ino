
struct RegistroClimatico {
  float temperatura;
  int humedad;
  int luz;
};

const int pinTemp = A0;      // Temp
const int pinHumedad = A1;   // Hum
const int pinLuz = A2;       // Luz

void setup() {
  Serial.begin(9600);// baudios o pulsos
  Serial.println("Iniciando captura de datos climáticos...");
  Serial.println("------------------------------------------");
}

void loop() {
  RegistroClimatico medicion;
  
  int lecturaTemp = analogRead(pinTemp);
  
  float voltaje = lecturaTemp * (5.0 / 1023.0);
  
  medicion.temperatura = (voltaje - 0.5) * 100.0;// documentacion tmp36
  
  int lecturaHum = analogRead(pinHumedad);
  // el sensor hum de 0 (seco) a ~876 (sumergido) mapeo 1-100.
  medicion.humedad = map(lecturaHum, 0, 876, 0, 100); 
  
  if (medicion.humedad > 100) medicion.humedad = 100; // Tope máximo

  int lecturaLuz = analogRead(pinLuz);
  // sensor luz de 0 a 1023 a un porcentaje de 0 a 100%
  medicion.luz = map(lecturaLuz, 0, 1023, 0, 100);

  Serial.print("Temperatura: ");
  Serial.print(medicion.temperatura);
  Serial.print(" C  |  ");
  
  Serial.print("Humedad: ");
  Serial.print(medicion.humedad);
  Serial.print(" %  |  ");
  
  Serial.print("Luz: ");
  Serial.print(medicion.luz);
  Serial.println(" %");

  delay(2000); 
}