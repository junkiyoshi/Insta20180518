#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
	ofSetLineWidth(2);

	this->cap.open(1);
	this->cap_size = cv::Size(320, 180);
	this->face_cascade.load("D:\\opencv-3.4.1\\build\\install\\etc\\haarcascades\\haarcascade_frontalface_default.xml");
	this->gap = ofPoint(0, 0);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->cap >> src;
	cv::resize(src, mini_src, this->cap_size);

	vector<cv::Rect> faces;
	this->face_cascade.detectMultiScale(mini_src, faces);

	if(faces.size() > 0){

		this->gap = ofPoint(ofMap(faces[0].x + faces[0].width / 2, 0, this->cap_size.width, 30, -30), ofMap(faces[0].y, 0, this->cap_size.height, -30, 30));
	}

	cv::imshow("mini_src", mini_src);
	cv::waitKey(1);
}


//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int z = 0; z > -600; z += -20) {

		ofFill();
		ofSetColor(239, ofMap(z, 0, -600, 255, 0));

		ofBeginShape();
		ofVertex(ofGetWidth() * 0.5, ofGetHeight() * 0.5, z);
		ofVertex(-ofGetWidth() * 0.5, ofGetHeight() * 0.5, z);
		ofVertex(-ofGetWidth() * 0.5, -ofGetHeight() * 0.5, z);
		ofVertex(ofGetWidth() * 0.5, -ofGetHeight() * 0.5, z);

		ofNextContour(true);

		ofVertex(ofGetWidth() * 0.47, ofGetHeight() * 0.47, z);
		ofVertex(-ofGetWidth() * 0.47, ofGetHeight() * 0.47, z);
		ofVertex(-ofGetWidth() * 0.47, -ofGetHeight() * 0.47, z);
		ofVertex(ofGetWidth() * 0.47, -ofGetHeight() * 0.47, z);

		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);

		ofBeginShape();
		ofVertex(ofGetWidth() * 0.47, ofGetHeight() * 0.47, z);
		ofVertex(-ofGetWidth() * 0.47, ofGetHeight() * 0.47, z);
		ofVertex(-ofGetWidth() * 0.47, -ofGetHeight() * 0.47, z);
		ofVertex(ofGetWidth() * 0.47, -ofGetHeight() * 0.47, z);
		ofEndShape(true);

		ofTranslate(this->gap.x, this->gap.y);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1920, 1080, OF_WINDOW);
	ofRunApp(new ofApp());
}