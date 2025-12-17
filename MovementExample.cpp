// Šis kods satur funkcijas, kas regulē kustību.

// Motor A
int IN1 = 7;
int IN2 = 6;

// Motor B
int IN3 = 5;
int IN4 = 4;

//SVARIGI Jums ir jānodrošina atbilstošas pinas no jūsu shēmas.

//Laiks ms, kas nepieciešams, lai pārvietotu vienu šūnu. Jūs varat to pielāgot, izmantojot kodu no 4. sadaļas.
int LaiksForward = 1000;

//Laiks ms, kas nepieciešams, lai pagrieztos par 90 grādiem. Jūs varat to pielāgot, izmantojot kodu no 4. sadaļas.
int LaiksRotate = 1000;


void Forward(){
    //Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(LaiksForward);
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

void Left(){
    //To dara, pagriežot motorus pretējās virzienos.
    //Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Motor B
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(LaiksRotate);
}

void Right(){
    //Motor A
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(LaiksRotate);
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

void Back(){
    //Motor A
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Motor B
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(LaiksForward);
}
