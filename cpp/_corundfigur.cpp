//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundfigur.cpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include "../hpp/_corundfigur.hpp"

//******************************************************************************************************************************************************************************************************
//                              C O R U N D F I G U R
//******************************************************************************************************************************************************************************************************
_corundfigur::_corundfigur(_corundwelt*cw):_listenknotenbasis<_corundfigur>(cw),_corundschaltkopplung(cw){
                                corundwelt=cw;
                                welt=corundwelt->welt;
};
_corundfigur::~_corundfigur(){
};
void _corundfigur::netzwahl(_netz*,int){
};
void _corundfigur::knotenwahl(_corundknoten*,int){
};
void _corundfigur::figurwahl(_corundfigur*,int){
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D K U G E L
//******************************************************************************************************************************************************************************************************
_corundkugel::_corundkugel(_corundwelt*ow,const _vektor3<_tg>&o,const _vektor3<_tg>&v,const _tg r,const _vektor4<_to>& f):_corundfigur(ow),_listenknotenbasis<_corundkugel>(ow),_kollidierbarkugel(this,ow->welt,o,v,r),_kugel(ow->welt,ow->welt,o,r,f,32){
                                corundwelt=ow;
                                farbe=f;
                                ladung=0;
                                gravitation=0;
                                steuerung=false;
                                augenmodus=false;
                                killer=false;
                                chaotischervektor=false;
                                chaotischerfaktor=0.02;
                                spieler=false;
                                zumspielervektor=false;
                                gesundheit=1;
                                tauchen=false;
                                inlava=false;
                                tauchzaehler=0;
                                //abgleitpolygon=0;
                                _partition::_zone*z;
                                _partition::_sektor*s;
                                if(corundwelt->welt->anfang(z)){
                                 s=z->sektor(o);
                                 zone(z);
                                 stammsektor(s);
                                 //_vektor3<_tg> h;
                                 _licht<_tg,_to>*lit;
                                 _partition::_sektor*sit;
                                 if(z->anfang(sit))do{
                                  if(sit->anfang(lit))do{
                                   erzeugenschatten(lit,500);
                                  }while(sit->naechstes(lit));
                                 }while(z->naechstes(sit));
                                }else{ 
                                 L->schreiben("Warnung : Für eine corundkugel konnte keine zone Bestimmt werden");
                                };
                                //für editor
                                dialog=0;
                                hauptfenster=0;
                                editorgummifarbe.setzen(1,1,1,0.5);
                                editorgummikoordinate.setzen(0,10,0);
                                editorgummistaerke=0.001;
                                editorfederfarbe.setzen(1,1,1,0.5);
                                editorfederkoordinate.setzen(10,0,0);
                                editorfederstaerke=0.001;
                                
                                dbvektor=0;
                                dbgrav=0;
                                dbort=0;
                               // h.setzen(ort()[0],ort()[1],ort()[2]);
                               // ws=new _weltdebugkugel(welt->welt,h,radius(),_vektor4<float>(1,1,1,0));
                               // ws->farbe(pfarbe);                                
};
_corundkugel::~_corundkugel(){
                                loeschengummiband();
                                loeschenfeder();
                                loeschendebug();
};
void _corundkugel::initialisieren(){
                                if(spieler) corundwelt->spieler=this;
                                _partition::_zone*zit;
                                _partition::_sektor*sit;
                                _licht<_tg,_to>*lit;
                                if(corundwelt->welt->anfang(zit))do{
                                 if(zit->anfang(sit))do{
                                  if(sit->anfang(lit))do{
                                   erzeugenschatten(lit,500);
                                  }while(sit->naechstes(lit));
                                 }while(zit->naechstes(sit));
                                }while(corundwelt->welt->naechstes(zit));
                                //*****DEBUG******
                                loeschendebug();
                                dbvektor=new _weltdebugtext(corundwelt->welt,"Vektor = ",_vektor2<_tg>(10,660),_vektor4<_to>(1,1,1,1));
                                dbgrav=new _weltdebugtext(corundwelt->welt,"Grav = ",_vektor2<_tg>(10,630),_vektor4<_to>(1,1,1,1));
                                dbort=new _weltdebugtext(corundwelt->welt,"Ort = ",_vektor2<_tg>(10,600),_vektor4<_to>(1,1,1,1));
                                //****************
};
void _corundkugel::zerstoeren(){
                                _listenknotenbasis<_corundkugel>::loeschmarkierung(true);
                                corundwelt->pskugeltot->ort(_kollidierbarkugel::ort());
                                corundwelt->pskugeltot->aktiv(true);
                                corundwelt->explosion->abspielen();
                                _kollidierbarkugel::aktivitaet(false);
};
void _corundkugel::abziehengesundheit(const _tg t){
                                gesundheit-=t;
                                if(gesundheit<=0) zerstoeren();
};
void _corundkugel::loeschengummiband(){
                                _listenknoten<_corundgummiband>*it;
                                _corundgummiband*og;
                                _corundstein*os;
                                _corundkugel*ok;
                                if(_liste<_corundgummiband>::anfang(it))do{
                                 os=0;
                                 ok=0;
                                 og=it->objekt();
                                 if(og->kugel==this) {
                                  if(og->kugel2) ok=og->kugel2; else os=og->stein;
                                 }else
                                 if(og->kugel2==this){
                                  ok=og->kugel;
                                 };
                                 if(ok) ok->_liste<_corundgummiband>::aushaengen(og);
                                 if(os) os->_liste<_corundgummiband>::aushaengen(og);
                                 
                                }while(_liste<_corundgummiband>::naechstes(it));
                                _liste<_corundgummiband>::loeschen();
};
void _corundkugel::loeschenfeder(){
                                _listenknoten<_corundfeder>*it;
                                _corundfeder*og;
                                _corundstein*os;
                                _corundkugel*ok;
                                if(_liste<_corundfeder>::anfang(it))do{
                                 os=0;
                                 ok=0;
                                 og=it->objekt();
                                 if(og->kugel==this) {
                                  if(og->kugel2) ok=og->kugel2; else os=og->stein;
                                 }else
                                 if(og->kugel2==this){
                                  ok=og->kugel;
                                 };
                                 if(ok) ok->_liste<_corundfeder>::aushaengen(og);
                                 if(os) os->_liste<_corundfeder>::aushaengen(og);
                                 
                                }while(_liste<_corundfeder>::naechstes(it));
                                _liste<_corundfeder>::loeschen();
};
void _corundkugel::animieren(){
                                _vektor3<_tg> grav;
                                _vektor3<_tg> drehgrav;
                                _vektor3<_tg> n;
                                _tg f,d,s;
                                _corundkugel*kit;
                                //------------------------------gravitationskraft---------------------------------------
                                grav=corundwelt->welt->gravitation(_kollidierbarkugel::ort());
                                //----------------------------Magnetische Feldkraft-------------------------------------
                                if(ladung!=0){
                                 _feldmagnetostatisch<_tg> * fmit;
                                 if(corundwelt->welt->anfang(fmit))do{
                                  if(fmit->aktiv()){
                                   fmit->vektor(_kollidierbarkugel::ort(),n);
                                   grav+=(_kollidierbarkugel::vektor()%n)*ladung; 
                                  };
                                 }while(corundwelt->welt->naechstes(fmit));
                                };
                                //----------------------------Elektrische Feldkraft-------------------------------------
                                if(ladung!=0){
                                 _feldelektrostatisch<_tg> * feit;
                                 if(corundwelt->welt->anfang(feit))do{
                                  if(feit->aktiv()){
                                   feit->vektor(_kollidierbarkugel::ort(),n);
                                   grav+=n*ladung; 
                                  };
                                 }while(corundwelt->welt->naechstes(feit));
                                };
                                //-------------------------------Gummibandkraft-----------------------------------------
                                _listenknoten<_corundgummiband>*lngit;
                                _corundgummiband*git;
                                if(_liste<_corundgummiband>::anfang(lngit))do{
                                 git=lngit->objekt();
                                 grav+=git->beschleunigung(this);
                                }while(_liste<_corundgummiband>::naechstes(lngit));
                                //--------------------------------federkraft-------------------------------------------
                                _listenknoten<_corundfeder>*lnfit;
                                if(_liste<_corundfeder>::anfang(lnfit))do{
                                 lnfit->objekt()->beschleunigung(this,grav,drehgrav);
                                }while(_liste<_corundfeder>::naechstes(lnfit));
                                //-----------------------Elektrische Ladungen anderer Kugeln---------------------------
                                if(corundwelt->anfang(kit))do{
                                 if(kit!=this){
                                  if(ladung!=0){
                                   if(kit->ladung!=0){
                                    s=-1;
                                    if((kit->ladung>0)&&(ladung<0)) s=+1;
                                    if((kit->ladung<0)&&(ladung>0)) s=+1;
                                    n=kit->_kollidierbar::ort()-_kollidierbar::ort();
                                    d=n.laenge();
                                    n.normalisieren();
                                    f=0.01*(s*(fabs(ladung)+fabs(kit->ladung)))/(1+d);
                                    grav+=n*f;
                                   };
                                  };
                                  if(kit->gravitation!=0){
                                    n=kit->_kollidierbar::ort()-_kollidierbar::ort();
                                    d=n.laenge();
                                    n.normalisieren();
                                    f=0.001*(kit->gravitation/(1+d));
                                    grav+=n*f;
                                  };
                                 };
                                }while(corundwelt->naechstes(kit));
                                //--------------------------------chaotische Kraft----------------------------------
                                if(chaotischervektor){
                                 _zufallsgenerator<_tg> zu;
                                 _tg cf=chaotischerfaktor;
                                 _tg cfp=vektor().laenge();
                                 if(cfp>cf) cfp=cf;
                                 cf+=cfp;
                                 vektor()+=_vektor3<_tg>(zu.berechnen(-cf,+cf),0,zu.berechnen(-cf,+cf));
                                };
                                //---------------------------------zum spieler kraft--------------------------------
                                if(zumspielervektor){
                                 if(corundwelt->spieler){
                                  if(this!=corundwelt->spieler){
                                   _vektor3<_tg> vs=corundwelt->spieler->_kugel::ort()-_kugel::ort();
                                   vs.normalisieren();
                                   vektor()+=vs*0.003;
                                  };
                                 };
                                };
                                //--------------------------------------reibung-------------------------------------
                                _tg reibungsfaktor=corundwelt->welt->viskositaet();
                                _listenknoten<_polygon>*lnpit;
                                if(_liste<_polygon>::anfang(lnpit))do{
                                 reibungsfaktor*=lnpit->objekt()->rollreibung();
                                }while(_liste<_polygon>::naechstes(lnpit));
                                if(tauchen){
                                 reibungsfaktor*=0.8;
                                };
                                if(inlava) reibungsfaktor*=0.8;
                                //-------------------------------inventar objekte abfragen----------------------------
                                _corundinventar*ci=corundwelt->corundinventar;
                                if(ci){
                                 if(spieler){
                                  _corundobjekt*co;
                                  if(ci->anfang(co)){
                                   //reisszwecke
                                   _corundobjektreisszwecke*corz=dynamic_cast<_corundobjektreisszwecke*>(co);
                                   if(corz){
                                    reibungsfaktor*=corz->bremsfaktor;
                                   }else{
                                    //gleitmittel
                                    _corundobjektgleitmittel*cogm=dynamic_cast<_corundobjektgleitmittel*>(co);
                                    if(cogm){
                                     reibungsfaktor=(1-cogm->gleitfaktor)*reibungsfaktor + cogm->gleitfaktor*1;
                                    };
                                   };
                                  };
                                 };
                                };
                                
                                
                                
                                //bewegung durchführen
                                vektor()*=reibungsfaktor;
                                vektor()+=grav;//vektor(vektor()*0.99 + grav);
                                drehvektor()+=drehgrav;
                                
                                //abgleitzustände behandeln (kontakte ggf. lösen!)
                                pruefenabgleitzustandaus();
                                _win::_tastatur kb;
                                if(kb.taste(66)) _liste<_polygon>::aushaengen();
                                
                              
                                bearbeitenabgleitzustand();  
                            //    corundwelt->debugschirm->schreiben("kugelvek= ",vektor());
                                
                                
                                //L->l("Vektzort=",_kollidierbarkugel::vektor());
                                                                 L->l("ort     =",_kollidierbarkugel::ort());
                                                                 L->l("Vektor  =",_kollidierbarkugel::vektor());
                               
                                if(bewegen(grav)) {
                                 if(_kollidierbarkugel::schnittpunkt.polygon) vektor()*=_kollidierbarkugel::schnittpunkt.polygon->netz()->elastizitaet();//stoßverlust
                                 else vektor()*=0.96;
                                }else{
                                };
                                
                                //drehimpulsverabeitung
                                drehvektor()*=0.99;
                                _vektor3<_tg> dn=drehvektor();
                                dn.normalisieren();
                                rotieren(dn,drehvektor().laenge());
                                //visualisierung
                                _kugel::ort(_kollidierbarkugel::ort());
                                
                               /* _vektor3<_tg> h;
                                if(_liste<_corundgummiband>::anfang(lngit))do{
                                 git=lngit->objekt();
                                 if(git->kugel2){
                                  h=git->kugel2->_kollidierbarkugel::ort();
                                 }else{
                                  h=git->ort;
                                 };
                                 git->wl->ort(0,h);
                                 git->wl->ort(1,git->kugel->_kollidierbarkugel::ort());
                                }while(_liste<_corundgummiband>::naechstes(lngit));                                
                                 
                                _corundfeder*fit;
                                if(_liste<_corundfeder>::anfang(lnfit))do{
                                 fit=lnfit->objekt();
                                 if(fit->kugel2){
                                  h=fit->kugel2->_kollidierbarkugel::ort();
                                 }else{
                                  h=fit->ort;
                                 };
                                 fit->wl->ort(0,h);
                                 fit->wl->ort(1,fit->kugel->_kollidierbarkugel::ort());
                                }while(_liste<_corundfeder>::naechstes(lnfit));*/




                               _zeichenkette<char> cc;
                                cc="Vektor=";
                                cc+=vektor();
                                dbvektor->text(cc);
                                
                                cc="Grav=";
                                cc+=grav;
                                dbgrav->text(cc);

                                cc="Ort=";
                                cc+=_kollidierbarkugel::ort();
                                dbort->text(cc);



                                
};
void _corundkugel::bearbeitenabgleitzustand(){
                                _listenknoten<_polygon>*pit;
                                if(_liste<_polygon>::anfang(pit))do{
                                 vektor()+=pit->objekt()->normale()* -(vektor()*pit->objekt()->normale());
                                }while(_liste<_polygon>::naechstes(pit));
};
void _corundkugel::pruefenabgleitzustandaus(){
                                //alle kontakt punkte zu polygonen untersuchen 
                                _listenknoten<_polygon>*pit;
                                if(_liste<_polygon>::anfang(pit))do{
                                 if((vektor()*pit->objekt()->normale())>nahenull){
                                  L->schreiben("abgleitzustand AUS durch vektor");
                                  pit->loeschmarkierung(true);
                                 }else{
                                  _vektor3<_tg> lot;
                                  _tg para;
                                  V3.lotpunktebene(_kollidierbarkugel::ort(),pit->objekt()->mitte(),pit->objekt()->normale(),lot,para);
                                 /* if(lot.laenge()>(_kollidierbarkugel::radius()+nahenull*50)){
                                   L->schreiben("abgleitzustand AUS durch lotlaenge");
                                   pit->loeschmarkierung(true);
                                  }else*/
                                  if(pit->objekt()->innerhalbpunkt(_kollidierbarkugel::ort()+lot)==false) {
                                   L->schreiben("abgleitzustand AUS durch Diskretion");
                                   pit->loeschmarkierung(true);
                                  };
                                  
                                 };
                                }while(_liste<_polygon>::naechstes(pit));
                                _liste<_polygon>::loeschenmarkiert();
                                
/*                                if(abgleitpolygon){//pruefen ob abgleitzustand ausgeschaltet werden kann
                                 if((vektor()*abgleitpolygon->normale())>nahenull) {
                                  abgleitpolygon=0;
                                  L->schreiben("abgleitzustand AUS durch vektor");
                                  _liste<_polygon>::aushaengen();//kontakte lösen
                                 }else{
                                  _vektor3<_tg> lot;
                                  _tg para;
                                  V3.lotpunktebene(_kollidierbarkugel::ort(),abgleitpolygon->mitte(),abgleitpolygon->normale(),lot,para);
                                  if(abgleitpolygon->innerhalbpunkt(_kollidierbarkugel::ort()+lot)==false) {
                                   abgleitpolygon=0;
                                   L->schreiben("abgleitzustand AUS durch Diskretion");
                                   _liste<_polygon>::aushaengen();//kontakte lösen
                                  };
                                 };
                                };*/
                                
                                
};                                
void _corundkugel::pruefenabgleitzustandein(){//pruefen ob abgleitzustand eingeschaltet werden kann
                                //if(abgleitpolygon==0){
                               /*  _listenknoten<_
                                 if(_kollidierbarkugel::schnittpunkt.polygon){
                                  _tg vl;
                                  vl=vektor().laenge();
                                  if(vl<0.01) {
                                   abgleitpolygon.einhaengen(_kollidierbarkugel::schnittpunkt.polygon);
                                   //abgleitpolygon=_kollidierbarkugel::schnittpunkt.polygon;
                                   L->schreiben("Abgleitzustand EIN durch niedrige geschwindigkeit.");
                                  };
                                  _vektor3<_tg> v=vektor();
                                  v.normalisieren();
                                  if(fabs(v*_kollidierbarkugel::schnittpunkt.polygon->normale())<0.4){
                                   L->schreiben("abgleitzustand EIN durch skalarprodukt");
                                   abgleitpolygon.einhaengen(_kollidierbarkugel::schnittpunkt.polygon);
                                   //abgleitpolygon=_kollidierbarkugel::schnittpunkt.polygon;
                                  };
                                 };*/
                                //};
};                                
/*
                             _vektor3<double> v=pvektor;
                            double pvl=v.laenge();
                            _vektor3<double> grav;
                            grav.setzen(0,-0.03,0);
                            pvektor+=grav;
                            if(abgleitpolygon){
                             if((pvektor*abgleitpolygon->normale())>nahenull) {
                              abgleitpolygon=0;
                              L->schreiben("abgleitzustand AUS durch vektor");
                             }else{
                              _vektor3<double> lot;
                              double para;
                              V3.lotpunktebene(port,abgleitpolygon->mitte(),abgleitpolygon->normale(),lot,para);
                              if(abgleitpolygon->innerhalbpunkt(port+lot)==false) {
                               abgleitpolygon=0;
                               L->schreiben("abgleitzustand AUS durch Diskretion");
                              };
                             };
                            };
                            double vl;
                            if(abgleitpolygon==0){
                             //--------------------------- reflektieren --------------------------
                             vl=pvektor.laenge();
                             _polygon*zuletztkollidiert;
                             _vektor3<double> altort=port;
                             if(kollision(port,pvektor,pvl,zuletztkollidiert)){
                              _vektor3<double> lot;
                              double para;
                              V3.lotpunktebene(port,altort,grav,lot,para);
                              
                              v.normalisieren();
                              _vektor3<double> da=((v*pvl*10)%zuletztkollidiert->normale())*(1-fabs(zuletztkollidiert->normale()*v)); 
                              ws->addierendrehimpuls(   da  );
                              ws->multiplizierendrehimpuls(0.96);
                              pvektor*=0.96;
                              vl=pvektor.laenge();
                              if(pvl<0.01){
                               L->schreiben("abgleitzustand EIN durch niedrige vektorlänge");
                               abgleitpolygon=zuletztkollidiert;
                              }else{
                              
                               v.normalisieren();
                               if(fabs(v*zuletztkollidiert->normale())<0.1){
                                L->schreiben("abgleitzustand EIN durch skalarprodukt");
                                abgleitpolygon=zuletztkollidiert;
                               };
                              };
                             }else{
                              port+=pvektor; 
                              ws->multiplizierendrehimpuls(0.996);
                             // pvektor*=0.999;
                             };
                            }else{
                             //----------------------------- abgleiten --------------------------
                             //gravitation projizieren auf ebene
                            // grav+=abgleitpolygon->normale()* -(grav*abgleitpolygon->normale());
                             
                             //pvektor+=grav;
                             pvektor+=abgleitpolygon->normale()* -(pvektor*abgleitpolygon->normale());
                             _polygon*zuletztkollidiert;
                             vl=pvektor.laenge();
                             
                             if(kollision(port,pvektor,vl,zuletztkollidiert)){
                              v.normalisieren();
                              _vektor3<double> da=((v*pvl*10)%zuletztkollidiert->normale())*(1-fabs(zuletztkollidiert->normale()*v)); 
                              ws->multiplizierendrehimpuls(0.96);
                              ws->addierendrehimpuls(   da   );
                              pvektor*=0.95;
                              L->schreiben("abgleitkollision aufgetreten");
                             }else{
                              port+=pvektor;
                              _vektor3<double> di;
                              di=pvektor%abgleitpolygon->normale();
                              di.normalisieren();
                              di*=(360.0f)*(pvektor.laenge())/(2*_pi*pradius);
                              ws->drehimpuls(di);
                              ws->animieren();
                              
                              pvektor*=0.99;
                              //ws->multiplizierendrehimpuls(0.996);
                             };
                            };
                            */                               

void _corundkugel::kollision(_kollidierbar*k){
                                //_kugel::farbe(_vektor4<_to>(1,0,0,1));
                                //farbe=_vektor4<_to>(1,0,0,1);
                                //L->schreiben("kugel wurde kollidiert");
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 if(killer) t->zerstoeren();
                                 if(t->killer) zerstoeren();
                                 //zerstoeren();
                                }else{
                                 _kollidierbarkugel*kk;
                                 kk=dynamic_cast<_kollidierbarkugel*>(k);
                                 if(kk){
                                  if(kk->kollisionskopplung){
                                   _corundsteinflak*osf;
                                   osf=dynamic_cast<_corundsteinflak*>(kk->kollisionskopplung);
                                   if(osf){
                                    zerstoeren();
                                   };
                                  };
                                 };
                                };
};
void _corundkugel::kollision(_kollidierbar*,_polygon*){
};
void _corundkugel::visualisieren(){
};
char _corundkugel::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundkugel>*sd){
                                char r=1;
                                _vektor3<_tg> v;
                                _tg h;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(v);_kollidierbarkugel::ort(v);_kugel::ort(v);
                                r^=sd->ladenwert(v);_kollidierbarkugel::vektor(v);
                                r^=sd->ladenwert(h);_kollidierbarkugel::radius(h);_kugel::radius(h);
                                r^=sd->ladenwert(farbe);_kugel::farbe(farbe);
                                r^=sd->ladenwert(spieler);                                
                                r^=sd->ladenwert(ladung);
                                r^=sd->ladenwert(gravitation);
                                r^=sd->ladenwert(steuerung);
                                r^=sd->ladenwert(augenmodus);
                                r^=sd->ladenwert(killer);
                                r^=sd->ladenwert(chaotischervektor);
                                r^=sd->ladenwert(chaotischerfaktor);
                                r^=sd->ladenwert(zumspielervektor);
                                r^=sd->ladenwert(gesundheit);
                                r^=sd->ladenwert(editorgummikoordinate);
                                r^=sd->ladenwert(editorgummifarbe);
                                r^=sd->ladenwert(editorgummistaerke);
                                r^=sd->ladenwert(editorfederkoordinate);
                                r^=sd->ladenwert(editorfederfarbe);
                                r^=sd->ladenwert(editorfederstaerke);
                              
                                if(spieler) corundwelt->spieler=this;
                                sd->ladenende();
                                return(r);
};                                
void _corundkugel::speichern(_speicherbardynamisch<_corundkugel>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(_kollidierbarkugel::ort());
                                sd->speichernwert(_kollidierbarkugel::vektor());
                                sd->speichernwert(_kollidierbarkugel::radius());
                                sd->speichernwert(farbe);
                                if(corundwelt->spieler==this) spieler=true; else spieler=false;                                
                                sd->speichernwert(spieler);
                                sd->speichernwert(ladung);
                                sd->speichernwert(gravitation);
                                sd->speichernwert(steuerung);
                                sd->speichernwert(augenmodus);
                                sd->speichernwert(killer);
                                sd->speichernwert(chaotischervektor);
                                sd->speichernwert(chaotischerfaktor);
                                sd->speichernwert(zumspielervektor);
                                sd->speichernwert(gesundheit);
                                sd->speichernwert(editorgummikoordinate);
                                sd->speichernwert(editorgummifarbe);
                                sd->speichernwert(editorgummistaerke);
                                sd->speichernwert(editorfederkoordinate);
                                sd->speichernwert(editorfederfarbe);
                                sd->speichernwert(editorfederstaerke);
                                
                                sd->speichernendeblock();
};                                
char _corundkugel::assoziieren(_speicherbardynamisch<_corundkugel>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
 void _corundkugel::netzwahl(_netz*ne,int i){
                                if(hauptfenster){
                                 _corundstein*cs=dynamic_cast<_corundstein*>(ne);
                                 if(cs){
                                  if(i==0){//für gummis
                                   _corundgummiband*gb=new _corundgummiband(this,cs,editorgummistaerke);
                                   gb->pfarbe=editorgummifarbe;
                                  };
                                  if(i==1){//für federn
                                   _corundfeder*gb=new _corundfeder(this,cs,editorfederstaerke);
                                   gb->pfarbe=editorfederfarbe;
                                  };
                                 }else{
                                  hauptfenster->information("Fehler","Das angewählte Netz ist kein Stein.");   
                                 };
                                 hauptfenster->zeichnen();
                                };
};
 void _corundkugel::figurwahl(_corundfigur*f,int i){
                                if(hauptfenster){
                                 _corundkugel*k=dynamic_cast<_corundkugel*>(f);
                                 if(k){
                                  if(i==0){//für gummis
                                   _corundgummiband*gb=new _corundgummiband(this,k,editorgummistaerke);
                                   gb->pfarbe=editorgummifarbe;
                                  };
                                  if(i==1){//für federn
                                   _corundfeder*gb=new _corundfeder(this,k,editorfederstaerke);
                                   gb->pfarbe=editorfederfarbe;
                                  };
                                 }else{
                                  hauptfenster->information("Fehler","Das angewählte Objekt ist keine Figur.");   
                                 };
                                 hauptfenster->zeichnen();
                                };
};

void _corundkugel::beineugummifest(_guiereignisdaten*){
                                if(dialog){
                                 dialog->auslesen(L"Allgemein",L"an Gummikoordinate",editorgummikoordinate);                                
                                 dialog->auslesen(L"Allgemein",L"mit Gummifarbe",editorgummifarbe);                                
                                 dialog->auslesen(L"Allgemein",L"der Gummistärke",editorgummistaerke);                                
                                 new _corundgummiband(this,editorgummikoordinate,editorgummifarbe,editorgummistaerke);
                                 if(hauptfenster) hauptfenster->zeichnen();
                                };
};
void _corundkugel::beineugummistein(_guiereignisdaten*){
                                if(hauptfenster){
                                 if(dialog){
                                  dialog->auslesen(L"Allgemein",L"mit Gummifarbe",editorgummifarbe);                                
                                  dialog->auslesen(L"Allgemein",L"der Gummistärke",editorgummistaerke);                                
                                 };
                                 hauptfenster->dnetzwahl->corundfigur(this);
                                 hauptfenster->dnetzwahl->index(0);//==für gummis
                                 hauptfenster->dnetzwahl->zeigen();
                                 hauptfenster->zeichnen();
                                };
                                
};
void _corundkugel::beineugummifigur(_guiereignisdaten*){
                                if(hauptfenster){
                                 if(dialog){
                                  dialog->auslesen(L"Allgemein",L"mit Gummifarbe",editorgummifarbe);                                
                                  dialog->auslesen(L"Allgemein",L"der Gummistärke",editorgummistaerke);                                
                                 };
                                 hauptfenster->dfigurwahl->corundfigur(this);
                                 hauptfenster->dfigurwahl->index(0);//==für gummis
                                 hauptfenster->dfigurwahl->zeigen();
                                 hauptfenster->zeichnen();
                                };
};
void _corundkugel::beiloeschengummi(_guiereignisdaten*){  
                                loeschengummiband();
                                if(hauptfenster) hauptfenster->zeichnen();
};
void _corundkugel::beineufederfest(_guiereignisdaten*){
                                if(dialog){
                                 dialog->auslesen(L"Allgemein",L"an Federkoordinate",editorfederkoordinate);                                
                                 dialog->auslesen(L"Allgemein",L"mit Federfarbe",editorfederfarbe);                                
                                 dialog->auslesen(L"Allgemein",L"der Federstärke",editorfederstaerke);                                
                                 new _corundfeder(this,editorfederkoordinate,editorfederfarbe,editorfederstaerke);
                                 if(hauptfenster) hauptfenster->zeichnen();
                                };
};
void _corundkugel::beineufederstein(_guiereignisdaten*){
                                if(hauptfenster){
                                 if(dialog){
                                  dialog->auslesen(L"Allgemein",L"mit Federfarbe",editorfederfarbe);                                
                                  dialog->auslesen(L"Allgemein",L"der Federstärke",editorfederstaerke);                                
                                 };
                                 hauptfenster->dnetzwahl->corundfigur(this);
                                 hauptfenster->dnetzwahl->index(1);//==für feders
                                 hauptfenster->dnetzwahl->zeigen();
                                 hauptfenster->zeichnen();
                                };
                                
};
void _corundkugel::beineufederfigur(_guiereignisdaten*){
                                if(hauptfenster){
                                 if(dialog){
                                  dialog->auslesen(L"Allgemein",L"mit Federfarbe",editorfederfarbe);                                
                                  dialog->auslesen(L"Allgemein",L"der Federstärke",editorfederstaerke);                                
                                 };
                                 hauptfenster->dfigurwahl->corundfigur(this);
                                 hauptfenster->dfigurwahl->index(1);//==für feders
                                 hauptfenster->dfigurwahl->zeigen();
                                 hauptfenster->zeichnen();
                                };
};

void _corundkugel::beiloeschenfeder(_guiereignisdaten*){  
                                loeschenfeder();
                                if(hauptfenster) hauptfenster->zeichnen();
};
void _corundkugel::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                d->loeschensektion();
                                _material<_tg>::einhaengendialog(d);
                                _oberflaeche<_tg>::einhaengendialog(d);
                                dialog=d;
                                
                                d->addierensektion(L"Allgemein");
                                d->sektion(L"Allgemein")->offen(true);
                                d->einhaengen(L"Allgemein",L"Position",_kollidierbarkugel::ort());
                                d->einhaengen(L"Allgemein",L"Vektor",_kollidierbarkugel::vektor());
                                d->einhaengen(L"Allgemein",L"Radius",_kollidierbarkugel::radius());
                                d->einhaengen(L"Allgemein",L"Farbe",farbe);
                                d->einhaengen(L"Allgemein",L"Diese Kugel ist Spieler",spieler);
                                d->einhaengen(L"Allgemein",L"Ladung",ladung);
                                d->einhaengen(L"Allgemein",L"Gravitation",gravitation);
                                d->einhaengen(L"Allgemein",L"Steuerung",steuerung);
                                d->einhaengen(L"Allgemein",L"Augenmodus",augenmodus);
                                d->einhaengen(L"Allgemein",L"Tödlich",killer);
                                d->einhaengen(L"Allgemein",L"Chaotisch",chaotischervektor);
                                d->einhaengen(L"Allgemein",L"Chaotischer Faktor",chaotischerfaktor);
                                d->einhaengen(L"Allgemein",L"Vektor zum Spieler",zumspielervektor);                                
                                d->einhaengen(L"Allgemein",L"Gesundheit",gesundheit);        
                                     
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Gummiband mit Festort",L"addieren",this,&_corundkugel::beineugummifest);                   
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Gummiband an Stein",L"addieren",this,&_corundkugel::beineugummistein);                   
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Gummiband an Figur",L"addieren",this,&_corundkugel::beineugummifigur);                   
                                d->einhaengen(L"Allgemein",L"an Gummikoordinate",editorgummikoordinate);                                
                                d->einhaengen(L"Allgemein",L"mit Gummifarbe",editorgummifarbe);                                
                                d->einhaengen(L"Allgemein",L"der Gummistärke",editorgummistaerke);                                
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Gummibänder",L"löschen",this,&_corundkugel::beiloeschengummi);                   
                                new _editionskopplungort(d,L"Allgemein",L"an Gummikoordinate");
                                
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Feder mit Festort",L"addieren",this,&_corundkugel::beineufederfest);                   
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Feder an Stein",L"addieren",this,&_corundkugel::beineufederstein);                   
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Feder an Figur",L"addieren",this,&_corundkugel::beineufederfigur);                   
                                d->einhaengen(L"Allgemein",L"an Federkoordinate",editorfederkoordinate);                                
                                d->einhaengen(L"Allgemein",L"mit Federfarbe",editorfederfarbe);                                
                                d->einhaengen(L"Allgemein",L"der Federstärke",editorfederstaerke);                                
                                d->einhaengenknopf<_corundkugel>(L"Allgemein",L"Federn",L"löschen",this,&_corundkugel::beiloeschenfeder);                   
                                new _editionskopplungort(d,L"Allgemein",L"an Federkoordinate");
};
void _corundkugel::auslesendialog(_dynamischerdialog*d){
                                _vektor3<_tg> o;
                                _tg r;
                                _material<_tg>::auslesendialog(d);
                                _oberflaeche<_tg>::auslesendialog(d);
                                d->auslesen(L"Allgemein",L"Position",o);_kollidierbarkugel::ort(o);
                                d->auslesen(L"Allgemein",L"Vektor",o);_kollidierbarkugel::vektor(o);
                                d->auslesen(L"Allgemein",L"Radius",r);_kollidierbarkugel::radius(r);
                                d->auslesen(L"Allgemein",L"Farbe",farbe);
                                _kugel::farbe(farbe);
                                
                                d->auslesen(L"Allgemein",L"Diese Kugel ist Spieler",spieler);
                                if(spieler) corundwelt->spieler=this;
                                d->auslesen(L"Allgemein",L"Ladung",ladung);
                                d->auslesen(L"Allgemein",L"Gravitation",gravitation);
                                d->auslesen(L"Allgemein",L"Steuerung",steuerung);
                                d->auslesen(L"Allgemein",L"Augenmodus",augenmodus);
                                d->auslesen(L"Allgemein",L"Tödlich",killer);
                                d->auslesen(L"Allgemein",L"Chaotisch",chaotischervektor);
                                d->auslesen(L"Allgemein",L"Chaotischer Faktor",chaotischerfaktor);
                                d->auslesen(L"Allgemein",L"Vektor zum Spieler",zumspielervektor);                                
                                d->auslesen(L"Allgemein",L"Gesundheit",gesundheit);                                
                                d->auslesen(L"Allgemein",L"an Gummikoordinate",editorgummikoordinate);                                
                                d->auslesen(L"Allgemein",L"mit Gummifarbe",editorgummifarbe);                                
                                d->auslesen(L"Allgemein",L"der Gummistärke",editorgummistaerke);                                
                                d->auslesen(L"Allgemein",L"an Federkoordinate",editorfederkoordinate);                                
                                d->auslesen(L"Allgemein",L"mit Federfarbe",editorfederfarbe);                                
                                d->auslesen(L"Allgemein",L"der Federstärke",editorfederstaerke);                                

};
void _corundkugel::loeschendebug(){
                                if(dbvektor) delete dbvektor;
                                if(dbgrav) delete dbgrav;
                                if(dbort) delete dbort;
                                dbvektor=0;
                                dbgrav=0;
                                dbort=0;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D G U M M I B A N D
//******************************************************************************************************************************************************************************************************
_corundgummiband::_corundgummiband(_corundwelt*cw):_listenknotenbasis<_corundgummiband>(cw){
                                pwelt=cw->welt;
                                corundwelt=cw;
                                kugel=0;
                                kugel2=0;
                                stein=0;
                                staerke=0.001;
                                pfarbe.setzen(0.5,0.5,0.5,1);
                                //_vektor3<_tg> h0;
                                //wl=new _weltdebuglinie(pwelt,h0,h0,pfarbe);
                                //wl->farbe(pfarbe);
};
_corundgummiband::_corundgummiband(_corundkugel*k,_corundstein*os,_tg s):_listenknotenbasis<_corundgummiband>(k->corundwelt){
                                pwelt=k->corundwelt->welt;
                                corundwelt=k->corundwelt;
                                kugel=k;
                                kugel2=0;
                                stein=os;
                                staerke=s;
                                kugel->_liste<_corundgummiband>::einhaengen(this);
                                stein->_liste<_corundgummiband>::einhaengen(this);
                                ort=stein->mitte();//.setzen(x,y,z);
                                pfarbe.setzen(0.5,0.5,0.5,1);
                                /*_vektor3<_tg> h0;
                                _vektor3<_tg> h1;
                                h0=kugel->_kollidierbarkugel::ort();
                                if(kugel2){
                                 h1=kugel2->_kollidierbarkugel::ort();
                                }else{
                                 h1.setzen(ort[0],ort[1],ort[2]);
                                };
                                wl=new _weltdebuglinie(kugel->welt->welt,h0,h1,pfarbe);
                                wl->farbe(pfarbe);*/
};
_corundgummiband::_corundgummiband(_corundkugel*k,_corundkugel*k2,_tg s):_listenknotenbasis<_corundgummiband>(k->corundwelt){
                                pwelt=k->corundwelt->welt;
                                corundwelt=k->corundwelt;
                                kugel=k;
                                kugel2=k2;
                                stein=0;
                                staerke=s;
                                kugel->_liste<_corundgummiband>::einhaengen(this);
                                kugel2->_liste<_corundgummiband>::einhaengen(this);
                                ort.setzen(0,0,0);
                                pfarbe.setzen(0.5,0.5,0.5,1);
                                /*_vektor3<_tg> h0;
                                _vektor3<_tg> h1;
                                h0=kugel->_kollidierbarkugel::ort();
                                h1=kugel2->_kollidierbarkugel::ort();
                                wl=new _weltdebuglinie(kugel->welt->welt,h0,h1,pfarbe);
                                wl->farbe(pfarbe);*/
};
_corundgummiband::_corundgummiband(_corundkugel*k,const _vektor3<_tg>&o,const _vektor4<_to>&f,_tg s):_listenknotenbasis<_corundgummiband>(k->corundwelt){
                                ort=o;
                                pwelt=k->corundwelt->welt;
                                corundwelt=k->corundwelt;
                                kugel=k;
                                kugel2=0;
                                stein=0;
                                staerke=s;
                                pfarbe=f;
                                kugel->_liste<_corundgummiband>::einhaengen(this);        
                                /*_vektor3<_tg> h0;
                                _vektor3<_tg> h1;
                                h0=kugel->_kollidierbarkugel::ort();
                                h1.setzen(ort[0],ort[1],ort[2]);
                                wl=new _weltdebuglinie(kugel->welt->welt,h0,h1,pfarbe);
                                wl->farbe(pfarbe);                                                       */
};
_corundgummiband::~_corundgummiband(){
                                //delete wl;
};
_vektor3<_tg>&_corundgummiband::beschleunigung(_corundkugel*kit){
                                if(kit){
                                 if(kugel2){
                                  if(kugel==kit){
                                   pbeschleunigung=kugel2->_kollidierbarkugel::ort()-kugel->_kollidierbarkugel::ort();
                                  }else{
                                   pbeschleunigung=kugel->_kollidierbarkugel::ort()-kugel2->_kollidierbarkugel::ort();
                                  };
                                 }else{
                                  if(stein) pbeschleunigung=stein->_netz::mitte()-kit->_kollidierbarkugel::ort(); else pbeschleunigung=ort-kit->_kollidierbarkugel::ort();
                                 };
                                }else{
                                };
                                pbeschleunigung*=staerke;
                                return(pbeschleunigung);
};
void _corundgummiband::zeichnen(_grafik*g){
                                if(kugel){
                                 _vektor3<_tg> h;
                                 if(kugel2) h=kugel2->_kollidierbarkugel::ort(); else
                                 if(stein) h=stein->_netz::mitte(); else
                                 h=ort;
                                 g->transparenz(true);
                                 g->zeichnen(kugel->_kollidierbarkugel::ort(),h,pfarbe,pfarbe);
                                 g->transparenz(false);
                                };
};
char _corundgummiband::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundgummiband>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(ort);
                                r^=sd->ladenwert(pfarbe);
                                r^=sd->ladenwert(staerke);
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();
                                sd->ladenende();
                                return(r);
};
void _corundgummiband::speichern(_speicherbardynamisch<_corundgummiband>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(ort);
                                sd->speichernwert(pfarbe);
                                sd->speichernwert(staerke);
                                saveassociationargument(sd->datei(),sd,kugel);
                                saveassociationargument(sd->datei(),sd,kugel2);
                                saveassociationargument(sd->datei(),sd,stein);
                                sd->speichernendeblock();
};
char _corundgummiband::assoziieren(_speicherbardynamisch<_corundgummiband>*sd){
                                sd->assoziierenverschachtelung();
                                associateassociationargument(sd->datei(),sd->assoziation(),kugel);
                                associateassociationargument(sd->datei(),sd->assoziation(),kugel2);
                                associateassociationargument(sd->datei(),sd->assoziation(),stein);
                                if(kugel) kugel->_liste<_corundgummiband>::einhaengen(this);
                                if(kugel2) kugel2->_liste<_corundgummiband>::einhaengen(this);
                                if(stein) stein->_liste<_corundgummiband>::einhaengen(this);
                                return(1);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D F E D E R 
//******************************************************************************************************************************************************************************************************
_corundfeder::_corundfeder(_corundwelt*cw):_listenknotenbasis<_corundfeder>(cw){
                                corundwelt=cw;
                                pwelt=cw->welt;
                                kugel=0;
                                kugel2=0;
                                stein=0;
                                staerke=0.001;
                                pfarbe.setzen(0.5,0.5,0.5,1);
                                pvektor[0].setzen(+1,0,0);
                                pvektor[1].setzen(-1,0,0);
                                plaenge=1;
};
_corundfeder::_corundfeder(_corundkugel*k,_corundstein*os,_tg s):_listenknotenbasis<_corundfeder>(k->corundwelt){
                                pwelt=k->corundwelt->welt;
                                corundwelt=k->corundwelt;
                                kugel=k;
                                kugel2=0;
                                stein=os;
                                staerke=s;
                                kugel->_liste<_corundfeder>::einhaengen(this);
                                stein->_liste<_corundfeder>::einhaengen(this);
                                ort=stein->ort+stein->breite*0.5;//.setzen(x,y,z);
                                pvektor[0]=ort-kugel->_kollidierbarkugel::ort();
                                pvektor[1]=-pvektor[0];
                                pvektor[0].normalisieren();
                                pvektor[1].normalisieren();
                                pfarbe.setzen(0.5,0.5,0.5,1);
                                plaenge=(kugel->_kollidierbarkugel::ort()-ort).laenge();
};
_corundfeder::_corundfeder(_corundkugel*k,_corundkugel*k2,_tg s):_listenknotenbasis<_corundfeder>(k->corundwelt){
                                pwelt=k->corundwelt->welt;
                                corundwelt=k->corundwelt;
                                kugel=k;
                                kugel2=k2;
                                pvektor[0]=kugel2->_kollidierbarkugel::ort() - kugel->_kollidierbarkugel::ort();
                                pvektor[1]=-pvektor[0];
                                pvektor[0].normalisieren();
                                pvektor[1].normalisieren();
                                plaenge=(kugel->_kollidierbarkugel::ort()-kugel2->_kollidierbarkugel::ort()).laenge();
                                stein=0;
                                staerke=s;
                                kugel->_liste<_corundfeder>::einhaengen(this);
                                kugel2->_liste<_corundfeder>::einhaengen(this);
                                ort.setzen(0,0,0);
                                pfarbe.setzen(0.5,0.5,0.5,1);
};
_corundfeder::_corundfeder(_corundkugel*k,const _vektor3<_tg>&o,const _vektor4<_to>&f,_tg s):_listenknotenbasis<_corundfeder>(k->corundwelt){
                                pwelt=k->corundwelt->welt;
                                corundwelt=k->corundwelt;
                                ort=o;
                                pfarbe=f;
                                kugel=k;
                                kugel2=0;
                                stein=0;
                                staerke=s;
                                pvektor[0]=ort - kugel->_kollidierbarkugel::ort();
                                pvektor[1]=-pvektor[0];
                                pvektor[0].normalisieren();
                                pvektor[1].normalisieren();
                                plaenge=(kugel->_kollidierbarkugel::ort()-ort).laenge();
                                kugel->_liste<_corundfeder>::einhaengen(this);
};
_corundfeder::~_corundfeder(){
};
void _corundfeder::beschleunigung(_corundkugel*kit,_vektor3<_tg>&beschleunigung,_vektor3<_tg>&drehbeschleunigung){
                                /*_vektor3<_tg> d;
                                _tg w;
                                _vektor3<_tg> v;
                                _vektor3<_tg> b;
                                */
                                if(kit){
                                 if(kugel2){
                                  if(kugel!=kit){
                                   //kit ist kugel2
                                   //kitvektor ist pvektor1
                                   //oth ist kugel
                                   //othvektor ist pvektor0
                                   _vektor3<_tg> vsoll=kugel->_kollidierbarkugel::ort()-kugel2->_kollidierbarkugel::ort();
                                   _vektor3<_tg> vist=kugel2->transformieren(pvektor[1]);
                                   _vektor3<_tg> osoll=kugel->_kollidierbarkugel::ort() + kugel->transformieren(pvektor[0])*plaenge;
                                   _vektor3<_tg> odiff=osoll-kugel2->_kollidierbarkugel::ort();
                                   _vektor3<_tg> n=vsoll%vist;
                                   
                                   
                                  _vektor3<_tg> erstebeschleun=(osoll-kugel2->_kollidierbarkugel::ort())*staerke;
                                  _vektor3<_tg> oist2=kugel2->_kollidierbarkugel::ort()+(kugel2->_kollidierbarkugel::vektor()+erstebeschleun)*0.5;
                                  _vektor3<_tg> zweitebeschleun=(osoll-oist2)*staerke;
                                  beschleunigung+=erstebeschleun*0.5f+zweitebeschleun*0.5f;//odiff*staerke;
                                   
                                   
                                   //beschleunigung+=odiff*staerke;
                                   if(n.laenge()>nahenull){
                                    n.normalisieren();
                                    drehbeschleunigung+=n*vsoll.winkel(vist)*staerke*1;
                                   };
                                   /*
                                   v=kugel->transformieren(pvektor[0]);
                                   d=kugel->_kollidierbarkugel::ort() + v*plaenge;
                                   b=d-kugel2->_kollidierbarkugel::ort();
                                   if(b.laenge()>nahenull){
                                    _vektor3<_tg> v0=d-kugel->_kollidierbarkugel::ort();
                                    _vektor3<_tg> v1=kugel2->_kollidierbarkugel::ort()-kugel->_kollidierbarkugel::ort();    
                                    _vektor3<_tg> n;
                                    w=v0.winkel(v1);
                                    n=v1%v0;
                                    n.normalisieren();
                                   // drehbeschleunigung+=n*w*staerke;
                                    kugel2->rotieren(n,w*0.5);
                                   };
                                   beschleunigung+=b*staerke;
                                   */
                                  }else{
                                   //kit ist kugel
                                   //kitvektor ist pvektor0
                                   //oth ist kugel2
                                   //othvektor ist pvektor1
                                   _vektor3<_tg> vsoll=kugel2->_kollidierbarkugel::ort()-kugel->_kollidierbarkugel::ort();
                                   _vektor3<_tg> vist=kugel->transformieren(pvektor[0]);
                                   _vektor3<_tg> osoll=kugel2->_kollidierbarkugel::ort() + kugel2->transformieren(pvektor[1])*plaenge;
                                   _vektor3<_tg> odiff=osoll-kugel->_kollidierbarkugel::ort();
                                   _vektor3<_tg> n=vsoll%vist;
                                   
                                   
                                  _vektor3<_tg> erstebeschleun=(osoll-kugel->_kollidierbarkugel::ort())*staerke;
                                  _vektor3<_tg> oist2=kugel->_kollidierbarkugel::ort()+(kugel->_kollidierbarkugel::vektor()+erstebeschleun)*0.5;
                                  _vektor3<_tg> zweitebeschleun=(osoll-oist2)*staerke;
                                  beschleunigung+=erstebeschleun*0.5f+zweitebeschleun*0.5f;//odiff*staerke;
                                   
                                   
                                //   beschleunigung+=odiff*staerke;
                                   if(n.laenge()>nahenull){
                                    n.normalisieren();
                                    drehbeschleunigung+=n*vsoll.winkel(vist)*staerke*1;
                                   };
                                   /*   ^^
                                   v=kugel2->transformieren(pvektor[1]);
                                   d=kugel2->_kollidierbarkugel::ort() + v*plaenge;
                                   b=d-kugel->_kollidierbarkugel::ort();
                                   if(b.laenge()>nahenull){
                                    _vektor3<_tg> v0=d-kugel2->_kollidierbarkugel::ort();
                                    _vektor3<_tg> v1=kugel->_kollidierbarkugel::ort()-kugel2->_kollidierbarkugel::ort();    
                                    _vektor3<_tg> n;
                                    w=v0.winkel(v1);
                                    n=v0%v1;
                                    n.normalisieren();
                                   // drehbeschleunigung+=n*w*staerke;
                                    kugel->rotieren(n,w*0.5);
                                   };
                                   beschleunigung+=b*staerke;
                                   */
                                  };
                                 }else{// feder, die an einem stein oder an einem festort befestigt ist
                                  _vektor3<_tg> vsoll=ort-kugel->_kollidierbarkugel::ort();
                                  _vektor3<_tg> vist=kugel->transformieren(pvektor[0]);
                                  _vektor3<_tg> osoll;
                                  if(stein) osoll=stein->_netz::mitte()+pvektor[1]*plaenge; else osoll=ort + pvektor[1]*plaenge;
                                  _vektor3<_tg> odiff=osoll-kugel->_kollidierbarkugel::ort();
                                  _vektor3<_tg> n=vsoll%vist;
                                  
                                  
                                  
                                  _vektor3<_tg> erstebeschleun=(osoll-kugel->_kollidierbarkugel::ort())*staerke;
                                  _vektor3<_tg> oist2=kugel->_kollidierbarkugel::ort()+(kugel->_kollidierbarkugel::vektor()+erstebeschleun)*0.5;
                                  _vektor3<_tg> zweitebeschleun=(osoll-oist2)*staerke;
                                  beschleunigung+=erstebeschleun*0.5f+zweitebeschleun*0.5f;//odiff*staerke;
                                  
                                  
                                  
                                  
                                  /*_tg vl=kugel->_kollidierbarkugel::vektor().laenge();
                                  _tg dl=odiff.laenge();
                                  if(vl>dl){
                                  }else{
                                   //die komplette beschleunigung anwenden
                                   _vektor3<_tg> odiffn=odiff;
                                   _vektor3<_tg> vektorn=kugel->_kollidierbarkugel::vektor();
                                   odiffn.normalisieren();
                                   vektorn.normalisieren();
                                   _tg faktor=((odiffn*-vektorn)+1);//0..2
                                   faktor/=2;//0..1
                                   faktor*=1.5;//0..1.5
                                   faktor+=0.5;//0.5..2
                                   beschleunigung+=odiff*staerke;//*faktor;
                                  };*/
                                  if(n.laenge()>nahenull){
                                   n.normalisieren();
                                   drehbeschleunigung+=n*vsoll.winkel(vist)*staerke*0.75;
                                  };
                                 };
                                };
                                //pbeschleunigung*=staerke;
                                //return(pbeschleunigung);
};
void _corundfeder::zeichnen(_grafik*g){
                                if(kugel){
                                 _vektor3<_tg> h;
                                 if(kugel2) h=kugel2->_kollidierbarkugel::ort(); else
                                 if(stein) h=stein->_netz::mitte(); else
                                 h=ort;
                                 g->transparenz(true);
                                 g->zeichnen(kugel->_kollidierbarkugel::ort(),h,pfarbe,pfarbe);
                                 g->transparenz(false);
                                };
};
char _corundfeder::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundfeder>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(ort);
                                r^=sd->ladenwert(pfarbe);
                                r^=sd->ladenwert(staerke);
                                r^=sd->ladenwert(pvektor[0]);
                                r^=sd->ladenwert(pvektor[1]);
                                r^=sd->ladenwert(plaenge);
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();
                                sd->ladenende();
                                return(r);
};
void _corundfeder::speichern(_speicherbardynamisch<_corundfeder>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(ort);
                                sd->speichernwert(pfarbe);
                                sd->speichernwert(staerke);
                                sd->speichernwert(pvektor[0]);
                                sd->speichernwert(pvektor[1]);
                                sd->speichernwert(plaenge);
                                saveassociationargument(sd->datei(),sd,kugel);
                                saveassociationargument(sd->datei(),sd,kugel2);
                                saveassociationargument(sd->datei(),sd,stein);
                                sd->speichernendeblock();
};
char _corundfeder::assoziieren(_speicherbardynamisch<_corundfeder>*sd){
                                sd->assoziierenverschachtelung();
                                associateassociationargument(sd->datei(),sd->assoziation(),kugel);
                                associateassociationargument(sd->datei(),sd->assoziation(),kugel2);
                                associateassociationargument(sd->datei(),sd->assoziation(),stein);
                                if(kugel) kugel->_liste<_corundfeder>::einhaengen(this);
                                if(kugel2) kugel2->_liste<_corundfeder>::einhaengen(this);
                                if(stein) stein->_liste<_corundfeder>::einhaengen(this);
                                return(1);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S K E L E T T
//******************************************************************************************************************************************************************************************************
_corundskelett::_corundskelett(_corundwelt*cw,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s):_corundfigur(cw),_skelett(cw->welt,o,r,n,s){
                                port=o;
				                federkraft=0.3;
				                traegheitsdaempfung=0.985;                                  
};
_corundskelett::~_corundskelett(){
};
void _corundskelett::visualisieren(){
                                 _skelett::visualisieren();
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D O R A K E L 
//******************************************************************************************************************************************************************************************************
_corundorakel::_corundorakel(_corundwelt*cw,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s):_corundskelett(cw,o,r,n,s){
                                int i,j,t;
                                _vektoranalysis3<_tg> va;
                                _vektor3<_tg> h,e;
                                _vektor3<_tg> null;
                                _knochen*neu=0;
                                _knochen*te=0;
                                //_extremitaetssegment*seg;
                                //------------------------------------------------------------------
                                unterrumpf[0] =new _knochen(this,this,0,_vektor3<double>(-1,-1,-1)); 
                                unterrumpf[1] =new _knochen(this,this,0,_vektor3<double>(+1,-1,-1)); 
                                unterrumpf[2] =new _knochen(this,this,0,_vektor3<double>(+1,-1,+1)); 
                                unterrumpf[3] =new _knochen(this,this,0,_vektor3<double>(-1,-1,+1)); 
                                rumpf=new _knochen(this,this,0,_vektor3<double>(0,1,0)); 
                                
            
                                for(t=0;t<4;t++){
                                 tentakel[t]=new _extremitaet(this,unterrumpf[t]);
                                 neu=unterrumpf[t];
                                 for(i=0;i<16;i++){
                                  neu=new _knochen(this,neu,neu,_vektor3<_tg>(0.2,0,0));
                                  tentakel[t]->einhaengen(neu);
                                 };
                                 
                                 //knochen in den normalszustand ausrichten modellierung der knochen entlang x-achse als basislinie
                                 tentakel[t]->ort(0,_vektor3<_tg>(0,0,0)+unterrumpf[t]->ortspitze());
                                 tentakel[t]->ort(1,_vektor3<_tg>(2,0,0)+unterrumpf[t]->ortspitze());//raum MUSS später länge 2 haben !                                 
                                 tentakel[t]->vektor(0,_vektor3<_tg>(1,4,0));
                                 tentakel[t]->vektor(1,_vektor3<_tg>(3,0,0));
                                 tentakel[t]->transformieren();
                                 tentakel[t]->reinitialisierenknochen();
                                 tentakel[t]->initialisierengammaortnormal();
                                 //in den gestreckten zustand ausrichten
                                 tentakel[t]->ausrichtenknochen(_vektor3<_tg>(1,0,0));
                                 tentakel[t]->initialisierengammaortgestreckt();      
                                 //am sinus ausrichten, knochenlängen beibehalten
                                 tentakel[t]->ausrichtenknochensinus(_vektor3<_tg>(0,1,0),180);//immer auf und ab (sägezahn)
                                 tentakel[t]->initialisierengammaortgestaucht();        
                                 tentakel[t]->initialisierengammavektoren();                      
                                 
                                 
                                 h=unterrumpf[t]->vektor();
                                 h.setzenkomponente(1,0);
                                 tentakel[t]->ort(0,unterrumpf[t]->ortspitze());
                                 tentakel[t]->ort(1,unterrumpf[t]->ortspitze()+unterrumpf[t]->vektor()+_vektor3<_tg>(0,-2,0));
                                 tentakel[t]->vektor(0,h*5);
                                 tentakel[t]->vektor(1,_vektor3<_tg>(0,-1,0));
                                 tentakel[t]->transformieren();
                                 tentakel[t]->initialisierenraum(2);
                                 tentakel[t]->interpolationgamma();
                                 
                                 
                                 
                                 
                                 te=neu;
                                 for(i=0;i<3;i++) {//dreifingen
                                  finger[t][i]=new _extremitaet(this,te);
                                  h.setzen(1,0,0);
                                  h.roty(120*i+t*90.0f);
                                  neu=te;
                                  for(j=0;j<10;j++){//5 segmente pro finger
                                   neu=new _knochen(this,neu,neu,h*0.07);
                                   finger[t][i]->einhaengen(neu);
                                  };
                                  finger[t][i]->ort(0,te->ortspitze());
                                  finger[t][i]->ort(1,te->ortspitze()+h*1.2f+_vektor3<_tg>(0,-1.5f,0));
                                  finger[t][i]->vektor(0,h*2);
                                  finger[t][i]->vektor(1,h*2);                                  
                                  finger[t][i]->transformieren();
                                  finger[t][i]->initialisierenraum(_vektor3<_tg>(finger[t][i]->ort(0)-finger[t][i]->ort(1)).laenge());
                                 };
                                 tentakel[t]->visualisieren();
                                };
                                gehezumspieler=true;
                                letztewahl=0;
                                for(t=0;t<4;t++){
                                 wsoll[t]=wist[t]=0;
                                };
};
_corundorakel::~_corundorakel(){
};
void _corundorakel::initialisieren(){
};
void _corundorakel::schreiten(const unsigned int i,const _vektor3<_tg>&v){
                                int j;
                                _listenknoten<_knochen>*kit;
                                _listenknoten<_knochen>*kitf;
                                _extremitaet*es;
                                _extremitaet*esf;
                                //-----------------------
                                es=tentakel[i];
                                es->knochenliste()->anfang(kit);
                                es->knochenliste()->vorheriges(kit);
                                 
                                es->animationort(1)->ort(0,kit->objekt()->ortspitze());
                                es->animationort(1)->ort(1,es->animationort(1)->ort(0)+v);//_skelett::ort()+unterrumpf[i]->vektor()+es->richtung(0)+v);
                                es->animationort(1)->vektor(0,_vektor3<_tg>(0,5,0));
                                es->animationort(1)->vektor(1,_vektor3<_tg>(0,-5,0));
                                 
                                es->animationvektor(1)->ort(0,_vektor3<_tg>(0,0,0));
                                es->animationvektor(1)->ort(1,_vektor3<_tg>(0,0,0));
                                es->animationvektor(1)->vektor(0,_vektor3<_tg>(0,0,0));
                                es->animationvektor(1)->vektor(1,_vektor3<_tg>(0,0,0));
                                 
                                _zufallsgenerator<_tg> zg;
                                _tg s=0.1;//zg.berechnen(,0.07);
                                 
                                es->animationortiterator(1,0);
                                es->animationortschritt(1,s);
                                es->animationortaktivitaet(1,true);
                                
                                es->animationvektoriterator(1,0);
                                es->animationvektorschritt(1,s);
                                es->animationvektoraktivitaet(1,true);                                 
                                 
                                //finger ort 1 animation
                                for(j=0;j<3;j++){
                                 esf=finger[i][j];
                                 esf->knochenliste()->anfang(kitf);
                                 esf->knochenliste()->vorheriges(kitf);
                                 esf->animationort(1)->ort(0,kitf->objekt()->ortspitze());
                                 esf->animationort(1)->ort(1,es->animationort(1)->ort(0)+v+esf->richtung(0));
                                 esf->animationort(1)->vektor(0,_vektor3<_tg>(0,3,0));
                                 esf->animationort(1)->vektor(1,_vektor3<_tg>(0,-3,0));
                                
                                 _vektor3<_tg> hh=esf->richtung(0);
                                 hh.setzenkomponente(1,0);
                                 esf->animationvektor(1)->ort(0,hh*2);
                                 esf->animationvektor(1)->ort(1,_vektor3<_tg>(0,-5,0));
                                 esf->animationvektor(1)->vektor(0,_vektor3<_tg>(0,0,0));
                                 esf->animationvektor(1)->vektor(1,_vektor3<_tg>(0,0,0));
                                
                                 esf->animationortiterator(1,0);
                                 esf->animationortschritt(1,s);
                                 esf->animationortaktivitaet(1,true);
                                  
                                 esf->animationvektoriterator(1,0);
                                 esf->animationvektorschritt(1,s*2);
                                 esf->animationvektoraktivitaet(1,true);                                 
                                };
};
void _corundorakel::schreitenzufall(const unsigned int i){
                                _vektor3<_tg> zu;
                                zu.zufall();
                                zu*=0.3;
                                zu.setzenkomponente(1,fabs(zu[1])+0.2);
                                zu.setzenkomponente(0,zu[0]*10);
                                zu.setzenkomponente(2,zu[2]*10);
                                schreiten(i,zu);
};
void _corundorakel::animieren(){
						    	_vektor3<_tg> v;
                                _vektor3<_tg> te[4];
                                _vektor3<_tg> sollort;
                                //--------------------
                                for(int k=0;k<4;k++){
                                // _extremitaetssegment*est;
                                 _listenknoten<_knochen>*kit;
                                 //tentakel[k]->anfang(est);
                                 tentakel[k]->knochenliste()->anfang(kit);
                                 tentakel[k]->knochenliste()->vorheriges(kit);
                                 te[k]=kit->objekt()->ortspitze();
                                 sollort+=te[k]-tentakel[k]->richtung(0)-unterrumpf[k]->vektor();
                                };
                                sollort*=0.25;
                                //port+=(sollort-port)*0.09;
                                v=(sollort-port);
                              //  v.normalisieren();
                                impuls+=v*0.09;
                                
                              
                              
                              
		    					
			    				_win::_tastatur kb;
					    		if(kb.taste(75)){
 							     v.zufall();
     							 v*=0.7;//stoßkraft;
	    						 impuls=v;
		    					};			
		    					if(kb.taste(65)){	
		    					 port=port-_vektor3<_tg>(0,0.01,0);
		    					};		    	
		    					if(kb.taste(66)){	
		    					 port=port+_vektor3<_tg>(0,0.01,0);
		    					};		    	
		    					if(kb.taste(67)){	
		    					 port=port+_vektor3<_tg>(0,0,0.01);
		    					};		    	
		    					if(kb.taste(68)){	
		    					 port=port-_vektor3<_tg>(0,0,0.01);
		    					};		    	
		    					if(kb.taste(69)){	
		    					 port=port+_vektor3<_tg>(0.01,0,0);
		    					};		    	
		    					if(kb.taste(70)){	
		    					 port=port-_vektor3<_tg>(0.01,0,0);
		    					};		    	
    						ort(port+verschiebung);

			    				impuls+=-verschiebung*federkraft;//federkraft 20%
				    	        verschiebung+=impuls;
					    		impuls*=traegheitsdaempfung;//trägheitsdämpfer 10%


                               // dreheny(0.06);








                                _skelett::animieren();
                           //     if(gehezumspieler){
                            //     if(corundwelt->spieler){
                                 /* _vektor3<_tg> h;
                                  h=(corundwelt->spieler->_kollidierbarkugel::ort()+_vektor3<_tg>(0,3,0))-ort();
                                  h.normalisieren();
                                  h*=0.1;
                                  bewegen(h);*/
                             //    };
                            //    };
                              //  ausloesenschreiten();
                                
                                //_extremitaetssegment*es;
                                //_extremitaetssegment*esf;
                                int i,j;
                                for(i=0;i<4;i++){
                                 //if(tentakel[i]->anfang(es)){ 
                                  if(tentakel[i]->animationortaktivitaet(1)==false) {
                                  }else{
                                   for(j=0;j<3;j++){
                                    //if(finger[i][j]->anfang(esf)){ 
                                     if(finger[i][j]->animationvektoraktivitaet(1)==false) {
                                      _vektor3<_tg> hh=finger[i][j]->richtung(0);
                                      hh.setzenkomponente(1,0);
                                      finger[i][j]->animationvektor(1)->ort(0,_vektor3<_tg>(0,-5,0));
                                      finger[i][j]->animationvektor(1)->ort(1,hh*2);
                                      finger[i][j]->animationvektor(1)->vektor(0,_vektor3<_tg>(0,0,0));
                                      finger[i][j]->animationvektor(1)->vektor(1,_vektor3<_tg>(0,0,0));
                                      finger[i][j]->animationvektoriterator(1,0);
                                      finger[i][j]->animationvektoraktivitaet(1,true);                                 
                                     };
                                    //};
                                   };
                                  };
                                 //};
                                };
                                transformieren();
};
void _corundorakel::ausloesenschreiten(){
                                if(gehezumspieler){
                                 if(corundwelt->spieler){
                                  _vektor3<_tg> sollfuss;
                                  _vektor3<_tg> istfuss;
                                  _vektor3<_tg> h;
                                  _vektor3<_tg> te[4];
                                 // _extremitaetssegment*est;
                                 // _extremitaetssegment*esf;
                                  _listenknoten<_knochen>*kit;
                                  for(int k=0;k<4;k++){
                                   //tentakel[k]->anfang(est);
                                   tentakel[k]->knochenliste()->anfang(kit);
                                   tentakel[k]->knochenliste()->vorheriges(kit);
                                   te[k]=kit->objekt()->ortspitze();
                                  };



                                  
                                  unsigned int wahl=5;
                                  _vektor3<_tg> wahlsollort;
                                  _vektor3<_tg> wahlistort;
                                  _tg hl=0;
                                  unsigned int anzbew=0;
                                  for(int t=0;t<4;t++){
                                   //tentakel[t]->anfang(est);
                                   if(tentakel[t]->animationortaktivitaet(1)==false){
                                    if(t!=letztewahl){
                                     istfuss=te[t];
                                     h=tentakel[t]->richtung(0);
                                     //finger[t][0]->anfang(esf);
                                     h+=finger[t][0]->richtung(0);
                                     h+=unterrumpf[t]->vektor();
                                     h.setzenkomponente(2,0);
                                     h.setzenkomponente(0,0);
                                     h*=-1;
                                     sollfuss=corundwelt->spieler->_kollidierbarkugel::ort()+h+tentakel[t]->richtung(0)+unterrumpf[t]->vektor();
                                     h=sollfuss-istfuss;
                                     
                                     
                                     
                                     
                                     if(h.laenge()>1){
                                      if(h.laenge()>hl){
                                       hl=h.laenge();
                                       wahl=t;
                                       wahlsollort=sollfuss;
                                       wahlistort=istfuss;
                                      };
                                     };
                                    };
                                   }else{ 
                                    anzbew++;
                                   };
                                  };
                                  
                                  if(wahl!=5){
                                   if(anzbew==0){         
                                    //schreiten zum spieler
                                    //***************** DEBUG ******************
                                    if(wist[wahl]) delete wist[wahl];
                                    if(wsoll[wahl]) delete wsoll[wahl];
                                    wist[wahl]=new _weltdebugkreuz(_corundfigur::welt,wahlistort,0.05,_vektor4<_to>(1,0,0,1));
                                    wsoll[wahl]=new _weltdebugkreuz(_corundfigur::welt,wahlsollort,0.05,_vektor4<_to>(0,1,1,1));
                                    //******************************************
                                    h=wahlsollort-wahlistort;
                                    _tg hl=h.laenge();;
                                    if(hl>2){
                                     h.normalisieren();
                                     h*=2;
                                    };
                                    /*  if(hl>1)*/ 
                                    schreiten(wahl,h); 
                                    letztewahl=wahl;
                                   };  
                                  };
                                 };
                                };
};
void _corundorakel::bewegen(const _vektor3<_tg>&v){
                                _skelett::bewegen(v);
};
void _corundorakel::drehenx(double w){
                                _skelett::vektor(0).rotx(w);
                                _skelett::vektor(1).rotx(w);
                                _skelett::vektor(2)=_skelett::vektor(0)%_skelett::vektor(1);
};
void _corundorakel::dreheny(double w){
                                _skelett::vektor(0).roty(w);
                                _skelett::vektor(1).roty(w);
                                _skelett::vektor(2)=_skelett::vektor(0)%_skelett::vektor(1);
                                int t,f;
                                //_extremitaetssegment*est;
                                //_extremitaetssegment*esf;
                                for(t=0;t<4;t++){
                                 //tentakel[t]->anfang(est);
                                 tentakel[t]->vektor(0).roty(w);
                                 for(f=0;f<3;f++){
                                  //finger[t][f]->anfang(esf);
                                  finger[t][f]->vektor(0).roty(w);
                               //   esf->vektor(1).roty(w);
                                 };
                                };
                                
};
void _corundorakel::drehenz(double w){
                                _skelett::vektor(0).rotz(w);
                                _skelett::vektor(1).rotz(w);
                                _skelett::vektor(2)=_skelett::vektor(0)%_skelett::vektor(1);
};
void _corundorakel::transformieren(){
                                //_extremitaetssegment*es;
                                //_extremitaetssegment*esf;
                                int i,j,k;
                                _vektor3<_tg> tos;
                                _vektor3<_tg> h;
                                _listenknoten<_knochen>*kit;
                                //-----------------------------
                                for(k=0;k<3;k++) _skelett::transformieren(rumpf->vektororiginal(),rumpf->vektor());
                                for(i=0;i<4;i++){
                                 //tentakel[i]->anfang(es);
                                 for(k=0;k<3;k++) _skelett::transformieren(tentakel[i]->richtungoriginal(k),tentakel[i]->richtung(k));
                                 tentakel[i]->richtung0normal()=tentakel[i]->richtung(0);
                                 tentakel[i]->richtung0normal().normalisieren();
                                 for(k=0;k<3;k++) _skelett::transformieren(unterrumpf[i]->vektororiginal(),unterrumpf[i]->vektor());
                                 tentakel[i]->ort(0,ort()+unterrumpf[i]->vektor());
                                 //es->ort(1,ort()+unterrumpf[i]->vektor()+
                                 tentakel[i]->transformieren();
                                 tentakel[i]->knochenliste()->anfang(kit);
                                 tentakel[i]->knochenliste()->vorheriges(kit);
                                 for(j=0;j<3;j++){
                                  
                                  //finger[i][j]->anfang(esf);
                                  for(k=0;k<3;k++) _skelett::transformieren(finger[i][j]->richtungoriginal(k),finger[i][j]->richtung(k));
                                  finger[i][j]->ort(0,kit->objekt()->ortspitze());
                                  //es->ort(1,

                                  finger[i][j]->transformieren();
                                 };
                                };
                                _skelett::transformierenvertex();
};
void _corundorakel::kollision(_kollidierbar*,_polygon*){
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S P I N N E
//******************************************************************************************************************************************************************************************************
_corundspinne::_corundspinne(_corundwelt*we,_vektor3<double> o):_skelett(we->welt,o,_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1)),_listenknotenbasis<_corundspinne>(we){
                                int s,c;
                                _zufallsgenerator<_tg> zu;
                                //-----------
                                kamverankert=false;
							    port=o;
							    oa=true;
							    vektor.setzen(0.0,0,0.0);
							    verschiebung.setzen(0,0,0);
							    impuls.setzen(0,0,0);
                                time=tr=0;
                                corundwelt=we;
                                welt=we->welt;
                                pzone=0;

                                vorderleib =new _knochen(this,this, 0, _vektor3<double>(0,0,1));    
                                hinterleib =new _knochen(this,this, 0, _vektor3<double>(0,-0.1,-1.5));    
                                warze[1][0] =new _knochen(this,hinterleib, hinterleib, _vektor3<double>(+0.05,0.05,-0.05));    
                                warze[0][0] =new _knochen(this,hinterleib, hinterleib, _vektor3<double>(-0.05,0.05,-0.05));    
                                warze[1][1] =new _knochen(this,warze[1][0], warze[1][0], _vektor3<double>(+0.03,0.05,-0.03));    
                                warze[0][1] =new _knochen(this,warze[0][0], warze[0][0], _vektor3<double>(-0.03,0.05,-0.03));    
                                warze[1][2] =new _knochen(this,warze[1][1], warze[1][1], _vektor3<double>(+0.01,0.05,-0.01));    
                                warze[0][2] =new _knochen(this,warze[0][1], warze[0][1], _vektor3<double>(-0.01,0.05,-0.01));    
    
                                taster[1][0] =new _knochen(this,vorderleib, vorderleib, _vektor3<double>(+0.08,0.05,0.05));    
                                taster[0][0] =new _knochen(this,vorderleib, vorderleib, _vektor3<double>(-0.08,0.05,0.05));    
                                taster[1][1] =new _knochen(this,taster[1][0], taster[1][0], _vektor3<double>(+0.03,0.04,0.2));    
                                taster[0][1] =new _knochen(this,taster[0][0], taster[0][0], _vektor3<double>(-0.03,0.04,0.2));    
                                taster[1][2] =new _knochen(this,taster[1][1], taster[1][1], _vektor3<double>(-0.01,-0.2,0.01));    
                                taster[0][2] =new _knochen(this,taster[0][1], taster[0][1], _vektor3<double>(+0.01,-0.2,0.01));    
                           
                                rumpf[1][0] =new _knochen(this,this, 0, _vektor3<double>( 0.4,0,0.8));    
                                rumpf[0][0] =new _knochen(this,this, 0, _vektor3<double>(-0.4,0,0.8));    
                                rumpf[1][1] =new _knochen(this,this, 0, _vektor3<double>( 0.5,0,0.6));    
                                rumpf[0][1] =new _knochen(this,this, 0, _vektor3<double>(-0.5,0,0.6));    
                                rumpf[1][2] =new _knochen(this,this, 0, _vektor3<double>( 0.5,0,0.4));    
                                rumpf[0][2] =new _knochen(this,this, 0, _vektor3<double>(-0.5,0,0.4));    
                                rumpf[1][3] =new _knochen(this,this, 0, _vektor3<double>( 0.4,0,0.2));    
                                rumpf[0][3] =new _knochen(this,this, 0, _vektor3<double>(-0.4,0,0.2));                                
                             
                                for(s=0;s<2;s++)for(c=0;c<4;c++) bein[s][c]=new _corundspinnenbein(this,rumpf[s][c]);
                                
                                bein[0][0]->setzen(+0.10,+0.40,+0.40,  -0.20,-0.20,+0.70,  -0.15,-0.30,+0.40,  -0.10,-0.05,+0.20);
                                bein[1][0]->setzen(-0.10,+0.40,+0.40,  +0.20,-0.20,+0.70,  +0.15,-0.30,+0.40,  +0.10,-0.05,+0.20);
                                bein[0][1]->setzen(-0.10,+0.50,+0.30,  -0.60,-0.20,+0.50,  -0.25,-0.40,+0.15,  -0.20,-0.05,+0.10);
                                bein[1][1]->setzen(+0.10,+0.50,+0.30,  +0.60,-0.20,+0.50,  +0.25,-0.40,+0.15,  +0.20,-0.05,+0.10);
                                bein[0][2]->setzen(-0.30,+0.60,-0.10,  -0.70,-0.20,-0.20,  -0.30,-0.50,-0.10,  -0.20,-0.05,-0.10);
                                bein[1][2]->setzen(+0.30,+0.60,-0.10,  +0.70,-0.20,-0.20,  +0.30,-0.50,-0.10,  +0.20,-0.05,-0.10);
                                bein[0][3]->setzen(-0.20,+0.50,-0.30,  -0.30,-0.20,-0.80,  -0.15,-0.40,-0.50,  -0.05,-0.05,-0.25);
                                bein[1][3]->setzen(+0.20,+0.50,-0.30,  +0.30,-0.20,-0.80,  +0.15,-0.40,-0.50,  +0.05,-0.05,-0.25);

                                
							    bein[0][0]->ausrichtungwinkel=-0.4;//schiefe ausrichtungsebenen
							    bein[1][0]->ausrichtungwinkel=+0.4;
							    bein[0][3]->ausrichtungwinkel=-0.4;
							    bein[1][3]->ausrichtungwinkel=+0.4;      
    							
    							
    							                      
                                normale.setzen(0,1,0);
                                richtung.setzen(0,0,1);
                                seite=normale%richtung;
                                _netz*n;
                                for(s=0;s<2;s++)
                                for(c=0;c<4;c++) {
                                 bein[s][c]->initialisieren();
                                 bein[s][c]->schreitendx=zu.berechnen(0.005,0.01);
                                 //_geometriequader*gq=new _geometriequader(0,_vektor3<_tg>(0,-0.1,-0.1),_vektor3<_tg>(bein[s][c]->laengemaxtheoretisch,0,0),_vektor3<_tg>(0,0.2,0),_vektor3<_tg>(0,0,0.2),corundwelt->textur[9]);
                                 //gq->aufloesung(_vektor<unsigned int>(8,1,1));
                                 //gq->texturkoordinatenlaenge(8,1,1);
                                 //n=gq->erzeugen();
                                 _geometriekonus*gk=new _geometriekonus(0,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0.1,0,0),_vektor3<_tg>(0,bein[s][c]->laengemaxtheoretisch,0),_vektor3<_tg>(0,0,0.1),corundwelt->textur[120]);
                                 gk->aufloesung(7,8);
                                 gk->texturkoordinatenlaenge(2,1,1,1);
                                 n=gk->erzeugen();

								 n->rotieren(_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,1,0),90);
								 n->rotieren(_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,1),90);
                                 n->keinbsp(true);
                                 n->subtraktiv(false);
                                 n->schattenvolumen(true);
                               //  n->skalierenkonisch(_vektor3<_tg>(0,0,0),_vektor3<_tg>(bein[s][c]->laengemaxtheoretisch,0,0),1,0.1);
                                 n->einhaengen(welt);
                                 //delete gq;
                                 delete gk;
                                 bein[s][c]->ausrichtenlinear(_vektor3<_tg>(1,0,0));
                                 assoziieren(n,_vektor3<_tg>(0,0,0),bein[s][c]->bein[0],true);
                                 bein[s][c]->animieren();
                                };
                                
                                _geometriekugel*go;
                                go=new _geometriekugel(0,_vektor3<_tg>(0,-0.05,-0.75),_vektor3<_tg>(0.6,0,0),_vektor3<_tg>(0,0.3,0),_vektor3<_tg>(0,0,0.75),corundwelt->textur[119]);
                                go->aufloesung(10,4);
                                n=go->erzeugen();
                                delete go;
                                n->rotieren(_vektor3<_tg>(0,0,-0.75),_vektor3<_tg>(1,0,0),5);
                                n->keinbsp(true);
                                n->subtraktiv(false);
                                n->schattenvolumen(true);
                                n->einhaengen(welt);
                               // hinterleib->ausrichtenlinear(_vektor3<_tg>(
                                assoziieren(n,_vektor3<_tg>(0,0,0),hinterleib,false);
                                hinterleib->animieren();
                                
                                go=new _geometriekugel(0,_vektor3<_tg>(0,0,0.5),_vektor3<_tg>(0.5,0,0),_vektor3<_tg>(0,0.2,0),_vektor3<_tg>(0,0,0.5),corundwelt->textur[118]);
                                go->aufloesung(10,3);
                                n=go->erzeugen();
                                delete go;
                                n->keinbsp(true);
                                n->subtraktiv(false);
                                n->schattenvolumen(true);
                                n->einhaengen(welt);
                                assoziieren(n,_vektor3<_tg>(0,0,0),vorderleib,false);
                                vorderleib->animieren();
                                
                                
                                
                                transformieren();
                                aktualisierennetze();
                                ws=new _weltdebugkugel(welt,ort(),0.7f,_vektor4<float>(0.2f,0.8f,1.0f,0));
};
_corundspinne::~_corundspinne(){
                                int s,c;
                                for(s=0;s<2;s++)
                                for(c=0;c<4;c++){
                                 //  delete fusskugel[s][c];
                                 if(bein[s][c]) delete bein[s][c];
                                };
};
void _corundspinne::kollision(_kollidierbar*,_polygon*){
};
void _corundspinne::zone(_partition::_zone*z){
                                pzone=z;
};
void _corundspinne::initialisieren(){
                                if(welt->anfang(pzone)){
                                 //kollisionskopplung vornehmen
                                 _listenknoten<_netz>*nit;
                                 _polygon*pit;
                                 if(netze()->anfang(nit))do{
                                  pzone->einfuegenintern(nit->objekt());
                                  if(nit->objekt()->anfang(pit))do{
                                   pit->::_liste<_kollisionskopplung>::aushaengen();
                                   pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                  }while(nit->objekt()->naechstes(pit));
                                  nit->objekt()->erzeugenvertexlicht(pzone);
                                 }while(netze()->naechstes(nit));
                                 //_partition::_zone*zit;
                                 //if(welt->welt->anfang(zit))do{
                                 lokussektor=pzone->sektor(ort());
                                 //}while(welt->welt->naechstes(zit));                             
                                };
};
void _corundspinne::drehenx(double w){
                                richtung.rotx(w);
                                normale.rotx(w);
                                seite=normale%richtung;
                                transformieren();
};
void _corundspinne::dreheny(double w){
                                richtung.roty(w);
                                normale.roty(w);
                                seite=normale%richtung;
                                transformieren();
};
void _corundspinne::drehenz(double w){
                                richtung.rotz(w);
                                normale.rotz(w);
                                seite=normale%richtung;
                                transformieren();
};
void _corundspinne::transformieren(){//alles ausrichten
                                int s,c;
                                transformieren(vorderleib->vektororiginal(),vorderleib->vektor());
                                transformieren(hinterleib->vektororiginal(),hinterleib->vektor());
                                for(s=0;s<2;s++){
                                 for(c=0;c<4;c++){
                                  transformieren(rumpf[s][c]->vektororiginal(),rumpf[s][c]->vektor());
                                  bein[s][c]->transformieren();
                                  //transformieren(bein[s][c][0]->vektororiginal(),bein[s][c][0]->vektor());
                                 };
                                 for(c=0;c<3;c++){
                                  transformieren(taster[s][c]->vektororiginal(),taster[s][c]->vektor());
                                  transformieren(warze[s][c]->vektororiginal(),warze[s][c]->vektor());
                                 };
                                };
                                transformierenvertex();
};
void _corundspinne::transformieren(_vektor3<double>&v,_vektor3<double>&e){
                                e=seite*v[0]+normale*v[1]+richtung*v[2];
};
void _corundspinne::animieren(){
                                int s,c;
    							_win::_tastatur kb;
	    						_kamera<>*cam;
    							_vektor3<double> v;
	    						double vl;
		    					double ss;
			    				_vektor3<double> front;
				    			_vektor3<double> seite;
	    						//-----------------
                                _skelett::animieren();
                                tr+=1; 
                                time=tr;//sin(tr*_ph)*1000;
    							verschiebung-=vektor;
		    					welt->anfang(cam);
                                normaleanpassen(oa);
                                transformieren();
							    oa=true;
							    front=richtung;
							    front.normalisieren();
							    front*=0.02;
							    seite=front%normale;
							    seite.normalisieren();
							    seite*=0.02;
							    ss=1;
							    vektor.setzen(0,0,0);
    							if(kb.leertaste()){
	    						 if(kamverankert){
		    					  kamverankert=false;
			    				 }else{
				    			  kamverankert=true;
					    		 };
   						         while(kb.leertaste());
    							};
	    						if(kb.shift()){
		    					 ss=3;
			    				};
				    			if(kb.taste(65)){
    							 vektor+=front*ss;
	    						 oa=false;
		    					};
			    				if(kb.taste(68)){
    							 vektor-=front*ss;
	    						 oa=false;
		    					};
			    				if(kb.taste(87)){
				    			 vektor+=seite*ss;
					    		 oa=false;
						    	};
    							if(kb.taste(83)){
	    						 vektor-=seite*ss;
		    					 oa=false;
			    				};
				    			
						    	if(kb.taste(88)){
					    		 drehenx(0.3*ss);
						    	// if(kamverankert) cam->yaw(cam->yaw()-0.3*ss);
							     oa=false;
    							};
	    						if(kb.taste(89)){
		    					 drehenx(-0.3*ss);
			    				// if(kamverankert) cam->yaw(cam->yaw()+0.3*ss);
				    			 oa=false;
					    		};
							
    							if(kb.taste(67)){
	    						 dreheny(0.3*ss);
		    					// if(kamverankert) cam->rot(cam->rot()-0.3*ss);
			    				 oa=false;
				    			};
					    		if(kb.taste(86)){
						    	 dreheny(-0.3*ss);
							    // if(kamverankert) cam->rot(cam->rot()+0.3*ss);
    							 oa=false;
	    						};
							
		    					if(kb.taste(70)){
			    				 drehenz(0.3*ss);
				    			// if(kamverankert) cam->rol(cam->rol()-0.3*ss);
					    		 oa=false;
						    	};
    							if(kb.taste(71)){
	    						 drehenz(-0.3*ss);
		    					// if(kamverankert) cam->rol(cam->rol()+0.3*ss);
			    				 oa=false;
				    			};
						    	cam->aktualisieren();
					    		if(kb.taste(75)){
 							     v.zufall();
     							 v*=0.4;//stoßkraft;
	    						 impuls=v;
		    					};
			    				
					    		port+=vektor;
						    	lokussektor=pzone->sektor(ort());
							    _vektor3<double> e;
    					/*		kollision(ort(),port+verschiebung,0.7,e);
	    						ort(e);*/
		    					ort(port+verschiebung);
			    				ws->ort(ort());
						    	
    							if(kamverankert) cam->ort(ort()+normale*0.3);
	    						v=-verschiebung;
		    					vl=v.laenge();
			    				impuls+=v*0.2;//federkraft 20%
				    	        verschiebung+=impuls;
					    		impuls*=0.9;//trägheitsdämpfer 10%
						    	for(s=0;s<2;s++)
                                for(c=0;c<4;c++) bein[s][c]->animieren();
                                _listenknoten<_netz>*nit;
                                if(netze()->anfang(nit))do{
                                 nit->objekt()->aktualisieren();
                                 nit->objekt()->aktualisierennetzschatten();
                                }while(netze()->naechstes(nit));
                                
                                
                                
                             //   animierenarsch();
};  
void  _corundspinne::animierenarsch(){
                                _vektor3<double> n;
                                _vektor3<double> a;
                                _vektor3<double> e;
                                //-----------------
                                n=rumpf[0][0]->vektor() % richtung;
                                double fb=((sin(3*tr*_ph)*0.5))*10;
                                V3.rotieren(n,hinterleib->vektororiginal(),fb,hinterleib->vektor());
                                V3.rotieren(n,vorderleib->vektororiginal(),-fb*0.6,vorderleib->vektor());                            
};
/*
void _spinne::sichernrumpf(int s,int c){
                            if(fixiert[s][c]) rumpfalt[s][c]=ort()+bein[s][c][0]->vektor();
};
                            // _vektor3<double> ns;
                             // _vektor3<double> nr;
                             // _vektor3<double> neueausr;
                             // _vektor3<double> neurumpf;
                             // if(war[s][c]) delete war[s][c];
                             // if(wan[s][c]) delete wan[s][c];
                             // anpassenausrichtung(n,nr,ns);
                             // h=ausrichtungoptimaloriginal[s][c];
                             // wan[s][c]=new _weltdebugpfeil(W,fuss[s][c],fuss[s][c]+n ,0.01,0.01,_vektor<float>(1,0,0));
                             // war[s][c]=new _weltdebugpfeil(W,fuss[s][c],fuss[s][c]+nr,0.01,0.01,_vektor<float>(0,0,1));
                             // neueausr=ns*h[0]+polygonfixiert[s][c]->normale()*h[1]+nr*h[2];
                             // h=bein[s][c][0]->vektororiginal();
                             // neurumpf=ns*h[0]+polygonfixiert[s][c]->normale()*h[1]+nr*h[2];;
                             // V3.lotpunktebene(vektor,_vektor3<double>(0,0,0),polygonfixiert[s][c]->normale(),lot,para);


                             // e=kurve[s][c].ort(1)-kurve[s][c].ort(0);
                             // e.normalisieren();
                             // if((e* *p)>-0.1f){

*/


void _corundspinne::normaleanpassen(bool ortanpassen){
                                _vektor3<double> solln;
                                _vektor3<double> sollo;
                                _vektor3<double> e;
                                _vektor3<double> a;
                                double anzahl,w;
                                int s,c;
                                //----------------
                                solln.setzen(0,0,0);
                                sollo.setzen(0,0,0);
                                anzahl=0;
                                for(s=0;s<2;s++)
                                for(c=0;c<4;c++){
                                 if(bein[s][c]->polygonfixiert){
                                  solln+=bein[s][c]->polygonfixiert->normale();
                                  sollo+=bein[s][c]->zielfuss-(rumpf[s][c]->vektor()+bein[s][c]->ausrichtungoptimal);
                                  anzahl+=1;
                                 };
                                };
                                if(anzahl>0){
                                 solln*=1.0f/anzahl;
                                 solln.normalisieren();
                                 sollo*=1.0f/anzahl;
                                }else{
                                 solln=normale;
                                 sollo=port;
                                };
                                
                                a=normale%solln;
                                w=-normale.winkel(solln);
                                w*=0.2;
                                if(w!=0){
                                 V3.rotieren(a,richtung,w,e);
                                 richtung=e;
                                 V3.rotieren(a,normale,w,e);
                                 normale=e;
                                 seite=normale%richtung;
                                };
                                
                                if(ortanpassen) {
                                e=(sollo)-(port);
                                //e.normalisieren();
                                port+=e*0.09;
                                };
                                // e=sollo-ort;
                                // ort+=e*0.03;
                                //normale=solln;
};
void _corundspinne::anpassenausrichtung(const _vektor3<double> neuenormale,_vektor3<double>&neuerichtung,_vektor3<double>&neueseite){
                                _vektor3<double> a;
                                _vektor3<double> e;
                                double w;
                            
                                neuerichtung=richtung;
                                neueseite=seite;
                                a=normale%neuenormale;
                                w=-normale.winkel(neuenormale);
                                if(w!=0){
                                 V3.rotieren(a,richtung,w,e);
                                 neuerichtung=e;
                                 //V3.rotieren(a,normale,w,e);
                                 //normale=e;
                                 neueseite=neuenormale%neuerichtung;
                                };
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S P I N N E N B E I N   
//******************************************************************************************************************************************************************************************************
_corundspinnenbein::_corundspinnenbein(_corundspinne*s,_knochen*k){
                                spinne=s;
                                wurzel=k;
                                for(int i=0;i<4;i++) bein[i]=0;     
                                fixiert=false;
                                polygonfixiert=0;
                                zielfuss.setzen(0,0,0);
							    ausrichtungwinkel=0;
                                wc=0;
                                fusssektor=0;
                                schreitenx=0;
                                schreitendx=0.05;
                                schreitmodus=+1;
                                schreitdurchlauf=1;
							    laengemin=0.05;
							    laengemax=1-0.05; 
                                wc=0;
                                was=0;
                                war=0;
                                wan=0;                                                           
};
_corundspinnenbein::~_corundspinnenbein(){
};
_knochen*_corundspinnenbein::operator[](const unsigned int i){
                                if(i<4) return(bein[i]); else return(bein[0]);
};
void _corundspinnenbein::setzen(_tg b0x,_tg b0y,_tg b0z,  _tg b1x,_tg b1y,_tg b1z,  _tg b2x,_tg b2y,_tg b2z,  _tg b3x,_tg b3y,_tg b3z){
                                bein[0]=new _knochen(spinne,wurzel ,wurzel ,_vektor3<_tg>(b0x,b0y,b0z));   
                                bein[1]=new _knochen(spinne,bein[0],bein[0],_vektor3<_tg>(b1x,b1y,b1z));   
                                bein[2]=new _knochen(spinne,bein[1],bein[1],_vektor3<_tg>(b2x,b2y,b2z));   
                                bein[3]=new _knochen(spinne,bein[2],bein[2],_vektor3<_tg>(b3x,b3y,b3z));   
};
void _corundspinnenbein::initialisieren(){
                                int b;
                                //----------
                                fixieren(0);
                                loesen();
                                fusskugel=new _kollidierbarkugel(spinne,spinne->welt,0,0,zielfuss,_vektor3<_tg>(0,0,0),0.0001);
                                schreitenx=0;
                                ingueltigerausrichtung=true;
                                laengemaxtheoretisch=0;
                                for(b=0;b<4;b++) laengemaxtheoretisch+=bein[b]->laengeoriginal();
                                ausrichtungoptimal.setzen(0,0,0);
                                for(b=0;b<4;b++) ausrichtungoptimal+=bein[b]->vektororiginal();
                                ausrichtungoptimaloriginal=ausrichtungoptimal;
                                laenge=ausrichtungoptimal.laenge()/laengemaxtheoretisch;
                                //ruderkurve initialisieren                             
							    kurve.ort(0,zielfuss);
							    kurve.ort(1,spinne->ort()+wurzel->vektor()+ausrichtungoptimal*(1+(schreitmodus*0.3)));
 							    kurve.vektor(0,spinne->normale* 3*schreitmodus);
  						        kurve.vektor(1,spinne->normale*-3*schreitmodus);
};
void _corundspinnenbein::transformieren(){
                                spinne->transformieren(ausrichtungoptimaloriginal,ausrichtungoptimal);            
};
void _corundspinnenbein::animieren(){
                            _vektor3<double> vbneu;
                            double vbneul;
                            double gamma;
                            _vektor3<double> q;
                           // double wn;
                            _vektor3<double> e;
                            _vektor3<double> rumpfl;
                            _vektor3<double> neu;
                            bool koll;
                            _polygon*kollpoly;
                            double blomax=bein[0]->laengeoriginal()+bein[1]->laengeoriginal()+bein[2]->laengeoriginal()+bein[3]->laengeoriginal();
                            double sicherheitslaenge=blomax*0.995;
                            //---------------
                            rumpfl=spinne->ort()+wurzel->vektor();
                            vbneu=rumpfl-zielfuss;
                            vbneul=vbneu.laenge();  
                            if(vbneul>sicherheitslaenge){
                             vbneu*=sicherheitslaenge/vbneul;
                             vbneul=sicherheitslaenge;  
                            };
                            gamma=vbneul/blomax;
                            //------------------------------------------------
                            
                            
                            
                            
                            
                            if(fixiert){
                            /* q=-vbneu;
                             q.normalisieren();  
                             e=ausrichtungoptimal;
                             e.normalisieren();                           
                             wn=q*e;
                             if((wn<0.8)||(gamma<laengemin)||(gamma>laengemax)){
                              if(vektor.laenge()>nahenull){
                               e=zielfuss-rumpfl;
                               e.normalisieren();
                               q=vektor;
                               q.normalisieren();
                               if((q*e)<0){
                                _vektor3<double> rumpflot;
                                double rumpflotl;
                                double schrittmax=ausrichtungoptimaloriginal.laenge();
                                double ebl;
                                polygonfixiert->normale();
                                _vektor3<double> v;
                                _vektor3<double> lot;
                                _vektor3<double> ziel;
                                _vektor3<double> neueausr;
                                double para;
                                _polygon*p=polygonfixiert;
                                _vektor3<double> ns;
                                _vektor3<double> nr;
                                _vektor3<double> h;
                                V3.lotpunktebene(rumpfl,p->mitte(),p->normale(),rumpflot,para);
                                rumpflotl=rumpflot.laenge();
                                ebl=sqrt(schrittmax*schrittmax + rumpflotl*rumpflotl);
                                spinne->anpassenausrichtung(p->normale(),nr,ns);
                                h=ausrichtungoptimaloriginal;
                                neueausr=ns*h[0]+polygonfixiert->normale()*h[1]+nr*h[2];
                                V3.lotpunktebene(neueausr,_vektor3<double>(0,0,0),p->normale(),lot,para);
                                neueausr=neueausr+lot;
                                neueausr.normalisieren();
                                neueausr*=ebl;
                                schreitenx=0;
                                schreitmodus=1;
                                schreitdurchlauf=0;
                                kurve.ort(0,zielfuss);
                                V3.lotpunktebene(vektor,_vektor3<double>(0,0,0),p->normale(),lot,para);
                                para=vektor.laenge()*45;
                                v=vektor+lot;
                                if(v.laenge()>0){
                                 v.normalisieren();
                                 v*=para;
                                };
                                ziel=rumpfl+rumpflot+neueausr+v;
                                if(was) delete was;
                                was=new _weltdebugpfeil(welt,zielfuss,ziel,0.01,0.01,_vektor4<float>(1,0,1,0));
                                kurve.ort(1,ziel);
                                e=kurve.ort(1)-kurve.ort(0);
                                double fn=e.laenge()*0.5;
                                if(fn>2) fn=2;
                                kurve.vektor(0,n*3*fn);
                                kurve.vektor(1,-n*2*fn);
                                loesen();	
                               };
                              };
						     };*/
							}else{
							 //---------------------------------- schreitmodus ---------------------------------
							 schreitenx+=schreitendx;
							 if(schreitenx<=1){
							  neu=kurve.berechnen(schreitenx);
							 // if(fusssektor){
							   _vektor3<double> f0=rumpfl-vbneu;
							   _vektor3<double> fn=neu-rumpfl;
							   double fnl=fn.laenge();
   							   if(fnl>sicherheitslaenge){
                                fn*=sicherheitslaenge/fnl;
							   };
							   fn+=rumpfl;
							   //zielfuss[s][c]+=fusssektor[s][c]->kollidierendervektor(f0,fn-f0,fusssektor[s][c],koll,kollpoly);
							   fusskugel->ort(zielfuss);
							   fusskugel->vektor(fn-f0);
							   koll=false;
							   kollpoly=0;
							  // if(fusskugel[s][c]->bewegen(_vektor3<double>(0,0,0))==false){
							  //  koll=true;
							  //  kollpoly=fusskugel[s][c]->schnittpunkt.polygon;
							 //  };
							   zielfuss=fusskugel->ort()   +fusskugel->vektor();
							 
							//   if(koll){
							 //   ausrichtenbein(s,c,vbneu,gamma);
							 //   fixieren(s,c,kollpoly);
							 //   schreitenx[s][c]=0;
							 //  }else{
							 //  };
							 // };
							 }else{
						  schreitdurchlauf+=1;
						//	  if(schreitdurchlauf[s][c]<6) {
							   //-------------------------------- rudern ---------------------------------------
							   schreitmodus*=-1;
							   kurve.ort(0,kurve.ort(1));
							   kurve.ort(1,rumpfl+ausrichtungoptimal*(1+(schreitmodus*0.3)));
 							   kurve.vektor(0,spinne->normale* 3*schreitmodus);
 							   kurve.vektor(1,spinne->normale*-3*schreitmodus);
  							   schreitenx=0;
  							   
				/*			  }else{
							   if(schreitdurchlauf[s][c]==6){
							    //-------------------------------- ruhezustand einleiten -----------------------
							    polygonfixiert[s][c]=0;
							    kurve[s][c].ort(0,kurve[s][c].ort(1));
 							    kurve[s][c].vektor(0,kurve[s][c].vektor(1));
							    kurve[s][c].ort(1,rumpf+ausrichtungoptimal[s][c]);
							    kurve[s][c].vektor(1,_vektor3<double>(0,0,0));
							    schreitenx[s][c]=0;
							    if(vektor.laenge()>nahenull) schreitdurchlauf[s][c]=0;
							   }else{
							    //------------------------------- ruhezustand ----------------------------------
							    kurve[s][c].ort(0,kurve[s][c].ort(1));
 							    kurve[s][c].vektor(0,kurve[s][c].vektor(1));
							    kurve[s][c].ort(1,rumpf+ausrichtungoptimal[s][c]);
							    kurve[s][c].vektor(1,_vektor3<double>(0,0,0));
							    schreitenx[s][c]=0;
							    if(vektor.laenge()>nahenull) schreitdurchlauf[s][c]=0;
							   };
							  };*/
							 };
							};
							ausrichten(vbneu,gamma);
                            
};
void _corundspinnenbein::ausrichtenlinear(const _vektor3<_tg>&v){
                                //in der regel ist v ein einheitsvektor
                                _vektor3<_tg> h;
                                for(int i=0;i<4;i++){
                                 bein[i]->vektor(v*bein[i]->laengeoriginal());
                                 bein[i]->ebene0(_vektor3<_tg>(0,1,0));
                                 h=bein[i]->ebene0()%v;
                                 h.normalisieren();
                                 bein[i]->ebene1(h);
                                };
};
void _corundspinnenbein::ausrichten(_vektor3<double>&vbneu,double&gamma){
                                //berechnung zur verankerung durchführen 
                                //_vektor3<double> vbneu;
                                _vektor3<double> rumpfneu;
    						    _vektor3<double> e;
                                double alpha[3];
                                _vektor3<double> gelenkneu[3];
                                double h[3];
                                double vbneul;
                                _vektor3<double> ziel=zielfuss;
                                double blo1=bein[0]->laengeoriginal();
                                double blo2=bein[1]->laengeoriginal();
                                double blo3=bein[2]->laengeoriginal();
                                double blo4=bein[3]->laengeoriginal();
                                double blomax=blo1+blo2+blo3+blo4;
                                double blon1=blo1/blomax;
                                double blon2=blo2/blomax;
                                double blon3=blo3/blomax;
                                double blon4=blo4/blomax;
                                double sicherheitslaenge=blomax*0.995;
                                //----------------------------------------------- KERNFUNKTION ZUR AUSRICHTUNG DER GELENKE DES BEINS
                                rumpfneu=spinne->ort()+wurzel->vektor();
                                vbneu=rumpfneu-ziel;
                                vbneul=vbneu.laenge();  
                                if(vbneul>sicherheitslaenge){
                                 vbneu*=sicherheitslaenge/vbneul;
                                 ziel=rumpfneu-vbneu;
                                 vbneul=sicherheitslaenge;  
                                };
                                laenge=gamma=vbneul/blomax;
                                alpha[0]=blon4*0.99f*(1-gamma*gamma)+ blon4*gamma;
                                alpha[1]=0.2f*(1-gamma) + (blon4+blon3)*gamma;
                                if(alpha[0]>( (blo4      -nahenull)/vbneul)) alpha[0]=((blo4-nahenull)/vbneul);
                                if(alpha[1]>(((blo4+blo3)-nahenull)/vbneul)) alpha[1]=(((blo4+blo3)-nahenull)/vbneul);
                                h[0]=sqrt(-pow(vbneul*alpha[0],2)           + pow(blo4,2));
                                h[1]=sqrt(-pow(vbneul*(alpha[1]-alpha[0]),2)+ pow(blo3,2));
						        e=(spinne->normale%vbneu);
						        e.normalisieren();
                                ausrichtung=e%vbneu; 
                                ausrichtung.normalisieren();
                                ausrichtung*=-1;
							    ausrichtung+=e*ausrichtungwinkel;
							    ausrichtung.normalisieren();
					            gelenkneu[0]=ziel+vbneu*alpha[0]+ausrichtung* h[0];
                                gelenkneu[1]=ziel+vbneu*alpha[1]+ausrichtung*(h[0]+h[1]);
                                //--------------------------------------------------- RESTANPASSUNG
                                _vektor3<double> v;
                                _vektor3<double> t;
                                _vektor3<double> q;
                                double l0,l1,vl0,vl;
                                l0=bein[1]->laengeoriginal();
                                l1=bein[0]->laengeoriginal();
                                v=rumpfneu-gelenkneu[1];
                                vl=v.laenge();
                                vl0=(((l1*l1)-(l0*l0)-(vl*vl))/(-2.0f*vl*l0))*l0;
                                t=gelenkneu[1]+v*(vl0/vl);
                                q=(vbneu%ausrichtung)%v;
                                q.normalisieren();
                                gelenkneu[2]=t+q*sqrt((l0*l0)-(vl0*vl0));
                                //--------------------------------------------------- SETZEN
                                //   new _weltdebugkreuz(spinne->welt,gelenkneu[1],0.01,_vektor4<_to>(1,0,0,1));
                                //   new _weltdebugkreuz(spinne->welt,gelenkneu[2],0.01,_vektor4<_to>(0,0,1,1));
                                bein[3]->vektor(ziel-gelenkneu[0]);
                                bein[2]->vektor(gelenkneu[0]-gelenkneu[1]);
                                bein[1]->vektor(gelenkneu[1]-gelenkneu[2]);
                                bein[0]->vektor(gelenkneu[2]-rumpfneu);
                                //raumvektoren anpassen
                                q=vbneu%ausrichtung;
                                q.normalisieren();
                                for(int i=0;i<4;i++){
                                 bein[i]->ebene1(q);
                                 e=bein[i]->vektor()%q;e.normalisieren();bein[i]->ebene0(e);
                                };
};
void _corundspinnenbein::fixieren(_polygon*p){
                                int i;
                                //----------
                                polygonfixiert=p;
                                fixiert=true;
                                zielfuss=spinne->ort()+wurzel->vektor();
                                for(i=0;i<4;i++){
                                 zielfuss+=bein[i]->vektor();
                                };
                                wc=new _weltdebugkreuz(spinne->welt,zielfuss,0.1,_vektor4<float>(1,0,0,0));
};  
void _corundspinnenbein::loesen(){
                                fixiert=false;
                                if(wc) {
                                 delete wc;
                                 wc=0;
                                };
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D H E B W E B E R
//******************************************************************************************************************************************************************************************************
_corundhebweber::_corundhebweber(_corundwelt*cw,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s):_corundskelett(cw,o,r,n,s){
};
_corundhebweber::~_corundhebweber(){
};
void _corundhebweber::initialisieren(){
};
void _corundhebweber::animieren(){
};
void _corundhebweber::transformieren(){
};
void _corundhebweber::kollision(_kollidierbar*,_polygon*){
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S P R I N G S P I N N E
//******************************************************************************************************************************************************************************************************
_corundspringspinne::_corundspringspinne(_corundwelt*cw,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s):_corundskelett(cw,o,r,n,s){
};
_corundspringspinne::~_corundspringspinne(){
};
void _corundspringspinne::initialisieren(){
};
void _corundspringspinne::animieren(){
};
void _corundspringspinne::transformieren(){
};
void _corundspringspinne::kollision(_kollidierbar*,_polygon*){
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D C A T W I E S E L 
//******************************************************************************************************************************************************************************************************
_corundcatwiesel::_corundcatwiesel(_corundwelt*cw,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s):_corundskelett(cw,o,r,n,s){
};
_corundcatwiesel::~_corundcatwiesel(){
};
void _corundcatwiesel::initialisieren(){
};
void _corundcatwiesel::animieren(){
};
void _corundcatwiesel::transformieren(){
};
void _corundcatwiesel::kollision(_kollidierbar*,_polygon*){
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D F L I E G E 
//******************************************************************************************************************************************************************************************************
_corundfliege::_corundfliege(_corundwelt*cw,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s):_corundskelett(cw,o,r,n,s){
};
_corundfliege::~_corundfliege(){
};
void _corundfliege::initialisieren(){
};
void _corundfliege::animieren(){
};
void _corundfliege::transformieren(){
};
void _corundfliege::kollision(_kollidierbar*,_polygon*){
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D M A D E 
//******************************************************************************************************************************************************************************************************
_corundmade::_corundmade(_corundwelt*cw,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s):_corundskelett(cw,o,r,n,s){
};
_corundmade::~_corundmade(){
};
void _corundmade::initialisieren(){
};
void _corundmade::animieren(){
};
void _corundmade::transformieren(){
};
void _corundmade::kollision(_kollidierbar*,_polygon*){
};