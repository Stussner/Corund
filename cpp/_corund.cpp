//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corund.cpp
//  Datum        : 04.04.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include "../hpp/_corund.hpp"


//******************************************************************************************************************************************************************************************************
//                              C O R U N D W E L T 
//******************************************************************************************************************************************************************************************************
_corundwelt::_corundwelt(_grafik*gra,_texturverwaltung<_tb>&texv,_akustik*sound,_tonverwaltung&tonv):_baumoctal<_polygon,_tg>(-100,-100,-100,100,100,100),textur(texv),tonverwaltung(tonv){
                                L->schreiben("_corundwelt()");
                                speichername="unbenannt.txt";
                                name="kein Name";
                                spieler=0;
                                ausgang=0;
                                diesekarte=0;
                                naechstekarte=-1;
                                naechsterknoten=0;
                                kamera=0;
                                teiloffen=0;
                                geoeffnet=0;
                                paaranzahl=0;
                                spezial=0;
                                skybox=0;
                                steinskalierung=-0.0001;
                                corundinventar=0;
                                psstaubwolke=0;
                                psstrahl=0;
                                psrot=0;
                                psfrage=0;
                                pseinschlag=0;
                                pskugeltot=0;                                
                                kamera=0;
                                pgrafik=gra;
                                debugschirm=0;
                                ambientlicht.setzen(0.02,0.02,0.02,1);

                                //reibung=0.99;
                                nebel=false;
                                nebelmodus=2;
                                nebelfarbe.setzen(1,0.9,0.8,1);
                                nebeldichte=0.01;
                                nebeldistanz.setzen(0,50);

                                pzeit=new _win::_zeit();
                                welt=new _welt();
                                welt->eigenetransformation(false);
                                welt->zeit(pzeit);
                                
                                zeitanfang=pzeit->system();                                
                                
                                mo=new _win::_maus<>(399,399);
                                mo->relativ(true);
                                kb=new _win::_tastatur();          
                                B=new _bestrahler();

                                zeichensatz=pgrafik->erzeugenzeichensatz(0,0,"zeichensatz/dauphin64");//new _zeichensatzbild((HDC)gra->kontext(),"Arial",30,30,false,false,false);
                                welt->debuggrafik(pgrafik);
                                welt->debugmaus(mo);
                                welt->debugtastatur(kb);
                                pgrafik->aktivitaet(true);
                                pgrafik->erzeugentexturen(&textur);
                                
                                pzeit->anfang();
                                explosion=new _corundton(this,tonverwaltung.ton(4),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));
                                explosion->lautstaerke=1;
                                corundinventar=new _corundinventar(this);
                                kameraverschiebung.setzen(0,9,0);
                                kamerafederhaerte=0.1;
                                kamera=new _corundkamera(this);
                                kamera->kam->yaw(70);
                                //erzeugenpartikelsysteme();
};
_corundwelt::~_corundwelt(){
                                pgrafik->aktivitaet(true);
                                pgrafik->loeschentexturen(&textur);
                                L->schreiben("~_corundwelt()");
                                loeschenpartikelsysteme();
                                delete explosion;
                                loeschenpartikelsysteme();
                                if(kamera) delete kamera;
                                if(corundinventar) delete corundinventar;
                                _listebasis<_corunddruckwelle>::loeschen();
                                _listebasis<_corundlicht>::loeschen();
                                _listebasis<_corundfigur>::loeschen();
                                _listebasis<_corundspinne>::loeschen();
                                _listebasis<_corundobjekt>::loeschen();
                                _listebasis<_corundboden>::loeschen();
                                _listebasis<_corundkugel>::loeschen();
                                _listebasis<_corundstein>::loeschen();
                                _listebasis<_corundgummiband>::loeschen();
                                _listebasis<_corundfeder>::loeschen();
                                _baumoctal<_polygon,_tg>::aushaengen();
                                delete zeichensatz;
                                delete B;
                                delete welt;
                                delete mo;
                                delete kb;
                                delete pzeit;
                                loeschendebugschirm();
                             
};
void _corundwelt::loeschenpartikelsysteme(){
                                if(psstaubwolke) delete psstaubwolke;
                                if(psstrahl) delete psstrahl;
                                if(psrot) delete psrot;
                                if(psfrage) delete psfrage;
                                if(pseinschlag) delete pseinschlag;
                                if(pskugeltot) delete pskugeltot;   
                                psstaubwolke=0;
                                psstrahl=0;
                                psrot=0;
                                psfrage=0;
                                pseinschlag=0;
                                pskugeltot=0;                                
};                                
                                
void _corundwelt::corundpaargeoeffnet(){
                                geoeffnet++;
                                if(geoeffnet==paaranzahl) {
                                 //spielende erreicht
                                 if(ausgang) ausgang->schalten();
                                 //new _weltdebugtext(welt,"Spielende erreicht",_vektor3<_tg>(3,2,5),_vektor3<_tg>(6,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                 //new _weltdebugtext(welt,"Laufen druecken",_vektor3<_tg>(3,2,3),_vektor3<_tg>(7,0,0),_vektor3<_tg>(0,0,1),_vektor4<_to>(1,1,1,1));
                                 if(corundinventar) corundinventar->text="Sie haben das Spielenede erreicht. Bitte Ausgang betreten.";
                                };                                
};

void _corundwelt::erzeugenbaum(){
                                //oktalbaum initialisieren
                                bool init;
                                _tg x0,x1,y0,y1,z0,z1;
                                _tg wx0,wx1,wy0,wy1,wz0,wz1;
                                
                                _partition::_zone*zit;
                                _partition::_sektor*sit;
                                _listenknoten<_polygon>*lnpit;
                                _netz*nit;
                                _polygon*pit;
                                //-------------------------
                                _baumoctal<_polygon,_tg>::aushaengen();
                                _baumoctal<_polygon,_tg>::maximalobjektanzahl(10);
                                _baumoctal<_polygon,_tg>::minimalwuerfelkante(0,0.8);
                                _baumoctal<_polygon,_tg>::minimalwuerfelkante(1,0.8);
                                _baumoctal<_polygon,_tg>::minimalwuerfelkante(2,0.8);
                                
                                if(welt->anfang(zit)){
                                 if(welt->anfang(zit))do{
                                  if(zit->anfang(sit))do{
                                   sit->erzeugenbaum(10,0.8);
                                  }while(zit->naechstes(sit));
                                 }while(welt->naechstes(zit));
                                 /*
                                 //umgrenzung bestimmen
                                 init=true;
                                 if(welt->anfang(zit))do{
                                  if(zit->anfang(sit))do{
                                   if(sit->internepolygone()->anfang(lnpit))do{
                                    if(lnpit->objekt()->markierung()==0){
                                     lnpit->objekt()->markierung(1);
                                     lnpit->objekt()->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                     if(init){
                                      wx0=x0;
                                      wx1=x1;
                                      wy0=y0;
                                      wy1=y1;
                                      wz0=z0;
                                      wz1=z1;
                                      init=false;
                                     }else{
                                      if(x0<wx0) wx0=x0;
                                      if(x1>wx1) wx1=x1;
                                      if(y0<wy0) wy0=y0;
                                      if(y1>wy1) wy1=y1;
                                      if(z0<wz0) wz0=z0;
                                      if(z1>wz1) wz1=z1;
                                     };
                                    };
                                   }while(sit->internepolygone()->naechstes(lnpit));
                                  }while(zit->naechstes(sit));
                                 }while(welt->naechstes(zit));
                                 
                                 //einhaengen
                                 _baumoctal<_polygon,_tg>::setzenhauptwuerfel(wx0,wx1,wy0,wy1,wz0,wz1);
                                 if(welt->anfang(zit))do{
                                  if(zit->anfang(sit))do{
                                   if(sit->internepolygone()->anfang(lnpit))do{
                                    if(lnpit->objekt()->markierung()==1){
                                     lnpit->objekt()->markierung(0);
                                     lnpit->objekt()->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                     _baumoctal<_polygon,_tg>::einhaengen(lnpit->objekt(),x0,x1,y0,y1,z0,z1);
                                    };
                                   }while(sit->internepolygone()->naechstes(lnpit));
                                  }while(zit->naechstes(sit));
                                 }while(welt->naechstes(zit));
                                 */
                                
                                }else{//---------------------------------------------------------------------------------------------------------------
                                 if(welt->anfang(nit))do{
                                  if(nit->keinbsp()==true)if(nit->anfang(pit))do{
                                   pit->markierung(0);
                                  }while(nit->naechstes(pit));
                                 }while(welt->naechstes(nit));

                                 //umgrenzung bestimmen
                                 init=true;
                                 if(welt->anfang(nit))do{
                                  if(nit->keinbsp()==true)if(nit->anfang(pit))do{
                                   if(pit->markierung()==0){
                                    pit->markierung(1);
                                    pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                    if(init){
                                     wx0=x0;
                                     wx1=x1;
                                     wy0=y0;
                                     wy1=y1;
                                     wz0=z0;
                                     wz1=z1;
                                     init=false;
                                    }else{
                                     if(x0<wx0) wx0=x0;
                                     if(x1>wx1) wx1=x1;
                                     if(y0<wy0) wy0=y0;
                                     if(y1>wy1) wy1=y1;
                                     if(z0<wz0) wz0=z0;
                                     if(z1>wz1) wz1=z1;
                                    };
                                   };
                                  }while(nit->naechstes(pit));
                                 }while(welt->naechstes(nit));
                                 //einhaengen
                                 _baumoctal<_polygon,_tg>::setzenhauptwuerfel(wx0,wx1,wy0,wy1,wz0,wz1);
                                 if(welt->anfang(nit))do{
                                  if(nit->keinbsp()==true)if(nit->anfang(pit))do{
                                   if(pit->markierung()==1){
                                    pit->markierung(0);
                                    pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                    _baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                   };
                                  }while(nit->naechstes(pit));
                                 }while(welt->naechstes(nit));
                                };
};                                   
void _corundwelt::zeichnenbaum(_grafik*gra){
                                _weltdebuglinie*wl=new _weltdebuglinie(welt,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor4<_to>(1,0,0,1));
                                if(wurzel()) zeichnenbaum(gra,wl,wurzel());
                                delete wl;
};
void _corundwelt::zeichnenbaum(_grafik*gra,_weltdebuglinie*wl,_baumoctalwuerfel<_polygon,_tg>*q){
                                _vektor3<_tg> v;
                                v.setzen(q->x0,q->y0,q->z0);wl->ort(0,v);v.setzen(q->x1,q->y0,q->z0);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x1,q->y0,q->z0);wl->ort(0,v);v.setzen(q->x1,q->y0,q->z1);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x1,q->y0,q->z1);wl->ort(0,v);v.setzen(q->x0,q->y0,q->z1);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x0,q->y0,q->z1);wl->ort(0,v);v.setzen(q->x0,q->y0,q->z0);wl->ort(1,v);   wl->zeichnen(gra);

                                v.setzen(q->x0,q->y1,q->z0);wl->ort(0,v);v.setzen(q->x1,q->y1,q->z0);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x1,q->y1,q->z0);wl->ort(0,v);v.setzen(q->x1,q->y1,q->z1);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x1,q->y1,q->z1);wl->ort(0,v);v.setzen(q->x0,q->y1,q->z1);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x0,q->y1,q->z1);wl->ort(0,v);v.setzen(q->x0,q->y1,q->z0);wl->ort(1,v);   wl->zeichnen(gra);

                                v.setzen(q->x0,q->y0,q->z0);wl->ort(0,v);v.setzen(q->x0,q->y1,q->z0);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x1,q->y0,q->z0);wl->ort(0,v);v.setzen(q->x1,q->y1,q->z0);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x1,q->y0,q->z1);wl->ort(0,v);v.setzen(q->x1,q->y1,q->z1);wl->ort(1,v);   wl->zeichnen(gra);
                                v.setzen(q->x0,q->y0,q->z1);wl->ort(0,v);v.setzen(q->x0,q->y1,q->z1);wl->ort(1,v);   wl->zeichnen(gra);
                                int i,j,k;
                                for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++) {
                                 if(q->kind[i][j][k]) zeichnenbaum(gra,wl,q->kind[i][j][k]);
                                };

};
void _corundwelt::initialisierenanimation(_grafik*gra){
                                unsigned int oi;
                                _corundstein*sit;
                                _corundobjekt*oit;
                                _corundboden*bit;
                                _corundsteincorund*sito;
                                _corundsteintor*sitt;
                                //-----------------
                                ausgang=0;
                                naechstekarte=-1;
                                naechsterknoten=0;
                                kamera->aktualisieren();
                                _partition::_zone*zit;
                                welt->anfang(zit);
                                if(psrot==0) {
                                 //es sind keine benutzerdefinierten partikelquellen angelegt worden
                                 erzeugenpartikelsysteme();
                                };
                                welt->initialisierenanimation();
                                mo->holen();
                                
                                //---------------------- netze aktualisieren -------------------------------
                                _netz*nit;
                                if(welt->anfang(nit))do{
                                 nit->optimierenpolygonstartvertex();
                                 nit->aktualisieren();
                                }while(welt->naechstes(nit));
                                //---------------------- kugel initialisieren -------------------------------
                               /* _corundkugel*kit;
                                if(anfang(kit))do{
                                 kit->initialisieren();
                                }while(naechstes(kit));*/
                                //---------------------- steine initialisieren ------------------------------
                                oi=0;
                                if(anfang(sit))do{
                                 sit->initialisieren();
                                 sito=dynamic_cast<_corundsteincorund*>(sit);
                                 if(sito){
                                  oi++;
                                 };
                                 sitt=dynamic_cast<_corundsteintor*>(sit);
                                 if(sitt){
                                  if(sitt->ausgang) ausgang=sitt;
                                 };
                                }while(naechstes(sit));
                                paaranzahl=oi/2;
                                //---------------------- objekte initialisieren ----------------------------
                                if(anfang(oit))do{
                                 oit->initialisieren();
                                }while(naechstes(oit));
                                //---------------------- böden initialisieren ----------------------------
                                if(anfang(bit))do{
                                 bit->initialisieren();
                                }while(naechstes(bit));
                                //---------------------- spinnen initialisieren ----------------------------
                                _corundspinne*csit;
                                if(anfang(csit))do{
                                 //csit->zone(zit);
                                 csit->initialisieren();
                                }while(naechstes(csit));
                                //---------------------- figuren initialisieren ----------------------------
                                _corundfigur*cfit;
                                if(anfang(cfit))do{
                                 cfit->initialisieren();
                                }while(naechstes(cfit));
                                //---------------------- grafik initialisieren -----------------------------
                                gra->aktivitaet(true);
                                if(nebel) gra->nebel(true); else gra->nebel(false);
                                gra->nebelmodus(nebelmodus);
                                gra->nebelfarbe(nebelfarbe);
                                gra->nebeldichte(nebeldichte);
                                gra->nebeldistanz(nebeldistanz[0],nebeldistanz[1]);
                                erzeugenbaum();
                                welt->initialisierenanimation();
                               erzeugendebugschirm();
};
void _corundwelt::animieren(_grafik*gra,_akustik*sound){
                                _corundkugel*kit;
                                _corundstein*osit;
                                _corundobjekt*coit;
                                _corundboden*cbit;
                                _corundlicht*clit;
                                //----------------------
                                grafikx=gra->groessex();
                                grafiky=gra->groessey();
                                //gra->loeschenseite();
                                //inventar animieren
                                if(corundinventar) corundinventar->animieren();

                                if(spieler){
                                 spieler->_kollidierbar::stammsektor()->transformieren(gra,kamera->kam);
                                 //if(kamera
                                }else{
                                 welt->transformieren(gra,kamera->kam,false);
                                };
                                //lichter animieren
                                if(anfang(clit))do{
                                 clit->animieren();
                                }while(naechstes(clit));
                                //böden animieren
                                if(anfang(cbit))do{
                                 cbit->animieren();
                                }while(naechstes(cbit));
                                //kugeln animieren
                                //if(anfang(kit))do{
                                // kit->animieren();
                                //}while(naechstes(kit));
                                //spinnen animieren
                                _corundspinne*csit;
                                if(anfang(csit))do{
                                 csit->animieren();
                                }while(naechstes(csit));
                                //figuren animieren
                                _corundfigur*cfit;
                                if(anfang(cfit))do{
                                 cfit->animieren();
                                }while(naechstes(cfit));
                                //steine animieren
                                if(anfang(osit))do{
                                 osit->animieren();
                                }while(naechstes(osit));
                                //objekte animieren
                                if(anfang(coit))do{
                                 coit->animieren();
                                }while(naechstes(coit));                     
                                //druckwellen animieren
                                _corunddruckwelle*cwit;
                                if(_listebasis<_corunddruckwelle>::anfang(cwit))do{
                                 cwit->animieren();
                                }while(_listebasis<_corunddruckwelle>::naechstes(cwit));
                                _listebasis<_corunddruckwelle>::loeschenmarkiert();
                                _vektor3<double> mk=mo->holen();
                                
                                
                                //kamerakontrolle
                                if((kb->shift())&&(kb->control()==false)) kamera->kam->bewegen(kb,mo,welt->animationsfaktor()); else{
                                 if(!kb->shift()){
                                  //steuerung umsetzen
                                  
                                  morelativ=mk;
                                  _vektor3<_tg> vadd(mk[0],0,-mk[1]);
                                  vadd*=0.0003241f;//*welt->animationsfaktor();
                                  L->l("Vadd = ",vadd);
                                  _tg impulsfaktor;
                                  if(anfang(kit))do{
                                   if(kit->steuerung){
                                   
                                   
                                   
                                    _listenknoten<_polygon>*lnpit;
                                    if(kit->_liste<_polygon>::anfang(lnpit)){
                                     do{
                                      //abgleitpolygon, impulsübertragung
                                      impulsfaktor=lnpit->objekt()->haftreibung() * kit->haftreibung();
                                      kit->vektor()+=vadd*impulsfaktor; 
                                    
                                      
                                     }while(kit->_liste<_polygon>::naechstes(lnpit));
                                    }else{
                                     //kurze impulsübertragung beim aufdotzen
                                     if(kit->schnittpunkt.polygon) kit->vektor()+=vadd*2;                                    
                                    };
                                   
                                   
                                   
                                   
                                   };
                                  }while(naechstes(kit));
                                  //kameraführung umsetzen
                                  kamera->animieren();
                                  
                                 };
                                 if(kb->control()){
                                  //_vektor3<double> mk=mo->holen();
                                  _vektor3<_tg> vadd(mk[0],-mk[1],0);
                                  vadd*=0.000324f;//*welt->animationsfaktor();
                                  if(spieler){
                                   spieler->vektor()+=vadd;
                                   
                                  };
                                 };
                                 //  L->l("kam->vektor =",*(kamera->kam));
                                 if(kb->taste(65)){
                                  _partition::_zone*zit;
                                  _partition::_sektor*sit;
                                  if(welt->anfang(zit))do{
                                   if(zit->anfang(sit))do{
                                    sit->visualisieren();
                                   }while(zit->naechstes(sit));
                                  }while(welt->naechstes(zit));
                                 };
                                };
                                
                                
                                //figuren löschen
                                if(spieler) {
                                 if(spieler->_listenknotenbasis<_corundkugel>::loeschmarkierung()){
                                  delete spieler;
                                  if(corundinventar) corundinventar->text="Ihre Kugel wurde zerstört.";
                                  spieler=0;
                                 };
                                };
                                _listebasis<_corundkugel>::loeschenmarkiert();
                                //objekte loeschen
                                _listebasis<_corundobjekt>::loeschenmarkiert();
                                //steine löschen
                                _listenknoten<_corundstein>*lncsit;
                                if(steinzumloeschen.anfang(lncsit))do{
                                 delete lncsit->objekt();
                                }while(steinzumloeschen.naechstes(lncsit));
                                steinzumloeschen.aushaengen();
                                
                                
                                //spezielle netz animation 
                                _polygon*pit;
                                if(spezial){
                                 if(spezial->anfang(pit))do{
                                  _vertex*vit;
                                  vit=pit->vertex();
                                  if(vit)do{
                                   _vektor3<_tg> v;
                                   v=vit->ort();
                                   v.setzenkomponente(1,sin(  (_tg(welt->zyklus())*0.1f)  +v[0]*16*_ph)*2 -2);
                                   vit->ort(v);
                                   vit=vit->naechstes(pit);
                                  }while(vit!=pit->vertex());
                                 }while(spezial->naechstes(pit));
                                 spezial->aktualisieren();
                                };
                                                                
                                //welt animieren
                                welt->animieren();
                                if(spieler){
                                 _vektor3<_tg> o=spieler->_kollidierbarkugel::ort();
                                 _vektor3<_tg> v=spieler->_kollidierbarkugel::vektor();
                                 sound->zuhoererort(_vektor3<>(o[0],o[1],o[2])); 
                                 sound->zuhoerergeschwindigkeit(_vektor3<>(v[0],v[1],v[2]));
                                };
                                sound->animieren((pzeit->system()-zeitanfang)/1000);
                                
                                //--------------------------------------zeichnen-----------------------------------------------
                               /* if(spieler){
                                 spieler->_kollidierbar::stammsektor()->zeichnen(gra,kam);
                                }else{
                                 welt->zeichnen(gra,kam); 
                                };*/
                                
                                kamera->kamerakugel->stammsektor()->zeichnen(gra,kamera->kam);
                                if(anfang(csit))do{
                                 csit->_skelett::visualisieren();
                                }while(naechstes(csit));
                                if(anfang(cfit))do{
                                 cfit->visualisieren();
                                }while(naechstes(cfit));
                                _corundfeder*cfedit;
                                _corundgummiband*cgubit;
                                if(anfang(cfedit))do{
                                 cfedit->zeichnen(gra);
                                }while(naechstes(cfedit));
                                if(anfang(cgubit))do{
                                 cgubit->zeichnen(gra);
                                }while(naechstes(cgubit));
                                if(corundinventar) corundinventar->zeichnen(gra);
                                //---------------------------------------------------------------------------------------------
                                //partikelkontrolle
                                psstaubwolke->aktiv(false);
                                pseinschlag->aktiv(false);
                                pskugeltot->aktiv(false);
                                if(strahldauer<=0) psstrahl->aktiv(false); else strahldauer-=1;
                                psrot->aktiv(false);
                                psfrage->aktiv(false);
                                gra->anzeigebufferumschalten();
                               // S->animieren();        
                                //skybox anpassen
                                //kam ort muss der mittelpunkt der skybox sein
                                //_vertex*vit;
                                //_polygon*pit;
                                _tg w=512;
                                if(skybox){
                                /* if(skybox->anfang(pit)){
                                  vit=pit->vertex();
                                  vit->setzen(*kam + _vektor3<_tg>(-w,-w,-w));
                                  vit=vit->naechstes(pit);
                                  vit->setzen(*kam + _vektor3<_tg>(+w,-w,-w));
                                  vit=vit->naechstes(pit);
                                  vit->setzen(*kam + _vektor3<_tg>(+w,-w,+w));
                                  vit=vit->naechstes(pit);
                                  vit->setzen(*kam + _vektor3<_tg>(-w,-w,+w));
                                  pit=pit->naechstes();
                                  vit=pit->vertex();
                                  vit->setzen(*kam + _vektor3<_tg>(-w,+w,-w));
                                  vit=vit->naechstes(pit);
                                  vit->setzen(*kam + _vektor3<_tg>(+w,+w,-w));
                                  vit=vit->naechstes(pit);
                                  vit->setzen(*kam + _vektor3<_tg>(+w,+w,+w));
                                  vit=vit->naechstes(pit);
                                  vit->setzen(*kam + _vektor3<_tg>(-w,+w,+w));
                                  skybox->aktualisieren();
                                 };*/
                                };
                                
                                
                                
                                //bremse
                                //for(double g=0;g<10e+4;g+=0.001) {};
                                
                                                                                         
};
void _corundwelt::deinitialisierenanimation(){
                                loeschendebugschirm();
};
void _corundwelt::erzeugendebugschirm(){
                                _vektor3<_tg> o0;
                                _vektor3<_tg> o1;
                                _vektor4<_to> col;
                                //---------------------
                                loeschendebugschirm();
                                o0.setzen(-0.53,0.07,1);
                                o1.setzen(+0.53,0.41,1);
                                col.setzen(1,1,1,0);
                                debugschirm=new _weltdebugschirm(welt,o0,o1,80,15,col);
                                col.setzen(0.99f,0.6f,0.65f,0);
                                if(debugschirm) debugschirm->schreiben("CORUND DEBUG SCHIRM",col);
};
void _corundwelt::loeschendebugschirm(){
                                if(debugschirm) delete debugschirm;
                                debugschirm=0;
};
void _corundwelt::erzeugenpartikelsysteme(){
                                loeschenpartikelsysteme();
                                psstaubwolke=new _partikelquellesprite(welt,welt,welt,pzeit,_vektor3<_tg>(-3,-1,-1),_vektor3<_tg>(-1,1,1),150,textur[8]);
                                psstaubwolke->name("psstaubwolke");
                                psstaubwolke->aktiv(false);
                                psstaubwolke->groesse(0.6);
                                psstaubwolke->generationsrate(100);
                                psstaubwolke->generationsratetoleranz(0.5);
                                psstaubwolke->groessetoleranz(0.5);
                                psstaubwolke->vektortoleranz(0.6);
                                psstaubwolke->rotation(0);
                                psstaubwolke->rotationtoleranz(0);
                                psstaubwolke->lebensdauerpartikeltoleranz(0.95);                                 
                               
                                psstrahl=new _partikelquellesprite(welt,welt,welt,pzeit,_vektor3<_tg>(-2,-1,-1),_vektor3<_tg>(-1,1,1),50,textur[15]);
                                psstrahl->name("psstrahl");
                                psstrahl->aktiv(false);
                                psstrahl->groesse(0.8);
                                psstrahl->generationsrate(5);
                                psstrahl->generationsratetoleranz(0.5);
                                psstrahl->groessetoleranz(0.5);
                                psstrahl->vektortoleranz(0.04);
                                psstrahl->rotation(0);
                                psstrahl->rotationtoleranz(0);
                                psstrahl->lebensdauerpartikeltoleranz(0.95);                                 
                                
                                psrot=new _partikelquellesprite(welt,welt,welt,pzeit,_vektor3<_tg>(-1,-1,-1),_vektor3<_tg>(0,0.5,0),150,textur[16]);
                                psrot->name("psrot");
                                psrot->aktiv(false);
                                psrot->groesse(0.5);
                                psrot->generationsrate(2000);
                                psrot->generationsratetoleranz(0.5);
                                psrot->groessetoleranz(0.5);
                                psrot->vektortoleranz(1.0);
                                psrot->rotation(0);
                                psrot->rotationtoleranz(0);
                                psrot->lebensdauerpartikeltoleranz(0.95);                                 

                                psfrage=new _partikelquellesprite(welt,welt,welt,pzeit,_vektor3<_tg>(0,-1,-1),_vektor3<_tg>(0,0.5,0),150,textur[40]);
                                psfrage->name("psfrage");
                                psfrage->aktiv(false);
                                psfrage->groesse(0.5);
                                psfrage->generationsrate(10);
                                psfrage->generationsratetoleranz(0.5);
                                psfrage->groessetoleranz(0.5);
                                psfrage->vektortoleranz(0.09);
                                psfrage->rotation(10);
                                psfrage->rotationtoleranz(1);
                                psfrage->lebensdauerpartikeltoleranz(0.95);   

                                pseinschlag=new _partikelquellesprite(welt,welt,welt,pzeit,_vektor3<_tg>(1,-1,-1),_vektor3<_tg>(0,0.5,0),10,textur[15]);
                                pseinschlag->name("pseinschlag");
                                pseinschlag->aktiv(false);
                                pseinschlag->groesse(0.1);
                                pseinschlag->generationsrate(100);
                                pseinschlag->generationsratetoleranz(0.5);
                                pseinschlag->groessetoleranz(0.5);
                                pseinschlag->vektortoleranz(0.6);
                                pseinschlag->rotation(0);
                                pseinschlag->rotationtoleranz(0);
                                pseinschlag->lebensdauerpartikeltoleranz(0.95);                                 

                                pskugeltot=new _partikelquellesprite(welt,welt,welt,pzeit,_vektor3<_tg>(2,-1,-1),_vektor3<_tg>(0,0.5,0),150,textur[15]);
                                pskugeltot->name("pskugeltot");
                                pskugeltot->aktiv(false);
                                pskugeltot->groesse(0.3);
                                pskugeltot->generationsrate(200);
                                pskugeltot->generationsratetoleranz(0.5);
                                pskugeltot->groessetoleranz(0.9);
                                pskugeltot->vektortoleranz(0.6);
                                pskugeltot->rotation(0);
                                pskugeltot->rotationtoleranz(0);
                                pskugeltot->lebensdauerpartikeltoleranz(0.95);                                 

};
bool _corundwelt::istinternepartikelquelle(_partikelquelle*p)const{
                                if(p==pskugeltot) return(true);
                                if(p==pseinschlag) return(true);
                                if(p==psstaubwolke) return(true);
                                if(p==psrot) return(true);
                                if(p==psfrage) return(true);
                                if(p==psstrahl) return(true);
                                return(false);
};
void _corundwelt::erzeugenskybox(){
                                _geometriequader*gb;
                                _netz*netz;
                                _vektor3<_tg> ort;
                                _vektor3<_to> farb;
                                _tg wx,wy,wz;
                                _polygon*pit;
                                //------------------------
                                wx=wy=wz=100;
                                ort.setzen(-wx/2.0f,-wy/2.0f,-wz/2.0f);
                                gb=new _geometriequader(welt,ort,wx,wy,wz,textur[17]);
                                gb->texturkoordinatenlaenge(1,1,1);
                                netz=gb->erzeugen();
                                netz->einhaengen(welt);
                                netz->verwendentextur(true); 
                                netz->markierungpolygon(1);
                                netz->subtraktiv(false);
                                netz->transparenzfaktor(0.0);
                                netz->verwendentextur(true);
                                netz->farbeverbinder(_vektor4<_to>(1,1,1,1));
                                netz->dynamischschattierend(false);
                                delete gb;
                                netz->anfang(pit);
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
                                skybox=netz;
                                
};
_netz* _corundwelt::erzeugenlichtnetz(_to r,_to g,_to b,_tg i,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_tg tks,_textur<_tb>*tex){
                                _geometriequader*gb;
                                _netz*netz;
                                _vektor3<_tg> ort;
                                _vektor3<_to> farb;
                                //------------------------
                                ort.setzen(x-wx/2.0f,y-wy/2.0f,z-wz/2.0f);
                                gb=new _geometriequader(welt,ort,wx,wy,wz,tex);
                                gb->texturkoordinatenlaenge(wx*tks,wy*tks,wz*tks);
                                netz=gb->erzeugen();
                                netz->einhaengen(welt);
                                netz->verwendentextur(true); 
                                netz->markierungpolygon(1);
                                netz->subtraktiv(false);
                                netz->transparenz(true);                                                                
                                netz->keinbsp(true);
                                netz->maskiert(true);
                                netz->zweiseitig(true);
                                netz->transparenzfaktor(0.0);
                                netz->verwendentextur(true);
                                netz->farbeverbinder(_vektor4<_to>(1,1,1,1));
                                delete gb;
                                return(netz);
};
_netz* _corundwelt::erzeugennetz(const _vektor3<_tg>&p,const _vektor3<_tg>&vex,const _vektor3<_tg>&vey,const _tg tks,_textur<_tb>*tex){ 
                               _polygon*pit;
                               _geometrienetz*gn=new _geometrienetz(welt,p,vex,vey,tex);
                               gn->texturkoordinatenlaenge(vex.laenge()*tks,vey.laenge()*tks);
                               gn->aufloesung(_vektor2<unsigned int>(1,1));
                               _netz*netz=gn->erzeugen();
                               netz->einhaengen(welt);
                               netz->verwendentextur(true); 
                               netz->markierungpolygon(1);
                               netz->subtraktiv(false);
                               netz->keinbsp(true);
                               netz->anfang(pit);
                               pit->anlegentexturkoordinaten(2);
                               pit->lightmaptexelgroesse(0.25);
                               //pit->anlegenlightmap("lightmap//lightmapnetz",0.25);//vorher:0.2);
                               netz->verwendentexturdynamisch(false);
                               netz->farbeverbinder(_vektor4<_to>(0,0,0,1));
                               netz->verwendentextur(true);
                               netz->aktualisieren();
                               _licht<_tg,_to>*lit;
                               if(welt->anfang(lit))do{
                                if(netz->anfang(pit))do{
                                 //pit->dynamischschattierend(true);
                                 //pit->erzeugenschatten(lit,400);
                                }while(netz->naechstes(pit)); 
                               }while(welt->naechstes(lit));
                               delete gn;
                               return(netz);
};
_netz* _corundwelt::erzeugennetz(const _vektor3<_tg>&p,const _vektor3<_tg>&vex,const _vektor3<_tg>&vey,const _tg tksx,const _tg tksy,_textur<_tb>*tex){ 
                               _polygon*pit;
                               _geometrienetz*gn=new _geometrienetz(welt,p,vex,vey,tex);
                               gn->texturkoordinatenlaenge(tksx,tksy);
                               gn->aufloesung(_vektor2<unsigned int>(1,1));
                               _netz*netz=gn->erzeugen();
                               netz->einhaengen(welt);
                               netz->verwendentextur(true); 
                               netz->markierungpolygon(1);
                               netz->keinbsp(true);
                               netz->subtraktiv(false);
                               netz->anfang(pit);
                               netz->farbeverbinder(_vektor4<_to>(0.5,0.5,0.5,1));
                               netz->verwendentextur(true);
                               netz->aktualisieren();
                               _licht<_tg,_to>*lit;
                               if(welt->anfang(lit))do{
                                if(netz->anfang(pit))do{
                                 //pit->dynamischschattierend(true);
                                 //pit->erzeugenschatten(lit,400);
                                }while(netz->naechstes(pit)); 
                               }while(welt->naechstes(lit));
                               delete gn;
                               return(netz);
};
_netz* _corundwelt::erzeugennetzspiegel(const _vektor3<_tg>&p,const _vektor3<_tg>&vex,const _vektor3<_tg>&vey,const _tg tks,_textur<_tb>*tex){ 
                               _partition::_zone*zit;
                               _polygon*pit;
                               _geometrienetz*gn=new _geometrienetz(welt,p,vex,vey,tex);
                               gn->texturkoordinatenlaenge(vex.laenge()*tks,vey.laenge()*tks);
                               _netz*netz=gn->erzeugen();
                               netz->einhaengen(welt);
                               netz->verwendentextur(true); 
                               netz->markierungpolygon(1);
                               netz->subtraktiv(false);
                               netz->keinbsp(true);
                               netz->anfang(pit);
                               pit->anlegentexturkoordinaten(2);
                               pit->lightmaptexelgroesse(1);
                               //pit->anlegenlightmap("lightmapnetz.tga",1);//vorher:0.2);
                               netz->verwendentexturdynamisch(true);
                               pit->transparenzfaktor(0.5);
                               pit->transparenz(true);
                               netz->verwendentextur(true);
                              // pit->spiegelnd(true);
                               netz->farbeverbinder(_vektor4<_to>(0,0,0,1));
                               delete gn;
                               return(netz);
};
void _corundwelt::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                d->loeschensektion(); 
                                welt->_material<_tg>::einhaengendialog(d);
                                d->addierensektion(L"corundwelt");
                                d->sektion(L"corundwelt")->offen(true);
                                d->einhaengen(L"corundwelt",L"Dateiname",speichername);
                                d->einhaengen(L"corundwelt",L"Name",name);
                                d->einhaengen(L"corundwelt",L"Verschiebung der Kamera",kameraverschiebung);
                                d->einhaengen(L"corundwelt",L"Federhärte der Kamera",kamerafederhaerte);
                                d->einhaengen(L"corundwelt",L"Ambientes Licht",ambientlicht);
                                d->einhaengen(L"corundwelt",L"Nebel",nebel);
                                d->einhaengen(L"corundwelt",L"Nebelmodus(0=exp,1=exp2,2=lin)",nebelmodus);                                
                                d->einhaengen(L"corundwelt",L"Nebelfarbe",nebelfarbe);
                                d->einhaengen(L"corundwelt",L"Nebeldichte",nebeldichte);
                                d->einhaengen(L"corundwelt",L"Nebeldistanz (min,max)",nebeldistanz);
                                
};
void _corundwelt::auslesendialog(_dynamischerdialog*d){
                                welt->_material<_tg>::auslesendialog(d);
                                d->auslesen(L"corundwelt",L"Dateiname",speichername);
                                d->auslesen(L"corundwelt",L"Name",name);
                                d->auslesen(L"corundwelt",L"Verschiebung der Kamera",kameraverschiebung);
                                d->auslesen(L"corundwelt",L"Federhärte der Kamera",kamerafederhaerte);
                                d->auslesen(L"corundwelt",L"Ambientes Licht",ambientlicht);         
                                d->auslesen(L"corundwelt",L"Nebel",nebel);
                                d->auslesen(L"corundwelt",L"Nebelmodus(0=exp,1=exp2,2=lin)",nebelmodus);
                                d->auslesen(L"corundwelt",L"Nebelfarbe",nebelfarbe);
                                d->auslesen(L"corundwelt",L"Nebeldichte",nebeldichte);
                                d->auslesen(L"corundwelt",L"Nebeldistanz (min,max)",nebeldistanz);
};
char _corundwelt::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundwelt>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(speichername);
                                r^=sd->ladenwert(name);
                                r^=sd->ladenwert(kameraverschiebung);
                                r^=sd->ladenwert(kamerafederhaerte);
                                r^=sd->ladenwert(ambientlicht);
                                r^=sd->ladenwert(nebel);
                                r^=sd->ladenwert(nebelmodus);
                                r^=sd->ladenwert(nebelfarbe);
                                r^=sd->ladenwert(nebeldichte);
                                r^=sd->ladenwert(nebeldistanz);
                                sd->ladenende();
                                return(r);
};
void _corundwelt::speichern(_speicherbardynamisch<_corundwelt>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();   
                                sd->speichernwert(speichername);
                                sd->speichernwert(name);
                                sd->speichernwert(kameraverschiebung);
                                sd->speichernwert(kamerafederhaerte);
                                sd->speichernwert(ambientlicht);
                                sd->speichernwert(nebel);
                                sd->speichernwert(nebelmodus);
                                sd->speichernwert(nebelfarbe);
                                sd->speichernwert(nebeldichte);
                                sd->speichernwert(nebeldistanz);
                                sd->speichernendeblock();
};
char _corundwelt::assoziieren(_speicherbardynamisch<_corundwelt>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);};




//******************************************************************************************************************************************************************************************************
//                              C O R U N D I N V E N T A R 
//******************************************************************************************************************************************************************************************************
_corundinventar::_corundinventar(_corundwelt*ow){
                                welt=ow;
                                text=".";
                                links=false;
                                textanimiert=false;
                                textx=1024+10;
                                textxd=-500;
                                rotx=0;
                                roty=0;
};
_corundinventar::~_corundinventar(){
};
void _corundinventar::aktualisieren(){
                                _corundobjekt*coit;
                                _tg x=2;
                                _vektor3<_tg> m;
                                _vektor3<_tg> z;
                                if(anfang(coit))do{
                                 m=coit->mitte();
                                 z.setzen(0,0,0);
                                 coit->verschiebenvertex(z-m);
                                 x+=1;
                                }while(naechstes(coit));
};
void _corundinventar::einhaengenobjekt(_corundobjekt*c){
                                c->_listenknotenbasis<_corundobjekt>::einhaengen(this);//_listebasis<_corundobjekt>::einhaengen(c);
                                _listebasis<_corundobjekt>::rotierenvorheriges();
                                aktualisieren();
};

void _corundinventar::animieren(){
                                _win::_tastatur t; 
                                if(textanimiert){
                                 //if(t.knopflinks()) textanimiert=false;
                                 textx-=5;
                                 if(textx<textxd) {
                                  textanimiert=false;
                                  text="";
                                 };
                                };
                                _corundobjekt*coit;
                                if(anfang(coit))do{
                                 coit->animieren();
                                }while(naechstes(coit));
                                _listebasis<_corundobjekt>::loeschenmarkiert();
                                rotx+=2;
                                roty+=0.311321;
                                
                                
                                if(t.knopflinks()) {
                                 if(links==false){
                                  links=true;
                                  _corundobjekt*erstes;
                                  if(_listebasis<_corundobjekt>::anfang(erstes)){
                                   if(welt->spieler){
                                    erstes->ablegen(welt->spieler->_kollidierbarkugel::ort()-_vektor3<_tg>(0,welt->spieler->_kollidierbarkugel::radius(),0));
                                    aktualisieren();
                                   };
                                  };
                                 };
                                }else links=false;
};
void _corundinventar::loeschenerstes(){
                                _corundobjekt*erstes;
                                if(_listebasis<_corundobjekt>::anfang(erstes)){
                                 delete erstes;
                                 aktualisieren();
                                };
};
void _corundinventar::textanimation(_zeichenkette<char> t){
                                textx=welt->grafikx+10;
                                textanimiert=true;
                                text=t;
                                int bx,by;
                                welt->zeichensatz->breite(text,bx,by);
                                textxd=-bx-10;
                                
};
void _corundinventar::zeichnen(_grafik*gra){
                         /*       glMatrixMode(GL_PROJECTION);                                  
                                glPushMatrix();
                                glLoadIdentity();         
                                glMatrixMode(GL_MODELVIEW);  
                                glPushMatrix();
                                glLoadIdentity();  
                                //---------------------------------- text und fläche zeichnnen -------------
	                            glOrtho(0, gra->groessex(), 0,gra->groessey(), -100, 100);
	                            glDisable(GL_DEPTH_TEST);
	                            glDisable(GL_STENCIL_TEST);
	                            glEnable(GL_BLEND);
	                            glDisable(GL_CULL_FACE);
	                            glDisable(GL_LIGHTING);
	                            glDisable(GL_TEXTURE_2D);
 	                            glBegin(GL_QUADS);
                                 glColor4f(0.03f, 0.03f, 0.04f, 0.03);
		                         glVertex3f(0 , 0, 1);
		                         glVertex3f(gra->groessex(), 0, 1);
		                         glVertex3f(gra->groessex(),60, 1);
		                         glVertex3f(0, 60, 1);
	                            glEnd();
	                            if(textanimiert){
	                          //   gra->text(text,welt->zeichensatz,_vektor3<_tg>(textx,gra->groessey()-50,1),_vektor4<_to>(1,1,1,0.5)); 
	                            }else{
	                          //   gra->text(text,welt->zeichensatz,_vektor3<_tg>(10,gra->groessey()-50,1),_vektor4<_to>(0.5,0.5,0.5,0.2)); 
	                            };
                                if(welt->spieler){
	                             char buf[1024];
	                             sprintf(buf, "%f.5", welt->spieler->gesundheit*100);//gcvt(welt->spieler->gesundheit*100,,buf);
	                             _zeichenkette<char> hh=buf;
	                             hh+="%";
	                            // gra->text(hh,welt->zeichensatz,_vektor3<_tg>(gra->groessex()-100,10,1),_vektor4<_to>(0.5,0.5,0.5,0.2)); 
	                            };
	                            glEnable(GL_DEPTH_TEST);
	                            glEnable(GL_CULL_FACE);
	                            glDisable(GL_BLEND);
	                            glEnable(GL_TEXTURE_2D);
	                            //------------------------------ objekte zeichnen -------------------------
	                            _corundobjekt*coit;
	                            _netz*nit;
	                            _sprite*spit;
	                            _polygon*pit;
	                            _tg x=0;
	                            if(anfang(coit))do{
	                             nit=coit;
                                 glMatrixMode(GL_PROJECTION);                                  
                                 glLoadIdentity();  
                                 glMatrixMode(GL_MODELVIEW);  
                                 glLoadIdentity();         
	                             glOrtho(0, gra->groessex(), 0,gra->groessey(), -100, 100);
	                             glTranslatef(16+x*40,32,0);
	                             glScalef(40,40,1);
	                             glRotatef(rotx,0,1,0);
	                           //  glRotatef(roty,1,0,0);
	                             if(nit->anfang(pit))do{
	                              pit->zeichnen(gra);
	                             }while(nit->naechstes(pit));
	                             if(coit->anfang(spit))do{
	                              spit->zeichnen(gra,0);
	                             }while(coit->naechstes(spit));
	                             x+=1;
	                            }while(naechstes(coit));
	                            glEnable(GL_LIGHTING);
                                glMatrixMode(GL_PROJECTION);                                  
                                glPopMatrix();
                                glMatrixMode(GL_MODELVIEW);  
                                glPopMatrix();*/
}; 
//******************************************************************************************************************************************************************************************************
//                              C O R U N D T O N 
//******************************************************************************************************************************************************************************************************
_corundton::_corundton(_corundwelt*ow,_ton*s,const _vektor3<_tg>&o,const _vektor3<_tg>&v){
                                welt=ow;
                                ort=o;
                                vektor=v;
                                ton=s;
                                lautstaerke=1;
                                schleife=false;
                                radius=20;
                                distanzlautstaerke=true;
                                beugung=1;
};
_corundton::~_corundton(){
};
void _corundton::abspielen(){
                                 ton->lautstaerke(lautstaerke);
                                 ton->schleife(schleife);
                                 ton->beugung(beugung);
                              //   ton->abspielen();
                                /* if(source) { 
                                 
                                  source->Loop(schleife); 
                                  source->Gain(lautstaerke); 
                                  source->Pitch(beugung);
                                  source->Position(ort[0], ort[1], ort[2]);
                                  source->Velocity(vektor[0],vektor[1],vektor[2]);
                                  source->DistanceAttenuation(distanzlautstaerke); 
                                  source->MaxDistance(radius);                                   
                                  source->Play(sample);      
                                                  
                                 };*/
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D K A M E R A
//******************************************************************************************************************************************************************************************************
_corundkamera::_corundkamera(_corundwelt*ow){
                                corundwelt=ow;
                                
                                kam=new _kamera<_tg>(corundwelt->welt);  
                                kam->yaw(0);
                                kam->rot(0);            
                                kurvenmodus=false;
                                standmodus=false;
                                kurvenparameter=0;
                                kurvenschritt=0.01;
                                kamerakugel=0;
                                aktualisieren();
                                
                                
};
_corundkamera::~_corundkamera(){
};
void _corundkamera::aktualisieren(){
                                if(corundwelt->spieler){   
                                 kam->setzen(corundwelt->spieler->_kollidierbarkugel::ort()+_vektor3<_tg>(0,1,0));
                                 _partition::_zone*zit;
                                 _partition::_sektor*sit;
                                 if(corundwelt->welt->anfang(zit)){
                                  sit=zit->sektor(corundwelt->spieler->_kollidierbarkugel::ort()+corundwelt->kameraverschiebung);
                                  kamerakugel=new _kollidierbarkugel(0,corundwelt->welt,zit,sit,corundwelt->spieler->_kollidierbarkugel::ort()+_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,0),0.1);
                                  kamerakugel->kollisionintern(false);
                                  kamerakugel->ort(*kam);

                                 }else{
                                  L->schreiben("Warnung : Für die Kamerakugel konnte keine Zone bestimmt werden.");
                                 };
                                };
};
void _corundkamera::animieren(){
                                if(standmodus==false){
                                 if(kurvenmodus==false){
                                  if(corundwelt->spieler){
                                   _vektor3<_tg> h;
                                   
                                   
                                   _vektor3<_tg> hv;
                                   _vektor3<_tg> hk;
                                   _tg hvl;
                                   _tg kl=corundwelt->kameraverschiebung.laenge();
                                   
                                   hv=corundwelt->spieler->_kollidierbarkugel::ort()-*kam;
                                   hvl=hv.laenge();
                                   
                                   if(hvl>(kl*1.5)){
                                    h=(corundwelt->spieler->_kollidierbarkugel::ort()+corundwelt->kameraverschiebung)-*kam;
                                    hk=-corundwelt->kameraverschiebung;
                                    hk.normalisieren();
                                    hk*=(hvl/(kl*1.5));
                                    h+=hk;
                                   }else{
                                   
                                    h=(corundwelt->spieler->_kollidierbarkugel::ort()+corundwelt->kameraverschiebung)-*kam;
                                   };
                                   h*=corundwelt->kamerafederhaerte;
                                   kamerakugel->vektor(h);
                                   kamerakugel->bewegen(_vektor3<_tg>(0,0,0));
                                   kam->setzen(kamerakugel->ort());
                                   
                                   
                                  
                                   
                                   
                                   
                                   _vektor3<_tg> v=corundwelt->spieler->_kollidierbarkugel::ort()-*kam;
                                   /*_vektor3<_tg> xa(1,0,0);
                                   _vektor3<_tg> ya(0,1,0);
                                   _vektor3<_tg> za(0,0,1);
                                   _vektor3<_tg> e0,e0yaw,e0rot;
                                   _vektor3<_tg> e1,e1yaw,e1rot;
                                   
                                   _vektor3<_tg> von;
                                   vyz.normalisieren();
                                   e1yaw=vzy%xa;
                                   e1rot=za;
                                   e1=(e1yaw+e1rot)*0.5f;
                                   */
                                   
                                   
                                   _vektor2<_tg> v2;
                                   //die rotation um z bestimmen (=wz)
                                   //dazu den winkel zwischen v und -ya bestimmen
                                   //betrachtung in der xy ebene
                                   v2.setzen(v[0],v[1]);
                                   _tg wz=v2.winkel(_vektor2<_tg>(0,-1));
                                   if((_vektor2<_tg>(1,0)*v2)<0) wz*=-1;
                                   //die rotation um x bestimmen (=wx)
                                   //dazu den winkel zwischen v und -ya bestimmen
                                   //betrachtung in der zy ebene
                                   v2.setzen(v[2],v[1]);
                                   _tg wx=v2.winkel(_vektor2<_tg>(0,-1));
                                   if((_vektor2<_tg>(1,0)*v2)>0) wx*=-1;
                              /*     
                                   if(wx>89) wx=89;
                                   if(wz>89) wz=89;
                                   if(wx<-89) wx=-89;
                                   if(wz<-89) wz=-89;
                                */   
                                   wx*=0.5;
                                   wz*=0.5;
                                   
                                   v.setzen(0,-1,0);
                                   v.rotz(wz);
                                   v.rotx(wx);
                                   
                                   
                                   _vektor3<_tg> e0(1,0,0);
                                   e0.rotz(wz);
                                   e0.rotx(wx);
                                   
                                   kam->vektorebene0(v,e0);
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   
                                   //kam->ebene0((_vektor3<_tg>(1,0,0)+kam->ebenenormalisiert(0))*0.5f);
                                   //kam->vektor(v);
                                  // kam->yaw(-90+h[2]*10);
                                 //  kam->rot(0/*+h[0]*10*/);
                                   kam->aktualisieren();
                                  };
                                 };
                                 if(kurvenmodus){
                                  kurvenparameter+=kurvenschritt;
                                  if(kurvenparameter>1) {
                                   kurvenmodus=false; 
                                   kurvenparameter=0;
                                  // kamerakugel->ort(*kam);
                                  }else{
                                   kam->setzen(kurve.berechnen(kurvenparameter));
                                   kam->vektor(richtung.berechnen(kurvenparameter));
                                   kam->ebene0(ebene0.berechnen(kurvenparameter));
                                   //L->schreiben("kam vektor nachher=",kam->vektor());
                                   kam->aktualisieren();
                                  };
                                 };
                                }else{
                                 _vektor3<_tg> o=*kam;
                                 kam->bewegen(corundwelt->kb,corundwelt->morelativ*0.1,1);
                                 kam->setzen(o);
                                 
                                };
};
//******************************************************************************************************************************************************************************************************
//                               C O R U N D L I C H T V E R W A L T U N G
//******************************************************************************************************************************************************************************************************
_corundlichtverwaltung::_corundlichtverwaltung(){
};
_corundlichtverwaltung::~_corundlichtverwaltung(){
                                polylisten.loeschen();
                                laengen.loeschen();
};
void _corundlichtverwaltung::einhaengenzumloeschen(_licht<_tg,_to>*l){
                                loeschliste.einhaengen(l);
};
void _corundlichtverwaltung::einhaengenzumschattieren(_liste< ::_polygon>*lp,_licht<_tg,_to>*l,_tg la){
                                polylisten.einhaengen(lp);
                                lichtliste.einhaengen(l);
                                _tg*lae=new _tg;
                                *lae=la;
                                laengen.einhaengen(lae);
};
void _corundlichtverwaltung::loeschen(){
                                loeschliste.loeschen();
};
void _corundlichtverwaltung::schattieren(){
                                _listenknoten<_licht<_tg,_to> >*lit;
                                _listenknoten<_liste<_polygon> >*tit;
                                _listenknoten<_tg>*dit;
                                //-----------------------------------
                                if(polylisten.anfang(tit)){
                                 lichtliste.anfang(lit);
                                 laengen.anfang(dit);
                                 do{
                                  _listenknoten<_polygon>*pit;
                                  if(tit->objekt()->anfang(pit))do{
                                   bool ks=lit->objekt()->schattenvolumen();
                                   lit->objekt()->schattenvolumen(true);
                                   pit->objekt()->erzeugenschatten(lit->objekt(),*(dit->objekt()));
                                   //pit->objekt()->visualisieren();
                                   lit->objekt()->schattenvolumen(ks);
                                  }while(tit->objekt()->naechstes(pit));
                                  
                                  laengen.naechstes(dit);
                                  lichtliste.naechstes(lit);
                                 }while(polylisten.naechstes(tit));
                                };
};

//******************************************************************************************************************************************************************************************************
//                               C O R U N D K N O T E N   
//******************************************************************************************************************************************************************************************************
_corundknoten::_corundknoten(_corundwelt*ow,const _vektor3<_tg>&o,const unsigned int i):_listenknotenbasis<_corundknoten>(ow){
                                                                ort=o;
                                                                vektorankunft.setzen(0,0,0);
                                                                vektorabfahrt.setzen(0,0,0);
                                                                index=i;
                                                                wartezeit=100;
};
_corundknoten::~_corundknoten(){
};
char _corundknoten::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundknoten>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(index);
                                                                r^=sd->ladenwert(ort);
                                                                r^=sd->ladenwert(vektorankunft);
                                                                r^=sd->ladenwert(vektorabfahrt);
                                                                r^=sd->ladenwert(wartezeit);
                                                                sd->ladenende();
                                                                return(r);
};
void _corundknoten::speichern(_speicherbardynamisch<_corundknoten>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(index);
                                                                sd->speichernwert(ort);
                                                                sd->speichernwert(vektorankunft);
                                                                sd->speichernwert(vektorabfahrt);
                                                                sd->speichernwert(wartezeit);
                                                                sd->speichernendeblock();
};
char _corundknoten::assoziieren(_speicherbardynamisch<_corundknoten>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
void _corundknoten::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->loeschensektion(); 
                                                                d->addierensektion(L"Allgemein");
                                                                d->sektion(L"Allgemein")->offen(true);
                                                                d->einhaengen(L"Allgemein",L"Index",index);
                                                                d->einhaengen(L"Allgemein",L"Position",ort);
                                                                d->einhaengen(L"Allgemein",L"Richtung der Ankunft",vektorankunft);
                                                                d->einhaengen(L"Allgemein",L"Richtung der Abfahrt",vektorabfahrt);
                                                                d->einhaengen(L"Allgemein",L"Wartezeit [zyklen]",wartezeit);
};
void _corundknoten::auslesendialog(_dynamischerdialog*d){
                                                                d->auslesen(L"Allgemein",L"Index",index);
                                                                d->auslesen(L"Allgemein",L"Position",ort);
                                                                d->auslesen(L"Allgemein",L"Richtung der Ankunft",vektorankunft);
                                                                d->auslesen(L"Allgemein",L"Richtung der Abfahrt",vektorabfahrt);
                                                                d->auslesen(L"Allgemein",L"Wartezeit [zyklen]",wartezeit);
};
//******************************************************************************************************************************************************************************************************
//                               C O R U N D L I C H T 
//******************************************************************************************************************************************************************************************************
_corundlicht::_corundlicht(_corundwelt*cw,_listebasis<_licht<_tg,_to> >*l,const _vektor3<_tg> o,const _vektor3<_to> f,const _to i):_listenknotenbasis<_corundlicht>(cw),_licht<_tg,_to>(l,o,f,i),_corundschaltkopplung(cw){
                                welt=cw;
                                int k,p;
                                animiert=false;
                                iterator=0;
                                for(p=0;p<4;p++) for(k=0;k<3;k++) {
                                 periodisch[p][k]=true;
                                 xoffset[p][k]=0.5;
                                 yoffset[p][k]=0.5;
                                 xfaktor[p][k]=1;
                                 yfaktor[p][k]=1;
                                 methode[p][k]=0;
                                };            
};
_corundlicht::_corundlicht(const _corundlicht*cl):_listenknotenbasis<_corundlicht>(cl->welt),_licht<_tg,_to>(cl),_corundschaltkopplung(cl->welt){
                                welt=cl->welt;
                                int k,p;
                                animiert=cl->animiert;
                                iterator=cl->iterator;
                                for(p=0;p<4;p++) for(k=0;k<3;k++) {
                                 periodisch[p][k]=cl->periodisch[p][k];
                                 xoffset[p][k]=cl->xoffset[p][k];
                                 yoffset[p][k]=cl->yoffset[p][k];
                                 xfaktor[p][k]=cl->xfaktor[p][k];
                                 yfaktor[p][k]=cl->yfaktor[p][k];
                                 methode[p][k]=cl->methode[p][k];
                                };            
                                
};
_corundlicht::~_corundlicht(){
};
void _corundlicht::kopieren(_licht<_tg,_to>*&cl)const{
                                cl=new _corundlicht(this);
};
void _corundlicht::schalten(){
                                animiert=!animiert;
};
void _corundlicht::animieren(){
                                if(animiert){
                                 int k,p;
                                 _tg x;
                                 bool setz;
                                 iterator+=0.001;
                                 for(p=0;p<4;p++) for(k=0;k<3;k++) {
                                  x=0;
                                  setz=false;
                                  switch(methode[p][k]){
                                   case 1:
                                   x=sin((iterator*xfaktor[p][k]+xoffset[p][k])*_ph)*yfaktor[p][k]+yfaktor[p][k]; 
                                   setz=true;
                                   break;
                                   case 2:
                                   x=iterator*xfaktor[p][k]+xoffset[p][k];
                                   int i=x;
                                   i%=2;
                                   x=_tg(i)*yfaktor[p][k]+yoffset[p][k]; 
                                   setz=true;
                                   break;
                                  };
                                  
                                  if(setz){
                                   if(p==0) {
                                    if(k==0) ort(_vektor3<_tg>(x,ort()[1],ort()[2]));
                                    if(k==1) ort(_vektor3<_tg>(ort()[0],x,ort()[2]));
                                    if(k==2) ort(_vektor3<_tg>(ort()[0],ort()[1],x));
                                   };
                                   if(p==1) {
                                    if(k==0) farbedynamisch(_vektor3<_to>(_to(x),farbedynamisch()[1],farbedynamisch()[2]));
                                    if(k==1) farbedynamisch(_vektor3<_to>(farbedynamisch()[0],_to(x),farbedynamisch()[2]));
                                    if(k==2) farbedynamisch(_vektor3<_to>(farbedynamisch()[0],farbedynamisch()[1],_to(x)));
                                   };
                                   if(p==2) {
                                    if(k==0) farbeglanz(_vektor3<_to>(_to(x),farbeglanz()[1],farbeglanz()[2]));
                                    if(k==1) farbeglanz(_vektor3<_to>(farbeglanz()[0],_to(x),farbeglanz()[2]));
                                    if(k==2) farbeglanz(_vektor3<_to>(farbeglanz()[0],farbeglanz()[1],_to(x)));
                                   };
                                   if(p==3) if(k==0) intensitaetdynamisch(_to(x));
                                  };
                                  
                                 };
                                };
};
char _corundlicht::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundlicht>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(animiert);
                                r^=sd->ladenwert(iterator);
                                int k,p;
                                for(p=0;p<4;p++) for(k=0;k<3;k++) {
                                 r^=sd->ladenwert(periodisch[p][k]);
                                 r^=sd->ladenwert(xoffset[p][k]);
                                 r^=sd->ladenwert(yoffset[p][k]);
                                 r^=sd->ladenwert(xfaktor[p][k]);
                                 r^=sd->ladenwert(yfaktor[p][k]);
                                 r^=sd->ladenwert(methode[p][k]);
                                };            
                                sd->ladenende();
                                return(r);
};
void _corundlicht::speichern(_speicherbardynamisch<_corundlicht>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(animiert);
                                sd->speichernwert(iterator);
                                int k,p;
                                for(p=0;p<4;p++) for(k=0;k<3;k++) {
                                 sd->speichernwert(periodisch[p][k]);
                                 sd->speichernwert(xoffset[p][k]);
                                 sd->speichernwert(yoffset[p][k]);
                                 sd->speichernwert(xfaktor[p][k]);
                                 sd->speichernwert(yfaktor[p][k]);
                                 sd->speichernwert(methode[p][k]);
                                };            
                                sd->speichernendeblock();
};
char _corundlicht::assoziieren(_speicherbardynamisch<_corundlicht>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundlicht::einhaengendialog(_dynamischerdialog*d){
                                _licht<_tg,_to>::einhaengendialog(d);
                                d->addierensektion(L"Corundlicht");
                                d->sektion(L"Allgemein")->offen(true);
                                d->sektion(L"Corundlicht")->offen(true);
                                d->einhaengen(L"Corundlicht",L"Animiert",animiert);
                                int k,p;
                                _vektor4<_tg> h;
                                
                                d->einhaengen(L"Corundlicht",L"Position x : Methode [0..7]",methode[0][0]);p=0;k=0;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Position x : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Position y : Methode [0..7]",methode[0][1]);p=0;k=1;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Position y : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Position z : Methode [0..7]",methode[0][2]);p=0;k=2;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Position z : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Farbe rot : Methode [0..7]",methode[1][0]);p=1;k=0;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Farbe rot : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Farbe grün : Methode [0..7]",methode[1][1]);p=1;k=1;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Farbe grün : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Farbe blau : Methode [0..7]",methode[1][2]);p=1;k=2;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Farbe blau : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Glanz rot : Methode [0..7]",methode[2][0]);p=2;k=0;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Glanz rot : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Glanz grün : Methode [0..7]",methode[2][1]);p=2;k=1;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Glanz grün : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Glanz blau : Methode [0..7]",methode[2][2]);p=2;k=2;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Glanz blau : xfak,xoff,yfak,yoff",h);
                                d->einhaengen(L"Corundlicht",L"Intensitaet : Methode [0..7]",methode[3][0]);p=3;k=0;h.setzen(xfaktor[p][k],xoffset[p][k],yfaktor[p][k],yoffset[p][k]);
                                d->einhaengen(L"Corundlicht",L"Intensitaet : xfak,xoff,yfak,yoff",h);

};
void _corundlicht::auslesendialog(_dynamischerdialog*d){
                                _licht<_tg,_to>::auslesendialog(d);
                                _vektor4<_tg> h;
                                int p,k;
                                d->auslesen(L"Corundlicht",L"Animiert",animiert);
                                
                                d->auslesen(L"Corundlicht",L"Position x : Methode [0..7]",methode[0][0]);
                                d->auslesen(L"Corundlicht",L"Position x : xfak,xoff,yfak,yoff",h);p=0;k=0;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Position y : Methode [0..7]",methode[0][1]);
                                d->auslesen(L"Corundlicht",L"Position y : xfak,xoff,yfak,yoff",h);p=0;k=1;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Position z : Methode [0..7]",methode[0][2]);
                                d->auslesen(L"Corundlicht",L"Position z : xfak,xoff,yfak,yoff",h);p=0;k=2;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Farbe rot : Methode [0..7]",methode[1][0]);
                                d->auslesen(L"Corundlicht",L"Farbe rot : xfak,xoff,yfak,yoff",h);p=1;k=0;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Farbe grün : Methode [0..7]",methode[1][1]);
                                d->auslesen(L"Corundlicht",L"Farbe grün : xfak,xoff,yfak,yoff",h);p=1;k=1;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Farbe blau : Methode [0..7]",methode[1][2]);
                                d->auslesen(L"Corundlicht",L"Farbe blau : xfak,xoff,yfak,yoff",h);p=1;k=2;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Glanz rot : Methode [0..7]",methode[2][0]);
                                d->auslesen(L"Corundlicht",L"Glanz rot : xfak,xoff,yfak,yoff",h);p=2;k=0;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Glanz grün : Methode [0..7]",methode[2][1]);
                                d->auslesen(L"Corundlicht",L"Glanz grün : xfak,xoff,yfak,yoff",h);p=2;k=1;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Glanz blau : Methode [0..7]",methode[2][2]);
                                d->auslesen(L"Corundlicht",L"Glanz blau : xfak,xoff,yfak,yoff",h);p=2;k=2;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
                                d->auslesen(L"Corundlicht",L"Intensitaet : Methode [0..7]",methode[3][0]);
                                d->auslesen(L"Corundlicht",L"Intensitaet : xfak,xoff,yfak,yoff",h);p=3;k=0;xfaktor[p][k]=h[0];xoffset[p][k]=h[1];yfaktor[p][k]=h[2];yoffset[p][k]=h[3];
};
//******************************************************************************************************************************************************************************************************
//                               C O R U N D D R U C K W E L L E 
//******************************************************************************************************************************************************************************************************
_corunddruckwelle::_corunddruckwelle(_corundwelt*cw,const _vektor3<_tg>&o,const _tg s,const _tg v,const unsigned int d):_listenknotenbasis<_corunddruckwelle>(cw){
                                grav=new _gravitation<_tg>(cw->welt,_vektor3<_tg>(0,0,0),0);
                                geschwindigkeit=v;
                                grav->blase(o,0.1,s);
                                dauer=d;
};
_corunddruckwelle::~_corunddruckwelle(){
                                delete grav;
};
void _corunddruckwelle::animieren(){
                                if(dauer>0) dauer--;
                                grav->blaseradius(0,grav->blaseradius(0)+geschwindigkeit);
                                if(dauer==0) loeschmarkierung(true);
};

