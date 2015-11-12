#pragma once

class CDebugRender;
class CContextManager;
class CSphericalCameraController;

class CApplication
{
public:
	CApplication(CDebugRender *_DebugRender, CContextManager *_ContextManager, CSphericalCameraController *_Camera);
	~CApplication();

	void Update(float _ElapsedTime);
	void Render();

private:

	CDebugRender *m_DebugRender;
	CContextManager *m_ContextManager;
	CSphericalCameraController *m_Camera;

	float m_WorldRotation;
};

