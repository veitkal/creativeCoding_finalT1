/*
	Class drawing and animating different shapes shown through an Ascii-esque filter. 
	Shapes are lines and rectangles, waves and "blips" or small rectangles
*/

#include "AsciiSource.h"

void AsciiSource::setup(){
    name = "AsciiSource";

    allocate(800, 1200);

    setupAscii();

    this->beginFbo();
    ofClear(0,0,0);
    this->endFbo();
}

void AsciiSource::setName(string _name){
    name = _name;
}


void AsciiSource::update(){
    updateAscii();
}

void AsciiSource::reset(){

    startTime = ofGetElapsedTimeMillis();   //initialise time at the start of source

}

void AsciiSource::draw(){
	drawAscii();
	//drawDbg(); //uncomment for debug lines for mapping
}

//================================================================
void AsciiSource::setupAscii() {
	w = fbo->getWidth();
	h = fbo->getHeight();


	posX = 0;
	posY = 0;
	spc1 = h / 12;
	t = ofRandom(1000);
	spacing = 10;
	startPos = spacing / 2;
	l = 0;
	ro = 0;
	offset = 15;
	brs = 0; //brightness
	alphabet = "abcdefghijklmnopqrsuvwxyz";
	symb = "+-\=/_";

	//fbo setup no alpha
	fboRGB.allocate(w, h, GL_RGB);

	//initial clearing of fbo
	fboRGB.begin();
	ofClear(0, 0, 0);
	fboRGB.end();

	//allocating pixels without alpha
	pixels.allocate(w, h, OF_PIXELS_RGB);

	font1.load("a", 28);
	font2.load("a", 30);

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

void AsciiSource::updateAscii(){
	//drawing to fbo
	fboRGB.begin();
	drawToFbo();
	fboRGB.end();

	//loading fbo to pixels
	fboRGB.readToPixels(pixels);




	if (ofGetElapsedTimeMillis() - startTime > 47000) {
		l + -20;
	}
	else {
		l += 20;
	}
}

void AsciiSource::drawAscii(){
	ofClear(0, 0, 0);

	if (ofGetElapsedTimeMillis() - startTime < 24000) {
		//ascii filter 2
		for (int x = 0; x < w; x += spacing * 6) {
			for (int y = 0; y < h; y += spacing * 6) {
				int locX = startPos + x;
				int locY = startPos + y;
				ofColor c = pixels.getColor(x, y);
				brs = c.getBrightness();
				ofSetColor(c);

				float stringIdx = ofMap(brs, 0, 255, 1, symb.length());
				char& ch = symb.at(stringIdx - 1);
				string chars(1, ch);

				//char ch = ofHexToChar(ofToString(ofMap(brs, 0, 255, 4, 39))); //works but haven't found a way to get dec to hex.
				//string chars = ofToString(ch);

				font2.drawString(chars, locX, locY);
			}
		}

	} if (ofGetElapsedTimeMillis() - startTime > 24000) {
		//ascii filter 1
		for (int x = 0; x < w; x += spacing * 4) {
			for (int y = 0; y < h; y += spacing * 4) {
				int locX = x;
				int locY = y;
				ofColor c = pixels.getColor(x, y);
				brs = c.getBrightness();
				ofSetColor(c);

				float stringIdx = ofMap(brs, 0, 255, 1, alphabet.length());
				char& ch = alphabet.at(stringIdx - 1);
				string chars(1, ch);

				//char ch = ofHexToChar(ofToString(ofMap(brs, 0, 255, 4, 39))); //works but haven't found a way to get dec to hex.
				//string chars = ofToString(ch);

				font1.drawString(chars, locX, locY);
			}
		}
	}	
}


//drawings to be filtered
void AsciiSource::drawToFbo() {
	ofClear(0, 0, 0);

	//ofSetColor(255);
	//ofDrawRectangle(0, 0, l, h);


	//ofSetColor(colors[(int)ofRandom(colors.size())]);
	//ofDrawCircle(w / 2, h / 2, sin(l) * 500);

	if (ofGetElapsedTimeMillis() - startTime < 7000) {
		if (ofGetFrameNum() % 3 == 0) {
			ofSetColor(255);
		}
		else {
			ofSetColor(0);
		}

		ofDrawRectangle(0, spc1, spc1 / 4, spc1 - offset);

		//draw blips
		if (ofGetElapsedTimeMillis() - startTime > 3000) {
			
			if (ofGetFrameNum() % 3 == 0) {
				ro = ofRandom(6);
			}

			ofDrawRectangle(0 + (ro*spc1 * 2), spc1 + (ro*spc1), spc1 / 4, spc1 / 2);
			ofDrawRectangle(0 + (ro*spc1 * 3), spc1 + (ro*spc1), spc1 / 4, spc1 / 2);
			ofDrawRectangle(0 + (ro*spc1 * 2.5), spc1 + (ro*spc1), spc1 / 4, spc1 / 2);
			ofDrawRectangle(0 + (ro*spc1 * 3.5), spc1 + (ro*spc1), spc1 / 4, spc1 / 2);
			ofDrawRectangle(0 + (ro*spc1 * 4), spc1 + (ro*spc1), spc1 / 4, spc1 / 2);
			ofDrawRectangle(0 + (ro*spc1 * 2.4), spc1 + (ro*spc1*5), spc1 / 4, spc1 / 2);
			ofDrawRectangle(0 + (ro*spc1 * 3.3), spc1 + (ro*spc1*4.4), spc1 / 4, spc1 / 2);
		}

	}
	else if (ofGetElapsedTimeMillis() - startTime < 30000) {
		//draw waterfall/rect from above
		if (ofGetElapsedTimeMillis() - startTime > 6000 && ofGetElapsedTimeMillis() - startTime < 18000) {
			ofSetColor(255);
			ofDrawRectangle(0, 0, w, cos(l*0.0009)*h);
		}


		if (ofGetElapsedTimeMillis() - startTime > 5000) {
			if (ofGetElapsedTimeMillis() - startTime < 9000) {
				bwSq(sin(l) * 12);
			}
			else {
				bwSq(spc1);
				bwSq(spc1 * 2);
				bwSq(spc1 * 3);
				bwSq(spc1 * 4);
				bwSq(spc1 * 5);
				bwSq(spc1 * 6);
				bwSq(spc1 * 7);
				bwSq(spc1 * 8);
				bwSq(spc1 * 9);
				bwSq(spc1 * 10);
				bwSq(spc1 * 11);
			}
		}
		if (ofGetElapsedTimeMillis() - startTime < 20000 ) {
			if (ofGetElapsedTimeMillis() - startTime > 11000 && ofGetFrameNum() % 160 > 15) {
				for (int i = 0; i < h / 2; i += spc1) {
					sines(i, i);
				}
			}
			else if (ofGetElapsedTimeMillis() - startTime > 11000 && ofGetFrameNum() % 160 < 15) {
				for (int i = h / 2; i < h; i += spc1) {
					sines(i, i);
				}
			}
		}

		if (ofGetElapsedTimeMillis() - startTime > 17000 && ofGetElapsedTimeMillis() - startTime < 19000) {
			for (int i = 0; i < h; i += spc1) {
				sines(i, i);
			}
		}

	}  //noisy wave
	else if (ofGetElapsedTimeMillis() - startTime < 53000) {
		wave(0.0001, 7);
		if (ofGetElapsedTimeMillis() - startTime > 45000) {
			wave(0.002, 7);
		}
	}
	//extraTransition
	if (ofGetElapsedTimeMillis() - startTime > 29000 && ofGetElapsedTimeMillis() - startTime < 34000) {
		for (int i = 0; i < h; i += spc1) {
			sines(i, i);
		}
	}
}

void AsciiSource::sines(float yOff, float sOff) {
	int size = 20;
	if (ofGetElapsedTimeMillis() - startTime < 29000) {
		ofSetColor(255);
	}
	else {
		ofSetColor(colors[(int)ofRandom(colors.size())]);
	}
	//
	for (int i = 0; i < w; i+=size) {
		float y = ofMap(sin(ofGetFrameNum()+sOff * 0.007) * i,0, w, 0,spc1);
		ofDrawRectangle(i, y + yOff, size, size);
	}
}

//line rects
void AsciiSource::bwSq(float offY) {
	if (ofGetElapsedTimeMillis() - startTime < 17000) {
		if (ofGetFrameNum() % 41 == 1) {
			ro = ofRandom(2);
		}
	} else {
		ro = 1;
	}
	ofPushMatrix();
	ofPushStyle();
	ofSetColor(sin(l*0.002) * 255);
	if (ofGetElapsedTimeMillis() - startTime > 20000) {
		ofSetColor(colors[(int)ofRandom(colors.size())]);
	}
	ofTranslate(0, 30);

	ofDrawRectangle(posX, offY*ro, spc1 + sin(l + offY * 0.0002)*w, spc1 / 2);
	ofPopMatrix();
	ofPopStyle();

	posX += spc1;
	if (posX >= w) {
		posX = 0;
		//posY += spc1;
	}

	if (posY >= h) {
		posX = 0;
		posY = 0;
	}

}

//Noisy waveform with nested noise/sine functions
void AsciiSource::wave(float t, float off) {
	float tp = ofNoise(l*t);
	ofSetColor(colors[(int)ofRandom(colors.size())]);
	for (int i = 0; i < w; i++) {
		ofDrawLine(i, 0, i, sin(l + i * tp)*h);

	}
	t += 0.01;
}

//Drawing debug lines for mapping
void AsciiSource::drawDbg() {

	ofSetColor(255, 0, 0);

	for (int i = 0; i < h; i += spc1) {
		ofDrawLine(0, i, w, i);
	}

}

