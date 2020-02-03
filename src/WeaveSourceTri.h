#pragma once

#include "ofMain.h"
#include "FboSource.h"

class WeaveSourceTri : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string _name);

		void selectShape(bool _shape);
		void reset();
		void setupWeave();
		void updateWeave();
		void drawWeave();
		void drawDbg();
		void drawToFbo();
		void bars();
		void linePattern(float posY, ofColor c, bool invert);
		void drawTriangles(ofColor c);
		void triangl(float x1, float x2, float x3, float y);



		float spc1, spc2, spacing, startPos, w, h, t, brs, x1, x2, x3, y1, y2, y3, len;
		int startTime, num;

		vector<ofVec2f> lx1;
		vector<ofVec2f> lx2;
		vector<ofVec2f> lx3;
		vector<float> lxVel;

		bool shape;

		ofFloatPixels pixels;

		ofFbo fboRGB;

		vector <ofColor> colors;

};
