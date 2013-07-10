package com.siemens.test;

import processing.core.*;


public class MainActivity extends PApplet {
	private final Bluetooth bluetooth = new Bluetooth();
	private String message = "";
	
	private static final String START = "start\n";
	
	public void setup() {
		background(0);
		
		if(bluetooth.check()) {
			bluetooth.write(START);
		}
    }
 
    public void draw() {
    	message = bluetooth.read();
    	
    	if(message.equals(START)) {
    		background(255);
    	}
    }
}
