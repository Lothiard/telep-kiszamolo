#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>

class TelepCalculator {
public:
    explicit TelepCalculator(int penz, int oraber) :
        penz_{penz},
        oraber_{oraber}
    {}

    static void printIntro() {
        std::cout << "Telep kalkulator\n";
        std::cout << "Ez a program kiszamolja, hany orat kell dolgoznod adott osszegu penzert.\n";
    }

    double calculateHours() const {
        if (oraber_ <= 0) {
            throw std::invalid_argument("Az orabernek nagyobbnak kell lennie nullanal!");
        }
        return static_cast<double>(penz_) / oraber_;
    }

    void printResult() const {
        try {
            double orak{ calculateHours() };
            int egeszOrak{ static_cast<int>(orak) };
            int percek{ static_cast<int>((orak - egeszOrak) * 60 + 0.5) };

            if (percek == 60) {
                ++egeszOrak;
                percek = 0;
            }

            std::cout << "A(z) " << penz_ << " Ft-ert a telepen "
                      << std::setfill('0') << std::setw(2) << egeszOrak << ":"
                      << std::setfill('0') << std::setw(2) << percek
                      << " orat kell dolgoznod " << oraber_ << " Ft/oras ber mellett.\n";
        } catch (const std::invalid_argument& e) {
            std::cerr << "Hiba: " << e.what() << '\n';
        }
    }

private:
    int penz_{};
    int oraber_{};
};

int main() {
    int forint{};
    int oraber{};

    TelepCalculator::printIntro();

    while (true) {
        std::cout << "Add meg az oraber osszeget forintban: ";
        if (std::cin >> oraber && oraber > 0) {
            break;
        } else {
            std::cout << "Kerlek pozitiv egesz szamot adj meg!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (true) {
        std::cout << "Add meg az osszeget forintban: ";
        if (std::cin >> forint && forint > 0) {
            break;
        } else {
            std::cout << "Kerlek pozitiv egesz szamot adj meg!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    TelepCalculator calculator(forint, oraber);
    calculator.printResult();

    std::cout << "Nyomj egy gombot a kilepeshez...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}
