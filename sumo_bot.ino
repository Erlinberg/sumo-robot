#define motor_r_e 3
#define motor_r_in1 4
#define motor_r_in2 5

#define motor_l_e 6
#define motor_l_in1 7
#define motor_l_in2 8

#define mz80 2

int run_away_state = 0; // 0 - None; 1 - Go left; 2 - Go right
int attack_state = 0; // 0 - find; 1 - Go forward;

static const uint8_t line_sensors = {A0,A1,A2,A3,A4,A5,A6,A7}; // from left to right

void setup() {
  pinMode(mz80, INPUT);
  pinMode(motor_r_e, OUTPUT);
  pinMode(motor_r_in1, OUTPUT);
  pinMode(motor_r_in2, OUTPUT);
  
  pinMode(motor_l_e, OUTPUT);
  pinMode(motor_l_in1, OUTPUT);
  pinMode(motor_l_in2, OUTPUT);

  for (int i = 0; i < 8; i++) {
      pinMode(line_sensors[i], INPUT);
    }

}

void get_direction() {
    bool danger = false;
    for (int i = 0; i < 4; i++) { // left
      danger = (digitalRead(line_sensors[i]) == HIGH);
      if (danger) { run_away_state = 2; return; }
    }
    
     for (int i = 4; i < 8; i++) { // right
      danger = (digitalRead(line_sensors[i]) == HIGH);
      if (danger) { run_away_state = 1; return; }
    }

    run_away_state = 0;
  }

void move_robot(speedL, in1L, in2L, speedR, in1R, in2R) {
  analogWrite(motor_l_e, speedL);
  digitalWrite(motor_l_in1, in1L);
  digitalWrite(motor_l_in2, in2L);

  analogWrite(motor_r_e, speedR);
  digitalWrite(motor_r_in1, in1R);
  digitalWrite(motor_r_in2, in2R);
  }

void find_enemy() {
    float distance = get_distance();
    if (distance < thershhold) {
      move_robot(255, HIGH, LOW, HIGH, LOW);
      attack_state = 0;
    }
    else {
      attack_state = 1;
    }
  
  }

float get_disance() {
  }

void loop() {
  get_direction();
  if (run_away_state != 0) {
      switch run_away_state:
        case 1:
          move_robot(200, LOW, LOW, HIGH, LOW);
        case 2:
          move_robot(200, HIGH, LOW, LOW, LOW);;
    }
  else {
    move_robot(255, HIGH, LOW, HIGH, LOW);
    } 
}
