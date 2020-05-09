
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

#define debug_printf(...) 
#ifdef DEBUG_3DS_USING_PRINTF 
#if (DEBUG_3DS_USING_PRINTF != 0) 
#undef debug_printf 
#define debug_printf printf 
#endif 
#endif 


//struct CLoad3DS * new_CLoad3DS(void);
static bool Import3DS(struct CLoad3DS * this, t3DModel * pModel, const char * strFileName);
static int  GetString(struct CLoad3DS * this, char *);
static void ReadChunk(struct CLoad3DS * this, tChunk *);
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
  this -> ReadChunk = ReadChunk;
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
    
  //printf("appel à Import3DS : pModel->numOfObjects = %i\n", pModel->numOfObjects);
    
  pModel -> numOfMaterials = 0;
  pModel -> numOfObjects = 0;
    
  //printf("appel à Import3DS : pModel->numOfObjects = %i\n", pModel->numOfObjects);
    
  // Open the 3DS file
  this -> m_FilePointer = fopen(strFileName, "rb");

  // Make sure we have a valid file pointer (we found the file)
  if (!this -> m_FilePointer) {
    printf("Unable to find the file: %s!\n", strFileName); 
    CleanUp(this);
    return false; 
  }; 
  
  // Once we have the file open, we need to read the very first data chunk
  // to see if it's a 3DS file.  That way we don't read an invalid file.
  // If it is a 3DS file, then the first chunk ID will be equal to PRIMARY (some hex num)
  
  // Read the first chuck of the file to see if it's a 3DS file
  ReadChunk(this, this -> m_CurrentChunk);

  // Make sure this is a 3DS file
  if (this -> m_CurrentChunk -> ID != PRIMARY) { 
    snprintf(strMessage, sizeof(strMessage), "Unable to load PRIMARY chuck from file: %s!", strFileName); 
    printf("%s\n", strMessage); 
    CleanUp(this); 
    return false; 
  }; 
  
  
  debug_printf("Le primary chunk a été loadé ; ID = %X ; PRIMARY = %X ; pointeur vers le fichier : %p\n", this -> m_CurrentChunk->ID, PRIMARY, this -> m_FilePointer);

  // Now we actually start reading in the data.  ProcessNextChunk() is recursive
  
  // Begin loading objects, by calling this recursive function
  debug_printf("   ProcessNextChunk...\n");
  ProcessNextChunk(this, pModel, this -> m_CurrentChunk);

  // After we have read the whole 3DS file, we want to calculate our own vertex normals.
  debug_printf("   ComputeNormals...\n");
  ComputeNormals(this, pModel);

  // Clean up after everything
  CleanUp(this);

  return true;
}

///////////////////////////////// CLEAN UP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function cleans up our allocated memory and closes the file
/////
///////////////////////////////// CLEAN UP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CleanUp(struct CLoad3DS * this) { 
  fclose(this -> m_FilePointer);                      // Close the current file pointer
  free(this -> m_CurrentChunk);                      // Free the current chunk
  free(this -> m_TempChunk);                         // Free our temporary chunk
}; 


///////////////////////////////// PROCESS NEXT CHUNK\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads the main sections of the .3DS file, then dives deeper with recursion
/////
///////////////////////////////// PROCESS NEXT CHUNK\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ProcessNextChunk(CLoad3DS * this, t3DModel *pModel, tChunk *pPreviousChunk) {
  t3DObject newObject;// = {0};
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
  tMaterialInfo newTexture;// = {0};  
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
    
  /*INITIALISATION MANQUANTE QUI MAINTENANT NE MANQUE PLUS*/
  /* pModel->numOfMaterials = 0;
     pModel->numOfObjects = 0;*/
  
  debug_printf("appel à processchunk : pModel->numOfObjects = %i\n", pModel->numOfObjects);

    
  unsigned int version = 0;                   // This will hold the file version
  //int buffer[5000] = {0};                    // This is used to read past unwanted data

  this -> m_CurrentChunk = new_tChunk();                // Allocate a new chunk             
  
  // Below we check our chunk ID each time we read a new chunk.  Then, if
  // we want to extract the information from that chunk, we do so.
  // If we don't want a chunk, we just read past it.  

  // Continue to read the sub chunks until we have reached the length.
  // After we read ANYTHING we add the bytes read to the chunk and then check
  // check against the length.
  debug_printf("boucle du chunk...\n");
  while (pPreviousChunk->bytesRead < pPreviousChunk->length) {
      // Read next Chunk
      debug_printf("   on lit un chunk...\n");
      ReadChunk(this, this -> m_CurrentChunk);

      debug_printf("    chunk lu avec succès...\n");
      // Check the chunk ID
      switch (this -> m_CurrentChunk->ID) {
        case VERSION:                           // This holds the version of the file
          debug_printf("    chunk VERSION... %X\n", VERSION);
          // This chunk has an unsigned short that holds the file version.
          // Since there might be new additions to the 3DS file format in 4.0,
          // we give a warning to that problem.

          // Read the file version and add the bytes read to our bytesRead variable
          //m_CurrentChunk->bytesRead += fread(&version, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
          this -> m_CurrentChunk->bytesRead += 4 * fread_(&version, 4, 1, this -> m_FilePointer);
          // On skippe s'il en reste.
          if (fseek(this -> m_FilePointer, this -> m_CurrentChunk->length - this -> m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
            { printf("Erreur de positionnement."); }
          this -> m_CurrentChunk->bytesRead = this -> m_CurrentChunk->length;
          debug_printf("Version: %X\n", version);

          // If the file version is over 3, give a warning that there could be a problem
          if (version > 0x03)
            printf("This 3DS file is over version 3 so it may load incorrectly\n");
          break;

        case OBJECTINFO:                        // This holds the version of the mesh
          debug_printf("    chunk OBJECTINFO... %X\n", OBJECTINFO);
          // This chunk holds the version of the mesh.  It is also the head of the MATERIAL
          // and OBJECT chunks.  From here on we start reading in the material and object info.

          // Read the next chunk
          ReadChunk(this, this -> m_TempChunk);

          // Get the version of the mesh
          //m_TempChunk->bytesRead += fread(&version, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);
          this -> m_TempChunk->bytesRead += 4 * fread_(&version, 4, 1, this -> m_FilePointer);
          // On skippe s'il en reste.
          if (fseek(this -> m_FilePointer, this -> m_TempChunk->length - this -> m_TempChunk->bytesRead, SEEK_CUR) != 0)
            { printf("Erreur de positionnement Mesh."); }
          debug_printf("Version Mesh: %X\n", version);
          //printf("m_TempChunk->length = %u\n", m_TempChunk->length); fflush(NULL);

          // Increase the bytesRead by the bytes read from the last chunk
          //m_CurrentChunk->bytesRead += m_TempChunk->bytesRead;
          this -> m_CurrentChunk->bytesRead += this -> m_TempChunk->length;

          // Go to the next chunk, which is the object has a texture, it should be MATERIAL, then OBJECT.
          ProcessNextChunk(this, pModel, this -> m_CurrentChunk);
          break;

        case MATERIAL:                          // This holds the material information
          debug_printf("    chunk MATERIAL... %X\n", MATERIAL);
          // This chunk is the header for the material info chunks

          // Add a empty texture structure to our texture list.
          // If you are unfamiliar with STL's "vector" class, all push_back()
          // does is add a new node onto the list.  I used the vector class
          // so I didn't need to write my own link list functions.  
          //pModel->pMaterials.push_back(newTexture);
          //pModel->pMaterials[pModel->pMaterials_nb++] = (newTexture);
          pModel->pMaterials[pModel->numOfMaterials] = (newTexture);

          // Increase the number of materials
          pModel->numOfMaterials++;

          // Proceed to the material loading function
          ProcessNextMaterialChunk(this, pModel, this -> m_CurrentChunk);
          break;

        case OBJECT:                            // This holds the name of the object being read
          debug_printf("    chunk OBJECT...\n");    
          // This chunk is the header for the object info chunks.  It also
          // holds the name of the object.

          // Add a new tObject node to our list of objects (like a link list)
          //pModel->pObject.push_back(newObject);
          //pModel->pObject[pModel->pObject_nb++] = (newObject);
          pModel->pObject[pModel->numOfObjects] = (newObject);
            
          // Increase the object count
          pModel->numOfObjects++;
        
          // Initialize the object and all it's data members
          debug_printf("    on initialise à 0 le pObject[%i]...\n",  pModel->numOfObjects - 1); 
          memset(&(pModel->pObject[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));
          debug_printf("    initialisation à 0 du pObject[%i] réussi...\n", pModel->numOfObjects - 1);  
          // Get the name of the object and store it, then add the read bytes to our byte counter.
          this -> m_CurrentChunk->bytesRead += GetString(this, pModel->pObject[pModel->numOfObjects - 1].strName);
            
          // Now proceed to read in the rest of the object information
          ProcessNextObjectChunk(this, pModel, &(pModel->pObject[pModel->numOfObjects - 1]), this -> m_CurrentChunk);
          break;

        case EDITKEYFRAME:
          debug_printf("    chunk EDITKEYFRAME... %X\n", EDITKEYFRAME);   
          // Because I wanted to make this a SIMPLE tutorial as possible, I did not include
          // the key frame information.  This chunk is the header for all the animation info.
          // In a later tutorial this will be the subject and explained thoroughly.

          //ProcessNextKeyFrameChunk(pModel, m_CurrentChunk);

          // Read past this chunk and add the bytes read to the byte counter
          //m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
    
          if (fseek(this -> m_FilePointer, this -> m_CurrentChunk->length - this -> m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
            { printf("Erreur de positionnement."); }
    
          this -> m_CurrentChunk->bytesRead = this -> m_CurrentChunk->length;
          break;

        default: 
          debug_printf("    chunk non identifié, tant pis on passe au suivant... %X\n", this -> m_CurrentChunk->ID);    
          // If we didn't care about a chunk, then we get here.  We still need
          // to read past the unknown or ignored chunk and add the bytes read to the byte counter.
          //m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
    
          if (fseek(this -> m_FilePointer, this -> m_CurrentChunk->length - this -> m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
            { debug_printf("Erreur de positionnement."); }
          this -> m_CurrentChunk->bytesRead = this -> m_CurrentChunk->length;
          break;
        }

      // Add the bytes read from the last chunk to the previous chunk passed in.
      pPreviousChunk->bytesRead += this -> m_CurrentChunk->bytesRead;
    }

  // Free the current chunk and set it back to the previous chunk (since it started that way)
  free(this -> m_CurrentChunk);
  this -> m_CurrentChunk = pPreviousChunk;
  debug_printf("fin chunk...\n");
}


///////////////////////////////// PROCESS NEXT OBJECT CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function handles all the information about the objects in the file
/////
///////////////////////////////// PROCESS NEXT OBJECT CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ProcessNextObjectChunk(CLoad3DS * this, t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk) {
  //int buffer[50000] = {0};                    // This is used to read past unwanted data
 
  // Allocate a new chunk to work with
  debug_printf("    Appel ProcessNextObjectChunk...\n");   
  this->m_CurrentChunk = new_tChunk();

  // Continue to read these chunks until we read the end of this sub chunk
  while (pPreviousChunk->bytesRead < pPreviousChunk->length) {
      // Read the next chunk
      debug_printf("      on lit chunk (object chunk)...\n");  
      ReadChunk(this, this->m_CurrentChunk);
      debug_printf("      chunk lu (object chunk) avec succès...\n");  
      // Check which chunk we just read
      switch (this->m_CurrentChunk->ID)
        {
        case OBJECT_MESH:                   // This lets us know that we are reading a new object
          debug_printf("      object-chunk OBJECT_MESH... %X\n", OBJECT_MESH);  
          // We found a new object, so let's read in it's info using recursion
          ProcessNextObjectChunk(this, pModel, pObject, this->m_CurrentChunk);
          break;

        case OBJECT_VERTICES:               // This is the objects vertices
          debug_printf("      object-chunk OBJECT_VERTICES... %X\n", OBJECT_VERTICES);  
          ReadVertices(this, pObject, this->m_CurrentChunk);
          break;

        case OBJECT_FACES:                  // This is the objects face information
          debug_printf("      object-chunk OBJECT_FACES... %X\n", OBJECT_FACES);  
          ReadVertexIndices(this, pObject, this->m_CurrentChunk);
          debug_printf("OBJECT_FACES: Read = %u ; Length = %u\n", this->m_CurrentChunk->bytesRead, this->m_CurrentChunk->length);
          break;

        case OBJECT_MATERIAL:               // This holds the material name that the object has
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
          debug_printf("      object-chunk OBJECT_UV... %X\n", OBJECT_UV);  
          // This chunk holds all of the UV coordinates for our object.  Let's read them in.
          ReadUVCoordinates(this, pObject, this->m_CurrentChunk);
          break;

        default:  
          debug_printf("      object-chunk non reconnu : on l'ignore... %X\n", this->m_CurrentChunk->ID);   
          // Read past the ignored or unknown chunks
          //this->m_CurrentChunk->bytesRead += fread(buffer, 1, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, m_FilePointer);
          // On skippe s'il en reste.
          if (fseek(this->m_FilePointer, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, SEEK_CUR) != 0)
            { printf("Erreur de positionnement OBJECT.");}
          this->m_CurrentChunk->bytesRead = this->m_CurrentChunk->length;
    
          break;
        }

      // Add the bytes read from the last chunk to the previous chunk passed in.
      pPreviousChunk->bytesRead += this->m_CurrentChunk->bytesRead;
    }

  // Free the current chunk and set it back to the previous chunk (since it started that way)
  free(this->m_CurrentChunk);
  this->m_CurrentChunk = pPreviousChunk;
}


///////////////////////////////// PROCESS NEXT MATERIAL CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function handles all the information about the material (Texture)
/////
///////////////////////////////// PROCESS NEXT MATERIAL CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ProcessNextMaterialChunk(CLoad3DS * this, t3DModel *pModel, tChunk *pPreviousChunk) {
  //int buffer[50000] = {0};                    // This is used to read past unwanted data

  // Allocate a new chunk to work with
  this->m_CurrentChunk = new_tChunk();

  // Continue to read these chunks until we read the end of this sub chunk
  while (pPreviousChunk->bytesRead < pPreviousChunk->length)
    {
      // Read the next chunk
      ReadChunk(this, this->m_CurrentChunk);

      // Check which chunk we just read in
      switch (this->m_CurrentChunk->ID)
        {
        case MATNAME:                           // This chunk holds the name of the material
          debug_printf("  Chunk Material Name %X\n", MATNAME);
          // Here we read in the material name
          //this->m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strName, 1, this->m_CurrentChunk->length - this->m_CurrentChunk->bytesRead, this->m_FilePointer);
          this->m_CurrentChunk->bytesRead += GetString(this, pModel->pMaterials[pModel->numOfMaterials - 1].strName);
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
          this->m_CurrentChunk->bytesRead += GetString(this, pModel->pMaterials[pModel->numOfMaterials - 1].strFile);
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
    }

  // Free the current chunk and set it back to the previous chunk (since it started that way)
  free(this->m_CurrentChunk);
  this->m_CurrentChunk = pPreviousChunk;
}

///////////////////////////////// READ CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in a chunk ID and it's length in bytes
/////
///////////////////////////////// READ CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ReadChunk(CLoad3DS * this, tChunk *pChunk) { 
  // This reads the chunk ID which is 2 bytes.
  // The chunk ID is like OBJECT or MATERIAL.  It tells what data is 
  // able to be read in within the chunks section.  
  //pChunk->bytesRead = fread(&pChunk->ID, 1, 2, this->m_FilePointer); 
  //pChunk -> bytesRead = 2 * fread_(&pChunk -> ID, /*object size*/2, /*number of objects to be read*/1, this -> m_FilePointer); 
  pChunk -> bytesRead = fread_(&pChunk -> ID, /*object size*/1, /*number of objects to be read*/2, this -> m_FilePointer); 
  debug_printf("ChunkID: %4X\n", (unsigned int) pChunk -> ID); 
  
  // Then, we read the length of the chunk which is 4 bytes. 
  // This is how we know how much to read in, or read past. 
  //pChunk->bytesRead += fread(&pChunk->length, 1, 4, this->m_FilePointer);
  //pChunk->bytesRead += 4 * fread_(&pChunk->length, /*object size*/4, /*number of objects to be read*/1, this->m_FilePointer); 
  pChunk -> bytesRead += fread_(&pChunk -> length, /*object size*/1, /*number of objects to be read*/4, this->m_FilePointer); 
  //messerr("ChunkLength: %u\n", pChunk -> length); 
  debug_printf("ChunkLength: %u\n", pChunk -> length); 
  debug_printf("Lecture En-Tete Chunk oki.\n"); 
}; 

///////////////////////////////// GET STRING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function reads in a string of characters
/////
///////////////////////////////// GET STRING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int GetString(CLoad3DS * this, char *pBuffer) {
  int index = 0;

  // Read 1 byte of data which is the first letter of the string
  fread(pBuffer, 1, 1, this->m_FilePointer);

  // Loop until we get NULL
  while (*(pBuffer + index++) != 0) {

    // Read in a character at a time until we hit NULL.
    fread(pBuffer + index, 1, 1, this->m_FilePointer);
  }

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
  ReadChunk(this, this->m_TempChunk);

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
#ifndef LIBPROG_ENDIAN_BIG
  pPreviousChunk->bytesRead += 2 * fread_(&pObject->numOfFaces, 2, 1, this->m_FilePointer);
#else
  pObject->numOfFaces = 0;
  pPreviousChunk->bytesRead += 2 * fread_((((unsigned short *)(&((pObject)->numOfFaces))) + 1), 2, 1, this->m_FilePointer);
#endif
  debug_printf("Number of vertices: %d\n",  pObject->numOfFaces);

  // Alloc enough memory for the faces and initialize the structure
  //pObject->pFaces = new tFace [pObject->numOfFaces];
  pObject->pFaces = malloc(pObject->numOfFaces * sizeof(tFace));
  memset(pObject->pFaces, 0, sizeof(tFace) * pObject->numOfFaces);

  // Go through all of the faces in this object
  for (int i = 0; i < pObject->numOfFaces; i++)
    {
      // Next, we read in the A then B then C index for the face, but ignore the 4th value.
      // The fourth value is a visibility flag for 3D Studio Max, we don't care about this.
      for (int j = 0; j < 4; j++)
        {
          // Read the first vertice index for the current face 
          //pPreviousChunk->bytesRead += fread(&index, 1, sizeof(index), this->m_FilePointer);
          pPreviousChunk->bytesRead += 2 * fread_(&index, 2, 1, this->m_FilePointer);
          debug_printf("ReadVertexIndices: index = %d\n", (int) index);

          if (j < 3)
            {
              // Store the index in our face structure.
              pObject->pFaces[i].vertIndex[j] = index;
            }
        }
    }
}


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
  debug_printf("  Number of Vertices: %d --- \n", pObject->numTexVertex); fflush(NULL);
  

  // Allocate memory to hold the UV coordinates

  // Si il y a 0 elt, le new plante sur mac
#ifdef LIBPROG_SYS_MACOSX
  if (pObject->numTexVertex != 0)
    pObject->pTexVerts = new CVector2 [pObject->numTexVertex];
  else
    pObject->pTexVerts = NULL;
#else
  //pObject->pTexVerts = new CVector2 [pObject->numTexVertex];
  pObject->pTexVerts = malloc(pObject->numTexVertex * sizeof(CVector2));
#endif

  // Read in the texture coodinates (an array 2 float)
  // Un float ici c'est 4.
  // Attention, ici tableau de vecteur...
  //messerr("ReadUVCoordinates:  pPreviousChunk->length = %u,  pPreviousChunk->bytesRead = %u\n", pPreviousChunk->length, pPreviousChunk->bytesRead);
  //pPreviousChunk->bytesRead += fread(pObject->pTexVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, this->m_FilePointer);
  pPreviousChunk->bytesRead += 4 * fread_(pObject->pTexVerts, 4, (pPreviousChunk->length - pPreviousChunk->bytesRead) / 4, this->m_FilePointer);
  // On skippe s'il en reste.
  if (fseek(this->m_FilePointer, pPreviousChunk->length - pPreviousChunk->bytesRead, SEEK_CUR) != 0)
    { printf("Erreur de positionnement ReadUVCoordinates."); }
  pPreviousChunk->bytesRead = pPreviousChunk->length;

}


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


  // Allocate the memory for the verts and initialize the structure
  //pObject->pVerts = new CVector3 [pObject->numOfVerts];
  pObject->pVerts = malloc(pObject->numOfVerts * sizeof(CVector3));
  memset(pObject->pVerts, 0, sizeof(CVector3) * pObject->numOfVerts);

  // Read in the array of vertices (an array of 3 floats)
  // C'est un tableau !!!!
  // Un float c 4.
  //pPreviousChunk->bytesRead += fread(pObject->pVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, this->m_FilePointer);
  pPreviousChunk->bytesRead += 4 * fread_(pObject->pVerts, 4, (pPreviousChunk->length - pPreviousChunk->bytesRead) / 4, this->m_FilePointer);
  // On skippe s'il en reste.
  if (fseek(this->m_FilePointer, pPreviousChunk->length - pPreviousChunk->bytesRead, SEEK_CUR) != 0)
    { printf("Erreur de positionnement ReadVertices."); }
  pPreviousChunk->bytesRead = pPreviousChunk->length;


  // Now we should have all of the vertices read in.  Because 3D Studio Max
  // Models with the Z-Axis pointing up (strange and ugly I know!), we need
  // to flip the y values with the z values in our vertices.  That way it
  // will be normal, with Y pointing up.  If you prefer to work with Z pointing
  // up, then just delete this next loop.  Also, because we swap the Y and Z
  // we need to negate the Z to make it come out correctly.

  // Go through all of the vertices that we just read and swap the Y and Z values
  for (int i = 0; i < pObject->numOfVerts; i++)
    {
      // Store off the Y value
      float fTempY = pObject->pVerts[i].y;

      // Set the Y value to the Z value
      pObject->pVerts[i].y = pObject->pVerts[i].z;

      // Set the Z value to the Y value, 
      // but negative Z because 3D Studio max does the opposite.
      pObject->pVerts[i].z = -fTempY;
    }
}


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
  pPreviousChunk->bytesRead += GetString(this, strMaterial);

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
      if (strcmp(strMaterial, pModel->pMaterials[i].strName) == 0)
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

// This computes the magnitude of a normal.   (magnitude = sqrt(x^2 + y^2 + z^2)
#define Mag(Normal) (sqrt(Normal.x*Normal.x + Normal.y*Normal.y + Normal.z*Normal.z))

// This calculates a vector between 2 points and returns the result
CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2)
{
  CVector3 vVector;                           // The variable to hold the resultant vector

  vVector.x = vPoint1.x - vPoint2.x;          // Subtract point1 and point2 x's
  vVector.y = vPoint1.y - vPoint2.y;          // Subtract point1 and point2 y's
  vVector.z = vPoint1.z - vPoint2.z;          // Subtract point1 and point2 z's

  return vVector;                             // Return the resultant vector
}

// This adds 2 vectors together and returns the result
CVector3 AddVector(CVector3 vVector1, CVector3 vVector2)
{
  CVector3 vResult;                           // The variable to hold the resultant vector
    
  vResult.x = vVector2.x + vVector1.x;        // Add Vector1 and Vector2 x's
  vResult.y = vVector2.y + vVector1.y;        // Add Vector1 and Vector2 y's
  vResult.z = vVector2.z + vVector1.z;        // Add Vector1 and Vector2 z's

  return vResult;                             // Return the resultant vector
}

// This divides a vector by a single number (scalar) and returns the result
CVector3 DivideVectorByScaler(CVector3 vVector1, float Scaler)
{
  CVector3 vResult;                           // The variable to hold the resultant vector
    
  vResult.x = vVector1.x / Scaler;            // Divide Vector1's x value by the scaler
  vResult.y = vVector1.y / Scaler;            // Divide Vector1's y value by the scaler
  vResult.z = vVector1.z / Scaler;            // Divide Vector1's z value by the scaler

  return vResult;                             // Return the resultant vector
}

// This returns the cross product between 2 vectors
CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
  CVector3 vCross;                                // The vector to hold the cross product
  // Get the X value
  vCross.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
  // Get the Y value
  vCross.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
  // Get the Z value
  vCross.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

  return vCross;                              // Return the cross product
}

// This returns the normal of a vector
CVector3 Normalize(CVector3 vNormal)
{
  double Magnitude;                           // This holds the magitude          

  Magnitude = Mag(vNormal);                   // Get the magnitude

  vNormal.x /= (float)Magnitude;              // Divide the vector's X by the magnitude
  vNormal.y /= (float)Magnitude;              // Divide the vector's Y by the magnitude
  vNormal.z /= (float)Magnitude;              // Divide the vector's Z by the magnitude

  return vNormal;                             // Return the normal
}

///////////////////////////////// COMPUTER NORMALS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This function computes the normals and vertex normals of the objects
/////
///////////////////////////////// COMPUTER NORMALS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ComputeNormals(CLoad3DS * this, t3DModel *pModel) {
  CVector3 vVector1, vVector2, vNormal, vPoly[3];

  // If there are no objects, we can skip this part
  if (pModel->numOfObjects <= 0)
    return;

  // What are vertex normals?  And how are they different from other normals?
  // Well, if you find the normal to a triangle, you are finding a "Face Normal".
  // If you give OpenGL a face normal for lighting, it will make your object look
  // really flat and not very round.  If we find the normal for each vertex, it makes
  // the smooth lighting look.  This also covers up blocky looking objects and they appear
  // to have more polygons than they do.    Basically, what you do is first
  // calculate the face normals, then you take the average of all the normals around each
  // vertex.  It's just averaging.  That way you get a better approximation for that vertex.

  // Go through each of the objects to calculate their normals
  for (int index = 0; index < pModel->numOfObjects; index++)
    {
      // Get the current object
      t3DObject *pObject = &(pModel->pObject[index]);

      // Here we allocate all the memory we need to calculate the normals
#if 0
      CVector3 *pNormals      = new CVector3 [pObject->numOfFaces];
      CVector3 *pTempNormals  = new CVector3 [pObject->numOfFaces];
      pObject->pNormals       = new CVector3 [pObject->numOfVerts];
#else
      CVector3 *pNormals      = malloc(pObject->numOfFaces * sizeof(CVector3));
      CVector3 *pTempNormals  = malloc(pObject->numOfFaces * sizeof(CVector3));
      pObject->pNormals       = malloc(pObject->numOfVerts * sizeof(CVector3));
#endif

      // Go though all of the faces of this object
      for (int i=0; i < pObject->numOfFaces; i++)
        {                                               
          // To cut down LARGE code, we extract the 3 points of this face
          vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
          vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
          vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

          // Now let's calculate the face normals (Get 2 vectors and find the cross product of those 2)

          vVector1 = Vector(vPoly[0], vPoly[2]);      // Get the vector of the polygon (we just need 2 sides for the normal)
          vVector2 = Vector(vPoly[2], vPoly[1]);      // Get a second vector of the polygon

          vNormal  = Cross(vVector1, vVector2);       // Return the cross product of the 2 vectors (normalize vector, but not a unit vector)
          pTempNormals[i] = vNormal;                  // Save the un-normalized normal for the vertex normals
          vNormal  = Normalize(vNormal);              // Normalize the cross product to give us the polygons normal

          pNormals[i] = vNormal;                      // Assign the normal to the list of normals
        }

      //////////////// Now Get The Vertex Normals /////////////////

      CVector3 vSum = {0.0, 0.0, 0.0};
      CVector3 vZero = vSum;
      int shared=0;

      for (int i = 0; i < pObject->numOfVerts; i++)           // Go through all of the vertices
        {
          for (int j = 0; j < pObject->numOfFaces; j++)   // Go through all of the triangles
            {                                               // Check if the vertex is shared by another face
              if (pObject->pFaces[j].vertIndex[0] == i || 
                  pObject->pFaces[j].vertIndex[1] == i || 
                  pObject->pFaces[j].vertIndex[2] == i)
                {
                  vSum = AddVector(vSum, pTempNormals[j]);// Add the un-normalized normal of the shared face
                  shared++;                               // Increase the number of shared triangles
                }
            }      
            
          // Get the normal by dividing the sum by the shared.  We negate the shared so it has the normals pointing out.
          //pObject->pNormals[i] = DivideVectorByScaler(vSum, float(-shared));
          pObject->pNormals[i] = DivideVectorByScaler(vSum, (-shared));

          // Normalize the normal for the final vertex normal
          pObject->pNormals[i] = Normalize(pObject->pNormals[i]); 

          vSum = vZero;                                   // Reset the sum
          shared = 0;                                     // Reset the shared
        }
    
      // Free our memory and start over on the next object
      free(pTempNormals);
      free(pNormals);
    }
}


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
