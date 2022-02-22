#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);

	// 配色デザイン P092 ビビットイエロー
	this->color_palette.push_back(ofColor(255, 240, 0));
	this->color_palette.push_back(ofColor(245, 217, 51));
	this->color_palette.push_back(ofColor(232, 229, 0));
	this->color_palette.push_back(ofColor(250, 229, 51));
	this->color_palette.push_back(ofColor(231, 180, 33));
	this->color_palette.push_back(ofColor(255, 255, 255));
	this->color_palette.push_back(ofColor(215, 131, 76));
	this->color_palette.push_back(ofColor(138, 196, 221));

	// 配色デザイン ビビッドレッド P038
	this->color_palette.push_back(ofColor(197, 0, 24));
	this->color_palette.push_back(ofColor(184, 12, 65));
	this->color_palette.push_back(ofColor(206, 97, 110));
	this->color_palette.push_back(ofColor(204, 85, 68));
	this->color_palette.push_back(ofColor(190, 145, 176));
	this->color_palette.push_back(ofColor(215, 130, 63));
	this->color_palette.push_back(ofColor(255, 241, 51));
	this->color_palette.push_back(ofColor(107, 182, 187));

	// 配色デザイン ビビットパープル P168
	this->color_palette.push_back(ofColor(109, 23, 129));
	this->color_palette.push_back(ofColor(75, 83, 158));
	this->color_palette.push_back(ofColor(132, 93, 159));
	this->color_palette.push_back(ofColor(66, 35, 128));
	this->color_palette.push_back(ofColor(200, 64, 114));
	this->color_palette.push_back(ofColor(0, 160, 158));
	this->color_palette.push_back(ofColor(215, 130, 63));
	this->color_palette.push_back(ofColor(0, 0, 0));
}


//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto span = 120;
	auto radius = 55;
	auto deg_span = 20;
	int index = 0;
	for (auto x = span * 0.5; x < ofGetWidth(); x += span) {

		int color_range_start = (index / 2) * 8;
		int color_range_end = color_range_start + 8;

		for (auto y = span * 0.5; y < ofGetHeight(); y += span) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (auto deg = 0; deg < 360; deg += deg_span) {

				auto noise_radius = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.02), 0, 1, radius * 0.25, radius);
				vector<glm::vec2> vertices;
				vector<glm::vec2> noise_vertices;
				for (auto tmp_deg = deg; tmp_deg <= deg + deg_span; tmp_deg++) {

					vertices.push_back(glm::vec2(radius * cos(tmp_deg * DEG_TO_RAD), radius * sin(tmp_deg * DEG_TO_RAD)));
					if (tmp_deg > deg + 2 && tmp_deg < deg + deg_span - 2) {

						noise_vertices.push_back(glm::vec2(noise_radius * cos(tmp_deg * DEG_TO_RAD), noise_radius * sin(tmp_deg * DEG_TO_RAD)));
					}
				}

				vertices.push_back(glm::vec2());
				noise_vertices.push_back(glm::vec2());

				int color_index_1 = ofRandom(color_range_start, color_range_end);
				int color_index_2 = ofRandom(color_range_start, color_range_end);

				ofSetColor(this->color_palette[color_index_1]);
				ofFill();
				ofBeginShape();
				ofVertices(noise_vertices);
				ofEndShape(true);

				ofSetColor(this->color_palette[color_index_2]);
				ofNoFill();
				ofBeginShape();
				ofVertices(noise_vertices);
				ofEndShape(true);
			}

			ofPopMatrix();
		}

		index++;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}