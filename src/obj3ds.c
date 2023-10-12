#include "global.h"
#include "obj3ds.h"
#include "texture.h"

// ***** DB ***** 
enum        { obj3ds_dico__size = 256 }; 
static char * obj3ds_dico__filename[obj3ds_dico__size] = {}; 
static C3DS * obj3ds_dico__obj3ds  [obj3ds_dico__size] = {}; 
static int    obj3ds_dico__usersnb [obj3ds_dico__size] = {}; 
static int    obj3ds_dico__nb = 0; 

static int obj3ds_dico__push(const char * filename, C3DS * obj3ds_non_copie) {
  assert(obj3ds_dico__nb < obj3ds_dico__size); 
  const int index = obj3ds_dico__nb; 
  obj3ds_dico__filename[index] = strcopy(filename); 
  obj3ds_dico__obj3ds  [index] = obj3ds_non_copie; 
  obj3ds_dico__usersnb [index] = 1; 
  obj3ds_dico__nb++; 
  return index; 
}; 

static int obj3ds_dico__lookup(const char * filename) {
  char * * p = obj3ds_dico__filename; 
  for (int i = 0; i < obj3ds_dico__nb; i++) {
    if (0 == strcmp(*p, filename)) return i; 
    p++; 
  };
  return -1;
}; 

static C3DS * obj3ds_dico__get(const int i) {
  obj3ds_dico__usersnb[i] ++; 
  return obj3ds_dico__obj3ds[i];
}; 

static void obj3ds_dico__release(const int i) {
  obj3ds_dico__usersnb[i] --; 
}; 





// ***** OBJECT ***** 

static int C3DS__load(C3DS * this, const char * filename) { 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  bool b3dModelLoaded;
  
  //printf("Importation du fichier 3DS '%s'" "\n", filename); 
  
  this -> g_ViewMode = GL_TRIANGLES; 
  for (int i = 0; i < MAX_TEXTURES; i++) { 
    this -> g_Texture[i] = NULL; 
  }; 
  

  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  // RL: Reading the file. 
  { 
    CLoad3DS g_Load3ds; 
    //CLoad3DS_make_aux(&this -> g_Load3ds);
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(g_Load3ds) = %lu" "\n", __func__, (unsigned long) sizeof(g_Load3ds)); // 128 
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sizeof(*this) = %lu" "\n", __func__, (unsigned long) sizeof(*this)); // 861032...! 
    CLoad3DS_make_aux(&g_Load3ds);
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
    
    // First we need to actually load the .3DS file. 
    // We just pass in an address to our t3DModel structure and the file name string we want to load ("face.3ds"). 
    //printf("   Début de la lecture du fichier 3DS '%s' ... !!\n", filename); 
    //b3dModelLoaded = this -> g_Load3ds.Import3DS(&this -> g_Load3ds, &this -> g_3DModel, filename);         // Load our .3DS file into our model structure 
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
    b3dModelLoaded = g_Load3ds.Import3DS(&g_Load3ds, &this -> g_3DModel, filename); // Load our .3DS file into our model structure 
    //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
    //g_Load3ds.CleanUp(&g_Load3ds); 
    if (!b3dModelLoaded) { 
      messerr("ERREUR: " "Impossible de charger le fichier 3DS '%s' ; soit le fichier n'existe pas, soit il est corrompu.", filename); 
      fflush(NULL); 
      return false; 
    }; 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  }; 
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  //printf("   Lecture du fichier 3DS '%s' terminée !!\n", filename); 
  
  //fflush(NULL); 
  
  
  // RL: Looking for texture files. 
  // Depending on how many textures we found, load each one (Assuming .BMP)
  // If you want to load other files than bitmaps, you will need to adjust CreateTexture().
  // Below, we go through all of the materials and check if they have a texture map to load.
  // Otherwise, the material just holds the color information and we don't need to load a texture.

  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  // Go through all the materials
  //printf("   Récupération des textures du 3DS %s terminé !!\n", filename); 
  for (int i = 0; i < this -> g_3DModel.numOfMaterials; i++) {
    // Check to see if there is a file name to load in this material
    if (strlen(this -> g_3DModel.pMaterials[i].strFile) > 0) {   
      //printf("   Ahh le fichier 3DS référence la texture '%s' !!\n", this -> g_3DModel.pMaterials[i].strFile); 
      // Use the name of the texture file to load the bitmap, with a texture ID (i). 
      // We pass in our global texture array, the name of the texture, and an ID to reference it. 
      //CreateTexture(g_Texture, g_3DModel.pMaterials[i].strFile, i);  
      this -> g_Texture[i] = CTexture_make(this -> g_3DModel.pMaterials[i].strFile); 
      //g_Texture[i] = LoadTex("./herbe.jpg");//g_3DModel.pMaterials[i].strFile); 
    }; 
    
    // Set the texture ID for this material 
    this -> g_3DModel.pMaterials[i].texureId = i; // RL: As far as I am concerned, that looks useless. // RL: Indeed, materialID is directly used instead. 
  }; 
  //printf("   Récupération des textures du 3DS %s terminé !!\n", filename); 
  // Here, we turn on a lighting and enable lighting.  We don't need to 
  // set anything else for lighting because we will just take the defaults. 
  // We also want color, so we turn that on 
  
  
  // RL: Displaying. 
  { 
    //printf("Obj3DS[%s] - this -> g_3DModel.numOfObjects   = %d" "\n", filename, this -> g_3DModel.numOfObjects); 
    //printf("Obj3DS[%s] - this -> g_3DModel.numOfMaterials = %d" "\n", filename, this -> g_3DModel.numOfMaterials); 
#if 0
    for (int i = 0; i < this -> g_3DModel.numOfObjects; i++) { 
      // Free the faces, normals, vertices, and texture coordinates. 
      free(this -> g_3DModel.pObject[i].pFaces); 
      free(this -> g_3DModel.pObject[i].pNormals); 
      free(this -> g_3DModel.pObject[i].pVerts); 
      free(this -> g_3DModel.pObject[i].pTexVerts); 
    }; 
#endif 
  }; 
  
  
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  // RL: Generating an OpenGL DisplayList 
  this -> Liste = glGenLists(1);        // RL: Getting the list ID. // RL: '0' is an invalid display-list index. 
  glNewList(this -> Liste, GL_COMPILE); // RL: Start recording. 
  this -> RenderGL(this);               // RL: Recorded OpenGL operations. 
  glEndList();                          // RL: End recording. 
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  printf("<<< Objet 3DS chargé: '%s' " "\n", filename); 
  return true;  
}; 











void C3DS__RenderGL(const C3DS * this) {
  // I am going to attempt to explain what is going on below up here as not to clutter the 
  // code below.  We have a model that has a certain amount of objects and textures.  We want 
  // to go through each object in the model, bind it's texture map to it, then render it.
  // To render the current object, we go through all of it's faces (Polygons).  
  // What is a face you ask?  A face is just (in this case) a triangle of the object.
  // For instance, a cube has 12 faces because each side has 2 triangles.
  // You might be thinking.  Well, if there are 12 faces in a cube, that makes
  // 36 vertices that we needed to read in for that object.  Not really true.  Because
  // a lot of the vertices are the same, since they share sides, they only need to save
  // 8 vertices, and ignore the duplicates.  Then, you have an array of all the
  // unique vertices in that object.  No 2 vertices will be the same.  This cuts down
  // on memory.  Then, another array is saved, which is the index numbers for each face,
  // which index in to that array of vertices.  That might sound silly, but it is better
  // than saving tons of duplicate vertices.  The same thing happens for UV coordinates.
  // You don't save duplicate UV coordinates, you just save the unique ones, then an array
  // that index's into them.  This might be confusing, but most 3D files use this format.
  // This loop below will stay the same for most file formats that you load, so all you need
  // to change is the loading code.  You don't need to change this loop (Except for animation).
  
  // Since we know how many objects our model has, go through each of them.
  for (int i = 0; i < this -> g_3DModel.numOfObjects; i++) {
    // Make sure we have valid objects just in case. (size() is in the vector class)
    if (this -> g_3DModel.numOfObjects <= 0) break;
    
    // Get the current object that we are displaying
    const t3DObject * pObject = &this -> g_3DModel.pObject[i];
    
    // Check to see if this object has a texture map, if so bind the texture to it.
    if (pObject -> bHasTexture) {
      
      // Turn on texture mapping and turn off color
      glEnable(GL_TEXTURE_2D);
      
      // Bind the texture map to the object by it's materialID
      CTexture__GLTextureCourante(this -> g_Texture[pObject -> materialID]);
      // glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);
      
    } else {
      // Turn off texture mapping and turn on color
      //glDisable(GL_TEXTURE_2D);
    }; 
    
    
    // Reset the color to normal again
    glColor3ub(255, 255, 255);
    
    
    // This determines if we are in wireframe or normal mode
    // Begin drawing with our selected mode (triangles or lines)
    glBegin(GL_TRIANGLES); { 
      // Go through all of the faces (polygons) of the object and draw them
      for (int j = 0; j < pObject -> numOfFaces; j++) { 
        // Go through each corner of the triangle and draw it.
        for (int whichVertex = 0; whichVertex < 3; whichVertex++) {
          // Get the index for each point of the face
          int index = pObject -> pFaces[j].vertIndex[whichVertex];
	  
          // Give OpenGL the normal for this vertex.
          glNormal3f(pObject -> pNormals[index].x, pObject->pNormals[index].y, pObject->pNormals[index].z); 
	  
          // If the object has a texture associated with it, give it a texture coordinate. 
          if (pObject -> bHasTexture) { 
            // Make sure there was a UVW map applied to the object or else it won't have tex coords. 
            if (pObject -> pTexVerts) { 
              glTexCoord2f(pObject -> pTexVerts[index].x, pObject->pTexVerts[index].y); 
            }; 
          } else { 
            // Make sure there is a valid material/color assigned to this object.
            // You should always at least assign a material color to an object, 
            // but just in case we want to check the size of the material list.
            // if the size is at least one, and the material ID != -1,
            // then we have a valid material.
            //if (g_3DModel.pMaterials.size() && pObject->materialID >= 0) {
            if (this -> g_3DModel.numOfMaterials > 0 && pObject -> materialID >= 0) {
              // Get and set the color that the object is, since it must not have a texture 
              const BYTE * pColor = this -> g_3DModel.pMaterials[pObject -> materialID].color; 
              
              // Assign the current color to this model 
              glColor3ub(pColor[0], pColor[1], pColor[2]); 
            }; 
          }; 
          
          // Pass in the current vertex of the object (Corner of current face) 
          glVertex3f(pObject -> pVerts[index].x, pObject -> pVerts[index].y, pObject -> pVerts[index].z);
        }; 
      }; 
    
    } glEnd(); 
    // End the drawing 
  }; 
  
};





static void C3DS__Render(const C3DS * this) { 
  glCallList(this -> Liste); 
}; 



static void C3DS__delete(C3DS * this) { 
  obj3ds_dico__release(this -> dico_i); 
}; 

static void C3DS__delete_hard(C3DS * this) { 
  if (this == NULL) { return; }; 

  glDeleteLists(this -> Liste, 1); 


  for (int i = 0; i < MAX_TEXTURES; i++) { 
    if (this -> g_Texture[i] != NULL) { 
      CTexture_delete(this -> g_Texture[i]); 
      this -> g_Texture[i] = NULL; 
    }; 
  }; 
  
  // Go through all the objects in the scene 
  for (int i = 0; i < this -> g_3DModel.numOfObjects; i++) { 
    // Free the faces, normals, vertices, and texture coordinates. 
    free(this -> g_3DModel.pObject[i].pFaces); 
    free(this -> g_3DModel.pObject[i].pNormals); 
    free(this -> g_3DModel.pObject[i].pVerts); 
    free(this -> g_3DModel.pObject[i].pTexVerts); 
  }; 
  
  BZERO_THIS(this); 
  free(this); 
}; 


static C3DS * C3DS__copy(const C3DS * this) { 
  return obj3ds_dico__get(this -> dico_i); 
}; 

C3DS * C3DS__make(const char * filename) { 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  const int lookedup_index = obj3ds_dico__lookup(filename); 
  if (lookedup_index >= 0) { return obj3ds_dico__get(lookedup_index); }; 
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  MALLOC_BZERO(C3DS,this); 
  
  ASSIGN_METHOD(C3DS,this,make); 
  ASSIGN_METHOD(C3DS,this,copy); 
  ASSIGN_METHOD(C3DS,this,delete); 
  ASSIGN_METHOD(C3DS,this,Render); 
  ASSIGN_METHOD(C3DS,this,RenderGL); 
  //ASSIGN_METHOD(C3DS,this,CalcPE); 
  
  this -> filename = strcopy(filename); 
  
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //char realfile[strlen(T3DSDIR) + strlen(filename) + 1]; 
  enum { realfile__bytesize = 1<<10 }; 
  const size_t realfile__cstrlen = strlen(T3DSDIR) + strlen(filename); 
  assert(realfile__bytesize > realfile__cstrlen); 
  char realfile[realfile__bytesize]; 
  strcat(strcpy(realfile, T3DSDIR), filename); 
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  C3DS__load(this, realfile); 
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  
  this -> dico_i = obj3ds_dico__push(filename, this); 
  
  //printf("{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "---" "\n", __func__); 
  return this; 
}; 






















#if 0 
C3DS * C3DS_copy__broken(const C3DS * src) {
  MALLOC_BZERO(C3DS,this);
  
  *this = *src; 

  for (int i = 0; i < MAX_TEXTURES; i++) { 
    if (NULL == src -> g_Texture[i]) continue; 
    this -> g_Texture[i] = CTexture_copy(src -> g_Texture[i]);
  };

  for (int i = 0; i < this -> g_3DModel.numOfObjects; i++) {
    // Free the faces, normals, vertices, and texture coordinates.
    free(this -> g_3DModel.pObject[i].pFaces);
    free(this -> g_3DModel.pObject[i].pNormals);
    free(this -> g_3DModel.pObject[i].pVerts);
    free(this -> g_3DModel.pObject[i].pTexVerts);
  }
  
  return this; 
}; 

C3DS * C3DS_copy(const C3DS * src) {
  return C3DS_make(src -> filename); 
}; 

C3DS * C3DS_make(const char * filename) {
  MALLOC_BZERO(C3DS,this);
  
  ASSIGN_METHOD(C3DS,this,Render); 
  ASSIGN_METHOD(C3DS,this,RenderGL); 
  //ASSIGN_METHOD(C3DS,this,CalcPE); 

  this -> filename = strcopy(filename); 
  
  char reelfile[strlen(T3DSDIR) + strlen(filename) + 1];
  strcat(strcpy(reelfile, T3DSDIR), filename);
  filename = reelfile;
  bool b3dModelLoaded;
  
  //printf("Importation du fichier 3DS %s...\n", filename);  
    
  this -> g_ViewMode = GL_TRIANGLES; 
  for (int i = 0; i < MAX_TEXTURES; i++) 
    this -> g_Texture[i] = NULL;
          
  CLoad3DS_make_aux(&this -> g_Load3ds);

  // First we need to actually load the .3DS file.  
  // We just pass in an address to our t3DModel structure and the file name string we want to load ("face.3ds"). 
  printf("   Début de la lecture du fichier 3DS '%s' ... !!\n", filename);
  b3dModelLoaded = this -> g_Load3ds.Import3DS(&this -> g_Load3ds, &this -> g_3DModel, filename);         // Load our .3DS file into our model structure
  if (b3dModelLoaded) {
    printf("   Lecture du fichier 3DS '%s' terminée !!\n", filename);
    fflush(NULL);
  }
  else {
    printf("Impossible de charger le fichier 3DS '%s' ; soit le fichier n'existe pas, soit il est corrompu.", filename);
    fflush(NULL);
    return this;
  };
  // Depending on how many textures we found, load each one (Assuming .BMP)
  // If you want to load other files than bitmaps, you will need to adjust CreateTexture().
  // Below, we go through all of the materials and check if they have a texture map to load.
  // Otherwise, the material just holds the color information and we don't need to load a texture.

  // Go through all the materials
  for (int i = 0; i < this -> g_3DModel.numOfMaterials; i++) {
    // Check to see if there is a file name to load in this material
    if (strlen(this -> g_3DModel.pMaterials[i].strFile) > 0) {   
      printf("   Ahh le fichier 3DS référence la texture %s !!\n", this -> g_3DModel.pMaterials[i].strFile); 
      // Use the name of the texture file to load the bitmap, with a texture ID (i).
      // We pass in our global texture array, the name of the texture, and an ID to reference it. 
      //CreateTexture(g_Texture, g_3DModel.pMaterials[i].strFile, i);  
      this -> g_Texture[i] = CTexture_make(this -> g_3DModel.pMaterials[i].strFile);         
      //g_Texture[i] = LoadTex("./herbe.jpg");//g_3DModel.pMaterials[i].strFile);
    };
    
    // Set the texture ID for this material
    this -> g_3DModel.pMaterials[i].texureId = i;
  };
  printf("   Récupération des textures du 3DS %s terminé !!\n", filename); 
  // Here, we turn on a lighting and enable lighting.  We don't need to
  // set anything else for lighting because we will just take the defaults.
  // We also want color, so we turn that on

  this -> Liste = glGenLists(1);
    
  glNewList(this -> Liste, GL_COMPILE);
  this -> RenderGL(this);
  glEndList();
    
  printf("   Objet 3DS '%s' entièrement terminé !!\n", filename);

  return this; 
}; 
























#endif 
