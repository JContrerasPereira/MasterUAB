#include "Application.h"

#include "Math\Matrix44.h"
#include "Math\Vector4.h"

#include "ContextManager.h"
#include "DebugRender.h"
#include "SphericalCameraController.h"
#include "InputManager.h"

CApplication::CApplication(CDebugRender *_DebugRender, CContextManager *_ContextManager, CSphericalCameraController _Camera)
	: m_DebugRender(_DebugRender)
	, m_ContextManager(_ContextManager)
	, m_WorldRotation(0)
	, m_Camera(_Camera)
{
}


CApplication::~CApplication()
{
}


void CApplication::Update(float _ElapsedTime)
{
	Vect3f cameraMovement(0,0,0);

	if (CInputManager::GetInputManager()->IsActionActive("MOVE_LEFT"))
	{
		cameraMovement.x += 0.01f * _ElapsedTime;
	}
	if (CInputManager::GetInputManager()->IsActionActive("MOVE_RIGHT"))
	{
		cameraMovement.x -= 0.01f * _ElapsedTime;
	}
	if (CInputManager::GetInputManager()->IsActionActive("MOVE_UP"))
	{
		cameraMovement.y += 0.01f * _ElapsedTime;
	}
	if (CInputManager::GetInputManager()->IsActionActive("MOVE_DOWN"))
	{
		cameraMovement.y -= 0.01f * _ElapsedTime;
	}

	m_Camera.Update(_ElapsedTime, cameraMovement);

}

void CApplication::Render()
{
	m_ContextManager->BeginRender();

	CCamera camera;

	camera.SetFOV(1.047f);
	camera.SetAspectRatio(m_ContextManager->GetAspectRatio());
	camera.SetZNear(0.1f);
	camera.SetZFar(50.f);

	camera.SetPosition(Vect3f(5, 10, 20));
	camera.SetLookAt(Vect3f(0, 0, 0));
	camera.SetUp(Vect3f(0, 1, 0));

	camera.SetMatrixs();

	Mat44f world;

	world.SetIdentity();
	world.RotByAnglesYXZ(m_WorldRotation, 0, 0);

	m_Camera.SetCamera(&camera);

	/*
	Mat44f world, view, projection;
	view.SetIdentity();
	view.SetFromLookAt(Vect3f(5, 10, 20), Vect3f(0, 0, 0), Vect3f(0, 1, 0));

	projection.SetIdentity();
	projection.SetFromPerspective(1.047f, 8.0f / 6.0f, 0.1f, 50.0f);
	*/

	m_ContextManager->SetWorldMatrix(world);
	m_ContextManager->SetCamera(camera);

	m_ContextManager->SetDebugSize(5);
	m_ContextManager->SetBaseColor(CColor(1, 1, 1, 1));

	m_ContextManager->Draw(m_DebugRender->GetSimpleCube(), CContextManager::RS_SOLID);


	m_ContextManager->EndRender();
}
