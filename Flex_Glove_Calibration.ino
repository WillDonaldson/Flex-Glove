/* Will Donaldson
 * 1/11/17
 * For detailed instructions on how to program the Arduino Lilypad without FTDI: 
 * https://www.instructables.com/id/How-to-upload-codes-to-Lilypad-Arduino-Without-FTD/
 */

int fingerPins[5]={A0, A1, A2, A3, A4};         //order of finger connections from thumb to pinky (ie: A0=thumb, A1=index,...etc.)
int fingerVals[5];                              //stores value of flex sensor on each finger
const char *names[5]={"Thumb: ", "Index: ", "Middle: ", "Ring: ", "Pinky: "};
int CalibrationVals[2][5];

void setup() {
  Serial.begin(9600);                           //If you have issues with the baudrate and serial monitor see the Read Me file. 
  CalibrateFlexSensors();
}

void loop() {
}

void CalibrateFlexSensors(){
  int calibrationCount=0;
  while(calibrationCount<=1){
    /* If calibrationCount==0, then find minimum flex value (hand relaxed position)
     * Elif calibrationCount==1, then find maximum flex value (hand in fist position)
     */
     if(calibrationCount==0){
      Serial.println("Please lay your hand flat");
      delay(3000);
      Serial.println("Collecting minimum flex readings");
     }
     else if(calibrationCount==1){
      Serial.println("Please close you hand into a fist");
      delay(3000);
      Serial.println("Collecting maximum flex readings");
     }
     for(int i=0; i<5; i++){
      int readingCount=0;
      int readingSum=0;
      while(readingCount<10){                        //Take 10 unique readings
        readingSum+=analogRead(fingerPins[i]);
        readingCount+=1;
        delay(200);
      }      
      CalibrationVals[calibrationCount][i]=readingSum/10;    //Record average of 10 readings
     }
     calibrationCount+=1;
  }
  Serial.println("Calibration Complete");
  Serial.println("In the order from thumb to pinky, your offsets are:");
  for(int i=0; i<2; i++){
    if(i==0){Serial.print("Minimum Offsets:\t");}
    else{Serial.print("Maximum Offsets:\t");}
    for(int j=0; j<5; j++){
      Serial.print(CalibrationVals[i][j]);
      Serial.print(", ");
    }  
    Serial.println();
  }
}

