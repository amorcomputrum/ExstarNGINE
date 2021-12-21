#include "Exstar/Physics/Collision.h"
#include "Exstar/Utils/Math.h"

bool exstar::Collision::PointvsCircle(int px,int py,int cx,int cy,int cr){
	return r > exstar::Distance(px,py,cx,cy);
}
bool exstar::Collision::CirclevsCircle(int r1,int x1,int y1,int r2,int x2,int y2){
	return r1+r2 > exstar::Distance(x1,y1,x2,y2);
}
bool exstar::Collision::PointvsRect(float px,float py,float rx,float ry,float w,float h){
	return (px >= x && px <= x + w && py >= y && py <= y + h);
}
bool exstar::Collision::RectvsRect(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2){
	return ((((x1+w1 > x2) && x1 < x2) || ((x1 < x2+w2) && (x1+w1 > x2))) && (((y1+h1 > y2) && y1 < y2) || ((y1 < y2+h2) && (y1+h1 > y2))));
}
bool exstar::Collision::CirclevsRect(float cx, float cy, float radius, float rx, float ry, float w, float h) {
  float testX = cx;
  float testY = cy;
  if (cx < rx)         testX = rx;
  else if (cx > rx+w) testX = rx+w;
  if (cy < ry)         testY = ry;
  else if (cy > ry+h) testY = ry+h;
  float distX = cx-testX;
  float distY = cy-testY;
  float distance = sqrt( (distX*distX) + (distY*distY) );
  return (distance <= radius);
}
bool exstar::Collision::LinevsCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r) {

  bool inside1 = PointvCircle(x1,y1, cx,cy,r);
  bool inside2 = PointvCircle(x2,y2, cx,cy,r);
  if (inside1 || inside2) return true;
  float distX = x1 - x2;
  float distY = y1 - y2;
  float len = sqrt( (distX*distX) + (distY*distY) );

  float dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);

  float closestX = x1 + (dot * (x2-x1));
  float closestY = y1 + (dot * (y2-y1));

  bool onSegment = LinevPoint(x1,y1,x2,y2, closestX,closestY);
  if (!onSegment) return false;
  distX = closestX - cx;
  distY = closestY - cy;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  return (distance <= r);
}
bool exstar::Collision::LinevsLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

  return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1); 
}
bool exstar::Collision::LinevsRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {

  bool left =   LinevLine(x1,y1,x2,y2, rx,ry,rx, ry+rh);
  bool right =  LinevLine(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
  bool top =    LinevLine(x1,y1,x2,y2, rx,ry, rx+rw,ry);
  bool bottom = LinevLine(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);

  return (left || right || top || bottom);
}

ArrayList<int>* exstar::Collision::LinevsCircleLoc(float x1, float y1, float x2, float y2, float cx, float cy, float r) {

  bool inside1 = PointvCircle(x1,y1, cx,cy,r);
  bool inside2 = PointvCircle(x2,y2, cx,cy,r);
  float distX = x1 - x2;
  float distY = y1 - y2;
  float len = sqrt( (distX*distX) + (distY*distY) );

  float dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);

  float closestX = x1 + (dot * (x2-x1));
  float closestY = y1 + (dot * (y2-y1));

  bool onSegment = LinevPoint(x1,y1,x2,y2, closestX,closestY);
  if (onSegment){
  	ArrayList<int>* points = new ArrayList<int>;
  	(*points).add(closestX);
  	(*points).add(closestY);
  	return points;
  }
  return NULL;
}

ArrayList<int>* exstar::Collision::LinevsLineLoc(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1){
   ArrayList<int>* points = new ArrayList<int>;
   int intersectionX = x1 + (uA * (x2-x1));
   int intersectionY = y1 + (uA * (y2-y1));
   (*points).add(intersectionX);
   (*points).add(intersectionY);
   return points;
 }
 return NULL;

}

ArrayList<int>* exstar::Collision::LinevsRectLoc(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh, int d) {

  ArrayList<int>* left =   LineLine(x1,y1,x2,y2, rx,ry,rx, ry+rh);
  ArrayList<int>* right =  LineLine(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
  ArrayList<int>* top =    LineLine(x1,y1,x2,y2, rx,ry, rx+rw,ry);
  ArrayList<int>* bottom = LineLine(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);
  switch(d){
  	case 1:
    return left;
    break;
    case 2:
    return right;
    break;
    case 3:
    return top;
    break;
    case 4:
    return bottom;
    break;
    default:
    return NULL;
    break;
  }

}