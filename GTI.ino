#define IR_SENSOR 2
#define R 6
#define G 5
#define B 4
#define R_S A0
#define C_S A1
#define L_S A2
#define BUZZER 7
#define RM_1 12
#define RM_2 13
#define LM_1 8
#define LM_2 9
#define RM_E 10
#define LM_E 11

int sensor_limit = 500;
int dir = 1;
bool r_s, c_s, l_s;
String sensor;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IR_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(RM_1, OUTPUT);
  pinMode(RM_2, OUTPUT);
  pinMode(LM_1, OUTPUT);
  pinMode(LM_2, OUTPUT);
  leds_off();
  set_speed(200, 240);
}

void set_speed(int l_v, int r_v) {
  analogWrite(LM_E, l_v);
  analogWrite(RM_E, r_v);
}

void forward() {
  digitalWrite(LM_1, LOW);
  digitalWrite(LM_2, HIGH);
  digitalWrite(RM_1, HIGH);
  digitalWrite(RM_2, LOW);
}

void reverse() {
  digitalWrite(LM_1, HIGH);
  digitalWrite(LM_2, LOW);
  digitalWrite(RM_1, LOW);
  digitalWrite(RM_2, HIGH);
}

void halt() {
  digitalWrite(LM_1, LOW);
  digitalWrite(LM_2, LOW);
  digitalWrite(RM_1, LOW);
  digitalWrite(RM_2, LOW);
}
void turn_right() {
  digitalWrite(LM_1, LOW);
  digitalWrite(LM_2, HIGH);
  digitalWrite(RM_1, LOW);
  digitalWrite(RM_2, HIGH);
}

void turn_left() {
  digitalWrite(LM_1, HIGH);
  digitalWrite(LM_2, LOW);
  digitalWrite(RM_1, HIGH);
  digitalWrite(RM_2, LOW);
}

void soft_right() {
  digitalWrite(LM_1, LOW);
  digitalWrite(LM_2, HIGH);
  digitalWrite(RM_1, LOW);
  digitalWrite(RM_2, LOW);
}

void soft_left() {
  digitalWrite(LM_1, LOW);
  digitalWrite(LM_2, LOW);
  digitalWrite(RM_1, HIGH);
  digitalWrite(RM_2, LOW);
}

void mild_right() {
  digitalWrite(LM_1, LOW);
  digitalWrite(LM_2, LOW);
  digitalWrite(RM_1, LOW);
  digitalWrite(RM_2, HIGH);
}

void mild_left() {
  digitalWrite(LM_1, HIGH);
  digitalWrite(LM_2, LOW);
  digitalWrite(RM_1, LOW);
  digitalWrite(RM_2, LOW);
}

void sensor_check() {
  r_s = analogRead(R_S) < sensor_limit ? 1 : 0;
  c_s = analogRead(C_S) < sensor_limit ? 1 : 0;
  l_s = analogRead(L_S) < sensor_limit ? 1 : 0;
  sensor = String(l_s) + String(c_s) + String(r_s);
  Serial.println(sensor);
}

void buzzer_on() {
  digitalWrite(BUZZER, HIGH);
}

void buzzer_off() {
  digitalWrite(BUZZER, LOW);
}

void red_on() {
  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
}

void green_on() {
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, HIGH);
}

void blue_on() {
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
}

void leds_off() {
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
}

void rotate_right() {
  turn_right();
  delay(500);
  while (1) {
    turn_right();
    sensor_check();
    if (sensor == "101") {
      break;
    }
  }
}
void line_follow() {
  sensor_check();
  while (sensor != "000") {
    sensor_check();
    if (sensor == "101") {
      forward();
      green_on();
    } else if (sensor == "100") {
      mild_right();
      red_on();
    } else if (sensor == "110") {
      turn_right();
      dir = 2;
    } else if (sensor == "001") {
      mild_left();
      blue_on();

    } else if (sensor == "011") {
      turn_left();
      dir = 0;
    } else if (sensor == "111") {
      if (dir == 2) {
        mild_right();

        dir = 1;
      } else if (dir == 0) {

        mild_left();
        dir = 1;
      } else {
        // rotate_right();

        dir = 1;
      }
    } else if (sensor == "000") {
      buzzer_on();
      forward();
      halt();
      buzzer_off();
    }
  }
}


void move_check() {
  //write your code here
  forward();
  Serial.println("FWD");
  delay(4000);
  reverse();
  Serial.println("REV");
  delay(4000);
  turn_right();
  Serial.println("RIGHT");
  delay(4000);
  turn_left();
  Serial.println("LEFT");
  delay(4000);
}

void ir_check() {
  if (digitalRead(IR_SENSOR) == LOW) {
    buzzer_on();
  } else {
    buzzer_off();
  }
}
void run_task() {
  //write your code here
  forward();
}

void rgb_check() {
  red_on();
  delay(1000);
  green_on();
  delay(1000);
  blue_on();
  delay(1000);
  leds_off();
  delay(1000);
}

void array_display() {
  Serial.println(String(analogRead(A2)) + "\t" + String(analogRead(A1)) + "\t" + String(analogRead(A0)));
  delay(100);
}
void loop() {
  // put your main code here, to run repeatedly:
  //run_task();
  //Serial.println(String(analogRead(A2)) + "\t" + String(analogRead(A1)) + "\t" + String(analogRead(A0)));
  //delay(100);
  line_follow();
  //forward();
  //sensor_check();
  //array_display();
  //rgb_check();
  //ir_check();
}
