#include "ROSHelper.h"

geometry_msgs::Vector3	FROSHelper::ConvertVectorUE4ToROS(const FVector &Vector)
{
	return geometry_msgs::Vector3(0.01*Vector.X, -0.01*Vector.Y, 0.01*Vector.Z);
}

FVector	FROSHelper::ConvertVectorROSToUE4(const geometry_msgs::Vector3 &vector)
{
	return FVector(100.0*vector.GetX(), -100.0*vector.GetY(), 100.0*vector.GetZ());
}

geometry_msgs::Quaternion FROSHelper::ConvertQuatUE4ToROS(const FQuat &Quat)
{
	FRotator rot = Quat.Rotator();
	FRotator out(-rot.Pitch, -rot.Yaw, rot.Roll);
	FQuat q = out.Quaternion();

	return geometry_msgs::Quaternion(q.X, q.Y, q.Z, q.W);
}

FQuat FROSHelper::ConvertQuatROSToUE4(const geometry_msgs::Quaternion &quat)
{
	FRotator rot = FQuat(quat.GetX(), quat.GetY(), quat.GetZ(), quat.GetW()).Rotator();
	FRotator out(-rot.Pitch, -rot.Yaw, rot.Roll);

	return out.Quaternion();
}

geometry_msgs::Vector3	FROSHelper::ConvertEulerAngleUE4ToROS(const FRotator &Rotator)
{
	return geometry_msgs::Vector3(	FMath::DegreesToRadians(Rotator.Roll),
									FMath::DegreesToRadians(-Rotator.Pitch),
									FMath::DegreesToRadians(-Rotator.Yaw));
}

FRotator FROSHelper::ConvertEulerAngleROSToUE4(const geometry_msgs::Vector3 &rotator)
{
	return FRotator(	FMath::RadiansToDegrees(-rotator.GetY()),
						FMath::RadiansToDegrees(-rotator.GetZ()),
						FMath::RadiansToDegrees(rotator.GetX()));
}

geometry_msgs::Transform FROSHelper::ConvertTransformUE4ToROS(const FTransform &Transform)
{
	geometry_msgs::Vector3 vector = FROSHelper::ConvertVectorUE4ToROS(Transform.GetLocation());
	geometry_msgs::Quaternion quat = FROSHelper::ConvertQuatUE4ToROS(Transform.GetRotation());
	
	return geometry_msgs::Transform(vector, quat);
}

FTransform	FROSHelper::ConvertTransformROSToUE4(const geometry_msgs::Transform &transform)
{
	FVector Vector = FROSHelper::ConvertVectorROSToUE4(transform.GetTranslation());
	FQuat Quat = FROSHelper::ConvertQuatROSToUE4(transform.GetRotation());

	return FTransform(Quat, Vector);
}