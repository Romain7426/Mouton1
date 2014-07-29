#ifndef _3DS_H
#define _3DS_H




typedef unsigned char BYTE;


//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////
// 
// This file includes all of the model structures that are needed to load
// in a .3DS file.  If you intend to do animation you will need to add on
// to this.  These structures only support the information that is needed
// to load the objects in the scene and their associative materials.

enum { MAX_TEXTURES = 100 };  // The maximum amount of textures to load

// This is our 3D point class.  This will be used to store the vertices of our model.
struct CVector3 {
//public:
  float x, y, z;
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(CVector3);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CVector3);


// This is our 2D point struct.  This will be used to store the UV coordinates.
struct CVector2 {
//public:
  float x, y;
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(CVector2);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CVector2);

// This is our face structure.  This is is used for indexing into the vertex 
// and texture coordinate arrays.  From this information we know which vertices
// from our vertex array go to which face, along with the correct texture coordinates.
struct tFace {
  int vertIndex[3];           // indicies for the verts that make up this triangle
  int coordIndex[3];          // indicies for the tex coords to texture this face
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(tFace);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(tFace);

// This holds the information for a material.  It may be a texture map of a color.
// Some of these are not used, but I left them because you will want to eventually
// read in the UV tile ratio and the UV tile offset for some models.
struct tMaterialInfo {
  char  strName[255];         // The texture name
  char  strFile[255];         // The texture file name (If this is set it's a texture map)
  BYTE  color[3];             // The color of the object (R, G, B)
  int   texureId;             // the texture ID
  float uTile;                // u tiling of texture  (Currently not used)
  float vTile;                // v tiling of texture  (Currently not used)
  float uOffset;              // u offset of texture  (Currently not used)
  float vOffset;              // v offset of texture  (Currently not used)
} ;
DEFINE_NEW_OPERATOR_FOR_STRUCT(tMaterialInfo);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(tMaterialInfo);;

// This holds all the information for our model/scene. 
// You should eventually turn into a robust struct that 
// has loading/drawing/querying functions like:
// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
struct t3DObject {
  int  numOfVerts;            // The number of verts in the model
  int  numOfFaces;            // The number of faces in the model
  int  numTexVertex;          // The number of texture coordinates
  int  materialID;            // The texture ID to use, which is the index into our texture array
  bool bHasTexture;           // This is TRUE if there is a texture map for this object
  char strName[255];          // The name of the object
  CVector3  *pVerts;          // The object's vertices
  CVector3  *pNormals;        // The object's normals
  CVector2  *pTexVerts;       // The texture's UV coordinates
  tFace *pFaces;              // The faces information of the object
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(t3DObject);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(t3DObject);

// This holds our model information.  This should also turn into a robust struct.
// We use STL's (Standard Template Library) vector struct to ease our link list burdens. :)
struct t3DModel {
  int numOfObjects;                   // The number of objects in the model
  int numOfMaterials;                 // The number of materials for the model
#if 0
  vector<tMaterialInfo> pMaterials;   // The list of material information (Textures and colors)
  vector<t3DObject> pObject;          // The object list for our model
#else
  tMaterialInfo * pMaterials;   // The list of material information (Textures and colors)
  t3DObject * pObject;          // The object list for our model
#endif
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(t3DModel);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(t3DModel);


//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


//extern int VideoFlags;                                    // The Pixel Format flags
//extern SDL_Surface * MainWindow;                        // Our Drawable portion of the window

//void CreateTexture(unsigned int textureArray[],char *strFileName,int textureID);



/////////////////////////////////////////////////////////////////////////////////
////
//// * QUICK NOTES *
////
//// This file includes all the structures that you need to hold the model data.
//// Of course, if you want a robust loader, you need some more things for animation, etc..
//// If you intend to use this code, I would make the model and object structures structes.
//// This way you can have a bunch of helper functions like Import(), Translate(), Render()...
////
//// * What's An STL (Standard Template Library) Vector? *
//// Let me quickly explain the STL vector for those of you who are not familiar with them.
//// To use a vector you must include <vector> and use the std namespace: using namespace std;
//// A vector is an array based link list.  It allows you to dynamically add and remove nodes.
//// This is a template struct so it can be a list of ANY type.  To create a vector of type
//// "int" you would say:  vector<int> myIntList;
//// Now you can add a integer to the dynamic array by saying: myIntList.push_back(10);
//// or you can say:  myIntList.push_back(num);.  The more you push back, the larger
//// your array gets.  You can index the vector like an array.  myIntList[0] = 0;
//// To get rid of a node you use the pop_back() function.  To clear the vector use clear().
//// It frees itself so you don't need to worry about it, except if you have data
//// structures that need information freed from inside them, like our objects.
////
//// The Import() function would decide which loader it needed to call, depending on the extension.
////
////
////
//// Ben Humphrey (DigiBen)
//// Game Programmer
//// DigiBen@GameTutorials.com
//// Co-Web Host of www.GameTutorials.com
////
////










































//>------ Primary Chunk, at the beginning of each file
#define PRIMARY       0x4D4D

//>------ Main Chunks
#define OBJECTINFO    0x3D3D                // This gives the version of the mesh and is found right before the material and object information
#define VERSION       0x0002                // This gives the version of the .3ds file
#define EDITKEYFRAME  0xB000                // This is the header for all of the key frame info

//>------ sub defines of OBJECTINFO
#define MATERIAL      0xAFFF                // This stored the texture info
#define OBJECT        0x4000                // This stores the faces, vertices, etc...

//>------ sub defines of MATERIAL
#define MATNAME       0xA000                // This holds the material name
#define MATDIFFUSE    0xA020                // This holds the color of the object/material
#define MATMAP        0xA200                // This is a header for a new material
#define MATMAPFILE    0xA300                // This holds the file name of the texture

#define OBJECT_MESH   0x4100                // This lets us know that we are reading a new object

//>------ sub defines of OBJECT_MESH
#define OBJECT_VERTICES     0x4110          // The objects vertices
#define OBJECT_FACES        0x4120          // The objects faces
#define OBJECT_MATERIAL     0x4130          // This is found if the object has a material, either texture map or color
#define OBJECT_UV           0x4140          // The UV texture coordinates


// Here is our structure for our 3DS indicies (since .3DS stores 4 unsigned shorts)
struct tIndices {                           
  unsigned short a, b, c, bVisible;       
  // This will hold point1, 2, and 3 index's into the vertex array plus a visible flag
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(tIndices);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(tIndices);

// This holds the chunk info
struct tChunk {
  unsigned short int ID;                  // The chunk's ID       
  unsigned int length;                    // The length of the chunk
  unsigned int bytesRead;                 // The amount of bytes read within that chunk
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(tChunk);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(tChunk);

// This struct handles all of the loading code
struct CLoad3DS {
//public:
  struct CLoad3DS * (*CLoad3DS)(void);                             // This inits the data members

//private:
  // The file pointer
  FILE * m_FilePointer;
  
  // These are used through the loading process to hold the chunk information
  tChunk * m_CurrentChunk;
  tChunk * m_TempChunk;


//public:
  // This is the function that you call to load the 3DS
  bool (* Import3DS)(struct CLoad3DS * this, t3DModel * pModel, const char * strFileName);

//private:
  // This reads in a string and saves it in the char array passed in
  int (* GetString)(struct CLoad3DS * this, char *);

  // This reads the next chunk
  void (* ReadChunk)(struct CLoad3DS * this, tChunk *);

  // This reads the next large chunk
  void (* ProcessNextChunk)(struct CLoad3DS * this, t3DModel *pModel, tChunk *);

  // This reads the object chunks
  void (* ProcessNextObjectChunk)(struct CLoad3DS * this, t3DModel *pModel, t3DObject *pObject, tChunk *);

  // This reads the material chunks
  void (* ProcessNextMaterialChunk)(struct CLoad3DS * this, t3DModel *pModel, tChunk *);

  // This reads the RGB value for the object's color
  void (* ReadColorChunk)(struct CLoad3DS * this, tMaterialInfo *pMaterial, tChunk *pChunk);

  // This reads the objects vertices
  void (* ReadVertices)(struct CLoad3DS * this, t3DObject *pObject, tChunk *);

  // This reads the objects face information
  void (* ReadVertexIndices)(struct CLoad3DS * this, t3DObject *pObject, tChunk *);

  // This reads the texture coodinates of the object
  void (* ReadUVCoordinates)(struct CLoad3DS * this, t3DObject *pObject, tChunk *);

  // This reads in the material name assigned to the object and sets the materialID
  void (* ReadObjectMaterial)(struct CLoad3DS * this, t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk);
    
  // This computes the vertex normals for the object (used for lighting)
  void (* ComputeNormals)(struct CLoad3DS * this, t3DModel *pModel);

  // This frees memory and closes the file
  void (* CleanUp)(struct CLoad3DS * this);
};

extern struct CLoad3DS * CLoad3DS(void);

//DEFINE_NEW_OPERATOR_FOR_STRUCT(CLoad3DS);
static struct CLoad3DS * new_CLoad3DS(void) {
  return CLoad3DS();
}


  




/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
// 
// This file is created in the hopes that you can just plug it into your code
// easily.  You will probably want to query more chunks though for animation, etc..
//
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//



#endif /* _3DS_H */

