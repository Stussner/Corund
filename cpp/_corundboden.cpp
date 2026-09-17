//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundboden.cpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include "../hpp/_corundboden.hpp"

//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N
//******************************************************************************************************************************************************************************************************

_corundboden::_corundboden(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_listenknotenbasis<_corundboden>(w),_corundschaltkopplung(w){
                                welt=w;             
                                ton=0;
                                ort=o;
                                ebene0=va;
                                ebene1=vb;
                                hauptfenster=0;
                                markierung=0;
};
_corundboden::~_corundboden(){
                                if(ton) delete ton;
};
void _corundboden::nachbereitenkonstruktion(){
};
void _corundboden::verschiebenvertex(const _vektor3<_tg>v){
                                _netz::verschiebenvertex(v);
                                ort+=v;
};   
void _corundboden::initialisieren(){
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
void _corundboden::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*co;
                                co=dynamic_cast<_corundkugel*>(k);
                                if(co){
                                };
};
void _corundboden::zeichnen(_grafik*grafik){//nur für editor
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
void _corundboden::animieren(){
};
void _corundboden::schalten(){
};
char _corundboden::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundboden>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(ort);
                                r^=sd->ladenwert(ebene0);
                                r^=sd->ladenwert(ebene1);
                                sd->ladenende();
                                return(r);

};
void _corundboden::speichern(_speicherbardynamisch<_corundboden>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(ort);
                                sd->speichernwert(ebene0);
                                sd->speichernwert(ebene1);
                                sd->speichernendeblock();
};
char _corundboden::assoziieren(_speicherbardynamisch<_corundboden>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundboden::netzwahl(_netz*,int){
};
void _corundboden::figurwahl(_corundfigur*,int){
};
void _corundboden::knotenwahl(_corundknoten*,int){
};
void _corundboden::einhaengendialog(_dynamischerdialog*d){
                                _netz::einhaengendialog(d);
                                d->addierensektion(L"Corundboden");
};
void _corundboden::auslesendialog(_dynamischerdialog*d){
                                _netz::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N N O R M A L  
//******************************************************************************************************************************************************************************************************
_corundbodennormal::_corundbodennormal(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodennormal::~_corundbodennormal(){
};
void _corundbodennormal::animieren(){
};
char _corundbodennormal::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodennormal>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodennormal::speichern(_speicherbardynamisch<_corundbodennormal>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodennormal::assoziieren(_speicherbardynamisch<_corundbodennormal>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodennormal::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden Normal");
};
void _corundbodennormal::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S C H A L T E R 
//******************************************************************************************************************************************************************************************************
_corundbodenschalter::_corundbodenschalter(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb),_corundschalter<_corundbodenschalter>(w){
                                anzahlzeigerek=0;
                                anzahlzeigerzk=0;
                                anzahlzeigerlk=0;
                                gedrueckt=false;
                                
};
_corundbodenschalter::~_corundbodenschalter(){
};
void _corundbodenschalter::kollision(_kollidierbar*k,_polygon*p){
                                _corundschalter<_corundbodenschalter>::kollision(k,p);
};
void _corundbodenschalter::animieren(){
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
void _corundbodenschalter::schalten(){
                                //alles schalten
                                //status=1-status;
                                //if(status==0) textur(welt->textur[80]); else textur(welt->textur[81]);
                                _corundschalter<_corundbodenschalter>::schaltenerstkontakt();
                                _corundschalter<_corundbodenschalter>::schaltenzwischenkontakt();
                                _corundschalter<_corundbodenschalter>::schaltenletztkontakt();
};
void _corundbodenschalter::schaltenerstkontakt(){
                                _corundschalter<_corundbodenschalter>::schaltenerstkontakt();
};
void _corundbodenschalter::schaltenzwischenkontakt(){
                                _corundschalter<_corundbodenschalter>::schaltenzwischenkontakt();
};
void _corundbodenschalter::schaltenletztkontakt(){
                                _corundschalter<_corundbodenschalter>::schaltenletztkontakt();
};
void _corundbodenschalter::zeichnen(_grafik*g) {
                                _corundboden::zeichnen(g);
                                _corundschalter<_corundbodenschalter>::zeichnen(g);
};
char _corundbodenschalter::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodenschalter>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=_corundschalter<_corundbodenschalter>::laden(fn,sd);
                                sd->ladenende();
                                return(r);
};
void _corundbodenschalter::speichern(_speicherbardynamisch<_corundbodenschalter>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung(); 
                                _corundschalter<_corundbodenschalter>::speichern(sd);   
                                sd->speichernendeblock();
};
char _corundbodenschalter::assoziieren(_speicherbardynamisch<_corundbodenschalter>*sd){
                                sd->assoziierenverschachtelung();
                                _corundschalter<_corundbodenschalter>::assoziieren(sd);
                                return(1);
};
void _corundbodenschalter::einhaengendialog(_dynamischerdialog*d){
                                _corundschalter<_corundbodenschalter>::dialogschaltkopplungswahl=hauptfenster->dbodenschaltkopplungswahl;
                                _corundboden::einhaengendialog(d);
                                _corundschalter<_corundbodenschalter>::einhaengendialog(d);
};
void _corundbodenschalter::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
                                _corundschalter<_corundbodenschalter>::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N I N V E R S
//******************************************************************************************************************************************************************************************************
_corundbodeninvers::_corundbodeninvers(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodeninvers::~_corundbodeninvers(){
};
void _corundbodeninvers::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(pit->haftreibung()*-1);
                                }while(_netz::naechstes(pit));
};
void _corundbodeninvers::animieren(){
};
char _corundbodeninvers::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodeninvers>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodeninvers::speichern(_speicherbardynamisch<_corundbodeninvers>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodeninvers::assoziieren(_speicherbardynamisch<_corundbodeninvers>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodeninvers::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden invers");
};
void _corundbodeninvers::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N W E L T R A U M 
//******************************************************************************************************************************************************************************************************
_corundbodenweltraum::_corundbodenweltraum(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodenweltraum::~_corundbodenweltraum(){
};
void _corundbodenweltraum::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0);
                                 pit->gleitreibung(1);
                                 pit->rollreibung(1);
                                }while(_netz::naechstes(pit));
};
void _corundbodenweltraum::animieren(){
};
char _corundbodenweltraum::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodenweltraum>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodenweltraum::speichern(_speicherbardynamisch<_corundbodenweltraum>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodenweltraum::assoziieren(_speicherbardynamisch<_corundbodenweltraum>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodenweltraum::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden weltraum");
};
void _corundbodenweltraum::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N E I S 
//******************************************************************************************************************************************************************************************************
_corundbodeneis::_corundbodeneis(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodeneis::~_corundbodeneis(){
};
void _corundbodeneis::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0.003);
                                 pit->gleitreibung(0.999);
                                 pit->rollreibung(0.999);
                                }while(_netz::naechstes(pit));
};
void _corundbodeneis::animieren(){
};
char _corundbodeneis::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodeneis>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodeneis::speichern(_speicherbardynamisch<_corundbodeneis>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodeneis::assoziieren(_speicherbardynamisch<_corundbodeneis>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodeneis::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden eis");
};
void _corundbodeneis::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S A N D
//******************************************************************************************************************************************************************************************************
_corundbodensand::_corundbodensand(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodensand::~_corundbodensand(){
};
void _corundbodensand::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0.8);
                                 pit->gleitreibung(0.9);
                                 pit->rollreibung(0.9);
                                }while(_netz::naechstes(pit));
};
void _corundbodensand::animieren(){
};
char _corundbodensand::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodensand>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodensand::speichern(_speicherbardynamisch<_corundbodensand>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodensand::assoziieren(_speicherbardynamisch<_corundbodensand>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodensand::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden sand");
};
void _corundbodensand::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S C H N E E
//******************************************************************************************************************************************************************************************************
_corundbodenschnee::_corundbodenschnee(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodenschnee::~_corundbodenschnee(){
};
void _corundbodenschnee::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0.6);
                                 pit->gleitreibung(0.98);
                                 pit->rollreibung(0.98);
                                }while(_netz::naechstes(pit));
};

void _corundbodenschnee::animieren(){
};
char _corundbodenschnee::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodenschnee>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodenschnee::speichern(_speicherbardynamisch<_corundbodenschnee>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodenschnee::assoziieren(_speicherbardynamisch<_corundbodenschnee>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodenschnee::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden schnee");
};
void _corundbodenschnee::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N W I E S E
//******************************************************************************************************************************************************************************************************
_corundbodenwiese::_corundbodenwiese(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodenwiese::~_corundbodenwiese(){
};
void _corundbodenwiese::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0.95);
                                 pit->gleitreibung(0.94);
                                 pit->rollreibung(0.94);
                                }while(_netz::naechstes(pit));
};
void _corundbodenwiese::animieren(){
};
char _corundbodenwiese::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodenwiese>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodenwiese::speichern(_speicherbardynamisch<_corundbodenwiese>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodenwiese::assoziieren(_speicherbardynamisch<_corundbodenwiese>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodenwiese::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden wiese");
};
void _corundbodenwiese::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N W A S S E R 
//******************************************************************************************************************************************************************************************************
_corundbodenwasser::_corundbodenwasser(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
                                texturvektor.setzen(0.03,0.01);
};
_corundbodenwasser::~_corundbodenwasser(){
};
void _corundbodenwasser::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0.95);
                                 pit->gleitreibung(0.94);
                                 pit->rollreibung(0.94);
                                 pit->transparenz(true);
                                 pit->zweiseitig(true);
                                 pit->farbeverbinder(_vektor4<_to>(1,1,1,0.5));
                                }while(_netz::naechstes(pit));
                                _netz::nurkollisionskopplung(true);
                                _netz::textur(welt->textur[53]);

};
void _corundbodenwasser::initialisieren(){
                                //kollisionskopplung vornehmen
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->::_liste<_kollisionskopplung>::aushaengen();
                                 pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                }while(_netz::naechstes(pit));
                                _netz::farbeverbinder(_vektor4<_to>(1,1,1,0.5));
                                _netz::transparenzfaktor(0.5);
}; 
void _corundbodenwasser::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*ck=dynamic_cast<_corundkugel*>(k);
                                if(ck){
                                 _listenknoten<_corundkugel>*kit;
                                 bool ex=false;
                                 if(geschnitten.anfang(kit))do{
                                  if(kit->objekt()==ck) ex=true;
                                 }while((geschnitten.naechstes(kit))&&(ex==false));
                                 if(ex==false) new _verbinder<_corundbodenwasser,_corundkugel>(ck,this,&geschnitten,ck);
                                };
};
void _corundbodenwasser::animieren(){
                                _listenknoten<_corundkugel>*kit;
                                if(geschnitten.anfang(kit)){
                                 do{
                                  if(innerhalb(kit->objekt())){
                                   //wenn kit vektor hoch, dann wasserspritzer
                                   kit->objekt()->tauchen=true;
                                  }else{
                                   kit->objekt()->tauchen=false;
                                  };
                                 }while(geschnitten.naechstes(kit));
                                 geschnitten.aushaengen();
                                };
                                //---------- wasser animieren
                               // _vektor2<_tg> v(0.03,0.01);
                                _polygon*pit;
                                _vertex*vit;
                                _listenknoten<_vertex>*lnvit;
                                _verbindervertexpolygon*cit;
                                if(_netz::anfang(pit))do{
                                 iterierenliste(pit,lnvit,
                                  vit=lnvit->objekt();
                                 //if(vit)do{
                                  cit=static_cast<_verbindervertexpolygon*>(lnvit);//vit->connector(pit);
                                  cit->holenvektor((unsigned int)0,(unsigned int)0)+=texturvektor;
                                 // vit=cit->naechstervertex();
                                 //}while(vit!=pit->vertex());
                                 );
                                }while(_netz::naechstes(pit));
};
bool _corundbodenwasser::innerhalb(_corundkugel*ck){
                                _polygon*pit;
                                _netz::anfang(pit);
                                _tg ds=(ck->_kollidierbarkugel::ort()-pit->mitte())*pit->normale();
                                if(ds<0) return(true); else return(false);
};
char _corundbodenwasser::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodenwasser>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(texturvektor);  
                                sd->ladenende();
                                return(r);

};
void _corundbodenwasser::speichern(_speicherbardynamisch<_corundbodenwasser>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();  
                                sd->speichernwert(texturvektor);  
                                sd->speichernendeblock();
};
char _corundbodenwasser::assoziieren(_speicherbardynamisch<_corundbodenwasser>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodenwasser::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden Wasser");
                                d->einhaengen(L"Corundboden Wasser",L"Texturbewegung",texturvektor);
};
void _corundbodenwasser::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
                                d->auslesen(L"Corundboden Wasser",L"Texturbewegung",texturvektor);

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S U M P F 
//******************************************************************************************************************************************************************************************************
_corundbodensumpf::_corundbodensumpf(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodensumpf::~_corundbodensumpf(){
};
void _corundbodensumpf::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0.96);
                                 pit->gleitreibung(0.8);
                                 pit->rollreibung(0.95);
                                 pit->transparenz(true);
                                 pit->zweiseitig(true);
                                 pit->farbeverbinder(_vektor4<_to>(1,1,1,0.9));
                                }while(_netz::naechstes(pit));
                                _netz::nurkollisionskopplung(true);
                                _netz::textur(welt->textur[53]);

};
void _corundbodensumpf::initialisieren(){
                                //kollisionskopplung vornehmen
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->::_liste<_kollisionskopplung>::aushaengen();
                                 pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                }while(_netz::naechstes(pit));
                                _netz::farbeverbinder(_vektor4<_to>(1,1,1,0.9));
                                _netz::transparenzfaktor(0.9);
}; 
void _corundbodensumpf::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*ck=dynamic_cast<_corundkugel*>(k);
                                if(ck){
                                 _listenknoten<_corundkugel>*kit;
                                 bool ex=false;
                                 if(geschnitten.anfang(kit))do{
                                  if(kit->objekt()==ck) ex=true;
                                 }while((geschnitten.naechstes(kit))&&(ex==false));
                                 if(ex==false) new _verbinder<_corundbodensumpf,_corundkugel>(ck,this,&geschnitten,ck);
                                };
};
void _corundbodensumpf::animieren(){
                                _listenknoten<_corundkugel>*kit;
                                if(geschnitten.anfang(kit)){
                                 do{
                                  if(innerhalb(kit->objekt())){
                                   //wenn kit vektor hoch, dann wasserspritzer
                                   kit->objekt()->tauchen=true;
                                  }else{
                                   kit->objekt()->tauchen=false;
                                  };
                                 }while(geschnitten.naechstes(kit));
                                 geschnitten.aushaengen();
                                };
                                //---------- wasser animieren
                               // _vektor2<_tg> v(0.03,0.01);
                                _polygon*pit;
                                _vertex*vit;
                                _listenknoten<_vertex>*lnvit;
                                _verbindervertexpolygon*cit;
                                if(_netz::anfang(pit))do{
                                 //vit=pit->vertex();
                                 //if(vit)do{
                                 // cit=vit->connector(pit);
                                 iterierenliste(pit,lnvit,
                                  vit=lnvit->objekt();
                                  cit=static_cast<_verbindervertexpolygon*>(lnvit);
                                  cit->holenvektor((unsigned int)0,(unsigned int)0)+=texturvektor;
                                 // vit=cit->naechstervertex();
                                 //}while(vit!=pit->vertex());
                                 );
                                }while(_netz::naechstes(pit));
};
bool _corundbodensumpf::innerhalb(_corundkugel*ck){
                                _polygon*pit;
                                _netz::anfang(pit);
                                _tg ds=(ck->_kollidierbarkugel::ort()-pit->mitte())*pit->normale();
                                if(ds<0) return(true); else return(false);
};
char _corundbodensumpf::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodensumpf>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(texturvektor);  
                                sd->ladenende();
                                return(r);

};
void _corundbodensumpf::speichern(_speicherbardynamisch<_corundbodensumpf>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();   
                                sd->speichernwert(texturvektor);  
                                sd->speichernendeblock();
};
char _corundbodensumpf::assoziieren(_speicherbardynamisch<_corundbodensumpf>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodensumpf::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden Sumpf");
                                d->einhaengen(L"Corundboden Sumpf",L"Texturbewegung",texturvektor);
};
void _corundbodensumpf::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
                                d->auslesen(L"Corundboden Sumpf",L"Texturbewegung",texturvektor);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N L A V A 
//******************************************************************************************************************************************************************************************************
_corundbodenlava::_corundbodenlava(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodenlava::~_corundbodenlava(){
};
void _corundbodenlava::nachbereitenkonstruktion(){
                                _corundboden::nachbereitenkonstruktion();
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->haftreibung(0.95);
                                 pit->gleitreibung(0.9);
                                 pit->rollreibung(0.9);
                                 pit->transparenz(true);
                                 pit->zweiseitig(true);
                                 pit->aufgehellt(true);
                                 pit->farbeverbinder(_vektor4<_to>(1,1,1,0.9));
                                }while(_netz::naechstes(pit));
                                _netz::nurkollisionskopplung(true);
                                _netz::textur(welt->textur[4]);

};
void _corundbodenlava::initialisieren(){
                                //kollisionskopplung vornehmen
                                _polygon*pit;
                                if(_netz::anfang(pit))do{
                                 pit->::_liste<_kollisionskopplung>::aushaengen();
                                 pit->::_liste<_kollisionskopplung>::einhaengen(this);
                                }while(_netz::naechstes(pit));
                                _netz::farbeverbinder(_vektor4<_to>(1,1,1,0.9));
                                _netz::transparenzfaktor(0.9);
}; 
void _corundbodenlava::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*ck=dynamic_cast<_corundkugel*>(k);
                                if(ck){
                                 _listenknoten<_corundkugel>*kit;
                                 bool ex=false;
                                 if(geschnitten.anfang(kit))do{
                                  if(kit->objekt()==ck) ex=true;
                                 }while((geschnitten.naechstes(kit))&&(ex==false));
                                 if(ex==false) new _verbinder<_corundbodenlava,_corundkugel>(ck,this,&geschnitten,ck);
                                };
};
void _corundbodenlava::animieren(){
                                _listenknoten<_corundkugel>*kit;
                                if(geschnitten.anfang(kit)){
                                 do{
                                  if(innerhalb(kit->objekt())){
                                   //wenn kit vektor hoch, dann wasserspritzer
                                   kit->objekt()->inlava=true;
                                  }else{
                                   kit->objekt()->inlava=false;
                                  };
                                 }while(geschnitten.naechstes(kit));
                                 geschnitten.aushaengen();
                                };
                                //---------- wasser animieren
                               // _vektor2<_tg> v(0.03,0.01);
                                _polygon*pit;
                                _vertex*vit;
                                _listenknoten<_vertex>*lnvit;
                                _verbindervertexpolygon*cit;
                                if(_netz::anfang(pit))do{
                                 //vit=pit->vertex();
                                 //if(vit)do{
                                 // cit=vit->connector(pit);
                                 iterierenliste(pit,lnvit,
                                  vit=lnvit->objekt();
                                  cit=static_cast<_verbindervertexpolygon*>(lnvit);
                                  cit->holenvektor((unsigned int)0,(unsigned int)0)+=texturvektor;
                                 );
                                 // vit=cit->naechstervertex();
                                 //}while(vit!=pit->vertex());
                                 
                                }while(_netz::naechstes(pit));
                               
                                
};
bool _corundbodenlava::innerhalb(_corundkugel*ck){
                                _polygon*pit;
                                _netz::anfang(pit);
                                _tg ds=(ck->_kollidierbarkugel::ort()-pit->mitte())*pit->normale();
                                if(ds<0) return(true); else return(false);
};
char _corundbodenlava::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodenlava>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(texturvektor);  

                                sd->ladenende();
                                return(r);

};
void _corundbodenlava::speichern(_speicherbardynamisch<_corundbodenlava>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();   
                                sd->speichernwert(texturvektor);  
                                sd->speichernendeblock();
};
char _corundbodenlava::assoziieren(_speicherbardynamisch<_corundbodenlava>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodenlava::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden Lava");
                                d->einhaengen(L"Corundboden Lava",L"Texturbewegung",texturvektor);
};
void _corundbodenlava::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
                                d->auslesen(L"Corundboden Lava",L"Texturbewegung",texturvektor);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N B E S C H L E U N I G U N G 
//******************************************************************************************************************************************************************************************************
_corundbodenbeschleunigung::_corundbodenbeschleunigung(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
                                vektor.setzen(1,0,0);
                                texturvektor.setzen(0.1,0);
                                eingeschaltet=true;
};
_corundbodenbeschleunigung::~_corundbodenbeschleunigung(){
};
void _corundbodenbeschleunigung::kollision(_kollidierbar*k,_polygon*){
};
void _corundbodenbeschleunigung::animieren(){
                                _polygon*pit;
                                _vertex*vit;
                                _listenknoten<_vertex>*lnvit;
                                _verbindervertexpolygon*cit;
                                _listenknoten<_kollidierbar>*kit;
                                //------------------------------
                                if(eingeschaltet){
                                 if(_netz::anfang(pit))do{
                                  //---------- kugeln beschleunigen , nutzt verbinder
                                  if(pit->_liste<_kollidierbar>::anfang(kit))do{
                                   _corundkugel*c=dynamic_cast<_corundkugel*>(kit->objekt());
                                   if(c) c->vektor(c->vektor()+vektor);
                                  }while(pit->_liste<_kollidierbar>::naechstes(kit));
                                  //---------- textur animieren
                                  //vit=pit->vertex();
                                  //if(vit)do{
                                  // cit=vit->connector(pit);
                                  iterierenliste(pit,lnvit,
                                   vit=lnvit->objekt();
                                   cit=static_cast<_verbindervertexpolygon*>(lnvit);
                                   cit->holenvektor((unsigned int)0,(unsigned int)0)+=texturvektor;
                                  // vit=cit->naechstervertex();
                                  //}while(vit!=pit->vertex());
                                  );
                                 }while(_netz::naechstes(pit));
                                };
};
void _corundbodenbeschleunigung::schalten(){
                                eingeschaltet=!eingeschaltet;
};
char _corundbodenbeschleunigung::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodenbeschleunigung>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(vektor);
                                r^=sd->ladenwert(texturvektor);
                                r^=sd->ladenwert(eingeschaltet);
                                sd->ladenende();
                                return(r);

};
void _corundbodenbeschleunigung::speichern(_speicherbardynamisch<_corundbodenbeschleunigung>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernwert(vektor);
                                sd->speichernwert(texturvektor);
                                sd->speichernwert(eingeschaltet);
                                sd->speichernendeblock();
};
char _corundbodenbeschleunigung::assoziieren(_speicherbardynamisch<_corundbodenbeschleunigung>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodenbeschleunigung::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden Beschleunigung");
                                d->sektion(L"Netz")->offen(false);
                                d->sektion(L"Corundboden Beschleunigung")->offen(true);
                                d->einhaengen(L"Corundboden Beschleunigung",L"Eingeschaltet",eingeschaltet);
                                d->einhaengen(L"Corundboden Beschleunigung",L"Beschleunigung [m/f]",vektor);
                                d->einhaengen(L"Corundboden Beschleunigung",L"Texturvektor [tm/f]",texturvektor);
};
void _corundbodenbeschleunigung::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
                                d->auslesen(L"Corundboden Beschleunigung",L"Eingeschaltet",eingeschaltet);
                                d->auslesen(L"Corundboden Beschleunigung",L"Beschleunigung [m/f]",vektor);
                                d->auslesen(L"Corundboden Beschleunigung",L"Texturvektor [tm/f]",texturvektor);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N G R A D I E N Z 
//******************************************************************************************************************************************************************************************************
_corundbodengradienz::_corundbodengradienz(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
};
_corundbodengradienz::~_corundbodengradienz(){
};
void _corundbodengradienz::animieren(){
};
char _corundbodengradienz::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodengradienz>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                sd->ladenende();
                                return(r);

};
void _corundbodengradienz::speichern(_speicherbardynamisch<_corundbodengradienz>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();    
                                sd->speichernendeblock();
};
char _corundbodengradienz::assoziieren(_speicherbardynamisch<_corundbodengradienz>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodengradienz::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden gradienz");
};
void _corundbodengradienz::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N T R A N S P O R T 
//******************************************************************************************************************************************************************************************************
_corundbodentransport::_corundbodentransport(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
                                status=0;
                                vektor.setzen(0,0,0);
                                deltavektor.setzen(0,0,0);
                                setzenvektor(_vektor3<_tg>(0,0,0));
                                wartezeit=200;
                                schritt=0.01;
                                iteratort=0;   
                                iteratork=0;   
                                knotenit=0;
                                anzahlzeiger=0;
                                zaehler=0;
                                kraftwirkung=1;
                                eingeschaltet=true;
                                kurve.ort(0,_vektor3<_tg>(0,0,0));
                                kurve.ort(1,_vektor3<_tg>(0,0,0));
                                kurve.vektor(0,_vektor3<_tg>(0,0,0));
                                kurve.vektor(1,_vektor3<_tg>(0,0,0));
                                
};
_corundbodentransport::~_corundbodentransport(){
};
void _corundbodentransport::setzenvektor(const _vektor3<_tg>&nv){
                                deltavektor=nv-vektor;
                                vektor=nv;
};
void _corundbodentransport::schalten(){
                                eingeschaltet=!eingeschaltet;
};
void _corundbodentransport::animieren(){
                               // new _weltdebugkreuz(welt->welt,_netz::mitte(),0.02,_vektor4<_to>(1,0,0,1));
                                if(eingeschaltet){
                                 if(status==1){//in bewegung 
                                  iteratort+=schritt;
                                  if((iteratort-1)<-nahenull){
                                   setzenvektor(kurve.berechnen(iteratort)-altort);
                                   altort+=vektor;
                                   bewegen(true);
                                  }else{
                                   //künstliches anpassen (ohne vektor manipulation der objekte)
                                   vektor=kurve.ort(1)-_netz::mitte();
                                   altort+=vektor;
                                   bewegen(false);
                                   iteratort=0;
                                   status=0;
                                  // deltavektor.setzen(0,0,0);
                                   if(knotenit) zaehler=knotenit->objekt()->wartezeit; else zaehler=wartezeit;
                                   if(zaehler==0){//gleich weiterfahren
                                    status=1;
                                    if(knotenit){
                                     _listenknoten<_corundknoten>*kn=knotenit->naechstes();
                                     kurve.ort(0,kurve.ort(1));
                                     kurve.ort(1,kn->objekt()->ort);
                                     kurve.vektor(0,knotenit->objekt()->vektorabfahrt);
                                     kurve.vektor(1,kn->objekt()->vektorankunft);
                                     knotenit=kn;
                                    };
                                  /*  iteratort+=schritt;
                                    setzenvektor(kurve.berechnen(iteratort)-altort);
                                    altort+=vektor;
                                    bewegen(true);*/
                                   };
                                   /*_netz::markierungvertex(1);
                                   _polygon*pit;
                                   _vertex*vit;
                                   if(_netz::anfang(pit))do{
                                    vit=pit->vertex();
                                    if(vit)do{
                                     if(vit->markierung()==1){
                                      vit->markierung(0);
                                      *vit+=h;
                                     };
                                     vit=vit->naechstes(pit);
                                    }while(vit!=pit->vertex);
                                   }while(_netz::naechstes(pit));
                                   */
                                  };
                                 }else{//in ruhe
                                  if(zaehler==0){
                                   status=1;
                                   iteratort=0;
                                   if(knotenit){
                                    _listenknoten<_corundknoten>*kn=knotenit->naechstes();
                                    kurve.ort(0,kurve.ort(1));
                                    kurve.ort(1,kn->objekt()->ort);
                                    kurve.vektor(0,knotenit->objekt()->vektorabfahrt);
                                    kurve.vektor(1,kn->objekt()->vektorankunft);
                                    knotenit=kn;
                                   };
                                  }else{
                                   zaehler--;
                                   vektor.setzen(0,0,0);
                                   deltavektor.setzen(0,0,0);
                                  };
                                   
                                 };
                                };
};
void _corundbodentransport::initialisieren(){
                                _listenknoten<_corundknoten>*it;
                                unsigned int i;
                                //-----------------------------
                                _corundboden::initialisieren();
                                vektor.setzen(0,0,0);
                                deltavektor.setzen(0,0,0);
                                kurve.ort(0,_netz::mitte());
                                kurve.ort(1,_netz::mitte());
                                kurve.vektor(0,_vektor3<_tg>(0,0,0));
                                kurve.vektor(1,_vektor3<_tg>(0,0,0));
                                knotenit=0;
                                if(listeck.anfang(it)){
                                 for(i=0;i<iteratork;i++) listeck.naechstes(it);
                                 knotenit=it;
                                 kurve.ort(1,it->objekt()->ort);
                                 kurve.vektor(0,_vektor3<_tg>(0,0,0));
                                 kurve.vektor(1,it->objekt()->vektorankunft);
                                };
                                altort=kurve.ort(0);
};

void _corundbodentransport::bewegen(bool vektormanipulation){
                                _netz::verschiebenvertex(vektor);
                                _tg x0,x1,y0,y1,z0,z1;
                                _partition::_zone*zit;
                                _partition::_sektor*sit;
                                _polygon*pit;
                                _vektor3<_tg> v;
                                
                                _listenknoten<_kollidierbar>*kit;
                                if(welt->welt->anfang(zit)){
                                 if(_netz::anfang(pit))do{
                                  pit->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                  pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                  if(zit->anfang(sit))do{
                                   sit->_baumoctal<_polygon,_tg>::einhaengen(pit,x0,x1,y0,y1,z0,z1);
                                  }while(zit->naechstes(sit));
                                 }while(_netz::naechstes(pit));                                  
                                };
                                if(vektormanipulation){
                                 if(_netz::anfang(pit))do{
                                  if(pit->anfang(kit))do{
                                   /* _tg f,s;
                                    v=vektor - kit->objekt()->vektor();
                                    s=(vektor*pit->gleitreibung())*kit->objekt()->vektor();
                                    if(s<0) f=1;
                                    if(s>1) f=0; else if(s>=0){
                                     f=1-s;
                                    };*/
                                   
                                    kit->objekt()->vektor()+=deltavektor*kraftwirkung;//voprher v
                                   }while(pit->naechstes(kit));
                                  }while(_netz::naechstes(pit));                                
                                 };
};
void _corundbodentransport::zeichnen(_grafik*g){
                                _corundboden::zeichnen(g);
                                _weltdebugpfeil*wp=new _weltdebugpfeil(welt->welt,_netz::mitte(),_vektor3<_tg>(0,0,0),0.1,0.05,_vektor4<_to>(1,1,0,1));
                                //_weltdebugtext*wt=new _weltdebugtext(welt->welt,"Erstkontakt",_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,0.3),_vektor4<_to>(1,1,0,1));
                                _listenknoten<_corundknoten>*oit;
                                _listenknoten<_corundknoten>*oin;
                                _vektor4<_to> col(0.5,0,0,1);
                                wp->farbe(_vektor4<_to>(1,1,0,1));
                               // wt->farbe(_vektor4<_to>(1,1,0,1));
                               // wt->text("Erstkontakt");
                                if(listeck.anfang(oit)){
                                 do{
                                  oin=oit->naechstes();
                                  kurve.ort(0,oit->objekt()->ort);
                                  kurve.ort(1,oin->objekt()->ort);
                                  kurve.vektor(0,oit->objekt()->vektorabfahrt);
                                  kurve.vektor(1,oin->objekt()->vektorankunft);
                                  for(_tg it=0;it<=1;it+=0.01){
                                   g->zeichnen(kurve.berechnen(it),kurve.berechnen(it+0.01),col,col);
                                  };
                                  wp->ort(1,oit->objekt()->ort);
                                  wp->zeichnen(g);
                                  wp->ort(0,wp->ort(1));
                                  //wt->ort((wp->ort(0)+wp->ort(1))*0.5);
                                  //wt->zeichnen(g);
                                 }while(listeck.naechstes(oit));
                                 wp->ort(1,oit->objekt()->ort);
                                 wp->zeichnen(g);
                                };
                                
                                //delete wt;
                                delete wp;
        
};
char _corundbodentransport::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodentransport>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(vektor);
                                r^=sd->ladenwert(status);
                                r^=sd->ladenwert(wartezeit);
                                r^=sd->ladenwert(schritt);
                                r^=sd->ladenwert(iteratort);   
                                r^=sd->ladenwert(iteratork);   
                                r^=sd->ladenwert(anzahlzeiger);
                                unsigned int i;
                                for(i=0;i<anzahlzeiger;i++) r^=sd->ladenassoziation();                                                             
                                _vektor3<_tg> o;
                                r^=sd->ladenwert(o);kurve.ort(0,o);
                                r^=sd->ladenwert(o);kurve.ort(1,o);
                                r^=sd->ladenwert(o);kurve.vektor(0,o);
                                r^=sd->ladenwert(o);kurve.vektor(1,o);
                                r^=sd->ladenwert(zaehler);
                                r^=sd->ladenwert(eingeschaltet);
                                r^=sd->ladenwert(kraftwirkung);
                                
                                sd->ladenende();
                                return(r);

};
void _corundbodentransport::speichern(_speicherbardynamisch<_corundbodentransport>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();  
                                sd->speichernwert(vektor);
                                sd->speichernwert(status);
                                sd->speichernwert(wartezeit);
                                sd->speichernwert(schritt);
                                sd->speichernwert(iteratort);
                                
                                sd->speichernwert(iteratork);
                                _listenknoten<_corundknoten>*it;
                                sd->speichernwert(listeck.anzahl());
                                if(listeck.anfang(it))do{
                                 saveassociationargument(sd->datei(),sd,it->objekt());
                                }while(listeck.naechstes(it));                                
                                sd->speichernwert(kurve.ort(0));
                                sd->speichernwert(kurve.ort(1));
                                sd->speichernwert(kurve.vektor(0));
                                sd->speichernwert(kurve.vektor(1));
                                sd->speichernwert(zaehler);
                                sd->speichernwert(eingeschaltet);
                                sd->speichernwert(kraftwirkung);
                                sd->speichernendeblock();
};
char _corundbodentransport::assoziieren(_speicherbardynamisch<_corundbodentransport>*sd){
                                unsigned int i;
                                _corundknoten*corundknoten=0;
                                sd->assoziierenverschachtelung();
                                listeck.aushaengen();
                                for(i=0;i<anzahlzeiger;i++) {
                                 corundknoten=0; associateassociationargument(sd->datei(),sd->assoziation(),corundknoten);
                                 if(corundknoten) listeck.einhaengen(corundknoten);
                                };
                                return(1);
};
void _corundbodentransport::knotenwahl(_corundknoten*n,int){
                                if(hauptfenster) {
                                 listeck.einhaengen(n);
                                 if(hauptfenster) hauptfenster->zeichnen();
                                };
};
void _corundbodentransport::beiknopfausfuehren(_guiereignisdaten*ep){
                                //netz auswahldialog aktivieren
                                if(hauptfenster) {
                                 hauptfenster->dknotenwahl->corundboden(this);
                                 hauptfenster->dknotenwahl->zeigen();
                                };
};
void _corundbodentransport::beiknopfloeschen(_guiereignisdaten*){
                                listeck.aushaengen();
                                if(hauptfenster) hauptfenster->zeichnen();
};
void _corundbodentransport::beiknopfloeschenletzten(_guiereignisdaten*){
                                _listenknoten<_corundknoten>*ln;
                                if(listeck.anfang(ln)){
                                 ln=ln->vorheriges();
                                 delete ln;
                                };
                                if(hauptfenster) hauptfenster->zeichnen();
};
void _corundbodentransport::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden Transport");
                                d->sektion(L"Netz")->offen(false);
                                d->sektion(L"Corundboden Transport")->offen(true);
                                d->einhaengenknopf<_corundbodentransport>(L"Corundboden Transport",L"Route : Neuen Knotenzeiger",L"holen",this,&_corundbodentransport::beiknopfausfuehren);
                                d->einhaengenknopf<_corundbodentransport>(L"Corundboden Transport",L"Route : Letzten Knotenzeiger",L"löschen",this,&_corundbodentransport::beiknopfloeschenletzten);
                                d->einhaengenknopf<_corundbodentransport>(L"Corundboden Transport",L"Route : Alle Knotenzeiger",L"löschen",this,&_corundbodentransport::beiknopfloeschen);
                                d->einhaengen(L"Corundboden Transport",L"Eingeschaltet",eingeschaltet);
                                d->einhaengen(L"Corundboden Transport",L"Status 0=Wartezeit,1=Bewegung",status);
                                d->einhaengen(L"Corundboden Transport",L"Wartezeit [f] ",wartezeit);
                                d->einhaengen(L"Corundboden Transport",L"Bewegungsschritt [m/f] ",schritt);
                                d->einhaengen(L"Corundboden Transport",L"Kraftwirkung [0..1]",kraftwirkung);
};
void _corundbodentransport::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
                                d->auslesen(L"Corundboden Transport",L"Eingeschaltet",eingeschaltet);
                                d->auslesen(L"Corundboden Transport",L"Status 0=Wartezeit,1=Bewegung",status);
                                d->auslesen(L"Corundboden Transport",L"Wartezeit [f] ",wartezeit);
                                d->auslesen(L"Corundboden Transport",L"Bewegungsschritt [m/f] ",schritt);
                                d->auslesen(L"Corundboden Transport",L"Kraftwirkung [0..1]",kraftwirkung);
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N T O T E N K O P F 
//******************************************************************************************************************************************************************************************************
_corundbodentotenkopf::_corundbodentotenkopf(_corundwelt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb):_corundboden(w,o,va,vb){
                                staerke=1;
                                zaehler=0;
                                status=0;
};
_corundbodentotenkopf::~_corundbodentotenkopf(){
};

void _corundbodentotenkopf::kollision(_kollidierbar*k,_polygon*){
                                _corundkugel*t;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 _vektor3<_tg> v=k->schnittpunkt.normale;
                                 v*=staerke;
                                 t->vektor(t->vektor()+v);
                                 t->zerstoeren();
                                 zaehler=100;
                                };
};
void _corundbodentotenkopf::animieren(){
                                if(zaehler>0){
                                 if((zaehler%10)==0){
                                  status=1-status;
                                  textur(welt->textur[82+status]);
                                 };
                                 zaehler--;
                                };
};
char _corundbodentotenkopf::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_corundbodentotenkopf>*sd){
                                char r=1;
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(staerke);
                                r^=sd->ladenwert(zaehler);
                                r^=sd->ladenwert(status);
                                
                                sd->ladenende();
                                return(r);

};
void _corundbodentotenkopf::speichern(_speicherbardynamisch<_corundbodentotenkopf>*sd){
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();   
                                sd->speichernwert(staerke); 
                                sd->speichernwert(zaehler);
                                sd->speichernwert(status);
                                sd->speichernendeblock();
};
char _corundbodentotenkopf::assoziieren(_speicherbardynamisch<_corundbodentotenkopf>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
void _corundbodentotenkopf::einhaengendialog(_dynamischerdialog*d){
                                _corundboden::einhaengendialog(d);
                                d->addierensektion(L"Corundboden Totenkopf");
                                d->einhaengen(L"Corundboden Totenkopf",L"Stärke",staerke);                                
};
void _corundbodentotenkopf::auslesendialog(_dynamischerdialog*d){
                                _corundboden::auslesendialog(d);
                                d->auslesen(L"Corundboden Totenkopf",L"Stärke",staerke);
};
