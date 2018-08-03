#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    cam.setupPerspective();
    cam.setFarClip(20000);

    receiver[0].init(4444);
    receiver[1].init(4445);
    receiver[2].init(4446);
    
    depth.setup(0, 0);
    
    for (int i=0; i<3; i++) {
        floorTransform[i].makeIdentityMatrix();
        pntObj[i].allocate(512*424*sizeof(ofVec4f), GL_STREAM_DRAW);
        pntVbo[i].setVertexBuffer(pntObj[i], 3, sizeof(ofVec4f), 0);
        points[i].initFromGLObject(pntObj[i].getId());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<3; i++) {
        receiver[i].update();
        if (receiver[i].isFrameNew()) {
            ofxSquashBuddies::Message & msg = (ofxSquashBuddies::Message&)receiver[i].getMessage();
            const ofxSquashBuddies::Header::Basic & h = msg.getHeader<ofxSquashBuddies::Header::Basic>();
            if (h.messageType == ofxSquashBuddies::MessageType::ShortPixels) {
                const ofxSquashBuddies::Header::ShortPixels & header = msg.getHeader<ofxSquashBuddies::Header::ShortPixels>();
                msg.getData(pixels);
                depth.write(pixels);
                depth.toPoints(70, 60, points[i]);
                //depth.map(8000, 0);
                //depth.updateTexture(tex[i]);
            }
            if (h.messageType == ofxSquashBuddies::MessageType::String) {
                string str;
                msg.getData(str);
                ofLog() << str;

                size_t p = str.find(":");
                if (p != string::npos) {
                    string name = str.substr(0, p);
                    string params = str.substr(p+2);
                    if (name == "floor") {
                        vector<string> f = ofSplitString(params, ", ");
                        floor[i].x = ofToFloat(f[0]);
                        floor[i].y = ofToFloat(f[1]);
                        floor[i].z = ofToFloat(f[2]);
                        floor[i].w = ofToFloat(f[3]) * 1000.f;
                        ofNode helper;
                        helper.lookAt(ofVec3f(floor[i].x, floor[i].z, -floor[i].y));
                        helper.boom(floor[i].w);
                        floorTransform[i] = helper.getGlobalTransformMatrix().getInverse();
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    
    for (int i=0; i<3; i++) {
        ofPushMatrix();
        ofMultMatrix(floorTransform[i]);
        ofTranslate(-6000+i*6000, 0);
        ofScale(-1, 1, -1);
        pntVbo[i].draw(GL_POINTS, 0, 512*424);
        ofPopMatrix();
    }
    
    cam.end();

    for (int i=0; i<3; i++) {
        ofDrawBitmapStringHighlight(ofToString(receiver[i].getIncomingFramerate(),1), 20+i*60, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
