//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundstein.hpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
class _corundstein;
class _corundsteincorund;
class _corundsteingummiband;
class _corundsteinschere;
class _corundsteinschieb;
class _corundsteinboulder;
class _corundsteinrotation;
class _corundsteinimpuls;
class _corundsteinelektrisch;
class _corundsteinerdung;
class _corundsteinbeschleunigung;
class _corundsteintotenkopf;
class _corundsteintor;
class _corundsteinschalter;
class _corundsteinkugelgen;
class _corundsteindach;
class _corundsteinflak;
class _corundsteinausgang;
class _corundsteinsenker;
class _corundstrahl;
class _corundsteinlaser;
class _corundsteinspiegel;
class _corundsteinschloss;
class _corundsteinereignis;
class _corundsteingerissen;
class _corundsteinspuck;
class _corundsteintauscher;
class _corundsteinmagnetisch;
class _corundsteindieb;
class _corundsteinfliegengen;
class _corundsteinspinnengen;
class _corundsteinshogun;
class _corundsteinpuzzle;
class _corundsteingas;
class _corundsteinkombinationsschloss;
class _corundsteindrehkreuz;
class _corundsteineinbahn;


#ifndef _corundstein_hpp_included
#define _corundstein_hpp_included
#include "../hpp/_corund.hpp"
#include "../hpp/_corundfigur.hpp"
#include <_weltkollision.hpp>
#include <_weltmechanik.hpp>
#include <_bild.hpp>
#include "../../oxydeditor/hpp/_corundeditor.hpp"
#include "../hpp/_corundschalter.hpp"


class _corundwelt;
class _corundgummiband;
class _corundfeder;
class _corundton;

class _hauptfenster;
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N 
//******************************************************************************************************************************************************************************************************
class _corundstein:
public _netz,
public _kollisionskopplung,
public _corundschaltkopplung,
public _listenknotenbasis<_corundstein>,
public _liste<_corundgummiband>,
public _liste<_corundfeder>,
public _basis::_speicherbarargument<_corundstein>,
public virtual _editierbar{
        public: 
                _corundstein(_corundwelt*);
                _corundstein(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*,bool);
                _corundstein(_corundwelt*,_netz*);
                virtual ~_corundstein();
                virtual void nachbereitenkonstruktion(); 
                virtual void initialisieren(); 
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                virtual void schalten();
                
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundstein>*);
                void speichern(_speicherbardynamisch<_corundstein>*);
                char assoziieren(_speicherbardynamisch<_corundstein>*);
                //editierbar
                void beiknopfverkleinern(_guiereignisdaten*);
                virtual void netzwahl(_netz*,int);
                virtual void figurwahl(_corundfigur*,int);
                virtual void knotenwahl(_corundknoten*,int);
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _corundwelt*welt;
                _hauptfenster*hauptfenster;
              //  _netz*netz;
                _vektor3<_tg> ort;
                _vektor3<_tg> breite;
                int status;
                int zaehler;
                bool verschiebbar;
           
                int markierung;
                _corundton*ton;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N C O R U N D
//******************************************************************************************************************************************************************************************************
class _corundsteincorund:public _corundstein,public _corundschalter<_corundsteincorund>,public _basis::_speicherbarargument<_corundsteincorund>, public virtual _editierbar{
        public:
                _corundsteincorund(_corundwelt*);
                _corundsteincorund(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*,unsigned int );
                virtual ~_corundsteincorund();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                virtual void schalten();
                virtual void schaltenerstkontakt();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteincorund>*);
                void speichern(_speicherbardynamisch<_corundsteincorund>*);
                char assoziieren(_speicherbardynamisch<_corundsteincorund>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                unsigned int symbol;
                int texstatus;
                _corundton*tonpaargeoeffnet;
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N G U M M I B A N D 
//******************************************************************************************************************************************************************************************************
class _corundsteingummiband:public _corundstein,public _basis::_speicherbarargument<_corundsteingummiband>, public virtual _editierbar{
        public:
                _corundsteingummiband(_corundwelt*);
                _corundsteingummiband(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*,_tg );
                virtual ~_corundsteingummiband();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void schalten();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteingummiband>*);
                void speichern(_speicherbardynamisch<_corundsteingummiband>*);
                char assoziieren(_speicherbardynamisch<_corundsteingummiband>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _tg staerke;
                 
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H E R E
//******************************************************************************************************************************************************************************************************
class _corundsteinschere:public _corundstein,public _basis::_speicherbarargument<_corundsteinschere>, public virtual _editierbar{
        public:
                _corundsteinschere(_corundwelt*);
                _corundsteinschere(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*);
                virtual ~_corundsteinschere();
                virtual void kollision(_kollidierbar*,_polygon*);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinschere>*);
                void speichern(_speicherbardynamisch<_corundsteinschere>*);
                char assoziieren(_speicherbardynamisch<_corundsteinschere>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        public:

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H I E B
//******************************************************************************************************************************************************************************************************
class _corundsteinschieb:public _corundstein,public _basis::_speicherbarargument<_corundsteinschieb>, public virtual _editierbar{
        public:
                _corundsteinschieb(_corundwelt*);
                _corundsteinschieb(_corundwelt*,_netz*,_tg);
                _corundsteinschieb(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*,_tg);
                virtual ~_corundsteinschieb();
                virtual void nachbereitenkonstruktion();
                virtual void initialisieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinschieb>*);
                void speichern(_speicherbardynamisch<_corundsteinschieb>*);
                char assoziieren(_speicherbardynamisch<_corundsteinschieb>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        public:
                _tg schiebschwelle;
                _kollidierbarnetztranslation*kn;

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N B O U L D E R 
//******************************************************************************************************************************************************************************************************
class _corundsteinboulder:public _corundstein,public _basis::_speicherbarargument<_corundsteinboulder>, public virtual _editierbar,public _liste<_corundsteinsenker>{
        public:
                _corundsteinboulder(_corundwelt*);
                _corundsteinboulder(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,unsigned int);
                virtual ~_corundsteinboulder();
                virtual void nachbereitenkonstruktion();
                virtual void initialisieren();
                //virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void zeichnen(_grafik*);
                void bewegen();
                void setzentextur(unsigned int);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinboulder>*);
                void speichern(_speicherbardynamisch<_corundsteinboulder>*);
                char assoziieren(_speicherbardynamisch<_corundsteinboulder>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                unsigned int prichtung;
                unsigned int zeitzaehler;
                unsigned int bildphase;//bildwechsel nach ms
                unsigned int bewegungsphase;//bewegung nach ms
                bool bildgewechselt;
                _textur<_tb>*tex[4][2];
                _kollidierbarkugel*kn;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N R O T A T I O N 
//******************************************************************************************************************************************************************************************************
class _corundsteinrotation:public _corundstein,public _basis::_speicherbarargument<_corundsteinrotation>, public virtual _editierbar{
        public:
                _corundsteinrotation(_corundwelt*);
                _corundsteinrotation(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*,unsigned int);
                virtual ~_corundsteinrotation();
                virtual void initialisieren();
                virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                virtual void zeichnen(_grafik*g);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinrotation>*);
                void speichern(_speicherbardynamisch<_corundsteinrotation>*);
                char assoziieren(_speicherbardynamisch<_corundsteinrotation>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        public:
                unsigned int prichtung;
                _kollidierbarnetztranslation*kn;
                _netz*dach;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N I M P U L S 
//******************************************************************************************************************************************************************************************************
class _corundsteinimpuls:public _corundstein,public _basis::_speicherbarargument<_corundsteinimpuls>, public virtual _editierbar{
        public:
                _corundsteinimpuls(_corundwelt*);
                _corundsteinimpuls(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinimpuls();
                virtual void initialisieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinimpuls>*);
                void speichern(_speicherbardynamisch<_corundsteinimpuls>*);
                char assoziieren(_speicherbardynamisch<_corundsteinimpuls>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        public:
                //_kollidierbarnetztranslation*kn[6]; zu langsam erstmal
                _kollidierbarkugel*kk[6];
                _netz*dach[4];
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E L E K T R I S C H 
//******************************************************************************************************************************************************************************************************
class _corundsteinelektrisch:public _corundstein,public _basis::_speicherbarargument<_corundsteinelektrisch>, public virtual _editierbar{
        public:
                _corundsteinelektrisch(_corundwelt*);
                _corundsteinelektrisch(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinelektrisch();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinelektrisch>*);
                void speichern(_speicherbardynamisch<_corundsteinelektrisch>*);
                char assoziieren(_speicherbardynamisch<_corundsteinelektrisch>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
               
        public:
                _tg ladung;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E R D U N G
//******************************************************************************************************************************************************************************************************
class _corundsteinerdung:public _corundstein,public _basis::_speicherbarargument<_corundsteinerdung>, public virtual _editierbar{
        public:
                _corundsteinerdung(_corundwelt*);
                _corundsteinerdung(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinerdung();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinerdung>*);
                void speichern(_speicherbardynamisch<_corundsteinerdung>*);
                char assoziieren(_speicherbardynamisch<_corundsteinerdung>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N B E S C H L E U N I G U N G 
//******************************************************************************************************************************************************************************************************
class _corundsteinbeschleunigung:public _corundstein,public _basis::_speicherbarargument<_corundsteinbeschleunigung>, public virtual _editierbar{
        public:
                _corundsteinbeschleunigung(_corundwelt*);
                _corundsteinbeschleunigung(_corundwelt*,_netz*,_tg);
                _corundsteinbeschleunigung(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinbeschleunigung();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinbeschleunigung>*);
                void speichern(_speicherbardynamisch<_corundsteinbeschleunigung>*);
                char assoziieren(_speicherbardynamisch<_corundsteinbeschleunigung>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                


        public:
                _tg staerke;
                _corundton*bton;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N T O T E N K O P F 
//******************************************************************************************************************************************************************************************************
class _corundsteintotenkopf:public _corundstein,public _basis::_speicherbarargument<_corundsteintotenkopf>, public virtual _editierbar{
        public:
                _corundsteintotenkopf(_corundwelt*);
                _corundsteintotenkopf(_corundwelt*,_netz*,_tg);
                _corundsteintotenkopf(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteintotenkopf();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteintotenkopf>*);
                void speichern(_speicherbardynamisch<_corundsteintotenkopf>*);
                char assoziieren(_speicherbardynamisch<_corundsteintotenkopf>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
                
        public:
                _tg staerke;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N T O R
//******************************************************************************************************************************************************************************************************
class _corundsteintor:public _corundstein,public _basis::_speicherbarargument<_corundsteintor>, public virtual _editierbar{
        public:
                _corundsteintor(_corundwelt*,_tg,_tg,_tg,unsigned int);
                _corundsteintor(_corundwelt*);
                virtual ~_corundsteintor();
                virtual void einhaengen(_liste<_netz>*,const _vektor3<_tg>&); 
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();
                virtual void zeichnen(_grafik*g);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteintor>*);
                void speichern(_speicherbardynamisch<_corundsteintor>*);
                char assoziieren(_speicherbardynamisch<_corundsteintor>*);
                //editierbar
                virtual void netzwahl(_netz*,int);
                void beiknopfneuerichtung(_guiereignisdaten*);
                void beiknopfloeschengruppe(_guiereignisdaten*);
                void beiknopfneuesnetz(_guiereignisdaten*);
                void beiknopfloeschenletztes(_guiereignisdaten*);
                void beiknopfloeschen(_guiereignisdaten*);
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
                
        public:
                unsigned int richtung;
                unsigned int zyklen;
                bool ausgang;
                _netz*tor[4];
                _liste<_liste<_netz> > netze;
                _liste<_vektor3<_tg> > richtungen;
                _dynamischerdialog*dyndialog;
        private:                
                //speichern hilfselemente
                _liste<unsigned int> anzahlnetz;
};/*
class _corundsteintorbuttonloeschen: public GUI ::BCPushButton{
        public:
                _corundsteintorbuttonloeschen(_corundsteintor*,T_String<> GUI::BCWindow*);
        private:
                //void PreProcessEvents(_guiereignisdaten*);                
                void PostProcessEvents(_guiereignisdaten*);    
                _corundsteintor*tor;            
};
class _corundsteintorbuttonloeschenletztes: public GUI ::BCPushButton{
        public:
                _corundsteintorbuttonloeschenletztes(_corundsteintor*,GUI::BCWindow*);
        private:
                //void PreProcessEvents(_guiereignisdaten*);                
                void PostProcessEvents(_guiereignisdaten*);                
                _corundsteintor*tor;
};
*/
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H A L T E R
//******************************************************************************************************************************************************************************************************
class _corundsteinschalter:
public _corundstein,
public _corundschalter<_corundsteinschalter>,
public _basis::_speicherbarargument<_corundsteinschalter>, 
public virtual _editierbar{
        public:
                _corundsteinschalter(_corundwelt*);
                _corundsteinschalter(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,int,_corundstein*);
                virtual ~_corundsteinschalter();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
               // virtual void schalten();
                
                virtual void schalten();//alles schalten was da ist
                virtual void schaltenerstkontakt();
               /* virtual void schaltenzwischenkontakt();
                virtual void schaltenletztkontakt();                */
                
                virtual void zeichnen(_grafik*);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinschalter>*);
                void speichern(_speicherbardynamisch<_corundsteinschalter>*);
                char assoziieren(_speicherbardynamisch<_corundsteinschalter>*);
                //editierbar
                /*virtual void netzwahl(_netz*,int);
                void beiknopfausfuehren(_guiereignisdaten*);
                void beiknopfloeschenletzten(_guiereignisdaten*);
                void beiknopfloeschen(_guiereignisdaten*);*/
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
       /* public:
                _liste<_corundstein> liste;
        private:                
                //speichern hilfselemente
                unsigned int anzahlzeiger;*/
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N K U G E L G E N
//******************************************************************************************************************************************************************************************************
class _corundsteinkugelgen:public _corundstein,public _basis::_speicherbarargument<_corundsteinkugelgen>, public virtual _editierbar{
        public:
                _corundsteinkugelgen(_corundwelt*);
                _corundsteinkugelgen(_corundwelt*,_tg,_tg,_tg,_vektor3<_tg>,_tg ,_tg,_tg,_vektor4<_to>);
                virtual ~_corundsteinkugelgen();
                virtual void generieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinkugelgen>*);
                void speichern(_speicherbardynamisch<_corundsteinkugelgen>*);
                char assoziieren(_speicherbardynamisch<_corundsteinkugelgen>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        public:
                _tg radius;
                _tg ladung;
                _tg gravitation;
                bool killer;
                bool chaotischervektor;
                bool zumspielervektor;
                bool schaltenautomatisch;//schaltet automatische generierung bei aufruf von schalten ein
                unsigned int automatischanzahl;//wieviel automatisch generatiert werden
                unsigned int automatischzaehler;//wieviel im moment noch genereriuert werden müssen
                unsigned int automatischrate;//in welchem takt genereriert wird
                _vektor4<_to> farbe;
                _vektor3<_tg> vektor;
                _vektor3<_tg> vektoreinzel;

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N D A C H
//******************************************************************************************************************************************************************************************************
class _corundsteindach:public _corundstein,public _basis::_speicherbarargument<_corundsteindach>, public virtual _editierbar{
        public:
                _corundsteindach(_corundwelt*);
                _corundsteindach(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*);
                virtual ~_corundsteindach();
                virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void verschiebenvertex(const _vektor3<_tg>);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteindach>*);
                void speichern(_speicherbardynamisch<_corundsteindach>*);
                char assoziieren(_speicherbardynamisch<_corundsteindach>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        private:
                void konstruieren(const _vektor3<_tg>&o,const _vektor3<_tg>&v0,const _vektor3<_tg>&v1,const _vektor3<_tg>&v2);
        public:
                _liste<_netz> netze;   
                unsigned int netzanzahl;   
                _textur<_tb>*textur;          
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N F L A K
//******************************************************************************************************************************************************************************************************
class _corundsteinflak:public _corundstein,public _skelett,public _basis::_speicherbarargument<_corundsteinflak>, public virtual _editierbar{
        public:
                using _corundstein::welt;
                using _corundstein::ort;
        public:
                _corundsteinflak(_corundwelt*);
                _corundsteinflak(_corundwelt*,_tg,_tg,_tg);
                virtual ~_corundsteinflak();
                virtual void nachbereitenkonstruktion();
                void transformierenmuendungsfeuer(const _vektor3<_tg>&xa,const _vektor3<_tg>&ya,const _vektor3<_tg>&za);
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                virtual void zeichnen(_grafik*);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinflak>*);
                void speichern(_speicherbardynamisch<_corundsteinflak>*);
                char assoziieren(_speicherbardynamisch<_corundsteinflak>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
                
        public:
                _liste<_netz> netze;
                _knochen*fuss[4];
                _knochen*stuetze;
                _knochen*lauf[2][8];
                _knochen*richtung;
                _liste<_netz> muendungsfeuer;
                unsigned int netzanzahl;
                _netz*muendungsfeuerquer[3];
                _corundton*schuss;
                bool dauerfeuer;
                bool schalterdauer;
                _kollidierbarkugel*kk;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N A U S G A N G 
//******************************************************************************************************************************************************************************************************
class _corundsteinausgang:public _corundstein,public _basis::_speicherbarargument<_corundsteinausgang>, public virtual _editierbar{
        public:
                _corundsteinausgang(_corundwelt*);
                _corundsteinausgang(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinausgang();
                virtual void kollision(_kollidierbar*,_polygon*);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinausgang>*);
                void speichern(_speicherbardynamisch<_corundsteinausgang>*);
                char assoziieren(_speicherbardynamisch<_corundsteinausgang>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                int kartenindex;        
                unsigned int knotenindex;        
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S E N K E R           
//******************************************************************************************************************************************************************************************************
class _corundsteinsenker:public _corundstein,public _basis::_speicherbarargument<_corundsteinsenker>, public virtual _editierbar,public _liste<_corundsteinboulder>{
        public:
                _corundsteinsenker(_corundwelt*);
                _corundsteinsenker(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*);
                virtual ~_corundsteinsenker();
                virtual void initialisieren();
                virtual void animieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                bool innerhalbboulder();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinsenker>*);
                void speichern(_speicherbardynamisch<_corundsteinsenker>*);
                char assoziieren(_speicherbardynamisch<_corundsteinsenker>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                int zaehler;
                _vektor3<_tg> vektor;
                unsigned int zyklen;
                int modus;//0= oben , 1=senkt ab, 2=unten, 3= geht hoch
                bool pruefen;

};


//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N L A S E R 
//******************************************************************************************************************************************************************************************************
class _corundsteinlaser:public _corundstein,public _basis::_speicherbarargument<_corundsteinlaser>, public virtual _editierbar,public _listebasis<_corundstrahl>,public _liste<_corundsteinspiegel>{
        public:
                _corundsteinlaser(_corundwelt*);
                _corundsteinlaser(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*);
                virtual ~_corundsteinlaser();
                void neuberechnen();
                virtual void schalten();
                virtual void schaltenstrahlberuehrung();
                virtual void animieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinlaser>*);
                void speichern(_speicherbardynamisch<_corundsteinlaser>*);
                char assoziieren(_speicherbardynamisch<_corundsteinlaser>*);
                //editierbar
                virtual void netzwahl(_netz*,int);
                void beiknopfausfuehren(_guiereignisdaten*);
                void beiknopfloeschenletzten(_guiereignisdaten*);
                void beiknopfloeschen(_guiereignisdaten*);                
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _vektor3<_tg> vektor;
                _corundton*pton;
                _liste<_corundstein> liste;
                bool toedlich;
        private:                
                //speichern hilfselemente
                unsigned int anzahlzeiger;                
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S P I E G E L
//******************************************************************************************************************************************************************************************************
class _corundsteinspiegel:public _corundstein,public _basis::_speicherbarargument<_corundsteinspiegel>, public virtual _editierbar,public _liste<_corundsteinlaser>{
        public:
                _corundsteinspiegel(_corundwelt*);
                _corundsteinspiegel(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg,_textur<_tb>*);
                virtual ~_corundsteinspiegel();
                virtual void schalten();
                virtual void animieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinspiegel>*);
                void speichern(_speicherbardynamisch<_corundsteinspiegel>*);
                char assoziieren(_speicherbardynamisch<_corundsteinspiegel>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _netz*spiegel;
                _vektor3<_tg> achse;
                _tg raster;
                _vektor3<_tg> festrichtung;
                bool modusfestrichtung;
                _corundton*pton;

};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T R A H L 
//******************************************************************************************************************************************************************************************************
class _corundstrahl:public _listenknotenbasis<_corundstrahl>,public _kollisionskopplung{
        public:
                _corundstrahl(_corundsteinlaser*,const _vektor3<_tg>&,const _vektor3<_tg>&);
                virtual ~_corundstrahl();
                void anlegen();
                virtual void kollision(_kollidierbar*,_polygon*);
        public:
                _vektor3<_tg> ort;
                _vektor3<_tg> vektor;
                _vektor3<_tg> vektornormal;
                _tg radius;
                _netz*netz[3];//strahlnetz
                _kollidierbarkugel*kk;
                _corundsteinlaser*laser;
                
                                
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S C H L O S S
//******************************************************************************************************************************************************************************************************
class _corundsteinschloss:
 public _corundstein,
 public _corundschalter<_corundsteinschloss>,
 public _basis::_speicherbarargument<_corundsteinschloss>, 
 public virtual _editierbar{
        public:
                _corundsteinschloss(_corundwelt*);
                _corundsteinschloss(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinschloss();
                virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                void abschliessen();
                void aufschliessen(_corundobjektschluessela*cs);
                virtual void initialisieren();
                virtual void animieren();
                virtual void zeichnen(_grafik*g);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinschloss>*);
                void speichern(_speicherbardynamisch<_corundsteinschloss>*);
                char assoziieren(_speicherbardynamisch<_corundsteinschloss>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                unsigned int schloss;
                _corundobjektschluessela*schluessel;
                
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E R E I G N I S S
//******************************************************************************************************************************************************************************************************
class _corundsteinereignis:
public _corundstein,
public _corundschalter<_corundsteinereignis>,
public _basis::_speicherbarargument<_corundsteinereignis>, 
public virtual _editierbar{
        public:
                _corundsteinereignis(_corundwelt*);
                _corundsteinereignis(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinereignis();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();//wird aufgerufen um einzuschalten
                virtual void zeichnen(_grafik*g);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinereignis>*);
                void speichern(_speicherbardynamisch<_corundsteinereignis>*);
                char assoziieren(_speicherbardynamisch<_corundsteinereignis>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                bool eingeschaltet;
                int takt;
                int zahler;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N G E R I S S E N 
//******************************************************************************************************************************************************************************************************
class _corundsteingerissen:public _corundstein,public _basis::_speicherbarargument<_corundsteingerissen>, public virtual _editierbar{
        public:
                _corundsteingerissen(_corundwelt*);
                _corundsteingerissen(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteingerissen();
                virtual void aktualisierentextur();
                virtual void nachbereitenkonstruktion();
                virtual void initialisieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                void zerstoeren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteingerissen>*);
                void speichern(_speicherbardynamisch<_corundsteingerissen>*);
                char assoziieren(_speicherbardynamisch<_corundsteingerissen>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _netz*huelle;
                _tg schwaechung;
                _vektor3<_tg> grav;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S P U C K 
//******************************************************************************************************************************************************************************************************
class _corundsteinspuck:public _corundstein,public _basis::_speicherbarargument<_corundsteinspuck>, public virtual _editierbar{
        public:
                _corundsteinspuck(_corundwelt*);
                _corundsteinspuck(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinspuck();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinspuck>*);
                void speichern(_speicherbardynamisch<_corundsteinspuck>*);
                char assoziieren(_speicherbardynamisch<_corundsteinspuck>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _vektor3<_tg> vektor;
                bool invalid;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N T A U S C H E R 
//******************************************************************************************************************************************************************************************************
class _corundsteintauscher:public _corundstein,public _basis::_speicherbarargument<_corundsteintauscher>, public virtual _editierbar{
        public:
                _corundsteintauscher(_corundwelt*);
                _corundsteintauscher(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteintauscher();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteintauscher>*);
                void speichern(_speicherbardynamisch<_corundsteintauscher>*);
                char assoziieren(_speicherbardynamisch<_corundsteintauscher>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N M A G N E T I S C H 
//******************************************************************************************************************************************************************************************************
class _corundsteinmagnetisch:public _corundstein,public _basis::_speicherbarargument<_corundsteinmagnetisch>, public virtual _editierbar{
        public:
                _corundsteinmagnetisch(_corundwelt*);
                _corundsteinmagnetisch(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinmagnetisch();
                virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                virtual void schalten();
                virtual void verschiebenvertex(const _vektor3<_tg>v);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinmagnetisch>*);
                void speichern(_speicherbardynamisch<_corundsteinmagnetisch>*);
                char assoziieren(_speicherbardynamisch<_corundsteinmagnetisch>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _feldmagnetostatisch<_tg>*magnet;
             
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N D I E B 
//******************************************************************************************************************************************************************************************************
class _corundsteindieb:public _corundstein,public _basis::_speicherbarargument<_corundsteindieb>, public virtual _editierbar{
        public:
                _corundsteindieb(_corundwelt*);
                _corundsteindieb(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteindieb();
                virtual void initialisieren();
                virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteindieb>*);
                void speichern(_speicherbardynamisch<_corundsteindieb>*);
                char assoziieren(_speicherbardynamisch<_corundsteindieb>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _corundton*lach[3];
                _netz*spinne;
                _netz*rahmen;
                int modus;//0=ruhe, 1=hoch, 2=runter
                int zaehler;
                bool hatgeklaut;
                _corundkugel*kugel;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N F L I E G E N G E N
//******************************************************************************************************************************************************************************************************
class _corundsteinfliegengen:public _corundstein,public _basis::_speicherbarargument<_corundsteinfliegengen>, public virtual _editierbar{
        public:
                _corundsteinfliegengen(_corundwelt*);
                _corundsteinfliegengen(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinfliegengen();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinfliegengen>*);
                void speichern(_speicherbardynamisch<_corundsteinfliegengen>*);
                char assoziieren(_speicherbardynamisch<_corundsteinfliegengen>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S P I N N E N G E N 
//******************************************************************************************************************************************************************************************************
class _corundsteinspinnengen:public _corundstein,public _basis::_speicherbarargument<_corundsteinspinnengen>, public virtual _editierbar{
        public:
                _corundsteinspinnengen(_corundwelt*);
                _corundsteinspinnengen(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinspinnengen();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinspinnengen>*);
                void speichern(_speicherbardynamisch<_corundsteinspinnengen>*);
                char assoziieren(_speicherbardynamisch<_corundsteinspinnengen>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N S H O G U N 
//******************************************************************************************************************************************************************************************************
class _corundsteinshogun:public _corundstein,public _basis::_speicherbarargument<_corundsteinshogun>, public virtual _editierbar{
        public:
                _corundsteinshogun(_corundwelt*);
                _corundsteinshogun(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinshogun();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinshogun>*);
                void speichern(_speicherbardynamisch<_corundsteinshogun>*);
                char assoziieren(_speicherbardynamisch<_corundsteinshogun>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N P U Z Z L E 
//******************************************************************************************************************************************************************************************************
class _corundsteinpuzzle:public _corundstein,public _basis::_speicherbarargument<_corundsteinpuzzle>, public virtual _editierbar{
        public:
                _corundsteinpuzzle(_corundwelt*);
                _corundsteinpuzzle(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinpuzzle();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinpuzzle>*);
                void speichern(_speicherbardynamisch<_corundsteinpuzzle>*);
                char assoziieren(_speicherbardynamisch<_corundsteinpuzzle>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N G A S 
//******************************************************************************************************************************************************************************************************
class _corundsteingas:public _corundstein,public _basis::_speicherbarargument<_corundsteingas>, public virtual _editierbar{
        public:
                _corundsteingas(_corundwelt*);
                _corundsteingas(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteingas();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteingas>*);
                void speichern(_speicherbardynamisch<_corundsteingas>*);
                char assoziieren(_speicherbardynamisch<_corundsteingas>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N K O M B I N A T I O N S S C H L O S S  
//******************************************************************************************************************************************************************************************************
class _corundsteinkombinationsschloss:public _corundstein,public _basis::_speicherbarargument<_corundsteinkombinationsschloss>, public virtual _editierbar{
        public:
                _corundsteinkombinationsschloss(_corundwelt*);
                _corundsteinkombinationsschloss(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteinkombinationsschloss();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteinkombinationsschloss>*);
                void speichern(_speicherbardynamisch<_corundsteinkombinationsschloss>*);
                char assoziieren(_speicherbardynamisch<_corundsteinkombinationsschloss>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N D R E H K R E U Z
//******************************************************************************************************************************************************************************************************
class _corundsteindrehkreuz:public _corundstein,public _basis::_speicherbarargument<_corundsteindrehkreuz>, public virtual _editierbar{
        public:
                _corundsteindrehkreuz(_corundwelt*);
                _corundsteindrehkreuz(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteindrehkreuz();
                virtual void kollision(_kollidierbar*,_polygon*);
                bool tuervektor(_polygon*p,_vektor3<_tg>&tv);
                virtual void initialisieren();
                virtual void schalten();
                virtual void animieren();
                virtual void zeichnen(_grafik*g);
                void einhaengenoktalbaum();
                void aushaengenoktalbaum();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteindrehkreuz>*);
                void speichern(_speicherbardynamisch<_corundsteindrehkreuz>*);
                char assoziieren(_speicherbardynamisch<_corundsteindrehkreuz>*);
                //editierbar
                virtual void netzwahl(_netz*,int);
                void beiknopftuersetzen(_guiereignisdaten*);
                void beiknopftuerloeschen(_guiereignisdaten*);
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                _liste<_netz> tuer;
                _vektor3<_tg> normale;
                _vektor3<_tg> nord;
                _tg winkelraster;
                unsigned int iteratorschritte;
                _tg iterator;
                _tg winkel;
                _tg winkelalt;
                _vektor3<_tg> netzmitte;
                _kurvehermite3<_tg> kurve;
                unsigned int anzahlnetz;
                
                                
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S T E I N E I N B A H N 
//******************************************************************************************************************************************************************************************************
class _corundsteineinbahn:public _corundstein,public _basis::_speicherbarargument<_corundsteineinbahn>, public virtual _editierbar{
        public:
                _corundsteineinbahn(_corundwelt*);
                _corundsteineinbahn(_corundwelt*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_corundsteineinbahn();
                
                virtual void nachbereitenkonstruktion();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void initialisieren();
                virtual void animieren();
                virtual void schalten();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundsteineinbahn>*);
                void speichern(_speicherbardynamisch<_corundsteineinbahn>*);
                char assoziieren(_speicherbardynamisch<_corundsteineinbahn>*);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);
        public:
                int richtung;//0=o, 1=s, 2=w, 3=n
};
#endif
