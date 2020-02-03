#pragma once

#include "ofMain.h"
#include "FboSource.h"

class AsciiSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);

		void reset();
		void setupAscii();
		void updateAscii();
		void drawAscii();
		void sines(float yOff, float sOff);
		void drawDbg();
		void drawToFbo();
		void bwSq(float offY);
		void wave(float t, float off);



		float posX, posY, spc1, spacing, startPos, ro, w, h, t, l, brs, offset;
		int startTime;
		string alphabet;
		string symb;

		ofTrueTypeFont font1, font2;
		ofFloatPixels pixels;

		ofFbo fboRGB;

		vector <ofColor> colors;

};
