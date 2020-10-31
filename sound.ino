#define NOTE_A4  440
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880

int melody[]={
  NOTE_A4,
  NOTE_A4,
  NOTE_C5,
  NOTE_D5,
  NOTE_E5,
  NOTE_A5,
  NOTE_A5,
  NOTE_G5,
  NOTE_E5,
  NOTE_D5,
  NOTE_C5,
  NOTE_A5,
  NOTE_C5,
  NOTE_D5,
  NOTE_E5,
  NOTE_A5,
  NOTE_A5,
  NOTE_G5,
  0,
  NOTE_A4,
  NOTE_A4,
  NOTE_C5,
  NOTE_D5,
  NOTE_E5,
  NOTE_A5,
  NOTE_GS5,
  NOTE_A5,
};

int noteDurations[]={
  3,3,4,8,3,3,4,6,3,
  8,3,3,4,8,3,3,4,6,2,4
  3,3,4,8,3,3,2,8,    
}

void play(){
  for (int thisNote = 0; thisNote < 28; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
void setup() {
  play();
}

void loop() {
  // put your main code here, to run repeatedly:

}
