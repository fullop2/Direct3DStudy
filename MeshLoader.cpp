#include <fstream>

#include "MeshLoader.h"
#include "Vertex.h"


MeshLoader::MeshLoader(LPDIRECT3DDEVICE9 device)
	:mDevice(device)
{
}


MeshLoader::~MeshLoader()
{
}


// use MeshLoader10 Direct X example
HRESULT MeshLoader::Create(LPCSTR dir, C3DModel* model)
{/*
	WCHAR strMaterialFilename[MAX_PATH] = { 0 };
	WCHAR wstr[MAX_PATH];
	char str[MAX_PATH];
	HRESULT hr;

	
	vector<D3DXVECTOR3> Positions;
	vector<D3DXVECTOR2> TexCoords;
	vector<D3DXVECTOR3> Normals;

	vector<DWORD> m_Indices; 

	// File input
	WCHAR strCommand[256] = { 0 };
	std::wifstream InFile(str);
	if (!InFile)
		return E_FAIL;

	for (; ; )
	{
		InFile >> strCommand;
		if (!InFile)
			break;

		if (0 == wcscmp(strCommand, L"#"))
		{
			// Comment
		}
		else if (0 == wcscmp(strCommand, L"v"))
		{
			// Vertex Position
			float x, y, z;
			InFile >> x >> y >> z;
			Positions.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (0 == wcscmp(strCommand, L"vt"))
		{
			// Vertex TexCoord
			float u, v;
			InFile >> u >> v;
			TexCoords.push_back(D3DXVECTOR2(u, v));
		}
		else if (0 == wcscmp(strCommand, L"vn"))
		{
			// Vertex Normal
			float x, y, z;
			InFile >> x >> y >> z;
			Normals.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (0 == wcscmp(strCommand, L"f"))
		{
			// Face
			UINT iPosition, iTexCoord, iNormal;
			TVertex vertex;

			for (UINT iFace = 0; iFace < 3; iFace++)
			{
				ZeroMemory(&vertex, sizeof(TVertex));

				// OBJ format uses 1-based arrays
				InFile >> iPosition;
				{
					vertex._x = Positions[iPosition - 1].x;
					vertex._y = Positions[iPosition - 1].y;
					vertex._z = Positions[iPosition - 1].z;
				}

				if ('/' == InFile.peek())
				{
					InFile.ignore();

					if ('/' != InFile.peek())
					{
						// Optional texture coordinate
						InFile >> iTexCoord;
						{
							vertex._u = TexCoords[iTexCoord - 1].x;
							vertex._v = TexCoords[iTexCoord - 1].y;
						}
					}

					if ('/' == InFile.peek())
					{
						InFile.ignore();

						// Optional vertex normal
						InFile >> iNormal;
						{
							vertex._x = Normals[iNormal - 1].x;
							vertex._y = Normals[iNormal - 1].y;
							vertex._z = Normals[iNormal - 1].z;
						}
					}
				}

				// If a duplicate vertex doesn't exist, add this vertex to the Vertices
				// list. Store the index in the Indices array. The Vertices and Indices
				// lists will eventually become the Vertex Buffer and Index Buffer for
				// the mesh.
				DWORD index = AddVertex(iPosition, &vertex);
				m_Indices.push_back(index);
			}
			m_Attributes.Add(dwCurSubset);
		}
		else if (0 == wcscmp(strCommand, L"mtllib"))
		{
			// Material library
			InFile >> strMaterialFilename;
		}
		else if (0 == wcscmp(strCommand, L"usemtl"))
		{
			// Material
			WCHAR strName[MAX_PATH] = { 0 };
			InFile >> strName;

			bool bFound = false;
			for (int iMaterial = 0; iMaterial < m_Materials.GetSize(); iMaterial++)
			{
				Material* pCurMaterial = m_Materials.GetAt(iMaterial);
				if (0 == wcscmp(pCurMaterial->strName, strName))
				{
					bFound = true;
					dwCurSubset = iMaterial;
					break;
				}
			}

			if (!bFound)
			{
				pMaterial = new Material();
				if (pMaterial == NULL)
					return E_OUTOFMEMORY;

				dwCurSubset = m_Materials.GetSize();

				InitMaterial(pMaterial);
				wcscpy_s(pMaterial->strName, MAX_PATH - 1, strName);

				m_Materials.Add(pMaterial);
			}
		}
		else
		{
			// Unimplemented or unrecognized command
		}

		InFile.ignore(1000, '\n');
	}

	// Cleanup
	InFile.close();
	*/

	return S_OK;
}