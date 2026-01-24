/* 
 * This program manages three asset objects, saving and loading their data from a file using classes and encapsulation.
 * */

#include<iostream>
#include<string>
#include<fstream>
#include<vector>

class asset
{
    private:
        std::string ticker;
        double price;
        int quantity;
    public:
        asset(std::string t, double p, int q)
        {
            ticker = t;
            price = p;
            quantity = q;
        }

        void saveToFile()
        {
            std::ofstream prt("portfolio.db", std::ios::app);
            
            if (!prt.is_open()) 
            {
                std::cout << "0";
            }

            prt << ticker << ";" << price << ";" << quantity << '\n';

            prt.close();
        }

        std::string getTicker() { return ticker; }
        double getPrice() { return price; }
        int getQuantity() { return quantity; }
};

std::vector<asset> memory()
{
    std::vector<asset> func;
    std::string line;
    
    std::ifstream prt("portfolio.db");

    while (getline(prt, line))
    {
        int pos1 = line.find(";");
        int pos2 = line.find(";", pos1 + 1);

        std::string t1 = line.substr(0, pos1);
        
        std::string p1 = line.substr(pos1 + 1, pos2 - pos1 - 1);
        double price = std::stod(p1);

        std::string q1 = line.substr(pos2 + 1);
        int quantity = std::stoi(q1);

        asset obj(t1, price, quantity);

        func.push_back(obj);
    }
    prt.close();

    return func;
}

int main()
{   
    asset PETR4("PETR4", 34.5, 100);
    asset VALE3("VALE3", 85.5, 50);
    asset ITUB4("ITUB4", 29.8, 200);
    
    PETR4.saveToFile();
    VALE3.saveToFile();
    ITUB4.saveToFile();

    std::vector<asset> function = memory(); 

    for (auto&a : function)
    {
        std::cout << a.getTicker() << " " << a.getPrice() << " " << a.getQuantity() << '\n';
    }
    
    return 0;
}
