#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	gameData = new SPageGameData();

	datas.setup("$R3E", sizeof(SPageGameData), false);

	clk_start = clock();
	clk_last = clk_start;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!isConnected && ofGetFrameNum() % 300 == 0)		isConnected = datas.connect();

	if (isConnected) {
		gameData = datas.getData();

		cout << setw(10) << "gear : " << gameData->gear;
		cout << setw(10) << "RPM : " << gameData->engine_rps * RPS_TO_RPM;
		cout << setw(10) << "SPEED : " << gameData->car_speed * MPS_TO_KPH;
		cout << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
