#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
/*    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    // FFTのサンプル数(2の累乗)を指定して初期化
    fft.setup(pow(2.0, 12.0));
*/
    //------naru------
    music.load("harley_hs.wav");
    music.play();

    ofBackground(0, 0, 0);
    cam.setDistance(200);
    
    // -- prepare sound input
    initialBufferSize = 256;
    // -- prepare fft vector
    nBandsToGet = 256;

    for (int i=0; i<initialBufferSize; i++) {
        vector<float> fft;
        fft.assign(nBandsToGet, 0.0);
        fftHistory.push_back(fft);
    }

    // -- prepare vbo
    for (int i=0; i<WIDTH; i++) {
        for (int j=0; j<HEIGHT; j++) {
            myVerts[i * WIDTH + j].set(i - WIDTH/2, j - HEIGHT/2, 0);
            myColor[i * WIDTH + j].set(0.5, 0.8, 1.0, 0.2);
        }
    }
    myVbo.setVertexData(myVerts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    myVbo.setColorData(myColor, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    
    //movie.load("LVR2017-10.MOV");
    movie.load("EriNaru2017.04.29.MOV");
    movie.play();
    double width = movie.getWidth();
    double height = movie.getHeight();
    double bigger = width > height ? width : height;
    double rate = ofGetWidth ()/bigger; // 縦横等しいのを既知とする
    movieWidth = width * rate;
    movieHeight = height * rate;
}

//--------------------------------------------------------------
void ofApp::update(){
//    fft.update(); // FFT更新
    
    //------naru-----
    ofSoundUpdate();
    float* val = ofSoundGetSpectrum(nBandsToGet);
    vector<float> currentFft;

    for (int i=0; i<nBandsToGet; i++) {
        currentFft.push_back(val[i]);
    }
    std::cout << currentFft[255] << std::endl;
    fftHistory.push_back(currentFft);
    
    if (fftHistory.size() >= 256) {
        fftHistory.erase(fftHistory.begin(), fftHistory.begin()+1);
    }
    // update vertex coodinates
    for (int i=0; i<WIDTH; i++) {
        vector<float> fft = fftHistory.at(i);
        for (int j=0; j<HEIGHT; j++) {
            float x = i - WIDTH/2;
            float y = j - HEIGHT/2;
            float z = fft.at(j) * 50;
            
            // myVerts[i * WIDTH + j] = ofVec3f(x,y,z);
            myVerts[i * WIDTH + j] = ofVec3f(x, z - (ofGetHeight()-movieHeight)/2, -1 * y);
            myColor[i * WIDTH + j].set(0.5+0.5*fft.at(j), 0.8, 1.0, 0.2+0.8*fft.at(j));
        }
    }
    myVbo.updateVertexData(myVerts, NUM_PARTICLES);
    myVbo.updateColorData(myColor, NUM_PARTICLES);

    movie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // float型の配列にFFT結果を格納
/*    vector<float> buffer;
    buffer = fft.getBins();
    // グラフに描画
    ofNoFill();
    ofSetLineWidth(2.0);
    ofBeginShape();
    for (int i = 0; i < buffer.size(); i++) {
        float x = ofMap(i, 0, buffer.size(), 0, ofGetWidth());
        float y = ofMap(buffer[i], 0, 1, ofGetHeight(), 0);
        ofVertex(x, y);
    }
    ofEndShape();
*/
    
    //ムービーデータを画面中央に表示
    movie.draw((ofGetWidth() - movieWidth)/2, (ofGetHeight() - movieHeight)/2, movieWidth, movieHeight);
    
 //   ofPushMatrix();
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - (ofGetHeight()-movieHeight)/2);
    
    cam.begin();
    glPointSize(2);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    myVbo.draw(GL_POINTS, 0, NUM_PARTICLES);
    //movie.draw((ofGetWidth() - movieWidth)/2, (ofGetHeight() - movieHeight)/2, movieWidth, movieHeight);

    cam.end();
    
//    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
        music.play();
    }
    if (key == 'e') {
        music.stop();
    }
    // pause
    if (key == 'p') {
        if (is_pause) {
            music.setPaused(false);
            is_pause = false;
        } else {
            music.setPaused(true);
            is_pause = true;
        }
    }
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
