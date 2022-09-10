#include <iostream>
using namespace std;

class vehicle
{
private:
    int id_car;

protected:
    string name_car;

public:
    string where_production;

    // vehicle(int id)
    //{
    //     id_car = id;
    // }
    void set_id_car()
    {
        cin >> id_car;
    }
    void return_id_car()
    {
        cout << id_car << endl;
    }
    void set_name_car();
    void set_where_production();
};
void vehicle::set_name_car()
{
    cin >> name_car;
}
void vehicle::set_where_production()
{
    cin >> where_production;
}
class Ford : public vehicle
{
public:
    string type_ford;
    void return_value()
    {
        cout << name_car << "\n";
        cout << where_production << endl;
    }
};

int main()
{
    // vehicle b{19};
    Ford a;
    a.set_name_car();
    a.set_where_production();
    a.set_id_car();
    a.return_id_car();
    a.return_value();
    return 0;
}