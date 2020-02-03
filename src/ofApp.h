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

#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "PrintSource.h"
#include "AsciiSource.h"
#include "WeaveSource.h"
#include "WeaveSourceTri.h"
#include "VideoSource.h"
#include "SceneManager.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxPiMapper piMapper;

		// By using a custom source that is derived from FboSource
		// you will be able to see the source listed in sources editor
		PrintSource * printSource;
		AsciiSource * asciiSource;
		WeaveSource * weaveSource;
		WeaveSourceTri * weaveSourceTri;
        ofImage dummyObjects;

        SceneManager sceneManager;
};
