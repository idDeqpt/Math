#include <Math/Transform3.hpp>

#include <cmath>

#include <Math/Mat4.hpp>
#include <Math/Vec3.hpp>
#include <Math/Quaternion.hpp>


mth::Transform3::Transform3()
{
	m_matrix = Mat4::getIdentity();
}

mth::Transform3::Transform3(const Mat4& mat)
{
	m_matrix = mat;
}

mth::Transform3::Transform3(Transform3& transform) : Transform3(transform.getMatrix()) {}


void mth::Transform3::translate(const Vec3& vec)
{
	Mat4 translate_m(
		1, 0, 0, vec.x,
		0, 1, 0, vec.y,
		0, 0, 1, vec.z,
		0, 0, 0, 1
	);
	m_matrix = m_matrix*translate_m;
}

void mth::Transform3::scale(const Vec3& vec)
{
	Mat4 scale_m(
		vec.x, 0, 0, 0,
		0, vec.y, 0, 0,
		0, 0, vec.z, 0,
		0, 0, 0, 1
	);
	m_matrix = m_matrix*scale_m;
}

void mth::Transform3::rotate(const Vec3& vec, float angle)
{
	float a = angle;
	float s = sin(a);
	float c = cos(a);

	Vec3 axis(vec.norm(1));
	Vec3 temp((1 - c)*axis);

	Mat4 rotate_m;
	rotate_m[0][0] = c + temp[0]*axis[0];
	rotate_m[0][1] = temp[0]*axis[1] + s*axis[2];
	rotate_m[0][2] = temp[0]*axis[2] - s*axis[1];

	rotate_m[1][0] = temp[1]*axis[0] - s*axis[2];
	rotate_m[1][1] = c + temp[1]*axis[1];
	rotate_m[1][2] = temp[1]*axis[2] + s*axis[0];

	rotate_m[2][0] = temp[2]*axis[0] + s*axis[1];
	rotate_m[2][1] = temp[2]*axis[1] - s*axis[0];
	rotate_m[2][2] = c + temp[2]*axis[2];

	rotate_m[3][3] = 1;

	m_matrix = m_matrix*rotate_m;
}

void mth::Transform3::rotate(const Quaternion& quat)
{
	Quaternion norm_q = quat.norm();

	Mat4 rot_m;
	rot_m[0][0] = 1 - 2 * (norm_q.y * norm_q.y + norm_q.z * norm_q.z);
	rot_m[0][1] = 2 * (norm_q.x * norm_q.y - norm_q.w * norm_q.z);
	rot_m[0][2] = 2 * (norm_q.x * norm_q.z + norm_q.w * norm_q.y);

	rot_m[1][0] = 2 * (norm_q.x * norm_q.y + norm_q.w * norm_q.z);
	rot_m[1][1] = 1 - 2 * (norm_q.x * norm_q.x + norm_q.z * norm_q.z);
	rot_m[1][2] = 2 * (norm_q.y * norm_q.z - norm_q.w * norm_q.x);

	rot_m[2][0] = 2 * (norm_q.x * norm_q.z - norm_q.w * norm_q.y);
	rot_m[2][1] = 2 * (norm_q.y * norm_q.z + norm_q.w * norm_q.x);
	rot_m[2][2] = 1 - 2 * (norm_q.x * norm_q.x + norm_q.y * norm_q.y);

	rot_m[3][3] = 1;

	m_matrix = m_matrix*rot_m;
}


mth::Mat4 mth::Transform3::getMatrix()
{
	return m_matrix;
}



mth::Mat4 mth::Transform3::getIdentity()
{
	return Mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}