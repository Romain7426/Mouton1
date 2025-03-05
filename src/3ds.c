
//***********************************************************************//
//                                                                       //
//      - "Talk to me like I'm a 3 year old!" Programming Lessons -      //
//                                                                       //
//      $Author:        DigiBen     digiben@gametutorials.com            //
//      $Program:       3DS Loader                                       //
//      $Description:   Demonstrates how to load a .3ds file format      //
//      $Date:          10/6/01                                          //
//                                                                       //
//***********************************************************************//

#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "3ds.h"

#define DEBUG_3DS_USING_PRINTF 0

#define DEBUG_TRACE 0

#define debug_printf(...) 
#ifdef DEBUG_3DS_USING_PRINTF 
#if (DEBUG_3DS_USING_PRINTF != 0) 
#undef debug_printf 
//#define debug_printf printf
#define debug_printf(...) fprintf(stderr,__VA_ARGS__)
#endif 
#endif 


//struct CLoad3DS * new_CLoad3DS(void);
static bool Import3DS(struct CLoad3DS * this, t3DModel * pModel, const char * strFileName);
static int  GetString(struct CLoad3DS * this, char *, int16_t);
static void ReadChunk_header(struct CLoad3DS * this, tChunk *);
static void ProcessNextChunk(struct CLoad3DS * this, t3DModel *pModel, tChunk *);
static void ProcessNextObjectChunk(struct CLoad3DS * this, t3DModel *pModel, t3DObject *pObject, tChunk *);
static void ProcessNextMaterialChunk(struct CLoad3DS * this, t3DModel *pModel, tChunk *);
static void ReadColorChunk(struct CLoad3DS * this, tMaterialInfo *pMaterial, tChunk *pChunk);
static void ReadVertices(struct CLoad3DS * this, t3DObject *pObject, tChunk *);
static void ReadVertexIndices(struct CLoad3DS * this, t3DObject *pObject, tChunk *);
static void ReadUVCoordinates(struct CLoad3DS * this, t3DObject *pObject, tChunk *);
static void ReadObjectMaterial(struct CLoad3DS * this, t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk);
static void ComputeNormals(struct CLoad3DS * this, t3DModel *pModel);
static void CleanUp(struct CLoad3DS * this);




static size_t fread_big_endian(void * ptr, size_t size, size_t nmemb, FILE * stream);

size_t fread_big_endian(void * ptr, size_t size, size_t nmemb, FILE * stream) {
  size_t i, j, nblus, nblustemp;
  char *temp;
  
  temp = (char *) ptr;
  nblus = 0;
  temp--; // decremente à cause la forme de la boucle.

  //printf("size = %u, nmemb = %u \n", (unsigned) size, (unsigned) nmemb);

  if (size == 0 || nmemb == 0) {
    return 0;
  }
  for (i = 0; i < nmemb; i++) {
    for (j = size; j > 0; j--) {
      nblustemp = fread(temp + j, 1, 1, stream);
      if (nblustemp == 0) {
	return nblus;
      }
      nblus += nblustemp;
    }
    temp += size;
    //printf("fread_  ptr * = %p \n", temp);
  }
  return nmemb;
}

#if 1 
// RL: For some unknown reasons, the 'BIG_ENDIAN' is defined while my current computer is little-endian. 
//     So I disable that for the moment. 
#define fread_ fread  
#else 
#ifdef BIG_ENDIAN 
#error BIG_ENDIAN 
#define fread_ fread_big_endian
#else
#define fread_ fread
#endif 
#endif 









// This file handles all of the code needed to load a .3DS file.
// Basically, how it works is, you load a chunk, then you check
// the chunk ID.  Depending on the chunk ID, you load the information
// that is stored in that chunk.  If you do not want to read that information,
// you read past it.  You know how many bytes to read past the chunk because
// every chunk stores the length in bytes of that chunk.

///////////////////////////////// CLOAD3DS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This constructor initializes the tChunk data
/////
///////////////////////////////// CLOAD3DS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CLoad3DS * CLoad3DS_make_aux(CLoad3DS * this) {
  bzero(this, sizeof(*this)); 
  
  this -> Import3DS = Import3DS;
  this -> GetString = GetString;
  this -> ReadChunk_header = ReadChunk_header;
  this -> ProcessNextChunk = ProcessNextChunk;
  this -> ProcessNextObjectChunk = ProcessNextObjectChunk;
  this -> ProcessNextMaterialChunk = ProcessNextMaterialChunk;
  this -> ReadColorChunk = ReadColorChunk;
  this -> ReadVertices = ReadVertices;
  this -> ReadVertexIndices = ReadVertexIndices;
  this -> ReadUVCoordinates = ReadUVCoordinates;
  this -> ReadObjectMaterial = ReadObjectMaterial;
  this -> ComputeNormals = ComputeNormals;
  this -> CleanUp = CleanUp;
  
  this -> m_CurrentChunk = new_tChunk();                // Initialize and allocate our current chunk
  this -> m_TempChunk = new_tChunk();                   // Initialize and allocate a temporary chunk

  return this;
}; 

CLoad3DS * CLoad3DS_make(void) {
  struct CLoad3DS * this = NULL;
  this = (struct CLoad3DS *) malloc(sizeof(struct CLoad3DS));
  bzero(this, sizeof(struct CLoad3DS));

  return CLoad3DS_make_aux(this);
}; 

struct CLoad3DS * new_CLoad3DS(void) {
  return CLoad3DS_make();
}; 


///////////////////////////////// IMPORT 3DS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This is called by the client to open the .3ds file, read it, then clean up
/////
///////////////////////////////// IMPORT 3DS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

//bool CLoad3DS::Import3DS(t3DModel *pModel, const char * strFileName)
bool Import3DS(CLoad3DS * this, t3DModel *pModel, const char * strFileName) {
  char strMessage[255] = {0}; 
  
  // RL: Quel est la structure d'un fichier 3DS?
  //     Un fichier 3DS est un arbre de "chunks".
  //     Un chunk est un bloc de données. Un chunk contient un en-tête de six octets puis ses données.
  //     L'en-tête d'un chunk contient le type du chunk (deux octets) puis la taille du chunk (quatre octets). 
  // 
  //     Le chunk racine est au début du fichier. Son type est nécessairement "primaire". 
  //     Quant à sa taille, celle-ci est l'intégralité des données; id est, quand on a fini de lire le chunk primaire, 
  //     alors on a lues toutes les données.
  
  //printf("appel à Import3DS : pModel->numOfObjects = %i\n", pModel->numOfObjects);
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    
  pModel -> numOfMaterials = 0;
  pModel -> numOfObjects = 0;
    
  //printf("appel à Import3DS : pModel->numOfObjects = %i\n", pModel->numOfObjects);
    
  // Open the 3DS file
  this -> m_FilePointer = fopen(strFileName, "rb");

  // Make sure we have a valid file pointer (we found the file)
  if (NULL == this -> m_FilePointer) {
    printf("Unable to find the file: %s - errno = %d" "\n", strFileName, errno); 
    CleanUp(this);
    return false; 
  }; 

#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 

    // RL: Maintenant que le fichier est ouvert, nous lisons les premiers octets
    //     et nous vérifions que son type est "primaire".
    
    // Once we have the file open, we need to read the very first data chunk
    // to see if it's a 3DS file.  That way we don't read an invalid file.
    // If it is a 3DS file, then the first chunk ID will be equal to PRIMARY (some hex num)
  
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
    // Read the first chuck of the file to see if it's a 3DS file
    ReadChunk_header(this, this -> m_CurrentChunk);
    
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
    // Make sure this is a 3DS file
    if (PRIMARY != this -> m_CurrentChunk -> ID) { 
      snprintf(strMessage, sizeof(strMessage), "Unable to load PRIMARY chuck from file: %s!", strFileName); 
      printf("%s\n", strMessage); 
      CleanUp(this); 
      return false; 
    }; 
  
#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
    //debug_printf("Le primary chunk a été loadé ; ID = %X ; PRIMARY = %X ; pointeur vers le fichier : %p\n", this -> m_CurrentChunk->ID, PRIMARY, this -> m_FilePointer);
    debug_printf("Le primary chunk a été loadé ; ID = %X [ PRIMARY = %X ] ; taille des données 3DS: %u""\n", this -> m_CurrentChunk->ID, PRIMARY, this -> m_CurrentChunk->ID);
    //fprintf(stderr,"Le primary chunk a été loadé ; ID = %X [ PRIMARY = %X ] ; taille des données 3DS: %u""\n", this -> m_CurrentChunk->ID, PRIMARY, this -> m_CurrentChunk->ID);
  
  // RL: Maintenant que nous avons reconnu le chunk primaire, on itère.
  //     Les données du chunk primaire sont une suite de chunks.
  //     On va donc parcourir la liste de ces chunks fils. 
  
  // Now we actually start reading in the data.  ProcessNextChunk() is recursive
  
  // Begin loading objects, by calling this recursive function
  //debug_printf("   ProcessNextChunk...\n");
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  ProcessNextChunk(this, pModel, this -> m_CurrentChunk);

#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 

#if 1
    {
      fprintf(stderr, "pModel -> numOfObjects = %d" "\n", pModel -> numOfObjects); 
      
      t3DObject * pObject = &(pModel->pObject[0]);
      CVector3 vPoly[3];
      CVector3 vVert;

      fprintf(stderr, "pObject -> numOfVerts = %d" "\n", pObject -> numOfVerts); 
#if 0
      for (int vert_i = 0; vert_i < pObject -> numOfVerts; vert_i++) {                                               
	vVert = pObject -> pVerts[vert_i];
	fprintf(stderr, "vert_i = %3d : ", vert_i); 
	fprintf(stderr, "vVert = { %f ; %f ; %f }" " - ", vVert.x, vVert.y, vVert.z); 
	fprintf(stderr, "\n"); 
      };
#endif 

      
      fprintf(stderr, "pObject -> numOfFaces = %d" "\n", pObject -> numOfFaces); 
#if 0
      for (int face_i = 0; face_i < pObject -> numOfFaces; face_i++) { 
	const uint16_t vert0 = pObject->pFaces[face_i].vertIndex[0];
	const uint16_t vert1 = pObject->pFaces[face_i].vertIndex[1];
	const uint16_t vert2 = pObject->pFaces[face_i].vertIndex[2];
	fprintf(stderr, "face_i = %3d : ", face_i); 
	fprintf(stderr, "vVert = { %3d ; %3d ; %3d }" " - ", vert0, vert1, vert2); 
	fprintf(stderr, "\n"); 
      };
#endif


      fprintf(stderr, "pObject -> numTexVertex = %d" "\n", pObject -> numTexVertex); 
#if 0
    {
      CVector2 vVert;
      fprintf(stderr, "pObject -> numTexVertex = %d" "\n", pObject -> numTexVertex); 
      for (int vert_i = 0; vert_i < pObject -> numTexVertex; vert_i++) {                                               
	vVert = pObject -> pTexVerts[vert_i];

	fprintf(stderr, "vert_i = %3d : ", vert_i); 
	fprintf(stderr, "vVert = { %f ; %f  }" " - ", vVert.x, vVert.y); 
	fprintf(stderr, "\n"); 
      };
    };
#endif 

      fflush(NULL); 
      //assert(false);
    };
#endif 


    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  // After we have read the whole 3DS file, we want to calculate our own vertex normals.
  debug_printf("   ComputeNormals...\n");
  for (int object_i = 0; object_i < pModel->numOfObjects; object_i++) {
    t3DObject * pObject = &(pModel->pObject[object_i]);
    pObject -> pNormals = NULL;
  };
  ComputeNormals(this, pModel);

  return true;



#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  // Clean up after everything
  CleanUp(this);
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 

#if DEBUG_TRACE != 0 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  return true;
}

///////////////////////////////// CLEAN UP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function cleans up our allocated memory and closes the file
/////
///////////////////////////////// CLEAN UP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CleanUp(struct CLoad3DS * this) { 
  fflush(NULL); 
  fclose(this -> m_FilePointer); 
  this -> m_FilePointer = NULL;
  free(this -> m_CurrentChunk);                      // Free the current chunk
  this -> m_CurrentChunk = NULL; 
  free(this -> m_TempChunk);                         // Free our temporary chunk
  this -> m_TempChunk = NULL; 
  fflush(NULL); 
}; 


///////////////////////////////// PROCESS NEXT CHUNK\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads the main sections of the .3DS file, then dives deeper with recursion
/////
///////////////////////////////// PROCESS NEXT CHUNK\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ProcessNextChunk(CLoad3DS * this, t3DModel *pModel, tChunk *pParentChunk) { 
  static int prof = 0; prof++; 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " ">>> prof = %d" "\n", __func__, prof); 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(t3DObject) = %lu" "\n", __func__, (unsigned long) sizeof(t3DObject)); // 304 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(tMaterialInfo) = %lu" "\n", __func__, (unsigned long) sizeof(tMaterialInfo)); // 536 

  // RL: Cette procédure parcourt la liste des chunks fils du chunk parent. 

#if 0 
  t3DObject newObject;// = {0};
#if 1 
  bzero(&newObject, sizeof(newObject)); 
#else 
  //3DObject newObject; // = {0, 0, 0, 0, 0, 0};                  // This is used to add to our object list
  newObject.numOfVerts = 0;
  newObject.numOfFaces = 0;
  newObject.numTexVertex = 0;
  newObject.materialID = 0;
  newObject.bHasTexture = 0;
  newObject.strName[0] = 0;
  newObject.pVerts = NULL;
  newObject.pNormals = NULL;
  newObject.pTexVerts = NULL;
  newObject.pFaces = NULL; 
#endif
#endif  
#if 0 
  tMaterialInfo newTexture;// = {0};  
#if 1 
  bzero(&newTexture, sizeof(newTexture)); 
#else 
  // tMaterialInfo newTexture; // = {0, 0, 0, 0, 0, 0, 0, 0};             // This is used to add to our material list
  newTexture.strName[0] = 0;
  newTexture.strFile[0] = 0;
  //newTexture.color[3] = 0;
  newTexture.color[0] = 0; 
  newTexture.color[1] = 0; 
  newTexture.color[2] = 0; 
  newTexture.texureId = 0;
  newTexture.uTile = 0;
  newTexture.vTile = 0;
  newTexture.uOffset = 0;
  newTexture.vOffset = 0;
#endif 
#endif 
    
  /*INITIALISATION MANQUANTE QUI MAINTENANT NE MANQUE PLUS*/
  /* pModel->numOfMaterials = 0;
     pModel->numOfObjects = 0;*/
  
  //debug_printf("appel à processchunk : pModel->numOfObjects = %i\n", pModel->numOfObjects);

    
  uint32_t version_3ds = 0;                   // This will hold the file version
  uint32_t version_mesh = 0; 
  //int buffer[5000] = {0};                    // This is used to read past unwanted data
  
  // RL: Allocation du chunk qui contiendra le chunk fils courant. 
  this -> m_CurrentChunk = new_tChunk(); { 
  
    // Below we check our chunk ID each time we read a new chunk.  Then, if
    // we want to extract the information from that chunk, we do so.
    // If we don't want a chunk, we just read past it.  
    
    // Continue to read the sub chunks until we have reached the length.
    // After we read ANYTHING we add the bytes read to the chunk and then check
    // check against the length.
    //debug_printf("boucle du chunk...\n");
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d" "\n", __func__, prof); 
    while (pParentChunk->bytesRead < pParentChunk->length) {
      // Read next Chunk
      //debug_printf("   on lit un chunk...\n"); 
      ReadChunk_header(this, this -> m_CurrentChunk); 
      //debug_printf("    chunk lu avec succès...\n"); 
      
      // Check the chunk ID
      switch (this -> m_CurrentChunk->ID) { 
      case VERSION: {                          // This holds the version of the file
	//debug_printf("    chunk VERSION... %X\n", VERSION);
	//printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d - CHUNK_ID = VERSION" "\n", __func__, prof); 
	// This chunk has an unsigned short that holds the file version.
	// Since there might be new additions to the 3DS file format in 4.0,
	// we give a warning to that problem.
	
	// Read the file version and add the bytes read to our bytesRead variable
	//m_CurrentChunk->bytesRead += fread(&version, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
	this -> m_CurrentChunk->bytesRead += 4 * fread_(&version_3ds, 4, 1, this -> m_FilePointer);
	// On skippe s'il en reste.
	const int skip_len = this -> m_CurrentChunk->length - this -> m_CurrentChunk->bytesRead;
	if (0 != fseek(this -> m_FilePointer, skip_len, SEEK_CUR)) { printf("Erreur de positionnement."); } 
	this -> m_CurrentChunk->bytesRead = this -> m_CurrentChunk->length;
	debug_printf("    chunk VERSION [%X] - version = %u" "\n", VERSION, version_3ds);

	// If the file version is over 3, give a warning that there could be a problem
	if (version_3ds > 0x03) printf("This 3DS file is over version 3 so it may load incorrectly\n");
      }; break; 

      case OBJECTINFO: {                       // This holds the version of the mesh
	debug_printf("    chunk OBJECTINFO... %X\n", OBJECTINFO);
	//printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d - CHUNK_ID = OBJECTINFO" "\n", __func__, prof); 
	// This chunk holds the version of the mesh.  It is also the head of the MATERIAL
	// and OBJECT chunks.  From here on we start reading in the material and object info.

	// Read the next chunk
	ReadChunk_header(this, this -> m_TempChunk);
	
	// Get the version of the mesh
	//m_TempChunk->bytesRead += fread(&version, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);
	this -> m_TempChunk->bytesRead += 4 * fread_(&version_mesh, 4, 1, this -> m_FilePointer);
	// On skippe s'il en reste.
	if (fseek(this -> m_FilePointer, this -> m_TempChunk->length - this -> m_TempChunk->bytesRead, SEEK_CUR) != 0) { printf("Erreur de positionnement Mesh."); }
	debug_printf("Version Mesh: %X\n", version_mesh);
	//printf("m_TempChunk->length = %u\n", m_TempChunk->length); fflush(NULL);

	// Increase the bytesRead by the bytes read from the last chunk
	this -> m_CurrentChunk->bytesRead += this -> m_TempChunk->length; 

	// Go to the next chunk, which is the object has a texture, it should be MATERIAL, then OBJECT.
	ProcessNextChunk(this, pModel, this -> m_CurrentChunk);
	}; break;

      case MATERIAL: {                          // This holds the material information
	debug_printf("    chunk MATERIAL... %X\n", MATERIAL);
	//printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d - CHUNK_ID = MATERIAL" "\n", __func__, prof); 
	// This chunk is the header for the material info chunks

	if (pModel->numOfMaterials < MATERIALS_MAX) { 
	  // Add a empty texture structure to our texture list.
	  // If you are unfamiliar with STL's "vector" class, all push_back()
	  // does is add a new node onto the list.  I used the vector class
	  // so I didn't need to write my own link list functions.  
	  //pModel->pMaterials.push_back(newTexture);
	  //pModel->pMaterials[pModel->pMaterials_nb++] = (newTexture);
	  //pModel->pMaterials[pModel->numOfMaterials] = (newTexture);
	  
	  // Increase the number of materials
	  pModel->numOfMaterials++;
	  
	  // Proceed to the material loading function
	  ProcessNextMaterialChunk(this, pModel, this -> m_CurrentChunk); 
	}; 
      }; break;

      case OBJECT: {                           // This holds the name of the object being read
	debug_printf("    chunk OBJECT...\n"); 
	//printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d - CHUNK_ID = [%d]OBJECT" "\n", __func__, prof, (int) OBJECT); 
	// This chunk is the header for the object info chunks.  It also
	// holds the name of the object.

	// Add a new tObject node to our list of objects (like a link list)
	//pModel->pObject.push_back(newObject);
	//pModel->pObject[pModel->pObject_nb++] = (newObject);
	if (pModel->numOfObjects < OBJECTS_MAX) { 
	  //pModel->pObject[pModel->numOfObjects] = (newObject);
	  
	  // Increase the object count
	  pModel -> numOfObjects++;
	  
	  // Initialize the object and all it's data members
	  //debug_printf("    on initialise à 0 le pObject[%i]...\n",  pModel->numOfObjects - 1); 
	  //memset(&(pModel->pObject[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));
	  //debug_printf("    initialisation à 0 du pObject[%i] réussi...\n", pModel->numOfObjects - 1);  
	  
	  // Get the name of the object and store it, then add the read bytes to our byte counter.
	  this -> m_CurrentChunk->bytesRead += GetString(this, pModel->pObject[pModel->numOfObjects - 1].strName, 255);
	  
	  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d - OBJECT NAME = '%s'" "\n", __func__, prof, pModel->pObject[pModel->numOfObjects - 1].strName); 

	  // Now proceed to read in the rest of the object information
	  ProcessNextObjectChunk(this, pModel, &(pModel->pObject[pModel->numOfObjects - 1]), this -> m_CurrentChunk);
	}; 
	}; break;

      case EDITKEYFRAME: { 
	debug_printf("    chunk EDITKEYFRAME... %X\n", EDITKEYFRAME);   
	//printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d - CHUNK_ID = EDITKEYFRAME" "\n", __func__, prof); 
	// Because I wanted to make this a SIMPLE tutorial as possible, I did not include
	// the key frame information.  This chunk is the header for all the animation info.
	// In a later tutorial this will be the subject and explained thoroughly.

	//ProcessNextKeyFrameChunk(pModel, m_CurrentChunk);

	// Read past this chunk and add the bytes read to the byte counter
	//m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
    
	if (fseek(this -> m_FilePointer, this -> m_CurrentChunk->length - this -> m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
	  { printf("Erreur de positionnement."); }
    
	this -> m_CurrentChunk->bytesRead = this -> m_CurrentChunk->length;
      }; break;

      default: 
	debug_printf("    chunk non identifié, tant pis on passe au suivant... %X\n", this -> m_CurrentChunk->ID);    
	printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- prof = %d - CHUNK_ID = UNKNOWN" "\n", __func__, prof); 
	// If we didn't care about a chunk, then we get here.  We still need
	// to read past the unknown or ignored chunk and add the bytes read to the byte counter.
	//m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
    
	if (fseek(this -> m_FilePointer, this -> m_CurrentChunk->length - this -> m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
	  { debug_printf("Erreur de positionnement."); }
	this -> m_CurrentChunk->bytesRead = this -> m_CurrentChunk->length;
	break;
      }; // END OF SWITCH 

      // Add the bytes read from the last chunk to the previous chunk passed in.
      pParentChunk->bytesRead += this -> m_CurrentChunk->bytesRead;
    }; // END OF WHILE 

  
  }; free(this -> m_CurrentChunk); 
  // Free the current chunk and set it back to the previous chunk (since it started that way) 
  this -> m_CurrentChunk = pParentChunk;
  //debug_printf("fin chunk...\n");
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "<<< prof = %d" "\n", __func__, prof); 
  prof--; 
}; 


///////////////////////////////// PROCESS NEXT OBJECT CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function handles all the information about the objects in the file
/////
///////////////////////////////// PROCESS NEXT OBJECT CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ProcessNextObjectChunk(CLoad3DS * this, t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk) {
  //int buffer[50000] = {0};                    // This is used to read past unwanted data
 
  // Allocate a new chunk to work with
  debug_printf("    Appel ProcessNextObjectChunk...\n");   
  this->m_CurrentChunk = new_tChunk(); { 

    // Continue to read these chunks until we read the end of this sub chunk
    while (pPreviousChunk->bytesRead < pPreviousChunk->length) {
      // Read the next chunk
      debug_printf("      on lit chunk (object chunk)...\n");  
      ReadChunk_header(this, this->m_CurrentChunk);
      debug_printf("      chunk lu (object chunk) avec succès...\n");  
      // Check which chunk we just read
      switch (this->m_CurrentChunk->ID) 
	{
	case OBJECT_MESH:                   // This lets us know that we are reading a new object
	  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---  CHUNK_ID = [%d]OBJECT_MESH " "\n", __func__, (int) OBJECT_MESH); 
	  debug_printf("      object-chunk OBJECT_MESH... %X\n", OBJECT_MESH);  
	  // We found a new object, so let's read in it's info using recursion
	  ProcessNextObjectChunk(this, pModel, pObject, this->m_CurrentChunk);
	  break;

	case OBJECT_VERTICES:               // This is the objects vertices
	  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---  CHUNK_ID = [%d]OBJECT_VERTICES " "\n", __func__, (int) OBJECT_VERTICES); 
	  debug_printf("      object-chunk OBJECT_VERTICES... %X\n", OBJECT_VERTICES);  
	  ReadVertices(this, pObject, this->m_CurrentChunk);
	  break;

	case OBJECT_FACES:                  // This is the objects face information
	  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---  CHUNK_ID = [%d]OBJECT_FACES " "\n", __func__, (int) OBJECT_FACES); 
	  debug_printf("      object-chunk OBJECT_FACES... %X\n", OBJECT_FACES);  
	  ReadVertexIndices(this, pObject, this->m_CurrentChunk);
	  debug_printf("OBJECT_FACES: Read = %u ; Length = %u\n", this->m_CurrentChunk->bytesRead, this->m_CurrentChunk->length);
	  break;

	case OBJECT_MATERIAL:               // This holds the material name that the object has
	  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---  CHUNK_ID = [%d]OBJECT_MATERIAL " "\n", __func__, (int) OBJECT_MATERIAL); 
	  debug_printf("      object-chunk OBJECT_MATERIAL... %X\n", OBJECT_MATERIAL);  
	  // This chunk holds the name of the material that the object has assigned to it.
	  // This could either be just a color or a texture map.  This chunk also holds
	  // the faces that the texture is assigned to (In the case that there is multiple
	  // textures assigned to one object, or it just has a texture on a part of the object.
	  // Since most of my game objects just have the texture around the whole object, and 
	  // they aren't multitextured, I just want the material name.

	  // We now will read the name of the material assigned to this object
	  ReadObjectMaterial(this, pModel, pObject, this->m_CurrentChunk);            
	  break;

	case OBJECT_UV:                     // This holds the UV texture coordinates for the object
	  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---  CHUNK_ID = [%d]OBJECT_UV " "\n", __func__, (int) OBJECT_UV); 
	  debug_printf("      object-chunk OBJECT_UV... %X\n", OBJECT_UV);  
	  // This chunk holds all of the UV coordinates for our object.  Let's read them in.
	  ReadUVCoordinates(this, pObject, this->m_CurrentChunk);
	  break;

	default:  
	  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---  CHUNK_ID = [%d]OBJECT_UNKNOWN " "\n", __func__, (int) this->m_CurrentChunk->ID); 
	  debug_printf("      object-chunk non reconnu : on l'ignore... %X\n", this->m_CurrentChunk->ID);   
	  // Read past the ignored or unknown chunks
	  //this->m_CurrentChunk->bytesRead += fread(buffer, 1, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, m_FilePointer);
	  // On skippe s'il en reste.
	  if (fseek(this->m_FilePointer, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, SEEK_CUR) != 0) { printf("Erreur de positionnement OBJECT.");}
	  this->m_CurrentChunk->bytesRead = this->m_CurrentChunk->length;
    
	  break;
	}; // END OF SWITCH 

      // Add the bytes read from the last chunk to the previous chunk passed in.
      pPreviousChunk->bytesRead += this->m_CurrentChunk->bytesRead;
    }; // END OF WHILE 

    // Free the current chunk and set it back to the previous chunk (since it started that way)
  }; free(this->m_CurrentChunk);
  this->m_CurrentChunk = pPreviousChunk;
}; 


///////////////////////////////// PROCESS NEXT MATERIAL CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function handles all the information about the material (Texture)
/////
///////////////////////////////// PROCESS NEXT MATERIAL CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ProcessNextMaterialChunk(CLoad3DS * this, t3DModel *pModel, tChunk *pPreviousChunk) {
  //int buffer[50000] = {0};                    // This is used to read past unwanted data

  // Allocate a new chunk to work with
  this->m_CurrentChunk = new_tChunk(); { 

  // Continue to read these chunks until we read the end of this sub chunk
  while (pPreviousChunk->bytesRead < pPreviousChunk->length) {
      // Read the next chunk
      ReadChunk_header(this, this->m_CurrentChunk);

      // Check which chunk we just read in
      switch (this->m_CurrentChunk->ID) {
        case MATNAME:                           // This chunk holds the name of the material
          debug_printf("  Chunk Material Name %X\n", MATNAME);
          // Here we read in the material name
          //this->m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strName, 1, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, this->m_FilePointer);
          this->m_CurrentChunk->bytesRead += GetString(this, pModel->pMaterials[pModel->numOfMaterials - 1].strName, 255);
          if (fseek(this->m_FilePointer, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
            { printf("Erreur de positionnement."); }
          this->m_CurrentChunk->bytesRead = this->m_CurrentChunk->length;
          debug_printf("  Chunk Material Name: %s\n", pModel->pMaterials[pModel->numOfMaterials - 1].strName);
          break;

        case MATDIFFUSE:                        // This holds the R G B color of our object
          debug_printf("   Chunk Material Diffuse %X\n", MATDIFFUSE);
          ReadColorChunk(this, &(pModel->pMaterials[pModel->numOfMaterials - 1]), this->m_CurrentChunk);
          break;
        
        case MATMAP:                            // This is the header for the texture info
          debug_printf("   Chunk Material Map %X\n", MATMAP);
          // Proceed to read in the material information
          ProcessNextMaterialChunk(this, pModel, this->m_CurrentChunk);
          break;

        case MATMAPFILE:                        // This stores the file name of the material
          debug_printf("   Chunk Material Map File %X\n", MATMAPFILE);
          // Here we read in the material's file name
          //this->m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strFile, 1, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, this->m_FilePointer);
          this->m_CurrentChunk->bytesRead += GetString(this, pModel->pMaterials[pModel->numOfMaterials - 1].strFile, 255);
          if (fseek(this->m_FilePointer, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
            { printf("Erreur de positionnement."); }
          this->m_CurrentChunk->bytesRead = this->m_CurrentChunk->length;
          debug_printf("Nom du File Materials: %s", (pModel->pMaterials[pModel->numOfMaterials - 1].strFile));
          break;
        
        default:  
          debug_printf("    Chunk Material Unknown %X\n", this->m_CurrentChunk->ID);
          // Read past the ignored or unknown chunks
          //this->m_CurrentChunk->bytesRead += fread(buffer, 1, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, this->m_FilePointer);
          if (fseek(this->m_FilePointer, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
            { debug_printf("Erreur de positionnement."); }
          this->m_CurrentChunk->bytesRead = this->m_CurrentChunk->length;
          break;
        }

      // Add the bytes read from the last chunk to the previous chunk passed in.
      pPreviousChunk->bytesRead += this->m_CurrentChunk->bytesRead;
    };

  // Free the current chunk and set it back to the previous chunk (since it started that way)
  }; free(this->m_CurrentChunk);
  this->m_CurrentChunk = pPreviousChunk;
}

///////////////////////////////// READ CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in a chunk ID and it's length in bytes
/////
///////////////////////////////// READ CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ReadChunk_header(CLoad3DS * this, tChunk *pChunk) { 
  this -> m_CurrentChunk -> ID = 0;

  // This reads the chunk ID which is 2 bytes.
  // The chunk ID is like OBJECT or MATERIAL.  It tells what data is 
  // able to be read in within the chunks section.  
  //pChunk->bytesRead = fread(&pChunk->ID, 1, 2, this->m_FilePointer); 
  //pChunk -> bytesRead = 2 * fread_(&pChunk -> ID, /*object size*/2, /*number of objects to be read*/1, this -> m_FilePointer); 
  pChunk -> bytesRead = fread_(&pChunk -> ID, /*object size*/1, /*number of objects to be read*/2, this -> m_FilePointer); 
  //debug_printf("ChunkID: %4X\n", (unsigned int) pChunk -> ID); 

  // Then, we read the length of the chunk which is 4 bytes. 
  // This is how we know how much to read in, or read past. 
  //pChunk->bytesRead += fread(&pChunk->length, 1, 4, this->m_FilePointer);
  //pChunk->bytesRead += 4 * fread_(&pChunk->length, /*object size*/4, /*number of objects to be read*/1, this->m_FilePointer); 
  pChunk -> bytesRead += fread_(&pChunk -> length, /*object size*/1, /*number of objects to be read*/4, this->m_FilePointer); 
  //messerr("ChunkLength: %u\n", pChunk -> length); 
  //debug_printf("ChunkLength: %u\n", pChunk -> length); 

  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- ChunkID: %4X - ChunkLength: %u " "\n", __func__, (unsigned int) pChunk -> ID, (int) pChunk -> length); 
  debug_printf("%s(): ChunkID: %4u - ChunkLength: %u " "\n", __func__, (unsigned int) pChunk -> ID, (int) pChunk -> length); 

  //debug_printf("Lecture En-Tete Chunk oki.\n"); 
}; 

///////////////////////////////// GET STRING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in a string of characters
/////
///////////////////////////////// GET STRING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int GetString(CLoad3DS * this, char *pBuffer, const int16_t buffer_bytesize) {
  int index = 0;
  int buffer_i = 0; 
  
#if 0
  // Read 1 byte of data which is the first letter of the string
  fread(pBuffer, 1, 1, this->m_FilePointer);
  index++;
  buffer_i++; 
#endif 

  char c; 
  // Loop until we get NULL
  //while (*(pBuffer + index++) != 0) {
  for (;;) { 
    // Read in a character at a time until we hit NULL.
    fread(&c, 1, 1, this->m_FilePointer);
    index++;
    if (buffer_bytesize > buffer_i) {
      pBuffer[buffer_i] = c; 
      buffer_i++;
    };
    if ('\0' == c) break;
  };

  // Return the string length, which is how many bytes we read in (including the NULL)
  //return strlen(pBuffer) + 1;
  return index;
}


///////////////////////////////// READ COLOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in the RGB color data
/////
///////////////////////////////// READ COLOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ReadColorChunk(CLoad3DS * this, tMaterialInfo *pMaterial, tChunk *pChunk) {
  // Read the color chunk info
  ReadChunk_header(this, this->m_TempChunk);

  // Read in the R G B color (3 bytes - 0 through 255)
  //this->m_TempChunk->bytesRead += fread(pMaterial->color, 1, this->m_TempChunk->length - this->m_TempChunk->bytesRead, this->m_FilePointer);
  this->m_TempChunk->bytesRead += 1 * fread(pMaterial->color, 1, 3, this->m_FilePointer);
  // On skippe s'il en reste.
  if (fseek(this->m_FilePointer, this->m_TempChunk->length - this->m_TempChunk->bytesRead, SEEK_CUR) != 0)
    { printf("Erreur de positionnement ReadColorChunk."); }
  this->m_TempChunk->bytesRead = this->m_TempChunk->length;

  // Add the bytes read to our chunk
  pChunk->bytesRead += this->m_TempChunk->bytesRead;
}


///////////////////////////////// READ VERTEX INDECES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in the indices for the vertex array
/////
///////////////////////////////// READ VERTEX INDECES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ReadVertexIndices(CLoad3DS * this, t3DObject * pObject, tChunk * pPreviousChunk) {
  unsigned short index = 0; // This is used to read in the current face index

  // In order to read in the vertex indices for the object, we need to first
  // read in the number of them, then read them in.  Remember,
  // we only want 3 of the 4 values read in for each face.  The fourth is
  // a visibility flag for 3D Studio Max that doesn't mean anything to us.

  // Read in the number of faces that are in this object (int)
  // un unsigned short en realite --- Connard
  //pPreviousChunk->bytesRead += fread(&pObject->numOfFaces, 1, 2, this->m_FilePointer);
  pObject->numOfFaces = 0;
#ifndef LIBPROG_ENDIAN_BIG
  pPreviousChunk->bytesRead += 2 * fread_(&pObject->numOfFaces, 2, 1, this->m_FilePointer);
#else
  pPreviousChunk->bytesRead += 2 * fread_((((unsigned short *)(&((pObject)->numOfFaces))) + 1), 2, 1, this->m_FilePointer);
#endif
  debug_printf("Number of faces: %d\n",  pObject->numOfFaces);
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "--- Number of vertices: %d" "\n", __func__, (int) pObject->numOfFaces); 

  // Alloc enough memory for the faces and initialize the structure
  //pObject->pFaces = new tFace [pObject->numOfFaces];
  const int32_t taille = pObject->numOfFaces * sizeof(tFace);
  pObject->pFaces = malloc(taille); 
  memset(pObject->pFaces, 0, taille); 

  const int32_t still = pPreviousChunk->length - pPreviousChunk->bytesRead; 
  debug_printf("still = %d" "\n", still);
  debug_printf("taille = %d" "\n", taille);
  //assert(still >= taille); 
  //assert(false); 

  for (int i = 0; i < pObject -> numOfFaces; i++) { 
    // Next, we read in the A then B then C index for the face, but ignore the 4th value.
    // The fourth value is a visibility flag for 3D Studio Max, we don't care about this.
    for (int j = 0; j < 4; j++) { 
      // Read the first vertice index for the current face 
      //pPreviousChunk->bytesRead += fread(&index, 1, sizeof(index), this->m_FilePointer);
      pPreviousChunk->bytesRead += 2 * fread_(&index, 2, 1, this->m_FilePointer);
      //debug_printf("ReadVertexIndices: index = %d\n", (int) index);
      if (4 == j) continue;
      pObject->pFaces[i].vertIndex[j] = index;
    }; 
  }; 

#if 0
  { 
    fprintf(stderr, "pObject -> numOfFaces = %d" "\n", pObject -> numOfFaces); 
    for (int face_i = 0; face_i < pObject -> numOfFaces; face_i++) { 
      const uint16_t vert0 = pObject->pFaces[face_i].vertIndex[0];
      const uint16_t vert1 = pObject->pFaces[face_i].vertIndex[1];
      const uint16_t vert2 = pObject->pFaces[face_i].vertIndex[2];
      fprintf(stderr, "face_i = %3d : ", face_i); 
      fprintf(stderr, "vVert = { %3d ; %3d ; %3d }" " - ", vert0, vert1, vert2); 
      fprintf(stderr, "\n"); 
    };
    fflush(NULL); 
    //assert(false);
  };
#endif

}; 


///////////////////////////////// READ UV COORDINATES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in the UV coordinates for the object
/////
///////////////////////////////// READ UV COORDINATES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ReadUVCoordinates(CLoad3DS * this, t3DObject *pObject, tChunk *pPreviousChunk) {
  // In order to read in the UV indices for the object, we need to first
  // read in the amount there are, then read them in.

  // Read in the number of UV coordinates there are (int)
  //pPreviousChunk->bytesRead += fread(&pObject->numTexVertex, 1, 2, this->m_FilePointer);

  pObject->numTexVertex = 0;
#ifndef LIBPROG_ENDIAN_BIG
  pPreviousChunk->bytesRead += 2 * fread_(&pObject->numTexVertex, 2, 1, this->m_FilePointer);
#else
  pPreviousChunk->bytesRead += 2 * fread_(( (unsigned short *) (&(pObject->numTexVertex))) + 1, 2, 1, this->m_FilePointer);
#endif
  debug_printf("  Number of TexVertex: %d --- \n", pObject->numTexVertex); //fflush(NULL);
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---  Number of Vertices = %d " "\n", __func__, (int) pObject->numTexVertex); 
  

  // Allocate memory to hold the UV coordinates

  // Si il y a 0 elt, le new plante sur mac
#if 0 
//#ifdef LIBPROG_SYS_MACOSX
  if (pObject->numTexVertex != 0)
    pObject->pTexVerts = new CVector2 [pObject->numTexVertex];
  else
    pObject->pTexVerts = NULL;
#endif
  const int32_t taille = pObject->numTexVertex * sizeof(CVector2);
  //pObject->pTexVerts = new CVector2 [pObject->numTexVertex];
  pObject -> pTexVerts = malloc(taille);
  memset(pObject->pTexVerts, 0, taille); 

  const int32_t still = pPreviousChunk->length - pPreviousChunk->bytesRead; 
  debug_printf("still = %d" "\n", still);
  debug_printf("taille = %d" "\n", taille);
  //assert(still >= taille); 
  //assert(false); 
  
  const int8_t nb_objects = fread_(pObject->pTexVerts, taille, 1, this->m_FilePointer);
  debug_printf("nb_objects = %d" "\n", nb_objects);
  pPreviousChunk->bytesRead += taille;
  // On skippe s'il en reste.
  if (0 != fseek(this->m_FilePointer, still - taille, SEEK_CUR))
    { printf("Erreur de positionnement ReadVertices."); }
  
  pPreviousChunk->bytesRead = pPreviousChunk->length;

#if 0
    {
      CVector2 vVert;
      fprintf(stderr, "pObject -> numTexVertex = %d" "\n", pObject -> numTexVertex); 
      for (int vert_i = 0; vert_i < pObject -> numTexVertex; vert_i++) {                                               
	vVert = pObject -> pTexVerts[vert_i];

	fprintf(stderr, "vert_i = %3d : ", vert_i); 
	fprintf(stderr, "vVert = { %f ; %f  }" " - ", vVert.x, vVert.y); 
	fprintf(stderr, "\n"); 
      };
      fflush(NULL); 
      assert(false);
    };
#endif 

};


///////////////////////////////// READ VERTICES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in the vertices for the object
/////
///////////////////////////////// READ VERTICES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ReadVertices(CLoad3DS * this, t3DObject *pObject, tChunk *pPreviousChunk) {
  // Like most chunks, before we read in the actual vertices, we need
  // to find out how many there are to read in.  Once we have that number
  // we then fread() them into our vertice array.

  // Read in the number of vertices (int)
  //pPreviousChunk->bytesRead += fread(&(pObject->numOfVerts), 1, 2, this->m_FilePointer);
#ifndef LIBPROG_ENDIAN_BIG
  pPreviousChunk->bytesRead += 2 * fread_(&(pObject->numOfVerts), 2, 1, this->m_FilePointer);
#else
  pPreviousChunk->bytesRead += 2 * fread_(( (unsigned short *) &(pObject->numOfVerts)) + 1, 2, 1, this->m_FilePointer);
#endif

  debug_printf("pObject -> numOfVerts = %d" "\n", pObject -> numOfVerts); 
  //assert(false);

  // Allocate the memory for the verts and initialize the structure
  //pObject->pVerts = new CVector3 [pObject->numOfVerts];
  const int32_t taille = pObject->numOfVerts * sizeof(CVector3);
  pObject->pVerts = malloc(taille);
  memset(pObject->pVerts, 0, taille); 

  // Read in the array of vertices (an array of 3 floats)
  // C'est un tableau !!!!
  // Un float c 4.
  //pPreviousChunk->bytesRead += fread(pObject->pVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, this->m_FilePointer);
  const int32_t still = pPreviousChunk->length - pPreviousChunk->bytesRead; 
  debug_printf("still = %d" "\n", still);
  debug_printf("taille = %d" "\n", taille);
  assert(still >= taille); 

  const int8_t nb_objects = fread_(pObject->pVerts, taille, 1, this->m_FilePointer);
  debug_printf("nb_objects = %d" "\n", nb_objects);
  pPreviousChunk->bytesRead += taille;
  // On skippe s'il en reste.
  if (0 != fseek(this->m_FilePointer, still - taille, SEEK_CUR))
    { printf("Erreur de positionnement ReadVertices."); }
  
  pPreviousChunk->bytesRead = pPreviousChunk->length;

#if 0
    {
      CVector3 vVert;
      fprintf(stderr, "pObject -> numOfVerts = %d" "\n", pObject -> numOfVerts); 
      for (int vert_i = 0; vert_i < pObject -> numOfVerts; vert_i++) {                                               
	vVert = pObject -> pVerts[vert_i];

	fprintf(stderr, "vert_i = %d : ", vert_i); 
	fprintf(stderr, "vVert = { %f ; %f ; %f }" " - ", vVert.x, vVert.y, vVert.z); 
	fprintf(stderr, "\n"); 
      };
      fflush(NULL); 
    };
#endif 


  // Now we should have all of the vertices read in.  Because 3D Studio Max
  // Models with the Z-Axis pointing up (strange and ugly I know!), we need
  // to flip the y values with the z values in our vertices.  That way it
  // will be normal, with Y pointing up.  If you prefer to work with Z pointing
  // up, then just delete this next loop.  Also, because we swap the Y and Z
  // we need to negate the Z to make it come out correctly.

  // Go through all of the vertices that we just read and swap the Y and Z values
  for (int vert_i = 0; vert_i < pObject->numOfVerts; vert_i++) {
    const float fTempY        = pObject->pVerts[vert_i].y;
    pObject->pVerts[vert_i].y = pObject->pVerts[vert_i].z;
    pObject->pVerts[vert_i].z = -fTempY;
  };


#if 0
    {
      CVector3 vVert;
      fprintf(stderr, "pObject -> numOfVerts = %d" "\n", pObject -> numOfVerts); 
      for (int vert_i = 0; vert_i < pObject -> numOfVerts; vert_i++) {                                               
	vVert = pObject -> pVerts[vert_i];

	fprintf(stderr, "vert_i = %d : ", vert_i); 
	fprintf(stderr, "vVert = { %f ; %f ; %f }" " - ", vVert.x, vVert.y, vVert.z); 
	fprintf(stderr, "\n"); 
      };
      fflush(NULL); 
      //assert(false);
    };
#endif 
  
};


///////////////////////////////// READ OBJECT MATERIAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in the material name assigned to the object and sets the materialID
/////
///////////////////////////////// READ OBJECT MATERIAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ReadObjectMaterial(CLoad3DS * this, t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk) {
  char strMaterial[255] = {0};            // This is used to hold the objects material name
  //int buffer[50000] = {0};                // This is used to read past unwanted data

  // *What is a material?*  - A material is either the color or the texture map of the object.
  // It can also hold other information like the brightness, shine, etc... Stuff we don't
  // really care about.  We just want the color, or the texture map file name really.

  // Here we read the material name that is assigned to the current object.
  // strMaterial should now have a string of the material name, like "Material #2" etc..
  pPreviousChunk->bytesRead += GetString(this, strMaterial, 255);

  // Now that we have a material name, we need to go through all of the materials
  // and check the name against each material.  When we find a material in our material
  // list that matches this name we just read in, then we assign the materialID
  // of the object to that material index.  You will notice that we passed in the
  // model to this function.  This is because we need the number of textures.
  // Yes though, we could have just passed in the model and not the object too.

  // Go through all of the textures
  for (int i = 0; i < pModel->numOfMaterials; i++)
    {
      // If the material we just read in matches the current texture name
      if (0 == strcmp(strMaterial, pModel->pMaterials[i].strName))
        {
          // Set the material ID to the current index 'i' and stop checking
          pObject->materialID = i;

          // Now that we found the material, check if it's a texture map.
          // If the strFile has a string length of 1 and over it's a texture
          if (strlen(pModel->pMaterials[i].strFile) > 0) {

            // Set the object's flag to say it has a texture map to bind.
            pObject->bHasTexture = true;
          }   
          break;
        }
      else
        {
          // Set the ID to -1 to show there is no material for this object
          pObject->materialID = -1;
        }
    }

  // Read past the rest of the chunk since we don't care about shared vertices
  // You will notice we subtract the bytes already read in this chunk from the total length.
  //pPreviousChunk->bytesRead += fread(buffer, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, this->m_FilePointer);
  // On skippe s'il en reste.
  if (fseek(this->m_FilePointer, pPreviousChunk->length - pPreviousChunk->bytesRead, SEEK_CUR) != 0)
    { printf("Erreur de positionnement ReadObjectMaterial."); }
  pPreviousChunk->bytesRead = pPreviousChunk->length;

}           

// *Note* 
//
// Below are some math functions for calculating vertex normals.  We want vertex normals
// because it makes the lighting look really smooth and life like.  You probably already
// have these functions in the rest of your engine, so you can delete these and call
// your own.  I wanted to add them so I could show how to calculate vertex normals.

//////////////////////////////  Math Functions  ////////////////////////////////*

// This calculates a vector between 2 points and returns the result
CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2) {
  CVector3 vVector;                           // The variable to hold the resultant vector

  vVector.x = vPoint1.x - vPoint2.x;          // Subtract point1 and point2 x's
  vVector.y = vPoint1.y - vPoint2.y;          // Subtract point1 and point2 y's
  vVector.z = vPoint1.z - vPoint2.z;          // Subtract point1 and point2 z's

  return vVector;                             // Return the resultant vector
}

// This adds 2 vectors together and returns the result
CVector3 AddVector(CVector3 vVector1, CVector3 vVector2) {
  CVector3 vResult;                           // The variable to hold the resultant vector
    
  vResult.x = vVector2.x + vVector1.x;        // Add Vector1 and Vector2 x's
  vResult.y = vVector2.y + vVector1.y;        // Add Vector1 and Vector2 y's
  vResult.z = vVector2.z + vVector1.z;        // Add Vector1 and Vector2 z's

  return vResult;                             // Return the resultant vector
}

// This divides a vector by a single number (scalar) and returns the result
CVector3 DivideVectorByScaler(CVector3 vVector1, float Scaler) {
  CVector3 vResult;                           // The variable to hold the resultant vector
    
  vResult.x = vVector1.x / Scaler;            // Divide Vector1's x value by the scaler
  vResult.y = vVector1.y / Scaler;            // Divide Vector1's y value by the scaler
  vResult.z = vVector1.z / Scaler;            // Divide Vector1's z value by the scaler

  return vResult;                             // Return the resultant vector
}

// This returns the cross product between 2 vectors
CVector3 Cross(CVector3 vVector1, CVector3 vVector2) {
  CVector3 vCross;                                // The vector to hold the cross product
  // Get the X value
  vCross.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
  // Get the Y value
  vCross.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
  // Get the Z value
  vCross.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

  return vCross;                              // Return the cross product
}

// magnitude = sqrt(x^2 + y^2 + z^2)
#define Mag(Normal) (sqrt(Normal.x*Normal.x + Normal.y*Normal.y + Normal.z*Normal.z))

CVector3 Normalize(CVector3 vNormal) {
  const double Magnitude = Mag(vNormal);
  vNormal.x /= (float)Magnitude; 
  vNormal.y /= (float)Magnitude; 
  vNormal.z /= (float)Magnitude; 
  return vNormal; 
};

///////////////////////////////// COMPUTER NORMALS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function computes the normals and vertex normals of the objects
/////
///////////////////////////////// COMPUTER NORMALS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

#undef DEBUG_TRACE
#define DEBUG_TRACE 0
static void ComputeNormals_one_face(CLoad3DS * this, t3DModel *pModel, t3DObject * pObject, tFace *pFace, const uint16_t face_i, CVector3 *pNormals, CVector3 *pTempNormals) {
  CVector3 vVector1, vVector2, vNormal, vPoly[3];
                                               
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
  fprintf(stderr, "face_i = %d / %d" "\n", face_i, pObject -> numOfFaces); 
#endif 

  vPoly[0] = pObject->pVerts[pFace -> vertIndex[0]];
  vPoly[1] = pObject->pVerts[pFace -> vertIndex[1]];
  vPoly[2] = pObject->pVerts[pFace -> vertIndex[2]];

#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
  fprintf(stderr, "face_i = %d / %d" "\n", face_i, pObject -> numOfFaces); 
  fprintf(stderr, "vPoly[0] = { %f ; %f ; %f }" "\n", vPoly[0].x, vPoly[0].y, vPoly[0].z); 
  fprintf(stderr, "vPoly[1] = { %f ; %f ; %f }" "\n", vPoly[1].x, vPoly[1].y, vPoly[1].z); 
  fprintf(stderr, "vPoly[2] = { %f ; %f ; %f }" "\n", vPoly[2].x, vPoly[2].y, vPoly[2].z); 
#endif 



  // Now let's calculate the face normals (Get 2 vectors and find the cross product of those 2)

#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
  fprintf(stderr, "face_i = %d / %d" "\n", face_i, pObject -> numOfFaces); 
#endif 
  vVector1 = Vector(vPoly[0], vPoly[2]);      // Get the vector of the polygon (we just need 2 sides for the normal)
  //vVector2 = Vector(vPoly[0], vPoly[2]);      // Get the vector of the polygon (we just need 2 sides for the normal)
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
  fprintf(stderr, "face_i = %d / %d" "\n", face_i, pObject -> numOfFaces); 
#endif 
  vVector2 = Vector(vPoly[2], vPoly[1]);      // Get a second vector of the polygon
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
  fprintf(stderr, "face_i = %d / %d" "\n", face_i, pObject -> numOfFaces); 
#endif 

#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
  fprintf(stderr, "face_i = %d / %d" "\n", face_i, pObject -> numOfFaces); 
#endif 
  vNormal = Cross(vVector1, vVector2);       // Return the cross product of the 2 vectors (normalize vector, but not a unit vector)
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
  fprintf(stderr, "pTempNormals = %p" "\n", pTempNormals); 
  fprintf(stderr, "face_i = %d / %d" "\n", face_i, pObject -> numOfFaces); 
  fprintf(stderr, "sizeof(*pTempNormals) = %d" "\n", sizeof(*pTempNormals)); 
  fprintf(stderr, "pTempNormals[face_i] = %p" "\n", pTempNormals[face_i]); 
#endif 
  pTempNormals[face_i] = vNormal;                  // Save the un-normalized normal for the vertex normals
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  vNormal  = Normalize(vNormal);              // Normalize the cross product to give us the polygons normal

#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  pNormals[face_i] = vNormal;                      // Assign the normal to the list of normals
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  //if (face_i == 0) assert(false);
};

#undef DEBUG_TRACE
#define DEBUG_TRACE 1


static void ComputeNormals_one_object(CLoad3DS * this, t3DModel *pModel, t3DObject * pObject) { 
  // RL: Il s'agit de calculer les normales des sommets. 
  //     D'abord il faut calculer les normales des faces. 
  //     Car la normale d'un sommet est la moyenne des normales de ses faces. 
  //     (En l'occurrence, il prend l'opposé de cette moyenne...?)

  // What are vertex normals?  And how are they different from other normals?
  // Well, if you find the normal to a triangle, you are finding a "Face Normal".
  // If you give OpenGL a face normal for lighting, it will make your object look
  // really flat and not very round.  If we find the normal for each vertex, it makes
  // the smooth lighting look.  This also covers up blocky looking objects and they appear
  // to have more polygons than they do.    Basically, what you do is first
  // calculate the face normals, then you take the average of all the normals around each
  // vertex.  It's just averaging.  That way you get a better approximation for that vertex.

#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 

  CVector3 *pNormals      = malloc(pObject->numOfFaces * sizeof(CVector3));
  CVector3 *pTempNormals  = malloc(pObject->numOfFaces * sizeof(CVector3));
    
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
    
  for (uint16_t face_i = 0; face_i < pObject -> numOfFaces; face_i++) {
    tFace *pFace = &pObject->pFaces[face_i];
    ComputeNormals_one_face(this, pModel, pObject, pFace, face_i, pNormals, pTempNormals); 
  };
    
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  
  
    
  //////////////// Now Get The Vertex Normals /////////////////

  pObject->pNormals       = malloc(pObject->numOfVerts * sizeof(CVector3));

  CVector3 vSum = {0.0, 0.0, 0.0};
  CVector3 vZero = vSum;
  int shared = 0;

  for (uint16_t vert_i = 0; vert_i < pObject->numOfVerts; vert_i++) {
    vSum = vZero; 
    shared = 0; 
    for (uint16_t face_i = 0; face_i < pObject->numOfFaces; face_i++) {                                               
      // Check if the vertex is shared by another face
      if (pObject->pFaces[face_i].vertIndex[0] == vert_i) goto label__found_one;
      if (pObject->pFaces[face_i].vertIndex[1] == vert_i) goto label__found_one;
      if (pObject->pFaces[face_i].vertIndex[2] == vert_i) goto label__found_one;
      continue;
      
    label__found_one:
      // Add the un-normalized normal of the shared face
      vSum = AddVector(vSum, pTempNormals[face_i]);
      shared++; 
    }; 
    pObject->pNormals[vert_i] = DivideVectorByScaler(vSum, (-shared)); 
    pObject->pNormals[vert_i] = Normalize(pObject->pNormals[vert_i]); 
  };
    
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
  free(pTempNormals);
  free(pNormals);
#if DEBUG_TRACE != 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "DEBUG:  " STRINGIFY(__LINE__)  "\n", __func__);  
#endif 
};



void ComputeNormals(CLoad3DS * this, t3DModel *pModel) {
  if (pModel -> numOfObjects <= 0) return;
  for (int index = 0; index < pModel->numOfObjects; index++) {
      t3DObject * pObject = &(pModel->pObject[index]);
      ComputeNormals_one_object(this, pModel, pObject);
  };
};



/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// This was a HUGE amount of knowledge and probably the largest tutorial yet!
// In the next tutorial we will show you how to load a text file format called .obj.
// This is the most common 3D file format that almost ANY 3D software will import.
//
// Once again I should point out that the coordinate system of OpenGL and 3DS Max are different.
// Since 3D Studio Max Models with the Z-Axis pointing up (strange and ugly I know! :), 
// we need to flip the y values with the z values in our vertices.  That way it
// will be normal, with Y pointing up.  Also, because we swap the Y and Z we need to negate 
// the Z to make it come out correctly.  This is also explained and done in ReadVertices().
//
// CHUNKS: What is a chunk anyway?
// 
// "The chunk ID is a unique code which identifies the type of data in this chunk 
// and also may indicate the existence of subordinate chunks. The chunk length indicates 
// the length of following data to be associated with this chunk. Note, this may 
// contain more data than just this chunk. If the length of data is greater than that 
// needed to fill in the information for the chunk, additional subordinate chunks are 
// attached to this chunk immediately following any data needed for this chunk, and 
// should be parsed out. These subordinate chunks may themselves contain subordinate chunks. 
// Unfortunately, there is no indication of the length of data, which is owned by the current 
// chunk, only the total length of data attached to the chunk, which means that the only way 
// to parse out subordinate chunks is to know the exact format of the owning chunk. On the 
// other hand, if a chunk is unknown, the parsing program can skip the entire chunk and 
// subordinate chunks in one jump. " - Jeff Lewis (werewolf@worldgate.com)
//
// In a short amount of words, a chunk is defined this way:
// 2 bytes - Stores the chunk ID (OBJECT, MATERIAL, PRIMARY, etc...)
// 4 bytes - Stores the length of that chunk.  That way you know when that
//           chunk is done and there is a new chunk.
//
// So, to start reading the 3DS file, you read the first 2 bytes of it, then
// the length (using fread()).  It should be the PRIMARY chunk, otherwise it isn't
// a .3DS file.  
//
// Below is a list of the order that you will find the chunks and all the know chunks.
// If you go to www.wosit.org you can find a few documents on the 3DS file format.
// You can also take a look at the 3DS Format.rtf that is included with this tutorial.
//
//
//
//      MAIN3DS  (0x4D4D)
//     |
//     +--EDIT3DS  (0x3D3D)
//     |  |
//     |  +--EDIT_MATERIAL (0xAFFF)
//     |  |  |
//     |  |  +--MAT_NAME01 (0xA000) (See mli Doc) 
//     |  |
//     |  +--EDIT_CONFIG1  (0x0100)
//     |  +--EDIT_CONFIG2  (0x3E3D) 
//     |  +--EDIT_VIEW_P1  (0x7012)
//     |  |  |
//     |  |  +--TOP            (0x0001)
//     |  |  +--BOTTOM         (0x0002)
//     |  |  +--LEFT           (0x0003)
//     |  |  +--RIGHT          (0x0004)
//     |  |  +--FRONT          (0x0005) 
//     |  |  +--BACK           (0x0006)
//     |  |  +--USER           (0x0007)
//     |  |  +--CAMERA         (0xFFFF)
//     |  |  +--LIGHT          (0x0009)
//     |  |  +--DISABLED       (0x0010)  
//     |  |  +--BOGUS          (0x0011)
//     |  |
//     |  +--EDIT_VIEW_P2  (0x7011)
//     |  |  |
//     |  |  +--TOP            (0x0001)
//     |  |  +--BOTTOM         (0x0002)
//     |  |  +--LEFT           (0x0003)
//     |  |  +--RIGHT          (0x0004)
//     |  |  +--FRONT          (0x0005) 
//     |  |  +--BACK           (0x0006)
//     |  |  +--USER           (0x0007)
//     |  |  +--CAMERA         (0xFFFF)
//     |  |  +--LIGHT          (0x0009)
//     |  |  +--DISABLED       (0x0010)  
//     |  |  +--BOGUS          (0x0011)
//     |  |
//     |  +--EDIT_VIEW_P3  (0x7020)
//     |  +--EDIT_VIEW1    (0x7001) 
//     |  +--EDIT_BACKGR   (0x1200) 
//     |  +--EDIT_AMBIENT  (0x2100)
//     |  +--EDIT_OBJECT   (0x4000)
//     |  |  |
//     |  |  +--OBJ_TRIMESH   (0x4100)      
//     |  |  |  |
//     |  |  |  +--TRI_VERTEXL          (0x4110) 
//     |  |  |  +--TRI_VERTEXOPTIONS    (0x4111)
//     |  |  |  +--TRI_MAPPINGCOORS     (0x4140) 
//     |  |  |  +--TRI_MAPPINGSTANDARD  (0x4170)
//     |  |  |  +--TRI_FACEL1           (0x4120)
//     |  |  |  |  |
//     |  |  |  |  +--TRI_SMOOTH            (0x4150)   
//     |  |  |  |  +--TRI_MATERIAL          (0x4130)
//     |  |  |  |
//     |  |  |  +--TRI_LOCAL            (0x4160)
//     |  |  |  +--TRI_VISIBLE          (0x4165)
//     |  |  |
//     |  |  +--OBJ_LIGHT    (0x4600)
//     |  |  |  |
//     |  |  |  +--LIT_OFF              (0x4620)
//     |  |  |  +--LIT_SPOT             (0x4610) 
//     |  |  |  +--LIT_UNKNWN01         (0x465A) 
//     |  |  | 
//     |  |  +--OBJ_CAMERA   (0x4700)
//     |  |  |  |
//     |  |  |  +--CAM_UNKNWN01         (0x4710)
//     |  |  |  +--CAM_UNKNWN02         (0x4720)  
//     |  |  |
//     |  |  +--OBJ_UNKNWN01 (0x4710)
//     |  |  +--OBJ_UNKNWN02 (0x4720)
//     |  |
//     |  +--EDIT_UNKNW01  (0x1100)
//     |  +--EDIT_UNKNW02  (0x1201) 
//     |  +--EDIT_UNKNW03  (0x1300)
//     |  +--EDIT_UNKNW04  (0x1400)
//     |  +--EDIT_UNKNW05  (0x1420)
//     |  +--EDIT_UNKNW06  (0x1450)
//     |  +--EDIT_UNKNW07  (0x1500)
//     |  +--EDIT_UNKNW08  (0x2200)
//     |  +--EDIT_UNKNW09  (0x2201)
//     |  +--EDIT_UNKNW10  (0x2210)
//     |  +--EDIT_UNKNW11  (0x2300)
//     |  +--EDIT_UNKNW12  (0x2302)
//     |  +--EDIT_UNKNW13  (0x2000)
//     |  +--EDIT_UNKNW14  (0xAFFF)
//     |
//     +--KEYF3DS (0xB000)
//        |
//        +--KEYF_UNKNWN01 (0xB00A)
//        +--............. (0x7001) ( viewport, same as editor )
//        +--KEYF_FRAMES   (0xB008)
//        +--KEYF_UNKNWN02 (0xB009)
//        +--KEYF_OBJDES   (0xB002)
//           |
//           +--KEYF_OBJHIERARCH  (0xB010)
//           +--KEYF_OBJDUMMYNAME (0xB011)
//           +--KEYF_OBJUNKNWN01  (0xB013)
//           +--KEYF_OBJUNKNWN02  (0xB014)
//           +--KEYF_OBJUNKNWN03  (0xB015)  
//           +--KEYF_OBJPIVOT     (0xB020)  
//           +--KEYF_OBJUNKNWN04  (0xB021)  
//           +--KEYF_OBJUNKNWN05  (0xB022)  
//
// Once you know how to read chunks, all you have to know is the ID you are looking for
// and what data is stored after that ID.  You need to get the file format for that.
// I can give it to you if you want, or you can go to www.wosit.org for several versions.
// Because this is a proprietary format, it isn't a official document.
//
// I know there was a LOT of information blown over, but it is too much knowledge for
// one tutorial.  In the animation tutorial that I eventually will get to, some of
// the things explained here will be explained in more detail.  I do not claim that
// this is the best .3DS tutorial, or even a GOOD one :)  But it is a good start, and there
// isn't much code out there that is simple when it comes to reading .3DS files.
// So far, this is the best I have seen.  That is why I made it :)
// 
// I would like to thank www.wosit.org and Terry Caton (tcaton@umr.edu) for his help on this.
//
// Let me know if this helps you out!
// 
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//
