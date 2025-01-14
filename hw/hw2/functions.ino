



int getThousands(int num) {
    return num % 10000 / 1000;
}

int getHundreds(int num) {
    return num % 1000 / 100;
}

int getTens(int num) {
    return num % 100 / 10;
}

int getOnes(int num) {
    return num % 10;
}

void setup ()
{
    int n = 6789;
    Serial.begin (9600);

    Serial . print ( " thousands : " );
    Serial . println ( getThousands ( n ));
    Serial . print ( " hundreds : " );
    Serial . println ( getHundreds ( n ));
    Serial . print ( " tens : " );
    Serial . println ( getTens ( n ));
    Serial . print ( " ones : " );
    Serial . println ( getOnes ( n ));
}

void loop() { 

}