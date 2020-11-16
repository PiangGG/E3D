#include "EFrustum.h"

namespace E3D 
{
	EFrustum::EFrustum(CAMERA_TYPE mode, const EVector4D& pos, const EVector4D& dir, const EVector4D& target, EFloat nearZ, EFloat farZ, EFloat ffov, EFloat viewportWidth, EFloat viewprotHeight)
	:camMode(mode),position(pos),dirction(dir),camTarget(target),clip_z_near(nearZ),clip_z_far(farZ),fov(ffov),viewplane_width(viewportWidth),viewplane_height(viewprotHeight),
	camUP(EVector4D::UNIT_Y),camRight(EVector4D::UNIT_Y),camLook(EVector4D::UNIT_Z),mWorldToCamera(EMatrix44::IDENTUTY),mCameraToPerspective(EMatrix44::IDENTUTY),mPerspectiveToScreen(EMatrix44::IDENTUTY)
	{
		viewport_center_X = (viewplane_width - 1) * 0.5;
		viewport_center_Y = (viewplane_height - 1) * 0.5;

		aspect_ratio = viewplane_width/viewplane_height;		//

		viewplane_width = 2.0f;
		viewplane_height = 2.0f / aspect_ratio;

		EFloat tan_fov_div2 = tan(Degree_TO_Radian(fov*0.5));
		view_dist = 0.5f * viewplane_width / tan_fov_div2;

		//设置裁剪平面
		//裁剪平面坐标是基于摄像机坐标系的
		EVector4D point = EVector4D::ZERO;
		//右裁剪平面
		EVector4D normalR = EVector4D(-view_dist,0,viewplane_width*0.5);
		clip_plane_R = EPlane3D(point, normalR);
		
		//左裁剪面
		EVector4D normalL = EVector4D(view_dist, 0, viewplane_width * 0.5);
		clip_plane_L = EPlane3D(point, normalL);

		//上裁剪面
		EVector4D normalT = EVector4D(0,-view_dist, viewplane_height * 0.5);
		clip_plane_T= EPlane3D(point, normalL);

		//下裁剪面
		EVector4D normalB = EVector4D(0, view_dist, viewplane_height * 0.5);
		clip_plane_B = EPlane3D(point, normalL);

		//摄像机坐标系到透视坐标系变换矩阵，经过矩阵变换后需除以w
		mPerspectiveToScreen = EMatrix44(	view_dist,0,0,0,
											0,view_dist,0,0,
											0,0,1,1,
											0,0,0,0);
	}
}

