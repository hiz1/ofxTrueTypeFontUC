#pragma once


#include <vector>
#include "ofMain.h"

//--------------------------------------------------
const static string OF_TTFUC_SANS = "sans-serif";
const static string OF_TTFUC_SERIF = "serif";
const static string OF_TTFUC_MONO = "monospace";

enum Alignment {
    TOP_LEFT   , TOP_CENTER   , TOP_RIGHT,
    MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT,
    BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT,
    NONE
};

//--------------------------------------------------
class ofxTrueTypeFontUC{
public:
  ofxTrueTypeFontUC();
  virtual ~ofxTrueTypeFontUC();
  
  // -- default (without dpi), anti aliased, 96 dpi:
  bool loadFont(const string &filename, int fontsize, bool bAntiAliased=true, bool makeContours=false, float simplifyAmt=0.3, int dpi=0);
  void reloadFont();
  
  void drawString(const string &utf8_string, float x, float y, Alignment alignment = NONE);
  void drawStringAsShapes(const string &utf8_string, float x, float y, Alignment alignment = NONE);
  
  vector<ofPath> getStringAsPoints(const string &utf8_string, bool vflip=ofIsVFlipped());
  ofRectangle getStringBoundingBox(const string &utf8_string, float x, float y);
  
  bool isLoaded();
  bool isAntiAliased();
  
  int getSize();
  float getLineHeight();
  void setLineHeight(float height);
  float getLetterSpacing();
  void setLetterSpacing(float spacing);
  float getSpaceSize();
  void setSpaceSize(float size);
  float stringWidth(const string &utf8_string);
  float stringHeight(const string &utf8_string);
  // get the num of loaded chars
  int getNumCharacters();
  ofTextEncoding getEncoding() const;
  // set the default dpi for all typefaces
  static void setGlobalDpi(int newDpi);

  // code for alignment
  ofVec2f getOffset(const string &s, Alignment alignment) {
    if(alignment == NONE)return ofVec2f();
    ofRectangle r = getStringBoundingBox(s, 0, 0);
    switch (alignment) {
      case TOP_LEFT:
        return ofVec2f(0, floor(-r.y ) );
      case TOP_CENTER:
        return ofVec2f( floor(-r.x - r.width * 0.5f), floor(-r.y ) );
      case TOP_RIGHT:
        return ofVec2f( 2.0 * floor(-r.x - r.width * 0.5f), floor(-r.y ) );
      case MIDDLE_LEFT:
        return ofVec2f( 0, floor(-r.y - r.height * 0.5f) );
      case MIDDLE_CENTER:
        return ofVec2f( floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f) );
      case MIDDLE_RIGHT:
        return ofVec2f( 2.0 * floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f) );
      case BOTTOM_LEFT:
        return ofVec2f( 0, floor(-r.y - r.height) );
      case BOTTOM_CENTER:
        return ofVec2f( floor(-r.x - r.width * 0.5f), floor(-r.y - r.height) );
      case BOTTOM_RIGHT:
        return ofVec2f( 2.0 * floor(-r.x - r.width * 0.5f), floor(-r.y - r.height) );
      default:
        break;
    }
  }
  
  void drawCenteredBoundingBox(const string &s, float x, float y, float padding = 0){
    ofRectangle r = getStringBoundingBox(s, 0, 0);
    r.x -= padding;
    r.y -= padding;
    r.width += 2.0f * padding;
    r.height += 2.0f * padding;
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect( x, y, r.width, r.height);
    ofSetRectMode(OF_RECTMODE_CORNER);
  }
  
private:
  class Impl;
  Impl *mImpl;
  
  // disallow copy and assign
  ofxTrueTypeFontUC(const ofxTrueTypeFontUC &);
  void operator=(const ofxTrueTypeFontUC &);
};

//--------------------------------------------------
namespace util {
  namespace ofxTrueTypeFontUC {
    basic_string<unsigned int> convUTF8ToUTF32(const string & utf8_string);
  }
}

