#pragma once

#include "ofMain.h"
#include "ofxSquashBuddies.h"
#include "ofxDepth.h"

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
    
    ofEasyCam cam;
		
    ofxSquashBuddies::Receiver receiver[3];
    ofShortPixels pixels;
    ofxDepth depth;
    ofTexture tex[3];
    ofBufferObject pntObj[3];
    ofVbo pntVbo[3];
    msa::OpenCLBuffer points[3];
    ofVec4f floor[3];
    ofMatrix4x4 floorTransform[3];
};
