#pragma once
#include "../ECore/ECommon.h"

namespace E3D 
{
	enum RenderMode
	{
		RENDER_WIRE,	//线框渲染
		RENDER_SOILD,	//实体渲染
	};
	class ECamera
	{
	public:
		//ECamera();
		~ECamera();

		void update();

		//设置近裁剪面得距离
		void setZNear(EFloat znear);

		//设置远裁剪面的距离
		void setZfar(EFloat zfar);

		//设置相机世界坐标
		void setPosition(const EVector3D& pos);

		//设置相机的观察视点,当lockTarget为true时，锁定观察视点
		void setTarget(const EVector3D& target, EBool lockTarget = false);
		void releaseTarget() { mLockTarget = false; };

		//基于世界坐标系移动
		void move(const EVector3D&mov);

		//基于相机自身坐标系移动
		void moveRelative(const EVector3D&mov);

		//绕Y轴旋转
		void yaw(EFloat yDegree);

		//绕x轴旋转
		void pich(EFloat pDegree);

		//设置渲染模式，线框或实体
		void setRenderMode(RenderMode mode) { mRenderMode = mode; }
		RenderMode getRenderMode() const { return mRenderMode; }

		EFrustum* getFrustum()const { return mFrustum; }
	protected:
		friend class ESceneManager;
		ECamera();

		EFrustum* mFrustum;

		EBool mLockTarget;

		EBool mNeedUpdate;

		RenderMode mRenderMode;
	private:

	};
}