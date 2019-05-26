// Mathtils.h

#pragma once

class MathUtils
{
private:
	MathUtils();
	~MathUtils();

public:
	static inline int Min(int a, int b) 
	{ 
		return a < b ? a : b; 
	}
	
	
	static inline int Min(int a, int b, int c) 
	{
		return MathUtils::Min(MathUtils::Min(a, b), c);
	}
	
	
	static inline int Max(int a, int b) 
	{
		return a > b ? a : b; 
	}
	
	
	static inline int Max(int a, int b, int c)
	{
		return MathUtils::Max(MathUtils::Max(a, b), c);
	}
};
