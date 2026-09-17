//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corund.hpp
//  Datum        : 04.04.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************

//******************************************************************************************************************************************************************************************************
//                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _corundwelt;

class _corundinventar;
class _corunddruckwelle;
class _corundlichtverwaltung;
class _corundknoten;
class _corundlicht;
class _corundkamera;
class _corundton;

//******************************************************************************************************************************************************************************************************
//                              I N C L U D E S
//******************************************************************************************************************************************************************************************************
#ifndef corundhpp
#define corundhpp


#define CORUND_MIT_OPENGL

#include "../hpp/_corundstein.hpp"
#include "../hpp/_corundfigur.hpp"
#include "../hpp/_corundobjekt.hpp"
#include "../hpp/_corundboden.hpp"

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


//******************************************************************************************************************************************************************************************************
//                              C O R U N D W E L T 
//******************************************************************************************************************************************************************************************************
class _corundwelt:
public _listebasis<_corundkugel>,
public _listebasis<_corundstein>,
public _listebasis<_corundobjekt>,
public _listebasis<_corundboden>,
public _listebasis<_corundfigur>,
public _listebasis<_corundspinne>,
public _listebasis<_corundknoten>,
public _listebasis<_corunddruckwelle>,
public _listebasis<_corundschaltkopplung>,
public _listebasis<_corundlicht>,
public _listebasis<_corundgummiband>,
public _listebasis<_corundfeder>,
public _baumoctal<_polygon,_tg>,
public _editierbar,
public _basis::_speicherbarargument<_corundwelt>{
        public:
                using _listebasis<_corundkugel>::anfang;
                using _listebasis<_corundknoten>::anfang;
                using _listebasis<_corundstein>::anfang;
                using _listebasis<_corundobjekt>::anfang;
                using _listebasis<_corundboden>::anfang;
                using _listebasis<_corundspinne>::anfang;
                using _listebasis<_corundfigur>::anfang;
                using _listebasis<_corundlicht>::anfang;
                using _listebasis<_corundgummiband>::anfang;
                using _listebasis<_corundfeder>::anfang;
                using _listebasis<_corundkugel>::naechstes;
                using _listebasis<_corundknoten>::naechstes;
                using _listebasis<_corundstein>::naechstes;
                using _listebasis<_corundobjekt>::naechstes;
                using _listebasis<_corundboden>::naechstes;
                using _listebasis<_corundspinne>::naechstes;
                using _listebasis<_corundfigur>::naechstes;
                using _listebasis<_corundlicht>::naechstes;
                using _listebasis<_corundgummiband>::naechstes;
                using _listebasis<_corundfeder>::naechstes;
                using _listebasis<_corundkugel>::vorheriges;
                using _listebasis<_corundknoten>::vorheriges;
                using _listebasis<_corundstein>::vorheriges;
                using _listebasis<_corundobjekt>::vorheriges;
                using _listebasis<_corundboden>::vorheriges;
                using _listebasis<_corundspinne>::vorheriges;
                using _listebasis<_corundfigur>::vorheriges;
                using _listebasis<_corundlicht>::vorheriges;
                using _listebasis<_corundgummiband>::vorheriges;
                using _listebasis<_corundfeder>::vorheriges;

        public:
                _corundwelt(_grafik*,_texturverwaltung<_tb>&,_akustik*,_tonverwaltung&);
                virtual ~_corundwelt();
                void erzeugenpartikelsysteme();
                void loeschenpartikelsysteme();
                bool istinternepartikelquelle(_partikelquelle*)const;
                void erzeugenszene0(_grafik*);
                void erzeugenszene1(_grafik*);
                void erzeugenszene2(_grafik*);
                void erzeugenszene3(_grafik*);
                void erzeugenszene4(_grafik*);
                void erzeugenszene5(_grafik*);
                void erzeugenszene6(_grafik*);
                void erzeugenszene7(_grafik*);
                void erzeugenszene8(_grafik*);
                void erzeugenszene9(_grafik*);
                _netz* erzeugenquader(const _vektor3<_tg>&o,const _vektor3<_tg>&vx,const _vektor3<_tg>& vy,const _vektor3<_tg>& vz,_textur<_tb>*t,_tg,_tg,_tg);
                void erzeugenumgebung0();
                _netz*erzeugenlichtnetz(_to r,_to g,_to b,_tg i,_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,_tg tks,_textur<_tb>*tex);
                void erzeugenskybox();
                _netz*erzeugennetz(const _vektor3<_tg>&p,const _vektor3<_tg>&vex,const _vektor3<_tg>&vey,const _tg tks, _textur<_tb>*tex);
                _netz*erzeugennetz(const _vektor3<_tg>&p,const _vektor3<_tg>&vex,const _vektor3<_tg>&vey,const _tg tksx,const _tg tksy, _textur<_tb>*tex);
                _netz*erzeugennetzspiegel(const _vektor3<_tg>&p,const _vektor3<_tg>&vex,const _vektor3<_tg>&vey,const _tg tks, _textur<_tb>*tex);
                void corundpaargeoeffnet();
                void erzeugenbaum();
                void zeichnenbaum(_grafik*gra);
                void zeichnenbaum(_grafik*gra,_weltdebuglinie*wl,_baumoctalwuerfel<_polygon,_tg>*q);
                void initialisierenanimation(_grafik*);
                void animieren(_grafik*,_akustik*);
                void deinitialisierenanimation();
                //debug
                void erzeugendebugschirm();
                void loeschendebugschirm();
                //speichern
                virtual char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundwelt>*);
                virtual void speichern(_speicherbardynamisch<_corundwelt>*);
                virtual char assoziieren(_speicherbardynamisch<_corundwelt>*);
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        public:
                _welt*welt;   
                _zeichenkette<char> speichername;
                _zeichenkette<char> name;
                _vektor3<_tg> kameraverschiebung;
                _tg kamerafederhaerte;
               
                 _grafik*pgrafik;//nur für destruktor (erzeugen und löschen von grafikinternen bildern)

                _bestrahler*B;
                _vektor4<_to> ambientlicht;
                //_tg reibung;
                bool nebel;
                unsigned int nebelmodus;
                _vektor4<_to> nebelfarbe;
                _tg nebeldichte;
                _vektor2<_tg> nebeldistanz;
                _win::_zeit* pzeit;
                _zeichensatzbild*zeichensatz;
                _win::_tastatur*kb;
                _win::_maus<>*mo;       
                _vektor3<_tg> morelativ;
                _partikelquellesprite*psstaubwolke;
                _partikelquellesprite*psstrahl;
                _partikelquellesprite*psrot;
                _partikelquellesprite*psfrage;
                _partikelquellesprite*pseinschlag;
                _partikelquellesprite*pskugeltot;
                _tg strahldauer;
                _netz*skybox;
                _corundsteincorund*teiloffen;
                _netz*spezial;
                _tg steinskalierung;
                _corundkugel*spieler;
                _corundkamera*kamera;
                _corundton*explosion;
                _corundsteintor*ausgang;
                int naechstekarte;
                unsigned int naechsterknoten;
                int diesekarte;
                unsigned int paaranzahl;
                unsigned int geoeffnet;
                unsigned int zeitanfang;
                unsigned int grafikx;
                unsigned int grafiky;
                _corundinventar*corundinventar;
                _texturverwaltung<_tb>&textur;
                _tonverwaltung&tonverwaltung;
                _liste<_corundboden> bodenzumloeschen;
                _liste<_corundobjekt> objektzumloeschen;
                _liste<_corundstein> steinzumloeschen;
                //debug
                _weltdebugschirm*debugschirm;
};               

//******************************************************************************************************************************************************************************************************
//                              C O R U N D I N V E N T A R 
//******************************************************************************************************************************************************************************************************
class _corundinventar:public _listebasis<_corundobjekt>{
        public:
        using _listebasis<_corundobjekt>             ::anfang;
        using _listebasis<_corundobjekt>             ::naechstes;
        using _listebasis<_corundobjekt>             ::vorheriges;
        public:
                _corundinventar(_corundwelt*);
                virtual ~_corundinventar();
                void aktualisieren();
                void einhaengenobjekt(_corundobjekt*c);
                void animieren();
                void loeschenerstes();
                void textanimation(_zeichenkette<char>);
                void zeichnen(_grafik*);
        public:
                _corundwelt*welt;
                _zeichenkette<char> text;
                bool textanimiert;
                _tg  textx;
                _tg  textxd;
                bool links;
                _tg rotx,roty;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D T O N
//******************************************************************************************************************************************************************************************************
class _corundton{
        public:
                _corundton(_corundwelt*,_ton*,const _vektor3<_tg>&,const _vektor3<_tg>&);
                virtual ~_corundton();
                void abspielen();
        public:
                _vektor3<_tg> ort;
                _vektor3<_tg> vektor;
                _ton*ton;
                _tg lautstaerke;
                _tg beugung;
                bool schleife;
                _tg radius;
                bool distanzlautstaerke;
                _corundwelt*welt;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D K A M E R A
//******************************************************************************************************************************************************************************************************
class _corundkamera{
        public:
                _corundkamera(_corundwelt*);
                virtual ~_corundkamera();
                void aktualisieren();
                virtual void animieren();
        public: 
                _corundwelt*corundwelt;               
                _kamera<_tg>*kam;  
                _kollidierbarkugel*kamerakugel;
                
                bool kurvenmodus;
                _kurvehermite3<_tg> kurve;
                _kurvehermite3<_tg> richtung;
                _kurvehermite3<_tg> ebene0;
                _tg kurvenparameter;
                _tg kurvenschritt;
                bool standmodus;
                
};
//******************************************************************************************************************************************************************************************************
//                               C O R U N D L I C H T V E R W A L T U N G
//******************************************************************************************************************************************************************************************************
class _corundlichtverwaltung{
        public:
                _corundlichtverwaltung();
                virtual ~_corundlichtverwaltung();
                void einhaengenzumloeschen(_licht<_tg,_to>*);
                void einhaengenzumschattieren(_liste< ::_polygon>*,_licht<_tg,_to>*,_tg);
                void loeschen();
                void schattieren();
                
        private:
                //für spezielle polygonschatten
                _liste<_liste<_polygon> > polylisten;
                _liste<_licht<_tg,_to> > lichtliste;
                _liste<_tg> laengen;
                //zum löschen
                _liste<_licht<_tg,_to> > loeschliste;
        
};
//******************************************************************************************************************************************************************************************************
//                               C O R U N D K N O T E N   
//******************************************************************************************************************************************************************************************************
class _corundknoten:public _listenknotenbasis<_corundknoten>,public _editierbar,public _basis::_speicherbarargument<_corundknoten>{
        public:
                _corundknoten(_corundwelt*,const _vektor3<_tg>&,const unsigned int);
                virtual ~_corundknoten();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundknoten>*);
                void speichern(_speicherbardynamisch<_corundknoten>*);
                char assoziieren(_speicherbardynamisch<_corundknoten>*);
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                
        public:                
                unsigned int index;
                _vektor3<_tg> ort;
                _vektor3<_tg> vektorankunft;
                _vektor3<_tg> vektorabfahrt;
                unsigned int wartezeit;
};
//******************************************************************************************************************************************************************************************************
//                               C O R U N D L I C H T 
//******************************************************************************************************************************************************************************************************
class _corundlicht:
 public _listenknotenbasis<_corundlicht>,
 public _licht<_tg,_to>,
 public _corundschaltkopplung,
 public virtual _editierbar,
 public _basis::_speicherbarargument<_corundlicht>{
        public:
                _corundlicht(_corundwelt*,_listebasis<_licht<_tg,_to> >*,const _vektor3<_tg>,const _vektor3<_to>,const _to);
                _corundlicht(const _corundlicht*);
                virtual ~_corundlicht();
                virtual void kopieren(_licht<_tg,_to>*&)const;
                virtual void schalten();
                virtual void animieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundlicht>*);
                void speichern(_speicherbardynamisch<_corundlicht>*);
                char assoziieren(_speicherbardynamisch<_corundlicht>*);                
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        public: 
                _corundwelt*welt;
                bool animiert;
                unsigned int methode[4][3];
                bool periodisch[4][3];
                _tg xoffset[4][3];
                _tg xfaktor[4][3];//geschwnidigkeit
                _tg yoffset[4][3];//y-achsenabschnitt
                _tg yfaktor[4][3];//amplitude
                _tg iterator;
                
/* *normal
 *sinus
 *rechteck
 *sägezahn
 *flackernd
 *strobo
 */
 };


//******************************************************************************************************************************************************************************************************
//                               C O R U N D D R U C K W E L L E 
//******************************************************************************************************************************************************************************************************
class _corunddruckwelle:public _listenknotenbasis<_corunddruckwelle>{
        public:
                _corunddruckwelle(_corundwelt*,const _vektor3<_tg>&o,const _tg s,const _tg v,const unsigned int d);
                virtual ~_corunddruckwelle();
                virtual void animieren();
        public:                
                _gravitation<_tg>*grav;
                int dauer;
                _tg geschwindigkeit;
};


#endif