/*
	A projection mapping project developed for projecting a staircase.
	The piece is drawing from and is aspiring to highlight the historical and technical
	connection between digital and analogue weaving technologies.
	One part is founded on ascii art and cli esthetics,
	the second part is a continuation from the classic Commodor 64 basic program 'PRINT CHR$(205.5+RND(1)); : GOTO 10'.
	and the third is trying to emulate and animate two classic weaving patterns,


	Built by Jakob Jennerholm Hammar
	for IS71014B: Workshops In Creative Coding 1, term 1 final project
	Goldsmiths University of London,
	January 2019
*/


#include "PrintSource.h"

void PrintSource::setup(){
    name = "PrintSource";

    allocate(800, 1200);

    setupPrint();

    this->beginFbo();
    ofClear(255,0,0);
    this->endFbo();
}

void PrintSource::setName(string _name){
    name = _name;
}


void PrintSource::update(){
    updatePrint();
}

void PrintSource::reset(){

    startTime = ofGetElapsedTimeMillis();   //initialise time at the start of source

}

void PrintSource::draw(){
	drawPrint();
//drawDbg(); //uncomment for debug lines for mapping
}

//================================================================
void PrintSource::setupPrint() {
	//initializing some variables
	w = fbo->getWidth();
	h = fbo->getHeight();
	posX = 0;
	posY = 0;
	spc1 = h / 12; //setting size/spacing of the screen according to the number of areas of the stairs. That is two for each step of which there are six.

	t2 = 0.001;
	t = ofRandom(1000);
	l = 0;
	prob = 0.5;

	//adding colors form fav vim/term color scheme 'base 16 tomorrow nigth' by chriskempson
	//order: red, orange, yellow, green, aqua, blue, purple 
	colors.push_back(ofColor(204, 102, 102));
	colors.push_back(ofColor(222, 147, 95));
	colors.push_back(ofColor(240, 198, 116));
	colors.push_back(ofColor(181, 189, 104));
	colors.push_back(ofColor(138, 190, 183));
	colors.push_back(ofColor(129, 162, 190));
	colors.push_back(ofColor(178, 148, 187));

}

void PrintSource::updatePrint(){
	//scroll / animate forward
	if (ofGetElapsedTimeMillis() - startTime > 0 && ofGetElapsedTimeMillis() - startTime < 4200) {
		posX += spc1;
		if (posX >= w) {
			posX = 0;
			posY += spc1;
		}

		if (posY >= h) {
			posX = 0;
			posY = 0;
		}
	}
	else if (ofGetElapsedTimeMillis() - startTime > 4200 && ofGetElapsedTimeMillis() - startTime < 5000) { //scroll backward
		posX -= spc1;

		if (posX <= 0 - spc1) {
			posX = w - spc1;
			posY -= spc1;
		}
		if (posY <= 0 - spc1) {
			posX = w;
			posY = h - spc1;
		}
	}
	else {
		posX += spc1;

		if (posX >= w) {
			posX = 0;
			posY += spc1;
		}

		if (posY >= h) {
			posX = 0;
			posY = 0;
		}
	}

	posXX -= spc1;

	if (posXX <= 0 - spc1) {
		posXX = w;
		posYY -= spc1;
	}
	if (posYY <= 0 - spc1) {
		posXX = w;
		posYY = h - spc1;
	}

	t += t2;
	t2 += 0.0005;


}

void PrintSource::drawPrint(){
	
	float ns = ofNoise(t);

	//switch between auto updated background/cleared screen
	if (ofGetElapsedTimeMillis() - startTime > 0 && ofGetElapsedTimeMillis() - startTime < 5000) {
		ofClear(0, 0, 0);
	}
	

	//draw simple 10print
	if (ofGetElapsedTimeMillis() - startTime > 0 && ofGetElapsedTimeMillis() - startTime < 30000) {
		ofSetColor(0);
		ofDrawRectangle(posX, posY, spc1, spc1);
		if (ns > 0.5) {
			ofSetColor(255);
			ofDrawLine(posX, posY, posX + spc1, posY + spc1);
		}
		else {
			ofSetColor(255);
			ofDrawLine(posX, posY + spc1, posX + spc1, posY);
		}
	}

	//setting some colours at the right time
	if (ofGetElapsedTimeMillis() - startTime > 20000 && ofGetElapsedTimeMillis() - startTime < 30000) {
		ofSetColor(colors[(int)ofRandom(colors.size())]);
	}

	//draw quadra 10print
	if (ofGetElapsedTimeMillis() - startTime > 12000 && ofGetElapsedTimeMillis() - startTime < 30000) {
		if (ns < 0.25) {
			ofDrawLine(posX, posY, posX + spc1, posY);
		}
		else if (ns < 0.5) {
			ofDrawLine(posX, posY + spc1, posX + spc1, posY + spc1);
		}
		else if (ns < 0.85) {
			ofDrawLine(posX, posY, posX, posY + spc1);
		}
		else {
			ofDrawLine(posX + spc1, posY, posX + spc1, posY + spc1);
		}

	}

	//draw white squares
	if (ofGetElapsedTimeMillis() - startTime > 17000 && ofGetElapsedTimeMillis() - startTime < 25000) {
		if (ns > 0.5) {

			ofSetColor(255);
			ofDrawRectangle(posX, posY, spc1, spc1);
		}
		else {

			ofSetColor(255);
			ofDrawLine(posX, posY + spc1, posX + spc1, posY);
		}
	}

	//draw triangle shapes
	if (ofGetElapsedTimeMillis() - startTime > 25000 && ofGetElapsedTimeMillis() - startTime < 27000) {
		ofSetColor(colors[(int)ofRandom(colors.size())]);
		if (ofRandom(1) > 0.7) {

			ofBeginShape();
			ofVertex(posX, posY);
			ofVertex(posX, posY + spc1);
			ofVertex(posX + spc1, posY + spc1);
			ofEndShape();
		}
		else if (ofRandom(1) > 0.7) {
			ofBeginShape();
			ofVertex(posX, posY);
			ofVertex(posX + spc1, posY);
			ofVertex(posX + spc1, posY + spc1);
			ofEndShape();
		}
	}

	//draw black blimps
	if (ofGetElapsedTimeMillis() - startTime > 25000 && ofGetElapsedTimeMillis() - startTime < 35000) {
		if (ofRandom(1) < 0.1) {
			ofSetColor(0);
			ofDrawRectangle(posX, posY, spc1, spc1);
			ofDrawLine(posX, posY, posX + spc1, posY);
		}
		else if (ofRandom(1) < 0.2) {
			ofSetColor(0);
			ofDrawRectangle(posX, posY, spc1, spc1);
			ofDrawLine(posX, posY + spc1, posX + spc1, posY + spc1);
		}
		else if (ofRandom(1) < 0.3) {
			ofSetColor(0);
			ofDrawRectangle(posX, posY, spc1, spc1);
			ofDrawLine(posX, posY, posX, posY + spc1);
		}
		else {
			ofSetColor(0);
			ofDrawRectangle(posX, posY, spc1, spc1);
			ofDrawLine(posX + spc1, posY, posX + spc1, posY + spc1);
		}

	}



	//draw coloured blimpLines
	if (ofGetElapsedTimeMillis() - startTime > 23000 && ofGetElapsedTimeMillis() - startTime < 33000) {
		ofSetColor(colors[(int)ofRandom(colors.size())], 200);
		if (ofRandom(1) < 0.1) {
			//ofSetColor(0);
			//ofDrawRectangle(posXX, posYY, spc1, spc1);
			ofDrawLine(posXX, posYY, posXX + spc1, posYY);
		}
		else if (ofRandom(1) < 0.2) {
			ofSetColor(0);
			//ofDrawRectangle(posXX, posYY, spc1, spc1);
			ofDrawLine(posXX, posYY + spc1, posXX + spc1, posYY + spc1);
		}
		else if (ofRandom(1) < 0.3) {
			//ofSetColor(0);
			//ofDrawRectangle(posXX, posYY, spc1, spc1);
			ofDrawLine(posXX, posYY, posXX, posYY + spc1);
		}
		else {
			//ofSetColor(0);
			//ofDrawRectangle(posXX, posYY, spc1, spc1);
			ofDrawLine(posXX + spc1, posYY, posXX + spc1, posYY + spc1);
		}

	}

	//draw triangle shapes
	if (ofGetElapsedTimeMillis() - startTime > 30000 && ofGetElapsedTimeMillis() - startTime < 38000) {
		ofSetColor(colors[(int)ofRandom(colors.size())]);
		if (ofGetElapsedTimeMillis() - startTime > 30000) {
			prob = 0.5;
			if (ofRandom(1) > prob) {
				ofBeginShape();
				ofVertex(posX, posY);
				ofVertex(posX, posY + spc1);
				ofVertex(posX + spc1, posY + spc1);
				ofEndShape();
			}
			else if (ofRandom(1) > prob) {
				ofBeginShape();
				ofVertex(posX, posY);
				ofVertex(posX + spc1, posY);
				ofVertex(posX + spc1, posY + spc1);
				ofEndShape();
			}
			else {
				ofBeginShape();
				ofVertex(posX, posY);
				ofVertex(posX + spc1, posY);
				ofVertex(posX + spc1, posY + spc1);
				ofVertex(posX + spc1, posY);
				ofEndShape();
			}
		}
		else if (ofGetElapsedTimeMillis() - startTime > 35000) {
			ofBeginShape();
			ofVertex(posX, posY);
			ofVertex(posX + spc1, posY);
			ofVertex(posX + spc1, posY + spc1);
			ofVertex(posX + spc1, posY);
			ofEndShape();
		}
		else {
			prob = 0.9;


			if (ofRandom(1) > prob) {
				ofBeginShape();
				ofVertex(posX, posY);
				ofVertex(posX, posY + spc1);
				ofVertex(posX + spc1, posY + spc1);
				ofEndShape();
			}
			else if (ofRandom(1) > prob) {
				ofBeginShape();
				ofVertex(posX, posY);
				ofVertex(posX + spc1, posY);
				ofVertex(posX + spc1, posY + spc1);
				ofEndShape();
			}
		}
	}

	//draw coloured squares
	if (ofGetElapsedTimeMillis() - startTime > 35000 && ofGetElapsedTimeMillis() - startTime < 44000) {
		ofSetColor(colors[(int)ofRandom(colors.size())]);
		ofDrawRectangle(posX, posY, spc1, spc1);
	}


	//draw coloured bars
	if (ofGetElapsedTimeMillis() - startTime > 44000 && ofGetElapsedTimeMillis() - startTime < 54990) {

		ofPushStyle();
		ofPushMatrix();
		ofSetColor(colors[0]);
		if (ofGetFrameNum() % 12 == 0) { //pick random color and translate
			ofSetColor(colors[(int)ofRandom(colors.size())]);
			ofTranslate(0, l);
			l += spc1;
		}
		ofDrawRectangle(0, 0, w, spc1);
		ofPopMatrix();

		if (l > h + spc1) { //rerun, go back to top and loop
			l = 0;
		}
		ofPopStyle();

	}



	//draw bars black step by step
	if (ofGetElapsedTimeMillis() - startTime == 50000) {
		l = 0;
		ofSetColor(0);
	}
	if (ofGetElapsedTimeMillis() - startTime > 50100) {
		ofSetColor(0);
		ofPushMatrix();
		if (ofGetFrameNum() % 12 == 0) {
			ofSetColor(0);
			ofTranslate(0, l);
			l += spc1;
		}
		ofDrawRectangle(0, 0, w, spc1);
		ofPopMatrix();

		if (l > h + spc1) {
			l = 0;
		}

	}
}



//Drawing debug lines for mapping
void PrintSource::drawDbg() {

	ofSetColor(255, 0, 0);

	for (int i = 0; i < h; i += spc1) {
		ofDrawLine(0, i, w, i);
	}

}

