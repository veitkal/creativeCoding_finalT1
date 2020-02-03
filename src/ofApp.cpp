/*
	A projection mapping project developed for projecting a staircase. 
	The piece is drawing from and is aspiring to highlight the historical and technical 
	connection between digital and analogue weaving technologies. 
	One part is founded on ascii art and cli esthetics, 
	the second is trying to emulate and animate two classic weaving patterns,
	the third one takes of from the classic Commodor 64 basic program 'PRINT CHR$(205.5+RND(1)); : GOTO 10'.

	Built by Jakob Jennerholm Hammar 
	for IS71014B: Workshops In Creative Coding 1, term 1 final project 
	Goldsmiths University of London, 
	January 2019
*/

#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
    ofSetFrameRate(60);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	printSource = new PrintSource();
	printSource->setup();
	piMapper.registerFboSource(printSource);

	asciiSource = new AsciiSource();
	asciiSource->setup();
	piMapper.registerFboSource(asciiSource);

	weaveSource = new WeaveSource();
	weaveSource->setup();
	piMapper.registerFboSource(weaveSource);

	weaveSourceTri = new WeaveSourceTri();
	weaveSourceTri->setup();
	piMapper.registerFboSource(weaveSourceTri);
	



    
	piMapper.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();
	
	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

    dummyObjects.load("stairsFront.png");

    //setup sceneManager to handle scene/present changes automatically
    sceneManager.setup("scenes.json", &piMapper);
}
//-----------------------------------------------------------
void ofApp::update(){
	//if (ofGetElapsedTimeMillis() >= (3 * 60 * 1000 - 20000)) ofExit();

	piMapper.update();
    sceneManager.update();
}
//-----------------------------------------------------------
void ofApp::draw(){
    //dummyObjects.draw(200,200);
    piMapper.draw();
}
//-----------------------------------------------------------
void ofApp::keyPressed(int key){
    //press 5 to go to previous preset (scene)
    if (key=='5') {
        if (piMapper.getNumPresets()>1){
            int targetScene = piMapper.getActivePresetIndex() - 1;
            if (targetScene<0) targetScene = piMapper.getNumPresets()-1;
            piMapper.setPreset(targetScene);
            cout << "Switched to preset: " << piMapper.getActivePresetIndex() << endl;
        } else cout << "only one preset available" << endl;
    }
    //press 6 to go to next preset (scene)
    else if (key=='6') {
        if (piMapper.getNumPresets()>1){
            piMapper.setNextPreset();
            cout << "Switched to preset: " << piMapper.getActivePresetIndex() << endl;
        } else cout << "only one preset available" << endl;
    }
    else if (key == '7'){
        piMapper.cloneActivePreset();
        piMapper.setPreset(piMapper.getNumPresets()-1);
        cout << "Cloned and switched to preset: " << piMapper.getActivePresetIndex() << endl;
    }

	piMapper.keyPressed(key);
}
//-----------------------------------------------------------
void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}
//-----------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}
//-----------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}
//-----------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}
