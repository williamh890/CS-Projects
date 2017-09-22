#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <map>
using std::map;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;

int main()
{
    map<int, string> m;
    int key;
    while(1)
    {
        cout << "Enter key and string value (int string): ";
        string input;
        getline(cin, input);
        if(input == "") break;
        istringstream in(input);
        string assoc;
        in >> key >> assoc;
        m[key] = assoc;
    }
    m.erase(key);

    while(1)
    {
    cout << endl << endl;
    cout << "Key: ";
    int k;
    cin >> k;
    if(m.count(k))
    {
        for(auto n : m)
            if(n.first == k)
                cout << "The key " << n.first << " has value: " << n.second;
    }
    else cout << "Key not in dataset" << endl;
    }

}
