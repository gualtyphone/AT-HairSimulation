#include "SphereCollider.h"
#include "GMath.h"

using namespace GMath;

Vector3 SphereCollider::GetPosition()
{
	return  transformPoint(transform.GetPosition(), parent->GetRef());
}
