#include "RenderableObjectsManager.h"
#include "InstanceMesh.h"

CRenderableObjectsManager::CRenderableObjectsManager()
{
}


CRenderableObjectsManager::~CRenderableObjectsManager()
{
	Destroy();
}


void CRenderableObjectsManager::Update(float ElapsedTime)
{
	for (int i = 0; i < m_ResourcesVector.size(); ++i)
	{
		m_ResourcesVector[i]->Update(ElapsedTime);
	}
}


void CRenderableObjectsManager::Render(CRenderManager *RM)
{
	for (int i = 0; i < m_ResourcesVector.size(); ++i)
	{
		m_ResourcesVector[i]->Render(RM);
	}
}


//No se si també s'hauria de llegir Yaw, Pitch, Roll y Visible, però com al constructor de moment no especifica no ho poso.
CRenderableObject * CRenderableObjectsManager::AddMeshInstance(CXMLTreeNode &TreeNode)
{
	std::string CoreName = TreeNode.GetPszProperty("core_name");
	std::string InstanceName = TreeNode.GetPszProperty("name");
	Vect3f Default(0.0f, 0.0f, 0.0f);
	Vect3f Position = TreeNode.GetVect3fProperty("pos", Default, false);

	return AddMeshInstance(CoreName, InstanceName, Position);
}


CRenderableObject * CRenderableObjectsManager::AddMeshInstance(const std::string &CoreMeshName, const std::string &InstanceName, const Vect3f &Position)
{
	TMapResources::iterator it = m_ResourcesMap.find(InstanceName);

	if (it != m_ResourcesMap.end())
	{
		return it->second.m_Value;
	}
	else
	{
		CInstanceMesh * Object = new CInstanceMesh(InstanceName, CoreMeshName);
		Object->SetPosition(Position);
		AddResource(InstanceName, Object);
		return Object;
	}
}


// TODO: Crec que va dir que aquests dos de moment no els fessim
CRenderableObject * CRenderableObjectsManager::AddAnimatedInstanceModel(CXMLTreeNode &TreeNode)
{
	return NULL;
}


CRenderableObject * CRenderableObjectsManager::AddAnimatedInstanceModel(const std::string &CoreModelName, const std::string &InstanceModelName, const Vect3f &Position)
{
	return NULL;
}


// TODO: No se si el path del fitxer s'ha de construir o el trobarà bé.
void CRenderableObjectsManager::Load(const std::string &FileName)
{
	CXMLTreeNode l_XML;
	if (l_XML.LoadFile(FileName.c_str()))
	{
		CXMLTreeNode l_Meshes = l_XML["renderable_objects"];
		if (l_Meshes.Exists())
		{
			for (int i = 0; i < l_Meshes.GetNumChildren(); ++i)
			{
				CXMLTreeNode l_Mesh = l_Meshes(i);

				if (l_Mesh.GetName() == std::string("mesh_instance"))
				{
					AddMeshInstance(l_Mesh);
				}
			}
		}
	}
}