//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundobjekt.hpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
class _corundobjekt;
class _corundobjektersatz;
class _corundobjektschluessela;
class _corundobjektbombe;
class _corundobjektdynamit;
class _corundobjektmine;
class _corundobjektsteinpille;
class _corundobjektalkohol;
class _corundobjektbungeeseil;
class _corundobjektschere;
class _corundobjektzettel;
class _corundobjektfallschirm;
class _corundobjektzauberstab;
class _corundobjekttriebwerk;
class _corundobjektgesundheit; 
class _corundobjektreisszwecke;
class _corundobjekthammer;
class _corundobjektgasbrenner;
class _corundobjektschutzschild;
class _corundobjektschneidbrenner;
class _corundobjektschwarzesloch;
class _corundobjektmagnet;
class _corundobjektpresslufthammer;
class _corundobjektteleporter;
class _corundobjektgleitmittel;
class _corundobjektgeld;
class _corundobjektsprungfeder;
class _corundobjektskalierer;
class _corundobjektpflanze;
class _corundobjektobst;
class _corundobjektdematerialisierung;
class _corundobjektdevisualisierung;
class _corundobjektinsektenspray;
class _corundobjektfeuerloescher;
class _corundobjektsummer;
class _corundobjektblinker;
class _corundobjektbatterie;
class _corundobjektpinsel;
class _corundobjektbesen;
class _corundobjektlampe;
class _corundobjektkerze;
class _corundobjektgewicht;
class _corundobjektgasmaske;
class _corundobjektschutzhelm;
class _corundobjektspritze;

#ifndef _corundobjekt_hpp_included
#define _corundobjekt_hpp_included

//class _corundton;

#include "../hpp/_corund.hpp"
#include "../hpp/_corundfigur.hpp"
#include <_weltkollision.hpp>
#include <_weltmechanik.hpp>
#include "../hpp/_bild.hpp"
#include "../../oxydeditor/hpp/_corundeditor.hpp"
#include "../hpp/_corundschalter.hpp"
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T 
//******************************************************************************************************************************************************************************************************
class _corundobjekt:
public _listenknotenbasis<_corundobjekt>,
public _netz,
public _kollisionskopplung,
public _corundschaltkopplung,
public _basis::_speicherbarargument<_corundobjekt>,
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
                _corundobjekt(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjekt();
                virtual void nachbereitenkonstruktion(); 
                virtual void initialisieren(); 
                virtual void kollision(_kollidierbar*,_polygon*);                
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                virtual void schalten();
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                virtual void aufsammeln();
                virtual void ablegen(const _vektor3<_tg>&o);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjekt>*);
                void speichern(_speicherbardynamisch<_corundobjekt>*);
                char assoziieren(_speicherbardynamisch<_corundobjekt>*);
                //editierbar
                virtual void knotenwahl(_corundknoten*,int);
                virtual void figurwahl(_corundfigur*,int);
                virtual void netzwahl(_netz*,int);                
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);                
        public:
                _corundwelt*welt;
                _corundton*ton;
                _vektor3<_tg> ort;
                _hauptfenster*hauptfenster;
                int markierung;
                bool iminventar;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T E R S A T Z 
//******************************************************************************************************************************************************************************************************
class _corundobjektersatz:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektersatz>, public virtual _editierbar{
        public:
                _corundobjektersatz(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektersatz();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektersatz>*);
                void speichern(_speicherbardynamisch<_corundobjektersatz>*);
                char assoziieren(_speicherbardynamisch<_corundobjektersatz>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H L U E S S E L A 
//******************************************************************************************************************************************************************************************************
class _corundobjektschluessela:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektschluessela>, public virtual _editierbar{
        public:
                _corundobjektschluessela(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektschluessela();
                virtual void nachbereitenkonstruktion();
                virtual void animieren();
              //  virtual void ablegen(const _vektor3<_tg>&o);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektschluessela>*);
                void speichern(_speicherbardynamisch<_corundobjektschluessela>*);
                char assoziieren(_speicherbardynamisch<_corundobjektschluessela>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                unsigned int schloss;
                _vektor3<_tg> verschiebung;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B O M B E
//******************************************************************************************************************************************************************************************************
class _corundobjektbombe:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektbombe>, public virtual _editierbar{
        public:
                _corundobjektbombe(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektbombe();
                virtual void nachbereitenkonstruktion();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void kollision(_kollidierbar*,_polygon*); 
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                virtual void schalten();
                virtual void ablegen(const _vektor3<_tg>&o);
                virtual void werfen(const _vektor3<_tg>&o,const _vektor3<_tg>&v);
                virtual void aufsammeln();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektbombe>*);
                void speichern(_speicherbardynamisch<_corundobjektbombe>*);
                char assoziieren(_speicherbardynamisch<_corundobjektbombe>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                bool gezuendet;
                int brenndauer;
                int zaehler;
                _tg staerke;
                _tg radius;
                bool wurfmodus;
                _kollidierbarkugel*kk;
                bool tauchen;

                _partikelquellesprite*pqzuendschnurr;
                _partikelquellesprite*pqdetonation;
                _corundton*ton;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T D Y N A M I T 
//******************************************************************************************************************************************************************************************************
class _corundobjektdynamit:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektdynamit>, public virtual _editierbar{
        public:
                _corundobjektdynamit(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektdynamit();
                virtual void nachbereitenkonstruktion();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void kollision(_kollidierbar*,_polygon*); 
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                virtual void schalten();
                virtual void ablegen(const _vektor3<_tg>&o);
                virtual void aufsammeln();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektdynamit>*);
                void speichern(_speicherbardynamisch<_corundobjektdynamit>*);
                char assoziieren(_speicherbardynamisch<_corundobjektdynamit>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                bool gezuendet;
                int brenndauer;
                int zaehler;
                _tg staerke;
                _tg radius;
                _partikelquellesprite*pqzuendschnurr;
                _partikelquellesprite*pqdetonation;
                _corundton*ton;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T M I N E 
//******************************************************************************************************************************************************************************************************
class _corundobjektmine:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektmine>, public virtual _editierbar{
        public:
                _corundobjektmine(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektmine();
                virtual void nachbereitenkonstruktion();
               // virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void kollision(_kollidierbar*,_polygon*); 
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                virtual void schalten();
                virtual void ablegen(const _vektor3<_tg>&o);
                virtual void aufsammeln();
                void anlegenlampe();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektmine>*);
                void speichern(_speicherbardynamisch<_corundobjektmine>*);
                char assoziieren(_speicherbardynamisch<_corundobjektmine>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                bool gezuendet;
                int sensorverzoegerung;
                _tg sensordistanz;
                int zaehler;
                _tg staerke;
                _tg radius;
                _partikelquellesprite*pqdetonation;
                _corundton*ton;
                _sprite*lampe;
                _tg lampeanim;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S T E I N P I L L E
//******************************************************************************************************************************************************************************************************
class _corundobjektsteinpille:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektsteinpille>, public virtual _editierbar{
        public:
                _corundobjektsteinpille(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektsteinpille();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektsteinpille>*);
                void speichern(_speicherbardynamisch<_corundobjektsteinpille>*);
                char assoziieren(_speicherbardynamisch<_corundobjektsteinpille>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T A L K O H O L
//******************************************************************************************************************************************************************************************************
class _corundobjektalkohol:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektalkohol>, public virtual _editierbar{
        public:
                _corundobjektalkohol(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektalkohol();
                virtual void kollision(_kollidierbar*,_polygon*); 
                virtual void animieren();

                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektalkohol>*);
                void speichern(_speicherbardynamisch<_corundobjektalkohol>*);
                char assoziieren(_speicherbardynamisch<_corundobjektalkohol>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg menge;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B U N G E E S E I L 
//******************************************************************************************************************************************************************************************************
class _corundobjektbungeeseil:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektbungeeseil>, public virtual _editierbar{
        public:
                _corundobjektbungeeseil(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektbungeeseil();
                virtual void nachbereitenkonstruktion();
                virtual void initialisieren(); 
                virtual void animieren();
                virtual void ablegen(const _vektor3<_tg>&o);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektbungeeseil>*);
                void speichern(_speicherbardynamisch<_corundobjektbungeeseil>*);
                char assoziieren(_speicherbardynamisch<_corundobjektbungeeseil>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg staerke;
                _vektor4<_to> farbe;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H E R E 
//******************************************************************************************************************************************************************************************************
class _corundobjektschere:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektschere>, public virtual _editierbar{
        public:
                _corundobjektschere(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektschere();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektschere>*);
                void speichern(_speicherbardynamisch<_corundobjektschere>*);
                char assoziieren(_speicherbardynamisch<_corundobjektschere>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T Z E T T E L 
//******************************************************************************************************************************************************************************************************
class _corundobjektzettel:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektzettel>, public virtual _editierbar{
        public:
                _corundobjektzettel(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektzettel();
                virtual void nachbereitenkonstruktion();                
                virtual void animieren();
                virtual void ablegen(const _vektor3<_tg>&o);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektzettel>*);
                void speichern(_speicherbardynamisch<_corundobjektzettel>*);
                char assoziieren(_speicherbardynamisch<_corundobjektzettel>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _zeichenkette<char> text;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T F A L L S C H I R M 
//******************************************************************************************************************************************************************************************************
class _corundobjektfallschirm:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektfallschirm>, public virtual _editierbar{
        public:
                _corundobjektfallschirm(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektfallschirm();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektfallschirm>*);
                void speichern(_speicherbardynamisch<_corundobjektfallschirm>*);
                char assoziieren(_speicherbardynamisch<_corundobjektfallschirm>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T Z A U B E R S T A B 
//******************************************************************************************************************************************************************************************************
class _corundobjektzauberstab:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektzauberstab>, public virtual _editierbar{
        public:
                _corundobjektzauberstab(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektzauberstab();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektzauberstab>*);
                void speichern(_speicherbardynamisch<_corundobjektzauberstab>*);
                char assoziieren(_speicherbardynamisch<_corundobjektzauberstab>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T T R I E B W E R K 
//******************************************************************************************************************************************************************************************************
class _corundobjekttriebwerk:public _corundobjekt,public _basis::_speicherbarargument<_corundobjekttriebwerk>, public virtual _editierbar{
        public:
                _corundobjekttriebwerk(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjekttriebwerk();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjekttriebwerk>*);
                void speichern(_speicherbardynamisch<_corundobjekttriebwerk>*);
                char assoziieren(_speicherbardynamisch<_corundobjekttriebwerk>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G E S U N D H E I T 
//******************************************************************************************************************************************************************************************************
class _corundobjektgesundheit:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektgesundheit>, public virtual _editierbar{
        public:
                _corundobjektgesundheit(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektgesundheit();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektgesundheit>*);
                void speichern(_speicherbardynamisch<_corundobjektgesundheit>*);
                char assoziieren(_speicherbardynamisch<_corundobjektgesundheit>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T R E I S S Z W E C K E 
//******************************************************************************************************************************************************************************************************
class _corundobjektreisszwecke:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektreisszwecke>, public virtual _editierbar{
        public:
                _corundobjektreisszwecke(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektreisszwecke();
                void nachbereitenkonstruktion();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektreisszwecke>*);
                void speichern(_speicherbardynamisch<_corundobjektreisszwecke>*);
                char assoziieren(_speicherbardynamisch<_corundobjektreisszwecke>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg bremsfaktor;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T H A M M E R 
//******************************************************************************************************************************************************************************************************
class _corundobjekthammer:public _corundobjekt,public _basis::_speicherbarargument<_corundobjekthammer>, public virtual _editierbar{
        public:
                _corundobjekthammer(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjekthammer();
                virtual void nachbereitenkonstruktion();
                virtual void animieren();
                virtual void ablegen(const _vektor3<_tg>&o);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjekthammer>*);
                void speichern(_speicherbardynamisch<_corundobjekthammer>*);
                char assoziieren(_speicherbardynamisch<_corundobjekthammer>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G A S B R E N N E R 
//******************************************************************************************************************************************************************************************************
class _corundobjektgasbrenner:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektgasbrenner>, public virtual _editierbar{
        public:
                _corundobjektgasbrenner(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektgasbrenner();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektgasbrenner>*);
                void speichern(_speicherbardynamisch<_corundobjektgasbrenner>*);
                char assoziieren(_speicherbardynamisch<_corundobjektgasbrenner>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H U T Z S C H I L D 
//******************************************************************************************************************************************************************************************************
class _corundobjektschutzschild:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektschutzschild>, public virtual _editierbar{
        public:
                _corundobjektschutzschild(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektschutzschild();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektschutzschild>*);
                void speichern(_speicherbardynamisch<_corundobjektschutzschild>*);
                char assoziieren(_speicherbardynamisch<_corundobjektschutzschild>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H N E I D B R E N N E R
//******************************************************************************************************************************************************************************************************
class _corundobjektschneidbrenner:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektschneidbrenner>, public virtual _editierbar{
        public:
                _corundobjektschneidbrenner(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektschneidbrenner();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektschneidbrenner>*);
                void speichern(_speicherbardynamisch<_corundobjektschneidbrenner>*);
                char assoziieren(_speicherbardynamisch<_corundobjektschneidbrenner>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H W A R Z E S L O C H 
//******************************************************************************************************************************************************************************************************
class _corundobjektschwarzesloch:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektschwarzesloch>, public virtual _editierbar{
        public:
                _corundobjektschwarzesloch(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektschwarzesloch();
                virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                virtual void schalten();
                //virtual void ablegen(const _vektor3<_tg>&o);
                //virtual void aufsammeln();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektschwarzesloch>*);
                void speichern(_speicherbardynamisch<_corundobjektschwarzesloch>*);
                char assoziieren(_speicherbardynamisch<_corundobjektschwarzesloch>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                 _gravitation<_tg>*gravitation;
                _partikelquellesprite*pq;
                _tg wx,wy;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T M A G N E T 
//******************************************************************************************************************************************************************************************************
class _corundobjektmagnet:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektmagnet>, public virtual _editierbar{
        public:
                _corundobjektmagnet(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektmagnet();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektmagnet>*);
                void speichern(_speicherbardynamisch<_corundobjektmagnet>*);
                char assoziieren(_speicherbardynamisch<_corundobjektmagnet>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T P R E S S L U F T H A M M E R 
//******************************************************************************************************************************************************************************************************
class _corundobjektpresslufthammer:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektpresslufthammer>, public virtual _editierbar{
        public:
                _corundobjektpresslufthammer(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektpresslufthammer();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektpresslufthammer>*);
                void speichern(_speicherbardynamisch<_corundobjektpresslufthammer>*);
                char assoziieren(_speicherbardynamisch<_corundobjektpresslufthammer>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T T E L E P O R T E R 
//******************************************************************************************************************************************************************************************************
class _corundobjektteleporter:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektteleporter>, public virtual _editierbar{
        public:
                _corundobjektteleporter(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektteleporter();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektteleporter>*);
                void speichern(_speicherbardynamisch<_corundobjektteleporter>*);
                char assoziieren(_speicherbardynamisch<_corundobjektteleporter>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G L E I T M I T T E L 
//******************************************************************************************************************************************************************************************************
class _corundobjektgleitmittel:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektgleitmittel>, public virtual _editierbar{
        public:
                _corundobjektgleitmittel(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektgleitmittel();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektgleitmittel>*);
                void speichern(_speicherbardynamisch<_corundobjektgleitmittel>*);
                char assoziieren(_speicherbardynamisch<_corundobjektgleitmittel>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg gleitfaktor;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G E L D 
//******************************************************************************************************************************************************************************************************
class _corundobjektgeld:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektgeld>, public virtual _editierbar{
        public:
                _corundobjektgeld(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektgeld();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektgeld>*);
                void speichern(_speicherbardynamisch<_corundobjektgeld>*);
                char assoziieren(_speicherbardynamisch<_corundobjektgeld>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S P R U N G F E D E R 
//******************************************************************************************************************************************************************************************************
class _corundobjektsprungfeder:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektsprungfeder>, public virtual _editierbar{
        public:
                _corundobjektsprungfeder(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektsprungfeder();
                virtual void animieren();
                virtual void ablegen(const _vektor3<_tg>&o);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektsprungfeder>*);
                void speichern(_speicherbardynamisch<_corundobjektsprungfeder>*);
                char assoziieren(_speicherbardynamisch<_corundobjektsprungfeder>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg kraft;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S K A L I E R E R
//******************************************************************************************************************************************************************************************************
class _corundobjektskalierer:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektskalierer>, public virtual _editierbar{
        public:
                _corundobjektskalierer(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektskalierer();
                virtual void animieren();
                virtual void ablegen(const _vektor3<_tg>&);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektskalierer>*);
                void speichern(_speicherbardynamisch<_corundobjektskalierer>*);
                char assoziieren(_speicherbardynamisch<_corundobjektskalierer>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg iterator;
                _tg schritt;
                bool weltskalieren;
                _kurvehermite3<_tg> kurve;
                _kurvehermite3<_tg> kamve;
                bool animation;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T P F L A N Z E 
//******************************************************************************************************************************************************************************************************
class _corundobjektpflanze:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektpflanze>, public virtual _editierbar{
        public:
                _corundobjektpflanze(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektpflanze();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektpflanze>*);
                void speichern(_speicherbardynamisch<_corundobjektpflanze>*);
                char assoziieren(_speicherbardynamisch<_corundobjektpflanze>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T O B S T
//******************************************************************************************************************************************************************************************************
class _corundobjektobst:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektobst>, public virtual _editierbar{
        public:
                _corundobjektobst(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektobst();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektobst>*);
                void speichern(_speicherbardynamisch<_corundobjektobst>*);
                char assoziieren(_speicherbardynamisch<_corundobjektobst>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T D E M A T E R I A L I S I E R U N G
//******************************************************************************************************************************************************************************************************
class _corundobjektdematerialisierung:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektdematerialisierung>, public virtual _editierbar{
        public:
                _corundobjektdematerialisierung(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektdematerialisierung();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektdematerialisierung>*);
                void speichern(_speicherbardynamisch<_corundobjektdematerialisierung>*);
                char assoziieren(_speicherbardynamisch<_corundobjektdematerialisierung>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T D E V I S U A L I S I E R U N G
//******************************************************************************************************************************************************************************************************
class _corundobjektdevisualisierung:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektdevisualisierung>, public virtual _editierbar{
        public:
                _corundobjektdevisualisierung(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektdevisualisierung();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektdevisualisierung>*);
                void speichern(_speicherbardynamisch<_corundobjektdevisualisierung>*);
                char assoziieren(_speicherbardynamisch<_corundobjektdevisualisierung>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T I N S E K T E N S P R A Y
//******************************************************************************************************************************************************************************************************
class _corundobjektinsektenspray:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektinsektenspray>, public virtual _editierbar{
        public:
                _corundobjektinsektenspray(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektinsektenspray();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektinsektenspray>*);
                void speichern(_speicherbardynamisch<_corundobjektinsektenspray>*);
                char assoziieren(_speicherbardynamisch<_corundobjektinsektenspray>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T F E U E R L O E S C H E R 
//******************************************************************************************************************************************************************************************************
class _corundobjektfeuerloescher:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektfeuerloescher>, public virtual _editierbar{
        public:
                _corundobjektfeuerloescher(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektfeuerloescher();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektfeuerloescher>*);
                void speichern(_speicherbardynamisch<_corundobjektfeuerloescher>*);
                char assoziieren(_speicherbardynamisch<_corundobjektfeuerloescher>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S U M M E R 
//******************************************************************************************************************************************************************************************************
class _corundobjektsummer:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektsummer>, public virtual _editierbar{
        public:
                _corundobjektsummer(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektsummer();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektsummer>*);
                void speichern(_speicherbardynamisch<_corundobjektsummer>*);
                char assoziieren(_speicherbardynamisch<_corundobjektsummer>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B L I N K E R 
//******************************************************************************************************************************************************************************************************
class _corundobjektblinker:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektblinker>, public virtual _editierbar{
        public:
                _corundobjektblinker(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektblinker();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektblinker>*);
                void speichern(_speicherbardynamisch<_corundobjektblinker>*);
                char assoziieren(_speicherbardynamisch<_corundobjektblinker>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B A T T E R I E 
//******************************************************************************************************************************************************************************************************
class _corundobjektbatterie:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektbatterie>, public virtual _editierbar{
        public:
                _corundobjektbatterie(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektbatterie();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektbatterie>*);
                void speichern(_speicherbardynamisch<_corundobjektbatterie>*);
                char assoziieren(_speicherbardynamisch<_corundobjektbatterie>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T P I N S E L 
//******************************************************************************************************************************************************************************************************
class _corundobjektpinsel:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektpinsel>, public virtual _editierbar{
        public:
                _corundobjektpinsel(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektpinsel();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektpinsel>*);
                void speichern(_speicherbardynamisch<_corundobjektpinsel>*);
                char assoziieren(_speicherbardynamisch<_corundobjektpinsel>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T B E S E N 
//******************************************************************************************************************************************************************************************************
class _corundobjektbesen:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektbesen>, public virtual _editierbar{
        public:
                _corundobjektbesen(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektbesen();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektbesen>*);
                void speichern(_speicherbardynamisch<_corundobjektbesen>*);
                char assoziieren(_speicherbardynamisch<_corundobjektbesen>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T L A M P E 
//******************************************************************************************************************************************************************************************************
class _corundobjektlampe:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektlampe>, public virtual _editierbar{
        public:
                _corundobjektlampe(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektlampe();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektlampe>*);
                void speichern(_speicherbardynamisch<_corundobjektlampe>*);
                char assoziieren(_speicherbardynamisch<_corundobjektlampe>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T K E R Z E 
//******************************************************************************************************************************************************************************************************
class _corundobjektkerze:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektkerze>, public virtual _editierbar{
        public:
                _corundobjektkerze(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektkerze();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektkerze>*);
                void speichern(_speicherbardynamisch<_corundobjektkerze>*);
                char assoziieren(_speicherbardynamisch<_corundobjektkerze>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G E W I C H T 
//******************************************************************************************************************************************************************************************************
class _corundobjektgewicht:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektgewicht>, public virtual _editierbar{
        public:
                _corundobjektgewicht(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektgewicht();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektgewicht>*);
                void speichern(_speicherbardynamisch<_corundobjektgewicht>*);
                char assoziieren(_speicherbardynamisch<_corundobjektgewicht>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T G A S M A S K E 
//******************************************************************************************************************************************************************************************************
class _corundobjektgasmaske:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektgasmaske>, public virtual _editierbar{
        public:
                _corundobjektgasmaske(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektgasmaske();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektgasmaske>*);
                void speichern(_speicherbardynamisch<_corundobjektgasmaske>*);
                char assoziieren(_speicherbardynamisch<_corundobjektgasmaske>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S C H U T Z H E L M 
//******************************************************************************************************************************************************************************************************
class _corundobjektschutzhelm:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektschutzhelm>, public virtual _editierbar{
        public:
                _corundobjektschutzhelm(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektschutzhelm();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektschutzhelm>*);
                void speichern(_speicherbardynamisch<_corundobjektschutzhelm>*);
                char assoziieren(_speicherbardynamisch<_corundobjektschutzhelm>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D O B J E K T S P R I T Z E
//******************************************************************************************************************************************************************************************************
class _corundobjektspritze:public _corundobjekt,public _basis::_speicherbarargument<_corundobjektspritze>, public virtual _editierbar{
        public:
                _corundobjektspritze(_corundwelt*,const _vektor3<_tg>&);
                virtual ~_corundobjektspritze();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundobjektspritze>*);
                void speichern(_speicherbardynamisch<_corundobjektspritze>*);
                char assoziieren(_speicherbardynamisch<_corundobjektspritze>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};


#endif
