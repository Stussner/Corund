//******************************************************************************************************************************************************************************************************
//  Projekt      : corund
//  Bibliothek   : 
//  Modul        : _corundfigur.hpp
//  Datum        : 03.07.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#ifndef _corundfigur_hpp_included
#define _corundfigur_hpp_included

class _corundfigur;
class _corundkugel;
class _corundgummiband;
class _corundfeder;
class _corundskelett;
class _corundorakel;
class _corundspinne;
class _corundspinnenbein;
class _corundhebweber;
class _corundspringspinne;
class _corundcatwiesel;
class _corundfliege;
class _corundmade;

#include "../hpp/_corund.hpp"
#include "../hpp/_corundstein.hpp"
#include <_struktur.hpp>
#include <_weltkollision.hpp>
#include <_weltmechanik.hpp>
#include "../hpp/_corundschalter.hpp"
#include "../hpp/_corundboden.hpp"


//******************************************************************************************************************************************************************************************************
//                              C O R U N D F I G U R
//******************************************************************************************************************************************************************************************************
class _corundfigur:
 public _listenknotenbasis<_corundfigur>,
 public _kollisionskopplung,
 public _corundschaltkopplung{
        public:
                _corundfigur(_corundwelt*);
                virtual ~_corundfigur();
                virtual void initialisieren()=0;
                virtual void animieren()=0;
                virtual void visualisieren()=0;
                virtual void netzwahl(_netz*,int);
                virtual void knotenwahl(_corundknoten*,int);
                virtual void figurwahl(_corundfigur*,int);
        public:
                _corundwelt*corundwelt;
                _welt*welt;                
};
  
//******************************************************************************************************************************************************************************************************
//                              C O R U N D K U G E L
//******************************************************************************************************************************************************************************************************
class _corundkugel:
 public _corundfigur,
 public _listenknotenbasis<_corundkugel>,
 public _liste<_corundgummiband>,
 public _liste<_corundfeder>,
 public _kollidierbarkugel,
 public _kugel,
 public _basis::_speicherbarargument<_corundkugel>,
 public virtual _editierbar,
 public _material<_tg>,
 public _oberflaeche<_tg>,
 public _liste<_corundbodenwasser>,
 public _liste<_corundbodensumpf>,
 public _liste<_corundbodenlava>
 {
        public:
                _corundkugel(_corundwelt*,const _vektor3<_tg>&,const _vektor3<_tg>&,const _tg,const _vektor4<_to>&);
                virtual ~_corundkugel();
                void initialisieren();
                void zerstoeren();
                void abziehengesundheit(const _tg);
                void animieren();
                void pruefenabgleitzustandein();
                void pruefenabgleitzustandaus();
                void bearbeitenabgleitzustand();
                void loeschengummiband();
                void loeschenfeder();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void kollision(_kollidierbar*);
                virtual void visualisieren();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundkugel>*);
                void speichern(_speicherbardynamisch<_corundkugel>*);
                char assoziieren(_speicherbardynamisch<_corundkugel>*);                
                //editierbar
                virtual void netzwahl(_netz*,int);
                virtual void figurwahl(_corundfigur*,int);
                void beineugummifest (_guiereignisdaten*);
                void beineugummistein(_guiereignisdaten*);
                void beineugummifigur(_guiereignisdaten*);
                void beiloeschengummi(_guiereignisdaten*);
                void beineufederfest (_guiereignisdaten*);
                void beineufederstein(_guiereignisdaten*);
                void beineufederfigur(_guiereignisdaten*);
                void beiloeschenfeder(_guiereignisdaten*);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                //debug
                void loeschendebug();
                
        public:
                //_corundwelt*corundwelt;                
                _vektor4<_to> farbe;
                _tg ladung;
                _tg gravitation;
                bool steuerung;
                bool spieler;
                bool augenmodus;
                bool killer;
                bool chaotischervektor;
                _tg chaotischerfaktor;
                bool zumspielervektor;
                _tg gesundheit;
                bool tauchen;
                int tauchzaehler;
                bool inlava;
                //_liste<_polygon> abgleitpolygon;
                //_weltdebugkugel*ws;
                _vektoranalysis3<_tg> V3;
                //für editor , nicht speichern
                _dynamischerdialog*dialog;
                _vektor3<_tg> editorgummikoordinate;
                _vektor4<_to> editorgummifarbe;
                _tg editorgummistaerke;
                _vektor3<_tg> editorfederkoordinate;
                _vektor4<_to> editorfederfarbe;
                _tg editorfederstaerke;
                _hauptfenster*hauptfenster;
                //debug
                _weltdebugtext*dbvektor;
                _weltdebugtext*dbgrav;
                _weltdebugtext*dbort;
                
};
//******************************************************************************************************************************************************************************************************
//                              O X Y D G U M M I B A N D 
//******************************************************************************************************************************************************************************************************
class _corundgummiband:public _listenknotenbasis<_corundgummiband>,public _basis::_speicherbarargument<_corundgummiband>{
    public:
            _corundgummiband(_corundwelt*);//für laden und speichern
            _corundgummiband(_corundkugel*k,_corundkugel*,_tg s);
            _corundgummiband(_corundkugel*k,_corundstein*,_tg s);
            _corundgummiband(_corundkugel*k,const _vektor3<_tg>&o,const _vektor4<_to>&f,_tg s);
            virtual ~_corundgummiband();
            _vektor3<_tg>&beschleunigung(_corundkugel*);
            void zeichnen(_grafik*);
            //speichern
            char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundgummiband>*);
            void speichern(_speicherbardynamisch<_corundgummiband>*);
            char assoziieren(_speicherbardynamisch<_corundgummiband>*);               
    public:
            _corundwelt*corundwelt;
            _welt*pwelt;            
            _vektor3<_tg> ort;
            _vektor4<_to> pfarbe;
            _tg staerke;
            _corundkugel*kugel;
            _corundkugel*kugel2;
            _corundstein*stein;
            _vektor3<_tg> pbeschleunigung;//vorberechnung?, nicht speichern
            //_weltdebuglinie*wl;//nicht speichern, zeichenhilfsmittel
};
//******************************************************************************************************************************************************************************************************
//                              O X Y D F E D E R
//******************************************************************************************************************************************************************************************************
class _corundfeder:public _listenknotenbasis<_corundfeder>,public _basis::_speicherbarargument<_corundfeder>{
    public:
            _corundfeder(_corundwelt*);//für laden und speichern
            _corundfeder(_corundkugel*k,_corundkugel*,_tg staerke);
            _corundfeder(_corundkugel*k,_corundstein*,_tg staerke);
            _corundfeder(_corundkugel*k,const _vektor3<_tg>&o,const _vektor4<_to>&f,_tg s);
            virtual ~_corundfeder();
            void beschleunigung(_corundkugel*,_vektor3<_tg>&,_vektor3<_tg>&);
            void zeichnen(_grafik*);
            //speichern
            char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundfeder>*);
            void speichern(_speicherbardynamisch<_corundfeder>*);
            char assoziieren(_speicherbardynamisch<_corundfeder>*);       
    public:
            _corundwelt*corundwelt;
            _welt*pwelt;      
            _vektor4<_to> pfarbe;
            _vektor3<_tg> ort;
            _tg staerke;
            _vektor3<_tg> pvektor[2];      
            _tg plaenge;
            _corundkugel*kugel;
            _corundkugel*kugel2;
            _corundstein*stein;
            _vektor3<_tg> pbeschleunigung;
            //_weltdebuglinie*wl;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S K E L E T T 
//******************************************************************************************************************************************************************************************************
class _corundskelett:
 public _corundfigur,
 public _skelett{
        public:
                _corundskelett(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
                virtual ~_corundskelett();
                //virtual void initialisieren()=0;//meistens einhaengungen in die datenstrukturen sektor und baum
                //virtual void animieren()=0;
                virtual void transformieren()=0;
                virtual void visualisieren();
                
                
        public:
                //_corundwelt*corundwelt;
                //_welt*welt;
                _vektor3<double> port;//steuerort
				_vektor3<double> verschiebung;//skelettort=ort+verschiebung;
				_vektor3<double> impuls;//trägheitsimpuls des rumpfs        
				_tg federkraft;
				_tg traegheitsdaempfung;        

};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D O R A K E L 
//******************************************************************************************************************************************************************************************************
class _corundorakel:public _corundskelett{
        public:
                _corundorakel(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
                virtual ~_corundorakel();
                void initialisieren();//meistens einhaengungen in die datenstrukturen sektor und baum
                virtual void animieren();
                virtual void transformieren();
                virtual void kollision(_kollidierbar*,_polygon*);
                //steuerfunktionen 
                void bewegen(const _vektor3<_tg>&v);
                void drehenx(double);
                void dreheny(double);
                void drehenz(double);
                void ausloesenschreiten();
                void schreiten(const unsigned int i,const _vektor3<_tg>&v);
                void schreitenzufall(const unsigned int i);//schreitet ein tentakel zufällig und den einheitsvektor zufall 
        public:
                _knochen*unterrumpf[4];
                _knochen*rumpf;   
                _extremitaet*tentakel[4];  
                _extremitaet*finger[4][3];    
                
                bool gehezumspieler; 
                unsigned int letztewahl;      
                _weltdebugkreuz*wsoll[4];
                _weltdebugkreuz*wist[4];
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S P I N N E
//******************************************************************************************************************************************************************************************************
class _corundspinne:public _skelett,public _listenknotenbasis<_corundspinne>,public _kollisionskopplung{
        public:
                _corundspinne(_corundwelt*,_vektor3<double>);
                virtual ~_corundspinne();
                void zone(_partition::_zone*);
                virtual void kollision(_kollidierbar*,_polygon*);
                void initialisieren();//meistens einhaengungen in die datenstrukturen sektor und baum
                void drehenx(double);
                void dreheny(double);
                void drehenz(double);
              //  inline void sichernrumpf(int,int);
                void animieren();
                inline void animierenarsch();
                void transformieren();
                inline void transformieren(_vektor3<double>&,_vektor3<double>&);
                void normaleanpassen(bool);
                void anpassenausrichtung(const _vektor3<double> neuenormale,_vektor3<double>&neuerichtung,_vektor3<double>&neueseite);
                //speichern
               /* char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_corundspinne>*);
                void speichern(_speicherbardynamisch<_corundspinne>*);
                char assoziieren(_speicherbardynamisch<_corundspinne>*);     
                //editierbar
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);      */                      
        public:
                _knochen*vorderleib;
                _knochen*hinterleib;
                _knochen*warze[2][3];
                _knochen*taster[2][3];
                _knochen*rumpf[2][4];
                _corundspinnenbein*bein[2][4];
                
                //-------------------
                _corundwelt*corundwelt;
                _welt*welt;
                _partition::_zone*pzone;
                _partition::_sektor*lokussektor;
                _vektor3<double> port;//steuerort
				_vektor3<double> verschiebung;//skelettort=ort+verschiebung;
				_vektor3<double> impuls;//trägheitsimpuls des rumpfs
				_vektor3<double> vektor;//gewünschte rumpfverschiebung
                
                _vektor3<double> normale;//figurnormale
                _vektor3<double> richtung;//globale firgurenausrichtung
                _vektor3<double> seite;//komplett orthonormiertes rechtssystem
                _vektoranalysis3<double> V3;
                double time,tr;
	            bool oa;                
                bool kamverankert;
                _weltdebugkugel*ws;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D S P I N N E N B E I N   
//******************************************************************************************************************************************************************************************************
class _corundspinnenbein{
        public:
                _corundspinnenbein(_corundspinne*,_knochen*);
                virtual ~_corundspinnenbein();
                _knochen * operator[](const unsigned int);
                void setzen(_tg b0x,_tg b0y,_tg b0z,  _tg b1x,_tg b1y,_tg b1z,  _tg b2x,_tg b2y,_tg b2z,  _tg b3x,_tg b3y,_tg b3z);
                void initialisieren(); 
                void transformieren();
                void animieren();
                void ausrichtenlinear(const _vektor3<_tg>&);
                void ausrichten(_vektor3<double>&,double&);      
                void fixieren(_polygon*);
                void loesen();                          
        public:
                _corundspinne*spinne;
                _knochen*wurzel;
                _knochen*bein[4];          
                bool fixiert;//status der fixierung  
                _vektor3<double> zielfuss;//fixpunkte zur verankerung
                _partition::_sektor*fusssektor;
                _kollidierbarkugel*fusskugel;
                _polygon*polygonfixiert;       
                _vektor3<double> ausrichtungoptimal;//otimale(originale) ausrichtung (verbindungslinie)
                _vektor3<double> ausrichtungoptimaloriginal;      
                double schreitenx;
                double schreitendx;
                double schreitmodus;
                double schreitdurchlauf;
                _kurvehermite3<_tg> kurve;  
				double ausrichtungwinkel;//kein winkel, sondern verschiebung, die sich orthogonal auf die höhenausrichtung auswirkt				
				double laenge;// momentane laenge in % (gamma)
				double laengemax;//in % der maximallaenge (gamma)
				double laengemin;//in % der maximallaenge (gamma)
				double laengemaxtheoretisch;
				bool ingueltigerausrichtung;
                _weltdebugkreuz*wc;
                _weltdebugpfeil*wan;
                _weltdebugpfeil*was;
                _weltdebugpfeil*war;	
                _vektor3<double> ausrichtung;//dynamische höhen-ausrichtung der beine
                                                   
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D H E B W E B E R
//******************************************************************************************************************************************************************************************************
class _corundhebweber:public _corundskelett{
        public:
                _corundhebweber(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
                virtual ~_corundhebweber();
                void initialisieren();//meistens einhaengungen in die datenstrukturen sektor und baum
                virtual void animieren();
                virtual void transformieren();
                virtual void kollision(_kollidierbar*,_polygon*);
        public:
                _knochen*hinterleib;
                _knochen*vorderleib;   
                _knochen*rumpf[2][4];//zu den beinen
                _extremitaet*bein[2][4];  
                _extremitaet*taster[2];
};

//******************************************************************************************************************************************************************************************************
//                              C O R U N D S P R I N G S P I N N E
//******************************************************************************************************************************************************************************************************
class _corundspringspinne:public _corundskelett{
        public:
                _corundspringspinne(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
                virtual ~_corundspringspinne();
                void initialisieren();//meistens einhaengungen in die datenstrukturen sektor und baum
                virtual void animieren();
                virtual void transformieren();
                virtual void kollision(_kollidierbar*,_polygon*);
        public:
                _knochen*hinterleib;
                _knochen*vorderleib;   
                _knochen*rumpf[2][4];//zu den beinen
                _extremitaet*bein[2][4];  
                _extremitaet*taster[2];
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D C A T W I E S E L 
//******************************************************************************************************************************************************************************************************
class _corundcatwiesel:public _corundskelett{
        public:
                _corundcatwiesel(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
                virtual ~_corundcatwiesel();
                void initialisieren();//meistens einhaengungen in die datenstrukturen sektor und baum
                virtual void animieren();
                virtual void transformieren();
                virtual void kollision(_kollidierbar*,_polygon*);
        public:
                _extremitaet*ruecken;
                _extremitaet*hals;
                _knochen*becken[2]; 
                _knochen*schluesselbein[2];
                _knochen*kopf;
                _knochen*ohr[2];
                _knochen*kiefer;  
                _extremitaet*bein[2];  
                _extremitaet*arm[2];
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D F L I E G E 
//******************************************************************************************************************************************************************************************************
class _corundfliege:public _corundskelett{
        public:
                _corundfliege(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
                virtual ~_corundfliege();
                void initialisieren();//meistens einhaengungen in die datenstrukturen sektor und baum
                virtual void animieren();
                virtual void transformieren();
                virtual void kollision(_kollidierbar*,_polygon*);
        public:
                _knochen*hinterleib;
                _knochen*vorderleib;   
                _knochen*kopf;
                _knochen*rumpf[2][3];//zu den beinen
                _extremitaet*bein[2][3];  
                _extremitaet*ruessel;
};
//******************************************************************************************************************************************************************************************************
//                              C O R U N D M A D E 
//******************************************************************************************************************************************************************************************************
class _corundmade:public _corundskelett{
        public:
                _corundmade(_corundwelt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
                virtual ~_corundmade();
                void initialisieren();//meistens einhaengungen in die datenstrukturen sektor und baum
                virtual void animieren();
                virtual void transformieren();
                virtual void kollision(_kollidierbar*,_polygon*);
        public:
                _extremitaet*vorne;
                _extremitaet*hinten;
                _knochen*rumpf[2];//zu den tastern
                _extremitaet*taster[2];
};

#endif
