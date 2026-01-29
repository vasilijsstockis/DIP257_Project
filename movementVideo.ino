int IN1 = 7;
int IN2 = 6;

// Motor B
int IN3 = 5;
int IN4 = 4;

//Laiks ms, kas nepieciešams, lai pārvietotu vienu šūnu. Jūs varat to pielāgot, izmantojot kodu no 4. sadaļas.
int LaiksForward = 650;

//Laiks ms, kas nepieciešams, lai pagrieztos par 90 grādiem. Jūs varat to pielāgot, izmantojot kodu no 4. sadaļas.
int LaiksRotate = 360;
int LaiksRotateL = 600;


void Forward(int t){
    //Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(t);
}

void STOPA(){
    //Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    //Motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);

    //Pielāgojiet, ja nepieciešams, bet šis laiks tiks izmantots konfigurācijā 4. solī.
    delay(100);

}

void Right(int t){
    //To dara, pagriežot motorus pretējās virzienos.
    //Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Motor B
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(t);
}

void Left(int t){
    //Motor A
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(t);
}

void STOPp(){
    //Motor A
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    //Motor B
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    delay(100);
}

void Back(int t){
    //Motor A
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Motor B
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(t);
}

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void loop() {
  delay(10000);
  Left(1000);
  STOPA();
  Right(1000);
  STOPA();
  Forward(1000);
  STOPA();
  while(true){

  }

}
