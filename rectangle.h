#ifndef RECTANGLE_H_
#define RECTANGLE_H_

struct Rectangle{
	Rectangle(int x, int y, int width, int height) :
		x_(x),
		y_(y),
		width_(width),
		height_(height){}

	int left(){ return x_; }
	int right(){ return x_ + width_; }
	int top(){ return y_; }
	int bottom(){ return y_ + height_; }

	int width(){ return width_; }
	int height(){ return height_; }

	private:
	int x_, y_, width_, height_;
};

#endif