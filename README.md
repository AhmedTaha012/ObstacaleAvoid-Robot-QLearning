# ObstacaleAvoid-Robot-QLearning
The main purpose of this project is to make our robot avoid obstacles by detecting it using
ultrasonic sensor and also learn to take the optimal action in this situation. The learning
process is based on q learning algorithm which will be discussed later in the algorithm
explanation
## Project Phases
In order to make the project building process simpler, the process should be decomposed
to number of steps or phases
### Phase 1 
This phase is focused on building the robot, controlling its motion and speed and also
check the ultrasonic detection by making sure that it works correctly. This phase must
work without any small errors before going to the next phase.
### Phase 2
Here, we focused more on the algorithm, learning and testing process. After choosing
the right algorithm, it is then tested on the robot until observing that the algorithm is
working correctly then we go to learning process and test the robot after that.

## Collaborators 
[AhmedTaha-TeamLeader](https://www.github.com/AhmedTaha012)\
[AhmedSamer](https://www.github.com/ahmedsamer806)\
[NouraMedhat](https://www.github.com/NouraMedhat28)\
[SalmaMohamed](https://www.github.com/Salma240)\
[PavlySafwt](https://www.github.com/PavlySafwat)

## List of components:
Microcontroller Arduino UNO 1\
Motor Driver L298N 1\
Ultrasonic sensor HC-SR04 2\
Battery Lithium ion 3\
Buzzer 1

## Arduino UNO 
is a microcontroller board based on the
ATmega328P. It has 14 digital input/output pins (of which 6 can
be used as PWM outputs), 6 analog inputs, a 16 MHz ceramic
resonator, a USB connection, a power jack, an ICSP header and
a reset button.


![image](https://user-images.githubusercontent.com/96799091/174682606-7177fd78-4dd0-44a0-89f2-7226542dcfc6.png)

## ATmega328P
is one of the high performances AVR
technology microcontroller. It is designed by 8-bit
CMOS technology and RISC CPU.
ATmega328P has three digital ports PORTB, PORTC, PORTD. All these pins can
be used as digital input/output. Each port can also be used for other purposes.

![image](https://user-images.githubusercontent.com/96799091/174682862-746d69f2-22e1-4be9-8af1-bb34988cd079.png)

### How to map between Arduino UNO and ATmega328P?

![image](https://user-images.githubusercontent.com/96799091/174682955-7cd889fa-3564-4562-b1de-ae151459ce9d.png)

## Motor Driver (L298N)
A motor driver is an integrated circuit chip which is
usually used to control motors in autonomous robots.
Motor driver act as an interface between Arduino and
the motors.

![image](https://user-images.githubusercontent.com/96799091/174684445-3df4e70d-c00c-4bd8-8115-42ca46f5e542.png)

### How it works:
It works on the concept of H-bridge. H-bridge is a circuit which allows the voltage to be
flown in either direction..

### Power supply pins
Pin               function\
Vcc               It is used to supply power to the motor (5v~35v).\
GND               Will be connected to the ground.\
+5V               If the 5-EN jumper is in place, this pin acts as output and can be used to power up another circuitry – in our project it powers up the Arduino.\

### Control pins
Pin function\
IN1 and IN2  are used to control the   direction of Motor A.\
IN3 IN3 and IN4 are used to control the direction of Motor B.\

### Speed control pins
Pins function
ENA This pin is connected to the PWM input of the microcontroller to control the speed of (Motor A).
It also can be connected to +5V, then the motor rotates maximum speed.
ENB This pin is connected to the PWM input of the microcontroller to control the speed of (Motor B).
It also can be connected to +5V, then the motor rotates maximum speed.

### Output pins
Pins function
OUT1 and OUT2 They provide the output for Motor A.
OUT3 and OUT4 They provide the output for Motor B

## Ultrasonic sensor (HC-SR04)
What is the ultrasonic sensor?
An ultrasonic sensor is an instrument that measures the distance
to an object using ultrasonic sound waves.

![image](https://user-images.githubusercontent.com/96799091/174684519-1ddafbd9-bf9d-4f7a-bac1-5094109e241c.png)

### How the sensor works:
The sensor head emits an ultrasonic wave and receives the wave
reflected back from the target.

![image](https://user-images.githubusercontent.com/96799091/174684683-f22319d7-b5fc-4d7c-bef9-e88593108a9e.png)

### The used equation:

![image](https://user-images.githubusercontent.com/96799091/174684696-7b31ccbc-9db8-46c8-8147-73be23b12565.png)

![image](https://user-images.githubusercontent.com/96799091/174684715-dd49a976-056c-4ea7-8967-b089e0978d76.png)

### Ultrasonic pins
Pin  function
Vcc This pin has to be connected to a power supply +5V.
Trig (Trigger) This pin is used to receive controlling signals from the Arduino board. This is the triggering input pin of the sensor
Echo  This pin is used for sending signals to the Arduino board where the Arduino calculates the pulse duration to know the distance. This pin is the echo output of the sensor.
Gnd This pin has to be connected to the ground. 

## Lithium ion 3.7v batteries
Lithium-ion battery or Li-ion battery is a type of rechargeable
battery composed of cells in which lithium ions move from the
negative electrode through an electrolyte to the positive electrode
during discharge and back when charging.

![image](https://user-images.githubusercontent.com/96799091/174685034-ee69da4f-ae83-46b8-853b-e0090979962a.png)

## Buzzer
The buzzer is used in our project to indicate the end of the learning
phase which means the beginning of the testing phase.

![image](https://user-images.githubusercontent.com/96799091/174685126-f73663d6-0f8a-4b44-80bb-57e2340262eb.png)

# Project phases:
As mentioned before the project has 2 phases:\
Phase One: Building the robot.\
Phase Two: Applying the Q Learning algorithm
