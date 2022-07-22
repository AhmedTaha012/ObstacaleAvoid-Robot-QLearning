# ObstacaleAvoid-Robot-QLearning
<p> This Project is based on <b> avr atmega328p </b> and <b> q-learning algorthim </b> </p>

The main purpose of this project is to make our robot avoid obstacles by detecting them using
ultrasonic sensor and also learn to take the optimal action in this situation. The learning
process is based on q learning algorithm which will be discussed later in the algorithm
explanation

# Real-Time Hardware Photo
![image](https://user-images.githubusercontent.com/96799091/174688527-ecd398ae-f920-49c1-b036-9c6ffeb552e7.png)

# Viedo Project Links 
### 
### Training 100 episodes then Testing
https://www.youtube.com/watch?v=g_ovc39Iz-Y
### Testing after 100 episodes
https://www.youtube.com/watch?v=fybteD33rh0
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

## Phase One
### Phase One – Part One:
After building the robot and putting the 2 DC motors in it, we need to know how
to control DC motors using Arduino. We can control the speed of the DC motor
by simply controlling the input voltage to the motor and the most common
method of doing that is by using PWM signal.
### PWM DC Motor Control:
PWM, or pulse width modulation is a technique which allows us to adjust the
average value of the voltage that’s going to the electronic device by turning on
and off the power at a fast rate.
The average voltage depends on the duty cycle, or the amount of time the signal
is ON versus the amount of time the signal is OFF in a single period of time.
And as we illustrated before we do mapping between Arduino and ATmega328P
and we use the AVR timer/counter to make it works on fast PWM mode of
operation.
### H-bridge DC motor concept:
For controlling the rotation direction, we just need to inverse
the direction of the current flow through the motor, and the
most common method of doing that is by using an H-Bridge.
An H-Bridge circuit contains four switching elements,
transistors or MOSFETs, with the motor at the center
forming an H-like configuration. By activating two
particular switches at the same time we can change the
direction of the current flow, thus change the rotation
direction of the motor. For example, if we closed s1 and s4
the motor rotates in a direction and if we closed s2 and s3,
the motor rotates in the other direction.
So if we combine these two methods, the PWM and the HBridge, we can have a complete control over the DC motor.
There are many DC motor drivers that have these features and the L298N is one
of them.

![image](https://user-images.githubusercontent.com/96799091/174686602-00654d3a-d69d-4f2f-ba36-4e0540dd5eab.png)

### Atmega328p and Motor Driver:
Let’s connect the driver with arduino board. As we can see in our simulation we
connect the enable pins from the driver to pin 5,6 in arduino which are the
(OC0A and OC0B) pins in avr that can be used to set the mode of operation of
the timer/counter to fast pwm mode by enabling the WGM00, WGM01,
WGM02 in TCCR0A and TCCR0B.
Then we connect the input pins to pins from 0 to 3 in the arduino in order to
control the direction and in the figure below, we run the code we wrote using c
language that ouput 0 to pins 0,2 and output 1 to pins 1,3 and that make the two
motors to rotate in the same direction but in backward direction

![image](https://user-images.githubusercontent.com/96799091/174686917-c2a9d153-7989-4bdf-b3e0-ef5d1730f803.png)

### Phase One – Part Two: (Ultrasonic phase)
In this part of phase one we connected 2 ultrasonic and 1 LCD to the Arduino
UNO and as wrote the code of their implementation on ATMEL Studio.
-The purpose of connecting the LCD is to observe the changing of the ultrasonic
readings.
-Why have we connected 2 ultrasonic? This will be explained in details in
phase2.

![image](https://user-images.githubusercontent.com/96799091/174687296-ea8a5384-7dfd-4c03-b7cd-0260d3b5ba99.png)

### The first ultrasonic:
-The trig pin is connected to TRIGGER1 and the echo pin is connected to
ECHO1 (INT0). In the implementation of the code we have enabled INT0 to
sense the interrupt at any logic change. As the signal goes from 0 to 1 – an
interrupt has been initiated – TCNT0 (Timer/Counter register) start counting
and as it goes from 1 to 0 – another interrupt has been initiated – the value of
TCNT0 is stored in a variable, so we can calculate the distance, then the TCNT0
is cleared.
### The second ultrasonic:
-The trig pin is connected to TRIGGER2 and the echo pin is connected to
ECHO2 (INT1). In the implementation of the code we have enabled INT1 to
sense the interrupt at any logic change. As the signal goes from 0 to 1 – an
interrupt has been initiated – TCNT2 (Timer/Counter register) start counting
and as it goes from 1 to 0 –another interrupt has been initiated – the value if
TCNT2 is stored in a variable, so we can calculate the distance, then the TCNT2
is cleared.

## Phase Two (Algorithm phase):
We used Q Learning algorithm.
### What is Q Learning algorithm?
Q-learning is a type of reinforcement learning algorithm that contains an “agent”, the
agent here is our robot which takes actions based on an optimal policy to reach a predefined goal or until it reaches a terminal state.
Reinforcement learning is a type of machine learning algorithms. When an input
dataset is provided to a reinforcement learning algorithm, it learns from this dataset
(Offline learning) otherwise it learns from its experience and surroundings (Online
learning).
### Why Q Learning algorithm?
As the robot knows nothing about the environment, it has to explore it first and learn
more about it, then the robot will be able to exploit it.
### What is epsilon – greedy algorithm?
The aim is to have a balance between exploration and exploitation. Exploration allows
us to have some room for trying new things, sometimes contradicting what we have
already learned. The epsilon parameter introduces randomness into the algorithm,
forcing us to try different actions. This helps not getting stuck in a local optimum.
In the beginning, the epsilon rates will be higher. The agent will explore the environment
and randomly choose actions. This occurs like this logically, since the agent does not
know anything about the environment. As the agent explores the environment, the
epsilon rate decreases and the agent starts to exploit the environment.
### Exploring the environment:
If the agent knows nothing about the environment, how would it learn?
Firstly the epsilon rate is high which means that the agent – our robot – takes a random
action so it goes from its current state to another new state (States are a representation
of the current world or environment of the task.) and receive a reward, this reward could
be a negative value – punishing the robot – so the robot learn that it should not reach this
state again, the reward could also be a positive value to encourage the robot to take this
action again in this situation, then the Q is updated and the robot keeps doing these steps
until it finishes exploring the environment which is called learning phase.
### What is the meaning of Q?
The ‘Q’ in Q-learning stands for quality. Quality here represents how useful a given
action is in gaining some future reward. Updating Q can be done using the following
equation:\
𝑄(𝑠, 𝑎) ← (1 − 𝛼)𝑄(𝑠, 𝑎) + 𝛼(𝑟 + 𝛾 max𝑎′ 𝑄(𝑠′, 𝑎′))\
Where:\
𝑄(𝑠, 𝑎) is the old value\
𝛼 is the learning rate\
(𝑟 + 𝛾 max𝑎′ 𝑄(𝑠′, 𝑎′)) is the learned value\
The Q equation will be update till reaching 𝑸∗(𝒔, 𝒂) at each action.
Where 𝑸∗(𝒔, 𝒂) is the expected utility starting out having taken action from state s and
acting optimally

### Exploiting the environment:
By the time the epsilon will decay which indicates the beginning of the exploiting stage.
In this stage the robot starts to act optimally based on what it has learned in the exploring
stage. The robot’s goal is always to maximize the reward and that is what the robot is
going to do based on what it learned previously using the following equation:\
𝑄∗(𝑠, 𝑎) = ∑ 𝑇(𝑠, 𝑎, 𝑠′)[𝑅(𝑠, 𝑎, 𝑠′) + 𝛾 𝑉∗(𝑠′)]
Where:\
𝑇(𝑠, 𝑎, 𝑠′) is the transition function\
𝑅(𝑠, 𝑎, 𝑠′) is the reward function\
𝑉∗(𝑠′) is the expected utility starting in s and acting optimally.

## Now we can answer the question of “why have we used 2 ultrasonic?”
In order to apply this algorithm, we need to determine 3 things:
1. State-Space
2. Action-space
3. The reward of taking an action to go from one state to another
### 1. State-space:
The states are the sensory information resulting from the robot’s space observation.
Our robot is using ultrasonic sensors for the purpose of determining the obstacles
around it. The robot uses both the right and the left sensors to determine the current
state. The readings of the sensors are converted to one of four values:\
0 No obstacles\
1 There is no obstacle on the right but there is a one on the left\
2 There is no obstacle on the left but there is a one on the right\
3 There is an obstacle on the left and on the right\
### 2. Action-space:
Here, we have 3 actions the robot can take:\
0 Forward\
1 Left\
2 Right\
3 Stop


# The flowchart of the code:
The following flowchart represents how the code works\

![image](https://user-images.githubusercontent.com/96799091/174688617-dbe96691-7600-4e26-9c21-9ed53b3f7602.png)

•	A certain number of episodes is determined – represents the number of the iterations. Then the robot will determine it is in the exploring phase or not. If the robot were in the exploring phase, the sensors readings will be sent to the robot to determine the current state of the robot and as the robot is in the exploring phase, it will take random action. Now and after taking a random action, the robot is in a new state. The reward will be calculated and the Q will be updated using and the number of the iterations will be decreased by one. This will be repeated till the end of the exploring phase.\

•	If the robot was exploiting, the sensors readings’ will be sent to the robot to determine the current state of the robot, and take an action to achieve its goal which is to get the maximum reward based on what it has learnt in the learning or exploring phase.





