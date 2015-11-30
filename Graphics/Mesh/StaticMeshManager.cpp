#include "StaticMeshManager.h"


CStaticMeshManager::CStaticMeshManager()
{
}


CStaticMeshManager::~CStaticMeshManager()
{
}


bool CStaticMeshManager::Load(const std::string &FileName)
{
	m_FileName = FileName;

	CXMLTreeNode l_XML;
	if (l_XML.LoadFile(FileName.c_str()))
	{
		CXMLTreeNode l_Meshes = l_XML["static_meshes"];
		if (l_Meshes.Exists())
		{
			for (int i = 0; i < l_Meshes.GetNumChildren(); ++i)
			{
				CXMLTreeNode l_Mesh = l_Meshes(i);

				if (l_Mesh.GetName() == std::string("static_mesh"))
				{
					CStaticMesh * Mesh = new CStaticMesh(l_Mesh);
					AddResource(Mesh->GetName(), Mesh);
				}
			}
		}
	}
	return true;
}


bool CStaticMeshManager::Reload()
{
	return true;
}