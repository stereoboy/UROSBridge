#pragma once
#include "ROSBridgeMsg.h"
#include "std_msgs/String.h"
#include "std_msgs/Header.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"

/*
	http://docs.ros.org/api/trajectory_msgs/html/msg/JointTrajectory.html
*/
namespace trajectory_msgs
{
	class JointTrajectory : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		TArray<FString> JointNames;
		TArray<trajectory_msgs::JointTrajectoryPoint> Points;
	public:
		JointTrajectory()
		{
			MsgType = "trajectory_msgs/JointTrajectory";
		}

		JointTrajectory(
			std_msgs::Header InHeader,
			const TArray<FString>& InJointNames, 
			const TArray<trajectory_msgs::JointTrajectoryPoint>& InPoints):
			Header(InHeader),
			JointNames(InJointNames),
			Points(InPoints)
		{
			MsgType = "trajectory_msgs/JointTrajectory";
		}

		~JointTrajectory() override {}

		std_msgs::Header GetHeader() const 
		{
			return Header;
		}

		TArray<FString> GetJointNames() const
		{
			return JointNames;
		}

		TArray<trajectory_msgs::JointTrajectoryPoint> GetPoints() const
		{
			return Points;
		}

		void SetHeader(std_msgs::Header InHeader) 
		{ 
			Header = InHeader; 
		}

		void SetPositions(const TArray<FString>& InJointNames)
		{
			JointNames = InJointNames;
		}

		void SetVelocities(const TArray<trajectory_msgs::JointTrajectoryPoint>& InPoints)
		{
			Points = InPoints;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			JointNames.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("joint_names"));
			for (auto &ptr : ValuesPtrArr)
				JointNames.Add(ptr->AsString());

			Points.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : ValuesPtrArr)
			{
				trajectory_msgs::JointTrajectoryPoint point = trajectory_msgs::JointTrajectoryPoint::GetFromJson(ptr->AsObject());
				Points.Add(point);
			}
		}
		static JointTrajectory GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			JointTrajectory Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString JointNameString = "[ ";
			for (auto &value : JointNames)
				JointNameString += value + TEXT(", ");
			JointNameString += " ]";

			FString PointString = "[ ";
			for (auto &value : Points)
				PointString += value.ToString() + TEXT(", ");
			PointString += " ]";

			return TEXT("JointTrajectoryPoint { header = ") + Header.ToString() +
				TEXT(", joint_names = ") + JointNameString +
				TEXT(", points = ") + PointString +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> JointNameArray, PointArray;
			for (auto &str : JointNames)
				JointNameArray.Add(MakeShareable(new FJsonValueString(str)));
			
			for (auto &val : Points)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(val.ToJsonObject()));
				PointArray.Add(Ptr);
			}
				
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetArrayField(TEXT("joint_names"), JointNameArray);
			Object->SetArrayField(TEXT("points"), PointArray);
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