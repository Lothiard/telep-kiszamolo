#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace Settings {
    enum Mode {
        ora_to_ft,
        ft_to_ora,
        max_modes,
    };
}

class TelepCalculator {
public:
    explicit TelepCalculator(int penz, int oraber, Settings::Mode mode) :
        penz_{penz},
        oraber_{oraber},
        mode_{mode} {}

    static void printIntro() {
        std::cout << "Köszontelek a Telep kalkulátorban!\n";
        std::cout
            << "Ez a program kiszámolja, hogy\n\t1) hány órát kell dolgoznod adott összegű pénzért,\n\t2) mennyi pénzt kereshetsz adott óraszám mellett.\n";

        std::cout << R"(
        ..
.---==+*+*.=:.                                   $$$$$$$$\ $$$$$$$$\ $$\       $$$$$$$$\ $$$$$$$\
    .:...++:.                                    \__$$  __|$$  _____|$$ |      $$  _____|$$  __$$\
--=#*=+:=-  .=:..                                   $$ |   $$ |      $$ |      $$ |      $$ |  $$ |
.-==:==.:.   .::-.                                  $$ |   $$$$$\    $$ |      $$$$$\    $$$$$$$  |
.:-.:-:        .::::.                               $$ |   $$  __|   $$ |      $$  __|   $$  ____/
  .....   ...    ..=-:.                             $$ |   $$ |      $$ |      $$ |      $$ |
       .:..:::.     -.:                             $$ |   $$$$$$$$\ $$$$$$$$\ $$$$$$$$\ $$ |
       :.    .::   .-                               \__|   \________|\________|\________|\__|
       :.      :  .:.
       .-......- .-                              ...........................       ::::
    .....-.:-. ...                               .:                       ..      :    :
   .:..:.   .:.-.                                :.              .        ..      :    :
   :  .-     ..                                  :.             .--.      ..       :.:.
  .:  .:     :                         ::::      ..            .-.-:.     ..         .
      .:     :                       .:   :      .:           .::::.-     .: :::.::.-:
      .:.   .-                   .::-.::... .:.. ::         .::.: - :     .:       -::
       :-..:-.               ...:.. -:::::::..   ::  ....:::..*.:::.:     .:         :.
      .:    :.              .:.      .:.         .:  .:-.:=..:..-.:.      ..        .::.
     .:      :.            .=.        .-.        :.   :::-::--:.-.        ..       .-  :.
     :.      .-       ..:::::::.         .:      ::                       ..      .:    :
 ....:::::::::::::::::--=-==-::::::::::::::::::::-...................:::::-:::::::::::::-:::::::.
    )" << std::endl;
    }

    constexpr double calculateHours() const {
        if (oraber_ <= 0) {
            throw std::invalid_argument(
                "Az órabérnek nagyobbnak kell lennie nullánál!\nAzért ilyen szarul nem fizet Attila.\n"
            );
        }
        return static_cast<double>(penz_) / oraber_;
    }

    constexpr double calculateMoney() const {
        if (oraber_ <= 0) {
            throw std::invalid_argument(
                "Az orabernek nagyobbnak kell lennie nullanal!"
            );
        }
        return static_cast<double>(penz_) * oraber_;
    }

    void printResult() const {
        try {
            if (mode_ == Settings::Mode::ft_to_ora) {
                double orak{calculateHours()};
                int egeszOrak{static_cast<int>(orak)};
                int percek{static_cast<int>((orak - egeszOrak) * 60 + 0.5)};

                if (percek == 60) {
                    ++egeszOrak;
                    percek = 0;
                }

                std::cout << penz_ << " Ft-ért a telepen " << egeszOrak
                          << " órát és " << percek << " percet kell dolgoznod "
                          << oraber_ << " Ft/órás bér mellett.\n";
            } else if (mode_ == Settings::Mode::ora_to_ft) {
                double osszeg{calculateMoney()};
                std::cout << penz_ << " óra alatt a telepen " << osszeg
                          << " Ft-ot kereshetsz " << oraber_
                          << " Ft/órás bér mellett.\n";
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Hiba: " << e.what() << '\n';
        }
    }

private:
    int penz_{};
    int oraber_{};
    Settings::Mode mode_{};
};

int main() {
    TelepCalculator::printIntro();

    int forint_or_time{};
    int oraber{};
    Settings::Mode mode{};

    while (true) {
        std::cout << "Válaszod: ";
        int modeInput;
        if (std::cin >> modeInput && (modeInput == 1 || modeInput == 2)) {
            mode = static_cast<Settings::Mode>(modeInput - 1);
            break;
        } else {
            std::cout << "Kérlek 1-et vagy 2-t válassz!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (true) {
        std::cout << "Add meg az órabért: ";
        if (std::cin >> oraber && oraber > 0) {
            break;
        } else {
            std::cout << "Testver ne jatsszal velem\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (mode == Settings::Mode::ft_to_ora) {
        while (true) {
            std::cout << "Add meg a pénzt: ";
            if (std::cin >> forint_or_time && forint_or_time > 0) {
                break;
            } else {
                std::cout << "Testver ne jatsszal velem\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
            }
        }
    } else if (mode == Settings::Mode::ora_to_ft) {
        while (true) {
            std::cout << "Add meg az óraszámot: ";
            if (std::cin >> forint_or_time && forint_or_time > 0) {
                break;
            } else {
                std::cout << "Testver ne jatsszal velem\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
            }
        }
    }

    TelepCalculator calculator(forint_or_time, oraber, mode);
    calculator.printResult();

    std::cout << "Nyomj entert a kilepeshez...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}
