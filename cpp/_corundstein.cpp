//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundstein.cpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include "../hpp/_corundstein.hpp"

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N 
//******************************************************************************************************************************************************************************************************
_corundstein::_corundstein(_corundwelt*ow):_listenknotenbasis<_corundstein>(ow),_corundschaltkopplung(ow){
                                welt=ow;
                                verschiebbar=false;
                                status=0;
                                zaehler=0;
                                ort.setzen(0,0,0);
                                breite.setzen(1,1,1);
                                ton=0;
                                hauptfenster=0;
                                markierung=0;
                                _netz::subtraktiv(false);
                                _netz::keinbsp(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(150);
                                initialisieren();
};                                
_corundstein::_corundstein(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex,bool ver):_listenknotenbasis<_corundstein>(ow),_corundschaltkopplung(ow){
                                _geometriequader*gb;
                                _polygon*pit;
                                _tg nz;
                                if(ow) nz=ow->steinskalierung; else nz=nahenull;
                                welt=ow;
                                verschiebbar=ver;
                                status=0;
                                markierung=0;
                                zaehler=0;
                                hauptfenster=0;
                                ort.setzen(x-nz*0,y-nz*0,z-nz*0);
                                breite.setzen(wx+0*nz,wy+0*nz,wz+0*nz);
                               // if(welt)welt->_baumoctal<_corundstein,_tg>::einhaengen(this,x-0.1,x+0.1,y-0.1,y+0.1,z-0.1,z+0.1);//stein in den weltbaum eingehängt
                                gb=new _geometriequader(0/*welt->welt*/,ort,wx+0*nz,wy+0*nz,wz+0*nz,tex);
                                gb->texturkoordinatenlaenge(wx,wy,wz);
                                _netz*temp=gb->erzeugen();
                                L->schreiben("Stein wurde erzeugt");
                                _netz::vereinigen(temp);
                                if(welt) _netz::einhaengen(welt->welt);
                                _netz::verwendentextur(true); 
                                _netz::markierungpolygon(1);
                                _netz::subtraktiv(false);
                                _netz::anlegentexturkoordinaten(2);
                                _netz::lightmaptexelgroesse(1);
                                _netz::verwendentexturdynamisch(false);
                                if(ver)_netz::verschiebennormal(nz);
                                if(welt) _netz::farbeverbinder(welt->ambientlicht);
                                _netz::verknuepfenverbindervertexpolygon();
                                _netz::keinbsp(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(150);
                                _netz::verwendentextur(true);
                                _netz::anfang(pit);
                                delete gb;
                                ton=0;
                                if(welt) ton=new _corundton(ow,ow->tonverwaltung.ton(0),ort,_vektor3<_tg>(0,0,0));
                                if(welt) initialisieren();
};
_corundstein::_corundstein(_corundwelt*ow,_netz*netz):_listenknotenbasis<_corundstein>(ow),_corundschaltkopplung(ow){
                                _polygon*pit;
                                welt=ow;
                                verschiebbar=false;
                                status=0;
                                zaehler=0;
                                markierung=0;
                                hauptfenster=0;
                                if(netz->anfang(pit)){
                                 ort=pit->vertex()->ort();
                                };
                                breite.setzen(1,1,1);
                                _netz*temp=netz->duplizieren();
                                _netz::vereinigen(temp);
                                if(welt) _netz::einhaengen(welt->welt);
                                _netz::verwendentextur(true); 
                                _netz::markierungpolygon(1);
                                //_netz::verschiebennormal(ow->steinskalierung);
                                _netz::farbeverbinder(ow->ambientlicht);
                                _netz::verknuepfenverbindervertexpolygon();
                                _netz::keinbsp(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(50);
                                if(welt) initialisieren();
                                ton=0;
};
_corundstein::~_corundstein(){
                                _listenknoten<_corundgummiband>*it;
                                _corundgummiband*og;
                                _corundkugel*ok;
                                if(_liste<_corundgummiband>::anfang(it))do{
                                 og=it->objekt();
                                 ok=og->kugel;
                                 ok->_liste<_corundgummiband>::aushaengen(og);
                                }while(_liste<_corundgummiband>::naechstes(it));
                                _liste<_corundgummiband>::loeschen();

                                _listenknoten<_corundfeder>*fit;
                                _corundfeder*of;
                                if(_liste<_corundfeder>::anfang(fit))do{
                                 of=fit->objekt();
                                 ok=of->kugel;
                                 ok->_liste<_corundfeder>::aushaengen(of);
                                }while(_liste<_corundfeder>::naechstes(fit));
                                _liste<_corundfeder>::loeschen();
                                if(ton) delete ton;

};
void _corundstein::nachbereitenkonstruktion(){
};
void _corundstein::initialisieren(){
                                //kollisionskopplung vornehmen
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->::_liste<_kollisionskopplung>::aushaengen();
                                 pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                }while(_netz::naechstes(pit));
};                                
void _corundstein::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 status=1-status;
                                 //netz->farbeverbinder(_vektor4<_to>(_to(status),_to(status)/2.0f,_to(status)/4.0f,1));
                                 _vektor3<_tg> v=k->vektor();
                                 _tg vl=v.laenge();
                                 if(vl>0.1){
                                
                                  welt->psstaubwolke->generationsrate(10);
                                  welt->psstaubwolke->aktiv(true);
                                  welt->psstaubwolke->ort(k->schnittpunkt.kontakt);
                                  _vektor3<_tg> v=k->vektor();
                                  v.normalisieren();
                                  _vektor3<_tg> n=k->schnittpunkt.normale;
                                  welt->psstaubwolke->vektor(n*  0.7f*(n*v)*vl);
                                 };
                                };
                                if(ton) {
                                 ton->lautstaerke=k->vektor().laenge();
                                 ton->abspielen();
                                };
};
void _corundstein::zeichnen(_grafik*grafik){//nur für editor
                                _tg x0,x1,y0,y1,z0,z1;  
                                _netz::umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                _tg s=0.1;
                                x0+=s;
                                x1-=s;
                                y0+=s;
                                y1-=s;
                                z0+=s;
                                z1-=s;
                                grafik->transparenz(true);
                                _vektor4<_to> c(0.1,0,0.4,0.5);
                                grafik->linie(_vektor3<_tg>(x0,y0,z0),_vektor3<_tg>(x1,y0,z0),c);
                                grafik->linie(_vektor3<_tg>(x0,y0,z0),_vektor3<_tg>(x0,y1,z0),c);
                                grafik->linie(_vektor3<_tg>(x0,y0,z0),_vektor3<_tg>(x0,y0,z1),c);
                                grafik->linie(_vektor3<_tg>(x1,y1,z1),_vektor3<_tg>(x0,y1,z1),c);
                                grafik->linie(_vektor3<_tg>(x1,y1,z1),_vektor3<_tg>(x1,y0,z1),c);
                                grafik->linie(_vektor3<_tg>(x1,y1,z1),_vektor3<_tg>(x1,y1,z0),c);
};
void _corundstein::animieren(){
};
void _corundstein::schalten(){
};
void _corundstein::netzwahl(_netz*,int){
};
void _corundstein::figurwahl(_corundfigur*,int){
};
void _corundstein::knotenwahl(_corundknoten*,int){
};
char _corundstein::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundstein>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(ort);
                                r^=sd->ladenwert(breite);
                                r^=sd->ladenwert(status);
                                r^=sd->ladenwert(zaehler);
                                r^=sd->ladenwert(verschiebbar);
                                sd->ladenende();
                                return(r);

};
void _corundstein::speichern(_speicherbardynamisch<_corundstein>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(ort);
                                sd->speichernwert(breite);
                                sd->speichernwert(status);
                                sd->speichernwert(zaehler);
                                sd->speichernwert(verschiebbar);  
                                sd->speichernendeblock();
};
char _corundstein::assoziieren(_speicherbardynamisch<_corundstein>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundstein::beiknopfverkleinern(_guiereignisdaten*){
                                if(hauptfenster){
                                 _netz::verschiebennormal(hauptfenster->corundwelt->steinskalierung);
                                 hauptfenster->statusbar->text(2,L"Netz des Steins wurde um nahe null verkleinert.");
                                 hauptfenster->zeichnen();
                                };
};
void _corundstein::einhaengendialog(_dynamischerdialog*d){
                                _netz::einhaengendialog(d);
                                d->addierensektion(L"corundstein");
                                d->einhaengen(L"corundstein",L"Status",status);
                                
};
void _corundstein::auslesendialog(_dynamischerdialog*d){
                                _netz::auslesendialog(d);
                                d->auslesen(L"corundstein",L"Status",status);
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N C O R U N D
//******************************************************************************************************************************************************************************************************
_corundsteincorund::_corundsteincorund(_corundwelt*ow):_corundstein(ow),_corundschalter<_corundsteincorund>(ow){
                               symbol=0;
                               status=0;//0=geschlossen ,1= teiloffen, 2 =offen
                               texstatus=0;
                               zaehler=0;
                               tonpaargeoeffnet=new _corundton(ow,ow->tonverwaltung.ton(1),ort,_vektor3<_tg>(0,0,0));
                                
};
_corundsteincorund::_corundsteincorund(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex,unsigned int symb):_corundstein(ow,x,y,z,wx,wy,wz,tex,false),_corundschalter<_corundsteincorund>(ow){
                               symbol=symb;
                               status=0;//0=geschlossen ,1= teiloffen, 2 =offen
                               texstatus=0;
                               zaehler=0;
                               if(ow) tonpaargeoeffnet=new _corundton(ow,ow->tonverwaltung.ton(1),ort,_vektor3<_tg>(0,0,0)); else tonpaargeoeffnet=0;
};
_corundsteincorund::~_corundsteincorund(){
                               if(tonpaargeoeffnet) delete tonpaargeoeffnet;
};
void _corundsteincorund::kollision(_kollidierbar*k,_polygon*){
                                _corundwelt*welt=_corundstein::welt;
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                // L->schreiben("---------sdfksdjglksdj");
                                //if(t){
                                if(ton) {
                                 ton->lautstaerke=k->vektor().laenge();
                                 ton->abspielen();
                                };
                                bool partikel=false;
                                if(status==0){
                                 if(welt->teiloffen==0){
                                  status=1;
                                   zaehler=30;
                                  welt->teiloffen=this;
                                  partikel=true;
                                 }else{
                                  //untersuchen, ob die symbole passen
                                  if(welt->teiloffen->symbol==symbol){
                                   //beide in den permanentoffen status (2) überführen
                                   welt->teiloffen->status=2;
                                   welt->teiloffen->textur(welt->textur[23+1+welt->teiloffen->symbol]);
                                   status=2;
                                   _netz::textur(welt->textur[23+1+symbol]);
                                   //welt->corundpaargeoeffnet();
                                   //----------------- corund schaltung auslösen ------------------
                                   _corundschalter<_corundsteincorund>::schalten();
                                   welt->teiloffen->_corundschalter<_corundsteincorund>::schalten();
                                   welt->teiloffen=0;
                                   //--------------------------------------------------------------
                                   if(tonpaargeoeffnet) tonpaargeoeffnet->abspielen();
                                   
                                   
                                   welt->psstaubwolke->generationsrate(1000);
                                   welt->psstaubwolke->aktiv(true);
                                   welt->psstaubwolke->ort(k->schnittpunkt.kontakt);
                                   _vektor3<_tg> v=k->vektor();
                                   _tg vl=v.laenge();
                                   v.normalisieren();
                                   _vektor3<_tg> n=k->schnittpunkt.normale;
                                   welt->psstaubwolke->vektor(_vektor3<_tg>(0,1,0)+(n*  0.3*(n*v)));                                  
                                   
                                  }else{
                                   //this öffnen mwelt->teiloffen schließen
                                   welt->teiloffen->status=0;
                                   welt->teiloffen->texstatus=0;
                                   welt->teiloffen->zaehler=0;
                                   welt->teiloffen->textur(welt->textur[23]);
                                   
                                   welt->teiloffen=this;
                                   status=1;
                                   zaehler=30;
                                   partikel=true;
                                  };
                                 };
                                }else{
                                };
                                
                                if(partikel){
                                  welt->psfrage->aktiv(true);
                                  welt->psfrage->vektor(_vektor3<_tg>(0,0.5,0));
                                  welt->psfrage->ort(k->schnittpunkt.kontakt);
                                //};
                                };
                             
};
void _corundsteincorund::zeichnen(_grafik*g){
                                _corundstein::zeichnen(g);
                                _corundschalter<_corundsteincorund>::zeichnen(g);
};
void _corundsteincorund::animieren(){
                               gedrueckt=false;
                               if(status==1){
                                zaehler--;
                                if(zaehler<=0){
                                 texstatus=(1+symbol)-texstatus;
                                 textur(_corundstein::welt->textur[23+texstatus]);
                                 zaehler=30;
                                };
                               };
};
void _corundsteincorund::schalten(){

};
void _corundsteincorund::schaltenerstkontakt(){

};
char _corundsteincorund::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteincorund>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(symbol);
                                r^=sd->ladenwert(texstatus);
                                r^=_corundschalter<_corundsteincorund>::laden(fn,sd);
                                sd->ladenende();
                                return(r);
};
void _corundsteincorund::speichern(_speicherbardynamisch<_corundsteincorund>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(symbol);
                                sd->speichernwert(texstatus);
                                _corundschalter<_corundsteincorund>::speichern(sd);   
                                sd->speichernendeblock();
};
char _corundsteincorund::assoziieren(_speicherbardynamisch<_corundsteincorund>*sd){
                                sd->assoziierenverschachtelung();
                                _corundschalter<_corundsteincorund>::assoziieren(sd);
                                return(1);
};

void _corundsteincorund::einhaengendialog(_dynamischerdialog*d){
                                _corundschalter<_corundsteincorund>::dialogschaltkopplungswahl=hauptfenster->dsteincorundschaltkopplungswahl;
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Corund");
                                d->sektion(L"Corundstein Corund")->offen(true);
                                d->einhaengen(L"Corundstein Corund",L"Symbol",symbol);
                                d->einhaengen(L"Corundstein Corund",L"Textur Status",texstatus);
                                _corundschalter<_corundsteincorund>::einhaengendialog(d);
                                
};
void _corundsteincorund::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Corund",L"Symbol",symbol);
                                d->auslesen(L"Corundstein Corund",L"Textur Status",texstatus);
                                _corundschalter<_corundsteincorund>::auslesendialog(d);    
};



//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N  G U M M I B A N D
//******************************************************************************************************************************************************************************************************
_corundsteingummiband::_corundsteingummiband(_corundwelt*ow):_corundstein(ow){
                                staerke=1;
                                
};
_corundsteingummiband::_corundsteingummiband(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex,_tg st):_corundstein(ow,x,y,z,wx,wy,wz,tex,false){
                                staerke=st;
};
_corundsteingummiband::~_corundsteingummiband(){
};
void _corundsteingummiband::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 _listenknoten<_corundgummiband>*lngit;
                                 _corundgummiband*git;
                                 bool vorhanden=false;
                                 if(t->_liste<_corundgummiband>::anfang(lngit))do{
                                  git=lngit->objekt();
                                  if(git->stein==this) vorhanden=true;
                                 }while(t->_liste<_corundgummiband>::naechstes(lngit));
                                 if(vorhanden==false) {
                                  new _corundgummiband(t,this,staerke);
                                  _vektor3<_tg> h=k->schnittpunkt.normale;//t->ort()-(ort+breite*0.5);
                                  h*=0.3;
                                  welt->psstrahl->aktiv(true);
                                  welt->strahldauer=60;
                                  welt->psstrahl->vektor(h);
                                  welt->psstrahl->ort(k->schnittpunkt.kontakt);
                                  
                                 };
                                };
};
void _corundsteingummiband::schalten(){
                                if(welt->spieler){
                                 _corundkugel*t=welt->spieler;
                                 _listenknoten<_corundgummiband>*lngit;
                                 _corundgummiband*git;
                                 bool vorhanden=false;
                                 if(t->_liste<_corundgummiband>::anfang(lngit))do{
                                  git=lngit->objekt();
                                  if(git->stein==this) vorhanden=true;
                                 }while(t->_liste<_corundgummiband>::naechstes(lngit));
                                 if(vorhanden==false) {
                                  new _corundgummiband(t,this,staerke);
                                  _vektor3<_tg> h(0,0.2,0);
                                  welt->psstrahl->aktiv(true);
                                  welt->strahldauer=60;
                                  welt->psstrahl->vektor(h);
                                  welt->psstrahl->ort(_netz::mitte());
                                 };
                                };
};
char _corundsteingummiband::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteingummiband>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(staerke);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteingummiband::speichern(_speicherbardynamisch<_corundsteingummiband>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(staerke);
                                sd->speichernendeblock();
};                                
char _corundsteingummiband::assoziieren(_speicherbardynamisch<_corundsteingummiband>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteingummiband::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Gummiband");
                                d->sektion(L"corundstein Gummiband")->offen(true);
                                d->einhaengen(L"corundstein Gummiband",L"Stärke",staerke);
                                
};
void _corundsteingummiband::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Gummiband",L"Stärke",staerke);
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H E R E
//******************************************************************************************************************************************************************************************************
_corundsteinschere::_corundsteinschere(_corundwelt*ow):_corundstein(ow){
};
_corundsteinschere::_corundsteinschere(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex):_corundstein(ow,x,y,z,wx,wy,wz,tex,false){
};
_corundsteinschere::~_corundsteinschere(){
};
void _corundsteinschere::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 _listenknoten<_corundgummiband>*lngit;
                                 _corundgummiband*git;
                                 if(t->_liste<_corundgummiband>::anfang(lngit)){
                                  git=lngit->objekt();
                                  welt->psrot->aktiv(true);
                                  //welt->psrot->vektor(_vektor3<_tg>(0,0.5,0));
                                  welt->psrot->ort(k->schnittpunkt.kontakt);
                                  t->loeschengummiband();//_listebasis<_corundgummiband>::loeschen();
                                 };
                                };
                                status=1-status;
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 if((pit->textur()==welt->textur[13])||(pit->textur()==welt->textur[14])) pit->textur(welt->textur[13+status]);
                                }while(_netz::naechstes(pit));
};
char _corundsteinschere::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinschere>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinschere::speichern(_speicherbardynamisch<_corundsteinschere>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteinschere::assoziieren(_speicherbardynamisch<_corundsteinschere>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinschere::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Schere");
                                d->sektion(L"corundstein Schere")->offen(true);
};
void _corundsteinschere::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};


//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H I E B
//******************************************************************************************************************************************************************************************************
_corundsteinschieb::_corundsteinschieb(_corundwelt*ow):_corundstein(ow){
                                schiebschwelle=0.1;
                                kn=new _kollidierbarnetztranslation(this,ow->welt,0,0,this,_vektor3<_tg>(0,0,0));
                                kn->aktualisieren();
};
_corundsteinschieb::_corundsteinschieb(_corundwelt*ow,_netz*n,_tg s):_corundstein(ow,n){
                                schiebschwelle=s;
                                kn=new _kollidierbarnetztranslation(this,ow->welt,0,0,this,_vektor3<_tg>(0,0,0));
                                kn->aktualisieren();
};
_corundsteinschieb::_corundsteinschieb(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex,_tg s):_corundstein(ow,x,y,z,wx,wy,wz,tex,true){
                                schiebschwelle=s;
                                kn=new _kollidierbarnetztranslation(this,ow->welt,0,0,this,_vektor3<_tg>(0,0,0));
                                kn->aktualisieren();
};
_corundsteinschieb::~_corundsteinschieb(){
                                delete kn;
};
void _corundsteinschieb::nachbereitenkonstruktion(){
                                _corundstein::nachbereitenkonstruktion();
                                _netz::dynamisch(true);
};
void _corundsteinschieb::initialisieren(){
                                _corundstein::initialisieren();
                                kn->aktualisieren();
};
void _corundsteinschieb::kollision(_kollidierbar*k,_polygon*){
                                _kollidierbarkugel*kk=0;
                                //-------------------------
                                kk=dynamic_cast<_kollidierbarkugel*>(k);
                                _corundkugel*t=0;
                                t=dynamic_cast<_corundkugel*>(k);
                                _corundsteinimpuls*osi=dynamic_cast<_corundsteinimpuls*>(k->kollisionskopplung);
                                if((t)||(osi)){
                                 _vektor3<_tg> v=k->vektor();
                                 _vektor3<_tg> n=-k->schnittpunkt.normale;
                                 //v.normalisieren();
                                 if(fabs(v*n)>schiebschwelle){
                                  //bewegungsrastermatrix laden
                                  _vektor3<_tg> bewq[3][3][3];
                                  _vektor3<_tg> bewn[3][3][3];
                                  unsigned int x,y,z;
                                  unsigned int nx,ny,nz;
                                  _tg zx,zy,zz;
                                  _tg nmax;
                                  x=y=z=0;
                                  for(zx=-1;zx<=+1;zx+=1){
                                   y=0;
                                   for(zy=-1;zy<=+1;zy+=1){
                                    z=0;
                                    for(zz=-1;zz<=+1;zz+=1){
                                     if((x==1)&&(y==1)&&(z==1)){
                                      bewq[x][y][z].setzen(0,0,0);
                                      bewn[x][y][z].setzen(0,0,0);
                                     }else{
                                      bewq[x][y][z].setzen(zx,zy,zz);
                                      bewn[x][y][z].setzen(zx,zy,zz);
                                      bewn[x][y][z].normalisieren();
                                     };
                                     z++;
                                    };
                                    y++;
                                   };
                                   x++;
                                  };
                                  //übereinstimmung suchen
                                  nmax=-2;
                                  nx=ny=nz=1;
                                  for(x=0;x<3;x++)
                                  for(y=0;y<3;y++)
                                  for(z=0;z<3;z++){
                                   if((n*bewn[x][y][z])>nmax){
                                    nmax=n*bewn[x][y][z];
                                    nx=x;
                                    ny=y;
                                    nz=z;
                                   };
                                  };
                                  _vektor3<_tg> v=bewq[nx][ny][nz];
                                  kn->vektor(v);
                                  if(kn->testen()){
                                   _netz::verschiebenvertex(v);
                                   ort+=v;
                                   _netz::aktualisieren();
                                   _netz::aktualisierensektor(kn->zone());
                                   _netz::aktualisierenbaum();
                                   _netz::aktualisierenschatten();
                                   //_netz::erzeugenvertexlicht(kn->zone);
                                  };
                                 };
                                }else{
                                };
};
char _corundsteinschieb::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinschieb>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(schiebschwelle);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinschieb::speichern(_speicherbardynamisch<_corundsteinschieb>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(schiebschwelle);
                                sd->speichernendeblock();
};                                
char _corundsteinschieb::assoziieren(_speicherbardynamisch<_corundsteinschieb>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinschieb::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Schieb");
                                d->sektion(L"corundstein Schieb")->offen(true);
                                d->einhaengen(L"corundstein Schieb",L"Schiebschwelle",schiebschwelle);
                                d->einhaengenknopf<_corundstein>(L"corundstein Schieb",L"Nahenull Verkleinerung jetzt",L"durchführen",this,&_corundstein::beiknopfverkleinern);
                                
                                
};
void _corundsteinschieb::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Schieb",L"Schiebschwelle",schiebschwelle);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N B O U L D E R 
//******************************************************************************************************************************************************************************************************
_corundsteinboulder::_corundsteinboulder(_corundwelt*ow):_corundstein(ow){
                                prichtung=0;
                                tex[0][0]=ow->textur[60];
                                tex[0][1]=ow->textur[61];
                                tex[1][0]=ow->textur[62];
                                tex[1][1]=ow->textur[63];
                                tex[2][0]=ow->textur[64];
                                tex[2][1]=ow->textur[65];
                                tex[3][0]=ow->textur[66];
                                tex[3][1]=ow->textur[67];
                                kn=new _kollidierbarkugel(this,welt->welt,0,0,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0),0.499);
                                zaehler=0;
                                zeitzaehler=0;
                                bildphase=10*17;
                                bewegungsphase=20*17;
                                bildgewechselt=false;
};
_corundsteinboulder::_corundsteinboulder(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,unsigned int r):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[41],true){
                                prichtung=r;
                                tex[0][0]=ow->textur[60];
                                tex[0][1]=ow->textur[61];
                                tex[1][0]=ow->textur[62];
                                tex[1][1]=ow->textur[63];
                                tex[2][0]=ow->textur[64];
                                tex[2][1]=ow->textur[65];
                                tex[3][0]=ow->textur[66];
                                tex[3][1]=ow->textur[67];
                                _netz::textur(ow->textur[41]);
                                _polygon*pit;
                                _netz::anfang(pit);
                                pit=pit->naechstes();
                                pit->textur(tex[prichtung][0]);
                                kn=new _kollidierbarkugel(this,welt->welt,0,0,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0),0.499);
                                zaehler=0;
                                zeitzaehler=0;
                                bildphase=10*17;
                                bewegungsphase=20*17;
                                bildgewechselt=false;
};
_corundsteinboulder::~_corundsteinboulder(){
                                delete kn;
};
void _corundsteinboulder::nachbereitenkonstruktion(){
                                _corundstein::nachbereitenkonstruktion();
                                _netz::dynamisch(true);
};
void _corundsteinboulder::initialisieren(){
                                _corundstein::initialisieren();
                                kn->ort(_netz::mitte());
                                kn->bestimmenzone();
                                zeitzaehler=0;
};
void _corundsteinboulder::animieren(){
                                zeitzaehler+=welt->welt->zykluszeit();
                                if(zeitzaehler>bildphase){
                                 if(bildgewechselt==false){
                                  bildgewechselt=true;
                                  setzentextur(0);
                                 };
                                };    
                                if(zeitzaehler>bewegungsphase){
                                 zeitzaehler=0;
                                 bildgewechselt=false;
                                 setzentextur(1);
                                 bewegen();
                                };
};
void _corundsteinboulder::kollision(_kollidierbar*k,_polygon*p){
                                //_polygon*pit;
                                //-------------------------
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 if(t==welt->spieler){
                                  _corundobjekt*co;
                                  _corundobjektzauberstab*c;
                                  if(welt->corundinventar->anfang(co)){
                                   c=dynamic_cast<_corundobjektzauberstab*>(co);
                                   if(c){
                                    switch(prichtung){
                                     case(0):prichtung=2;break;
                                     case(1):prichtung=3;break;
                                     case(2):prichtung=0;break;
                                     case(3):prichtung=1;break;
                                    };
                                   };
                                  };
                                 };
                                };
                                //das ist der standardweg gemäß kollisionsdesign
                                _kollisionskopplung*kk=k->kollisionskopplung;
                                if(kk){
                                 _corundsteinimpuls*i=dynamic_cast<_corundsteinimpuls*>(kk);
                                 if(i){
                                  _vektor3<_tg> n=k->schnittpunkt.normale;
                                  if(n==_vektor3<_tg>(1,0,0)) prichtung=3;
                                  if(n==_vektor3<_tg>(-1,0,0)) prichtung=1;
                                  if(n==_vektor3<_tg>(0,0,1)) prichtung=2;
                                  if(n==_vektor3<_tg>(0,0,-1)) prichtung=0;
                                 /* if(prichtung==0) prichtung==2; else
                                  if(prichtung==1) prichtung==3; else*/
                                 // if(prichtung==2) prichtung=0; else
                                 // if(prichtung==3) prichtung=1; 
                                 };
                                };
};                                 
void _corundsteinboulder::bewegen(){                                     
                                _polygon*pit;
                                _netz::anfang(pit);
                                pit=pit->naechstes();
                                pit->textur(tex[prichtung][1]);
                                _vektor3<_tg> v;
                                if(prichtung==0) v.setzen(0,0,1);
                                if(prichtung==1) v.setzen(1,0,0);
                                if(prichtung==2) v.setzen(0,0,-1);
                                if(prichtung==3) v.setzen(-1,0,0);
                                _vektor3<_tg> o=ort+_vektor3<_tg>(0.5,0.5,0.5);
                                _vektor3<_tg> grav(0,0,0);
                                kn->aktualisieren();
                                kn->vektor(v);
                                bool kugelmatsch=false;
                                bool beweg=false;
                                do{
                                 kugelmatsch=false;
                                 kn->vektor(v);
                                 if(kn->testen()==false){
                                  if(kn->schnittpunkt.kollidierbarkugel){
                                   _corundkugel*ck=dynamic_cast<_corundkugel*>(kn->schnittpunkt.kollidierbarkugel);
                                   if(ck){
                                    ck->zerstoeren();
                                    kugelmatsch=true;
                                   };
                                  };
                                 }else beweg=true;
                                }while((kugelmatsch)&&(beweg==false));
                                if(beweg){
                                 _netz::verschiebenvertex(v);
                                 kn->ort(kn->ort()+v);
                                 ort+=v;
                                 /*_tg x0,x1,y0,y1,z0,z1;
                                 if(_netz::anfang(pit))do{
                                  _partition::_zone*zit;
                                  _partition::_sektor*sit;
                                  zit=kn->zone();
                                  pit->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                  pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                  //totaler schrott !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                  if(zit->anfang(sit))do{
                                   sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                  }while(zit->naechstes(sit));
                                 }while(_netz::naechstes(pit));                                  */
                                 _netz::aktualisierensektor(kn->zone());
                                 _netz::aktualisierenbaum();
                                 _netz::anfang(pit);
                                 if(pit->verwendentexturdynamisch()==false) {
                                  _netz::erzeugenvertexlicht(kn->zone());
                                 };
                                 _netz::aktualisierenschatten();
                                 //senker verknüpfung .... aktualisierung der überwachung einschalten
                                 _listenknoten<_corundsteinsenker>*seit;
                                 if(_liste<_corundsteinsenker>::anfang(seit))do{
                                  seit->objekt()->pruefen=true;
                                 }while(_liste<_corundsteinsenker>::naechstes(seit));
                                }else{
                                 _polygon*steinpoly=kn->schnittpunkt.polygon;
                                 if(steinpoly){
                                  _netz*stein=steinpoly->netz();
                                  if(stein){
                                   _corundsteinrotation*osr;
                                   osr=dynamic_cast<_corundsteinrotation*>(stein);
                                   if(osr){
                                    if(osr->prichtung==0){
                                     prichtung++;
                                     if(prichtung==4) prichtung=0;
                                    }else{
                                     if(prichtung==0) prichtung=3; else prichtung--;
                                    };
                                    setzentextur(1);
                                   };
                                  };
                                 };
                                };
};
void _corundsteinboulder::setzentextur(unsigned int i){
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 if((pit->textur()==tex[prichtung][1])||(pit->textur()==tex[prichtung][1]))pit->textur(tex[prichtung][i]);
                                }while(_netz::naechstes(pit));
};
void _corundsteinboulder::zeichnen(_grafik*g) {
                                _corundstein::zeichnen(g);
                                _vektor3<_tg> v;
                                if(prichtung==3)  v.setzen(-1,0,0); 
                                if(prichtung==1)  v.setzen(1,0,0); 
                                if(prichtung==2)  v.setzen(0,0,-1); 
                                if(prichtung==0)  v.setzen(0,0,1); 
                                _weltdebugpfeil*wp=new _weltdebugpfeil(welt->welt,_netz::mitte(),_netz::mitte()+v,0.3,0.2,_vektor4<_to>(0.15,0.9,1,1));
                                wp->zeichnen(g);
                                delete wp;
};
char _corundsteinboulder::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinboulder>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(prichtung);
                                r^=sd->ladenwert(bildgewechselt);
                                r^=sd->ladenwert(zeitzaehler);
                                r^=sd->ladenwert(bildphase);
                                r^=sd->ladenwert(bewegungsphase);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinboulder::speichern(_speicherbardynamisch<_corundsteinboulder>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(prichtung);
                                sd->speichernwert(bildgewechselt);
                                sd->speichernwert(zeitzaehler);
                                sd->speichernwert(bildphase);
                                sd->speichernwert(bewegungsphase);
                                sd->speichernendeblock();
};                                
char _corundsteinboulder::assoziieren(_speicherbardynamisch<_corundsteinboulder>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinboulder::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Boulder");
                                d->sektion(L"corundstein Boulder")->offen(true);
                                d->einhaengen(L"corundstein Boulder",L"Richtung",prichtung);
                                d->einhaengen(L"corundstein Boulder",L"Bildphase [ms]",bildphase);
                                d->einhaengen(L"corundstein Boulder",L"Bewegungsphase [ms]",bewegungsphase);
                                d->einhaengenknopf<_corundstein>(L"corundstein Boulder",L"Nahenull Verkleinerung jetzt",L"durchführen",this,&_corundstein::beiknopfverkleinern);
};
void _corundsteinboulder::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Boulder",L"Richtung",prichtung);
                                d->auslesen(L"corundstein Boulder",L"Bildphase [ms]",bildphase);
                                d->auslesen(L"corundstein Boulder",L"Bewegungsphase [ms]",bewegungsphase);
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N R O T A T I O N
//******************************************************************************************************************************************************************************************************
_corundsteinrotation::_corundsteinrotation(_corundwelt*ow):_corundstein(ow){
                                prichtung=0;
                                kn=0;
                                zaehler=0;
                                dach=0;
                                
};

_corundsteinrotation::_corundsteinrotation(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*textur,unsigned int r):_corundstein(ow,x,y,z,wx,wy,wz,textur,true){
                                prichtung=r;
                                kn=0;
                                zaehler=0;
                                dach=0;
                                nachbereitenkonstruktion();
};
_corundsteinrotation::~_corundsteinrotation(){
                                if(dach) delete dach;
};
void _corundsteinrotation::nachbereitenkonstruktion(){
                                if(dach) delete dach;
                                dach=0;
                                _tg x0,x1,y0,y1,z0,z1;
                                _netz::umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                ort.setzen(x0,y0,z0);
                                breite.setzen(x1-x0,y1-y0,z1-z0);
                                _tg x=ort[0];
                                _tg y=ort[1];
                                _tg z=ort[2];
                                _tg wx=breite[0];
                                _tg wy=breite[1];
                                _tg wz=breite[2];
                                _geometrienetz*nn=new _geometrienetz(welt->welt,_vektor3<_tg>(x+wx*0.25,y+wy+0.01,z+wz*0.25),_vektor3<_tg>(0.5,0,0),_vektor3<_tg>(0 ,0,0.5),welt->textur[69+prichtung]);
                                dach=nn->erzeugen();
                                dach->einhaengen(welt->welt);
                                dach->verwendentextur(true); 
                                dach->markierungpolygon(1);
                                dach->subtraktiv(false);
                                dach->farbeverbinder(_vektor4<_to>(1.0,1.0,1.0,1));
                                dach->keinbsp(true);
                                dach->schattenvolumen(false);
                                dach->nichtspeichern(true);
                                delete nn;
};
void _corundsteinrotation::initialisieren(){
                                _corundstein::initialisieren();
                                _tg x0,x1,y0,y1,z0,z1;
                                _netz::umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                ort.setzen(x0,y0,z0);
                                breite.setzen(x1-x0,y1-y0,z1-z0);
                                
};
void _corundsteinrotation::animieren(){
                                 _polygon*pit;
                                 _vertex*vit;
                                 _vektor3<_tg> m=ort+_vektor3<_tg>(breite[0]*0.5,breite[1]+0.01,breite[2]*0.5);
                                 _tg diff=zaehler-45;
                                 //-------------
                                 dach->anfang(pit);
                                 vit=pit->vertex();
                                 if(vit)do{
                                  vit->ort(m[0]+cos(diff*_ph)*0.3,m[1],m[2]+sin(diff*_ph)*0.3);
                                  vit=vit->naechstes(pit);
                                  diff+=90;
                                 }while(vit!=pit->vertex());
                                 pit->aktualisieren();
                                 
                                 if(prichtung==0) {
                                  zaehler+=4; 
                                  if(zaehler>349) zaehler-=360;
                                 }else{
                                  zaehler-=4;
                                  if(zaehler<0) zaehler+=360;
                                 };
                                /*if(z==0) {
                                 _polygon*pit;
                                 netz->anfang(pit);
                                 pit=pit->naechstes();
                                 pit->textur(tex[prichtung][0]);
                                };
                                if(z==20) {
                                 _polygon*pit;
                                 netz->anfang(pit);
                                 pit=pit->naechstes();
                                 pit->textur(tex[prichtung][1]);
                                 _vektor3<_tg> v;
                                 if(prichtung==0) v.setzen(0,0,1);
                                 if(prichtung==1) v.setzen(1,0,0);
                                 if(prichtung==2) v.setzen(0,0,-1);
                                 if(prichtung==3) v.setzen(-1,0,0);
                                  _vektor3<_tg> o=ort+_vektor3<_tg>(0.5,0.5,0.5);
                                  _vektor3<_tg> grav(0,0,0);
                                  _partition::_zone*zo;
                                  welt->welt->anfang(zo);
                                  _partition::_sektor*s=zo->sektor(o);
                                  
                                  kn=new _kollidierbarnetztranslation(welt->welt,zo,s,netz,v);
                                  
                                  if(kn->bewegen(grav)==false){
                                   netz->verschiebenvertex(v);
                                   ort+=v;
                                   netz->aktualisierenschatten();
                                  };
                                  delete kn;                                 
                                };
                                z++;
                                if(z>=30) z=0;*/
};
void _corundsteinrotation::kollision(_kollidierbar*k,_polygon*p){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 prichtung=1-prichtung;
                                 dach->textur(welt->textur[69+prichtung]);
                                };
};
void _corundsteinrotation::verschiebenvertex(const _vektor3<_tg>v){
                                _netz::verschiebenvertex(v);
                                if(dach) dach->verschiebenvertex(v);
                                ort+=v;
};   
void _corundsteinrotation::zeichnen(_grafik*g) {
                                _corundstein::zeichnen(g);
                                _vektor3<_tg> v;
                                _weltdebugpfeil*wp=new _weltdebugpfeil(welt->welt,_netz::mitte(),_netz::mitte()+v,0.3,0.2,_vektor4<_to>(0.15,0.9,1,1));
                                _tg x0,x1,y0,y1,z0,z1;
                                _netz::umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                x0-=0.2;
                                y0-=0.2;
                                z0-=0.2;
                                x1+=0.2;
                                y1+=0.2;
                                z1+=0.2;
                                if(prichtung==0){
                                 wp->ort(0,_vektor3<_tg>(x0,y1,z0));
                                 wp->ort(1,_vektor3<_tg>(x1,y1,z0));
                                 wp->zeichnen(g);
                                 wp->ort(0,wp->ort(1));
                                 wp->ort(1,_vektor3<_tg>(x1,y1,z1));
                                 wp->zeichnen(g);
                                 wp->ort(0,wp->ort(1));
                                 wp->ort(1,_vektor3<_tg>(x0,y1,z1));
                                 wp->zeichnen(g);
                                 wp->ort(0,wp->ort(1));
                                 wp->ort(1,_vektor3<_tg>(x0,y1,z0));
                                 wp->zeichnen(g);
                                }else{
                                 wp->ort(0,_vektor3<_tg>(x0,y1,z0));
                                 wp->ort(1,_vektor3<_tg>(x0,y1,z1));
                                 wp->zeichnen(g);
                                 wp->ort(0,wp->ort(1));
                                 wp->ort(1,_vektor3<_tg>(x1,y1,z1));
                                 wp->zeichnen(g);
                                 wp->ort(0,wp->ort(1));
                                 wp->ort(1,_vektor3<_tg>(x1,y1,z0));
                                 wp->zeichnen(g);
                                 wp->ort(0,wp->ort(1));
                                 wp->ort(1,_vektor3<_tg>(x0,y0,z0));
                                 wp->zeichnen(g);
                                };
                                
                                delete wp;
};
char _corundsteinrotation::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinrotation>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(prichtung);
                               // r^=sd->ladenassoziation();
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinrotation::speichern(_speicherbardynamisch<_corundsteinrotation>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(prichtung);
                                //saveassociationargument(sd->datei(),sd,dach);
                                sd->speichernendeblock();
};                                
char _corundsteinrotation::assoziieren(_speicherbardynamisch<_corundsteinrotation>*sd){
                                sd->assoziierenverschachtelung();
                                //associateassociationargument(sd->datei(),sd->assoziation(),dach);
                                return(1);
};
void _corundsteinrotation::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Rotation");
                                d->sektion(L"corundstein Rotation")->offen(true);
                                d->einhaengen(L"corundstein Rotation",L"Richtung",prichtung);
                                
};
void _corundsteinrotation::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Rotation",L"Richtung",prichtung);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N I M P U L S 
//******************************************************************************************************************************************************************************************************
_corundsteinimpuls::_corundsteinimpuls(_corundwelt*ow):_corundstein(ow){
                            
                                _tg wx,wy,wz;
                                wx=wy=wz=1;
                                zaehler=0;
                               /* dach[0]=0;
                                dach[1]=0;
                                dach[2]=0;
                                dach[3]=0;*/
                                _vektor3<_tg> m=_vektor3<_tg>(wx*0.5,wy*0.5,wz*0.5);
                                kk[0]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(wx* 0.2,0,0),wx*0.4);
                                kk[1]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(wx*-0.2,0,0),wx*0.4);
                                kk[2]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,0,wz* 0.2),wx*0.4);
                                kk[3]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,0,wz*-0.2),wx*0.4);
                                kk[4]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,wy* 0.2,0),wx*0.4);
                                kk[5]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,wy*-0.2,0),wx*0.4);                                
                                for(int i=0;i<6;i++) kk[i]->aktivitaet(false);
                                
};

_corundsteinimpuls::_corundsteinimpuls(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[32],false){
                                zaehler=0;
                               /* dach[0]=0;
                                dach[1]=0;
                                dach[2]=0;
                                dach[3]=0;*/
                                nachbereitenkonstruktion();
                               // _partition::_zone*zo;
                               // welt->welt->anfang(zo);
                                _vektor3<_tg> m=ort+_vektor3<_tg>(wx*0.5,wy*0.5,wz*0.5);
                               // _partition::_sektor*s=zo->sektor(m);
                               /* kn[0]=new _kollidierbarnetztranslation(welt->welt,zo,s,this,_vektor3<_tg>(0.01,0,0));
                                kn[1]=new _kollidierbarnetztranslation(welt->welt,zo,s,this,_vektor3<_tg>(-0.01,0,0));
                                kn[2]=new _kollidierbarnetztranslation(welt->welt,zo,s,this,_vektor3<_tg>(0,0,0.01));
                                kn[3]=new _kollidierbarnetztranslation(welt->welt,zo,s,this,_vektor3<_tg>(0,0,-0.01));
                                kn[4]=new _kollidierbarnetztranslation(welt->welt,zo,s,this,_vektor3<_tg>(0,0.01,0));
                                kn[5]=new _kollidierbarnetztranslation(welt->welt,zo,s,this,_vektor3<_tg>(0,-0.01,0));*/
                                
                                kk[0]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(wx* 0.2,0,0),wx*0.4);
                                kk[1]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(wx*-0.2,0,0),wx*0.4);
                                kk[2]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,0,wz* 0.2),wx*0.4);
                                kk[3]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,0,wz*-0.2),wx*0.4);
                                kk[4]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,wy* 0.2,0),wx*0.4);
                                kk[5]=new _kollidierbarkugel(this,welt->welt,0,0,m,_vektor3<_tg>(0,wy*-0.2,0),wx*0.4);
                                for(int i=0;i<6;i++) kk[i]->aktivitaet(false);

};
_corundsteinimpuls::~_corundsteinimpuls(){
                                /*delete kn[0];
                                delete kn[1];
                                delete kn[2];
                                delete kn[3];
                                delete kn[4];
                                delete kn[5];*/
                              /*  if(dach[0]){
                                 delete dach[0];
                                 delete dach[1];
                                 delete dach[2];
                                 delete dach[3];
                                };  */                              
                                delete kk[0];
                                delete kk[1];
                                delete kk[2];
                                delete kk[3];
                                delete kk[4];
                                delete kk[5];
};
void _corundsteinimpuls::initialisieren(){
                                _corundstein::initialisieren();
                                _vektor3<_tg> m=_netz::mitte();
                                for(int i=0;i<6;i++) {
                                 kk[i]->ort(m);
                                 kk[i]->bestimmenzone();
                                };
                                
                                
};

void _corundsteinimpuls::animieren(){
                                 //_polygon*pit;
                                 //_vertex*vit;
                                 int i;
                                 _vektor3<_tg> v;
                                 _vektor3<_tg> ori[4];
                                 _tg x=ort[0];
                                 _tg y=ort[1];
                                 _tg z=ort[2];
                                 _tg wx=breite[0];
                                 _tg wy=breite[1];
                                 _tg wz=breite[2];
                                 //-------------
                                 
                                 /*for(i=0;i<4;i++){
                                  if(i==0) {
                                   v.setzen(0,0,-1);
                                   ori[0].setzen(x,y+wy+0.01,z+wz*0.25);
                                   ori[1].setzen(x+wx,y+wy+0.01,z+wz*0.25);
                                   ori[2].setzen(x+wx,y+wy+0.01,z+wz*0.25+0.2);
                                   ori[3].setzen(x,y+wy+0.01,z+wz*0.25+0.2);
                                  };
                                  if(i==1) {
                                   v.setzen(0,0,+1);
                                   ori[0].setzen(x,y+wy+0.01,z+wz*0.55);
                                   ori[1].setzen(x+wx,y+wy+0.01,z+wz*0.55);
                                   ori[2].setzen(x+wx,y+wy+0.01,z+wz*0.55+0.2);
                                   ori[3].setzen(x,y+wy+0.01,z+wz*0.55+0.2);
                                  };
                                  if(i==2) {
                                   v.setzen(-1,0,0);
                                   ori[0].setzen(x+wx*0.25,y+wy+0.015,z);
                                   ori[1].setzen(x+wx*0.25+0.2,y+wy+0.015,z);
                                   ori[2].setzen(x+wx*0.25+0.2,y+wy+0.015,z+wz);
                                   ori[3].setzen(x+wx*0.25,y+wy+0.015,z+wz);
                                  };
                                  if(i==3) {
                                   v.setzen(+1,0,0);
                                   ori[0].setzen(x+wx*0.55,y+wy+0.015,z);
                                   ori[1].setzen(x+wx*0.55+0.2,y+wy+0.015,z);
                                   ori[2].setzen(x+wx*0.55+0.2,y+wy+0.015,z+wz);
                                   ori[3].setzen(x+wx*0.55,y+wy+0.015,z+wz);
                                  };
                                  dach[i]->anfang(pit);
                                  vit=pit->vertex();
                                  int j=0;
                                  if(vit)do{
                                   if(zaehler!=0){
                                    if(zaehler>120) {
                                     vit->setzen(ori[j]+v*0.25*  (1-((zaehler-90)/90.0f))    );//sin(zaehler*_ph));
                                    };
                                    if(zaehler<120) {
                                     vit->setzen(ori[j]+v*0.25*sin(zaehler*_ph));
                                    };
                                   }else{
                                    vit->setzen(ori[j]);   
                                   };
                                   vit=vit->naechstes(pit);
                                   j++;
                                  }while(vit!=pit->vertex());
                                  pit->aktualisieren();
                                 };*/
                                 if(zaehler>7){
                                  _netz::textur(welt->textur[32+((14-zaehler))]);
                                 }else{
                                  if(zaehler>0) _netz::textur(welt->textur[31+zaehler]);
                                 };
                                 if(zaehler==8){//impulse in alle richtungen weitergeben
                                  for(i=0;i<6;i++){
                                   //kn[i]->aktualisieren();
                                   if(kk[i]->testen()==false){
                                    //L->schreiben("Impulsschnittunkt");
                                    /*_polygon*steinpoly=kk[i]->schnittpunkt.polygon;
                                    if(steinpoly){
                                     _netz*stein=steinpoly->netz();
                                     if(stein){
                                      _corundsteinimpuls*osi;
                                      osi=dynamic_cast<_corundsteinimpuls*>(stein);
                                      if(osi){
                                       osi->schalten();
                                      };
                                      _corundsteincorund*os;
                                      os=dynamic_cast<_corundsteincorund*>(stein);
                                      if(os){
                                       os->kollision(kk[i],steinpoly);
                                      };
                                     };
                                    };*/
                                   };
                                  };
                                 };
                                 
                                 if(zaehler!=0) zaehler-=1; 
};
void _corundsteinimpuls::kollision(_kollidierbar*k,_polygon*p){
                                _corundkugel*o=dynamic_cast<_corundkugel*>(k);
                                if(o){
                                 schalten();
                                 return;
                                };
                                //das ist der standardweg gemäß kollisionsdesign
                                 _kollisionskopplung*kk=k->kollisionskopplung;
                                 if(kk){
                                  _corundsteinimpuls*i=dynamic_cast<_corundsteinimpuls*>(kk);
                                  if(i){
                                   schalten();
                                   return;
                                  };
                                  _corundsteinboulder*b=dynamic_cast<_corundsteinboulder*>(kk);
                                  if(b){
                                   schalten();
                                   return;
                                  };
                                 };
                                
};
void _corundsteinimpuls::schalten(){
                                 if(zaehler==0) {
                                  zaehler=14;
                                 };
};
void _corundsteinimpuls::verschiebenvertex(const _vektor3<_tg>v){
                                _netz::verschiebenvertex(v);
                               // for(int i=0;i<4;i++) if(dach[i]) dach[i]->verschiebenvertex(v);
                                ort+=v;
};                                
char _corundsteinimpuls::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinimpuls>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                               /* r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();*/
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinimpuls::speichern(_speicherbardynamisch<_corundsteinimpuls>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                              /*  saveassociationargument(sd->datei(),sd,dach[0]);
                                saveassociationargument(sd->datei(),sd,dach[1]);
                                saveassociationargument(sd->datei(),sd,dach[2]);
                                saveassociationargument(sd->datei(),sd,dach[3]);*/
                                sd->speichernendeblock();
};                                
char _corundsteinimpuls::assoziieren(_speicherbardynamisch<_corundsteinimpuls>*sd){
                                sd->assoziierenverschachtelung();
                              /*  associateassociationargument(sd->datei(),sd->assoziation(),dach[0]);
                                associateassociationargument(sd->datei(),sd->assoziation(),dach[1]);
                                associateassociationargument(sd->datei(),sd->assoziation(),dach[2]);
                                associateassociationargument(sd->datei(),sd->assoziation(),dach[3]);*/
                                return(1);
};
void _corundsteinimpuls::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Impuls");
                                d->sektion(L"corundstein Impuls")->offen(true);
};
void _corundsteinimpuls::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E L E K T R I S C H 
//******************************************************************************************************************************************************************************************************
_corundsteinelektrisch::_corundsteinelektrisch(_corundwelt*ow):_corundstein(ow){
                                zaehler=0;
                                ladung=1;
};
_corundsteinelektrisch::_corundsteinelektrisch(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_tg l):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[71],true){
                                zaehler=0;
                                ladung=l;
                                if(l>=0) textur(welt->textur[71]);
                                if(l< 0) textur(welt->textur[73]);
};
_corundsteinelektrisch::~_corundsteinelektrisch(){
};
void _corundsteinelektrisch::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 t->ladung=ladung;
                                 if(ladung>0) t->_kugel::farbe(t->farbe+_vektor4<_to>(0.5,0,0,1));
                                 if(ladung<0) t->_kugel::farbe(t->farbe+_vektor4<_to>(0,0,0.5,1));
                                 zaehler=50;
                                };
};
void _corundsteinelektrisch::animieren(){
                                if(zaehler>0) zaehler--;
                                if(ladung>=0)if((zaehler%4)>2) textur(welt->textur[72]); else textur(welt->textur[71]);
                                if(ladung< 0)if((zaehler%4)>2) textur(welt->textur[74]); else textur(welt->textur[73]);
};
char _corundsteinelektrisch::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinelektrisch>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(ladung);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinelektrisch::speichern(_speicherbardynamisch<_corundsteinelektrisch>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(ladung);
                                sd->speichernendeblock();
};                                
char _corundsteinelektrisch::assoziieren(_speicherbardynamisch<_corundsteinelektrisch>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinelektrisch::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Elektrisch");
                                d->sektion(L"corundstein Elektrisch")->offen(true);
                                d->einhaengen(L"corundstein Elektrisch",L"Ladung",ladung);
                                
};
void _corundsteinelektrisch::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Elektrisch",L"Ladung",ladung);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E R D U N G
//******************************************************************************************************************************************************************************************************
_corundsteinerdung::_corundsteinerdung(_corundwelt*ow):_corundstein(ow){
                                zaehler=0;
};
_corundsteinerdung::_corundsteinerdung(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
                                zaehler=0;
};
_corundsteinerdung::~_corundsteinerdung(){
};
void _corundsteinerdung::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 t->ladung=0;
                                 t->_kugel::farbe(t->farbe);
                                 zaehler=50;
                                };
};
void _corundsteinerdung::animieren(){
                                if(zaehler>0) zaehler--;
                                if((zaehler%4)>2) textur(welt->textur[76]); else textur(welt->textur[75]);
};
char _corundsteinerdung::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinerdung>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinerdung::speichern(_speicherbardynamisch<_corundsteinerdung>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteinerdung::assoziieren(_speicherbardynamisch<_corundsteinerdung>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinerdung::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Erdung");
                                d->sektion(L"corundstein Erdung")->offen(true);
                                
};
void _corundsteinerdung::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N B E S C H L E U N I G U N G 
//******************************************************************************************************************************************************************************************************
_corundsteinbeschleunigung::_corundsteinbeschleunigung(_corundwelt*ow):_corundstein(ow){
                                staerke=1;
                                zaehler=0;
                                bton=new _corundton(ow,ow->tonverwaltung.ton(2),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));
};
_corundsteinbeschleunigung::_corundsteinbeschleunigung(_corundwelt*ow,_netz*n,_tg s):_corundstein(ow,n){
                                staerke=s;
                                zaehler=0;
                                bton=new _corundton(ow,ow->tonverwaltung.ton(2),n->mitte(),_vektor3<_tg>(0,0,0));
};
_corundsteinbeschleunigung::_corundsteinbeschleunigung(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_tg st):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[0],false){
                                staerke=st;
                                zaehler=0;
                                bton=new _corundton(ow,ow->tonverwaltung.ton(2),ort+breite*0.5,_vektor3<_tg>(0,0,0));
};
_corundsteinbeschleunigung::~_corundsteinbeschleunigung(){
                                delete bton;
};
void _corundsteinbeschleunigung::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 _vektor3<_tg> v=k->schnittpunkt.normale;
                                 v*=staerke;
                                 t->vektor(t->vektor()+v);
                                 zaehler=10;
                                 bton->abspielen();
                                };
};
void _corundsteinbeschleunigung::animieren(){
                                if(zaehler>0){
                                 zaehler--;
                                 _netz::farbeverbinder(  welt->ambientlicht+(_vektor4<_to>(1,1,1,1)-welt->ambientlicht)*(_tg(zaehler)*0.1f)  );
                                 
                                };
};
char _corundsteinbeschleunigung::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinbeschleunigung>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(staerke);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinbeschleunigung::speichern(_speicherbardynamisch<_corundsteinbeschleunigung>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(staerke);
                                sd->speichernendeblock();
};                                
char _corundsteinbeschleunigung::assoziieren(_speicherbardynamisch<_corundsteinbeschleunigung>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinbeschleunigung::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Beschleunigung");
                                d->sektion(L"corundstein Beschleunigung")->offen(true);
                                d->einhaengen(L"corundstein Beschleunigung",L"Stärke",staerke);
                                
};
void _corundsteinbeschleunigung::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Beschleunigung",L"Stärke",staerke);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N T O T E N K O P F
//******************************************************************************************************************************************************************************************************
_corundsteintotenkopf::_corundsteintotenkopf(_corundwelt*ow):_corundstein(ow){
                                staerke=1;
                                zaehler=0;
};
_corundsteintotenkopf::_corundsteintotenkopf(_corundwelt*ow,_netz*n,_tg st):_corundstein(ow,n){
                                staerke=st;
                                zaehler=0;
};
_corundsteintotenkopf::_corundsteintotenkopf(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_tg st):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[82],false){
                                staerke=st;
                                zaehler=0;
};
_corundsteintotenkopf::~_corundsteintotenkopf(){
};
void _corundsteintotenkopf::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 _vektor3<_tg> v=k->schnittpunkt.normale;
                                 v*=staerke;
                                 t->vektor(t->vektor()+v);
                                 t->zerstoeren();
                                 //if(t==welt->spieler){
                                  zaehler=100;
                                 //};
                                };
};
void _corundsteintotenkopf::animieren(){
                                if(zaehler>0){
                                 if((zaehler%10)==0){
                                  status=1-status;
                                  textur(welt->textur[82+status]);
                                 };
                                 zaehler--;
                                };
};
char _corundsteintotenkopf::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteintotenkopf>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(staerke);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteintotenkopf::speichern(_speicherbardynamisch<_corundsteintotenkopf>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(staerke);
                                sd->speichernendeblock();
};                                
char _corundsteintotenkopf::assoziieren(_speicherbardynamisch<_corundsteintotenkopf>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteintotenkopf::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Totenkopf");
                                d->sektion(L"corundstein Totenkopf")->offen(true);
                                d->einhaengen(L"corundstein Totenkopf",L"Stärke",staerke);
                                
};
void _corundsteintotenkopf::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Totenkopf",L"Stärke",staerke);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N T O R 
//******************************************************************************************************************************************************************************************************
_corundsteintor::_corundsteintor(_corundwelt*ow):_corundstein(ow){
                                richtung=0;
                                zaehler=0;
                                zyklen=40;
                                dyndialog=0;
                                ausgang=false;
};
_corundsteintor::_corundsteintor(_corundwelt*ow,_tg x,_tg y,_tg z,unsigned int r):_corundstein(ow){
                                _geometriequader*gb;
                                _polygon*pit;
                                _tg nz=ow->steinskalierung;
                                _tg wx,wy,wz;
                                _liste<_netz> ln;
                                //-----------------------------
                                richtung=r;
                                zaehler=0;
                                dyndialog=0;
                                ausgang=false;
                                if(richtung==0){
                                 wx=0.2;
                                 wy=0.8;
                                 wz=0.5;
                                }else{
                                 wx=0.5;
                                 wy=0.8;
                                 wz=0.2;
                                };
                                breite.setzen(wx,wy,wz);
                              //  ow->_baumoctal<_corundstein,_tg>::einhaengen(this,x-0.1,x+0.1,y-0.1,y+0.1,z-0.1,z+0.1);//stein in den weltbaum eingehängt
                                
                                for(int i=0;i<4;i++){
                                 if(richtung==0){
                                  if(i==0) ort.setzen(x+0.2,y+0.1,z+0.0);else 
                                  if(i==1) ort.setzen(x+0.6,y+0.1,z+0.0);else 
                                  if(i==2) ort.setzen(x+0.2,y+0.1,z+0.5);else 
                                  if(i==3) ort.setzen(x+0.6,y+0.1,z+0.5);
                                 }else{
                                  if(i==0) ort.setzen(x,y+0.1,z+0.2);else 
                                  if(i==1) ort.setzen(x,y+0.1,z+0.6);else 
                                  if(i==2) ort.setzen(x+0.5,y+0.1,z+0.2);else 
                                  if(i==3) ort.setzen(x+0.5,y+0.1,z+0.6);
                                 };
                                
                                 gb=new _geometriequader(welt->welt,ort,wx,wy,wz,welt->textur[41]);
                                 gb->texturkoordinatenlaenge(1,1,1);
                                 tor[i]=gb->erzeugen();
                                 tor[i]->verwendentextur(true); 
                                 tor[i]->subtraktiv(false);
                                 tor[i]->farbeverbinder(_vektor4<_to>(0.5,0.5,0.5,1));
                                 tor[i]->verknuepfenverbindervertexpolygon();
                                 tor[i]->schattenvolumen(true);
                                 tor[i]->schattenvolumenlaenge(100);
                                 tor[i]->keinbsp(true);
                                 delete gb;
                                 ln.aushaengen();
                                 ln.einhaengen(tor[i]);
                                 einhaengen(&ln,_vektor3<_tg>(1,0,0));
                                 //---------------------------------------------------------------------------------------------------------
                                 /*
                                 zit->einfuegenintern(tor[i]);
                                 //sektorlicht benutzen
                                 _listenknoten<_partition::_sektor>*lnsit;
                                 _partition::_sektor*sit;
                                 if(tor[i]->_liste<_partition::_sektor>::anfang(lnsit))do{
                                  sit=lnsit->objekt();
                                  if(sit->anfang(lit))do{
                                   tor[i]->markierungverbinder(-1);
                                   tor[i]->erzeugenschatten(lit,100.0f);
                                  }while(sit->naechstes(lit));
                                  //wir brauchen die primäre sichtbarkeit
                                  //um schattenvolumen von den lichtern in ihr
                                  //anzulegen
                                  _listenknoten<_partition::_sektor>*lnsii;
                                  _partition::_sektor*sii;
                                  if(sit->sichtbarkeitsektor()->anfang(lnsii))do{
                                   sii=lnsii->objekt();
                                   if(sii->anfang(lit))do{
                                    //tor[i]->markierungverbinder(-1);
                                    //tor[i]->erzeugenschatten(lit,150.0f);
                                   }while(sii->naechstes(lit));
                                  }while(sit->sichtbarkeitsektor()->naechstes(lnsii));
                                 }while(tor[i]->_liste<_partition::_sektor>::naechstes(lnsit)); 
                                 */
                                 //--------------------------------------------kollisionskopplung vornehmen---------------------------------
                                 if(tor[i]->anfang(pit))do{
                                  pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                 }while(tor[i]->naechstes(pit));
                                };
};
_corundsteintor::~_corundsteintor(){
                                _listenknoten<_liste<_netz> >*listit;
                                if(netze.anfang(listit))do{
                               //  listit->objekt()->loeschen();
                                }while(netze.naechstes(listit));
                                netze.loeschen();
                                richtungen.loeschen();
};
void _corundsteintor::einhaengen(_liste<_netz>*netzgruppe,const _vektor3<_tg>&vektor){
                                _liste<_netz>*neu;
                                _netz*netz;
                                _polygon*pit;
                                //_partition::_zone*zit;
                                _listenknoten<_netz>*it;
                                //_listenknoten<_partition::_sektor>*lnsit;
                                //_partition::_sektor*sit;
                                //_listenknoten<_partition::_sektor>*lnsii;
                                //_partition::_sektor*sii;
                                //_licht<_tg,_to>*lit;
                                //--------------------
                                neu=new _liste<_netz>();
                                netze.einhaengen(neu);
                               
                                if(netzgruppe->anfang(it))do{
                                
                                
                                 netz=it->objekt();
                                 neu->einhaengen(netz);
                                 //welt->welt->anfang(zit);
                                 netz->einhaengen(welt->welt);
                                 netz->verknuepfenverbindervertexpolygon();
                                 //netz->erzeugenvertexlicht(zit);
                                 netz->farbeverbinder(welt->ambientlicht);
                                 netz->keinbsp(true);
                                 netz->schattenvolumen(true);
                                 netz->schattenvolumenlaenge(100);
                                 
                                 //---------------------------------------------------------------------------------------------------------
                                 /*zit->einfuegenintern(netz);
                                 if(netz->_liste<_partition::_sektor>::anfang(lnsit))do{
                                  sit=lnsit->objekt();
                                  if(sit->anfang(lit))do{
                                   netz->markierungverbinder(-1);
                                   netz->erzeugenschatten(lit,100.0f);
                                  }while(sit->naechstes(lit));
                                  if(sit->sichtbarkeitsektor()->anfang(lnsii))do{
                                   sii=lnsii->objekt();
                                   if(sii->anfang(lit))do{
                                    //netz->markierungverbinder(-1);
                                    //netz->erzeugenschatten(lit,150.0f);
                                   }while(sii->naechstes(lit));
                                  }while(sit->sichtbarkeitsektor()->naechstes(lnsii));
                                 }while(netz->_liste<_partition::_sektor>::naechstes(lnsit)); */
                                 //--------------------------------------------kollisionskopplung vornehmen---------------------------------
                                 if(netz->anfang(pit))do{
                                  pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                 }while(netz->naechstes(pit));
                                 
                                }while(netzgruppe->naechstes(it));
                                _vektor3<_tg>*v=new _vektor3<_tg>(vektor);
                                richtungen.einhaengen(v);
};
void _corundsteintor::kollision(_kollidierbar*k,_polygon*){
                                /*_corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 schalten();
                                };
                                */
};
void _corundsteintor::animieren(){
                                _listenknoten<_liste<_netz> >*listeit;
                                _listenknoten<_netz>*netzit;
                                _listenknoten<_vektor3<_tg> >*vektorit;
                                //int i;
                                _tg s=0.01;
                                if(zaehler>0){
                                 //if(status==1){
                                  
                                  if(netze.anfang(listeit)){
                                   richtungen.anfang(vektorit);
                                   do{
                                    if(listeit->objekt()->anfang(netzit))do{
                                     netzit->objekt()->verschiebenvertex((*(vektorit->objekt())) *  ((_tg(status)*2.0f)-1.0f));
                                     netzit->objekt()->aktualisierennetzschatten();
                                    }while(listeit->objekt()->naechstes(netzit));
                                    richtungen.naechstes(vektorit);
                                   }while(netze.naechstes(listeit));
                                  };
                                  /*if(richtung==0){
                                   for(i=0;i<4;i++){
                                    if(i<2) tor[i]->verschiebenvertex(_vektor3<_tg>(0,0,-s)); else
                                            tor[i]->verschiebenvertex(_vektor3<_tg>(0,0,+s));
                                   };
                                  }else{
                                   for(i=0;i<4;i++){
                                    if(i<2) tor[i]->verschiebenvertex(_vektor3<_tg>(-s,0,0)); else
                                            tor[i]->verschiebenvertex(_vektor3<_tg>(+s,0,0));
                                   };
                                  };*/
                                  
                                 //}else{
                                  /*if(richtung==0){
                                   for(i=0;i<4;i++){
                                    if(i<2) tor[i]->verschiebenvertex(_vektor3<_tg>(0,0,+s)); else
                                            tor[i]->verschiebenvertex(_vektor3<_tg>(0,0,-s));
                                   };
                                  }else{
                                   for(i=0;i<4;i++){
                                    if(i<2) tor[i]->verschiebenvertex(_vektor3<_tg>(+s,0,0)); else
                                            tor[i]->verschiebenvertex(_vektor3<_tg>(-s,0,0));
                                   };
                                  };*/
                                  
                                 //};
                                 //for(i=0;i<4;i++) tor[i]->aktualisierennetzschatten();
                                 zaehler--;
                                };    
                                
};
void _corundsteintor::schalten(){
                                status=1-status;
                                zaehler=zyklen-zaehler;
};
void _corundsteintor::zeichnen(_grafik*g) {
                                _corundstein::zeichnen(g);
                                _vektor3<_tg> m=_netz::mitte();
                                _vektor3<_tg> z;
                                char buf[1024];
                                _weltdebugpfeil*wp=new _weltdebugpfeil(welt->welt,_netz::mitte(),_vektor3<_tg>(0,0,0),0.1,0.05,_vektor4<_to>(1,0.4,0,1));
                                _weltdebugtext*wt=new _weltdebugtext(welt->welt,"G0",m,_vektor3<_tg>(0.5,0,0),_vektor3<_tg>(0,0,0.3),_vektor4<_to>(1,0.4,0,1));
                                _listenknoten<_liste<_netz> >*nlistit;
                                unsigned int i=0;
                                _listenknoten<_netz>*lnnit;
                                _zeichenkette<char> h;
                                if(netze.anfang(nlistit))do{
                                 h="Gr.";
                                 _itoa(i,buf,10);
                                 h+=buf;
                                 if(nlistit->objekt()->anfang(lnnit))do{
                                  z=lnnit->objekt()->mitte();
                                  wp->ort(1,z);
                                  wt->ort((z+m)*0.5);
                                  wt->text(h);
                                  wp->zeichnen(g);
                                  wt->zeichnen(g);
                                 }while(nlistit->objekt()->naechstes(lnnit));
                                 i++;
                                }while(netze.naechstes(nlistit));
                                delete wp;
                                delete wt;
};
char _corundsteintor::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteintor>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(zyklen);
                                r^=sd->ladenwert(ausgang);
                                //tornetzzeiger laden
                                anzahlnetz.loeschen();
                                unsigned int lanz,nanz,i,j;
                                r^=sd->ladenwert(lanz);
                                for(i=0;i<lanz;i++){
                                 r^=sd->ladenwert(nanz);
                                 unsigned int*ni=new unsigned int;
                                 *ni=nanz;
                                 anzahlnetz.einhaengen(ni);
                                 for(j=0;j<nanz;j++){
                                  r^=sd->ladenassoziation();
                                 };
                                };
                                //richtungen laden
                                _vektor3<_tg> v;
                                richtungen.loeschen();
                                r^=sd->ladenwert(lanz);
                                for(i=0;i<lanz;i++){
                                 r^=sd->ladenwert(v);
                                 richtungen.einhaengen(new _vektor3<_tg>(v));
                                };
                                sd->ladenende();
                                return(r);
};                                
void _corundsteintor::speichern(_speicherbardynamisch<_corundsteintor>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(zyklen);
                                sd->speichernwert(ausgang);
                                //tornetzzeiger speichern
                                _listenknoten<_liste<_netz > >*lit;
                                _listenknoten<_netz>*nit;
                                sd->speichernwert(netze.anzahl());
                                if(netze.anfang(lit))do{
                                 sd->speichernwert(lit->objekt()->anzahl());
                                 if(lit->objekt()->anfang(nit))do{
                                  saveassociationargument(sd->datei(),sd,nit->objekt());
                                 }while(lit->objekt()->naechstes(nit));
                                }while(netze.naechstes(lit));
                                //richtungen speichern
                                _listenknoten<_vektor3<_tg> >*vit;
                                sd->speichernwert(richtungen.anzahl());
                                if(richtungen.anfang(vit))do{
                                 sd->speichernwert(*vit->objekt());
                                }while(richtungen.naechstes(vit));
                                sd->speichernendeblock();
};                                
char _corundsteintor::assoziieren(_speicherbardynamisch<_corundsteintor>*sd){
                                sd->assoziierenverschachtelung();
                                _listenknoten<_liste<_netz> >*listit;
                                if(netze.anfang(listit))do{
                                 listit->objekt()->loeschen();
                                }while(netze.naechstes(listit));
                                netze.loeschen();
                                _listenknoten<unsigned int>*iit;
                                if(anzahlnetz.anfang(iit))do{
                                 _liste<_netz>* ln=new _liste<_netz>();
                                 netze.einhaengen(ln);
                                 int i,n=*iit->objekt();
                                 for(i=0;i<n;i++) {
                                  _netz*netz=0;
                                  associateassociationargument(sd->datei(),sd->assoziation(),netz);
                                  if(netz){
                                   ln->einhaengen(netz);
                                  };
                                 };
                                }while(anzahlnetz.naechstes(iit));
                                anzahlnetz.loeschen();
                                return(1);
};
 void _corundsteintor::netzwahl(_netz*ne,int i){
                                _listenknoten<_liste<_netz> >*nlistit;
                                netze.anfang(nlistit);
                                for(int n=0;n<i;n++) netze.naechstes(nlistit);
                                nlistit->objekt()->einhaengenunredundant(ne);
                                if(hauptfenster) hauptfenster->zeichnen();
};
void _corundsteintor::beiknopfneuerichtung(_guiereignisdaten*){
                                _vektor3<_tg>*v=new _vektor3<_tg>(0,1,0);
                                _liste<_netz>*ln=new _liste<_netz>();
                                richtungen.einhaengen(v);
                                netze.einhaengen(ln);
                                if(dyndialog) {//einhaengendialog(dyndialog);
                                 _zeichenkette<char> h;
                                 char buf[1280];
                                 unsigned int i=richtungen.anzahl()-1;
                                 h="Bewegungsrichtung Gruppe ";
                                 _itoa(i,buf,10);
                                 h+=buf;                                 
                                 dyndialog->einhaengen(L"corundstein Tor",ANSIToUnicode(h.daten()),*v);
                                 h="Neuen Netzeiger für Gruppe ";
                                 h+=buf;
                                 dyndialog->einhaengenknopf<_corundsteintor>(L"corundstein Tor",ANSIToUnicode(h.daten()),L"holen",this,&_corundsteintor::beiknopfneuesnetz);
                                 h="Letzten Netzeiger der Gruppe ";
                                 h+=buf;
                                 dyndialog->einhaengenknopf<_corundsteintor>(L"corundstein Tor",ANSIToUnicode(h.daten()),L"loeschen",this,&_corundsteintor::beiknopfloeschenletztes);
                                 h="Alle  Netzeiger der Gruppe ";
                                 h+=buf;
                                 dyndialog->einhaengenknopf<_corundsteintor>(L"corundstein Tor",ANSIToUnicode(h.daten()),L"loeschen",this,&_corundsteintor::beiknopfloeschen);
                                 dyndialog->zeigen();
                                };
};
void _corundsteintor::beiknopfloeschengruppe(_guiereignisdaten*){
                                //letzte gruppe löschen
                                _listenknoten<_vektor3<_tg> >*vit;
                                _listenknoten<_liste<_netz> >*nit;
                                if(netze.anfang(nit)){
                                 nit=nit->vorheriges();
                                 delete nit;
                                };
                                if(richtungen.anfang(vit)){
                                 vit=vit->vorheriges();
                                 vit->loeschmarkierungobjekt(true);
                                 delete vit;
                                };
                                if(hauptfenster) hauptfenster->zeichnen();
                                
};
void _corundsteintor::beiknopfneuesnetz(_guiereignisdaten*ep){
                                _guiobjekt*o=ep->objekt;
                                _guiknopf*bb=dynamic_cast<_guiknopf*>(o);
                                if(bb){
                                 _guieditierbar*e=dynamic_cast<_guieditierbar*>(bb->besitzer()); 
                                 _zeichenkette<char> h=(char*)UnicodeToANSI(e->_guiobjekt::name()).Data();
                                 unsigned int i,c;
                                 char buf[128];
                                 i=h.groesse();
                                 while((i>=0)&&(h[i]!=' ')) i--;
                                 i++;
                                 c=0;
                                 while(h[i]!=0) buf[c++]=h[i++];
                                 buf[c]=0;
                                 i=atoi(buf);
                                 if(hauptfenster) {
                                  hauptfenster->dnetzwahl->corundstein(this);
                                  hauptfenster->dnetzwahl->index(i);
                                  hauptfenster->dnetzwahl->zeigen();
                                 };                                 
                                };
};
void _corundsteintor::beiknopfloeschenletztes(_guiereignisdaten*ep){
                                _guiobjekt*o=ep->objekt;
                                _guiknopf*bb=dynamic_cast<_guiknopf*>(o);
                                if(bb){
                                 _guieditierbar*e=dynamic_cast<_guieditierbar*>(bb->besitzer()); 
                                 _zeichenkette<char> h=(char*)UnicodeToANSI(e->_guiobjekt::name()).Data();
                                 //gruppenindex bestimmen
                                 unsigned int i,c;
                                 char buf[128];
                                 i=h.groesse();
                                 while((i>=0)&&(h[i]!=' ')) i--;
                                 i++;
                                 c=0;
                                 while(h[i]!=0) buf[c++]=h[i++];
                                 buf[c]=0;
                                 i=atoi(buf);
                                 //letztem netzzeiger der gruppe i löschen
                                 _listenknoten<_liste<_netz> >*nlistit;
                                 if(netze.anfang(nlistit)){
                                  for(unsigned int z=0;z<i;z++) netze.naechstes(nlistit);
                                  _listenknoten<_netz>*nit;
                                  if(nlistit->objekt()->anfang(nit)){
                                   nit=nit->vorheriges();
                                   delete nit;
                                   if(hauptfenster) hauptfenster->zeichnen();
                                  };
                                 };
                                };
};
void _corundsteintor::beiknopfloeschen(_guiereignisdaten*ep){
                                _guiobjekt*o=ep->objekt;
                                _guiknopf*bb=dynamic_cast<_guiknopf*>(o);
                                if(bb){
                                 _guieditierbar*e=dynamic_cast<_guieditierbar*>(bb->besitzer()); 
                                 _zeichenkette<char> h=(char*)UnicodeToANSI(e->_guiobjekt::name()).Data();
                                 //gruppenindex bestimmen
                                 unsigned int i,c;
                                 char buf[128];
                                 i=h.groesse();
                                 while((i>=0)&&(h[i]!=' ')) i--;
                                 i++;
                                 c=0;
                                 while(h[i]!=0) buf[c++]=h[i++];
                                 buf[c]=0;
                                 i=atoi(buf);
                                 //letztem netzzeiger der gruppe i löschen
                                 _listenknoten<_liste<_netz> >*nlistit;
                                 if(netze.anfang(nlistit)){
                                  for(unsigned int z=0;z<i;z++) netze.naechstes(nlistit);
                                  nlistit->objekt()->aushaengen();
                                  /*_listenknoten<_netz>*nit;
                                  if(nlistit->objekt()->anfang(nit))do{
                                   nit->loeschmarkierungobjekt(true);
                                  }while(nlistit->objekt()->naechstes(nit));
                                  */
                                  if(hauptfenster) hauptfenster->zeichnen();
                                 };
                                };
};
void _corundsteintor::einhaengendialog(_dynamischerdialog*d){
                                _zeichenkette<char> h;
                                char buf[1280];
                                unsigned int i;
                                dyndialog=d;
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Tor");
                                d->sektion(L"corundstein Tor")->offen(true);
                                d->einhaengen(L"corundstein Tor",L"Zyklen",zyklen);
                                d->einhaengen(L"corundstein Tor",L"Kartenausgang",ausgang);
                                d->einhaengenknopf<_corundsteintor>(L"corundstein Tor",L"Neue Bewegungsgruppe",L"erzeugen",this,&_corundsteintor::beiknopfneuerichtung);
                                d->einhaengenknopf<_corundsteintor>(L"corundstein Tor",L"Letzte Bewegungsgruppe",L"löschen",this,&_corundsteintor::beiknopfloeschengruppe);
                                _listenknoten<_vektor3<_tg> >*vit;
                                i=0;
                                if(richtungen.anfang(vit))do{
                                 h="Bewegungsrichtung Gruppe ";
                                 _itoa(i,buf,10);
                                 h+=buf;
                                 d->einhaengen(L"corundstein Tor",ANSIToUnicode(h.daten()),*vit->objekt());
                                 h="Neuen Netzeiger für Gruppe ";
                                 h+=buf;
                                 d->einhaengenknopf<_corundsteintor>(L"corundstein Tor",ANSIToUnicode(h.daten()),L"holen",this,&_corundsteintor::beiknopfneuesnetz);
                                 h="Letzten Netzeiger der Gruppe ";
                                 h+=buf;
                                 d->einhaengenknopf<_corundsteintor>(L"corundstein Tor",ANSIToUnicode(h.daten()),L"loeschen",this,&_corundsteintor::beiknopfloeschenletztes);
                                 h="Alle  Netzeiger der Gruppe ";
                                 h+=buf;
                                 d->einhaengenknopf<_corundsteintor>(L"corundstein Tor",ANSIToUnicode(h.daten()),L"loeschen",this,&_corundsteintor::beiknopfloeschen);
                                 i++;
                                }while(richtungen.naechstes(vit));
};
void _corundsteintor::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Tor",L"Zyklen",zyklen);
                                d->auslesen(L"corundstein Tor",L"Kartenausgang",ausgang);
                                _listenknoten<_vektor3<_tg> >*vit;
                                _zeichenkette<char> h;
                                char buf[1280];
                                unsigned int i=0;
                                if(richtungen.anfang(vit))do{
                                 h="Bewegungsrichtung Gruppe ";
                                 _itoa(i,buf,10);
                                 h+=buf;                     
                                 d->auslesen(L"corundstein Tor",ANSIToUnicode(h.daten()),*vit->objekt());
                                 i++;
                                }while(richtungen.naechstes(vit));           
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H A L T E R 
//******************************************************************************************************************************************************************************************************
_corundsteinschalter::_corundsteinschalter(_corundwelt*ow):_corundstein(ow),_corundschalter<_corundsteinschalter>(ow){
                                status=0;
                                //anzahlzeiger=0;
};
_corundsteinschalter::_corundsteinschalter(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,int st,_corundstein*s):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[80],false),_corundschalter<_corundsteinschalter>(ow){
                                status=st;
                               // anzahlzeiger=0;
                                listeek.einhaengen(s);
                                if(status==0) textur(_corundstein::welt->textur[80]); else textur(_corundstein::welt->textur[81]);
};
_corundsteinschalter::~_corundsteinschalter(){
};
void _corundsteinschalter::kollision(_kollidierbar*k,_polygon*p){
                                _corundstrahl*t=0;
                                t=dynamic_cast<_corundstrahl*>(k->kollisionskopplung);
                               // if(t){
                                 if(t==0) _corundschalter<_corundsteinschalter>::kollision(k,p);
                               // };
};
void _corundsteinschalter::animieren(){
 
                                if(gedrueckt){
                                 _polygon*pit;
                                 _listenknoten<_kollidierbar>*kit;
                                 unsigned int anzahl=0;
                                 if(_netz::anfang(pit))do{
                                  if(pit->anfang(kit))do{
                                   anzahl++;
                                  }while(pit->naechstes(kit));
                                 }while(_netz::naechstes(pit));
                                 //es sind grad anzahl kollidierbare auf diesem boden
                                 if(anzahl==0){
                                  gedrueckt=false;
                                  schaltenletztkontakt();
                                 }else{
                                  schaltenzwischenkontakt();
                                 };
                                };
};  
void _corundsteinschalter::zeichnen(_grafik*g) {
                                _corundstein::zeichnen(g);
                                _corundschalter<_corundsteinschalter>::zeichnen(g);
                                /*_weltdebugpfeil*wp=new _weltdebugpfeil(welt->welt,_netz::mitte(),_vektor3<_tg>(0,0,0),0.1,0.05,_vektor4<_to>(1,1,0,1));
                                _listenknoten<_corundstein>*oit;
                                if(liste.anfang(oit))do{
                                 wp->ort(1,oit->objekt()->_netz::mitte());
                                 wp->zeichnen(g);
                                }while(liste.naechstes(oit));
                                delete wp;*/
};
void _corundsteinschalter::schalten(){
                                status=1-status;
                                if(status==0) textur(_corundstein::welt->textur[80]); else textur(_corundstein::welt->textur[81]);
                                _corundschalter<_corundsteinschalter>::schalten();
                                /*_listenknoten<_corundstein>*oit;
                                if(liste.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(liste.naechstes(oit));*/
};
void _corundsteinschalter::schaltenerstkontakt(){
                                status=1-status;
                                if(status==0) textur(_corundstein::welt->textur[80]); else textur(_corundstein::welt->textur[81]);
                                _corundschalter<_corundsteinschalter>::schaltenerstkontakt();
};
char _corundsteinschalter::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinschalter>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=_corundschalter<_corundsteinschalter>::laden(fn,sd);
                                //r^=sd->ladenwert(anzahlzeiger);
                                //for(unsigned int i=0;i<anzahlzeiger;i++) r^=sd->ladenassoziation();
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinschalter::speichern(_speicherbardynamisch<_corundsteinschalter>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                _corundschalter<_corundsteinschalter>::speichern(sd);   
                                /*_listenknoten<_corundstein>*it;
                                sd->speichernwert(liste.anzahl());
                                if(liste.anfang(it))do{
                                 saveassociationargument(sd->datei(),sd,it->objekt());
                                }while(liste.naechstes(it));*/
                                sd->speichernendeblock();
};                                
char _corundsteinschalter::assoziieren(_speicherbardynamisch<_corundsteinschalter>*sd){
                                sd->assoziierenverschachtelung();
                                _corundschalter<_corundsteinschalter>::assoziieren(sd);
                                /*liste.aushaengen();
                                _corundstein*corundstein=0;
                                for(unsigned int i=0;i<anzahlzeiger;i++) {
                                 corundstein=0;
                                 associateassociationargument(sd->datei(),sd->assoziation(),corundstein);
                                 if(corundstein){
                                  liste.einhaengen(corundstein);
                                 };
                                };
                                */
                                return(1);
};
/*
 void _corundsteinschalter::netzwahl(_netz*n,int){
                                _corundstein*os=dynamic_cast<_corundstein*>(n);
                                if(os){
                                 liste.einfuegenunredundant(os);
                                };
};
void _corundsteinschalter::beiknopfausfuehren(_guiereignisdaten*ep){
                                //netz auswahldialog aktivieren
                                
                                if(hauptfenster) {
                                 hauptfenster->dnetzwahl->corundstein(this);
                                 hauptfenster->dnetzwahl->zeigen();
                                };
                                L->schreiben("Netzzeigerrfubkt");
};
void _corundsteinschalter::beiknopfloeschen(_guiereignisdaten*){
                                liste.aushaengen();
                                hauptfenster->zeichnen();
                                L->schreiben("Netzzeigerloeschrfubkt");
};
void _corundsteinschalter::beiknopfloeschenletzten(_guiereignisdaten*){
                                _listenknoten<_corundstein>*lnosit;
                                if(liste.anfang(lnosit)){
                                 lnosit=lnosit->vorheriges();
                                 delete lnosit;
                                };
                                hauptfenster->zeichnen();
                                L->schreiben("Netzzeigerloeschrfubkt");
};*/
void _corundsteinschalter::einhaengendialog(_dynamischerdialog*d){
                                _corundschalter<_corundsteinschalter>::dialogschaltkopplungswahl=hauptfenster->dsteinschaltkopplungswahl;
                                _corundstein::einhaengendialog(d);
                                _corundschalter<_corundsteinschalter>::einhaengendialog(d);
                                /*d->addierensektion(L"corundstein Schalter");
                                d->sektion(L"corundstein Schalter")->offen(true);
                                d->einhaengenknopf<_corundsteinschalter>(L"corundstein Schalter",L"Neuen Zeiger",L"holen",this,beiknopfausfuehren);
                                d->einhaengenknopf<_corundsteinschalter>(L"corundstein Schalter",L"Letzten Zeiger",L"löschen",this,beiknopfloeschenletzten);
                                d->einhaengenknopf<_corundsteinschalter>(L"corundstein Schalter",L"Alle Zeiger",L"löschen",this,beiknopfloeschen);
                                */
};
void _corundsteinschalter::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                _corundschalter<_corundsteinschalter>::auslesendialog(d);                                
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N K U G E L G E N 
//******************************************************************************************************************************************************************************************************
_corundsteinkugelgen::_corundsteinkugelgen(_corundwelt*ow):_corundstein(ow){
                                vektor=_vektor3<_tg>(0,1,0);
                                radius=0.2;
                                ladung=0;
                                gravitation=0;
                                farbe=_vektor4<_to>(1,1,1,1);
                                killer=false;
                                chaotischervektor=false;
                                zumspielervektor=false;
                                schaltenautomatisch=false;
                                automatischanzahl=5;
                                automatischzaehler=0;
                                automatischrate=500;
};
_corundsteinkugelgen::_corundsteinkugelgen(_corundwelt*ow,_tg x,_tg y,_tg z,_vektor3<_tg> v,_tg rad,_tg lad,_tg grav,_vektor4<_to> f):_corundstein(ow,x,y,z,1,1,1,ow->textur[68],false){
                                vektor=v;
                                radius=rad;
                                ladung=lad;
                                gravitation=grav;
                                farbe=f;
                                killer=false;
                                chaotischervektor=false;
                                zumspielervektor=false;
                                schaltenautomatisch=false;
                                automatischanzahl=5;
                                automatischzaehler=0;
                                automatischrate=500;
};
_corundsteinkugelgen::~_corundsteinkugelgen(){
};
void _corundsteinkugelgen::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 _vektor3<_tg> n=k->einfallsvektor;
                                 n.normalisieren();
                                 n*=k->vektor().laenge();
                                 vektoreinzel=vektor+n;
                                 if(zaehler==0){
                                  zaehler=50;
                                  generieren();
                                 };
                                };
};
void _corundsteinkugelgen::generieren(){
                                _vektor3<_tg> vv;
                                 vv.zufall();
                                 _corundkugel*ok=new _corundkugel(welt,mitte()+_vektor3<_tg>(0.5,0.5,0.5),vektor*0.8+vv*0.2,radius,farbe);
                                 ok->ladung=ladung;
                                 ok->gravitation=gravitation;
                                 ok->killer=killer;
                                 ok->chaotischervektor=chaotischervektor;
                                 ok->zumspielervektor=zumspielervektor;
};                                 
void _corundsteinkugelgen::animieren(){
                                if(zaehler>0){
                                 zaehler--;
                                }else{
                                 if(automatischzaehler>0){
                                  automatischzaehler--;
                                  zaehler=automatischrate;
                                  generieren();
                                 };
                                };
};
void _corundsteinkugelgen::schalten(){
                                 if(schaltenautomatisch){
                                  automatischzaehler=automatischanzahl-1;
                                  zaehler=automatischrate;
                                  welt->explosion->abspielen();
                                 };
                                 generieren();
                                 
                                
};
char _corundsteinkugelgen::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinkugelgen>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(radius);
                                r^=sd->ladenwert(ladung);
                                r^=sd->ladenwert(gravitation);
                                r^=sd->ladenwert(killer);
                                r^=sd->ladenwert(chaotischervektor);
                                r^=sd->ladenwert(zumspielervektor);
                                r^=sd->ladenwert(schaltenautomatisch);//schaltet automatische generierung bei aufruf von schalten ein
                                r^=sd->ladenwert(automatischanzahl);//wieviel automatisch generatiert werden
                                r^=sd->ladenwert(automatischzaehler);//wieviel im moment noch genereriuert werden müssen
                                r^=sd->ladenwert(automatischrate);//in welchem takt genereriert wird
                                r^=sd->ladenwert(farbe);
                                r^=sd->ladenwert(vektor);
                                r^=sd->ladenwert(vektoreinzel);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinkugelgen::speichern(_speicherbardynamisch<_corundsteinkugelgen>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(radius);
                                sd->speichernwert(ladung);
                                sd->speichernwert(gravitation);
                                sd->speichernwert(killer);
                                sd->speichernwert(chaotischervektor);
                                sd->speichernwert(zumspielervektor);
                                sd->speichernwert(schaltenautomatisch);//schaltet automatische generierung bei aufruf von schalten ein
                                sd->speichernwert(automatischanzahl);//wieviel automatisch generatiert werden
                                sd->speichernwert(automatischzaehler);//wieviel im moment noch genereriuert werden müssen
                                sd->speichernwert(automatischrate);//in welchem takt genereriert wird
                                sd->speichernwert(farbe);
                                sd->speichernwert(vektor);
                                sd->speichernwert(vektoreinzel);
                                sd->speichernendeblock();
};                                
char _corundsteinkugelgen::assoziieren(_speicherbardynamisch<_corundsteinkugelgen>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinkugelgen::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Kugelgenerator");
                                d->sektion(L"corundstein Kugelgenerator")->offen(true);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Radius",radius);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Ladung",ladung);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Gravitation",gravitation);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Killer",killer);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Chaotischer Vektor",chaotischervektor);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Zum Spieler Vektor",zumspielervektor);
                                d->einhaengen(L"corundstein Kugelgenerator",L"schalten automatisch",schaltenautomatisch);
                                d->einhaengen(L"corundstein Kugelgenerator",L"automatische Anzahl",automatischanzahl);
                                d->einhaengen(L"corundstein Kugelgenerator",L"automatischer Zähler",automatischzaehler);
                                d->einhaengen(L"corundstein Kugelgenerator",L"automatische Rate",automatischrate);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Farbe",farbe);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Vektor",vektor);
                                d->einhaengen(L"corundstein Kugelgenerator",L"Vektor einzeln",vektoreinzel);
                                
};
void _corundsteinkugelgen::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Kugelgenerator",L"Radius",radius);
                                d->auslesen(L"corundstein Kugelgenerator",L"Ladung",ladung);
                                d->auslesen(L"corundstein Kugelgenerator",L"Gravitation",gravitation);
                                d->auslesen(L"corundstein Kugelgenerator",L"Killer",killer);
                                d->auslesen(L"corundstein Kugelgenerator",L"Chaotischer Vektor",chaotischervektor);
                                d->auslesen(L"corundstein Kugelgenerator",L"Zum Spieler Vektor",zumspielervektor);
                                d->auslesen(L"corundstein Kugelgenerator",L"schalten automatisch",schaltenautomatisch);
                                d->auslesen(L"corundstein Kugelgenerator",L"automatische Anzahl",automatischanzahl);
                                d->auslesen(L"corundstein Kugelgenerator",L"automatischer Zähler",automatischzaehler);
                                d->auslesen(L"corundstein Kugelgenerator",L"automatische Rate",automatischrate);
                                d->auslesen(L"corundstein Kugelgenerator",L"Farbe",farbe);
                                d->auslesen(L"corundstein Kugelgenerator",L"Vektor",vektor);
                                d->auslesen(L"corundstein Kugelgenerator",L"Vektor einzeln",vektoreinzel);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N D A C H
//******************************************************************************************************************************************************************************************************
_corundsteindach::_corundsteindach(_corundwelt*ow):_corundstein(ow){
                                netzanzahl=0;
                                textur=ow->textur[0];
};
_corundsteindach::_corundsteindach(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*t):_corundstein(ow){
                                textur=t;    
                                netzanzahl=0;
                                _geometriequader*gb;
                                ort.setzen(x,y,z);
                                breite.setzen(wx,wy,wz);
                                gb=new _geometriequader(welt->welt,ort,wx,wy,wz,t);
                                gb->texturkoordinatenlaenge(1,1,1);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::markierungpolygon(1);
                                delete gb;
                                nachbereitenkonstruktion();
};
_corundsteindach::~_corundsteindach(){
                                netze.loeschen();       
};
void _corundsteindach::nachbereitenkonstruktion(){
                                _tg x,x1,y,y1,z,z1,wx,wy,wz;
                                //-------------------
                                netze.loeschen();   
                                _netz::umgrenzungsquader(x,x1,y,y1,z,z1);
                                _netz::subtraktiv(false);
                                //_netz::verschiebennormal(ow->steinskalierung);
                                _netz::farbeverbinder(_vektor4<_to>(1,0,0,1));
                                _netz::verknuepfenverbindervertexpolygon();
                                _netz::verwendentextur(false);
                                _netz::zeichnenflaeche(false);
                                _netz::keinbsp(true);
                                _netz::schattenvolumen(false);
                                _netz::lightmapschattierung(false);
                                wx=x1-x;
                                wy=y1-y;
                                wz=z1-z;
                                netze.loeschen();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->::_liste<_kollisionskopplung>::aushaengen();
                                 pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                }while(_netz::naechstes(pit));
                                _tg xi,zi;
                                _tg xd=wx/1.0f;
                                _tg zd=wz/1.0f;
                                for(zi=z;zi<z+wz;zi+=zd)
                                for(xi=x;xi<x+wx;xi+=xd){
                                 konstruieren(_vektor3<_tg>(xi,y,zi),_vektor3<_tg>(xd,0,0),_vektor3<_tg>(0,wy,0),_vektor3<_tg>(0,0,zd));
                                };
};
void _corundsteindach::kollision(_kollidierbar*,_polygon*){
};
void _corundsteindach::animieren(){
};
void _corundsteindach::verschiebenvertex(const _vektor3<_tg> v){
                                _netz::verschiebenvertex(v);
                                _listenknoten<_netz>*nit;
                                if(netze.anfang(nit))do{
                                 nit->objekt()->verschiebenvertex(v);
                                }while(netze.naechstes(nit));
};
void _corundsteindach::konstruieren(const _vektor3<_tg>&o,const _vektor3<_tg>&v0,const _vektor3<_tg>&v1,const _vektor3<_tg>&v2){
                                _geometriequader*gq;
                                _netz*n[9];
                                gq=new _geometriequader(welt->welt,o,v0,v1*0.1,v2*0.1,textur);
                                n[0]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o+v2*0.9,v0,v1*0.1,v2*0.1,textur);
                                n[1]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o+v2*0.1,v0*0.1,v1*0.1,v2*0.8,textur);
                                n[2]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o+v2*0.1+v0*0.9,v0*0.1,v1*0.1,v2*0.8,textur);
                                n[3]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o+v1*0.1,  v0*0.1,  v0*0.4+ v1*0.8+v2*0.4     ,v2*0.1,textur);
                                n[4]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o+v1*0.1+v2*0.9,  v0*0.1,  v0*0.4+ v1*0.8-v2*0.4     ,v2*0.1,textur);
                                n[5]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o + v0*0.9 + v1*0.1,  v0*0.1,  -v0*0.4+ v1*0.8+v2*0.4     ,v2*0.1,textur);
                                n[6]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o + v0*0.9 + v1*0.1 + v2*0.9,  v0*0.1,  -v0*0.4+ v1*0.8-v2*0.4     ,v2*0.1,textur);
                                n[7]=gq->erzeugen();
                                delete gq;
                                gq=new _geometriequader(welt->welt,o + v0*0.4 + v1*0.9 + v2*0.4,  v0*0.2,  v1*0.1    ,v2*0.2,textur);
                                n[8]=gq->erzeugen();
                                delete gq;
                                _modifikationnetzintersektion I;
                                I.bearbeiten(n[8],n[7],2);
                                I.bearbeiten(n[8],n[6],2);
                                I.bearbeiten(n[8],n[5],2);
                                I.bearbeiten(n[8],n[4],2);
                                I.bearbeiten(n[8],n[0],2);
                                I.bearbeiten(n[8],n[1],2);
                                I.bearbeiten(n[8],n[2],2);
                                I.bearbeiten(n[8],n[3],2);
                                for(int i=0;i<8;i++) delete n[i];
                                netze.einhaengen(n[8]);
                                _listenknoten<_netz> * lnit;
                                _netz*nn;
                                if(netze.anfang(lnit))do{
                                 nn=lnit->objekt();
                                 nn->einhaengen(welt->welt);
                                 nn->nichtspeichern(true);
                                 nn->verwendentextur(true); 
                                 nn->verwendentexturdynamisch(true); 
                                 nn->markierungpolygon(1);
                                 nn->subtraktiv(false);
                                 nn->kollision(false);
                                 nn->farbeverbinder(welt->ambientlicht);
                                 nn->verknuepfenverbindervertexpolygon();
                                 nn->keinbsp(true);
                                 nn->schattenvolumen(false);
                                }while(netze.naechstes(lnit));
};
char _corundsteindach::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteindach>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                              /*  netze.loeschen();
                                unsigned int i;
                                r^=sd->ladenwert(netzanzahl);
                                for(i=0;i<netzanzahl;i++){
                                 r^=sd->ladenassoziation();
                                };*/
                                sd->ladenende();
                                return(r);
};                                
void _corundsteindach::speichern(_speicherbardynamisch<_corundsteindach>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                               /* sd->speichernwert(netze.anzahl());
                                _listenknoten<_netz>*nit;
                                if(netze.anfang(nit))do{
                                 saveassociationargument(sd->datei(),sd,nit->objekt());
                                }while(netze.naechstes(nit));*/
                                sd->speichernendeblock();
};                                
char _corundsteindach::assoziieren(_speicherbardynamisch<_corundsteindach>*sd){
                                sd->assoziierenverschachtelung();
                              /*  for(unsigned int i=0;i<netzanzahl;i++){
                                 _netz*netz=0;
                                 associateassociationargument(sd->datei(),sd->assoziation(),netz);
                                 if(netz) netze.einhaengen(netz);
                                };*/
                                return(1);
};
void _corundsteindach::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Dach");
                                d->sektion(L"corundstein Dach")->offen(true);
};
void _corundsteindach::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N F L A K
//******************************************************************************************************************************************************************************************************
_corundsteinflak::_corundsteinflak(_corundwelt*ow):_corundstein(ow),_skelett(ow->welt,_vektor3<_tg>(0.5,2,0.5),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1)){
                                status=0;
                                netzanzahl=0;
                                dauerfeuer=false;
                                schalterdauer=false;
                                muendungsfeuerquer[0]=0;
                                muendungsfeuerquer[1]=0;
                                muendungsfeuerquer[2]=0;
                                fuss[0]=new _knochen(this,this,0,_vektor3<_tg>(-0.5,-1,-0.5));
                                fuss[1]=new _knochen(this,this,0,_vektor3<_tg>(+0.5,-1,-0.5));
                                fuss[2]=new _knochen(this,this,0,_vektor3<_tg>(+0.5,-1,+0.5));
                                fuss[3]=new _knochen(this,this,0,_vektor3<_tg>(-0.5,-1,+0.5));
                                stuetze=new _knochen(this,this,0,_vektor3<_tg>(0,0.2,0));
                                richtung=new _knochen(this,stuetze,stuetze,_vektor3<_tg>(0,0,1));
                                schuss=new _corundton(ow,ow->tonverwaltung.ton(3),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));                     
                                kk=new _kollidierbarkugel(this,welt->welt,0,0,richtung->ortspitze(),richtung->vektor(),0.123);
                              //  nachbereitenkonstruktion();
                                
};
_corundsteinflak::_corundsteinflak(_corundwelt*ow,_tg x,_tg y,_tg z):_corundstein(ow,x,y,z,1,1,1,ow->textur[68],false),_skelett(ow->welt,_vektor3<_tg>(x+0.5,y+2,z+0.5),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1)){
                                status=0;
                                dauerfeuer=false;
                                netzanzahl=0;
                                muendungsfeuerquer[0]=0;
                                muendungsfeuerquer[1]=0;
                                muendungsfeuerquer[2]=0;
                                schalterdauer=false;
                                fuss[0]=new _knochen(this,this,0,_vektor3<_tg>(-0.5,-1,-0.5));
                                fuss[1]=new _knochen(this,this,0,_vektor3<_tg>(+0.5,-1,-0.5));
                                fuss[2]=new _knochen(this,this,0,_vektor3<_tg>(+0.5,-1,+0.5));
                                fuss[3]=new _knochen(this,this,0,_vektor3<_tg>(-0.5,-1,+0.5));
                                stuetze=new _knochen(this,this,0,_vektor3<_tg>(0,0.2,0));
                                richtung=new _knochen(this,stuetze,stuetze,_vektor3<_tg>(0,0,1));
  
                                schuss=new _corundton(ow,ow->tonverwaltung.ton(3),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));                     
                               // _partition::_sektor*sit=zit->sektor(richtung->ortspitze());
                                kk=new _kollidierbarkugel(this,welt->welt,0,0,richtung->ortspitze(),richtung->vektor(),0.123);
                                nachbereitenkonstruktion();
};
_corundsteinflak::~_corundsteinflak(){
                                delete schuss;
                                delete kk;
                                muendungsfeuer.loeschen();
                                for(int i=0;i<3;i++) if(muendungsfeuerquer[i]) delete muendungsfeuerquer[i];
};
void _corundsteinflak::nachbereitenkonstruktion(){
                                muendungsfeuer.loeschen();
                                for(int i=0;i<3;i++) if(muendungsfeuerquer[i]) delete muendungsfeuerquer[i];
                                _tg x0,x1,y0,y1,z0,z1;
                                _netz::umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                ort.setzen(x0,y0,z0);
                                breite.setzen(x1-x0,y1-y0,z1-z0);

                                _geometrienetz*gn;
                                _netz*n;
                                _tg wx,wy;
                                wx=0.5;
                                wy=1.5;
                                 
                                _skelett::ort(_netz::mitte()+_vektor3<_tg>(0,1.5,0));
                               
                                L->schreiben("AAAAA");
                                for(int i=0;i<8;i++){
                                 _tg w=_tg(i)*(180.0f/8.0f)*_ph;
                                 gn=new _geometrienetz(welt->welt,richtung->ortspitze()-_vektor3<_tg>(cos(w)*wx,sin(w)*wx,0),_vektor3<_tg>(cos(w)*wx*2,sin(w)*wx*2,0),_vektor3<_tg>(0,0,wy),welt->textur[29]);
                                 n=gn->erzeugen();
                                 delete gn;
                                 n->farbeverbinder(_vektor4<_to>(0.5,0.5,0.5,0.3));
                                 n->zweiseitig(true);
                                 n->dynamischschattiert(false);
                                 n->lightmapschattierung(false);
                                 n->transparenz(true);
                                 n->einhaengen(welt->welt);
                                 n->verwendentextur(true); 
                                 n->markierungpolygon(1);
                                 n->subtraktiv(false);
                                 n->kollision(false);
                                 n->zeichnenflaeche(false);
                                 n->keinbsp(true);
                                 n->schattenvolumen(false);
                                 n->nichtspeichern(true);
                                 muendungsfeuer.einhaengen(n);
                                };
                                
                                for(int i=0;i<3;i++){
                                 gn=new _geometrienetz(welt->welt,richtung->ortspitze()-_vektor3<_tg>(1*wx,1*wx,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),welt->textur[30]);
                                 n=gn->erzeugen();
                                 delete gn;
                                 n->farbeverbinder(_vektor4<_to>(0.5,0.5,0.5,0.3));
                                 n->zweiseitig(true);
                                 n->dynamischschattiert(false);
                                 n->lightmapschattierung(false);
                                 n->transparenz(true);
                                 n->einhaengen(welt->welt);
                                 n->verwendentextur(true); 
                                 n->kollision(false);
                                 n->markierungpolygon(1);
                                 n->subtraktiv(false);
                                 n->zeichnenflaeche(false);
                                 n->keinbsp(true);
                                 n->schattenvolumen(false);
                                 n->nichtspeichern(true);
                                 muendungsfeuerquer[i]=n;
                                };
                                transformierenmuendungsfeuer(_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1));
};
void _corundsteinflak::transformierenmuendungsfeuer(const _vektor3<_tg>&xa,const _vektor3<_tg>&ya,const _vektor3<_tg>&za){
                                _listenknoten<_netz>*nit;
                                _polygon*pit;
                                _vektor3<_tg> o[4];
                                 _vertex*vit;
                                 int j;
                                _vektor3<_tg> rn=richtung->vektor();
                                _vektor3<_tg> zn=za;
                                zn.normalisieren();
                                _zufallsgenerator<_tg> zufi;
                                _tg wx=1+zufi.berechnen(0,0.5);
                                _tg wy=2+zufi.berechnen(0,1);
                                //------------------------------
                                rn.normalisieren();
                                muendungsfeuer.anfang(nit);
                                for(int i=0;i<8;i++){
                                 nit->objekt()->anfang(pit);
                                 _tg w=_tg(i)*(180.0f/8.0f)*_ph;
                                 o[0]=richtung->ortspitze() - xa*cos(w)*wx   - ya*sin(w)*wx;
                                 o[1]=o[0]                  + xa*cos(w)*wx*2 + ya*sin(w)*wx*2;
                                 o[2]=o[1] + rn*wy;
                                 o[3]=o[0] + rn*wy;
                                 vit=pit->vertex();
                                 j=0;
                                 if(vit)do{
                                  vit->ort(o[j++]);
                                  vit=vit->naechstes(pit);
                                 }while(vit!=pit->vertex());
                                 pit->aktualisieren(); 
                                 nit=nit->naechstes();
                                };
                                
                                for(int i=0;i<3;i++){
                                
                                 wx*=0.8;
                                 o[0]=richtung->ortspitze() - xa*wx - ya*wx + rn*wy*(0.2+_tg(i)*0.2);
                                 o[1]=o[0]                         + xa*wx*2;
                                 o[2]=o[1]                         + ya*wx*2;
                                 o[3]=o[2]                         - xa*wx*2;
                                 muendungsfeuerquer[i]->anfang(pit);
                                 vit=pit->vertex();
                                 j=0;
                                 if(vit)do{
                                  vit->ort(o[j++]);
                                  vit=vit->naechstes(pit);
                                 }while(vit!=pit->vertex());
                                 pit->aktualisieren(); 
                                };
                                 
};
void _corundsteinflak::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                _vektor3<_tg> v;
                                if(status==0){
                                 t=dynamic_cast<_corundkugel*>(k);
                                 if(t){
                                  if(t==welt->spieler){
                                   welt->spieler->steuerung=false;
                                   status=1;
                                   v=welt->kamera->kam->vektor();
                                   v.normalisieren();
                                   welt->kamera->kurvenmodus=true;
                                   welt->kamera->kurvenschritt=0.05;
                                   welt->kamera->kurve.ort(0,*(welt->kamera->kam));
                                   welt->kamera->kurve.ort(1,ort+_vektor3<_tg>(0.5,2.5,0.5));
                                   welt->kamera->kurve.vektor(0,v);
                                   welt->kamera->kurve.vektor(1,richtung->vektor());
                                  
                                   welt->kamera->richtung.ort(0,v);
                                   welt->kamera->richtung.ort(1,richtung->vektor());
                                   welt->kamera->richtung.vektor(0,_vektor3<_tg>(0,0,0));
                                   welt->kamera->richtung.vektor(1,_vektor3<_tg>(0,0,0));
                                   
                                   _vektoranalysis3<_tg> V3;
                                   _vektor3<_tg> e;
                                   _vektor3<_tg> p=richtung->vektor();
                                   p.setzenkomponente(1,0);
                                   V3.rotieren(_vektor3<_tg>(0,1,0),p,-90,e);
                                   

                                   welt->kamera->ebene0.ort(0,welt->kamera->kam->ebene(0));
                                   welt->kamera->ebene0.ort(1,e);
                                   welt->kamera->ebene0.vektor(0,_vektor3<_tg>(0,0,0));
                                   welt->kamera->ebene0.vektor(1,_vektor3<_tg>(0,0,0));                                 


                                  };
                                 };
                                };
};

void _corundsteinflak::animieren(){
                                _listenknoten<_netz>*it;
                                if(status==1){
                                 if(welt->kamera->kurvenmodus==false){
                                  status=2;
                                 };
                                };
                                if(status==2){//kamera in position
                                 _win::_tastatur ta;
                                 welt->kamera->standmodus=true;
                                 _vektor3<_tg> v=welt->kamera->kam->vektor();
                                 v.normalisieren();
                                 v*=richtung->laengeoriginal();
                                 richtung->vektor(v);
                                 if(ta.knopflinks()){
                                  if(zaehler==0) zaehler=3;
                                 };
                                 
                                 
                                 if(ta.knopfrechts()){
                                  status=3;
                                  _vektor3<_tg> zielort;
                                  if(welt->spieler) zielort=welt->spieler->_kollidierbarkugel::ort()+welt->kameraverschiebung;
                                  else              zielort=ort+welt->kameraverschiebung;
                                  welt->kamera->kurvenmodus=true;
                                  welt->kamera->standmodus=false;
                                  welt->kamera->kurvenparameter=0;
                                  //corundwelt->spieler->_kollidierbarkugel::ort()+kameraverschiebung
                                  welt->kamera->kurvenschritt=0.01;
                                  welt->kamera->kurve.ort(0,*(welt->kamera->kam));
                                  welt->kamera->kurve.ort(1,zielort);
                                  welt->kamera->kurve.vektor(0,-welt->kamera->kam->vektor());
                                  welt->kamera->kurve.vektor(1,_vektor3<_tg>(0,1,0));
                                 
                                  welt->kamera->richtung.ort(0,welt->kamera->kam->vektor());
                                  welt->kamera->richtung.ort(1,_vektor3<_tg>(0,-1,0));
                                  welt->kamera->richtung.vektor(0,_vektor3<_tg>(0,0,0));
                                  welt->kamera->richtung.vektor(1,_vektor3<_tg>(0,0,0));
                                  
                                  welt->kamera->ebene0.ort(0,welt->kamera->kam->ebene(0));
                                  welt->kamera->ebene0.ort(1,_vektor3<_tg>(1,0,0));
                                  welt->kamera->ebene0.vektor(0,_vektor3<_tg>(0,0,0));
                                  welt->kamera->ebene0.vektor(1,_vektor3<_tg>(0,0,0));     
                                 };
                                };
                                if(status==3){ //kamera zurückfahren
                                 if(welt->kamera->kurvenmodus==false){
                                  status=0;
                                  if(welt->spieler) welt->spieler->steuerung=true;
                                  welt->kamera->kamerakugel->ort(*(welt->kamera->kam));
                                 };
                                };
                                visualisieren();
                                if(zaehler==3){
                                 transformierenmuendungsfeuer(welt->kamera->kam->ebenenormalisiert(0),welt->kamera->kam->ebenenormalisiert(1),richtung->vektor());
                                 if(muendungsfeuer.anfang(it))do{
                                  it->objekt()->zeichnenflaeche(true);
                                 }while(muendungsfeuer.naechstes(it));
                                 for(int i=0;i<3;i++) muendungsfeuerquer[i]->zeichnenflaeche(true);
                                 schuss->lautstaerke=1;
                                 schuss->abspielen();
                                 _vektor3<_tg> vn=richtung->vektor();
                                 vn.normalisieren();
                                 vn*=300;
                                 kk->vektor(vn);
                                 kk->ort(richtung->ortspitze());
                                 if(kk->testen()==false){
                                  welt->pseinschlag->aktiv(true);
                                  welt->pseinschlag->ort(kk->schnittpunkt.ort);
                                  welt->pseinschlag->vektor(kk->schnittpunkt.normale*0.1);
                                  new _corunddruckwelle(welt,kk->schnittpunkt.ort,-0.2,0.3,7);
                                 };
                                }else 
                                if(zaehler==2){
                                 if(muendungsfeuer.anfang(it))do{
                                  it->objekt()->zeichnenflaeche(false);
                                 }while(muendungsfeuer.naechstes(it));
                                 for(int i=0;i<3;i++) muendungsfeuerquer[i]->zeichnenflaeche(false);
                                };
                                if(zaehler>0) zaehler--;
                                if(dauerfeuer) if(zaehler==0) zaehler=3;
};
void _corundsteinflak::schalten(){
                                if(schalterdauer) {
                                 if(dauerfeuer) dauerfeuer=false; else dauerfeuer=true;
                                }else{
                                 if(zaehler==0) zaehler=3;
                                };
                                
};
void _corundsteinflak::verschiebenvertex(const _vektor3<_tg>v){
                                _netz::verschiebenvertex(v);
                                _listenknoten<_netz>*nit;
                                if(muendungsfeuer.anfang(nit))do{
                                 nit->objekt()->verschiebenvertex(v);
                                }while(muendungsfeuer.naechstes(nit));
                                for(int i=0;i<3;i++) if(muendungsfeuerquer[i]) muendungsfeuerquer[i]->verschiebenvertex(v);
                                _skelett::ort(_skelett::ort()+v);
                                ort+=v;
                                
};
void _corundsteinflak::zeichnen(_grafik*g){
                                _corundstein::zeichnen(g);
                                _skelett::visualisieren();
};
char _corundsteinflak::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinflak>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(dauerfeuer);
                                r^=sd->ladenwert(schalterdauer);
                                _vektor3<_tg> v;
                                r^=sd->ladenwert(v);
                                _skelett::ort(v);
                                kk->ort(richtung->ortspitze());
                                r^=sd->ladenwert(v);
                                richtung->vektor(v);
                                kk->vektor(richtung->vektor());
                               /* unsigned int i;
                                r^=sd->ladenwert(netzanzahl);
                                for(i=0;i<netzanzahl;i++){
                                 r^=sd->ladenassoziation();
                                };
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();
                                r^=sd->ladenassoziation();*/
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinflak::speichern(_speicherbardynamisch<_corundsteinflak>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(dauerfeuer);
                                sd->speichernwert(schalterdauer);
                                sd->speichernwert(_skelett::ort());
                                sd->speichernwert(richtung->vektor());
                              /*  sd->speichernwert(muendungsfeuer.anzahl());
                                _listenknoten<_netz>*nit;
                                if(muendungsfeuer.anfang(nit))do{
                                 saveassociationargument(sd->datei(),sd,nit->objekt());
                                }while(muendungsfeuer.naechstes(nit));
                                saveassociationargument(sd->datei(),sd,muendungsfeuerquer[0]);
                                saveassociationargument(sd->datei(),sd,muendungsfeuerquer[1]);
                                saveassociationargument(sd->datei(),sd,muendungsfeuerquer[2]);*/
                                sd->speichernendeblock();
};                                
char _corundsteinflak::assoziieren(_speicherbardynamisch<_corundsteinflak>*sd){
                                sd->assoziierenverschachtelung();
                               /* unsigned int i;
                                muendungsfeuer.loeschen();
                                for(i=0;i<netzanzahl;i++){
                                 _netz*netz=0;
                                 associateassociationargument(sd->datei(),sd->assoziation(),netz);
                                 muendungsfeuer.einhaengen(netz);
                                };
                                associateassociationargument(sd->datei(),sd->assoziation(),muendungsfeuerquer[0]);
                                associateassociationargument(sd->datei(),sd->assoziation(),muendungsfeuerquer[1]);
                                associateassociationargument(sd->datei(),sd->assoziation(),muendungsfeuerquer[2]);*/
                                return(1);
};
void _corundsteinflak::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Flak");
                                d->sektion(L"corundstein Flak")->offen(true);
                                d->einhaengen(L"corundstein Flak",L"Dauerfeuer",dauerfeuer);
                                d->einhaengen(L"corundstein Flak",L"Schalterdauer",schalterdauer);
                                d->einhaengen(L"corundstein Flak",L"Richtung",richtung->vektor());
                                
};
void _corundsteinflak::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Flak",L"Dauerfeuer",dauerfeuer);
                                d->auslesen(L"corundstein Flak",L"Schalterdauer",schalterdauer);
                                _vektor3<_tg> r;
                                d->auslesen(L"corundstein Flak",L"Richtung",r);
                                r.normalisieren();
                                r*=richtung->laengeoriginal();
                                richtung->vektor(r);visualisieren();
                                transformierenmuendungsfeuer(welt->kamera->kam->ebenenormalisiert(0),welt->kamera->kam->ebenenormalisiert(1),richtung->vektor());
                                if(hauptfenster) hauptfenster->zeichnen();
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N  A U S G A N G
//******************************************************************************************************************************************************************************************************
_corundsteinausgang::_corundsteinausgang(_corundwelt*ow):_corundstein(ow){
                                kartenindex=-1;
                                knotenindex=0;
};
_corundsteinausgang::_corundsteinausgang(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[0],false){
                                kartenindex=-1;
                                knotenindex=0;
};
_corundsteinausgang::~_corundsteinausgang(){
};
void _corundsteinausgang::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 if(t->spieler){
                                  if(kartenindex==-1) {//naechste karte betreten
                                   welt->naechstekarte=welt->diesekarte+1;
                                   welt->naechsterknoten=knotenindex;
                                  }else{
                                   welt->naechstekarte=kartenindex;
                                   welt->naechsterknoten=knotenindex;
                                  };
                                 };
                                };
};
char _corundsteinausgang::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinausgang>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(kartenindex);
                                r^=sd->ladenwert(knotenindex);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinausgang::speichern(_speicherbardynamisch<_corundsteinausgang>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(kartenindex);
                                sd->speichernwert(knotenindex);
                                sd->speichernendeblock();
};                                
char _corundsteinausgang::assoziieren(_speicherbardynamisch<_corundsteinausgang>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinausgang::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"corundstein Ausgang");
                                d->sektion(L"corundstein Ausgang")->offen(true);
                                d->einhaengen(L"corundstein Ausgang",L"Sprung nach Karte (-1 == inkr)",kartenindex);
                                d->einhaengen(L"corundstein Ausgang",L"Sprung auf Knoten",knotenindex);
                                
};
void _corundsteinausgang::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"corundstein Ausgang",L"Sprung nach Karte (-1 == inkr)",kartenindex);
                                d->auslesen(L"corundstein Ausgang",L"Sprung auf Knoten",knotenindex);
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S E N K E R
//******************************************************************************************************************************************************************************************************
_corundsteinsenker::_corundsteinsenker(_corundwelt*ow):_corundstein(ow){
                                zaehler=0;
                                vektor.setzen(0,-0.1,0);
                                zyklen=9;
                                modus=0;
                                pruefen=true;
};
_corundsteinsenker::_corundsteinsenker(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex):_corundstein(ow,x,y,z,wx,wy,wz,tex,false){
                                zaehler=0;
                                vektor.setzen(0,-0.1,0);
                                zyklen=9;
                                modus=0;
                                pruefen=true;
};
_corundsteinsenker::~_corundsteinsenker(){
};
void _corundsteinsenker::initialisieren(){
                                _corundstein::initialisieren();
                                if(modus==4) _netz::nurkollisionskopplung(true);
};
void _corundsteinsenker::kollision(_kollidierbar*k,_polygon*){
                                _corundsteinboulder*b;
                                _listenknoten<_corundsteinboulder>*bit;
                                //-------------------------------------
                                b=dynamic_cast<_corundsteinboulder*>(k->kollisionskopplung);
                                if(b){
                                 if(_liste<_corundsteinboulder>::suchen(b,bit)==false) new _verbinder<_corundsteinsenker,_corundsteinboulder>(b,this,this,b);
                                 switch(modus){
                                  case 0://senker erstmals berührt, absenken wird eingeleitet
                                   zaehler=(int)zyklen;
                                   modus=1;
                                   break;
                                  case 2://senker im abegesenkten zustand erstmals berührt
                                   zaehler=10;
                                   modus=3;
                                   break;
                                  case 4://senker im abgesenkten, entrührten zustand wieder berührt
                                   zaehler=10;
                                   modus=5;
                                   break;
                                 };
                                };
};
void _corundsteinsenker::animieren(){
                                switch(modus){
                                 case 1://senkt ab
                                  welt->corundinventar->text="1";
                                  if(zaehler>0){
                                   _netz::verschiebenvertex(vektor);
                                   _netz::aktualisierenschatten();
                                   _netz::aktualisieren();
                                   zaehler--;
                                  }else{// senker wurde abgesenkt
                                   modus=2;
                                   welt->corundinventar->text="2";
                                  _netz::nurkollisionskopplung(true);
                                  _netz::aktualisierenbaum();
                                  };
                                  break;
                                 case 3://wurde nach absenken berührt, wartet auf entrührung
                                  welt->corundinventar->text="3";
                                  if(zaehler>0){
                                   zaehler--;
                                  }else{
                                   if(innerhalbboulder()==false){
                                    _liste<_corundsteinboulder>::aushaengen();//verbund
                                    modus=4;//überwachung folgt : warte bis alle runter sind
                                   };
                                  };
                                  break;
                                 case 4://senker wurde entrührt , wartet auf berührung
                                  welt->corundinventar->text="4";
                                  break;
                                 case 5://senker wurde wieder berührt
                                  welt->corundinventar->text="5";
                                  if(zaehler>0){
                                   zaehler--;
                                  }else{
                                   if(innerhalbboulder()==false){
                                    _liste<_corundsteinboulder>::aushaengen();//verbund
                                    modus=6;
                                    _netz::nurkollisionskopplung(false);
                                    zaehler=(int)zyklen;
                                   };
                                  };
                                  break;
                                 case 6:
                                  welt->corundinventar->text="6";
                                  if(zaehler>0){
                                   _netz::verschiebenvertex(-vektor);
                                   _netz::aktualisierenschatten();
                                   _netz::aktualisieren();
                                   zaehler--;
                                  }else{// senker wurde hochgefahren
                                   modus=0;
                                   welt->corundinventar->text="0";
                                   _netz::aktualisierenbaum();
                                  };                                  
                                  break;
                                };
};
bool _corundsteinsenker::innerhalbboulder(){
                                _listenknoten<_corundsteinboulder>*bit;
                                //if(pruefen){//wird von boulder bei bewegung gesetzt
                                 if(_liste<_corundsteinboulder>::anfang(bit))do{
                                  if(bit->objekt()->hatintersektion(this)) return(true);
                                 }while(_liste<_corundsteinboulder>::naechstes(bit));
                               //  pruefen=false;
                                //};
                                return(false);
};
char _corundsteinsenker::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinsenker>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(modus);
                                r^=sd->ladenwert(zaehler);
                                r^=sd->ladenwert(zyklen);
                                r^=sd->ladenwert(vektor);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinsenker::speichern(_speicherbardynamisch<_corundsteinsenker>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(modus);
                                sd->speichernwert(zaehler);
                                sd->speichernwert(zyklen);
                                sd->speichernwert(vektor);
                                sd->speichernendeblock();
};                                
char _corundsteinsenker::assoziieren(_speicherbardynamisch<_corundsteinsenker>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinsenker::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Senker");
                                d->sektion(L"Corundstein Senker")->offen(true);
                                d->einhaengen(L"Corundstein Senker",L"Modus (0=oben, 4=abgesenkt)",modus);
                                d->einhaengen(L"Corundstein Senker",L"Animationszaehler",zaehler);
                                d->einhaengen(L"Corundstein Senker",L"Animationszyklen",zyklen);
                                d->einhaengen(L"Corundstein Senker",L"Animationsrichtung",vektor);
};
void _corundsteinsenker::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Senker",L"Modus (0=oben, 4=abgesenkt)",modus);
                                d->auslesen(L"Corundstein Senker",L"Animationszaehler",zaehler);
                                d->auslesen(L"Corundstein Senker",L"Animationszyklen",zyklen);
                                d->auslesen(L"Corundstein Senker",L"Animationsrichtung",vektor);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T R A H L 
//******************************************************************************************************************************************************************************************************
_corundstrahl::_corundstrahl(_corundsteinlaser*csl,const _vektor3<_tg>&o,const _vektor3<_tg>&v):_listenknotenbasis<_corundstrahl>(csl){    
                                radius=0.3;
                                ort=o;
                                vektor=v;
                                laser=csl;
                                kk=new _kollidierbarkugel(this,laser->welt->welt,0,0,o,v,0.00001);
                                netz[0]=0;
                                netz[1]=0;
                                netz[2]=0;
};
_corundstrahl::~_corundstrahl(){
                                if(netz[0]) delete netz[0];
                                if(netz[1]) delete netz[1];
                                if(netz[2]) delete netz[2];
                                delete kk;
};
void _corundstrahl::anlegen(){
                                vektornormal=vektor;
                                vektornormal.normalisieren();
                                if(kk->testen()==false){
                                 vektor=kk->schnittpunkt.ort-ort;
                                };
                                kk->aktivitaet(false);
                                if(vektor.laenge()>nahenull){ 
                                 _vektoranalysis3<_tg> V3;
                                 _vektor3<_tg> h;
                                 L->schreiben("Vektor ======",vektor);

                                 V3.berechnenorthogonalenvektor(vektornormal,h);
                                   h.normalisieren();
                                  h*=radius;
                                 for(int i=0;i<3;i++){
                                  L->schreiben("hr ======",h);
                                
                                  _geometrienetz*gn=new _geometrienetz(0,ort-h*0.5,vektor,h,laser->welt->textur[45]);
                                  //_geometrienetz*gn=new _geometrienetz(0,ort,_vektor3<_tg>(100,0,0),h,laser->welt->textur[39]);
                                  netz[i]=gn->erzeugen();
                                  netz[i]->einhaengen(laser->welt->welt);
                                  netz[i]->transparenz(true);
                                  netz[i]->verwendentexturdynamisch(false);
                                  netz[i]->farbeverbinder(_vektor4<_to>(0.0,0.0,1,1));
                                  netz[i]->subtraktiv(true);
                                  netz[i]->zweiseitig(true);
                                  netz[i]->lightmapschattierung(false);
                                  netz[i]->keinbsp(true);
                                  netz[i]->schattenvolumen(false);
                                  netz[i]->schattenvolumenlaenge(150);
                                  netz[i]->nurkollisionskopplung(true);                                 
                                  //netz[i]->zeichnenkante(true);                                 
                                  delete gn;
                                  _partition::_zone*zit;
                                  _partition::_sektor*sit;
                                  _tg x0,x1,y0,y1,z0,z1;
                                  _polygon*pit;
                                  if(laser->welt->welt->anfang(zit))do{
                                   zit->einfuegenintern(netz[i]);
                                   if(netz[i]->anfang(pit))do{
                                    pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                    
                                    //kollisionskopplung vornehmen
                                    pit->::_liste<_kollisionskopplung>::aushaengen();
                                    pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                    
                                    if(zit->anfang(sit))do{
                                     sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                    }while(zit->naechstes(sit));
                                   }while(netz[i]->naechstes(pit));
                                  }while(laser->welt->welt->naechstes(zit));
                                  _vektor3<_tg> e;
                                  V3.rotieren(vektornormal,h,60,e);
                                  h=e;
                                  

                                  
                                 };
                                };
};
void _corundstrahl::kollision(_kollidierbar*k,_polygon*){
                                 _corundkugel*kk;
                                 kk=dynamic_cast<_corundkugel*>(k);
                                 if(kk){
                                  laser->schaltenstrahlberuehrung();
                                  if(laser->toedlich) kk->zerstoeren();
                                 };

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N L A S E R 
//******************************************************************************************************************************************************************************************************
_corundsteinlaser::_corundsteinlaser(_corundwelt*ow):_corundstein(ow){
                                vektor.setzen(1,0,0);
                                pton=new _corundton(ow,ow->tonverwaltung.ton(6),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));
                                toedlich=true;
};
_corundsteinlaser::_corundsteinlaser(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex):_corundstein(ow,x,y,z,wx,wy,wz,tex,false){
                                vektor.setzen(1,0,0);
                                pton=new _corundton(ow,ow->tonverwaltung.ton(6),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));
                                toedlich=true;
};
_corundsteinlaser::~_corundsteinlaser(){
                                delete pton;
};
void _corundsteinlaser::neuberechnen(){
                                if(_listebasis<_corundstrahl>::anzahl()>0){
                                 _listebasis<_corundstrahl>::loeschen();
                                 _liste<_corundsteinspiegel>::aushaengen();
                                 _corundstrahl*cs=new _corundstrahl(this,_netz::mitte()-_vektor3<_tg>(0,0.2,0),vektor*500);
                                 cs->anlegen();
                                };
};
void _corundsteinlaser::schalten(){
                                if(_listebasis<_corundstrahl>::anzahl()>0) {
                                 //licht aus
                                 _listebasis<_corundstrahl>::loeschen();
                                 _liste<_corundsteinspiegel>::aushaengen();
                                }else{
                                 //licht an
                                 _corundstrahl*cs=new _corundstrahl(this,_netz::mitte()-_vektor3<_tg>(0,0.2,0),vektor*500);
                                 cs->anlegen();
                                 pton->ort=_netz::mitte();
                                 pton->abspielen();
                                };
};
void _corundsteinlaser::schaltenstrahlberuehrung(){
                                _listenknoten<_corundstein>*oit;
                                if(liste.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(liste.naechstes(oit));
};
void _corundsteinlaser::animieren(){
};
void _corundsteinlaser::kollision(_kollidierbar*k,_polygon*){

};
char _corundsteinlaser::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinlaser>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(vektor);
                                r^=sd->ladenwert(toedlich);
                                r^=sd->ladenwert(anzahlzeiger);
                                for(unsigned int i=0;i<anzahlzeiger;i++) r^=sd->ladenassoziation();

                                sd->ladenende();
                                return(r);
};                                
void _corundsteinlaser::speichern(_speicherbardynamisch<_corundsteinlaser>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(vektor);
                                sd->speichernwert(toedlich);
                                _listenknoten<_corundstein>*it;
                                sd->speichernwert(liste.anzahl());
                                if(liste.anfang(it))do{
                                 saveassociationargument(sd->datei(),sd,it->objekt());
                                }while(liste.naechstes(it));
                                
                                sd->speichernendeblock();
};                                
char _corundsteinlaser::assoziieren(_speicherbardynamisch<_corundsteinlaser>*sd){
                                sd->assoziierenverschachtelung();
                                liste.aushaengen();
                                _corundstein*corundstein=0;
                                for(unsigned int i=0;i<anzahlzeiger;i++) {
                                 corundstein=0;
                                 associateassociationargument(sd->datei(),sd->assoziation(),corundstein);
                                 if(corundstein){
                                  liste.einhaengen(corundstein);
                                 };
                                };                                
                                return(1);
};
 void _corundsteinlaser::netzwahl(_netz*n,int){
                                _corundstein*os=dynamic_cast<_corundstein*>(n);
                                if(os){
                                 liste.einhaengenunredundant(os);
                                };
};
void _corundsteinlaser::beiknopfausfuehren(_guiereignisdaten*ep){
                                //netz auswahldialog aktivieren
                                
                                if(hauptfenster) {
                                 hauptfenster->dnetzwahl->corundstein(this);
                                 hauptfenster->dnetzwahl->zeigen();
                                };
};
void _corundsteinlaser::beiknopfloeschen(_guiereignisdaten*){
                                liste.aushaengen();
                                hauptfenster->zeichnen();
};
void _corundsteinlaser::beiknopfloeschenletzten(_guiereignisdaten*){
                                _listenknoten<_corundstein>*lnosit;
                                if(liste.anfang(lnosit)){
                                 lnosit=lnosit->vorheriges();
                                 delete lnosit;
                                };
                                hauptfenster->zeichnen();
};
void _corundsteinlaser::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Laser");
                                d->sektion(L"Corundstein Laser")->offen(true);
                                d->einhaengen(L"Corundstein Laser",L"Strahlrichtung",vektor);
                                d->einhaengen(L"Corundstein Laser",L"Tödlich",toedlich);
                                d->einhaengenknopf<_corundsteinlaser>(L"Corundstein Laser",L"Schalter : Neuen Zeiger",L"holen",this,&_corundsteinlaser::beiknopfausfuehren);
                                d->einhaengenknopf<_corundsteinlaser>(L"Corundstein Laser",L"Schalter : Letzten Zeiger",L"löschen",this,&_corundsteinlaser::beiknopfloeschenletzten);
                                d->einhaengenknopf<_corundsteinlaser>(L"Corundstein Laser",L"Schalter : Alle Zeiger",L"löschen",this,&_corundsteinlaser::beiknopfloeschen);
                                
};
void _corundsteinlaser::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Laser",L"Strahlrichtung",vektor);
                                d->auslesen(L"Corundstein Laser",L"Tödlich",toedlich);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S P I E G E L
//******************************************************************************************************************************************************************************************************
_corundsteinspiegel::_corundsteinspiegel(_corundwelt*ow):_corundstein(ow){
                                achse.setzen(0,1,0);
                                raster=90;
                                festrichtung.setzen(1,0,0);
                                modusfestrichtung=false;                                
                                pton=new _corundton(ow,ow->tonverwaltung.ton(7),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));
};
_corundsteinspiegel::_corundsteinspiegel(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_textur<_tb>*tex):_corundstein(ow,x,y,z,wx,wy,wz,tex,false){
                                achse.setzen(0,1,0);
                                raster=90;
                                festrichtung.setzen(1,0,0);
                                modusfestrichtung=false;                                
                                pton=new _corundton(ow,ow->tonverwaltung.ton(7),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));                                
};
_corundsteinspiegel::~_corundsteinspiegel(){
                                delete pton;
};

void _corundsteinspiegel::schalten(){
                                //untersuchen, welche laser aktualisiert werden müssen
                                _liste<_corundsteinlaser> ls;
                                _listenknoten<_corundsteinlaser>*lit;
                                if(_liste<_corundsteinlaser>::anfang(lit))do{
                                 ls.einhaengenunredundant(lit->objekt());
                                }while(_liste<_corundsteinlaser>::naechstes(lit));
                                //netz drehen
                                _netz::rotieren(_netz::mitte(),achse,raster);
                                _netz::aktualisierenschatten();
                                //laser aktualisieren
                                if(ls.anfang(lit))do{
                                 lit->objekt()->neuberechnen();
                                }while(ls.naechstes(lit));
                                ls.aushaengen();
                                //ton abspielen
                                pton->ort=_netz::mitte();
                                pton->abspielen();
                                

};
void _corundsteinspiegel::animieren(){

};
void _corundsteinspiegel::kollision(_kollidierbar*k,_polygon*){
                                _corundstrahl*cs=dynamic_cast<_corundstrahl*>(k->kollisionskopplung);
                                if(cs){
                                 //neuen strahl anlegen
                                 _vektor3<_tg> l,av,o;
                                 if(modusfestrichtung==false){
                                  _vektoranalysis3<_tg> v3;
                                  _tg p;
                                  v3.lotpunktgerade(k->schnittpunkt.ort-cs->vektornormal,k->schnittpunkt.ort,k->schnittpunkt.normale,l,p);
                                  av=((k->schnittpunkt.ort-cs->vektornormal)+(l*2))-k->schnittpunkt.ort;
                                  o=k->schnittpunkt.ort;
                                 }else{
                                  av=festrichtung;
                                  o=_netz::mitte();
                                 };
                                 av.normalisieren();
                                 new _verbinder<_corundsteinlaser,_corundsteinspiegel>(this,cs->laser,cs->laser,this);
                                 _corundstrahl*csn=new _corundstrahl(cs->laser,o,av*500);
                                 csn->anlegen();
                                };
};
char _corundsteinspiegel::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinspiegel>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(achse);
                                r^=sd->ladenwert(raster);
                                r^=sd->ladenwert(festrichtung);
                                r^=sd->ladenwert(modusfestrichtung);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinspiegel::speichern(_speicherbardynamisch<_corundsteinspiegel>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(achse);
                                sd->speichernwert(raster);
                                sd->speichernwert(festrichtung);
                                sd->speichernwert(modusfestrichtung);
                                sd->speichernendeblock();
};                                
char _corundsteinspiegel::assoziieren(_speicherbardynamisch<_corundsteinspiegel>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinspiegel::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Spiegel");
                                d->sektion(L"Corundstein Spiegel")->offen(true);
                                d->einhaengen(L"Corundstein Spiegel",L"Rotationsachse",achse);
                                d->einhaengen(L"Corundstein Spiegel",L"Rotationsraster",raster);
                                d->einhaengen(L"Corundstein Spiegel",L"Feste Ausfallsrichtung benutzen",modusfestrichtung);
                                d->einhaengen(L"Corundstein Spiegel",L"Feste Ausfallsrichtung",festrichtung);

};
void _corundsteinspiegel::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Spiegel",L"Rotationsachse",achse);
                                d->auslesen(L"Corundstein Spiegel",L"Rotationsraster",raster);
                                d->auslesen(L"Corundstein Spiegel",L"Feste Ausfallsrichtung benutzen",modusfestrichtung);
                                d->auslesen(L"Corundstein Spiegel",L"Feste Ausfallsrichtung",festrichtung);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H L O S S
//******************************************************************************************************************************************************************************************************
_corundsteinschloss::_corundsteinschloss(_corundwelt*ow):_corundstein(ow),_corundschalter<_corundsteinschloss>(ow){
                                schloss=0;
                                schluessel=0;
};
_corundsteinschloss::_corundsteinschloss(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[92],true),_corundschalter<_corundsteinschloss>(ow){
                                schloss=0;
                                schluessel=0;
};
_corundsteinschloss::~_corundsteinschloss(){
};
void _corundsteinschloss::nachbereitenkonstruktion(){
                                if(schluessel==0) _netz::textur(_corundstein::welt->textur[92]); else _netz::textur(_corundstein::welt->textur[93]);
};
void _corundsteinschloss::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*c=dynamic_cast<_corundkugel*>(k);
                                if(c){
                                 if((c==_corundstein::welt->spieler)&&(_corundstein::welt->corundinventar)){
                                  if(schluessel){
                                   abschliessen();
                                  }else{
                                   //untersuchen ob spieler schluessel hat
                                   //und dann aufschließen
                                   _corundobjekt*co;
                                   _corundobjektschluessela*cosa;
                                   cosa=0;
                                   if(_corundstein::welt->corundinventar->anfang(co))do{
                                    cosa=dynamic_cast<_corundobjektschluessela*>(co);
                                    if(cosa){
                                     if(cosa->schloss!=schloss) cosa=0;
                                    };
                                   }while((_corundstein::welt->corundinventar->naechstes(co))&&(cosa==0));
                                   if(cosa){
                                    aufschliessen(cosa);
                                   };
                                  };
                                 };
                                };
};
void _corundsteinschloss::abschliessen(){
                                if(schluessel) schluessel->aufsammeln();
                                schluessel=0;                                
                                _corundschalter<_corundsteinschloss>::schalten();
                                _netz::textur(_corundstein::welt->textur[92]);
};
void _corundsteinschloss::aufschliessen(_corundobjektschluessela*cs){
                                schluessel=cs;
                                schluessel->ablegen(_netz::mitte());
                                _corundschalter<_corundsteinschloss>::schalten();
                                _netz::textur(_corundstein::welt->textur[93]);
};
void _corundsteinschloss::initialisieren(){
                                _corundstein::initialisieren();
                                if(schluessel==0) _netz::textur(_corundstein::welt->textur[92]); else _netz::textur(_corundstein::welt->textur[93]);
};
void _corundsteinschloss::animieren(){
};
void _corundsteinschloss::zeichnen(_grafik*g){
                                _corundstein::zeichnen(g);
                                _corundschalter<_corundsteinschloss>::zeichnen(g);
};

char _corundsteinschloss::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinschloss>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(schloss);
                                r^=sd->ladenassoziation();
                                _corundschalter<_corundsteinschloss>::laden(fn,sd);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinschloss::speichern(_speicherbardynamisch<_corundsteinschloss>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(schloss);
                                saveassociationargument(sd->datei(),sd,schluessel);
                                _corundschalter<_corundsteinschloss>::speichern(sd);
                                sd->speichernendeblock();
};                                
char _corundsteinschloss::assoziieren(_speicherbardynamisch<_corundsteinschloss>*sd){
                                sd->assoziierenverschachtelung();
                                associateassociationargument(sd->datei(),sd->assoziation(),schluessel);
                                _corundschalter<_corundsteinschloss>::assoziieren(sd);
                                return(1);
};
void _corundsteinschloss::einhaengendialog(_dynamischerdialog*d){
                                _corundschalter<_corundsteinschloss>::dialogschaltkopplungswahl=hauptfenster->dsteinschlossschaltkopplungswahl;
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Schloss");
                                d->sektion(L"Corundstein Schloss")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundstein Schloss",L"Schlossindex [uint]",schloss);
                                _corundschalter<_corundsteinschloss>::einhaengendialog(d);
};
void _corundsteinschloss::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Schloss",L"Schlossindex [uint]",schloss);
                                _corundschalter<_corundsteinschloss>::auslesendialog(d);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E R E I G N I S S
//******************************************************************************************************************************************************************************************************
_corundsteinereignis::_corundsteinereignis(_corundwelt*ow):_corundstein(ow),_corundschalter<_corundsteinereignis>(ow){
                                zaehler=0;
                                takt=700;
                                eingeschaltet=true;
};
_corundsteinereignis::_corundsteinereignis(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true),_corundschalter<_corundsteinereignis>(ow){
                                zaehler=0;
                                takt=700;
                                eingeschaltet=true;
};
_corundsteinereignis::~_corundsteinereignis(){
};
void _corundsteinereignis::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteinereignis::animieren(){
                                if(eingeschaltet){
                                 zaehler++;
                                 if(zaehler>takt) {
                                  zaehler=0;
                                  _corundschalter<_corundsteinereignis>::schalten();
                                 };
                                };
};
void _corundsteinereignis::schalten(){
                                eingeschaltet=!eingeschaltet;
};
void _corundsteinereignis::zeichnen(_grafik*g){
                                _corundstein::zeichnen(g);
                                _corundschalter<_corundsteinereignis>::zeichnen(g);
};
char _corundsteinereignis::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinereignis>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(eingeschaltet);
                                r^=sd->ladenwert(takt);
                                r^=sd->ladenwert(zaehler);
                                _corundschalter<_corundsteinereignis>::laden(fn,sd);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinereignis::speichern(_speicherbardynamisch<_corundsteinereignis>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(eingeschaltet);
                                sd->speichernwert(takt);
                                sd->speichernwert(zaehler);
                                _corundschalter<_corundsteinereignis>::speichern(sd);
                                sd->speichernendeblock();
};                                
char _corundsteinereignis::assoziieren(_speicherbardynamisch<_corundsteinereignis>*sd){
                                sd->assoziierenverschachtelung();
                                _corundschalter<_corundsteinereignis>::assoziieren(sd);
                                return(1);
};
void _corundsteinereignis::einhaengendialog(_dynamischerdialog*d){
                                _corundschalter<_corundsteinereignis>::dialogschaltkopplungswahl=hauptfenster->dsteinereignisschaltkopplungswahl;
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Ereignis");
                                d->sektion(L"Corundstein Ereignis")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundstein Ereignis",L"Eingeschaltet",eingeschaltet);
                                d->einhaengen(L"Corundstein Ereignis",L"Periode [f]",takt);
                                d->einhaengen(L"Corundstein Ereignis",L"Zähler [f]",zaehler);
                                _corundschalter<_corundsteinereignis>::einhaengendialog(d);
};
void _corundsteinereignis::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Ereignis",L"Eingeschaltet",eingeschaltet);
                                d->auslesen(L"Corundstein Ereignis",L"Periode [f]",takt);
                                d->auslesen(L"Corundstein Ereignis",L"Zähler [f]",zaehler);
                                _corundschalter<_corundsteinereignis>::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N G E R I S S E N 
//******************************************************************************************************************************************************************************************************
_corundsteingerissen::_corundsteingerissen(_corundwelt*ow):_corundstein(ow){
                                huelle=0;
                                schwaechung=0;
};
_corundsteingerissen::_corundsteingerissen(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
                                huelle=0;
                                schwaechung=0;
                                nachbereitenkonstruktion();
};
_corundsteingerissen::~_corundsteingerissen(){
                                if(huelle) delete huelle;
                                huelle=0;
};
void _corundsteingerissen::nachbereitenkonstruktion(){
                                if(huelle) delete huelle;
                                huelle=0;
                                _tg x0,x1,y0,y1,z0,z1;
                                _netz::umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                ort.setzen(x0,y0,z0);
                                breite.setzen(x1-x0,y1-y0,z1-z0);
                                _netz::lightmapschattierung(false);
                                huelle=_netz::duplizieren();
                                huelle->verschiebennormal(0.01);
                                huelle->einhaengen(welt->welt);
                                huelle->transparenz(true);
                                huelle->transparenzadditiv(false);
                                huelle->verwendentextur(true); 
                                huelle->subtraktiv(false);
                                huelle->kollision(false);
                                huelle->farbeverbinder(_vektor4<_to>(1.0,1.0,1.0,1));
                                huelle->keinbsp(true);
                                huelle->lightmapschattierung(false);
                                huelle->schattenvolumen(false);
                                huelle->nichtspeichern(true);
                                aktualisierentextur();
};
void _corundsteingerissen::initialisieren(){
                                _corundstein::initialisieren();
                                grav=welt->welt->gravitation(ort);
};
void _corundsteingerissen::aktualisierentextur(){
                                int i=85+int((schwaechung+(1.0f/12.0f))*6);
                                if(i<85) i=85;
                                if(i>90) i=90;
                                huelle->textur(welt->textur[i]);
};
void _corundsteingerissen::kollision(_kollidierbar*k,_polygon*){
                                _corundobjekt*co;
                                _corundobjekthammer*coh;
                                _corundkugel*c=dynamic_cast<_corundkugel*>(k);
                                if(c){
                                 if(c==welt->spieler){
                                  if(welt->corundinventar){
                                   if(welt->corundinventar->anfang(co)){
                                    coh=dynamic_cast<_corundobjekthammer*>(co);
                                    if(coh){
                                     schwaechung+=0.1;
                                     if(schwaechung>1){
                                      schwaechung=1;
                                      zerstoeren();
                                     };
                                     aktualisierentextur();
                                    };
                                   };
                                  };
                                 };
                                };
};
void _corundsteingerissen::zerstoeren(){
                                welt->steinzumloeschen.einhaengenunredundant(this);
                                _partikelquellesprite*psrot;
                                _polygon*pit;
                                _netz::anfang(pit);
                                pit=pit->naechstes();
                                psrot=new _partikelquellesprite(welt->welt,welt->welt,welt->welt,welt->pzeit,_vektor3<_tg>(-1,-1,-1),_vektor3<_tg>(0,0,0),150,pit->textur());
                                psrot->name("Gerissener Stein : Broesel");
                                psrot->aktiv(true);
                                psrot->ort(ort);
                                psrot->ortraum(_vektor3<_tg>(breite[0]/2.0f,0,0), _vektor3<_tg>(0,breite[1]/2.0f,0), _vektor3<_tg>(0,0,breite[2]/2.0f));
                                psrot->groesse(0.2);
                                psrot->generationsrate(1000);
                                psrot->generationsratetoleranz(0.5);
                                psrot->groessetoleranz(0.5);
                                psrot->vektortoleranz(0.0);
                                psrot->rotation(1);
                                psrot->rotationtoleranz(0.9);
                                psrot->lebensdauerpartikeltoleranz(0.5);    
                                psrot->animieren();
                                delete psrot;                              
};
void _corundsteingerissen::animieren(){
                                _vektor3<_tg> g;
                                g=welt->welt->gravitation(ort);
                                _tg f=fabs(g.laenge()-grav.laenge());
                                if(f>0.04){
                                 schwaechung+=f*0.2;
                                 if(schwaechung>1) {
                                  schwaechung=1;
                                  zerstoeren();
                                 };
                                 aktualisierentextur();
                                };
                                grav=g;
};
char _corundsteingerissen::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteingerissen>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(schwaechung);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteingerissen::speichern(_speicherbardynamisch<_corundsteingerissen>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(schwaechung);
                                sd->speichernendeblock();
};                                
char _corundsteingerissen::assoziieren(_speicherbardynamisch<_corundsteingerissen>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteingerissen::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Gerissen");
                                d->sektion(L"Corundstein Gerissen")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundstein Gerissen",L"Beschädigung [0..1]",schwaechung);

};
void _corundsteingerissen::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Gerissen",L"Beschädigung [0..1]",schwaechung);
                                aktualisierentextur();
                                
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S P U C K 
//******************************************************************************************************************************************************************************************************
_corundsteinspuck::_corundsteinspuck(_corundwelt*ow):_corundstein(ow){
                                vektor.setzen(0,0.3,0);
                                invalid=false;
};
_corundsteinspuck::_corundsteinspuck(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
                                vektor.setzen(0,0.3,0);
                                invalid=false;
};
_corundsteinspuck::~_corundsteinspuck(){
};
void _corundsteinspuck::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*c;
                                _corundobjekt*co;
                                _corundobjektbombe*cob;
                                //--------------------
                                c=dynamic_cast<_corundkugel*>(k);
                                if(c){
                                 if(c==welt->spieler){
                                  if(welt->corundinventar){
                                   cob=0;
                                   if(welt->corundinventar->anfang(co))do{
                                    cob=dynamic_cast<_corundobjektbombe*>(co);
                                   }while((welt->corundinventar->naechstes(co))&&(cob==0));
                                   if(cob){
                                    if(invalid==false){
                                     _vektor3<_tg> v=k->schnittpunkt.vektor;
                                     v.normalisieren();
                                     v*=k->vektor().laenge();
                                     cob->werfen(_netz::mitte(),v+vektor);//kugelvektor+steinvektor
                                    };
                                   }; 
                                  };
                                 }; 
                                }else{
                                 cob=dynamic_cast<_corundobjektbombe*>(k->kollisionskopplung);
                                 if(cob){
                                  if(cob->wurfmodus){
                                   invalid=true;
                                  };
                                 };
                                };
};
void _corundsteinspuck::animieren(){
};
char _corundsteinspuck::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinspuck>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(vektor);
                                r^=sd->ladenwert(invalid);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinspuck::speichern(_speicherbardynamisch<_corundsteinspuck>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(vektor);
                                sd->speichernwert(invalid);
                                sd->speichernendeblock();
};                                
char _corundsteinspuck::assoziieren(_speicherbardynamisch<_corundsteinspuck>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinspuck::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Spuck");
                                d->sektion(L"Corundstein Spuck")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundstein Spuck",L"Richtung [m/f]",vektor);
                                d->einhaengen(L"Corundstein Spuck",L"Invalid",invalid);
};
void _corundsteinspuck::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Spuck",L"Richtung [m/f]",vektor);
                                d->auslesen(L"Corundstein Spuck",L"Invalid",invalid);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N T A U S C H E R 
//******************************************************************************************************************************************************************************************************
_corundsteintauscher::_corundsteintauscher(_corundwelt*ow):_corundstein(ow){
};
_corundsteintauscher::_corundsteintauscher(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
};
_corundsteintauscher::~_corundsteintauscher(){
};
void _corundsteintauscher::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteintauscher::animieren(){
};
char _corundsteintauscher::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteintauscher>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteintauscher::speichern(_speicherbardynamisch<_corundsteintauscher>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteintauscher::assoziieren(_speicherbardynamisch<_corundsteintauscher>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteintauscher::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein tauscher");
                                d->sektion(L"Corundstein tauscher")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteintauscher::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N M A G N E T I S C H 
//******************************************************************************************************************************************************************************************************
_corundsteinmagnetisch::_corundsteinmagnetisch(_corundwelt*ow):_corundstein(ow){
                                magnet=0;
};
_corundsteinmagnetisch::_corundsteinmagnetisch(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
                                magnet=0;
                                nachbereitenkonstruktion();
};
_corundsteinmagnetisch::~_corundsteinmagnetisch(){
                                if(magnet) delete magnet;
                                magnet=0;
};
void _corundsteinmagnetisch::nachbereitenkonstruktion(){
                                if(magnet==0){
                                 magnet=new _feldmagnetostatisch<_tg>(welt->welt,_netz::mitte(),_vektor3<_tg>(0,1,0));
                                };
};
void _corundsteinmagnetisch::verschiebenvertex(const _vektor3<_tg>v){
                                _netz::verschiebenvertex(v);
                                if(magnet){
                                 magnet->ort(magnet->ort()+v);
                                };
};
void _corundsteinmagnetisch::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteinmagnetisch::animieren(){
};
void _corundsteinmagnetisch::schalten(){
                                if(magnet){
                                 magnet->aktiv(!magnet->aktiv());
                                };
};
char _corundsteinmagnetisch::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinmagnetisch>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenassoziation();
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinmagnetisch::speichern(_speicherbardynamisch<_corundsteinmagnetisch>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                saveassociationargument(sd->datei(),sd,magnet);
                                sd->speichernendeblock();
};                                
                              
                               
char _corundsteinmagnetisch::assoziieren(_speicherbardynamisch<_corundsteinmagnetisch>*sd){
                                sd->assoziierenverschachtelung();
                                associateassociationargument(sd->datei(),sd->assoziation(),magnet); 
                                return(1);
};
void _corundsteinmagnetisch::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Magnetisch");
                                d->sektion(L"Corundstein Magnetisch")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                magnet->einhaengendialog(d);
};
void _corundsteinmagnetisch::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                magnet->auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N D I E B 
//******************************************************************************************************************************************************************************************************
_corundsteindieb::_corundsteindieb(_corundwelt*ow):_corundstein(ow){
                                lach[0]=new _corundton(ow,ow->tonverwaltung.ton(8),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));             
                                lach[1]=new _corundton(ow,ow->tonverwaltung.ton(9),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));             
                                lach[2]=new _corundton(ow,ow->tonverwaltung.ton(10),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));             
                                spinne=0;
                                rahmen=0;
                                modus=0;
                                zaehler=0;
                                kugel=0;
                                hatgeklaut=false;
};
_corundsteindieb::_corundsteindieb(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
                                lach[0]=new _corundton(ow,ow->tonverwaltung.ton(8),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));             
                                lach[1]=new _corundton(ow,ow->tonverwaltung.ton(9),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));             
                                lach[2]=new _corundton(ow,ow->tonverwaltung.ton(10),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));             
                                spinne=0;
                                rahmen=0;
                                modus=0;
                                zaehler=0;
                                kugel=0;
                                hatgeklaut=false;
                                nachbereitenkonstruktion();

};
_corundsteindieb::~_corundsteindieb(){
                                delete lach[0];
                                delete lach[1];
                                delete lach[2];
                                if(spinne) delete spinne;
                                spinne=0;
                                if(rahmen) delete rahmen;
                                rahmen=0;
};
void _corundsteindieb::nachbereitenkonstruktion(){
                                if(spinne) delete spinne;
                                spinne=0;
                                if(rahmen) delete rahmen;
                                rahmen=0;
                                _netz::textur(welt->textur[84]);
                                _netz::maskiert(true);
                                
                                _tg x0,x1,y0,y1,z0,z1;
                                _netz::umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                ort.setzen(x0,y0,z0);
                                breite.setzen(x1-x0,y1-y0,z1-z0);
                                _tg x=ort[0];
                                _tg y=ort[1];
                                _tg z=ort[2];
                                _tg wx=breite[0];
                                _tg wy=breite[1];
                                _tg wz=breite[2];
                                _geometrienetz*nn=new _geometrienetz(welt->welt,_vektor3<_tg>(x+wx*0.01,y+wy+0.01,z+wz*0.01),_vektor3<_tg>(wx*0.98,0,0),_vektor3<_tg>(0 ,0,wz*0.98),welt->textur[54]);
                                spinne=nn->erzeugen();
                                spinne->einhaengen(welt->welt);
                                spinne->verwendentextur(true); 
                                spinne->markierungpolygon(1);
                                spinne->subtraktiv(false);
                                spinne->farbeverbinder(_vektor4<_to>(1.0,1.0,1.0,1));
                                spinne->keinbsp(true);
                                spinne->schattenvolumen(false);
                                spinne->nichtspeichern(true);
                                spinne->verschiebentexturkoordinaten(_vektor2<_tg>(0,+0.6),0);
                                delete nn;
                                nn=new _geometrienetz(welt->welt,_vektor3<_tg>(x,y+wy+0.02,z),_vektor3<_tg>(wx,0,0),_vektor3<_tg>(0 ,0,wz),welt->textur[84]);
                                rahmen=nn->erzeugen();
                                rahmen->einhaengen(welt->welt);
                                rahmen->verwendentextur(true); 
                                rahmen->markierungpolygon(1);
                                rahmen->subtraktiv(false);
                                rahmen->farbeverbinder(_vektor4<_to>(1.0,1.0,1.0,1));
                                rahmen->keinbsp(true);
                                rahmen->maskiert(true);
                                rahmen->schattenvolumen(false);
                                rahmen->nichtspeichern(true);
                                delete nn;
};                                
                                

void _corundsteindieb::initialisieren(){
                                _corundstein::initialisieren();
                                _vektor3<_tg> m=_netz::mitte();
                                lach[0]->ort=m;
                                lach[1]->ort=m;
                                lach[2]->ort=m;
                                spinne->farbeverbinder(_vektor4<_to>(1.0,1.0,1.0,1));

};
void _corundsteindieb::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*c=dynamic_cast<_corundkugel*>(k);
                                if(c){
                                 if(c->spieler){
                                  if(modus==0){
                                   modus=1;
                                   kugel=c;       
                                   zaehler=40;
                                  };
                                 };                          
                                };
};
void _corundsteindieb::animieren(){
                                if(modus==1){
                                 zaehler--;
                                 spinne->verschiebentexturkoordinaten(_vektor2<_tg>(0,-0.4f/40.0f),0);
                                 if(zaehler==0){
                                  modus=2;
                                  zaehler=64;
                                  //objekt aus dem inventar klauen
                                  _corundinventar*inv=welt->corundinventar;
                                  if(inv){
                                   if(inv->anzahl()>0){
                                    _zufallsgenerator<_tg> z;
                                    unsigned int i=(int)z.berechnen(0,2.9999);
                                    if(i>2) i=2;
                                    lach[i]->abspielen();
                                    inv->loeschenerstes();
                                    hatgeklaut=true;
                                   };
                                  };
                                 };
                                }else if(modus==2){
                                 zaehler--;
                                 if(hatgeklaut){
                                  if((zaehler%4)==0) {
                                   int i=zaehler/4;
                                   if((i%2)==0) {
                                    spinne->verschiebentexturkoordinaten(_vektor2<_tg>(0,+0.02),0);
                                   }else{
                                    spinne->verschiebentexturkoordinaten(_vektor2<_tg>(0,-0.02),0);
                                   };
                                  };
                                 };
                                 if(zaehler==0){
                                  modus=3;
                                  zaehler=40;
                                 };
                                }else if(modus==3){
                                 zaehler--;
                                 spinne->verschiebentexturkoordinaten(_vektor2<_tg>(0,+0.4f/40.0f),0);
                                 if(zaehler==0){
                                  modus=0;
                                  hatgeklaut=false;
                                 };
                                };
                                    
};
char _corundsteindieb::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteindieb>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(modus);
                                r^=sd->ladenwert(zaehler);
                                r^=sd->ladenwert(hatgeklaut);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteindieb::speichern(_speicherbardynamisch<_corundsteindieb>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(modus);
                                sd->speichernwert(zaehler);
                                sd->speichernwert(hatgeklaut);
                                sd->speichernendeblock();
};                                
char _corundsteindieb::assoziieren(_speicherbardynamisch<_corundsteindieb>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteindieb::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein dieb");
                                d->sektion(L"Corundstein dieb")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteindieb::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N F L I E G E N G E N
//******************************************************************************************************************************************************************************************************
_corundsteinfliegengen::_corundsteinfliegengen(_corundwelt*ow):_corundstein(ow){
};
_corundsteinfliegengen::_corundsteinfliegengen(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
};
_corundsteinfliegengen::~_corundsteinfliegengen(){
};
void _corundsteinfliegengen::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteinfliegengen::animieren(){
};
char _corundsteinfliegengen::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinfliegengen>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinfliegengen::speichern(_speicherbardynamisch<_corundsteinfliegengen>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteinfliegengen::assoziieren(_speicherbardynamisch<_corundsteinfliegengen>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinfliegengen::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein fliegengen");
                                d->sektion(L"Corundstein fliegengen")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteinfliegengen::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S P I N N E N G E N 
//******************************************************************************************************************************************************************************************************
_corundsteinspinnengen::_corundsteinspinnengen(_corundwelt*ow):_corundstein(ow){
};
_corundsteinspinnengen::_corundsteinspinnengen(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
};
_corundsteinspinnengen::~_corundsteinspinnengen(){
};
void _corundsteinspinnengen::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteinspinnengen::animieren(){
};
char _corundsteinspinnengen::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinspinnengen>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinspinnengen::speichern(_speicherbardynamisch<_corundsteinspinnengen>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteinspinnengen::assoziieren(_speicherbardynamisch<_corundsteinspinnengen>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinspinnengen::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein spinnengen");
                                d->sektion(L"Corundstein spinnengen")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteinspinnengen::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S H O G U N 
//******************************************************************************************************************************************************************************************************
_corundsteinshogun::_corundsteinshogun(_corundwelt*ow):_corundstein(ow){
};
_corundsteinshogun::_corundsteinshogun(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
};
_corundsteinshogun::~_corundsteinshogun(){
};
void _corundsteinshogun::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteinshogun::animieren(){
};
char _corundsteinshogun::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinshogun>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinshogun::speichern(_speicherbardynamisch<_corundsteinshogun>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteinshogun::assoziieren(_speicherbardynamisch<_corundsteinshogun>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinshogun::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein shogun");
                                d->sektion(L"Corundstein shogun")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteinshogun::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N P U Z Z L E 
//******************************************************************************************************************************************************************************************************
_corundsteinpuzzle::_corundsteinpuzzle(_corundwelt*ow):_corundstein(ow){
};
_corundsteinpuzzle::_corundsteinpuzzle(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
};
_corundsteinpuzzle::~_corundsteinpuzzle(){
};
void _corundsteinpuzzle::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteinpuzzle::animieren(){
};
char _corundsteinpuzzle::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinpuzzle>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinpuzzle::speichern(_speicherbardynamisch<_corundsteinpuzzle>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteinpuzzle::assoziieren(_speicherbardynamisch<_corundsteinpuzzle>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinpuzzle::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein puzzle");
                                d->sektion(L"Corundstein puzzle")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteinpuzzle::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N G A S 
//******************************************************************************************************************************************************************************************************
_corundsteingas::_corundsteingas(_corundwelt*ow):_corundstein(ow){
};
_corundsteingas::_corundsteingas(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
};
_corundsteingas::~_corundsteingas(){
};
void _corundsteingas::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteingas::animieren(){
};
char _corundsteingas::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteingas>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteingas::speichern(_speicherbardynamisch<_corundsteingas>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteingas::assoziieren(_speicherbardynamisch<_corundsteingas>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteingas::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein gas");
                                d->sektion(L"Corundstein gas")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteingas::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N K O M B I N A T I O N S S C H L O S S  
//******************************************************************************************************************************************************************************************************
_corundsteinkombinationsschloss::_corundsteinkombinationsschloss(_corundwelt*ow):_corundstein(ow){
};
_corundsteinkombinationsschloss::_corundsteinkombinationsschloss(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
};
_corundsteinkombinationsschloss::~_corundsteinkombinationsschloss(){
};
void _corundsteinkombinationsschloss::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteinkombinationsschloss::animieren(){
};
char _corundsteinkombinationsschloss::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteinkombinationsschloss>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteinkombinationsschloss::speichern(_speicherbardynamisch<_corundsteinkombinationsschloss>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernendeblock();
};                                
char _corundsteinkombinationsschloss::assoziieren(_speicherbardynamisch<_corundsteinkombinationsschloss>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteinkombinationsschloss::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein kombinationsschloss");
                                d->sektion(L"Corundstein kombinationsschloss")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundsteinkombinationsschloss::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N D R E H K R E U Z
//******************************************************************************************************************************************************************************************************
_corundsteindrehkreuz::_corundsteindrehkreuz(_corundwelt*ow):_corundstein(ow){
                                normale.setzen(0,1,0);
                                nord.setzen(0,0,1);
                                winkelraster=90;
                                iteratorschritte=20;
                                iterator=0;
                                winkel=0;
                                winkelalt=0;
                                kurve.ort(0,_vektor3<_tg>(0,0,0));
                                kurve.ort(1,_vektor3<_tg>(90,0,0));
                                kurve.vektor(0,_vektor3<_tg>(0,0,0));
                                kurve.vektor(1,_vektor3<_tg>(0,0,0));
};
_corundsteindrehkreuz::_corundsteindrehkreuz(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
                                normale.setzen(0,1,0);
                                nord.setzen(0,0,1);
                                winkelraster=90;
                                iteratorschritte=20;
                                iterator=0;
                                winkel=0;
                                winkelalt=0;
                                kurve.ort(0,_vektor3<_tg>(0,0,0));
                                kurve.ort(1,_vektor3<_tg>(90,0,0));
                                kurve.vektor(0,_vektor3<_tg>(0,0,0));
                                kurve.vektor(1,_vektor3<_tg>(0,0,0));
                                nachbereitenkonstruktion();
};
_corundsteindrehkreuz::~_corundsteindrehkreuz(){
};
void _corundsteindrehkreuz::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*ck=dynamic_cast<_corundkugel*>(k);
                                if(ck){
                                 if(k->schnittpunkt.polygon){
                                 
                                  _vektor3<_tg> tv;
                                  _vektor3<_tg> sv;
                                  _tg fn,ft;
                                  if(tuervektor(k->schnittpunkt.polygon,tv)){
                                   //ok, welche richtung ?
                                   //new _weltdebugpfeil(welt->welt,_netz::mitte(),_netz::mitte()+tv,0.1,0.04,_vektor4<_to>(0,1,1,1));
                                   sv=k->schnittpunkt.vektor;
                                   sv.normalisieren();
                                   ft=sv*tv;
                                   fn=sv*normale;
                                   if((fabs(ft)<0.5)&&(fabs(fn)<0.5)&&(fabs(k->schnittpunkt.polygon->normale()*normale)<0.5)){
                                    //gültiger stoßvektor
                                    _vektor3<_tg> h=sv%tv;
                                    if((h*normale)>0){
                                     winkelalt=winkel;
                                     iterator=1;
                                     kurve.ort(0,_vektor3<_tg>(winkelraster,0,0));
                                     kurve.ort(1,_vektor3<_tg>(0,0,0));
                                     kurve.vektor(1,_vektor3<_tg>(winkelraster*0.25,0,0));
                                     aushaengenoktalbaum();
                                    }else{
                                     winkelalt=winkel;
                                     iterator=1;
                                     kurve.ort(0,_vektor3<_tg>(-winkelraster,0,0));
                                     kurve.ort(1,_vektor3<_tg>(0,0,0));
                                     kurve.vektor(1,_vektor3<_tg>(-(winkelraster*0.25),0,0));
                                     aushaengenoktalbaum();
                                    };
                                   };
                                  };
                                 };
                                };
};
bool _corundsteindrehkreuz::tuervektor(_polygon*p,_vektor3<_tg>&tv){
                                _vektoranalysis3<_tg> va;
                                _listenknoten<_netz>*nit;
                                if(tuer.anfang(nit))do{
                                 _polygon*pit;
                                 if(nit->objekt()->anfang(pit))do{
                                  if(pit==p){
                                   tv=nit->objekt()->mitte()-netzmitte;
                                   tv.normalisieren();
                                   return(true);
                                  };
                                 }while(nit->objekt()->naechstes(pit));
                                }while(tuer.naechstes(nit));
                                return(false);
};
void _corundsteindrehkreuz::initialisieren(){
                                _corundstein::initialisieren();
                                _listenknoten<_netz>*nit;
                                if(tuer.anfang(nit))do{
                                 //kollisionskopplung vornehmen
                                 _polygon*pit;
                                 if(nit->objekt()->anfang(pit))do{
                                  pit->::_liste<_kollisionskopplung>::aushaengen();
                                  pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                 }while(nit->objekt()->naechstes(pit));
                                }while(tuer.naechstes(nit));
                                netzmitte=_netz::mitte();
                                _partition::_zone*zit;
                           
                                welt->welt->anfang(zit);
                                _netz::aktualisierennetzschatten();
                                _netz::erzeugenvertexlicht(zit);
                                _netz::kopierenortinparameter();
                                if(tuer.anfang(nit))do{
                                 nit->objekt()->aktualisierennetzschatten();
                                 nit->objekt()->erzeugenvertexlicht(zit);
                                 nit->objekt()->kopierenortinparameter();
                                }while(tuer.naechstes(nit));                                
};
void _corundsteindrehkreuz::schalten(){
                                if(iterator==0){
                                 winkelalt=winkel;
                                 iterator=1;
                                 kurve.ort(0,_vektor3<_tg>(winkelraster,0,0));
                                 kurve.ort(1,_vektor3<_tg>(0,0,0));
                                 kurve.vektor(1,_vektor3<_tg>(winkelraster*0.25,0,0));
                                 aushaengenoktalbaum();                                
                                };
};
void _corundsteindrehkreuz::animieren(){
                                _polygon*pit;
                                _listenknoten<_netz>*nit;
                                _tg ws;
                                _tg idelta;
                                //-------
                                if(iterator>0){
                                 idelta=1.0f/_tg(iteratorschritte);
                                 iterator-=idelta;
                                 
                                 if(fabs(iterator)<nahenull){//letzer zyklus
                                  iterator=0;
                                  winkel+=kurve.ort(0)[0];
                                  while(winkel>+360) winkel-=360;
                                  while(winkel<-360) winkel+=360;
                                  ws=winkel;
                                 }else{
                                  ws=winkel+kurve.berechnen(iterator)[0];//-winkelalt; 
                                 };
                                 
                                 
                                 
                                 
                                 _vektor3<_tg> m=netzmitte;
                                 
                                 
                                 
                                 
                                 
                                 
                                 
                                 
                                 //provisorisches anwenden der rotationskollision
                                 if(welt->spieler){
                                  if(tuer.anfang(nit))do{
                                   if(nit->objekt()->anfang(pit))do{
                                    if(fabs(normale*pit->normale())<(1-nahenull)){//cullen
                                     if(pit->innerhalbpunktrotation(welt->spieler->_kollidierbarkugel::ort(),m,normale,ws-winkelalt)) welt->spieler->zerstoeren();
                                    };
                                   }while(nit->objekt()->naechstes(pit));
                                  }while(tuer.naechstes(nit));
                                 };
                                 
                                 //rotation durchführen
                                 _partition::_zone*zit;
                                 welt->welt->anfang(zit);
                                 _netz::kopierenparameterinort();
                                 _netz::rotieren(m,normale,ws);
                                 _netz::aktualisierennetzschatten();
                                 _netz::erzeugenvertexlicht(zit);
                                 if(tuer.anfang(nit))do{
                                  nit->objekt()->kopierenparameterinort();
                                  nit->objekt()->rotieren(m,normale,ws);
                                  nit->objekt()->aktualisierennetzschatten();
                                  nit->objekt()->erzeugenvertexlicht(zit);
                                 }while(tuer.naechstes(nit));
                                 if(iterator==0){
                                  einhaengenoktalbaum();
                                 };
                                 winkelalt=ws;
                                };
};
void _corundsteindrehkreuz::aushaengenoktalbaum(){
                              //  _tg x0,x1,y0,y1,z0,z1;
                                _polygon*pit;
                                _listenknoten<_netz>*nit;
                                //-----------------------
                                if(_netz::anfang(pit))do{
                                 pit->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                }while(_netz::naechstes(pit)); 
                                if(tuer.anfang(nit))do{
                                 if(nit->objekt()->anfang(pit))do{
                                  pit->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                 }while(nit->objekt()->naechstes(pit));
                                }while(tuer.naechstes(nit));
};
void _corundsteindrehkreuz::einhaengenoktalbaum(){
                                _tg x0,x1,y0,y1,z0,z1;
                                _polygon*pit;
                                _partition::_zone*zit;
                                _partition::_sektor*sit;
                                _listenknoten<_netz>*nit;
                                //-------------------------
                                welt->welt->anfang(zit);
                                if(_netz::anfang(pit))do{
                                 pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                 if(zit->anfang(sit))do{
                                  sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                 }while(zit->naechstes(sit));
                                }while(_netz::naechstes(pit));             
                                if(tuer.anfang(nit))do{                     
                                 if(nit->objekt()->anfang(pit))do{
                                  pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                  if(zit->anfang(sit))do{
                                   sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                  }while(zit->naechstes(sit));
                                 }while(nit->objekt()->naechstes(pit));                                  
                                }while(tuer.naechstes(nit));
};
void _corundsteindrehkreuz::zeichnen(_grafik*g){
                                _corundstein::zeichnen(g);
                                _vektor3<_tg> m=_netz::mitte();
                                _listenknoten<_netz>*nit;
                                if(tuer.anfang(nit))do{
                                 _weltdebugpfeil*wp=new _weltdebugpfeil(welt->welt,m,nit->objekt()->mitte(),0.1,0.05,_vektor4<_to>(1,0.5,0.1,1));
                                 _weltdebugtext*wt=new _weltdebugtext (welt->welt,"Drehfluegel",(m+nit->objekt()->mitte())*0.5f,_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,0.3),_vektor4<_to>(1,0.5,0.1,1));
                                 wp->zeichnen(g);
                                 wt->zeichnen(g);
                                 delete wp;
                                 delete wt;
                                }while(tuer.naechstes(nit));
};
char _corundsteindrehkreuz::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteindrehkreuz>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(normale);
                                r^=sd->ladenwert(nord);
                                r^=sd->ladenwert(winkelraster);
                                r^=sd->ladenwert(iteratorschritte);
                                r^=sd->ladenwert(anzahlnetz);
                                for(unsigned int i=0;i<anzahlnetz;i++) r^=sd->ladenassoziation();
                                sd->ladenwert(iterator);
                                sd->ladenwert(winkel);
                                sd->ladenwert(winkelalt);
                                _vektor3<_tg> h;
                                sd->ladenwert(h);kurve.ort(0,h);
                                sd->ladenwert(h);kurve.ort(1,h);
                                sd->ladenwert(h);kurve.vektor(0,h);
                                sd->ladenwert(h);kurve.vektor(1,h);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteindrehkreuz::speichern(_speicherbardynamisch<_corundsteindrehkreuz>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(normale);
                                sd->speichernwert(nord);
                                sd->speichernwert(winkelraster);
                                sd->speichernwert(iteratorschritte);
                                sd->speichernwert(tuer.anzahl());
                                _listenknoten<_netz>*nit;
                                if(tuer.anfang(nit))do{
                                 saveassociationargument(sd->datei(),sd,nit->objekt());
                                }while(tuer.naechstes(nit));
                                sd->speichernwert(iterator);
                                sd->speichernwert(winkel);
                                sd->speichernwert(winkelalt);
                                sd->speichernwert(kurve.ort(0));
                                sd->speichernwert(kurve.ort(1));
                                sd->speichernwert(kurve.vektor(0));
                                sd->speichernwert(kurve.vektor(1));
                                sd->speichernendeblock();
};                                
char _corundsteindrehkreuz::assoziieren(_speicherbardynamisch<_corundsteindrehkreuz>*sd){
                                sd->assoziierenverschachtelung();
                                tuer.aushaengen();
                                unsigned int i;
                                for(i=0;i<anzahlnetz;i++){
                                 _netz*n=0;
                                 associateassociationargument(sd->datei(),sd->assoziation(),n);
                                 if(n){
                                  tuer.einhaengen(n);
                                 };
                                };
                                return(1);
};
void _corundsteindrehkreuz::netzwahl(_netz*n,int i){
                                tuer.einhaengenunredundant(n);
                                if(hauptfenster){
                                 hauptfenster->zeichnen();
                                };
                                
};
void _corundsteindrehkreuz::beiknopftuersetzen(_guiereignisdaten*){
                                if(hauptfenster){
                                 hauptfenster->dnetzwahl->corundstein(this);
                                 hauptfenster->dnetzwahl->index(0);
                                 hauptfenster->dnetzwahl->zeigen();
                                };
};
void _corundsteindrehkreuz::beiknopftuerloeschen(_guiereignisdaten*){
                                _listenknoten<_netz>*nit;
                                if(tuer.anfang(nit)){
                                 nit=nit->vorheriges();
                                 delete nit;
                                 if(hauptfenster){
                                  hauptfenster->zeichnen();
                                 };
                                };
};

void _corundsteindrehkreuz::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Drehkreuz");
                                d->sektion(L"Corundstein Drehkreuz")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengenknopf<_corundsteindrehkreuz>(L"Corundstein Drehkreuz",L"Drehflügel",L"setzen",this,&_corundsteindrehkreuz::beiknopftuersetzen);
                                d->einhaengenknopf<_corundsteindrehkreuz>(L"Corundstein Drehkreuz",L"Drehflügel",L"löschen",this,&_corundsteindrehkreuz::beiknopftuerloeschen);
                                d->einhaengen(L"Corundstein Drehkreuz",L"Normale",normale);
                                d->einhaengen(L"Corundstein Drehkreuz",L"Vektor Nord",nord);
                                d->einhaengen(L"Corundstein Drehkreuz",L"Winkelraster",winkelraster);
                                d->einhaengen(L"Corundstein Drehkreuz",L"Animationsschritte [uint]",iteratorschritte);

};
void _corundsteindrehkreuz::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Drehkreuz",L"Normale",normale);
                                d->auslesen(L"Corundstein Drehkreuz",L"Vektor Nord",nord);
                                d->auslesen(L"Corundstein Drehkreuz",L"Winkelraster",winkelraster);
                                d->auslesen(L"Corundstein Drehkreuz",L"Animationsschritte [uint]",iteratorschritte);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E I N B A H N
//******************************************************************************************************************************************************************************************************
_corundsteineinbahn::_corundsteineinbahn(_corundwelt*ow):_corundstein(ow){
                                richtung=0;
};
_corundsteineinbahn::_corundsteineinbahn(_corundwelt*ow,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz):_corundstein(ow,x,y,z,wx,wy,wz,ow->textur[75],true){
                                richtung=0;
                                nachbereitenkonstruktion();
};
_corundsteineinbahn::~_corundsteineinbahn(){
};
void _corundsteineinbahn::nachbereitenkonstruktion(){
};
void _corundsteineinbahn::initialisieren(){
                                _polygon*pit;
                                _polygon*pd;
                                _netz::nurkollisionskopplung(false);
                                _netz::textur(welt->textur[59]);
                                
                                _netz::anfang(pd);
                                pd=pd->naechstes();
                                _netz::maskiert(true);
                                if (richtung==0){//ost
                                 pd->textur(welt->textur[55]);
                                 _netz::anfang(pit);
                                 for(int i=0;i<2;i++) pit=pit->naechstes();
                                 pit->textur(welt->textur[84]);
                                 pit->nurkollisionskopplung(true);
                                };
                                if (richtung==1){//sued
                                 pd->textur(welt->textur[56]);
                                 _netz::anfang(pit);
                                 for(int i=0;i<5;i++) pit=pit->naechstes();
                                 pit->textur(welt->textur[84]);
                                 pit->nurkollisionskopplung(true);
                                }; 
                                if (richtung==2){//west
                                 pd->textur(welt->textur[57]);
                                 _netz::anfang(pit);
                                 for(int i=0;i<3;i++) pit=pit->naechstes();
                                 pit->textur(welt->textur[84]);
                                 pit->nurkollisionskopplung(true);
                                }; 
                                if (richtung==3){//nord
                                 pd->textur(welt->textur[58]);
                                 _netz::anfang(pit);
                                 for(int i=0;i<4;i++) pit=pit->naechstes();
                                 pit->textur(welt->textur[84]);
                                 pit->nurkollisionskopplung(true);
                                }; 
};
void _corundsteineinbahn::kollision(_kollidierbar*k,_polygon*){
};
void _corundsteineinbahn::animieren(){
};
void _corundsteineinbahn::schalten(){
                                richtung++;
                                if(richtung>3) richtung=0;
                                initialisieren();
};
char _corundsteineinbahn::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundsteineinbahn>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(richtung);
                                sd->ladenende();
                                return(r);
};                                
void _corundsteineinbahn::speichern(_speicherbardynamisch<_corundsteineinbahn>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(richtung);
                                sd->speichernendeblock();
};                                
char _corundsteineinbahn::assoziieren(_speicherbardynamisch<_corundsteineinbahn>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundsteineinbahn::einhaengendialog(_dynamischerdialog*d){
                                _corundstein::einhaengendialog(d);
                                d->addierensektion(L"Corundstein Einbahn");
                                d->sektion(L"Corundstein Einbahn")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundstein Einbahn",L"Richtung 0=Ost,1=Süd,2=West,3=Nord",richtung);
};
void _corundsteineinbahn::auslesendialog(_dynamischerdialog*d){
                                _corundstein::auslesendialog(d);
                                d->auslesen(L"Corundstein Einbahn",L"Richtung 0=Ost,1=Süd,2=West,3=Nord",richtung);
                                initialisieren();
};
