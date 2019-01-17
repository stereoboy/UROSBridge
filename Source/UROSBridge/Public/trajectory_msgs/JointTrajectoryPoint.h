#pragma once
#include "ROSBridgeMsg.h"

/*
	http://docs.ros.org/api/trajectory_msgs/html/msg/JointTrajectoryPoint.html
*/
namespace trajectory_msgs
{
	class JointTrajectoryPoint : public FROSBridgeMsg
	{
		TArray<double> 	Positions;
		TArray<double> 	Velocities;
		TArray<double> 	Accelerations;
		TArray<double> 	Effort;
		FROSTime		TimeFromStart;

	public:
		JointTrajectoryPoint()
		{
			MsgType = "trajectory_msgs/JointTrajectoryPoint";
		}

		JointTrajectoryPoint(
			const TArray<double>& InPositions,
			const TArray<double>& InVelocities,
			const TArray<double>& InAccelerations,
			const TArray<double>& InEffort,
			const FROSTime InTimeFromStart):
			Positions(InPositions),
			Velocities(InVelocities),
			Accelerations(InAccelerations),
			Effort(InEffort)
		{
			MsgType = "trajectory_msgs/JointTrajectoryPoint";
		}

		~JointTrajectoryPoint() override {}

		TArray<double> GetPosition() const
		{
			return Positions;
		}

		TArray<double> GetVelocities() const
		{
			return Velocities;
		}

		TArray<double> GetAccelerations() const
		{
			return Accelerations;
		}

		TArray<double> GetEffort() const
		{
			return Effort;
		}

		FROSTime GetTimeFromStart() const
		{
			return TimeFromStart;
		}

		void SetPositions(const TArray<double>& InPositions)
		{
			Positions = InPositions;
		}

		void SetVelocities(const TArray<double>& InVelocities)
		{
			Velocities = InVelocities;
		}

		void SetAccelerations(const TArray<double>& InAccelerations)
		{
			Accelerations = InAccelerations;
		}

		void SetEffort(const TArray<double>& InEffort)
		{
			Effort = InEffort;
		}

		void SetTimeFromStart(const FROSTime InTimeFromStart)
		{
			TimeFromStart = InTimeFromStart;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Positions.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("positions"));
			for (auto &ptr : ValuesPtrArr)
				Positions.Add(ptr->AsNumber());

			Velocities.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("velocities"));
			for (auto &ptr : ValuesPtrArr)
				Velocities.Add(ptr->AsNumber());

			Accelerations.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("accelerations"));
			for (auto &ptr : ValuesPtrArr)
				Accelerations.Add(ptr->AsNumber());

			Effort.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("effort"));
			for (auto &ptr : ValuesPtrArr)
				Effort.Add(ptr->AsNumber());

			TimeFromStart = FROSTime::GetFromJson(JsonObject->GetObjectField(TEXT("time_from_start")));
		}
		static JointTrajectoryPoint GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			JointTrajectoryPoint Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString PositionString = "[ ";
			for (auto &value : Positions)
				PositionString += FString::SanitizeFloat(value) + TEXT(", ");
			PositionString += " ]";

			FString VelocityString = "[ ";
			for (auto &value : Velocities)
				VelocityString += FString::SanitizeFloat(value) + TEXT(", ");
			VelocityString += " ]";

			FString AccelerationString = "[ ";
			for (auto &value : Accelerations)
				AccelerationString += FString::SanitizeFloat(value) + TEXT(", ");
			AccelerationString += " ]";

			FString EffortString = "[ ";
			for (auto &value : Effort)
				EffortString += FString::SanitizeFloat(value) + TEXT(", ");
			EffortString += " ]";

			return TEXT("JointTrajectoryPoint { position = ") + PositionString +
				TEXT(", velocities = ") + VelocityString +
				TEXT(", accelerations = ") + AccelerationString +
				TEXT(", effort = ") + EffortString +
				TEXT(", time_from_start = ") + TimeFromStart.ToString() +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> PositionArray, VelocityArray, AccelerationArray, EffortArray;
			for (auto &val : Positions)
				PositionArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : Velocities)
				VelocityArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : Accelerations)
				AccelerationArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : Effort)
				EffortArray.Add(MakeShareable(new FJsonValueNumber(val)));

			Object->SetArrayField(TEXT("positions"), PositionArray);
			Object->SetArrayField(TEXT("velocities"), VelocityArray);
			Object->SetArrayField(TEXT("accelerations"), VelocityArray);
			Object->SetArrayField(TEXT("effort"), EffortArray);
			Object->SetObjectField(TEXT("time_from_start"), TimeFromStart.ToJsonObject());

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
} // namespace trajectory_msgs