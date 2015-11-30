fn Init = 
(
	format "____Init____\n"
)		

fn GetLevelName =
(
	return "C:\Users\Jose\Documents\MasterUAB\bin\VideogameTest\Data\\"
)

fn GetCores =
(
	return $*
)

fn GetInstances =
(
	return $*
)

fn createStaticMeshes =
(
	local file=createfile (GetLevelName()+"Meshes\\static_meshes.xml" )
	local cores = GetCores()
	format "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" to:file
	format "<static_meshes>\n" to:file
	for i=1 to cores.count do
	(
		format "\t<static_mesh name=\"%\" filename=\"%.mesh\"/>\n" cores[i].name (GetLevelName()+cores[i].name) to:file
	)	
	format "</static_meshes>\n" to:file 
	format "____CreatedStatic____\n"
	close file
)
	
fn createRenderableObjects =
(
	local file=createfile (GetLevelName()+"renderable_objects.xml" )
	local instances = GetInstances()
	format "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" to:file
	format "<renderable_objects>\n" to:file
	for i=1 to instances.count do
	(
		Pos = TranslationToRH(instances[i].transform.translation)
		Yaw = GetYaw(instances[i].transform)
		Pitch = GetPitch(instances[i].transform)
		Roll = GetRoll(instances[i].transform)
		format "\t<mesh_instance name=\"%\" core_name=\"%\" pos=\"% % %\" yaw=\"%\" pitch=\"%\" roll=\"%\" visible=\"%\"/>\n" instances[i].name instances[i].name Pos[1] Pos[2] Pos[3] Yaw Pitch Roll instances[i].visibility to:file
	)
	format "</renderable_objects>\n" to:file 
	format "____CreatedRenderableObjects____\n"
	close file
)	

fn createMaterials =
(
	local file=createfile (GetLevelName()+"materials.xml" )
	
	local cores = GetCores()
	format "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" to:file
	format "<materials>\n" to:file
	for i=1 to cores.count do
	( --undefined
		if classof cores[i].material == Standardmaterial then
		(			
			format "\t<material name=\"%\" effect_technique=\"diffuse_technique\" >\n" cores[i].material.name (GetLevelName()+cores[i].material.name) to:file		
			if cores[i].material.diffuseMap != undefined and cores[i].material.diffuseMap.bitmap != undefined then --TODO: comprobar difuso no bitmap??
			(
				format "\t\t <texture filename=\"%\"/>\n" cores[i].material.diffuseMap.filename to:file
			)
			else
			(
				messageBox ("¡¡¡El material "+cores[i].material.name+" de la malla "+cores[i].name+" tiene las texturas mal!!!") title:"MENSAJE PARA ARTISTAS" 
			)
			format "\t</material>\n" to:file 
		)
		else
		(
			for j = 1 to cores[i].material.numsubs do
			(
				--Si ya existe no exportamos
				format "\t<material name=\"%\" effect_technique=\"diffuse_technique\" >\n" cores[i].material[j].name (GetLevelName()+cores[i].material[j].name) to:file	
				if cores[i].material[j].diffuseMap != undefined and cores[i].material[j].diffuseMap.bitmap != undefined then --TODO: comprobar difuso no bitmap??
				(
					format "\t\t <texture filename=\"%\"/>\n" cores[i].material[j].diffuseMap.filename to:file
				)
				else
				(
					messageBox ("¡¡¡El material "+cores[i].material.name+" de la malla "+cores[i].name+" tiene las texturas mal!!!") title:"MENSAJE PARA ARTISTAS" 
				)
				format "\t</material>\n" to:file 
			)
		)
	)
	
	format "</materials>\n" to:file 
	format "____CreatedMaterials____\n"
	close file
)

fn createMeshes =
(
	local cores = GetCores()
	
	for i=1 to cores.count do
	(
		core_mesh = convertToMesh cores[i]
		createMesh(core_mesh)
	)
)

global file

function ConvertVtx Vtx =
(
	local l_Text = stringstream ""
	local l_Value=""
	
	for i=1 to Vtx.count do
	(
		format "%," Vtx[i] to:l_Text
	)
	
	return (l_Text as string)
)

function DotNetAddVertex VtxArray VtxMap Vtx =
(
	local l_VtxString=ConvertVtx Vtx
	local l_Idx=1
	
	if (VtxMap.ContainsKey (l_VtxString))==false then
	(
		l_Idx=VtxArray.count
		append VtxArray Vtx
		VtxMap.Add l_VtxString l_Idx
	)
	else
	(
		l_Idx=VtxMap.Item[l_VtxString]
	)
	
	return l_Idx
)

fn createMesh obj =
(
	file = fopen  (GetLevelName()+"Meshes\\"+obj.name+".mesh" ) "wb"
	
	--Header
	writeshort file 0xFE55
	
	local numMats
	
	--Materials
	if classof obj.material == Standardmaterial then
	(
		numMats=1
		writeshort file 1
		writeshort file obj.material.name.count
		writestring file obj.material.name
	)
	else
	(
		numMats = obj.material.numsubs
		writeshort file obj.material.numsubs
		for mats=1 to obj.material.numsubs do
		(
			writeshort file obj.material[mats].name.count
			writestring file obj.material[mats].name
		)
	)
	
	--Vertex
	local l_VtxsMap = dotnetobject "System.Collections.Generic.Dictionary`2[System.String,System.Int16]"
	global idxs = #()
	global vtxs = #()
	
	--TODO: Evitar duplicados
	for i=1 to numMats do
	(
		writeshort file 19 --vertexType
		NumVertex = getNumVerts obj
		writeshort file NumVertex --TODO: coger vertices afectados por ese mat...
		NumFaces = getNumFaces obj
		for numFace = 1 to NumFaces do
		(
			global face = getFace obj numFace
			global matID = getFaceMatID obj numFace
			--writeshort file createVertex(obj IdxsFace)
			for numVtx = 1 to 3 do
			(
				vert = getVert obj face[numVtx]
				global vtx = createVertex  obj numVtx
				local idx = DotNetAddVertex vtxs l_VtxsMap vtx
				append idxs idx
			)
		)	
	)
	
	writeshort file vtxs.count
	
	for idVtx = 1 to vtxs.count do
	(
		global vtx = vtxs[idVtx]
		global idPrp = 1
		for idPrp = 1 to vtx.count do
		(
			writefloat file vtx[1][idPrp]
		)
	)
	
	writeshort file idxs.count
	
	for idx = 1 to idxs.count do
	(
		writeshort file idxs[idx]
	)
	
	--Index
	/*
	writeshort file 16 --Tamaño indice
	for i=1 to numMats do (
		
		for numFace = 1 to getNumFaces obj do (
			writeshort file getFace obj numFace 
		)
	)
	*/
	
	--Footer
	writeshort file 0xFE55
		
	fflush file
	fclose file
	
)


fn createVertex obj Idx =
(
	-- Para coger los vértices de la primera cara
	local Vtx1=getVert obj Idx
	-- Para coger las normales de los vértices de la primera cara
	local Normal1=getNormal obj Idx
	-- Para coger los índices de las coordenadas de textura de la primera cara, el 1 señala al primer
	--conjunto de coordenadas aplicadas sobre la cara 
	local IdxsMap=meshop.getMapFace obj 1 Idx
	-- Para coger las coordenadas de los vértices de la primera cara
	local TUVMap1= meshop.getMapVert obj 1 IdxsMap.x
	local TUVMap2= meshop.getMapVert obj 1 IdxsMap.y
	local TUVMap3= meshop.getMapVert obj 1 IdxsMap.z 
	
	return #(Vtx1, Normal1, TUVMap1)

)

fn GetYaw transform =
(
	return -(transform as eulerangles).z
)
fn GetPitch transform =
(
	return -(transform as eulerangles).y
)
fn GetRoll transform =
(
	return (transform as eulerangles).x
) 


fn TranslationToRH translation =
(
	return point3 -translation.x translation.z translation.y
) 
	
	
Init()
createStaticMeshes()
createRenderableObjects()
createMaterials()
createMeshes()

