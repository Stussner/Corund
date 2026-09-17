#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <_global.hpp>
#include <_struktur.hpp>
#include <_funktion.hpp>
#include <_text.hpp>
#include <_textbuffer.hpp>
#include <_datei.hpp>
#include <_bild.hpp>
#include <_grafikwin.hpp>

#include <_welt.hpp>
#include <_weltpolygon.hpp>
#include <_weltoptik.hpp>   
#include <_weltfigur.hpp>
#include <_weltmechanik.hpp>
#include <_weltkollision.hpp>
//-------------- ODE ----------------
/*extern "C"
{*/

  // #include <ode.h>
  // #include <collision_trimesh.h>
//}

//#include <_tonwin.hpp>
//#include <_edition.hpp>
void animieren(){
                                                                MSG m;
                                                                while(PeekMessage(&m,NULL,0,0,PM_NOREMOVE))
                                                                 if(GetMessage(&m,NULL,0,0)){
                                                                   TranslateMessage(&m);
                                                                   DispatchMessage(&m);
                                                                 }else{
                                                                  
                                                                 };
};
void peep(int x){
                                                                for(int i=0;i<x;i++) MessageBeep(0xffffffff);
};
//******************************************************************************************************************************************************************************************************
//                                                               O X Y D 
//******************************************************************************************************************************************************************************************************
class _kugel;
class _gummiband;
class _gummiband:public _basis::_listenknoten<_gummiband>{
    public:
            _gummiband(_kugel*k,_kugel*,_tg staerke);
            _gummiband(_kugel*k,_tg x,_tg y,_tg z,_tg staerke);
            _tg*beschleunigung();
    public:
            _welt*pwelt;            
            _vektor<_to> pfarbe;
            _tg ort[3];
            _tg pbeschleunigung[3];
            _kugel*kugel;
            _kugel*kugel2;
            
            _tg staerke;
            _weltdebuglinie*wl;
};
//******************************************************************************************************************************************************************************************************
//                                                              K U G E L
//******************************************************************************************************************************************************************************************************
class _kugel:public _basis::_listenknoten<_kugel>,public _basis::_liste<_gummiband>,public _kollidierbarkugel{
        public:
        using _basis::_liste<_gummiband>::anfang;
        using _basis::_liste<_gummiband>::naechstes;
        public:
                _kugel(_welt*w,_basis::_liste<_kugel>*l,_vektor<_tg> o,_tg r,_vektor<_tg> v);
                ~_kugel();
                void animieren();
                void farbe(_vektor<_to>);
                _welt*welt();
        private:
                _welt*pwelt;
                _polygon*abgleitpolygon;
                _vektor<_to> pfarbe;
                _weltdebugkugel*ws;
                _vektoranalysis3d<_tg> V3;
};
_kugel::_kugel(_welt*w,_basis::_liste<_kugel>*l,_vektor<_tg> o,_tg r,_vektor<_tg> v):_basis::_listenknoten<_kugel>(l),_kollidierbarkugel(w,o.daten(),v.daten(),r){
                                pwelt=w;
                                pfarbe.setzen(1,1,1);
                                _partition::_zone*z;
                                _partition::_sektor*s;
                                pwelt->anfang(z);
                                s=z->sektor(o);
                                zone(z);
                                stammsektor(s);
                                abgleitpolygon=0;
                                _vektor<_tg> h;
                                h.setzen(ort()[0],ort()[1],ort()[2]);
                                ws=new _weltdebugkugel(pwelt,h,radius(),_vektor<float>(1,1,1));
                                ws->farbe(pfarbe);
};
_kugel::~_kugel(){
                                //delete ws;
};
void _kugel::animieren(){
                                //_win::_tastatur kb;
                               // if(abgleitpolygon) if(kb.knopfrechts()==true) vektor(vektor()+abgleitpolygon->normale()*0.25);
                                _tg gkraft[3];
                                _tg grav[3];
                                grav[0]=0;
                                grav[1]=-0.003;
                                grav[2]=0;
                                
                                
                                _gummiband*git;
                                if(anfang(git))do{
                                 ::addieren(grav,git->beschleunigung());
                                 if(git->kugel2){
                                  ::setzen<_tg>(gkraft,git->beschleunigung());
                                  ::multiplizieren<_tg>(gkraft,-1.0f*0.99f);
                                  ::addieren(git->kugel2->vektor(),gkraft);
                                 };
                                }while(naechstes(git));
                                
                                
                                ::multiplizieren<_tg>(vektor(),0.99f);
                                ::addieren<_tg>(vektor(),grav);//vektor(vektor()*0.99 + grav);
                                
                                
                                if(bewegen(grav)) {
                                 ::multiplizieren<_tg>(vektor(),0.95f);
                                }else{
                                };
                                //DEBUG
                                _vektor<_tg> h;
                                h.setzen(ort()[0],ort()[1],ort()[2]);
                                ws->ort(h);
                                
                                
                                if(anfang(git))do{
                                 if(git->kugel2){
                                  h.setzen(git->kugel2->ort()[0],git->kugel2->ort()[1],git->kugel2->ort()[2]);
                                 }else{
                                 h.setzen(git->ort[0],git->ort[1],git->ort[2]);
                                 };
                                 git->wl->ort(0,h);
                                 
                                 h.setzen(ort()[0],ort()[1],ort()[2]);
                                 git->wl->ort(1,h);
                                }while(naechstes(git));
};
void _kugel::farbe(_vektor<_to> f){
                                pfarbe=f;
                                ws->farbe(pfarbe);
};
_welt*_kugel::welt(){
                                return(pwelt);
};




//******************************************************************************************************************************************************************************************************
//                                                              G U M M I B A N D
//******************************************************************************************************************************************************************************************************
_gummiband::_gummiband(_kugel*k,_tg x,_tg y,_tg z,_tg s):_basis::_listenknoten<_gummiband>(k){
                                pwelt=k->welt();
                                kugel=k;
                                kugel2=0;
                                staerke=s;
                                ort[0]=x;
                                ort[1]=y;
                                ort[2]=z;
                                pfarbe.setzen(0.5,0.5,0.5);
                                
                                _vektor<_tg> h0;
                                _vektor<_tg> h1;
                                h0.setzen(kugel->ort()[0],kugel->ort()[1],kugel->ort()[2]);
                                if(kugel2){
                                 h1.setzen(kugel2->ort()[0],kugel2->ort()[1],kugel2->ort()[2]);
                                }else{
                                 h1.setzen(ort[0],ort[1],ort[2]);
                                };
                                wl=new _weltdebuglinie(kugel->welt(),h0,h1,pfarbe);
                                wl->farbe(pfarbe);
};
_gummiband::_gummiband(_kugel*k,_kugel*k2,_tg s):_basis::_listenknoten<_gummiband>(k){
                                pwelt=k->welt();
                                kugel=k;
                                kugel2=k2;
                                staerke=s;
                                ort[0]=0;
                                ort[1]=0;
                                ort[2]=0;
                                pfarbe.setzen(0.5,0.5,0.5);
                                
                                _vektor<_tg> h0;
                                _vektor<_tg> h1;
                                
                                h0.setzen(kugel->ort()[0],kugel->ort()[1],kugel->ort()[2]);
                                if(kugel2){
                                 h1.setzen(kugel2->ort()[0],kugel2->ort()[1],kugel2->ort()[2]);
                                }else{
                                 h1.setzen(ort[0],ort[1],ort[2]);
                                };
                                wl=new _weltdebuglinie(kugel->welt(),h0,h1,pfarbe);
                                wl->farbe(pfarbe);
};
_tg*_gummiband::beschleunigung(){
                                if(kugel2){
                                 ::subtrahieren<_tg>(pbeschleunigung,kugel2->ort(),kugel->ort());
                                }else{
                                 ::subtrahieren<_tg>(pbeschleunigung,ort,kugel->ort());
                                };
                                ::multiplizieren<_tg>(pbeschleunigung,staerke);
                                return(pbeschleunigung);
};








/*
                            _vektor<double> v=pvektor;
                            double pvl=v.laenge();
                            _vektor<double> grav;
                            grav.setzen(0,-0.03,0);
                            pvektor+=grav;
                            if(abgleitpolygon){
                             if((pvektor*abgleitpolygon->normale())>nahenull) {
                              abgleitpolygon=0;
                              L->schreiben("abgleitzustand AUS durch vektor");
                             }else{
                              _vektor<double> lot;
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
                             _vektor<double> altort=port;
                             if(kollision(port,pvektor,pvl,zuletztkollidiert)){
                              _vektor<double> lot;
                              double para;
                              V3.lotpunktebene(port,altort,grav,lot,para);
                              
                              v.normalisieren();
                              _vektor<double> da=((v*pvl*10)%zuletztkollidiert->normale())*(1-fabs(zuletztkollidiert->normale()*v)); 
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
                              _vektor<double> da=((v*pvl*10)%zuletztkollidiert->normale())*(1-fabs(zuletztkollidiert->normale()*v)); 
                              ws->multiplizierendrehimpuls(0.96);
                              ws->addierendrehimpuls(   da   );
                              pvektor*=0.95;
                              L->schreiben("abgleitkollision aufgetreten");
                             }else{
                              port+=pvektor;
                              _vektor<double> di;
                              di=pvektor%abgleitpolygon->normale();
                              di.normalisieren();
                              di*=(360.0f)*(pvektor.laenge())/(2*_pi*pradius);
                              ws->drehimpuls(di);
                              ws->animieren();
                              
                              pvektor*=0.99;
                              //ws->multiplizierendrehimpuls(0.996);
                             };
                            };
                            
};
bool _kugel::kollision(_vektor<double> o,_vektor<double> v,const double vl,_polygon*&zuletztkollidiert){
                            _vektoranalysis3d<> V3;
                            _basis::_liste<_schnittpunktkollision> schnitte;
                            _liste<_polygon > polylist;
                            _liste<_partition::_sektor > sektorlist;
                            //-------------------------
                            zuletztkollidiert=0;
                            if(psektor==0){
                             psektor=pzone->sektor(o);
                            };
                            if(psektor){
                             erstellenkollisionssequenz(o,v,psektor,&sektorlist,&polylist,&schnitte);
                            };
                     
                            _schnittpunktkollision*sit;
                            if(schnitte.anfang(sit)==false){
                             return(false);
                            }else{
                             //new _weltdebugpfeil(pwelt,o,o+v,0.02,0.015,_vektor<float>(0,1,0));
                             _vektor<double> schnittvektor=sit->ort-o;
                             double sl=schnittvektor.laenge();
                             _vektor<double> lot;
                             V3.lotpunktgerade(o,o+v,sit->normale,lot);
                             schnittvektor=(o+lot*2)-(o+v);
                             schnittvektor.normalisieren();
                             pvektor=schnittvektor*vl;
                             schnittvektor*=fabs(vl-sl);
                           //  new _weltdebugpfeil(pwelt,sit->ort,sit->ort+schnittvektor,0.02,0.015,_vektor<float>(1,1,1));
                             //rekursion enleiten
                             psektor=0;
                             if(kollision(sit->ort+sit->normale *nahenull*2,schnittvektor,vl,zuletztkollidiert)==false) port=sit->ort+sit->normale *nahenull*2+schnittvektor;
                             zuletztkollidiert=sit->polygon;
                             return(true);
                            };
};*/
//******************************************************************************************************************************************************************************************************
//                                                              S P I N N E
//******************************************************************************************************************************************************************************************************
class _spinne:public _skelett{
        public:
                _spinne(_welt*,_vektor<double>);
                void zone(_partition::_zone*);
                void aktualisierensektor();
                void fixieren(int,int,_polygon*);
                void loesen(int,int);
                void drehenx(double);
                void dreheny(double);
                void drehenz(double);
              //  inline void sichernrumpf(int,int);
                void animieren();
                inline void animierenarsch();
                void animierenbein(int,int);
                void ausrichtenbein(int,int,_vektor<double>&,double&);
                void normaleanpassen(bool);
                void transformieren();
                inline void transformieren(_vektor<double>&,_vektor<double>&);
                void kollision(_vektor<double>,_vektor<double>,double,_vektor<double>&);
        private:                
                void anpassenausrichtung(const _vektor<double> neuenormale,_vektor<double>&neuerichtung,_vektor<double>&neueseite);
        public:
                _knochen*vorderleib;
                _knochen*hinterleib;
                _knochen*warze[2][3];
                _knochen*taster[2][3];
                _knochen*bein[2][4][5];

              
                
                //-------------------
                _welt*welt;
                _partition::_zone*pzone;
                double time,tr;
                _vektor<double> port;//steuerort
				_vektor<double> verschiebung;//skelettort=ort+verschiebung;
				_vektor<double> impuls;//trägheitsimpuls des rumpfs
				_vektor<double> vektor;//gewünschte rumpfverschiebung
                _partition::_sektor*lokussektor;
                
                bool fixiert[2][4];//status der fixierung
                _vektor<double> zielfuss[2][4];//fixpunkte zur verankerung
                _partition::_sektor*fusssektor[2][4];
                _polygon*polygonfixiert[2][4];
                _vektor<double> ausrichtung;//dynamische höhen-ausrichtung der beine
                _vektor<double> ausrichtungoptimal[2][4];//otimale(originale) ausrichtung (verbindungslinie)
                _vektor<double> ausrichtungoptimaloriginal[2][4];
				double ausrichtungwinkel[2][4];//kein winkel, sondern verschiebung, die sich orthogonal auf die höhenausrichtung auswirkt				
				double laenge[2][4];// momentane laenge in % (gamma)
				double laengemax[4] ;//in % der maximallaenge (gamma)
				double laengemin[4] ;//in % der maximallaenge (gamma)
				double laengemaxtheoretisch[2][4];
				bool ingueltigerausrichtung[2][4];
				//double beinwinkel[2][4];
				/*double neigungmax[4];//deg-winkel
				double neigungmin[4];//deg-winkel
				double drehungmax[4];//deg-winkel
				double drehungmin[4];//deg-winkel
				*/
                _vektor<double> normale;//figurnormale
                _vektor<double> richtung;//globale firgurenausrichtung
                _vektor<double> seite;//komplett orthonormiertes rechtssystem
                
                
                double schreitenx[2][4];
                double schreitmodus[2][4];
                double schreitdurchlauf[2][4];
                _kurvehermite<> kurve[2][4];
	            bool oa;                
                bool kamverankert;
                
                
                
                //_vektor<double> rumpfalt[2][4];
                _vektoranalysis3d<double> V3;
                _weltdebugkreuz*wc[2][4];
                _weltdebugpfeil*wan[2][4];
                _weltdebugpfeil*was[2][4];
                _weltdebugpfeil*war[2][4];
                _weltdebugkugel*ws;
//                _vektor<double> hilf;
                
};

_spinne::_spinne(_welt*we,_vektor<double> o):_skelett(we,o){
                            int s,c,b;
                            //-----------
                            kamverankert=false;
							port=o;
							oa=true;
							vektor.setzen(0.0,0,0.0);
							verschiebung.setzen(0,0,0);
							impuls.setzen(0,0,0);
                            time=tr=0;
                            welt=we;
                            pzone=0;
                            for (s=0;s<2;s++)
                            for (c=0;c<4;c++) {
                             fixiert[s][c]=false;
                             polygonfixiert[s][c]=0;
                             zielfuss[s][c].setzen(0,0,0);
							 ausrichtungwinkel[s][c]=0;
                             wc[s][c]=0;
                             fusssektor[s][c]=0;
                             schreitenx[s][c]=0;
                             schreitmodus[s][c]=+1;
                             schreitdurchlauf[s][c]=1;
                             wc[s][c]=0;
                             was[s][c]=0;
                             war[s][c]=0;
                             wan[s][c]=0;
                             
                            };

                            vorderleib =new _knochen(this,this, 0, _vektor<double>(0,0,1));    
                            hinterleib =new _knochen(this,this, 0, _vektor<double>(0,-0.1,-1.5));    
                            warze[1][0] =new _knochen(this,hinterleib, hinterleib, _vektor<double>(+0.05,0.05,-0.05));    
                            warze[0][0] =new _knochen(this,hinterleib, hinterleib, _vektor<double>(-0.05,0.05,-0.05));    
                            warze[1][1] =new _knochen(this,warze[1][0], warze[1][0], _vektor<double>(+0.03,0.05,-0.03));    
                            warze[0][1] =new _knochen(this,warze[0][0], warze[0][0], _vektor<double>(-0.03,0.05,-0.03));    
                            warze[1][2] =new _knochen(this,warze[1][1], warze[1][1], _vektor<double>(+0.01,0.05,-0.01));    
                            warze[0][2] =new _knochen(this,warze[0][1], warze[0][1], _vektor<double>(-0.01,0.05,-0.01));    

                            taster[1][0] =new _knochen(this,vorderleib, vorderleib, _vektor<double>(+0.08,0.05,0.05));    
                            taster[0][0] =new _knochen(this,vorderleib, vorderleib, _vektor<double>(-0.08,0.05,0.05));    
                            taster[1][1] =new _knochen(this,taster[1][0], taster[1][0], _vektor<double>(+0.03,0.04,0.2));    
                            taster[0][1] =new _knochen(this,taster[0][0], taster[0][0], _vektor<double>(-0.03,0.04,0.2));    
                            taster[1][2] =new _knochen(this,taster[1][1], taster[1][1], _vektor<double>(-0.01,-0.2,0.01));    
                            taster[0][2] =new _knochen(this,taster[0][1], taster[0][1], _vektor<double>(+0.01,-0.2,0.01));    
                            
                            bein[1][0][0] =new _knochen(this,this, 0, _vektor<double>( 0.4,0,0.8));    
                            bein[0][0][0] =new _knochen(this,this, 0, _vektor<double>(-0.4,0,0.8));    
                            bein[1][1][0] =new _knochen(this,this, 0, _vektor<double>( 0.5,0,0.6));    
                            bein[0][1][0] =new _knochen(this,this, 0, _vektor<double>(-0.5,0,0.6));    
                            bein[1][2][0] =new _knochen(this,this, 0, _vektor<double>( 0.5,0,0.4));    
                            bein[0][2][0] =new _knochen(this,this, 0, _vektor<double>(-0.5,0,0.4));    
                            bein[1][3][0] =new _knochen(this,this, 0, _vektor<double>( 0.4,0,0.2));    
                            bein[0][3][0] =new _knochen(this,this, 0, _vektor<double>(-0.4,0,0.2));    
                            
                            bein[1][0][1] =new _knochen(this,bein[1][0][0],bein[1][0][0], _vektor<double>(-0.1,0.4,0.4));    
                            bein[0][0][1] =new _knochen(this,bein[0][0][0],bein[0][0][0], _vektor<double>(+0.1,0.4,0.4));    
                            bein[1][1][1] =new _knochen(this,bein[1][1][0],bein[1][1][0], _vektor<double>(+0.1,0.5,0.3));    
                            bein[0][1][1] =new _knochen(this,bein[0][1][0],bein[0][1][0], _vektor<double>(-0.1,0.5,0.3));    
                            bein[1][2][1] =new _knochen(this,bein[1][2][0],bein[1][2][0], _vektor<double>(+0.3,0.6,-0.1));    
                            bein[0][2][1] =new _knochen(this,bein[0][2][0],bein[0][2][0], _vektor<double>(-0.3,0.6,-0.1));    
                            bein[1][3][1] =new _knochen(this,bein[1][3][0],bein[1][3][0], _vektor<double>(+0.2,0.5,-0.3));    
                            bein[0][3][1] =new _knochen(this,bein[0][3][0],bein[0][3][0], _vektor<double>(-0.2,0.5,-0.3));    

                            bein[1][0][2] =new _knochen(this,bein[1][0][1],bein[1][0][1], _vektor<double>(+0.2,-0.2,0.7));    
                            bein[0][0][2] =new _knochen(this,bein[0][0][1],bein[0][0][1], _vektor<double>(-0.2,-0.2,0.7));    
                            bein[1][1][2] =new _knochen(this,bein[1][1][1],bein[1][1][1], _vektor<double>(+0.6,-0.2,0.5));    
                            bein[0][1][2] =new _knochen(this,bein[0][1][1],bein[0][1][1], _vektor<double>(-0.6,-0.2,0.5));    
                            bein[1][2][2] =new _knochen(this,bein[1][2][1],bein[1][2][1], _vektor<double>(+0.7,-0.2,-0.2));    
                            bein[0][2][2] =new _knochen(this,bein[0][2][1],bein[0][2][1], _vektor<double>(-0.7,-0.2,-0.2));    
                            bein[1][3][2] =new _knochen(this,bein[1][3][1],bein[1][3][1], _vektor<double>(+0.3,-0.2,-0.8));    
                            bein[0][3][2] =new _knochen(this,bein[0][3][1],bein[0][3][1], _vektor<double>(-0.3,-0.2,-0.8));    

                            bein[1][0][3] =new _knochen(this,bein[1][0][2],bein[1][0][2], _vektor<double>(+0.15,-0.3,0.4));    
                            bein[0][0][3] =new _knochen(this,bein[0][0][2],bein[0][0][2], _vektor<double>(-0.15,-0.3,0.4));    
                            bein[1][1][3] =new _knochen(this,bein[1][1][2],bein[1][1][2], _vektor<double>(+0.25,-0.4,0.15));    
                            bein[0][1][3] =new _knochen(this,bein[0][1][2],bein[0][1][2], _vektor<double>(-0.25,-0.4,0.15));    
                            bein[1][2][3] =new _knochen(this,bein[1][2][2],bein[1][2][2], _vektor<double>(+0.3, -0.5,-0.1));    
                            bein[0][2][3] =new _knochen(this,bein[0][2][2],bein[0][2][2], _vektor<double>(-0.3, -0.5,-0.1));    
                            bein[1][3][3] =new _knochen(this,bein[1][3][2],bein[1][3][2], _vektor<double>(+0.15,-0.4,-0.5));    
                            bein[0][3][3] =new _knochen(this,bein[0][3][2],bein[0][3][2], _vektor<double>(-0.15,-0.4,-0.5));    

                            bein[1][0][4] =new _knochen(this,bein[1][0][3],bein[1][0][3], _vektor<double>(+0.1, -0.05,0.2));    
                            bein[0][0][4] =new _knochen(this,bein[0][0][3],bein[0][0][3], _vektor<double>(-0.1, -0.05,0.2));    
                            bein[1][1][4] =new _knochen(this,bein[1][1][3],bein[1][1][3], _vektor<double>(+0.2, -0.05,0.1));    
                            bein[0][1][4] =new _knochen(this,bein[0][1][3],bein[0][1][3], _vektor<double>(-0.2, -0.05,0.1));    
                            bein[1][2][4] =new _knochen(this,bein[1][2][3],bein[1][2][3], _vektor<double>(+0.2, -0.05,-0.1));    
                            bein[0][2][4] =new _knochen(this,bein[0][2][3],bein[0][2][3], _vektor<double>(-0.2, -0.05,-0.1));    
                            bein[1][3][4] =new _knochen(this,bein[1][3][3],bein[1][3][3], _vektor<double>(+0.05,-0.05,-0.25));    
                            bein[0][3][4] =new _knochen(this,bein[0][3][3],bein[0][3][3], _vektor<double>(-0.05,-0.05,-0.25));    
                            
							ausrichtungwinkel[0][0]=-0.4;//schiefe ausrichtungsebenen
							ausrichtungwinkel[1][0]=+0.4;
							ausrichtungwinkel[0][3]=-0.4;
							ausrichtungwinkel[1][3]=+0.4;
							
							laengemin[0]=0.05;
							laengemin[1]=0.05;
							laengemin[2]=0.05;
							laengemin[3]=0.05;
							laengemax[0]=1-0.05;
							laengemax[1]=1-0.05;
							laengemax[2]=1-0.05;
							laengemax[3]=1-0.05;
                            
                            normale.setzen(0,1,0);
                            richtung.setzen(0,0,1);
                            seite=normale%richtung;

                            for(s=0;s<2;s++)
                            for(c=0;c<4;c++){
                             fixieren(s,c,0);
                             loesen(s,c);
                             schreitenx[s][c]=0;
                             double blo1=bein[s][c][1]->laengeoriginal();
                             double blo2=bein[s][c][2]->laengeoriginal();
                             double blo4=bein[s][c][4]->laengeoriginal();
                             double blo3=bein[s][c][3]->laengeoriginal();
                             laengemaxtheoretisch[s][c]=blo1+blo2+blo3+blo4;
                             ingueltigerausrichtung[s][c]=true;
                             ausrichtungoptimal[s][c].setzen(0,0,0);
                             for(b=1;b<5;b++){
                              ausrichtungoptimal[s][c]+=bein[s][c][b]->vektororiginal();
                              ausrichtungoptimaloriginal[s][c]=ausrichtungoptimal[s][c];
                             };
                             laenge[s][c]=ausrichtungoptimal[s][c].laenge()/laengemaxtheoretisch[s][c];
                            };
                            /*
                            fixieren(0,0);
                            fixieren(0,1);
                            fixieren(0,2);
                            fixieren(0,3);
                            fixieren(1,0);
                            fixieren(1,1);
                            fixieren(1,2);
                            fixieren(1,3);
                            */
                            aktualisierensektor();
                            ws=new _weltdebugkugel(welt,ort(),0.7f,_vektor<float>(0.2f,0.8f,1.0f));
};
void _spinne::zone(_partition::_zone*z){
                            pzone=z;
};
void _spinne::aktualisierensektor(){
                            if(pzone){
                             lokussektor=pzone->sektor(ort());
                             for(int s=0;s<2;s++)
                              for(int c=0;c<4;c++)
                               fusssektor[s][c]=pzone->sektor(zielfuss[s][c]);
                            };
};
void _spinne::fixieren(int s,int c,_polygon*p){
                            int i;
                            //----------
                            polygonfixiert[s][c]=p;
                            fixiert[s][c]=true;
                            zielfuss[s][c]=ort();
                            for(i=0;i<5;i++){
                             zielfuss[s][c]+=bein[s][c][i]->vektor();
                            };
                            wc[s][c]=new _weltdebugkreuz(welt,zielfuss[s][c],0.1,_vektor<float>(1,0,0));
};
void _spinne::loesen(int s,int c){
                            fixiert[s][c]=false;
                            
                            if(wc[s][c]) {
                             delete wc[s][c];
                             wc[s][c]=0;
                            };
};
void _spinne::drehenx(double w){
                            richtung.rotx(w);
                            normale.rotx(w);
                            seite=normale%richtung;
                            transformieren();
};
void _spinne::dreheny(double w){
                            richtung.roty(w);
                            normale.roty(w);
                            seite=normale%richtung;
                            transformieren();
};
void _spinne::drehenz(double w){
                            richtung.rotz(w);
                            normale.rotz(w);
                            seite=normale%richtung;
                            transformieren();
};
void _spinne::transformieren(){//alles ausrichten
                            int s,c;
                            transformieren(vorderleib->vektororiginal(),vorderleib->vektor());
                            transformieren(hinterleib->vektororiginal(),hinterleib->vektor());
                            for(s=0;s<2;s++){
                            for(c=0;c<4;c++){
                             transformieren(bein[s][c][0]->vektororiginal(),bein[s][c][0]->vektor());
                             transformieren(ausrichtungoptimaloriginal[s][c],ausrichtungoptimal[s][c]);
                            };
                            for(c=0;c<3;c++){
                             transformieren(taster[s][c]->vektororiginal(),taster[s][c]->vektor());
                             transformieren(warze[s][c]->vektororiginal(),warze[s][c]->vektor());
                            };
                            };
};
void _spinne::transformieren(_vektor<double>&v,_vektor<double>&e){
                            e=seite*v[0]+normale*v[1]+richtung*v[2];
};
void _spinne::animieren(){
                            tr+=1; 
                            time=tr;//sin(tr*_ph)*1000;

							
							verschiebung-=vektor;
                           

							_win::_tastatur kb;
							_kamera<>*cam;
							welt->anfang(cam);
							_vektor<double> v;
							double vl;
							double ss;
							_vektor<double> front;
							_vektor<double> seite;
							
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
							 if(kamverankert) cam->yaw(cam->yaw()-0.3*ss);
							 oa=false;
							};
							if(kb.taste(89)){
							 drehenx(-0.3*ss);
							 if(kamverankert) cam->yaw(cam->yaw()+0.3*ss);
							 oa=false;
							};
							
							if(kb.taste(67)){
							 dreheny(0.3*ss);
							 if(kamverankert) cam->rot(cam->rot()-0.3*ss);
							 oa=false;
							};
							if(kb.taste(86)){
							 dreheny(-0.3*ss);
							 if(kamverankert) cam->rot(cam->rot()+0.3*ss);
							 oa=false;
							};
							
							if(kb.taste(70)){
							 drehenz(0.3*ss);
							 if(kamverankert) cam->rol(cam->rol()-0.3*ss);
							 oa=false;
							};
							if(kb.taste(71)){
							 drehenz(-0.3*ss);
							 if(kamverankert) cam->rol(cam->rol()+0.3*ss);
							 oa=false;
							};
							cam->aktualisieren();
							if(kb.taste(75)){
 							 v.zufallsberechnen();
 							 v*=0.4;//stoßkraft;
							 impuls=v;
							};
							
							
							port+=vektor;
							lokussektor=pzone->sektor(ort());
							_vektor<double> e;
							kollision(ort(),port+verschiebung,0.7,e);
							ort(e);
							ws->ort(ort());
							
							
							
							if(kamverankert) cam->ort(ort()+normale*0.3);
							v=-verschiebung;
							vl=v.laenge();
							impuls+=v*0.2;//federkraft 20%
					        verschiebung+=impuls;
							impuls*=0.9;//trägheitsdämpfer 10%
							   
                            animierenbein(0,0);
                            animierenbein(0,1);
                            animierenbein(0,2);
                            animierenbein(0,3);
                            animierenbein(1,0);
                            animierenbein(1,1);
                            animierenbein(1,2);
                            animierenbein(1,3);
                            
                        
                         //   animierenarsch();
};
void _spinne::animierenarsch(){
                            _vektor<double> n;
                            _vektor<double> a;
                            _vektor<double> e;
                           //---------------
                            n=bein[0][0][0]->vektor() % richtung;
                            double fb=((sin(3*tr*_ph)*0.5))*10;
                            V3.rotieren(n,hinterleib->vektororiginal(),fb,hinterleib->vektor());
                            V3.rotieren(n,vorderleib->vektororiginal(),-fb*0.6,vorderleib->vektor());                            
};
/*
void _spinne::sichernrumpf(int s,int c){
                            if(fixiert[s][c]) rumpfalt[s][c]=ort()+bein[s][c][0]->vektor();
};
*/
void _spinne::animierenbein(int s,int c){
                            _vektor<double> vbneu;
                            double vbneul;
                            double gamma;
                            _vektor<double> q;
                            double wn;
                            _vektor<double> e;
                            _vektor<double> rumpf;
                            _vektor<double> neu;
                            bool koll;
                            _polygon*kollpoly;
                            double blomax=bein[s][c][1]->laengeoriginal()+bein[s][c][2]->laengeoriginal()+bein[s][c][3]->laengeoriginal()+bein[s][c][4]->laengeoriginal();
                            double sicherheitslaenge=blomax*0.995;
                            rumpf=ort()+bein[s][c][0]->vektor();
                            vbneu=rumpf-zielfuss[s][c];
                            vbneul=vbneu.laenge();  
                            if(vbneul>sicherheitslaenge){
                             vbneu*=sicherheitslaenge/vbneul;
                         // ziel=rumpfneu-vbneu;
                             vbneul=sicherheitslaenge;  
                            };
                            gamma=vbneul/blomax;
                            //---------------
                            q=-vbneu;
                            q.normalisieren();  
                            e=ausrichtungoptimal[s][c];
                            e.normalisieren();                           
                            wn=q*e;//normale.winkel(vbneu);
                            if(fixiert[s][c]){
                             if(
                             (wn<0.8)||
                             (gamma<laengemin[c])||
                             (gamma>laengemax[c])){
                             
                              if(vektor.laenge()>nahenull){
                              e=zielfuss[s][c]-rumpf;
                              e.normalisieren();
                              q=vektor;
                              q.normalisieren();
                              if((q*e)<0){
                               _vektor<double> rumpflot;
                               double rumpflotl;
                               double schrittmax=ausrichtungoptimaloriginal[s][c].laenge();
                               double ebl;
                               _vektor<double> n=/*normale;//*/polygonfixiert[s][c]->normale();
                               _vektor<double> v;
                               _vektor<double> lot;
                               _vektor<double> ziel;
                               _vektor<double> neueausr;
                               double para;
                               _polygon*p=polygonfixiert[s][c];
                               _vektor<double> ns;
                               _vektor<double> nr;
                               _vektor<double> h;
                              
                                 
                              
                               V3.lotpunktebene(rumpf,p->mitte(),p->normale(),rumpflot,para);
                               rumpflotl=rumpflot.laenge();
                               ebl=sqrt(schrittmax*schrittmax + rumpflotl*rumpflotl);
                               anpassenausrichtung(p->normale(),nr,ns);
                               h=ausrichtungoptimaloriginal[s][c];
                               neueausr=ns*h[0]+polygonfixiert[s][c]->normale()*h[1]+nr*h[2];
                               V3.lotpunktebene(neueausr,_vektor<double>(0,0,0),p->normale(),lot,para);
                               neueausr=neueausr+lot;
                               neueausr.normalisieren();
                               neueausr*=ebl;
                              
                              
                               schreitenx[s][c]=0;
                               schreitmodus[s][c]=1;
                               schreitdurchlauf[s][c]=0;
                               kurve[s][c].ort(0,zielfuss[s][c]);
                              
                              V3.lotpunktebene(vektor,_vektor<double>(0,0,0),p->normale(),lot,para);
                              para=vektor.laenge()*45;
                              v=vektor+lot;
                              if(v.laenge()>0){
                               v.normalisieren();
                               v*=para;
                              };
 
                               ziel=rumpf+rumpflot+neueausr+v;
                            
                              
                              /*_vektor<double> ns;
                              _vektor<double> nr;
                              _vektor<double> neueausr;
                              _vektor<double> neurumpf;
                              
                              if(war[s][c]) delete war[s][c];
                              if(wan[s][c]) delete wan[s][c];
                              
                              
                              anpassenausrichtung(n,nr,ns);
                              
                              h=ausrichtungoptimaloriginal[s][c];
                              
                              wan[s][c]=new _weltdebugpfeil(W,fuss[s][c],fuss[s][c]+n ,0.01,0.01,_vektor<float>(1,0,0));
                              war[s][c]=new _weltdebugpfeil(W,fuss[s][c],fuss[s][c]+nr,0.01,0.01,_vektor<float>(0,0,1));
                             
                             
                              
                              
                              
                              
                              
                              
                               neueausr=ns*h[0]+polygonfixiert[s][c]->normale()*h[1]+nr*h[2];
                               h=bein[s][c][0]->vektororiginal();
                               neurumpf=ns*h[0]+polygonfixiert[s][c]->normale()*h[1]+nr*h[2];;
                               
                              V3.lotpunktebene(vektor,_vektor<double>(0,0,0),polygonfixiert[s][c]->normale(),lot,para);
                              
                              */
                              if(was[s][c]) delete was[s][c];
                              was[s][c]=new _weltdebugpfeil(welt,zielfuss[s][c],ziel,0.01,0.01,_vektor<float>(1,0,1));
                              
                              kurve[s][c].ort(1,ziel);
                              e=kurve[s][c].ort(1)-kurve[s][c].ort(0);
                              double fn=e.laenge()*0.5;
                              if(fn>2) fn=2;
                              kurve[s][c].vektor(0,n*3*fn);
                              kurve[s][c].vektor(1,-n*2*fn);
                             
                             
                             
                             // e=kurve[s][c].ort(1)-kurve[s][c].ort(0);
                             // e.normalisieren();
                             // if((e* *p)>-0.1f){
                              loesen(s,c);	
                              };
                             };
                             // };
						     };
							}else{
							 //---------------------------------- schreitmodus ---------------------------------
							 schreitenx[s][c]+=1.0f/30.0f;
							 if(schreitenx[s][c]<=1){
							  neu=kurve[s][c].berechnen(schreitenx[s][c]);
							  if(fusssektor[s][c]){
							   _vektor<double> f0=rumpf-vbneu;
							   _vektor<double> fn=neu-rumpf;
							   double fnl=fn.laenge();
   							   if(fnl>sicherheitslaenge){
                                fn*=sicherheitslaenge/fnl;
							   };
							   fn+=rumpf;
							   zielfuss[s][c]+=fusssektor[s][c]->kollidierendervektor(f0,fn-f0,fusssektor[s][c],koll,kollpoly);
							  // neu;
							   if(koll){
							    ausrichtenbein(s,c,vbneu,gamma);
							    fixieren(s,c,kollpoly);
							    schreitenx[s][c]=0;
							   }else{
							   };
							  };
							 }else{
							  schreitdurchlauf[s][c]+=1;
							  if(schreitdurchlauf[s][c]<6) {
							   //-------------------------------- rudern ---------------------------------------
							   schreitmodus[s][c]*=-1;
							   kurve[s][c].ort(0,kurve[s][c].ort(1));
							   kurve[s][c].ort(1,rumpf+ausrichtungoptimal[s][c]*(1+(schreitmodus[s][c]*0.3)));
 							   kurve[s][c].vektor(0,normale* 3*schreitmodus[s][c]);
 							   kurve[s][c].vektor(1,normale*-3*schreitmodus[s][c]);
  							   schreitenx[s][c]=0;
  							   
							  }else{
							   if(schreitdurchlauf[s][c]==6){
							    //-------------------------------- ruhezustand einleiten -----------------------
							    polygonfixiert[s][c]=0;
							    kurve[s][c].ort(0,kurve[s][c].ort(1));
 							    kurve[s][c].vektor(0,kurve[s][c].vektor(1));
							    kurve[s][c].ort(1,rumpf+ausrichtungoptimal[s][c]);
							    kurve[s][c].vektor(1,_vektor<double>(0,0,0));
							    schreitenx[s][c]=0;
							    if(vektor.laenge()>nahenull) schreitdurchlauf[s][c]=0;
							   }else{
							    //------------------------------- ruhezustand ----------------------------------
							    kurve[s][c].ort(0,kurve[s][c].ort(1));
 							    kurve[s][c].vektor(0,kurve[s][c].vektor(1));
							    kurve[s][c].ort(1,rumpf+ausrichtungoptimal[s][c]);
							    kurve[s][c].vektor(1,_vektor<double>(0,0,0));
							    schreitenx[s][c]=0;
							    if(vektor.laenge()>nahenull) schreitdurchlauf[s][c]=0;
							   };
							  };
							 };
							};
							ausrichtenbein(s,c,vbneu,gamma);
                            
};
void _spinne::ausrichtenbein(int s,int c,_vektor<double>&vbneu,double&gamma){
                             //berechnung zur verankerung durchführen 
                             //_vektor<double> vbneu;
                             _vektor<double> rumpfneu;
							 _vektor<double> e;
                             double alpha[3];
                             _vektor<double> gelenkneu[3];
                             double h[3];
                             //double hh[3];
                             double vbneul;
                             _vektor<double> ziel=zielfuss[s][c];
                           
                           
                             double blo1=bein[s][c][1]->laengeoriginal();
                             double blo2=bein[s][c][2]->laengeoriginal();
                             double blo4=bein[s][c][4]->laengeoriginal();
                             double blo3=bein[s][c][3]->laengeoriginal();
                             double blomax=blo1+blo2+blo3+blo4;
                             double blon1=blo1/blomax;
                             double blon2=blo2/blomax;
                             double blon3=blo3/blomax;
                             double blon4=blo4/blomax;
                            // double gamma;                             
                             
                             double sicherheitslaenge=blomax*0.995;
                             rumpfneu=ort()+bein[s][c][0]->vektor();
                             vbneu=rumpfneu-ziel;
                             vbneul=vbneu.laenge();  
                             if(vbneul>sicherheitslaenge){
                              vbneu*=sicherheitslaenge/vbneul;
                              ziel=rumpfneu-vbneu;
                              vbneul=sicherheitslaenge;  
                             };
                             laenge[s][c]=gamma=vbneul/blomax;
                             alpha[0]=blon4*0.99f*(1-gamma*gamma)+ blon4*gamma;
                             alpha[1]=0.2f*(1-gamma) + (blon4+blon3)*gamma;
                             if(alpha[0]>( (blo4      -nahenull)/vbneul)) alpha[0]=((blo4-nahenull)/vbneul);
                             if(alpha[1]>(((blo4+blo3)-nahenull)/vbneul)) alpha[1]=(((blo4+blo3)-nahenull)/vbneul);
                             h[0]=sqrt(-pow(vbneul*alpha[0],2)           + pow(blo4,2));
                             h[1]=sqrt(-pow(vbneul*(alpha[1]-alpha[0]),2)+ pow(blo3,2));
						     e=(normale%vbneu);
						     e.normalisieren();
                             ausrichtung=e%vbneu; 
                             ausrichtung.normalisieren();
                             ausrichtung*=-1;
							 ausrichtung+=e*ausrichtungwinkel[s][c];
							 ausrichtung.normalisieren();
					         gelenkneu[0]=ziel+vbneu*alpha[0]+ausrichtung* h[0];
                             gelenkneu[1]=ziel+vbneu*alpha[1]+ausrichtung*(h[0]+h[1]);
                             //--------------------------------------------------- ANPASSUNG
                             _vektor<double> v;
                             _vektor<double> t;
                             _vektor<double> q;
                             double l0,l1,vl0,vl;
                             l0=bein[s][c][2]->laengeoriginal();
                             l1=bein[s][c][1]->laengeoriginal();
                             v=rumpfneu-gelenkneu[1];
                             vl=v.laenge();
                             vl0=(((l1*l1)-(l0*l0)-(vl*vl))/(-2.0f*vl*l0))*l0;
                             t=gelenkneu[1]+v*(vl0/vl);
                             q=(vbneu%ausrichtung)%v;
                             q.normalisieren();
                             gelenkneu[2]=t+q*sqrt((l0*l0)-(vl0*vl0));
                             //---------------------------------------------------
                             bein[s][c][4]->vektor(ziel-gelenkneu[0]);
                             bein[s][c][3]->vektor(gelenkneu[0]-gelenkneu[1]);
                             bein[s][c][2]->vektor(gelenkneu[1]-gelenkneu[2]);
                             bein[s][c][1]->vektor(gelenkneu[2]-rumpfneu);
                              
};
void _spinne::normaleanpassen(bool ortanpassen){
                            _vektor<double> solln;
                            _vektor<double> sollo;
                            _vektor<double> e;
                            _vektor<double> a;
                            double anzahl,w;
                            int s,c;
                            //----------------
                            solln.setzen(0,0,0);
                            sollo.setzen(0,0,0);
                            anzahl=0;
                            for(s=0;s<2;s++)
                            for(c=0;c<4;c++){
                             if(polygonfixiert[s][c]){
                              solln+=polygonfixiert[s][c]->normale();
                              sollo+=zielfuss[s][c]-(bein[s][c][0]->vektor()+ausrichtungoptimal[s][c]);
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
void _spinne::anpassenausrichtung(const _vektor<double> neuenormale,_vektor<double>&neuerichtung,_vektor<double>&neueseite){
                            _vektor<double> a;
                            _vektor<double> e;
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
void _spinne::kollision(_vektor<double> start,_vektor<double> ende,double r,_vektor<double>&neuesende){
                            _partition::_polygon*pit;
                            //-------------------------
                            neuesende=ende;
                            if(lokussektor)
                            if(lokussektor->anfang(pit))do{
                             if(pit->portal()){
                              /*if(pit->innerhalbkugelverschiebungsvolumen(start,ende,r)){
                               pit->visualisieren(_vektor<float>(0,1,1));
                               _listenknoten<_partition::_polygon >*lnpit;
                               if(pit->anfang(lnpit))do{
                                lnpit->objekt()->visualisieren(_vektor<float>(0,1,1));
                               }while(pit->naechstes(lnpit));
                              };*/
                              
                             }else{
                              //if(pit->polygon()->innerhalbkugelverschiebungsvolumen(start,ende,r,true)){
                             //  pit->polygon()->visualisieren(_vektor<float>(0,1,1));
                               _vektor<double> vektor=ende-start;
                               _vektor<double> schnittpunkt;
                               _vektor<double> schnittvektor;
                               _vektor<double> n;
                               //double parameter;
                              /* if(pit->polygon()->schnittpunktradialverbreitert(start,vektor,r,n,schnittpunkt,parameter)){
                               schnittvektor=schnittpunkt-start;
                               double vl=vektor.laenge();
                               double sl=schnittvektor.laenge();
                               
                               V3.reflektierenpunktnormale(start,schnittpunkt,n,neuesende);
                               schnittvektor=neuesende-schnittpunkt;
                               schnittvektor.normalisieren();
                               schnittvektor*=fabs(vl-sl);
                               neuesende=schnittpunkt+schnittvektor;
                               }else{
                                
                               };
                               
                               */
                              //};
                             };
                            }while(lokussektor->naechstes(pit));
};
//******************************************************************************************************************************************************************************************************
//                                                              T E S T W O R L D 
//******************************************************************************************************************************************************************************************************
class _testwelt{
        public:
                _testwelt(HINSTANCE);
                ~_testwelt();
                void testspeichern();
                void testladen();
                void testcompile(_welt*w);
                void testbestrahlung();
                void testbaumoctal();
                void testkugel();
                void testsichtbarkeit();
                _netz*erzeugenraum(_welt*w,_vektor<_tg> h,_vektor<_tg> v0,_vektor<_tg> v1,_vektor<_tg> v2,_textur<>*t,_textur<>*tb,_textur<>*td);
                void visualisierenbaum(_welt*we,_baumoctalwuerfel<_weltdebugkreuz,double>*w);
                void associatetexture(_polygon*);
                void statistik(_welt*);
                void texturen();
                void texturenfigur();
                void display(_welt*,_kamera<>*,_figurspieler*);
                void szenekonstruktion(_welt*&,_kamera<>*&,_figurspieler*&);
                void szenekonstruktionbestrahlung(_welt*&,_kamera<>*&,_figurspieler*&,double);
                void szenedestruktion(_welt*);
                void oxydstein(_welt*w,int x,int y,int wx,int wy,_textur<_to>*dach,_textur<_to>*seite,_liste<_netz>*os);
                 
        private:
                HINSTANCE hi;
                _win::_system*s;
                _win::_zeit timer;
                _zufallsgenerator<double> zufall;
                _textur<>*textur[128];
                _bildtga<>*bild[256];
                int texturanzahl;
                unsigned int time[4];
                _basis::_liste<_textur<> > tl;
};
_testwelt::_testwelt(HINSTANCE h){
                                                                //------------------------------------ system anlegen ------------------------------------------------
                                                                S=s=new _win::_system(h);
                                                                hi=h;
};
_testwelt::~_testwelt(){
                                                                delete s;
                                                                S=0;
                                                                L->schreiben("System wurde destruiert.");
};                 
void _testwelt::statistik(_welt*w){
                                                                //--------------------------------------- weltstatistik -------------------------------------
                                                                _logbuch*WS;
                                                                _zeichenkette<char> wss="Weltstatistik.txt";
                                                                WS=new _logbuch(wss);
                                                                WS->schreiben("-------------------------------------Nach der Präparation-------------------------------------");
                                                                unsigned int sbvector;
                                                                unsigned int sbmesh;
                                                                unsigned int sbpolygon;
                                                                unsigned int sbvertex;
                                                                unsigned int sbconnector;
                                                                unsigned int sbmapvector;
                                                                unsigned int sbzone;
                                                                unsigned int sbbsp;
                                                                unsigned int sbsector;
                                                                unsigned int sbsectorpolygon;
                                                                unsigned int sbsectorportal;
                                                                unsigned int sbsectorportalvertex;
                                                                unsigned int sbvispolynode;
                                                                unsigned int sbvissectornode;
                                                                unsigned int sbges;
                                                                unsigned int sb;
                                                                sbvector=sizeof(_vektor<>);
                                                                sbmesh=sizeof(_netz)+3*sizeof(typgeometrie);
                                                                sbpolygon=sizeof(_polygon)+(11*3*sizeof(typgeometrie));
                                                                sbvertex=sizeof(_vertex)+(3*3*sizeof(typgeometrie));
                                                                sbconnector=sizeof(_verbindervertexpolygon)+3*sizeof(typoptik);
                                                                sbmapvector=sizeof(_bildvektor<>)+2*sizeof(typgeometrie);
                                                                sbzone=sizeof(_partition::_zone)+(2*3*sizeof(typgeometrie));
                                                                sbbsp=sizeof(_partition::_ebene);
                                                                sbsector=sizeof(_partition::_sektor)+3*sizeof(typgeometrie);//+ alle listenkonten auf poly (sichtbarkeitslisten)
                                                                sbsectorpolygon=sizeof(_partition::_polygon)+3*sizeof(typgeometrie);
                                                                sbsectorportal=sizeof(_partition::_polygon)+3*sizeof(typgeometrie);
                                                                sbsectorportalvertex=sizeof(_partition::_vertex)+3*sizeof(typgeometrie);
                                                                sbvispolynode=sizeof(::_listenknoten< ::_polygon >);
                                                                sbvissectornode=sizeof(::_listenknoten< _partition::_sektor >);
                                                                WS->schreiben("Anzahl der Drahtgitter                              :",(int)w->anzahlnetz());
                                                                WS->schreiben("Anzahl der Polygone                                 :",(int)w->anzahlpolygon());
                                                                WS->schreiben("Anzahl der Vertices                                 :",(int)w->anzahlvertex());
                                                                WS->schreiben("Anzahl der Connectoren                              :",(int)w->anzahlverbindervertexpolygon());
                                                                WS->schreiben("Anzahl der Mapvektoren                              :",(int)w->anzahlbildvektor());
                                                                WS->schreiben("Anzahl der Zonen                                    :",(int)w->anzahlzone());
                                                                WS->schreiben("Anzahl der BSP Knoten                               :",(int)w->anzahlbaumknoten());
                                                                WS->schreiben("Anzahl der Sektoren                                 :",(int)w->anzahlsektor());
                                                                WS->schreiben("Anzahl der Sektorpolygone                           :",(int)w->anzahlsektorpolygon());
                                                                WS->schreiben("Anzahl der Sektorportale                            :",(int)w->anzahlsektorportal());
                                                                WS->schreiben("Anzahl der Sektorportalvertex                       :",(int)w->anzahlsektorportalvertex());
                                                                WS->schreiben("Anzahl der Polygonsichtbarkeiten                    :",(int)w->anzahlsektorsichtbarkeitpolygon());
                                                                WS->schreiben("Anzahl der Sektorsichtbarkeiten                     :",(int)w->anzahlsektorsichtbarkeitsektor());
                                                                WS->schreiben("--------------------------------------------------------------");
                                                                WS->schreiben("Speicherbedarf eines Vectors (ohne Feld)            :",(int)sbvector);
                                                                WS->schreiben("Speicherbedarf eines Drahtgitters                   :",(int)sbmesh);
                                                                WS->schreiben("Speicherbedarf eines Polygons                       :",(int)sbpolygon);
                                                                WS->schreiben("Speicherbedarf eines Vertex                         :",(int)sbvertex);
                                                                WS->schreiben("Speicherbedarf eines Connectors                     :",(int)sbconnector);
                                                                WS->schreiben("Speicherbedarf eines Mapvektors                     :",(int)sbmapvector);
                                                                WS->schreiben("Speicherbedarf einer Zone                           :",(int)sbzone);
                                                                WS->schreiben("Speicherbedarf eines BSP Knoten                     :",(int)sbbsp);
                                                                WS->schreiben("Speicherbedarf eines Sektors                        :",(int)sbsector);
                                                                WS->schreiben("Speicherbedarf eines Sektorpolygons                 :",(int)sbsectorpolygon);
                                                                WS->schreiben("Speicherbedarf eines Sektorportals                  :",(int)sbsectorportal);
                                                                WS->schreiben("Speicherbedarf eines Sektorportalvertex             :",(int)sbsectorportalvertex);
                                                                WS->schreiben("Speicherbedarf einer Polygonsichtbarkeit            :",(int)sbvispolynode);
                                                                WS->schreiben("Speicherbedarf einer Sektorsichtbarkeit             :",(int)sbvissectornode);
                                                                WS->schreiben("--------------------------------------------------------------");
                                                                sbges=0;
                                                                sb=w->anzahlnetz()*sbmesh;sbges+=sb;                             WS->schreiben("Speicherbedarf aller Drahtgitter                    :",(int)sb);
                                                                sb=w->anzahlpolygon()*sbpolygon;sbges+=sb;                       WS->schreiben("Speicherbedarf aller Polygone                       :",(int)sb);
                                                                sb=w->anzahlvertex()*sbvertex;sbges+=sb;                         WS->schreiben("Speicherbedarf aller Vertex                         :",(int)sb);
                                                                sb=w->anzahlverbindervertexpolygon()*sbconnector;sbges+=sb;      WS->schreiben("Speicherbedarf aller Connectoren                    :",(int)sb);
                                                                sb=w->anzahlbildvektor()*sbmapvector;sbges+=sb;                   WS->schreiben("Speicherbedarf aller Mapvektoren                    :",(int)sb);
                                                                sb=w->anzahlzone()*sbzone;sbges+=sb;                             WS->schreiben("Speicherbedarf aller Zonen                          :",(int)sb);
                                                                sb=w->anzahlbaumknoten()*sbbsp;sbges+=sb;                          WS->schreiben("Speicherbedarf aller BSP Knoten                     :",(int)sb);
                                                                sb=w->anzahlsektor()*sbsector;sbges+=sb;                         WS->schreiben("Speicherbedarf aller Sektoren                       :",(int)sb);
                                                                sb=w->anzahlsektorpolygon()*sbsectorpolygon;sbges+=sb;           WS->schreiben("Speicherbedarf aller Sektorpolygone                 :",(int)sb);
                                                                sb=w->anzahlsektorportal()*sbsectorportal;sbges+=sb;             WS->schreiben("Speicherbedarf aller Sektorportale                  :",(int)sb);
                                                                sb=w->anzahlsektorportalvertex()*sbsectorportalvertex;sbges+=sb; WS->schreiben("Speicherbedarf aller Sektorportalvertex             :",(int)sb);
                                                                sb=w->anzahlsektorsichtbarkeitpolygon()*sbvispolynode;sbges+=sb;   WS->schreiben("Speicherbedarf aller Polygonsichtbarkeiten          :",(int)sb);
                                                                sb=w->anzahlsektorsichtbarkeitsektor()*sbvissectornode;sbges+=sb;  WS->schreiben("Speicherbedarf aller Sektorsichtbarkeiten           :",(int)sb);
                                                                WS->schreiben("Speicherbedarf aller Objekte                        :",(int)sbges);
                                                                WS->schreiben("--------------------------------------------------------------");
                                                                WS->schreiben("Zeitdauer der Texturenkonstruktion [ms]             :",((int)(time[1]-time[0])));
                                                                WS->schreiben("Zeitdauer der Weltkonstruktion [ms]                 :",((int)(time[2]-time[1])));
                                                                WS->schreiben("Zeitdauer der Intersektion [ms]                     :",(int)w->zeitintersektion());
                                                                WS->schreiben("Zeitdauer der Zonenkonstruktion [ms]                :",(int)w->zeitzonenerzeugung());
                                                                WS->schreiben("Zeitdauer der Halbraumzerteilung [ms]               :",(int)w->zeitbinaerehalbraumteilung());
                                                                WS->schreiben("Zeitdauer der Sektorkonstruktion [ms]               :",(int)w->zeitsektorerzeugung());
                                                                WS->schreiben("Zeitdauer der Sektorverknuepfung [ms]               :",(int)w->zeitsektorverbindung());
                                                                WS->schreiben("Zeitdauer der Sichtbarkeit [ms]                     :",(int)w->zeitsichtbarkeit());
                                                                WS->schreiben("Zeitdauer der nicht-portalen Vertexdestruktion [ms] :",(int)w->zeitloeschennichtportalvertex());
                                                                WS->schreiben("Zeitdauer der Bestrahlung [ms]                      :",(int)w->zeitbestrahlung());
                                                                WS->schreiben("Gesamtzeitdauer der Präparation [ms]                :",((int)(time[3]-time[0])));
                                                                WS->schreiben("--------------------------------------------------------------");
                                                                delete WS;
                                                                WS=0;
                                                                L->schreiben("Weltstatistik wurde erzeugt.");
};                                                                 
void _testwelt::texturen(){
                                                                _bild<>*m;
                                                                //------------------------------------ TEXTUREN LADEN, INITIALISIEREN --------------------------------
                                                                texturanzahl=14;
                                                                
                                                                textur[0]=new _textur<>(&tl,"m");
                                                                bild[0]=new _bildtga<>("textur//oxydbodenplatte00.tga",1,1);
                                                                textur[0]->einfuegenbitmap(bild[0]);
                                                                bild[0]->tiefereskalieren(1);
                                                                bild[0]->datentausch(0,2);

                                                                textur[1]=new _textur<>(&tl,"w");
                                                                bild[1]=new _bildtga<>("textur//oxydsteinpyramide00.tga",1,1);                                                               
                                                                textur[1]->einfuegenbitmap(bild[1]);
                                                                bild[1]->tiefereskalieren(1);
                                                                bild[1]->datentausch(0,2);

                                                                textur[2]=new _textur<>(&tl,"s");
                                                                bild[2]=new _bildtga<>("textur//oxydsteinkreuz.tga",1,1);
                                                                textur[2]->einfuegenbitmap(bild[2]);
                                                                bild[2]->tiefereskalieren(1);
                                                                bild[2]->datentausch(0,2);

                                                                textur[3]=new _textur<>(&tl,"s");
                                                                bild[3]=new _bildtga<>("textur//marmor01.tga",1,1);
                                                                textur[3]->einfuegenbitmap(bild[3]);
                                                                bild[3]->tiefereskalieren(1);
                                                                bild[3]->datentausch(0,2);
                                                                
                                                                textur[4]=new _textur<>(&tl,"b");
                                                                bild[4]=new _bildtga<>("textur//trench00maske.tga",1,1);
                                                                textur[4]->einfuegenbitmap(bild[4]);
                                                                bild[4]->tiefereskalieren(1);
                                                                bild[4]->datentausch(0,2);
                                                                /*m=new _bildtga<>("td22_duenn.tga",1,1);
                                                                textur[4]->einfuegenspecularmap(m);
                                                                m->tiefereskalieren(1);
                                                                m->datentausch(0,2);
                                                                m->wiederholung(0,false);
                                                                m->wiederholung(1,false);*/

                                                                textur[5]=new _textur<>(&tl,"h");
                                                                bild[5]=new _bildtga<>("textur//trench00.tga",1,1);
                                                                textur[5]->einfuegenbitmap(bild[5]);
                                                                bild[5]->tiefereskalieren(1);
                                                                bild[5]->datentausch(0,2);
                                                                m=new _bildtga<>("textur//td22_duenn.tga",1,1);
                                                                textur[5]->einfuegenspecularmap(m);
                                                                m->tiefereskalieren(1);
                                                                m->datentausch(0,2);
                                                                m->wiederholung(0,false);
                                                                m->wiederholung(1,false);

                                                                textur[6]=new _textur<>(&tl,"t");
                                                                bild[6]=new _bildtga<>("textur//brickrtc.tga",1,1);
                                                                textur[6]->einfuegenbitmap(bild[6]);
                                                                bild[6]->tiefereskalieren(1);
                                                                bild[6]->datentausch(0,2);
                                                                m=new _bildtga<>("textur//td22_duenn.tga",1,1);
                                                                textur[6]->einfuegenspecularmap(m);
                                                                m->tiefereskalieren(1);
                                                                m->datentausch(0,2);
                                                                m->wiederholung(0,false);
                                                                m->wiederholung(1,false);

                                                                textur[7]=new _textur<>(&tl,"j");
                                                                bild[7]=new _bildtga<>("textur//wall05.tga",1,1);
                                                                textur[7]->einfuegenbitmap(bild[7]);
                                                                bild[7]->tiefereskalieren(1);
                                                                bild[7]->datentausch(0,2);

                                                                textur[8]=new _textur<>(&tl,"c");
                                                                bild[8]=new _bildtga<>("textur//indus01hell.tga",1,1);
                                                                textur[8]->einfuegenbitmap(bild[8]);
                                                                bild[8]->tiefereskalieren(1);
                                                                bild[8]->datentausch(0,2);

                                                                textur[9]=new _textur<>(&tl,"b");
                                                                bild[9]=new _bildtga<>("textur//trenchlochmaske.tga",1,1);
                                                                textur[9]->einfuegenbitmap(bild[9]);
                                                                bild[9]->tiefereskalieren(1);
                                                                bild[9]->datentausch(0,2);

                                                                textur[10]=new _textur<>(&tl,"b");
                                                                bild[10]=new _bildtga<>("textur//brick00.tga",1,1);
                                                                textur[10]->einfuegenbitmap(bild[10]);
                                                                bild[10]->tiefereskalieren(1);
                                                                bild[10]->datentausch(0,2);

                                                                textur[11]=new _textur<>(&tl,"b");
                                                                bild[11]=new _bildtga<>("textur//feuer01.tga",1,1);
                                                                textur[11]->einfuegenbitmap(bild[11]);
                                                                bild[11]->tiefereskalieren(1);
                                                                bild[11]->datentausch(0,2);

                                                                textur[12]=new _textur<>(&tl,"f");
                                                                bild[12]=new _bildtga<>("textur//coron08.tga",1,1);
                                                                textur[12]->einfuegenbitmap(bild[12]);
                                                                bild[12]->tiefereskalieren(1);
                                                                bild[12]->datentausch(0,2);

                                                                textur[13]=new _textur<>(&tl,"l");
                                                                bild[13]=new _bildtga<>("textur//coron01.tga",1,1);
                                                                textur[13]->einfuegenbitmap(bild[13]);
                                                                bild[13]->tiefereskalieren(1);
                                                                bild[13]->datentausch(0,2);
};                                                                
void _testwelt::texturenfigur(){
                                                                //------------------------------------ TEXTUREN LADEN, INITIALISIEREN --------------------------------
                                                                texturanzahl=1;
                                                                
                                                                textur[0]=new _textur<>(&tl,"c");
                                                                bild[0]=new _bildtga<>("textur//coron01.tga",1,1);
                                                                textur[0]->einfuegenbitmap(bild[0]);
                                                                bild[0]->tiefereskalieren(1);
                                                                bild[0]->datentausch(0,2);

};                                                                

void _testwelt::display(_welt*w,_kamera<>*cam,_figurspieler*spieler){
                                                                _win::_grafikopengl<>*gra;
                                                                bool raus;
                                                                _partition::_zone*zone;
                                                                _partition::_sektor*sektor;
                                                                _partition::_sektor*sit;
                                                                _win::_tastatur kb;
                                                                _win::_maus<> mo(399,399);
                                                                //------------------------------
                                                                mo.relativ(true);
                                                                mo.verstecken();
                                                                //--------------------------------------- grafik anlegen , texturen verknüpfen --------------
                                                                gra=new _win::_grafikopengl<>(0,0,1152,864);
                                                                L->schreiben("Grafik wurde konstruiert.");
                                                                gra->texturen(&tl);
                                                             
                                                                //--------------------------------------- testdraw, komplett ohne sektoren-------------------
                                                                gra->loeschenseite();
                                                                cam->bewegen(&kb,&mo,1);
                                                                w->transformieren(gra,cam,false);
                                                                w->zeichnen(gra); 
                                                                //w->zeichnendebug(gra); 
                                                                //w->zeichnenlinie(gra); 
                                                                gra->umschaltenseite();
                                                                //--------------------------------------- Display -------------------------------------------
                                                                L->schreiben("Weltendarstellung wird gestartet.");
                                                                int svis;
                                                                int markierung;
                                                                markierung=0;
                                                                svis=0;
                                                                raus=false;
                                                                if(w->anfang(zone)){
                                                                 w->uebergebenlightmapzone(gra);
                                                                 L->schreiben("Die Welt wurde kompiliert und besitzt eine Zone");
                                                                 //--------------------------------- manipulation -----------------------------------------
                                                                 _netz*m;
                                                                 _vektor<float> c;
                                                                 c.setzen(0,0,1);
                                                                 w->anfang(m);
                                                                 //m->transparent(false);
                                                                 //m->transparentfaktor(0.5);
                                                                // m->zeichnenkante(true);
                                                                // m->zeichnennormale(true);
                                                               //  m->zeichnenflaeche(true);
                                                                 m->verwendentextur(true);
                                                                 m->verwendentexturdynamisch(true);
                                                                 m->farbekante(c);
                                                               //  c.setzen(0,1,0,0.5);
                                                               //  m->farbeverbinder(c);
                                                                 //------------------------------------------------------------------------------------------
                                                                 spieler->ort()=*cam;
                                                                 sektor=zone->sektor(*cam);
                                                                 spieler->aktualisierensektor(zone);
                                                                 zone->initialisierenzeitfaktor(&timer);
                                                                 if(zone->anfang(sit))do{
                                                                  sit->unvisualisieren();
                                                                 }while(zone->naechstes(sit));
                                                
                                                                 do{
                                                                  //gra->aktivitaet(true);
                                                                  //gra2->aktivitaet(false);
                                                                  gra->loeschenseite();
                                                                  //gra->aktivitaet(false);
                                                                  //gra2->aktivitaet(true);
                                                                  //gra2->loeschenseite();
                                                                  sektor=spieler->sektoraktuell();
                                                                  if(sektor){
                                                                   //L->schreiben("SECTORE");
                                                                   //------------------------------ auf 1.grafik zeichnen ------------------------
                                                                   //gra->aktivitaet(true);
                                                                   //gra2->aktivitaet(false);
                                                                   //gra->loeschenseite();
                                                                   w->transformierensektor(gra,spieler->kamera(),sektor);
                                                                   w->zeichnensektor(gra,spieler->kamera(),sektor); 
                                                                   w->zeichnensprite(gra,spieler->kamera());
                                                                   //------------------------------ auf 2.grafik zeichnen ------------------------
                                                                   //gra->aktivitaet(false);
                                                                   //gra2->aktivitaet(true);
                                                                   //gra2->loeschenseite();
                                                                   //spieler->kamera()->rol(spieler->kamera()->rol()-180);
                                                                   //w->transformierensektor(gra2,spieler->kamera(),sektor);
                                                                   //w->zeichnensektor(gra2,spieler->kamera(),sektor); 
                                                                   //w->zeichnensprite(gra2,spieler->kamera());
                                                                   //spieler->kamera()->rol(spieler->kamera()->rol()+180);
                                                                  };
                                                                  zone->berechnenzeitfaktor(&timer);
                                                                  w->animieren();
                                                                  w->animierenpartikelquelle(zone);
                                                                  w->animierensprite();
                                                                  w->animierenfigur(zone,&kb,&mo);
                                                                  //------------------------------- tastaturbefehle ------------------------------
 
                                                                  if(kb.taste(83)){
                                                                   while(kb.taste(83));
                                                                   if(svis==0){
                                                                    if(zone->anfang(sit))do{
                                                                     sit->unvisualisieren();
                                                                    }while(zone->naechstes(sit));
                                                                   }else{
                                                                    if(zone->anfang(sit))do{
                                                                     sit->visualisieren();
                                                                    }while(zone->naechstes(sit));
                                                                   };
                                                                   svis=1-svis;
                                                                  };
                                                                  if(kb.taste(65)){
                                                                   while(kb.taste(65));
                                                                   _figur*fit;
                                                                   if(w->anfang(fit))do{
                                                                    if(fit->partei()==1){
                                                                     fit->sprengen();
                                                                    };
                                                                   }while(w->naechstes(fit));
                                                                  };
                                                                  if(kb.taste(66)){
                                                                   while(kb.taste(66));
                                                                   spieler->aktualisierensektor(zone);
                                                                  };
                                                                  //------------------------------- seiten beider grafikobjekte umschalten -------
                                                                  //gra->aktivitaet(true);
                                                                  //gra2->aktivitaet(false);
                                                                  gra->umschaltenseite();
                                                                  //gra->aktivitaet(false);
                                                                  //gra2->aktivitaet(true);
                                                                  //gra2->umschaltenseite();
                                                                  //------------------------------- system animieren -----------------------------
                                                                  S->animieren();
                                                                  if(kb.escape()) raus=true;
                                                                 }while(raus==false);
                                                                }else{
                                                                 L->schreiben("Die Welt besteht aus Rohdaten, sie besitzt keine Zone.");
                                                                 
                                                                                                                     
                                                                
                                                                 do{
                                                                  //--------------------------------- manipulation -----------------------------------------
                                                                  //_vektor<float> c;
                                                                  //c.setzen(0,0,1);
                                                                  //w->transparent(true);
                                                                  //w->transparentfaktor(0.5);
                                                                  //w->zeichnenkante(false);
                                                                  //w->zeichnennormale(false);
                                                                  //w->zeichnenflaeche(true);
                                                                  //w->verwendentextur(true);
                                                                  //w->farbekante(c);
                                                                  //c.setzen(0,1,0,0.5);
                                                                  //w->farbeverbinder(c);
                                                                  //----------------------------------------------------------------------------------------
                                                                  gra->loeschenseite();
                                                                  cam->bewegen(&kb,&mo,1);
                                                                  w->transformieren(gra,cam,false);
                                                                  //w->transformieren(gra,cam,0.2,1);
                                                                  //w->zeichnendebug(gra); 
                                                                  w->zeichnen(gra); 
                                                                  gra->umschaltenseite();
                                                                  S->animieren();
                                                                  if(kb.escape()) raus=true;
                                                                 }while(raus==false);
                                                                };
                                                                while(kb.escape()) S->animieren();
                                                                delete gra;
                                                                gra=0;
                                                                L->schreiben("Grafik wurde destruiert.");
                                                                //delete gra2;
                                                                //gra2=0;
                                                                //L->schreiben("Grafik1 wurde destruiert.");
};                                                                
void _testwelt::szenekonstruktion(_welt*&w,_kamera<>*&cam,_figurspieler*&spieler){
                                                                //int i;
                                                                _netz*m;
                                                                //_netz*m2;
                                                                _vektor<> h;
                                                                _vektor<> hh;
                                                                _vektor<> vx;
                                                                _vektor<> vy;
                                                                _vektor<> vz;
                                                                _vektor<> vec;
                                                                _vektor<> rad;
                                                                _vektor<typgeometrie> v;
                                                                _vektor<typgeometrie> x;
                                                                _vektor<typoptik> c;
                                                                _vektor<unsigned int> res;
                                                                //_geometriezylinder*gc;
                                                                _geometriequader*gb;
                                                                //_geometriegang*gg;
                                                                //_geometrieraum*gr;
                                                                //_geometriekreuzdrei*gk;
                                                                _modifikationnetzintersektion ism;
                                                                _partikelquellesprite*pqdeath;
                                                                _partikelquellesprite*pqlife;
                                                                //_polygon*pit;
                                                                //_licht<>*lit1;
                                                                _licht<>*lit0;
                                                                //_licht<>*lb[3];
                                                                //_licht<>*lr[3];
                                                                //unsigned int sr;
                                                                //double n;
                                                                //double dx,dy,dz;
                                                                //------------------------------------ welt anlegen --------------------------------------------------
                                                                timer.animieren();
                                                                time[0]=timer.system();
                                                                w=new _welt();
                                                                w->time(&timer);
                                                                texturen();
                                                                timer.animieren();
                                                                time[1]=timer.system();
                                                                cam=new _kamera<>(w);
                                                                _vektor<> r;
                                                                //r.setzen(0,0,0);//x-y-ansicht
                                                                //r.setzen(90,0,0);//z-y-ansicht
                                                                r.setzen(0,-90,0);//x-z-ansicht, hier evtl auch (0,-90,0)... ausprobieren
                                                                cam->rotation(r);
                                                                
                                                                //gr halle
                                                                /*h.setzen(0,0,0);
                                                                gb=new _geometriequader(w,h,100,100,100,textur[1]);
                                                                gb->texturkoordinatenlaenge(10,10,10);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //dachloch
                                                                h.setzen(0,100,0);
                                                                gb=new _geometriequader(w,h,100,10,100,textur[0]);
                                                                gb->texturkoordinatenlaenge(10,1,10);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //dachraum
                                                                h.setzen(-20,110,-20);
                                                                gb=new _geometriequader(w,h,140,40,140,textur[1]);
                                                                gb->texturkoordinatenlaenge(14,4,14);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //dachraumdach
                                                                h.setzen(0,150,0);
                                                                gb=new _geometriequader(w,h,100,20,100,textur[1]);
                                                                gb->texturkoordinatenlaenge(10,2,10);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                h.setzen(20,170,20);
                                                                gb=new _geometriequader(w,h,60,20,60,textur[1]);
                                                                gb->texturkoordinatenlaenge(6,2,6);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //querkanal links
                                                                h.setzen(-20,0,10);
                                                                gb=new _geometriequader(w,h,20,10,80,textur[1]);
                                                                gb->texturkoordinatenlaenge(2,1,8);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //querkanal rechts
                                                                h.setzen(100,0,10);
                                                                gb=new _geometriequader(w,h,20,10,80,textur[1]);
                                                                gb->texturkoordinatenlaenge(2,1,8);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //hochkanal links
                                                                h.setzen(-30,0,0);
                                                                gb=new _geometriequader(w,h,10,120,100,textur[0]);
                                                                gb->texturkoordinatenlaenge(1,12,10);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit=pit->naechstes();
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[12]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //hochkanal links, 1.stufe
                                                                h.setzen(-40,10,10);
                                                                gb=new _geometriequader(w,h,10,100,80,textur[0]);
                                                                gb->texturkoordinatenlaenge(1,10,8);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit=pit->naechstes();
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[12]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //hochkanal links, 2.stufe
                                                                h.setzen(-50,20,20);
                                                                gb=new _geometriequader(w,h,10,80,60,textur[0]);
                                                                gb->texturkoordinatenlaenge(1,8,6);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit=pit->naechstes();
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[12]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //hochkanal links, 3.stufe
                                                                h.setzen(-60,30,30);
                                                                gb=new _geometriequader(w,h,10,60,40,textur[0]);
                                                                gb->texturkoordinatenlaenge(1,6,4);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit=pit->naechstes();
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                h.setzen(-40,60,50);
                                                                c.setzen(0.2,0.05,1);
                                                                new _licht<>(w,h,c,100);
                                                                //gang lings
                                                                h.setzen(-220,40,40);
                                                                gg=new _geometriegang(w,h,160,40,20,textur[1],textur[0],textur[2],textur[13]);
                                                                gg->iteration(4);
                                                                gg->texturkoordinatenlaenge(4,4,2);
                                                                m=gg->erzeugen();
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                h.setzen(-200,60,50);
                                                                c.setzen(1,0.1,0);
                                                                new _licht<>(w,h,c,100);
                                                                //linke anschlusshalle
                                                                h.setzen(-260,40,30);
                                                                gb=new _geometriequader(w,h,40,50,40,textur[1]);
                                                                gb->texturkoordinatenlaenge(4,5,4);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //gang hinten links
                                                                h.setzen(-230,40,70);
                                                                vx.setzen(0,0,160);
                                                                vy.setzen(0,40,0);
                                                                vz.setzen(-20,0,0);
                                                                gg=new _geometriegang(w,h,vx,vy,vz,textur[1],textur[0],textur[2],textur[13]);
                                                                gg->iteration(4);
                                                                gg->texturkoordinatenlaenge(4,4,2);
                                                                m=gg->erzeugen();
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                h.setzen(-240,80,50);
                                                                c.setzen(1,0.3,0);
                                                                new _licht<>(w,h,c,50);
                                                                h.setzen(-240,60,200);
                                                                c.setzen(0.21,0,1);
                                                                new _licht<>(w,h,c,100);
                                                                //hinten linke anschlusshalle
                                                                h.setzen(-260,40,230);
                                                                gb=new _geometriequader(w,h,40,50,40,textur[1]);
                                                                gb->texturkoordinatenlaenge(4,5,4);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //gang links hinten
                                                                h.setzen(-220,40,240);
                                                                gg=new _geometriegang(w,h,320,40,20,textur[1],textur[0],textur[2],textur[13]);
                                                                gg->iteration(8);
                                                                gg->texturkoordinatenlaenge(4,4,2);
                                                                m=gg->erzeugen();
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                h.setzen(20,60,250);
                                                                c.setzen(1,0.3,0.1);
                                                                new _licht<>(w,h,c,100);
                                                                //raum hinten
                                                                h.setzen(100,40,230);
                                                                gr=new _geometrieraum(w,h,40,60,40,textur[1],textur[0],textur[2],textur[13],textur[12]);
                                                                gr->texturkoordinatenlaenge(4,6,4);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(100,40,230+40);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(100+40,40,230);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(120,60,250);
                                                                c.setzen(1,0.3,0.1);
                                                                new _licht<>(w,h,c,100);
                                                                //gang hinten zurück
                                                                h.setzen(130,40,230-40);
                                                                vx.setzen(0,0,40);
                                                                vy.setzen(0,40,0);
                                                                vz.setzen(-20,0,0);
                                                                gg=new _geometriegang(w,h,vx,vy,vz,textur[1],textur[0],textur[2],textur[13]);
                                                                gg->iteration(1);
                                                                gg->texturkoordinatenlaenge(4,4,2);
                                                                m=gg->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(130,80,210);
                                                                c.setzen(0.2,0,1);
                                                                new _licht<>(w,h,c,50);
                                                                //nochn raum
                                                                h.setzen(100,40,150);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(120,60,170);
                                                                c.setzen(1,0.3,0.1);
                                                                new _licht<>(w,h,c,100);
                                                                h.setzen(100-40,40,150);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(100+40,40,150);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);*/
                                                                //gang hinten rechts
                                                                /*h.setzen(180,40,160);
                                                                vx.setzen(160,0,0);
                                                                vy.setzen(0,40,0);
                                                                vz.setzen(0,0,20);
                                                                gg=new _geometriegang(w,h,vx,vy,vz,textur[1],textur[0],textur[2],textur[13]);
                                                                gg->iteration(1);
                                                                gg->texturkoordinatenlaenge(4,4,2);
                                                                m=gg->erzeugen();
                                                                m->einhaengen(w);*/
                                                                h.setzen(350,70,125);
                                                                c.setzen(1,1,0.1f);
                                                                new _licht<>(w,h,c,100);
                                                               // h.setzen(350,70,170);
                                                               // c.setzen(0,1,0.1);
                                                               // new _licht<>(w,h,c,100);
                                                                //anschlusshalle0
                                                                h.setzen(0,20,0);
                                                                gb=new _geometriequader(w,h,10,1,0.3,textur[2]);
                                                                gb->texturkoordinatenlaenge(6,6,6);
                                                                m=gb->erzeugen();
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //anschlusshalle1
                                                              /*  h.setzen(420,30,140);
                                                                gb=new _geometriequader(w,h,60,60,60,textur[2]);
                                                                gb->texturkoordinatenlaenge(6,6,6);
                                                                m2=gb->erzeugen();
                                                                m2->einhaengen(w);
                                                                m2->subtraktiv(true);
                                                                ism.bearbeiten(m,m2,2);
                                                                delete m2;
                                                                //anschlusshalle2
                                                                h.setzen(330,20,130);
                                                                gb=new _geometriequader(w,h,80,80,80,textur[3]);
                                                                gb->texturkoordinatenlaenge(6,6,6);
                                                                m2=gb->erzeugen();
                                                                m2->einhaengen(w);
                                                                m2->subtraktiv(true);
                                                                ism.bearbeiten(m2,m,1);
                                                                h.setzen(0,80,0);
                                                                *m2+=h;
                                                                m2->aktualisieren();*/
                                                                //raum rechts
                                                                /*h.setzen(400,40,150);
                                                                vx.setzen(0,40,0);
                                                                vy.setzen(60,0,0);
                                                                vz.setzen(0,0,40);
                                                                gr=new _geometrieraum(w,h,vx,vy,vz,textur[1],textur[0],textur[2],textur[13],textur[12]);
                                                                gr->texturkoordinatenlaenge(4,6,4);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                //raum hinten
                                                                vx.setzen(40,0,0);
                                                                vy.setzen(0,0,60);
                                                                vz.setzen(0,40,0);
                                                                h.setzen(350,40,200);
                                                                gr->vektor(vx,vy,vz);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                //raum vorne
                                                                vx.setzen(40,0,0);
                                                                vy.setzen(0,0,-60);
                                                                vz.setzen(0,40,0);
                                                                h.setzen(350,40,140);
                                                                gr->vektor(vx,vy,vz);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                //raum unten 
                                                                vx.setzen(40,0,0);
                                                                vy.setzen(0,-60,0);
                                                                vz.setzen(0,0,40);
                                                                h.setzen(350,30,150);
                                                                gr->vektor(vx,vy,vz);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                //raum oben
                                                                vx.setzen(40,0,0);
                                                                vy.setzen(0,60,0);
                                                                vz.setzen(0,0,40);
                                                                h.setzen(350,90,150);
                                                                gr->vektor(vx,vy,vz);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(380,70,170);
                                                                c.setzen(1,0.3,0.02);
                                                                new _licht<>(w,h,c,100);
                                                                //raum unten unten
                                                                vx.setzen(40,0,0);
                                                                vy.setzen(0,60,0);
                                                                vz.setzen(0,0,40);
                                                                h.setzen(350,-90,150);
                                                                gr=new _geometrieraum(w,h,vx,vy,vz,textur[1],textur[0],textur[2],textur[13],textur[12]);
                                                                gr->texturkoordinatenlaenge(4,6,4);
                                                                gr->vektor(vx,vy,vz);
                                                                gr->ort(h);
                                                                m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(380,-70,170);
                                                                c.setzen(0.2,0.04,1);
                                                                new _licht<>(w,h,c,50);
                                                                //raum unten unten unten
                                                                vx.setzen(40,0,0);
                                                                vy.setzen(0,60,0);
                                                                vz.setzen(0,0,40);
                                                                h.setzen(350,-150,150);
                                                                gr->vektor(vx,vy,vz);
                                                                for(dx=0;dx<4*40;dx+=40)
                                                                for(dz=0;dz<1*40;dz+=40){
                                                                 h.setzen(350+dx,-150,150+dz);
                                                                 gr->ort(h);
                                                                 m=gr->erzeugen();
                                                                 m->einhaengen(w);
                                                                 h.setzen(350+dx+20,-115,150+dz+20);
                                                                 c.setzen(dx/160.0f,1,0);
                                                                 new _licht<>(w,h,c,15);
                                                                };
                                                                //gang
                                                                h.setzen(480,-150,-10);
                                                                vx.setzen(0,0,160);
                                                                vy.setzen(0,40,0);
                                                                vz.setzen(20,0,0);
                                                                gg=new _geometriegang(w,h,vx,vy,vz,textur[1],textur[0],textur[2],textur[13]);
                                                                gg->iteration(4);
                                                                gg->texturkoordinatenlaenge(4,4,2);
                                                                m=gg->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(490,-130,0);
                                                                c.setzen(0,0.1,1);
                                                                new _licht<>(w,h,c,150);
                                                                for(dx=0;dx<4*40;dx+=40)
                                                                for(dz=0;dz<5*40;dz+=40){
                                                                 h.setzen(470+dx,-150,-50-dz);
                                                                 gr->ort(h);
                                                                 m=gr->erzeugen();
                                                                 m->einhaengen(w);
                                                                };
                                                                h.setzen(470+3*40+20,-115,(-50-3*40)+20);
                                                                c.setzen(1,1,1);
                                                                new _licht<>(w,h,c,100);
                                                                //hochkanal rechts
                                                                h.setzen(120,0,0);
                                                                gb=new _geometriequader(w,h,10,120,100,textur[1]);
                                                                gb->texturkoordinatenlaenge(1,12,10);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(true);
                                                                //dachklotz
                                                                h.setzen(20,100,20);
                                                                gb=new _geometriequader(w,h,60,10,60,textur[0]);
                                                                gb->texturkoordinatenlaenge(6,1,6);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[2]);
                                                                m->einhaengen(w);
                                                                m->subtraktiv(false);
                                                                //säule dach aussen
                                                                _netz*mv;
                                                                mv=0;
                                                                for(dz=0;dz<=100;dz+=100)
                                                                for(dx=0;dx<=100;dx+=100){
                                                                 h.setzen(-5+dx,90,-5+dz);
                                                                 gb=new _geometriequader(w,h,10,80,10,textur[3]);
                                                                 gb->texturkoordinatenlaenge(1,8,1);
                                                                 m=gb->erzeugen();
                                                                 m->anfang(pit);
                                                                 pit->textur(textur[0]);
                                                                 m->einhaengen(w);
                                                                 m->subtraktiv(false);
                                                                 if(mv) mv->vereinigen(m); else mv=m;
                                                                };

                                                                //säule dach innen
                                                                for(dz=0;dz<=60;dz+=60)
                                                                for(dx=0;dx<=60;dx+=60){
                                                                 h.setzen(15+dx,90,15+dz);
                                                                 gb=new _geometriequader(w,h,10,100,10,textur[3]);
                                                                 gb->texturkoordinatenlaenge(1,10,1);
                                                                 m=gb->erzeugen();
                                                                 m->anfang(pit);
                                                                 pit->textur(textur[0]);
                                                                 m->einhaengen(w);
                                                                 m->subtraktiv(false);
                                                                 mv->vereinigen(m);
                                                                };
                                                                */
                                                                //licht,gr halle
                                                                h.setzen(2,2,2);
                                                                c.setzen(0.3f,1,0.1f);
                                                                lit0=new _licht<>(w,h,c,10);
                                                                h.setzen(98,98,98);
                                                                c.setzen(0.3f,0.1f,1);
                                                                lit0=new _licht<>(w,h,c,10);
                                                                h.setzen(50,50,50);
                                                                c.setzen(1,0.5f,0);
                                                                lit0=new _licht<>(w,h,c,40);
                                                                //licht querkanal links
                                                                h.setzen(-10,5,50);
                                                                c.setzen(1,0.5f,0.13f);
                                                                lit0=new _licht<>(w,h,c,20);
                                                                //licht querkanal rechts
                                                                h.setzen(110,5,50);
                                                                c.setzen(1,0.5f,0.13f);
                                                                lit0=new _licht<>(w,h,c,20);
                                                                //licht hochkanal links
                                                                h.setzen(-25,20,50);
                                                                c.setzen(1,0.6f,0.13f);
                                                                lit0=new _licht<>(w,h,c,30);
                                                                //licht hochkanal rechts
                                                                h.setzen(125,20,50);
                                                                c.setzen(1,0.6f,0.13f);
                                                                lit0=new _licht<>(w,h,c,30);
                                                                 //licht dachraum
                                                                h.setzen(10,130,10);
                                                                c.setzen(1,0.5f,0);
                                                                lit0=new _licht<>(w,h,c,50);
                                                                h.setzen(90,130,90);
                                                                c.setzen(0,0.5f,1);
                                                                lit0=new _licht<>(w,h,c,50);
                                                                h.setzen(50,180,50);
                                                                c.setzen(0,1,0);
                                                                lit0=new _licht<>(w,h,c,50);
                                                                //--------------------------------------- sprites -------------------------------------------
                                                                h.setzen(220,-270,150);
                                                                vx.setzen(5,0,0);
                                                                vy.setzen(0,5,0);
                                                                new _sprite(w,w,h,vx,vy,textur[5]);
                                                                //h.setzen(50+15,50,50);
                                                                //new _sprite(w,h,vx,vy,textur[10]);
                                                                //---------------------------------------- gravitation --------------------------------------
                                                                h.setzen(220,-270,150);
                                                                new _gravitation<>(w,h,1500);
                                                                //h.setzen(-140,-150,50);
                                                                //new _gravitation<>(w,h,280);
                                                                //h.setzen(50+15,50,50);
                                                                //new _gravitation<>(w,h,-15);
                                                                //-------------------------------------- figur,spieler -------------------------------------
                                                                //_figursprite*fig;
                                                                h.setzen(20,20,20);
                                                                vx.setzen(1,0,0);
                                                                pqdeath=new _partikelquellesprite(w,w,h,vx,50,textur[8]);
                                                                pqdeath->einfuegentextur(textur[7]);
                                                                //pqdeath->einfuegentextur(textur[10]);
                                                                //pqdeath->einfuegentextur(textur[11]);
                                                                pqdeath->aktiv(false);
                                                                pqdeath->laenge(0.3);
                                                                pqdeath->generationsrate(15);
                                                                pqdeath->generationsratetoleranz(0.5);
                                                                pqdeath->laengetoleranz(0.5);
                                                                pqdeath->vektortoleranz(0.5);
                                                                pqdeath->rotation(60);
                                                                pqdeath->rotationtoleranz(1);
                                                                pqdeath->lebensdauerpartikeltoleranz(0.95);
                                                                pqlife=new _partikelquellesprite(w,w,h,vx,30,textur[4]);
                                                                pqlife->aktiv(false);
                                                                pqlife->laenge(0.1);
                                                                pqlife->laengetoleranz(0.5);
                                                                pqlife->vektortoleranz(0.5);
                                                                pqlife->lebensdauerpartikeltoleranz(0.5);
                                                                h.setzen(350,40,150);
                                                                spieler=new _figurspieler(w,w,h);
                                                                spieler->einfuegentexturdetonation(textur[6]);
                                                                spieler->partikelquelle()->einfuegentextur(textur[8]);
                                                                spieler->partikelquelle()->partikelquelledestruktion(pqdeath);
                                                                //spieler->partikelquelle()->partikelquellelebensdauer(pqlife);
};
void _testwelt::szenedestruktion(_welt*w){
                                                                //--------------------------------------- exit -----------------------------------
                                                                w->unuebersetzen();
                                                                L->schreiben("Welt wurde unpräpariert.");
                                                                delete w;
                                                                //W=0;
                                                                L->schreiben("Welt wurde destruiert.");
};
void _testwelt::testspeichern(){
                                                                _welt*w;
                                                                _kamera<>*cam;
                                                                _figurspieler*spieler;
                                                                _liste<_netz >*rohmeshes;
                                                                //--------------------------------------- konstruieren der welt -----------------------------------
                                                                szenekonstruktion(w,cam,spieler);
                                                                 display(w,cam,spieler);
                                                                //--------------------------------------- speichern der rohen welt --------------------------------
                                                                ::weltspeichern("Weltdatenroh.txt",w);
                                                                //--------------------------------------- präparation, übersetzung --------------------------------
                                                                timer.animieren();
                                                                time[2]=timer.system();
                                                                L->schreiben("Weltenpräparation wird gestartet.");
                                                                rohmeshes=w->uebersetzen();
                                                                rohmeshes->loeschen();
                                                                delete rohmeshes;
                                                                L->schreiben("Weltenpräparation ist beendet.");
                                                                timer.animieren();
                                                                time[3]=timer.system();
                                                                statistik(w);
                                                                display(w,cam,spieler);
                                                                //--------------------------------------- speichern der übersetzten welt --------------------------
                                                                ::weltspeichern("Weltdatenuebersetzt.txt",w);
                                                                szenedestruktion(w);
                                                                w=0;
};
//******************************************************************************************************************************************************************************************************
//                                                              L A D E N   T E S T 
//******************************************************************************************************************************************************************************************************

void _testwelt::associatetexture(_polygon*p){
                                                                _textur<>*tit;
                                                                bool gef;
                                                                //-------------
                                                                gef=false;
                                                                if(tl.anfang(tit))do{
                                                                 if(tit->name()==p->texturstring()) {
                                                                  p->textur(tit);
                                                                  gef=true;
                                                                 };
                                                                }while((tl.naechstes(tit))&&(gef==false));
                                                                if(gef==false){
                                                                 p->textur(tit);
                                                                };
                                                                
};
void _testwelt::testladen(){
                                                                _welt*w;
                                                                _netz*m;
                                                                _polygon*p;
                                                                _kamera<>*cam;
                                                                _figurspieler*spieler;
                                                                _liste<_welt > lw;
                                                                _listenknoten<_welt >*lwit;
                                                                _vektor<> h;
                                                                _vektor<> vx;
                                                                _partikelquellesprite*pqdeath;
                                                                _partikelquellesprite*pqlife;
                                                                //--------------------------------------- laden der welt ------------------------------------------
                                                                texturen();
                                                                ::weltladen("c:\\daten\\geometrie\\test13.bild",&lw);
                                                                if(lw.anfang(lwit)){
                                                                 L->schreiben("Welt nach dem Laden existent.");
                                                                 statistik(lwit->objekt());
                                                                 w=lwit->objekt();
                                                                 w->anfang(cam);
                                                                 w->naechstes(cam);
                                                                 //w->anfang(f);
                                                                 //spieler=(_figurspieler*)f;
                                                                 w->anfang(m);
                                                                 _vektor<float> co;
                                                                 co.setzen(1,0,0,0.5);
                                                                 m->farbeverbinder(co);
                                                                 
                                                                 //-------------------------------------- figur,spieler -------------------------------------
                                                                 if(w->anfang(m))do{
                                                                  if(m->anfang(p))do{
                                                                   L->schreiben("geladener texturestring : ",p->texturstring());
                                                                   associatetexture(p);
                                                                  }while(m->naechstes(p));
                                                                 }while(w->naechstes(m));
                                                                 texturenfigur();
                                                                 
                                                                 h.setzen(20,20,20);
                                                                 vx.setzen(1,0,0);
                                                                 pqdeath=new _partikelquellesprite(w,w,h,vx,50,textur[0]);
                                                                 pqdeath->einfuegentextur(textur[0]);
                                                                 pqdeath->aktiv(false);
                                                                 pqdeath->laenge(0.3);
                                                                 pqdeath->generationsrate(15);
                                                                 pqdeath->generationsratetoleranz(0.5);
                                                                 pqdeath->laengetoleranz(0.5);
                                                                 pqdeath->vektortoleranz(0.5);
                                                                 pqdeath->rotation(60);
                                                                 pqdeath->rotationtoleranz(1);
                                                                 pqdeath->lebensdauerpartikeltoleranz(0.95);
                                                                 pqlife=new _partikelquellesprite(w,w,h,vx,30,textur[0]);
                                                                 pqlife->aktiv(false);
                                                                 pqlife->laenge(0.1);
                                                                 pqlife->laengetoleranz(0.5);
                                                                 pqlife->vektortoleranz(0.5);
                                                                 pqlife->lebensdauerpartikeltoleranz(0.5);
                                                                 h.setzen(350,40,150);
                                                                 spieler=new _figurspieler(w,w,h);
                                                                 spieler->einfuegentexturdetonation(textur[0]);
                                                                 spieler->partikelquelle()->einfuegentextur(textur[0]);
                                                                 spieler->partikelquelle()->partikelquelledestruktion(pqdeath);
                                                                 //spieler->partikelquelle()->partikelquellelebensdauer(pqlife);
                                                                 //--------------------------------------- anzeigen der welt----------------------------------------
                                                                 _weltdebugkreuz*wc;
                                                                 _vektor<float> col;
                                                                 _vektor<> ss;
                                                                 col.setzen(1,0,0);
                                                                 w->anfang(m);
                                                                 wc=new _weltdebugkreuz(w,m->schwerpunkt(),0.3,col);
                                                                 
                                                                 display(w,cam,spieler);
                                                                 delete wc;
                                                                 testcompile(w);
                                                                 display(w,cam,spieler);
                                                                 lw.loeschen();
                                                                 w=0;
                                                                }else L->schreiben("Keine Welt nach dem Laden vorhanden .");
};
//******************************************************************************************************************************************************************************************************
//                                                              C O M P I L E R   T E S T 
//******************************************************************************************************************************************************************************************************
void _testwelt::testcompile(_welt*w){
                                                                _netz*m;
                                                                _vektor<float> co;
                                                                _liste<_netz >*rohmeshes;
                                                                co.setzen(1,0,0);
                                                                timer.animieren();
                                                                time[2]=timer.system();
                                                                L->schreiben("Weltenpräparation wird gestartet.");
                                                                rohmeshes=w->uebersetzen();
                                                                rohmeshes->loeschen();
                                                                delete rohmeshes;
                                                                L->schreiben("Weltenpräparation ist beendet.");
                                                                timer.animieren();
                                                                time[3]=timer.system();
                                                                statistik(w);
                                                                w->anfang(m);
                                                                m->farbeverbinder(co);
                                                              //  display(w,cam,spieler);
                                                                
};

//******************************************************************************************************************************************************************************************************
//                                                              B E S T R A H L E R   T E S T 
//******************************************************************************************************************************************************************************************************
bool dateiexistiert(_zeichenkette<char> f){
                                                                FILE*a;
                                                                a=fopen(f,"r");
                                                                if(a!=0){
                                                                 fclose(a);
                                                                 a=0;
                                                                 return(true);
                                                                };
                                                                return(false);
};
void _testwelt::testbestrahlung(){
                                                                _welt*w;
                                                                _netz*m;
                                                                //_polygon*p;
                                                                _kamera<>*cam;
                                                                _kamera<>*cam2;
                                                                _figurspieler*spieler;
                                                                //_liste<_netz >*rohmeshes;
                                                                _bestrahler B;
                                                                _bildtga<> bild(1024,768);
                                                                _win::_grafikopengl<>*gra;
                                                                _win::_grafikopengl<>*gra2;
                                                                _zeichenkette<char> fn;
                                                                _zeichenkette<char> ns;
                                                                unsigned int n;
                                                                char buff[1024];
                                                                //double brech;
                                                                double wink;
                                                                _win::_tastatur kb;
                                                                _win::_maus<>*mo;
                                                                _spinne*spinne;
                                                                _partition::_zone*zone;
                                                                //--------------------------------------- konstruieren der welt -----------------------------------
                                                                szenekonstruktionbestrahlung(w,cam,spieler,1);
                                                                display(w,cam,spieler);
                                                                cam->laenge(2);
                                                                cam->groesse(1.024,0.768);
                                                                cam->aktualisieren();
                                                                mo=new _win::_maus<>(399,399);
                                                                mo->relativ(true);
                                                                mo->verstecken();
                                                                gra2=new _win::_grafikopengl<>(0,0,1280,1024);
                                                                gra2->texturen(&tl);
                                                                gra= new _win::_grafikopengl<>(0,0,1280,1024);
                                                                gra->texturen(&tl);
                                                                //gra= new _win::_grafikopengl<>(0  ,0,576,864);
                                                                //gra2=new _win::_grafikopengl<>(576,0,576,864);
                                                                gra->aktivitaet(true);
                                                                gra->loeschenseite();
                                                                gra->umschaltenseite();
                                                                gra->loeschenseite();
                                                                gra->umschaltenseite();
                                                                //----------------------------------------- skelett anlegen ----------------------------
                                                                spinne=new _spinne(w,_vektor<double>(0,-7,0));
                                                                _basis::_liste<_kugel> kugellist;
                                                              //  _kugel * kugel=new _kugel(w,&kugellist,_vektor<double>(0,-6.2,0),0.4,_vektor<double>(+0.080011113121,0.043,-0.01));
                                                                new _kugel(w,&kugellist,_vektor<double>(6-2,-6,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6-1,-6,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6+0,-6,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6+1,-6,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6+2,-6,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));

                                                                new _kugel(w,&kugellist,_vektor<double>(6,-6-2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6,-6-1,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6,-6+1,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6,-6+2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                
                                                                new _kugel(w,&kugellist,_vektor<double>(6-2,-6+1,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6-2,-6+2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                
                                                                new _kugel(w,&kugellist,_vektor<double>(6+2,-6-1,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6+2,-6-2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));

                                                                new _kugel(w,&kugellist,_vektor<double>(6+1,-6+2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6+1,-6+2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));

                                                                new _kugel(w,&kugellist,_vektor<double>(6-1,-6-2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));
                                                                new _kugel(w,&kugellist,_vektor<double>(6-1,-6-2,14),0.4,_vektor<double>(-6e-001,+4e-001,-5e-001));

                                                              /*  _kugel * kugel=
                                                                new _kugel(w,&kugellist,
                                                                _vektor<double>(-8+3+0.01,-7,-15+3),
                                                                0.4,
                                                                _vektor<double>(-0.113,0.0,-0.113));*/
                                                               // new _weltdebugzylinder(w,_vektor<double>(2,-8,0.2),_vektor<double>(0,5,0),0.4,_vektor<float>(0,1,1));
                                                                bool raus;
                                                                //--------------------
                                                                //----------------------------------------- lightmap bestrahlung -----------------------
                                                                B.lichtambient(_vektor<float>(0.05f,0,0.0));
                                                                B.bestrahlenlightmapzone(w);
                                                                //w->bestrahlenlightmap();
                                                                w->uebergebenlightmap(gra);
                                                                //--------------------------------------------------------------------------------------
                                                                //display(w,cam,spieler);
                                                                cam2=new _kamera<>(w);
                                                                cam2->setzen(0,0,0);
                                                                cam2->rot(45);
                                                                cam2->aktualisieren();
                                                                //for(brech=1.5;brech<1.55;brech+=0.05){
                                                                bool stop=false;
                                                                bool speichern=true;
                                                                for(wink=0.5;wink<=1;wink+=0.02){
                                                                 n=0;
                                                                 do{
                                                                  itoa(n,buff,16);
                                                                  ns=buff;
                                                                  while(ns.groesse()<8) ns.anhaengenfront("0");
                                                                  fn="bestrahler\\bestrahler_";
                                                                  fn+=ns;
                                                                  fn+=".tga";
                                                                  n++;
                                                                 }while(dateiexistiert(fn));
                                                                 bild.dateiname(fn);
                                                                 B.reflektionstiefe(0);
                                                                 B.refraktionstiefe(5);
                                                                 B.dispersionsaufloesung(20);
                                                                 B.refraktiondispersiv(true);
                                                                 w->anfang(m);
                                                                 m=m->naechstes();
                                                                 //m=m->naechstes();
                                                                 //m->brechzahl(1.8);
                                                                 //m->rotiereny(3.0);
                                                                 m->transparentfaktor(float(wink));
                                                                 B.starten(w,cam,&bild);
                                                                 speichern=true;
                                                                 B.visualisierung(true);
                                                                 spinne->visualisieren();
                                                                 while((B.animieren(S,&kb,mo,gra,cam2)&&(stop==false))){
                                                                  //if(B.bilditeratorx()==0) {B.zeichnenzeile();peep(10);};
                                                                  S->animieren();
                                                                  
                                                                  if(kb.enter()) {stop=true;speichern=true;};
                                                                  if(kb.escape()) {stop=true;speichern=false;};
                                                                  if(kb.leertaste()) {
                                                                   B.visualisierungumschalten();
                                                                   while(kb.leertaste()) S->animieren();
                                                                  };
                                                                  if(kb.taste(65)){
                                                                   if(B.visualisierunganhalten()==false){
                                                                    B.visualisierunganhalten(true);
                                                                   }else{
                                                                    B.visualisierunganhalten(false);
                                                                   };
                                                                   while(kb.taste(65)) S->animieren();
                                                                  };
                                                                  
                                                                 };
                                                                 B.beenden();
                                                                 if(speichern) bild.speichern(); 
                                                                 if(stop) wink=10000;
                                                                };
                                                                 gra->nebelmodus(1);
                                                                 gra->nebelfarbe(0.5f,0.5f,0.5f);
                                                                 gra->nebeldichte(0.05f);
                                                                 gra->nebeldistanz(1,40);
                                                                 gra->nebel(true); 
                                                                 glHint(GL_FOG_HINT, GL_DONT_CARE);  
                                                                 float xxx=0;
                                                                while(kb.escape()) S->animieren();
                                                                if(w->anfang(zone)) {
                                                                 spinne->zone(zone);
                                                                 spinne->aktualisierensektor();
                                                                };
                                                                raus=false;
                                                                w->eigenetransformation(false);
                                                                _kugel*kit;
                                                                do{ 
                                                                 float ff=0.5f+float(sin(xxx*_ph))*0.5f;
                                                                 gra->nebelfarbe(ff,ff,ff);
                                                                 gra->loeschenseite();
                                                                 if(kb.shift()==false) cam->bewegen(&kb,mo,1); else{
                                                                  _vektor<double> mk=mo->holen();
                                                                  _tg vadd[3];
                                                                  vadd[0]=mk[0];
                                                                  vadd[1]=0;
                                                                  vadd[2]=-mk[1];
                                                                  ::multiplizieren<_tg>(vadd,0.001);
                                                                  if(kugellist.anfang(kit))do{
                                                                   ::addieren(kit->vektor(),vadd);
                                                                  }while(kugellist.naechstes(kit));
                                                                 };
                                                                  
                                                                   
                                                                   
                                                                 w->transformieren(gra,cam,false);
                                                                 w->zeichnen(gra); 
                                                                 spinne->visualisieren();
                                                                 gra->umschaltenseite();                                                                 
                                                                 spinne->animieren();
                                                                 if(kugellist.anfang(kit))do{
                                                                  kit->animieren();
                                                                 }while(kugellist.naechstes(kit));
                                                                 S->animieren();
                                                                 if(kb.escape()) raus=true;
                                                                 xxx+=4;
                                                                }while(raus==false);
                                                                delete gra;
                                                                delete gra2;
                                                                delete mo;
                                                                
                                                                //--------------------------------------- speichern der rohen welt --------------------------------
                                                                //::weltspeichern<typgeometrie,typoptik,typakustik>("Weltdatenroh.txt",w);
                                                                //--------------------------------------- präparation, übersetzung --------------------------------
                                                                szenedestruktion(w);
                                                                w=0;
};
void _testwelt::szenekonstruktionbestrahlung(_welt*&w,_kamera<>*&cam,_figurspieler*&spieler,double brech){
                                                                _netz*m;
                                                                //_netz*m2;
                                                                _vektor<> h;
                                                                _vektor<> hh;
                                                                _vektor<> vx;
                                                                _vektor<> vy;
                                                                _vektor<> vz;
                                                                _vektor<> vec;
                                                                _vektor<> rad;
                                                                _vektor<typgeometrie> v;
                                                                _vektor<typgeometrie> x;
                                                                _vektor<typoptik> c;
                                                                _vektor<unsigned int> res;
                                                                _geometriequader*gb;
                                                                _modifikationnetzintersektion ism;
                                                                _partikelquellesprite*pqdeath;
                                                                _partikelquellesprite*pqlife;
                                                                _polygon*pit;
                                                                //unsigned int sr;
                                                                //double n;
                                                                //double dx,dy,dz;
                                                                _liste<_netz >*rohmeshes;
                                                                //------------------------------------ welt anlegen --------------------------------------------------
                                                                timer.animieren();
                                                                time[0]=timer.system();
                                                                w=new _welt();
                                                                w->time(&timer);
                                                                texturen();
                                                                timer.animieren();
                                                                time[1]=timer.system();
                                                                cam=new _kamera<>(w);
                                                                cam->setzen(0,0,0);
                                                                cam->rot(45);
                                                                cam->aktualisieren();

                                                                h.setzen(-1,-1,-1);
                                                                c.setzen(1,1,1);
                                                               // new _licht<>(w,h,c,5);
                                                                //-------------------------------umgebung------------------------------
                                                                _netz*halle;
                                                                h.setzen(-8,-8,-15);
                                                                gb=new _geometriequader(w,h,16,24,30,textur[4]);
                                                                gb->texturkoordinatenlaenge(8,12,15);
                                                                halle=m=gb->erzeugen();
                                                                m->einhaengen(w);
                                                                m->subtraktiv(false);
                                                                m->transparentfaktor(0);
                                                                m->transparent(false);
                                                                m->anfang(pit);
                                                                pit->textur(textur[5]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[5]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[6]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[6]);
                                                                m->anlegentexturkoordinaten(5);
                                                                m->anlegenlightmap("lightmaphalle",2);
                                                                
                                                                
                                                               
                                                                halle->subtraktiv(true);
                                                                //-------------------------- säulen --------------------------
                                                                _zufallsgenerator<> R;
                                                                _netz*mv=0;
                                                               /* double ho;
                                                                for(double u=-6;u<=6;u+=12)
                                                                for(double n=-6;n<=6;n+=3){
                                                                 ho=R.berechnen(6,15);
                                                                 h.setzen(n,-9,u);
                                                                 vx.setzen(2,0,0);
                                                                 vy.setzen(0,ho,0);
                                                                 vz.setzen(0,0,2);
                                                                 gb=new _geometriequader(w,h,vx,vy,vz,textur[10]);
                                                                 gb->texturkoordinatenlaenge(1,ho*0.5f,1);
                                                                 m=gb->erzeugen();
                                                                 m->einhaengen(w);
                                                                 m->maskiert(false);
                                                                 m->zweiseitig(true);
                                                                // m->zeichnenkante(true);
                                                                // m->zeichnennormale(true);
                                                                 m->brechzahl(1.4);
                                                                // m->textur(textur[10]);
                                                                 
                                                                 h.setzen(-1,0,-1);
                                                                 m->verschiebenvertex(h);
                                                                 m->anlegenlightmap("lightmapsaeule",0.5);
                                                                 if(mv) mv->vereinigen(m); else mv=m;
                                                                };*/
                                                                //-----------------------  quer ----------------------------
                                                              /*  h.setzen(-8,1,-2);
                                                                vx.setzen(16,0,0);
                                                                vy.setzen(0,4,0);
                                                                vz.setzen(0,0,4);
                                                                gb=new _geometriequader(w,h,vx,vy,vz,textur[7]);
                                                                gb->texturkoordinatenlaenge(8,2,2);
                                                                m=gb->erzeugen();
                                                                m->einhaengen(w);
                                                               // m->anlegenlightmap("lightmapquer",0.5);
                                                                m->zweiseitig(true);
                                                                h.setzen(-8,-6,-2);
                                                                vx.setzen(4,0,0);
                                                                vy.setzen(0,7,0);
                                                                vz.setzen(0,0,4);
                                                                gb=new _geometriequader(w,h,vx,vy,vz,textur[7]);
                                                                gb->texturkoordinatenlaenge(2,4.5,2);
                                                                _netz*mq0=gb->erzeugen();
                                                                //m->einhaengen(w);
                                                              //  m->anlegenlightmap("lightmapquerl",0.5);
                                                               // m->zweiseitig(true);
                                                                h.setzen(4,-6,-2);
                                                                vx.setzen(4,0,0);
                                                                vy.setzen(0,7,0);
                                                                vz.setzen(0,0,4);
                                                                gb=new _geometriequader(w,h,vx,vy,vz,textur[7]);
                                                                gb->texturkoordinatenlaenge(2,4.5,2);
                                                                _netz*mq1=gb->erzeugen();
                                                              //  m->einhaengen(w);
                                                               // m->anlegenlightmap("lightmapquerr",0.5);
                                                               // m->zweiseitig(true);
                                                                 ism.bearbeiten(m,mq0,2);
                                                                 ism.bearbeiten(m,mq1,2);
                                                                 _netz*m00=m->duplizieren();
                                                                 _netz*m01=m->duplizieren();
                                                                 *m00-=_vektor<double>(0,0,10);
                                                                 *m01+=_vektor<double>(0,0,10);
                                                                 m->vereinigen(m00);
                                                                 m->vereinigen(m01);
                                                                 m->anlegenlightmap("lightmapquer",2);*/
                                                                 //----------------------------feuerwürfel-----------------------
                                                             /*  h.setzen(0,-5,0);
                                                                vx.setzen(2,0,0);
                                                                vy.setzen(0,2,0);
                                                                vz.setzen(0,0,2);
                                                                //vz.setzen(sin(240*_ph)*1.5,2,cos(240*_ph)*1.5);
                                                                gb=new _geometriequader(w,h,vx,vy,vz,textur[11]);
                                                                gb->texturkoordinatenlaenge(1,1,1);
                                                                m=gb->erzeugen();
                                                                m->einhaengen(w);
                                                                h.setzen(-1,-1,-1);
                                                                m->verschiebenvertex(h);
                                                                
                                                                m->subtraktiv(false);
                                                                m->transparent(true);
                                                                m->zweiseitig(true);
                                                                m->rotiereny(-30);
                                                                m->rotierenx(24);
                                                                //double al;
                                                                //al=(acos(sqrt(8.0f)/sqrt(sqrt(8.0f)*sqrt(8.0f)+4.0f))*180.0f)/_pi;
                                                                //al=90-al;
                                                              //  m->rotierenz(al);
                                                                //h.setzen(-3-cos(30*_ph)*1.97,-1.4,0);
                                                                //*m+=h;
                                                                //m->aktualisieren();
                                                                //ism.bearbeiten(m,halle,0);
                                                                //m->rotiereny(30);
                                                              //  m->rotierenz(20);
                                                                //*m-=h;
                                                                m->aktualisieren();
                                                                
                                                                m->subtraktiv(false);
                                                                m->transparentfaktor(0.5);
                                                                m->transparent(true);
                                                                m->maskiert(false);
                                                                m->zweiseitig(true);
                                                                m->zeichnenkante(true);
                                                                m->zeichnennormale(true);
                                                                m->brechzahl(1.4);
                                                                m->textur(textur[11]);
                                                                */
                                                                //-------------------------- licht ----------------------------
                                                              /*  h.setzen(0,-3,-10);
                                                                c.setzen(1.0,0.3,0.0);
                                                                new _licht<>(w,h,c,6);*/
                                                                h.setzen(0,-5,+5);
                                                                c.setzen(0.05f,0.0,1.0f);
                                                                new _licht<>(w,h,c,40);
                                                                h.setzen(0,-5,-5);
                                                                c.setzen(0.15f,0.0f,1.0f);
                                                                new _licht<>(w,h,c,40);
                                                                /*h.setzen(0,-3,+10);
                                                                c.setzen(1.0,0.2,0.0);
                                                                new _licht<>(w,h,c,6);*/
                                                                
                                                                
                                                                
                                                                h.setzen(4,10,1);
                                                                c.setzen(0.05f,0.2f,0.9f);
                                                                new _licht<>(w,h,c,35);
                                                            /*    h.setzen(-4,10,-1);
                                                                c.setzen(0.8,0.7,0.1);
                                                                new _licht<>(w,h,c,55);
                                                                h.setzen(0,11,0);
                                                                c.setzen(1.0,0.5,0.1);
                                                                new _licht<>(w,h,c,25);*/
                                                               /* h.setzen(1.5,-7,-7.5);
                                                                c.setzen(1,0.31,0);
                                                                new _licht<>(w,h,c,200);*/
                                                               /* h.setzen(7.5,4,7.5);
                                                                c.setzen(0.01,1,0);
                                                                new _licht<>(w,h,c,200);*/
                                                                //--------------------------------------- sprites -------------------------------------------
                                                                h.setzen(220,-270,150);
                                                                vx.setzen(5,0,0);
                                                                vy.setzen(0,5,0);
                                                                new _sprite(w,w,h,vx,vy,textur[5]);
                                                                //---------------------------------------- gravitation --------------------------------------
                                                                h.setzen(5,-70,5);
                                                                new _gravitation<>(w,h,1500);
                                                                //-------------------------------------- figur,spieler -------------------------------------
                                                                h.setzen(20,20,20);
                                                                vx.setzen(1,0,0);
                                                                pqdeath=new _partikelquellesprite(w,w,h,vx,50,textur[8]);
                                                                pqdeath->einfuegentextur(textur[7]);
                                                                pqdeath->aktiv(false);
                                                                pqdeath->laenge(0.3);
                                                                pqdeath->generationsrate(15);
                                                                pqdeath->generationsratetoleranz(0.5);
                                                                pqdeath->laengetoleranz(0.5);
                                                                pqdeath->vektortoleranz(0.5);
                                                                pqdeath->rotation(60);
                                                                pqdeath->rotationtoleranz(1);
                                                                pqdeath->lebensdauerpartikeltoleranz(0.95);
                                                                pqlife=new _partikelquellesprite(w,w,h,vx,30,textur[4]);
                                                                pqlife->aktiv(false);
                                                                pqlife->laenge(0.1);
                                                                pqlife->laengetoleranz(0.5);
                                                                pqlife->vektortoleranz(0.5);
                                                                pqlife->lebensdauerpartikeltoleranz(0.5);
                                                                h.setzen(350,40,150);
                                                                spieler=new _figurspieler(w,w,h);
                                                                spieler->einfuegentexturdetonation(textur[6]);
                                                                spieler->partikelquelle()->einfuegentextur(textur[8]);
                                                                spieler->partikelquelle()->partikelquelledestruktion(pqdeath);
                                                                //----------------------------------------- welt compiliern ---------------------------
                                                                rohmeshes=w->uebersetzen();
                                                                rohmeshes->loeschen();
                                                                delete rohmeshes;    
                                                              //  w->anlegenlightmapzone("zonenlightmap",0.5);
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              T E S T B A U M O C T A L
//******************************************************************************************************************************************************************************************************
void _testwelt::visualisierenbaum(_welt*we,_baumoctalwuerfel<_weltdebugkreuz,double>*w){
                                                                
                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y0,w->z0),_vektor<double>(w->x1,w->y0,w->z0),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y1,w->z0),_vektor<double>(w->x1,w->y1,w->z0),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y1,w->z1),_vektor<double>(w->x1,w->y1,w->z1),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y0,w->z1),_vektor<double>(w->x1,w->y0,w->z1),_vektor<float>(1,0,0));

                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y0,w->z0),_vektor<double>(w->x0,w->y1,w->z0),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x1,w->y0,w->z0),_vektor<double>(w->x1,w->y1,w->z0),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x1,w->y0,w->z1),_vektor<double>(w->x1,w->y1,w->z1),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y0,w->z1),_vektor<double>(w->x0,w->y1,w->z1),_vektor<float>(1,0,0));

                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y0,w->z0),_vektor<double>(w->x0,w->y0,w->z1),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x1,w->y0,w->z0),_vektor<double>(w->x1,w->y0,w->z1),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x1,w->y1,w->z0),_vektor<double>(w->x1,w->y1,w->z1),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(we,_vektor<double>(w->x0,w->y1,w->z0),_vektor<double>(w->x0,w->y1,w->z1),_vektor<float>(1,0,0));
                                                                
                                                                unsigned int i,j,k;
                                                                for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++) {
                                                                 if(w->kind[i][j][k]){
                                                                  visualisierenbaum(we,w->kind[i][j][k]);
                                                                 };
                                                                };


/*

                                                                new _weltdebuglinie(W,_vektor<double>(w->x0,w->y0,w->z0),_vektor<double>(w->x1,w->y0,w->z0),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(W,_vektor<double>(w->x0,w->y0,w->z0),_vektor<double>(w->x0,w->y1,w->z0),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(W,_vektor<double>(w->x0,w->y0,w->z0),_vektor<double>(w->x0,w->y0,w->z1),_vektor<float>(1,0,0));

                                                                new _weltdebuglinie(W,_vektor<double>(w->x1,w->y1,w->z1),_vektor<double>(w->x0,w->y1,w->z1),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(W,_vektor<double>(w->x1,w->y1,w->z1),_vektor<double>(w->x1,w->y0,w->z1),_vektor<float>(1,0,0));
                                                                new _weltdebuglinie(W,_vektor<double>(w->x1,w->y1,w->z1),_vektor<double>(w->x1,w->y1,w->z0),_vektor<float>(1,0,0));
                                                                */
};
void _testwelt::testbaumoctal(){
                                                                _welt*w;
                                                                _kamera<>*cam;
                                                                _weltdebugkreuz*wp;
                                                                w=new _welt();
                                                                cam=new _kamera<>(w);
                                                                
                                                                _baumoctal<_weltdebugkreuz,double> baum(-10,10,-10,10,-10,10);
                                                                baum.maximalobjektanzahl(1);
                                                                baum.minimalwuerfelkante(0.005f);
                                                                new _weltdebugtext(w,"GRUNDPLATTE",_vektor<double>(-10,10.5+3.3+3.3,-10),_vektor<double>(20,0,0),_vektor<double>(0,3,0),_vektor<float>(1,1,1));
                                                                new _weltdebugtext(w," S ",_vektor<double>(-10,10.5+3.3,-10),_vektor<double>(20,0,0),_vektor<double>(0,3,0),_vektor<float>(1,1,1));
                                                                new _weltdebugtext(w,"N !",_vektor<double>(-10,10.5,-10),_vektor<double>(20,0,0),_vektor<double>(0,3,0),_vektor<float>(1,1,1));
                                                                new _weltdebugtext(w,"::_baumoctal<T,_tg> : Test mit limitierter wuerfelkantenlänge = 0.5f",_vektor<double>(-10,-10.5-3,-10),_vektor<double>(20,0,0),_vektor<double>(0,0.65f,0),_vektor<float>(1,1,1));
                                                                wp=new _weltdebugkreuz(w,_vektor<double>(1,-4,1), 0.05f,_vektor<float>(1,1,0));
                                                                baum.einhaengen(wp,wp->ort()[0],wp->ort()[0],wp->ort()[1],wp->ort()[1],wp->ort()[2],wp->ort()[2]);
                                                                wp=new _weltdebugkreuz(w,_vektor<double>(2,-4,1), 0.05f,_vektor<float>(1,1,0));
                                                                baum.einhaengen(wp,wp->ort()[0],wp->ort()[0],wp->ort()[1],wp->ort()[1],wp->ort()[2],wp->ort()[2]);
                                                                wp=new _weltdebugkreuz(w,_vektor<double>(2,-4,1.1f), 0.05f,_vektor<float>(1,1,0));
                                                                baum.einhaengen(wp,wp->ort()[0],wp->ort()[0],wp->ort()[1],wp->ort()[1],wp->ort()[2],wp->ort()[2]);
                                                                wp=new _weltdebugkreuz(w,_vektor<double>(-9,-9,-9),0.05f,_vektor<float>(1,1,0));
                                                                baum.einhaengen(wp,wp->ort()[0],wp->ort()[0],wp->ort()[1],wp->ort()[1],wp->ort()[2],wp->ort()[2]);
                                                                wp=new _weltdebugkreuz(w,_vektor<double>(7,2,2),  0.05f,_vektor<float>(1,1,0));
                                                                baum.einhaengen(wp,wp->ort()[0],wp->ort()[0],wp->ort()[1],wp->ort()[1],wp->ort()[2],wp->ort()[2]);
                                                                visualisierenbaum(w,baum.wurzel());
                                                                w->eigenetransformation(false);
                                                                display(w,cam,0);
                                                                delete w;
                                                                w=0;
                                                                
};
template <class _tg=typgeometrie> class _feldvertex{
    public:
        _feldvertex(){
                                                                x=y=z=0;
        };
        _feldvertex(_tg ix,_tg iy,_tg iz){
                                                                x=ix;
                                                                y=iy;
                                                                z=iz;
        };  
        void setzen(_tg ix,_tg iy,_tg iz){
                                                                x=ix;
                                                                y=iy;
                                                                z=iz;
        };                                                              
        _tg x;
        _tg y;
        _tg z;
                        
};
class _feldindex{
    public:
        _feldindex(){
                                                                i[0]=0;
                                                                i[1]=1;
                                                                i[2]=2;
        };
        _feldindex(int i0,int i1,int i2){
                                                                i[0]=i0;
                                                                i[1]=i1;
                                                                i[2]=i2;
        };
        void setzen(int i0,int i1,int i2){
                                                                i[0]=i0;
                                                                i[1]=i1;
                                                                i[2]=i2;
        };
        int i[3];
};
//******************************************************************************************************************************************************************************************************
//                                                              K U G E L  T E S T 
//******************************************************************************************************************************************************************************************************
void _testwelt::oxydstein(_welt*w,int x,int y,int wx,int wy,_textur<_to>*dach,_textur<_to>*seite,_liste<_netz>*os){
                                                                _vektor<> h;
                                                                _netz*m;
                                                                _geometriequader*gb;
                                                                _polygon*pit;
                                                                h.setzen(x,0,y);
                                                                gb=new _geometriequader(w,h,_vektor<_tg>(wx,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,wy),seite);
                                                                gb->texturkoordinatenlaenge(wx/2,1,wy/2);
                                                                m=gb->erzeugen();
                                                                m->anfang(pit);
                                                                pit->textur(dach);
                                                                pit=pit->naechstes();
                                                                pit->textur(dach);
                                                                m->einhaengen(w);
                                                                m->anlegentexturkoordinaten(2);
                                                                m->anlegenlightmap("lightmapoxyd",1);
                                                                m->subtraktiv(false);
                                                                m->transparentfaktor(0);
                                                                m->transparent(false);                                                                
                                                                m->verwendentexturdynamisch(true);
                                                                m->verwendentextur(true);
                                                                os->einhaengen(m);
};
void _testwelt::testkugel(){
                                                                _welt*w;
                                                                _kamera<>*cam;
                                                                //_liste<_netz >*rohmeshes;
                                                                _bestrahler*B;
                                                                _win::_grafikopengl<>*gra;
                                                                _win::_tastatur kb;
                                                                _win::_maus<>*mo;
                                                                _spinne*spinne;
                                                                _partition::_zone*zone;
                                                                _netz*m;
                                                                _vektor<> h;
                                                                _vektor<> hh;
                                                                _vektor<> vx;
                                                                _vektor<> vy;
                                                                _vektor<> vz;
                                                                _vektor<> vec;
                                                                _vektor<> rad;
                                                                _vektor<typgeometrie> v;
                                                                _vektor<typgeometrie> x;
                                                                _vektor<typoptik> c;
                                                                _vektor<unsigned int> res;
                                                                _geometriequader*gb;
                                                                _geometrieraum*gr;
                                                                _geometriezylinder*gz;
                                                                _modifikationnetzintersektion ism;
                                                                _polygon*pit;
                                                                _liste<_netz >*rohmeshes;
                                                                //------------------------------------ welt anlegen --------------------------------------------------
                                                                timer.animieren();
                                                                time[0]=timer.system();
                                                                w=new _welt();
                                                                w->time(&timer);
                                                                texturen();
                                                                timer.animieren();
                                                                time[1]=timer.system();
                                                                cam=new _kamera<>(w);
                                                                cam->setzen(12.5,0.5,1);
                                                                cam->yaw(0);
                                                                cam->rot(0);
                                                                cam->aktualisieren();
                                                                //-------------------------------umgebung------------------------------
                                                                _netz*halle;
                                                                h.setzen(0,0,0);
                                                                gb=new _geometriequader(w,h,_vektor<_tg>(32,0,0),_vektor<_tg>(0,24,0),_vektor<_tg>(0,0,24),textur[2]);
                                                                gb->texturkoordinatenlaenge(32,24,24);
                                                                m=gb->erzeugen();
                                                                m->einhaengen(w);
                                                                m->anfang(pit);
                                                                pit->textur(textur[0]);
                                                                pit=pit->naechstes();
                                                                pit->textur(textur[0]);
                                                                m->anlegentexturkoordinaten(2);
                                                                m->anlegenlightmap("lightmaphalle",0.4);
                                                                m->subtraktiv(true);
                                                                m->transparentfaktor(0);
                                                                m->transparent(false);                                                                
                                                                m->verwendentexturdynamisch(true);
                                                                m->verwendentextur(true);

                                                                _liste<_netz> os;
                                                                _listenknoten<_netz>*osit;
                                                                oxydstein(w,0,0,2,2,textur[2],textur[0],&os);
                                                                oxydstein(w,30,0,2,2,textur[2],textur[0],&os);
                                                                oxydstein(w,0,22,2,2,textur[2],textur[0],&os);
                                                                oxydstein(w,30,22,2,2,textur[2],textur[0],&os);
                                                                oxydstein(w,26,4,2,14,textur[2],textur[0],&os);
                                                                oxydstein(w,4,4,2,14,textur[2],textur[0],&os);
                                                                
                                                                m=0;
                                                                if(os.anfang(osit))do{
                                                                 if(m==0){
                                                                  m=osit->objekt();
                                                                 }else{
                                                                  ism.bearbeiten(m,osit->objekt(),2);
                                                                  osit->loeschmarkierungobjekt(true);
                                                                 };
                                                                }while(os.naechstes(osit));
                                                                os.loeschenmarkiert();
                                                                os.aushaengen();
                                                                
                                                                /*
                                                     
                                                                m=0;
                                                                if(os.anfang(osit))do{
                                                                 if(m==0){
                                                                  m=osit->objekt();
                                                                 }else{
                                                                  ism.bearbeiten(m,osit->objekt(),2);
                                                                  osit->loeschmarkierungobjekt(true);
                                                                 };
                                                                }while(os.naechstes(osit));
                                                                os.loeschenmarkiert();
                                                                os.aushaengen();
                                                               */
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                //m->verwendenverbinderfarbe(false);
                                                                //m->farbeverbinder(_vektor<_to>(1,1,1));
                                                               // m->subtraktiv(false);
                                                              //  m->transparentfaktor(0);
                                                              //  m->transparent(false);
                                                              //  m->anfang(pit);
                                                              //  pit->textur(textur[0]);
                                                              //  pit=pit->naechstes();
                                                              //  pit->textur(textur[0]);
                                                              ////  pit=pit->naechstes();
                                                              //  pit->textur(textur[0]);
                                                              //  pit=pit->naechstes();
                                                              //  pit->textur(textur[0]);
                                                               /* h.setzen(0,0,24);
                                                                gr=new _geometrieraum(w,h,_vektor<_tg>(32,0,0),_vektor<_tg>(0,24,0),_vektor<_tg>(0,0,12),textur[0],textur[2],textur[3],textur[2],textur[10]);
                                                                gr->texturkoordinatenlaenge(16,12,12);
                                                                halle=m=gr->erzeugen();
                                                                m->einhaengen(w);
                                                                m->anlegentexturkoordinaten(2);
                                                                m->anlegenlightmap("lightmaphalle",1);
                                                                halle->subtraktiv(true);*/
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                //-----------------------  vertiefung ----------------------------
                                                             /*   h.setzen(16,-1,0);
                                                                vx.setzen(24,0,0);
                                                                vy.setzen(0,1,0);
                                                                vz.setzen(0,0,24);
                                                                gb=new _geometriequader(w,h,vx,vy,vz,textur[1]);
                                                                gb->texturkoordinatenlaenge(24,1,24);
                                                                m=gb->erzeugen();
                                                                m->einhaengen(w);
                                                                m->anlegentexturkoordinaten(2);
                                                                m->anlegenlightmap("lightmaphalle",2);
                                                                m->subtraktiv(true);*/
                                                                //-------------------------- licht ----------------------------
                                                                h.setzen(1,8,23);
                                                                c.setzen(1.0f,1.0f,1.0f);
                                                                new _licht<>(w,h,c,150);
                                                               /* h.setzen(20,-0.5,12);
                                                                c.setzen(1,1,1);
                                                                new _licht<>(w,h,c,100);
                                                                h.setzen(4,10,1);
                                                                c.setzen(0.7f,0.6f,0.4f);
                                                                new _licht<>(w,h,c,135);*/
                                                                //---------------------------------------- gravitation --------------------------------------
                                                                h.setzen(220,-270,150);
                                                                new _gravitation<>(w,h,1500);
                                                                //----------------------------------------- welt compiliern ---------------------------
                                                                rohmeshes=w->uebersetzen();
                                                                rohmeshes->loeschen();
                                                                delete rohmeshes;    
                                                                
                                                                
                                                                
                                                              //  w->anlegenlightmapzone("zonenlightmap",0.5);
                                                                cam->laenge(2);
                                                                cam->groesse(1.024,0.768);
                                                                cam->aktualisieren();
                                                                mo=new _win::_maus<>(399,399);
                                                                mo->relativ(true);
                                                                mo->verstecken();
                                                                
                                                                RECT r;
                                                                unsigned int wx,wy;
                                                                SystemParametersInfo(SPI_GETWORKAREA,0,&r,0);
                                                                wx=abs(r.right-r.left);
                                                                wy=abs(r.top-r.bottom);
                                                                gra= new _win::_grafikopengl<>(0,0,wx,wy+32);
                                                                gra->texturen(&tl);
                                                                gra->aktivitaet(true);
                                                                gra->loeschenseite();
                                                                gra->umschaltenseite();
                                                                //L->schreiben("1");
                                                                //----------------------------------------- skelett anlegen ----------------------------
                                                                spinne=new _spinne(w,_vektor<double>(25,0.5,20));
                                                                _basis::_liste<_kugel> kugellist;
                                                              //  _kugel * kugel=new _kugel(w,&kugellist,_vektor<double>(0,-6.2,0),0.4,_vektor<double>(+0.080011113121,0.043,-0.01));
                                                              //  _kugel * kugel=new _kugel(w,&kugellist,_vektor<double>(6.540930092,6.898130069,14.11098494),0.4,_vektor<double>(0,0,0));
                                                              
                                                              
                                                              
                                                              
                                                              
                                                              //for(_tg x=0;x<4;x++)
                                                            /*  for(_tg y=0;y<2;y++)
                                                             
                                                              {
                                                                _kugel*kk=new _kugel(w,&kugellist,_vektor<double>(26+x,14,6+y),0.4,_vektor<double>(0,-0.1,0));
                                                                kk->farbe(_vektor<_to>(1-x/40.f,x/4.0f,y/4.0f));
                                                              };*/
                                                              //  new _kugel(w,&kugellist,_vektor<double>(28,14.00001,6),0.4,_vektor<double>(0.0911111,0,0));
                                                                //new _kugel(w,&kugellist,_vektor<double>(26,14.000011,6),0.4,_vektor<double>(-0.0411,0,0));
                                                             //   new _weltdebugtext(w,"ODE DEMONSTRATION",_vektor<_tg>(15,1,1),_vektor<_tg>(-10,0,0),_vektor<_tg>(0,2,0),_vektor<_to>(1,0.7,0.2));
                                                              /*  _kugel*kk=0;
                                                                for(_tg x=0;x<2;x++)
                                                                for(_tg y=0;y<2;y++){
                                                                 kk=new _kugel(w,&kugellist,_vektor<double>(8+x*2,14,8+y*2),0.9,_vektor<double>(0.111,0,0));
                                                                 if((x==0)&&(y==0)) kk->farbe(_vektor<_to>(1,0,0));
                                                                };*/
                                                          //      new _kugel(w,&kugellist,_vektor<double>(11,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                _kugel*k0;
                                                                _kugel*k1;
                                                                //k1=new _kugel(w,&kugellist,_vektor<double>(16,8,18.20),4,_vektor<double>(0,0,0));
                                                                //k1->farbe(_vektor<_to>(0,1,0));
                                                                //k1=new _kugel(w,&kugellist,_vektor<double>(16,7,12.20),4,_vektor<double>(-0.0,0,0));
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(11,1,12.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(1,0,0));
                                                                
                                                                
                                                                
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(12,1,12.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0,1,1));
                                                                new _gummiband(k0,6,0.7,12,0.01);
                                                                new _gummiband(k0,26,0.7,12,0.002);

                                                                _kugel*alt=0;
                                                                for(int qq=0;qq<22;qq++){
                                                                 k0=new _kugel(w,&kugellist,_vektor<double>(13,1+qq,12.00),0.4,_vektor<double>(+0.2,0,0));
                                                                 k0->farbe(_vektor<_to>(0.1,0,0.7));
                                                                 if(qq==0) new _gummiband(k0,0,9.5,24,0.02); 
                                                                 if(alt) new _gummiband(k0,alt,0.02);
                                                                 if(qq==21) new _gummiband(k0,32,9.5,0,0.02);
                                                                 alt=k0;
                                                                };
                                                                
                                                                
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(12,1,10.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0,1,1));
                                                                new _gummiband(k0,6,0.7,10,0.01);
                                                                new _gummiband(k0,26,0.7,10,0.002);
                                                                
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(13,1,10.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0,1,1));
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(12,1,8.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0,1,0));
                                                                new _gummiband(k0,6,0.7,8,0.01);
                                                                new _gummiband(k0,26,0.7,8,0.002);

                                                                k0=new _kugel(w,&kugellist,_vektor<double>(13,1,8.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0,1,0));
                                                                new _gummiband(k0,13,24,8,0.0002);
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(12,1,6.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(1,1,0));
                                                                new _gummiband(k0,6,0.7,6,0.01);
                                                                new _gummiband(k0,26,0.7,6,0.002);

                                                                k0=new _kugel(w,&kugellist,_vektor<double>(13,1,6.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(1,1,0));
                                                                new _gummiband(k0,13,24,6,0.0001);
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(12,1,4.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(1,0.5,0));
                                                                new _gummiband(k0,6,0.7,4,0.01);
                                                                new _gummiband(k0,26,0.7,4,0.002);

                                                                k0=new _kugel(w,&kugellist,_vektor<double>(13,1,4.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(1,0.5,0));
                                                                new _gummiband(k0,12,24,14,0.0004);
                                                              /*  k0=new _kugel(w,&kugellist,_vektor<double>(12,1,2.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0.8,0.4,0));
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(13,1,2.00),0.4,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0.8,0.4,0));*/
                                                                k0=new _kugel(w,&kugellist,_vektor<double>(16,8,12.00),3,_vektor<double>(+0.0,0,0));
                                                                k0->farbe(_vektor<_to>(0,1,0));
                                                                new _gummiband(k0,16,4.1,0 ,0.02);
                                                                new _gummiband(k0,16,4.1,24,0.04);
                                                                
                                                               
                                                                
                                                               /* new _kugel(w,&kugellist,_vektor<double>(17,1,12.20),0.4,_vektor<double>(-0.2,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(18,1,12.20),0.4,_vektor<double>(-0.2,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(19,1,12.20),0.4,_vektor<double>(-0.2,0,0));
                                                                 for(_tg x=0;x<2;x++) for(_tg y=0;y<2;y++) {
                                                                  k1=new _kugel(w,&kugellist,_vektor<double>(20+x,1,12.20+y),0.2,_vektor<double>(-0.2,0,0));
                                                                  k1->farbe(_vektor<_to>(0,1,1));
                                                                 };*/
                                                                
                                                             
                                                               /* new _kugel(w,&kugellist,_vektor<double>(13,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(14,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(15,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(16,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(17,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(18,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(19,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(20,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(21,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(22,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(23,14.000001,10.00),0.4,_vektor<double>(0.111,0,0));
                                                                */
                                                              /*  kk=new _kugel(w,&kugellist,_vektor<double>(15,14.000001,10),0.4,_vektor<double>(0.0,0,0));
                                                                kk->farbe(_vektor<_to>(1.0f,0,0));
                                                                kk=new _kugel(w,&kugellist,_vektor<double>(19,14.000001,20),0.4,_vektor<double>(0.005,0,0));
                                                                kk->farbe(_vektor<_to>(1.0f,1.0f,0));
                                                                kk=new _kugel(w,&kugellist,_vektor<double>(18,14.000001,20),0.2,_vektor<double>(-0,0,0));
                                                               kk->farbe(_vektor<_to>(0,0.2f,1));*/
                                                              /*  new _kugel(w,&kugellist,_vektor<double>(17,14.000001,20),0.2,_vektor<double>(0,0,0));
                                                                 new _kugel(w,&kugellist,_vektor<double>(16,14.000001,20),0.2,_vektor<double>(0,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(15,14.000001,20),0.2,_vektor<double>(0,0,0));
                                                                new _kugel(w,&kugellist,_vektor<double>(1,14.000001,6),0.4,_vektor<double>(0.111,0,0));
                                                                kk=new _kugel(w,&kugellist,_vektor<double>(2,14.000001,20),0.4,_vektor<double>(0.02,0,0));
                                                                kk->farbe(_vektor<_to>(0,0,1));*/

                                                              

                                                               // new _weltdebugzylinder(w,_vektor<double>(2,-8,0.2),_vektor<double>(0,5,0),0.4,_vektor<float>(0,1,1));
                                                                bool raus;
                                                                //L->schreiben("2");
                                                                //----------------------------------------- lightmap bestrahlung -----------------------
                                                                B=new _bestrahler();
                                                                B->lichtambient(_vektor<float>(0.1f,0.1f,0.1f));
                                                                B->bestrahlenlightmapzone(w);
                                                                //w->bestrahlenlightmap();
                                                                w->uebergebenlightmap(gra);
                                                                delete B;
                                                                //L->schreiben("3");
                                                                //----------------------------------------- Intersektionsszene anlegen -----------------
                                                                _netz*ine[10];
                                                                _licht<>*inl[10];
                                                                _kurvehermite<_tg> kh0(_vektor<_tg>(8,3.5,5.5)  ,_vektor<_tg>(6.5,3.5,5.5),_vektor<_tg>(0,0,0),_vektor<_tg>(0,0,0));
                                                                _kurvehermite<_tg> kh1(_vektor<_tg>(6.5,3.5,5.5),_vektor<_tg>(6.5,5.5,5.5),_vektor<_tg>(5,-5,0),_vektor<_tg>(-5,-5,0));
                                                                _kurvehermite<_tg> kh2(_vektor<_tg>(6.5,5.5,5.5),_vektor<_tg>(4.5,5.5,5.5),_vektor<_tg>(5,5,0),_vektor<_tg>(5,-5,0));
                                                                _kurvehermite<_tg> kh3(_vektor<_tg>(4.5,5.5,5.5),_vektor<_tg>(4.5,3.5,5.5),_vektor<_tg>(-5,5,0),_vektor<_tg>(5,5,0));
                                                                _kurvehermite<_tg> kh4(_vektor<_tg>(4.5,3.5,5.5),_vektor<_tg>(10,3.5,5.5),_vektor<_tg>(-5,-5,0),_vektor<_tg>(0,0,0));
                                                                _kurvehermite<_tg> kh5(_vektor<_tg>(5,4,5),_vektor<_tg>(7,4,5),_vektor<_tg>(0,+8,0),_vektor<_tg>(0,-8,0));
                                                                _kurvehermite<_tg> kh6(_vektor<_tg>(5,4,5),_vektor<_tg>(5,6,5),_vektor<_tg>(0,0,+7),_vektor<_tg>(0,0,-7));
                                                                _kurvehermite<_tg> kh7(_vektor<_tg>(6.8,1,5.8),_vektor<_tg>(6.8,6,5.8),_vektor<_tg>(0,0,0),_vektor<_tg>(0,0,0));
                                                                _kurvehermite<_tg> kh8(_vektor<_tg>(6.8,6,5.8),_vektor<_tg>(8.8,6,5.8),_vektor<_tg>(0,-15,0),_vektor<_tg>(0,+15,0));
                                                                _kurvehermite<_tg> kh9(_vektor<_tg>(8.8,6,5.8),_vektor<_tg>(4.8,6,5.8),_vektor<_tg>(0,-15,0),_vektor<_tg>(0,+15,0));
                                                                _kurvehermite<_tg> kh10(_vektor<_tg>(4.8,6,5.8),_vektor<_tg>(6.8,1,5.8),_vektor<_tg>(0,-15,0),_vektor<_tg>(0,0,0));
                                                                _kurvehermite<_tg> kh11(_vektor<_tg>(5,6,5),_vektor<_tg>(9,6,5),_vektor<_tg>(0,0,+10),_vektor<_tg>(0,0,-10));
                                                                _kurvehermite<_tg> kh12(_vektor<_tg>(4,5.9,16),_vektor<_tg>(4,5.9,6),_vektor<_tg>(0,0,0),_vektor<_tg>(0,0,0));
                                                                _kurvehermite<_tg> kh13(_vektor<_tg>(5,6,5),_vektor<_tg>(5,6,7),_vektor<_tg>(0,+35,0),_vektor<_tg>(0,-1,0));
                                                                _kurvehermite<_tg> kh14(_vektor<_tg>(5,6,7),_vektor<_tg>(5,6,9),_vektor<_tg>(0,+35,0),_vektor<_tg>(0,-1,0));
                                                                _kurvehermite<_tg> kh15(_vektor<_tg>(4,5.9,6),_vektor<_tg>(6,4,8),_vektor<_tg>(0,0,0),_vektor<_tg>(0,0,0));
                                                                _kurvehermite<_tg> kh16(_vektor<_tg>(4,8,10),_vektor<_tg>(4,1,10),_vektor<_tg>(0,0,0),_vektor<_tg>(0,0,0));
                                                                _kurvehermite<_tg> kh17(_vektor<_tg>(4+14,8,10),_vektor<_tg>(4+14,1,10),_vektor<_tg>(0,0,0),_vektor<_tg>(0,0,0));
                                                                h.setzen(10,10,10);
                                                                inl[0]=new _licht<>(w,h,_vektor<_to>(1,0.6,0.1),35);
                                                                h.setzen(1,1,1);
                                                                inl[1]=new _licht<>(w,h,_vektor<_to>(1,0.28,0.05),25);
                                                                /*
                                                                //--------------------------------------------------------------------------------------
                                                                dJointGroupID contactgroup;
                                                                contactgroup = dJointGroupCreate(0);
                                                                //--------------------------------------------------------------------------------------
                                                                
                                                                _feldvertex<dReal>*vfeld;
                                                                _feldindex*ifeld;
                                                                vfeld= new _feldvertex<dReal>[4];
                                                                ifeld= new _feldindex[2];
                                                                vfeld[0].setzen(0,0,0);
                                                                vfeld[1].setzen(100,0,0);
                                                                vfeld[2].setzen(100,100,0);
                                                                vfeld[3].setzen(0,100,0);
                                                                ifeld[0].setzen(0,1,2);
                                                                ifeld[1].setzen(0,2,3);
                                                                
                                                                dTriMeshDataID odemesh;
                                                                dGeomID odemeshgeom;
                                                                dBodyID odemeshbody;
                                                                odemesh=dGeomTriMeshDataCreate();
                                                                

                                                                
                                                                dGeomTriMeshDataBuildDouble(odemesh,vfeld,sizeof(_feldvertex<dReal>),4,ifeld,2,sizeof(_feldindex));
                                                                odemeshgeom=dCreateTriMesh(w->odespace,odemesh,0,0,0);
                                                                odemeshbody=dBodyCreate(w->odewelt);
                                                                dGeomSetBody(odemeshgeom,odemeshbody);
                                                                */
                                                                
                                                                gra->nebelmodus(1);
                                                                gra->nebelfarbe(0.5f,0.5f,0.5f);
                                                                gra->nebeldichte(0.008f);
                                                                gra->nebeldistanz(1,40);
                                                                gra->nebel(false); 
                                                                glHint(GL_FOG_HINT, GL_DONT_CARE);  
                                                                float xxx=0;
                                                                while(kb.escape()) S->animieren();
                                                                if(w->anfang(zone)) {
                                                                 spinne->zone(zone);
                                                                 spinne->aktualisierensektor();
                                                                };
                                                                raus=false;
                                                                w->eigenetransformation(false);
                                                                _kugel*kit;
                                                                _tg tt=0;
                                                                int tm=-1;
                                                                do{ 
                                                                 float ff=0.5f+float(sin(xxx*_ph))*0.5f;
                                                                 gra->nebelfarbe(ff,ff,ff);
                                                                 gra->loeschenseite();
                                                                 
                                                                 
                                                                 if((kb.shift()==false)&&(kb.control()==false)) cam->bewegen(&kb,mo,1); else{
                                                                 
                                                                  if(kb.shift()){
                                                                   _vektor<double> mk=mo->holen();
                                                                   _tg vadd[3];
                                                                   vadd[0]=mk[0];
                                                                   vadd[1]=0;
                                                                   vadd[2]=-mk[1];
                                                                   ::multiplizieren<_tg>(vadd,0.001f);
                                                                   if(kugellist.anfang(kit)){
                                                                    ::addieren(kit->vektor(),vadd);
                                                                   };
                                                                  };

                                                                  if(kb.control()){
                                                                   _vektor<double> mk=mo->holen();

                                                                   _tg vadd[3];
                                                                   vadd[0]=mk[0];
                                                                   vadd[1]=-mk[1];
                                                                   vadd[2]=0;
                                                                   ::multiplizieren<_tg>(vadd,0.001f);

                                                                   if(kugellist.anfang(kit)){
                                                                    ::addieren(kit->vektor(),vadd);
                                                                   };
                                                                  };
                                                                 };
                                                                 
                                                                 
                                                                 w->transformieren(gra,cam,false);
                                                                 w->zeichnen(gra); 
                                                                 w->animieren();
                                                                 spinne->visualisieren();
                                                                 gra->umschaltenseite();                                                                 
                                                                 spinne->animieren();
                                                                 if(kugellist.anfang(kit))do{
                                                                  kit->animieren();
                                                                 }while(kugellist.naechstes(kit));
                                                                 
                                                   
                                                                 _tg fs=1;
                                                                 _vektor<_tg> gg;
                                                                 ism.schreibenlogbuch(false);
                                                                 /*
                                                                 switch(tm){
                                                                 case -1:
                                                                  h.setzen(5,4,5);
                                                                  gb=new _geometriequader(w,h,2,2,2,textur[0]);
                                                                  gb->texturkoordinatenlaenge(2,2,2);
                                                                  ine[0]=gb->erzeugen();
                                                                  ine[0]->subtraktiv(false);
                                                                  ine[0]->einhaengen(w);
                                                                  ine[0]->markierungpolygon(1);
                                                                  ine[0]->transparent(false);
                                                                  ine[0]->transparentfaktor(0.4);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  ine[0]->verwendenverbinderfarbe(true);
                                                                  delete gb;
                                                                  h=kh0.ort(0);
                                                                  gb=new _geometriequader(w,h,1,1,1,textur[1]);
                                                                  ine[1]=gb->erzeugen();
                                                                  ine[1]->subtraktiv(false);
                                                                  ine[1]->einhaengen(w);
                                                                  ine[1]->markierungpolygon(1);
                                                                  ine[1]->transparent(false);
                                                                  ine[1]->transparentfaktor(0.3);
                                                                  ine[1]->erzeugenvertexlicht();
                                                                  ine[1]->verwendenverbinderfarbe(true);
                                                                  delete gb;
                                                                  tm=0;
                                                                  break;

                                                                 case 0:
                                                                  tt+=0.01*fs;ine[1]->setzen(kh0.berechnen(tt));if(tt>=1) {tm++;tt=0;};
                                                                  ine[1]->erzeugenvertexlicht();
                                                                  break;
                                                                 case 1:
                                                                  ism.bearbeiten(ine[0],ine[1],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  //ine[0]->zeichnenkante(true);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 2:
                                                                  tt+=0.01*fs;ine[1]->setzen(kh1.berechnen(tt));if(tt>=1) {tm++;tt=0;};
                                                                  ine[1]->erzeugenvertexlicht();
                                                                  break;
                                                                 case 3:
                                                                  ism.bearbeiten(ine[0],ine[1],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  //ine[0]->zeichnenkante(true);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 4:
                                                                  tt+=0.01*fs;ine[1]->setzen(kh2.berechnen(tt));if(tt>=1) {tm++;tt=0;};
                                                                  ine[1]->erzeugenvertexlicht();
                                                                  break;
                                                                 case 5:
                                                                  ism.bearbeiten(ine[0],ine[1],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  //ine[0]->zeichnenkante(true);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 6:
                                                                  tt+=0.01*fs;ine[1]->setzen(kh3.berechnen(tt));if(tt>=1) {tm++;tt=0;};
                                                                  ine[1]->erzeugenvertexlicht();
                                                                  break;
                                                                 case 7:
                                                                  ism.bearbeiten(ine[0],ine[1],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 8:
                                                                  tt+=0.01*fs;ine[1]->setzen(kh4.berechnen(tt));if(tt>=1) {tm++;tt=0;};
                                                                  ine[1]->erzeugenvertexlicht();
                                                                  break;
                                                                 case 9:
                                                                  ine[2]=ine[0]->duplizieren();
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  ine[2]->einhaengen(w);
                                                                  tm++;
                                                                  tt=0;
                                                                  break;
                                                                 case 10:
                                                                  tt+=0.005*fs;
                                                                  ine[2]->setzen(kh5.berechnen(tt));
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 11:
                                                                  ism.bearbeiten(ine[0],ine[2],2);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  delete ine[2];
                                                                  tm++;
                                                                  break;
                                                                 case 12:
                                                                  tt+=0.005*fs;
                                                                  ine[0]->setzen(kh6.berechnen(tt));
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 13:
                                                                  h=kh7.ort(0);
                                                                  gb=new _geometriequader(w,h,0.4,2,0.4,textur[7]);
                                                                  gb->texturkoordinatenlaenge(1,5,1);
                                                                  ine[2]=gb->erzeugen();
                                                                  ine[2]->subtraktiv(false);
                                                                  ine[2]->einhaengen(w);
                                                                  ine[2]->markierungpolygon(1);
                                                                  ine[2]->transparent(false);
                                                                  ine[2]->transparentfaktor(0.3);
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  ine[2]->verwendenverbinderfarbe(true);
                                                                  delete gb;
                                                                  tm++;
                                                                  break;
                                                                 case 14:
                                                                  tt+=0.005*fs;
                                                                  ine[2]->setzen(kh7.berechnen(tt));
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 15:
                                                                  ism.bearbeiten(ine[0],ine[2],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  //ine[0]->zeichnenkante(true);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 16:
                                                                  tt+=0.005*fs;
                                                                  ine[2]->setzen(kh8.berechnen(tt));
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 17:
                                                                  ism.bearbeiten(ine[0],ine[2],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  //ine[0]->zeichnenkante(true);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 18:
                                                                  tt+=0.005*fs;
                                                                  ine[2]->setzen(kh9.berechnen(tt));
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 19:
                                                                  ism.bearbeiten(ine[0],ine[2],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  //ine[0]->zeichnenkante(true);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 20:
                                                                  tt+=0.005*fs;
                                                                  ine[2]->setzen(kh10.berechnen(tt));
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 21:
                                                                  ine[2]=ine[0]->duplizieren();
                                                                  ine[2]->einhaengen(w);
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  tt=0;
                                                                  break;
                                                                 case 22:
                                                                  tt+=0.005*fs;
                                                                  ine[2]->setzen(kh11.berechnen(tt));
                                                                  ine[2]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 23:
                                                                  ism.bearbeiten(ine[0],ine[2],2);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  delete ine[2];
                                                                  tm++;
                                                                  break;
                                                                  
                                                                 case 24:
                                                                  h=kh12.ort(0);
                                                                  gb=new _geometriequader(w,h,10,3,4,textur[0]);
                                                                  gb->texturkoordinatenlaenge(10,3,4);
                                                                  ine[3]=gb->erzeugen();
                                                                  ine[3]->subtraktiv(false);
                                                                  ine[3]->einhaengen(w);
                                                                  ine[3]->markierungpolygon(1);
                                                                  ine[3]->transparent(false);
                                                                  ine[3]->transparentfaktor(0.3);
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  ine[3]->verwendenverbinderfarbe(true);
                                                                  delete gb;
                                                                  tm++;
                                                                  break;
                                                       
                                                                 case 25:
                                                                  tt+=0.005*fs;
                                                                  ine[3]->setzen(kh12.berechnen(tt));
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 
                                                                 case 26: 
                                                                  ism.bearbeiten(ine[3],ine[0],0);
                                                                  ine[3]->transparentfaktor(0.5);
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  ine[4]=ine[0];
                                                                  ine[0]=ine[3];
                                                                  ine[3]=ine[4];
                                                                  ine[4]=0;
                                                                  tm++;
                                                                  break;
                                                                 case 27:
                                                                  tt+=0.005;
                                                                  ine[3]->setzen(kh13.berechnen(tt));
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 28:
                                                                  ism.bearbeiten(ine[0],ine[3],0);
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 29:
                                                                  tt+=0.005;
                                                                  ine[3]->setzen(kh14.berechnen(tt));
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 30:
                                                                  ism.bearbeiten(ine[0],ine[3],0);
                                                                  delete ine[3];
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 31:
                                                                  //delete ine[2];
                                                                  //delete ine[1];
                                                                  tt+=0.005;
                                                                  ine[0]->setzen(kh15.berechnen(tt));
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 32:
                                                                  h=kh16.ort(0);
                                                                  gz=new _geometriezylinder(w,h,_vektor<_tg>(2,0,0),_vektor<_tg>(10,10,0),_vektor<_tg>(0,0,2.5),textur[8]);
                                                                  gz->aufloesung(_vektor<unsigned int>(32,1));
                                                                  gz->texturkoordinatenlaenge(12,15,3);
                                                                  ine[3]=gz->erzeugen();
                                                                  ine[3]->subtraktiv(false);
                                                                  ine[3]->einhaengen(w);
                                                                  ine[3]->markierungpolygon(1);
                                                                  ine[3]->transparent(false);
                                                                  ine[3]->transparentfaktor(0.3);
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  ine[3]->verwendenverbinderfarbe(true);
                                                                  delete gz;
                                                                  tm++;
                                                                  break;
                                                                 case 33:
                                                                  tt+=0.005;
                                                                  ine[3]->setzen(kh16.berechnen(tt));
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 34:
                                                                  ism.bearbeiten(ine[0],ine[3],0);
                                                                  delete ine[3];
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 35:
                                                                  h=kh17.ort(0);
                                                                  gz=new _geometriezylinder(w,h,_vektor<_tg>(2,0,0),_vektor<_tg>(-10,10,0),_vektor<_tg>(0,0,2.5),textur[8]);
                                                                  gz->aufloesung(_vektor<unsigned int>(32,1));
                                                                  gz->texturkoordinatenlaenge(12,15,3);
                                                                  ine[3]=gz->erzeugen();
                                                                  ine[3]->subtraktiv(false);
                                                                  ine[3]->einhaengen(w);
                                                                  ine[3]->markierungpolygon(1);
                                                                  ine[3]->transparent(false);
                                                                  ine[3]->transparentfaktor(0.3);
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  ine[3]->verwendenverbinderfarbe(true);
                                                                  delete gz;
                                                                  tm++;
                                                                  break;
                                                                 case 36:
                                                                  tt+=0.005;
                                                                  ine[3]->setzen(kh17.berechnen(tt));
                                                                  ine[3]->erzeugenvertexlicht();
                                                                  if(tt>=1) {tm++;tt=0;};
                                                                  break;
                                                                 case 37:
                                                                  ism.bearbeiten(ine[0],ine[3],0);
                                                                  delete ine[3];
                                                                  ine[0]->transparentfaktor(0.5);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  tm++;
                                                                  break;
                                                                 case 38:
                                                                  ine[0]->verschiebenvertex(_vektor<_tg>(-5,-1.5,-2));
                                                                  *ine[0]+=_vektor<_tg>(5,1.5,2);
                                                                  tm++;
                                                                  tt=0;
                                                                  h.setzen(10,2,8);
                                                                  inl[2]=new _licht<>(w,h,_vektor<_to>(1,0.5,0.1),7);
                                                                  
                                                                  break;
                                                                 case 39:
                                                                  tt+=1;
                                                                  ine[0]->rotiereny(1);
                                                                  ine[0]->erzeugenvertexlicht();
                                                                  if(tt>=90){
                                                                   tm++;
                                                                   tt=0;
                                                                  };
                                                                  break;
                                                                 case 40:
                                                                  ine[0]->zeichnenkante(true);
                                                                  //ine[0]->transparent(true);
                                                                  ine[0]->zeichnennormale(true);
                                                                  tm++;
                                                                  break;
                                                                 case 41:
                                                                  tt+=1;
                                                                  ine[0]->rotiereny(1);
                                                                 // ine[0]->erzeugenvertexlicht();
                                                                  if(tt>=360){
                                                                   tt=0;
                                                                   tm++;
                                                                  };
                                                                  break;
                                                                 case 42:
                                                                  ine[0]->zeichnenkante(false);
                                                                  ine[0]->zeichnennormale(false);
                                                                  tm++;
                                                                  break;
                                                                 case 43:
                                                                  tt+=1;
                                                                  ine[0]->rotiereny(1);
                                                                  //ine[0]->rotierenx(0.31);
                                                                  //ine[0]->rotierenz(0.1123);
                                                                  //ine[0]->erzeugenvertexlicht();
                                                                  if(tt>=(360)){
                                                                   tt=0;
                                                                   tm++;
                                                                  };
                                                                  break;
                                                                 case 44:
                                                                  break;
                                                                  
                                                                  
                                                                  
                                                                 
                                                                  
                                                                  
                                                                  
                                                                 
                                                                  
                                                                  
                                                                  
                                                                   
                                                                 default:
                                                                  tm=-1;
                                                                  tt=0;
                                                                  delete ine[0];
                                                                  delete ine[1];
                                                                  //delete ine[2];
                                                                  break;
                                                                 };
                                                                 */
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 S->animieren();
                                                                 if(kb.escape()) raus=true;
                                                                 xxx+=1;
                                                                }while(raus==false);
                                                                delete gra;
                                                                delete mo;
                                                               /* dJointGroupDestroy(contactgroup);
                                                                dGeomTriMeshDataDestroy(odemesh);
                                                                dBodyDestroy(odemeshbody);
                                                                dGeomDestroy(odemeshgeom);                                                                
                                                                delete[] vfeld;
                                                                delete[] ifeld;*/
                                                                
                                                                
                                                                //--------------------------------------- speichern der rohen welt --------------------------------
                                                                //::weltspeichern<typgeometrie,typoptik,typakustik>("Weltdatenroh.txt",w);
                                                                //--------------------------------------- präparation, übersetzung --------------------------------
                                                                szenedestruktion(w);
                                                                w=0;
};
//******************************************************************************************************************************************************************************************************
//                                                              T E S T S I C H T B A R K E I T 
//******************************************************************************************************************************************************************************************************
_netz* _testwelt::erzeugenraum(_welt*w,_vektor<_tg> h,_vektor<_tg> v0,_vektor<_tg> v1,_vektor<_tg> v2,_textur<>*t,_textur<>*tb,_textur<>*td){                                                                
                                                                _geometriequader*gb;
                                                                _geometrieraum*gr;
                                                                _geometriezylinder*gz;
                                                                _netz*m;
                                                                _polygon*pit;
                                                                //---------------------
                                                                gb=new _geometriequader(w,h,v0,v1,v2,t);
                                                                gb->texturkoordinatenlaenge(v0.laenge(),v1.laenge(),v2.laenge());
                                                                m=gb->erzeugen();
                                                                m->einhaengen(w);
                                                               // m->subtraktiv(false);
                                                              //  m->transparentfaktor(0);
                                                              //  m->transparent(false);
                                                                m->anfang(pit);
                                                                pit->textur(tb);
                                                                pit=pit->naechstes();
                                                                pit->textur(td);
                                                                pit=pit->naechstes();
                                                                //pit->textur(textur[2]);
                                                                pit=pit->naechstes();
                                                                //pit->textur(textur[2]);
                                                                m->anlegentexturkoordinaten(2);
                                                                m->anlegenlightmap("lightmap",2);
                                                                m->subtraktiv(true);
                                                                m->markierungpolygon(1);
                                                                m->maskiert(true);
                                                                delete gb;
                                                                return(m);
};
void _testwelt::testsichtbarkeit(){
                                                                _welt*w;
                                                                _kamera<>*cam;
                                                                _bestrahler*B;
                                                                _win::_grafikopengl<>*gra;
                                                                _win::_tastatur kb;
                                                                _win::_maus<>*mo;
                                                                _partition::_zone*zone;
                                                                _partition::_sektor*sektor;
                                                                _partition::_sektor*sit;
                                                                _netz*m;
                                                                _vektor<> h;
                                                                _vektor<> hh;
                                                                _vektor<> vx;
                                                                _vektor<> vy;
                                                                _vektor<> vz;
                                                                _vektor<> vec;
                                                                _vektor<> rad;
                                                                _vektor<typgeometrie> v;
                                                                _vektor<typgeometrie> x;
                                                                _vektor<typoptik> c;
                                                                _vektor<unsigned int> res;
                                                                _geometriequader*gb;
                                                                _geometrieraum*gr;
                                                                _geometriezylinder*gz;
                                                                _modifikationnetzintersektion ism;
                                                                _polygon*pit;
                                                                _liste<_netz >*rohmeshes;
                                                                bool raus;
                                                                _tg xx;
                                                                _partikelquellesprite*pqdeath;
                                                                _partikelquellesprite*pqlife;
                                                                _partikelquellesprite*pqs[3];
                                                                int svis=1;
                                                                //------------------------------------ welt anlegen --------------------------------------------------
                                                                timer.animieren();
                                                                time[0]=timer.system();
                                                                w=new _welt();
                                                                w->time(&timer);
                                                                texturen();
                                                                timer.animieren();
                                                                time[1]=timer.system();
                                                                cam=new _kamera<>(w);
                                                                cam->setzen(1,1.5,1);
                                                                cam->yaw(0);
                                                                cam->rot(23);
                                                                cam->aktualisieren();
                                                                //-------------------------------------------------------------
                                                                _tg cc=sqrt(_tg(6*6+6*6));
                                                                xx=sqrt((cc*cc)/2.0f);
                                                                erzeugenraum(w,_vektor<_tg>(0,0,0),_vektor<_tg>(10,0,0),_vektor<_tg>(0,10,0),_vektor<_tg>(0,0,10),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(2,10,2),_vektor<_tg>(6,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,6),textur[9],textur[4],textur[4]);
                                                                erzeugenraum(w,_vektor<_tg>(2,-2,2),_vektor<_tg>(6,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,6),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(4,-4,4),_vektor<_tg>(2,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(10,1,10-xx),_vektor<_tg>(6,0,6),_vektor<_tg>(0,8,0),_vektor<_tg>(-6,0,6),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(0,1,-xx),_vektor<_tg>(6,0,6),_vektor<_tg>(0,8,0),_vektor<_tg>(-6,0,6),textur[9],textur[4],textur[9]);
                                                              //  m=erzeugenraum(w,_vektor<_tg>(-7+ 2,3.5,-7+ -2),_vektor<_tg>(32,0,32),_vektor<_tg>(0,3,0),_vektor<_tg>(-3.5,0,3.5),textur[9],textur[4],textur[9]);
                                                           
                                                           
                                                           
                                                                erzeugenraum(w,_vektor<_tg>(-25,-6,4),_vektor<_tg>(60,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(-27,-6,4-10),_vektor<_tg>(2,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,20),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(35,-6,4-10),_vektor<_tg>(2,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,20),textur[9],textur[4],textur[9]);

                                                                erzeugenraum(w,_vektor<_tg>(-27+10,-6,4-10),_vektor<_tg>(2,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,20),textur[9],textur[9],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(35-10,-6,4-10),_vektor<_tg>(2,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,20),textur[9],textur[9],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(-27+20,-6,4-10),_vektor<_tg>(2,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,20),textur[9],textur[9],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(35-20,-6,4-10),_vektor<_tg>(2,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,20),textur[9],textur[9],textur[9]);
                                                                new _licht<>(w,_vektor<_tg>(-16,-5,-3),_vektor<_to>(1,0.4,0),80);
                                                                new _licht<>(w,_vektor<_tg>(- 6,-5,-3),_vektor<_to>(1,0.5,0),80);
                                                                new _licht<>(w,_vektor<_tg>(16,-5,-3),_vektor<_to>(1,0.4,0.1),80);
                                                                new _licht<>(w,_vektor<_tg>(26,-5,-3),_vektor<_to>(1,0.3,0.1),80);


                                                            
                                                                erzeugenraum(w,_vektor<_tg>(-27,-6,4+10),_vektor<_tg>(64,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(-27,-6,-8),_vektor<_tg>(64,0,0),_vektor<_tg>(0,2,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);
                                                            
                                                                erzeugenraum(w,_vektor<_tg>(-27,-10,4),_vektor<_tg>(2,0,0),_vektor<_tg>(0,4,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>( 35,-10,4),_vektor<_tg>(2,0,0),_vektor<_tg>(0,4,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);
                                                                //vorne und hinten : hochkanal für diagonalgang
                                                                erzeugenraum(w,_vektor<_tg>(4-12,-4,-8),_vektor<_tg>(2,0,0),_vektor<_tg>(0,30,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(2+12,-4,14),_vektor<_tg>(2,0,0),_vektor<_tg>(0,30,0),_vektor<_tg>(0,0,2),textur[9],textur[4],textur[9]);



                                                                erzeugenraum(w,_vektor<_tg>( -28,-14,3),_vektor<_tg>(66,0,0),_vektor<_tg>(0,4,0),_vektor<_tg>(0,0,4),textur[9],textur[4],textur[9]);
                                                                m=erzeugenraum(w,_vektor<_tg>( -23,-14,4),_vektor<_tg>(2,0,0),_vektor<_tg>(0,4,0),_vektor<_tg>(0,0,2),textur[4],textur[4],textur[4]);
                                                                m->subtraktiv(false);
                                                                m=erzeugenraum(w,_vektor<_tg>( (-28+66)-5-2,-14,4),_vektor<_tg>(2,0,0),_vektor<_tg>(0,4,0),_vektor<_tg>(0,0,2),textur[4],textur[4],textur[4]);
                                                                m->subtraktiv(false);
                                                                
                                                                
                                                                erzeugenraum(w,_vektor<_tg>(3,-14,3),_vektor<_tg>(4,0,0),_vektor<_tg>(0,-100,0),_vektor<_tg>(0,0,4),textur[9],textur[4],textur[9]);
                                                                erzeugenraum(w,_vektor<_tg>(-8,-114,-8),_vektor<_tg>(26,0,0),_vektor<_tg>(0,-30,0),_vektor<_tg>(0,0,26),textur[9],textur[4],textur[9]);

                                                                m=erzeugenraum(w,_vektor<_tg>(-7+ 2,3,-7+ -2),_vektor<_tg>(7,0,7),_vektor<_tg>(0,4,0),_vektor<_tg>(-4,0,4),textur[9],textur[4],textur[9]);
                                                                m=erzeugenraum(w,_vektor<_tg>((-7+ 2)+15,3,(-7+ -2)+15),_vektor<_tg>(7,0,7),_vektor<_tg>(0,4,0),_vektor<_tg>(-4,0,4),textur[9],textur[4],textur[9]);
                                                                //m->subtraktiv(false);
                                                                m=erzeugenraum(w,_vektor<_tg>(0,4,0),_vektor<_tg>(10,0,0),_vektor<_tg>(0,1,0),_vektor<_tg>(0,0,10),textur[9],textur[4],textur[4]);
                                                                m->subtraktiv(false);
                                                                //-------------------------------------------------------------
                                                                new _licht<>(w,_vektor<_tg>(5,9,5),_vektor<_to>(0.3,0,1),80);
                                                                new _licht<>(w,_vektor<_tg>(5,1,5),_vektor<_to>(1,0.45,0),80);
                                                                new _licht<>(w,_vektor<_tg>(-26,-5,5),_vektor<_to>(1,0,0),80);
                                                                new _licht<>(w,_vektor<_tg>(36,-5,5),_vektor<_to>(1,0.5,0),80);
                                                                new _licht<>(w,_vektor<_tg>(-26,-5,15),_vektor<_to>(1,0.4,0),80);
                                                                new _licht<>(w,_vektor<_tg>(36,-5,15),_vektor<_to>(1,0.6,0),80);
                                                                new _licht<>(w,_vektor<_tg>(0,-5,-7),_vektor<_to>(1,0.2,0),80);
                                                                new _licht<>(w,_vektor<_tg>(36,-5,-7),_vektor<_to>(1,0.7,0),80);
                                                                new _licht<>(w,_vektor<_tg>(-26,-11,5),_vektor<_to>(1,1,1),80);
                                                                new _licht<>(w,_vektor<_tg>(5,-11,5),_vektor<_to>(1,1,1),80);
                                                                new _licht<>(w,_vektor<_tg>(-26+62,-11,5),_vektor<_to>(1,1,1),80);
                                                                new _licht<>(w,_vektor<_tg>(5,-115,5),_vektor<_to>(0.3,0,1),180);

                                                                new _licht<>(w,_vektor<_tg>((4-12)+1,14,-7),_vektor<_to>(1,1,1),380);
                                                                new _licht<>(w,_vektor<_tg>((2+12)+1,14,15),_vektor<_to>(1,1,1),380);

                                                                //---------------------------------------- gravitation --------------------------------------
                                                                h.setzen(5,-126,5);
                                                                new _gravitation<>(w,h,10);
                                                                new _sprite(w,w,_vektor<_tg>(5,-126,5),_vektor<_tg>(5,0,0),_vektor<_tg>(0,0,5),textur[12]);
                                                                new _licht<>(w,_vektor<_tg>(5,-126,5),_vektor<_to>(1,0.6,0.08),50);
                                                                h.setzen(5,-12,5);
                                                                new _gravitation<>(w,h,10);
                                                                new _sprite(w,w,_vektor<_tg>(5,-12,5),_vektor<_tg>(5,0,0),_vektor<_tg>(0,0,5),textur[12]);
                                                                new _licht<>(w,_vektor<_tg>(5,-12,5),_vektor<_to>(1,0.6,0.08),50);
                                                                //-------------------------------------- figur,spieler -------------------------------------
                                                                _figurspieler*spieler;
                                                                h.setzen(1,1,1);
                                                                vx.setzen(1,0,0);
                                                                pqdeath=new _partikelquellesprite(w,w,h,vx,50,textur[13]);
                                                                pqdeath->einfuegentextur(textur[12]);
                                                                //pqdeath->einfuegentextur(textur[10]);
                                                                //pqdeath->einfuegentextur(textur[11]);
                                                                pqdeath->aktiv(false);
                                                                pqdeath->laenge(0.3);
                                                                pqdeath->generationsrate(15);
                                                                pqdeath->generationsratetoleranz(0.5);
                                                                pqdeath->laengetoleranz(0.5);
                                                                pqdeath->vektortoleranz(0.5);
                                                                pqdeath->rotation(60);
                                                                pqdeath->rotationtoleranz(1);
                                                                pqdeath->lebensdauerpartikeltoleranz(0.95);
                                                                pqlife=new _partikelquellesprite(w,w,h,vx,30,textur[12]);
                                                                pqlife->aktiv(false);
                                                                pqlife->laenge(0.04);
                                                                pqlife->laengetoleranz(0.5);
                                                                pqlife->vektortoleranz(0.5);
                                                                pqlife->lebensdauerpartikeltoleranz(0.5);
                                                                h.setzen(1,1,1);
                                                                spieler=new _figurspieler(w,w,h);
                                                                spieler->einfuegentexturdetonation(textur[12]);
                                                                spieler->partikelquelle()->einfuegentextur(textur[13]);
                                                                spieler->partikelquelle()->partikelquelledestruktion(pqdeath);                                                                
                                                                
                                                                //------------------------------------- partikelquellen ---------------------------------------
                                                                vx.setzen(0,0,0.4);
                                                                h.setzen(-6,-120,5);
                                                                pqs[0]=new _partikelquellesprite(w,w,h,vx,200,textur[13]);
                                                                pqs[0]->generationsrate(1);
                                                              //  pqs[0]->generationsratetoleranz(0.5);
                                                                pqs[0]->laenge(0.5);
                                                                pqs[0]->laengetoleranz(0.5);
                                                                pqs[0]->vektortoleranz(0.1);
                                                                pqs[0]->rotation(60);
                                                                pqs[0]->rotationtoleranz(1);
                                                                pqs[0]->lebensdauerpartikeltoleranz(0.95);
                                                               // pqs[0]->lokusraum(_vektor<_tg>(1,0,0),_vektor<_tg>(1,0,0),_vektor<_tg>(1,0,0));
                                                                
                                                                
                                                                //----------------------------------------- welt compiliern ---------------------------
                                                                rohmeshes=w->uebersetzen();
                                                                rohmeshes->loeschen();
                                                                delete rohmeshes;    
                                                                //--------------------------------------------------------------------------------------
                                                                
                                                                
                                                              //  w->anlegenlightmapzone("zonenlightmap",0.5);
                                                                cam->laenge(2);
                                                                cam->groesse(1.024,0.768);
                                                                cam->aktualisieren();
                                                                mo=new _win::_maus<>(399,399);
                                                                mo->relativ(true);
                                                                mo->verstecken();
                                                                
                                                                RECT r;
                                                                unsigned int wx,wy;
                                                                SystemParametersInfo(SPI_GETWORKAREA,0,&r,0);
                                                                wx=abs(r.right-r.left);
                                                                wy=abs(r.top-r.bottom)+32;
                                                                gra= new _win::_grafikopengl<>(0,0,wx,wy);
                                                                gra->texturen(&tl);
                                                                gra->aktivitaet(true);
                                                                gra->nebelmodus(1);
                                                                gra->nebelfarbe(0.5f,0.5f,0.5f);
                                                                gra->nebeldichte(0.008f);
                                                                gra->nebeldistanz(1,40);
                                                                gra->nebel(false); 
                                                                glHint(GL_FOG_HINT, GL_DONT_CARE);  
                                                                
                                                                //----------------------------------------- welt compiliern ---------------------------
                                                                B=new _bestrahler();
                                                                B->lichtambient(_vektor<float>(0.2f,0.2f,0.2f));
                                                                B->bestrahlenlightmapzone(w);
                                                                //w->bestrahlenlightmap();
                                                                w->uebergebenlightmap(gra);
                                                                delete B;
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                while(kb.escape()) S->animieren();
                                                                raus=false;
                                                                w->eigenetransformation(false);
                                                                w->anfang(zone);
                                                                w->anfang(m);
                                                                m->markierungpolygon(1);
                                                                
                                                                
                                                                
                                                                 //------------------------------------------------------------------------------------------
                                                                 spieler->ort()=*cam;
                                                                 sektor=zone->sektor(*cam);
                                                                 spieler->aktualisierensektor(zone);
                                                                 zone->initialisierenzeitfaktor(&timer);
                                                                 if(zone->anfang(sit))do{
                                                                  sit->unvisualisieren();
                                                                 }while(zone->naechstes(sit));
                                                                 _partition::_sektor*pqsektor=zone->sektor(pqs[0]->ort());
                                                                 do{
                                                                  gra->loeschenseite();
                                                                  sektor=spieler->sektoraktuell();
                                                                  if(sektor){
                                                                   //------------------------------ auf 1.grafik zeichnen ------------------------
                                                                   w->transformierensektor(gra,spieler->kamera(),sektor);
                                                                   w->zeichnensektor(gra,spieler->kamera(),sektor); 
                                                                   w->zeichnensprite(gra,spieler->kamera());
                                                                  };
                                                                  zone->berechnenzeitfaktor(&timer);
                                                                  pqs[0]->aktiv(false);
                                                                  if(spieler->sektoraktuell()==pqsektor){
                                                                   
                                                                   if(((w->zyklus()/40)%2)==0) pqs[0]->aktiv(true);
                                                                  };
                                                                  w->animieren();
                                                                  w->animierenpartikelquelle(zone);
                                                                  w->animierensprite();
                                                                  w->animierenfigur(zone,&kb,mo);
                                                                  //------------------------------- tastaturbefehle ------------------------------
                                                                  if(kb.taste(83)){
                                                                   while(kb.taste(83));
                                                                   if(svis==0){
                                                                    if(zone->anfang(sit))do{
                                                                     sit->unvisualisieren();
                                                                    }while(zone->naechstes(sit));
                                                                   }else{
                                                                    if(zone->anfang(sit))do{
                                                                     sit->visualisieren();
                                                                    }while(zone->naechstes(sit));
                                                                   };
                                                                   svis=1-svis;
                                                                  };
                                                                
                                                                 //cam->bewegen(&kb,mo,1); 
                                                                 //w->transformieren(gra,cam,true);
                                                                 //w->zeichnen(gra); 
                                                                 gra->umschaltenseite();                                                                 

                                                                 S->animieren();
                                                                 if(kb.escape()) raus=true;
                                                                }while(raus==false);
                                                                delete gra;
                                                                delete mo;
                                                                szenedestruktion(w);
                                                                w=0;
};
//******************************************************************************************************************************************************************************************************
//                                                              H A U P T F U N K T I O N 
//******************************************************************************************************************************************************************************************************
/*class _sek;
class _kug;


class _sek:public _liste<_kug>{
        public:
            _sek(){};
            void verbinden(_kug*);
};
class _kug:public _liste<_sek>{
        public:
            _kug(){};
            void verbinden(_sek*);
};

void _kug::verbinden(_sek*s){
             new _verbinder<_sek,_kug>(this,s,s,this);
};

void _sek::verbinden(_kug*k){
             new _verbinder<_sek,_kug>(k,this,this,k);
};
*/

int WINAPI WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int){
                                                                _zeichenkette<char> s="logbuch.txt";
                                                                _testwelt*tw;
                                                                //-------------------------
                                                                L=new _logbuch(s);
                                                                tw=new _testwelt(hi);
                                                                /*
                                                                _sek*ss=new _sek();
                                                                _kug*kk=new _kug();
                                                                
                                                                ss->verbinden(kk);
                                                                L->schreiben("kugel : ",(int)kk->anzahl());
                                                                L->schreiben("sektor : ",(int)ss->anzahl());
                                                                ss->aushaengen();
                                                                
                                                                L->schreiben("kugel : ",(int)kk->anzahl());
                                                                L->schreiben("sektor : ",(int)ss->anzahl());
                                                                */
                                                                
                                                                //tw->testladen();
                                                                //tw->testspeichern();
                                                                //tw->testbestrahlung();
                                                                //tw->testbaumoctal();
                                                                tw->testkugel();
                                                                //tw->testsichtbarkeit();
                                                                delete tw;
                                                                delete L;
                                                                return(0);
};
