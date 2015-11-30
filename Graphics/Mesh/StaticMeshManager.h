#ifndef STATIC_MESH_MANAGER_H
#define STATIC_MESH_MANAGER_H

#include "Utils\TemplatedMapManager.h"
#include "StaticMesh.h"

class CStaticMeshManager : public CTemplatedMapManager<CStaticMesh>
{
protected:
	std::string m_FileName;
public:
	CStaticMeshManager();
	~CStaticMeshManager();
	bool Load(const std::string &FileName);
	bool Reload();
};

#endif