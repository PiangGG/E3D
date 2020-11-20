#pragma once

#include "../ECore/ECommon.h"
#include "../ECore/ECore.h"
#include "../ECore/EMaterial.h"
#include "EObject.h"

namespace E3D 
{
	enum COLLSION_TYPE
	{
		COLLSION_COLLSION,
		COLLSION_IGNORE,
	};

	class EMesh:public EObject 
	{
	public:
		~EMesh();

		void setScale(const EVector3D &scale);
		void setPosition(const EVector3D &pos);
		EVector3D getPosition()const;
		void move(const EVector3D &move);

		//给定点是否在包围盒内，如果是则返回true，否则返回false
		EBool intersect(const EVector3D& point);

		//
		void setVisible(EBool visible) { mIsVisible = visible; }
		EBool isVisible()const { return mIsVisible; }

		//是否执行剔除操作
		void setCullFlag(EBool needCull) { mObject->needCull = needCull; }

		//绕y轴旋转
		void yaw(EFloat yDegree);
		//绕z轴旋转
		void roll(EFloat rDegree);
		//绕x轴旋转
		void pitch(EFloat pDegree);

		void setCullsionType(COLLSION_TYPE type) { mCollsionType = type; }
		COLLSION_TYPE getCollsionType() { return mCollsionType; }

		EMaterial* getMaterial(EInt index=0);
		void setMaterial(EInt index,EString matName);

		EObject4D* getObject()const { return mObject; }

		EInt getPolyonNumber()const { return mPolyonNumber; }
		EInt getVertexNumber()const { return mVertexNumber; }
		EInt getSubmeshNumber()const { return mSubmeshNumber; }

		//获取各轴的旋转分量，以角度表示
		EVector3D getRotateVec()const { return mRotate; }

		//对此模型进行读盘clone，避免再次读盘读取模型
		EMesh* clone();
		
	public:
		friend class ESceneManage;

		EMesh();

		EMesh(const EString& name, const EString& meshName);

		EObject4D* mObject;

		EInt mPolyonNumber;
		EInt mVertexNumber;
		EInt mSubmeshNumber;

		EVector3D mRotate;

		EBool mIsVisible;
		COLLSION_TYPE mCollsionType;
	};
}