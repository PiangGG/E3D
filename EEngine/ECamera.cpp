#include "ECamera.h"
#include "../ECore/EFrustum.h"

namespace E3D
{
	ECamera::ECamera():mLockTarget(false),mNeedUpdate(true),mRenderMode(RENDER_SOILD)
	{
		mFrustum = new EFrustum(CAMERA_MODEL_UVN,EVector4D::ZERO,EVector4D::ZERO,EVector4D::ZERO,10,1000,75,SCREEN_WIDTH,SCREEN_HEIGHT);
		update();
	}
	ECamera::~ECamera()
	{
		SafeDelete(mFrustum);
	}

	void ECamera::update()
	{
		if (mNeedUpdate)
		{
			EMatrix44 mt_inv;

			GetTranslateMatrix44(mt_inv,-mFrustum->position.x, -mFrustum->position.y, -mFrustum->position.z);
			//注视点-位置=注视方向
			mFrustum->camLook = mFrustum->camTarget - mFrustum->position;

			mFrustum->camUP = EVector4D::UNIT_Y;
			mFrustum->camRight = mFrustum->camUP.crossProduct(mFrustum->camLook);
			mFrustum->camUP	 = mFrustum->camLook.crossProduct(mFrustum->camRight);

			mFrustum->camLook.normalize();
			mFrustum->camRight.normalize();
			mFrustum->camUP.normalize();

			EMatrix44 mt_uvn(	mFrustum->camRight.x, mFrustum->camUP.x, mFrustum->camLook.x, 0,
								mFrustum->camRight.y, mFrustum->camUP.y, mFrustum->camLook.y, 0,
								mFrustum->camRight.z, mFrustum->camUP.z, mFrustum->camLook.z, 0,
								0,0,0,1);	
			mFrustum->mWorldToCamera = mt_inv * mt_uvn;

			mNeedUpdate = false;
		}
	}

	void ECamera::setZNear(EFloat znear)
	{
		mFrustum->clip_z_near = znear;
		mNeedUpdate = true;
	}

	void ECamera::setZfar(EFloat zfar)
	{
		mFrustum->clip_z_far = zfar;
		mNeedUpdate = true;
	}

	void ECamera::setPosition(const EVector3D& pos)
	{
		mFrustum->position.x = pos.x;
		mFrustum->position.y = pos.y;
		mFrustum->position.z = pos.z;
	}

	void ECamera::setTarget(const EVector3D& target, EBool lockTarget)
	{
		mFrustum->camTarget.x = target.x;
		mFrustum->camTarget.y = target.y;
		mFrustum->camTarget.z = target.z;

		mLockTarget = lockTarget;
		mNeedUpdate = true;
	}

	void ECamera::move(const EVector3D& mov)
	{
		mFrustum->position.x += mov.x;
		mFrustum->position.y += mov.y;
		mFrustum->position.z += mov.z;

		if (!mLockTarget)
		{
			mFrustum->camTarget.x = mov.x;
			mFrustum->camTarget.y = mov.y;
			mFrustum->camTarget.z = mov.z;
		}
		mNeedUpdate = true;
	}

	void ECamera::moveRelative(const EVector3D& mov)
	{
		EVector4D offset = mFrustum->camRight * mov.x+	mFrustum->camUP*mov.y+mFrustum->camLook*mov.z;
		mFrustum->position = mFrustum->position + offset;
		if (!mLockTarget)
		{
			mFrustum->camTarget = mFrustum->camTarget + offset;
		}
		mNeedUpdate = true;	
	}

	void ECamera::yaw(EFloat yDegree)
	{
		EMatrix44 rotMat;
		EVector4D distence = mFrustum->camTarget - mFrustum->position;
		GetRotateMatrix44(rotMat,mFrustum->camUP,yDegree);
		GetVector4DMulMatrix44(distence,rotMat,distence);

		//旋转后的目标点
		mFrustum->camTarget = distence + mFrustum->position;
		mNeedUpdate = true;
	}

	void ECamera::pich(EFloat pDegree)
	{
		EMatrix44 rotMat;
		EVector4D distence = mFrustum->camTarget - mFrustum->position;
		GetRotateMatrix44(rotMat, mFrustum->camRight, pDegree);
		GetVector4DMulMatrix44(distence, rotMat, distence);

		//旋转后的目标点
		mFrustum->camTarget = distence + mFrustum->position;
		mNeedUpdate = true;
	}

}