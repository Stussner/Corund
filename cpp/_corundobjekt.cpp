//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundobjekt.cpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include "../hpp/_corundobjekt.hpp"
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T 
//******************************************************************************************************************************************************************************************************
_corundobjekt::_corundobjekt(_corundwelt*w,const _vektor3<_tg>&o):_listenknotenbasis<_corundobjekt>(w),_corundschaltkopplung(w){
                                welt=w;             
                                ton=0;
                                ort=o;
                                hauptfenster=0;
                                markierung=0;
                                iminventar=false;
                               // initialisieren(); 
                                                                       
};
_corundobjekt::~_corundobjekt(){
                                if(ton) delete ton;
};
void _corundobjekt::nachbereitenkonstruktion(){
                                _geometriequader*gb;
                                gb=new _geometriequader(welt->welt,ort,
                                0.2,0.8,0.2,welt->textur[0]);
                                gb->texturkoordinatenlaenge(2,8,2);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::dynamisch(true);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(50);
                                _netz::nurkollisionskopplung(true);
                                delete gb;  
                                
                                if(iminventar) {
                                 aufsammeln();
                                };

};
void _corundobjekt::aufsammeln(){
                                if(welt->corundinventar) {
                                 if(welt->corundinventar->links==false){
                                  iminventar=true;
                                  _listenknotenbasis<_corundobjekt>::aushaengen();
                                  _listenknotenbasis<_netz>::aushaengen();
                                  _netz::_liste<_partition::_sektor>::aushaengen();
                                  _netz::loeschenschatten();  
                                  _polygon*pit;
                                  if(_listebasis<_polygon>::anfang(pit))do{
                                   pit->_liste<_partition::_sektor>::aushaengen();
                                   pit->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                  }while(_listebasis<_polygon>::naechstes(pit));
                                  welt->corundinventar->text="Sie haben ein Objekt aufgesammelt.";
                                  welt->corundinventar->einhaengenobjekt(this);
                                 };
                                };
};
void _corundobjekt::ablegen(const _vektor3<_tg>&o){
                                _partition::_zone*zit;
                                _polygon*pit;
                                _tg x0,x1,y0,y1,z0,z1;
                                _vektor3<_tg> m;
                                _listenknoten<_partition::_sektor>*lnsit;
                                _listenknoten<_partition::_sektor>*lnsii;
                                _licht<_tg,_to>*lit;
                                //--------------------------- neue position bestimmen -----------
                                m=_netz::mitte();
                                m=o-m;
                                _netz::verschiebenvertex(m);
                                ort+=m;
                                //-------------------------- strukturen aktualisieren -------------
                                _listenknotenbasis<_corundobjekt>::aushaengen();
                                _listenknotenbasis<_corundobjekt>::einhaengen(welt);//->_listebasis<_corundobjekt>::einhaengen(this);
                                _listenknotenbasis<_netz>::einhaengen(welt->welt);//->_listebasis<_netz>::einhaengen(this);
                                if(welt->welt->anfang(zit))do{
                                 zit->einfuegenintern(this);
                                 _netz::erzeugenvertexlicht(zit);
                                }while(welt->welt->naechstes(zit)); 
                                if(_listebasis<_polygon>::anfang(pit))do{
                                 pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                 if(pit->_liste<_partition::_sektor>::anfang(lnsit))do{
                                  
                                  lnsit->objekt()->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                  
                                  if(lnsit->objekt()->anfang(lit))do{
                                   _netz::erzeugenschatten(lit,_netz::schattenvolumenlaenge());
                                  // L->schreiben("Schatten wurde erzeugt");
                                  }while(lnsit->objekt()->naechstes(lit));
                                  
                                  if(lnsit->objekt()->sichtbarkeitsektor()->anfang(lnsii))do{
                                   if(lnsii->objekt()->anfang(lit))do{
                                   
                                    _netz::erzeugenschatten(lit,_netz::schattenvolumenlaenge());
                                   // L->schreiben("Schattensichtbar wurde erzeugt");
                                   }while(lnsii->objekt()->naechstes(lit));
                                  }while(lnsit->objekt()->sichtbarkeitsektor()->naechstes(lnsii));
                                  
                                 }while(pit->_liste<_partition::_sektor>::naechstes(lnsit));
                                }while(_listebasis<_polygon>::naechstes(pit));
                                _netz::aktualisierenschatten();     
                                iminventar=false;                             
};
void _corundobjekt::verschiebenvertex(const _vektor3<_tg>v){
                                _netz::verschiebenvertex(v);
                                ort+=v;
};   
void _corundobjekt::initialisieren(){
                                //kollisionskopplung vornehmen
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->::_liste<_kollisionskopplung>::aushaengen();
                                 pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                }while(_netz::naechstes(pit));
                                _partition::_zone*zit;
                                if(welt->welt->anfang(zit))do{
                                 _netz::erzeugenvertexlicht(zit);
                                }while(welt->welt->naechstes(zit));                                 
};  
void _corundobjekt::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*co;
                                co=dynamic_cast<_corundkugel*>(k);
                                if(co){
                                 if(co->spieler){
                                  if(welt->corundinventar){
                                   if(welt->corundinventar->links==false){
                                    if(iminventar==false) aufsammeln();
                                   };
                                  };
                                 };
                                };
};
void _corundobjekt::zeichnen(_grafik*grafik){//nur für editor
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
void _corundobjekt::animieren(){
};
void _corundobjekt::schalten(){
};
char _corundobjekt::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjekt>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(ort);

                                sd->ladenende();
                                return(r);

};
void _corundobjekt::speichern(_speicherbardynamisch<_corundobjekt>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(ort);
                                sd->speichernendeblock();
};
char _corundobjekt::assoziieren(_speicherbardynamisch<_corundobjekt>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjekt::netzwahl(_netz*,int){
};
void _corundobjekt::figurwahl(_corundfigur*,int){
};
void _corundobjekt::knotenwahl(_corundknoten*,int){
};
void _corundobjekt::einhaengendialog(_dynamischerdialog*d){
                                _netz::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt");
};
void _corundobjekt::auslesendialog(_dynamischerdialog*d){
                                _netz::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T E R S A T Z 
//******************************************************************************************************************************************************************************************************
_corundobjektersatz::_corundobjektersatz(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                                                      
};
_corundobjektersatz::~_corundobjektersatz(){
                                
};/*
void _corundobjektersatz::kollision(_kollidierbar*k,_polygon*){
};
*/
void _corundobjektersatz::animieren(){
};
char _corundobjektersatz::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektersatz>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);

                                sd->ladenende();
                                return(r);

};
void _corundobjektersatz::speichern(_speicherbardynamisch<_corundobjektersatz>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    

                                sd->speichernendeblock();
};
char _corundobjektersatz::assoziieren(_speicherbardynamisch<_corundobjektersatz>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektersatz::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Ersatz");
};
void _corundobjektersatz::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H L U E S S E L A 
//******************************************************************************************************************************************************************************************************
_corundobjektschluessela::_corundobjektschluessela(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                schloss=0;
                                verschiebung.setzen(0,0.1,0);
};
_corundobjektschluessela::~_corundobjektschluessela(){
};
void _corundobjektschluessela::nachbereitenkonstruktion(){
                                _geometriezylinder*gb;
                                gb=new _geometriezylinder(welt->welt,ort+verschiebung-_vektor3<_tg>(0.3,0,0),
                                _vektor3<_tg>(0,0,0.03),_vektor3<_tg>(0.6,0,0),_vektor3<_tg>(0,0.03,0),welt->textur[94]);
                                gb->aufloesung(_vektor<unsigned int>(6,1));
                                gb->texturkoordinatenlaenge(1,0.4,1,1);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(1);
                                _netz::nurkollisionskopplung(true);
                                _netz::normaleinterpoliert(true);
                                delete gb;  
                                _geometriequader*gq=new _geometriequader(welt->welt,ort+verschiebung+_vektor3<_tg>(0.1,-0.01,0),_vektor3<_tg>(0.15,0,0),_vektor3<_tg>(0,0.02,0),_vektor3<_tg>(0,0,-0.1),welt->textur[94]);
                                gq->aufloesung(_vektor<unsigned int>(1,1,1));
                                gq->texturkoordinatenlaenge(0.2,0.01,0.1);
                                _netz*nq=gq->erzeugen();
                                nq->subtraktiv(false);  
                                nq->keinbsp(true);  
                                nq->dynamisch(true);   
                                nq->schattenvolumen(true);
                                nq->schattenvolumenlaenge(1);
                                nq->nurkollisionskopplung(true);                                                       
                                nq->lightmapschattierung(false);
                                //nq->skalierenkonisch(ort+verschiebung+_vektor3<_tg>(0.1,-0.01,0),_vektor3<_tg>(0.05,0,0),0.5,0.5);
                                _netz::vereinigen(nq);
                                
                                _geometrietorus*gt=new _geometrietorus(welt->welt,
                                ort+verschiebung+_vektor3<_tg>(-0.4,0,0),
                                _vektor3<_tg>(0.1,0,0),
                                _vektor3<_tg>(0,1,0),
                                _vektor3<_tg>(0,0,0.1),
                                0.030,
                                0.030,
                                welt->textur[94]);
                                gt->aufloesung(_vektor<unsigned int>(6,10));
                                gt->texturkoordinatenlaenge(1,1);
                                _netz*nt=gt->erzeugen();
                                nt->subtraktiv(false);  
                                nt->keinbsp(true);   
                                nt->dynamisch(true); 
                                nt->schattenvolumen(true);
                                nt->schattenvolumenlaenge(1);
                                nt->nurkollisionskopplung(true);                                                       
                                nt->lightmapschattierung(false);
                                nt->normaleinterpoliert(true);
                                //nq->skalierenkonisch(ort+verschiebung+_vektor3<_tg>(0.1,-0.01,0),_vektor3<_tg>(0.05,0,0),0.5,0.5);
                                _netz::vereinigen(nt);                                
                                
                                if(iminventar) {
                                 aufsammeln();
                                };
};
void _corundobjektschluessela::animieren(){
};/*
void _corundobjektschluessela::ablegen(const _vektor3<_tg>&o){
                                _partition::_zone*zit;
                                _partition::_sektor*sit;
                                _polygon*pit;
                                _tg x0,x1,y0,y1,z0,z1;
                                _vektor3<_tg> m;
                                //--------------------------- neue position bestimmen -----------
                                m=_netz::mitte();
                                m=o-m;
                                _netz::verschiebenvertex(m+verschiebung);
                                ort+=m;
                                //-------------------------- strukturen aktualisieren -------------
                                _listenknotenbasis<_corundobjekt>::aushaengen();
                                welt->_listebasis<_corundobjekt>::einhaengen(this);
                                welt->welt->_listebasis<_netz>::einhaengen(this);
                                if(welt->welt->anfang(zit))do{
                                 zit->einfuegenintern(this);
                                 if(_listebasis<_polygon>::anfang(pit))do{
                                  pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                  if(zit->anfang(sit))do{
                                   sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                  }while(zit->naechstes(sit));
                                 }while(_listebasis<_polygon>::naechstes(pit));
                                 _netz::erzeugenvertexlicht(zit);
                                }while(welt->welt->naechstes(zit)); 
                                _netz::aktualisierenschatten();     
                                iminventar=false;                             
};*/
char _corundobjektschluessela::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektschluessela>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(schloss);
                                sd->ladenende();
                                return(r);
};
void _corundobjektschluessela::speichern(_speicherbardynamisch<_corundobjektschluessela>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(schloss);
                                sd->speichernendeblock();
};
char _corundobjektschluessela::assoziieren(_speicherbardynamisch<_corundobjektschluessela>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektschluessela::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Schlüssel A");
                                d->sektion(L"Netz")->offen(false);
                                d->sektion(L"Corundobjekt Schlüssel A")->offen(true);
                                d->einhaengen(L"Corundobjekt Schlüssel A",L"Schlossindex [unit]",schloss);
};
void _corundobjektschluessela::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Schlüssel A",L"Schlossindex [unit]",schloss);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B O M B E
//******************************************************************************************************************************************************************************************************
_corundobjektbombe::_corundobjektbombe(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                gezuendet=false;
                                wurfmodus=false;
                                tauchen=false;
                                brenndauer=400;
                                staerke=10;
                                radius=5;
                                zaehler=0;
                                pqdetonation=new _partikelquellesprite(w->welt,0,w->welt,w->pzeit,o,_vektor3<_tg>(0,0.2,0),150,
                                w->textur[15]);
                                pqdetonation->name("pqdetonation");
                                pqdetonation->aktiv(false);
                                pqdetonation->groesse(0.3);
                                pqdetonation->generationsrate(200);
                                pqdetonation->generationsratetoleranz(0.5);
                                pqdetonation->groessetoleranz(0.9);
                                pqdetonation->vektortoleranz(0.6);
                                pqdetonation->rotation(0);
                                pqdetonation->rotationtoleranz(0);
                                pqdetonation->lebensdauerpartikeltoleranz(0.95);                                 

                                pqzuendschnurr=new _partikelquellesprite(w->welt,0,w->welt,w->pzeit,o+_vektor3<_tg>(0,0.9,0),_vektor3<_tg>(0,0.3,0),50,
                                w->textur[15]);
                                pqzuendschnurr->name("pqzuendschnurr");
                                pqzuendschnurr->aktiv(false);
                                pqzuendschnurr->groesse(0.1);
                                pqzuendschnurr->generationsrate(2);
                                pqzuendschnurr->generationsratetoleranz(0.5);
                                pqzuendschnurr->groessetoleranz(0.9);
                                pqzuendschnurr->vektortoleranz(0.1);
                                pqzuendschnurr->rotation(5);
                                pqzuendschnurr->rotationtoleranz(0.9);
                                pqzuendschnurr->lebensdauerpartikeltoleranz(0.55);      
                                
                                ton=new _corundton(w,w->tonverwaltung.ton(5),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));   
                                kk=new _kollidierbarkugel(this,w->welt,0,0,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0),0.1);                        
                                kk->aktivitaet(false);

                                
};
_corundobjektbombe::~_corundobjektbombe(){
                                delete kk;
                                delete pqdetonation;
                                delete pqzuendschnurr;
                                delete ton;
};
void _corundobjektbombe::nachbereitenkonstruktion(){
                                _geometriezylinder*gb;
                                gb=new _geometriezylinder(welt->welt,ort,
                                _vektor3<_tg>(0.1,0,0),_vektor3<_tg>(0,0.6,0),_vektor3<_tg>(0,0,0.1),welt->textur[50]);
                                gb->aufloesung(_vektor<unsigned int>(7,1));
                                gb->texturkoordinatenlaenge(3,1,1,1);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(10);
                                _netz::nurkollisionskopplung(true);
                                delete gb;  
                                
                                if(iminventar) {
                                 aufsammeln();
                                };

};
void _corundobjektbombe::kollision(_kollidierbar*k,_polygon*p){
                                _corundobjekt::kollision(k,p);//standardverhalten (aufsammeln prüfen)
                                _corundsteinflak*csf=dynamic_cast<_corundsteinflak*>(k->kollisionskopplung);
                                L->schreiben("bomde kollidiert");
                                if(csf){
                                 brenndauer=0;
                                 L->schreiben("mit flak");
                                 schalten();
                                };
                                _corundstrahl*csl=dynamic_cast<_corundstrahl*>(k->kollisionskopplung);
                                if(csl){
                                 L->schreiben("mit strahl");
                                 brenndauer=100;
                                 pqzuendschnurr->aktiv(true);
                                 schalten();
                                };
};

void _corundobjektbombe::verschiebenvertex(const _vektor3<_tg>v){
                                _corundobjekt::verschiebenvertex(v);
                                pqdetonation->ort(ort);
                                pqzuendschnurr->ort(ort+_vektor3<_tg>(0,0.9,0));
                                
}; 
void _corundobjektbombe::animieren(){

                                if((wurfmodus)&&(!iminventar)){
                                 kk->aktivitaet(true);                                
                                 //grav und reibung
                                 _tg r=1;
                                 kk->vektor()+=welt->welt->gravitation(kk->ort());
                                 r*=welt->welt->viskositaet();
                                 if(tauchen) r*=0.8;
                                 kk->vektor()*=r;
                                 if(kk->testen()==false){//aufschlag, zünden
                                  zaehler=0;
                                 }else{//bewegung frei
                                  kk->ort(kk->ort()+kk->vektor());
                                  pqdetonation->ort(kk->ort());
                                  pqzuendschnurr->ort(kk->ort()+_vektor3<_tg>(0,0.9,0));  
                                  _netz::verschiebenvertex(kk->vektor());
                                  ort+=kk->vektor();
                                  _tg x0,x1,y0,y1,z0,z1;
                                  _polygon*pit;
                                  if(_netz::anfang(pit))do{
                                   _partition::_zone*zit;
                                   _partition::_sektor*sit;
                                   zit=kk->zone();
                                   pit->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                   pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                   if(zit->anfang(sit))do{
                                    sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                   }while(zit->naechstes(sit));
                                  }while(_netz::naechstes(pit));                                  
                                  _netz::anfang(pit);
                                  if(pit->verwendentexturdynamisch()==false) {
                                   _netz::erzeugenvertexlicht(kk->zone());
                                  };
                                  _netz::aktualisierenschatten();                                  
                                 };
                                 kk->aktivitaet(false);
                                };

                        
                               if(gezuendet) {
                                pqzuendschnurr->aktiv(true);
                                pqzuendschnurr->animieren();
                                if(zaehler>0) zaehler--;
                                if(zaehler==0) {
                                 new _corunddruckwelle(welt,ort,-4,0.7,80);
                                 ton->ort=ort;
                                 ton->vektor.setzen(0,0,0);
                                 ton->abspielen();
                                 pqdetonation->aktiv(true);
                                 pqdetonation->animieren();
                                 _listenknotenbasis<_corundobjekt>::loeschmarkierung(true); 
                                 if(iminventar) {
                                  if(welt->spieler) {
                                   welt->spieler->zerstoeren();
                                   welt->spieler=0;
                                  };
                                 }else{
                                  _corundkugel*kit;
                                  _vektor3<_tg> m;
                                  if(welt->anfang(kit))do{
                                   m=kit->_kollidierbarkugel::ort()-ort;
                                   if(m.laenge()<=radius){
                                    kit->abziehengesundheit(staerke/(1+(m.laenge()*m.laenge())));
                                   };
                                  }while(welt->naechstes(kit));
                                 };
                                };
                               };
                               if(iminventar){
                                _partikel*pait;
                                if(anfang(pait))do{
                                 pait->animieren();
                                }while(naechstes(pait));
                                _listebasis<_partikel>::loeschenmarkiert();
                               };
};
void _corundobjektbombe::schalten(){
                                if(gezuendet==false){
                                 gezuendet=true;
                                 zaehler=brenndauer;
                                 pqdetonation->ort(ort);
                                 pqzuendschnurr->ort(ort); 
                                };
};
void _corundobjektbombe::ablegen(const _vektor3<_tg>&o){
                                _corundobjekt::ablegen(o);
                                pqdetonation->ort(ort);
                                pqdetonation->kollision(true);
                                pqdetonation->listepartikel(welt->welt);                                
                                pqdetonation->spriteliste(welt->welt);
                                pqzuendschnurr->ort(ort+_vektor3<_tg>(0,0.9,0)); 
                                pqzuendschnurr->kollision(true);                               
                                pqzuendschnurr->listepartikel(welt->welt);                                
                                pqzuendschnurr->spriteliste(welt->welt);

                                schalten();                                
};
void _corundobjektbombe::werfen(const _vektor3<_tg>&o,const _vektor3<_tg>&v){
                                _corundobjekt::ablegen(o);
                                pqdetonation->ort(ort);
                                pqdetonation->kollision(true);
                                pqdetonation->listepartikel(welt->welt);                                
                                pqdetonation->spriteliste(welt->welt);
                                pqzuendschnurr->ort(ort+_vektor3<_tg>(0,0.9,0)); 
                                pqzuendschnurr->kollision(true);                               
                                pqzuendschnurr->listepartikel(welt->welt);                                
                                pqzuendschnurr->spriteliste(welt->welt);
                                kk->ort(ort);
                                kk->vektor(v);
                                wurfmodus=true;
                                gezuendet=true;
                                zaehler=brenndauer;
                                pqdetonation->ort(ort);
                                pqzuendschnurr->ort(ort); 
};
void _corundobjektbombe::aufsammeln(){
                                _corundobjekt::aufsammeln();
                                pqdetonation->kollision(false); 
                                pqdetonation->listepartikel(this);
                                pqdetonation->spriteliste(this);
                                pqzuendschnurr->kollision(false);                               
                                pqzuendschnurr->listepartikel(this);
                                pqzuendschnurr->spriteliste(this);
};
char _corundobjektbombe::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektbombe>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(gezuendet);
                                r^=sd->ladenwert(brenndauer);   
                                r^=sd->ladenwert(staerke);   
                                r^=sd->ladenwert(radius);   
                                r^=sd->ladenwert(wurfmodus);
                                r^=sd->ladenwert(tauchen);
                                sd->ladenende();
                                return(r);

};
void _corundobjektbombe::speichern(_speicherbardynamisch<_corundobjektbombe>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung(); 
                                sd->speichernwert(gezuendet);
                                sd->speichernwert(brenndauer);   
                                sd->speichernwert(staerke);   
                                sd->speichernwert(radius);  
                                sd->speichernwert(wurfmodus);
                                sd->speichernwert(tauchen);

                                sd->speichernendeblock();
};
char _corundobjektbombe::assoziieren(_speicherbardynamisch<_corundobjektbombe>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektbombe::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Bombe");
                                d->einhaengen(L"Corundobjekt Bombe",L"Gezündet",gezuendet);
                                d->einhaengen(L"Corundobjekt Bombe",L"Brenndauer [f]",brenndauer);
                                d->einhaengen(L"Corundobjekt Bombe",L"Stärke",staerke);
                                d->einhaengen(L"Corundobjekt Bombe",L"Radius",radius);
                                
};
void _corundobjektbombe::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Bombe",L"Gezündet",gezuendet);
                                d->auslesen(L"Corundobjekt Bombe",L"Brenndauer [f]",brenndauer);
                                d->auslesen(L"Corundobjekt Bombe",L"Stärke",staerke);
                                d->auslesen(L"Corundobjekt Bombe",L"Radius",radius);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T D Y N A M I T 
//******************************************************************************************************************************************************************************************************
_corundobjektdynamit::_corundobjektdynamit(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                gezuendet=false;
                                brenndauer=400;
                                staerke=10;
                                radius=5;
                                zaehler=0;
                                pqdetonation=new _partikelquellesprite(w->welt,0,w->welt,w->pzeit,o,_vektor3<_tg>(0,0.2,0),150,
                                w->textur[15]);
                                pqdetonation->name("pqdetonation");
                                pqdetonation->aktiv(false);
                                pqdetonation->groesse(0.3);
                                pqdetonation->generationsrate(200);
                                pqdetonation->generationsratetoleranz(0.5);
                                pqdetonation->groessetoleranz(0.9);
                                pqdetonation->vektortoleranz(0.6);
                                pqdetonation->rotation(0);
                                pqdetonation->rotationtoleranz(0);
                                pqdetonation->lebensdauerpartikeltoleranz(0.95);                                 

                                pqzuendschnurr=new _partikelquellesprite(w->welt,0,w->welt,w->pzeit,o+_vektor3<_tg>(0,0.9,0),_vektor3<_tg>(0,0.3,0),50,
                                w->textur[15]);
                                pqzuendschnurr->name("pqzuendschnurr");
                                pqzuendschnurr->aktiv(false);
                                pqzuendschnurr->groesse(0.1);
                                pqzuendschnurr->generationsrate(2);
                                pqzuendschnurr->generationsratetoleranz(0.5);
                                pqzuendschnurr->groessetoleranz(0.9);
                                pqzuendschnurr->vektortoleranz(0.1);
                                pqzuendschnurr->rotation(5);
                                pqzuendschnurr->rotationtoleranz(0.9);
                                pqzuendschnurr->lebensdauerpartikeltoleranz(0.55);      
                                
                                ton=new _corundton(w,w->tonverwaltung.ton(5),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));                           

                                
};
_corundobjektdynamit::~_corundobjektdynamit(){
                                delete pqdetonation;
                                delete pqzuendschnurr;
                                delete ton;
};
void _corundobjektdynamit::nachbereitenkonstruktion(){
                                _geometriezylinder*gb;
                                gb=new _geometriezylinder(welt->welt,ort,
                                _vektor3<_tg>(0.05,0,0),_vektor3<_tg>(0,0.5,0),_vektor3<_tg>(0,0,0.05),welt->textur[48]);
                                gb->aufloesung(_vektor<unsigned int>(7,1));
                                gb->texturkoordinatenlaenge(3,1,1,1);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(10);
                                _netz::nurkollisionskopplung(true);
                                delete gb;  
                                
                                if(iminventar) {
                                 aufsammeln();
                                };

};
void _corundobjektdynamit::kollision(_kollidierbar*k,_polygon*p){
                                _corundobjekt::kollision(k,p);//standardverhalten (aufsammeln prüfen)
                                _corundsteinflak*csf=dynamic_cast<_corundsteinflak*>(k->kollisionskopplung);
                                if(csf){
                                 brenndauer=0;
                                 schalten();
                                };
                                _corundstrahl*csl=dynamic_cast<_corundstrahl*>(k->kollisionskopplung);
                                if(csl){
                                 brenndauer=100;
                                 pqzuendschnurr->aktiv(true);
                                 schalten();
                                };
};

void _corundobjektdynamit::verschiebenvertex(const _vektor3<_tg>v){
                                _corundobjekt::verschiebenvertex(v);
                                pqdetonation->ort(ort);
                                pqzuendschnurr->ort(ort+_vektor3<_tg>(0,0.9,0));
                                
}; 
void _corundobjektdynamit::animieren(){
                               if(gezuendet) {
                                pqzuendschnurr->aktiv(true);
                                pqzuendschnurr->animieren();
                                if(zaehler>0) zaehler--;
                                if(zaehler==0) {
                                 new _corunddruckwelle(welt,ort,-4,0.7,80);
                                 ton->ort=ort;
                                 ton->vektor.setzen(0,0,0);
                                 ton->abspielen();
                                 pqdetonation->aktiv(true);
                                 pqdetonation->animieren();
                                 _listenknotenbasis<_corundobjekt>::loeschmarkierung(true); 
                                 if(iminventar) {
                                  if(welt->spieler) {
                                   welt->spieler->zerstoeren();
                                   welt->spieler=0;
                                  };
                                 }else{
                                  _corundkugel*kit;
                                  _vektor3<_tg> m;
                                  if(welt->anfang(kit))do{
                                   m=kit->_kollidierbarkugel::ort()-ort;
                                   if(m.laenge()<=radius){
                                    kit->abziehengesundheit(staerke/(1+(m.laenge()*m.laenge())));
                                   };
                                  }while(welt->naechstes(kit));
                                 };
                                };
                               };
                               if(iminventar){
                                _partikel*pait;
                                if(anfang(pait))do{
                                 pait->animieren();
                                }while(naechstes(pait));
                                _listebasis<_partikel>::loeschenmarkiert();
                               };
};
void _corundobjektdynamit::schalten(){
                                if(gezuendet==false){
                                 gezuendet=true;
                                 zaehler=brenndauer;
                                 pqdetonation->ort(ort);
                                 pqzuendschnurr->ort(ort); 
                                };
};
void _corundobjektdynamit::ablegen(const _vektor3<_tg>&o){
                                _corundobjekt::ablegen(o);
                                pqdetonation->ort(ort);
                                pqdetonation->kollision(true);
                                pqdetonation->listepartikel(welt->welt);                                
                                pqdetonation->spriteliste(welt->welt);
                                pqzuendschnurr->ort(ort); 
                                pqzuendschnurr->kollision(true);                               
                                pqzuendschnurr->listepartikel(welt->welt);                                
                                pqzuendschnurr->spriteliste(welt->welt);

                                schalten();                                
};
void _corundobjektdynamit::aufsammeln(){
                                _corundobjekt::aufsammeln();
                                pqdetonation->kollision(false); 
                                pqdetonation->listepartikel(this);
                                pqdetonation->spriteliste(this);
                                pqzuendschnurr->kollision(false);                               
                                pqzuendschnurr->listepartikel(this);
                                pqzuendschnurr->spriteliste(this);
};
char _corundobjektdynamit::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektdynamit>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(gezuendet);
                                r^=sd->ladenwert(brenndauer);   
                                r^=sd->ladenwert(staerke);   
                                r^=sd->ladenwert(radius);   
                                sd->ladenende();
                                return(r);

};
void _corundobjektdynamit::speichern(_speicherbardynamisch<_corundobjektdynamit>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung(); 
                                sd->speichernwert(gezuendet);
                                sd->speichernwert(brenndauer);   
                                sd->speichernwert(staerke);   
                                sd->speichernwert(radius);   

                                sd->speichernendeblock();
};
char _corundobjektdynamit::assoziieren(_speicherbardynamisch<_corundobjektdynamit>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektdynamit::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Dynamit");
                                d->einhaengen(L"Corundobjekt Dynamit",L"Gezündet",gezuendet);
                                d->einhaengen(L"Corundobjekt Dynamit",L"Brenndauer [f]",brenndauer);
                                d->einhaengen(L"Corundobjekt Dynamit",L"Stärke",staerke);
                                d->einhaengen(L"Corundobjekt Dynamit",L"Radius",radius);
                                
};
void _corundobjektdynamit::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Dynamit",L"Gezündet",gezuendet);
                                d->auslesen(L"Corundobjekt Dynamit",L"Brenndauer [f]",brenndauer);
                                d->auslesen(L"Corundobjekt Dynamit",L"Stärke",staerke);
                                d->auslesen(L"Corundobjekt Dynamit",L"Radius",radius);
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T M I N E
//******************************************************************************************************************************************************************************************************
_corundobjektmine::_corundobjektmine(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                gezuendet=false;
                                sensorverzoegerung=50;
                                sensordistanz=2;
                                staerke=10;
                                radius=5;
                                zaehler=0;
                                pqdetonation=new _partikelquellesprite(w->welt,0,w->welt,w->pzeit,o,_vektor3<_tg>(0,0.2,0),150,
                                w->textur[15]);
                                pqdetonation->name("pqdetonation");
                                pqdetonation->aktiv(false);
                                pqdetonation->groesse(0.3);
                                pqdetonation->generationsrate(200);
                                pqdetonation->generationsratetoleranz(0.5);
                                pqdetonation->groessetoleranz(0.9);
                                pqdetonation->vektortoleranz(0.6);
                                pqdetonation->rotation(0);
                                pqdetonation->rotationtoleranz(0);
                                pqdetonation->lebensdauerpartikeltoleranz(0.95);                                 
                                ton=new _corundton(w,w->tonverwaltung.ton(5),_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0));   
                                lampe=0;
                                lampeanim=0;
                                                        
};
_corundobjektmine::~_corundobjektmine(){
                                delete pqdetonation;
                                if(lampe) delete lampe;
                                delete ton;
};
void _corundobjektmine::anlegenlampe(){
                                if(lampe) delete lampe;
                                lampe=new _sprite(welt->welt,welt->welt,ort+_vektor3<_tg>(0,0.11,0),_vektor3<_tg>(0.2,0,0),_vektor3<_tg>(0,0.2,0),welt->textur[16]);
                                lampe->farbe(_vektor4<_to>(1,0.6,0,1));
};
void _corundobjektmine::nachbereitenkonstruktion(){
                                _geometriezylinder*gb;
                                gb=new _geometriezylinder(welt->welt,ort,
                                _vektor3<_tg>(0.2,0,0),_vektor3<_tg>(0,0.1,0),_vektor3<_tg>(0,0,0.2),welt->textur[49]);
                                gb->aufloesung(_vektor<unsigned int>(14,1));
                                gb->texturkoordinatenlaenge(3,1,0.5,0.5);
                                gb->texturkoodinatenverschiebung(0,0,0.5,0.5);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(10);
                                _netz::nurkollisionskopplung(true);
                                delete gb;  
                                anlegenlampe();
                                
                                if(iminventar) {
                                 aufsammeln();
                                };

};
void _corundobjektmine::kollision(_kollidierbar*k,_polygon*p){
                                _corundobjekt::kollision(k,p);//standardverhalten (aufsammeln prüfen)
                                _corundsteinflak*csf=dynamic_cast<_corundsteinflak*>(k->kollisionskopplung);
                                if(csf){
                                 schalten();
                                };
                                _corundstrahl*csl=dynamic_cast<_corundstrahl*>(k->kollisionskopplung);
                                if(csl){
                                 schalten();
                                };
};
void _corundobjektmine::verschiebenvertex(const _vektor3<_tg>v){
                                _corundobjekt::verschiebenvertex(v);
                                pqdetonation->ort(ort);
}; 
void _corundobjektmine::animieren(){
                               if(gezuendet) {
                                
                                if(lampe){
                                 _vektor4<_to> c(1,0.6,0,1);
                                 c*=fabs(sin(lampeanim*_ph));
                                 c.setzenkomponente(3,1);                                 
                                 lampe->farbe(c);
                                 lampeanim+=10;
                                 while(lampeanim>360) lampeanim-=360;
                                };
                                
                                _corundkugel*kit;
                                _vektor3<_tg> d;
                                bool sprengen=false;
                                
                                
                                if(zaehler>0) zaehler--;
                                if(zaehler==0){
                                 if(welt->anfang(kit))do{
                                  d=ort-kit->_kollidierbarkugel::ort();
                                  if(d.laenge()<=sensordistanz) sprengen=true;
                                 }while(welt->naechstes(kit));
                                };
                                
                                if(sprengen){
                                 new _corunddruckwelle(welt,ort,-4,0.7,80);
                                 ton->ort=ort;
                                 ton->vektor.setzen(0,0,0);
                                 ton->abspielen();
                                 pqdetonation->aktiv(true);
                                 pqdetonation->animieren();
                                 _listenknotenbasis<_corundobjekt>::loeschmarkierung(true); 
                                 if(iminventar) {
                                  if(welt->spieler) {
                                   welt->spieler->zerstoeren();
                                   welt->spieler=0;
                                  };
                                 }else{
                                  _corundkugel*kit;
                                  _vektor3<_tg> m;
                                  if(welt->anfang(kit))do{
                                   m=kit->_kollidierbarkugel::ort()-ort;
                                   if(m.laenge()<=radius){
                                    kit->abziehengesundheit(staerke/(1+(m.laenge()*m.laenge())));
                                   };
                                  }while(welt->naechstes(kit));
                                 };
                                };
                               };


                               /*if(iminventar){
                                _partikel*pait;
                                if(anfang(pait))do{
                                 pait->animieren();
                                }while(naechstes(pait));
                                _listebasis<_partikel>::loeschenmarkiert();
                               };*/
};
void _corundobjektmine::schalten(){
                                if(gezuendet==false){
                                 gezuendet=true;
                                 zaehler=sensorverzoegerung;
                                 pqdetonation->ort(ort);
                                };
};
void _corundobjektmine::ablegen(const _vektor3<_tg>&o){
                                _corundobjekt::ablegen(o);
                                pqdetonation->ort(ort);
                                if(lampe) {
                                 lampe->_listenknotenbasis<_sprite>::aushaengen();
                                 lampe->_listenknotenbasis<_sprite>::einhaengen(welt->welt);
                                 lampe->ort(ort+_vektor3<_tg>(0,0.11,0));
                                };

                                pqdetonation->kollision(true);
                                pqdetonation->listepartikel(welt->welt);                                
                                pqdetonation->spriteliste(welt->welt);
                                schalten();                                
};
void _corundobjektmine::aufsammeln(){
                                _corundobjekt::aufsammeln();
                                lampe->ort(ort+_vektor3<_tg>(0,0.11,0));
                                if(lampe) {
                                 lampe->_listenknotenbasis<_sprite>::aushaengen();
                                 lampe->_listenknotenbasis<_sprite>::einhaengen(this);
                                };
                                pqdetonation->kollision(false); 
                                pqdetonation->listepartikel(this);
                                pqdetonation->spriteliste(this);
};
char _corundobjektmine::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektmine>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(gezuendet);
                                r^=sd->ladenwert(sensordistanz);   
                                r^=sd->ladenwert(sensorverzoegerung);   
                                r^=sd->ladenwert(staerke);   
                                r^=sd->ladenwert(radius);   
                                sd->ladenende();
                                return(r);

};
void _corundobjektmine::speichern(_speicherbardynamisch<_corundobjektmine>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung(); 
                                sd->speichernwert(gezuendet);
                                sd->speichernwert(sensordistanz);
                                sd->speichernwert(sensorverzoegerung);
                                sd->speichernwert(staerke);   
                                sd->speichernwert(radius);   
                                sd->speichernendeblock();
};
char _corundobjektmine::assoziieren(_speicherbardynamisch<_corundobjektmine>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektmine::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Mine");
                                d->einhaengen(L"Corundobjekt Mine",L"Gezündet",gezuendet);
                                d->einhaengen(L"Corundobjekt Mine",L"Sensordistanz",sensordistanz);
                                d->einhaengen(L"Corundobjekt Mine",L"Sensorverzoegerung [f]",sensorverzoegerung);
                                d->einhaengen(L"Corundobjekt Mine",L"Stärke",staerke);
                                d->einhaengen(L"Corundobjekt Mine",L"Radius",radius);
                                
};
void _corundobjektmine::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Mine",L"Gezündet",gezuendet);
                                d->auslesen(L"Corundobjekt Mine",L"Sensordistanz",sensordistanz);
                                d->auslesen(L"Corundobjekt Mine",L"Sensorverzoegerung [f]",sensorverzoegerung);
                                d->auslesen(L"Corundobjekt Mine",L"Stärke",staerke);
                                d->auslesen(L"Corundobjekt Mine",L"Radius",radius);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S T E I N P I L L E
//******************************************************************************************************************************************************************************************************
_corundobjektsteinpille::_corundobjektsteinpille(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektsteinpille::~_corundobjektsteinpille(){
};
void _corundobjektsteinpille::animieren(){
};
char _corundobjektsteinpille::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektsteinpille>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektsteinpille::speichern(_speicherbardynamisch<_corundobjektsteinpille>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektsteinpille::assoziieren(_speicherbardynamisch<_corundobjektsteinpille>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektsteinpille::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Steinpille");
};
void _corundobjektsteinpille::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T A L K O H O L
//******************************************************************************************************************************************************************************************************
_corundobjektalkohol::_corundobjektalkohol(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                menge=0.01;
};
_corundobjektalkohol::~_corundobjektalkohol(){
};
void _corundobjektalkohol::animieren(){
};
void _corundobjektalkohol::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*ck;
                                ck=dynamic_cast<_corundkugel*>(k);
                                if(ck){
                                 _listenknotenbasis<_corundobjekt>::loeschmarkierung(true);
                                 ck->chaotischervektor=true;
                                 ck->chaotischerfaktor=menge;
                                };
};

char _corundobjektalkohol::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektalkohol>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(menge);
                                sd->ladenende();
                                return(r);
};
void _corundobjektalkohol::speichern(_speicherbardynamisch<_corundobjektalkohol>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(menge);
                                sd->speichernendeblock();
};
char _corundobjektalkohol::assoziieren(_speicherbardynamisch<_corundobjektalkohol>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektalkohol::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Alkohol");
                                d->sektion(L"Corundobjekt Alkohol")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundobjekt Alkohol",L"Menge",menge);
                                
};
void _corundobjektalkohol::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Alkohol",L"Menge",menge);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B U N G E E S E I L 
//******************************************************************************************************************************************************************************************************
_corundobjektbungeeseil::_corundobjektbungeeseil(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                staerke=0.01;
                                farbe.setzen(1,0.3,0.2,0.9);
};
_corundobjektbungeeseil::~_corundobjektbungeeseil(){
};
void _corundobjektbungeeseil::nachbereitenkonstruktion(){
                                _geometriequader*gb;
                                gb=new _geometriequader(welt->welt,ort,
                                0.5,0.1,0.5,welt->textur[51]);
                                gb->texturkoordinatenlaenge(1,1,1);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::maskiert(true);
                                _netz::transparenz(false);
                                _netz::farbeverbinder(_vektor4<_to>(1,1,1,1));
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(false);
                                _netz::nurkollisionskopplung(true);
                                _polygon*pit;
                                int i=0;
                                if(_netz::anfang(pit))do{
                                 if(i!=1) pit->zeichnenflaeche(false);
                                 i++;
                                }while(_netz::naechstes(pit));
                                delete gb;  
                                
                                if(iminventar) {
                                 aufsammeln();
                                };

};
void _corundobjektbungeeseil::initialisieren(){
                                //kollisionskopplung vornehmen
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->::_liste<_kollisionskopplung>::aushaengen();
                                 pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                }while(_netz::naechstes(pit));
                               
};  
void _corundobjektbungeeseil::animieren(){
};
void _corundobjektbungeeseil::ablegen(const _vektor3<_tg>&o){
                                _listenknotenbasis<_corundobjekt>::aushaengen();
                                _listenknotenbasis<_corundobjekt>::einhaengen(welt);//->_listebasis<_corundobjekt>::einhaengen(this);
                                _listenknotenbasis<_corundobjekt>::loeschmarkierung(true);
                                if(welt->spieler) new _corundgummiband(welt->spieler,welt->spieler->_kollidierbarkugel::ort()-_vektor3<_tg>(0,welt->spieler->_kollidierbarkugel::radius()-0.0001,0),farbe,staerke);
};
char _corundobjektbungeeseil::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektbungeeseil>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(staerke);
                                r^=sd->ladenwert(farbe);
                                sd->ladenende();
                                return(r);
};
void _corundobjektbungeeseil::speichern(_speicherbardynamisch<_corundobjektbungeeseil>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();   
                                sd->speichernwert(staerke); 
                                sd->speichernwert(farbe); 
                                sd->speichernendeblock();
};
char _corundobjektbungeeseil::assoziieren(_speicherbardynamisch<_corundobjektbungeeseil>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektbungeeseil::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Bungeeseil");
                                d->sektion(L"Corundobjekt Bungeeseil")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundobjekt Bungeeseil",L"Stärke",staerke);
                                d->einhaengen(L"Corundobjekt Bungeeseil",L"Farbe",farbe);
};
void _corundobjektbungeeseil::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Bungeeseil",L"Stärke",staerke);
                                d->auslesen(L"Corundobjekt Bungeeseil",L"Farbe",farbe);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H E R E 
//******************************************************************************************************************************************************************************************************
_corundobjektschere::_corundobjektschere(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektschere::~_corundobjektschere(){
};
void _corundobjektschere::animieren(){
};
char _corundobjektschere::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektschere>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektschere::speichern(_speicherbardynamisch<_corundobjektschere>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektschere::assoziieren(_speicherbardynamisch<_corundobjektschere>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektschere::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Schere");
};
void _corundobjektschere::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T Z E T T E L 
//******************************************************************************************************************************************************************************************************
_corundobjektzettel::_corundobjektzettel(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                text="Hier steht nichts.";
};
_corundobjektzettel::~_corundobjektzettel(){
};
void _corundobjektzettel::nachbereitenkonstruktion(){
                                _geometriequader*gb;
                                gb=new _geometriequader(welt->welt,ort,
                                0.4,0.1,0.6,welt->textur[52]);
                                gb->texturkoordinatenlaenge(1,1,1);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::farbeverbinder(_vektor4<_to>(1,1,1,1));
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::nurkollisionskopplung(true);
                                if(iminventar) {
                                 aufsammeln();
                                };

};
void _corundobjektzettel::animieren(){
};
void _corundobjektzettel::ablegen(const _vektor3<_tg>&o){
                                _listenknotenbasis<_corundobjekt>::aushaengen();
                                _listenknotenbasis<_corundobjekt>::einhaengen(welt);//->_listebasis<_corundobjekt>::einhaengen(this);
                                _listenknotenbasis<_corundobjekt>::loeschmarkierung(true);
                                if(welt->corundinventar){
                                 welt->corundinventar->textanimation(text);
                                };
};
char _corundobjektzettel::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektzettel>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(text);
                                sd->ladenende();
                                return(r);
};
void _corundobjektzettel::speichern(_speicherbardynamisch<_corundobjektzettel>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(text);
                                sd->speichernendeblock();
};
char _corundobjektzettel::assoziieren(_speicherbardynamisch<_corundobjektzettel>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektzettel::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Zettel");
                                d->sektion(L"Corundobjekt Zettel")->offen(true);
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundobjekt Zettel",L"Text",text);
};
void _corundobjektzettel::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Zettel",L"Text",text);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T F A L L S C H I R M 
//******************************************************************************************************************************************************************************************************
_corundobjektfallschirm::_corundobjektfallschirm(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektfallschirm::~_corundobjektfallschirm(){
};
void _corundobjektfallschirm::animieren(){
};
char _corundobjektfallschirm::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektfallschirm>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektfallschirm::speichern(_speicherbardynamisch<_corundobjektfallschirm>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektfallschirm::assoziieren(_speicherbardynamisch<_corundobjektfallschirm>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektfallschirm::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Fallschirm");
};
void _corundobjektfallschirm::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T Z A U B E R S T A B 
//******************************************************************************************************************************************************************************************************
_corundobjektzauberstab::_corundobjektzauberstab(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektzauberstab::~_corundobjektzauberstab(){
};
void _corundobjektzauberstab::animieren(){
};
char _corundobjektzauberstab::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektzauberstab>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektzauberstab::speichern(_speicherbardynamisch<_corundobjektzauberstab>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektzauberstab::assoziieren(_speicherbardynamisch<_corundobjektzauberstab>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektzauberstab::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Zauberstab");
};
void _corundobjektzauberstab::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T T R I E B W E R K 
//******************************************************************************************************************************************************************************************************
_corundobjekttriebwerk::_corundobjekttriebwerk(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjekttriebwerk::~_corundobjekttriebwerk(){
};
void _corundobjekttriebwerk::animieren(){
};
char _corundobjekttriebwerk::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjekttriebwerk>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjekttriebwerk::speichern(_speicherbardynamisch<_corundobjekttriebwerk>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjekttriebwerk::assoziieren(_speicherbardynamisch<_corundobjekttriebwerk>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjekttriebwerk::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Triebwerk");
};
void _corundobjekttriebwerk::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G E S U N D H E I T 
//******************************************************************************************************************************************************************************************************
_corundobjektgesundheit::_corundobjektgesundheit(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektgesundheit::~_corundobjektgesundheit(){
};
void _corundobjektgesundheit::animieren(){
};
char _corundobjektgesundheit::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektgesundheit>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektgesundheit::speichern(_speicherbardynamisch<_corundobjektgesundheit>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektgesundheit::assoziieren(_speicherbardynamisch<_corundobjektgesundheit>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektgesundheit::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Gesundheit");
};
void _corundobjektgesundheit::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T R E I S S Z W E C K E 
//******************************************************************************************************************************************************************************************************
_corundobjektreisszwecke::_corundobjektreisszwecke(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                bremsfaktor=0.5;
};
_corundobjektreisszwecke::~_corundobjektreisszwecke(){
};
void _corundobjektreisszwecke::nachbereitenkonstruktion(){
                                _geometriezylinder*gb;
                                gb=new _geometriezylinder(welt->welt,_vektor3<_tg>(0,0,0),
                                _vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0.4,0),_vektor3<_tg>(0,0,1),welt->textur[49]);
                                gb->aufloesung(_vektor<unsigned int>(12,1));
                                gb->texturkoordinatenlaenge(3,1,0.5,0.5);
                                gb->texturkoodinatenverschiebung(0,0,0.5,0.5);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::markierungpolygon(1);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(10);
                                _netz::nurkollisionskopplung(true);
                                _netz::skalierenkonisch(_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0.4,0),0.01,0.05);
                               // _netz::skalierenkonisch(ort+_vektor3<_tg>(0,0.10,0),_vektor3<_tg>(0,0.15,0),0.4,0.1);
                                
                                gb->vektor(_vektor3<_tg>(0,0.6,0));
                                gb->aufloesung(_vektor<unsigned int>(12,3));
                                _netz*temp2=gb->erzeugen();
                                temp2->subtraktiv(false);
                                temp2->lightmapschattierung(false);
                                temp2->keinbsp(true);
                                temp2->dynamisch(true);
                                temp2->schattenvolumen(true);
                                temp2->schattenvolumenlaenge(10);
                                temp2->nurkollisionskopplung(true);
                                temp2->skalierenkonisch(_vektor3<_tg>(0,0.0,0),_vektor3<_tg>(0,0.1,0),0.3 ,0.30);
                                temp2->skalierenkonisch(_vektor3<_tg>(0,0.2,0),_vektor3<_tg>(0,0.2,0),0.08,0.08);
                                temp2->skalierenkonisch(_vektor3<_tg>(0,0.6,0),_vektor3<_tg>(0,0.1,0),0.2 ,0.20);
                                temp2->verschiebenvertex(_vektor3<_tg>(0,0.4,0));
                                
                                delete gb;  

                                _netz::vereinigen(temp2);
                                _netz::rotierenx(35);
                                _netz::rotierenz(-40);                                
                                _netz::verschiebenvertex(ort);
                                
                                if(iminventar) {
                                 aufsammeln();
                                };

};
void _corundobjektreisszwecke::animieren(){
};
char _corundobjektreisszwecke::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektreisszwecke>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(bremsfaktor);
                                sd->ladenende();
                                return(r);
};
void _corundobjektreisszwecke::speichern(_speicherbardynamisch<_corundobjektreisszwecke>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(bremsfaktor);
                                sd->speichernendeblock();
};
char _corundobjektreisszwecke::assoziieren(_speicherbardynamisch<_corundobjektreisszwecke>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektreisszwecke::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Reisszwecke");
                                d->einhaengen(L"Corundobjekt Reisszwecke",L"Bremsfaktor [0..1]",bremsfaktor);
};
void _corundobjektreisszwecke::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Reisszwecke",L"Bremsfaktor [0..1]",bremsfaktor);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T H A M M E R 
//******************************************************************************************************************************************************************************************************
_corundobjekthammer::_corundobjekthammer(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjekthammer::~_corundobjekthammer(){
};
void _corundobjekthammer::animieren(){
};
void _corundobjekthammer::nachbereitenkonstruktion(){
                                _geometriezylinder*gb;
                                gb=new _geometriezylinder(welt->welt,ort+_vektor3<_tg>(0,0.03,0),
                                _vektor3<_tg>(0.04,0,0),_vektor3<_tg>(0,0,-0.6),_vektor3<_tg>(0,0.03,0),welt->textur[91]);
                                gb->aufloesung(_vektor<unsigned int>(10,1));
                                gb->texturkoordinatenlaenge(3,1,0.5,0.5);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::markierungpolygon(1);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(10);
                                _netz::nurkollisionskopplung(true);
                                _netz::skalierenkonisch(ort+_vektor3<_tg>(0,0.03,0),_vektor3<_tg>(0,0,-0.6),0.5,0.8);
                                delete gb;  
                                _geometriequader*gq=new _geometriequader(welt->welt,ort-_vektor3<_tg>(0.2,0,0),_vektor3<_tg>(0.4,0,0),_vektor3<_tg>(0,0.1,0),_vektor3<_tg>(0,0,0.1),welt->textur[49]);
                                gq->aufloesung(_vektor<unsigned int>(3,1,1));
                                _netz*nq=gq->erzeugen();
                                nq->subtraktiv(false);  
                                nq->keinbsp(true);     
                                nq->dynamisch(true);
                                nq->schattenvolumen(true);
                                nq->schattenvolumenlaenge(10);
                                nq->nurkollisionskopplung(true);                                                       
                                nq->lightmapschattierung(false);
                                nq->skalierenkonisch(ort+_vektor3<_tg>(-0.2,0.05,0.05),_vektor3<_tg>(0.05,0,0),0.5,0.5);
                                _netz::vereinigen(nq);
                                delete gq;
                                if(iminventar) {
                                 aufsammeln();
                                };
};
void _corundobjekthammer::ablegen(const _vektor3<_tg>&o){
                                _partition::_zone*zit;
                                _partition::_sektor*sit;
                                _polygon*pit;
                                _tg x0,x1,y0,y1,z0,z1;
                                _vektor3<_tg> m;
                                //--------------------------- neue position bestimmen -----------
                                m=_netz::mitte();
                                m=o-m;
                                _netz::verschiebenvertex(m+_vektor3<_tg>(0,0.03,0));
                                ort+=m;
                                //-------------------------- strukturen aktualisieren -------------
                                _listenknotenbasis<_corundobjekt>::aushaengen();
                                _listenknotenbasis<_corundobjekt>::einhaengen(welt);//welt->_listebasis<_corundobjekt>::einhaengen(this);
                                _listenknotenbasis<_netz>::einhaengen(welt->welt);//->_listebasis<_netz>::einhaengen(this);
                                if(welt->welt->anfang(zit))do{
                                 zit->einfuegenintern(this);
                                 if(_listebasis<_polygon>::anfang(pit))do{
                                  pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                  if(zit->anfang(sit))do{
                                   sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                  }while(zit->naechstes(sit));
                                 }while(_listebasis<_polygon>::naechstes(pit));
                                 _netz::erzeugenvertexlicht(zit);
                                }while(welt->welt->naechstes(zit)); 
                                _netz::aktualisierenschatten();     
                                iminventar=false;                             
};
char _corundobjekthammer::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjekthammer>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjekthammer::speichern(_speicherbardynamisch<_corundobjekthammer>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjekthammer::assoziieren(_speicherbardynamisch<_corundobjekthammer>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjekthammer::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Hammer");
};
void _corundobjekthammer::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G A S B R E N N E R 
//******************************************************************************************************************************************************************************************************
_corundobjektgasbrenner::_corundobjektgasbrenner(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektgasbrenner::~_corundobjektgasbrenner(){
};
void _corundobjektgasbrenner::animieren(){
};
char _corundobjektgasbrenner::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektgasbrenner>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektgasbrenner::speichern(_speicherbardynamisch<_corundobjektgasbrenner>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektgasbrenner::assoziieren(_speicherbardynamisch<_corundobjektgasbrenner>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektgasbrenner::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Gasbrenner");
};
void _corundobjektgasbrenner::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H U T Z S C H I L D 
//******************************************************************************************************************************************************************************************************
_corundobjektschutzschild::_corundobjektschutzschild(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektschutzschild::~_corundobjektschutzschild(){
};
void _corundobjektschutzschild::animieren(){
};
char _corundobjektschutzschild::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektschutzschild>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektschutzschild::speichern(_speicherbardynamisch<_corundobjektschutzschild>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektschutzschild::assoziieren(_speicherbardynamisch<_corundobjektschutzschild>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektschutzschild::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Schutzschild");
};
void _corundobjektschutzschild::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H N E I D B R E N N E R
//******************************************************************************************************************************************************************************************************
_corundobjektschneidbrenner::_corundobjektschneidbrenner(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektschneidbrenner::~_corundobjektschneidbrenner(){
};
void _corundobjektschneidbrenner::animieren(){
};
char _corundobjektschneidbrenner::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektschneidbrenner>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektschneidbrenner::speichern(_speicherbardynamisch<_corundobjektschneidbrenner>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektschneidbrenner::assoziieren(_speicherbardynamisch<_corundobjektschneidbrenner>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektschneidbrenner::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Schneidbrenner");
};
void _corundobjektschneidbrenner::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H W A R Z E S L O C H 
//******************************************************************************************************************************************************************************************************
_corundobjektschwarzesloch::_corundobjektschwarzesloch(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                pq=new _partikelquellesprite(w->welt,0,w->welt,w->pzeit,o+_vektor3<_tg>(0,0.9,0),_vektor3<_tg>(0,0.3,0),50,w->textur[15]);
                                pq->name("pq fuer schwarzes loch");
                                pq->aktiv(true);
                                pq->groesse(0.1);
                                pq->generationsrate(2);
                                pq->generationsratetoleranz(0);
                                pq->groessetoleranz(0.9);
                                pq->vektortoleranz(0.05);
                                pq->rotation(5);
                                pq->rotationtoleranz(0.9);
                                pq->lebensdauerpartikeltoleranz(0.1);     
                                gravitation=0;
                                wx=0;
                                wy=0;
                                                             
};
_corundobjektschwarzesloch::~_corundobjektschwarzesloch(){
                                if(gravitation) delete gravitation;
                                gravitation=0;
                                delete pq;
};
void _corundobjektschwarzesloch::nachbereitenkonstruktion(){


                                _geometriezylinder*gb;
                                gb=new _geometriezylinder(welt->welt,ort,
                                _vektor3<_tg>(0.1,0,0),_vektor3<_tg>(0,0.6,0),_vektor3<_tg>(0,0,0.1),welt->textur[50]);
                                gb->aufloesung(_vektor<unsigned int>(7,1));
                                gb->texturkoordinatenlaenge(3,1,1,1);
                                _netz*temp=gb->erzeugen();
                                _netz::vereinigen(temp);
                                _netz::einhaengen(welt->welt);
                                _netz::markierungpolygon(1);
                                _netz::subtraktiv(false);
                                _netz::lightmapschattierung(false);
                                _netz::keinbsp(true);
                                _netz::dynamisch(true);
                                _netz::schattenvolumen(true);
                                _netz::schattenvolumenlaenge(10);
                                _netz::nurkollisionskopplung(true);
                                delete gb;  
                                
                                if(gravitation==0){
                                 gravitation=new _gravitation<_tg>(welt->welt,_vektor3<_tg>(0,0,0),0.01);
                                 gravitation->divergenz(ort+_vektor3<_tg>(0,0.8,0),0.2);
                                 gravitation->_feld<_tg>::ort(ort);
                                };
                                
                                _vektor3<_tg> h(1,0,0);
                                _vektor3<_tg> v(0,0,0.5);
                                h.roty(wx);
                                h.rotx(wy);
                                v.roty(wx);
                                v.rotx(wy);
                                wx+=1.11;
                                wy+=2.21;
                                
                                
                                
                                pq->ort(ort+_vektor3<_tg>(0,0.8,0)+h);
                                
                                pq->vektor(v);


};
void _corundobjektschwarzesloch::kollision(_kollidierbar*k,_polygon*p){
                                //_corundobjekt::kollision(k,p);//standardverhalten (aufsammeln prüfen)
                                _corundkugel*ck=dynamic_cast<_corundkugel*>(k);
                                if(ck){
                                 ck->zerstoeren();
                                };
};

void _corundobjektschwarzesloch::verschiebenvertex(const _vektor3<_tg>v){
                                _corundobjekt::verschiebenvertex(v);
                                pq->ort(ort);
                                gravitation->divergenzort(0,ort);
                                gravitation->_feld<_tg>::ort(ort);
}; 
void _corundobjektschwarzesloch::animieren(){
                                _vektor3<_tg> h(1,0,0);
                                _vektor3<_tg> v(0,0,0.3);
                                h.rotz(sin(wx*_ph)*10);
                                h.roty(wy);
                               // v.rotz(wx);
                                v.roty(wy);
                                wx+=1.11;
                                wy+=5.821;
                                
                                
                                
                                pq->ort(ort+_vektor3<_tg>(0,0.8,0)+h);
                                
                                pq->vektor(v);
                                pq->animieren();
};
void _corundobjektschwarzesloch::schalten(){
                                gravitation->aktiv(!gravitation->aktiv());
                                pq->aktiv(gravitation->aktiv());
};

char _corundobjektschwarzesloch::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektschwarzesloch>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenassoziation();
                                sd->ladenende();
                                return(r);
};
void _corundobjektschwarzesloch::speichern(_speicherbardynamisch<_corundobjektschwarzesloch>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                saveassociationargument(sd->datei(),sd,gravitation);
                                sd->speichernendeblock();
};
char _corundobjektschwarzesloch::assoziieren(_speicherbardynamisch<_corundobjektschwarzesloch>*sd){
                                sd->assoziierenverschachtelung();
                                associateassociationargument(sd->datei(),sd->assoziation(),gravitation);
                                return(1);
};
void _corundobjektschwarzesloch::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Schwarzesloch");
                                d->sektion(L"Corundobjekt Schwarzesloch")->offen(true);
                                d->sektion(L"Netz")->offen(false);
};
void _corundobjektschwarzesloch::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T M A G N E T 
//******************************************************************************************************************************************************************************************************
_corundobjektmagnet::_corundobjektmagnet(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektmagnet::~_corundobjektmagnet(){
};
void _corundobjektmagnet::animieren(){
};
char _corundobjektmagnet::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektmagnet>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektmagnet::speichern(_speicherbardynamisch<_corundobjektmagnet>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektmagnet::assoziieren(_speicherbardynamisch<_corundobjektmagnet>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektmagnet::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Magnet");
};
void _corundobjektmagnet::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T P R E S S L U F T H A M M E R 
//******************************************************************************************************************************************************************************************************
_corundobjektpresslufthammer::_corundobjektpresslufthammer(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektpresslufthammer::~_corundobjektpresslufthammer(){
};
void _corundobjektpresslufthammer::animieren(){
};
char _corundobjektpresslufthammer::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektpresslufthammer>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektpresslufthammer::speichern(_speicherbardynamisch<_corundobjektpresslufthammer>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektpresslufthammer::assoziieren(_speicherbardynamisch<_corundobjektpresslufthammer>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektpresslufthammer::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Presslufthammer");
};
void _corundobjektpresslufthammer::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T T E L E P O R T E R 
//******************************************************************************************************************************************************************************************************
_corundobjektteleporter::_corundobjektteleporter(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektteleporter::~_corundobjektteleporter(){
};
void _corundobjektteleporter::animieren(){
};
char _corundobjektteleporter::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektteleporter>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektteleporter::speichern(_speicherbardynamisch<_corundobjektteleporter>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektteleporter::assoziieren(_speicherbardynamisch<_corundobjektteleporter>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektteleporter::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Teleporter");
};
void _corundobjektteleporter::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G L E I T M I T T E L 
//******************************************************************************************************************************************************************************************************
_corundobjektgleitmittel::_corundobjektgleitmittel(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                gleitfaktor=0.9;
};
_corundobjektgleitmittel::~_corundobjektgleitmittel(){
};
void _corundobjektgleitmittel::animieren(){
};
char _corundobjektgleitmittel::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektgleitmittel>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(gleitfaktor);
                                sd->ladenende();
                                return(r);
};
void _corundobjektgleitmittel::speichern(_speicherbardynamisch<_corundobjektgleitmittel>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(gleitfaktor);
                                sd->speichernendeblock();
};
char _corundobjektgleitmittel::assoziieren(_speicherbardynamisch<_corundobjektgleitmittel>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektgleitmittel::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Gleitmittel");
                                d->sektion(L"Netz")->offen(false);
                                d->einhaengen(L"Corundobjekt Gleitmittel",L"Gleitfaktor [0..1]",gleitfaktor);
};
void _corundobjektgleitmittel::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Gleitmittel",L"Gleitfaktor [0..1]",gleitfaktor);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G E L D 
//******************************************************************************************************************************************************************************************************
_corundobjektgeld::_corundobjektgeld(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektgeld::~_corundobjektgeld(){
};
void _corundobjektgeld::animieren(){
};
char _corundobjektgeld::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektgeld>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektgeld::speichern(_speicherbardynamisch<_corundobjektgeld>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektgeld::assoziieren(_speicherbardynamisch<_corundobjektgeld>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektgeld::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Geld");
};
void _corundobjektgeld::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S P R U N G F E D E R 
//******************************************************************************************************************************************************************************************************
_corundobjektsprungfeder::_corundobjektsprungfeder(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                kraft=0.5;
};
_corundobjektsprungfeder::~_corundobjektsprungfeder(){
};
void _corundobjektsprungfeder::animieren(){
};

void _corundobjektsprungfeder::ablegen(const _vektor3<_tg>&o){
                                _listenknoten<_polygon>*lnpit;
                                if(welt->spieler){
                                 _vektor3<_tg> h;
                                 if(welt->spieler->_liste<_polygon>::anfang(lnpit)){
                                  do{
                                   h+=lnpit->objekt()->normale();
                                  }while(welt->spieler->_liste<_polygon>::naechstes(lnpit));
                                  h.normalisieren();
                                  welt->spieler->vektor()+=h*kraft;
                                 };
                                };
};
char _corundobjektsprungfeder::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektsprungfeder>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(kraft);
                                sd->ladenende();
                                return(r);
};
void _corundobjektsprungfeder::speichern(_speicherbardynamisch<_corundobjektsprungfeder>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(kraft);                                
                                sd->speichernendeblock();
};
char _corundobjektsprungfeder::assoziieren(_speicherbardynamisch<_corundobjektsprungfeder>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektsprungfeder::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt Sprungfeder");
                                d->sektion(L"Netz")->offen(false);
                                d->sektion(L"Corundobjekt Sprungfeder")->offen(true);
                                d->einhaengen(L"Corundobjekt Sprungfeder",L"Sprungkraft [m/f]",kraft);
};
void _corundobjektsprungfeder::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                d->auslesen(L"Corundobjekt Sprungfeder",L"Sprungkraft [m/f]",kraft);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S K A L I E R E R
//******************************************************************************************************************************************************************************************************
_corundobjektskalierer::_corundobjektskalierer(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
                                kurve.vektor(0,_vektor3<_tg>(0,0,0));
                                kurve.vektor(1,_vektor3<_tg>(0,0,0));
                                kurve.ort(0,_vektor3<_tg>(0.2,0,0));
                                kurve.ort(1,_vektor3<_tg>(1.0,0,0));
                                kamve.vektor(0,_vektor3<_tg>(0,0,0));
                                kamve.vektor(1,_vektor3<_tg>(0,0,0));
                                kamve.ort(0,w->kameraverschiebung);
                                kamve.ort(1,w->kameraverschiebung);
                                iterator=0;
                                schritt=100;
                                animation=false;
                                weltskalieren=false;
};
_corundobjektskalierer::~_corundobjektskalierer(){
};
void _corundobjektskalierer::animieren(){
                                if(welt->spieler){
                                 _kollidierbarkugel*k=welt->spieler;
                                 _vektoranalysis3<_tg> va; 
                                 _listenknoten<_polygon>*it;
                                 _vektor3<_tg> lot;
                                 _tg p;
                                 bool abbruch=false;
                                 if(animation){
                                  k->radius(kurve.berechnen(iterator).laenge());
                                  iterator+=1.0f/schritt;
                                  welt->spieler->_kugel::radius(k->radius());
                                  _vektor3<_tg> altvek=k->vektor();
                                  k->_liste<_polygon>::aushaengen();// momentane kontakte entfernen 
                                  while((k->schnittstatisch())&&(abbruch==false)){
                                   if(k->_liste<_polygon>::anfang(it))do{
                                    va.lotpunktebene(k->ort(),it->objekt()->mitte(),it->objekt()->normale(),lot,p);
                                    lot+=k->ort();
                                    k->vektor()=lot+(it->objekt()->normale()*(k->radius()+nahenull)) - k->ort();
                                    if(k->testen()){
                                     k->ort(k->ort()+k->vektor()); 
                                    }else{
                                     welt->spieler->zerstoeren();
                                     abbruch=true;
                                     animation=false;
                                     _listenknotenbasis<_corundobjekt>::loeschmarkierung(true);
                                    };
                                    welt->spieler->_kugel::ort(k->ort());
                                   }while(k->_liste<_polygon>::naechstes(it));
                                   k->_liste<_polygon>::aushaengen();
                                   k->inkrementierenrekursionszaehler();
                                  };
                                  k->vektor(altvek);
                                  
                                  //kameraanimation
                                  if(weltskalieren) welt->kameraverschiebung=kamve.berechnen(iterator);
                                  
                                  
                                  if(iterator>1){
                                   animation=false;
                                   _listenknotenbasis<_corundobjekt>::loeschmarkierung(true);
                                  };
                                 };
                                };
};
void _corundobjektskalierer::ablegen(const _vektor3<_tg>&){
                                _tg r=welt->spieler->_kollidierbarkugel::radius();
                                _tg z=kurve.ort(1).laenge();
                                _tg s=z/r;
                                
                                kurve.ort(0,_vektor3<_tg>(r,0,0));
                                kamve.ort(0,welt->kameraverschiebung);
                                kamve.ort(1,welt->kameraverschiebung*s);
                                animation=true;
};
char _corundobjektskalierer::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektskalierer>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                _tg t;
                                r^=sd->ladenwert(t);
                                kurve.ort(1,_vektor3<_tg>(t,0,0));
                                r^=sd->ladenwert(schritt);
                                r^=sd->ladenwert(weltskalieren);
                                
                                sd->ladenende();
                                return(r);
};
void _corundobjektskalierer::speichern(_speicherbardynamisch<_corundobjektskalierer>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(kurve.ort(1).laenge());
                                sd->speichernwert(schritt);
                                sd->speichernwert(weltskalieren);
                                sd->speichernendeblock();
};
char _corundobjektskalierer::assoziieren(_speicherbardynamisch<_corundobjektskalierer>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektskalierer::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->sektion(L"Netz")->offen(false);
                                d->addierensektion(L"Corundobjekt Skalierer");
                                d->sektion(L"Corundobjekt Skalierer")->offen(true);
                                d->einhaengen(L"Corundobjekt Skalierer",L"Zielradius",kurve.ort(1).laenge());
                                d->einhaengen(L"Corundobjekt Skalierer",L"Skalierdauer",schritt);
                                d->einhaengen(L"Corundobjekt Skalierer",L"Weltskalierung",weltskalieren);
};
void _corundobjektskalierer::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
                                _tg t;
                                d->auslesen(L"Corundobjekt Skalierer",L"Zielradius",t);
                                kurve.ort(1,_vektor3<_tg>(t,0,0));
                                d->auslesen(L"Corundobjekt Skalierer",L"Skalierdauer",schritt);
                                d->auslesen(L"Corundobjekt Skalierer",L"Weltskalierung",weltskalieren);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T P F L A N Z E 
//******************************************************************************************************************************************************************************************************
_corundobjektpflanze::_corundobjektpflanze(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektpflanze::~_corundobjektpflanze(){
};
void _corundobjektpflanze::animieren(){
};
char _corundobjektpflanze::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektpflanze>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektpflanze::speichern(_speicherbardynamisch<_corundobjektpflanze>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektpflanze::assoziieren(_speicherbardynamisch<_corundobjektpflanze>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektpflanze::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt pflanze");
};
void _corundobjektpflanze::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T O B S T
//******************************************************************************************************************************************************************************************************
_corundobjektobst::_corundobjektobst(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektobst::~_corundobjektobst(){
};
void _corundobjektobst::animieren(){
};
char _corundobjektobst::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektobst>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektobst::speichern(_speicherbardynamisch<_corundobjektobst>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektobst::assoziieren(_speicherbardynamisch<_corundobjektobst>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektobst::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt obst");
};
void _corundobjektobst::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T D E M A T E R I A L I S I E R U N G
//******************************************************************************************************************************************************************************************************
_corundobjektdematerialisierung::_corundobjektdematerialisierung(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektdematerialisierung::~_corundobjektdematerialisierung(){
};
void _corundobjektdematerialisierung::animieren(){
};
char _corundobjektdematerialisierung::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektdematerialisierung>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektdematerialisierung::speichern(_speicherbardynamisch<_corundobjektdematerialisierung>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektdematerialisierung::assoziieren(_speicherbardynamisch<_corundobjektdematerialisierung>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektdematerialisierung::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt dematerialisierung");
};
void _corundobjektdematerialisierung::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T D E V I S U A L I S I E R U N G
//******************************************************************************************************************************************************************************************************
_corundobjektdevisualisierung::_corundobjektdevisualisierung(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektdevisualisierung::~_corundobjektdevisualisierung(){
};
void _corundobjektdevisualisierung::animieren(){
};
char _corundobjektdevisualisierung::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektdevisualisierung>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektdevisualisierung::speichern(_speicherbardynamisch<_corundobjektdevisualisierung>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektdevisualisierung::assoziieren(_speicherbardynamisch<_corundobjektdevisualisierung>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektdevisualisierung::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt devisualisierung");
};
void _corundobjektdevisualisierung::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T I N S E K T E N S P R A Y
//******************************************************************************************************************************************************************************************************
_corundobjektinsektenspray::_corundobjektinsektenspray(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektinsektenspray::~_corundobjektinsektenspray(){
};
void _corundobjektinsektenspray::animieren(){
};
char _corundobjektinsektenspray::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektinsektenspray>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektinsektenspray::speichern(_speicherbardynamisch<_corundobjektinsektenspray>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektinsektenspray::assoziieren(_speicherbardynamisch<_corundobjektinsektenspray>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektinsektenspray::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt insektenspray");
};
void _corundobjektinsektenspray::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T F E U E R L O E S C H E R 
//******************************************************************************************************************************************************************************************************
_corundobjektfeuerloescher::_corundobjektfeuerloescher(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektfeuerloescher::~_corundobjektfeuerloescher(){
};
void _corundobjektfeuerloescher::animieren(){
};
char _corundobjektfeuerloescher::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektfeuerloescher>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektfeuerloescher::speichern(_speicherbardynamisch<_corundobjektfeuerloescher>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektfeuerloescher::assoziieren(_speicherbardynamisch<_corundobjektfeuerloescher>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektfeuerloescher::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt feuerloescher");
};
void _corundobjektfeuerloescher::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S U M M E R 
//******************************************************************************************************************************************************************************************************
_corundobjektsummer::_corundobjektsummer(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektsummer::~_corundobjektsummer(){
};
void _corundobjektsummer::animieren(){
};
char _corundobjektsummer::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektsummer>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektsummer::speichern(_speicherbardynamisch<_corundobjektsummer>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektsummer::assoziieren(_speicherbardynamisch<_corundobjektsummer>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektsummer::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt summer");
};
void _corundobjektsummer::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B L I N K E R 
//******************************************************************************************************************************************************************************************************
_corundobjektblinker::_corundobjektblinker(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektblinker::~_corundobjektblinker(){
};
void _corundobjektblinker::animieren(){
};
char _corundobjektblinker::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektblinker>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektblinker::speichern(_speicherbardynamisch<_corundobjektblinker>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektblinker::assoziieren(_speicherbardynamisch<_corundobjektblinker>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektblinker::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt blinker");
};
void _corundobjektblinker::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B A T T E R I E 
//******************************************************************************************************************************************************************************************************
_corundobjektbatterie::_corundobjektbatterie(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektbatterie::~_corundobjektbatterie(){
};
void _corundobjektbatterie::animieren(){
};
char _corundobjektbatterie::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektbatterie>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektbatterie::speichern(_speicherbardynamisch<_corundobjektbatterie>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektbatterie::assoziieren(_speicherbardynamisch<_corundobjektbatterie>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektbatterie::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt batterie");
};
void _corundobjektbatterie::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T P I N S E L 
//******************************************************************************************************************************************************************************************************
_corundobjektpinsel::_corundobjektpinsel(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektpinsel::~_corundobjektpinsel(){
};
void _corundobjektpinsel::animieren(){
};
char _corundobjektpinsel::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektpinsel>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektpinsel::speichern(_speicherbardynamisch<_corundobjektpinsel>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektpinsel::assoziieren(_speicherbardynamisch<_corundobjektpinsel>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektpinsel::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt pinsel");
};
void _corundobjektpinsel::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B E S E N 
//******************************************************************************************************************************************************************************************************
_corundobjektbesen::_corundobjektbesen(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektbesen::~_corundobjektbesen(){
};
void _corundobjektbesen::animieren(){
};
char _corundobjektbesen::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektbesen>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektbesen::speichern(_speicherbardynamisch<_corundobjektbesen>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektbesen::assoziieren(_speicherbardynamisch<_corundobjektbesen>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektbesen::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt besen");
};
void _corundobjektbesen::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T L A M P E 
//******************************************************************************************************************************************************************************************************
_corundobjektlampe::_corundobjektlampe(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektlampe::~_corundobjektlampe(){
};
void _corundobjektlampe::animieren(){
};
char _corundobjektlampe::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektlampe>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektlampe::speichern(_speicherbardynamisch<_corundobjektlampe>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektlampe::assoziieren(_speicherbardynamisch<_corundobjektlampe>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektlampe::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt lampe");
};
void _corundobjektlampe::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T K E R Z E 
//******************************************************************************************************************************************************************************************************
_corundobjektkerze::_corundobjektkerze(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektkerze::~_corundobjektkerze(){
};
void _corundobjektkerze::animieren(){
};
char _corundobjektkerze::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektkerze>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektkerze::speichern(_speicherbardynamisch<_corundobjektkerze>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektkerze::assoziieren(_speicherbardynamisch<_corundobjektkerze>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektkerze::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt kerze");
};
void _corundobjektkerze::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G E W I C H T 
//******************************************************************************************************************************************************************************************************
_corundobjektgewicht::_corundobjektgewicht(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektgewicht::~_corundobjektgewicht(){
};
void _corundobjektgewicht::animieren(){
};
char _corundobjektgewicht::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektgewicht>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektgewicht::speichern(_speicherbardynamisch<_corundobjektgewicht>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektgewicht::assoziieren(_speicherbardynamisch<_corundobjektgewicht>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektgewicht::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt gewicht");
};
void _corundobjektgewicht::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G A S M A S K E 
//******************************************************************************************************************************************************************************************************
_corundobjektgasmaske::_corundobjektgasmaske(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektgasmaske::~_corundobjektgasmaske(){
};
void _corundobjektgasmaske::animieren(){
};
char _corundobjektgasmaske::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektgasmaske>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektgasmaske::speichern(_speicherbardynamisch<_corundobjektgasmaske>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektgasmaske::assoziieren(_speicherbardynamisch<_corundobjektgasmaske>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektgasmaske::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt gasmaske");
};
void _corundobjektgasmaske::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H U T Z H E L M 
//******************************************************************************************************************************************************************************************************
_corundobjektschutzhelm::_corundobjektschutzhelm(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektschutzhelm::~_corundobjektschutzhelm(){
};
void _corundobjektschutzhelm::animieren(){
};
char _corundobjektschutzhelm::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektschutzhelm>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektschutzhelm::speichern(_speicherbardynamisch<_corundobjektschutzhelm>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektschutzhelm::assoziieren(_speicherbardynamisch<_corundobjektschutzhelm>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektschutzhelm::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt schutzhelm");
};
void _corundobjektschutzhelm::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S P R I T Z E
//******************************************************************************************************************************************************************************************************
_corundobjektspritze::_corundobjektspritze(_corundwelt*w,const _vektor3<_tg>&o):_corundobjekt(w,o){
};
_corundobjektspritze::~_corundobjektspritze(){
};
void _corundobjektspritze::animieren(){
};
char _corundobjektspritze::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundobjektspritze>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);
};
void _corundobjektspritze::speichern(_speicherbardynamisch<_corundobjektspritze>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundobjektspritze::assoziieren(_speicherbardynamisch<_corundobjektspritze>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundobjektspritze::einhaengendialog(_dynamischerdialog*d){
                                _corundobjekt::einhaengendialog(d);
                                d->addierensektion(L"Corundobjekt spritze");
};
void _corundobjektspritze::auslesendialog(_dynamischerdialog*d){
                                _corundobjekt::auslesendialog(d);
};