#pragma once
#include "ROSBridgeMsg.h"

/*
	http://docs.ros.org/api/control_msgs/html/msg/JointTolerance.html
*/
namespace control_msgs
{
	class JointTolerance : public FROSBridgeMsg
	{
		FString	Name;
		double  Position;  // in radians or meters (for a revolute or prismatic joint, respectively)
		double 	Velocity;  // in rad/sec or m/sec
		double 	Acceleration;  // in rad/sec^2 or m/sec^2

	public:
		JointTolerance()
		{
			MsgType = "control_msgs/JointTolerance";
		}

		JointTolerance(
			const FString InName,
			const double InPosition,
			const double InVelocity,
			const double InAcceleration):
			Name(InName),
			Position(InPosition),
			Velocity(InVelocity),
			Acceleration(InAcceleration)
		{
			MsgType = "control_msgs/JointTolerance";
		}

		~JointTolerance() override {}

		FString GetName() const
		{
			return Name;
		}

		double GetPosition() const
		{
			return Position;
		}

		double GetVelocity() const
		{
			return Velocity;
		}

		double GetAcceleration() const
		{
			return Acceleration;
		}

		void SetName(const FString& InName)
		{
			Name = InName;
		}

		void SetPosition(const double InPosition)
		{
			Position = InPosition;
		}

		void SetVelocity(const double InVelocity)
		{
			Velocity = InVelocity;
		}

		void SetAcceleration(const double InAcceleration)
		{
			Acceleration = InAcceleration;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Name = JsonObject->GetStringField(TEXT("name"));
			Position = (double)(JsonObject->GetNumberField(TEXT("position")));
			Velocity = (double)(JsonObject->GetNumberField(TEXT("velocity")));
			Acceleration = (double)(JsonObject->GetNumberField(TEXT("acceleration")));
		}
		static JointTolerance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			JointTolerance Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("JointTolerance { name = ") + Name +
				TEXT(", position = ") + FString::SanitizeFloat(Position) +
				TEXT(", velocity = ") + FString::SanitizeFloat(Velocity) +
				TEXT(", acceleration = ") + FString::SanitizeFloat(Acceleration) +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetStringField(TEXT("name"), Name);
			Object->SetNumberField(TEXT("position"), Position);
			Object->SetNumberField(TEXT("velocity"), Velocity);
			Object->SetNumberField(TEXT("acceleration"), Acceleration);
			return Object;
		}

		virtual FString ToYamlString() const override 
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
} // namespace control_msgs