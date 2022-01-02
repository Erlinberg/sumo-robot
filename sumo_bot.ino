#include <QTRSensors.h>

#define motor_r_e 3
#define motor_r_in1 12
#define motor_r_in2 10

#define motor_l_e 6
#define motor_l_in1 9
#define motor_l_in2 11

#define mz80 2

int run_away_state = 0; // 0 - None; 1 - Go left; 2 - Go right
int attack_state = 0; // 0 - find; 1 - Go forward;

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

void setup() {
  pinMode(mz80, INPUT);
  pinMode(motor_r_e, OUTPUT);
  pinMode(motor_r_in1, OUTPUT);
  pinMode(motor_r_in2, OUTPUT);
  
  pinMode(motor_l_e, OUTPUT);
  pinMode(motor_l_in1, OUTPUT);
  pinMode(motor_l_in2, OUTPUT);

  Serial.begin(9600);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A7, A6, A5, A4, A3, A2, A1, A0}, SensorCount);
  qtr.setEmitterPin(2);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();


  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

unsigned int sensor_values[8];

void loop() {
  uint16_t position = qtr.readLineBlack(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line
  // position
  int sum_left = 0;
  int sum_right = 0;
  for (uint8_t i = 0; i < SensorCount/2; i++)
  {
    sum_left += sensorValues[i]/1000;
    sum_right += sensorValues[i+4]/1000;
  }
  Serial.println(sum_left);
  Serial.println(sum_right);

  /*if (sum_left > 1) {
      analogWrite(motor_r_e, 50);
      digitalWrite(motor_r_in1, LOW);
      digitalWrite(motor_r_in2, LOW);
    
      analogWrite(motor_l_e, 50);
      digitalWrite(motor_l_in1, HIGH);
      digitalWrite(motor_l_in2, LOW);    
    }
  else if (sum_right > 1) {
      analogWrite(motor_r_e, 50);
      digitalWrite(motor_r_in1, HIGH);
      digitalWrite(motor_r_in2, LOW);
    
      analogWrite(motor_l_e, 50);
      digitalWrite(motor_l_in1, LOW/);
      digitalWrite(motor_l_in2, LOW);       
    }
  else {
      analogWrite(motor_r_e, 50);
      digitalWrite(motor_r_in1, HIGH);
      digitalWrite(motor_r_in2, LOW);
    
      analogWrite(motor_l_e, 50);
      digitalWrite(motor_l_in1, HIGH);
      digitalWrite(motor_l_in2, LOW);
    }*/

}
