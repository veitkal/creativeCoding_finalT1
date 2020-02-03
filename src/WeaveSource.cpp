/*
	Class drawing either lines over checker board pattern or triangles moving in oposit directions over each whole step of the stairs,
	run through a pixel-esque filter.
	Inspired by classic weaving patterns, that is the actuall esthetics of the printet patterns to be woven.
*/

#include "WeaveSource.h"

void WeaveSource::setup(){
    name = "WeaveSource";

    allocate(1000, 500);

    setupWeave();

    this->beginFbo();
    ofClear(0,0,0);
    this->endFbo();
}

void WeaveSource::selectShape(bool _shape) {
	shape = _shape;
}

void WeaveSource::setName(string _name){
    name = _name;
}


void WeaveSource::update(){
    updateWeave();
}

void WeaveSource::reset(){

    startTime = ofGetElapsedTimeMillis();   //initialise time at the start of source

}

void WeaveSource::draw(){
	drawWeave();
	//drawDbg(); //uncomment for debug lines for mapping
}

void WeaveSource::setupWeave() {
	w = fbo->getWidth();
	h = fbo->getHeight();

	//init of variables 
	spc1 = h / 12;
	spc2 = h / 6;
	num = 10;
	len = w / num;
	x1 = 0;
	x2 = len;
	x3 = 0;
	y1 = 0;
	y2 = spc2 / 2;
	y3 = spc2;
	t = h;
	s = 0;

	colorC = ofColor(255);

	spacing = 7;
	startPos = spacing / 2;
	brs = 0; //brightness

	shape = 1; //set shape  - 0 for triangles, 1 for lines

	//fbo setup no alpha
	fboRGB.allocate(w, h, GL_RGB);

	//initial clearing of fbo
	fboRGB.begin();
	ofClear(0, 0, 0);
	fboRGB.end();

	//allocating pixels without alpha
	pixels.allocate(w, h, OF_PIXELS_RGB);

	//adding colors form fav vim/term color scheme 'base 16 tomorrow nigth' by chriskempson
	//order: red, orange, yellow, green, aqua, blue, purple 
	colors.push_back(ofColor(204, 102, 102));
	colors.push_back(ofColor(222, 147, 95));
	colors.push_back(ofColor(240, 198, 116));
	colors.push_back(ofColor(181, 189, 104));
	colors.push_back(ofColor(138, 190, 183));
	colors.push_back(ofColor(129, 162, 190));
	colors.push_back(ofColor(178, 148, 187));

	//adding locations for triangles into vectors
	for (int i = 0; i < w + len; i += len) {
		ofVec2f loc1, loc2, loc3;
		loc1.set(x1 + i, y1);
		loc2.set(x2 + i, y2);
		loc3.set(x3 + i, y3);

		lx1.push_back(loc1);
		lx2.push_back(loc2);
		lx3.push_back(loc3);
		lxVel.push_back(ofRandom(-20, 20));
	}
}

void WeaveSource::updateWeave(){
	//drawing to fbo
	fboRGB.begin();
	drawToFbo();
	fboRGB.end();

	//loading fbo to pixels
	fboRGB.readToPixels(pixels);

	x1 += 5;
	x2 += 5;
	x3 += 5;

	if (x1 > w) {
		x1 = 0 - len;
		x2 = 0;
		x3 = 0 - len;
	}

	//updating start positions and locations, adding movement & checking for edges
	if (shape == 0) {
		for (int i = 0; i < lx1.size(); i++) {
			if (ofGetElapsedTimeMillis() - startTime < 15000) {
				if (lx1[i].x > w) {
					lx1[i].x = 0 - len;
					lx2[i].x = 0;
					lx3[i].x = 0 - len;
				}
			}
			if (ofGetElapsedTimeMillis() - startTime < 2000) {
				lx1[i].x = 0 - len;
				lx2[i].x = 0;
				lx3[i].x = 0 - len;
			}
			if (ofGetElapsedTimeMillis() - startTime > 6000 && ofGetFrameNum() % 60 > 0 && ofGetFrameNum() % 60 < 30 && ofGetElapsedTimeMillis() - startTime < 15000) {
				lx1[i].x += lxVel[i];
				lx2[i].x += lxVel[i];
				lx3[i].x += lxVel[i];
			}
			else {
				lx1[i].x += 10;
				lx2[i].x += 10;
				lx3[i].x += 10;
			}
		}
	}
	else if (shape == 1) {
		if (ofGetElapsedTimeMillis() - startTime > 2000 && ofGetFrameNum() % 8 == 0) {
			t -= spc1;
		}
		for (int i = 0; i < lx1.size(); i++) {
			if (ofGetElapsedTimeMillis() - startTime < 15000) {
				if (lx1[i].x > w) {
					lx1[i].x = 0 - len;
					lx2[i].x = 0;
					lx3[i].x = 0 - len;
				}
			}
			if (ofGetElapsedTimeMillis() - startTime < 9000) {
				lx1[i].x = 0 - len;
				lx2[i].x = 0;
				lx3[i].x = 0 - len;
			}
			if (ofGetElapsedTimeMillis() - startTime > 13000 && ofGetFrameNum() % 60 > 0 && ofGetFrameNum() % 60 < 40 && ofGetElapsedTimeMillis() - startTime < 18000) {
				lx1[i].x += lxVel[i];
				lx2[i].x += lxVel[i];
				lx3[i].x += lxVel[i];
			}
			else {
				lx1[i].x += 15;
				lx2[i].x += 15;
				lx3[i].x += 15;
			}

		}
	}
}

void WeaveSource::drawWeave(){
	ofClear(0, 0, 0);

	////pixel filter
	for (int x = 0; x < w; x += spacing) {
		for (int y = 0; y < h; y += spacing) {
			int locX = x;
			int locY = y;
			ofColor c = pixels.getColor(x, y);
			brs = c.getBrightness();
			ofSetColor(c);
			ofDrawRectangle(locX, locY, spacing - 2, spacing - 2);
		}
	}
}

//drawings to be filtered
void WeaveSource::drawToFbo() {
	ofClear(0, 0, 0);
	ofSetColor(255);

	if (ofGetElapsedTimeMillis() - startTime > 2000) {
		if (shape == 0) {
			//drawing of triangles along each steps
			drawTriangles(colors[0]);
		}
		else {
			//drawing lines function looping over the height, setting the y position at each top/front area
			//checking if i is odd or even and inverting the colour.
			for (int i = 0; i < h; i += spc1) {
				linePattern(i, ofColor(255), i % 2);
			}
			ofSetColor(0);
			ofDrawRectangle(0, 0, w, t);
		}

		//growing bars slides over steps in black and white
		if (ofGetElapsedTimeMillis() - startTime > 21000) {
			for (int i = 0; i < h; i += spc1) {
				bars(ofColor(colorC*(i % 2)), i, 0);
			}
		}

		if (ofGetElapsedTimeMillis() - startTime > 23000) {
			for (int i = 0; i < h; i += spc1) {
				bars(ofColor(0), i + spc1, w*1.5);
			}
		}

		if (ofGetElapsedTimeMillis() - startTime > 25000) {
			for (int i = 0; i < h; i += spc1) {
				bars(ofColor(colorC*(i % 2)), i + spc1, w*4);
			}
		}

		if (ofGetElapsedTimeMillis() - startTime > 28000) {
			for (int i = 0; i < h; i += spc1) {
				bars(ofColor(ofColor(0)), i, w*7);
			}
		}
	}

}

//drawing checkerboard like patter with overlapping  vertical lines, inverted for each half step of the stairs.
void WeaveSource::linePattern(float posY, ofColor c, bool invert) {
	if (invert) {
		//Invert
       //backgroundRect
		ofSetColor(c);
		ofDrawRectangle(0, posY, w, spc1);
		//black rectangles
		for (int i = spc1 * 2; i < w - spc1 * 2; i += spc1 * 2) {
			ofRectMode(CENTER);
			ofSetColor(0);
			ofDrawRectangle(i, posY, spc1, spc1);
		}
		//looping lines
		ofSetColor(0);
		for (int i = 0; i < lx1.size(); i++) {
			ofSetColor(0);
			ofDrawRectangle(lx1[i].x, posY, 10, spc1);
			ofDrawRectangle(lx1[i].x + 10, posY, 10, spc1);
		}
	}
	else {
		//backgroundRect
		ofSetColor(0);
		ofDrawRectangle(0, posY, w, spc1);
		//colored rectangles
		for (int i = spc1 * 2; i < w - spc1 * 2; i += spc1 * 2) {
			ofRectMode(CENTER);
			ofSetColor(c);
			ofDrawRectangle(i, posY, spc1, spc1);
		}
		//looping lines
		ofSetColor(0);
		for (int i = 0; i < lx1.size(); i++) {
			ofSetColor(c);
			ofDrawRectangle(lx1[i].x, posY, 10, spc1);
			ofDrawRectangle(lx1[i].x + 20, posY, 10, spc1);

		}
	}
}

//bars covering one area of a step. 
void WeaveSource::bars(ofColor c, float yOff, float sOff) {
	ofSetColor(c);
	ofDrawRectangle(0, yOff, spc1 * 2 + s - sOff, spc1);

	s++;
}

void WeaveSource::triangl(float x1, float x2, float x3, float yoff) {
	//animated triangles, moving sideways
	ofBeginShape();
	ofVertex(x1, y1 + yoff);
	ofVertex(x2, y2 + yoff);
	ofVertex(x3, y3 + yoff);
	ofEndShape();
}

void WeaveSource::drawTriangles(ofColor c) {
	//drawing triangles along each step, looping through the vector. flipped on every other step
	for (int i = 0; i < lx1.size(); i++) {
		ofSetColor(c);
		triangl(lx1[i].x, lx2[i].x, lx3[i].x, 0);
	}

	ofPushMatrix();
	ofTranslate(w, spc1 * 6);
	ofRotateDeg(180);
	for (int i = 0; i < lx1.size(); i++) {
		triangl(lx1[i].x, lx2[i].x, lx3[i].x, spc1 * 2);
	}
	ofPopMatrix();

	for (int i = 0; i < lx1.size(); i++) {
		triangl(lx1[i].x, lx2[i].x, lx3[i].x, spc1 * 4);
	}

	ofPushMatrix();
	ofTranslate(w, spc1 * 10);
	ofRotateDeg(180);
	for (int i = 0; i < lx1.size(); i++) {
		triangl(lx1[i].x, lx2[i].x, lx3[i].x, spc1 * 2);
	}
	ofPopMatrix();

	for (int i = 0; i < lx1.size(); i++) {
		triangl(lx1[i].x, lx2[i].x, lx3[i].x, spc1 * 8);
	}

	ofPushMatrix();
	ofTranslate(w, spc1 * 14);
	ofRotateDeg(180);
	for (int i = 0; i < lx1.size(); i++) {
		triangl(lx1[i].x, lx2[i].x, lx3[i].x, spc1 * 2);
	}
	ofPopMatrix();
}

//Drawing debug lines for mapping
void WeaveSource::drawDbg() {

	ofSetColor(255, 0, 0);

	for (int i = 0; i < h; i += spc1) {
		ofDrawLine(0, i, w, i);
	}

}

