#include <Math/Transformable3.hpp>

#include <Math/Transform3.hpp>
#include <Math/Vec3.hpp>


mth::Transformable3::Transformable3()
{
	m_parent = nullptr;
	m_scale = Vec3(1);
	m_rot_angle = 0;
	m_rot_vec = Vec3(1, 0, 0);
	m_transform_need_update = true;
}

mth::Transformable3::Transformable3(Transformable3& parent)
{
	m_parent = &parent;
	m_scale = Vec3(1);
	m_rot_angle = 0;
	m_rot_vec = Vec3(1, 0, 0);
	m_transform_need_update = true;
}


void mth::Transformable3::move(const Vec3& offset)
{
	m_position += offset;
	m_transform_need_update = true;
}

void mth::Transformable3::scale(const Vec3& scale_v)
{
	m_scale += scale_v;
	m_transform_need_update = true;
}


void mth::Transformable3::setPosition(const Vec3& new_position)
{
	m_position = new_position;
	m_transform_need_update = true;
}

void mth::Transformable3::setScale(const Vec3& new_scale)
{
	m_scale = new_scale;
	m_transform_need_update = true;
}

void mth::Transformable3::setRotation(const Vec3& new_rot_vec, float new_rot_angle)
{
	m_rot_vec = new_rot_vec;
	m_rot_angle = new_rot_angle;
	m_transform_need_update = true;
}

void mth::Transformable3::setParent(Transformable3& parent)
{
	m_parent = &parent;
}


mth::Transformable3* mth::Transformable3::getParent()
{
	return m_parent;
}

mth::Transform3 mth::Transformable3::getLocalTransform()
{
	if (m_transform_need_update)
	{
		m_transform.translate(m_position);
		m_transform.rotate(m_rot_vec, m_rot_angle);
		m_transform.scale(m_scale);

		m_transform_need_update = false;
	}
	return m_transform;
}

mth::Transform3 mth::Transformable3::getGlobalTransform()
{
	if (m_parent == nullptr)
		return getLocalTransform();
	return m_parent->getGlobalTransform().getMatrix()*getLocalTransform().getMatrix();
}