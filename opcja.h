//basic class opcja//

#ifndef LATTICE_H
#define LATTICE_H
#include "lattice.h"
#endif

#ifndef PLASTER_H
#define PLASTER_H
#include "plaster.h"
#endif

#ifndef SET_H
#define SET_H
#include <set>
#endif


class opcja
{
private:
vector < vector <double> > equi_curve;	//przechowuje wczytane zaleznosc Cv 
vector <plaster> BLOKS;		//zawiera plasterki obszaru rownowarzenia
vector <plaster> HIST;		//zawiera plasterki calej probki do monitorowania
vector <plaster> reservuars; //0-lewa/1-prawa strona
vector <vector <double> > reservuars_par;	//zawiera parametry inicjowania dla rezerwuarow z conf.dat ->init_reservuars

set <site* > Vtoadd;		//zawiera adresy wakancju dodane do symulacji podczas do_equi()

double TEMPERATURE, OPCJA_NORM;
int EQ_STEP, TRYB;			//TRYB ==2 : path;	TRYB == 1 : swap;	TRYB == 0 : converse; set in opcja::init()

double BIN_ST,BIN_END,BIN_SIZE;		//describe plasterki
int BIN_ATOMS_TYP,BIN_DIRECTION;

long DIRECT_STEPS;
vector<long int> ROZMIAR;
int REZ_TO_MOVE, TYP_TO_MOVE,NEW_PLANE;
bool MOVE_FRAME,SINGLE,EQ_BUILDED;													//true if frame was changed during do_equi()
wektor del_L_sim, del_R_sim;											//przesuniecie obszaru symulacji -> korzystam w lattice::reinit_sim_area()

lattice *SAMPLE;		
potential &POT;
vector < vector <double> > &BARRIERS;
set <site*> &VAC_LIST;

string SAVE_file;
bool SAVE_AVG, SAVE_BUILDED;
int SAVE_step;
long SAVE_MCstep, SAVE_count;
double SAVE_MCtime;						
double Actual_MCtime;													//aktualny czas z RTA. Nie podleaga zerowaniu. Zapis ciagly. 

double ST_VOL;															//obszar od rezerwuaru do rezervuaru - volume.
double END_VOL;

	
public:

opcja(potential& pot_in, vector < vector <double> > &bar, set <site*> &vatoms) : POT(pot_in), BARRIERS(bar), VAC_LIST(vatoms){
	
	TRYB=0;
	EQ_STEP=0;
	EQ_BUILDED=false;	
	BIN_END=0;
	BIN_SIZE=0;
	BIN_DIRECTION=0;
	BIN_ATOMS_TYP=0;
	SAVE_file = "0_";
	SAVE_step = 0;
	SAVE_count = 0;
	SAVE_MCstep = 0;
	SAVE_MCtime = 0.0;
	Actual_MCtime=0.0;
	SAVE_AVG = false;
	SAVE_BUILDED = false;
	MOVE_FRAME = false;
	NEW_PLANE = false;
	SINGLE = false;
	BIN_ATOMS_TYP=0;
	DIRECT_STEPS=0;
	ST_VOL=0;
	END_VOL=0;
	OPCJA_NORM=0.0005;

	equi_curve.reserve(2000);
	BLOKS.reserve(5000);
	HIST.reserve(5000);
	reservuars.reserve(20);
	reservuars_par.reserve(20);


	};

~opcja(){
	};

void build_bins(vector<plaster>& layer_new, string name);
void init_EQ(vector <double> &parameters);
void init_reservuar(vector <double> &parameters);
void set_opcja_lattice(lattice *sample);
void init_settings(vector <double> &parameters);

void execute(string name, vector<double>&parameters);
void show();
void reset_site(site *node);
void read_file(string filename);
void call_flux(site* atom_to_jump,site* vac_to_jump);	
void call_flux_dislocation(site* atom_to_jump,site* vac_to_jump);	
double call_total_flux(double range, unsigned int nr_bin);
double Ceq_vac(double stech);
int choose_reservuar(site* atom);
int check_stech(double stech, double vac, double size);
bool check_rez_dN();
bool check_rezervuars(int i, int typ);
bool check_rezervuars(site* node, site* &next_node);
bool check_x_belonging_volume(double x);
void do_equi_vac();
void do_equi_rez();
void equilibrate();
double errCeq_vac(double stech);
void flux_net_add(double pos_V, double pos_A, int typV, int typA, vector<plaster>& layer_new);
void flux_add(site* V, site* A,vector<plaster>& layer_new);
void flux_add_dislocation(site* V, site* A, vector<plaster>& layer_new);
bool get_save_flag(){return SAVE_AVG;};
int get_steps(){return EQ_STEP;};
int get_direction(){return BIN_DIRECTION;};
int get_start_volume(){return ST_VOL;};
int get_end_volume(){return END_VOL;};
void move_frame();
void reinit_reservuars(int nr, int typ);
void reinit_bloks();
void refresh(int on = 0);
void refresh_simarea();
void refresh_vac_list();
	
void swap(plaster &source, plaster &destination, int FLAG);

void init_save(double iod,double ido,double istep, double direction);
bool save_stauts(){return SAVE_BUILDED;};
void save_hist(double MCtime, double MCstep, string fileout);
void save_call();
void save_write();
void add_MCtime(double dt){Actual_MCtime += dt;};
void set_temperature(double T){TEMPERATURE=T;}

void identify_phases();
void identify_matano();
double matano_localize(vector <plaster>::iterator bin);

void find_interface();
void source_sink_act(int i, int vac, bool &FLAG);	
site* source_sink_localize(int in_bin, bool create, int &for_rez, long int &nr_site, int &dir);	
site* get_node( int in_bin, bool create, int for_rez,long int &nr_site);
bool find_migration_path(site *node,int DIR, vector <site*> &migration_path);	
void dislocation_walk(vector <site*> &migration_path);
void cal_angles(site *node, wektor &main, vector <site*> &wynik_at, vector <site*> &wynik_vac);
void cal_angles_strong(site *node, wektor &main, vector <site*> &wynik_at, vector <site*> &wynik_vac);
void virtual_jump_vac_atom( site* VAC, site* B);
void update_opcja( site* node, bool status );
};
