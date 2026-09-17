
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <_global.hpp>
#include <_struktur.hpp>
#include <_funktion.hpp>
#include <_text.hpp>
#include <_textbuffer.hpp>
#include <_datei.hpp>
#include <_bild.hpp>
#include <_grafikwin.hpp>

#include <_welt.hpp>
#include <_weltpolygon.hpp>
#include <_weltoptik.hpp>   
#include <_weltfigur.hpp>
#include <_weltmechanik.hpp>
#include <_weltkollision.hpp>
#include <_oxyd.hpp>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>



//I_Sound  *Soundkarte;

//typedef _vektor3<> T_Vector3<>;
//******************************************************************************************************************************************************************************************************
//                                                              H A U P T F U N K T I O N 
//******************************************************************************************************************************************************************************************************

  

int WINAPI WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int){
                                L=new _logbuch("_oxydlogbuch.txt");
                                S=new _win::_system(hi);
                                _oxydwelt*ow;
                                _win::_grafikopengl<>*gra;
                                I_Sound*sound;
                                           
                                
                                try {
                                  C_ConfigSection  *section;
                                  // Read Configuration
                                  GLog.Open(L"Sound.log");
                                  if(!GConfig.Read(L"Sound.ini")) throw "soundinitialisierung : GConfig.read() fehlgeschlagen";
                                  if(!(section = GConfig.Section(L"Sound"))) throw "soundinitialisierung : GConfig.getSection() fehlgeschlagen";
                                  if(!LoadPackageAndClass(sound, section, L"Driver")) throw "soundinitialisierung : LoadPackageWuithClass() fehlgeschlagen";
                                  sound->Init();
                                  L->schreiben("soundinit");
                                  
                                  
                                  RECT r;
                                  unsigned int wx,wy;
                                  SystemParametersInfo(SPI_GETWORKAREA,0,&r,0);
                                  wx=abs(r.right-r.left);
                                  wy=abs(r.top-r.bottom);
                                  gra= new _win::_grafikopengl<>(0,0,wx,wy+32);
                                  gra->aktivitaet(true);
                                  gra->loeschenseite();
                                  gra->umschaltenseite();                                  
                                  ow=new _oxydwelt(gra,sound);//braucht grafik um texturen und zeichensatz anzulegen
                                  ow->erzeugenszene8(gra);
                                }
                                catch(const char*c){
                                 L->schreiben("Fehler : ",c);
                                 return(-1);
                                }

                                catch(...)
                                {
                                 L->schreiben("sontiges Problem mit dem Oxydweltkonstruktor");
                                 return(-1);
                                }
  
  
   /*
  
  I_Stream  *stream = Soundkarte->CreateStream();
  C_File  file(L"musik/lied2.ogg", L"rb");
  std::vector<bcUInt8>  buffer;
  file.Read(buffer, file.Size());
  stream->Load(buffer);
  stream->SetVolume(0.4);
  stream->SetPitch(0.25);
  //Sound->PlayStream(stream);
  
  I_Sample  *sample = Soundkarte->CreateSample();
  file.Read(buffer, file.Size());
  sample->Load(buffer);
  sample->SetVolume(0.4);
  sample->SetPitch(0.5);
  
  
  file.Open(L"ton/raul.ogg",L"rb");
  I_Sample  *sample2 = Soundkarte->CreateSample();
  file.Read(buffer, file.Size());
  sample2->Load(buffer);
  sample2->SetVolume(0.4);
  sample2->SetPitch(1.0);
  
  
  Soundkarte->PlaySample(pool, sample, T_Vector3<>(), T_Vector3<>());
  Soundkarte->PlaySample(pool, sample2, T_Vector3<>(), T_Vector3<>());*/
  
                        

                                
                                ow->welt->initialisierenanimation();
                                while(ow->kb->escape()==false) {
                                 //Soundkarte->Update((z.system()-anfang)/1000);
                                 ow->animieren(gra,sound);
                                };
                                
                              /*L->schreiben("polygon = ",(int)sizeof(_polygon));
                                L->schreiben("vertex = ",(int)sizeof(_vertex));
                                L->schreiben("verbindervertexpoly = ",(int)sizeof(_verbindervertexpolygon));
                                L->schreiben("bildvektor = ",(int)sizeof(_bildvektor<double>));*/
                            
                                delete ow;
                                SAFE_RELEASE(sound);
                                delete S;
                                delete L;
                                return(0);
};