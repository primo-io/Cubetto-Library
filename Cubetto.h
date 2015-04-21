/*
 *      Primo Cubetto Library v0.1
 *		http://primo.io
 *
 *      Created on Apr 2015
 *      by Matteo Loglio
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "Arduino.h"
#include "sound.h"
#include "../AccelStepper/AccelStepper.h"
#include "../AccelStepper/AccelStepper.cpp"

#ifndef Cubetto_h
#define Cubetto_h

#define PRIMO_BUZZER_PIN 13

#define PRIMO_LEFT_STEPPER_PIN_1 12
#define PRIMO_LEFT_STEPPER_PIN_2 10
#define PRIMO_LEFT_STEPPER_PIN_3 11
#define PRIMO_LEFT_STEPPER_PIN_4 9

#define PRIMO_RIGHT_STEPPER_PIN_1 6
#define PRIMO_RIGHT_STEPPER_PIN_2 4
#define PRIMO_RIGHT_STEPPER_PIN_3 5
#define PRIMO_RIGHT_STEPPER_PIN_4 3

#define PRIMO_STEPPER_MAX_SPEED    1000
#define PRIMO_STEPPER_ACCELERATION 500

#define PRIMO_STEPPER_FORWARD_STEPS 2700
#define PRIMO_STEPPER_TURN_STEPS    1170

#define PRIMO_DEBUG_MODE 

AccelStepper leftStepper(AccelStepper::HALF4WIRE, PRIMO_LEFT_STEPPER_PIN_1, PRIMO_LEFT_STEPPER_PIN_2, PRIMO_LEFT_STEPPER_PIN_3, PRIMO_LEFT_STEPPER_PIN_4);
AccelStepper rightStepper(AccelStepper::HALF4WIRE, PRIMO_RIGHT_STEPPER_PIN_1, PRIMO_RIGHT_STEPPER_PIN_2, PRIMO_RIGHT_STEPPER_PIN_3, PRIMO_RIGHT_STEPPER_PIN_4); 

 //classes

 class Cubetto
{
	public:
	    void init() {
	    	pinMode(PRIMO_BUZZER_PIN, OUTPUT);

			pinMode(PRIMO_LEFT_STEPPER_PIN_1, OUTPUT);
			pinMode(PRIMO_LEFT_STEPPER_PIN_2, OUTPUT);
			pinMode(PRIMO_LEFT_STEPPER_PIN_3, OUTPUT);
			pinMode(PRIMO_LEFT_STEPPER_PIN_4, OUTPUT);

			pinMode(PRIMO_RIGHT_STEPPER_PIN_1, OUTPUT);
			pinMode(PRIMO_RIGHT_STEPPER_PIN_2, OUTPUT);
			pinMode(PRIMO_RIGHT_STEPPER_PIN_3, OUTPUT);
			pinMode(PRIMO_RIGHT_STEPPER_PIN_4, OUTPUT);

			// IMPORTANT Stepper outputs are disabled here to minimise power usage whilst
			// stationary, as they are automatically enabled in the AccelStepper class
			// constructor
			leftStepper.disableOutputs();
			rightStepper.disableOutputs();

			leftStepper.setMaxSpeed(PRIMO_STEPPER_MAX_SPEED);
			rightStepper.setMaxSpeed(PRIMO_STEPPER_MAX_SPEED);
			leftStepper.setAcceleration(PRIMO_STEPPER_ACCELERATION);
			rightStepper.setAcceleration(PRIMO_STEPPER_ACCELERATION);
			
			playHappyTune();  			
	    }

	    ///////// SOUND ////////

	    void playHappyTune()
		{
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_C6);
		  delay(150);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_E6);
		  delay(150);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G6);
		  delay(100);
		  noTone(PRIMO_BUZZER_PIN);
		}

		void playSadTune()
		{
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G5);
		  delay(150);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_DS5);
		  delay(150);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_C5);
		  delay(300);
		  noTone(PRIMO_BUZZER_PIN);
		}

		void playPairedTune()
		{
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_D6);
		  delay(150);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_F6);
		  delay(150);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_DS5);
		  delay(100);
		  noTone(PRIMO_BUZZER_PIN);
		}

		void playUnpairedTune()
		{
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G3);
		  delay(250);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_F3);
		  delay(250);
		  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_B2);
		  delay(300);
		  noTone(PRIMO_BUZZER_PIN);
		}

		void playForwardTune() {
		  tone(PRIMO_BUZZER_PIN, 3000);
		  delay(50);
		  noTone(PRIMO_BUZZER_PIN);
		}

		void playLeftTune() {
		  tone(PRIMO_BUZZER_PIN, 5000);
		  delay(50);
		  noTone(PRIMO_BUZZER_PIN);
		}

		void playRightTune() {
		  tone(PRIMO_BUZZER_PIN, 4000);
		  delay(50);
		  noTone(PRIMO_BUZZER_PIN);
		}

		///////// MOVEMENT ////////

		void runBothSteppers()
		{
		  leftStepper.enableOutputs();
		  rightStepper.enableOutputs();

		  bool leftStepperIsRunning, rightStepperIsRunning;

		  do
		  {
		    // Run both steppers
		    leftStepperIsRunning = leftStepper.run();
		    rightStepperIsRunning = rightStepper.run();
		  }
		  while (leftStepper.run() || rightStepper.run());

		  leftStepper.disableOutputs();
		  rightStepper.disableOutputs();
		}

		/////// STANDARD //////

		void forward() {
			leftStepper.move(-PRIMO_STEPPER_FORWARD_STEPS);
      		rightStepper.move(PRIMO_STEPPER_FORWARD_STEPS);      
			runBothSteppers();
			playForwardTune();
		}

		void backward() {
			leftStepper.move(PRIMO_STEPPER_FORWARD_STEPS);
      		rightStepper.move(-PRIMO_STEPPER_FORWARD_STEPS);      
			runBothSteppers();
			playForwardTune();
		}

		void left() {
			leftStepper.move(-PRIMO_STEPPER_TURN_STEPS);
		    rightStepper.move(-PRIMO_STEPPER_TURN_STEPS);		    
			runBothSteppers();
			playLeftTune();     
		}

		void right() {
			leftStepper.move(PRIMO_STEPPER_TURN_STEPS);
      		rightStepper.move(PRIMO_STEPPER_TURN_STEPS);     
			runBothSteppers();
			playRightTune();
		}		  

		//////// CUSTOM ////////
		void forward(int steps) {
			leftStepper.move(-steps);
      		rightStepper.move(steps);      
			runBothSteppers();
			playForwardTune();
		}

		void backward(int steps) {
			leftStepper.move(steps);
      		rightStepper.move(-steps);      
			runBothSteppers();
			playForwardTune();
		}

		void left(int steps) {
			leftStepper.move(-steps);
		    rightStepper.move(-steps);		    
			runBothSteppers();
			playLeftTune();     
		}

		void right(int steps) {
			leftStepper.move(steps);
      		rightStepper.move(steps);     
			runBothSteppers();
			playRightTune();
		}

};
#endif