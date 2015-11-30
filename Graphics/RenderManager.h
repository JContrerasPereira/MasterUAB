#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "Camera\Camera.h"
#include "Camera\Frustum.h"
#include "RenderableObject\RenderableObject.h"
#include <vector>
#include <d3d11.h>

class CContextManager;
class CMaterialManager;

class CRenderManager
{
public:
	CRenderManager()
		: m_UseDebugCamera(false)
		, m_CurrentRenderlistLength(0)
	{
	}

	void SetCurrentCamera(const CCamera& _CurrentCamera);
	void SetDebugCamera(const CCamera& _DebugCamera) { m_DebugCamera = _DebugCamera; }

	void SetUseDebugCamera(bool _use) { m_UseDebugCamera = _use; }

	ID3D11Device * GetDevice() const { return m_D3DDevice; }
	ID3D11DeviceContext * GetDeviceContext() const { return m_DeviceContext; }

	void SetDevice(ID3D11Device * Device) { m_D3DDevice = Device; }
	void SetDeviceContext(ID3D11DeviceContext * DeviceContext) { m_DeviceContext = DeviceContext; }

	bool AddRenderableObjectToRenderList(const CRenderableObject* _RenderableObject);

	void Render(CContextManager* _Context, CMaterialManager* _MaterialManager);

private:
	ID3D11Device *m_D3DDevice;
	ID3D11DeviceContext *m_DeviceContext;
	CCamera m_CurrentCamera;
	CFrustum m_CullFrustum;
	CCamera m_DebugCamera;
	bool m_UseDebugCamera;

	size_t m_CurrentRenderlistLength;
	std::vector<const CRenderableObject*> m_RenderableObjects;

};

#endif