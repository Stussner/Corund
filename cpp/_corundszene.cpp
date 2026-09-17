//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundszene.cpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include "../hpp/_corund.hpp"
#include <_weltfeld.hpp>
void _corundwelt::erzeugenszene0(_grafik*gra){
                                _vektor3<_tg> h;
                                _vektor3<_to> c;

                                _polygon*pit;
                                _geometriequader*gb;

                                 _vektor3<_tg> ort;
                                 _gravitation<_tg>*grav;
                               
                                //---------------------------------------- gravitation -----------------------------------------
                                grav=new _gravitation<_tg>(welt,_vektor3<_tg>(0,-0.05,0),1);
                                //grav->rotation(_vektor3<_tg>(5,5,4),_vektor3<_tg>(0,0,-8),4);
                                //grav->rotation(_vektor3<_tg>(5,0,-4),_vektor3<_tg>(0,0,8),4);
                               // grav->homogen(true);
                             //   feld=new _feld<_tg>();
                              //   feld->divergenz(_vektor3<_tg>(5,5,5),0.05);
                                //-----------------------------------------skybox anlegen----------------------------------------
                                _netz*mg;
                                _tg w=1024;
                                h.setzen(-w/2,-w/2,-w/2);
                                gb=new _geometriequader(welt,h,_vektor3<_tg>(w,0,0),_vektor3<_tg>(0,w,0),_vektor3<_tg>(0,0,w),textur[17]);
                                gb->texturkoordinatenlaenge(1,1,1);
                                mg=gb->erzeugen();
                                delete gb;
                                mg->einhaengen(welt);
                                mg->subtraktiv(true);
                                mg->transparenzfaktor(0);
                                mg->transparenz(false);                                                                
                                mg->verwendentextur(true);
                                mg->dynamischschattierend(false);
                                mg->aufgehellt(true);
                                skybox=mg;
                                mg->anfang(pit);
                                pit=pit->naechstes();
                                pit->textur(textur[18]);
                                pit=pit->naechstes();
                                pit->textur(textur[19]);
                                pit=pit->naechstes();
                                pit->textur(textur[20]);
                                pit=pit->naechstes();
                                pit->textur(textur[21]);
                                pit=pit->naechstes();
                                pit->textur(textur[22]);
                                mg->farbeverbinder(_vektor4<_to>(1,1,1,1));
                                //-------------------------------------licht  ---------------------------------
                                _licht<_tg,_to>*lit;
                                h.setzen(-40.1,65.1,-40.3);
                                c.setzen(0.8,0.9,1);
                                lit=new _licht<>(welt,h,c,8);
                                lit->farbeglanz(_vektor3<_to>(0.5,0.5,0.1));
                                //-------------------------------------- corundwelt bauen-------------------------------------------
                            /*    new _corundsteincorund(this, 1,0,1,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 11,0,8,1,1,1,textur[23],1);
                                new _corundsteincorund(this, 2,0,3,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 2,0,9,1,1,1,textur[23],1);*/
                                paaranzahl=2;
                                //boden
                                erzeugennetz(_vektor3<_tg>(0,  0, 0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,11),1,textur[11]);
                                //new _corundsteinflak(this,3,0,3);
                                spieler=new _corundkugel(this,_vektor3<_tg>(12.5,0+0.30005,1.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
};
void _corundwelt::erzeugenszene1(_grafik*gra){
                                _vektor3<_tg> h;
                                _vektor3<_to> c;
                                _netz*m;
                                _polygon*pit;
                                _geometriequader*gb;

                                 _vektor3<_tg> ort;
                                 _gravitation<_tg>*grav;
                                //----------------
                                grav=new _gravitation<_tg>(welt,_vektor3<_tg>(0,-0.006,0),1);
                                //grav->homogen(true);
                                //-----------------------------------------zone anlegen----------------------------------------
                                _netz*mg;
                                _tg w=1024;
                                h.setzen(-w/2,-w/2,-w/2);
                                gb=new _geometriequader(welt,h,_vektor3<_tg>(w,0,0),_vektor3<_tg>(0,w,0),_vektor3<_tg>(0,0,w),textur[17]);
                                gb->texturkoordinatenlaenge(1,1,1);
                                mg=gb->erzeugen();
                                delete gb;
                                mg->einhaengen(welt);
                                mg->subtraktiv(true);
                                mg->transparenzfaktor(0);
                                mg->transparenz(false);                                                                
                                mg->verwendentextur(true);
                                mg->dynamischschattierend(false);
                                //-------------------------------------licht und übersetzung ---------------------------------
                                _licht<_tg,_to>*lit;
                                h.setzen(-140.1,65.1,140.3);
                                c.setzen(0.8,0.9,1);
                                lit=new _licht<>(welt,h,c,80);
                                lit->farbeglanz(_vektor3<_to>(0.1,0.1,0.1));
                                //-------------------------------sky box texturieren---------------------------------------
                                welt->anfang(m);  
                                skybox=m;
                                skybox->anfang(pit);
                                pit=pit->naechstes();
                                pit->textur(textur[18]);
                                pit=pit->naechstes();
                                pit->textur(textur[19]);
                                pit=pit->naechstes();
                                pit->textur(textur[20]);
                                pit=pit->naechstes();
                                pit->textur(textur[21]);
                                pit=pit->naechstes();
                                pit->textur(textur[22]);
                                m->farbeverbinder(_vektor4<_to>(1,1,1,1));
                                //-------------------------------------- corundwelt bauen-------------------------------------------
                                new _corundsteincorund(this, 1,0,1,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 11,0,8,1,1,1,textur[23],1);
                                new _corundsteincorund(this, 2,0,3,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 2,0,9,1,1,1,textur[23],1);
                                paaranzahl=2;
                                _netz*ns;
                                //boden
                                ns=erzeugennetz(_vektor3<_tg>(0,  0, 0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,11),1,textur[11]);
                                ns->anfang(pit);
                                new _corundstein(this,0,0,0 ,14,1,1,textur[0],false);
                                new _corundstein(this,0,0,10,14,1,1,textur[0],false);
                                new _corundstein(this,0,0,1,  1,1,9,textur[0],false);
                                new _corundstein(this,13,0,1,  1,1,9,textur[0],false);

                                new _corundstein(this,1,0,3,  1,1,1,textur[0],false);
                                new _corundstein(this,3,0,3,  3,1,1,textur[0],false);
                                new _corundstein(this,4,0,1,  1,1,1,textur[0],false);
                                new _corundstein(this,7,0,4,  3,1,1,textur[0],false);
                                new _corundstein(this,9,0,1,  1,1,3,textur[0],false);
                                new _corundstein(this,10,0,1, 2,1,1,textur[0],false);
                                new _corundstein(this,11,0,2, 1,1,3,textur[0],false);
                                new _corundstein(this,11,0,6, 2,1,1,textur[0],false);
                                new _corundstein(this,9,0,6,  1,1,1,textur[0],false);
                                new _corundstein(this,9,0,8,  1,1,2,textur[0],false);
                                new _corundstein(this,1,0,7,  4,1,1,textur[0],false);
                                new _corundstein(this,6,0,7,  2,1,1,textur[0],false);
                                new _corundstein(this,7,0,8,  1,1,2,textur[0],false);

                                new _corundsteinschieb(this,4,0,2,2,1,1,textur[2],0.04);
                                new _corundsteinschieb(this,2,0,4,3,1,1,textur[2],0.04);
                                new _corundsteinschieb(this,3,0,5,5,1,1,textur[2],0.04);
                                new _corundsteinschieb(this,11,0,5,1,1,1,textur[2],0.04);
                                
                               // new _weltdebugtext(welt,"Diese Karte wurde entworfen von Carmen Drescher",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                spieler=new _corundkugel(this,_vektor3<_tg>(12.5,0+0.30005,1.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
};
void _corundwelt::erzeugenszene2(_grafik*gra){
                                _vektor3<_tg> h;
                                _vektor3<_to> c;
                                _netz*m;
                                _polygon*pit;
                                _geometriequader*gb;


                                 _vektor3<_tg> ort;
                                 _gravitation<_tg>*grav;
                                //----------------
                                grav=new _gravitation<_tg>(welt,_vektor3<_tg>(0,-0.006,0),1);
                                //grav->homogen(true);
                                //-----------------------------------------zone anlegen----------------------------------------
                                _netz*mg;
                                _tg w=1024;
                                h.setzen(-w/2,-w/2,-w/2);
                                gb=new _geometriequader(welt,h,_vektor3<_tg>(w,0,0),_vektor3<_tg>(0,w,0),_vektor3<_tg>(0,0,w),textur[17]);
                                gb->texturkoordinatenlaenge(1,1,1);
                                mg=gb->erzeugen();
                                delete gb;
                                mg->einhaengen(welt);
                                mg->subtraktiv(true);
                                mg->transparenzfaktor(0);
                                mg->transparenz(false);                                                                
                                mg->verwendentextur(true);
                                mg->dynamischschattierend(false);
                                //-------------------------------------licht und übersetzung ---------------------------------
                                _licht<_tg,_to>*lit;
                                h.setzen(-40.1,65.1,40.3);
                                c.setzen(0.8,0.9,1);
                                lit=new _licht<>(welt,h,c,80);
                                lit->farbeglanz(_vektor3<_to>(0.1,0.1,0.1));
                                //-------------------------------sky box texturieren---------------------------------------
                                welt->anfang(m);  
                                skybox=m;
                                skybox->anfang(pit);
                                pit=pit->naechstes();
                                pit->textur(textur[18]);
                                pit=pit->naechstes();
                                pit->textur(textur[19]);
                                pit=pit->naechstes();
                                pit->textur(textur[20]);
                                pit=pit->naechstes();
                                pit->textur(textur[21]);
                                pit=pit->naechstes();
                                pit->textur(textur[22]);
                                m->farbeverbinder(_vektor4<_to>(1,1,1,1));
                                //-------------------------------------- corundwelt bauen-------------------------------------------
                                _netz*ns;
                                //boden
                                ns=erzeugennetz(_vektor3<_tg>(0,0,0),_vektor3<_tg>(20,0,0),_vektor3<_tg>(0,0,15),1,textur[11]);
                                ns->anfang(pit);
                                new _corundstein(this,0,0,0 ,20,1,1,textur[0],false);
                                new _corundstein(this,0,0,14,20,1,1,textur[0],false);
                                new _corundstein(this,0,0,1,  1,1,13,textur[0],false);
                                new _corundstein(this,19,0,1,  1,1,13,textur[0],false);
                                //U
                                new _corundstein(this,8,0,6,  1,1,3,textur[0],false);
                                new _corundstein(this,9,0,8,  2,1,1,textur[0],false);
                                new _corundstein(this,9,0,6,  2,1,1,textur[0],false);
                                 
                                new _corundstein(this,6,0,10,  3,1,1,textur[0],false);
                                new _corundstein(this,10,0,10, 1,1,1,textur[0],false);
                                new _corundstein(this,12,0,8,  1,1,3,textur[0],false);
                                new _corundstein(this,12,0,4,  1,1,3,textur[0],false);
                                new _corundstein(this,7,0,4,   2,1,1,textur[0],false);
                                new _corundstein(this,10,0,4,  2,1,1,textur[0],false);
                                 
                                new _corundstein(this,4,0,10,  1,1,3,textur[0],false);
                                new _corundstein(this,5,0,12,  4,1,1,textur[0],false);
                                new _corundstein(this,10,0,12, 1,1,1,textur[0],false);
                                new _corundstein(this,12,0,12, 3,1,1,textur[0],false);
                                new _corundstein(this,13,0,8,  1,1,1,textur[0],false);
                                new _corundstein(this,14,0,10, 1,1,2,textur[0],false);
                                new _corundstein(this,14,0,2,  1,1,7,textur[0],false);
                                new _corundstein(this,4,0,2,   10,1,1,textur[0],false);
                                new _corundstein(this,8,0,13,  1,1,1,textur[0],false);
                                new _corundstein(this,4,0,6,   1,1,3,textur[0],false);
                                new _corundstein(this,4,0,3,  1,1,2,textur[0],false);
                                new _corundstein(this,16,0,12,  1,1,2,textur[0],false);
                                new _corundstein(this,16,0,10,  3,1,1,textur[0],false);
                                new _corundstein(this,6,0,4,  1,1,1,textur[0],false);
                                new _corundstein(this,6,0,7,  1,1,3,textur[0],false);
                                new _corundstein(this,2,0,6,  2,1,1,textur[0],false);
                                new _corundstein(this,2,0,7,  1,1,2,textur[0],false);
                                new _corundstein(this,9,0,1,  1,1,1,textur[0],false);
                                new _corundstein(this,6,0,6,  1,1,1,textur[0],false);
                                /*new _corundstein(this,10,0,10,1,1,1,textur[0],false);
                                new _corundstein(this,6,0,9,  1,1,2,textur[0],false);
                                new _corundstein(this,7,0,10, 2,1,1,textur[0],false);
                                new _corundstein(this,12,0,12,3,1,1,textur[0],false);
                                new _corundstein(this,14,0,2, 1,1,6,textur[0],false);*/
                                //new _corundstein(this,,0,,  1,1,1,textur[0],false);
                                new _corundsteincorund(this, 2,0,12,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 1,0,7,1,1,1,textur[23],1);
                                new _corundsteincorund(this, 2,0,3,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 17,0,12,1,1,1,textur[23],1);
                                paaranzahl=2;
                                new _corundsteinschieb(this,3,0,9,2,1,1,textur[2],0.04);
                                new _corundsteinschieb(this,3,0,5,1,1,1,textur[2],0.04);
                                new _corundsteinschieb(this,5,0,5,1,1,1,textur[2],0.04);
                                new _corundsteinschieb(this,10,0,7,2,1,1,textur[2],0.04);
                                new _corundsteinschieb(this,9,0,10,1,1,2,textur[2],0.04);
                                new _corundsteinschieb(this,14,0,9,1,1,1,textur[2],0.04);
                                new _corundsteinboulder(this,15,0,1,1,1,1,0);
                                //new _weltdebugtext(welt,"Diese Karte wurde entworfen von Carmen Drescher",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                spieler=new _corundkugel(this,_vektor3<_tg>(9.5,0+0.30005,7.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
};
void _corundwelt::erzeugenszene3(_grafik*gra){
                                erzeugenumgebung0();
                                _netz*ns;
                                ns=erzeugennetz(_vektor3<_tg>(0,0,0),_vektor3<_tg>(20,0,0),_vektor3<_tg>(0,0,15),1,textur[11]);
                                
                                new _corundstein(this,0,0,0 ,20,1,1,textur[0],false);
                                new _corundstein(this,0,0,14,20,1,1,textur[0],false);
                                new _corundstein(this,0,0,1,  1,1,13,textur[0],false);
                                new _corundstein(this,19,0,1,  1,1,13,textur[0],false);
                                 
                                new _corundsteincorund(this, 2,0,12,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 9,1,5,1,1,1,textur[23],1);
                                new _corundsteincorund(this, 2,0,1,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 17,0,12,1,1,1,textur[23],1);                                
                                paaranzahl=2;

                                new _corundsteinelektrisch(this,6,0,13,1,1,1,+1);
                                new _corundsteinelektrisch(this,10,0,13,1,1,1,-1);
                                new _corundsteinerdung(this,9,0,13,1,1,1);
                                new _corundsteinimpuls(this,16,0,10,1,1,1);
                                new _corundsteinimpuls(this,15,0,10,1,1,1);
                                new _corundsteinimpuls(this,14,0,10,1,1,1);
                                new _corundsteinimpuls(this,13,0,10,1,1,1);
                                new _corundsteinimpuls(this,12,0,10,1,1,1);
                                new _corundsteinimpuls(this,11,0,10,1,1,1);
                                new _corundsteinimpuls(this,10,0,10,1,1,1);
                                new _corundsteinimpuls(this,9 ,0,10,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,10,1,1,1);
                                new _corundsteinimpuls(this,7 ,0,10,1,1,1);
                                new _corundsteinimpuls(this,6 ,0,10,1,1,1);
                                new _corundsteinimpuls(this,5 ,0,10,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,11,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,12,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,13,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,9,1,1,1);
                                 
                                new _corundsteinimpuls(this,8 ,0,8,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,7,1,1,1);
                                new _corundsteinimpuls(this,8 ,1,7,1,1,1);
                                new _corundsteinimpuls(this,8 ,1,6,1,1,1);
                                new _corundsteinimpuls(this,8 ,1,5,1,1,1);
                                new _corundsteinimpuls(this,8 ,1,4,1,1,1);
                                new _corundsteinimpuls(this,8 ,1,3,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,2,1,1,1);
                                new _corundsteinimpuls(this,8 ,1,2,1,1,1);
                                new _corundsteinimpuls(this,8 ,0,1,1,1,1);                              
                                new _corundsteinschieb(this,7 ,0,1,1,1,1,textur[41],0.04);
                                
                                new _corundsteinboulder(this,10,0,1,1,1,1,0);
                                new _corundsteinboulder(this,17,0,11,1,1,1,2);
                                new _corundsteinrotation(this,10,0,7,1,1,1,textur[68],0);
                                new _corundsteinrotation(this,1,0,6,1,1,1,textur[68],1);
                                new _corundsteinrotation(this,18,0,6,1,1,1,textur[68],0);
                                new _corundsteinrotation(this,17,0,1,1,1,1,textur[68],0);
                                new _corundsteinrotation(this,9,0,2,1,1,1,textur[68],0);
                                new _corundsteinrotation(this,11,0,3,1,1,1,textur[68],1);
                                new _corundsteinrotation(this,2,0,2,1,1,1,textur[68],1);
                                
                                new _weltdebugtext(welt,"Szene_03",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                spieler=new _corundkugel(this,_vektor3<_tg>(9.5,0+0.30005,7.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
                                ambientlicht.setzen(0.2,0.3,0.4,1);
};
void _corundwelt::erzeugenszene4(_grafik*gra){
                                erzeugenumgebung0();
                                _netz*ns;
                                ns=erzeugennetz(_vektor3<_tg>(0,0,0),_vektor3<_tg>(20,0,0),_vektor3<_tg>(0,0,15),1,textur[11]);
                                new _corundstein(this,0,0,0 ,20,1,1,textur[0],false);
                                new _corundstein(this,0,0,14,20,1,1,textur[0],false);
                                new _corundstein(this,0,0,1,  1,1,13,textur[0],false);
                                new _corundstein(this,19,0,1,  1,1,13,textur[0],false);
                                 
                                new _corundsteincorund(this, 2,0,12,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 1,0,9,1,1,1,textur[23],1);
                                new _corundsteincorund(this, 2,0,1,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 1,0,5,1,1,1,textur[23],1);                                
                                paaranzahl=2;
                                 
                                new _corundstein(this,1,0,7,  5,1,1,textur[0],false);
                                new _corundstein(this,1,0,3,  5,1,1,textur[0],false);
                                new _corundstein(this,1,0,11,  5,1,1,textur[0],false);

                                new _corundsteinimpuls(this,7,0,7,  1,1,1);
                                new _corundsteinimpuls(this,8,0,7,  1,1,1);
                                new _corundsteinimpuls(this,9,0,7,  1,1,1);
                                new _corundsteinimpuls(this,10,0,7,  1,1,1);
                                new _corundsteinschieb(this,12,0,7,  2,1,1,textur[41],0.05);
                                new _corundsteinschieb(this,10,0,9,  1,1,2,textur[41],0.05);
                                new _corundsteinschieb(this,10,0,4,  1,1,2,textur[41],0.05);
                                 
                                new _corundsteinimpuls(this,14,0,7,1,1,1);
                                new _corundsteinimpuls(this,10,0,3,1,1,1);
                                new _corundsteinimpuls(this,10,0,11,1,1,1);
                                 
                                new _corundsteinimpuls(this,6,0,3,1,1,1);
                                new _corundsteinimpuls(this,6,0,11,1,1,1);
                                new _corundsteinimpuls(this,6,1,3,1,1,1);
                                new _corundsteinimpuls(this,6,1,11,1,1,1);
                                new _corundsteinimpuls(this,6,2,3,1,1,1);
                                new _corundsteinimpuls(this,6,2,11,1,1,1);
                                new _corundsteinimpuls(this,7,2,3,1,1,1);
                                new _corundsteinimpuls(this,7,2,11,1,1,1);
                                new _corundsteinimpuls(this,8,2,3,1,1,1);
                                new _corundsteinimpuls(this,8,2,11,1,1,1);
                                new _corundsteinimpuls(this,8,2,4,1,1,1);
                                new _corundsteinimpuls(this,8,2,10,1,1,1);
                                new _corundsteinimpuls(this,8,2,5,1,1,1);
                                new _corundsteinimpuls(this,8,2,9,1,1,1);
                                new _corundsteinimpuls(this,8,2,6,1,1,1);
                                new _corundsteinimpuls(this,8,2,8,1,1,1);
                                new _corundsteinimpuls(this,8,2,7,1,1,1);
                                new _corundsteinimpuls(this,8,1,7,1,1,1);
                                
                                new _corundsteinschieb(this,6,0,4,1,1,6,textur[41],0.04);

                                new _corundstein(this,9,0,5,  1,1,2,textur[0],false);
                                new _corundstein(this,11,0,5,  1,1,2,textur[0],false);
                                new _corundstein(this,11,0,8,  1,1,2,textur[0],false);
                                new _corundstein(this,9,0,8,  1,1,2,textur[0],false);
                                new _corundstein(this,12,0,6,  1,1,1,textur[0],false);
                                new _corundstein(this,12,0,8,  1,1,1,textur[0],false);
                                new _corundstein(this,7,0,3,  3,1,1,textur[0],false);
                                new _corundstein(this,7,0,11,  3,1,1,textur[0],false);
                                new _corundstein(this,12,0,3,  3,1,1,textur[0],false);
                                new _corundstein(this,11,0,11,  4,1,1,textur[0],false);
                                new _corundstein(this,14,0,4,  1,1,3,textur[0],false);
                                new _corundstein(this,14,0,8,  1,1,3,textur[0],false);
                                new _weltdebugtext(welt,"Szene_04",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                spieler=new _corundkugel(this,_vektor3<_tg>(1.5,0+0.30005,1.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
                                ambientlicht.setzen(0.5,0.4,0.1,1);
};
void _corundwelt::erzeugenszene5(_grafik*gra){
                                erzeugenumgebung0();
                                _netz*ns;
                                ns=erzeugennetz(_vektor3<_tg>(-20,0,-15),_vektor3<_tg>(40,0,0),_vektor3<_tg>(0,0,32),1,textur[11]);
                                new _corundstein(this,-20,0,-15 ,40,1,1,textur[0],false);
                                new _corundstein(this,-20,0,16,40,1,1,textur[0],false);
                                new _corundstein(this,-20,0,-14,  1,1,30,textur[0],false);
                                new _corundstein(this,19,0,-14,  1,1,30,textur[0],false);
                                
                                new _corundsteincorund(this, 18,0, 12,1,1,1,textur[23],0);
                                new _corundsteincorund(this, -1,0,9  ,1,1,1,textur[23],1);
                                new _corundsteincorund(this, -2,0,1  ,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 18,0,-13,1,1,1,textur[23],1);                                
                                paaranzahl=2;
                                
                                new _corundsteinimpuls(this,3,0,0 ,1,1,1);
                                new _corundsteinimpuls(this,5,0,0 ,1,1,1);
                                new _corundsteinimpuls(this,7,0,0 ,1,1,1);
                                new _corundsteinimpuls(this,5,0,4 ,1,1,1);
                                new _corundsteinimpuls(this,7,0,4 ,1,1,1);
                                new _corundsteinimpuls(this,4,0,5 ,1,1,1);
                                new _corundsteinimpuls(this,8,0,5 ,1,1,1);
                                new _corundsteinimpuls(this,9,0,5 ,1,1,1);
                                new _corundsteinimpuls(this,4,0,7 ,1,1,1);
                                new _corundsteinimpuls(this,8,0,7 ,1,1,1);
                                new _corundsteinimpuls(this,3,0,6 ,1,1,1);
                                new _corundsteinimpuls(this,3,0,-1 ,1,1,1);
                                new _corundsteinimpuls(this,3,0,-2 ,1,1,1);
                                new _corundsteinimpuls(this,3,0,-3 ,1,1,1);
                                new _corundsteinimpuls(this,4,0,-3 ,1,1,1);
                                new _corundsteinimpuls(this,5,0,-3 ,1,1,1);
                                new _corundsteinimpuls(this,5,0,-2 ,1,1,1);
                                new _corundsteinimpuls(this,5,0,-1 ,1,1,1);
                                new _corundsteinimpuls(this,6,0,-3 ,1,1,1);
                                new _corundsteinimpuls(this,7,0,-3 ,1,1,1);
                                new _corundsteinimpuls(this,7,0,-2 ,1,1,1);
                                new _corundsteinimpuls(this,7,0,-1 ,1,1,1);

                                new _corundsteinimpuls(this,9,0,12 ,1,1,1);
                                new _corundsteinimpuls(this,9,1,12 ,1,1,1);
                                new _corundsteinimpuls(this,9,2,12 ,1,1,1);
                                 
                                new _corundsteinimpuls(this,10,2,12 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,11 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,10 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,9 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,8 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,7 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,6 ,1,1,1);
                                 
                                new _corundsteinimpuls(this,10,2,5 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,4 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,3 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,2 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,1 ,1,1,1);
                                new _corundsteinimpuls(this,10,2,0 ,1,1,1);
                                new _corundsteinimpuls(this, 9,2,0 ,1,1,1);
                                new _corundsteinimpuls(this, 8,2,0 ,1,1,1);
                                new _corundsteinimpuls(this, 7,2,0 ,1,1,1);
                                new _corundsteinimpuls(this, 7,1,0 ,1,1,1);
                                 
                                new _corundsteinbeschleunigung(this,-10,0,-10,1,1,1,0.1);
                                new _corundsteintotenkopf(this,-7,0,-10,1,1,1,0.1);
                                new _corundsteinelektrisch(this,-8,0,-10,1,1,1,1);
                                new _corundsteinelektrisch(this,-2,0,-10,1,1,1,-1);
                                new _corundsteinerdung(this,-15,0,13,1,1,1);
                                new _corundsteinkugelgen(this,-15,0,3,_vektor3<_tg>(0,0.2,0),0.3,0,1,_vektor4<_to>(0,0.4,0,1));
                                 
                                new _corundstein(this,-6,0,-5,  1,1,1,textur[0],false);
                                new _corundstein(this,-4,0,-5,  1,1,1,textur[0],false);
                                new _corundsteinschalter(this,-3,0,-5,  1,1,1,0,new _corundsteintor(this,-5,0,-5,1));

                                new _corundsteintor(this,-8,0,-5,0);
                                new _corundstein(this,-8,0,-4,  1,1,1,textur[0],false);
                                new _corundstein(this,-8,0,-6,  1,1,1,textur[0],false);
                                //new _corundsteinimpuls(this,1,0,0 ,1,1,1);
                                //new _corundsteinimpuls(this,2,0,0 ,1,1,1);
                                new _corundsteinboulder(this,9,0,8,1,1,1,2);
                                //new _corundsteinimpuls(this,1,0,10 ,1,1,1);
                                /*new _corundsteinimpuls(this,5,1,0 ,1,1,1);
                                new _corundsteinimpuls(this,5,2,0 ,1,1,1);
                                new _corundsteinimpuls(this,4,2,0 ,1,1,1);
                                new _corundsteinimpuls(this,4,2,1 ,1,1,1);
                                new _corundsteinimpuls(this,4,2,2 ,1,1,1);
                                new _corundsteinimpuls(this,4,2,3 ,1,1,1);
                                new _corundsteinimpuls(this,4,2,4 ,1,1,1);
                                new _corundsteinimpuls(this,4,2,5 ,1,1,1);
                                new _corundsteinimpuls(this,4,1,5 ,1,1,1);*/

                                new _corundsteinschieb(this,3,0,2 ,1,2,4,textur[41],0.05);
                                new _corundsteinschieb(this,5,0,2 ,1,2,2,textur[41],0.05);
                                new _corundsteinschieb(this,7,0,2 ,1,2,2,textur[41],0.05);
                                new _corundsteinschieb(this,5,0,5 ,2,2,1,textur[41],0.05);
                                new _corundsteinschieb(this,2,0,7 ,2,2,1,textur[41],0.05);
                                new _corundsteinschieb(this,6,0,7 ,2,2,1,textur[41],0.05);
                                 
                                new _corundstein(this,0,0,0,  3,1,1,textur[0],false);
                                new _corundstein(this,4,0,0,  1,1,1,textur[0],false);
                                new _corundstein(this,6,0,0,  1,1,1,textur[0],false);
                                new _corundstein(this,6,0,2,  1,1,1,textur[0],false);
                                new _corundstein(this,8,0,0,  3,1,1,textur[0],false);
                                new _corundstein(this,8,0,2,  11,1,1,textur[0],false);
                                new _corundstein(this,4,0,4,  1,1,1,textur[0],false);
                                new _corundstein(this,6,0,4,  1,1,1,textur[0],false);
                                new _corundstein(this,8,0,4,  3,1,1,textur[0],false);
                                
                                new _corundstein(this,2,0,4,  1,1,1,textur[0],false);
                                new _corundstein(this,2,0,6,  1,1,1,textur[0],false);
                                new _corundstein(this,4,0,6,  1,1,1,textur[0],false);
                                new _corundstein(this,6,0,6,  1,1,1,textur[0],false);
                                new _corundstein(this,8,0,6,  1,1,1,textur[0],false);
                                new _corundstein(this,4,0,8,  1,1,1,textur[0],false);
                                new _corundstein(this,8,0,8,  1,1,1,textur[0],false);
                                new _corundstein(this,10,0,5, 1,1,11,textur[0],false);
                                new _corundstein(this,10,0,-14, 1,1,14,textur[0],false);
                                _netz*nn0;
                                _netz*nn1;
                                _geometriequader*gq;
                                _modifikationnetzintersektion I;
                                gq=new _geometriequader(welt,_vektor3<_tg>(-1,0,2),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,4),textur[41]);
                                gq->texturkoordinatenlaenge(1,1,4);
                                nn0=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt,_vektor3<_tg>(-3,0,6),_vektor3<_tg>(3,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(3,1,1);
                                nn1=gq->erzeugen();
                                delete gq;
                                I.bearbeiten(nn0,nn1,2);
                                delete nn1;
                                nn0->verwendentexturdynamisch(true);
                                new _corundsteinschieb(this,nn0,0.06);
                                delete nn0;
                                new _weltdebugtext(welt,"Szene_05",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                spieler=new _corundkugel(this,_vektor3<_tg>(1.5,0+0.30005,1.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
                                new _corundkugel(this,_vektor3<_tg>(1.5,0+0.30005,-6),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                 ambientlicht.setzen(0.5,0.4,0.1,1);
};
void _corundwelt::erzeugenszene6(_grafik*gra){
                                erzeugenumgebung0();
                                _netz*ns;
                                ns=erzeugennetz(_vektor3<_tg>(-20,0,-15),_vektor3<_tg>(40,0,0),_vektor3<_tg>(0,0,32),1,textur[11]);
                                new _corundstein(this,-20,0,-15 ,40,1,1,textur[0],false);
                                new _corundstein(this,-20,0,16,40,1,1,textur[0],false);
                                new _corundstein(this,-20,0,-14,  1,1,30,textur[0],false);
                                new _corundstein(this,19,0,-14,  1,1,30,textur[0],false);
                                 
                                new _corundsteincorund(this, 18,0, 12,1,1,1,textur[23],0);
                                new _corundsteincorund(this, -1,0,9  ,1,1,1,textur[23],1);
                                new _corundsteincorund(this, -2,0,1  ,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 18,0,-13,1,1,1,textur[23],1);                                
                                paaranzahl=2;
                                 
                                new _corundsteinbeschleunigung(this,-10,0,-10,1,1,1,0.1);
                                new _corundsteintotenkopf(this,15,0,1,1,1,1,0.1);
                                new _corundsteinelektrisch(this,-8,0,-10,1,1,1,1);
                                new _corundsteinelektrisch(this,-2,0,-10,1,1,1,-1);
                                new _corundsteinerdung(this,-15,0,13,1,1,1);
                                new _corundsteinkugelgen(this,-15,0,3,_vektor3<_tg>(0,0.2,0),0.2,0,0,_vektor4<_to>(0,0.4,0,1));
                                new _corundstein(this,-14,0,-5,  1,1,1,textur[0],false);
                                new _corundstein(this,-12,0,-5,  1,1,1,textur[0],false);
                                _corundsteinschalter*oss=new _corundsteinschalter(this,-11,0,-5,  1,1,1,0,new _corundsteintor(this,-13,0,-5,1));
                                _corundsteintor*ost=new _corundsteintor(this,-8,0,-5,0);
                                oss->listeek.einhaengen(ost);
                                new _corundsteinschalter(this,-11,0,-7,  1,1,1,0,ost);
                                 
                                new _corundstein(this,-8,0,-4,  1,1,1,textur[0],false);
                                new _corundstein(this,-8,0,-6,  1,1,1,textur[0],false);
                                
                                new _weltdebugtext(welt,"Szene_06",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                //  kugeln erzeugen 
                                spieler=new _corundkugel(this,_vektor3<_tg>(5.5,3,2.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
                                _corundkugel*ok[3][7];
                                _tg wi=0;
                                _tg dw=360/6;
                                ok[0][0]=new _corundkugel(this,_vektor3<_tg>(3.5,0.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                //ok[0][1]=new _corundkugel(this,_vektor3<_tg>(7.5,0.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                //ok[0][2]=new _corundkugel(this,_vektor3<_tg>(7.5,0.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                //ok[0][3]=new _corundkugel(this,_vektor3<_tg>(3.5,0.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                /* ok[1][0]=new _corundkugel(this,_vektor3<_tg>(3.5,4.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[1][1]=new _corundkugel(this,_vektor3<_tg>(7.5,4.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[1][2]=new _corundkugel(this,_vektor3<_tg>(7.5,4.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[1][3]=new _corundkugel(this,_vektor3<_tg>(3.5,4.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                */
                                new _corundfeder(ok[0][0],new _corundstein(this,0,0,0,1,1,1,textur[0],false),0.1);
                                // new _corundfeder(ok[0][0],ok[0][1],1);                                
                                /* new _corundfeder(ok[0][0],ok[0][1],0.05);
                                new _corundfeder(ok[0][1],ok[0][2],0.05);
                                new _corundfeder(ok[0][2],ok[0][3],0.05);
                                new _corundfeder(ok[0][3],ok[0][0],0.05);*/
                                //   for(n=0;n<4;n++) new _corundfeder(spieler,ok[0][n],0.001);
                                /*   new _corundfeder(ok[1][0],ok[1][1],0.005);
                                new _corundfeder(ok[1][1],ok[1][2],0.005);
                                new _corundfeder(ok[1][2],ok[1][3],0.005);
                                new _corundfeder(ok[1][3],ok[1][0],0.005);*/
                                //for(n=0;n<4;n++) new _corundfeder(spieler,ok[1][n],0.001);
                                //for(n=0;n<4;n++) ok[0][n]->steuerung=true;
                                //for(n=0;n<4;n++) ok[1][n]->steuerung=true;
                                //for(n=0;n<4;n++) new _corundfeder(ok[0][n],ok[1][n],0.005);
                                /*
                                for(j=0;j<3;j++){
                                 for(n=0;n<6;n++){
                                  ok[j][n]=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*3,j*15+0.20005,sin(wi*_ph)*3),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                  ok[j][n]->ladung=0;
                                  //ok[j][n]->gravitation=-60;
                                  ok[j][n]->steuerung=true;
                                  wi+=dw;
                                 };
                                 for(n=0;n<6;n++){
                                  if(n==5) m=0; else m=n+1;
                                  // new _corundgummiband(ok[j][n],ok[j][m],0.007);
                                  // new _corundgummiband(spieler,ok[j][n],0.001+_tg(j)*0.001);
                                  new _corundfeder(ok[j][n],ok[j][m],0.005);
                                 };
                                };
                                for(n=0;n<6;n++){
                                 new _corundfeder(ok[0][n],ok[1][n],0.005);
                                };
                                for(n=0;n<6;n++){
                                 new _corundfeder(ok[1][n],ok[2][n],0.005);
                                 new _corundfeder(spieler,ok[1][n],0.005);
                                };
                                _corundkugel*ok0;
                                _corundkugel*ok1;
                                _corundkugel*ok2;
                                _corundkugel*ok3;
                                _corundkugel*ok4;
                                _corundkugel*ok5;
                                _corundkugel*ok6;
                                _corundkugel*ok7;
                                _tg wi=0;
                                _tg dw=360/5;
                                ok=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*2,0+0.20005,sin(wi*_ph)*2),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok->ladung=0;
                                ok->gravitation=-60;
                                wi+=dw;
                                ok0=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*2,0+0.20005,sin(wi*_ph)*2),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok0->ladung=0;
                                ok0->gravitation=-60;
                                wi+=dw;
                                ok1=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*2,0+0.20005,sin(wi*_ph)*2),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok1->ladung=0;
                                ok1->gravitation=-60;
                                wi+=dw;
                                ok2=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*2,0+0.20005,sin(wi*_ph)*2),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok2->ladung=0;
                                ok2->gravitation=-60;
                                wi+=dw;
                                ok3=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*2,0+0.20005,sin(wi*_ph)*2),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok3->ladung=0;
                                ok3->gravitation=-60;
                                wi+=dw;
                                ok4=new _corundkugel(this,_vektor3<_tg>(0,0+0.20005,0),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok4->ladung=0;
                                ok4->gravitation=-60;
                                wi=0;
                                dw=360/3;
                                
                                ok5=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*0.5,3,sin(wi*_ph)*0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok5->ladung=0;
                                ok5->gravitation=+0;
                                wi+=dw;
                                ok6=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*0.5,3,sin(wi*_ph)*0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok6->ladung=0;
                                ok6->gravitation=+0;
                                wi+=dw;
                                ok7=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*0.5,3,sin(wi*_ph)*0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok7->ladung=0;
                                ok7->gravitation=+0;
                                wi+=dw;
                                
                                ok->steuerung=true;
                                ok0->steuerung=true;
                                ok1->steuerung=true;
                                ok2->steuerung=true;
                                ok3->steuerung=true;
                                new _corundgummiband(spieler,ok ,0.002);
                                new _corundgummiband(spieler,ok0,0.002);
                                new _corundgummiband(spieler,ok1,0.002);
                                new _corundgummiband(spieler,ok2,0.002);
                                new _corundgummiband(spieler,ok3,0.002);

                                new _corundgummiband(ok,ok0, 0.007);
                                new _corundgummiband(ok0,ok1,0.007);
                                new _corundgummiband(ok1,ok2,0.007);
                                new _corundgummiband(ok2,ok3,0.007);
                                new _corundgummiband(ok3,ok ,0.007);
                                
                                new _corundgummiband(ok4,ok, 0.007);
                                new _corundgummiband(ok4,ok0, 0.007);
                                new _corundgummiband(ok4,ok1, 0.007);
                                new _corundgummiband(ok4,ok2, 0.007);
                                new _corundgummiband(ok4,ok3, 0.007);
                                
                                new _corundgummiband(spieler,ok5,0.002);
                                new _corundgummiband(spieler,ok6,0.002);
                                new _corundgummiband(spieler,ok7,0.002);
                                
                                new _corundgummiband(,ok6,0.002);
                                new _corundgummiband(spieler,ok7,0.002);
                                new _corundgummiband(spieler,ok5,0.002);
                                new _corundgummiband(spieler,ok6,0.002);
                                new _corundgummiband(spieler,ok7,0.002);
                                */
};
void _corundwelt::erzeugenszene7(_grafik*gra){
                                erzeugenumgebung0();
                                _netz*ns;
                                ns=erzeugennetz(_vektor3<_tg>(-20,0,-10),_vektor3<_tg>(40,0,0),_vektor3<_tg>(0,0,20),4,4,textur[26]);
                                 
                                new _corundstein(this,-20,0,-10 ,40,1,1,textur[0],false);
                                new _corundstein(this,-20,0,10,40,1,1,textur[0],false);
                                new _corundstein(this,-20,0,-10,  1,1,18,textur[0],false);
                                new _corundstein(this,19,0,-10,  1,1,18,textur[0],false);
                                 
                                new _corundsteincorund(this, 18,0, 12,1,1,1,textur[23],0);
                                new _corundsteincorund(this, -1,0,9  ,1,1,1,textur[23],1);
                                new _corundsteincorund(this, -2,0,1  ,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 18,0,-13,1,1,1,textur[23],1);                                
                                paaranzahl=2;
                                 
                                 
                                new _corundsteinbeschleunigung(this,-10,0,-10,1,1,1,0.1);
                                new _corundsteintotenkopf(this,15,0,1,1,1,1,0.1);
                                new _corundsteinelektrisch(this,-8,0,-10,1,1,1,1);
                                new _corundsteinelektrisch(this,-2,0,-10,1,1,1,-1);
                                new _corundsteinerdung(this,-15,0,13,1,1,1);
                                new _corundsteinkugelgen(this,-15,0,3,_vektor3<_tg>(0,0.2,0),0.2,0,0,_vektor4<_to>(0,0.4,0,1));
                                 
                                new _corundstein(this,-14,0,-5,  1,1,1,textur[0],false);
                                new _corundstein(this,-12,0,-5,  1,1,1,textur[0],false);
                                _corundsteinschalter*oss=new _corundsteinschalter(this,-11,0,-5,  1,1,1,0,new _corundsteintor(this,-13,0,-5,1));
                                _corundsteintor*ost=new _corundsteintor(this,-8,0,-5,0);
                                oss->listeek.einhaengen(ost);
                                new _corundsteinschalter(this,-11,0,-7,  1,1,1,0,ost);
                                 
                                new _corundstein(this,-8,0,-4,  1,1,1,textur[0],false);
                                new _corundstein(this,-8,0,-6,  1,1,1,textur[0],false);
                               
                                new _weltdebugtext(welt,"Szene_07",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                //  kugeln erzeugen 
                                spieler=new _corundkugel(this,_vektor3<_tg>(5.5,3,2.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
                                _corundkugel*ok[3][7];
                                _tg wi=0;
                                _tg dw=360/6;
                                
                                
                                ok[0][0]=new _corundkugel(this,_vektor3<_tg>(3.5,0.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[0][1]=new _corundkugel(this,_vektor3<_tg>(7.5,0.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[0][2]=new _corundkugel(this,_vektor3<_tg>(7.5,0.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[0][3]=new _corundkugel(this,_vektor3<_tg>(3.5,0.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));

                               /* ok[1][0]=new _corundkugel(this,_vektor3<_tg>(3.5,4.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[1][1]=new _corundkugel(this,_vektor3<_tg>(7.5,4.30005,0.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[1][2]=new _corundkugel(this,_vektor3<_tg>(7.5,4.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                ok[1][3]=new _corundkugel(this,_vektor3<_tg>(3.5,4.30005,4.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
*/
                            //    new _corundfeder(ok[0][0],new _corundstein(this,0,0,0,1,1,1,textur[0],false),0.1);
                               // new _corundfeder(ok[0][0],ok[0][1],1);                                
                                new _corundfeder(ok[0][0],ok[0][1],0.002);
                                new _corundfeder(ok[0][1],ok[0][2],0.002);
                                new _corundfeder(ok[0][2],ok[0][3],0.002);
                                new _corundfeder(ok[0][3],ok[0][0],0.002);
                             //  for(n=0;n<4;n++) new _corundfeder(spieler,ok[0][n],0.005);
                             /*   new _corundfeder(ok[1][0],ok[1][1],0.005);
                                new _corundfeder(ok[1][1],ok[1][2],0.005);
                                new _corundfeder(ok[1][2],ok[1][3],0.005);
                                new _corundfeder(ok[1][3],ok[1][0],0.005);*/
                            //   for(n=0;n<4;n++) new _corundfeder(spieler,ok[1][n],0.001);
                                //for(n=0;n<4;n++) ok[0][n]->steuerung=true;
                           //     for(n=0;n<4;n++) ok[1][n]->steuerung=true;
                                
                              //  for(n=0;n<4;n++) new _corundfeder(ok[0][n],ok[1][n],0.005);
                                
                              /*  for(j=0;j<2;j++){
                                 for(n=0;n<6;n++){
                                  ok[j][n]=new _corundkugel(this,_vektor3<_tg>(cos(wi*_ph)*3,j*5+0.20005,sin(wi*_ph)*3),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0.3,0.05,0,1));
                                  ok[j][n]->ladung=0;
                                  //ok[j][n]->gravitation=-60;
                                  ok[j][n]->steuerung=true;
                                  wi+=dw;
                                 };
                                
                                 for(n=0;n<6;n++){
                                  if(n==5) m=0; else m=n+1;
                                  // new _corundgummiband(ok[j][n],ok[j][m],0.007);
                                  // new _corundgummiband(spieler,ok[j][n],0.001+_tg(j)*0.001);
                                  new _corundfeder(ok[j][n],ok[j][m],0.001);
                                 };
                                };
                                 for(n=0;n<6;n++){
                                  new _corundfeder(ok[0][n],ok[1][n],0.001);
                                 };
                                 for(n=0;n<6;n++){
                                //  new _corundfeder(ok[1][n],ok[2][n],0.05);
                                 // new _corundfeder(spieler,ok[1][n],0.005);
                                 };
                                */
                                
                                
};
void _corundwelt::erzeugenszene8(_grafik*gra){
                                _partition::_zone*zit;
                                //_partition::_sektor*sit;
                                //_partition::_polygon*pit;
                                _corundstein*os;
                                //_liste<_licht<_tg,_to> > llist;
                                _corundlichtverwaltung ovl;
                                _tg x,z;
                                _licht<_tg,_to>*lit;
                                _licht<_tg,_to>*licht;
                                _licht<_tg,_to>*licht2;
                                _vektor3<_tg> h;
                                _vektor3<_to> c;
                                //_netz*nt0;
                                //_netz*nt1;
                                //_netz*nt2;
                                _netz*nit;
                                _netz*nt;
                                _gravitation<_tg>*grav;
                                //_liste<_netz >*rohmeshes;
                                _corundsteinschalter*oss[5];
                                _corundsteintor*tor[5];
                                _netz*tornetz;
                                _liste<_netz> tornetze;
                                _geometriequader*gn;
                                _geometriequader*gqt;
                                _modifikationnetzintersektion I;
                                _polygon*poly;
                                _netz*netz;
                                //---------------------------------------------------------------------------------------------------------------------------------
                               

                                
                                grav=new _gravitation<_tg>(welt,_vektor3<_tg>(0,-0.02,0),1);
                                //grav->homogen(true);
                                //--------------------------------------------------- kleine start halle -------------------------------------------------------
                                erzeugenquader(_vektor3<_tg>(1,0,1),_vektor3<_tg>(13,0,0),_vektor3<_tg>(0,50,0),_vektor3<_tg>(0,0,12),textur[11],13,50,12);
                                h.setzen(3.1,3,10);
                                c.setzen(0.03,0.1,0.8);
                                lit=new _licht<>(welt,h,c,100);
                                lit->farbeglanz(_vektor3<_to>(0.01,0.01,0.1));
                                lit->schattenvolumen(false);
                                ovl.einhaengenzumloeschen(lit);
                                erzeugenquader(_vektor3<_tg>(5,0,-2),_vektor3<_tg>(3,0,0),_vektor3<_tg>(0,12,0),_vektor3<_tg>(0,0,3),textur[0],3,12,3);
                                new _corundsteincorund(this, 1,0,12,1,1,1,textur[23],1);                                
                                new _corundstein(this,1,0,2,3,2,1,textur[0],false);
                                new _corundstein(this,1,0,3,1,2,8,textur[0],false);
                                new _corundstein(this,2,0,10,6,2,1,textur[0],false);
                                new _corundstein(this,9,0,10,5,2,1,textur[0],false);
                                new _corundstein(this,13,0,2,1,2,8,textur[0],false);
                                new _corundstein(this,11,0,2,2,2,1,textur[0],false);
                                new _corundstein(this,5,0,8,3,2,1,textur[0],false);
                                new _corundstein(this,9,0,8,2,2,1,textur[0],false);
                                new _corundstein(this,11,0,5,1,2,1,textur[0],false);
                                new _corundstein(this,11,0,7,1,2,2,textur[0],false);
                                new _corundstein(this,7,0,4,1,2,2,textur[0],false);
                                new _corundstein(this,5,0,6,1,2,1,textur[0],false);
                                new _corundstein(this,5,0,7,3,2,1,textur[0],false);
                                new _corundsteinschieb(this,8,0,4 ,3,2,1,textur[41],0.05);
                                new _corundsteinschieb(this,9,0,7 ,1,2,1,textur[41],0.05);
                                new _corundsteinschieb(this,8,0,9 ,1,2,2,textur[41],0.05);
                                new _corundsteinimpuls(this,4,0,4 ,1,1,1);
                                new _corundsteinimpuls(this,5,0,4 ,1,1,1);
                                new _corundsteinimpuls(this,6,0,4 ,1,1,1);
                                new _corundsteinimpuls(this,6,0,5 ,1,1,1);
                                new _corundsteinimpuls(this,4,0,5 ,1,1,1);
                                new _corundsteinimpuls(this,4,0,6 ,1,1,1);
                                new _corundsteinimpuls(this,4,0,7 ,1,1,1);
                                new _corundsteinimpuls(this,4,0,8 ,1,1,1);
                                new _corundsteinimpuls(this,11,0,6 ,1,1,1);
                                //---------------------------------------------------gruene halle---------------------------------------------------------------
                                erzeugenquader(_vektor3<_tg>(1,-1,-30),_vektor3<_tg>(28,0,0),_vektor3<_tg>(0,40,0),_vektor3<_tg>(0,0,28),textur[11],28,40,28);
                                h.setzen(14.1,0.3,-17.001);
                                c.setzen(0.1,0.9,0.2);
                                licht=lit=new _licht<>(welt,h,c,100);
                                lit->farbeglanz(_vektor3<_to>(0.005,0.1,0.005));
                                //lit->dynamischadditiv(false);
                                for(x=5;x<28;x+=5){
                                 h.setzen(x+0.01,25,-28);
                                 c.setzen(0.7,0.9,0.4);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->farbeglanz(_vektor3<_to>(0.01,0.01,0.1));
                                 lit->dynamischadditiv(false);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                 h.setzen(x+0.01,25,-4);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->farbeglanz(_vektor3<_to>(0.01,0.01,0.1));
                                 lit->dynamischadditiv(false);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                };
                                erzeugenquader(_vektor3<_tg>(-50,-1,-20),_vektor3<_tg>(51,0,0),_vektor3<_tg>(0,12,0),_vektor3<_tg>(0,0,6),textur[0],51,12,6);
                                erzeugenquader(_vektor3<_tg>(16,23,-42),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,12),textur[0],2,14,12);

                                erzeugenquader(_vektor3<_tg>(10,23,-44),_vektor3<_tg>(8,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,2),textur[0],8,14,2);
                                erzeugenquader(_vektor3<_tg>(10,23,-50),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,6),textur[0],2,14,6);
                                erzeugenquader(_vektor3<_tg>(10,23,-52),_vektor3<_tg>(8,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,2),textur[0],8,14,2);
                                 h.setzen(11,27,-43);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                 h.setzen(11,27,-52);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                
                                
                                erzeugenquader(_vektor3<_tg>(16,23,-62),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,10),textur[0],2,14,10);
                                erzeugenquader(_vektor3<_tg>(16,23,-64),_vektor3<_tg>(8,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,2),textur[0],8,14,2);
                                erzeugenquader(_vektor3<_tg>(22,23,-70),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,6),textur[0],2,14,6);
                                erzeugenquader(_vektor3<_tg>(16,23,-72),_vektor3<_tg>(8,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,2),textur[0],8,14,2);
                                 h.setzen(23,27,-71);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                 h.setzen(23,27,-63);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                 
                                 
                                 h.setzen(17,27,-40);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                 h.setzen(17,27,-60);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                erzeugenquader(_vektor3<_tg>(16,15,-102),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,8,30),textur[0],2,14,30);
                                 h.setzen(17,23,-85);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                erzeugenquader(_vektor3<_tg>(-30,15,-108),_vektor3<_tg>(48,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,6),textur[0],48,14,6);
                                for(x=-32;x<=17.01;x+=(32.0f+17.0f)/5.0f){
                                 h.setzen(x,19,-105);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->schattenvolumen(false);
                                 ovl.einhaengenzumloeschen(lit);
                                };
                               // erzeugenquader(_vektor3<_tg>(-30,15,-102),_vektor3<_tg>(4,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,42),textur[0],4,14,42);
                                 
                                
                             //   erzeugenquader(_vektor3<_tg>(17,23,-32),_vektor3<_tg>(9,-8,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,1),textur[0],10,14,1);
                             //   erzeugenquader(_vektor3<_tg>(26,15,-34),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,3),textur[0],1,14,3);
                                new _corundsteincorund(this, 20,23,-7 ,1,1,1,textur[23],1);
                                new _corundstein(this,11,-1,-20,2,12,2,textur[0],false);
                                new _corundstein(this,15,-1,-20,2,12,2,textur[0],false);
                                new _corundstein(this,11,-1,-16,2,12,2,textur[0],false);
                                new _corundstein(this,15,-1,-16,2,12,2,textur[0],false);

                                new _corundstein(this,9,1,-18,4,6,2,textur[0],false);
                                new _corundstein(this,15,-1,-18,2,8,2,textur[0],false);
                                 
                                new _corundstein(this,11,9,-18,2,2,2,textur[0],false);
                                new _corundstein(this,15,9,-18,2,2,2,textur[0],false);
                                 
                                new _corundstein(this,13,7,-20,2,4,2,textur[0],false);
                                new _corundstein(this,13,7,-16,2,4,2,textur[0],false);

                                new _corundsteingummiband(this,14.5,22,-17.5,1,1,1,textur[12],0.0012);
                                 
                                //new _corundstein(this,15,22,-30,2,1,12,textur[0],false);
                                os=new _corundstein(this,16,22,-30,2,1,22,textur[44],false);
                                os->maskiert(true);
                                os->zweiseitig(true);
                                os=new _corundstein(this,16,23,-60,2,6,6,textur[44],false);
                                os->maskiert(true);
                                os->subtraktiv(true);
                                os->schattenvolumen(false);
                                os->lightmapschattierung(false);
                                os->_netz::anfang(poly);
                                poly=poly->naechstes();
                                poly->_listenknotenbasis<_polygon>::loeschmarkierung(true);
                                poly=poly->naechstes();
                                poly=poly->naechstes();
                                poly=poly->naechstes();
                                poly->_listenknotenbasis<_polygon>::loeschmarkierung(true);
                                poly=poly->naechstes();
                                poly->_listenknotenbasis<_polygon>::loeschmarkierung(true);
                                netz=os;
                                netz-> _listebasis<_polygon>:: loeschenmarkiert();
                                
                                os=new _corundstein(this,16,23,-60,2,6,6,textur[44],false);
                                os->maskiert(true);
                                os->subtraktiv(false);
                                os->schattenvolumen(false);
                                os->lightmapschattierung(false);
                                os->_netz::anfang(poly);
                                poly=poly->naechstes();
                                poly->_listenknotenbasis<_polygon>::loeschmarkierung(true);
                                poly=poly->naechstes();
                                poly=poly->naechstes();
                                poly=poly->naechstes();
                                poly->_listenknotenbasis<_polygon>::loeschmarkierung(true);
                                poly=poly->naechstes();
                                poly->_listenknotenbasis<_polygon>::loeschmarkierung(true);
                                netz=os;
                                netz-> _listebasis<_polygon>:: loeschenmarkiert();
                                
                                
                                
                                os=new _corundstein(this,16,22,-8,6,1,3,textur[44],false);
                                os->maskiert(true);
                                os->zweiseitig(true);
                                os=new _corundstein(this,5,0,-14,3,1,12,textur[44],false);
                                os->maskiert(true);
                                os->zweiseitig(true);
                                os=new _corundstein(this,1,1,-20,1,3,6,textur[44],false);
                                os->maskiert(true);
                                os->zweiseitig(true);
                                new _corundsteinschieb(this,11,7,-18 ,6,2,2,textur[43],0.05); 
                                new _corundsteinschieb(this,13,5,-20 ,2,2,6,textur[43],0.05); 
                                 
                                gn=new _geometriequader(welt,_vektor3<_tg>(1,6,-18),_vektor3<_tg>(2,-1,0),_vektor3<_tg>(0,0.1,0),_vektor3<_tg>(0,0,2),textur[44]);
                                gn->texturkoordinatenlaenge(2,1,2);
                                nt=gn->erzeugen();
                                new _corundsteinbeschleunigung(this,nt,0.5);
                                delete nt;
                                delete gn;
                                // gn=new _geometriequader(welt,_vektor3<_tg>(1,-1,-14),_vektor3<_tg>(28,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,12),textur[82]);
                                // gn->texturkoordinatenlaenge(28,1,12);
                                // nt0=gn->erzeugen();delete gn;
                                // gn=new _geometriequader(welt,_vektor3<_tg>(17,-1,-20),_vektor3<_tg>(12,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,6),textur[82]);
                                // gn->texturkoordinatenlaenge(12,1,6);
                                // nt1=gn->erzeugen();delete gn;
                                // gn=new _geometriequader(welt,_vektor3<_tg>(1,-1,-30),_vektor3<_tg>(28,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,10),textur[82]);
                                // gn->texturkoordinatenlaenge(28,1,10);
                                // nt2=gn->erzeugen();delete gn;
                                // I.bearbeiten(nt0,nt1,2);
                                // I.bearbeiten(nt0,nt2,2);
                                // delete nt1;
                                // delete nt2;
                                // os=new _corundsteintotenkopf(this,nt0,1);
                                // os->anlegentexturkoordinaten(2);
                                // os->anlegenlightmap("lightmap//lightmaptotenkopf",0.5);
                                // delete nt0;
                                 
                                new _corundsteintotenkopf(this,1,-1,-14,28,1,12,1);
                                new _corundsteintotenkopf(this,17,-1,-20,12,1,6,1);
                                os=new _corundsteintotenkopf(this,1,-1,-30,28,1,10,1);
                                netz=os;
                                netz->_listebasis<_polygon>::anfang(poly);
                                poly=poly->naechstes();
                                poly->debuggen(true);
                                
                                new _corundsteindach(this,1,0,-20,10,1,6,textur[0]);
                                os=new _corundsteinschere(this,13,-1,-20,2,6,2,textur[13]);
                                os->loeschentexturkoordinaten(2);
                                os->verwendentexturdynamisch(false);
                                os->transparenz(true);
                                os->transparenzfaktor(0.4);
                                os->schattenvolumen(false);
                                //os->zweiseitig(true);
                                os->farbeverbinder(_vektor4<_to>(0,1,0,0.4));
                                os=new _corundsteinschere(this,13,-1,-16,2,6,2,textur[13]);
                                os->loeschentexturkoordinaten(2);
                                os->verwendentexturdynamisch(false);
                                os->transparenz(true);
                                os->transparenzfaktor(0.4);
                                //os->zweiseitig(true);
                                os->schattenvolumen(false);
                                os->farbeverbinder(_vektor4<_to>(0,1,0,0.4));           
                                                     
                                //---------------------------------------------------blaue halle---------------------------------------------------------------
                                erzeugenquader(_vektor3<_tg>(-70,-1,-30),_vektor3<_tg>(20,0,0),_vektor3<_tg>(0,20,0),_vektor3<_tg>(0,0,20),textur[0],20,20,20);
                                for(x=-65;x<-50;x+=5){
                                 h.setzen(x+0.01,2,-28);
                                 c.setzen(0.03,0.1,0.8);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->farbeglanz(_vektor3<_to>(0.01,0.01,0.1));
                                 lit->dynamischadditiv(false);
                                 if(x!=-60) lit->schattenvolumen(false);
                                 if(x!=-60) ovl.einhaengenzumloeschen(lit);
                                 h.setzen(x+0.01,2,-12);
                                 c.setzen(0.03,0.1,0.8);
                                 lit=new _licht<>(welt,h,c,20);
                                 lit->farbeglanz(_vektor3<_to>(0.01,0.01,0.1));
                                 lit->dynamischadditiv(false);
                                 if(x!=-60) lit->schattenvolumen(false);
                                 if(x!=-60) ovl.einhaengenzumloeschen(lit);
                                };
                                erzeugenquader(_vektor3<_tg>(-60,-1,-10),_vektor3<_tg>(6,0,0),_vektor3<_tg>(0,12,0),_vektor3<_tg>(0,0,30),textur[0],6,12,30);
                                new _corundsteincorund(this, -65,-1,-15,1,1,1,textur[23],0);
                                new _corundsteincorund(this, -65,-1,-25,1,1,1,textur[23],0);
                                new _corundstein(this,-61,-1,-11,1,20,1,textur[28],false);
                                new _corundstein(this,-54,-1,-11,1,20,1,textur[28],false);
                                tornetze.aushaengen();
                                gqt=new _geometriequader(welt,_vektor3<_tg>(-60,-1,-11),_vektor3<_tg>(6,0,0),_vektor3<_tg>(0,20,0),_vektor3<_tg>(0,0,1),textur[44]);
                                gqt->texturkoordinatenlaenge(6,20,1);
                                tornetz=gqt->erzeugen();
                                tornetz->verschiebennormal(steinskalierung);
                                tornetz->maskiert(true);
                                tornetze.einhaengen(tornetz);
                                tornetz->subtraktiv(false);
                                tornetz->lightmapschattierung(false);
                                tor[0]=new _corundsteintor(this);
                                tor[0]->zyklen=100;
                                tor[0]->einhaengen(&tornetze,_vektor3<_tg>(0,0.1,0));
                                oss[0]=new _corundsteinschalter(this,-61,-1,-13,  1,1,1,0,tor[0]);
                                delete gqt;
                                new _corundsteinflak(this,-60,-1,-25);
                                _corundsteinflak*osf=new _corundsteinflak(this,-57,-1,-25);
                                osf->schalterdauer=true;
                                new _corundsteinschalter(this,-57,-1,-26,1,1,1,0,osf);
                                new _corundstein(this,-61,-1,-30,1,1,6,textur[43],false);
                                new _corundstein(this,-59,-1,-28,1,1,4,textur[43],false);

                                //--------------------------------------------------- rote halle -------------------------------------------------------------
                                erzeugenquader(_vektor3<_tg>(-70,-1,20),_vektor3<_tg>(20,0,0),_vektor3<_tg>(0,40,0),_vektor3<_tg>(0,0,20),textur[0],20,40,20);
                                h.setzen(-55.1,1.3,25.1);
                                c.setzen(1,0.3,0.0);
                                lit=new _licht<>(welt,h,c,100);
                                lit->farbeglanz(_vektor3<_to>(0.1,0.03,0.0));
                                //lit->dynamischadditiv(false);
                                erzeugenquader(_vektor3<_tg>(-90,15,28),_vektor3<_tg>(20,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,4),textur[0],20,14,4);
                                erzeugenquader(_vektor3<_tg>(-50,15,28),_vektor3<_tg>(20,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,4),textur[0],20,14,4);
                                 new _corundsteincorund(this, -85,15,30,1,1,1,textur[23],2);
                                 new _corundsteincorund(this, -35,15,30,1,1,1,textur[23],2);                                
                                 tornetze.aushaengen();
                                 new _corundstein(this,-61,-1,20,1,20,1,textur[28],false);
                                 new _corundstein(this,-54,-1,20,1,20,1,textur[28],false);
                                 gqt=new _geometriequader(welt,_vektor3<_tg>(-60,-1,20),_vektor3<_tg>(6,0,0),_vektor3<_tg>(0,20,0),_vektor3<_tg>(0,0,1),textur[44]);
                                 gqt->texturkoordinatenlaenge(6,20,1);
                                 tornetz=gqt->erzeugen();
                                 tornetz->verschiebennormal(steinskalierung);
                                 tornetz->maskiert(true);
                                 tornetze.einhaengen(tornetz);
                                 tornetz->subtraktiv(false);
                                 tornetz->lightmapschattierung(false);
                                 tor[1]=new _corundsteintor(this);
                                 tor[1]->zyklen=100;
                                 tor[1]->einhaengen(&tornetze,_vektor3<_tg>(0,0.1,0));
                                 oss[2]=new _corundsteinschalter(this,-58,-1,18,  1,1,1,0,tor[1]);
                                 oss[2]->listeek.einhaengen(tor[0]);
                                 delete gqt;
                                 gn=new _geometriequader(welt,_vektor3<_tg>(-70,-0.3,29),_vektor3<_tg>(2,-0.8,0),_vektor3<_tg>(0,0.1,0),_vektor3<_tg>(0,0,2),textur[44]);
                                 gn->texturkoordinatenlaenge(2,1,2);
                                 nt=gn->erzeugen();
                                 new _corundsteinbeschleunigung(this,nt,1.1);
                                 delete nt;
                                 delete gn;
                                 gn=new _geometriequader(welt,_vektor3<_tg>(-52,-1.1,29),_vektor3<_tg>(2,0.8,0),_vektor3<_tg>(0,0.1,0),_vektor3<_tg>(0,0,2),textur[44]);
                                 gn->texturkoordinatenlaenge(2,1,2);
                                 nt=gn->erzeugen();
                                 new _corundsteinbeschleunigung(this,nt,1.1);
                                 delete nt;
                                 delete gn;
                                //--------------------------------------------------- gelber gang -------------------------------------------------------------
                                erzeugenquader(_vektor3<_tg>(-30,15,-102),_vektor3<_tg>(4,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,134),textur[0],4,14,134);
                                erzeugenquader(_vektor3<_tg>(-50,12,-20),_vektor3<_tg>(20,3,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,6),textur[0],20,14,6);
                                h.setzen(-28,20,-18);
                                c.setzen(1,0.3,0.0);
                                lit=new _licht<>(welt,h,c,200);
                                lit->farbeglanz(c*0.08);
                                lit->dynamischadditiv(false);
                                oss[1]=new _corundsteinschalter(this,-30,15,-20,1,1,1,0,tor[0]);
                                _corundsteinkugelgen*oskg=new _corundsteinkugelgen(this,-28,15,-10,_vektor3<_tg>(0,0,0.1),0.2,0,0,_vektor4<_to>(1,0,0,1));
                                oskg->killer=true;
                                oskg->zumspielervektor=true;
                                oskg->chaotischervektor=true;                                
                                //--------------------------------------------------- roter gang ------------------------------------------------------------
                                erzeugenquader(_vektor3<_tg>(-26,15,-60),_vektor3<_tg>(60,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,6),textur[0],60,14,6);
                                for(x=-25;x<(-25+60);x+=15){
                                 h.setzen(x+0.01,19,-57);
                                 c.setzen(0.9,0.3,0.0);
                                 lit=new _licht<>(welt,h,c,30);
                                 lit->farbeglanz(c*0.08);
                                 lit->schattenvolumen(false);
                                 if(x!=20) ovl.einhaengenzumloeschen(lit);
                                 if(x==20) licht2=lit;
                                };
                                erzeugenquader(_vektor3<_tg>(34,15,-60),_vektor3<_tg>(6,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,80),textur[0],6,14,80);
                                for(z=-60;z<(-25+60);z+=15){
                                 h.setzen(37,19,z);
                                 lit=new _licht<>(welt,h,c,30);
                                 lit->farbeglanz(c*0.08);
                                 lit->schattenvolumen(false);
                                 /*if(z!=0) */ovl.einhaengenzumloeschen(lit);
                                };
                                erzeugenquader(_vektor3<_tg>(34,15,20),_vektor3<_tg>(6,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,6),textur[0],6,14,6);
                                erzeugenquader(_vektor3<_tg>(0,0,20),_vektor3<_tg>(34,15,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,6),textur[0],34,14,6);
                                erzeugenquader(_vektor3<_tg>(-2,0,1),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,25),textur[0],2,14,25);
                                h.setzen(-1,5,23);
                                c.setzen(0.1,0,0.9);
                                lit=new _licht<>(welt,h,c,10);
                                lit->farbeglanz(c*0.08);
                                lit->schattenvolumen(false);
                                ovl.einhaengenzumloeschen(lit);
                                h.setzen(-1,5,3);
                                c.setzen(0.1,0,0.9);
                                lit=new _licht<>(welt,h,c,5);
                                lit->farbeglanz(c*0.08);
                                lit->schattenvolumen(false);
                                ovl.einhaengenzumloeschen(lit);
                                erzeugenquader(_vektor3<_tg>(0,0,1),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,1),textur[0],1,14,1);
                                //lit->schattenvolumen(false);
                               // ovl.einhaengenzumloeschen(lit);
                                for(x=-26;x<(-26+60);x+=5){
                                 new _corundstein(this,x,15,-60,1,14,1,textur[28],false); 
                                 new _corundstein(this,x,15,-55,1,14,1,textur[28],false);
                                };                                 
                                for(z=-60;z<(20);z+=5){
                                 new _corundstein(this,34,15,z,1,14,1,textur[28],false); 
                                 new _corundstein(this,39,15,z,1,14,1,textur[28],false);
                                };                     
                                //new _corundstein(this,39,15,-40,1,14,1,textur[28],false);            
                                new _corundsteinflak(this,38,15,-59);
                                 
                                tornetze.aushaengen();
                                gqt=new _geometriequader(welt,_vektor3<_tg>(35,15,-55),_vektor3<_tg>(4,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,1),textur[44]);
                                gqt->texturkoordinatenlaenge(4,14,1);
                                tornetz=gqt->erzeugen();
                                delete gqt;
                                tornetz->verschiebennormal(steinskalierung);
                                tornetz->maskiert(true);
                                tornetz->subtraktiv(false);
                                tornetz->lightmapschattierung(false);
                                tornetze.einhaengen(tornetz);
                                 
                                gqt=new _geometriequader(welt,_vektor3<_tg>(34,15,-59),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,14,0),_vektor3<_tg>(0,0,4),textur[44]);
                                gqt->texturkoordinatenlaenge(1,14,4);
                                tornetz=gqt->erzeugen();
                                delete gqt;
                                tornetz->verschiebennormal(steinskalierung);
                                tornetz->maskiert(true);
                                tornetz->subtraktiv(false);
                                tornetz->lightmapschattierung(false);
                                tornetze.einhaengen(tornetz);

                                tor[4]=new _corundsteintor(this);
                                tor[4]->zyklen=100;
                                tor[4]->einhaengen(&tornetze,_vektor3<_tg>(0,0.1,0));
                                oss[4]=new _corundsteinschalter(this,32,15,-60,  1,1,1,0,tor[4]);
                                _corundsteinkugelgen*oskg0=new _corundsteinkugelgen(this,-20,15,-58,_vektor3<_tg>(0.2,0,0),0.2,0,0,_vektor4<_to>(1,0,0,1));
                                oskg0->schaltenautomatisch=true;
                                oskg0->zumspielervektor=true;
                                oskg0->chaotischervektor=true;
                                oskg0->killer=true;
                                _corundsteinkugelgen*oskg1=new _corundsteinkugelgen(this,37,15,5,_vektor3<_tg>(0,0,-0.2),0.2,0,0,_vektor4<_to>(1,0,0,1));
                                oskg1->schaltenautomatisch=true;
                                oskg1->zumspielervektor=true;
                                oskg1->chaotischervektor=true;
                                oskg1->killer=true;
                                oss[4]->listeek.einhaengen(oskg0);
                                oss[4]->listeek.einhaengen(oskg1);                               
                                //-----------------------------------------------------------------------------------------------------------------------
                                if(welt->anfang(nit))do{
                                }while(welt->naechstes(nit));
                                ambientlicht.setzen(0.02,0.02,0.02,1);
                               /* rohmeshes=welt->uebersetzen();
                                rohmeshes->loeschen();
                                delete rohmeshes;  
                                welt->anfang(nit);
                                nit->farbeverbinder(_vektor4<_to>(0,0,0,1));
                                if(welt->anfang(zit)){
                                 if(zit->anfang(sit))do{
                                  if(sit->anfang(pit))do{
                                   if(sit->anfang(lit))do{
                                  //  pit->polygon()->erzeugenschatten(lit,200);
                                   }while(sit->naechstes(lit));
                                  }while(sit->naechstes(pit));
                                 }while(zit->naechstes(sit));
                                };
                                */
                                
                                //----------------------------------------------- corundwelt bauen-------------------------------------------------------------
                                if(welt->anfang(zit)){
                                /* ovl.einhaengenzumschattieren(zit->innerhalbquader(10,22,-54,8,14,12),licht2,130); 
                                 ovl.einhaengenzumschattieren(zit->innerhalbquader(16,22,-72,8,14,12),licht2,130); 
                                 ovl.einhaengenzumschattieren(zit->innerhalbquader(0,-2,-3,30,42,5),licht,30); 
                                 erzeugenpartikelsysteme(zit);
                                 //--------------------------------------------------------- spezielle aufrüstungen mit schattenvolumen -------------------------------------
                                 ovl.schattieren();*/
                                 paaranzahl=3;                                
                                 new _weltdebugtext(welt,"Szene_08",_vektor3<_tg>(2,2,2),_vektor3<_tg>(11,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                };
                                
                                
                                
                                
                                
                                
                                gra->aktivitaet(true);
                                B->lichtambient(_vektor3<float>(ambientlicht[0],ambientlicht[1],ambientlicht[2]));
                               // B->bestrahlenlightmapzone(welt);
                                welt->uebergebenlightmap(gra);
                                
                               // ovl.loeschen();
                                
                            
                                //kugeln erzeugen 
                                spieler=new _corundkugel(this,_vektor3<_tg>(17,23.51,-29),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                _corundkugel*ok;
                                ok=new _corundkugel(this,_vektor3<_tg>(-57.5,0,0),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(1,0,0,1));
                                ok->killer=true;
                                ok->chaotischervektor=true;
                                ok->zumspielervektor=true;
                                ok=new _corundkugel(this,_vektor3<_tg>(-57.5,0,25),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(1,0,0,1));
                                ok->killer=true;
                                ok->chaotischervektor=true;
                                ok->zumspielervektor=true;
                                
                               
                                //sound->PlayStream(stream[0]);
                                
                                
                          
};
void _corundwelt::erzeugenszene9(_grafik*gra){
                                _netz*nn0;
                                _netz*nn1;
                                _geometriequader*gq;
                                _modifikationnetzintersektion I;
                                //----------------
                                erzeugenumgebung0();
                                _netz*ns;
                                //boden
                                ns=erzeugennetz(_vektor3<_tg>(-1,0,-1),_vektor3<_tg>(9+2,0,0),_vektor3<_tg>(0,0,19+2),2,4,textur[26]);
                                 
                                new _corundstein(this,-1,0,-1 ,11,1,1,textur[0],false);
                                new _corundstein(this,-1,0,19,11,1,1,textur[0],false);
                                new _corundstein(this,-1,0,0,  1,1,19,textur[0],false);
                                new _corundstein(this,9,0,0,  1,1,19,textur[0],false);
                                 
                                new _corundsteincorund(this, 6,0,18,1,1,1,textur[23],0);
                                new _corundsteincorund(this, 2,0,0  ,1,1,1,textur[23],0);
                                //new _corundsteincorund(this, -2,0,1  ,1,1,1,textur[23],0);
                                //new _corundsteincorund(this, 18,0,-13,1,1,1,textur[23],1);                                
                                paaranzahl=1;
                                 
                                new _corundstein(this,0,0,16,2,1,1,textur[0],false);
                                new _corundstein(this,3,0,15,1,1,1,textur[0],false);
                                new _corundstein(this,7,0,13,2,1,1,textur[0],false);
                                new _corundstein(this,8,0,12,1,1,1,textur[0],false);
                                new _corundstein(this,4,0,9,2,1,1,textur[0],false);
                                new _corundstein(this,3,0,8,6,1,1,textur[0],false);
                                new _corundstein(this,5,0,3,1,1,5,textur[0],false);
                                new _corundstein(this,4,0,3,1,1,1,textur[0],false);
                                new _corundstein(this,4,0,5,1,1,1,textur[0],false);
                                new _corundstein(this,2,0,4,2,1,1,textur[0],false);
                                new _corundstein(this,3,0,2,2,1,1,textur[0],false);
                                new _corundstein(this,0,0,2,2,1,1,textur[0],false);
                                new _corundstein(this,0,0,3,1,1,3,textur[0],false);
                                new _corundstein(this,0,0,8,1,1,1,textur[0],false);
                            
                                new _corundsteinschieb(this,6,0,11,3,1,1,textur[41],0.04);
                                new _corundsteinschieb(this,1,0,7,1,1,2,textur[41],0.04);
                                 
                                gq=new _geometriequader(welt,_vektor3<_tg>(2,0,15),_vektor3<_tg>(0,0,3),_vektor3<_tg>(0,1,0),_vektor3<_tg>(1,0,0),textur[41]);
                                gq->texturkoordinatenlaenge(1,1,3);
                                nn0=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt,_vektor3<_tg>(3,0,16),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(2,1,1);
                                nn1=gq->erzeugen();
                                delete gq;
                                I.bearbeiten(nn0,nn1,2);
                                delete nn1;
                                new _corundsteinschieb(this,nn0,0.06);
                                delete nn0;
                         
                                gq=new _geometriequader(welt,_vektor3<_tg>(4,0,13),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,3),textur[41]);
                                gq->texturkoordinatenlaenge(1,1,3);
                                nn0=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt,_vektor3<_tg>(5,0,14),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(2,1,1);
                                nn1=gq->erzeugen();
                                delete gq;
                                I.bearbeiten(nn0,nn1,2);
                                delete nn1;
                                new _corundsteinschieb(this,nn0,0.06);
                                delete nn0;
                         
                                gq=new _geometriequader(welt,_vektor3<_tg>(7,0,14),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,3),textur[41]);
                                gq->texturkoordinatenlaenge(1,1,3);
                                nn0=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt,_vektor3<_tg>(5,0,15),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(2,1,1);
                                nn1=gq->erzeugen();
                                delete gq;
                                I.bearbeiten(nn0,nn1,2);
                                delete nn1;
                                new _corundsteinschieb(this,nn0,0.06);
                                delete nn0;
                                
                                gq=new _geometriequader(welt,_vektor3<_tg>(5,0,10),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,3),textur[41]);
                                gq->texturkoordinatenlaenge(1,1,3);
                                nn0=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt,_vektor3<_tg>(3,0,11),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(2,1,1);
                                nn1=gq->erzeugen();
                                delete gq;
                                I.bearbeiten(nn0,nn1,2);
                                delete nn1;
                                new _corundsteinschieb(this,nn0,0.06);
                                delete nn0;
                                
                                gq=new _geometriequader(welt,_vektor3<_tg>(1,0,9),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,3),textur[41]);
                                gq->texturkoordinatenlaenge(1,1,3);
                                nn0=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt,_vektor3<_tg>(2,0,10),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(2,1,1);
                                nn1=gq->erzeugen();
                                delete gq;
                                I.bearbeiten(nn0,nn1,2);
                                delete nn1;
                                new _corundsteinschieb(this,nn0,0.06);
                                delete nn0;
                          
                                gq=new _geometriequader(welt,_vektor3<_tg>(2,0,6),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(2,1,1);
                                nn0=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt,_vektor3<_tg>(3,0,5),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),textur[41]);
                                gq->texturkoordinatenlaenge(1,1,1);
                                nn1=gq->erzeugen();
                                delete gq;
                                I.bearbeiten(nn0,nn1,2);
                                delete nn1;
                                new _corundsteinschieb(this,nn0,0.06);
                                delete nn0;
                            
                                new _weltdebugtext(welt,"Szene_09",_vektor3<_tg>(0,2,0),_vektor3<_tg>(14,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                //  kugeln erzeugen 
                                spieler=new _corundkugel(this,_vektor3<_tg>(4.5,3,18.5),_vektor3<_tg>(0,0,0),0.2,_vektor4<_to>(0,0,0,1));
                                spieler->steuerung=true;
                                spieler->spieler=true;
};
_netz* _corundwelt::erzeugenquader(const _vektor3<_tg>&o,const _vektor3<_tg>&vx,const _vektor3<_tg>& vy,const _vektor3<_tg>& vz,_textur<_tb>*t,_tg tksx,_tg tksy,_tg tksz){
                                _geometriequader*gq;
                                _netz*netz;
                                //-----------------
                                gq=new _geometriequader(welt,o,vx,vy,vz,t);
                                gq->texturkoordinatenlaenge(tksx,tksy,tksz);
                                netz=gq->erzeugen();
                                delete gq;
                                netz->einhaengen(welt);
                                netz->subtraktiv(true);
                                netz->transparenzfaktor(0);
                                netz->transparenz(false);                                                                
                                netz->verwendentextur(true);
                                netz->dynamischschattierend(false);
                                netz->anlegentexturkoordinaten(2);
                                netz->lightmaptexelgroesse(1);
                                //netz->anlegenlightmap("lightmap//lightmapzone",1);
                                netz->verwendentexturdynamisch(true);
                                netz->keinbsp(false);
                                netz->schattenvolumen(false);
                                return(netz);
};
void _corundwelt::erzeugenumgebung0(){
                                _vektor3<_tg> h;
                                _vektor3<_to> c;
                                _netz*m;
                                _polygon*pit;
                                _geometriequader*gb;

                                _vektor3<_tg> ort;
                                _gravitation<_tg>*grav;
                                //----------------------------------------gravitation-------------------------------------------
                                grav=new _gravitation<_tg>(welt,_vektor3<_tg>(0,-0.006,0),1);
                                //grav->homogen(true);
                                //-----------------------------------------zone anlegen----------------------------------------
                                _netz*mg;
                                _tg w=1024;
                                h.setzen(-w/2,-w/2,-w/2);
                                gb=new _geometriequader(welt,h,_vektor3<_tg>(w,0,0),_vektor3<_tg>(0,w,0),_vektor3<_tg>(0,0,w),textur[17]);
                                gb->texturkoordinatenlaenge(1,1,1);
                                mg=gb->erzeugen();
                                delete gb;
                                mg->einhaengen(welt);
                                mg->subtraktiv(true);
                                mg->transparenzfaktor(0);
                                mg->transparenz(false);                                                                
                                mg->verwendentextur(true);
                                mg->dynamischschattierend(false);
                               // mg->zweiseitig(true);
                               // mg->invertieren();
                                //mg->kollidierend(false);
                               // mg->zeichnenflaeche(true);
                                //-------------------------------------licht und übersetzung ---------------------------------
                                _licht<_tg,_to>*lit;
                                h.setzen(-140.1,165.1,140.3);
                                c.setzen(0.8,0.9,1);
                                lit=new _licht<>(welt,h,c,120);
                                lit->farbeglanz(_vektor3<_to>(0.2,0.1,0.05));
                                //-------------------------------sky box texturieren---------------------------------------
                                welt->anfang(m);  
                                skybox=m;
                                skybox->anfang(pit);
                                pit=pit->naechstes();
                                pit->textur(textur[18]);
                                pit=pit->naechstes();
                                pit->textur(textur[19]);
                                pit=pit->naechstes();
                                pit->textur(textur[20]);
                                pit=pit->naechstes();
                                pit->textur(textur[21]);
                                pit=pit->naechstes();
                                pit->textur(textur[22]);
                                m->farbeverbinder(_vektor4<_to>(1,1,1,1));
};