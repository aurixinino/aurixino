<h1> How to Compile the Example </h1>

This example, can be recreated on your host computer by:
  1. install the Aurix Development Studio (ADS) from https://www.infineon.com/cms/en/tools/aurix-tools/free-tools/infineon/
  2. select the Blinky_LED1_KIT_TC275_LK (ref. https://www.infineon.com/cms/en/product/promopages/aurix-expert-training/) by the importing function available inside teh ADS development system
  3. replace the source files Cpu0_Main.c / Cpu1_Main.c / Cpu2_Main.c with the one in this GIT
  4. add the file Sketch_Blinky_Multicore.c in the project root directory (to clarify: on the side of Cpu0_Main.c)
  5. dowload from this GIT the Arduino folder and place under Libraries (to clarify: on the side of iLLD)
  6. compile
  7. flash
  8. observe example behaviour as described into https://aurixino.blogspot.com/2021/04/led-blink-in-aurixmulticore.html


<b>Notes:</b> to oberserve the CPU syncronization, enable the following code '//TO TEST THE DESYNC: semaphore_wait(s_cpuSync);' in cpu0_setup() function (in the dowloaded file it is commented out)
