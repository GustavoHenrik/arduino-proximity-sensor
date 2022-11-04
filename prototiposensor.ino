/******************************************************************************/
/*          Projeto: Protótipo Sensor para Estacionamento em Garagem          */
/*                     PontoCanal - Ponto Makers                              */
/******************************************************************************/

//Configuração de Distancia Mínima em centimetros
const int distancia_amarela = 20; 
const int distancia_vermelha = 10;

//Configurações de Portas do Arduino

//Sensor
const int TRIG = 3;
const int ECHO = 2;

//Demais componentes
const int ledYellow = 6;
const int ledGreen = 7;
const int ledRed = 8;
const int buzzer = 9;


// Variaveis para funcionamento do Buzzer
float seno;
int frequencia;

void setup() {
  Serial.begin(9600);
  
  // Configurações do Sensor
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  
  // Configurações do LED
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode (ledYellow, OUTPUT);

  //Configurações do Buzzer
  pinMode(buzzer, OUTPUT); 
  
}

void loop() {
  int distancia = sensor_morcego(TRIG,ECHO);

      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
      Serial.print(distancia);
      Serial.println("cm");
    
    if(distancia > distancia_amarela){
      Serial.print("Livre : ");
      digitalWrite(ledGreen, HIGH); //ledGreen
      noTone(buzzer);

    }
    else if(distancia >= distancia_vermelha){
      Serial.print("Atencao: ");
      digitalWrite(ledYellow, HIGH); //ledYellow
      noTone(buzzer);
    }
    else{
      Serial.print("Limite: ");
      digitalWrite(ledRed, HIGH); //ledRed
      tocaBuzzer();
    }
  delay(100);
  
}

int sensor_morcego(int pinotrig,int pinoecho){
  digitalWrite(pinotrig,LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig,LOW);

  return pulseIn(pinoecho,HIGH)/58;
}

//Função para execução do Alarme Sonoro
void tocaBuzzer(){
 for(int x=0;x<180;x++){
  seno=(sin(x*3.1416/180));
  frequencia = 200+(int(seno*1000));
  tone(buzzer,frequencia);
  delay(2);
}

}