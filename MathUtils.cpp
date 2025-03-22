#include "MathUtils.h"
constexpr float MOUSE_SENSE = 0.01f;

Vector3 Vector3::operator+(const Vector3& v) {
	return Vector3(
		this->x + v.x,
		this->y + v.y,
		this->z + v.z
	);
}

Vector3 Vector3::operator-(const Vector3& v) {
	return Vector3(
		this->x - v.x,
		this->y-v.y,
		this->z-v.z,
		this->w-v.w
	);
}

Vector3 Vector3::operator*(float k) {
	return Vector3(this->x*k, this->y * k, this->z * k);
}

float Vector3::getLenght() {
	return sqrtf(x*x+y*y+z*z);
}

Vector3 Vector3::normalise() {
	float l = this->getLenght();
	return Vector3(this->x / l, this->y / l, this->z / l);
}

Vector3 Vector3::crossProduct(Vector3& v1, Vector3& v2) {
	return Vector3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

float Vector3::scalarProduct(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Matrix4 Matrix4::operator*(const Matrix4& other) {
	Matrix4 result;
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			float sum = 0.0f;
			for (int i = 0; i < 4; ++i) {
				sum += (*this)(row, i) * other(i, col);
			}
			result(row, col) = sum;
		}
	}
	return result;
}

Vector3 Matrix4::operator*(const Vector3& vector) {
	Vector3 result = Vector3(
		(*this)(0, 0) * vector.x + (*this)(0, 1) * vector.y + (*this)(0, 2) * vector.z + (*this)(0, 3) * vector.w,
		(*this)(1, 0) * vector.x + (*this)(1, 1) * vector.y + (*this)(1, 2) * vector.z + (*this)(1, 3) * vector.w,
		(*this)(2, 0) * vector.x + (*this)(2, 1) * vector.y + (*this)(2, 2) * vector.z + (*this)(2, 3) * vector.w,
		(*this)(3, 0) * vector.x + (*this)(3, 1) * vector.y + (*this)(3, 2) * vector.z + (*this)(3, 3) * vector.w
	);
	return result;
}

Matrix4 Matrix4::identity() {
	return Matrix4(std::array<float, 16>{
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	});
}

Matrix4 Matrix4::getTranslation(float dx, float dy, float dz) {
	return Matrix4(std::array<float, 16>{
			1, 0, 0, dx,
			0, 1, 0, dy,
			0, 0, 1, dz,
			0, 0, 0, 1
	});
}

Matrix4 Matrix4::getScale(float sx, float sy, float sz) {
	return Matrix4(std::array<float, 16>{
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1
	});
}

Matrix4 Matrix4::getRotationX(float angel){
	float rad = PI / 180 * angel;
	return Matrix4(std::array<float, 16>{
		1,0,0,0,
		0,cosf(rad),-sinf(rad),0,
		0,sinf(rad),cosf(rad),0,
		0,0,0,1
	});
}

Matrix4 Matrix4::getRotationY(float angle) {
	float rad = PI / 180.0f * angle;
	return Matrix4(std::array<float, 16>{
		cos(rad), 0, sin(rad), 0,
		0, 1, 0, 0,
		-sin(rad), 0, cos(rad), 0,
		0, 0, 0, 1
	});
}

Matrix4 Matrix4::getRotationZ(float angle) {
	float rad = PI / 180.0f * angle;
	return Matrix4(std::array<float, 16>{
		cos(rad), -sin(rad), 0, 0,
		sin(rad), cos(rad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	});
}

Matrix4 Matrix4::getLookAt(Vector3 eye, Vector3 target, Vector3 up) {
	Vector3 vz = (eye- target).normalise();
	Vector3 vx = Vector3::crossProduct(up, vz).normalise();
	Vector3 vy = Vector3::crossProduct(vz, vx).normalise();
	Matrix4 m = Matrix4(std::array<float, 16>{
		vx.x, vx.y, vx.z, 0,
			vy.x, vy.y, vy.z, 0,
			vz.x, vz.y, vz.z, 0,
			0, 0, 0, 1
	});
	return Matrix4::getTranslation(-eye.x, -eye.y, -eye.z) * m;
}

Matrix4 Matrix4::getPerspectiveProjection(float fov, float aspect, float near, float far) {
	float rad = PI / 180 * fov;
	float sx = (1 / tanf(rad / 2)) / aspect;
	float sy = (1 / tanf(rad / 2));
	float sz = (far + near) / (far - near);
	float dz = (-2 * far * near) / (far - near);
	return Matrix4(std::array<float, 16>{
		sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, dz,
			0, 0, -1, 0
	});
}

Matrix4 Matrix4::rotate(Matrix4& m, float angle, Vector3 axis) {
	Vector3 normalizedAxis = axis.normalise();

	float radAngle = angle * (PI / 180.0f); // Перевод угла в радианы
	float c = cos(radAngle);
	float s = sin(radAngle);
	float t = 1.0f - c;

	float x = normalizedAxis.x, y = normalizedAxis.y, z = normalizedAxis.z;

	Matrix4 rotation(std::array<float, 16>{
		t* x* x + c, t* x* y - z * s, t* x* z + y * s, 0.f,
			t* x* y + z * s, t* y* y + c, t* y* z - x * s, 0.f,
			t* x* z - y * s, t* y* z + x * s, t* z* z + c, 0.f,
			0, 0, 0, 1
	});

	return rotation* m;
}


Matrix4 rotation = Matrix4::identity();
Vector3 front(0,0,-1,0);
Vector3 right;
Vector3 up(0,1,0,0);

Vector3 cameraPos(0, 0, 1);
float x_rot = 0;
float y_rot = 0;

void Cube::Draw(sf::RenderWindow& window) {

	std::vector<sf::Vertex> sfmlVertices;
	sf::Vector2i windowCenter(window.getSize().x / 2, window.getSize().y / 2);


	float speed = 5.f;


	if (window.hasFocus()) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2i movement = mousePosition - windowCenter;
		if ((movement.x != 0 || movement.y != 0)&&sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			y_rot += movement.x * MOUSE_SENSE;
			x_rot -= movement.y * MOUSE_SENSE;
//			std::cout << "Mouse moved: " << x_rot << ", " << y_rot << std::endl;
		}
	}




	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		x_rot -= 0.5 *speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		x_rot += 0.5 * speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		y_rot -= 0.5 * speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		y_rot += 0.5 * speed;




	// 1 - все Rotation
	// 2 - * на матрицу размера Scale
	// 3 - * на матрицу перемещения Translation
	// 4 - * на матрицу LookAt
	// 5 - * на матрицу перспективы
	Matrix4 matrix = Matrix4::getRotationX(x_rot);
	matrix = Matrix4::getRotationY(y_rot) * matrix;
	matrix = Matrix4::getScale(100, 100, 100) * matrix;
	matrix = Matrix4::getTranslation(0, 0, -300) * matrix;
	matrix = Matrix4::getLookAt(
		cameraPos,
		cameraPos+ front,
		up
	) * matrix;
	matrix = Matrix4::getPerspectiveProjection(90, 800 / 600, 0.1f, 100.f) * matrix;

	angle++;

	std::vector<Vector3> sfm;
	for (Vector3 v_ : this->vertices) {
		Vector3 vertex = matrix * v_;
		vertex.x = vertex.x / vertex.w * windowCenter.x;
		vertex.y = vertex.y / vertex.w * windowCenter.y;
		sfm.push_back(vertex);
	}

	for (std::array<int, 3> indice : this->indices) {
		Vector3 v1 = sfm[indice[0]];
		Vector3 v2 = sfm[indice[1]];
		Vector3 v3 = sfm[indice[2]];

		Vector3 t1 = v1 - v2;
		Vector3 t2 = v2 - v3;
		Vector3 normal = Vector3::crossProduct(t1, t2).normalise();
		float res = Vector3::scalarProduct(front, normal);

		// центруем
		v1.x = v1.x + windowCenter.x;
		v2.x = v2.x + windowCenter.x;
		v3.x = v3.x + windowCenter.x;
		// переворачиваем вершины
		v1.y = -(v1.y- windowCenter.y);
		v2.y = -(v2.y - windowCenter.y);
		v3.y = -(v3.y - windowCenter.y);




		sfmlVertices.push_back({ {v1.x,v1.y},sf::Color(0,0,255) });
		sfmlVertices.push_back({ {v2.x,v2.y},sf::Color(0,0,255) });
		sfmlVertices.push_back({ {v2.x,v2.y},sf::Color(0,0,255) });
		sfmlVertices.push_back({ {v3.x,v3.y},sf::Color(0,0,255) });
		sfmlVertices.push_back({ {v3.x,v3.y},sf::Color(0,0,255) });
		sfmlVertices.push_back({ {v1.x,v1.y},sf::Color(0,0,255) });
		// если нужны треугольники, то русием только три точки v1, v2 и v3. В draw стави sf::PrimitiveType::Triangles


	}



	window.draw(sfmlVertices.data(), sfmlVertices.size(), sf::PrimitiveType::Lines);
}