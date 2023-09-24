#pragma once

#include <cstdlib>

struct Rect
{
    Rect(size_t l, size_t t, size_t r, size_t b)
    	: l(l)
	    , t(t)
		, r(r)
		, b(b)
	{
	}

	size_t getWidth() const { return r - l; }
	size_t getHeight() const { return b - t; }

	size_t l;
	size_t t;
	size_t r;
	size_t b;
};
