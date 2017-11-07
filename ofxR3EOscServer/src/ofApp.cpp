#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	gameData = new SPageGameData();

	datas.setup("$R3E", sizeof(SPageGameData), false);

	clk_start = clock();
	clk_last = clk_start;

	sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
	

	if (!isConnected && ofGetFrameNum() % 300 == 0)		isConnected = datas.connect();

	if (isConnected) {
		gameData = datas.getData();

		/*cout << setw(10) << "gear : " << gameData->gear;
		cout << setw(10) << "RPM : " << gameData->engine_rps * RPS_TO_RPM;
		cout << setw(10) << "SPEED : " << gameData->car_speed * MPS_TO_KPH;
		cout << setw(10) << "PROGRESS : " << ofMap(gameData->lap_distance_fraction, 0, 1, 0, 100, true) << " %" << endl;
		cout << endl;*/
	}

	//sendTelemetryMessage("gear", gameData->gear);
	//sendTelemetryMessage("RPM", gameData->engine_rps * RPS_TO_RPM);
	//sendTelemetryMessage("speed", gameData->car_speed * MPS_TO_KPH);

	sendStringTelemetryMessage("carInfo", ofToString(gameData->vehicle_info.name));
	
	//sendFloatTelemetryMessage("lapDistance", gameData->lap_distance);
	sendStringTelemetryMessage("track", ofToString(gameData->track_name) + " - " + ofToString(gameData->layout_name));
	sendFloatTelemetryMessage("layoutLength", gameData->layout_length);

	sendIntTelemetryMessage("gear", gameData->gear);
	sendFloatTelemetryMessage("rpm", gameData->engine_rps * RPS_TO_RPM);
	sendFloatTelemetryMessage("rpmMax", gameData->max_engine_rps * RPS_TO_RPM);
	sendFloatTelemetryMessage("speed", gameData->car_speed * MPS_TO_KPH);
	sendFloatTelemetryMessage("brakeTemp", (gameData->brake_temp[0] + gameData->brake_temp[1] + gameData->brake_temp[2] + gameData->brake_temp[3] / 4));

	// lap information
	cout << gameData->lap_time_current_self << endl;

	sendIntTelemetryMessage("completedLaps", gameData->completed_laps);
	sendFloatTelemetryMessage("laptimeCurrent", gameData->lap_time_current_self);
	sendFloatTelemetryMessage("laptimeBest", gameData->lap_time_best_self);
	sendFloatTelemetryMessage("laptimeLast", gameData->lap_time_previous_self);

	sendFloatTelemetryMessage("lapProgress", gameData->lap_distance_fraction);

	
	// control information
	sendFloatTelemetryMessage("throttlePedal", gameData->throttle_pedal);
	sendFloatTelemetryMessage("brakePedal", gameData->brake_pedal);
	sendFloatTelemetryMessage("clutchPedal", gameData->clutch_pedal);
}

void ofApp::sendIntTelemetryMessage(string addressEndpoint, int value) {
	ofxOscMessage m;
	m.setAddress("/telemetry/" + addressEndpoint);
	m.addInt32Arg(value);
	sender.sendMessage(m);
}
void ofApp::sendFloatTelemetryMessage(string addressEndpoint, float value) {
	ofxOscMessage m;
	m.setAddress("/telemetry/" + addressEndpoint);
	m.addFloatArg(value);
	sender.sendMessage(m);
}
void ofApp::sendStringTelemetryMessage(string addressEndpoint, string value) {
	ofxOscMessage m;
	m.setAddress("/telemetry/" + addressEndpoint);
	m.addStringArg(value);
	sender.sendMessage(m);
}

void ofApp::sendBoolTelemetryMessage(string addressEndpoint, bool value) {
	ofxOscMessage m;
	m.setAddress("/telemetry/" + addressEndpoint);
	m.addBoolArg(value);
	sender.sendMessage(m);
}




//--------------------------------------------------------------
void ofApp::draw(){
	stringstream ss;
	
	ss << setw(15) << "gear : " << gameData->gear << endl
		<< setw(15) << "RPM : " << ofToString(gameData->engine_rps * RPS_TO_RPM, 0) << endl
		<< setw(15) << "SPEED : " << ofToString(gameData->car_speed * MPS_TO_KPH, 2 ) + " Km/h" << endl
		<< setw(15) << "PROGRESS : " << ofToString(ofMap(gameData->lap_distance_fraction, 0, 1, 0, 100, true), 1) << "%" << endl;

	ofDrawBitmapStringHighlight(ss.str(), 20, 20);
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
