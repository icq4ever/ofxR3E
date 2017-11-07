#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 9000

struct timeTemplate {
	int min;
	int second;
	int millisecond;
};

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
	ofxOscReceiver receiver;
	string messageAddrHeader = "/telemetry/";

	string carInfo;
	string trackInfo;
	float layoutLength;

	int gear;
	float rpm;
	float rpmMax;
	float speed;
	float brakeTemp;

	int completedLaps;
	float laptimeCurrent, laptimeBest, laptimeLast;
	float lapProgress;

	// control information
	float throttlePedal, brakePedal, clutchPedal;

	// draw pedal status
	void drawInputStatus(int x, int y);
	void drawRpmSpeed(int x, int y);
	void drawLapTimeInformation(int x, int y);

	timeTemplate lapT(float seconds);
	string lapT2String(timeTemplate t);

	timeTemplate currentLap;
	timeTemplate lastLap;
	timeTemplate bestLap;
};

