#include <iostream>
#include "json.hh"

using namespace std;
using namespace JSON;

int main(int argc, char** argv)
{
    // Load JSON file
    
    printf("Parsing :\n");
    Value v = parse_file("../tests/comp.json");    
    //cout << v << endl;
    cout << "---" << endl << endl;
    
    // Build object programmatically
    Object obj;
    
    obj["salut"] = true;
    obj["je vaux 4"] = 12;
    obj["je vaux 4"] = 4;
    
    Object o;
    o["bite"] = true;
    o["faux"] = false;
    o["succes"] = "OUI";
    
    obj["matthieu"] = o;
    
    Array a;
    a.push_back(true);
    a.push_back("rondoudou");
    a.push_back(64);
    a.push_back(3.14);
    a.push_back(3.14);
        
    obj["biere"] = a;

    printf("Valeur de matthieu -> bite : %s\n", obj["matthieu"]["bite"] ? "true" : "false");
    printf("Valeur de matthieu -> faux : %s\n", obj["matthieu"]["bonjour"] ? "true" : "false");
    printf("Valeur de je vaux 4 : %i\n\n", obj["je vaux 4"]);
    printf("Valeur de matthieu -> succes : %s\n\n", obj["matthieu"]["succes"]);

    cout << obj << endl;
    
    return EXIT_SUCCESS;
}
