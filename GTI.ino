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

int sensor_limit = 350;
int dir = 1;
bool r_s, c_s, l_s;
String sensor;
int node = 0;

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
  set_speed(175, 175);
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

void blue_on() {
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, HIGH);
}

void green_on() {
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
}

void leds_off() {
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
}




void line_follow_1() {
  sensor_check();
  while (sensor != "000") {
    sensor_check();
    if (sensor == "101") {
      forward();
    } else if (sensor == "100") {
      mild_right();
    } else if (sensor == "110") {
      turn_right();
      dir = 2;
    } else if (sensor == "001") {
      mild_left();
    } else if (sensor == "011") {
      turn_left();
      dir = 0;
    } else if (sensor == "111") {
      if (dir == 2) {
        soft_right();
        dir = 1;
      } else if (dir == 0) {
        soft_left();
        dir = 1;
      } else {
        dir = 1;
      }
    } else if (sensor == "000") {
      forward();
      buzzer_on();
      red_on();
      delay(500);
      buzzer_off();
      leds_off();
      node = node + 1;
      Serial.print("node: ");
      Serial.println(node);


      sensor_check();
      if (node == 1) {
        if(ir_check) {
          red_on();
          delay(200);
          leds_off();
          forward();
        }
        forward();
        delay(500);  // Add a delay to ensure it's moving forward properly
        sensor_check();
      } else if (node == 2) {
        // Turn right and re-align after node 2
        turn_right();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_right();  // Gradual right to align with the line
          sensor_check();
        }
        forward();  // Move forward after aligning
      } else if (node == 3) {
        // Turn left and re-align after node 3
        turn_left();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_left();  // Gradual left to align with the line
          sensor_check();
        }
        forward();  // Move forward after aligning
      } else if (node == 4) {
        // Turn left and re-align after node 3
        turn_left();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_left();  // Gradual left to align with the line
          sensor_check();
        }
        forward();  // Move forward after aligning
      } else if (node == 6) {
        // Turn left and re-align after node 3
        turn_left();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_left();  // Gradual left to align with the line
          sensor_check();
        }
        forward();  // Move forward after aligning
      } else if (node == 10) {
        // Turn left and re-align after node 3
        turn_left();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_left();  // Gradual left to align with the line
          sensor_check();
        }
        forward();  // Move forward after aligning
      } else if (node == 12) {
        // Turn left and re-align after node 3
        turn_left();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_left();  // Gradual left to align with the line
          sensor_check();
        }
        forward();  // Move forward after aligning
      } else if (node == 13) {
        // Turn left and re-align after node 3
        turn_left();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_left();  // Gradual left to align with the line
          sensor_check();
        }
        forward();  // Move forward after aligning
      } else if (node == 14) {
        // Turn right and re-align after node 2
        turn_right();
        delay(500);  // Adjust delay as needed
        sensor_check();
        while (sensor != "101") {
          mild_right();  // Gradual right to align with the line
          sensor_check();
        }
        forward();
      } else if (node == 16) {
        //set_speed(0,0);
        halt();
      }
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

int ir_check() {
  if (digitalRead(IR_SENSOR) == LOW) {
    red_on();
    return 1;
  } else {
    blue_on();
    return 0;
  }
}
void run_task() {
  line_follow_1();
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
  int x = ir_check();
  //Serial.println(String(analogRead(A2)) + "\t" + String(analogRead(A1)) + "\t" + String(analogRead(A0)));
  //delay(100);
  //line_follow();
  // rgb_check();
  // ir_check();
  //sensor_check();
}
