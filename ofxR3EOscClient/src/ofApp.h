#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 9000
#define recInterval 100

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


	// game information
	string carInfo;
	string trackInfo;
	float layoutLength;

	int gear;
	int rpm;
	int rpmMax;
	float speed;
	float brakeTemp;

	int completedLaps;
	float laptimeCurrent, laptimeBest, laptimeLast;
	float lapProgress;

	// control information
	float throttlePedal, brakePedal, clutchPedal;


	// osc save
	int64_t lastCheckedTimer;


	// draw telemetry functions
	void drawInputStatus(int x, int y);
	void drawRpmSpeed(int x, int y);
	void drawLapTimeInformation(int x, int y);

	// rpmDrawing
	void rpmDrawing(int x, int y);

	timeTemplate lapT(float seconds);
	string lapT2String(timeTemplate t);

	timeTemplate currentLap;
	timeTemplate lastLap;
	timeTemplate bestLap;

	ofFbo rpmFbo;

	vector<int> tele_gears;
	vector<int> tele_rpm;
	vector<int> tele_speed;
	//ofPixels rpmPixels;
};

