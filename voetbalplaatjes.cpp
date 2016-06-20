#include <iostream>
#include <vector>

using namespace std;

int main(int charc, char** argv) {
  int i,j,k;
  int m;
  int verschillende;
  int zakjesgrootte;
  int albums;
  int STEEKPROEF;
  bool debug, allesprinten;
  vector<int> duurvoornalbumsvol;
  vector<int> gehad;
  vector<int> wanneergetrokken;
  vector<int> albumvulling;
  int totaalresultaat=0;

  cout<<"Aantal kaarten (standaard 270)                : ";
  cin>>m;
  cout<<"Aantal verschillende kaarten in een zakje     : ";
  cin>>zakjesgrootte;
  cout<<"Aantal te vullen albums                       : ";
  cin>>albums;
  cout<<"Grootte steekproef                            : ";
  cin>>STEEKPROEF;
  cout<<"Alle trekkingen naar stderr? (0=nee, 1=ja)    : ";
  cin>>allesprinten;
  cout<<"Debuggen?                    (0=nee, 1=ja)    : ";
  cin>>debug;
  duurvoornalbumsvol.resize(albums);
  gehad.resize(m);
  wanneergetrokken.resize(m);
  albumvulling.resize(albums);

  cout<<"Aantal kaartjes: "<<m<<endl;
  cout<<"Zakjesgrootte  : "<<zakjesgrootte<<endl;
  cout<<"Aantal albums  : "<<albums<<endl;
  cout<<"Steekproef     : "<<STEEKPROEF<<endl;
  srand(4314314);

  for (j=0;j<albums;j++)
    duurvoornalbumsvol[j]=0;

  for (j=0;j<STEEKPROEF;j++) {
    verschillende=0;
    for (k=0;k<albums;k++) {
      albumvulling[k]=0;
    }
    for (k=0;k<m;k++) { // Leegmaken
      gehad[k]=0;
      wanneergetrokken[k]=-zakjesgrootte;
    }
    k=0;

    while (verschillende<m*albums) {
      i=((double)rand())/RAND_MAX*m; // Kies plaatje
      if (debug) {cout<<"Beurt "<<k<<", pak plaatje "<<i;}

      if (wanneergetrokken[i]/zakjesgrootte==k/zakjesgrootte) {
        if (debug) {cout<<"...\tZat al in 't zakje (beurt "<<wanneergetrokken[i]<<"), sla ik over"<<endl;}
        continue;
      }

      wanneergetrokken[i]=k;
      
      if (gehad[i]<albums) {
        albumvulling[gehad[i]]++;
        if (albumvulling[gehad[i]]==m) {  // Album gehad[i] is vol!
          duurvoornalbumsvol[gehad[i]]+=k;
          if (debug) {cout<<"Album "<<gehad[i]<<" is vol!"<<endl;}
          if (allesprinten) {cerr<<"{"<<gehad[i]<<","<<(double)k/(gehad[i]+1)<<"},"<<endl;}
        }
        gehad[i]++;
        verschillende++;
        if (debug) {cout<<"...\tHad ik nog niet, ik heb er nu "<<verschillende<<endl;}
      }
      else  {
        if (debug) {cout<<"...\tHad ik al"<<endl;}
      }
      k++;
    }
    if (debug) {cout<<"HOERA, COMPLEET!!! (na "<<k<<" plaatjes)"<<endl;}
    totaalresultaat+=k;
  }
  for (j=0;j<albums;j++) {
    cout<<"{"<<j+1<<","<<(double)duurvoornalbumsvol[j]/STEEKPROEF/(j+1)<<"},"<<endl;
  } 
  cout<<(double)totaalresultaat/STEEKPROEF/albums<<endl;
  cout<<endl;
}
