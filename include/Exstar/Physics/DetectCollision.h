#pragma once

#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Utils/Point.h"
#include "Exstar/Utils/Vector2d.h"

namespace exstar{
	namespace physics{
		struct DetectCollision{
			static bool PointvsCircle(int px, int py, int cx, int cy, int cr);

			static bool CirclevsCircle(int r1, int x1, int y1, int r2, int x2, int y2);

			static bool PointvsRect(float px, float py, float rx, float ry, float w, float h);

			static bool RectvsRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

			static bool CirclevsRect(float cx, float cy, float radius, float rx, float ry, float w, float h);

			static bool LinevsPoint(float x1, float y1, float x2, float y2, float px, float py);

			static bool LinevsCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r);

			static bool LinevsLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

			static bool LinevsRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);

			static exstar::ArrayList<int>* LinevsCircleLoc(float x1, float y1, float x2, float y2, float cx, float cy, float r);

			static exstar::ArrayList<int>* LinevsLineLoc(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

			static exstar::ArrayList<int>* LinevsRectLoc(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh, int d);
		};
	}
}
