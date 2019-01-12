#pragma once

#include "ofMain.h"
#include "ofxEasyFft.h"

#define WIDTH 256
#define HEIGHT 256
#define NUM_PARTICLES HEIGHT * WIDTH

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
//    ofxEasyFft fft;
    
    //------naru------
    ofSoundPlayer music;
    ofVbo myVbo;
    ofVec3f myVerts[NUM_PARTICLES];
    ofFloatColor myColor[NUM_PARTICLES];
    
    vector<vector<float>> fftHistory;
    int nBandsToGet;
    int initialBufferSize;
    // pause
    bool is_pause = false;
    
    // movie
    ofVideoPlayer movie;
    double movieWidth;
    double movieHeight;
    ofEasyCam cam;
    
};
