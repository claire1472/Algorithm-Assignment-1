#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;


class Store_Data {
public:
    fstream file;
    struct Goods {
        int Id{0};
        string Name;
        double Price{0};
        string Category;
    };

    vector <Goods> access_Goods() const {

        return goods_list;

    }

    vector<Goods> Open() {
        file.open("product_data.txt");
        while (getline(file, line)) {
            istringstream iss(line);
            while (getline(iss, word, ',')) {
                line_words.push_back(word);
            }
        }
        for (int i{0}; i < line_words.size(); i++) {
            temp.push_back(line_words[i]);
            if ((i + 1) % 4 == 0 || i == line_words.size() - 1) {
                Data.push_back(temp);
                temp.clear();
            }
        }
        for (const vector<string> &i: Data) {
            Goods Good;
            Good.Id = stoi(i[0]);
            Good.Name = i[1];
            Good.Price = stod(i[2]);
            Good.Category = i[3];
            goods_list.push_back(Good);
        }
        return goods_list;
    }


    void Show(const vector<Goods>& goods_list) {
        for (const Goods& i: goods_list) {
            cout << i.Id << "  "<< i.Name<< "  " << i.Price << "  "<< i.Category << "  ";
            cout<< endl;
        }
    }

    void Search (const int id) const {
        for (const Goods &Good : goods_list) {
            if (Good.Id == id) {
                cout << "Requested Goods Name Is: " << Good.Name <<endl;
                return;
            }
        }
        std::cout << "Item with name '" << id << "' not found." <<endl;
    }

    void Add (int &id, string &name, double &price, string &category){
        Goods Good;
        Good.Id = id;
        Good.Name = name;
        Good.Price = price;
        Good.Category = category;
        goods_list.push_back(Good);
    }

    void Delete (int& id){
        for (auto index = goods_list.begin(); index != goods_list.end(); ) {
            if ((*index).Id == id) {
                index = goods_list.erase(index);
            } else {
                ++index;
            }
        }
    }

    void Update(int&id, string &name, double &price, string &category) {
        bool loop {true};
        do{
            for (Goods &Good: goods_list) {
                if (Good.Id == id) {
                        Good.Name = name;
                        Good.Price = price;
                        Good.Category = category;
                }
                loop = false;
            }
        }while(loop);
    }
    void Insertion_Sort() {
        int j;
        for (int i = 1; i < goods_list.size(); i++) {
            Goods compairPoint = goods_list[i];
            j = i - 1;
            while (j >= 0 && goods_list[j].Price > compairPoint.Price) {
                goods_list[j + 1] = goods_list[j];
                j = j - 1;
            }
            goods_list[j + 1] = compairPoint;
        }
    }

private:
    vector<Goods> goods_list;
    string line{}, word{};
    vector<string> temp;
    vector<string> line_words;
    vector<vector<string>> Data;

    };

int main() {

    Store_Data Information;
    Information.Open();

    string name;
    double price;
    string category;
    int id;
    int choice{};
    bool loop{true};
    do {
        cout << "1. Display\n2. Add\n3. Remove\n"
                "4. Edit\n5. Search\n6. Sort\n7. Exit\n>";
        cin >> choice;
        switch (choice) {
            case 1:
                Information.Show(Information.access_Goods());
                break;
            case 2:
                cout << "Enter the good id: " << endl;
                cin >> id;
                cin.ignore();
                cout << "Enter the good name: " << endl;
                getline(cin, name);
                cout << "Enter the good price: " << endl;
                cin >> price;
                cin.ignore();
                cout << "Enter the good category: " << endl;
                getline(cin, category);
                Information.Add(id, name, price, category);
                break;
            case 3:
                cout << "Enter the id of the good you wish to remove: " << endl;
                cin >> id;
                Information.Delete(id);
                break;
            case 4:
                cout << "Enter the id of the good you wish to edit: " << endl;
                cin >> id;
                cin.ignore();
                cout << "Enter the new name: " << endl;
                getline(cin, name);
                cout << "Enter the new price: " << endl;
                cin >> price;
                cin.ignore();
                cout << "Enter the new category: " << endl;
                getline(cin, category);
                Information.Update(id, name, price, category);
                break;
            case 5:
                cin.ignore();
                cout << "Enter the id of the good your looking for: ";
                cin >> id;
                Information.Search(id);
                break;
            case 6:
                Information.Insertion_Sort();
                break;
            case 7:
                loop = false;
                break;
            default:
                break;
        }
    } while (loop);
    return 0;
}
