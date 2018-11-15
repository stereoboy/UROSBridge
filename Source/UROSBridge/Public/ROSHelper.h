#pragma once

#include "geometry_msgs/Point.h"
#include "geometry_msgs/Transform.h"

class UROSBRIDGE_API FROSHelper
{
public:
	static geometry_msgs::Vector3	ConvertVectorUE4ToROS(const FVector &Vector);
	static FVector					ConvertVectorROSToUE4(const geometry_msgs::Vector3 &vector);

	static geometry_msgs::Point	ConvertPointUE4ToROS(const FVector &Vector);
	static FVector					ConvertPointROSToUE4(const geometry_msgs::Point &point);

	static geometry_msgs::Quaternion ConvertQuatUE4ToROS(const FQuat &Quat);
	static FQuat					 ConvertQuatROSToUE4(const geometry_msgs::Quaternion &quat);

	static geometry_msgs::Vector3	ConvertEulerAngleUE4ToROS(const FRotator &Rotator);
	static FRotator					ConvertEulerAngleROSToUE4(const geometry_msgs::Vector3 &rotator);

	static geometry_msgs::Transform ConvertTransformUE4ToROS(const FTransform &transform);
	static FTransform				ConvertTransformROSToUE4(const geometry_msgs::Transform &transform);
};
