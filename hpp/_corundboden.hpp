//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundboden.hpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#ifndef _corundboden_hpp_included
#define _corundboden_hpp_included


class _corundboden;
class _corundbodennormal;
class _corundbodenschalter;
class _corundbodeninvers;
class _corundbodenweltraum;
class _corundbodeneis;
class _corundbodensand;
class _corundbodenschnee;
class _corundbodenwiese;
class _corundbodenwasser;
class _corundbodensumpf;
class _corundbodenlava;
class _corundbodenbeschleunigung;
class _corundbodengradienz;
class _corundbodentransport;
class _corundbodentotenkopf;


#include "../hpp/_corund.hpp"
#include "../hpp/_corundfigur.hpp"
#include <_weltkollision.hpp>
#include <_weltmechanik.hpp>
#include <_bild.hpp>
#include "../../oxydeditor/hpp/_corundeditor.hpp"
#include "../hpp/_corundschalter.hpp"

//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N
//******************************************************************************************************************************************************************************************************
class _corundboden:
public _listenknotenbasis<_corundboden>,
public _netz,
public _kollisionskopplung,
public _corundschaltkopplung,
public _basis::_speicherbarargument<_corundboden>,
public _listebasis<_sprite>,
public _listebasis<_partikel>,
public _listebasis<_licht<_tg,_to> >,
public _listebasis<_gravitation<_tg> >,
public virtual _editierbar{
        public:
        using _listebasis<_partikel>             ::anfang;
        using _listebasis<_sprite >              ::anfang;
        using _listebasis<_licht<_tg,_to> >      ::anfang;
        using _listebasis<_gravitation<_tg> >    ::anfang;
        using _listebasis<_partikel>             ::naechstes;
        using _listebasis<_sprite >              ::naechstes;
        using _listebasis<_licht<_tg,_to> >      ::naechstes;
        using _listebasis<_gravitation<_tg> >    ::naechstes;
        using _listebasis<_partikel>             ::vorheriges;
        using _listebasis<_sprite >              ::vorheriges;
        using _listebasis<_licht<_tg,_to> >      ::vorheriges;
        using _listebasis<_gravitation<_tg> >    ::vorheriges;
        
        public:
                _corundboden(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundboden();
                virtual void nachbereitenkonstruktion(); 
                virtual void initialisieren(); 
                virtual void kollision(_kollidierbar*,_polygon*);                
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                virtual void schalten();
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundboden>*);
                void speichern(_speicherbardynamisch<_corundboden>*);
                char assoziieren(_speicherbardynamisch<_corundboden>*);
                //editierbar
                virtual void netzwahl(_netz*,int);
                virtual void figurwahl(_corundfigur*,int);
                virtual void knotenwahl(_corundknoten*,int);
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);                
        public:
                _corundwelt*welt;
                _corundton*ton;
                _vektor3<_tg> ort;
                _vektor3<_tg> ebene0;
                _vektor3<_tg> ebene1;
                _hauptfenster*hauptfenster;
                int markierung;

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N N O R M A L 
//******************************************************************************************************************************************************************************************************
class _corundbodennormal:public _corundboden,public _basis::_speicherbarargument<_corundbodennormal>, public virtual _editierbar{
        public:
                _corundbodennormal(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodennormal();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodennormal>*);
                void speichern(_speicherbardynamisch<_corundbodennormal>*);
                char assoziieren(_speicherbardynamisch<_corundbodennormal>*);
                //editierbar
           
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S C H A L T E R 
//******************************************************************************************************************************************************************************************************
class _corundbodenschalter:
 public _corundboden,
 public _corundschalter<_corundbodenschalter>,
 public _basis::_speicherbarargument<_corundbodenschalter>, 
 public virtual _editierbar{
        public:
                _corundbodenschalter(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodenschalter();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();//alles schalten was da ist
                virtual void schaltenerstkontakt();
                virtual void schaltenzwischenkontakt();
                virtual void schaltenletztkontakt();
                virtual void zeichnen(_grafik*);//editorzeichnung                
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodenschalter>*);
                void speichern(_speicherbardynamisch<_corundbodenschalter>*);
                char assoziieren(_speicherbardynamisch<_corundbodenschalter>*);
                //editierbar
                /*virtual void netzwahl(_netz*,int);
                void beiknopfausfuehrenek(_guiereignisdaten*);
                void beiknopfausfuehrenzk(_guiereignisdaten*);
                void beiknopfausfuehrenlk(_guiereignisdaten*);
                void beiknopfloeschenletztenek(_guiereignisdaten*);
                void beiknopfloeschenletztenzk(_guiereignisdaten*);
                void beiknopfloeschenletztenlk(_guiereignisdaten*);
                void beiknopfloeschenek(_guiereignisdaten*);                
                void beiknopfloeschenzk(_guiereignisdaten*);                
                void beiknopfloeschenlk(_guiereignisdaten*); */               
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
/*        public:
                _liste<_corundstein> listeek;
                _liste<_corundstein> listezk;
                _liste<_corundstein> listelk;
        private:                
                //speichern hilfselemente
                unsigned int anzahlzeigerek;  
                unsigned int anzahlzeigerzk;  
                unsigned int anzahlzeigerlk;  
                bool gedrueckt;//speichern ! nicht editeren!    
                int modus;//nur interne edition    
  */                    
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N I N V E R S
//******************************************************************************************************************************************************************************************************
class _corundbodeninvers:public _corundboden,public _basis::_speicherbarargument<_corundbodeninvers>, public virtual _editierbar{
        public:
                _corundbodeninvers(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodeninvers();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void nachbereitenkonstruktion(); 
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodeninvers>*);
                void speichern(_speicherbardynamisch<_corundbodeninvers>*);
                char assoziieren(_speicherbardynamisch<_corundbodeninvers>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N W E L T R A U M 
//******************************************************************************************************************************************************************************************************
class _corundbodenweltraum:public _corundboden,public _basis::_speicherbarargument<_corundbodenweltraum>, public virtual _editierbar{
        public:
                _corundbodenweltraum(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodenweltraum();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void nachbereitenkonstruktion(); 
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodenweltraum>*);
                void speichern(_speicherbardynamisch<_corundbodenweltraum>*);
                char assoziieren(_speicherbardynamisch<_corundbodenweltraum>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N E I S 
//******************************************************************************************************************************************************************************************************
class _corundbodeneis:public _corundboden,public _basis::_speicherbarargument<_corundbodeneis>, public virtual _editierbar{
        public:
                _corundbodeneis(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodeneis();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void nachbereitenkonstruktion(); 
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodeneis>*);
                void speichern(_speicherbardynamisch<_corundbodeneis>*);
                char assoziieren(_speicherbardynamisch<_corundbodeneis>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S A N D
//******************************************************************************************************************************************************************************************************
class _corundbodensand:public _corundboden,public _basis::_speicherbarargument<_corundbodensand>, public virtual _editierbar{
        public:
                _corundbodensand(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodensand();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void nachbereitenkonstruktion(); 
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodensand>*);
                void speichern(_speicherbardynamisch<_corundbodensand>*);
                char assoziieren(_speicherbardynamisch<_corundbodensand>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S C H N E E
//******************************************************************************************************************************************************************************************************
class _corundbodenschnee:public _corundboden,public _basis::_speicherbarargument<_corundbodenschnee>, public virtual _editierbar{
        public:
                _corundbodenschnee(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodenschnee();
                // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void nachbereitenkonstruktion(); 
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodenschnee>*);
                void speichern(_speicherbardynamisch<_corundbodenschnee>*);
                char assoziieren(_speicherbardynamisch<_corundbodenschnee>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N W I E S E
//******************************************************************************************************************************************************************************************************
class _corundbodenwiese:public _corundboden,public _basis::_speicherbarargument<_corundbodenwiese>, public virtual _editierbar{
        public:
                _corundbodenwiese(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodenwiese();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void nachbereitenkonstruktion(); 
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodenwiese>*);
                void speichern(_speicherbardynamisch<_corundbodenwiese>*);
                char assoziieren(_speicherbardynamisch<_corundbodenwiese>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N W A S S E R 
//******************************************************************************************************************************************************************************************************
class _corundbodenwasser:public _corundboden,public _basis::_speicherbarargument<_corundbodenwasser>, public virtual _editierbar{
        public:
                _corundbodenwasser(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodenwasser();
                virtual void nachbereitenkonstruktion(); 
                virtual void initialisieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                bool innerhalb(_corundkugel*ck);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodenwasser>*);
                void speichern(_speicherbardynamisch<_corundbodenwasser>*);
                char assoziieren(_speicherbardynamisch<_corundbodenwasser>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _liste<_corundkugel> geschnitten;//nicht editieren, nicht speichern
                _vektor2<_tg> texturvektor;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N S U M P F 
//******************************************************************************************************************************************************************************************************
class _corundbodensumpf:public _corundboden,public _basis::_speicherbarargument<_corundbodensumpf>, public virtual _editierbar{
        public:
                _corundbodensumpf(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodensumpf();
                virtual void nachbereitenkonstruktion(); 
                virtual void initialisieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                bool innerhalb(_corundkugel*ck);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodensumpf>*);
                void speichern(_speicherbardynamisch<_corundbodensumpf>*);
                char assoziieren(_speicherbardynamisch<_corundbodensumpf>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _liste<_corundkugel> geschnitten;//nicht editieren, nicht speichern
                _vektor2<_tg> texturvektor;

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N L A V A 
//******************************************************************************************************************************************************************************************************
class _corundbodenlava:public _corundboden,public _basis::_speicherbarargument<_corundbodenlava>, public virtual _editierbar{
        public:
                _corundbodenlava(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodenlava();
                virtual void nachbereitenkonstruktion(); 
                virtual void initialisieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                bool innerhalb(_corundkugel*ck);                
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodenlava>*);
                void speichern(_speicherbardynamisch<_corundbodenlava>*);
                char assoziieren(_speicherbardynamisch<_corundbodenlava>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _liste<_corundkugel> geschnitten;//nicht editieren, nicht speichern
                _vektor2<_tg> texturvektor;

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N B E S C H L E U N I G U N G 
//******************************************************************************************************************************************************************************************************
class _corundbodenbeschleunigung:public _corundboden,public _basis::_speicherbarargument<_corundbodenbeschleunigung>, public virtual _editierbar{
        public:
                _corundbodenbeschleunigung(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodenbeschleunigung();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodenbeschleunigung>*);
                void speichern(_speicherbardynamisch<_corundbodenbeschleunigung>*);
                char assoziieren(_speicherbardynamisch<_corundbodenbeschleunigung>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _vektor3<_tg> vektor;
                _vektor2<_tg> texturvektor;
                bool eingeschaltet;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N G R A D I E N Z 
//******************************************************************************************************************************************************************************************************
class _corundbodengradienz:public _corundboden,public _basis::_speicherbarargument<_corundbodengradienz>, public virtual _editierbar{
        public:
                _corundbodengradienz(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodengradienz();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodengradienz>*);
                void speichern(_speicherbardynamisch<_corundbodengradienz>*);
                char assoziieren(_speicherbardynamisch<_corundbodengradienz>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N T R A N S P O R T 
//******************************************************************************************************************************************************************************************************
class _corundbodentransport:public _corundboden,public _basis::_speicherbarargument<_corundbodentransport>, public virtual _editierbar{
        public:
                _corundbodentransport(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodentransport();
               // virtual void kollision(_kollidierbar*,_polygon*);
                void setzenvektor(const _vektor3<_tg>&);
                virtual void schalten();
                virtual void animieren();
                void bewegen(bool);
                virtual void zeichnen(_grafik*);//editorzeichnung   
                virtual void initialisieren(); 
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodentransport>*);
                void speichern(_speicherbardynamisch<_corundbodentransport>*);
                char assoziieren(_speicherbardynamisch<_corundbodentransport>*);
                //editierbar
                virtual void knotenwahl(_corundknoten*,int);
                void beiknopfausfuehren(_guiereignisdaten*);
                void beiknopfloeschenletzten(_guiereignisdaten*);
                void beiknopfloeschen(_guiereignisdaten*);                
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _vektor3<_tg> vektor;//momentaner vektor, nur speichern
                _vektor3<_tg> deltavektor;
                bool eingeschaltet;
                _tg kraftwirkung;
                int status;//0= ruhe, wartezeit, 1=bewegung
                int wartezeit;
                _tg schritt;//m/frame
                _tg iteratort;
                _liste<_corundknoten> listeck;
                _kurvehermite3<_tg> kurve;//dynamisch geladen, nicht speichern, nicht editieren
        private:
                unsigned int anzahlzeiger;    
                unsigned int iteratork;    
                int zaehler;
                _vektor3<_tg> altort;
                _listenknoten<_corundknoten>*knotenit;        
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D B O D E N T O T E N K O P F 
//******************************************************************************************************************************************************************************************************
class _corundbodentotenkopf:public _corundboden,public _basis::_speicherbarargument<_corundbodentotenkopf>, public virtual _editierbar{
        public:
                _corundbodentotenkopf(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&va,const _vektor3<_tg>&vb);
                virtual ~_corundbodentotenkopf();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundbodentotenkopf>*);
                void speichern(_speicherbardynamisch<_corundbodentotenkopf>*);
                char assoziieren(_speicherbardynamisch<_corundbodentotenkopf>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg staerke;  
                int zaehler;
                int status;              
};
#endif
