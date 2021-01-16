#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <ctime>
#include <list>
#include <regex>
#include <iomanip>
#include <fstream>
#include <sstream> 
using namespace std;
using std::vector;

class Arhiva
{public:
	virtual bool arhivare() = 0;
	virtual bool dezarhivare(int i) = 0;
};

class Afisare
{
public:
	virtual string name() = 0;
};


//clasa pentru gestionarea datei
class Data {
private:
	time_t timer;
public:
	//constructor implicit
	Data() : timer(time(0))
	{
	}
	//constructor cu parametrul timer
	Data(time_t t) : timer(t)
	{
	}
	//constructor cu parametrul referinta la time_t 
	Data(const time_t* t) : timer(*t)
	{
	}
	//constructor cu parametru string in format dd.mm.yyyy
	Data(string d)
	{

		timer = time(0);//initializez timer cu data curenta
		stringstream s;
		s << d;//preiau string in stringstream
		char dummy;
		unsigned int dd, mm, yyyy;
		s >> dd >> dummy >> mm >> dummy >> yyyy; //preiau componentele datei in variabile int
		struct tm* data_temp = new struct tm; //construiesc struct tm pentru pragatirea datei
		localtime_s(data_temp, &timer);
		data_temp->tm_mday = dd;
		data_temp->tm_mon = mm - 1;
		data_temp->tm_year = yyyy - 1900;
		data_temp->tm_hour = 0;
		timer = mktime(data_temp); //transform struct tm in time_t
		delete data_temp;//eliberez memoria de variabila temporara

	}

	//constructor cu parametru string in format dd.mm.yyyy + int ora
	Data(string d, int h) :Data(d)
	{
		timer += (3600 * h);
	}

	//time setter
	void setTime(time_t t)
	{
		timer = t;
	}

	//time setter
	void setTime_string(string s) // valoarea parametrului este un time_t,in format string
	{
		stringstream a;
		time_t b;
		a << s;
		a >> b;
		timer = b;
	}


	//seteaza data din string in format dd.mm.yyyy + int ora
	void setDataSiOra(string d, int h)
	{
		timer = time(0);//initializez timer cu data curenta
		stringstream s;
		s << d;//preiau string in stringstream
		char dummy;
		unsigned int dd, mm, yyyy;
		s >> dd >> dummy >> mm >> dummy >> yyyy; //preiau componentele datei in variabile int
		struct tm* data_temp = new struct tm; //construiesc struct tm pentru pragatirea datei
		localtime_s(data_temp, &timer);
		data_temp->tm_mday = dd;
		data_temp->tm_mon = mm - 1;
		data_temp->tm_year = yyyy - 1900;
		data_temp->tm_hour = 0;
		timer = mktime(data_temp); //transform struct tm in time_t
		delete data_temp;//eliberez memoria de variabila temporara
		timer += (3600 * h);
	}

	//adauga ore la data curenta
	void adaugaOra(int h)
	{
		timer += (3600 * h);
	}
	//aduna zile la data curenta
	void adaugaZile(int z)
	{
		timer += 86400 * z;
	}

	//aduna o zi la data curenta
	bool operator ++()
	{
		timer += 86400;
		return true;
	}


	//returneaza data in format time_t
	time_t returnTimeT()
	{
		return timer;
	}

	// returneaza data in format dd.mm.yyyy
	string returData()
	{
		struct tm* data_temp = new struct tm;
		localtime_s(data_temp, &timer);
		unsigned int dd, mm, yyyy, h;
		dd = data_temp->tm_mday;
		mm = data_temp->tm_mon + 1;
		yyyy = data_temp->tm_year + 1900;
		h = data_temp->tm_hour;
		stringstream d;
		d << dd << "." << mm << "." << yyyy;
		string rd;
		d >> rd;
		delete data_temp;//eliberez memoria de variabila temporara
		return rd;
	}

	// returneaza ora int
	int returOra()
	{
		struct tm* data_temp = new struct tm;
		localtime_s(data_temp, &timer);
		unsigned int h;
		h = data_temp->tm_hour;
		stringstream d;
		d << h;
		int rd;
		d >> rd;
		delete data_temp;//eliberez memoria de variabila temporara
		return rd;
	}

	//destructor
	~Data() {}

	friend istream& operator >> (istream&, Data&);
};

//supraincarcare operator citire
istream& operator >> (istream& i, Data& d)
{
	char dummy;
	unsigned int dd, mm, yyyy;
	i >> dd >> dummy >> mm >> dummy >> yyyy; //preiau componentele datei in variabile int
	struct tm* data_temp = new struct tm; //construiesc struct tm pentru pragatirea datei
	localtime_s(data_temp, &d.timer);
	data_temp->tm_mday = dd;
	data_temp->tm_mon = mm - 1;
	data_temp->tm_year = yyyy - 1900;
	data_temp->tm_hour = 0;
	d.timer = mktime(data_temp); //transform struct tm in time_t
	delete data_temp;//eliberez memoria de variabila temporara
	return i;
}


//functie template pentru cautarea unui element in lista
template <typename T>
bool contains(list<T>& listaCautare, const T& elementCautat)
{
	// gaseste elementul in lista
	auto it = find(listaCautare.begin(), listaCautare.end(), elementCautat);
	//daca returneaza sfarsitul listei, elementul nu se gaseste in lista
	return it != listaCautare.end();
}

//functie pentru verificarea formatului adresei demail
bool emailFormat(string email)
{
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(email, pattern);
}

//clasa Film
class Film : public Afisare
{
private:
	const int codFilm;
	string numeFilm;
	string producator;
	int durata;
	string subtitrare; //dublat, subtitrat, original
	int tehnologie2d;
	int tehnologie3d;
	static int ultCod;
public:
	//constructorul implicit
	Film() :codFilm(Film::ultCod + 1), numeFilm("Necunoscut"), producator("Necunoscut"), durata(0), subtitrare(""), tehnologie2d(0), tehnologie3d(0)
	{
		Film::ultCod = this->codFilm;
		//cout << "apelez constructorul implicit clasa Film" << endl;
	};
	//constructorul cu parametri
	Film(string n, string p, int d, string s, int d2, int d3) :codFilm(Film::ultCod + 1), numeFilm(n), producator(p), durata(d), subtitrare(s), tehnologie2d(d2), tehnologie3d(d3)
	{
		Film::ultCod = this->codFilm;
		//cout << "apelez constructorul cu parametri clasa Film" << endl;
	};
	//constructor de copiere
	Film(const Film& f) :codFilm(Film::ultCod + 1)
	{
		Film::ultCod = this->codFilm;
		this->numeFilm = f.numeFilm;
		this->producator = f.producator;
		this->durata = f.durata;
		this->subtitrare = f.subtitrare;
		this->tehnologie2d = f.tehnologie2d;
		this->tehnologie3d = f.tehnologie3d;
		//cout << "apelez constructorul de copiere clasa Film" << endl;
	}
	//operator egal
	Film& operator = (const Film& f)
	{
		//pastrez codul filmului existent, copii restul campurilor
		numeFilm = f.numeFilm;
		producator = f.producator;
		durata = f.durata;
		subtitrare = f.subtitrare;
		this->tehnologie2d = f.tehnologie2d;
		this->tehnologie3d = f.tehnologie3d;
		//cout << "apelez operatorul egal clasa Film" << endl;
		return *this;
	}
	~Film()
	{
	}

	//cast la string - returneaza numele filmului
	operator string() const
	{
		return numeFilm;
	}

	//cast la int - returneaza durata filmului
	operator int() const
	{
		return durata;
	}


	//cast la bool - returneaza true pentru filme 3d, false pentru 2d
	operator bool() const
	{
		if (tehnologie3d == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	//citesc tehnologie 3d
	bool returnTehnologie3d()
	{
		if (tehnologie3d == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	//returneaza durata filmului
	int returnDurata()
	{
		return durata;
	}

	//functie de afisare - pentru <<
	void afisare()
	{
		cout << "Numele filmului: " << numeFilm << endl;
		cout << "Producator: " << producator << endl;
		cout << "Durata: " << durata << endl;
		cout << "Subtitrare: " << subtitrare << endl;
		cout << "Vizionare 2d: ";
		if (tehnologie2d == 1)
		{
			cout << "Da" << endl;;
		}
		else
		{
			cout << "Nu" << endl;
		}
		cout << "Vizionare 3d: ";
		if (tehnologie3d == 1)
		{
			cout << "Da" << endl;
		}
		else
		{
			cout << "Nu" << endl;
		}

	}


	//functie de citire - pentru >>
	//format stream pentru apelarea automata: "numeFilm\nproducator\ndurata\nsubtitrare\n2d\n3d\n"
	istream& citire(istream& in)
	{
		cout << endl << "Numele filmului: ";
		getline(in, this->numeFilm);
		cout << "Producator film: ";
		getline(in, this->producator);
		while (!(durata > 0))
		{
			cout << "Durata filmului in minute: ";
			if (!(in >> durata))
			{
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		int s = 0;
		while (s <= 0 || s > 3)
		{
			cout << "Selectati optiunea de subtitrare: 1 = dublat, 2 = subtittat, 3 = original: ";
			if (!(in >> s))
			{
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		switch (s)
		{
		case 1:  this->subtitrare = "dublat";
			break;
		case 2:  this->subtitrare = "subtitrat";
			break;
		case 3:  this->subtitrare = "original";
			break;
		default: this->subtitrare = "original";
		}

		char t = ' ';
		while (toupper(t) != 'Y' && toupper(t) != 'N')
		{
			cout << "Filmul poate fi vizionat pe tehnologie 2D (Y / N)? ";
			if (!(in >> t))
			{
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		if (toupper(t) == 'Y')
		{
			this->tehnologie2d = 1;
		}
		else
		{
			this->tehnologie2d = 0;
		}
		t = ' ';//resetez variabila pentru a o refolosi in 3d

		while (toupper(t) != 'Y' && toupper(t) != 'N')
		{
			cout << "Filmul poate fi vizionat pe tehnologie 3D (Y / N)? ";
			if (!(in >> t))
			{
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		if (toupper(t) == 'Y')
		{
			this->tehnologie3d = 1;
		}
		else
		{
			this->tehnologie3d = 0;
		}

		return in;
	}

	//supraincarcare operator == returneaza true daca numele, producatorul, durata, subtitrarea, 3d si 2d  a celor 2 filme sunt egale
	bool operator== (const Film& f)
	{
		if (this->numeFilm == f.numeFilm &&
			this->producator == f.producator &&
			this->durata == f.durata &&
			this->subtitrare == f.subtitrare &&
			this->tehnologie2d == f.tehnologie2d &&
			this->tehnologie3d == f.tehnologie3d)
		{
			return true;
		}
		else { return false; }
	}

	//definire functie nume(), din clasa virtuala
	string name()
	{
		return this->numeFilm;
	}

};
//initializare membru static
int Film::ultCod = 0;
//supraincarcare pentru operator citire
istream& operator>> (istream& i, Film& f)
{
	//apelez functia de citire din clasa de baza
	f.citire(i);
	return i;
};

//supraincarcare pentru operator scriere
ostream& operator<<(ostream& o, Film& f)
{
	//apelez functia de scriere din clasa de baza
	f.afisare();
	return o;
};

//clasa SalaSpectacol
class SalaSpectacol: public Afisare
{
private:
	string numeSala;
	int randuriSala;
	int scaunePeRand;
	string tehnologieVizionare;//accept o singura valoare (2d, 3d), pe care o voi compara cu una din valorile obiectului Film
public:
	//constructor implicit
	SalaSpectacol() :numeSala(""), randuriSala(0), scaunePeRand(0), tehnologieVizionare("")
	{
		//	cout << "apelez constructorul implicit clasa SalaSpectacol" << endl;

	}
	//constructor cu parametri
	SalaSpectacol(string numeSala, int randuriSala, int scaunePeRand, string TehnologieVizionare)
		:numeSala(numeSala), randuriSala(randuriSala), scaunePeRand(scaunePeRand), tehnologieVizionare(TehnologieVizionare)
	{
		//	cout << "apelez constructorul cu parametri clasa SalaSpectacol" << endl;
	}
	//constructor de copiere
	SalaSpectacol(const SalaSpectacol& s) :numeSala(s.numeSala), randuriSala(s.randuriSala), scaunePeRand(s.scaunePeRand), tehnologieVizionare(s.tehnologieVizionare)
	{
		//	cout << "apelez constructorul de copiere clasa SalaSpectacol" << endl;
	}
	//operator egal
	SalaSpectacol& operator=(const SalaSpectacol& s)
	{
		numeSala = s.numeSala;
		randuriSala = s.randuriSala;
		scaunePeRand = s.scaunePeRand;
		tehnologieVizionare = s.tehnologieVizionare;
		//	cout << "apelez operatorul egal clasa SalaSpectacol" << endl;
		return *this;
	}

	//destructor
	~SalaSpectacol() {}

	//supraincarcare operator <= returneaza true daca numarul de locuri din sala curenta este mai mic sau egal decat cel din sala de comparatie
	bool operator<=(const SalaSpectacol& s)
	{
		int a = this->randuriSala * this->scaunePeRand;
		int b = s.randuriSala * s.scaunePeRand;
		return a <= b ? true : false;
	}

	//return randuri sala
	int returnRanduriSala() {
		return this->randuriSala;
	}
	//return numar scaune pe rand
	int returnScaunePeRand() {
		return this->scaunePeRand;
	}
	//return tehnologie
	string returnTehnologie()
	{
		return tehnologieVizionare;
	}

	//definire functie nume(), mostenita din clasa virtuala
	string name()
	{
		return this->numeSala;
	}

	
	//cast catre string - returneaza numele salii
	operator string()
	{
		return numeSala;
	}
	//cast catre bool - returneaza true daca sala accepta 3d si false daca nu accepta 3d
	operator bool()
	{
		if (tehnologieVizionare == "3D")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//functie de citire - pentru >>
	//format string input: "numeSala \n randuriSala \n scaunePeRand \accepta3D"
	istream& citire(istream& in)
	{
		cin.clear();
		//cin.ignore(10000, '\n');
		cout << endl << "Nume Sala: ";
		getline(in, this->numeSala);
		while (!(randuriSala > 0))
		{
			cout << "Numar randuri: ";
			if (!(in >> randuriSala))
			{
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}

		while (!(scaunePeRand > 0))
		{
			cout << "Numar scaune pe rand: ";
			if (!(in >> scaunePeRand))
			{
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}

		char t = ' ';
		while (toupper(t) != 'Y' && toupper(t) != 'N')
		{
			cout << "Sala accepta spectacole 3d? (Y / N)";
			if (!(in >> t))
			{
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		if (toupper(t) == 'Y')
		{
			tehnologieVizionare = "3D";
		}
		else
		{
			tehnologieVizionare = "2D";
		}
		return in;
	}


};

//supraincarcare pentru operator citire
istream& operator>> (istream& i, SalaSpectacol& s)
{
	//apelez functia de citire din clasa de baza
	s.citire(i);
	return i;
};

//supraincarcare pentru operator scriere
ostream& operator<<(ostream& o, SalaSpectacol& s)
{

	cout << "Numele salii: " << s.name() << endl;
	cout << "Randuri in sala: " << s.returnRanduriSala() << endl;
	cout << "Scaune pe rand: " << s.returnScaunePeRand() << endl;
	cout << "Tehnologie vizionare: " << s.returnTehnologie() << endl;
	return o;
};


// clasa pentru gestionarea programului de vizionare 
// o vizionare preprezinta o programare a unui film pe o sala, la o data si ora, cu un pret stabilit
// obiectul va gestiona statusul ocuparii salii in functie de emiterea biletelor
class VizionareFilm
{
private:
	const int codVizionare;
	string status; //deschis, inchis, vandut, anulat
	time_t dataVizionare;
	Film* film;
	SalaSpectacol* sala;
	float pretBilet;
	int** ocupareSala;//in functie de sala selectata, dimensiunea va fi egala cu numarul de randuri si scaune pe rand din sala respectiva
						  //valoare implicita pentru constructorul cu parametri va fi 0; la emiterea unui bilet va fi completata cu id-ul biletului	

	//constructor implicit
public:
	VizionareFilm() :codVizionare(0), status("inchis"), dataVizionare(time(0)), film(NULL), sala(NULL), pretBilet(0), ocupareSala(NULL)
	{
		//	cout << "apelez constructorul implicit clasa VizionareFilm" << endl;

	}
	//constructor cu parametri
	VizionareFilm(int c, time_t d, Film* f, SalaSpectacol* s, float p) :codVizionare(c), status("inchis"), dataVizionare(d), film(f), sala(s), pretBilet(p)
	{
		if (s)
		{
			int a = s->returnRanduriSala();
			int b = s->returnScaunePeRand();
			ocupareSala = new int* [a];
			for (int i = 0; i < a; i++)
			{
				ocupareSala[i] = new int[b];
				for (int j = 0; j < b; j++)
				{
					ocupareSala[i][j] = 0;
				}
			}
		}
		else
		{
			ocupareSala = NULL;
		}
		//cout << "apelez constructorul cu parametri clasa VizionareFilm" << endl;

	}


	//constructor de copiere
	VizionareFilm(const VizionareFilm& v) :codVizionare(v.codVizionare), status(v.status), dataVizionare(v.dataVizionare), film(v.film), sala(v.sala), pretBilet(v.pretBilet)
	{
		if (v.sala)
		{
			int a = v.sala->returnRanduriSala();
			int b = v.sala->returnScaunePeRand();
			ocupareSala = new int* [a];
			for (int i = 0; i < a; i++)
			{
				ocupareSala[i] = new int[b];
				for (int j = 0; j < b; j++)
				{
					ocupareSala[i][j] = 0;
				}
			}
		}
		else { ocupareSala = NULL; }
		//cout << "apelez constructorul de copiere clasa VizionareFilm" << endl;
	}



	//operator egal
	VizionareFilm& operator=(const VizionareFilm& v)
	{
		this->dataVizionare = v.dataVizionare;
		this->pretBilet = v.pretBilet;
		this->sala = v.sala;
		this->film = v.film;

		//sterg array daca exista
		if (ocupareSala)
		{
			delete[] ocupareSala;
		}
		//populez array in functie de numarul de randuri si scaune din parametru
		if (v.sala)
		{
			int a = v.sala->returnRanduriSala();
			int b = v.sala->returnScaunePeRand();
			ocupareSala = new int* [a];
			for (int i = 0; i < a; i++)
			{
				ocupareSala[i] = new int[b];
				for (int j = 0; j < b; j++)
				{
					ocupareSala[i][j] = v.ocupareSala[i][j];
				}
			}
		}
		else { ocupareSala = NULL; }
		//cout << "apelez operatorul egal clasa VizionareFilm" << endl;
		return *this;

	}

	//return status ocupare
	int returnOcupare(int rand, int scaun)
	{
		if (ocupareSala)
		{
			return ocupareSala[rand - 1][scaun - 1];
		}
	}

	//set status ocupare
	void setStatusOcupare(int rand, int scaun, int idBilet)
	{
		if (rand > 0 && rand <= this->sala->returnRanduriSala() //validez corectitudinea parametrilor
			&& scaun > 0 && scaun <= this->sala->returnRanduriSala()
			&& idBilet > 0)
		{
			ocupareSala[rand - 1][scaun - 1] = idBilet;
		}
		else
		{
			cout << "parametri eronati pentru status ocupare" << endl;
		}

	}

	//supraincarcare pentru operator () 
	//poate inlocui functia returnStatusOcupare, poate fi utilizata atat pentru citire cat si pentru scriere 
	int& operator()(int rand, int scaun)
	{
		if (ocupareSala && rand > 0 && rand <= this->sala->returnRanduriSala() //validez corectitudinea parametrilor
			&& scaun > 0 && scaun <= this->sala->returnScaunePeRand())
		{
			return ocupareSala[rand - 1][scaun - 1];//numerele randurilor/scaunelor incep de la 1, numerotarea vectorului de la 0
		}
		else
		{
			//cout << "Parametri eronati pentru numar rand sau numar scaun" << endl;
			throw exception("Parametri eronati pentru numar rand sau numar scaun");
		}
	}

	////cast la int - returneaza id-ul filmului
	//operator int() const
	//{
	//	return this->codVizionare;
	//}

	//supraincarcare pentru operator += seteaza statusul locurilor din sala, de pe vizionarea curenta, la 0
	//daca parametrul nu este egal cu 0, returneaza eroare
	bool operator+=(int m)
	{
		if (m == 0 && this->sala)
		{
			int a = sala->returnRanduriSala();
			int b = sala->returnScaunePeRand();

			if (!ocupareSala) //creez array daca nu exista
			{
				ocupareSala = new int* [a];
				for (int i = 0; i < a; i++)
				{
					ocupareSala[i] = new int[b];
				}
			}

			for (int i = 0; i < a; i++) //populez cu 0
			{
				for (int j = 0; j < b; j++)
				{
					ocupareSala[i][j] = 0;
				}
			}
			return true;
		}
		else
		{
			cout << "parametri eronati pentru \"operator=\" Introduceti 0 pentru marcarea locurilor din sala ca locuri libere" << endl;
			return false;
		}
	}

	//supraincarcare pentru operator ==  returneaza true daca filmul vizionarii este acelasi cu filmul de comparatie
	bool operator==(const Film& f)
	{
		if (*this->returnFilm() == f)
		{
			return true;
		}
		else { return false; }
	}
	//supraincarcare pentru operator + seteaza pretul pentru vizionarea programata la p
	void operator+(float p)
	{
		this->pretBilet = p;
	}


	//return pret
	float returnPret()
	{
		return pretBilet;
	}

	//return film
	Film* returnFilm()
	{
		if (film)
		{
			return film;
		}
		else
		{
			cout << "filmul nu a fost setat" << endl;
			return nullptr;
		}
	}
	//return sala
	SalaSpectacol* returnSala()
	{
		if (sala)
		{
			return sala;
		}
		else
		{
			cout << "sala nu a fost setata" << endl;
			return nullptr;
		}
	}


	//return data programarii vizionarii
	time_t returnDataVizionare()
	{
		Data d(dataVizionare);
		cout << d.returData() << ", ora: " << d.returOra();
		return dataVizionare;

	}
	//seteaza data vizionare
	//permite setarea datei de vizionare
	void setDataVizionare(time_t dataVizionare)
	{
		this->dataVizionare = dataVizionare;
		returnDataVizionare();
	}

	//seteaza sala si film
	void setSalaSiFilm(SalaSpectacol* s, Film* f)
	{
		if (s && f)//verific parametrii
		{
			this->sala = s;
			this->film = f;
		}
	}

	//return status 
	string returnStatus()
	{
		return status;
	}
	//seteaza status
	void setStatus(string status)
	{
		list<string>valoriAcceptate = { "deschis", "inchis", "vandut", "anulat" };
		bool verificare = contains(valoriAcceptate, status); //utilizez functie template contains 
		if (verificare)
		{
			this->status = status;
			cout << "Statusul salii este: " << returnStatus() << endl;
		}
		else
		{
			cout << "Status sala eronat" << endl;
		}

	}
	~VizionareFilm()
	{
		if (sala)
		{
			delete sala;
		}
		if (film)
		{
			delete film;
		}
		if (ocupareSala)
		{
			delete[] ocupareSala;
		}
	}

};



//supraincarcare pentru operator citire
//permite preluarea de la tastatura a datei si orei spectacolului, pentru o vizionare care are deja Film si sala
istream& operator>> (istream& i, VizionareFilm& v)
{
	if (v.returnFilm() && v.returnSala())
	{
		cin.clear();
		cin.ignore(10000, '\n');

		//preluarea datei de vizionare folosind clasa Data
		Data d(time(0)); //initializez data cu data curenta
		while (!(d.returnTimeT() > time(0)))//data vizionare trebuie setata la o data in viitor
		{
			cout << "Introduceti data vizionarii in format dd.mm.yyyy. Data trebuie sa fie mai mare decat data curenta: ";
			string s = "";
			cin >> s;
			unsigned int h = 0; //variabila pentru stocarea orei
			while (!(h == 10 || h == 15 || h == 20))
			{
				cout << "Ore acceptate 10, 15, 20. Introduceti ora vizionarii:";
				cin >> h;
			}
			d.setDataSiOra(s, h); //actualizez data in obiectul d
		}
		v.setDataVizionare(d.returnTimeT());//apelez functia de setare a datei din clasa

	}
	else
	{
		cout << "film si sala invalide pentru vizionarea selectata. Nu puteti seta data vizionarii" << endl;
	}
	return i;

};

//supraincarcare pentru operator scriere
ostream& operator << (ostream& o, VizionareFilm& v)
{
	// returnez datele programarii (film, sala, data, ora, pret bilet, status, ocuparea salii)
	if (v.returnFilm() && v.returnSala())
	{
		cout << *v.returnFilm() << endl;
		cout << *v.returnSala() << endl;
	}
	v.returnDataVizionare();
	cout << endl;
	cout << "Pretul biletului este: " << v.returnPret() << endl;
	cout << "Aceasta vizionare are status: " << v.returnStatus() << endl;

	if (v.returnSala())
	{
		//afisez statusul de ocupare
		//pentru locurile libere = afisez 0, pentru locurile ocupare = afisez x
		cout << "Status ocupare sala:" << endl;
		int r = v.returnSala()->returnRanduriSala(); //citesc numarul de randuri din sala
		int s = v.returnSala()->returnScaunePeRand(); //citesc numarul de scaune pe rand

		cout << "    ";
		for (int i = 1; i <= s; i++) //afisez o linie cu numarul scaunului (header coloane)
		{
			i < 10 ? cout << i << "  " : cout << i << " ";//coloanele pana la 10 decalate pentru afisarea corecta a matricii
		}
		//parcurg randurile si scaunele si preiau statusul
		for (int i = 1; i <= r; i++)
		{
			//afisez numarul randului (header randuri)
			i < 10 ? cout << endl << i << "  " : cout << endl << i << " "; //randurile pana la 10 decalate pentru afisarea corecta a matricii
			for (int j = 1; j <= s; j++)
			{
				v.returnOcupare(i, j) > 0 ? cout << " x " : cout << " 0 ";
			}
		}
		cout << endl;
		//cout << "Sfarsit afisare status ocupare" << endl;
	}
	else
	{
		cout << "Nu pot afisa status ocupare deoarece vizionarea nu are alocata o sala" << endl;
	}

	return o;
}



class Spectator:public Afisare
{
private:
	char* nume;
	string telefon;
	string email;
public:
	//construcotr implicit
	Spectator() : telefon(""), email("")
	{
		nume = nullptr;
		//cout << "am apelat consructorul implicit clasa Spectator" << endl;
	}
	//constructor cu parametri
	Spectator(char* n, string t, string e) : telefon(t), email(e)
	{
		int l = strlen(n) + 1;
		nume = new char[l];
		strcpy_s(nume, l, n);
		//cout << "am apelat consructorul cu parametri clasa Spectator" << endl;
	}
	//constructor de copiere
	Spectator(const Spectator& s) : telefon(s.telefon), email(s.email)
	{
		if (s.nume)
		{
			int l = strlen(s.nume) + 1;
			nume = new char[l];
			strcpy_s(nume, l, s.nume);
		}
		else
		{
			this->nume = nullptr;
		}
		//	cout << "am apelat consructorul de copiere clasa Spectator" << endl;
	}

	//operator egal
	Spectator& operator = (const Spectator& s)
	{
		telefon = s.telefon;
		email = s.email;
		if (nume)
		{
			delete[] nume;
		}

		if (s.nume)
		{
			int l = strlen(s.nume) + 1;
			nume = new char[l];
			strcpy_s(nume, l, s.nume);
		}
		//		cout << "am apelat operatorul egal clasa Spectator" << endl;
		return *this;
	}
	//destructor
	~Spectator()
	{
		if (nume)
		{
			delete[] nume;
		}

	}

	//cast Spectator catre string - afiseaza numele spectatorului
	operator string ()
	{
		string numeSpect(nume);
		return numeSpect;
	}
	
	//definire functie nume(), mostenita din clasa virtuala
	string name()
	{
		if (nume)
		{
			string numeSpect(nume);
			return numeSpect;
		}
		else 
		{ 
			return ""; 
		};

	}


	//afiseaza datele spectatorului
	void afiseaza()
	{
		cout << "Spectator: " << nume << " Telefon: " << telefon << " Email: " << email << endl;
	}
	
	//afiseaza datele spectatorului- functie virtuala cu redefinire in clasa derivata 
	virtual void afiseazaSpectator()
	{
		afiseaza();
	}
	//afiseaza tipul spectatorului
	virtual void afiseazaTip()
	{
		cout << "Spectator obisnuit";
	}

	//setez numele spectatorului din parametru
	//transformare de la string la char*
	bool setNume(string nume)
	{
		int l = nume.size() + 1;
		if (l > 3)
		{
			if (this->nume)
			{
				delete[] this->nume;
			}
			this->nume = new char[l];
			strcpy_s(this->nume, l, nume.c_str());
			cout << "Am setat numele spectatorului la " << this->nume << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	//setez telefonul spectatorului din parametru
	//preiau din stringul transmis numai partea numerica
	//testez daca lungimea este de 10 caractere
	//daca parametrul = 0, setez telefon = 0
	bool setTelefon(string telefon)
	{
		if (telefon == "0")
		{
			this->telefon = "0";
			cout << "Spectator fara telefon" << endl;
			return true;
		}

		string tmpTelefon = "";

		int l = telefon.size() + 1;//lungimea parametrului transmis
		char* t = new char[l]; // creez un array de char de lungimea stringului
		strcpy_s(t, l, telefon.c_str()); // copii stringul in char
		for (int i = 0; i < l; i++)  //parcurg char-ul si preiau caracterele numerice in tmpTelefon
		{
			if (isdigit(t[i]))
			{
				tmpTelefon += t[i];
			}
		}

		l = tmpTelefon.size();
		if (l == 10)
		{
			this->telefon = tmpTelefon;
			cout << "Am setat telefonul la: " << this->telefon << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	//setez emailul spectatorului din parametru
	//verific formatul folosind functia emailFormat
	//daca parametrul = 0 = setez email = 0
	bool setEmail(string email)
	{
		if (email == "0")
		{
			cout << "Spectator fara email" << endl;
			return true;
		}
		if (emailFormat(email))
		{
			this->email = email;
			cout << "Am setat adresa de email la " << this->email << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

};

//supraincarcare pentru operator scriere <<
//apelez functia din definitia clasei
ostream& operator << (ostream& o, Spectator& s)
{
	s.afiseaza();
	return o;
}

//supraincarcare pentru operator citire >>
istream& operator >> (istream& i, Spectator& s)
{

	string n = "";
	while (!(s.setNume(n)))
	{

		cin.clear();
		cin.ignore(10000, '\n');
		cout << endl << "Introduceti Numele spectatorului (cel putin 3 caractere): ";
		getline(i, n);
	}
	string t = "";
	while (!(s.setTelefon(t)))
	{

		cin.clear();
		cout << endl << "introduceti un numar de telefon din 10 cifre!" << endl;
		cout << "Caracterele nenumerice vor fi ignorate. (0 = fara telefon): ";
		getline(i, t);
	}
	string e = "";
	while (!(s.setEmail(e)))
	{

		cin.clear();
		cout << endl << "Introduceti o adresa de email valida" << endl;
		cout << "in formatul nume@domeniu.com. (0 = fara email) : ";
		getline(i, e);
	}

	return i;
}


class SpectatorSpecializat : public Spectator  /*spectatori de tip Presa, critic de film, staff */
{
private:
	string tipSpecializare;
	string detaliiSpecializare;
	float procentReducereBilet;//de modificat in functie de specializare
public:
	//constructor implicit
	SpectatorSpecializat() :tipSpecializare(""), detaliiSpecializare(""), procentReducereBilet(0)
	{
		//	cout << "am apelat consructorul implicit clasa SpectatorSpecializat" << endl;
		setProcentReducere();
	};
	//constructor cu parametri
	SpectatorSpecializat(char* n, string t, string e, string tipS, string detaliiS) :Spectator(n, t, e), tipSpecializare(tipS), detaliiSpecializare(detaliiS), procentReducereBilet(0)
	{
		//	cout << "am apelat consructorul cu parametri clasa SpectatorSpecializat" << endl;
		setProcentReducere();
	};

	//constructor de copiere
	SpectatorSpecializat(const SpectatorSpecializat& s) :Spectator(s), tipSpecializare(s.tipSpecializare), detaliiSpecializare(s.detaliiSpecializare), procentReducereBilet(s.procentReducereBilet)
	{
		//	cout << "am apelat consructorul de copiere clasa SpectatorSpecializat" << endl;
		setProcentReducere();
	};
	//operator egal
	SpectatorSpecializat& operator = (const SpectatorSpecializat& s)
	{
		Spectator::operator=(s);
		tipSpecializare = s.tipSpecializare;
		detaliiSpecializare = s.detaliiSpecializare;
		procentReducereBilet = s.procentReducereBilet;
		//		cout << "am apelat operatorul egal clasa SpectatorSpecializat" << endl;
		setProcentReducere();
		return *this;
	};
	//destructor
	~SpectatorSpecializat()
	{};

	//metoda pentru stabilirea procentului de reducere in functie de tipul specializarii
	void setProcentReducere()
	{
		if (tipSpecializare == "presa" || tipSpecializare == "PRESA")
		{
			procentReducereBilet = 100;
		}
		else if (tipSpecializare == "critic" || tipSpecializare == "CRITIC")
		{
			procentReducereBilet = 100;
		}
		else if (tipSpecializare == "staff" || tipSpecializare == "STAFF")
		{
			procentReducereBilet = 50;
		}
		else if (tipSpecializare == "student" || tipSpecializare == "STUDENT")
		{
			procentReducereBilet = 50;
		}
		else { procentReducereBilet = 0; }
	}

	//getter pentru returnarea procentului de reducere
	float returnProcentReducere()
	{
		return procentReducereBilet;
	}

	//setare tip specializare
	bool setSpecializare(string specializare, string detalii)
	{
		list<string>valoriAcceptate = { "presa", "critic", "staff", "student", "altele", "x", "PRESA", "CRITIC", "STAFF", "STUDENT", "ALTELE", "X" };
		bool verificare = contains(valoriAcceptate, specializare); //utilizez functie template contains 
		if (verificare)
		{
			this->tipSpecializare = specializare;
			this->detaliiSpecializare = detalii;
			setProcentReducere();//recalculez procentul de reducere
			return true;
		}
		else
		{
			cout << endl << "introduceti un tip de specializare din urmatoarea lista:" << endl;
			cout << "--> presa, critic, staff, student, altele, x: ";
			return false;
		}
	}



	//afiseaza Spectator specializat
	void afiseaza()
	{
		Spectator* a = this; //pointer catre Spectator pentru apelarea operatorului din clasa de baza
		cout << *a;
		cout << "Tip Spectator: " << tipSpecializare << endl<< " Detalii: " << detaliiSpecializare << endl;
		cout << "Beneficiaza de o reducere de: " << procentReducereBilet << "%" << endl;
	}
	
	//afiseaza datele spectatorului- redefinire functie virtuala
	void afiseazaSpectator() 
	{
		this->afiseaza();
	}

	//afiseaza tipul spectatorului
	void afiseazaTip()
	{
		cout << this->tipSpecializare;
	}
	
	//definire functie nume(), mostenita din clasa virtuala
	string name()
	{
		return this->Spectator::name() + '\n' + this->tipSpecializare;
	}

};

//supraincarcare pentru operator de scriere <<
ostream& operator << (ostream& o, SpectatorSpecializat& s)
{
	s.afiseaza();
	return o;
}

//supraincarcare pentru operator citire>>
istream& operator >> (istream& i, SpectatorSpecializat& s)
{
	//apelez operatorul din clasa de baza
	Spectator& a = s; //upcast catre clasa de baza
	cin >> a;


	string t = "";//string pentru tip specializare
	string d = "";//string pentru detalii specializare
	while (!(s.setSpecializare(t, d)))
	{
		cin.clear();
		getline(i, t);
		cin.clear();
		cout << endl << "Detalii specializare (optional): ";
		getline(i, d);
	}

	return i;
}


class Bilet: public Arhiva
{
private:
	int idBilet;
	time_t dataEmitere;
	string statusBilet;
	VizionareFilm* vizionare;
	int rand;
	int scaun;
	Spectator* spectator;
	SpectatorSpecializat* spectatorSpecializat;
	float sumaCash;
	float sumaCard;
	static int ultBilet;
public:

	//constructorul implicit
	Bilet() : idBilet(Bilet::ultBilet + 1), dataEmitere(time(0)), statusBilet("In asteptare"), vizionare(NULL), rand(0), scaun(0), spectator(NULL), spectatorSpecializat(NULL), sumaCash(0), sumaCard(0)
	{
		Bilet::ultBilet = this->idBilet;
		//cout << "apelez constructorul implicit clasa Bilet" << endl;
	};

	//constructorul cu parametri
	Bilet(VizionareFilm* v, Spectator* s, SpectatorSpecializat* ss) :idBilet(Bilet::ultBilet + 1), dataEmitere(time(0)), statusBilet("In asteptare"), vizionare(v), spectator(s), spectatorSpecializat(ss), rand(0), scaun(0), sumaCash(0), sumaCard(0)
	{
		Bilet::ultBilet = this->idBilet;
		//cout << "apelez constructorul cu parametri clasa Bilet" << endl;
	};


	//constructorul de copiere
	Bilet(Bilet& b) : idBilet(Bilet::ultBilet + 1), dataEmitere(b.dataEmitere), statusBilet("In asteptare"), vizionare(b.vizionare), rand(0), scaun(0), sumaCash(0), sumaCard(0)
	{
		Bilet::ultBilet = this->idBilet;
		//cout << "apelez constructorul de copiere clasa Bilet" << endl;
	}

	//operatorul egal
	Bilet& operator = (Bilet& b)
	{
		idBilet = this->idBilet;//pastrez id-ul existent
		dataEmitere = b.dataEmitere;
		statusBilet = "In asteptare";
		vizionare = b.vizionare;
		rand = 0;
		scaun = 0;
		sumaCash = 0;
		sumaCard = 0;
		//cout << "apelez operator egal clasa Bilet" << endl;
		return *this;
	}

	//destructor
	~Bilet()
	{
		if (vizionare) 
		{
			delete vizionare;
		}
		if (spectator)
		{
			delete spectator;
		}
		if (spectatorSpecializat) 
		{
			delete spectatorSpecializat; 
		}

	}


	bool operator== (const Bilet& b)
	{
		if (this->idBilet == b.idBilet && this->dataEmitere == b.dataEmitere)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//supraincarcare pentru operator ! anuleaza biletul curent (sterge id-ul biletului de pe scaun si schimba statusul in Anulat)
	void operator!()
	{
		statusBilet = "Anulat";//actualizez statusul biletului curent
		if (vizionare)
		{
			vizionare->operator()(rand, scaun) = 0;
		}
		this->rand = 0; //sterg locul ocupat de pe bilet
		this->scaun = 0;
		this->sumaCash = 0;//sterg suma incasata
		this->sumaCard = 0;
		cout << "Biletul a fost anulat!" << endl;
	}

	//supraincarcare pentru operator ++ (prefix operator)  schimba randul programarii pe primul rand superior cu locuri disponibile
	bool operator++()
	{
		int r = vizionare->returnSala()->returnRanduriSala();//preiau numarul maxim de randuri
		int s = vizionare->returnSala()->returnScaunePeRand();//preiau numarul de scaune pe rand
		for (int i = this->rand + 1; i <= r; i++)//parcurg randurile superioare, de la randul curent pana la ultimul rand
		{
			for (int j = 1; j <= s; j++)
			{
				if (vizionare->returnOcupare(i, j) == 0)
				{
					//eliberez locul actual
					vizionare->operator()(this->rand, this->scaun) = 0;
					//schimb numarul locului pe biletul curent
					this->rand = i;
					this->scaun = j;
					//marchez noul loc cu id-ul biletului curent
					vizionare->setStatusOcupare(rand, scaun, this->idBilet);
					cout << "am mutat biletul pe randul " << i << " locul " << j << endl;
					return true;
				}
			}

		}
		cout << "Nu am gasit un loc liber pe randurile superioare! " << endl;
		return false;
	}



	//supraincarcare pentru operator -- schimba randul programarii pe primul rand inferior cu scaune disponibile
	bool operator--()
	{
		int s = vizionare->returnSala()->returnScaunePeRand();//preiau numarul de scaune pe rand
		for (int i = this->rand - 1; i > 0; i--)//parcurg randurile inferioare, de la randul curent pana la primul rand
		{
			for (int j = 1; j <= s; j++)
			{
				if (vizionare->returnOcupare(i, j) == 0)
				{
					//eliberez locul actual
					vizionare->operator()(this->rand, this->scaun) = 0;
					//schimb numarul locului pe biletul curent
					this->rand = i;
					this->scaun = j;
					//marchez noul loc cu id-ul biletului curent
					vizionare->setStatusOcupare(rand, scaun, this->idBilet);
					cout << "am mutat biletul pe randul " << i << " locul " << j << endl;
					return true;
				}
			}

		}
		cout << "Nu am gasit un loc liber pe randurile superioare! " << endl;
		return false;
	}

	//operator indexare [] - schimba locul biletului curent pe locul specificat, daca acesta este liber (deplasare pe alt loc, de pe acelasi rand)
	bool operator[](int s)
	{
		if (!(s > 0 && s < vizionare->returnSala()->returnScaunePeRand()))
		{
			cout << "Locul solicitat nu se regaseste in sala! " << endl;
			return false;
		}

		if (vizionare->operator()(this->rand, s) == 0)
		{
			//eliberez locul actual
			vizionare->operator()(this->rand, this->scaun) = 0;
			//schimb numarul locului pe biletul curent
			this->scaun = s;
			//marchez noul loc cu id-ul biletului curent
			vizionare->setStatusOcupare(this->rand, s, this->idBilet);
			cout << "am mutat biletul pe randul " << this->rand << " locul " << this->scaun << endl;
			return true;
		}
		else
		{
			cout << "Locul solicitat nu este liber! " << endl;
			return false;
		}

	}

	//supraincarcare pentru operator int - returneaza id-ul biletului
	operator int() const
	{
		return this->idBilet;
	}


	//supraincarcare operator bool - returneaza true pentru biletele valide
	operator bool() const
	{
		if (this->statusBilet == "Valid")
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	//calculeaza pret bilet
	float calculeazaPret()
	{
		float p = 0;//pretul intreg al biletului
		if (this->vizionare)//returnez valori doar daca vizionarea are setata o sala		{
		{
			p = this->vizionare->returnPret();
		}

		float r = 0;//procent reducere
		if (this->spectatorSpecializat)
		{
			r = (float)this->spectatorSpecializat->returnProcentReducere();
		}
		//cout << "Pretul este: " << p - p * r / 100 << endl;
		return p - p * r / 100;
	}

	//cast la float. Am folosit codul functiei calculeazaPret()
	operator float() const
	{
		float p = 0;//pretul intreg al biletului
		if (this->vizionare)//returnez valori doar daca vizionarea are setata o sala		{
		{
			p = this->vizionare->returnPret();
		}

		float r = 0;//procent reducere
		if (this->spectatorSpecializat)
		{
			r = (float)this->spectatorSpecializat->returnProcentReducere();
		}
		//cout << "Pretul este: " << p - p * r / 100 << endl;
		return p - p * r / 100;
	}

	//validare bilet
	bool validareBilet(int rand, int scaun, float sumaCash, float sumaCard)
	{
		if (rand > 0 && scaun > 0 && (spectator || spectatorSpecializat) && //daca s-a specificat randul, scaunul si spectatorul
			(vizionare->returnOcupare(rand, scaun) == 0 || vizionare->returnOcupare(rand, scaun) == idBilet) //daca locul nu este ocupat sau este ocupat de biletul curent 
			&& this->calculeazaPret() - (sumaCard + sumaCash) < 0.01 // biletul este platit
			)
		{
			statusBilet = "Valid";//actualizez statusul biletului curent
			vizionare->setStatusOcupare(rand, scaun, this->idBilet); //marchez locul ca fiind ocupat in clasa VizionareFilm
			this->rand = rand; //setez pe bilet locul ocupat
			this->scaun = scaun;
			this->sumaCash = sumaCash;
			this->sumaCard = sumaCard;
			cout << "Datele introduse au fost validate!" << endl;
			return true;
		}
		else
		{
			statusBilet = "in asteptare";
			cout << "Biletul nu a fost validat" << endl;
			return false;
		}
	}

	//return numarul de randuri din sala
	int returnRanduri()
	{
		if (this->vizionare && this->vizionare->returnSala())//returnez valori doar daca vizionarea are setata o sala
		{
			return	this->vizionare->returnSala()->returnRanduriSala();
		}
		else
		{
			//selectie invalida
			return -1;
		}
	}
	//return numarul de scaune pe rand
	int returnScaune()
	{
		if (this->vizionare && this->vizionare->returnSala())//returnez valori doar daca vizionarea are setata o sala
		{
			return	this->vizionare->returnSala()->returnScaunePeRand();
		}
		else
		{
			//selectie invalida
			return -1;
		}
	}

	//printeaza detaliile vizionarii selectate in biletul curent
	void printVizionare()
	{
		cout << *vizionare;
	}

	void afisareBilet()
	{
		cout << endl;
		cout << "=====================================" << endl;
		cout << "BILET DE ACCES LA CINEMA" << endl;
		Data de(dataEmitere);
		cout << "Numar bilet: " << this->idBilet << endl;
		cout << "Data bilet: " << de.returData() << endl;;
		this->vizionare->returnFilm()->afisare();//functia afiseaza datele filmului
		this->vizionare->returnDataVizionare();//returneaza si afiseaza data vizionare
		cout << endl;
		cout << (string)*this->vizionare->returnSala() << endl;//cast la string pentur Sala = afiseaza numele salii
		cout << "Randul: " << this->rand << " Scaunul: " << this->scaun << endl;
		cout << this->statusBilet << endl;
		cout << "=====================================" << endl;
	}

	bool arhivare()
	{
		fstream b;
		b.open("bilete.dat", ios::out | ios::app | ios::_Nocreate | ios::binary);//deschiderea fisierului bilete in mod binar, nu rescriu daca exista, scriu la sfarsit 
		if (b) 
		{

			b << idBilet << '\n' << dataEmitere << '\n' << statusBilet << '\n'
				<< this->vizionare->returnSala()->name() << '\n'
				<< this->vizionare->returnFilm()->name() << '\n'
				<< this->vizionare->returnDataVizionare() << '\n'
				<< rand << '\n' << scaun << '\n' 
				<< this->spectator->name() << '\n'
				<< this->spectatorSpecializat->name() << '\n'//returneaza nume si tip specializare
				<< sumaCash << '\n' 
				<< sumaCard << '\n';
			
			b.close();
			return true;
		}
		else
		{ 
			"fisierul nu se deschide";
			return false;
		}
		
	}
	
	bool dezarhivare(int numarBilet)
	{
		vector<string> bilete;
		ifstream b;
		b.open("bilete.dat", ios::in | ios::_Nocreate|ios::binary);//deschiderea fisierului bilete 

		if (b)
		{
			//declar variabile temporare pentru stocarea valorilor din fisier
			string idBilet;
			string dataEmitere;
			string statusBilet;
			string numeSala;
			string numeFilm;
			string dataVizionare;
			string rand;
			string scaun;
			string spectator;
			string spectatorSpecializat;
			string sumaCash;
			string sumaCard;
			bool amGasitBiletul = false;
			//preiau sumele in variabilele temporare
			while (
				b >> idBilet >> dataEmitere >> statusBilet && b.ignore(1000, '\n')
				&& getline(b, numeSala) && getline(b, numeFilm)
				&& b >> dataVizionare >> rand >> scaun
				&& b.ignore(1000, '\n') && getline(b, spectator) && getline(b, spectator)
				&& getline(b, spectatorSpecializat) && b >> sumaCash >> sumaCard
				)
			{
				//concatenez biletul in string a, pe care il voi incarca in vector de string
				string a;
				a = idBilet + '\n' + dataEmitere + '\n' + statusBilet + '\n' + numeSala
					+ '\n' + numeFilm + '\n' + dataVizionare + '\n' + rand + '\n' + scaun + '\n' + spectator
					+ '\n' + spectatorSpecializat + '\n' + sumaCash + '\n' + sumaCard;
				//transfer in vector
				bilete.push_back(a);
			}
			//parcurg vectorul de la sfarsit la inceput. pentru biletele care au avut mai multe statusuri, ultimul este considerat corect
			for (vector<string>::reverse_iterator i = bilete.rbegin();
				i != bilete.rend(); ++i)
			{
				int idb; //variabila temporara pentru testarea id-ului de bilet
				stringstream n;
				n << *i; //alimentez n cu inregistrarea curenta din vector
				n >> idb; //transfer in variabila prima  parte a stringului. Daca idul corespunde cu parametrul functiei, reconstruiesc si afisez biletul
				if (idb == numarBilet)
				{
					amGasitBiletul = true;
					//sparg stringstream in variabile string
					n >> dataEmitere >> statusBilet &&
						n.ignore(1000, '\n')
						&& getline(n, numeSala) && getline(n, numeFilm)
						&& n >> dataVizionare >> rand >> scaun
						&& n.ignore(1000, '\n')
						&& getline(n, spectator) && getline(n, spectatorSpecializat)
						&& n >> sumaCash >> sumaCard;
					Data de; de.setTime_string(dataEmitere);//cast string la time_t. Altfel, este apelat eronat constructorul cu parametru string
					Data dv; dv.setTime_string(dataVizionare); //cast string la time_t. Altfel, este apelat eronat constructorul cu parametru string
				
					//refac imaginea biletului
					cout << endl;
					cout << "=====================================" << endl;
					cout << "COPIE - BILET DE ACCES LA CINEMA" << endl;
					cout << "Numar bilet: " << idb << endl;
					cout << "Data bilet: " << de.returData() << endl;
					cout << numeFilm << endl;
					cout << "Data vizionare: " << dv.returData() << ", ora: " << dv.returOra() << endl;
					cout << endl;
					cout << numeSala << endl;
					cout << "Randul: " << rand << " Scaunul: " << scaun << endl;
					cout << statusBilet << endl;
					cout << "=====================================" << endl;
					break;
				}
				
			}
			b.close();
			return amGasitBiletul;
		}
		else
		{
			cout << "Fisierul pentru dezarhivare nu s-a deschis." << endl;
			return false;
		}
	}
};
//initializare membru static
int Bilet::ultBilet = 0;

//supraincarcare pentru operator scriere
ostream& operator << (ostream& o, Bilet& b)
{//apelez functia de afisare din clasa 
	b.afisareBilet();
	return o;
}

// supraincarcare operator citire
// permite selectia randului, scaunului si metodei de plata
// valideaza biletul daca este posibil
istream& operator >> (istream& i, Bilet& b)
{
	int r = 0;
	int s = 0;

	cout << "introduceti numarul randului in intervalul 0 < > " << b.returnRanduri() << ": ";
	while (!(r > 0 && r <= b.returnRanduri()))
	{
		cin.clear();
		i >> r;
	}
	cout << "introduceti numarul scaunului in intervalul 0 < > " << b.returnScaune() << ": ";
	while (!(s > 0 && s <= b.returnScaune()))
	{
		cin.clear();
		i >> s;
	}
	float p = b; //.operator= .calculeazaPret();//returneaza pretul biletului pretul biletului
	float n = 0; //suma inc asara cu numerar;
	float c = 0; //suma incasara pe card;
	cout << "Pretul biletului este " << p << endl;

	char o = ' '; //optiune incasare
	while (!(toupper(o) == 'N' || toupper(o) == 'C' || toupper(o) == 'R'))
	{
		cout << "Selectati metoda de incasare. Tastati:" << endl;
		cout << "--> N pentru incasarea cu numerar" << endl;
		cout << "--> C pentru incasarea pe card" << endl;
		cout << "--> R biletul este prea scump, nu am bani" << endl;

		cin.clear();
		i >> o;
		if (toupper(o) == 'N')
		{
			n = p;
		}
		else if (toupper(o) == 'C')
		{
			c = p;
		}
		else { n = 0; c = 0; }

	}
	//apelez functia de validare a biletului
	b.validareBilet(r, s, n, c);
	return i;
}




//clasa penru popularea obiectelor cu date de test si implementarea meniului de vanzare a biletelor
class masterCinema
{
public:
	int nss; //numar sali spectacol
	int nf;//numar filme care vor rula in cinema
	int z; //numarul de zile pentru initializarea programului de vizionare. 

	//membri gestionare salaSpectacol
	SalaSpectacol* cinema;//array pentru popularea salilor de cinema

	//membri gestionare filme
	Film* ListaFilme; //array cu filmele care ruleaza in cinema

	//membri gestionare programari
	int* durataFilm;//array cu durata filmelor
	string dataStart;//prima zi de vizionare
	Data** oreVizionare;//z zile //array pentru prelucrarea datei folosind functiile din clasa Data
	VizionareFilm*** programCinema;//z zile * 3 vizionari pe zi * nss sali spectacol
	VizionareFilm** tempVizionari;//array liniar de pointeri la VizionareFilm pentru indexarea accesului la vizionarile unui anumit film
	vector<Bilet*> bileteEmise;//vector pentru gestionarea biletelor emise
	vector<Bilet*>::iterator it = bileteEmise.end();// variabila iterator pentru stocarea ultimului id adaugat in vectorul de bilete

	//membri noi, de tip map (cheie, valoare) pentru gestionarea Salilor, Filmelor si Vizionarilor
	map<int, SalaSpectacol*> mapCinema;
	map<int, Film*> mapListaFilme;
	map<int, Bilet*> mapBileteEmise;
	map<int, Spectator*> mapSpectatori;


	//constructorul default
	masterCinema() :nss(0), nf(0), z(0), cinema(NULL), ListaFilme(NULL), dataStart(""), oreVizionare(NULL), programCinema(NULL), tempVizionari(NULL)
		//initializare pentru membrii map
		,mapCinema(), mapListaFilme(), mapBileteEmise(), mapSpectatori()
	{};

	//metoda initializare
	void initializare()
	{
		nss = 5; //numar sali spectacol
		nf = 4;//numar filme care vor rula in cinema
		z = 3; //numarul de zile pentru initializarea programului de vizionare.
		dataStart = "15.01.2021";//prima zi de vizionare

		// INITIALIZARE SALI CINEMA
		//initializez Cinema cu nss sali de spectacol
		cinema = new SalaSpectacol[nss];
		//array pentru popularea salilor de cinema
		string a[5];
		a[0] = "Sala 0\n20\n25\nY\n";
		a[1] = "Sala 1\n15\n10\nN\n";
		a[2] = "Sala 2\n10\n15\nY\n";
		a[3] = "Sala 3\n20\n25\nY\n";
		a[4] = "Sala 4\n10\n10\nN\n";

		//popularea salilor folosind supraincarcarea operatorului de citire >>
		for (int i = 0; i < nss; i++)
		{
			stringstream in;
			in << a[i];
			in >> cinema[i];
			//afisez datele salii folosind supraincarcarea operatorului de scriere <<
			cout << endl << "Am populat sala " << i << " cu urmatoarele date:" << endl << cinema[i];
		}

		//popularea containerului mapCinema
		for (int i = 0; i < nss; i++)
		{
			stringstream in;
			in << a[i];
			mapCinema[i] = new SalaSpectacol;
			in >> *mapCinema[i];
			//afisez datele salii folosind supraincarcarea operatorului de scriere <<
			cout << endl << "Am populat sala " << i << " cu urmatoarele date:" << endl << *mapCinema[i];
		}

		// INITIALIZARE FILME
		//initializez lista de filme 
		ListaFilme = new Film[nf];
		//array pentru popularea listei filmelor
		//format stream pentru apelarea automata: "numeFilm\nproducator\ndurata\nsubtitrare(1 = dublat, 2 = subtitrat, 3 = original )\n 2d (Y/N) \n 3d (Y/N) \n"
		string lf[4];
		lf[0] = "Pantera Neagra\nDysney\n120\n1\nY\nN\n";
		lf[1] = "Titanic\nParamount Pictures\n200\n1\nN\nY\n";
		lf[2] = "Gone with the Wind\nFox\n160\n1\nN\nN\n";
		lf[3] = "Romania neamblanzita\nRomaniaFilm\n100\n1\nY\nY\n";

		//popularea listei filmelor folosind supraincarcarea operatorului de citire >>
		for (int i = 0; i < nf; i++)
		{
			stringstream in;
			in << lf[i];
			in >> ListaFilme[i];
			//afisez datele filmului folosind supraincarcarea operatorului de scriere <<
			cout << endl << "Am populat filmul " << i << " cu urmatoarele date:" << endl << ListaFilme[i];
		}

		//popularea containerului mapListaFilme
		for (int i = 0; i < nf; i++)
		{
			stringstream in;
			in << lf[i];
			mapListaFilme[i] = new Film;
			in >> *mapListaFilme[i];
			//afisez datele filmului folosind supraincarcarea operatorului de scriere <<
			cout << endl << "Am populat filmul " << i << " cu urmatoarele date:" << endl << *mapListaFilme[i];
		}

		//INITIALIZARE PROGRAM DE VIZIONARE
		//programez vizionarea filmelor pentru urmatoarele z zile
		//in fiecare sala ruleaza 3 spectacole / zi, la ora 10, 15, 20
		//repartizez parcurgand array de filme si array de sali, pe prima sala cu tehnologia 3d/2d disponibila
		//vom avea un numar de nss(numarul de sali) x  z (numarul de zile) x 3 = numarul de spectacole in saptamana
		//pretul biletului: 
			// - pentru filme 3D cu durata >= 100 minute = 15
			// - pentru filme 3D cu durata mai mica de 100 minute = 10
			// - pentru filme 2D cu durata >= 100 minute = 10
			// - pentru filme 2D cu durata mai mica de 100 minute = 5
		//programez filmele 3d in salile care accepta tehnologie 3d

	//creez array multidimensional pentru programarea vizionarilor
		oreVizionare = new Data * [z];//z zile //array pentru prelucrarea datei folosind functiile din clasa Data
		programCinema = new VizionareFilm * *[z];//z zile * 3 vizionari pe zi * nss sali spectacol
		int uf = 0; //variabila pentru scanarea ultimului film programat
		for (int i = 0; i < z; i++) //parcurg zilele de vizionare
		{
			oreVizionare[i] = new Data[3];
			programCinema[i] = new VizionareFilm * [3];//3 vizionari pe zi
			for (int j = 0; j < 3; j++) //parcurg orele de vizionare
			{
				//prelucrez data folosind clasa Data
				int h = 0;//variabila pentru ora
				switch (j)
				{
				case 0:
					h = 10;
					break;
				case 1:
					h = 15;
					break;
				case 2:
					h = 20;
					break;
				};
				oreVizionare[i][j].setDataSiOra(dataStart, h);
				oreVizionare[i][j].adaugaZile(i);
				//sfarsit prelucrare data
				programCinema[i][j] = new VizionareFilm[nss];//nss sali de cinema
				for (int k = 0; k < nss; k++) //parcurg salile
				{
					programCinema[i][j][k].setDataVizionare(oreVizionare[i][j].returnTimeT());
					for (int l = uf;; l = (l + 1) % nf) //parcurg filmele circular, dupa ultimul film programat 
					{
						if ((bool)ListaFilme[l] == (bool)cinema[k])//daca tehnologia filmului corespunde cu cea a salii
						{
							uf = (l + 1) % nf;//pastrez urmatorul film de programat in variabila
							programCinema[i][j][k].setSalaSiFilm(&cinema[k], &ListaFilme[l]);//setez filmul si sala pe programarea curenta

							//calculez pretul filmului in functie de durata si tehnologie (s-ar putea defini o functie de calcul cu parametri)
							bool df = ((int)ListaFilme[l] >= 100); //folosesc cast la int si bool pentru returnarea minutelor si tehnologiei
							bool tf = ((bool)ListaFilme[l] == true);
							float pretFilm = 0;
							if (df && tf) //3d, peste 100min
							{
								pretFilm = 15;
							}
							else if (!df && tf) { pretFilm = 10; } //3d, sub 100min
							else if (df && !tf) { pretFilm = 10; } //2d, peste 100min
							else { pretFilm = 5; } //2d, sub 100min
							programCinema[i][j][k] + pretFilm;//setez pretul folosind supraincarcarea pentru opeerator +
							programCinema[i][j][k] += 0;//setez toate locurile ca fiind libere - supraincarcarea pentru +=
							//setez statusul programarii ca deschis
							programCinema[i][j][k].setStatus("deschis");

							break;
						}
					}
				}
			}
		}



	}

	//afiseaza toate programarile
	void afisareProgramari()
	{
		for (int i = 0; i < z; i++) //parcurg zilele de vizionare
		{
			for (int j = 0; j < 3; j++) //parcurg orele de vizionare
			{
				for (int k = 0; k < nss; k++) //parcurg salile
				{
					cout << endl << programCinema[i][j][k] << endl;//folosesc supraincarcarea pentru <<
				}
			}
		}
	}



	~masterCinema() {
		delete[] cinema;//array pentru popularea salilor de cinema
		delete[] ListaFilme; //array cu filmele care ruleaza in cinema
		delete[] oreVizionare;//z zile //array pentru prelucrarea datei folosind functiile din clasa Data
		delete[] programCinema;//z zile * 3 vizionari pe zi * nss sali spectacol
		delete[] tempVizionari;

	}

	void veziListaFilme()
	{
		cout << "Lista filmelor care ruleaza in Cinema:" << endl;
		for (int i = 0; i < nf; i++)
		{
			cout << "\t\t";
			(i + 1) < 10 ? cout << i + 1 << "  " : cout << i + 1 << " ";
			cout << " --> " << (string)ListaFilme[i] << " - " << (int)ListaFilme[i] << " minute, vizionare: ";
			(bool)ListaFilme[i] ? cout << "3D" : cout << "2D";
			cout << endl;

		}

	}

	void afiseazaSpectatori()
	{
		cout << "Spectatorii care au achizitionat bilete la Cinema:" << endl;
		auto iter = mapSpectatori.begin();
		while (iter != mapSpectatori.end()) 
		{
			cout << iter->first << "-->";
			iter->second->afiseazaTip();
			cout << endl;
			iter->second->afiseazaSpectator();
			cout << endl;
			++iter;
		}
		
	}


	//afiseaza programului filmului "a" (id-ul din functia veziListaFilme)
	// incarca variantele posibile de vizionare ale filmuului selectat intr-un array liniar de vizionari
	// returneaza t = indexul maxim al array-ului tempVizionari = adresa ultimei vizionari a filmului selectat
	int afisareFilmeProgramate(int a)
	{
		if (a > nf)
		{
			cout << "Selectie film eronata" << endl;
			return -1;
		}
		else
		{
			//initializare array liniar pentru accesul la vizionarile unui film selectat
			if (tempVizionari)
			{
				delete[] tempVizionari;
			}
			tempVizionari = new VizionareFilm * [nss * z * 3];
			int t = 0;//index pentru array liniar de vizionari

			//daca a==0 prezint toate filmele. Altfel, prezint filmul cu indexul selectat de operator
			for (int f = (a == 0 ? a : a - 1); f < (a == 0 ? nf : a); f++) 
			{
				cout << endl << endl << "Filmul: " << (string)ListaFilme[f] << " este disponibil in urmatoarele date:" << endl;

				for (int i = 0; i < z; i++) //parcurg zilele de vizionare
				{
					for (int j = 0; j < 3; j++) //parcurg orele de vizionare
					{
						for (int k = 0; k < nss; k++) //parcurg salile
						{
							if (programCinema[i][j][k] == ListaFilme[f])//folosesc supraincarcarea operatorului == pentru a compara o vizionare cu un film
							{
								tempVizionari[t] = &programCinema[i][j][k];
								t++;
								cout << "\t\t";
								t < 10 ? cout << t << "  " : cout << t << " ";
								cout << " --> ";
								programCinema[i][j][k].returnDataVizionare(); //functia returneaza data si afiseaza rezultatul
								cout << endl;
							}
						}
					}
				}
			}
			return t - 1;
		}
	}

	//functie pentru afisarea detaliilor unei anumite vizionari
	//preia de la operator filmul dorit
	//afiseaza programarile filmului respectiv 
	//preia de la operator data de vizionare dorita
	//afiseaza detaliile vizionarii respective
	int selectieProgramare() 
	{
		int n = -1;//initializez n cu o valoare in afara listei de selectie
		while (!(n >= 0 && n <= nf))
		{
			//sterge si renunta la input anterior
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Selecteaza un film pentru afisarea programului (0 = toate filmele): ";
			while (!(cin >> n))
			{
				cout << "ERROR: Te rog sa introduci un numar :) ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		
		//apeleaza functia de afisare a programarilor pentru filmul selectat
		int t = afisareFilmeProgramate(n);

		int v = -1;//initializare variabila de selectie a vizionarii cu o valoare in afara listei de selectie
		while (!(v >= 0 && v <= t + 1))
		{
			//sterge si renunta la input anterior
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Selecteaza data de vizionare pentru afisarea salii " << endl;
			cout << "Tasteaza 0 pentru a reveni la meniul principal: ";
			while (!(cin >> v))
			{
				cout << "ERROR: Te rog sa introduci un numar :)";
				cin.clear();
				cin.ignore(1000, '\n');
			}

		}
		if (v != 0)
		{
			cout << endl << "Detaliile filmului selectat:" << endl;
			cout << *tempVizionari[v - 1];//operator afisare pentru clasa Vizionare Film (dereferentiez pentru a ajunge la VizionareFilm)
										//v este afisat cu 1 unitate mai mult decat pozitia in vector
			
		}
		return v; //returneaza id-ul vizionarii selectate de operator
	}


	//FUNCTIE PENTRU GESTIONAREA EMITERII BILETELOR + ALTE OPERATII ASUPRA BILETELOR
	void gestionareBilet()
	{
		vector<Bilet*>::iterator it = bileteEmise.end();// variabila iterator pentru stocarea ultimului id adaugat in vectorul de bilete
		char optiune = '0';

		while (toupper(optiune) != 'X') //X = iesire din meniul de gestionare a biletelor
		{
			system("CLS");
			afiseazaHeader();
			cout << "\t\tAI SELECTAT: ";
			cout << "3--> Gestionare bilete (emitere, modificare, anulare)" << endl;

			//afisez datele ultimului bilet emis 
			if (!(it == bileteEmise.end()))
			{
				cout << endl << "ULTIMUL BILET EMIS:" << endl;
				(**it).printVizionare(); //print detalii vizionare
				cout << **(it);//supraincarcare operator scriere pentru Bilet
			}

			cout << endl << "SELECTEAZA O OPTIUNE" << endl;
			cout << "\t\t1--> emitere bilet" << endl;


			//testez daca ultimul bilet este valid. Daca este valid, activez optiunile suplimentare din meniu (schimbare loc si anulare bilet)
			bool n = false;
			if (!(it == bileteEmise.end())) //daca iteratorul nu este setat pe end = exista bilete in vectorul de bilete
			{
				n = **it; //supraincarcare operator bool pentru clasa Bilet
			}
			//
			if (n) //daca exista bilete in vectorul de bilete si ultimul bilet este valid
			{
				cout << "\t\t2--> schimba locul ultimului bilet pe randul superior" << endl;
				cout << "\t\t3--> schimba locul ultimului bilet pe randul inferior" << endl;
				cout << "\t\t4--> schimba locul ultimului bilet pe locul .... " << endl;
				cout << "\t\t5--> anuleaza ultimul bilet" << endl;
			}
			cout << "\t\t6--> cauta bilet emis in sesiunea curenta" << endl;
			cout << "\t\t7--> printeaza bilet din arhiva" << endl;
			cout << "\t\t8--> cauta bilet emis in sesiunea curenta in mapBileteEmise" << endl;
			cout << "\t\t9--> afiseaza Spectatori" << endl;
			cout << "\t\tX--> revin la meniul principal" << endl;
			cin >> optiune;

			if (optiune == '1')
			{
				int v = -1; //variabila pentru gestionarea pozitiei in vectorul tempvizionari
				veziListaFilme();
				v = selectieProgramare();
				v--;//v este afisat si returnat cu 1 unitate mai mult decat pozitia vizionarii in vector
				while (v >= 0)
				{
					cout << endl << "Avem nevoie de cateva date despre spectator .... " << endl;

					SpectatorSpecializat* ss = new SpectatorSpecializat;
					Spectator* s = new Spectator;

					//optiune spectator specializat
					char specializare = ' ';
					while (!(toupper(specializare) == 'Y' || toupper(specializare) == 'N'))
					{
						cout << "Spectatorul beneficiaza de reducere? Y/N: ";
						cin >> specializare;
					}

					//daca s-a selectat Y - Spectator specializat
					if (toupper(specializare) == 'Y')
					{
						cin >> *ss;
					}
					else //daca s-a selectat Y - Spectator 
					{
						cin >> *s;
					}

					//Incep construirea biletului
					Bilet* b = new Bilet(*&tempVizionari[v], s, ss); //creez obiect nou Bilet folosind constructorul cu parametri
					bileteEmise.push_back(b);//copie pointerul la bilet in vector

					if (!bileteEmise.empty()) //verific daca vectorul s-a populat. Comanda de mai jos nu poate fi executata pe vector gol
					{
						it = bileteEmise.end() - 1; //preiau in iterator ultimul element al vectorului
					}

					if (*b == **it) //operator ==  pentru verificarea egalitatii biletului emis cu cel din iterator
					{
						cin >> **it; //supraincarcare operator citire pentru Bilet
						cout << **it;//supraincarcare operator scriere pentru Bilet
						b->arhivare();
											
						//salvarea spectatorului in vectorul mapSpectatori
						// folosesc prin conventie acelasi index cu cel al biletelor
						if (toupper(specializare) == 'Y')
						{
							s = ss; //upcast spectator specializat catre spectator
						}
						mapSpectatori[b->operator int()] = s;
						
						//cod pentru copierea suplimentara a biletului in mapBilete
						mapBileteEmise[b->operator int()] = b;//copie pointerul la bilet in container mapBileteEmise
						//END cod pentru copierea suplimentara a biletului in mapBilete

					}
					else
					{
						cout << "biletul nu a fost copiat corect in vector";
					}

					

					//optiune de emitere a unui nou bilet, pentru acelasi film
					char biletNou = '0';
					while (!(toupper(biletNou) == 'Y' || toupper(biletNou) == 'N'))
					{
						cout << endl << "SELECTEAZA O OPTIUNE" << endl;
						cout << "\t\tY--> emitere un nou bilet pentru acelasi film" << endl;
						cout << "\t\tN--> revin la meniul anterior" << endl;
						cin >> biletNou;
					}
					if (toupper(biletNou) == 'Y')
					{
						system("CLS");
						afiseazaHeader();
						cout << endl << "Detaliile filmului selectat:" << endl;
						(**it).printVizionare();
						cout << endl;
						cout << "\t\tAI SELECTAT: ";
						cout << "Y--> emitere un nou bilet pentru acelasi film" << endl;

					}
					else
					{
						v = -1;//la v=-1 ies din bucla while v>=0
					}

				}

			}

			if (optiune == '2' && n)
			{
				if (!bileteEmise.empty()) //testez daca vectorul nu este gol, just in case
				{
					++** (it);//supraincarcare operator ++ prefix
					cout << endl << "Detaliile filmului selectat:" << endl;

					(**it).printVizionare(); //print detalii vizionare
					cout << **(it);//supraincarcare operator scriere pentru Bilet
					(**(it)).arhivare();

				}
				system("PAUSE");
			}
			if (optiune == '3' && n)
			{
				if (!bileteEmise.empty()) //testez daca vectorul nu este gol, just in case
				{
					--(**it);//supraincarcare operator -- prefix
					cout << endl << "Detaliile filmului selectat:" << endl;
					(**it).printVizionare();
					cout << **it;//supraincarcare operator scriere pentru Bilet
					(**(it)).arhivare();
				}
				system("PAUSE");
			}
			if (optiune == '4' && n)
			{
				if (!bileteEmise.empty()) //testez daca vectorul nu este gol, just in case
				{
					int loc = 0;
					while (loc == 0)
					{
						cout << "Introduceti locul dorit de spectator: ";
						cin >> loc;
					}
					(**it)[loc];//supraincarcare operator indexare
					cout << endl << "Detaliile filmului selectat:" << endl;
					(**it).printVizionare();
					cout << **it;//supraincarcare operator scriere pentru Bilet
					(**(it)).arhivare();
				}
				system("PAUSE");
			}
			if (optiune == '5' && n)
			{
				if (!bileteEmise.empty()) //testez daca vectorul nu este gol, just in case
				{
					char anulare = ' ';
					while (!(toupper(anulare) == 'Y' || toupper(anulare) == 'N'))
					{
						cout << endl << "Spectatorul s-a razgandit? Y = anulez biletul / N = pastrez biletul   ";
						cin >> anulare;
					}
					if (toupper(anulare) == 'Y')
					{
						!(**it);//supraincarcare operator !
					}
					cout << endl << "Detaliile filmului selectat:" << endl;
					(**it).printVizionare();
					cout << **it;//supraincarcare operator scriere pentru Bilet
					(**(it)).arhivare();
				}
				system("PAUSE");
			}
			if (optiune == '6')
			{
				if (!bileteEmise.empty()) //testez daca vectorul nu este gol, just in case
				{
					cout << "cauta biletul cu id: ";
					int a = -1; //variabila pentru id-ul biletului cautat
					int f = 0; //setez la 1 daca gasesc un bilet
					cin >> a;
					for (it = begin(bileteEmise); it != end(bileteEmise); ++it)
					{
						if (a == (int)**it)
						{
							f = 1;
							cout << endl << "Detaliile filmului selectat:" << endl;
							(**it).printVizionare();
							cout << **it;//supraincarcare operator scriere pentru Bilet
							break;
						}
					}
					f == 0 ? cout << "nu am gasit biletul cu numarul: " << a << endl : cout << endl; //mesaj daca nu gasesc biletul cautat
				}
				else
				{
					cout << "Vectorul de bilete este gol!" << endl;
				}
				system("PAUSE");
			}

			if (optiune == '7')
			{
				cout << "cauta in arhiva biletul cu id: ";
				int a = -1; //variabila pentru id-ul biletului cautat
				bool f = false; //setez la 1 daca gasesc un bilet

				while (!(cin >> a))
				{
					cout << "ERROR: Te rog sa introduci un numar :)";
					cin.clear();
					cin.ignore(1000, '\n');
				}

				Bilet arhiva;
				f = arhiva.dezarhivare(a);
				f == false ? cout << "nu am gasit biletul cu numarul: " << a << endl : cout << endl; //mesaj daca nu gasesc biletul cautat
				system("PAUSE");
			}

			if (optiune == '8')
			{
				if (!mapBileteEmise.empty()) //testez daca containerul nu este gol, just in case
				{
					cout << "cauta biletul cu id: ";
					int a = -1; //variabila pentru id-ul biletului cautat
					int f = 0; //setez la 1 daca gasesc un bilet
					cin >> a;
					if (mapBileteEmise.count(a))
					{
						f = 1;
						cout << endl << "Detaliile filmului selectat:" << endl;
						mapBileteEmise[a]->printVizionare();
						cout << *mapBileteEmise[a];//supraincarcare operator scriere pentru Bilet
					}
					f == 0 ? cout << "nu am gasit biletul cu numarul: " << a << endl : cout << endl; //mesaj daca nu gasesc biletul cautat
				}
				else 
				{
					cout << "nu am gasit bilete emise in sesiunea curenta" << endl;;
				}
				system("PAUSE");
			}

			if (optiune == '9')
			{
				if (!mapSpectatori.empty()) //testez daca containerul nu este gol, just in case
				{
					system("CLS");
					afiseazaHeader();
					cout << "\t\tAI SELECTAT: ";
					cout << "9--> afiseaza Spectatori" << endl;
					cout << "Aici testez cum se comporta functiile virtuale" << endl;
					cout << "Afisarea difera pentru Spectator si Spectator Specializat, desi containerul este de pointeri catre Spectator" << endl << endl;
					afiseazaSpectatori();
				}
				else
				{
					cout << "Nu am gasit spectatori" << endl; 
				}
				system("PAUSE");
			}
		}

	//	system("PAUSE");
	}

	void afiseazaHeader()
	{

		cout << "****************************************************************  " << endl;
		cout << "\tAcademia de Studii Economice din Bucuresti" << endl;
		cout << "Facultatea de Cibernetica, Statistica si Informatica Economica" << endl;
		cout << "****************************************************************  " << endl;
		cout << "\t" << "Student: Radu Claudiu, Grupa 1133, anul II-ID" << endl;
		cout << "\t" << "Profesor: Iancu Bogdan" << endl;
		cout << "****************************************************************  " << endl << endl;
		cout << "\t" << "PROIECT POO: VANZARE BILETE DE CINEMA" << endl;
		cout << "****************************************************************  " << endl << endl;

	}

	void selectieMeniuPrincipal()
	{
		int optiune;//optiune de selectie a meniului
		do {
			afiseazaHeader();
			cout << "\t\t1--> Afiseaza filmele disponibile" << endl;
			cout << "\t\t2--> Afiseaza programul de vizionare" << endl;
			cout << "\t\t3--> Gestionare bilete (emitere, modificare, anulare) " << endl;
			cout << "\t\t4--> Inchide aplicatia" << endl;

			cout << endl << "\t\tSelecteaza o optiune: ";
			cin >> optiune;

			int n = 0; //optiune pentru selectia filmului din lista
			//int v = 0;//optiune de selectie a vizionarii (film + sala + ora)
			int t = 0;//numarul maxim de vizionari ale filmului selectat
			switch (optiune)
			{
			case 1:
				system("CLS");
				afiseazaHeader();
				cout << "\t\tAI SELECTAT: ";
				cout << "1--> Afiseaza filmele disponibile" << endl;
				veziListaFilme();
				system("PAUSE");
				system("CLS");
				break;
			case 2:
				system("CLS");
				afiseazaHeader();
				cout << "\t\tAI SELECTAT: ";
				cout << "2--> Afiseaza programul de vizionare" << endl;
				veziListaFilme();
				selectieProgramare();
				system("PAUSE");
				system("CLS");
				break;

			case 3:
				gestionareBilet();
				system("PAUSE");
				system("CLS");
				break;

			case 4:
				cout << "\nExit aplicatie gestionare bilete\n" << endl;
				break;
			default:
				cout << "==== Selecteaza o optiune corecta====" << endl;
				cout << "=====================================" << endl;
				cin.ignore();
				cin.clear();
				system("PAUSE");
				system("CLS");
			}
		} while (optiune != 4);
	};
};

void main()
{
//initiaza clasa pentru interfata cu utilizatorul
	masterCinema a;
	a.initializare();
//afiseaza meniul principal
	a.selectieMeniuPrincipal();
}