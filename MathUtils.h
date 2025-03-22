#include "iostream"
#include <SFML/Graphics.hpp>



constexpr float PI = 3.14159265358979323846f;

class Vector3 {
public:
	Vector3(float x = 0, float y = 0, float z = 0, float w = 1)
		: x(x), y(y), z(z), w(w) {}

	Vector3 operator+(const Vector3& v);
	Vector3 operator-(const Vector3& v);
	Vector3 operator*(const float k);
	static float scalarProduct(const Vector3& v1, const Vector3& v2);
	float getLenght();
	Vector3 normalise();
	static Vector3 crossProduct(Vector3& v1, Vector3& v2);


	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 1.f;

};


class Matrix4 {
public:

	 Matrix4 operator*(const Matrix4& m);
	 Vector3 operator*(const Vector3& m);

	 static Matrix4 getTranslation(float dx, float dy, float dz);
	 static Matrix4 getScale(float sx, float sy, float sz);
	 static Matrix4 identity();
	std::array<float, 16> data;
	 static Matrix4 getRotationX(float angel);
	 static Matrix4 getRotationY(float angel);
	 static Matrix4 getRotationZ(float angel);
	 static Matrix4 getLookAt(Vector3 eye, Vector3 target, Vector3 up);
	 static Matrix4 getPerspectiveProjection(float fov, float aspect, float near, float fear);
	 static Matrix4 rotate(Matrix4& m, float angel, Vector3 axis);

	float& operator()(int row, int col) {
		return data[row * 4 + col];
	}

	const float& operator()(int row, int col) const {
		return data[row * 4 + col];
	}

	Matrix4(const std::array<float, 16>& values) {
		data = values;
	}
	
	Matrix4() {
		data.fill(0.0f);
	}
};


class Cube {
public:
	 void Draw(sf::RenderWindow& window);

	float angle = 0;

	std::array<Vector3, 8> vertices = {
			Vector3(-0.5, 1, 0.5),
			Vector3(-0.5, 1, -0.5),
			Vector3(0.5, 1, -0.5),
			Vector3(0.5, 1, 0.5),
			Vector3(-1, -1, 1),
			Vector3(-1, -1, -1),
			Vector3(1, -1, -1),
			Vector3(1, -1, 1)
		};


	std::array<std::array<int, 3>, 12> indices = {
		std::array<int, 3>{0, 2, 1},
		std::array<int, 3>{0, 2, 3},

		std::array<int, 3>{4, 6, 5},
		std::array<int, 3>{4, 6, 7},

		std::array<int, 3>{0, 5, 1},
		std::array<int, 3>{0, 5, 4},

		std::array<int, 3>{1, 5, 2},
		std::array<int, 3>{6, 5, 2},

		std::array<int, 3>{3, 6, 2},
		std::array<int, 3>{3, 6, 7},

		std::array<int, 3>{3, 4, 0},
		std::array<int, 3>{3, 4, 7},
	};
};

