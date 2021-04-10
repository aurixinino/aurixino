# aurixino

Years back, I did develop the adaptation of Arduino to the Infineon XMC product family. I think it was 2014 and I spent some night to work on that. It was fan and my goal was not to create anything professional, as later on was done by Infineon directly. 

Nowadays, I like to try similar stuff with AURIX hardware, even if could be interpreted as a nonsense....


Arduino Wiring Language porting to AURIX™ microcontrollers


Arduino™ Wiring language is a widely used language for embedded system programming. It is very easy and immediate to create little microcontrollers applications such as to control servos, motors, inputs, outputs, displays, etc.. . This project has the aim to port the Arduino™ Wiring language to the AURIX™ microcontrollers. I've started the project by using the Infineon TC275 Lite Kit and AURIX™ Development Studio:


Why Arduino to AURIX™?

I've started this porting project because I like very much the simplicity and intuitive Arduino Wiring language, but I'm not comfortable with the absence of a professional debug (Arduino 'serial.print()' is good only for basic debug purposes). Merging Arduino to AURIX™ I'll get the best of both environments: 
TriCore 32-bit power; 
Arduino's simplicity; 
Arduino's various examples; 
Arduino's various libraries; 
AURIX™ professional Development Studio environment (IDE), Eclipse based; 
AURIX™ professional debug environment (Tasking plug-in); 
AURIX™ code examples and Low Level drivers (iLLD).
