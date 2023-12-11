#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

// ����������� �������� ������ Product
class Product {
public:
    Product(const std::string& name, double price, int quantity) : name(name), price(price), quantity(quantity) {}
    ~Product() {}

    void displayInfo() const {
        std::cout << "Name: " << name << ", Price: " << price << ", Quantity: " << quantity << std::endl;
    }
    void saveToFile(std::ofstream& outFile) const {
        outFile << name << " " << price << " " << quantity << " ";
    }

    double getPrice() const {
        return price;
    }

    const std::string& getName() const {
        return name;
    }
    int getQuantity() const {
        return quantity;
    }


protected:
    std::string name;
    double price;
    int quantity;
};

// ��������� ����� Pair ��� �������� ���� ������������� ��������
template <typename T1, typename T2>
class Pair {
public:
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

private:
    T1 first;
    T2 second;
};

// STL: ���������� ��������� �� ����
void sortProductsByPrice(std::vector<Product>& products) {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getPrice() < b.getPrice();
        });
}

// ������������ �� �������� ������ Product
class Clothing : public Product {
public:
    using Product::Product;  // ������������ ������������ �������� ������

    void displayInfo() const {
        Product::displayInfo();
        // �������������� ���������� ��� ������
    }
};

class Electronics : public Product {
public:
    using Product::Product;

    void displayInfo() const {
        Product::displayInfo();
        // �������������� ���������� ��� �����������
    }
};

// ���� � �����
void addProduct(std::vector<Product>& products, const Product& item) {
    products.push_back(item);
}

void searchProduct(const std::vector<Product>& products, const std::string& productName) {
    // ���������� ������
}



// �������������� ������
void loadFromFile(std::vector<Product>& products, const std::string& filename) {
    // ���������� �������� �� �����
}

void modifyProduct(std::vector<Product>& products, const std::string& productName, double newPrice) {
    // ���������� ��������� ���� ��������
}

// �������������� ��������
class StockInfo {
public:
    StockInfo(int totalQuantity) : totalQuantity(totalQuantity) {}

private:
    int totalQuantity;
    // �������������� ������
};
void saveProductsToFile(const std::vector<Product*>& products, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ������." << std::endl;
        return;
    }

    for (const auto* student : products) {
        student->saveToFile(outFile);
    }

    outFile.close();
}


int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<Product*> products;

    int choice;
    std::string filename;

    do {
        std::cout << "����:" << std::endl;
        std::cout << "1. �������� �������" << std::endl;
        std::cout << "2. ����� �������" << std::endl;
        std::cout << "3. ������� ������ ���������" << std::endl;
        std::cout << "4. ��������� � ����" << std::endl;
        std::cout << "5. ����������� �� ����" << std::endl;
        std::cout << "6. �����" << std::endl;

        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name;
            double price;
            int quantity;
            std::string type;
            std::cout << "������� ������ ��������:" << std::endl;
            std::cout << "���: ";
            std::cin >> name;
            std::cout << "���������: ";
            std::cin >> price;
            std::cout << "����������: ";
            std::cin >> quantity;
            std::cout << "���: ";
            std::cin >> type;
            if (type == "Clothing")
            {
                Clothing cl(name, price, quantity);
            }
            if (type == "Electronics")
            {
                Electronics el(name, price, quantity);
            }
            products.push_back(new Product(name, price, quantity));

            break;
        }
        case 2: {
            std::string name;
            std::cout << "������� ������ �������� ��� ������:" << std::endl;
            std::cout << "��������: ";
            std::cin >> name;


            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name;
                });

            if (it != products.end()) {
                (*it)->displayInfo();
            }
            else {
                std::cout << "������� �� ������." << std::endl;
            }

            break;
        }
        case 3: {
            std::cout << "������ ���������:" << std::endl;
            for (const auto* product : products) {
                product->displayInfo();
            }
            break;
        }
        case 4: {
            std::cout << "������� ��� ����� ��� ���������� ������: ";
            std::cin >> filename;
            saveProductsToFile(products, filename);
            break;
        }
        case 5: {
            std::sort(products.begin(), products.end());
            std::cout << "������ ��������� ������������ �� ����." << std::endl;
            break;
        }
        case 6:
            std::cout << "�����." << std::endl;
            break;
        default:
            std::cout << "�������� �����." << std::endl;
        }
    } while (choice != 6);

    for (const auto* product : products) {
        delete product;
    }

    return 0;
}
