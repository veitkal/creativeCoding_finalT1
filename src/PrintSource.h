#pragma once

#include "ofMain.h"
#include "FboSource.h"

class PrintSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);

		void reset();
		void setupPrint();
		void updatePrint();
		void drawFirstPrint();
		void drawPrint();
		void drawPrint2();
		void drawDbg();


		float posX, posY, posXX, posYY, spc1, spc2, w, h, t, t2, l, prob;
        int startTime;

		vector <ofColor> colors;
};
