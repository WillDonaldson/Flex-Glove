/*  Will Donaldson 
 *  1/11/17
 *  
 *  Instructions: 
 *  YouTube Video:
 *  
 *  Build flex glove first, then run Flex_Glove_Calibration.ino. Copy output into line 31 before running this code.
 *  
 *  Wiring Convention:   
 *  Finger  | Lilypad Pin         
 *  Thumb   | D5      
 *  Index   | D6         
 *  Middle  | D7         
 *  Ring    | D8         
 *  Pinky   | D9  
 *  
 */

#include <Servo.h>
Servo thumb, index, middle, ring, pinky;

int angles[5];                              //array for storing servo angles
int val;
int flexPins[]={A0,A1,A2,A3,A4};            //order of finger connections from thumb to pinky (ie: A0=thumb, A1=index,...etc.)

/*  
 *  Below are the calibration offsets for flex sensors, top row is offset for relaxed finger, bottom row is offset for contracted finger. 
 *  Columns, from left to right correspond from the thumb to pinky. 
 *  Values from the output of Flex_Glove_Calibration.ino
 */
int flexsensorRange[2][5]= {{260, 400, 480, 230, 380},
                            {330, 500, 900, 360, 450}};  
                            
void setup() {
  Serial.begin(9600);                        //If you have issues with the baudrate and serial monitor see the Read Me file. 
  thumb.attach(5);  
  index.attach(6);  
  middle.attach(7); 
  ring.attach(8);   
  pinky.attach(9);
}

void loop() {
  for(int i=0; i<5; i+=1){                        //repeat process for each of the 5 fingers
    val=analogRead(flexPins[i]);                  //reads the position of the finger
   
    /* 
     * The following if and else if pair of statements are because 2 of the servos are orientated in reverse to the other 3 (see youtube video around 5:14 minute mark)
     * As such depending on which servo is being written to the angle may need to be reversed. 
     * The angles depend case by case basis of how you oreintate the servos and which fingers the fishing line goes to, change the code as needed
     */
    if(i%2==0){ //                       
      angles[i]=map(val, flexsensorRange[0][i], flexsensorRange[1][i], 0, 180);   //maps the value measured from the flex sensor and outputs an angle for the servo within the range finger motion
    }
    else if(i%2!=0){
      angles[i]=map(val, flexsensorRange[0][i], flexsensorRange[1][i], 180, 0);
    }
    
    angles[i]=constrain(angles[i], 0, 180);       //any values above/below the maximum/minimum calibration value are reset to the highest/lowest value within the acceptable range
    Serial.print(angles[i]);
    Serial.print('\t');     
    if(i==0){ thumb.write(angles[i]);}             //move servos to set angle
    if(i==1){ index.write(angles[i]);}
    if(i==2){ middle.write(angles[i]);}
    if(i==3){ ring.write(angles[i]);}
    if(i==4){ pinky.write(angles[i]);}
  }
  Serial.println();
  delay(100);
}


