package com.siemens.test;

import processing.core.*;


public class MainActivity extends PApplet {
	private final Bluetooth bluetooth = new Bluetooth();
	private String message = "";
	
	private static final String START = "start\n";
	
	private long time = 0;
	
	public void setup() {
		background(199,178,153);
		
		if(bluetooth.check()) {
			bluetooth.write(START);
		}
    }
 
    public void draw() {
    	time = millis();
    	
    	message = bluetooth.read();
    	
    	if(message.equals(START)) {
    		background(255);
    	}
    }
}
