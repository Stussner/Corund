void _welt::zeichnen(_grafik<char,_tg,_to>*gra,_kamera<_tg>*kam){
                                                                _netz*mit;
                                                                _partition::_zone*zit;
                                                                _partition::_sektor*sit;
                                                                _listenknoten<_polygon>*lnpit;
                                                                _polygon*pit;
                                                                _weltdebug*dit;
                                                                _licht<_tg,_to>*lit;
                                                                _vektor4<_to> fh(0,0,0,0.5);
                                                                unsigned int is;
                                                                GLfloat lp[4];
                                                                GLfloat lc[4];
                                                                GLfloat lv[4];
                                                                _vertex*vit0; 
                                                                _vertex*vit1; 
                                                                _vertex*vit2; 
                                                                _vertex*vit3; 
                                                                _vertex*vn; 
                                                                _verbindervertexpolygon*pvcp; 
                                                                _verbindervertexpolygon*vcp0; 
                                                                _verbindervertexpolygon*vcp1;                                                                 
                                                                //-------------------------
                                                                //glClearStencil(0);
                                                                gra->tiefenbuffertesten(true);
                                                                //gra->stencil(false);
                                                                //--------------------------------------- lichtquellen laden -----------------------------------
                                                                is=0;
                                                                if(anfang(lit))do{
                                                                 glEnable(GL_LIGHT0+(GLenum)is);
                                                                 lp[0]=lit->ort()[0];
                                                                 lp[1]=lit->ort()[1];
                                                                 lp[2]=lit->ort()[2];
                                                                 lp[3]=1;
                                                                 glLightfv(GL_LIGHT0+(GLenum)is,GL_POSITION,lp);
                                                                 lc[0]=lit->farbe()[0]*0.2f;
                                                                 lc[1]=lit->farbe()[1]*0.2f;
                                                                 lc[2]=lit->farbe()[2]*0.2f;
                                                                 lc[3]=1;
                                                                 glLightfv(GL_LIGHT0+(GLenum)is,GL_DIFFUSE,lc);
                                                                 glLightf(GL_LIGHT0+(GLenum)is,GL_SPOT_CUTOFF,(GLfloat)120.0f);
                                                                 glLightf(GL_LIGHT0+(GLenum)is,GL_CONSTANT_ATTENUATION,(GLfloat)0.1f);
                                                                 glLightf(GL_LIGHT0+(GLenum)is,GL_LINEAR_ATTENUATION,(GLfloat)0.0f);
                                                                 glLightf(GL_LIGHT0+(GLenum)is,GL_QUADRATIC_ATTENUATION,(GLfloat)0.0001f);
                                                                 lv[0]=0;
                                                                 lv[1]=-0.7;
                                                                 lv[2]=-0.7;
                                                                 lv[3]=1;
                                                                 glLightfv(GL_LIGHT0+(GLenum)is,GL_SPOT_DIRECTION,lv);
                                                                 lc[0]=lit->farbe()[0]*0.8f;
                                                                 lc[1]=lit->farbe()[1]*0.8f;
                                                                 lc[2]=lit->farbe()[2]*0.8f;
                                                                 lc[3]=1;
                                                                 glLightfv(GL_LIGHT0+(GLenum)is,GL_SPECULAR,lc);
                                                                 glLightf(GL_LIGHT0+(GLenum)is,GL_SPOT_EXPONENT,(GLfloat)2.0f);
                                                                 lc[0]=0.5;
                                                                 lc[1]=0.5;
                                                                 lc[2]=0.5;
                                                                 lc[3]=0;
                                                                 glMaterialfv(GL_FRONT,GL_SPECULAR,lc);
                                                                 glMaterialf(GL_FRONT,GL_SHININESS,(GLfloat)2.0f);
                                                                 lc[0]=0.0;
                                                                 lc[1]=0;
                                                                 lc[2]=0;
                                                                 lc[3]=0.5;
                                                                 glMaterialfv(GL_FRONT,GL_EMISSION,lc);
                                                                 glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,(GLfloat)1.0f);
                                                                 glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
                                                                 is++;
                                                                }while(naechstes(lit));


                                                                //--------------------------------------- SCHATTENBILD -------------------------------------
                                                                int windowWidth=gra->groessex(), windowHeight=gra->groessey();
                                                                MATRIX4X4 lightProjectionMatrix;
                                                                MATRIX4X4 lightViewMatrix;
                                                                MATRIX4X4 cameraProjectionMatrix;
                                                                MATRIX4X4 cameraViewMatrix;
                                                                //Load identity modelview
                                                                glMatrixMode(GL_MODELVIEW);
                                                                glLoadIdentity();
                                                                //Shading states
                                                                glShadeModel(GL_SMOOTH);
                                                                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                                                                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                                                                glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
                                                                //Depth states
                                                                glClearDepth(1.0f);
                                                                glDepthFunc(GL_LEQUAL);
                                                                glEnable(GL_DEPTH_TEST);
                                                             //   glEnable(GL_CULL_FACE);
//We use glScale when drawing the scene
glEnable(GL_NORMALIZE);


                                                                
                                                                
                                                                
                                                                if(anfang(lit)){ 
                                                                 //Calculate & save matrices
                                                                 glPushMatrix();
                                                                 
                                                                 //glMatrixMode(GL_PROJECTION);  
                                                                 glLoadIdentity();  
                                                                 gluPerspective(45.0f, (float)windowWidth/windowHeight, 1.0f, 1000.0f);
                                                                 glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
                                                                 
                                                                 glLoadIdentity();
                                                                 _vektor3<_tg> f=kam->ort()+kam->vektor();
                                                                 _vektor3<_tg> u=kam->ebenenormalisiert(1);
                                                                 gluLookAt(
                                                                 kam->ort()[0], kam->ort()[1], kam->ort()[2],
                                                                 f[0],f[1],f[2],
                                                                 u[0],u[1],u[2]);
                                                                 glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);
                                                                 /*
                                                                 
                                                                 
                                                                 
                                                                glMatrixMode(GL_MODELVIEW);  
                                                                glLoadIdentity();  
                                                                GLfloat m[4][4];
                                                                _vektor3<_tg> v=kam->vektor();
                                                                _vektor3<_tg> a=kam->ebenenormalisiert(0);
                                                                _vektor3<_tg> b=kam->ebenenormalisiert(1);
                                                                v.normalisieren();
                                                                a.normalisieren();
                                                                b.normalisieren();
                                                                m[0][0]=a[0];
                                                                m[1][0]=a[1];
                                                                m[2][0]=a[2];
                                                                m[3][0]=0;
                                                                m[0][1]=b[0];
                                                                m[1][1]=b[1];
                                                                m[2][1]=b[2];
                                                                m[3][1]=0;
                                                                m[0][2]=-v[0];
                                                                m[1][2]=-v[1];
                                                                m[2][2]=-v[2];
                                                                m[3][2]=0;
                                                                m[0][3]=0;
                                                                m[1][3]=0;
                                                                m[2][3]=0;
                                                                m[3][3]=1;
                                                                glLoadMatrixf((GLfloat*)m);
                                                                glTranslatef((_to)-kam->holen(0),(_to)-kam->holen(1),(_to)-kam->holen(2));                                                                  
                                                                 */
                                                                 
                                                                 
                                                                 
                                                                 glLoadIdentity();
                                                                 gluPerspective(45.0f, 1.0f, 1.0f, 2000.0f);
                                                                 glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);
                                                                 glLoadIdentity();
                                                                 gluLookAt( lit->ort()[0], lit->ort()[1], lit->ort()[2],
                                                                 0.0f, 0.0f, 0.0f,
                                                                 0.0f, 1.0f, 0.0f);
                                                                 glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);
                                                                 glPopMatrix();   
                                                                                                                
                                                                 
                                                                 
                                                                 //First pass - from light's point of view
                                                                 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                                 glMatrixMode(GL_PROJECTION);
                                                                 glLoadMatrixf(lightProjectionMatrix);
                                                                 glMatrixMode(GL_MODELVIEW);
                                                                 glLoadMatrixf(lightViewMatrix);
                                                                 //Use viewport the same size as the shadow map
                                                                 glViewport(0, 0, 512, 512);
                                                                 //Draw back faces into the shadow map
                                                                // glCullFace(GL_FRONT);
                                                                 //Disable color writes, and use flat shading for speed
                                                                 glShadeModel(GL_FLAT);
                                                                 glColorMask(0, 0, 0, 0);   
                                                                 if(anfang(mit))do{
                                                                  if(mit->anfang(pit))do{
                                                                   pit->zeichnen(gra);
                                                                  }while(mit->naechstes(pit));
                                                                 }while(naechstes(mit));                                            
                                                                 //Read the depth buffer into the shadow map texture
                                                                 glBindTexture(GL_TEXTURE_2D, gra->schattenbild);
                                                                 glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 512, 512);            
                                                                 //restore states
                                                                 glCullFace(GL_BACK);
                                                                 glShadeModel(GL_SMOOTH);
                                                                 glColorMask(1, 1, 1, 1);                                                                 
                                                               //  glViewport(0, 0, windowWidth, windowHeight);
                                                                //  gluPerspective(45.0f,(float)windowWidth/windowHeight,1.0f,2000.0f);
                                                                // gluPerspective(45.0f, (float)windowWidth/windowHeight, 1.0f, 2000.0f);
                                                              //   glPopMatrix();   
                                                                 
                                                                
   

                                                                 //2nd pass - Draw from camera's point of view
                                                                 //szene dunkel zeichnen
                                                                 glDisable(GL_LIGHTING);
                                                                 glClear(GL_DEPTH_BUFFER_BIT);
                                                                 glMatrixMode(GL_PROJECTION);
                                                                 glLoadMatrixf(cameraProjectionMatrix);
                                                                 glMatrixMode(GL_MODELVIEW);
                                                                 glLoadMatrixf(cameraViewMatrix);                                                                 
                                                                 glViewport(0, 0, windowWidth, windowHeight);
                                                                 if(anfang(mit))do{
                                                                  if(mit->anfang(pit))do{
                                                                   pit->zeichnen(gra);
                                                                  }while(mit->naechstes(pit));
                                                                 }while(naechstes(mit));
                                                                
                                                                
                                                                
                                                                 //3rd pass
                                                                 //Draw with bright light    
                                                                 //szene nochmal zeichnen mit der aktuellen Lichquelle 
                                                                 //Calculate texture matrix for projection
                                                                 //This matrix takes us from eye space to the light's clip space
                                                                 //It is postmultiplied by the inverse of the current view matrix when specifying texgen
                                                                 glEnable(GL_LIGHTING);   
                                                                 glEnable(GL_LIGHT0);
                                                                 lp[0]=lit->ort()[0];
                                                                 lp[1]=lit->ort()[1];
                                                                 lp[2]=lit->ort()[2];
                                                                 lp[3]=1;
                                                                 glLightfv(GL_LIGHT0,GL_POSITION,lp);
                                                                 static MATRIX4X4 biasMatrix(
                                                                 0.5f, 0.0f, 0.0f, 0.0f,
                                                                 0.0f, 0.5f, 0.0f, 0.0f,
                                                                 0.0f, 0.0f, 0.5f, 0.0f,
                                                                 0.5f, 0.5f, 0.5f, 1.0f); //bias from [-1, 1] to [0, 1]
                                                                 MATRIX4X4 textureMatrix=biasMatrix*lightProjectionMatrix*lightViewMatrix;
                                                                 //Set up texture coordinate generation.
                                                                 glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
                                                                 glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
                                                                 glEnable(GL_TEXTURE_GEN_S);
                                                                 glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
                                                                 glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
                                                                 glEnable(GL_TEXTURE_GEN_T);
                                                                 glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
                                                                 glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
                                                                 glEnable(GL_TEXTURE_GEN_R);
                                                                 glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
                                                                 glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
                                                                 glEnable(GL_TEXTURE_GEN_Q);                            
                                                                 //Bind & enable shadow map texture
                                                                 glBindTexture(GL_TEXTURE_2D, gra->schattenbild);
                                                                 glEnable(GL_TEXTURE_2D);
                                                                 //Enable shadow comparison
                                                                 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);
                                                                 //Shadow comparison should be true (ie not in shadow) if r<=texture
                                                                 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
                                                                 //Shadow comparison should generate an INTENSITY result
                                                                 glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);                                                                                                     
                                                                 //Set alpha test to discard false comparisons
                                                                 glAlphaFunc(GL_GEQUAL, 0.99f);
                                                                 glEnable(GL_ALPHA_TEST);
                                                                
                                                                
                                                                
                                                                 glEnable(GL_BLEND);
                                                                 glBlendFunc(GL_ONE,GL_ONE);
                                                                 glDepthFunc(GL_EQUAL);
                                                                 glEnable(GL_DEPTH_TEST);
                                                                 
                                                                 //zeichnen
                                                                 fh.setzen(1,1,1,0.2);
                                                                 if(anfang(mit))do{
                                                                  if(mit->anfang(pit))do{
                                                                     //pit->zeichnen(gra);
                                                                     //-----------------piit->zeichnen(gra);----------------
                                                                     vit0=pit->vertex(); 
                                                                     vit0=vit0->naechstes(pit); 
                                                                     vit1=vit0->naechstes(pit); 
                                                                     pvcp=pit->vertex()->connector(pit); 
                                                                     vcp0=vit0->connector(pit); 
                                                                     vcp1=vit1->connector(pit); 
                                                                     do{
                                                                      gra->zeichnen( *pit->vertex(), *vit0, *vit1, fh,fh,fh);
                                                                      vit0=vit1;
                                                                      vcp0=vcp1;
                                                                      vit1=vit1->naechstes(pit); 
                                                                      vcp1=vit1->connector(pit); 
                                                                    }while(vit1!=pit->vertex());
                                                                   //-----------------------------------------------------                                                                    
                                                                  }while(mit->naechstes(pit));
                                                                 }while(naechstes(mit));
                                                                 //Disable textures and texgen
                                                                 glDisable(GL_TEXTURE_GEN_S);
                                                                 glDisable(GL_TEXTURE_GEN_T);
                                                                 glDisable(GL_TEXTURE_GEN_R);
                                                                 glDisable(GL_TEXTURE_GEN_Q);
                                                                 //Restore other states
                                                                 glDisable(GL_LIGHTING);
                                                                 glDisable(GL_ALPHA_TEST);      
                                                                 glDepthFunc(GL_LEQUAL);
                                                                 glEnable(GL_DEPTH_TEST);
                                                                };//while(naechstes(lit));
                                                                
                                                                
                                                                
                                                                
                                                                if(anfang(dit))do{
                                                                 dit->zeichnen(gra);
                                                                }while(naechstes(dit));
                                                                zeichnensprite(gra,kam);
