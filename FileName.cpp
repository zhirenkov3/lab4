#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

// Определение базового класса Product
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

// Шаблонный класс Pair для хранения пары характеристик продукта
template <typename T1, typename T2>
class Pair {
public:
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

private:
    T1 first;
    T2 second;
};

// STL: Сортировка продуктов по цене
void sortProductsByPrice(std::vector<Product>& products) {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getPrice() < b.getPrice();
        });
}

// Наследование от базового класса Product
class Clothing : public Product {
public:
    using Product::Product;  // Наследование конструктора базового класса

    void displayInfo() const {
        Product::displayInfo();
        // Дополнительная информация для одежды
    }
};

class Electronics : public Product {
public:
    using Product::Product;

    void displayInfo() const {
        Product::displayInfo();
        // Дополнительная информация для электроники
    }
};

// Меню и файлы
void addProduct(std::vector<Product>& products, const Product& item) {
    products.push_back(item);
}

void searchProduct(const std::vector<Product>& products, const std::string& productName) {
    // Реализация поиска
}



// Дополнительные задачи
void loadFromFile(std::vector<Product>& products, const std::string& filename) {
    // Реализация загрузки из файла
}

void modifyProduct(std::vector<Product>& products, const std::string& productName, double newPrice) {
    // Реализация изменения цены продукта
}

// Дополнительные сущности
class StockInfo {
public:
    StockInfo(int totalQuantity) : totalQuantity(totalQuantity) {}

private:
    int totalQuantity;
    // Дополнительные методы
};
void saveProductsToFile(const std::vector<Product*>& products, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
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
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить продукт" << std::endl;
        std::cout << "2. Найти продукт" << std::endl;
        std::cout << "3. Вывести список продуктов" << std::endl;
        std::cout << "4. Сохранить в файл" << std::endl;
        std::cout << "5. Сортировать по цене" << std::endl;
        std::cout << "6. Выход" << std::endl;

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name;
            double price;
            int quantity;
            std::string type;
            std::cout << "Введите данные продукта:" << std::endl;
            std::cout << "Имя: ";
            std::cin >> name;
            std::cout << "Стоимость: ";
            std::cin >> price;
            std::cout << "Количество: ";
            std::cin >> quantity;
            std::cout << "Тип: ";
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
            std::cout << "Введите данные продукта для поиска:" << std::endl;
            std::cout << "название: ";
            std::cin >> name;


            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                return product->getName() == name;
                });

            if (it != products.end()) {
                (*it)->displayInfo();
            }
            else {
                std::cout << "Продукт не найден." << std::endl;
            }

            break;
        }
        case 3: {
            std::cout << "Список продуктов:" << std::endl;
            for (const auto* product : products) {
                product->displayInfo();
            }
            break;
        }
        case 4: {
            std::cout << "Введите имя файла для сохранения данных: ";
            std::cin >> filename;
            saveProductsToFile(products, filename);
            break;
        }
        case 5: {
            std::sort(products.begin(), products.end());
            std::cout << "Список продуктов отсортирован по цене." << std::endl;
            break;
        }
        case 6:
            std::cout << "Выход." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    } while (choice != 6);

    for (const auto* product : products) {
        delete product;
    }

    return 0;
}
