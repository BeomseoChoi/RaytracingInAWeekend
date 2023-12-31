#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>

class vec3 {
public:
	vec3()
		: e{ 0.0f, 0.0f, 0.0f } {

	}

	vec3(float e0, float e1, float e2)
		: e{ e0, e1, e2 } {
	}

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline vec3& operator+=(const vec3& v);
	inline vec3& operator-=(const vec3& v);
	inline vec3& operator*=(const vec3& v);
	inline vec3& operator/=(const vec3& v);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length() const;
	inline float squared_length() const;
	inline void make_unit_vector();

	float e[3];
};

inline vec3& vec3::operator+=(const vec3& v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];

	return *this;
}

inline vec3& vec3::operator-=(const vec3& v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];

	return *this;
}

inline vec3& vec3::operator*=(const vec3& v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];

	return *this;
}

inline vec3& vec3::operator/=(const vec3& v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];

	return *this;
}

inline vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;

	return *this;
}

inline vec3& vec3::operator/=(const float t) {
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;

	return *this;
}

inline float vec3::length() const {
	const float SQUARED_LENGTH = squared_length();
	return std::sqrt(SQUARED_LENGTH);
}

inline float vec3::squared_length() const {
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

inline void vec3::make_unit_vector() {
	const float K = 1.0f / length();
	e[0] *= K;
	e[1] *= K;
	e[2] *= K;
}

inline std::istream& operator>>(std::istream& is, vec3& t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];

	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];

	return os;
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, float t) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3& v, float t) {
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const vec3& v1, const vec3& v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]), (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])), (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}
