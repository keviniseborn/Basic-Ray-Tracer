#ifndef VEC3H
#define VEC3H
#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:
	
	#pragma region constructors

	vec3() {}
	vec3(float val0, float val1, float val2) { vec[0] = val0; vec[1] = val1; vec[2] = val2; }
	
	#pragma endregion

	#pragma region function declarations
	
	inline float x() const { return vec[0]; }
	inline float y() const { return vec[1]; }
	inline float z() const { return vec[2]; }
	inline float r() const { return vec[0]; }
	inline float g() const { return vec[1]; }
	inline float b() const { return vec[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-vec[0], -vec[1], -vec[2]); }
	inline float operator[](int i) const { return vec[i]; }
	inline float& operator[](int i) { return vec[i]; };

	inline vec3& operator+=(const vec3 &v2);
	inline vec3& operator-=(const vec3 &v2);
	inline vec3& operator*=(const vec3 &v2);
	inline vec3& operator/=(const vec3 &v2);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	
	// Calculate Lenght of vector
	inline float length() const
	{
		return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	}

	// Calculate squared length of vector
	inline float squared_length() const
	{
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	}

	inline void make_unit_vector();
	#pragma endregion

	#pragma region fields

	float vec[3];

	#pragma endregion
};

#pragma region function definitions

// input values into the associated vector
// is = input stream
// t = vector
inline std::istream& operator>>(std::istream &is, vec3 &t) 
{
	is >> t.vec[0] >> t.vec[1] >> t.vec[2];
	return is;
}

// output values of the associated vector
// is = output stream
// t = vector
inline std::ostream& operator<<(std::ostream &os, const vec3 &t) 
{
	os << t.vec[0] << " " << t.vec[1] << " " << t.vec[2];
	return os;
}

// make vector a unit vector
inline void vec3::make_unit_vector() 
{
	float k = 1.0 / sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	vec[0] *= k; 
	vec[1] *= k; 
	vec[2] *= k;
}

// return result of addition of two vectors
inline vec3 operator+(const vec3 &v1, const vec3 &v2) 
{
	return vec3(v1.vec[0] + v2.vec[0], v1.vec[1] + v2.vec[1], v1.vec[2] + v2.vec[2]);
}

// return results of substraction between two vectors
inline vec3 operator-(const vec3 &v1, const vec3 &v2) 
{
	return vec3(v1.vec[0] - v2.vec[0], v1.vec[1] - v2.vec[1], v1.vec[2] - v2.vec[2]);
}

// return result of multiplaction between two vectors
inline vec3 operator*(const vec3 &v1, const vec3 &v2) 
{
	return vec3(v1.vec[0] * v2.vec[0], v1.vec[1] * v2.vec[1], v1.vec[2] * v2.vec[2]);
}

// return result of dividing two vectors
inline vec3 operator/(const vec3 &v1, const vec3 &v2) 
{
	return vec3(v1.vec[0] / v2.vec[0], v1.vec[1] / v2.vec[1], v1.vec[2] / v2.vec[2]);
}

// return result of multiplication of a vector and a float
inline vec3 operator*(float t, const vec3 &v) 
{
	return vec3(t*v.vec[0], t*v.vec[1], t*v.vec[2]);
}
inline vec3 operator*(const vec3 &v, float t) 
{
	return vec3(t*v.vec[0], t*v.vec[1], t*v.vec[2]);
}

// return result of division between a vector and a float
inline vec3 operator/(vec3 v, float t) 
{
	return vec3(v.vec[0] / t, v.vec[1] / t, v.vec[2] / t);
}

// return the results of the dot product between two vectors
inline float dot(const vec3 &v1, const vec3 &v2) 
{
	return v1.vec[0] * v2.vec[0] + v1.vec[1] * v2.vec[1] + v1.vec[2] * v2.vec[2];
}

// return the results of the cross product between two vectors
inline vec3 cross(const vec3 &v1, const vec3 &v2) 
{
	return vec3((v1.vec[1] * v2.vec[2] - v1.vec[2] * v2.vec[1]),
				(-(v1.vec[0] * v2.vec[2] - v1.vec[2] * v2.vec[0])),
				(v1.vec[0] * v2.vec[1] - v1.vec[1] * v2.vec[0]));
}

// return result of passed in vector added to this vector
inline vec3& vec3::operator+=(const vec3 &v) 
{
	vec[0] += v.vec[0];
	vec[1] += v.vec[1];
	vec[2] += v.vec[2];
	return *this;
}

// return the results of the passed in vector mulitplied by this vector
inline vec3& vec3::operator*=(const vec3 &v) 
{
	vec[0] *= v.vec[0];
	vec[1] *= v.vec[1];
	vec[2] *= v.vec[2];
	return *this;
}

// return result of the passed in vector devided by this vector
inline vec3& vec3::operator/=(const vec3 &v) 
{
	vec[0] /= v.vec[0];
	vec[1] /= v.vec[1];
	vec[2] /= v.vec[2];
	return *this;
}

// return the result of the passed in vector minus this vector
inline vec3& vec3::operator-=(const vec3& v) 
{
	vec[0] -= v.vec[0];
	vec[1] -= v.vec[1];
	vec[2] -= v.vec[2];
	return *this;
}

// return the result of passed in float multiplied by this vector
inline vec3& vec3::operator*=(const float t) 
{
	vec[0] *= t;
	vec[1] *= t;
	vec[2] *= t;
	return *this;
}

// return the result of the passed in float devided by this vector
inline vec3& vec3::operator/=(const float t) 
{
	float k = 1.0 / t;

	vec[0] *= k;
	vec[1] *= k;
	vec[2] *= k;
	return *this;
}

// return the unit vector of passed in vector
inline vec3 unit_vector(vec3 v) 
{
	return v / v.length();
}

#pragma endregion

#endif