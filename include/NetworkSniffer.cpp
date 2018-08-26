#include <iostream>
#include <string>
#include "NetworkSnifferManager.h"


using namespace std;


int main(int argc, char* argv[]) {

  NetworkSnifferManager *nm = new NetworkSnifferManager(8192);

  nm->~NetworkSnifferManager();
  nm->OpenConnection();

  cout << "Finishing Network Sniffer" << endl;
  return 0;
}