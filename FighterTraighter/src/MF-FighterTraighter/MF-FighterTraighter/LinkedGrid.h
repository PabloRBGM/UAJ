#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class LinkedGrid
{
public:
	LinkedGrid(size_t width, size_t height) : grid_(height), sizeX_(width), sizeY_(height)
	{
		for (std::vector<T>& v : grid_) {
			v.resize(width);
		}
	}
	T GetItem(size_t x, size_t y) const
	{
		return (grid_[y])[x];
	}
	void SetItemInPos(T item, size_t x, size_t y) 
	{
		if(y < 0 || y >= sizeY_ || x < 0 || x >= sizeX_) throw new std::out_of_range("Position out of range");
		(grid_[y])[x] = item;
	}
	inline size_t GetSizeX() {
		return sizeX_;
	}
	inline size_t GetSizeY() {
		return sizeY_;
	}
	virtual ~LinkedGrid() {};
private:
	std::vector<std::vector<T>> grid_;
	size_t sizeX_, sizeY_;
};

