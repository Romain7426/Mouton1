#include "obj3ds.hpp"
#include "texture.hpp"


C3DS::C3DS(const char * filename) {
  char * reelfile;
  reelfile = new char[strlen(T3DSDIR) + strlen(filename) + 1];
  strcat(strcpy(reelfile, T3DSDIR), filename);
  filename = reelfile;
  bool b3dModelLoaded;

  printf("Importation du fichier 3DS %s...\n", filename);  
    
  g_ViewMode   = GL_TRIANGLES; 
  for (int i = 0; i<MAX_TEXTURES; i++)
    g_Texture[MAX_TEXTURES] = 0;
          

  // First we need to actually load the .3DS file.  
  // We just pass in an address to our t3DModel structure and the file name string we want to load ("face.3ds").
  printf("   Début de la lecture du fichier 3DS '%s' ... !!\n", filename);
  b3dModelLoaded = g_Load3ds.Import3DS(&g_3DModel, (char *)filename);         // Load our .3DS file into our model structure
  if (b3dModelLoaded) {
    printf("   Lecture du fichier 3DS '%s' terminée !!\n", filename);
    fflush(NULL);
  }
  else 
    {
      printf("Impossible de charger le fichier 3DS '%s' ; soit le fichier n'existe pas, soit il est corrompu.", filename);
      fflush(NULL);
      delete [] reelfile;
      return;
    }
  // Depending on how many textures we found, load each one (Assuming .BMP)
  // If you want to load other files than bitmaps, you will need to adjust CreateTexture().
  // Below, we go through all of the materials and check if they have a texture map to load.
  // Otherwise, the material just holds the color information and we don't need to load a texture.

  // Go through all the materials
  for (int i = 0; i < g_3DModel.numOfMaterials; i++)
    {
      // Check to see if there is a file name to load in this material
      if (strlen(g_3DModel.pMaterials[i].strFile) > 0)
        {   
          printf("   Ahh le fichier 3DS référence la texture %s !!\n", g_3DModel.pMaterials[i].strFile); 
          // Use the name of the texture file to load the bitmap, with a texture ID (i).
          // We pass in our global texture array, the name of the texture, and an ID to reference it. 
          //CreateTexture(g_Texture, g_3DModel.pMaterials[i].strFile, i);  
          g_Texture[i] = new CTexture(g_3DModel.pMaterials[i].strFile);         
          //g_Texture[i] = LoadTex("./herbe.jpg");//g_3DModel.pMaterials[i].strFile);
        }
        
      // Set the texture ID for this material
      g_3DModel.pMaterials[i].texureId = i;
    }
  printf("   Récupération des textures du 3DS %s terminé !!\n", filename); 
  // Here, we turn on a lighting and enable lighting.  We don't need to
  // set anything else for lighting because we will just take the defaults.
  // We also want color, so we turn that on

  Liste = glGenLists(1);
    
  glNewList(Liste,GL_COMPILE);
  RenderGL();
  glEndList();
    
  printf("   Objet 3DS '%s' entièrement terminé !!\n", filename);
  
  
  delete [] reelfile;

}










void C3DS::RenderGL(void) {
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
  for (int i = 0; i < g_3DModel.numOfObjects; i++) {
    // Make sure we have valid objects just in case. (size() is in the vector class)
    if (g_3DModel.pObject.size() <= 0) break;

    // Get the current object that we are displaying
    t3DObject *pObject = &g_3DModel.pObject[i];
    
    // Check to see if this object has a texture map, if so bind the texture to it.
    if (pObject->bHasTexture) {
      
      // Turn on texture mapping and turn off color
      glEnable(GL_TEXTURE_2D);
      
      // Bind the texture map to the object by it's materialID
      g_Texture[pObject->materialID]->GLTextureCourante();
      // glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);

    } else {
      // Turn off texture mapping and turn on color
      //glDisable(GL_TEXTURE_2D);
    }

      
    // Reset the color to normal again
    glColor3ub(255, 255, 255);


    // This determines if we are in wireframe or normal mode
    // Begin drawing with our selected mode (triangles or lines)
    glBegin(GL_TRIANGLES); {
      // Go through all of the faces (polygons) of the object and draw them
      for (int j = 0; j < pObject->numOfFaces; j++) {
        // Go through each corner of the triangle and draw it.
        for (int whichVertex = 0; whichVertex < 3; whichVertex++) {
          // Get the index for each point of the face
          int index = pObject->pFaces[j].vertIndex[whichVertex];
        
          // Give OpenGL the normal for this vertex.
          glNormal3f(pObject->pNormals[index].x, pObject->pNormals[index].y, pObject->pNormals[index].z);
        
          // If the object has a texture associated with it, give it a texture coordinate.
          if (pObject->bHasTexture) {
            // Make sure there was a UVW map applied to the object or else it won't have tex coords.
            if (pObject->pTexVerts) {
              glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
            }
          } else {
            // Make sure there is a valid material/color assigned to this object.
            // You should always at least assign a material color to an object, 
            // but just in case we want to check the size of the material list.
            // if the size is at least one, and the material ID != -1,
            // then we have a valid material.
            if (g_3DModel.pMaterials.size() && pObject->materialID >= 0) {
              // Get and set the color that the object is, since it must not have a texture
              BYTE *pColor = g_3DModel.pMaterials[pObject->materialID].color;
              
              // Assign the current color to this model
              glColor3ub(pColor[0], pColor[1], pColor[2]);
            }
          }
          
          // Pass in the current vertex of the object (Corner of current face)
          glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
        }
      }
    
    } glEnd();
    // End the drawing
  }

}





void C3DS::Render(void) const {
  glCallList(Liste);
}



C3DS::~C3DS(void) {
  for (int i = 0; i < MAX_TEXTURES; i++)
    if (g_Texture[i] != NULL) {
      delete g_Texture[i];
      g_Texture[i] = NULL;
    }

  // Go through all the objects in the scene
  for (int i = 0; i < g_3DModel.numOfObjects; i++) {
    // Free the faces, normals, vertices, and texture coordinates.
    delete [] g_3DModel.pObject[i].pFaces;
    delete [] g_3DModel.pObject[i].pNormals;
    delete [] g_3DModel.pObject[i].pVerts;
    delete [] g_3DModel.pObject[i].pTexVerts;
  }
}

