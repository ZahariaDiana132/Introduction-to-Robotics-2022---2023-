# Introduction to Robotics 2022-2023
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

<details>
   <summary> Homework nr 1. </summary>

Task Requirements:
Use a separat potentiometer in controlling each of the color of the RGB led (Red,Green and Blue).  The control must be done with digital electronics(aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

Components:  RBG  LED  (1  minimum),  potentiometers  (3  minimum),resistors and wires (per logic)

   Picture of setup :
   
   
![rgbpot](https://user-images.githubusercontent.com/79654042/197527552-16f3c33b-eb0d-4cef-8011-cee6844fa21c.jpeg)

   [Video of the setup](https://youtu.be/0gd4UtJibwI)
   
 [Source code](https://github.com/ZahariaDiana132/Introduction-to-Robotics-2022---2023-/blob/584f794e456182e03eb7b9ce4ed742b3d89f9d83/Homework1code.ino)
</details>
<details>
<summary> Homework nr 2. </summary>

 
 Task Requirements: You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).See the states it needs to go through:
 The system has the following states:
 1.State 1 (default, reinstated after state 4 ends):  green light for cars,red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  by pressing the button.
  
 2.State 2 (initiated by counting down 8 seconds after a button press):the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds.Duration:  3 seconds.
 
 3.State 3  (initiated after state 2 ends):  red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration:8 seconds.
 
 4.State 4 (initiated after state 3 ends):  red for cars,blinking green for people and a beeping sound from the buzzer,  at a constant interval,  faster than the beeping in state 3.  This state should last 4 seconds.

 Components: 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)
 
   Picture of setup :
   
   
   
![trafficlightt](https://user-images.githubusercontent.com/79654042/198995790-7aebd79b-85f0-4575-9d53-df48ca259c8d.jpg)



   [Video of the setup](https://youtu.be/Hp1TCFuaUxA)
   
 [Source code](https://github.com/ZahariaDiana132/Introduction-to-Robotics-2022---2023-/blob/0c45ab3f3f20d6ce4297058e2fcf801eec1f93c9/trafficlightsZahariaDianaa.ino)

</details>
<details>
<summary> Homework nr 3. </summary>

 
 Task Requirements: 
 The system has to have the following states:
 <details>
 <summary> State  1 </summary> 
 (default,  but  also  initiated  after  a  button  press  in  State2):  Current  position  blinking.   Can  use  the  joystick  to  move  from one  position  to  neighbors.   Short  pressing  the  button  toggles  state2.  Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
 </details>
 
 <details>
 <summary> State  2 </summary>
 (initiated  after  a  button  press  in  State  1):   The  current segment  stops  blinking,  adopting  the  state  of  the  segment  before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change  the  segment  state  from  ON  to  OFF  or  from  OFF  to  ON. Clicking the joystick should save the segment state and exit back to state 1.
 </details>
 
 
 Components: 
 1  7-segment  display,  1  joystick,  resistors  and  wires  (per logic)
 
 Picture of setup :
 
 
 
 
 ![7digitDrawDia](https://user-images.githubusercontent.com/79654042/200570969-7841a23c-b425-4f34-bc52-572fd3135037.jpg)


 [Video of the setup](https://youtu.be/hj81Vb1BxJY)
   
 [Source code](https://github.com/ZahariaDiana132/Introduction-to-Robotics-2022---2023-/blob/2d9dfeab612dbe0fc8211f4fcba87e369f83afcd/7digitDrawDiana.ino)

</details>


<details>
<summary> Homework nr 4.</summary>

 
 Task Requirements: 
 The project consists in manipulating a 4-digit 7-segment display using a joystick. The joystick can be moved by the one axis in the first state to change the current display and by the other axis in the second state to change the display number. State is changed by short pressing the button. Long pressing in the first state causes a reset.

 Components:
 a  joystick,  a  4  digit  7-segment  display,  a  74hc595  shift register, rezistors
 
  Picture of setup:  
  ![c65f3949-cf6e-42a2-9256-8606f3732794](https://user-images.githubusercontent.com/79654042/202196622-148fced2-562a-46e9-9366-f315e8cc88a7.jpg)



  [Video of the setup]( https://youtu.be/DeK5w3XTYy0)
  
   
 [Source code](https://github.com/ZahariaDiana132/Introduction-to-Robotics-2022---2023-/blob/85ddd8878d859c4d130e21bd68423a77ec237036/4_7digitCountDiana.ino)

</details>


<details>
<summary> Matrix project menu (initial state) </summary>

 
Description : Intermediate state of the project. Game menu that contains necessary settings(saved in eeprom), an about, tells you how to play and so much more.
  (more details about the tasks, components in the final version)
   
Bugs/Missing:
   -- the highscore only updates the score not the name of the player for now --
   -- sometimes the screen looks weird(most likely an alimentation problem)--
   -- joystick button is weird, doesn't always press right --
   -- no setting for lcd brightness(always conected through resistor to 5V) because buzzer messed with it and I preffer music over changing how bright the screen is--
   --for now a lot of Serial.prints that help me see the code functions corectly but will further be deleted after I complete the project--
   
   
 Components Used:

   1 LCD,
   
   1 1088AS matrix,
   
   1 MAX7219 LED Driver,
   
   1 joystick,
   
   1 passive buzzer,
   
   1 potentiometer (for controlling the LCD contrast),
   
   1 10??F, 50V electrolytic capacitor,
   
   1 (104) 0.1??F ceramic capacitor,
   
   2 buttons (not yet used),
   
   resistors and wires (per logic)
   
   
   
   
  Picture of setup:  

![WhatsApp Image 2022-12-06 at 21 37 48](https://user-images.githubusercontent.com/79654042/206010543-5798eb6e-5cad-4386-9321-3de67e956d6f.jpeg)


  [Video of the setup initial](https://youtu.be/NFwmhA32Iqs)
  
  [Video of the setup modified](https://youtu.be/Li9PKt_7hw8)
  
 [Source code initial(in history) - 84% memory usage + modified 64% mem usage ](proiectmatricemeniu.ino)
 


</details>


