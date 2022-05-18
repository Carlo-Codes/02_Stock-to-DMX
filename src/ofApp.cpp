#include "ofApp.h"





vector <ofJson> data_list(5);
vector <float> price_list(5);
vector <int> remapped_price_list(5);
vector <int> re_remapped_price_list(5);
float hi_lo[1];

float remap(float value, float low1, float high1, float low2, float high2) {

	float remaped = (((value - low1) / (high1 - low1)) * (high2 - low2)) + low2;
	return remaped;
}


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::white);

	//for (ofJson::iterator i = j_data["data"].begin(); i != j_data["data"].end(); ++i) {
	//	data_list.push_back(*i);
	//}
	sender.SetSenderName("Dr Carlo");
	fbo.allocate(ofGetWidth(),ofGetHeight());
	ofLoadImage(pxls, "black.jpg");

	
}

//--------------------------------------------------------------
void ofApp::update(){

	
	
	pxls.setNumChannels(1);

	hi_lo[0] = 0;
	hi_lo[1] = 0;

	j_data = ofLoadJson("data.json");

	

	for (int i = 0; i < j_data["data"].size(); i++) { //populate vector with data from json
		price_list.push_back(j_data["data"][i]["Price"]);
		hi_lo[0] = j_data["data"][i]["High"];
		hi_lo[1] = j_data["data"][i]["Low"];
	}

	int width = pxls.getWidth();
	int height = pxls.getHeight();

	

	unsigned char* raw_pxls = pxls.getData();

	
	// remapping values
	for (int i = 0; i < price_list.size();i++) { //remapping numbers to 0 to 255
		remapped_price_list.push_back(remap(price_list[i], hi_lo[1], hi_lo[0], 0, 255));
		
	} 



	//finding min / max
	int remapped_max = remapped_price_list[0];
	int remapped_min = remapped_price_list[0];
	for (int i = 0; i < remapped_price_list.size(); i++) {
		if (remapped_price_list[i] > remapped_max) {
			remapped_max = remapped_price_list[i];
		}
		if (remapped_price_list[i] < remapped_min) {
			remapped_min = remapped_price_list[i];
		}
	}
	//cout << "max = " << remapped_max << " // //" << "min = " << remapped_min << "\n";

	for (int i = 0; i < remapped_price_list.size(); i++) {
		re_remapped_price_list.push_back(remap(remapped_price_list[i], remapped_min, remapped_max, 0, 255));
		cout << remapped_price_list[i] << "\n";
	}
	cout <<"\n\n\n\n";
	//cout << "\n\n\n\n";
	//cout << "max = " << remapped_max << " // //" << "min = " << remapped_min << "\n";

	//cout << remapped_price_list[2];


	
	int columns = 4;
	float width_spacing = width / columns; //plus 2 to give side spacing
	for (int y = 1; y < height; y++) {
			
			for (int i = 0; i < columns; i++) {
				int pix0 = y * width + (width_spacing * i);
				for (int j = 0; j < 30; j++){
					raw_pxls[pix0 + j] = remapped_price_list[i];
					raw_pxls[pix0 - j] = remapped_price_list[i];
				}
			}

	}
	
	tex.allocate(pxls);
	

}



//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	fbo.clear();
	tex.draw(0, 0);
	for (int i = 0; i < price_list.size(); i++) {
		string price = "Price = ";  
		ofDrawBitmapString(price_list[i], (((pxls.getWidth() / 4) * i) + 10), 50);

	}
	fbo.end();

	sender.SendFbo(fbo.getId(), ofGetWidth(), ofGetHeight(), false);
	//cout << re_remapped_price_list[0] << "\n";
	price_list.clear(); // clearing the price values
	remapped_price_list.clear();
	re_remapped_price_list.clear();
	j_data.clear();
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

void ofApp::exit() {
	sender.ReleaseSender();

}