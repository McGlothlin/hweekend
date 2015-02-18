# HWeekend
Embedded code I wrote for a car that was controlled by Bluetooth via an Android app.

This project took place over 30 hours one weekend for an event called HWeekend (Hardware Weekend) and was sponsored by Rockwell Collins. The goal was to think of and create a project that you could build within the allotted time in a group, and then demo it for the sponsors/other teams at the end. I came up with the idea to do a Bluetooth R/C car. Seven other students at the event joined me in my endeavor, and I thus led the project design as a whole. One of the students was a fifth year senior in industrial engineering and he led a mechanical team that built and designed the chassis.

The code in this repo was written for the Teensy 2.0 microcontroller. We connected this board to two motor controllers which drove each of the four wheels. Most of the embedded code was figuring out which way the wheels needed to turn depending on which bits were set in the signal received from the app. By the end, I programmed controls for the car to move 8 different ways, and stop when a kill signal was sent. Much of the embedded programming became extremely difficult to debug as the night rolled on, because a single character's difference would change the direction of a wheel, and I got so tired that I could barely tell the difference between the commands since we pulled an all nighter to finish the project. In the end I succeeded though, and the car rolled as I had planned!

I uploaded this as a single commit since I wrote this on my local machine during the event.
