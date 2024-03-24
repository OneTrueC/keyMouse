#!/usr/bin/python3
import sys,evdev,pyautogui as pg;
device = evdev.InputDevice('/dev/input/event0');
device.grab();

for event in device.read_loop():
    if event.type == evdev.ecodes.EV_KEY:
        if event.code==103 and event.value!=0:
            pg.move(0,-10);
        elif event.code==108 and event.value!=0:
            pg.move(0,10);
        elif event.code==105 and event.value!=0:
            pg.move(-10,0);
        elif event.code==106 and event.value!=0:
            pg.move(10,0);
        elif event.code==17 and event.value!=0:
            pg.move(0,-50);
        elif event.code==31 and event.value!=0:
            pg.move(0,50);
        elif event.code==30 and event.value!=0:
            pg.move(-50,0);
        elif event.code==32 and event.value!=0:
            pg.move(50,0);
        elif event.code==23 and event.value!=0:
            pg.move(0,-200);
        elif event.code==37 and event.value!=0:
            pg.move(0,200);
        elif event.code==36 and event.value!=0:
            pg.move(-200,0);
        elif event.code==38 and event.value!=0:
            pg.move(200,0);

        #Click Events
        elif event.code==100:
            if event.value==1:
                pg.mouseDown();
            elif event.value==0:
                pg.mouseUp();
        elif event.code==97:
            if event.value==1:
                pg.mouseDown(button='right');
            elif event.value==0:
                pg.mouseUp(button='right');
        elif event.code==54:
            if event.value==1:
                pg.mouseDown(button='middle');
            elif event.value==0:
                pg.mouseUp(button='middle');
        elif event.code==28:
            pg.mouseDown();
        elif not event.code in [103,108,105,106,17,31,30,32,100,97,54,23,36,37,38,28]:
            device.ungrab();
            exit();
