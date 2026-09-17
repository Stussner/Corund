//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundschalter.hpp
//  Datum        : 04.04.2006
//  Beschreibung : Schaltmachanismen
//******************************************************************************************************************************************************************************************************
//******************************************************************************************************************************************************************************************************
//                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _corundschaltkopplung;
template<class T>class _corundschalter;
//******************************************************************************************************************************************************************************************************
//                              I N C L U D E S
//******************************************************************************************************************************************************************************************************
#ifndef _corundschalterhpp_included
#define _corundschalterhpp_included
#include <_ton.hpp>
#include <_text.hpp>
#include <_weltpolygon.hpp>
#include <_welt.hpp>
#include <_weltkomponente.hpp>
#include <_weltoptik.hpp>
#include <_weltgeometrie.hpp>
#include <_systemwin.hpp>
#ifdef CORUND_MIT_OPENGL
 #include <_grafikopengl.hpp>
#else
 #include <_grafikdirectx.hpp>
#endif
#include <_editionwin.hpp>
//#include <_corundeditor.hpp>
class _hauptfenster;
class _corundwelt;
template<class T>class _dialogschaltkopplungwahl;
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S C H A L T K O P P L U N G
//******************************************************************************************************************************************************************************************************
class _corundschaltkopplung:public _listenknotenbasis<_corundschaltkopplung>{
        public:
                _corundschaltkopplung(_corundwelt*);
                virtual ~_corundschaltkopplung();
                virtual void schalten();
                virtual void schalten(bool);       
        public:
                _zeichenkette<char> dateiqualifikation;//muss in den speicherprozeduren gesetzt werden                
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S C H A L T E R 
//******************************************************************************************************************************************************************************************************
template<class T>class _corundschalter:public virtual _editierbar{
        public:
                _corundschalter(_corundwelt*);
                virtual ~_corundschalter();        
                virtual void schalten();
                virtual void schalten(bool);
                virtual void schaltenerstkontakt();
                virtual void schaltenzwischenkontakt();
                virtual void schaltenletztkontakt();                
                virtual void schaltenerstkontakt(bool);
                virtual void schaltenzwischenkontakt(bool);
                virtual void schaltenletztkontakt(bool);   
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren()=0;
                virtual void zeichnen(_grafik*g);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<T>*);
                void speichern(_speicherbardynamisch<T>*);
                char assoziieren(_speicherbardynamisch<T>*);
                //edition
                virtual void schaltkopplungwahl(_corundschaltkopplung*,int);
                void beiknopfausfuehrenek(_guiereignisdaten*);
                void beiknopfausfuehrenzk(_guiereignisdaten*);
                void beiknopfausfuehrenlk(_guiereignisdaten*);
                void beiknopfloeschenletztenek(_guiereignisdaten*);
                void beiknopfloeschenletztenzk(_guiereignisdaten*);
                void beiknopfloeschenletztenlk(_guiereignisdaten*);
                void beiknopfloeschenek(_guiereignisdaten*);                
                void beiknopfloeschenzk(_guiereignisdaten*);                
                void beiknopfloeschenlk(_guiereignisdaten*);                
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);                   
        public:                
                _liste<_corundschaltkopplung> listeek;
                _liste<_corundschaltkopplung> listezk;
                _liste<_corundschaltkopplung> listelk;
        protected:               
                _corundwelt*welt; 
                //speichern hilfselemente
                unsigned int anzahlzeigerek;  
                unsigned int anzahlzeigerzk;  
                unsigned int anzahlzeigerlk;  
                bool gedrueckt;//speichern ! nicht editeren!      
                //_hauptfenster*hauptfenster;
                _dialogschaltkopplungwahl<T>*dialogschaltkopplungswahl;
        private:
                int modus;            
                
};
template<class T>_corundschalter<T>::_corundschalter(_corundwelt*w){
                                //hauptfenster=0;
                                welt=w;
                                dialogschaltkopplungswahl=0;
                                modus=0;
                                gedrueckt=false;
                                anzahlzeigerek=0;
                                anzahlzeigerzk=0;
                                anzahlzeigerlk=0;                                
};
template<class T>_corundschalter<T>::~_corundschalter(){
};

template<class T>void _corundschalter<T>::schalten(){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listeek.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(listeek.naechstes(oit));
                                if(listezk.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(listezk.naechstes(oit));
                                if(listelk.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(listelk.naechstes(oit));
};
template<class T>void _corundschalter<T>::schalten(bool b){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listeek.anfang(oit))do{
                                 oit->objekt()->schalten(b);
                                }while(listeek.naechstes(oit));
                                if(listezk.anfang(oit))do{
                                 oit->objekt()->schalten(b);
                                }while(listezk.naechstes(oit));
                                if(listelk.anfang(oit))do{
                                 oit->objekt()->schalten(b);
                                }while(listelk.naechstes(oit));
};
template<class T>void _corundschalter<T>::schaltenerstkontakt(){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listeek.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(listeek.naechstes(oit));
};
template<class T>void _corundschalter<T>::schaltenzwischenkontakt(){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listezk.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(listezk.naechstes(oit));
};
template<class T>void _corundschalter<T>::schaltenletztkontakt(){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listelk.anfang(oit))do{
                                 oit->objekt()->schalten();
                                }while(listelk.naechstes(oit));
};                
template<class T>void _corundschalter<T>::schaltenerstkontakt(bool b){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listeek.anfang(oit))do{
                                 oit->objekt()->schalten(b);
                                }while(listeek.naechstes(oit));
};
template<class T>void _corundschalter<T>::schaltenzwischenkontakt(bool b){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listezk.anfang(oit))do{
                                 oit->objekt()->schalten(b);
                                }while(listezk.naechstes(oit));
};
template<class T>void _corundschalter<T>::schaltenletztkontakt(bool b){
                                _listenknoten<_corundschaltkopplung>*oit;
                                if(listelk.anfang(oit))do{
                                 oit->objekt()->schalten(b);
                                }while(listelk.naechstes(oit));
};   


template<class T>void _corundschalter<T>::kollision(_kollidierbar*k,_polygon*p){
                                _corundkugel*t=0;
                                t=dynamic_cast<_corundkugel*>(k);
                                if(t){
                                 if(gedrueckt==false){
                                  gedrueckt=true;
                                  schaltenerstkontakt();
                                 };
                                };
};                                
template<class T>void _corundschalter<T>::zeichnen(_grafik*g){
                                _netz*nsk;
                                _licht<_tg,_to>*lit;
                                _netz*netz=dynamic_cast<_netz*>(this);
                                if(netz){
                                 _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                  _weltdebugpfeil*wp=new _weltdebugpfeil(welt->welt,netz->mitte(),_vektor3<_tg>(0,0,0),0.1,0.05,_vektor4<_to>(1,1,0,1));
                                  _weltdebugtext*wt=new _weltdebugtext(welt->welt,"Erstkontakt",_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,0.3),_vektor4<_to>(1,1,0,1));
                                  _listenknoten<_corundschaltkopplung>*oit;
                                 
                                  wp->farbe(_vektor4<_to>(1,1,0,1));
                                  wt->farbe(_vektor4<_to>(1,1,0,1));
                                  wt->text("Erstkontakt");
                                  if(listeek.anfang(oit))do{
                                   nsk=0;
                                   lit=0;
                                   nsk=dynamic_cast<_netz*>(oit->objekt());
                                   if(nsk) wp->ort(1,nsk->mitte()); else{
                                    lit=dynamic_cast<_licht<_tg,_to>* >(oit->objekt());
                                    if(lit) wp->ort(1,lit->ort());
                                   };
                                   if(nsk||lit){
                                    wp->zeichnen(g);
                                    wt->ort((wp->ort(0)+wp->ort(1))*0.5);
                                    wt->zeichnen(g);
                                   };
                                  }while(listeek.naechstes(oit));
                                
                                  wp->farbe(_vektor4<_to>(1,1,0,1));
                                  wt->farbe(_vektor4<_to>(1,1,0,1));
                                  wt->text("Zwischenkontakt");
                                  if(listezk.anfang(oit))do{
                                   nsk=0;
                                   lit=0;
                                   nsk=dynamic_cast<_netz*>(oit->objekt());
                                   if(nsk) wp->ort(1,nsk->mitte()); else{
                                    lit=dynamic_cast<_licht<_tg,_to>* >(oit->objekt());
                                    if(lit) wp->ort(1,lit->ort());
                                   };
                                   if(nsk||lit){
                                    wp->ort(1,nsk->mitte());
                                    wp->zeichnen(g);
                                    wt->ort((wp->ort(0)+wp->ort(1))*0.5);
                                    wt->zeichnen(g);
                                   };
                                  }while(listezk.naechstes(oit));
                                 
                                  wp->farbe(_vektor4<_to>(1,1,0,1));
                                  wt->farbe(_vektor4<_to>(1,1,0,1));
                                  wt->text("Letztkontakt");
                                  if(listelk.anfang(oit))do{
                                   nsk=0;
                                   lit=0;
                                   nsk=dynamic_cast<_netz*>(oit->objekt());
                                   if(nsk) wp->ort(1,nsk->mitte()); else{
                                    lit=dynamic_cast<_licht<_tg,_to>* >(oit->objekt());
                                    if(lit) wp->ort(1,lit->ort());
                                   };
                                   if(nsk||lit){
                                    wp->ort(1,nsk->mitte());
                                    wp->zeichnen(g);
                                    wt->ort((wp->ort(0)+wp->ort(1))*0.5);
                                    wt->zeichnen(g);
                                   };
                                  }while(listelk.naechstes(oit));
                                
                                  delete wt;
                                  delete wp;
                                 //};
                                };
};

template<class T>char _corundschalter<T>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<T>*sd){
                                char r=1;
                                unsigned int i;
                                r^=sd->ladenwert(gedrueckt);
                                r^=sd->ladenwert(anzahlzeigerek);
                                for(i=0;i<anzahlzeigerek;i++) r^=sd->ladenassoziation();
                                r^=sd->ladenwert(anzahlzeigerzk);
                                for(i=0;i<anzahlzeigerzk;i++) r^=sd->ladenassoziation();
                                r^=sd->ladenwert(anzahlzeigerlk);
                                for(i=0;i<anzahlzeigerlk;i++) r^=sd->ladenassoziation();   
                                return(r);
};
template<class T>void _corundschalter<T>::speichern(_speicherbardynamisch<T>*sd){
                                _zeichenkette<char> tn;
                                sd->speichernwert(gedrueckt);
                                _listenknoten<_corundschaltkopplung>*it;
                                sd->speichernwert(listeek.anzahl());
                                if(listeek.anfang(it))do{
                                 sd->speichernwertroh(it->objekt()->dateiqualifikation);
                                }while(listeek.naechstes(it));
                                sd->speichernwert(listezk.anzahl());
                                if(listezk.anfang(it))do{
                                 sd->speichernwertroh(it->objekt()->dateiqualifikation);
                                }while(listezk.naechstes(it));
                                sd->speichernwert(listelk.anzahl());
                                if(listelk.anfang(it))do{
                                 sd->speichernwertroh(it->objekt()->dateiqualifikation);
                                }while(listelk.naechstes(it));
};
template<class T>char _corundschalter<T>::assoziieren(_speicherbardynamisch<T>*sd){
                                unsigned int i;
                                _zeichenkette<char> name;
                                _corundschaltkopplung*corundschaltkopplung=0;
                                _corundschaltkopplung*it;
                                listeek.aushaengen();
                                listezk.aushaengen();
                                listelk.aushaengen();
                                for(i=0;i<anzahlzeigerek;i++) {
                                 corundschaltkopplung=0;
                                 name=sd->assoziation();
                                 L->schreiben("NAAAAAAAAAAAME==",name);
                                 if(name!="0"){
                                  if(welt->_listebasis<_corundschaltkopplung>::anfang(it))do{
                                   if(name==it->dateiqualifikation) {corundschaltkopplung=it;};
                                  }while(welt->_listebasis<_corundschaltkopplung>::naechstes(it));
                                 };
                                 if(corundschaltkopplung)listeek.einhaengen(corundschaltkopplung);
                                };
                                for(i=0;i<anzahlzeigerzk;i++) {
                                 corundschaltkopplung=0;
                                 name=sd->assoziation();
                                 if(name!="0"){
                                  if(welt->_listebasis<_corundschaltkopplung>::anfang(it))do{
                                   if(name==it->dateiqualifikation) corundschaltkopplung=it;
                                  }while(welt->_listebasis<_corundschaltkopplung>::naechstes(it));
                                 };
                                 if(corundschaltkopplung)listezk.einhaengen(corundschaltkopplung);
                                };
                                for(i=0;i<anzahlzeigerlk;i++) {
                                 corundschaltkopplung=0;
                                 name=sd->assoziation();
                                 if(name!="0"){
                                  if(welt->_listebasis<_corundschaltkopplung>::anfang(it))do{
                                   if(name==it->dateiqualifikation) corundschaltkopplung=it;
                                  }while(welt->_listebasis<_corundschaltkopplung>::naechstes(it));
                                 };
                                 if(corundschaltkopplung)listelk.einhaengen(corundschaltkopplung);
                                };
                                return(1);
};
template<class T>void _corundschalter<T>::schaltkopplungwahl(_corundschaltkopplung*os,int){
                                if(os){
                                 if(modus==0)listeek.einhaengenunredundant(os);
                                 if(modus==1)listezk.einhaengenunredundant(os);
                                 if(modus==2)listelk.einhaengenunredundant(os);
                                };
};
template<class T>void _corundschalter<T>::beiknopfausfuehrenek(_guiereignisdaten*ep){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                if(hauptfenster) {
                                 modus=0;
                                 dialogschaltkopplungswahl->corundschalter(this);
                                 dialogschaltkopplungswahl->zeigen();
                                };
};
template<class T>void _corundschalter<T>::beiknopfausfuehrenzk(_guiereignisdaten*ep){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                if(hauptfenster) {
                                 modus=1;
                                 dialogschaltkopplungswahl->corundschalter(this);
                                 dialogschaltkopplungswahl->zeigen();
                                };
};
template<class T>void _corundschalter<T>::beiknopfausfuehrenlk(_guiereignisdaten*ep){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                if(hauptfenster) {
                                 modus=2;
                                 dialogschaltkopplungswahl->corundschalter(this);
                                 dialogschaltkopplungswahl->zeigen();
                                };
};
template<class T>void _corundschalter<T>::beiknopfloeschenek(_guiereignisdaten*){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                listeek.aushaengen();
                                hauptfenster->zeichnen();
};
template<class T>void _corundschalter<T>::beiknopfloeschenzk(_guiereignisdaten*){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                listezk.aushaengen();
                                hauptfenster->zeichnen();
};
template<class T>void _corundschalter<T>::beiknopfloeschenlk(_guiereignisdaten*){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                listelk.aushaengen();
                                hauptfenster->zeichnen();
};
template<class T>void _corundschalter<T>::beiknopfloeschenletztenek(_guiereignisdaten*){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                _listenknoten<_corundschaltkopplung>*lnosit;
                                if(listeek.anfang(lnosit)){
                                 lnosit=lnosit->vorheriges();
                                 delete lnosit;
                                };
                                hauptfenster->zeichnen();
};
template<class T>void _corundschalter<T>::beiknopfloeschenletztenzk(_guiereignisdaten*){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                _listenknoten<_corundschaltkopplung>*lnosit;
                                if(listezk.anfang(lnosit)){
                                 lnosit=lnosit->vorheriges();
                                 delete lnosit;
                                };
                                hauptfenster->zeichnen();
};
template<class T>void _corundschalter<T>::beiknopfloeschenletztenlk(_guiereignisdaten*){
                                _hauptfenster*hauptfenster=0;T*konkret=dynamic_cast<T*>(this);if(konkret) hauptfenster=konkret->hauptfenster;
                                _listenknoten<_corundschaltkopplung>*lnosit;
                                if(listelk.anfang(lnosit)){
                                 lnosit=lnosit->vorheriges();
                                 delete lnosit;
                                };
                                hauptfenster->zeichnen();
};
template<class T>void _corundschalter<T>::einhaengendialog(_dynamischerdialog*d){
                                d->addierensektion(L"Corund Schalter");
                                d->sektion(L"Corund Schalter")->offen(true);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Erstkontakt : Neuen Zeiger",L"holen",this,&_corundschalter<T>::beiknopfausfuehrenek);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Erstkontakt : Letzten Zeiger",L"löschen",this,&_corundschalter<T>::beiknopfloeschenletztenek);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Erstkontakt : Alle Zeiger",L"löschen",this,&_corundschalter<T>::beiknopfloeschenek);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Zwischenkontakt : Neuen Zeiger",L"holen",this,&_corundschalter<T>::beiknopfausfuehrenzk);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Zwischenkontakt : Letzten Zeiger",L"löschen",this,&_corundschalter<T>::beiknopfloeschenletztenzk);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Zwischenkontakt : Alle Zeiger",L"löschen",this,&_corundschalter<T>::beiknopfloeschenzk);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Letztkontakt : Neuen Zeiger",L"holen",this,&_corundschalter<T>::beiknopfausfuehrenlk);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Letztkontakt : Letzten Zeiger",L"löschen",this,&_corundschalter<T>::beiknopfloeschenletztenlk);
                                d->einhaengenknopf<_corundschalter<T> >(L"Corund Schalter",L"Bei Letztkontakt : Alle Zeiger",L"löschen",this,&_corundschalter<T>::beiknopfloeschenlk);
};
template<class T>void _corundschalter<T>::auslesendialog(_dynamischerdialog*d){
};
#endif