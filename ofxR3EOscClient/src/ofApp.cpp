#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	receiver.setup(PORT);
	ofBackground(54);

	rpmFbo.allocate(600, 600, GL_RGBA);
	rpmFbo.begin();
	ofClear(0);
	rpmFbo.end();
	//rpmPixels.allocate(600, 600, OF_PIXELS_RGBA);

	lastCheckedTimer = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);

		
		// car/track information
		if (m.getAddress() == messageAddrHeader + "carInfo")		carInfo = m.getArgAsString(0);
		if (m.getAddress() == messageAddrHeader + "track")			trackInfo = m.getArgAsString(0);
		if (m.getAddress() == messageAddrHeader + "layoutLength")	layoutLength = m.getArgAsFloat(0);

		// car status
		if (m.getAddress() == messageAddrHeader + "gear")			gear = m.getArgAsInt32(0);
		if (m.getAddress() == messageAddrHeader + "rpm")			rpm = (int)m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "rpmMax")			rpmMax = (int)m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "speed")			speed = m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "brakeTemp")		brakeTemp = m.getArgAsFloat(0);

		// lap information
		if (m.getAddress() == messageAddrHeader + "completedLaps")	completedLaps = m.getArgAsInt32(0);
		if (m.getAddress() == messageAddrHeader + "laptimeCurrent")	laptimeCurrent = m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "laptimeLast")	laptimeLast = m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "laptimeBest")	laptimeBest = m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "lapProgress")	lapProgress = m.getArgAsFloat(0);

		// control status
		if (m.getAddress() == messageAddrHeader + "throttlePedal")	throttlePedal = m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "brakePedal")		brakePedal = m.getArgAsFloat(0);
		if (m.getAddress() == messageAddrHeader + "clutchPedal")	clutchPedal = m.getArgAsFloat(0);
	}

	// save to rpmFbo
	rpmFbo.begin();
	ofPushMatrix();
	//ofSetHexColor(0xFFFFFF);
	ofSetColor(ofColor::green.getLerped(ofColor::red, ofMap(rpm, 8000, rpmMax, 0, 1)));
	ofNoFill();
	ofTranslate(150, 150);
	ofRotate(ofMap(lapProgress, 0, 1, 0, 360));
	ofDrawLine(50, 0, ofMap(rpm, 0, rpmMax, 50, 150), 0);
	ofPopMatrix();
	rpmFbo.end();

	// save to pixel
	//rpmFbo.readToPixels(rpmPixels);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(54);
	
	drawInputStatus(50, 50);
	drawRpmSpeed(300, 50);
	drawLapTimeInformation(50, 300);
	rpmDrawing(300, 300);
}

void ofApp::drawInputStatus(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);
	ofSetHexColor(0x000000);
	ofDrawRectangle(0, 0, 208, 100);

	ofDrawBitmapStringHighlight("INPUT STATUS \nclutch / brake / throttle", 4, 110);
	
	// draw Clutch
	ofTranslate(40, 10);
	ofSetColor(ofColor::blue);
	ofDrawRectangle(0, ofMap(clutchPedal, 0, 1, 80, 0, true), 20, ofMap(clutchPedal, 0, 1, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofFill();
	ofSetColor(ofColor::red);
	ofDrawRectangle(0, ofMap(brakePedal, 0, 1, 80, 0, true), 20, ofMap(brakePedal, 0, 1, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofFill();
	ofSetColor(ofColor::green);
	ofDrawRectangle(0, ofMap(throttlePedal, 0, 1, 80, 0, true), 20, ofMap(throttlePedal, 0, 1, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofPopStyle();
	ofPopMatrix();
}
void ofApp::drawRpmSpeed(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);
	
	ofFill();
	ofSetColor(ofColor::black);
	ofDrawRectangle(0, 10, 400, 20);
	ofSetColor(ofColor::lightGreen);
	ofDrawRectangle(0, 10, ofMap(rpm, 0, rpmMax, 0, 400), 20);
	ofNoFill();
	ofSetColor(ofColor::white);
	ofDrawRectangle(0, 10, 400, 20);

	ofDrawBitmapStringHighlight(ofToString(speed, 2) + "KPH / " + ofToString(rpm, 0) + " RPM", 0, 50);

	ofPopStyle();
	ofPopMatrix();
}

timeTemplate ofApp::lapT(float seconds) {
	timeTemplate t;
	t.min = (int)seconds / 60;
	t.second = (int)seconds % 60;
	t.millisecond = (int)((seconds - (int)seconds) * 100);

	return t;
}

string ofApp::lapT2String(timeTemplate t) {
	string minStr, secStr, millisStr;
	if (t.min < 10)			minStr = "0" + ofToString(t.min);
	else					minStr = ofToString(t.min);

	if (t.second < 10)		secStr = "0" + ofToString(t.second);
	else					secStr = ofToString(t.second);

	if (t.millisecond < 10)	millisStr = "0" + ofToString(t.millisecond);
	else					millisStr = ofToString(t.millisecond);

	return minStr + ":" + secStr + ":" + millisStr;
}

void ofApp::drawLapTimeInformation(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);

	currentLap = lapT(laptimeCurrent);
	lastLap = lapT(laptimeLast);
	bestLap = lapT(laptimeBest);
	
	ofDrawBitmapStringHighlight("laptimeSeconds : " + ofToString(laptimeCurrent), 10, -10);
	ofDrawBitmapStringHighlight("current lapTime : " + lapT2String(lapT(laptimeCurrent)), 10, 10);
	ofDrawBitmapStringHighlight("   last lapTime : " + lapT2String(lapT(laptimeLast)), 10, 30);
	ofDrawBitmapStringHighlight("   best lapTime : " + lapT2String(lapT(laptimeBest)), 10, 50);
	

	ofPopStyle();
	ofPopMatrix();
}

void ofApp::rpmDrawing(int x, int y) {
	ofPushMatrix();
	ofTranslate(x, y);

	rpmFbo.draw(0, 0);

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ }
//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){ }
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }
